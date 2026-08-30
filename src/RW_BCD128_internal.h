// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
// Binary Coded Decimal based on int128_t (RW_BCD128) Internal Header
//****************************************************************

/* 
 * File:   RW_BCD128_internal.h
 *  Generated 06/03/2026 08:40:22
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




#include        <RW_BCD128.h>
#ifdef  RW_BCD128_SUPER_DEFINED
#include        <obj_internal.h>
#endif
#include        <JsonIn.h>


#ifndef RW_BCD128_INTERNAL_H
#define RW_BCD128_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------


#if !defined(__arm64__)
#pragma pack(push, 1)
#endif
struct RW_BCD128_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
#ifdef  RW_BCD128_SUPER_DEFINED
    OBJ_DATA        super;
#else
    OBJ_DATA        super;
#endif
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    int128_t        dec;
    ASTR_DATA       *pStr;

#ifdef   RW_BCD128_MSGS
    // Informational and Warning Log Messages
    void            (*pMsgInfo)(OBJ_ID, const char *, ...);
    void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...);
    OBJ_ID          pMsgObj;
#endif

    uint16_t        size;           // maximum number of elements
    uint16_t        rsvd16;
};
#if !defined(__arm64__)
#pragma pack(pop)
#endif

    extern
    struct RW_BCD128_class_data_s  
                        RW_BCD128_ClassObj;

    extern
    const
    RW_BCD128_VTBL      RW_BCD128_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  RW_BCD128_SINGLETON
    RW_BCD128_DATA * 
                    RW_BCD128_getSingleton (
        void
    );

    bool            RW_BCD128_setSingleton (
     RW_BCD128_DATA     *pValue
);
#endif


    /*  
        +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
        Define internal routines here so that they can be used
        in testing. Make sure that they have the object name
        prefixing the routine names to avoid conflicts.
        +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    */



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  RW_BCD128_SUPER_DEFINED
    OBJ_DATA *      RW_BCD128_getSuper (
        RW_BCD128_DATA  *this
    );
#else
    OBJ_DATA *      RW_BCD128_getSuper (
        RW_BCD128_DATA  *this
    );
#endif


    OBJ_IUNKNOWN *  RW_BCD128_getSuperVtbl (
        RW_BCD128_DATA  *this
    );


    ERESULT         RW_BCD128_Assign (
        RW_BCD128_DATA  *this,
        RW_BCD128_DATA  *pOther
    );


    RW_BCD128_DATA *       
                    RW_BCD128_Copy (
        RW_BCD128_DATA  *this
    );


    void            RW_BCD128_Dealloc (
        OBJ_ID          objId
    );


    RW_BCD128_DATA * 
                    RW_BCD128_DeepCopy (
        RW_BCD128_DATA  *this
    );


    RW_BCD128_DATA * 
                    RW_BCD128_Init (
        RW_BCD128_DATA  *this
    );


    RW_BCD128_DATA * 
                    RW_BCD128_New (
        void
    );
   
 
 #ifdef  RW_BCD128_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    RW_BCD128_DATA * 
                    RW_BCD128_ParseJsonObject (
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
    ERESULT         RW_BCD128_ParseJsonFields (
        JSONIN_DATA     *pParser,
        RW_BCD128_DATA  *pObject
    );
#endif


    void *          RW_BCD128_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  RW_BCD128_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = RW_BCD128_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     RW_BCD128_ToJson (
        RW_BCD128_DATA  *this
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
    ERESULT         RW_BCD128_ToJsonFields (
        RW_BCD128_DATA  *this,
        ASTR_DATA       *pStr
    );
#endif


    ASTR_DATA *     RW_BCD128_ToDebugString (
        RW_BCD128_DATA  *this,
        int             indent
    );


#ifdef NDEBUG
#else
    bool            RW_BCD128_Validate (
        RW_BCD128_DATA  *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* RW_BCD128_INTERNAL_H */

