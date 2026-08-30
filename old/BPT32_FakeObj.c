// vi:nu:et:sts=4 ts=4 sw=4
//****************************************************************
//                 BPT32 RequestBlock Test Object
//****************************************************************
/*
 * Program
 *          BPT32 RequestBlock Test Object
 * Purpose
 *          Thi
 *          parameters.
 *
 * Remarks
 *  1.      This relies on the fact that we can add to the Test
 *          Object by simply coding methods that use the Test
 *          Object.
 *
 * History
 *  08/29/2021 Generated
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


#include    <test_defs.h>
#include    <Test_internal.h>
#include    <trace.h>
#include    <BPT32_internal.h>
#include    <BPT32_Request.h>
#include    <U32Index.h>


/*
 TestForFail(error_sttring)         <= Tests eRc for failure
 TestForFalse(test, error_sttring)
 TestForNotNull(test, error)
 TestForNull(test, error)
 TestForSuccess(error)              <= Tests eRc for success
 TestForTrue(test, error)
 */





uint32_t        BPT32FO_MasterLBN = 100;
uint32_t        BPT32FO_MasterBlockSize = 128;
uint32_t        BPT32FO_MasterDataSize = 128;
uint32_t        BPT32FO_MasterKeyLen = 4;
uint32_t        BPT32FO_MasterKeyOff = 0;

static
BPT32_HEADER    BPT32FO_hdr = {
    0
};


// This VTbl supports Retain() and Release() which is
static
const
char        *pBPT32FO_RequestDesc[] = {
    "BPT32_REQUEST_UNKNOWN",            //  0
    "BPT32_REQUEST_NEW_LBN",            //  1 - Return a new Logical Block Number not
    //                                  // currently allocated.
    //                                  //  obj   - ignored
    //                                  //  parm1 - ignored
    //                                  //  parm2 - ignored
    //                                  //  parm3 - lbn return pointer (uint32_t *)
    "BPT32_REQUEST_NEW_INDEX",          //  2 - Return a new empty index block.
    "BPT32_REQUEST_NEW_LEAF",           //  3 - Return a new empty leaf block.
    "BPT32_REQUEST_PARENT",             //  4 - Get Parent after a search
    "BPT32_REQUEST_READ",               //  5 - Read a buffer from disk
    //                                  //  obj   - object requesting read
    //                                  //        (lbn and block are gotten from vtbl)
    //                                  //  parm1 - lbn pointer
    //                                  //  parm2 - block pointer
    //                                  //  parm3 - ignored
    "BPT32_REQUEST_SPLIT",              //  6 - A Block Split is needed???
    "BPT32_REQUEST_SPLIT_INDEX",        //  7 - A Block Split occurred so
    //                                  // handle the index block update(s)
    "BPT32_REQUEST_SPLIT_LEAF",         //  8 - A Leaf Block Split is needed. Handle it
    //                                  // and the index block update(s)
    "BPT32_REQUEST_SET_TAIL",           //  9 - Change Data Tail to given block.
    //                                  //  obj   - object requesting tail
    //                                  //        (lbn is gotten from vtbl)
    //                                  //  parm1 - ignored
    //                                  //  parm2 - ignored
    //                                  //  parm3 - ignored
    "BPT32_REQUEST_WRITE",              // 10 -Write a buffer to disk.

};



//---------------------------------------------------------------
//                  B l o c k  R e q u e s t
//---------------------------------------------------------------

/*!
 @warning   This method must always conform to P_ERESULT_EXIT5.
 */
