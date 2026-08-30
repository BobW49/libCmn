// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//              Scan an AST for various manipulations (AstScan) Object Support
//****************************************************************


/*
 * File:   AstScan.c
 *  Generated 02/12/2023 09:19:30
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
#include        <AstScan_internal.h>
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
    void            AstScan_task_body (
        void            *pData
    )
    {
        //ASTSCAN_DATA  *this = pData;
        TRC_OBJ(this, "%s:\n", __func__);
        
    }
#endif



    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    ASTSCAN_DATA *  AstScan_Alloc (
        void
    )
    {
        ASTSCAN_DATA    *this;
        uint32_t        cbSize = sizeof(ASTSCAN_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    ASTSCAN_DATA *  AstScan_New (
        void
    )
    {
        ASTSCAN_DATA    *this;
        
        this = AstScan_Alloc( );
        if (this) {
            this = AstScan_Init(this);
        } 
        return this;
    }


    ASTSCAN_DATA *  AstScan_NewPre (
        AST_DATA        *pTree,
        AST_ENTRY       *pRoot
    )
    {
        ERESULT         eRc;
        ASTSCAN_DATA    *this;
        
        if ((OBJ_NIL == pTree) || (NULL == pRoot)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        this = AstScan_New( );
        if (this) {
            AstScan_setAst(this, pTree);
            eRc = AstScan_SetupPre(this, pRoot);
            if (ERESULT_FAILED(eRc)) {
                DEBUG_BREAK();
                obj_Release(this);
                return OBJ_NIL;
            }
        }
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                            A r r a y
    //---------------------------------------------------------------
    
    PTRARRAY_DATA * AstScan_getArray (
        ASTSCAN_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!AstScan_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pArray;
    }
    
    
    bool            AstScan_setArray (
        ASTSCAN_DATA    *this,
        PTRARRAY_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!AstScan_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pArray) {
            obj_Release(this->pArray);
        }
        this->pArray = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                            A s t
    //---------------------------------------------------------------
    
    AST_DATA *      AstScan_getAst (
        ASTSCAN_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!AstScan_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pAst;
    }
    
    
    bool            AstScan_setAst (
        ASTSCAN_DATA    *this,
        AST_DATA        *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!AstScan_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pAst) {
            obj_Release(this->pAst);
        }
        this->pAst = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n d e x
    //---------------------------------------------------------------
    
    uint32_t        AstScan_getIndex (
        ASTSCAN_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !AstScan_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        return this->index;
    }

    bool            AstScan_setIndex (
        ASTSCAN_DATA    *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !AstScan_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        this->index = value;
        
        return true;
    }



    //---------------------------------------------------------------
    //                      M e s s a g e s
    //---------------------------------------------------------------

#ifdef   ASTSCAN_MSGS
    bool            AstScan_setMsgs (
        ASTSCAN_DATA    *this,
        void            (*pMsgInfo)(OBJ_ID, const char *, ...),
        void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...),
        OBJ_ID          pObj
    )
    {
#ifdef NDEBUG
#else
        if (!AstScan_Validate(this)) {
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
    
    uint16_t        AstScan_getPriority (
        ASTSCAN_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!AstScan_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            AstScan_setPriority (
        ASTSCAN_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!AstScan_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        return true;
    }



    //---------------------------------------------------------------
    //                            R o o t
    //---------------------------------------------------------------
    
    AST_ENTRY *     AstScan_getRoot (
        ASTSCAN_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!AstScan_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pRoot;
    }

    
    
    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        AstScan_getSize (
        ASTSCAN_DATA    *this
    )
    {
        uint32_t        num = 0;
        
#ifdef NDEBUG
#else
        if (!AstScan_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        if (this->pArray) {
            num = ptrArray_getSize(this->pArray);
        }
        
        return num;
    }



    //---------------------------------------------------------------
    //                          S t a r t
    //---------------------------------------------------------------
    
    uint32_t        AstScan_getStart (
        ASTSCAN_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !AstScan_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        return this->start;
    }

    bool            AstScan_setStart (
        ASTSCAN_DATA    *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !AstScan_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        this->start = value;
        
        return true;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
#ifdef  ASTSCAN_SUPER_DEFINED
    OBJ_DATA *  AstScan_getSuper (
        ASTSCAN_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!AstScan_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return (OBJ_DATA *)this;
    }
#else
    OBJ_DATA *  AstScan_getSuper (
        ASTSCAN_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!AstScan_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return (OBJ_DATA *)this;
    }
#endif

    
    OBJ_IUNKNOWN *  AstScan_getSuperVtbl (
        ASTSCAN_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!AstScan_Validate(this)) {
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
        ERESULT eRc = AstScan_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another ASTSCAN object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         AstScan_Assign (
        ASTSCAN_DATA       *this,
        ASTSCAN_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!AstScan_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!AstScan_Validate(pOther)) {
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

        // Return to caller.
        eRc = ERESULT_SUCCESS;
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
    int             AstScan_Compare (
        ASTSCAN_DATA     *this,
        ASTSCAN_DATA     *pOther
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
#ifdef  ASTSCAN_SINGLETON
        if (OBJ_NIL == this) {
            this = AstScan_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!AstScan_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!AstScan_Validate(pOther)) {
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
        AstScan      *pCopy = AstScan_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a ASTSCAN object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    ASTSCAN_DATA *     AstScan_Copy (
        ASTSCAN_DATA       *this
    )
    {
        ASTSCAN_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!AstScan_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef ASTSCAN_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = AstScan_New( );
        if (pOther) {
            eRc = AstScan_Assign(this, pOther);
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

    void            AstScan_Dealloc (
        OBJ_ID          objId
    )
    {
        ASTSCAN_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!AstScan_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((ASTSCAN_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        AstScan_setArray(this, OBJ_NIL);
        AstScan_setAst(this, OBJ_NIL);

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
        AstScan      *pDeepCopy = AstScan_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a ASTSCAN object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    ASTSCAN_DATA *  AstScan_DeepCopy (
        ASTSCAN_DATA    *this
    )
    {
        ASTSCAN_DATA    *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!AstScan_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = AstScan_New( );
        if (pOther) {
            eRc = AstScan_Assign(this, pOther);
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
    ERESULT         AstScan_Disable (
        ASTSCAN_DATA    *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  ASTSCAN_SINGLETON
        if (OBJ_NIL == this) {
            this = AstScan_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!AstScan_Validate(this)) {
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
    ERESULT         AstScan_Enable (
        ASTSCAN_DATA    *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  ASTSCAN_SINGLETON
        if (OBJ_NIL == this) {
            this = AstScan_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!AstScan_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        TRC_OBJ(this,"\tEnabled?: %s:\n", obj_Enable(this) ? "true" : "false");
#ifdef   ASTSCAN_MSGS
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

    ASTSCAN_DATA *  AstScan_Init (
        ASTSCAN_DATA    *this
    )
    {
        uint32_t        cbSize = sizeof(ASTSCAN_DATA);
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

#ifdef  ASTSCAN_SUPER_DEFINED
        this = (OBJ_ID)obj_Init((OBJ_DATA *)this);   // Needed for Inheritance
#else
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_ASTSCAN);
#endif
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&AstScan_Vtbl);
#ifdef  ASTSCAN_JSON_SUPPORT
        JsonIn_RegisterClass(AstScan_Class());
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
        if (!AstScan_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "AstScan::sizeof(ASTSCAN_DATA) = %lu\n", 
                sizeof(ASTSCAN_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(ASTSCAN_DATA));
#endif

        return this;
    }

     

    //--------------------------------------------------------------
    //                  I n p u t  A d v a n c e
    //--------------------------------------------------------------
    
    AST_ENTRY *     AstScan_InputAdvance (
        ASTSCAN_DATA    *this,
        uint32_t        numChrs
    )
    {
        AST_ENTRY       *pEntry = NULL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !AstScan_Validate(this) ) {
            DEBUG_BREAK();
            return pEntry;
        }
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            return pEntry;
        }
        if (numChrs > 0)
            ;
        else {
            DEBUG_BREAK();
            return pEntry;
        }
#endif
        
        // Shift inputs.
        this->index += numChrs;
        if (this->index < ptrArray_getSize(this->pArray))
            ;
        else {
            return OBJ_NIL;
        }
        pEntry = ptrArray_GetData(this->pArray, (this->index + 1));

        // Return to caller.
        return pEntry;
    }
    
    
    
    //--------------------------------------------------------------
    //               I n p u t  L o o k  A h e a d
    //--------------------------------------------------------------
    
    AST_ENTRY *     AstScan_InputLookAhead (
        ASTSCAN_DATA    *this,
        uint32_t        num
    )
    {
        uint32_t        idx;
        AST_ENTRY       *pEntry = NULL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !AstScan_Validate(this) ) {
            DEBUG_BREAK();
            return pEntry;
        }
        if (NULL == this->pArray) {
            DEBUG_BREAK();
            return pEntry;
        }
        if (num > 0)
            ;
        else {
            DEBUG_BREAK();
            return pEntry;
        }
#endif
        
        idx = this->index + (num - 1);
        if (idx < ptrArray_getSize(this->pArray))
            ;
        else {
            return pEntry;
        }
        pEntry = ptrArray_GetData(this->pArray, (idx + 1));

        // Return to caller.
        return pEntry;
    }
    
    
    
    //---------------------------------------------------------------
    //                      I s  E n a b l e d
    //---------------------------------------------------------------
    
    bool                AstScan_IsEnabled (
        ASTSCAN_DATA       *this
    )
    {
        //ERESULT         eRc;
        bool            fRc = false;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  ASTSCAN_SINGLETON
        if (OBJ_NIL == this) {
            this = AstScan_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!AstScan_Validate(this)) {
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
    
    
    
    //--------------------------------------------------------------
    //                 M a t c h   C l a s s
    //--------------------------------------------------------------
    
    AST_ENTRY *     AstScan_MatchClass (
        ASTSCAN_DATA    *this,
        int32_t         cls
    )
    {
        AST_ENTRY       *pEntry = NULL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !AstScan_Validate(this) ) {
            DEBUG_BREAK();
            return pEntry;
        }
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            return pEntry;
        }
#endif
        this->start = this->index;

        if (this->index < ptrArray_getSize(this->pArray))
            ;
        else {
            return pEntry;
        }

        pEntry = AstScan_InputLookAhead(this, 1);
        if (pEntry && (cls == pEntry->type)) {
            (void)AstScan_InputAdvance(this, 1);
            return pEntry;
        }
        
        // Return to caller.
        return NULL;
    }
    
    
    AST_ENTRY *     AstScan_MatchClasses (
        ASTSCAN_DATA    *this,
        int32_t         *pSet
    )
    {
        AST_ENTRY       *pEntry = NULL;
        uint32_t        start;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AstScan_Validate(this) ) {
            DEBUG_BREAK();
            return pEntry;
        }
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            return pEntry;
        }
        if (NULL == pSet) {
            DEBUG_BREAK();
            return pEntry;
        }
#endif
        start = this->index;
        
        while (*pSet) {
            pEntry = AstScan_MatchClass(this, *pSet);
            if (pEntry) {
                this->start = start;
                return pEntry;
            }
            ++pSet;
        }
        
        // Return to caller.
        return NULL;
    }
    
    
    AST_ENTRY *     AstScan_MatchClassesUntil (
        ASTSCAN_DATA    *this,
        int32_t         *pSet
    )
    {
        AST_ENTRY       *pEntry = NULL;
        uint32_t        start;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!AstScan_Validate(this)) {
            DEBUG_BREAK();
            return pEntry;
        }
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            return pEntry;
        }
        if (NULL == pSet) {
            DEBUG_BREAK();
            return pEntry;
        }
#endif
        start = this->index;
        
        while (this->index < ptrArray_getSize(this->pArray)) {
            pEntry = AstScan_MatchClasses(this, pSet);
            if (pEntry) {
                this->start = start;
                return pEntry;
            }
            this->index++;
        }
        
        // Return to caller.
        return NULL;
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
        void        *pMethod = AstScan_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_DATA, an object's data is returned
                        if it fits in a "void *".
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "AstScan", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          AstScan_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        ASTSCAN_DATA     *this = objId;
        const
        char            *pStrA = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!AstScan_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(ASTSCAN_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)AstScan_Class();
                break;

            case OBJ_QUERYINFO_TYPE_DATA:
                switch (*pStrA) {
     
                    case 'A':
                        if (str_Compare("Ast", (char *)pStrA) == 0) {
                            return (void *)this->pAst;
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
                            return AstScan_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStrA) == 0) {
                            return AstScan_Enable;
                        }
                        break;

                    case 'P':
#ifdef  ASTSCAN_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStrA) == 0) {
                            return AstScan_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStrA) == 0) {
                            return AstScan_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStrA) == 0) {
                            return AstScan_ToDebugString;
                        }
#ifdef  ASTSCAN_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStrA) == 0) {
                            return AstScan_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStrA) == 0) {
                            return AstScan_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == AstScan_ToDebugString)
                    return "ToDebugString";
#ifdef  ASTSCAN_JSON_SUPPORT
                if (pData == AstScan_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                          R e s e t
    //---------------------------------------------------------------

    ERESULT         AstScan_Reset (
        ASTSCAN_DATA    *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!AstScan_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif

        if (this->pAst && obj_IsKindOf(this->pAst, OBJ_IDENT_AST)) {
            if (this->pArray) {
                AstScan_setIndex(this, 0);
                AstScan_setStart(this, 0);
            } else {
                eRc = ERESULT_DATA_MISSING;
            }
        } else {
            eRc = ERESULT_DATA_MISSING;
        }

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          S e t u p
    //---------------------------------------------------------------

    ERESULT         AstScan_SetupPre (
        ASTSCAN_DATA    *this,
        AST_ENTRY       *pRoot
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        PTRARRAY_DATA   *pArray;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!AstScan_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif

        if (this->pAst && obj_IsKindOf(this->pAst, OBJ_IDENT_AST)) {
            pArray = Ast_ToLinearizationPre(this->pAst, pRoot);
            if (OBJ_NIL == pArray) {
                return ERESULT_GENERAL_FAILURE;
            }
            AstScan_setArray(this, pArray);
            obj_Release(pArray);
            this->pRoot = pRoot;
            AstScan_setIndex(this, 0);
            AstScan_setStart(this, 0);
        } else {
            eRc = ERESULT_DATA_MISSING;
        }

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = AstScan_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     AstScan_ToDebugString (
        ASTSCAN_DATA      *this,
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
        if (!AstScan_Validate(this)) {
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
                    AstScan_getSize(this),
                    obj_getRetainCount(this)
            );
        USE_VAR(eRc);

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
        USE_VAR(eRc);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

#ifdef NDEBUG
#else
    bool            AstScan_Validate (
        ASTSCAN_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_ASTSCAN))
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


        if (!(obj_getSize(this) >= sizeof(ASTSCAN_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef  __cplusplus
}
#endif


