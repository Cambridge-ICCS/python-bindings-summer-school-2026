#include <iostream>
#include <stdexcept>
#include <functional>

// Pybind 11
#include <pybind11/pybind11.h>

// Enables Numpy arrays
#include <pybind11/numpy.h>

// Enables callbacks
#include <pybind11/functional.h>

// Solution:
// Need to add this header to return a std::vector
#include <pybind11/stl.h>


namespace py = pybind11;

using py::literals::operator""_a;

/*<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>*/
/* Here goes C++ code                                                         */


// TASK 1:

// Note that now we can use a pure C++ function that needs no knowledge of or
// linking with the Python C API
//
// It could have just come from a codebase that was not designed to be used in Python.
void splash_cpp(const std::string &name) {
    std::cout << name << " made a splash!🌊\n";
}


// Pybind11 automatically translates C++ exceptions to Python ones
void raise_exception(bool should_raise) {
    if (should_raise) {
        // Note the translation table for exception types:
        // https://pybind11.readthedocs.io/en/stable/advanced/exceptions.html#built-in-c-to-python-exception-translation
        throw std::runtime_error("Exception as requested ;-)");
    }
}

// Multiple splash again: Solution
void multiple_splash(const std::string &name, int count) {
    if (count < 0) {
        throw py::value_error("count must be non-negative");
    }
    for (int i = 0; i < count; i++) {
        std::cout << name << " made a splash!🌊\n";
    }
}

// TASK 2:

// We can take Numpy arrays directly as arguments
void print_numpy_array(py::array_t<double> numpy_array) {
    py::ssize_t size = numpy_array.size();

    std::cout << "Size: " << size << " [ ";
    for (py::ssize_t i = 0; i < size; i++) {
        std::cout << numpy_array.at(i) << ",";
    }
    std::cout << "]\n";
}


py::array_t<int> apply_on_range(std::function<int(int)> func, int start, int end) {
    if (end <= start) {
        // We can build an uninitialised numpy array by providing
        // just the sizes to the constructor
        return py::array_t<int>({0});
    }
    const int size = end - start;
    py::array_t<int> out({size});
    for (int i = 0; i < size; i++ ) {
        // We need to use a special getter to get 'mutable' reference to
        // an element
        out.mutable_at(i) = func(start + i);
    }
    return out;
}

// Solution: returning numpy array
py::array_t<double> interpolate_np(std::function<double(double)> func, py::array_t<double> grid) {
    py::array_t<double> out({grid.size()});
    for (py::ssize_t i = 0; i < grid.size(); i++) {
        out.mutable_at(i) = func(grid.at(i));
    }
    return out;
}

// Solution: returning std::vector
std::vector<double> interpolate(std::function<double(double)> func, py::array_t<double> grid) {
    std::vector<double> out;
    py::ssize_t size = grid.size();
    out.reserve(size);

    for (py::ssize_t i = 0; i < size; i++) {
        out.push_back(func(grid.at(i)));
    }
    return out;
}


/*<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>*/
/* Here goes the Python bindings code with pybind11                           */


// This defines PyInit_plunge_pyb function for us
// Macro `PYBIND11_MODULE` takes care of the boilerplate
// We get the `m` module handle that allows us to populate it with new entries
//
PYBIND11_MODULE(plunge_pyb, m) {

    // Add a module docstring
    // We can use C++'s Raw string literals https://en.cppreference.com/cpp/language/string_literal
    // to preserve newlines 'as is'
    m.doc() = R"pbdoc(
"Jump into the water of Python extensions!" module
    )pbdoc";

    // Adding a function definition is 'just like Python'
    // Use `def` to provide a name, and the `&` operator to take 'address' of the
    // function
    //
    // Pybind11 allows us to easily specify argument names (so we can call them
    // using the keyword argument syntax; try it out: `plunge_pyb.splash(name="me")` )
    m.def("splash", &splash_cpp, 
        R"pbdoc(
Makes a splash!
        
Here you can put a docstring ;-) 
Don't forget to view it in REPL with 'help'.)pbdoc", 
        py::arg("name"));


    // C++ offers a quality of life feature of "custom string literals"
    // We can use custom suffix `_a` to translate:
    // "str"_a -> py::arg("str")
    //
    // We need to declare and use it explicitly:
    // see: `using py::literals::operator""_a;`
    m.def("raise_exception", &raise_exception, 
        "If called with true raises an exception", 
        "should_raise"_a);

    // Multiple splash again: Solution
    m.def("multiple_splash", &multiple_splash, 
        "Makes a splash N times!", 
        py::arg("name"), 
        "count"_a);


    m.def("print_numpy_array", &print_numpy_array,
        "Prints a numpy array in one line with a element count",
        "array"_a
    );

    m.def("apply_on_range", &apply_on_range,
        "Apply python function on a range of integers and return the result",
        "func"_a, "start"_a, "end"_a
    );

    // Solution
    m.def("interpolate", &interpolate,
        "Apply python function on a numpy grid",
        "func"_a, "grid"_a
    );
    m.def("interpolate_np", &interpolate_np,
        "Apply python function on a numpy grid",
        "func"_a, "grid"_a
    );
}
