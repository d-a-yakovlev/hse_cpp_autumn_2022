#include <stdio.h>

#include <Python.h>


PyObject* cjson_loads(PyObject* self, PyObject* args)
{
    PyObject* dict = NULL;

    return dict;
}


PyObject* cjson_dumps(PyObject* self, PyObject* args)
{
    return Py_BuildValue("s", "plugplug");
}


static PyMethodDef methods[] = {
    { "loads", cjson_loads, METH_VARARGS, "Load dict from JSON string"},
    { "dumps", cjson_dumps, METH_VARARGS, "Dict to string"},
    { NULL, NULL, 0, NULL}
};


static struct PyModuleDef cjsonmodule = {
    PyModuleDef_HEAD_INIT, "cjson",
    NULL, -1, methods
};


PyMODINIT_FUNC PyInit_cjson(void)
{
    return PyModule_Create( &cjsonmodule);
};