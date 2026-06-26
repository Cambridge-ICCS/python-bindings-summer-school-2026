# Exercise 2: Python Extension with Pybind11

The goal of this exercise is to show how we can use
[Pybind11](https://pybind11.readthedocs.io/en/stable/) to create a Python
extension with similar functionality to the Hello World example from Exercise 1.

Hopefully it will show that writing a Python extension can be simple and
not very invasive for the C++ side of the code.


## Prerequisites

This exercise was prepared and developed on Ubuntu 22.04 with Python 3.11,
but it should work on other Linux distributions and Python versions as well.
It will run out of the box in the GitHub Codespace included in the repository.

The project requires the following:
- C and C++ compiler (e.g. g++)
- CMake (version 3.16 or higher)
- Python development headers (e.g. python3-dev)
- Python and pip

## Building and testing the extension

### Setting up the environment

Same as in Exercise 1, we will work inside a Python virtual
environment. You can create one with the following command:

```bash
python3 -m venv name-of-your-venv
```
and then activate it:

```bash
source name-of-your-venv/bin/activate
```

### Building and installing the extension

To build the extension module, simply navigate to the exercise directory
(the one that contains the `pyproject.toml` file) and invoke pip:
```bash
pip install . -v
```
Note that we added the optional `--verbose` (`-v`) flag so the output of the
build process with CMake will be printed. This is useful to understand what
is going on behind the scenes, but not necessary in general.

You might have noted that we did not use an 'editable' install
(i.e. `pip install -e .`). Editable installs are not supported for these exercises.
When you iterate on your project you will want to explicitly reinstall the
package after each change:
```bash
pip install . -v
```

If needed, you can uninstall the package with:
```bash
pip uninstall -y plunge_pyb
```

## Tasks

The Python bindings are defined together with the C++ code in the
`src/plunge_pyb.cpp` file. You will notice that there are a couple of functions
already defined in that file:

### Task 1: Re-implement the `multiple_splash` function

You may notice that two functions familiar from Exercise 1 are already
defined in the `plunge_pyb.cpp` file. These are:
- `splash` that takes a string and prints a message to the console
- `raise_exception` that optionally raises an exception.

Have a look at them and compare them to the versions from Exercise 1. Finally,
re-implement the `multiple_splash` function. As a reminder, this is what it is
supposed to do:

- `multiple_splash` takes a string and an integer `n` and prints the message
  to the console `n` times. If the count is negative, it should raise
  a `ValueError` exception.

### Task 2: Implement the `interpolate` function

Since pybind11 makes writing extensions easier, we can do some more adventurous
things! We can use `numpy`-compatible interfaces to operate on arrays or even
call Python functions from C++.

In the `plunge_pyb.cpp` you will find two extra functions:

- `print_numpy_array` that takes a numpy array and prints it to the console
- `apply_on_range` that takes a function and applies it on a range of integers.

Use them as a reference to implement an `interpolate` function that will take
a numpy array of x values and a python function `f` and return a new numpy array
with the values of `f(x)` for each element in the input array.

Try two different versions. One that returns `std::vector<double>` and one that
returns `py::array_t<double>`.
