
// Python includes
#include <Python.h>

// STD includes
#include <stdio.h>

//-----------------------------------------------------------------------------
static PyObject *hello_example(PyObject *self, PyObject *args)
{
  // Unpack a string from the arguments
  const char *strArg;
  if (!PyArg_ParseTuple(args, "s", &strArg))
    return NULL;

  // Print message and return None
  PySys_WriteStdout("Hello, %s!\n", strArg);
  Py_RETURN_NONE;
}

//-----------------------------------------------------------------------------
static PyObject *elevation_example(PyObject *self, PyObject *args)
{
  // Return an integer
  return PyLong_FromLong(21467L);
}

//-----------------------------------------------------------------------------
static PyMethodDef plunge_methods[] = {
  {
    "hello",
    hello_example,
    METH_VARARGS,
    "Prints back 'Hello <param>', for example example: hello.hello('you')"
  },

  {
    "elevation",
    elevation_example,
    METH_VARARGS,
    "Returns elevation of Nevado Sajama."
  },
  {NULL, NULL, 0, NULL}        /* Sentinel */
};


static struct PyModuleDef plunge_module_def = {
  PyModuleDef_HEAD_INIT,
  "_plunge",
  "\"Jump into the water of Python extensions!\" module",
  -1,
  plunge_methods
};

PyMODINIT_FUNC PyInit__plunge(void)
{
  return PyModule_Create(&plunge_module_def);
}
