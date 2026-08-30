// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
// Python Interface to/from Objects (PythonInter) Object Support
//****************************************************************


/*
 * File:   PythonInter.c
 *  Generated 05/21/2026 07:03:39
 *
 */

 
/*
 This is free and unencumbered software released into the public domain.
 
 Anyone is free to copy, modify, publish, use, compile, sell, or
 distribute this software, either in source code form or as a compiled
 binary, for any purpose, commercial or non-commercial, and by any
 means.
 
 In jurisdictions that recognize copyright laws, the author or authors
 of this software dedicate any and all copyright interest in the
 software to the public domain. We make this dedication for the benefit
 of the public at large and to the detriment of our heirs and
 successors. We intend this dedication to be an overt act of
 relinquishment in perpetuity of all present and future rights to this
 software under copyright law.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 OTHER DEALINGS IN THE SOFTWARE.
 
 For more information, please refer to <http://unlicense.org/>
 */




//*****************************************************************
//* * * * * * * * * * * *  Data Definitions   * * * * * * * * * * *
//*****************************************************************

/* Header File Inclusion */
#include        <PythonInter_internal.h>
#include        <JsonIn.h>
#include        <trace.h>
#include        <utf8.h>






#ifdef  __cplusplus
extern "C" {
#endif
    

    
    //****************************************************************
    // * * * * * * * * * * *    Internal Data    * * * * * * * * * * *
    //****************************************************************

    // Place constant internal data here. Generally, it should be
    // 'static' so that it does not interfere with other objects.

    // Module methods
    static
    PyMethodDef methods[] = {
        //{"parse", py_hjson_parse, METH_VARARGS, "Parse HJSON file → Python dict/list"},
        {NULL, NULL, 0, NULL}
    };

    static 
    struct PyModuleDef module = {
        PyModuleDef_HEAD_INIT,
        "myhjson",
        "Custom HJSON parser bridge",
        -1,
        methods
    };




    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/



    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            PythonInter_task_body (
        void            *pData
    )
    {
        PYTHONINTER_DATA 
                        *this = pData;
        TRC_OBJ(this, "%s(%p):\n", __func__, this);
        
    }
#endif



    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    /*
        C Type,     Best Function,                  Notes
        int64_t     PyLong_FromLongLong()           Recommended
        uint64_t    PyLong_FromUnsignedLongLong()   For unsigned
        int32_t     PyLong_FromLong()               Smaller types
        uint32_t    PyLong_FromUnsignedLong()       -
        Any integer PyLong_FromSsize_t() |
                    PyLong_FromSize_t()             Good for sizes/indices


        Python Type → C Type    Best Function,                  Notes
        int → int64_t           PyLong_AsLongLong(),            Most common
        int → int64_t + check   PyLong_AsLongLongAndOverflow()  Best for safety
        int → uint64_t          PyLong_AsUnsignedLongLong()     Unsigned version

        double → Python         PyFloat_FromDouble()            Simple & fast
        Python → double         PyFloat_AsDouble()              Accepts int too
        With overflow check     PyFloat_AsDouble()              Sets exception automatically
     */


    PYTHONINTER_DATA * 
                    PythonInter_Alloc (
        void
    )
    {
        PYTHONINTER_DATA 
                        *this;
        uint32_t        cbSize = sizeof(PYTHONINTER_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    PYTHONINTER_DATA * 
                    PythonInter_New (
        void
    )
    {
        PYTHONINTER_DATA 
                        *this;
        
        this = PythonInter_Alloc( );
        if (this) {
            this = PythonInter_Init(this);
        } 
        return this;
    }


    PyObject *      PythonInter_PyDictCreate (
        void
    ) {
        return PyDict_New();
    }


    PyObject *      PythonInter_PyArrayCreate (
        void
    ) {
        return PyList_New(0);
    }


    PyObject *      PythonInter_PyFalseCreate (
        void
    ) 
    {
        return Py_NewRef(Py_False);
    }


    int64_t         PythonInter_FromPyInteger (
        PyObject        *py_int, 
        int64_t         default_value
    )
    {
        int64_t         value;

        if (NULL == py_int || Py_None == py_int) {
            return default_value;
        }

        if (!PyLong_Check(py_int)) {
            PyErr_SetString(PyExc_TypeError, "Expected an integer");
            return default_value;   // or return 0 and let caller check error
        }

        value = PyLong_AsLongLong(py_int);

        if (value == -1 && PyErr_Occurred()) {
            // Overflow or other error occurred
            return default_value;   // or handle error as needed
        }

        return value;
    }


    PyObject *      PythonInter_IntegerFromStrToPy (
        const 
        char            *pNumstr        // NUL-Terminated String
    ) {
        return PyLong_FromString(pNumstr, NULL, 0);
    }

    
    PyObject *      PythonInter_PyNullCreate (
        void
    ) 
    {
        Py_RETURN_NONE;
    }



    PyObject *      PythonInter_PyTrueCreate (
        void
    ) 
    {
        return Py_NewRef(Py_True);
    }



    static 
    PyObject*       py_create_number(
    const 
    char                *numstr,     // NUL-Terminated String
    bool                isFloat
) {
    if (isFloat)
        return PyFloat_FromDouble(atof(numstr));
    return PyLong_FromString(numstr, NULL, 10);
}

static PyObject* py_create_bool(
    bool value
) {
    return Py_NewRef(value ? Py_True : Py_False);
}

static PyObject* py_create_false(
    void
) {
    return Py_NewRef(Py_False);
}

static PyObject* py_create_true(
    void
) {
    return Py_NewRef(Py_True);
}

PyObject* py_create_null(void) {
    Py_RETURN_NONE;
}

static PyObject* py_create_double(void* ctx, double value)
{
    (void)ctx;

    PyObject* py_float = PyFloat_FromDouble(value);

    if (py_float == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "Failed to create Python float");
        return NULL;
    }
    return py_float;
}

static double py_to_double(PyObject* obj, double default_value)
{
    if (obj == NULL || obj == Py_None) {
        return default_value;
    }

    if (!PyFloat_Check(obj) && !PyLong_Check(obj)) {   // accept int too
        PyErr_SetString(PyExc_TypeError, "Expected float or integer");
        return default_value;
    }

    double value = PyFloat_AsDouble(obj);

    if (PyErr_Occurred()) {
        return default_value;     // Error already set (e.g. overflow)
    }

    return value;
}

static double py_to_double_safe(PyObject* obj)
{
    if (obj == NULL || obj == Py_None) {
        PyErr_SetString(PyExc_TypeError, "Expected float, got None");
        return 0.0;
    }

    double value = PyFloat_AsDouble(obj);

    if (PyErr_Occurred()) {
        // Python already set the exception (TypeError, OverflowError, etc.)
        return 0.0;
    }

    return value;
}



    PyObject *      PythonInter_AStrToPy (
        ASTR_DATA       *pAStr
    ) {
        const 
        char            *utf8 = AStr_getData(pAStr);
        Py_ssize_t      len = AStr_getByteLength(pAStr);    // Byte length excluding NUL

        if (OBJ_NIL == pAStr) 
            Py_RETURN_NONE;

        return PyUnicode_FromStringAndSize(utf8, len);
    }


    PyObject *      PythonInter_StringToPy (
        const 
        char            *pUtf8,
        size_t          len
    )
    {
        PyObject        *pObj = NULL;

        if (NULL == pUtf8) {
            PyErr_SetString(PyExc_ValueError, "py_create_string received NULL pointer");
            return NULL;
        }
        if (0 == len)
            len = strlen(pUtf8);

        pObj = PyUnicode_DecodeUTF8(pUtf8, (Py_ssize_t)len, "strict");
        if (NULL == pObj) {
            // Add context to the existing UnicodeDecodeError
            PyErr_Format(PyExc_UnicodeDecodeError, 
                         "Invalid UTF-8 data at offset %zu (total length = %zu)", 
                         (size_t)0, len);   // you can improve offset if needed
            return NULL;
        }

        return pObj;
    }
    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          F l a g
    //---------------------------------------------------------------
    
#ifdef  NEED_ALL_GENERATED_CODE
    // @property Flag
    //  assumes a 1-byte flag in this object.

    bool            PythonInter_getFlag (
        PYTHONINTER_DATA 
                        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!PythonInter_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->flag ? true : false;
    }


    bool            PythonInter_setFlag (
        PYTHONINTER_DATA 
                        *this,
        bool            fValue
    )
    {
#ifdef NDEBUG
#else
        if (!PythonInter_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = fValue ? 1 : 0;

        return true;
    }
#endif



    //---------------------------------------------------------------
    //                      M e s s a g e s
    //---------------------------------------------------------------

#ifdef   PYTHONINTER_MSGS
    bool            PythonInter_setMsgs (
        PYTHONINTER_DATA 
                        *this,
        void            (*pMsgInfo)(OBJ_ID, const char *, ...),
        void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...),
        OBJ_ID          pObj
    )
    {
#ifdef NDEBUG
#else
        if (!PythonInter_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->pMsgInfo = pMsgInfo;
        this->pMsgWarn = pMsgWarn;
        this->pMsgObj = pObj;

        return true;
    }
#endif



    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
#ifdef  NEED_ALL_GENERATED_CODE
    uint16_t        PythonInter_getPriority (
        PYTHONINTER_DATA 
                        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!PythonInter_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            PythonInter_setPriority (
        PYTHONINTER_DATA 
                        *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!PythonInter_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        return true;
    }
#endif



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        PythonInter_getSize (
        PYTHONINTER_DATA 
                        *this
    )
    {
#ifdef NDEBUG
#else
        if (!PythonInter_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA *     PythonInter_getStr (
        PYTHONINTER_DATA 
                        *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!PythonInter_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStr;
    }
    
    
    bool            PythonInter_setStr (
        PYTHONINTER_DATA 
                        *this,
        ASTR_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!PythonInter_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pStr) {
            obj_Release(this->pStr);
        }
        this->pStr = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
#ifdef  PYTHONINTER_SUPER_DEFINED
    OBJ_DATA *      PythonInter_getSuper (
        PYTHONINTER_DATA 
                        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!PythonInter_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return (OBJ_DATA *)this;
    }
#else
    OBJ_DATA *      PythonInter_getSuper (
        PYTHONINTER_DATA 
                        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!PythonInter_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return (OBJ_DATA *)this;
    }
#endif

    
    OBJ_IUNKNOWN *  PythonInter_getSuperVtbl (
        PYTHONINTER_DATA 
                        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!PythonInter_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before 
     a copy of the object is performed.
     Example:
     @code 
        ERESULT eRc = PythonInter_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another PYTHONINTER object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         PythonInter_Assign (
        PYTHONINTER_DATA 
                        *this,
        PYTHONINTER_DATA 
                        *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!PythonInter_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!PythonInter_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Assign any Super(s).
        if (this->pSuperVtbl && (this->pSuperVtbl->pWhoAmI() != OBJ_IDENT_OBJ)) {
            if (this->pSuperVtbl->pAssign) {
                eRc = this->pSuperVtbl->pAssign(this, pOther);
                if (ERESULT_FAILED(eRc)) {
                    return eRc;
                }
            }
        }

        // Release objects and areas in other object.
#ifdef  XYZZY
        if (pOther->pStr) {
            obj_Release(pOther->pStr);
            pOther->pStr = OBJ_NIL;
        }
#endif

        // Create a copy of objects and areas in this object placing
        // them in other.
#ifdef  XYZZY
        if (this->pStr) {
            if (obj_getVtbl(this->pStr)->pCopy) {
                pOther->pStr = obj_getVtbl(this->pStr)->pCopy(this->pStr);
            }
            else {
                obj_Retain(this->pStr);
                pOther->pStr = this->pStr;
            }
        }
#endif

        // Copy other data from this object to other.
        //pOther->x     = this->x; 

        // Return to caller.
        eRc = ERESULT_SUCCESS;
    eom:
        //FIXME: Implement the assignment.        
        eRc = ERESULT_NOT_IMPLEMENTED;
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                      C o m p a r e
    //---------------------------------------------------------------
    
    /*!
     Compare the two provided objects.
     @return    0  if this == other
                <0 if this < other
                >0 if this > other
     */
    int             PythonInter_Compare (
        PYTHONINTER_DATA 
                        *this,
        PYTHONINTER_DATA 
                        *pOther
    )
    {
        int             iRc = -1;
#ifdef  xyzzy        
        const
        char            *pStr1;
        const
        char            *pStr2;
#endif
        
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  PYTHONINTER_SINGLETON
        if (OBJ_NIL == this) {
            this = PythonInter_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!PythonInter_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!PythonInter_Validate(pOther)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -2;
        }
#endif

        //TODO: iRc = utf8_StrCmp(AStr_getData(this->pStr), AStr_getData(pOther->pStr));
     
        return iRc;
    }
    
   
 
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        PythonInter      *pCopy = PythonInter_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a PYTHONINTER object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    PYTHONINTER_DATA * 
                    PythonInter_Copy (
        PYTHONINTER_DATA 
                        *this
    )
    {
        PYTHONINTER_DATA 
                        *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!PythonInter_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef PYTHONINTER_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = PythonInter_New( );
        if (pOther) {
            eRc = PythonInter_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
#endif
        
        // Return to caller.
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            PythonInter_Dealloc (
        OBJ_ID          objId
    )
    {
        PYTHONINTER_DATA 
                        *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!PythonInter_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((PYTHONINTER_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        PythonInter_setStr(this, OBJ_NIL);

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                         D e e p  C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        PythonInter      *pDeepCopy = PythonInter_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a PYTHONINTER object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    PYTHONINTER_DATA * 
                    PythonInter_DeepCopy (
        PYTHONINTER_DATA 
                        *this
    )
    {
        PYTHONINTER_DATA 
                        *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!PythonInter_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = PythonInter_New( );
        if (pOther) {
            eRc = PythonInter_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    /*!
     Disable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         PythonInter_Disable (
        PYTHONINTER_DATA 
                        *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  PYTHONINTER_SINGLETON
        if (OBJ_NIL == this) {
            this = PythonInter_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!PythonInter_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Put code here...

        TRC_OBJ(this,"\tEnabled?: %s:\n", obj_Enable(this) ? "true" : "false");
        obj_Disable(this);
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    /*!
     Enable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         PythonInter_Enable (
        PYTHONINTER_DATA 
                        *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  PYTHONINTER_SINGLETON
        if (OBJ_NIL == this) {
            this = PythonInter_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!PythonInter_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        TRC_OBJ(this,"\tEnabled?: %s:\n", obj_Enable(this) ? "true" : "false");
#ifdef   PYTHONINTER_MSGS
        if (this->pMsgInfo) {
            this->pMsgInfo(this->pMsgObj, "Enabling object!\n");
        }
#endif
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          H a s h
    //---------------------------------------------------------------
    
    uint32_t        PythonInter_Hash(
        PYTHONINTER_DATA 
                        *this
    )
    {
        uint32_t        hash = 0;
        char            *pStr = NULL;
        
#ifdef NDEBUG
#else
        if( !PythonInter_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
       
        /* 
        pStr = array_Ptr(this->pData, 1);
        if (pStr) {
            hash = str_HashAcmA(pStr, NULL);
        }
        */
        
        return hash;
    }
    
    

    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    PYTHONINTER_DATA * 
                    PythonInter_Init (
        PYTHONINTER_DATA 
                        *this
    )
    {
        uint32_t        cbSize = sizeof(PYTHONINTER_DATA);
        //ERESULT         eRc;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        /* cbSize can be zero if Alloc() was not called and we are
         * are passed the address of a zero'd area.
         */
        //cbSize = obj_getSize(this);       // cbSize must be set in Alloc().
        if (cbSize == 0) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

#ifdef  PYTHONINTER_SUPER_DEFINED
        this = (OBJ_ID)obj_Init((OBJ_DATA *)this);   // Needed for Inheritance
#else
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_PYTHONINTER);
#endif
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&PythonInter_Vtbl);
#ifdef  PYTHONINTER_JSON_SUPPORT
        JsonIn_RegisterClass(PythonInter_Class());
#endif
        
        /*
        this->pArray = ObjArray_New( );
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        */

#ifdef NDEBUG
#else
        if (!PythonInter_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "PythonInter::sizeof(PYTHONINTER_DATA) = %lu\n", 
                sizeof(PYTHONINTER_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(PYTHONINTER_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                      I s  E n a b l e d
    //---------------------------------------------------------------
    
    bool            PythonInter_IsEnabled (
        PYTHONINTER_DATA 
                        *this
    )
    {
        //ERESULT         eRc;
        bool            fRc = false;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  PYTHONINTER_SINGLETON
        if (OBJ_NIL == this) {
            this = PythonInter_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!PythonInter_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return fRc;
        }
#endif
        
        if (obj_IsEnabled(this)) {
            fRc = true;
        }
        
        // Return to caller.
        return fRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    /*!
     Return information about this object. This method can translate
     methods to strings and vice versa, return the address of the
     object information structure.
     Example:
     @code
        // Return a method pointer for a string or NULL if not found. 
        void        *pMethod = PythonInter_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_DATA, an object's data is returned
                        if it fits in a "void *".
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "PythonInter", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          PythonInter_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        PYTHONINTER_DATA 
                        *this = objId;
        const
        char            *pStrA = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!PythonInter_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(PYTHONINTER_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)PythonInter_Class();
                break;

            case OBJ_QUERYINFO_TYPE_DATA:
                switch (*pStrA) {
     
                    case 'S':
                        if (str_Compare("Str", (char *)pStrA) == 0) {
                            return (void *)this->pStr;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;

                              
            case OBJ_QUERYINFO_TYPE_DATA_PTR:
                switch (*pStrA) {
     
                    case 'S':
                        if (str_Compare("SuperClass", (char *)pStrA) == 0) {
                            return (void *)(obj_getInfo(this)->pClassSuperObject);
                        }
                        break;
                        
                    default:
                        break;
                }
                break;

            case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStrA) {
                        
                    case 'D':
                        if (str_Compare("Disable", (char *)pStrA) == 0) {
                            return PythonInter_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStrA) == 0) {
                            return PythonInter_Enable;
                        }
                        break;

                    case 'P':
#ifdef  PYTHONINTER_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStrA) == 0) {
                            return PythonInter_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStrA) == 0) {
                            return PythonInter_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStrA) == 0) {
                            return PythonInter_ToDebugString;
                        }
#ifdef  PYTHONINTER_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStrA) == 0) {
                            return PythonInter_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStrA) == 0) {
                            return PythonInter_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == PythonInter_ToDebugString)
                    return "ToDebugString";
#ifdef  PYTHONINTER_JSON_SUPPORT
                if (pData == PythonInter_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = PythonInter_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     PythonInter_ToDebugString (
        PYTHONINTER_DATA 
                        *this,
        int             indent
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        //uint32_t        i;
        //uint32_t        j;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!PythonInter_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pInfo = obj_getInfo(this);
        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc = AStr_AppendPrint(
                    pStr,
                    "{%p(%s) size=%d retain=%d\n",
                    this,
                    pInfo->pClassName,
                    PythonInter_getSize(this),
                    obj_getRetainCount(this)
            );

#ifdef  XYZZY        
        if (this->pData) {
            if (((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString(
                                                    this->pData,
                                                    indent+3
                            );
                if (pWrkStr) {
                    AStr_Append(pStr, pWrkStr);
                    obj_Release(pWrkStr);
                }
            }
        }
#endif
        
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc =   AStr_AppendPrint(
                    pStr,
                    " %p(%s)}\n", 
                    this, 
                    pInfo->pClassName
                );
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

#ifdef NDEBUG
#else
    bool            PythonInter_Validate (
        PYTHONINTER_DATA 
                        *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_PYTHONINTER))
                ;
            else {
                // 'this' is not our kind of data. We really don't
                // know what that it is at this point. 
                return false;
            }
        }
        else {
            // 'this' is NULL.
            return false;
        }
        // Now, we have validated that we have a valid pointer in
        // 'this'.


        if (!(obj_getSize(this) >= sizeof(PYTHONINTER_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
#ifdef  __cplusplus
}
#endif


