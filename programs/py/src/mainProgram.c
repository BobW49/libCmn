// vi:nu:et:sts=4 ts=4 sw=4
//
//  main.c
//
//  Created by bob on 7/17/17.
//  Updated to add embedding Python.
//


#define	EMBED_PYTHON

#ifdef	EMBED_PYTHON
#define PY_SSIZE_T_CLEAN
#include <Python.h>
#endif


//#include        <stdio.h>
#define		MAIN_PROGRAM
#include	<cmn_defs.h>
#include        <Main.h>




#ifdef	EMBED_PYTHON
#endif

int             main(
    int             cArgs,
    char            *ppArgV[],
    char            **ppEnv
)
{
    int             iRc = 0;
    MAIN_DATA       *pMain = OBJ_NIL;
    ERESULT         eRc;
#ifdef	EMBED_PYTHON
    PyObject 	    *pName;         // Name of .py script to execute
    PyObject        *pModule;       // Module object gotten from pName
    PyObject        *pFunc;
    PyObject 	    *pArgs;
    PyObject        *pValue;
    int             i;
#endif
    
#ifdef XYZZY
    fprintf(stderr, "\n\nEnvironment Variables:\n");
    while (*ppEnv) {
        fprintf(stderr, "\t%s\n", *ppEnv);
        ++ppEnv;
    }
    fprintf(stderr, "\n\n");
#endif

#ifdef	EMBED_PYTHON
    Py_Initialize();
    pName = PyUnicode_DecodeFSDefault(argv[1]);
    /* Error checking of pName left out */

    // ???
    pModule = PyImport_Import(pName);
    Py_DECREF(pName);
#endif

    pMain = Main_Shared( );
    if (pMain == OBJ_NIL) {
        fprintf(stderr, "FATAL ERROR - \n");
        exit(EXIT_FAILURE);
    }
    
    eRc = Main_SetupFromArgV(pMain, cArgs, ppArgV, ppEnv);
    if (ERESULT_FAILED(eRc)) {
        fprintf(stderr, "FATAL - Failed to set up arguments!\n\n\n");
        return 8;
    }

#ifdef	EMBED_PYTHON
    # Execute a function provided from the command line.
    if (pModule != NULL) {
        pFunc = PyObject_GetAttrString(pModule, argv[2]);
        /* pFunc is a new reference */

        if (pFunc && PyCallable_Check(pFunc)) {
            pArgs = PyTuple_New(argc - 3);
            for (i = 0; i < argc - 3; ++i) {
                pValue = PyLong_FromLong(atoi(argv[i + 3]));
                if (!pValue) {
                    Py_DECREF(pArgs);
                    Py_DECREF(pModule);
                    fprintf(stderr, "Cannot convert argument\n");
                    return 1;
                }
                /* pValue reference stolen here: */
                PyTuple_SetItem(pArgs, i, pValue);
            }
            pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);
            if (pValue != NULL) {
                printf("Result of call: %ld\n", PyLong_AsLong(pValue));
                Py_DECREF(pValue);
            }
            else {
                Py_DECREF(pFunc);
                Py_DECREF(pModule);
                PyErr_Print();
                fprintf(stderr,"Call failed\n");
                return 1;
            }
        }
        else {
            if (PyErr_Occurred())
                PyErr_Print();
            fprintf(stderr, "Cannot find function \"%s\"\n", argv[2]);
        }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    }
    else {
        PyErr_Print();
        fprintf(stderr, "Failed to load \"%s\"\n", argv[1]);
        return 1;
    }
#endif
    
    iRc = Main_Exec(pMain);

#ifdef	EMBED_PYTHON
    if (Py_FinalizeEx() < 0) {
        return 120;
    }
#endif
    //obj_SharedReset( );
    pMain = OBJ_NIL;
    return iRc;
}

int		main(
	int 		argc, 
	char 		*argv[])
{
    PyObject *pName, *pModule, *pFunc;
    PyObject *pArgs, *pValue;
    int i;

    if (argc < 3) {
        fprintf(stderr,"Usage: call pythonfile funcname [args]\n");
        return 1;
    }

    Py_Initialize();
    pName = PyUnicode_DecodeFSDefault(argv[1]);
    /* Error checking of pName left out */

    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) {
        pFunc = PyObject_GetAttrString(pModule, argv[2]);
        /* pFunc is a new reference */

        if (pFunc && PyCallable_Check(pFunc)) {
            pArgs = PyTuple_New(argc - 3);
            for (i = 0; i < argc - 3; ++i) {
                pValue = PyLong_FromLong(atoi(argv[i + 3]));
                if (!pValue) {
                    Py_DECREF(pArgs);
                    Py_DECREF(pModule);
                    fprintf(stderr, "Cannot convert argument\n");
                    return 1;
                }
                /* pValue reference stolen here: */
                PyTuple_SetItem(pArgs, i, pValue);
            }
            pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);
            if (pValue != NULL) {
                printf("Result of call: %ld\n", PyLong_AsLong(pValue));
                Py_DECREF(pValue);
            }
            else {
                Py_DECREF(pFunc);
                Py_DECREF(pModule);
                PyErr_Print();
                fprintf(stderr,"Call failed\n");
                return 1;
            }
        }
        else {
            if (PyErr_Occurred())
                PyErr_Print();
            fprintf(stderr, "Cannot find function \"%s\"\n", argv[2]);
        }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    }
    else {
        PyErr_Print();
        fprintf(stderr, "Failed to load \"%s\"\n", argv[1]);
        return 1;
    }
    if (Py_FinalizeEx() < 0) {
        return 120;
    }
    return 0;
}

