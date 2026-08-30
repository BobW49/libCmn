// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//              Source File Location (SrcLoc) Object Support
//****************************************************************


/*
 * File:   SrcLoc.c
 *  Generated 12/25/2022 08:43:29
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
#include        <SrcLoc_internal.h>
#include        <JsonIn.h>
#include        <szTbl.h>
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
    void            SrcLoc_task_body (
        void            *pData
    )
    {
        //SRCLOC_DATA  *this = pData;
        TRC_OBJ(this, "%s:\n", __func__);
        
    }
#endif



    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    SRCLOC_DATA *     SrcLoc_Alloc (
        void
    )
    {
        SRCLOC_DATA       *this;
        uint32_t        cbSize = sizeof(SRCLOC_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    SRCLOC_DATA *     SrcLoc_New (
        void
    )
    {
        SRCLOC_DATA       *this;
        
        this = SrcLoc_Alloc( );
        if (this) {
            this = SrcLoc_Init(this);
        } 
        return this;
    }



    SRCLOC_DATA *   SrcLoc_NewFLC (
        const
        char            *pFileNameA,
        int64_t         offset,
        uint32_t        lineNo,
        uint16_t        colNo
    )
    {
        SRCLOC_DATA       *this;
        
        this = SrcLoc_New( );
        if (this) {
            SrcLoc_setFileName(this, pFileNameA);
            this->data.offset = offset;
            this->data.lineNo = lineNo;
            this->data.colNo  = colNo;
        }
        return this;
    }



    SRCLOC_DATA *   SrcLoc_NewSrcLoc (
        SRCLOC          *pSrc
    )
    {
        SRCLOC_DATA       *this;
        
        this = SrcLoc_New( );
        if (this) {
            memmove(&this->data, pSrc, sizeof(SRCLOC));
        }
        return this;
    }





    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          C o l  N o
    //---------------------------------------------------------------
    
    uint16_t        SrcLoc_getColNo (
        SRCLOC_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !SrcLoc_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        
        return this->data.colNo;
    }
    
    
    bool            SrcLoc_setColNo (
        SRCLOC_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !SrcLoc_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        this->data.colNo = value;
        return true;
    }
    
    
    
    const
    char *          SrcLoc_getFileName (
        SRCLOC_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !SrcLoc_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->data.pFileNameA;
    }
    
    
    bool            SrcLoc_setFileName (
        SRCLOC_DATA     *this,
        const
        char            *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !SrcLoc_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        this->data.pFileNameA = pValue ? szTbl_StringToString(szTbl_Shared(), pValue) : NULL;
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                         L i n e  N o
    //---------------------------------------------------------------
    
    uint32_t        SrcLoc_getLineNo(
        SRCLOC_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !SrcLoc_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        return this->data.lineNo;
    }
    
    bool            SrcLoc_setLineNo(
        SRCLOC_DATA     *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !SrcLoc_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        this->data.lineNo = value;
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                      M e s s a g e s
    //---------------------------------------------------------------

#ifdef   SRCLOC_MSGS
    bool            SrcLoc_setMsgs (
        SRCLOC_DATA    *this,
        void            (*pMsgInfo)(OBJ_ID, const char *, ...),
        void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...),
        OBJ_ID          pObj
    )
    {
#ifdef NDEBUG
#else
        if (!SrcLoc_Validate(this)) {
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
    //                         O f f s e t
    //---------------------------------------------------------------
    
    int64_t         SrcLoc_getOffset (
        SRCLOC_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !SrcLoc_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        return this->data.offset;
    }
    
    bool            SrcLoc_setOffset (
        SRCLOC_DATA     *this,
        int64_t         value
    )
    {
#ifdef NDEBUG
#else
        if( !SrcLoc_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        this->data.offset = value;
        return true;
    }
    
    
     //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        SrcLoc_getPriority (
        SRCLOC_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SrcLoc_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            SrcLoc_setPriority (
        SRCLOC_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!SrcLoc_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        SrcLoc_getSize (
        SRCLOC_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!SrcLoc_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S r c
    //---------------------------------------------------------------
    
    SRCLOC *        SrcLoc_getSrc(
        SRCLOC_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !SrcLoc_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        
        return &this->data;
    }
    
    
    bool            SrcLoc_setSrc(
        SRCLOC_DATA     *this,
        SRCLOC          *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !SrcLoc_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        memmove(&this->data, pValue, sizeof(SRCLOC));
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
#ifdef  SRCLOC_SUPER_DEFINED
    OBJ_DATA *  SrcLoc_getSuper (
        SRCLOC_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SrcLoc_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return (OBJ_DATA *)this;
    }
#else
    OBJ_DATA *  SrcLoc_getSuper (
        SRCLOC_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SrcLoc_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return (OBJ_DATA *)this;
    }
#endif

    
    OBJ_IUNKNOWN *  SrcLoc_getSuperVtbl (
        SRCLOC_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SrcLoc_Validate(this)) {
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
        ERESULT eRc = SrcLoc_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another SRCLOC object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         SrcLoc_Assign (
        SRCLOC_DATA     *this,
        SRCLOC_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!SrcLoc_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!SrcLoc_Validate(pOther)) {
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
        if (pOther->pArray) {
            obj_Release(pOther->pArray);
            pOther->pArray = OBJ_NIL;
        }
#endif

        // Create a copy of objects and areas in this object placing
        // them in other.
#ifdef  XYZZY
        if (this->pArray) {
            if (obj_getVtbl(this->pArray)->pCopy) {
                pOther->pArray = obj_getVtbl(this->pArray)->pCopy(this->pArray);
            }
            else {
                obj_Retain(this->pArray);
                pOther->pArray = this->pArray;
            }
        }
#endif

        // Copy other data from this object to other.
        //pOther->x     = this->x; 
        memmove(&pOther->data, &this->data, sizeof(SRCLOC));

        // Return to caller.
        eRc = ERESULT_SUCCESS;
    eom:
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
    int             SrcLoc_Compare (
        SRCLOC_DATA     *this,
        SRCLOC_DATA     *pOther
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
#ifdef  SRCLOC_SINGLETON
        if (OBJ_NIL == this) {
            this = SrcLoc_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!SrcLoc_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!SrcLoc_Validate(pOther)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -2;
        }
#endif

        iRc = strcmp(this->data.pFileNameA, pOther->data.pFileNameA);
        if (0 == iRc) {
            ;
        }
        else {
            return iRc;
        }
        
        iRc = this->data.lineNo == pOther->data.lineNo;
        if (0 == iRc) {
            ;
        }
        else {
            return iRc;
        }
        
        iRc = this->data.colNo == pOther->data.colNo;
        if (0 == iRc) {
            ;
        }
        else {
            return iRc;
        }
        
        return iRc;
    }
    
   
 
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        SrcLoc      *pCopy = SrcLoc_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a SRCLOC object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    SRCLOC_DATA *     SrcLoc_Copy (
        SRCLOC_DATA       *this
    )
    {
        SRCLOC_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!SrcLoc_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef SRCLOC_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = SrcLoc_New( );
        if (pOther) {
            eRc = SrcLoc_Assign(this, pOther);
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

    void            SrcLoc_Dealloc (
        OBJ_ID          objId
    )
    {
        SRCLOC_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!SrcLoc_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((SRCLOC_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

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
        SrcLoc      *pDeepCopy = SrcLoc_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a SRCLOC object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    SRCLOC_DATA *     SrcLoc_DeepCopy (
        SRCLOC_DATA       *this
    )
    {
        SRCLOC_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!SrcLoc_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = SrcLoc_New( );
        if (pOther) {
            eRc = SrcLoc_Assign(this, pOther);
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
    ERESULT         SrcLoc_Disable (
        SRCLOC_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  SRCLOC_SINGLETON
        if (OBJ_NIL == this) {
            this = SrcLoc_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!SrcLoc_Validate(this)) {
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
    ERESULT         SrcLoc_Enable (
        SRCLOC_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  SRCLOC_SINGLETON
        if (OBJ_NIL == this) {
            this = SrcLoc_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!SrcLoc_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        TRC_OBJ(this,"\tEnabled?: %s:\n", obj_Enable(this) ? "true" : "false");
#ifdef   SRCLOC_MSGS
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
    //                          I n i t
    //---------------------------------------------------------------

    SRCLOC_DATA *   SrcLoc_Init (
        SRCLOC_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(SRCLOC_DATA);
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

#ifdef  SRCLOC_SUPER_DEFINED
        this = (OBJ_ID)obj_Init((OBJ_DATA *)this);   // Needed for Inheritance
#else
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_SRCLOC);
#endif
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&SrcLoc_Vtbl);
#ifdef  SRCLOC_JSON_SUPPORT
        JsonIn_RegisterClass(SrcLoc_Class());
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
        if (!SrcLoc_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "SrcLoc::sizeof(SRCLOC_DATA) = %lu\n", 
                sizeof(SRCLOC_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(SRCLOC_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                      I s  E n a b l e d
    //---------------------------------------------------------------
    
    bool                SrcLoc_IsEnabled (
        SRCLOC_DATA       *this
    )
    {
        //ERESULT         eRc;
        bool            fRc = false;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  SRCLOC_SINGLETON
        if (OBJ_NIL == this) {
            this = SrcLoc_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!SrcLoc_Validate(this)) {
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
        void        *pMethod = SrcLoc_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_DATA, an object's data is returned
                        if it fits in a "void *".
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "SrcLoc", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          SrcLoc_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        SRCLOC_DATA     *this = objId;
        const
        char            *pStrA = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!SrcLoc_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(SRCLOC_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)SrcLoc_Class();
                break;

            case OBJ_QUERYINFO_TYPE_DATA:
                switch (*pStrA) {
     
                    case 'S':
                        if (str_Compare("Src", (char *)pStrA) == 0) {
                            return (void *)&this->data;
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
                            return SrcLoc_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStrA) == 0) {
                            return SrcLoc_Enable;
                        }
                        break;

                    case 'P':
#ifdef  SRCLOC_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStrA) == 0) {
                            return SrcLoc_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStrA) == 0) {
                            return SrcLoc_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStrA) == 0) {
                            return SrcLoc_ToDebugString;
                        }
#ifdef  SRCLOC_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStrA) == 0) {
                            return SrcLoc_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStrA) == 0) {
                            return SrcLoc_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == SrcLoc_ToDebugString)
                    return "ToDebugString";
#ifdef  SRCLOC_JSON_SUPPORT
                if (pData == SrcLoc_ToJson)
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
        ASTR_DATA      *pDesc = SrcLoc_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     SrcLoc_ToDebugString (
        SRCLOC_DATA      *this,
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
#ifdef NDEBUG
#else
        if (!SrcLoc_Validate(this)) {
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
                    "{%p(srcLoc) file=%s offset=%lld line=%d col=%d ",
                    this,
                    SrcLoc_getFileName(this) ? SrcLoc_getFileName(this) : "",
                    SrcLoc_getOffset(this),
                    SrcLoc_getLineNo(this),
                    SrcLoc_getColNo(this)
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
    bool            SrcLoc_Validate (
        SRCLOC_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_SRCLOC))
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


        if (!(obj_getSize(this) >= sizeof(SRCLOC_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef  __cplusplus
}
#endif


