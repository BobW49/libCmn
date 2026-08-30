// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//              Source File Location (SrcLoc) Internal Header
//****************************************************************

/* 
 * File:   SrcLoc_internal.h
 *  Generated 12/25/2022 08:43:29
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




#include        <SrcLoc.h>
#ifdef  SRCLOC_SUPER_DEFINED
#include        <obj_internal.h>
#endif
#include        <JsonIn.h>


#ifndef SRCLOC_INTERNAL_H
#define SRCLOC_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

    /*  
        +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
        Remember that if you change the fields of this struct that
        you probably need to change the JSON support as well!
        +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    */

#if !defined(__arm64__)
#pragma pack(push, 1)
#endif
struct SrcLoc_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
#ifdef  SRCLOC_SUPER_DEFINED
    OBJ_DATA        super;
#else
    OBJ_DATA        super;
#endif
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    SRCLOC          data;

#ifdef   SRCLOC_MSGS
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
    struct SrcLoc_class_data_s  SrcLoc_ClassObj;

    extern
    const
    SRCLOC_VTBL         SrcLoc_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  SRCLOC_SINGLETON
    SRCLOC_DATA *     SrcLoc_getSingleton (
        void
    );

    bool            SrcLoc_setSingleton (
     SRCLOC_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  SRCLOC_SUPER_DEFINED
    OBJ_DATA *  SrcLoc_getSuper (
        SRCLOC_DATA     *this
    );
#else
    OBJ_DATA *  SrcLoc_getSuper (
        SRCLOC_DATA     *this
    );
#endif


    OBJ_IUNKNOWN *  SrcLoc_getSuperVtbl (
        SRCLOC_DATA     *this
    );


    ERESULT         SrcLoc_Assign (
        SRCLOC_DATA    *this,
        SRCLOC_DATA    *pOther
    );


    SRCLOC_DATA *       SrcLoc_Copy (
        SRCLOC_DATA     *this
    );


    void            SrcLoc_Dealloc (
        OBJ_ID          objId
    );


    SRCLOC_DATA *     SrcLoc_DeepCopy (
        SRCLOC_DATA       *this
    );


#ifdef  SRCLOC_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    SRCLOC_DATA *       SrcLoc_ParseJsonObject (
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
    ERESULT         SrcLoc_ParseJsonFields (
        JSONIN_DATA     *pParser,
        SRCLOC_DATA     *pObject
    );
#endif


    void *          SrcLoc_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  SRCLOC_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = SrcLoc_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     SrcLoc_ToJson (
        SRCLOC_DATA      *this
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
    ERESULT         SrcLoc_ToJsonFields (
        SRCLOC_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool            SrcLoc_Validate (
        SRCLOC_DATA       *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* SRCLOC_INTERNAL_H */

