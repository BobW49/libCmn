// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//      16-bit Variable Sized Tuples (Tuple16) Internal Header
//****************************************************************

/* 
 * File:   Tuple16_internal.h
 *  Generated 01/28/2023 10:39:21
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




#include        <Tuple16.h>
#ifdef  TUPLE16_SUPER_DEFINED
#include        <obj_internal.h>
#endif
#include        <JsonIn.h>


#ifndef TUPLE16_INTERNAL_H
#define TUPLE16_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif


#define offsetPtr(base,off)  (((uint8_t *)base) + off)



    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------


#if !defined(__arm64__)
#pragma pack(push, 1)
#endif
struct Tuple16_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
#ifdef  TUPLE16_SUPER_DEFINED
    OBJ_DATA        super;
#else
    OBJ_DATA        super;
#endif
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    TUPLE16_SEGMENT_BASE
                    *pTuple;
    uint16_t        size;           // maximum number of elements
    uint16_t        rsvd16;

#ifdef   TUPLE16_MSGS
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
    struct Tuple16_class_data_s  Tuple16_ClassObj;

    extern
    const
    TUPLE16_VTBL         Tuple16_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  TUPLE16_SINGLETON
    TUPLE16_DATA *  Tuple16_getSingleton (
        void
    );

    bool            Tuple16_setSingleton (
     TUPLE16_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  TUPLE16_SUPER_DEFINED
    OBJ_DATA *      Tuple16_getSuper (
        TUPLE16_DATA    *this
    );
#else
    OBJ_DATA *      Tuple16_getSuper (
        TUPLE16_DATA    *this
    );
#endif


    OBJ_IUNKNOWN *  Tuple16_getSuperVtbl (
        TUPLE16_DATA    *this
    );


    ERESULT         Tuple16_Assign (
        TUPLE16_DATA    *this,
        TUPLE16_DATA    *pOther
    );


    TUPLE16_DATA *  Tuple16_Copy (
        TUPLE16_DATA    *this
    );


    void            Tuple16_Dealloc (
        OBJ_ID          objId
    );


    TUPLE16_DATA *  Tuple16_DeepCopy (
        TUPLE16_DATA    *this
    );


#ifdef  TUPLE16_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    TUPLE16_DATA *  Tuple16_ParseJsonObject (
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
    ERESULT         Tuple16_ParseJsonFields (
        JSONIN_DATA     *pParser,
        TUPLE16_DATA    *pObject
    );
#endif


    void *          Tuple16_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ERESULT         Tuple16_SegmentAppend (
        TUPLE16_DATA    *this,
        TUPLE16_SEGMENT *pSeg
    );


    ERESULT         Tuple16_SegmentDelete (
        TUPLE16_DATA    *this,
        int             index
    );


    ERESULT         Tuple16_SegmentInsert (
        TUPLE16_DATA    *this,
        int             index,
        TUPLE16_SEGMENT *pSeg
    );


    int             Tuple16_SegmentOffset (
        TUPLE16_DATA    *this,
        int             index
    );


#ifdef  TUPLE16_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Tuple16_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Tuple16_ToJson (
        TUPLE16_DATA      *this
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
    ERESULT         Tuple16_ToJsonFields (
        TUPLE16_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool            Tuple16_Validate (
        TUPLE16_DATA       *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* TUPLE16_INTERNAL_H */