static
ERESULT         BPT32FO_BlockRequest(
    OBJ_ID          this,
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
    uint32_t        lbn = 0;            // Logical Block Number
    void            *pBlock = NULL;
    BPT32_BLK_VTBL  *pVtbl = NULL;
    uint16_t        ident;


    fprintf(
            stderr,
            "BPT32FO_FakeObj::BlockRequest(%d - %s)\n",
            request,
            pBPT32FO_RequestDesc[request]
    );
    
    switch (request) {

        case BPT32_REQUEST_NEW_LBN:
            if (NULL == pParm3) {
                DEBUG_BREAK();
                return ERESULT_INVALID_PARAMETER;
            }
            lbn = ++BPT32FO_MasterLBN;
            if (pParm3)
                *((uint32_t *)pParm3) = lbn;
            break;

        case BPT32_REQUEST_NEW_INDEX:
            if (NULL == pParm3) {
                DEBUG_BREAK();
                return ERESULT_INVALID_PARAMETER;
            }
            lbn = ++BPT32FO_MasterLBN;
            fprintf(
                    stderr,
                    "BPT32FO_FakeObj::BlockSize: %d  BPT32FO_FakeObj::DataSize: %d  BPT32FO_FakeObj::LBN: %d\n",
                    BPT32FO_MasterBlockSize,
                    BPT32FO_MasterDataSize,
                    BPT32FO_MasterLBN
            );
            pIndex =    BPT32Index_NewWithSizes(
                                        BPT32FO_MasterBlockSize,
                                        sizeof(uint32_t),
                                        lbn,
                                        true,
                                        this
                        );
            if (OBJ_NIL == pIndex) {
                DEBUG_BREAK();
                --BPT32FO_MasterLBN;
                return ERESULT_OUT_OF_MEMORY;
            }
            if (NULL == pIndex->pBlock) {
                DEBUG_BREAK();
                --BPT32FO_MasterLBN;
                return ERESULT_OUT_OF_MEMORY;
            }
            if (pParm3)
                *((void **)pParm3) = pIndex;
            else
                obj_Release(pIndex);
            pIndex = NULL;
            eRc = ERESULT_SUCCESS;
            break;

        case BPT32_REQUEST_NEW_LEAF:
            if (NULL == pParm3) {
                DEBUG_BREAK();
                return ERESULT_INVALID_PARAMETER;
            }
            lbn = ++BPT32FO_MasterLBN;
            pLeaf = BPT32Leaf_NewWithSizes(
                                        BPT32FO_MasterBlockSize,
                                        BPT32FO_MasterDataSize,
                                        lbn,
                                        true,
                                        this
                    );
            if (OBJ_NIL == pLeaf) {
                DEBUG_BREAK();
                --BPT32FO_MasterLBN;
                return ERESULT_OUT_OF_MEMORY;
            }
            pLeaf->pReq = BPT32FO_BlockRequest;
            if (pParm3)
                *((void **)pParm3) = pLeaf;
            else
                obj_Release(pLeaf);
            pLeaf = NULL;
            eRc = ERESULT_SUCCESS;
            break;

        case BPT32_REQUEST_PARENT:
            if (NULL == pObj) {
                DEBUG_BREAK();
                return ERESULT_INVALID_PARAMETER;
            }
            pVtbl = (BPT32_BLK_VTBL *)obj_getVtbl(pObj);
            lbn = pVtbl->pGetLBN(pObj);
            //FIXME: eRc = BPT_BlockFindParent(this, lbn, pParm3);
            break;

        case BPT32_REQUEST_READ:
            if (NULL == pObj) {
                DEBUG_BREAK();
                return ERESULT_INVALID_PARAMETER;
            }
            lbn = *(LBN32_T *)pParm1;
            fprintf(stderr, "\tRead data for block %d...\n", lbn);
#ifdef XYZZY
            pVtbl = (BPT32_BLK_VTBL *)obj_getVtbl(pObj);
            lbn = pVtbl->pGetLBN(pObj);
            pBlock = pVtbl->pGetBlock(pObj);
            if (NULL == pBlock) {
                eRc = ERESULT_DATA_MISSING;
            } else {
                if (lbn && pBlock) {
                    eRc = ERESULT_SUCCESS;
                }
                else
                    eRc = ERESULT_GENERAL_FAILURE;
            }
#endif
            eRc = ERESULT_SUCCESS;
            break;

        case BPT32_REQUEST_SPLIT:
            // pObj == Left Object
            // pParm1 == Right Object
            //FIXME: eRc = BPT_BlockSplit(this, (OBJ_ID)pObj, pRet);
            eRc = ERESULT_SUCCESS;
            break;

        case BPT32_REQUEST_SET_TAIL:
            if (OBJ_IDENT_BPT32LEAF == obj_getType(pObj)) {
                BPT32FO_hdr.dataTail = BPT32Leaf_getLBN((BPT32LEAF_DATA *)pObj);
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
            fprintf(stderr, "\tWrite block data\n");
            ident = obj_getType(pObj);
            if (OBJ_IDENT_BPT32INDEX == ident) {
                fprintf(stderr, "\t\tBPT32INDEX\n");
            }
            else if (OBJ_IDENT_BPT32INDEX == ident) {
                fprintf(stderr, "\t\tBPT32LEAF\n");
            }
            else {
                fprintf(stderr, "\tInvalid obj_ident,  %d\n", ident);
            }
            lbn = 0;
            pVtbl = (BPT32_BLK_VTBL *)obj_getVtbl(pObj);
            if (pVtbl) {
            } else {
                fprintf(stderr, "\tInvalid pVtbl from pObj!\n");
            }
            if (pVtbl->pGetLBN) {
                lbn = pVtbl->pGetLBN(pObj);
            } else {
                fprintf(stderr, "\tInvalid pVtbl->pGetLBN\n");
            }
            fprintf(stderr, "\tWrite data for block %d...\n", lbn);
            pBlock = pVtbl->pGetBlock(pObj);
            if (lbn && pBlock) {
                eRc = ERESULT_SUCCESS;
            }
            else
                eRc = ERESULT_GENERAL_FAILURE;
            break;

        default:
            fprintf(stderr, "\tUnknown Request\n");
            DEBUG_BREAK();
            return ERESULT_INVALID_REQUEST;
            break;
    }

    return eRc;
}



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

void *          BPT32FO_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    BPT32_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;

    if (OBJ_NIL == this) {
        return NULL;
    }

    switch (type) {

        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {

                case 'M':
                    if (str_Compare("MasterBlockSize", (char *)pStr) == 0) {
                        return &BPT32FO_MasterBlockSize;
                    }
                    if (str_Compare("MasterDataSize", (char *)pStr) == 0) {
                        return &BPT32FO_MasterBlockSize;
                    }
                    if (str_Compare("MasterKeyLen", (char *)pStr) == 0) {
                        return &BPT32FO_MasterKeyLen;
                    }
                    if (str_Compare("MasterKeyOff", (char *)pStr) == 0) {
                        return &BPT32FO_MasterKeyOff;
                    }
                    if (str_Compare("MasterLBN", (char *)pStr) == 0) {
                        return &BPT32FO_MasterLBN;
                    }
                    break;

                default:
                    break;
            }
            break;

        case OBJ_QUERYINFO_TYPE_METHOD:
            switch (*pStr) {

                case 'B':
                    if (str_Compare("BlockRequest", (char *)pStr) == 0) {
                        return BPT32FO_BlockRequest;
                    }
                    break;

                default:
                    break;
            }
            break;

        default:
            break;
    }

    return NULL;
}



// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
static
const
BPT32_VTBL     BPT32FO_Vtbl = {
    {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        (P_OBJ_QUERYINFO)BPT32FO_QueryInfo,
        NULL,
        NULL,           // BPTIndex_Enable,
        NULL,           // BPTIndex_Disable,
        NULL,           // (P_OBJ_ASSIGN)BPTIndex_Assign,
        NULL,           // (P_OBJ_COMPARE)BPTIndex_Compare,
        NULL,           // (P_OBJ_PTR)BPTIndex_Copy,
        NULL,           // (P_OBJ_PTR)BPTIndex_DeepCopy,
        NULL            // (P_OBJ_HASH)BPTIndex_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //BPTIndex_IsEnabled,

};


static
struct  BPT32_request_data_s {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;

    // Common Data
    uint32_t        misc;
}           BPT32FO_fakeObj = {
    {
        (void *)&BPT32FO_Vtbl,
        sizeof(OBJ_DATA),                       // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    0
};


OBJ_DATA    *pBPT32_FakeObj = (void *)&BPT32FO_fakeObj;








