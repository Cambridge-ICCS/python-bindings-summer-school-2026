// Python includes
#define PY_SSIZE_T_CLEAN
#include <Python.h>


//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
// Functions
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

static PyObject *splash_in_cpp(PyObject */*self*/, PyObject *args)
{
  const char *name;

  // Doc: 
  // - https://docs.python.org/3/c-api/arg.html#c.PyArg_ParseTuple
  // - https://docs.python.org/3/c-api/arg.html#parsing-arguments-and-building-values
  if (!PyArg_ParseTuple(args, "s", &name))
    return NULL;

  // Doc: https://docs.python.org/3/c-api/sys.html#c.PySys_WriteStdout
  PySys_WriteStdout("%s made a splash!\U0001F30A\n", name);
  Py_RETURN_NONE;
}

// Note that this takes single argument via PyObject pointer
static PyObject *raise_exception(PyObject */*self*/, PyObject *arg) 
{
  // https://docs.python.org/3/c-api/object.html#c.PyObject_IsTrue
  int raise = PyObject_IsTrue(arg);

  // PyObject_IsTrue may fail (e.g. when bool(arg) raises exception)
  // In that case Python requires us to just return
  // The exception and its message is set by the callee
  if (raise < 0)
    return NULL;
  
  if (raise) {
    PyErr_SetString(PyExc_RuntimeError, "Exception as requested ;-)");
    return NULL;
  }

  // If it does not raise it returns normally
  Py_RETURN_NONE;
}


static PyObject *multiple_splash(PyObject */*self*/, PyObject *args)
{
  // Unpack the argument tuple
  const char *name;
  int count;

  if (!PyArg_ParseTuple(args, "si", &name, &count))
    return NULL;

  if (count < 0) {
    PyErr_SetString(PyExc_ValueError, "Negative count");
    return NULL;
  }

  for (int i = 0; i < count; i++){
    PySys_WriteStdout(u8"%s made a splash!\U0001F30A\n", name);
  }
  
  Py_RETURN_NONE;
}

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
// Module Definition
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

static PyMethodDef plunge_methods[] = {
  {
    "splash",
    splash_in_cpp,
    // https://docs.python.org/3/c-api/structures.html#c.METH_VARARGS
    METH_VARARGS, // <- This indicates function takes a Tuple as argument 
    "Makes a splash!\n\nHere you can put a docstring ;-). "
    "Don't forget to view it in REPL with 'help'."
  },
  {
    "raise_exception",
    raise_exception,
    // https://docs.python.org/3/c-api/structures.html#c.METH_O
    METH_O, // <- This indicates 1 argument function (passed as generic PyObject*)
    "If called with true raises an exception"
  },
  {
    "multiple_splash",
    multiple_splash,
    METH_VARARGS,
    "Makes a splash N times!"
  },
  {NULL, NULL, 0, NULL} /* Sentinel */
};

// Doc: https://docs.python.org/3/c-api/module.html#c.PyModuleDef
static struct PyModuleDef plunge_module_def = {
  PyModuleDef_HEAD_INIT,
  "plunge",
  "\"Jump into the water of Python extensions!\" module",
  -1,
  plunge_methods,
  NULL,
  NULL,
  NULL,
  NULL
};

// Note that we are using a legacy 'single-phase' initialisation
// https://docs.python.org/3/c-api/extension-modules.html#legacy-single-phase-initialization
PyMODINIT_FUNC PyInit_plunge(void)
{
  return PyModule_Create(&plunge_module_def);
}
