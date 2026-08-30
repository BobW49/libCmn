// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//              Base for All Objects (ObjBase) Object Support
//****************************************************************


/*
 * File:   ObjBase.c
 *  Generated 02/24/2025 10:18:39
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
#include        <ObjBase_internal.h>
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





    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/



    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            ObjBase_task_body (
        void            *pData
    )
    {
        OBJBASE_DATA    *this = pData;
        TRC_OBJ(this, "%s(%p):\n", __func__, this);
        
    }
#endif



    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    OBJBASE_DATA *  ObjBase_Alloc (
        void
    )
    {
        OBJBASE_DATA    *this;
        uint32_t        cbSize = sizeof(OBJBASE_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    OBJBASE_DATA *  ObjBase_New (
        void
    )
    {
        OBJBASE_DATA    *this;
        
        this = ObjBase_Alloc( );
        if (this) {
            this = ObjBase_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          F l a g
    //---------------------------------------------------------------
    
    // @property Flag
    //  assumes a 1-byte flag in this object.

    bool            ObjBase_getFlag (
        OBJBASE_DATA    *this,
        uint16_t        flag_number
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!ObjBase_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        if ((flag_number > 15)) {
            DEBUG_BREAK();
            return false;
        }

        return (this->cbFlags & (1 << flag_number))  ? true : false;
    }


    bool            ObjBase_setFlag (
        OBJBASE_DATA    *this,
        uint16_t        flag_number,
        bool            fValue
    )
    {
#ifdef NDEBUG
#else
        if (!ObjBase_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        if ((flag_number > 15)) {
            DEBUG_BREAK();
            return false;
        }

        if (fValue) {
            this->cbFlags |= (1 << flag_number);
        } else {
            this->cbFlags &= ~(1 << flag_number);
        }

        return true;
    }



    //---------------------------------------------------------------
    //                          I n f o
    //---------------------------------------------------------------
    
    const
    OBJ_INFO *      ObjBase_getInfo (
        OBJBASE_DATA    *this
    )
    {
        const
        OBJ_IUNKNOWN    *pVtbl = NULL;
        const
        OBJ_INFO        *pInfo = NULL;

        pVtbl = ObjBase_getVtbl(this);
        if (NULL == pVtbl) {
            return pInfo;
        }
        pInfo = pVtbl->pInfo;
        return pInfo;
    }

    

    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
#ifdef  NEED_ALL_GENERATED_CODE
    uint16_t        ObjBase_getPriority (
        OBJBASE_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!ObjBase_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            ObjBase_setPriority (
        OBJBASE_DATA    *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!ObjBase_Validate(this)) {
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
    
    uint32_t        ObjBase_getSize (
        OBJBASE_DATA    *this
    )
    {
#ifdef NDEBUG
#else
        if (!ObjBase_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->cbSize;
    }

    
    bool            ObjBase_setSize (
        OBJBASE_DATA    *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!ObjBase_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->cbSize = value;

        return true;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJBASE_DATA *  ObjBase_getSuper (
        OBJBASE_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!ObjBase_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return (OBJBASE_DATA *)this;
    }

    
    const
    OBJ_IUNKNOWN *  ObjBase_getSuperVtbl (
        OBJBASE_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!ObjBase_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pVtbl;
    }
    
  

    //---------------------------------------------------------------
    //                          T y p e
    //---------------------------------------------------------------
    
    uint16_t        ObjBase_getType (
        OBJBASE_DATA    *this
    )
    {
        const
        OBJ_IUNKNOWN    *pVtbl = NULL;
        uint16_t        type = OBJ_IDENT_UNKNOWN;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!ObjBase_Validate(this)) {
            DEBUG_BREAK();
            return type;
        }
#endif
        pVtbl = this->pVtbl;
        if (pVtbl && pVtbl->pWhoAmI) {
            type = pVtbl->pWhoAmI();
        }
        return type;
    }


    bool            ObjBase_setType (
        OBJBASE_DATA    *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!ObjBase_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        return true;
    }



    //---------------------------------------------------------------
    //                       V t b l
    //---------------------------------------------------------------
    
    const
    OBJ_IUNKNOWN *  ObjBase_getVtbl (
        OBJBASE_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!ObjBase_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pVtbl;
    }
    
    
    bool            ObjBase_setVtbl (
        OBJBASE_DATA    *this,
        const
        OBJ_IUNKNOWN    *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!ObjBase_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->pVtbl = pValue;
        
        return true;
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
        ERESULT eRc = ObjBase_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another OBJBASE object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         ObjBase_Assign (
        OBJBASE_DATA    *this,
        OBJBASE_DATA    *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!ObjBase_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!ObjBase_Validate(pOther)) {
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
    int             ObjBase_Compare (
        OBJBASE_DATA    *this,
        OBJBASE_DATA    *pOther
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
#ifdef  OBJBASE_SINGLETON
        if (OBJ_NIL == this) {
            this = ObjBase_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!ObjBase_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!ObjBase_Validate(pOther)) {
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
        ObjBase      *pCopy = ObjBase_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a OBJBASE object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    OBJBASE_DATA *  ObjBase_Copy (
        OBJBASE_DATA    *this
    )
    {
        OBJBASE_DATA    *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!ObjBase_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef OBJBASE_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = ObjBase_New( );
        if (pOther) {
            eRc = ObjBase_Assign(this, pOther);
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

    void            ObjBase_Dealloc (
        OBJ_ID          objId
    )
    {
        OBJBASE_DATA    *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!ObjBase_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((OBJBASE_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        ObjBase_setStr(this, OBJ_NIL);

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
        ObjBase      *pDeepCopy = ObjBase_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a OBJBASE object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    OBJBASE_DATA *  ObjBase_DeepCopy (
        OBJBASE_DATA    *this
    )
    {
        OBJBASE_DATA    *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!ObjBase_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = ObjBase_New( );
        if (pOther) {
            eRc = ObjBase_Assign(this, pOther);
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
    ERESULT         ObjBase_Disable (
        OBJBASE_DATA    *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  OBJBASE_SINGLETON
        if (OBJ_NIL == this) {
            this = ObjBase_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!ObjBase_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Put code here...

        TRC_OBJ(this,"\tEnabled?: %s:\n", obj_Enable(this) ? "true" : "false");
        this->cbFlags &= ~(1 << OBJ_FLAG_ENABLED);

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
    ERESULT         ObjBase_Enable (
        OBJBASE_DATA    *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  OBJBASE_SINGLETON
        if (OBJ_NIL == this) {
            this = ObjBase_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!ObjBase_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        TRC_OBJ(this,"\tEnabled?: %s:\n", obj_Enable(this) ? "true" : "false");
        this->cbFlags |= (1 << OBJ_FLAG_ENABLED);

        // Put code here...
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          H a s h
    //---------------------------------------------------------------
    
    uint32_t        ObjBase_Hash(
        OBJBASE_DATA    *this
    )
    {
        uint32_t        hash = 0;
        char            *pStr = NULL;
        
#ifdef NDEBUG
#else
        if( !ObjBase_Validate(this) ) {
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

    OBJBASE_DATA *  ObjBase_Init (
        OBJBASE_DATA    *this
    )
    {
        uint32_t        cbSize = sizeof(OBJBASE_DATA);
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

#ifdef  OBJBASE_SUPER_DEFINED
        this = (OBJ_ID)obj_Init((OBJ_DATA *)this);   // Needed for Inheritance
#else
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_OBJBASE);
#endif
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        ObjBase_setSize(this, cbSize);
        ObjBase_setType(this, OBJ_IDENT_OBJBASE);
        //this->pSuperVtbl = ObjBase_getVtbl(this);
        ObjBase_setVtbl(this, (OBJ_IUNKNOWN *)&ObjBase_Vtbl);
#ifdef  OBJBASE_JSON_SUPPORT
        JsonIn_RegisterClass(ObjBase_Class());
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
        if (!ObjBase_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "ObjBase::sizeof(OBJBASE_DATA) = %lu\n", 
                sizeof(OBJBASE_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(OBJBASE_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                      I s  E n a b l e d
    //---------------------------------------------------------------
    
    bool            ObjBase_IsEnabled (
        OBJBASE_DATA    *this
    )
    {
        //ERESULT         eRc;
        bool            fRc = false;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  OBJBASE_SINGLETON
        if (OBJ_NIL == this) {
            this = ObjBase_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!ObjBase_Validate(this)) {
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
    //                      I s K i n d O f
    //---------------------------------------------------------------
    
    bool            ObjBase_IsKindOf (
        OBJ_ID          objId,
        uint16_t        type
    )
    {
        OBJBASE_DATA    *this = objId;
        
        // Do initialization.
        if (OBJ_NIL == this) {
            return false;
        }
        if (this->pVtbl == NULL) {
            return false;
        }
        if (this->pVtbl->pIsKindOf == NULL) {
            return false;
        }
        
        if (this->pVtbl->pIsKindOf(type))
            return true;
        
        // Return to caller.
        return false;
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
        void        *pMethod = ObjBase_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_DATA, an object's data is returned
                        if it fits in a "void *".
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "ObjBase", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          ObjBase_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        OBJBASE_DATA    *this = objId;
        const
        char            *pStrA = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!ObjBase_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(OBJBASE_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)ObjBase_Class();
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
                            return ObjBase_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStrA) == 0) {
                            return ObjBase_Enable;
                        }
                        break;

                    case 'P':
#ifdef  OBJBASE_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStrA) == 0) {
                            return ObjBase_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStrA) == 0) {
                            return ObjBase_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStrA) == 0) {
                            return ObjBase_ToDebugString;
                        }
#ifdef  OBJBASE_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStrA) == 0) {
                            return ObjBase_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStrA) == 0) {
                            return ObjBase_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == ObjBase_ToDebugString)
                    return "ToDebugString";
#ifdef  OBJBASE_JSON_SUPPORT
                if (pData == ObjBase_ToJson)
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
        ASTR_DATA      *pDesc = ObjBase_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     ObjBase_ToDebugString (
        OBJBASE_DATA    *this,
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
        if (!ObjBase_Validate(this)) {
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
                    ObjBase_getSize(this),
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
    bool            ObjBase_Validate (
        OBJBASE_DATA    *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (ObjBase_IsKindOf(this, OBJ_IDENT_OBJBASE))
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


        if (!(obj_getSize(this) >= sizeof(OBJBASE_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
#ifdef  __cplusplus
}
#endif


