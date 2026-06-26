# Exercise 1: Hello World Python Extension

The goal of this exercise is to create, build and install a simple Python extension
module written in C++. The build system and workflow are prepared for you.

Your task will be to add a new function to the module.

## Prerequisites

This exercise has been prepared and developed on Ubuntu 22.04 with Python 3.11,
but it should work on other Linux distributions and Python versions as well.
MacOS and Windows have not been tested.

The project requires you to have the following available:
- C and C++ compiler (e.g. g++)
- CMake (version 3.18 or higher)
- Python development headers (e.g. 'python3-dev' package)
- Python and pip

## Building and testing the extension

### Setting up the environment

To keep things clean, we will work inside a Python virtual environment.
You can create one with the following command:

```bash
python3 -m venv name-of-your-venv
```
and then activate it:

```bash
source name-of-your-venv/bin/activate
```

The only dependency we need to install is the toolkit that will help us build
Python extensions. In this exercise we will use [scikit-build-core](https://scikit-build-core.readthedocs.io/en/latest/)
which is a modern build system for Python extensions. You can install it with pip:

```bash
pip install scikit-build-core
```

### Building and installing the extension

To build the extension module, simply navigate to the exercise directory
(the one that contains the `pyproject.toml` file) and invoke pip:
```bash
pip install . -v
```
Note that we added the optional `--verbose` (`-v`) flag so the output of the build
process with CMake will be printed. This is useful to understand what is going on
behind the scenes, but not necessary in general.

You might have noted that we did not use an 'editable' install (i.e. `pip install -e .`).
Editable installs are not supported for these exercises. When you iterate on your
project you will want to explicitly reinstall the package after each change:
```bash
pip install . -v
```

[!WARNING]
    We have named our package `plunge`, but there is an existing PyPI package
    [with the same name](https://pypi.org/project/plunge/). Take care when installing
    since if you invoke:
    ```bash
    pip install plunge
    ```
    it will install **the PyPI package** instead of the exercise one.


## Task

Inside the `plunge.cpp` you may notice that there are two functions already defined:
- `splash` that takes a string and prints a message to the console
- `raise_exception` that optionally raises an exception

What you need to do is the following:

1. Implement the `multiple_splash` function that takes a string and an integer count
   and prints the message to the console `count` times. If the count is negative,
   it should raise a `ValueError` exception.

Good luck!

## Extra questions
If you have solved the main task and there is still some time left, here are some
prompts to let you explore further:

- Have you tried to call `raise_exception` with a value that is not `bool` (e.g. `7`)?
  What happens then? Is this correct behaviour?
- Try to create a module with an empty methods list. What happens when you remove
  the sentinel value? Why does it behave that way?

## Notes

### Multi-phase vs legacy Single-phase initialisation

The example we are working with is not how one would write an extension module
nowadays. We are building a module using a [legacy single-phase initialisation](https://docs.python.org/3/c-api/extension-modules.html#legacy-single-phase-initialization).
This works better for an example since the setup is easier, but the resulting
extension module may not work correctly in all contexts, especially when
'sub-interpreters' are involved (e.g. new free-threaded Python). The recommended
way to build a module is using a [multi-phase initialisation](https://peps.python.org/pep-0489/) where
module creation is split into multiple phases.


### Acknowledgments

When preparing this exercise, I have used the following great resources:

    - scikit-build examples: https://github.com/scikit-build/scikit-build-sample-projects
    - The Python manual: https://docs.python.org/3/extending/extending.html#writing-extensions-in-c

I would like to express the gratitude to their authors and please refer to them
to learn more.
