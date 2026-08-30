// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//  a List of 16-bit Variable Sized Tuples (Tuples16) Internal Header
//****************************************************************

/* 
 * File:   Tuples16_internal.h
 *  Generated 01/28/2023 10:52:55
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




#include        <Tuples16.h>
#ifdef  TUPLES16_SUPER_DEFINED
#include        <obj_internal.h>
#endif
#include        <JsonIn.h>
#include        <listdl.h>


#ifndef TUPLES16_INTERNAL_H
#define TUPLES16_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif

typedef struct Tuple16_Entry_s {
    LISTDL_NODE             list;
    TUPLE16_SEGMENT_BASE    base;
} TUPPLE16_ENTRY;


    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------


#if !defined(__arm64__)
#pragma pack(push, 1)
#endif
struct Tuples16_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
#ifdef  TUPLES16_SUPER_DEFINED
    OBJ_DATA        super;
#else
    OBJ_DATA        super;
#endif
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    TUPLE16_DATA    *pTuple;
    LISTDL_DATA     list;

#ifdef   TUPLES16_MSGS
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
    struct Tuples16_class_data_s  Tuples16_ClassObj;

    extern
    const
    TUPLES16_VTBL         Tuples16_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  TUPLES16_SINGLETON
    TUPLES16_DATA *     Tuples16_getSingleton (
        void
    );

    bool            Tuples16_setSingleton (
     TUPLES16_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  TUPLES16_SUPER_DEFINED
    OBJ_DATA *  Tuples16_getSuper (
        TUPLES16_DATA     *this
    );
#else
    OBJ_DATA *  Tuples16_getSuper (
        TUPLES16_DATA     *this
    );
#endif


    OBJ_IUNKNOWN *  Tuples16_getSuperVtbl (
        TUPLES16_DATA     *this
    );


    ERESULT         Tuples16_Assign (
        TUPLES16_DATA    *this,
        TUPLES16_DATA    *pOther
    );


    TUPLES16_DATA *       Tuples16_Copy (
        TUPLES16_DATA     *this
    );


    void            Tuples16_Dealloc (
        OBJ_ID          objId
    );


    TUPLES16_DATA *     Tuples16_DeepCopy (
        TUPLES16_DATA       *this
    );


#ifdef  TUPLES16_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    TUPLES16_DATA *       Tuples16_ParseJsonObject (
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
    ERESULT         Tuples16_ParseJsonFields (
        JSONIN_DATA     *pParser,
        TUPLES16_DATA     *pObject
    );
#endif


    void *          Tuples16_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  TUPLES16_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Tuples16_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Tuples16_ToJson (
        TUPLES16_DATA      *this
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
    ERESULT         Tuples16_ToJsonFields (
        TUPLES16_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool            Tuples16_Validate (
        TUPLES16_DATA       *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* TUPLES16_INTERNAL_H */

