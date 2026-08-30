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

python3 setup.py build
python3 setup

# setup.py 
from setuptools import setup, Extension
# Look at the one for libCmn to get this working

json_parser_module = Extension(
    'json_parser',
    sources=['hjson_parser.c'],
    libraries=['cmn'],                  # Ensure to have json-c library available
)

setup(
    name='json_parser',
    version='1.0',
    description='A simple JSON parser C extension',
    ext_modules=[json_parser_module],
)

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <cmn_defs.h>
#include <hjson.h> // Ensure you have the json-c library installed

// Function to parse JSON string and return Python objects
//
// We need to iterate the HJSON output from the bottom up ???
// Probably, creating the lower units building to the top.
// hmmm or we recursively recreate the tree from the bottom up.
static PyObject* parse_hjson(PyObject* self, PyObject* args) {
    const char* json_string;

    // Parse input string
    if (!PyArg_ParseTuple(args, "s", &json_string)) {
        return NULL; // Handle error
    }

    struct json_object *parsed_json;
    struct json_object *json_value;
    PyObject *result = NULL;

    // Parse JSON using json-c
    parsed_json = json_tokener_parse(json_string);
    if (!parsed_json) {
        PyErr_SetString(PyExc_ValueError, "Invalid JSON string");
        return NULL; // Handle parsing error
    }

    // Convert json-c object to Python object
    if (json_object_get_type(parsed_json) == json_type_object) {
        result = PyDict_New();
        // Iterate over the JSON object and add items to Python dictionary
        for (int i = 0; i < json_object_object_length(parsed_json); i++) {
            const char *key;
            json_object_object_foreach(parsed_json, key, json_value) {
                PyObject *py_key = PyUnicode_FromString(key);
                PyObject *py_value;
                
                // Check the value type
                switch (json_object_get_type(json_value)) {
                    case json_type_string:
                        py_value = PyUnicode_FromString(json_object_get_string(json_value));
                        break;
                    case json_type_int:
                        py_value = PyLong_FromLong(json_object_get_int(json_value));
                        break;
                    case json_type_boolean:
                        py_value = json_object_get_boolean(json_value) ? Py_True : Py_False;
                        Py_INCREF(py_value);
                        break;
                    case json_type_double:
                        py_value = PyFloat_FromDouble(json_object_get_double(json_value));
                        break;
                    case json_type_object:
                        // You can recursively parse the sub-object
                        // For simplicity, could also return NULL if deep parsing isn't needed
                        break;
                    case json_type_array:
                        // Implement similar logic for arrays
                        break;
                    default:
                        py_value = Py_None;
                        Py_INCREF(py_value);
                        break;
                }

                // Add to the dictionary
                PyDict_SetItem(result, py_key, py_value);
                Py_DECREF(py_key);
                Py_DECREF(py_value);
            }
        }
    } else if (json_object_get_type(parsed_json) == json_type_array) {
        result = PyList_New(json_object_array_length(parsed_json));
        for (size_t i = 0; i < json_object_array_length(parsed_json); i++) {
            json_value = json_object_array_get_idx(parsed_json, i);
            // Similar logic to handle types
        }
    } else {
        PyErr_SetString(PyExc_ValueError, "Unsupported JSON type");
    }

    // Cleanup
    json_object_put(parsed_json); // Release JSON objects
    return result; // Return the parsed Python object
}

// Method definitions
static PyMethodDef JsonMethods[] = {
    {"parse_hjson", parse_hjson, METH_VARARGS, "Parse a HJSON string and return corresponding Python object."},
    {NULL, NULL, 0, NULL} // Sentinel
};

// Module definition
static struct PyModuleDef jsonmodule = {
    PyModuleDef_HEAD_INIT,
    "json_parser", // name of module
    NULL, // module documentation, may be NULL
    -1, // size of per-interpreter state of the module
    JsonMethods // structure that defines the module's functions
};

// Module initialization function
PyMODINIT_FUNC PyInit_json_parser(void) {
    return PyModule_Create(&jsonmodule);
}






//----------------------------------------------------------------
//  Create a Python Dictionary of Strings Module Definition
//----------------------------------------------------------------

#define PY_SSIZE_T_CLEAN
#include <Python.h>

