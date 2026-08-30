// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
// Binary Coded Decimal based on int128_t (RW_BCD128) Object Support
//****************************************************************


/*
 * File:   RW_BCD128.c
 *  Generated 06/03/2026 08:40:22
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
#include        <RW_BCD128_internal.h>
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
    void            RW_BCD128_task_body (
        void            *pData
    )
    {
        RW_BCD128_DATA  *this = pData;
        TRC_OBJ(this, "%s(%p):\n", __func__, this);
        
    }
#endif



    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    RW_BCD128_DATA * 
                    RW_BCD128_Alloc (
        void
    )
    {
        RW_BCD128_DATA  *this;
        uint32_t        cbSize = sizeof(RW_BCD128_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    RW_BCD128_DATA * 
                    RW_BCD128_New (
        void
    )
    {
        RW_BCD128_DATA  *this;
        
        this = RW_BCD128_Alloc( );
        if (this) {
            this = RW_BCD128_Init(this);
        } 
        return this;
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

    bool            RW_BCD128_getFlag (
        RW_BCD128_DATA  *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!RW_BCD128_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->flag ? true : false;
    }


    bool            RW_BCD128_setFlag (
        RW_BCD128_DATA  *this,
        bool            fValue
    )
    {
#ifdef NDEBUG
#else
        if (!RW_BCD128_Validate(this)) {
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

#ifdef   RW_BCD128_MSGS
    bool            RW_BCD128_setMsgs (
        RW_BCD128_DATA  *this,
        void            (*pMsgInfo)(OBJ_ID, const char *, ...),
        void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...),
        OBJ_ID          pObj
    )
    {
#ifdef NDEBUG
#else
        if (!RW_BCD128_Validate(this)) {
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
    uint16_t        RW_BCD128_getPriority (
        RW_BCD128_DATA  *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!RW_BCD128_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            RW_BCD128_setPriority (
        RW_BCD128_DATA  *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!RW_BCD128_Validate(this)) {
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
    
    uint32_t        RW_BCD128_getSize (
        RW_BCD128_DATA  *this
    )
    {
#ifdef NDEBUG
#else
        if (!RW_BCD128_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA *     RW_BCD128_getStr (
        RW_BCD128_DATA  *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!RW_BCD128_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStr;
    }
    
    
    bool            RW_BCD128_setStr (
        RW_BCD128_DATA  *this,
        ASTR_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!RW_BCD128_Validate(this)) {
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
    
#ifdef  RW_BCD128_SUPER_DEFINED
    OBJ_DATA *      RW_BCD128_getSuper (
        RW_BCD128_DATA  *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!RW_BCD128_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return (OBJ_DATA *)this;
    }
#else
    OBJ_DATA *      RW_BCD128_getSuper (
        RW_BCD128_DATA  *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!RW_BCD128_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return (OBJ_DATA *)this;
    }
#endif

    
    OBJ_IUNKNOWN *  RW_BCD128_getSuperVtbl (
        RW_BCD128_DATA  *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!RW_BCD128_Validate(this)) {
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
        ERESULT eRc = RW_BCD128_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another RW_BCD128 object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         RW_BCD128_Assign (
        RW_BCD128_DATA  *this,
        RW_BCD128_DATA  *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!RW_BCD128_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!RW_BCD128_Validate(pOther)) {
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
    int             RW_BCD128_Compare (
        RW_BCD128_DATA  *this,
        RW_BCD128_DATA  *pOther
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
#ifdef  RW_BCD128_SINGLETON
        if (OBJ_NIL == this) {
            this = RW_BCD128_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!RW_BCD128_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!RW_BCD128_Validate(pOther)) {
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
        RW_BCD128      *pCopy = RW_BCD128_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a RW_BCD128 object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    RW_BCD128_DATA * 
                    RW_BCD128_Copy (
        RW_BCD128_DATA  *this
    )
    {
        RW_BCD128_DATA  *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!RW_BCD128_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef RW_BCD128_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = RW_BCD128_New( );
        if (pOther) {
            eRc = RW_BCD128_Assign(this, pOther);
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

    void            RW_BCD128_Dealloc (
        OBJ_ID          objId
    )
    {
        RW_BCD128_DATA  *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!RW_BCD128_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((RW_BCD128_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        RW_BCD128_setStr(this, OBJ_NIL);

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
        RW_BCD128      *pDeepCopy = RW_BCD128_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a RW_BCD128 object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    RW_BCD128_DATA * 
                    RW_BCD128_DeepCopy (
        RW_BCD128_DATA  *this
    )
    {
        RW_BCD128_DATA  *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!RW_BCD128_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = RW_BCD128_New( );
        if (pOther) {
            eRc = RW_BCD128_Assign(this, pOther);
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
    ERESULT         RW_BCD128_Disable (
        RW_BCD128_DATA  *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  RW_BCD128_SINGLETON
        if (OBJ_NIL == this) {
            this = RW_BCD128_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!RW_BCD128_Validate(this)) {
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
    ERESULT         RW_BCD128_Enable (
        RW_BCD128_DATA  *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  RW_BCD128_SINGLETON
        if (OBJ_NIL == this) {
            this = RW_BCD128_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!RW_BCD128_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        TRC_OBJ(this,"\tEnabled?: %s:\n", obj_Enable(this) ? "true" : "false");
#ifdef   RW_BCD128_MSGS
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
    
    uint32_t        RW_BCD128_Hash(
        RW_BCD128_DATA  *this
    )
    {
        uint32_t        hash = 0;
        char            *pStr = NULL;
        
#ifdef NDEBUG
#else
        if( !RW_BCD128_Validate(this) ) {
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

    RW_BCD128_DATA * 
                    RW_BCD128_Init (
        RW_BCD128_DATA  *this
    )
    {
        uint32_t        cbSize = sizeof(RW_BCD128_DATA);
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

#ifdef  RW_BCD128_SUPER_DEFINED
        this = (OBJ_ID)obj_Init((OBJ_DATA *)this);   // Needed for Inheritance
#else
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_RW_BCD128);
#endif
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&RW_BCD128_Vtbl);
#ifdef  RW_BCD128_JSON_SUPPORT
        JsonIn_RegisterClass(RW_BCD128_Class());
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
        if (!RW_BCD128_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "RW_BCD128::sizeof(RW_BCD128_DATA) = %lu\n", 
                sizeof(RW_BCD128_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(RW_BCD128_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                      I s  E n a b l e d
    //---------------------------------------------------------------
    
    bool            RW_BCD128_IsEnabled (
        RW_BCD128_DATA  *this
    )
    {
        //ERESULT         eRc;
        bool            fRc = false;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  RW_BCD128_SINGLETON
        if (OBJ_NIL == this) {
            this = RW_BCD128_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!RW_BCD128_Validate(this)) {
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
        void        *pMethod = RW_BCD128_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_DATA, an object's data is returned
                        if it fits in a "void *".
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "RW_BCD128", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          RW_BCD128_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        RW_BCD128_DATA  *this = objId;
        const
        char            *pStrA = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!RW_BCD128_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(RW_BCD128_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)RW_BCD128_Class();
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
                            return RW_BCD128_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStrA) == 0) {
                            return RW_BCD128_Enable;
                        }
                        break;

                    case 'P':
#ifdef  RW_BCD128_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStrA) == 0) {
                            return RW_BCD128_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStrA) == 0) {
                            return RW_BCD128_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStrA) == 0) {
                            return RW_BCD128_ToDebugString;
                        }
#ifdef  RW_BCD128_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStrA) == 0) {
                            return RW_BCD128_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStrA) == 0) {
                            return RW_BCD128_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == RW_BCD128_ToDebugString)
                    return "ToDebugString";
#ifdef  RW_BCD128_JSON_SUPPORT
                if (pData == RW_BCD128_ToJson)
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
        ASTR_DATA      *pDesc = RW_BCD128_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     RW_BCD128_ToDebugString (
        RW_BCD128_DATA  *this,
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
        if (!RW_BCD128_Validate(this)) {
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
                    RW_BCD128_getSize(this),
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
    bool            RW_BCD128_Validate (
        RW_BCD128_DATA  *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_RW_BCD128))
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


        if (!(obj_getSize(this) >= sizeof(RW_BCD128_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
#ifdef  __cplusplus
}
#endif


