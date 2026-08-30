// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
// Scan an AST for various manipulations (AstScan) Internal Header
//****************************************************************

/* 
 * File:   AstScan_internal.h
 *  Generated 02/12/2023 09:19:30
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




#include        <AstScan.h>
#ifdef  ASTSCAN_SUPER_DEFINED
#include        <obj_internal.h>
#endif
#include        <JsonIn.h>


#ifndef ASTSCAN_INTERNAL_H
#define ASTSCAN_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------


#if !defined(__arm64__)
#pragma pack(push, 1)
#endif
struct AstScan_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
#ifdef  ASTSCAN_SUPER_DEFINED
    OBJ_DATA  super;
#else
    OBJ_DATA        super;
#endif
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    AST_DATA        *pAst;
    AST_ENTRY       *pRoot;
    PTRARRAY_DATA   *pArray;
    uint32_t        index;
    uint32_t        start;

#ifdef   ASTSCAN_MSGS
    // Informational and Warning Log Messages
    void            (*pMsgInfo)(OBJ_ID, const char *, ...);
    void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...);
    OBJ_ID          pMsgObj;
#endif
};
#if !defined(__arm64__)
#pragma pack(pop)
#endif

    extern
    struct AstScan_class_data_s  AstScan_ClassObj;

    extern
    const
    ASTSCAN_VTBL         AstScan_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  ASTSCAN_SINGLETON
    ASTSCAN_DATA *     AstScan_getSingleton (
        void
    );

    bool            AstScan_setSingleton (
     ASTSCAN_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  ASTSCAN_SUPER_DEFINED
    OBJ_DATA *  AstScan_getSuper (
        ASTSCAN_DATA     *this
    );
#else
    OBJ_DATA *  AstScan_getSuper (
        ASTSCAN_DATA     *this
    );
#endif


    OBJ_IUNKNOWN *  AstScan_getSuperVtbl (
        ASTSCAN_DATA     *this
    );


    ERESULT         AstScan_Assign (
        ASTSCAN_DATA    *this,
        ASTSCAN_DATA    *pOther
    );


    ASTSCAN_DATA *       AstScan_Copy (
        ASTSCAN_DATA     *this
    );


    void            AstScan_Dealloc (
        OBJ_ID          objId
    );


    ASTSCAN_DATA *     AstScan_DeepCopy (
        ASTSCAN_DATA       *this
    );


#ifdef  ASTSCAN_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    ASTSCAN_DATA *       AstScan_ParseJsonObject (
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
    ERESULT         AstScan_ParseJsonFields (
        JSONIN_DATA     *pParser,
        ASTSCAN_DATA     *pObject
    );
#endif


    void *          AstScan_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  ASTSCAN_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = AstScan_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     AstScan_ToJson (
        ASTSCAN_DATA      *this
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
    ERESULT         AstScan_ToJsonFields (
        ASTSCAN_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool            AstScan_Validate (
        ASTSCAN_DATA       *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* ASTSCAN_INTERNAL_H */

