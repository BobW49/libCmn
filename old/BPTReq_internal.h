// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
// B-Plus Tree Internal Request Processor (BPTReq) Internal Header
//****************************************************************

/* 
 * File:   BPTReq_internal.h
 *  Generated 01/31/2023 20:11:00
 *
 * Notes:
 *  --  N/A
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




#include        <BPTReq.h>
#ifdef  BPTREQ_SUPER_DEFINED
#include        <obj_internal.h>
#endif
#include        <BPTIndex_internal.h>
#include        <BPTLeaf_internal.h>
#include        <JsonIn.h>
#include        <lru_internal.h>
#include        <ObjArray.h>
#include        <RRDS_internal.h>


#ifndef BPTREQ_INTERNAL_H
#define BPTREQ_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif


    //          Block Descriptor
    //#pragma pack(push, 1)
    typedef struct  BPT_blkidx_s {
        OBJ_ID          pBlock;
        uint32_t        blockLsn;       // Current Node Number in Work Block
    } BPT_BLKIDX;
    //#pragma pack(pop)


    //                      File Header
    // This header is saved in the 1st record of the file.
    //#pragma pack(push, 1)
    typedef struct  BPT_header_s {
        uint16_t        dataSize;       // Size of Data in node
        uint16_t        actualSize;
        uint32_t        blockSize;
        uint32_t        cRecords;       // Number of Records in the File including header
        uint32_t        root;           // Root Block Index
        uint32_t        dataHead;       // Head of Leaf Chain
        uint32_t        dataTail;       // End of Leaf Chain
        uint32_t        deleteHead;     // Head of Free Block Chain
    } BPT_HEADER;
    //#pragma pack(pop)




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------


#pragma pack(push, 1)
struct BPTReq_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
#ifdef  BPTREQ_SUPER_DEFINED
    OBJ_DATA  super;
#else
    OBJ_DATA        super;
#endif
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    ASTR_DATA       *pStr;
    PATH_DATA       *pPath;
    RRDS_DATA       *pIO;
    OBJARRAY_DATA   *pSrchStk;      // Search Block List
    OBJ_ID          pRoot;          // Root Record
    BPT_HEADER      *pHdr;
    uint16_t        size;           // maximum number of elements
    uint16_t        rsvd16;

#ifdef   BPTREQ_MSGS
    // Informational and Warning Log Messages
    void            (*pMsgInfo)(OBJ_ID, const char *, ...);
    void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...);
    OBJ_ID          pMsgObj;
#endif
};
#pragma pack(pop)

    extern
    struct BPTReq_class_data_s  BPTReq_ClassObj;

    extern
    const
    BPTREQ_VTBL         BPTReq_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  BPTREQ_SINGLETON
    BPTREQ_DATA *   BPTReq_getSingleton (
        void
    );

    bool            BPTReq_setSingleton (
     BPTREQ_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  BPTREQ_SUPER_DEFINED
    OBJ_DATA *      BPTReq_getSuper (
        BPTREQ_DATA     *this
    );
#else
    OBJ_DATA *      BPTReq_getSuper (
        BPTREQ_DATA     *this
    );
#endif


    OBJ_IUNKNOWN *  BPTReq_getSuperVtbl (
        BPTREQ_DATA     *this
    );


    ERESULT         BPTReq_Assign (
        BPTREQ_DATA    *this,
        BPTREQ_DATA    *pOther
    );


    ERESULT         BPTReq_BlockRead(
        BPTREQ_DATA     *this,
        uint32_t        lbn,                // Logical Block Number
        OBJ_ID          *ppObj
    );


    BPTREQ_DATA *   BPTReq_Copy (
        BPTREQ_DATA    *this
    );


    void            BPTReq_Dealloc (
        OBJ_ID          objId
    );


    BPTREQ_DATA *     BPTReq_DeepCopy (
        BPTREQ_DATA       *this
    );


#ifdef  BPTREQ_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    BPTREQ_DATA *       BPTReq_ParseJsonObject (
        JSONIN_DATA     *pParser
    );


    /*!
     Parse the object from an established parser. This helps facilitate
     parsing the fields from an inheriting object.
     @param pParser     an established jsonIn Parser Object
     @param pObject     an Object to be filled in with the
                        parsed fields.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         BPTReq_ParseJsonFields (
        JSONIN_DATA     *pParser,
        BPTREQ_DATA     *pObject
    );
#endif


    void *          BPTReq_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  BPTREQ_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = BPTReq_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     BPTReq_ToJson (
        BPTREQ_DATA      *this
    );


    /*!
     Append the json representation of the object's fields to the given
     string. This helps facilitate parsing the fields from an inheriting 
     object.
     @param this        Object Pointer
     @param pStr        String Pointer to be appended to.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         BPTReq_ToJsonFields (
        BPTREQ_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool            BPTReq_Validate (
        BPTREQ_DATA       *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* BPTREQ_INTERNAL_H */