static PyObject* create_dict(PyObject* self, PyObject* args) {
    PyObject* my_dict = PyDict_New();
    PyDict_SetItemString(my_dict, "key1", PyUnicode_FromString("value1"));
    PyDict_SetItemString(my_dict, "key2", PyUnicode_FromString("value2"));
    return my_dict;
}

static PyMethodDef MyMethods[] = {
    {"create_dict", create_dict, METH_VARARGS, "Create a dictionary of strings."},
    {"create_string_list", create_string_list, METH_VARARGS, "Create a list of strings"},
    {"print_python_string", print_python_string, METH_VARARGS, "Print a Python string"},
    {"return_true", return_true, METH_VARARGS, "Return True"},    
    {"return_none", return_none, METH_VARARGS, "Return None"},    
    {"return_integer_from_string", return_integer_from_string, METH_VARARGS, "Return a Python integer from a C string"},    
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef mymodule = {
    PyModuleDef_HEAD_INIT,
    "my_extension",                 // name of module
    NULL,                           // module documentation, may be NULL
    -1,                             // size of per-interpreter state of the module
    MyMethods                       // structure that defines the module's functions
};

PyMODINIT_FUNC PyInit_mymodule(void) {
    return PyModule_Create(&mymodule);
}



// Function to print the received Python string
static 
PyObject*   print_python_string(
    PyObject*   self, 
    PyObject*   args
) 
{
    const 
    char        *input_string;

    // Parse the Python argument as a string
    if (!PyArg_ParseTuple(args, "s", &input_string)) {
        return NULL; // Handle error
    }

    // Print the C string
    printf("Received string: %s\n", input_string);

    Py_RETURN_NONE; // Nothing to return
}


// Function to return Python True
static 
PyObject* return_true(PyObject* self, PyObject* args) {
    Py_RETURN_TRUE; // Return the Python True object
}

// Function to return Python None
static 
PyObject* return_none(PyObject* self, PyObject* args) {
    Py_RETURN_NONE; // Return the Python None object
}


// Function to return a Python integer from a C string
static 
PyObject* return_integer_from_string(PyObject* self, PyObject* args) {
    const char* c_string = "123";  // Your C string
    long c_integer;

    // Convert C string to long
    c_integer = strtol(c_string, NULL, 10);
    
    // Return as Python integer
    return PyLong_FromLong(c_integer);
}



//----------------------------------------------------------------
//           Create a Python Dictionary of Strings
//----------------------------------------------------------------

PyObject* my_module_function(PyObject* self, PyObject* args) {
    PyObject* my_dict = PyDict_New();
    PyDict_SetItemString(my_dict, "key1", PyUnicode_FromString("value1"));
    PyDict_SetItemString(my_dict, "key2", PyUnicode_FromString("value2"));
    return my_dict;  // Return the dictionary
}





//----------------------------------------------------------------
//      Create a Python List of Strings Module Definition
//----------------------------------------------------------------

static 
PyMethodDef MyMethods[] = {
    {"create_string_list", create_string_list, METH_VARARGS, "Create a list of strings"},
    {NULL, NULL, 0, NULL} // Sentinel
};

static 
struct PyModuleDef mymodule = {
    PyModuleDef_HEAD_INIT,
    "mymodule", // Name of the module
    NULL, // Module documentation
    -1, // Size of per-interpreter state of the module
    MyMethods
};


PyMODINIT_FUNC PyInit_mymodule(void) {
    return PyModule_Create(&mymodule);
}



//----------------------------------------------------------------
//              Create a Python List of Strings
//----------------------------------------------------------------

static PyObject* create_string_list(PyObject* self) {
    // Create a new list
    PyObject* string_list = PyList_New(0);
    
    // Check if the list was created successfully
    if (string_list == NULL) {
        return NULL; // Return NULL on failure
    }

    // Create strings and add them to the list
    PyObject* str1 = PyUnicode_FromString("Hello");
    PyObject* str2 = PyUnicode_FromString("World");
    
    // Append strings to the list
    PyList_Append(string_list, str1);
    PyList_Append(string_list, str2);
    
    // Decrease reference count for the strings
    Py_DECREF(str1);
    Py_DECREF(str2);
    
    return string_list; // Return the list
}

