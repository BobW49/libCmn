// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//      16-bit Variable Sized Tuples (Tuple16) Object Support
//****************************************************************


/*
 * File:   Tuple16.c
 *  Generated 01/28/2023 10:39:21
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
#include        <Tuple16_internal.h>
#include        <JsonIn.h>
#include        <Misc.h>
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

#include        <Tuple16_Type_tables.c>

 
    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/



    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#include        <Tuple16_Type_routines.c>
    

    ERESULT         Tuple16_SegmentAppend (
        TUPLE16_DATA    *this,
        TUPLE16_SEGMENT *pSeg
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        uint16_t        sizeNew;
        TUPLE16_SEGMENT_BASE
                        *pNew = this->pTuple;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);

        sizeNew = this->pTuple->segLen + pSeg->segLen;
        if (sizeNew > this->pTuple->alloc) {
            pNew = mem_Malloc(sizeNew);
            if (NULL == pNew) {
                eRc = ERESULT_OUT_OF_MEMORY;
            }
            memmove(pNew, this->pTuple, this->pTuple->segLen);
            pNew->alloc = sizeNew;
            mem_Free(this->pTuple);
            this->pTuple = pNew;
        }
        memmove(((uint8_t *)pNew)+pNew->segLen, pSeg, pSeg->segLen);
        pNew->segLen = sizeNew;
        pNew->cTuples++;

        // Return to caller.
        return eRc;
    }



    ERESULT         Tuple16_SegmentDelete (
        TUPLE16_DATA    *this,
        int             index
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        uint16_t        offset;
        TUPLE16_SEGMENT
                        *pSegWrk = NULL;
        uint16_t        segLen = 0;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
        if (index >= this->pTuple->cTuples)
            return ERESULT_DATA_TOO_BIG;

        offset = Tuple16_SegmentOffset(this, index);
        pSegWrk = (TUPLE16_SEGMENT *)(((uint8_t*)this->pTuple) + offset);
        segLen = pSegWrk->segLen;
        
        if ((offset + segLen) < this->pTuple->segLen) {
            memmove(
                    offsetPtr(this->pTuple, offset),
                    offsetPtr(this->pTuple, (offset + pSegWrk->segLen)),
                    (this->pTuple->segLen - offset - segLen)
            );
        }
        this->pTuple->segLen -= segLen;
        this->pTuple->cTuples--;

        // Return to caller.
        return eRc;
    }



    ERESULT         Tuple16_SegmentInsert (
        TUPLE16_DATA    *this,
        int             index,
        TUPLE16_SEGMENT *pSeg
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        uint16_t        sizeNew;
        int             offset;
        TUPLE16_SEGMENT_BASE
                        *pNew = NULL;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);

        if (index >= this->pTuple->cTuples) {
            eRc = Tuple16_SegmentAppend(this, pSeg);
            return eRc;
        }
        
        offset = Tuple16_SegmentOffset(this, index);
        sizeNew = this->pTuple->segLen + pSeg->segLen;
        pNew = mem_Malloc(sizeNew);
        if (pNew) {
            memmove(pNew, this->pTuple, offset);
            memmove(((uint8_t *)pNew)+offset, pSeg, pSeg->segLen);
            if (offset < this->pTuple->segLen) {
                memmove(
                        ((uint8_t *)pNew)+offset+pSeg->segLen,
                        ((uint8_t *)this->pTuple)+offset,
                        this->pTuple->segLen - offset
                );
            }
            pNew->alloc = sizeNew;
            pNew->segLen = sizeNew;
            pNew->cTuples++;
            mem_Free(this->pTuple);
            this->pTuple = pNew;
        } else {
            eRc = ERESULT_OUT_OF_MEMORY;
        }

        // Return to caller.
        return eRc;
    }



    int             Tuple16_SegmentOffset (
        TUPLE16_DATA    *this,
        int             index
    )
    {
        //ERESULT         eRc = ERESULT_SUCCESS;
        uint16_t        offset = sizeof(TUPLE16_SEGMENT_BASE);
        TUPLE16_SEGMENT
                        *pSegWrk = NULL;
        int             i;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
        if (NULL == this->pTuple) {
            return -1;
        }
        if (index >= this->pTuple->cTuples)
            return -1;

        // Find offset of deletion point.
        pSegWrk = (TUPLE16_SEGMENT *)offsetPtr(this->pTuple, sizeof(TUPLE16_SEGMENT_BASE));
        for (i=0; (i < index) && (i < this->pTuple->cTuples); i++) {
            offset += pSegWrk->segLen;
            pSegWrk = (TUPLE16_SEGMENT *)(((uint8_t*)pSegWrk) + pSegWrk->segLen);
        }
        
        // Return to caller.
        return offset;
    }



    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    TUPLE16_DATA *  Tuple16_Alloc (
        void
    )
    {
        TUPLE16_DATA    *this;
        uint32_t        cbSize = sizeof(TUPLE16_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    TUPLE16_DATA *  Tuple16_New (
        void
    )
    {
        TUPLE16_DATA    *this;
        
        this = Tuple16_Alloc( );
        if (this) {
            this = Tuple16_Init(this);
        } 
        return this;
    }


    TUPLE16_DATA *  Tuple16_NewBase (
        uint16_t        op
    )
    {
        TUPLE16_DATA    *this;
        
        this = Tuple16_New( );
        if (this) {
            this->pTuple = mem_Calloc(1, sizeof(TUPLE16_SEGMENT_BASE));
            if (this->pTuple) {
                this->pTuple->alloc = sizeof(TUPLE16_SEGMENT_BASE);
                this->pTuple->segLen = sizeof(TUPLE16_SEGMENT_BASE);
                this->pTuple->type = op;
                this->pTuple->op = op;
            }
        }
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                      M e s s a g e s
    //---------------------------------------------------------------

#ifdef   TUPLE16_MSGS
    bool            Tuple16_setMsgs (
        TUPLE16_DATA    *this,
        void            (*pMsgInfo)(OBJ_ID, const char *, ...),
        void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...),
        OBJ_ID          pObj
    )
    {
#ifdef NDEBUG
#else
        if (!Tuple16_Validate(this)) {
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
    
    uint16_t        Tuple16_getPriority (
        TUPLE16_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Tuple16_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            Tuple16_setPriority (
        TUPLE16_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!Tuple16_Validate(this)) {
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
    
    uint32_t        Tuple16_getSize (
        TUPLE16_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!Tuple16_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
#ifdef  TUPLE16_SUPER_DEFINED
    OBJ_DATA *  Tuple16_getSuper (
        TUPLE16_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Tuple16_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return (OBJ_DATA *)this;
    }
#else
    OBJ_DATA *  Tuple16_getSuper (
        TUPLE16_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Tuple16_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return (OBJ_DATA *)this;
    }
#endif

    
    OBJ_IUNKNOWN *  Tuple16_getSuperVtbl (
        TUPLE16_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Tuple16_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    //---------------------------------------------------------------
    //                          T u p l e
    //---------------------------------------------------------------
    
    TUPLE16_SEGMENT_BASE *
                    Tuple16_getTuple (
        TUPLE16_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Tuple16_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pTuple;
    }
    
    
    bool            Tuple16_setTuple (
        TUPLE16_DATA    *this,
        TUPLE16_SEGMENT_BASE
                        *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Tuple16_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->pTuple = pValue;
        
        return true;
    }
    
    
    
    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                      A p p e n d
    //---------------------------------------------------------------

    ERESULT         Tuple16_AppendDouble (
        TUPLE16_DATA    *this,
        uint8_t         op,
        double          data
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        TUPLE16_DOUBLE  seg = {0};

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  TUPLE16_SINGLETON
        if (OBJ_NIL == this) {
            this = Tuple16_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Tuple16_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == this->pTuple) {
            DEBUG_BREAK();
            return ERESULT_DATA_MISSING;
        }
#endif
        if (0 == op) {
            op = TUPLE16_TYPE_DOUBLE;
        }

        seg.segLen = sizeof(TUPLE16_DOUBLE);
        seg.type = TUPLE16_TYPE_DOUBLE;
        seg.op = op;
        seg.data = data;
        eRc = Tuple16_SegmentAppend(this, (TUPLE16_SEGMENT *)&seg);
        
        // Return to caller.
        return eRc;
    }


    ERESULT         Tuple16_AppendInteger8 (
        TUPLE16_DATA    *this,
        uint8_t         op,
        int8_t          data
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        TUPLE16_INTEGER8
                        seg = {0};

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  TUPLE16_SINGLETON
        if (OBJ_NIL == this) {
            this = Tuple16_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Tuple16_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == this->pTuple) {
            DEBUG_BREAK();
            return ERESULT_DATA_MISSING;
        }
#endif
        if (0 == op) {
            op = TUPLE16_TYPE_INT8;
        }

        seg.segLen = sizeof(TUPLE16_INTEGER8);
        seg.type = TUPLE16_TYPE_INT8;
        seg.op = op;
        seg.data = data;
        eRc = Tuple16_SegmentAppend(this, (TUPLE16_SEGMENT *)&seg);
        
        // Return to caller.
        return eRc;
    }


    ERESULT         Tuple16_AppendInteger16 (
        TUPLE16_DATA    *this,
        uint8_t         op,
        int16_t         data
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        TUPLE16_INTEGER16
                        seg = {0};

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  TUPLE16_SINGLETON
        if (OBJ_NIL == this) {
            this = Tuple16_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Tuple16_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == this->pTuple) {
            DEBUG_BREAK();
            return ERESULT_DATA_MISSING;
        }
#endif
        if (0 == op) {
            op = TUPLE16_TYPE_INT16;
        }

        seg.segLen = sizeof(TUPLE16_INTEGER16);
        seg.type = TUPLE16_TYPE_INT16;
        seg.op = op;
        seg.data = data;
        eRc = Tuple16_SegmentAppend(this, (TUPLE16_SEGMENT *)&seg);
        
        // Return to caller.
        return eRc;
    }


    ERESULT         Tuple16_AppendInteger32 (
        TUPLE16_DATA    *this,
        uint8_t         op,
        int32_t         data
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        TUPLE16_INTEGER32
                        seg = {0};

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  TUPLE16_SINGLETON
        if (OBJ_NIL == this) {
            this = Tuple16_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Tuple16_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == this->pTuple) {
            DEBUG_BREAK();
            return ERESULT_DATA_MISSING;
        }
#endif
        if (0 == op) {
            op = TUPLE16_TYPE_INT32;
        }

        seg.segLen = sizeof(TUPLE16_INTEGER32);
        seg.type = TUPLE16_TYPE_INT32;
        seg.op = op;
        seg.data = data;
        eRc = Tuple16_SegmentAppend(this, (TUPLE16_SEGMENT *)&seg);
        
        // Return to caller.
        return eRc;
    }


    ERESULT         Tuple16_AppendInteger64 (
        TUPLE16_DATA    *this,
        uint8_t         op,
        int64_t         data
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        TUPLE16_INTEGER64
                        seg = {0};

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  TUPLE16_SINGLETON
        if (OBJ_NIL == this) {
            this = Tuple16_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Tuple16_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == this->pTuple) {
            DEBUG_BREAK();
            return ERESULT_DATA_MISSING;
        }
#endif
        if (0 == op) {
            op = TUPLE16_TYPE_INT64;
        }

        seg.segLen = sizeof(TUPLE16_INTEGER64);
        seg.type = TUPLE16_TYPE_INT64;
        seg.op = op;
        seg.data = data;
        eRc = Tuple16_SegmentAppend(this, (TUPLE16_SEGMENT *)&seg);
        
        // Return to caller.
        return eRc;
    }


    ERESULT         Tuple16_AppendObject (
        TUPLE16_DATA    *this,
        uint8_t         op,
        OBJ_ID          pData
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        TUPLE16_OBJECT  seg = {0};

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  TUPLE16_SINGLETON
        if (OBJ_NIL == this) {
            this = Tuple16_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Tuple16_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == this->pTuple) {
            DEBUG_BREAK();
            return ERESULT_DATA_MISSING;
        }
#endif
        if (0 == op) {
            op = TUPLE16_TYPE_OBJECT;
        }

        seg.segLen = sizeof(TUPLE16_OBJECT);
        seg.type = TUPLE16_TYPE_OBJECT;
        seg.op = op;
        seg.pData = pData;
        eRc = Tuple16_SegmentAppend(this, (TUPLE16_SEGMENT *)&seg);
        
        // Return to caller.
        return eRc;
    }


    ERESULT         Tuple16_AppendOpcode (
        TUPLE16_DATA    *this,
        uint8_t         op,
        OPCODE_DATA     *pData
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        TUPLE16_OPCODE  seg = {0};

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  TUPLE16_SINGLETON
        if (OBJ_NIL == this) {
            this = Tuple16_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Tuple16_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == this->pTuple) {
            DEBUG_BREAK();
            return ERESULT_DATA_MISSING;
        }
#endif
        if (0 == op) {
            op = TUPLE16_TYPE_OPCODE;
        }

        seg.segLen = sizeof(TUPLE16_OPCODE);
        seg.type = TUPLE16_TYPE_OPCODE;
        seg.op = op;
        seg.pData = pData;
        eRc = Tuple16_SegmentAppend(this, (TUPLE16_SEGMENT *)&seg);
        
        // Return to caller.
        return eRc;
    }


    ERESULT         Tuple16_AppendPointer (
        TUPLE16_DATA    *this,
        uint8_t         op,
        void            *pData
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        TUPLE16_POINTER seg = {0};

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  TUPLE16_SINGLETON
        if (OBJ_NIL == this) {
            this = Tuple16_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Tuple16_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == this->pTuple) {
            DEBUG_BREAK();
            return ERESULT_DATA_MISSING;
        }
#endif
        if (0 == op) {
            op = TUPLE16_TYPE_PTR;
        }

        seg.segLen = sizeof(TUPLE16_POINTER);
        seg.type = TUPLE16_TYPE_PTR;
        seg.op = op;
        seg.pData = pData;
        eRc = Tuple16_SegmentAppend(this, (TUPLE16_SEGMENT *)&seg);
        
        // Return to caller.
        return eRc;
    }


    ERESULT         Tuple16_AppendSymbol (
        TUPLE16_DATA    *this,
        uint8_t         op,
        SYM_DATA        *pData
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        TUPLE16_SYMBOL  seg = {0};

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  TUPLE16_SINGLETON
        if (OBJ_NIL == this) {
            this = Tuple16_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Tuple16_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == this->pTuple) {
            DEBUG_BREAK();
            return ERESULT_DATA_MISSING;
        }
#endif
        if (0 == op) {
            op = TUPLE16_TYPE_SYMBOL;
        }

        seg.segLen = sizeof(TUPLE16_SYMBOL);
        seg.type = TUPLE16_TYPE_SYMBOL;
        seg.op = op;
        seg.pData = pData;
        eRc = Tuple16_SegmentAppend(this, (TUPLE16_SEGMENT *)&seg);
        
        // Return to caller.
        return eRc;
    }


    ERESULT         Tuple16_AppendToken (
        TUPLE16_DATA    *this,
        uint8_t         op,
        TOKEN_FIELDS    *pData
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        TUPLE16_TOKEN   seg = {0};

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  TUPLE16_SINGLETON
        if (OBJ_NIL == this) {
            this = Tuple16_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Tuple16_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == this->pTuple) {
            DEBUG_BREAK();
            return ERESULT_DATA_MISSING;
        }
#endif
        if (0 == op) {
            op = TUPLE16_TYPE_TOKEN;
        }

        seg.segLen = sizeof(TUPLE16_TOKEN);
        seg.type = TUPLE16_TYPE_TOKEN;
        seg.op = op;
        memmove(&seg.data, pData, sizeof(TOKEN_FIELDS));
        eRc = Tuple16_SegmentAppend(this, (TUPLE16_SEGMENT *)&seg);
        
        // Return to caller.
        return eRc;
    }



    ERESULT         Tuple16_AppendUTF8 (
        TUPLE16_DATA    *this,
        uint8_t         op,
        uint16_t        len,
        uint8_t         *pData
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        int             segLen = sizeof(TUPLE16_UTF8) + len;
        TUPLE16_UTF8    *pSeg;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  TUPLE16_SINGLETON
        if (OBJ_NIL == this) {
            this = Tuple16_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Tuple16_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == this->pTuple) {
            DEBUG_BREAK();
            return ERESULT_DATA_MISSING;
        }
#endif
        if (0 == op) {
            op = TUPLE16_TYPE_UTF8;
        }
        
        pSeg = mem_Malloc(segLen);
        if (NULL == pSeg) {
            DEBUG_BREAK();
            return ERESULT_OUT_OF_MEMORY;
        }

        pSeg->segLen = segLen;
        pSeg->type = TUPLE16_TYPE_UTF8;
        pSeg->op = op;
        pSeg->dataLen = len;
        if (len) {
            memmove(pSeg->data, pData, len);
        }
        eRc = Tuple16_SegmentAppend(this, (TUPLE16_SEGMENT *)pSeg);
        
        mem_Free(pSeg);
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before 
     a copy of the object is performed.
     Example:
     @code 
        ERESULT eRc = Tuple16_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another TUPLE16 object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         Tuple16_Assign (
        TUPLE16_DATA       *this,
        TUPLE16_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!Tuple16_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Tuple16_Validate(pOther)) {
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
    int             Tuple16_Compare (
        TUPLE16_DATA     *this,
        TUPLE16_DATA     *pOther
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
#ifdef  TUPLE16_SINGLETON
        if (OBJ_NIL == this) {
            this = Tuple16_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Tuple16_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!Tuple16_Validate(pOther)) {
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
        Tuple16      *pCopy = Tuple16_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a TUPLE16 object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    TUPLE16_DATA *     Tuple16_Copy (
        TUPLE16_DATA       *this
    )
    {
        TUPLE16_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!Tuple16_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef TUPLE16_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = Tuple16_New( );
        if (pOther) {
            eRc = Tuple16_Assign(this, pOther);
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

    void            Tuple16_Dealloc (
        OBJ_ID          objId
    )
    {
        TUPLE16_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!Tuple16_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((TUPLE16_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        if (this->pTuple) {
            mem_Free(this->pTuple);
            this->pTuple = NULL;
        }

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
        Tuple16      *pDeepCopy = Tuple16_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a TUPLE16 object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    TUPLE16_DATA *     Tuple16_DeepCopy (
        TUPLE16_DATA       *this
    )
    {
        TUPLE16_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!Tuple16_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = Tuple16_New( );
        if (pOther) {
            eRc = Tuple16_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                      D e l e t e
    //---------------------------------------------------------------

    ERESULT         Tuple16_DeleteSegment(
        TUPLE16_DATA    *this,
        uint8_t         index
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  TUPLE16_SINGLETON
        if (OBJ_NIL == this) {
            this = Tuple16_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Tuple16_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == this->pTuple) {
            DEBUG_BREAK();
            return ERESULT_DATA_MISSING;
        }
        if ((0 == index) || (index > this->pTuple->cTuples)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        eRc = Tuple16_SegmentDelete(this, (index - 1));

        // Return to caller.
        return eRc;
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
    ERESULT         Tuple16_Disable (
        TUPLE16_DATA    *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  TUPLE16_SINGLETON
        if (OBJ_NIL == this) {
            this = Tuple16_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Tuple16_Validate(this)) {
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
    ERESULT         Tuple16_Enable (
        TUPLE16_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  TUPLE16_SINGLETON
        if (OBJ_NIL == this) {
            this = Tuple16_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Tuple16_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        TRC_OBJ(this,"\tEnabled?: %s:\n", obj_Enable(this) ? "true" : "false");
#ifdef   TUPLE16_MSGS
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

    TUPLE16_DATA *   Tuple16_Init (
        TUPLE16_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(TUPLE16_DATA);
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

#ifdef  TUPLE16_SUPER_DEFINED
        this = (OBJ_ID)obj_Init((OBJ_DATA *)this);   // Needed for Inheritance
#else
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_TUPLE16);
#endif
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&Tuple16_Vtbl);
#ifdef  TUPLE16_JSON_SUPPORT
        JsonIn_RegisterClass(Tuple16_Class());
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
        if (!Tuple16_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "Tuple16::sizeof(TUPLE16_DATA) = %lu\n", 
                sizeof(TUPLE16_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(TUPLE16_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                      I n s e r t
    //---------------------------------------------------------------

    ERESULT         Tuple16_InsertDouble (
        TUPLE16_DATA    *this,
        uint8_t         index,
        uint8_t         op,
        double          data
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        TUPLE16_DOUBLE  seg = {0};

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  TUPLE16_SINGLETON
        if (OBJ_NIL == this) {
            this = Tuple16_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Tuple16_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == this->pTuple) {
            DEBUG_BREAK();
            return ERESULT_DATA_MISSING;
        }
        if ((0 == index) || (index > this->pTuple->cTuples)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        if (0 == op) {
            op = TUPLE16_TYPE_DOUBLE;
        }

        seg.segLen = sizeof(TUPLE16_DOUBLE);
        seg.type = TUPLE16_TYPE_DOUBLE;
        seg.op = op;
        seg.data = data;
        eRc = Tuple16_SegmentInsert(this, index, (TUPLE16_SEGMENT *)&seg);
        
        // Return to caller.
        return eRc;
    }


    ERESULT         Tuple16_InsertInteger8 (
        TUPLE16_DATA    *this,
        uint8_t         index,
        uint8_t         op,
        int8_t          data
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        TUPLE16_INTEGER8
                        seg = {0};

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  TUPLE16_SINGLETON
        if (OBJ_NIL == this) {
            this = Tuple16_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Tuple16_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == this->pTuple) {
            DEBUG_BREAK();
            return ERESULT_DATA_MISSING;
        }
        if ((0 == (0 == this->pTuple->cTuples)) || (index > this->pTuple->cTuples)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        if (0 == op) {
            op = TUPLE16_TYPE_INT8;
        }

        seg.segLen = sizeof(TUPLE16_INTEGER8);
        seg.type = TUPLE16_TYPE_INT8;
        seg.op = op;
        seg.data = data;
        eRc = Tuple16_SegmentInsert(this, index, (TUPLE16_SEGMENT *)&seg);

        // Return to caller.
        return eRc;
    }


    ERESULT         Tuple16_InsertInteger16 (
        TUPLE16_DATA    *this,
        uint8_t         index,
        uint8_t         op,
        int16_t         data
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        TUPLE16_INTEGER16
                        seg = {0};

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  TUPLE16_SINGLETON
        if (OBJ_NIL == this) {
            this = Tuple16_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Tuple16_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == this->pTuple) {
            DEBUG_BREAK();
            return ERESULT_DATA_MISSING;
        }
        if ((0 == this->pTuple->cTuples) || (index > this->pTuple->cTuples)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        if (0 == op) {
            op = TUPLE16_TYPE_INT16;
        }

        seg.segLen = sizeof(TUPLE16_INTEGER16);
        seg.type = TUPLE16_TYPE_INT16;
        seg.op = op;
        seg.data = data;
        eRc = Tuple16_SegmentInsert(this, index, (TUPLE16_SEGMENT *)&seg);

        // Return to caller.
        return eRc;
    }


    ERESULT         Tuple16_InsertInteger32 (
        TUPLE16_DATA    *this,
        uint8_t         index,
        uint8_t         op,
        int32_t         data
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        TUPLE16_INTEGER32
                        seg = {0};

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  TUPLE16_SINGLETON
        if (OBJ_NIL == this) {
            this = Tuple16_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Tuple16_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == this->pTuple) {
            DEBUG_BREAK();
            return ERESULT_DATA_MISSING;
        }
        if ((0 == (0 == this->pTuple->cTuples)) || (index > this->pTuple->cTuples)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        if (0 == op) {
            op = TUPLE16_TYPE_INT32;
        }

        seg.segLen = sizeof(TUPLE16_INTEGER32);
        seg.type = TUPLE16_TYPE_INT32;
        seg.op = op;
        seg.data = data;
        eRc = Tuple16_SegmentInsert(this, index, (TUPLE16_SEGMENT *)&seg);

        // Return to caller.
        return eRc;
    }


    ERESULT         Tuple16_InsertInteger64 (
        TUPLE16_DATA    *this,
        uint8_t         index,
        uint8_t         op,
        int64_t         data
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        TUPLE16_INTEGER64
                        seg = {0};

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  TUPLE16_SINGLETON
        if (OBJ_NIL == this) {
            this = Tuple16_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Tuple16_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == this->pTuple) {
            DEBUG_BREAK();
            return ERESULT_DATA_MISSING;
        }
        if ((0 == (0 == this->pTuple->cTuples)) || (index > this->pTuple->cTuples)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        if (0 == op) {
            op = TUPLE16_TYPE_INT64;
        }

        seg.segLen = sizeof(TUPLE16_INTEGER64);
        seg.type = TUPLE16_TYPE_INT64;
        seg.op = op;
        seg.data = data;
        eRc = Tuple16_SegmentInsert(this, index, (TUPLE16_SEGMENT *)&seg);

        // Return to caller.
        return eRc;
    }


    ERESULT         Tuple16_InsertObject (
        TUPLE16_DATA    *this,
        uint8_t         index,
        uint8_t         op,
        OBJ_ID          pData
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        TUPLE16_OBJECT  seg = {0};

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  TUPLE16_SINGLETON
        if (OBJ_NIL == this) {
            this = Tuple16_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Tuple16_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == this->pTuple) {
            DEBUG_BREAK();
            return ERESULT_DATA_MISSING;
        }
#endif
        if (0 == op) {
            op = TUPLE16_TYPE_OBJECT;
        }

        seg.segLen = sizeof(TUPLE16_OBJECT);
        seg.type = TUPLE16_TYPE_OBJECT;
        seg.op = op;
        seg.pData = pData;
        eRc = Tuple16_SegmentInsert(this, index, (TUPLE16_SEGMENT *)&seg);

        // Return to caller.
        return eRc;
    }


    ERESULT         Tuple16_InsertOpcode (
        TUPLE16_DATA    *this,
        uint8_t         index,
        uint8_t         op,
        OPCODE_DATA     *pData
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        TUPLE16_OPCODE  seg = {0};

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  TUPLE16_SINGLETON
        if (OBJ_NIL == this) {
            this = Tuple16_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Tuple16_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == this->pTuple) {
            DEBUG_BREAK();
            return ERESULT_DATA_MISSING;
        }
#endif
        if (0 == op) {
            op = TUPLE16_TYPE_OPCODE;
        }

        seg.segLen = sizeof(TUPLE16_OPCODE);
        seg.type = TUPLE16_TYPE_OPCODE;
        seg.op = op;
        seg.pData = pData;
        eRc = Tuple16_SegmentInsert(this, index, (TUPLE16_SEGMENT *)&seg);

        // Return to caller.
        return eRc;
    }


    ERESULT         Tuple16_InsertPointer (
        TUPLE16_DATA    *this,
        uint8_t         index,
        uint8_t         op,
        void            *pData
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        TUPLE16_POINTER seg = {0};

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  TUPLE16_SINGLETON
        if (OBJ_NIL == this) {
            this = Tuple16_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Tuple16_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == this->pTuple) {
            DEBUG_BREAK();
            return ERESULT_DATA_MISSING;
        }
        if ((0 == (0 == this->pTuple->cTuples)) || (index > this->pTuple->cTuples)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        if (0 == op) {
            op = TUPLE16_TYPE_PTR;
        }

        seg.segLen = sizeof(TUPLE16_POINTER);
        seg.type = TUPLE16_TYPE_PTR;
        seg.op = op;
        seg.pData = pData;
        eRc = Tuple16_SegmentInsert(this, index, (TUPLE16_SEGMENT *)&seg);

        // Return to caller.
        return eRc;
    }


    ERESULT         Tuple16_InsertSymbol (
        TUPLE16_DATA    *this,
        uint8_t         index,
        uint8_t         op,
        SYM_DATA        *pData
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        TUPLE16_SYMBOL  seg = {0};

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  TUPLE16_SINGLETON
        if (OBJ_NIL == this) {
            this = Tuple16_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Tuple16_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == this->pTuple) {
            DEBUG_BREAK();
            return ERESULT_DATA_MISSING;
        }
#endif
        if (0 == op) {
            op = TUPLE16_TYPE_SYMBOL;
        }

        seg.segLen = sizeof(TUPLE16_SYMBOL);
        seg.type = TUPLE16_TYPE_SYMBOL;
        seg.op = op;
        seg.pData = pData;
        eRc = Tuple16_SegmentInsert(this, index, (TUPLE16_SEGMENT *)&seg);

        // Return to caller.
        return eRc;
    }


    ERESULT         Tuple16_InsertToken (
        TUPLE16_DATA    *this,
        uint8_t         index,
        uint8_t         op,
        TOKEN_FIELDS    *pData
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        TUPLE16_TOKEN   seg = {0};

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  TUPLE16_SINGLETON
        if (OBJ_NIL == this) {
            this = Tuple16_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Tuple16_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == this->pTuple) {
            DEBUG_BREAK();
            return ERESULT_DATA_MISSING;
        }
#endif
        if (0 == op) {
            op = TUPLE16_TYPE_TOKEN;
        }

        seg.segLen = sizeof(TUPLE16_TOKEN);
        seg.type = TUPLE16_TYPE_TOKEN;
        seg.op = op;
        memmove(&seg.data, pData, sizeof(TOKEN_FIELDS));
        eRc = Tuple16_SegmentInsert(this, index, (TUPLE16_SEGMENT *)&seg);
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                      I s  E n a b l e d
    //---------------------------------------------------------------
    
    bool                Tuple16_IsEnabled (
        TUPLE16_DATA       *this
    )
    {
        //ERESULT         eRc;
        bool            fRc = false;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  TUPLE16_SINGLETON
        if (OBJ_NIL == this) {
            this = Tuple16_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Tuple16_Validate(this)) {
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
        void        *pMethod = Tuple16_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_DATA, an object's data is returned
                        if it fits in a "void *".
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "Tuple16", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          Tuple16_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        TUPLE16_DATA     *this = objId;
        const
        char            *pStrA = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!Tuple16_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(TUPLE16_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)Tuple16_Class();
                break;

            case OBJ_QUERYINFO_TYPE_DATA:
                switch (*pStrA) {
     
                    case 'T':
                        if (str_Compare("Tuple", (char *)pStrA) == 0) {
                            return (void *)this->pTuple;
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
                            return Tuple16_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStrA) == 0) {
                            return Tuple16_Enable;
                        }
                        break;

                    case 'P':
#ifdef  TUPLE16_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStrA) == 0) {
                            return Tuple16_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStrA) == 0) {
                            return Tuple16_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStrA) == 0) {
                            return Tuple16_ToDebugString;
                        }
#ifdef  TUPLE16_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStrA) == 0) {
                            return Tuple16_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStrA) == 0) {
                            return Tuple16_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == Tuple16_ToDebugString)
                    return "ToDebugString";
#ifdef  TUPLE16_JSON_SUPPORT
                if (pData == Tuple16_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                      S e g m e n t
    //---------------------------------------------------------------
    
    TUPLE16_SEGMENT * Tuple16_Segment (
        TUPLE16_DATA    *this,
        uint8_t         index
    )
    {
        //ERESULT         eRc;
        int             offset;
        TUPLE16_SEGMENT *pSeg = NULL;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  TUPLE16_SINGLETON
        if (OBJ_NIL == this) {
            this = Tuple16_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Tuple16_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return NULL;
        }
        if (NULL == this->pTuple) {
            DEBUG_BREAK();
            //return ERESULT_DATA_MISSING;
            return NULL;
        }
        if ((0 == index) || (index > this->pTuple->cTuples)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return NULL;
        }
#endif
        index--;
        offset = Tuple16_SegmentOffset(this, index);
        if (offset > 0) {
            pSeg = (TUPLE16_SEGMENT *)offsetPtr(this->pTuple, offset);
        }
        
        // Return to caller.
        return pSeg;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Tuple16_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     Tuple16_ToDebugString (
        TUPLE16_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        uint32_t        i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Tuple16_Validate(this)) {
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
                    Tuple16_getSize(this),
                    obj_getRetainCount(this)
            );

        if (this->pTuple) {
            if (indent) {
                AStr_AppendCharRepeatA(pStr, indent, ' ');
            }
            AStr_AppendPrint(
                             pStr,
                             "Base: alloc:%d len:%d op:%d cTuples:%d\n",
                             this->pTuple->alloc,
                             this->pTuple->segLen,
                             this->pTuple->op,
                             this->pTuple->cTuples
            );
            for (i=0; i<this->pTuple->cTuples; i++) {
                TUPLE16_SEGMENT *pSeg = (TUPLE16_SEGMENT *)offsetPtr(this->pTuple,
                                                                     Tuple16_SegmentOffset(this, i));
                if (indent) {
                    AStr_AppendCharRepeatA(pStr, indent+4, ' ');
                }
                AStr_AppendPrint(
                                 pStr,
                                 "Seg: len:%d op:%d\n",
                                 pSeg->segLen,
                                 pSeg->op
                );
            }
        }
        
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
    bool            Tuple16_Validate (
        TUPLE16_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_TUPLE16))
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


        if (!(obj_getSize(this) >= sizeof(TUPLE16_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef  __cplusplus
}
#endif


