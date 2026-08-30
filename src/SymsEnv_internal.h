// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//     Symbol Table Environment ADT (SymsEnv) Internal Header
//****************************************************************

/* 
 * File:   SymsEnv_internal.h
 *  Generated 05/29/2023 10:14:40
 *
 * Notes:
 *  --  Since we are dealing with record pointers, we can not delete
 *      records. If we converted to using an index mechanism, then
 *      we could add deletion, but that incurs more overhead.
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




#include        <SymsEnv.h>
#ifdef  SYMSENV_SUPER_DEFINED
#include        <Blocks_internal.h>
#endif
#include        <JsonIn.h>
#include        <listdl.h>


#ifndef SYMSENV_INTERNAL_H
#define SYMSENV_INTERNAL_H


#define SYMSENV_USE_PTRS



#ifdef  __cplusplus
extern "C" {
#endif


#define SZTBL_BLOCK_SIZE  4096        /* Heap Control Block Size */


// The following are needed to eleminate referencing problems below.
typedef struct SymsEnv_Access_s *SYMSENV_ACCESSP;       // Access pointer
typedef struct SymsEnv_EnvElt_s *SYMSENV_ENVELTP;       // Environment pointer
typedef struct SymsEnv_ScpElt_s *SYMSENV_SCPELTP;       // Scope pointer
typedef struct SymsEnv_StkElt_s *SYMSENV_STKELTP;       // Stack pointer


#if !defined(__arm64__)
#pragma pack(push, 1)
#endif
    typedef struct index_record_s {
        uint16_t        idxSize;        // Size of Data including this header
    } INDEX_RECORD;
#if !defined(__arm64__)
#pragma pack(pop)
#endif


#if !defined(__arm64__)
#pragma pack(push, 1)
#endif
    typedef struct data_block_s {
        uint16_t        cbSize;         // Total Size of BLock including this header
#define DATA_BLOCK_MAX_SIZE 0x7FFF
        uint16_t        unusedSize;     // Amount of Data Unused between Index and
        //                              // data records
        uint16_t        numRecords;
        INDEX_RECORD    index[0];       // Index
    } DATA_BLOCK;
#if !defined(__arm64__)
#pragma pack(pop)
#endif


    typedef struct SymsEnv_Block_s {
#ifdef SYMSENV_USE_PTRS
        LISTDL_NODE     list;           // Block Chain List
#else
        uint32_t        prev;           // Block chain list
        uint32_t        next;
#endif
        DATA_BLOCK      data[0];        // Index
    } SYMSENV_BLOCK;

    typedef struct SymsEnv_Access_s {
        OBJARRAY_DATA   *pStks;             // Array of Stack Elements (SYMSENV_STKELT)
        SYMSENV_ENVELTP pCur;               // Current Environment
    } SYMSENV_ACCESS;

    typedef struct SymsEnv_EnvElt_s {
        SYMSENV_ENVELTP pParent;
        SYMSENV_ACCESSP pNested;
        SYMS_DATA       *pKeys;
    } SYMSENV_ENVELT;

    typedef struct SymsEnv_ScpElt_s {
        SYMSENV_SCPELTP pNext;
        SYM_DATA        *pName;
        SYM_DATA        *pKey;
    } SYMSENV_SCPELT;

    typedef struct SymsEnv_StkElt_s {
        SYMSENV_STKELTP pOut;
        SYMSENV_ENVELTP pEnv;
        SYM_DATA        *pKey;
    } SYMSENV_STKELT;


    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------


//#pragma pack(push, 1)
struct SymsEnv_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
#ifdef  SYMSENV_SUPER_DEFINED
    BLOCKS_DATA     super;
#else
    OBJ_DATA        super;
#endif
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    ASTR_DATA       *pStr;
    LISTDL_DATA     *pBlks;         // Block List

#ifdef   SYMSENV_MSGS
    // Informational and Warning Log Messages
    void            (*pMsgInfo)(OBJ_ID, const char *, ...);
    void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...);
    OBJ_ID          pMsgObj;
#endif

    uint16_t        size;           // maximum number of elements
    uint16_t        rsvd16;
};
//#pragma pack(pop)

    extern
    struct SymsEnv_class_data_s  SymsEnv_ClassObj;

    extern
    const
    SYMSENV_VTBL         SymsEnv_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  SYMSENV_SINGLETON
    SYMSENV_DATA *  SymsEnv_getSingleton (
        void
    );

    bool            SymsEnv_setSingleton (
     SYMSENV_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  SYMSENV_SUPER_DEFINED
    OBJ_DATA *      SymsEnv_getSuper (
        SYMSENV_DATA     *this
    );
#else
    OBJ_DATA *      SymsEnv_getSuper (
        SYMSENV_DATA     *this
    );
#endif


    OBJ_IUNKNOWN *  SymsEnv_getSuperVtbl (
        SYMSENV_DATA     *this
    );


    ERESULT         SymsEnv_Assign (
        SYMSENV_DATA    *this,
        SYMSENV_DATA    *pOther
    );


    SYMSENV_DATA *   SymsEnv_Copy (
        SYMSENV_DATA     *this
    );


    void            SymsEnv_Dealloc (
        OBJ_ID          objId
    );


    SYMSENV_DATA *  SymsEnv_DeepCopy (
        SYMSENV_DATA       *this
    );


#ifdef  SYMSENV_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    SYMSENV_DATA *  SymsEnv_ParseJsonObject (
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
    ERESULT         SymsEnv_ParseJsonFields (
        JSONIN_DATA     *pParser,
        SYMSENV_DATA    *pObject
    );
#endif


    void *          SymsEnv_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  SYMSENV_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = SymsEnv_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     SymsEnv_ToJson (
        SYMSENV_DATA    *this
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
    ERESULT         SymsEnv_ToJsonFields (
        SYMSENV_DATA    *this,
        ASTR_DATA       *pStr
    );
#endif


#ifdef NDEBUG
#else
    bool            SymsEnv_Validate (
        SYMSENV_DATA    *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* SYMSENV_INTERNAL_H */

