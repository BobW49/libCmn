// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//              Output UTF-8 Textual Data (TextOut) Internal Header
//****************************************************************

/* 
 * File:   TextOut_internal.h
 *  Generated 08/03/2023 22:53:34
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




#include        <TextOut.h>
#ifdef  TEXTOUT_SUPER_DEFINED
#include        <obj_internal.h>
#endif
#include        <JsonIn.h>


#ifndef TEXTOUT_INTERNAL_H
#define TEXTOUT_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif


typedef enum TextOut_type_e {
    TEXTOUT_TYPE_UNKNOWN=0,
    TEXTOUT_TYPE_ASTR,
    TEXTOUT_TYPE_FILE,
    TEXTOUT_TYPE_FILE_CLOSE,
    TEXTOUT_TYPE_U8ARRAY
} TEXTOUT_TYPE;




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------


//#pragma pack(push, 1)
struct TextOut_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
#ifdef  TEXTOUT_SUPER_DEFINED
    OBJ_DATA        super;
#else
    OBJ_DATA        super;
#endif
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    union {
        ASTR_DATA           *pStr;
        FILE                *pFile;
        U8ARRAY_DATA        *pU8Array;
    };
    W32CHR_T        fillChar;       // Fill Char, normally ' '
    uint32_t        lineNo;         // Line number
    uint16_t        colNo;          // Column number
    uint16_t        colMax;         // Maximum Column number before automatic new-line
    uint16_t        offset;         //
    uint16_t        tabSize;        //
    uint8_t         type;
    uint8_t         fExpandTabs;
    uint8_t         fExpandMax;     // Whenever a NL is sent, fill out the line to colMax.
    uint8_t         rsvd8[3];

#ifdef   TEXTOUT_MSGS
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
    struct TextOut_class_data_s  TextOut_ClassObj;

    extern
    const
    TEXTOUT_VTBL         TextOut_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  TEXTOUT_SINGLETON
    TEXTOUT_DATA *     TextOut_getSingleton (
        void
    );

    bool            TextOut_setSingleton (
     TEXTOUT_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  TEXTOUT_SUPER_DEFINED
    OBJ_DATA *  TextOut_getSuper (
        TEXTOUT_DATA     *this
    );
#else
    OBJ_DATA *  TextOut_getSuper (
        TEXTOUT_DATA     *this
    );
#endif


    OBJ_IUNKNOWN *  TextOut_getSuperVtbl (
        TEXTOUT_DATA     *this
    );


    ERESULT         TextOut_Assign (
        TEXTOUT_DATA    *this,
        TEXTOUT_DATA    *pOther
    );


    TEXTOUT_DATA *       TextOut_Copy (
        TEXTOUT_DATA     *this
    );


    void            TextOut_Dealloc (
        OBJ_ID          objId
    );


    TEXTOUT_DATA *     TextOut_DeepCopy (
        TEXTOUT_DATA       *this
    );


#ifdef  TEXTOUT_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    TEXTOUT_DATA *       TextOut_ParseJsonObject (
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
    ERESULT         TextOut_ParseJsonFields (
        JSONIN_DATA     *pParser,
        TEXTOUT_DATA     *pObject
    );
#endif


    void *          TextOut_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  TEXTOUT_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = TextOut_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     TextOut_ToJson (
        TEXTOUT_DATA      *this
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
    ERESULT         TextOut_ToJsonFields (
        TEXTOUT_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif


#ifdef NDEBUG
#else
    bool            TextOut_Validate (
        TEXTOUT_DATA       *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* TEXTOUT_INTERNAL_H */

