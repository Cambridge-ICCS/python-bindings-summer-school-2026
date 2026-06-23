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
The slides for this workshop can be viewed here: [\<TODO\>](https://iccs.cam.ac.uk/)

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

1. Open this repository in a [GitHub Codespace](https://docs.github.com/en/codespaces/overview)
   by clicking the green **Code** button on the repository page and selecting **Open with Codespaces**.
2. Wait for the devcontainer to build and start — this installs all system dependencies automatically.
3. Inside the terminal, create and activate a Python virtual environment before starting an exercise:
   ```bash
   python3 -m venv .venv
   source .venv/bin/activate
   ```


## Installation and setup

TODO

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
