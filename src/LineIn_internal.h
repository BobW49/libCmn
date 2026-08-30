// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//              File Input - Line at a time (LineIn) Internal Header
//****************************************************************

/* 
 * File:   LineIn_internal.h
 *  Generated 03/31/2023 08:27:53
 *
 * Notes:
 *  --  TODO:
 *      -- Add LineIndex Support
 *      -- Add LineAccum Support ??? or direct movement from file
 *          buffer to line buffer.
 *      -- Add IBM 80-Col support
 *      -- Add Push support (FIFO)
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




#include        <LineIn.h>
#ifdef  LINEIN_SUPER_DEFINED
#include        <FileIO_internal.h>
#endif
#include        <JsonIn.h>


#ifndef LINEIN_INTERNAL_H
#define LINEIN_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------


#if !defined(__arm64__)
#pragma pack(push, 1)
#endif
struct LineIn_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
#ifdef  LINEIN_SUPER_DEFINED
    FILEIO_DATA     super;
#else
    OBJ_DATA        super;
#endif
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    LINEINDEX_DATA  *pIndex;
    
    //      Input File Buffer and control variables
    // see pBuffer above.
    uint8_t         *pBuffer;
    uint32_t        maxBuffer;
    uint32_t        cBuffer;            // Current Buffer usage
    uint32_t        iBuffer;            // Current index into buffer
    uint32_t        iPos;               // File Position
    
    SRCLOC          loc;
    uint8_t         fEOF;
    uint8_t         rsvd8;
    uint16_t        rsvd16;

#ifdef   LINEIN_MSGS
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
    struct LineIn_class_data_s  LineIn_ClassObj;

    extern
    const
    LINEIN_VTBL         LineIn_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  LINEIN_SINGLETON
    LINEIN_DATA *     LineIn_getSingleton (
        void
    );

    bool            LineIn_setSingleton (
     LINEIN_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  LINEIN_SUPER_DEFINED
    FILEIO_DATA *   LineIn_getSuper (
        LINEIN_DATA     *this
    );
#else
    OBJ_DATA *      LineIn_getSuper (
        LINEIN_DATA     *this
    );
#endif


    OBJ_IUNKNOWN *  LineIn_getSuperVtbl (
        LINEIN_DATA     *this
    );


    ERESULT         LineIn_Assign (
        LINEIN_DATA     *this,
        LINEIN_DATA     *pOther
    );


    LINEIN_DATA *   LineIn_Copy (
        LINEIN_DATA     *this
    );


    void            LineIn_Dealloc (
        OBJ_ID          objId
    );


    LINEIN_DATA *   LineIn_DeepCopy (
        LINEIN_DATA     *this
    );


#ifdef  LINEIN_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    LINEIN_DATA *   LineIn_ParseJsonObject (
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
    ERESULT         LineIn_ParseJsonFields (
        JSONIN_DATA     *pParser,
        LINEIN_DATA     *pObject
    );
#endif


    void *          LineIn_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    /*!
     Read the next input buffer.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         LineIn_Read (
        LINEIN_DATA     *this
    );


#ifdef  LINEIN_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = LineIn_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     LineIn_ToJson (
        LINEIN_DATA     *this
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
    ERESULT         LineIn_ToJsonFields (
        LINEIN_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool            LineIn_Validate (
        LINEIN_DATA     *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* LINEIN_INTERNAL_H */

