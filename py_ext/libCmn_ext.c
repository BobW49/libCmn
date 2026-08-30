// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//              C Extension for Python
//****************************************************************
/*
 * Program
 *			C Extension for Python
 * Purpose
 *			This object pr
 *          generation process.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	11/23/2019 Generated
 */



//----------------------------------------------------------------
//              Parse HJSON String
//----------------------------------------------------------------





#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "hjson.h"

// ================================================================
//            Convert C variables to Python variables
// ================================================================

static PyObject* py_create_hash(void* ctx) {
    return PyDict_New();
}

static PyObject* py_create_array(void* ctx) {
    return PyList_New(0);
}

static PyObject* py_create_integer(
    void* ctx, 
    const char* numstr      // NUL-Terminated String
) {
    return PyLong_FromString(numstr, NULL, 0);
}

static PyObject* py_create_string(
    void* ctx, 
    const char* utf8,       // NUL-Terminated String
    size_t len              // Size in bytes of the string, not character count
) {
    return PyUnicode_FromStringAndSize(utf8, len);
}

static PyObject* py_create_number(
    void* ctx, 
    const char* numstr,     // NUL-Terminated String
    bool isFloat
) {
    if (isFloat)
        return PyFloat_FromDouble(atof(numstr));
    return PyLong_FromString(numstr, NULL, 10);
}

static PyObject* py_create_bool(
    void* ctx, 
    bool value
) {
    return Py_NewRef(value ? Py_True : Py_False);
}

static PyObject* py_create_false(
    void* ctx
) {
    return Py_NewRef(Py_False);
}

static PyObject* py_create_true(
    void* ctx
) {
    return Py_NewRef(Py_True);
}

static PyObject* py_create_null(void* ctx) {
    Py_RETURN_NONE;
}



// ================================================================
//  Registration function you will call from your overridden hooks
// ================================================================

static PyObject* py_hjson_set_hooks(PyObject* self, PyObject* args)
{
    HJSON_DATA* hjson;
    if (!PyArg_ParseTuple(args, "K", (unsigned long long*)&hjson))
        return NULL;

    // You will call this from C after creating the HJSON object
    // and before parsing.

    // Example of what you will do in C:
    // hjson->pythonHooks.pNewHash   = (void*(*)(void*))py_create_hash;
    // hjson->pythonHooks.pNewArray  = (void*(*)(void*))py_create_array;
    // etc.

    Py_RETURN_NONE;
}



// ================================================================
//  Main parse function
// ================================================================

static 
PyObject*       py_hjson_parse_file(
    PyObject        *self, 
    PyObject        *args
)
{
    const 
    char            *filepath;
    NODE_DATA       *pNode = OBJ_NIL;
    NODEARRAY_DATA  *pArray = OBJ_NIL;
    NODEHASH_DATA   *pHash = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    int             iRc;

    if (!PyArg_ParseTuple(args, "s", &filepath))
        return NULL;

    HJSON_DATA      *pHJSON = hjson_NewFromPath(NULL, filepath, 4);   // tabSize = 4
    if (!pHJSON) {
        PyErr_SetString(PyExc_RuntimeError, "Failed to create HJSON parser");
        return NULL;
    }

    pNode = hjson_ParseFileHash(pHJSON);
    if (!pNode) {
        PyErr_SetString(PyExc_RuntimeError, "Failed to parse HJSON file");
        return NULL;
    }
    iRc = Node_CompareA(pNode, "hash");    
    if (!(0 == iRc)) {
        PyErr_SetString(PyExc_RuntimeError, "Top node was not a hash");
        return NULL;
    }
    pHash = Node_getData(pNode);

    // === This is where you will set your hooks from C side ===
    // For now we just expose the object so you can set them
    PyObject* result = PyCapsule_New(hjson, "hjson.HJSON_DATA", NULL);
    if (!result) {
        obj_Release(hjson);
        return NULL;
    }

    // You can also add a convenience wrapper later

    return result;   // User will call set_hooks then parse
}



// ================================================================
//              Module Definitions for Python
// ================================================================


// Module definition
static PyMethodDef methods[] = {
    {"hjson_parse_file",  py_hjson_parse_file, METH_VARARGS, "Parse Custom relaxed HJSON - returns Python Object"},
    // {"set_hooks",      py_hjson_set_hooks,  METH_VARARGS, "Set Python creation hooks"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef module = {
    PyModuleDef_HEAD_INIT,
    "libCmn",
    "Interface to libCmn Facilities",
    -1,
    methods
};

PyMODINIT_FUNC PyInit_myhjson(void) {
    return PyModule_Create(&module);
}


