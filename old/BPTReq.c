// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
// B-Plus Tree Internal Request Processor (BPTReq) Object Support
//****************************************************************


/*
 * File:   BPTReq.c
 *  Generated 01/31/2023 20:11:00
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
#include        <BPTReq_internal.h>
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

    ERESULT         BPTReq_BlockFindParent(
        BPTREQ_DATA     *this,
        uint32_t        lbn,                // Logical Block Number
        OBJ_ID          *ppObj
    )
    {
        ERESULT         eRc = ERESULT_DATA_NOT_FOUND;
        OBJ_ID          *pObj;
        uint32_t        iMax;
        uint32_t        i;
        uint32_t        index;
        BPT_BLK_VTBL    *pVtbl = NULL;

        TRC_OBJ(this, "BPT_BlockFindParent lsn=%d\n", lbn);
        
        if (ppObj)
            *ppObj = OBJ_NIL;
        iMax = ObjArray_getSize(this->pSrchStk);
        for (i=iMax; i>0; --i) {
            pObj = ObjArray_Get(this->pSrchStk, i);
            pVtbl = (BPT_BLK_VTBL *)obj_getVtbl(pObj);
            index = pVtbl->pGetLBN(pObj);
            if (lbn == index) {
                if (i > 1) {
                    pObj = ObjArray_Get(this->pSrchStk, (i - 1));
                    if (ppObj)
                        *ppObj = pObj;
#ifdef NDEBUG
#else
                    if (obj_Trace(this)) {
                        OBJ_IUNKNOWN    *pVtbl = obj_getVtbl(pObj);
                        ASTR_DATA       *pStr = pVtbl->pToDebugString(pObj, 8);
                        TRC_OBJ(this, "\tFound:\n%s\n", AStr_getData(pStr));
                        obj_Release(pStr);
                    }
#endif
                    eRc = ERESULT_SUCCESS;
                }
                break;
            }
        }
        
        TRC_OBJ(this, "\tNot Found\n");
        return eRc;
    }
    
    
    


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    BPTREQ_DATA *     BPTReq_Alloc (
        void
    )
    {
        BPTREQ_DATA       *this;
        uint32_t        cbSize = sizeof(BPTREQ_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    BPTREQ_DATA *     BPTReq_New (
        void
    )
    {
        BPTREQ_DATA       *this;
        
        this = BPTReq_Alloc( );
        if (this) {
            this = BPTReq_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                           I / O
    //---------------------------------------------------------------

    RRDS_DATA *     BPTReq_getIO (
        BPTREQ_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!BPTReq_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pIO;
    }


    bool        BPTReq_setIO (
        BPTREQ_DATA     *this,
        RRDS_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!BPTReq_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pIO) {
            obj_Release(this->pIO);
        }
        this->pIO = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                      M e s s a g e s
    //---------------------------------------------------------------

#ifdef   BPTREQ_MSGS
    bool            BPTReq_setMsgs (
        BPTREQ_DATA    *this,
        void            (*pMsgInfo)(OBJ_ID, const char *, ...),
        void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...),
        OBJ_ID          pObj
    )
    {
#ifdef NDEBUG
#else
        if (!BPTReq_Validate(this)) {
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
    //                           P a t h
    //---------------------------------------------------------------

    PATH_DATA *     BPTReq_getPath (
        BPTREQ_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!BPTReq_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pPath;
    }


    bool        BPTReq_setPath (
        BPTREQ_DATA     *this,
        PATH_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!BPTReq_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pPath) {
            obj_Release(this->pPath);
        }
        this->pPath = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        BPTReq_getPriority (
        BPTREQ_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!BPTReq_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            BPTReq_setPriority (
        BPTREQ_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!BPTReq_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        return true;
    }



    //---------------------------------------------------------------
    //                           R o o t
    //---------------------------------------------------------------

    OBJ_ID          BPTReq_getRoot (
        BPTREQ_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!BPTReq_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pRoot;
    }


    bool        BPTReq_setRoot (
        BPTREQ_DATA     *this,
        OBJ_ID          pValue
    )
    {
#ifdef NDEBUG
#else
        if (!BPTReq_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pRoot) {
            obj_Release(this->pRoot);
        }
        this->pRoot = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        BPTReq_getSize (
        BPTREQ_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!BPTReq_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                  S e a r c h  S t a c k
    //---------------------------------------------------------------

    OBJARRAY_DATA * BPTReq_getSrchStk (
        BPTREQ_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!BPTReq_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pSrchStk;
    }


    bool        BPTReq_setSrchStk (
        BPTREQ_DATA     *this,
        OBJARRAY_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!BPTReq_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pSrchStk) {
            obj_Release(this->pSrchStk);
        }
        this->pSrchStk = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA * BPTReq_getStr (
        BPTREQ_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!BPTReq_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStr;
    }
    
    
    bool        BPTReq_setStr (
        BPTREQ_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!BPTReq_Validate(this)) {
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
    
#ifdef  BPTREQ_SUPER_DEFINED
    OBJ_DATA *  BPTReq_getSuper (
        BPTREQ_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!BPTReq_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return (OBJ_DATA *)this;
    }
#else
    OBJ_DATA *  BPTReq_getSuper (
        BPTREQ_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!BPTReq_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return (OBJ_DATA *)this;
    }
#endif

    
    OBJ_IUNKNOWN *  BPTReq_getSuperVtbl (
        BPTREQ_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!BPTReq_Validate(this)) {
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
        ERESULT eRc = BPTReq_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another BPTREQ object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         BPTReq_Assign (
        BPTREQ_DATA       *this,
        BPTREQ_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!BPTReq_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!BPTReq_Validate(pOther)) {
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
    //                 B l o c k  R e a d
    //---------------------------------------------------------------
    
    ERESULT         BPTReq_BlockRead(
        BPTREQ_DATA     *this,
        uint32_t        lbn,                // Logical Block Number
        OBJ_ID          *ppObj
    )
    {
        ERESULT         eRc = ERESULT_OUT_OF_MEMORY;
        BPTINDEX_DATA   *pIndex = OBJ_NIL;
        BPTLEAF_DATA    *pLeaf = OBJ_NIL;
        uint8_t         *pData = NULL;

        TRC_OBJ(this, "BPTReq_BlockRead lsn=%d\n", lbn);
        
        // Load the block into the LRU.
        eRc =   RRDS_RecordRead(
                                    this->pIO,
                                    lbn,
                                    NULL
                );
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            TRC_OBJ(this, "\tRead Error!\n");
            return eRc;
        }
        
        //FIXME: pData = (uint8_t *)lru_FindBuffer(this->pLRU, lbn);
        if (*pData == 'I') {
            pIndex = BPTIndex_New();
            if (OBJ_NIL == pIndex) {
                DEBUG_BREAK();
                TRC_OBJ(this, "\tCould not create Index Block Error!\n");
                return ERESULT_OUT_OF_MEMORY;
            }
#ifdef NDEBUG
#else
            if (obj_Trace(this))
                obj_TraceSet(pIndex, true);
#endif
            //FIXME: eRc = BPTIndex_Setup(pIndex, this->blockSize, lbn, this->dataSize, true);
            if (ERESULT_FAILED(eRc)) {
                TRC_OBJ(this, "\tIndex Block Setup Error!\n");
                obj_Release(pIndex);
                return eRc;
            }
            BPTIndex_setManager(pIndex, (void *)this);
            //FIXME: BPTIndex_CopyFrom(pIndex, (void *)pData);
#ifdef NDEBUG
#else
            if (obj_Trace(this)) {
                eRc = BPTIndex_Verify(pIndex);
                if (ERESULT_FAILED(eRc)) {
                    TRC_OBJ(this, "\tIndex Block Verify Error!\n");
                    ASTR_DATA       *pStr = BPTLeaf_ToDebugString(pLeaf, 4);
                    fprintf(stderr, "%s\n", AStr_getData(pStr));
                    obj_Release(pStr);
                    DEBUG_BREAK();
                    obj_Release(pIndex);
                    return eRc;
                }
            }
#endif
            if (ppObj)
                *ppObj = pIndex;
            else
                obj_Release(pIndex);
            pIndex = OBJ_NIL;
            TRC_OBJ(this, "\tFound index Block\n");
        }
        else if (*pData == 'L') {
            pLeaf = BPTLeaf_New();
            if (OBJ_NIL == pLeaf) {
                TRC_OBJ(this, "\tCould not create Leaf Block Error!\n");
                DEBUG_BREAK();
                return ERESULT_OUT_OF_MEMORY;
            }
#ifdef NDEBUG
#else
            if (obj_Trace(this))
                obj_TraceSet(pLeaf, true);
#endif
            //FIXME: eRc = BPTLeaf_Setup(pLeaf, this->blockSize, this->dataSize, lbn, true);
            if (ERESULT_FAILED(eRc)) {
                TRC_OBJ(this, "\tLeaf Block Setup Error!\n");
                obj_Release(pLeaf);
                return eRc;
            }
            BPTLeaf_setManager(pLeaf, (void *)this);
            //FIXME: BPTLeaf_CopyFrom(pLeaf, (void *)pData);
#ifdef NDEBUG
#else
            if (obj_Trace(this)) {
                eRc = BPTLeaf_Verify(pLeaf);
                if (ERESULT_FAILED(eRc)) {
                    TRC_OBJ(this, "\tLeaf Block Verify Error!\n");
                    ASTR_DATA       *pStr = BPTLeaf_ToDebugString(pLeaf, 4);
                    fprintf(stderr, "%s\n", AStr_getData(pStr));
                    obj_Release(pStr);
                    DEBUG_BREAK();
                    obj_Release(pLeaf);
                    return eRc;
                }
            }
#endif
            if (ppObj)
                *ppObj = pLeaf;
            else
                obj_Release(pLeaf);
            pLeaf = OBJ_NIL;
            TRC_OBJ(this, "\tFound Leaf Block\n");
        }
        else {
            DEBUG_BREAK();
            return ERESULT_GENERAL_FAILURE;
        }
        
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                 B l o c k  S e a r c h
    //---------------------------------------------------------------
    
    /*!
     Search the blocks down to the leaf blocks for a specific key.  If found,
     set up work block for the found key.  If not found, set up work block for
     insertion point in block.  Also, the srchStk will contain all the blocks
     searched to find the leaf block.  So, it can be used for figuring out
     parent blocks.
     @param     this        Object Pointer
     @param     lbn         Block Number to start with
     @param     key         key to be looked for
     @param     pData       Optional pointer to the returned data for the key
                            if found
     @return    If successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     @warning   this->srchCur should be zeroed before a search begins.
     */
    ERESULT         BPTReq_BlockSearchKey (
        BPTREQ_DATA     *this,
        uint32_t        lbn,                // Logical Block Number
        uint32_t        key,
        void            *pData
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        uint32_t        nodeIndex = 0;
        OBJ_ID          pObject = OBJ_NIL;
        bool            fMore = true;
        bool            fRead = false;
        BPT_BLK_VTBL    *pVtbl;
        
        // Do initialization.
        TRC_OBJ(this, "BPTReq_BlockSearchKey lsn=%d, key=%d\n", lbn, key);
        
        if (0 == lbn) {         // Use the root.
            pObject = this->pRoot;
            TRC_OBJ(this, "\tUsing Root for first block\n");
        }
        
        while (fMore) {
            fRead = false;
            if (pObject)
                ;
            else {
                // Read the root block into the common buffer.
                TRC_OBJ(this, "\tReading %d\n", lbn);
                eRc = BPTReq_BlockRead(this, lbn, &pObject);
                if (ERESULT_FAILED(eRc)) {
                    DEBUG_BREAK();
                    return eRc;
                }
                fRead = true;
            }
            
            if (pObject) {
                ObjArray_Push(this->pSrchStk, pObject);
                if (pObject == this->pRoot)
                    ;
                else {
                    obj_Release(pObject);
                }
            }
            else {
                return ERESULT_GENERAL_FAILURE;
            }
#ifdef XYZZZ
            if (fRead)
                obj_Release(pObject);       // objArray has retained it.
#endif

            if ( pObject) {
                if (obj_getType(pObject) == OBJ_IDENT_BPTLEAF) {
                    //FIXME: eRc = BPTLeaf_FindKey(pObject, key, pData);
                    if (ERESULT_FAILED(eRc)) {
                        TRC_OBJ(this, "\tLeaf block, key %d not found\n", key);
                    }
                    else {
                        pVtbl = (void *)obj_getVtbl((OBJ_ID)pObject);
                        //FIXME: this->lastLSN = pVtbl->pGetLBN(pObject);
                        //FIXME: this->lastKey = key;
                        TRC_OBJ(this, "\tLeaf block, key %d found\n", key);
                    }
                    return eRc;
                }
                else if (obj_getType(pObject) == OBJ_IDENT_BPTINDEX) {
                    //FIXME: eRc = BPTIndex_FindKey(pObject, key, &nodeIndex);
                    if (ERESULT_FAILED(eRc)) {
                        TRC_OBJ(this, "\tIndex block, key %d not found\n", key);
                       return eRc;
                    }
                    TRC_OBJ(
                            this,
                            "\tIndex block, key %d found, index=%d\n",
                            key,
                            nodeIndex
                    );
                }
                else {
                    DEBUG_BREAK();
                    return ERESULT_GENERAL_FAILURE;
                }
            }
            
            lbn = nodeIndex;
            pObject = OBJ_NIL;
        }

        // Return to caller.
        TRC_OBJ(this, "\tkey %d not found, returning\n", key);
        return ERESULT_DATA_NOT_FOUND;
    }
    
    
    
    /*!
     This method is called after a block split occurs.  It's job is to further
     propogate the split up the Tree as high as it needs to go.  If a new index
     block is needed, that shows a split of the root and this method handles
     that as well.
     
     The first split should always be in a leaf block.  All splits after that will
     be index block(s).  When a split occurs, the index block which is parent will
     only be new if the root needs to be split.  When the root is split whether it
     is a leaf or index block, a new block will be needed.  The new block's p0
     should be set to the index of the left block and the first node entry should
     be to the lowest key of the right block.
     
     @param     this        Object Pointer
     @param     pLeft       Object Pointer for the lefthand block of the split
     @param     pRight      Object Pointer for the righthand block of the split
     @return    If successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         BPTReq_BlockSplit(
        BPTREQ_DATA     *this,
        OBJ_ID          *pLeft,
        OBJ_ID          *pRight
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        BPTINDEX_DATA   *pIndex = OBJ_NIL;
        OBJ_ID          pObj;
        uint32_t        key = 0;
        uint32_t        index = 0;
        uint32_t        lbn = 0;
        BPT_BLK_VTBL    *pVtblL = NULL;
        BPT_BLK_VTBL    *pVtblR = NULL;

#ifdef NDEBUG
#else
        if (OBJ_NIL == pLeft) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if (OBJ_NIL == pRight) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        pVtblL = (BPT_BLK_VTBL *)obj_getVtbl(pLeft);
        pVtblR = (BPT_BLK_VTBL *)obj_getVtbl(pRight);
        TRC_OBJ(
                this,
                "BPT_BlockSplit Left: type=%d lsn=%d, Right: type=%d lsn=%d\n",
                obj_getType(pLeft),
                pVtblR->pGetLBN(pLeft),
                obj_getType(pRight),
                pVtblR->pGetLBN(pRight)
        );

        if (this->pRoot == pLeft) {
            TRC_OBJ(this, "\tSplitting the root...\n");
            //FIXME: below
#ifdef XYZZY
            eRc =   BPT_BlockRequest(
                                     this,
                                     BPT_REQUEST_NEW_INDEX,
                                     OBJ_NIL,
                                     NULL,
                                     NULL,
                                     &pIndex
                    );
#endif
            if (ERESULT_FAILED(eRc)) {
                DEBUG_BREAK();
                return eRc;
            }
            BPTIndex_setP0(pIndex, pVtblL->pGetLBN(pLeft));
            //FIXME: eRc = pVtblR->pGet(pRight, 1, &key, NULL);
            index = pVtblR->pGetLBN(pRight);
            //FIXME: BPTIndex_Insert(pIndex, key, &index);
            // Note - No split should occur here.
            
            // Write the new block to the file.
            eRc =   RRDS_RecordWrite(
                                     this->pIO,
                                     BPTIndex_getLBN(pIndex),
                                     BPTIndex_getBlock(pIndex)
                    );
            if (ERESULT_FAILED(eRc)) {
                DEBUG_BREAK();
                return eRc;
            }
            
            // Make a new index block the root.
            obj_Release(this->pRoot);
            this->pRoot = pIndex;
            this->pHdr->root = BPTIndex_getLBN(pIndex);
            TRC_OBJ(this, "\tAdded new Root Index Block, %d\n", BPTIndex_getLBN(pIndex));
        } else {
            TRC_OBJ(this, "\tAdding key to the parent index...\n");
            lbn = pVtblL->pGetLBN(pLeft);
            eRc = BPTReq_BlockFindParent(this, lbn, &pObj);
            if (pObj && (OBJ_IDENT_BPTINDEX == obj_getType(pObj)))
                ;
            else {
                // Parent should always be an index block if present.
                DEBUG_BREAK();
                return ERESULT_GENERAL_FAILURE;
            }
            //FIXME: eRc = pVtblR->pGet(pRight, 1, &key, NULL);
            index = pVtblR->pGetLBN(pRight);
            //FIXME: eRc = BPTIndex_Insert(pObj, key, &index);
            TRC_OBJ(
                    this,
                    "\tAdded key %d index %d to the index %d\n",
                    key,
                    index,
                    BPTIndex_getLBN(pObj)
            );
        }
        
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
    int             BPTReq_Compare (
        BPTREQ_DATA     *this,
        BPTREQ_DATA     *pOther
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
#ifdef  BPTREQ_SINGLETON
        if (OBJ_NIL == this) {
            this = BPTReq_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!BPTReq_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!BPTReq_Validate(pOther)) {
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
        BPTReq      *pCopy = BPTReq_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a BPTREQ object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    BPTREQ_DATA *     BPTReq_Copy (
        BPTREQ_DATA       *this
    )
    {
        BPTREQ_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!BPTReq_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef BPTREQ_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = BPTReq_New( );
        if (pOther) {
            eRc = BPTReq_Assign(this, pOther);
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

    void            BPTReq_Dealloc (
        OBJ_ID          objId
    )
    {
        BPTREQ_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!BPTReq_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((BPTREQ_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        BPTReq_setIO(this, OBJ_NIL);
        BPTReq_setPath(this, OBJ_NIL);
        BPTReq_setRoot(this, OBJ_NIL);
        BPTReq_setSrchStk(this, OBJ_NIL);
        BPTReq_setStr(this, OBJ_NIL);

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
        BPTReq      *pDeepCopy = BPTReq_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a BPTREQ object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    BPTREQ_DATA *     BPTReq_DeepCopy (
        BPTREQ_DATA       *this
    )
    {
        BPTREQ_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!BPTReq_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = BPTReq_New( );
        if (pOther) {
            eRc = BPTReq_Assign(this, pOther);
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
    ERESULT         BPTReq_Disable (
        BPTREQ_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  BPTREQ_SINGLETON
        if (OBJ_NIL == this) {
            this = BPTReq_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!BPTReq_Validate(this)) {
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
    ERESULT         BPTReq_Enable (
        BPTREQ_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  BPTREQ_SINGLETON
        if (OBJ_NIL == this) {
            this = BPTReq_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!BPTReq_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        TRC_OBJ(this,"\tEnabled?: %s:\n", obj_Enable(this) ? "true" : "false");
#ifdef   BPTREQ_MSGS
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

    BPTREQ_DATA *   BPTReq_Init (
        BPTREQ_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(BPTREQ_DATA);
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

#ifdef  BPTREQ_SUPER_DEFINED
        this = (OBJ_ID)obj_Init((OBJ_DATA *)this);   // Needed for Inheritance
#else
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_BPTREQ);
#endif
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&BPTReq_Vtbl);
#ifdef  BPTREQ_JSON_SUPPORT
        JsonIn_RegisterClass(BPTReq_Class());
#endif
        
        this->pSrchStk = ObjArray_New( );
        if (OBJ_NIL == this->pSrchStk) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

#ifdef NDEBUG
#else
        if (!BPTReq_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "BPTReq::sizeof(BPTREQ_DATA) = %lu\n", 
                sizeof(BPTREQ_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(BPTREQ_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                      I s  E n a b l e d
    //---------------------------------------------------------------
    
    bool                BPTReq_IsEnabled (
        BPTREQ_DATA       *this
    )
    {
        //ERESULT         eRc;
        bool            fRc = false;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  BPTREQ_SINGLETON
        if (OBJ_NIL == this) {
            this = BPTReq_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!BPTReq_Validate(this)) {
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
        void        *pMethod = BPTReq_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_DATA, an object's data is returned
                        if it fits in a "void *".
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "BPTReq", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          BPTReq_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        BPTREQ_DATA     *this = objId;
        const
        char            *pStrA = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!BPTReq_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(BPTREQ_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)BPTReq_Class();
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
                            return BPTReq_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStrA) == 0) {
                            return BPTReq_Enable;
                        }
                        break;

                    case 'P':
#ifdef  BPTREQ_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStrA) == 0) {
                            return BPTReq_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStrA) == 0) {
                            return BPTReq_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStrA) == 0) {
                            return BPTReq_ToDebugString;
                        }
#ifdef  BPTREQ_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStrA) == 0) {
                            return BPTReq_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStrA) == 0) {
                            return BPTReq_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == BPTReq_ToDebugString)
                    return "ToDebugString";
#ifdef  BPTREQ_JSON_SUPPORT
                if (pData == BPTReq_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
#ifdef XYZZY
    /*!
     @warning   This method must always conform to P_ERESULT_EXIT4.
     */
    ERESULT         BPT32_BlockRequest(
        BPT32_DATA      *this,
        uint32_t        request,
        OBJ_ID          pObj,
        void            *pParm1,
        void            *pParm2,
        void            *pParm3
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        BPT32INDEX_DATA *pIndex = OBJ_NIL;
        BPT32LEAF_DATA  *pLeaf = OBJ_NIL;
        LBN32_T         lbn = 0;                    // Logical Block Number
        void            *pBlock = NULL;
        BPT32_BLK_VTBL  *pVtbl = NULL;

#ifdef NDEBUG
#else
        if (!BPT32_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
        TRC_OBJ(this, "BPT32_BlockRequest req=%d\n", request);
#endif
        
        switch (request) {
                
            case BPT32_REQUEST_NEW_INDEX:
                if (NULL == pParm3) {
                    DEBUG_BREAK();
                    return ERESULT_INVALID_PARAMETER;
                }
                lbn = ++this->pHdr->cRecords;
                TRC_OBJ(this, "\tNew Index Block  lsn: %d\n", lbn);
                pIndex =    BPT32Index_NewWithSizes(
                                             this->blockSize,
                                             this->dataSize,
                                             lbn,
                                             true,
                                             this
                            );
                if (OBJ_NIL == pIndex) {
                    DEBUG_BREAK();
                    --this->pHdr->cRecords;
                    return ERESULT_OUT_OF_MEMORY;
                }
                TRC_OBJ(this, "\t\tAddress: %p\n", pIndex);
#ifdef NDEBUG
#else
                if (obj_Trace(this))
                    obj_TraceSet(pIndex, true);
#endif
                eRc =   RRDS_RecordWrite(
                                         this->pIO,
                                         BPT32Index_getLBN(pIndex),
                                         BPT32Index_getBlock(pIndex)
                        );
                if (pParm3)
                    *((void **)pParm3) = pIndex;
                else
                    obj_Release(pIndex);
                pIndex = NULL;
                break;
                
            case BPT32_REQUEST_NEW_LEAF:
                if (NULL == pParm3) {
                    DEBUG_BREAK();
                    return ERESULT_INVALID_PARAMETER;
                }
                lbn = ++this->pHdr->cRecords;
                TRC_OBJ(this, "\tNew Leaf Block  lsn: %d\n", lbn);
                pLeaf = BPT32Leaf_NewWithSizes(
                                             this->blockSize,
                                             this->dataSize,
                                             lbn,
                                             true,
                                             this
                        );
                if (OBJ_NIL == pLeaf) {
                    DEBUG_BREAK();
                    --this->pHdr->cRecords;
                    return ERESULT_OUT_OF_MEMORY;
                }
                TRC_OBJ(this, "\t\tAddress: %p\n", pLeaf);
#ifdef NDEBUG
#else
                if (obj_Trace(this))
                    obj_TraceSet(pLeaf, true);
#endif
                eRc =   RRDS_RecordWrite(
                                         this->pIO,
                                         BPT32Leaf_getLBN(pLeaf),
                                         BPT32Leaf_getBlock(pLeaf)
                        );
                if (pParm3)
                    *((void **)pParm3) = pLeaf;
                else
                    obj_Release(pLeaf);
                pLeaf = NULL;
                break;
                
            case BPT32_REQUEST_PARENT:
                if (NULL == pObj) {
                    DEBUG_BREAK();
                    return ERESULT_INVALID_PARAMETER;
                }
                pVtbl = (BPT32_BLK_VTBL *)obj_getVtbl(pObj);
                lbn = pVtbl->pGetLBN(pObj);
                TRC_OBJ(this, "\tFind Parent for %d...\n", lbn);
                eRc = BPT32_BlockFindParent(this, lbn, pParm3);
                break;
                
            case BPT32_REQUEST_READ:
                if (NULL == pObj) {
                    DEBUG_BREAK();
                    return ERESULT_INVALID_PARAMETER;
                }
                pVtbl = (BPT32_BLK_VTBL *)obj_getVtbl(pObj);
                lbn = pVtbl->pGetLBN(pObj);
                TRC_OBJ(this, "\tRead data for block %d...\n", lbn);
                pBlock = pVtbl->pGetBlock(pObj);
#ifdef XYZZY
                if (NULL == pBlock) {
                    eRc = pVtbl->pSetup(
                                        pObj,
                                        this->blockSize,
                                        this->dataSize,
                                        lbn,
                                        true
                            );
                    pVtbl->pSetManager(pObj, this);
                    pBlock = pVtbl->pGetBlock(pObj);
                }
#endif
                if (lbn && pBlock) {
                    eRc =   RRDS_RecordRead(
                                            this->pIO,
                                            lbn,
                                            pBlock
                            );
                }
                else
                    eRc = ERESULT_GENERAL_FAILURE;
#ifdef NDEBUG
#else
                if (obj_Trace(this) && !ERESULT_FAILED(eRc)) {
                    ASTR_DATA       *pStr = OBJ_NIL;
                    if (OBJ_IDENT_BPT32INDEX == obj_getType(pObj)) {
                        eRc = BPT32Index_Verify(pObj);
                        if (ERESULT_FAILED(eRc)) {
                            pStr = BPT32Index_ToDebugString(pObj, 4);
                        }
                    }
                    if (OBJ_IDENT_BPT32LEAF == obj_getType(pObj)) {
                        eRc = BPT32Leaf_Verify(pObj);
                        if (ERESULT_FAILED(eRc)) {
                            pStr = BPT32Leaf_ToDebugString(pObj, 4);
                        }
                    }
                   if (ERESULT_FAILED(eRc)) {
                       TRC_OBJ(this, "\tBlock Verify Error!\n");
                       if (pStr) {
                           fprintf(stderr, "%s\n", AStr_getData(pStr));
                           obj_Release(pStr);
                       }
                        DEBUG_BREAK();
                        obj_Release(pObj);
                        return eRc;
                    }
                }
#endif
                break;
                
            case BPT32_REQUEST_SPLIT:
                TRC_OBJ(this, "\tSplit Block...\n");
                eRc = BPT32_BlockSplit(this, (OBJ_ID)pObj, pParm1);
                break;
                
            case BPT32_REQUEST_SET_TAIL:
                TRC_OBJ(this, "\tSet new data tail...\n");
                if (OBJ_IDENT_BPT32LEAF == obj_getType(pObj)) {
                    this->pHdr->dataTail = BPT32Leaf_getLBN((BPT32LEAF_DATA *)pObj);
                    eRc = ERESULT_SUCCESS;
                }
                else
                    eRc = ERESULT_GENERAL_FAILURE;
                break;
                
            case BPT32_REQUEST_WRITE:
                if (NULL == pObj) {
                    DEBUG_BREAK();
                    return ERESULT_INVALID_PARAMETER;
                }
                pVtbl = (BPT32_BLK_VTBL *)obj_getVtbl(pObj);
                lbn = pVtbl->pGetLBN(pObj);
                TRC_OBJ(this, "\tWrite data for block %d...\n", lbn);
                pBlock = pVtbl->pGetBlock(pObj);
                if (lbn && pBlock) {
                    eRc =   RRDS_RecordWrite(
                                             this->pIO,
                                             lbn,
                                             pBlock
                            );
                }
                else
                    eRc = ERESULT_GENERAL_FAILURE;
                break;
                
            default:
                DEBUG_BREAK();
                return ERESULT_INVALID_REQUEST;
                break;
        }
        
        return eRc;
    }
    
    
    
#endif
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = BPTReq_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     BPTReq_ToDebugString (
        BPTREQ_DATA      *this,
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
        if (!BPTReq_Validate(this)) {
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
                    BPTReq_getSize(this),
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
    bool            BPTReq_Validate (
        BPTREQ_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_BPTREQ))
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


        if (!(obj_getSize(this) >= sizeof(BPTREQ_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef  __cplusplus
}
#endif


