<img src="./images/UCAM_ICCS_Logo.png"  width="600">

# Python Bindings to Compiled Languages

This repository contains documentation, resources, and code for the 'Python Bindings for compiled languages'
session designed and delivered by Mikolaj Adam Kowalski of [ICCS](https://github.com/Cambridge-ICCS).
All materials, including slides and videos, are available such that individuals can cover the
course in their own time.

## Contents

- [Learning Objectives](#learning-objectives)
- [Teaching material](#teaching-material)
- [Preparation and prerequisites](#preparation-and-prerequisites)
- [Installation and setup](#installation-and-setup)
- [License information](#license)
- [Contribution Guidelines and Support](#contribution-guidelines-and-support)


## Learning Objectives

This course is intended as a first introduction to binding external code written
in a compiled language (C++) to Python as a Python extension module. It does
not attempt to cover every detail of the process, but rather give you a flavour
of what to expect.

By the end of this course you should be able to:

- Explain why Python extension modules are needed and when they are the right tool
- Understand the structure of the Python C API for writing extension modules
- Use [pybind11](https://pybind11.readthedocs.io/en/stable/) to expose C++ functions to Python
- Use pybind11 to work with NumPy arrays and call Python functions from C++

## Teaching Material

### Slides
The slides for this workshop can be viewed at: https://cambridge-iccs.github.io/python-bindings-summer-school-2026/

### Exercises

The repository contains two exercises, each in their own directory:

| Exercise | Topic | Description |
|---|---|---|
| [exercise_1](exercise_1/) | Python C API | Build a "hello world" extension module using the low-level Python C API. Add a `multiple_splash` function that prints a message a given number of times. |
| [exercise_2](exercise_2/) | pybind11 | Re-implement the same extension using [pybind11](https://pybind11.readthedocs.io/en/stable/), then add an `interpolate` function that applies a Python callable to a NumPy array. |

Each exercise directory contains its own `README.md` with detailed instructions and tasks.

### Worked Solutions

Fully worked solutions for both exercises are provided in the [solutions/](solutions/) directory.


## Preparation and prerequisites

### Prerequisites

- Prior experience with Python is assumed. You should be comfortable writing and reading Python code
- Basic familiarity with C++, but no expert knowledge is required. Just enough to read C++ code will be sufficient.
- A laptop and a GitHub account. The course will use [GitHub Codespaces](https://docs.github.com/en/codespaces/about-codespaces/what-are-codespaces) as the development environment.


### Preparation

In the exercises we will be writing C++ code. A short refresher on the basics 
of the syntax may be useful. We restrict ourselves to a basic subset of the 
language. Topics that may need to be reviewed include:

- Writing C/C++ functions
- Pass by value and pass by reference
- `#include <...>` and `#include "..."` directives
- Raw string literals (e.g. `R"(Hello, world!)"` see 
  [cppreference](https://en.cppreference.com/w/cpp/language/string_literal))
- `std::function` [class](https://en.cppreference.com/cpp/utility/functional/function) and 
  [lambda expressions](https://en.cppreference.com/cpp/language/lambda).
- Working with `std::vector` and `std::string` types
- Using the `&` operator to take the address of entities (e.g. variables or functions)
- Using `.` and `->` operators to access members of a `struct` or `class`
- Using `{}` to initialise a `struct`


## Installation and setup

1. Open this repository in a [GitHub Codespace](https://docs.github.com/en/codespaces/overview)
    1. Click the green "Code" button and select "Codespace" tab
    2. Click on "Create codespace on main" to start a new codespace
    3. A new browser tab will open with the codespace. Be patient, it can take a few minutes to 
       start up.
    4. Once the codespace is ready, you will see a VS Code interface with a terminal open at the 
       bottom.
    5. If you close the tab, you can return to the codespace by going to the "Codespaces" tab 
       in the repository and clicking on the codespace name. It will take you back to where 
       you left off.
    6. At the end of the course go to the "Codespaces" tab in the repository and click on the "..." 
       next to the codespace name. Select "Delete codespace" to free up resources.

2. Open the terminal in the codespace, then create and activate a Python virtual 
   environment before starting an exercise:
   ```bash
   python3 -m venv .venv
   source .venv/bin/activate
   ```
   The `.venv` folder is part of the workspace, so it persists across codespace restarts. 
   If you open a new terminal, remember to re-activate with `source .venv/bin/activate`.

## Building and running the exercises

Every exercise in this course can be built in one of the two ways. It is most
convenient to use both, depending on the context.

### Build locally with cmake

This builds the module inside a `build/` subdirectory at the root of the exercise.
It does not install the module in your virtual environment, so it will only be importable
if you **invoke python from the `build` folder**. This is recommended for iteration and debugging.

You can build with the following commands:
```bash
mkdir -p build
cd build
cmake ..
cmake --build .
```

After each change to the source code, re-run `cmake --build .` from within the `build/` folder.

### Install with pip

This builds and installs the module into your virtual environment, i.e. it
places the compiled binary in the `site-packages` folder. The module can then be
imported from any directory.

You can build and install with the following command:
```bash
pip install -v .
```
The `-v` (verbose) flag shows the build system and compiler output.

After each change to the source code, reinstall:
```bash
pip install -v .
```

Editable installs (`pip install -e .`) are not supported for these exercises.
You must reinstall after every change.

Once you are done with the exercise, you can uninstall it with:
```bash
pip uninstall <library_name>
```

## License

The code materials in this project are licensed under the [MIT License](LICENSE).

The teaching materials are licensed under a separate
Creative Commons License [CC BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/). 

## Contribution Guidelines and Support

If you spot an issue with the materials please let us know by
[opening an issue](https://github.com/Cambridge-ICCS/python-bindings-summer-school-2026/issues)
here on GitHub clearly describing the problem.

If you are able to fix an issue that you spot, or an
[existing open issue](https://github.com/Cambridge-ICCS/python-bindings-summer-school-2026/issues)
please get comment on the issue or just drop in a pull request.


To contribute back to the repository please first
[fork it](https://github.com/Cambridge-ICCS/python-bindings-summer-school-2026/fork),
make the necessary changes to fix the problem, and then open a pull request back to
this repository.

If you would like support using these materials, adapting them to your needs, or
delivering them please get in touch either via GitHub or via
[ICCS](https://github.com/Cambridge-ICCS).
