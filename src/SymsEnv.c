// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//              Symbol Table Environment ADT (SymsEnv) Object Support
//****************************************************************


/*
 * File:   SymsEnv.c
 *  Generated 05/29/2023 10:14:40
 *
 */

 
/*

        The record grows from the bottom up.  The index grows from the top
        down. The unused space is the space in-between. To get the valid
        offset to the next data record, we must add back in the size of
        block header and the index.

    Offset
      0                                     +==========================+
                                            |      Block Header        |
                                            +==========================+
 sizeof(DATA_BLOCK)                         |          Index           |
                                            | (Grows down toward Data) |
                                            +--------------------------+
                                            |   Index 1 - 20 bytes     |
                                            +--------------------------+
 sizeof(DATA_BLOCK) + sizeof(INDEX_RECORD)  |   Index 2 - 30 bytes     |
                                            +==========================+
                                            |                          |
                                            |      Unused Space        |
                                            |                          |
                                            +==========================+
                                            |      Data Records        |
                                            | (Grows up toward Index)  |
                                            +--------------------------+
                                            | Data Record 2 - 30 bytes |
                                            +--------------------------+
                                            | Data Record 1 - 20 bytes |
                                            +==========================+
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
#include        <SymsEnv_internal.h>
#include        <JsonIn.h>
#include        <trace.h>
#include        <utf8.h>






#ifdef  __cplusplus
extern "C" {
#endif
    

    // Address of Index Entry for x'th entry (x relative to 0)
    #define IndexPtr(x)\
            (INDEX_RECORD *)(((uint8_t *)pBlock)+sizeof(DATA_BLOCK)+(x * sizeof(INDEX_RECORD)))


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

    //---------------------------------------------------------------
    //              B l o c k  M a n i p u l a t i o n
    //---------------------------------------------------------------

    ERESULT         SymsEnv_BlockSetup (
        SYMSENV_DATA    *this,
        uint16_t        blockSize,
        DATA_BLOCK      *pBlock
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        uint16_t        minSize;

        if (0 == blockSize) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if (NULL == pBlock) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }

        minSize = sizeof(DATA_BLOCK) + sizeof(INDEX_RECORD) + 1;
        if ((blockSize < minSize) || (blockSize > DATA_BLOCK_MAX_SIZE)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }

        pBlock->cbSize = blockSize;
        pBlock->unusedSize = (blockSize - sizeof(DATA_BLOCK));
        pBlock->numRecords = 0;

        return eRc;
    }



    uint16_t        SymsEnv_DataOffset (
        SYMSENV_DATA    *this,
        DATA_BLOCK      *pBlock,
        uint16_t        index,
        uint16_t        recordSize
    )
    {
        INDEX_RECORD    *pIndex;
        int32_t         offset = 0;
        int             i;

        // Do initialization.
        if (index > pBlock->numRecords)
            return 0;

        offset += pBlock->cbSize;
        if (index) {
            for (i=0; i<=(index-1); i++) {
                pIndex = IndexPtr(i);
                offset -= pIndex->idxSize;
            }
        }
        offset -= recordSize;

        // Return to caller.
        return (uint16_t)(offset & 0xFFFF);
    }



    ERESULT         SymsEnv_RecordAppend (
        SYMSENV_DATA    *this,
        DATA_BLOCK      *pBlock,
        uint16_t        rcdSize,
        void            *pData,
        uint8_t         **ppRcd         // OUT - Record Address
    )
    {
        //ERESULT         eRc;
        //uint16_t        amt;
        //uint16_t        rcdNum;
        uint16_t        offset = 0;
        uint8_t         *pBlockData;
        INDEX_RECORD    *pIndex;

        // Do initialization.
#ifdef NDEBUG
#else
        if (NULL == pBlock) {
            DEBUG_BREAK();
            return ERESULT_GENERAL_FAILURE;
        }
        if ((rcdSize == 0) || (rcdSize >= DATA_BLOCK_MAX_SIZE)) {
            DEBUG_BREAK();
            return ERESULT_DATA_SIZE;
        }
#endif
        if ((rcdSize + sizeof(INDEX_RECORD)) > pBlock->unusedSize) {
            return ERESULT_DATA_TOO_BIG;
        }

        offset = SymsEnv_DataOffset(this, pBlock, pBlock->numRecords, rcdSize);
        pBlockData = (((uint8_t *)pBlock) + offset);
        memmove(pBlockData, pData, rcdSize);
        pIndex = IndexPtr(pBlock->numRecords);
        pIndex->idxSize = rcdSize;
        pBlock->numRecords++;
        pBlock->unusedSize -= rcdSize + sizeof(INDEX_RECORD);

        // Return to caller.
        if (ppRcd) {
            *ppRcd = pBlockData;
        }
        return ERESULT_SUCCESS;
    }




    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    SYMSENV_DATA *     SymsEnv_Alloc (
        void
    )
    {
        SYMSENV_DATA       *this;
        uint32_t        cbSize = sizeof(SYMSENV_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    SYMSENV_DATA *     SymsEnv_New (
        void
    )
    {
        SYMSENV_DATA       *this;
        
        this = SymsEnv_Alloc( );
        if (this) {
            this = SymsEnv_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                      M e s s a g e s
    //---------------------------------------------------------------

#ifdef   SYMSENV_MSGS
    bool            SymsEnv_setMsgs (
        SYMSENV_DATA    *this,
        void            (*pMsgInfo)(OBJ_ID, const char *, ...),
        void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...),
        OBJ_ID          pObj
    )
    {
#ifdef NDEBUG
#else
        if (!SymsEnv_Validate(this)) {
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
    
    uint16_t        SymsEnv_getPriority (
        SYMSENV_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SymsEnv_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            SymsEnv_setPriority (
        SYMSENV_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!SymsEnv_Validate(this)) {
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
    
    uint32_t        SymsEnv_getSize (
        SYMSENV_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!SymsEnv_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA * SymsEnv_getStr (
        SYMSENV_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SymsEnv_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStr;
    }
    
    
    bool        SymsEnv_setStr (
        SYMSENV_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!SymsEnv_Validate(this)) {
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
    
#ifdef  SYMSENV_SUPER_DEFINED
    OBJ_DATA *  SymsEnv_getSuper (
        SYMSENV_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SymsEnv_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return (OBJ_DATA *)this;
    }
#else
    OBJ_DATA *  SymsEnv_getSuper (
        SYMSENV_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SymsEnv_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return (OBJ_DATA *)this;
    }
#endif

    
    OBJ_IUNKNOWN *  SymsEnv_getSuperVtbl (
        SYMSENV_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SymsEnv_Validate(this)) {
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
        ERESULT eRc = SymsEnv_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another SYMSENV object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         SymsEnv_Assign (
        SYMSENV_DATA       *this,
        SYMSENV_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!SymsEnv_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!SymsEnv_Validate(pOther)) {
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
    int             SymsEnv_Compare (
        SYMSENV_DATA     *this,
        SYMSENV_DATA     *pOther
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
#ifdef  SYMSENV_SINGLETON
        if (OBJ_NIL == this) {
            this = SymsEnv_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!SymsEnv_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!SymsEnv_Validate(pOther)) {
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
        SymsEnv      *pCopy = SymsEnv_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a SYMSENV object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    SYMSENV_DATA *     SymsEnv_Copy (
        SYMSENV_DATA       *this
    )
    {
        SYMSENV_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!SymsEnv_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef SYMSENV_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = SymsEnv_New( );
        if (pOther) {
            eRc = SymsEnv_Assign(this, pOther);
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

    void            SymsEnv_Dealloc (
        OBJ_ID          objId
    )
    {
        SYMSENV_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!SymsEnv_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((SYMSENV_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        SymsEnv_setStr(this, OBJ_NIL);

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
        SymsEnv      *pDeepCopy = SymsEnv_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a SYMSENV object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    SYMSENV_DATA *     SymsEnv_DeepCopy (
        SYMSENV_DATA       *this
    )
    {
        SYMSENV_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!SymsEnv_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = SymsEnv_New( );
        if (pOther) {
            eRc = SymsEnv_Assign(this, pOther);
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
    ERESULT         SymsEnv_Disable (
        SYMSENV_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  SYMSENV_SINGLETON
        if (OBJ_NIL == this) {
            this = SymsEnv_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!SymsEnv_Validate(this)) {
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
    ERESULT         SymsEnv_Enable (
        SYMSENV_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  SYMSENV_SINGLETON
        if (OBJ_NIL == this) {
            this = SymsEnv_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!SymsEnv_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        TRC_OBJ(this,"\tEnabled?: %s:\n", obj_Enable(this) ? "true" : "false");
#ifdef   SYMSENV_MSGS
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

    SYMSENV_DATA *   SymsEnv_Init (
        SYMSENV_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(SYMSENV_DATA);
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

#ifdef  SYMSENV_SUPER_DEFINED
        this = (OBJ_ID)Blocks_Init((BLOCKS_DATA *)this);        // Needed for Inheritance
#else
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_SYMSENV);
#endif
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&SymsEnv_Vtbl);
#ifdef  SYMSENV_JSON_SUPPORT
        JsonIn_RegisterClass(SymsEnv_Class());
#endif
        
#ifdef  XYZZY
        // Allow for fast access to objects.
        eRc = Blocks_SetupSizes((BLOCKS_DATA *)this, 0, sizeof(OBJHASH_NODE));
        if (ERESULT_FAILED(eRc)) {
           DEBUG_BREAK();
           obj_Release(this);
           return this;
        }

        Blocks_setDeleteExit(
                             (BLOCKS_DATA *)this,
                             (void *)ObjHash_DeleteExit,
                             this,
                             NULL
        );
        Blocks_SetupIndex((BLOCKS_DATA *)this);
        
        this->main.pLevels = array_NewWithSize(sizeof(LISTDL_DATA));
        if (OBJ_NIL == this->main.pLevels) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        } else {
            LISTDL_DATA     list;
            // Add Scope 0.
            listdl_Init(&list, offsetof(OBJHASH_NODE, level));
            eRc = array_Push(this->main.pLevels, &list);
        }
#endif

#ifdef NDEBUG
#else
        if (!SymsEnv_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "SymsEnv::sizeof(SYMSENV_DATA) = %lu\n", 
                sizeof(SYMSENV_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(SYMSENV_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                      I s  E n a b l e d
    //---------------------------------------------------------------
    
    bool                SymsEnv_IsEnabled (
        SYMSENV_DATA       *this
    )
    {
        //ERESULT         eRc;
        bool            fRc = false;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  SYMSENV_SINGLETON
        if (OBJ_NIL == this) {
            this = SymsEnv_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!SymsEnv_Validate(this)) {
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
        void        *pMethod = SymsEnv_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_DATA, an object's data is returned
                        if it fits in a "void *".
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "SymsEnv", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          SymsEnv_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        SYMSENV_DATA     *this = objId;
        const
        char            *pStrA = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!SymsEnv_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(SYMSENV_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)SymsEnv_Class();
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
                            return SymsEnv_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStrA) == 0) {
                            return SymsEnv_Enable;
                        }
                        break;

                    case 'P':
#ifdef  SYMSENV_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStrA) == 0) {
                            return SymsEnv_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStrA) == 0) {
                            return SymsEnv_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStrA) == 0) {
                            return SymsEnv_ToDebugString;
                        }
#ifdef  SYMSENV_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStrA) == 0) {
                            return SymsEnv_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStrA) == 0) {
                            return SymsEnv_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == SymsEnv_ToDebugString)
                    return "ToDebugString";
#ifdef  SYMSENV_JSON_SUPPORT
                if (pData == SymsEnv_ToJson)
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
        ASTR_DATA      *pDesc = SymsEnv_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     SymsEnv_ToDebugString (
        SYMSENV_DATA      *this,
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
        if (!SymsEnv_Validate(this)) {
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
                    SymsEnv_getSize(this),
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
    bool            SymsEnv_Validate (
        SYMSENV_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_SYMSENV))
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


        if (!(obj_getSize(this) >= sizeof(SYMSENV_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
#ifdef  __cplusplus
}
#endif


