// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//              Look-Ahead Scanner (LAScan) Internal Header
//****************************************************************

/* 
 * File:   LAScan_internal.h
 *  Generated 02/26/2023 10:04:02
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




#include        <LAScan.h>
#ifdef  LASCAN_SUPER_DEFINED
#include        <obj_internal.h>
#endif
#include        <JsonIn.h>


#ifndef LASCAN_INTERNAL_H
#define LASCAN_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif


#ifdef NDEBUG
#   define     LOOKAHEAD(num)   this->pInputLookAhead(this->pInputObj, num, &this->input)
#   define     ADVANCE(num)     this->pInputAdvance(this->pInputObj, num, &this->input)
#   define     ADVLOOK(num)     LAScan_InputAdvLook(this, num)
#else
#   define     LOOKAHEAD(num)   LAScan_InputLookAhead(this, num)
#   define     ADVANCE(num)     this->pInputAdvance(this->pInputObj, num, &this->input)
#   define     ADVLOOK(num)     LAScan_InputAdvLook(this, num)
#endif





    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------


#if !defined(__arm64__)
#pragma pack(push, 1)
#endif
struct LAScan_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
#ifdef  LASCAN_SUPER_DEFINED
    OBJ_DATA        super;
#else
    OBJ_DATA        super;
#endif
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    ASTR_DATA       *pStr;
    TOKEN_FIELDS    input;          // Current lookahead Token just constructed by Scan
    int32_t         inputCls;
    SRCLOC          inputBeginLoc;  // Beginning Source Location for parsed token
    uint8_t         fWS;            // true == scan white-space before what was requested
    uint8_t         fBool1;
    uint8_t         fBool2;
    uint8_t         fBool3;

    // External Input Methods/Object
    int32_t         (*pInputAdvance)(OBJ_ID, uint16_t, TOKEN_FIELDS *);
    int32_t         (*pInputLookAhead)(OBJ_ID, uint16_t, TOKEN_FIELDS *);
    OBJ_ID          pInputObj;

    // string accumulation buffer
    uint8_t         *pAccum;        // UTF-8 Buffer
    uint32_t        cBuffer;
    uint32_t        cAccum;
    uint32_t        maxAccum;
    uint32_t        rsvd32_b;
    
#ifdef   LASCAN_MSGS
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
    struct LAScan_class_data_s  LAScan_ClassObj;

    extern
    const
    LASCAN_VTBL         LAScan_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  LASCAN_SINGLETON
    LASCAN_DATA *     LAScan_getSingleton (
        void
    );

    bool            LAScan_setSingleton (
     LASCAN_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  LASCAN_SUPER_DEFINED
    OBJ_DATA *  LAScan_getSuper (
        LASCAN_DATA     *this
    );
#else
    OBJ_DATA *  LAScan_getSuper (
        LASCAN_DATA     *this
    );
#endif


    OBJ_IUNKNOWN *  LAScan_getSuperVtbl (
        LASCAN_DATA     *this
    );


    bool            LAScan_AccumStr (
        LASCAN_DATA     *this,
        const
        W32CHR_T        wrk
    );


    int32_t         LAScan_InputAdvLook (
        LASCAN_DATA     *this,
        int             num                 // Number of tokens to advance
    );


    ERESULT         LAScan_Assign (
        LASCAN_DATA    *this,
        LASCAN_DATA    *pOther
    );


    LASCAN_DATA *       LAScan_Copy (
        LASCAN_DATA     *this
    );


    void            LAScan_Dealloc (
        OBJ_ID          objId
    );


    LASCAN_DATA *   LAScan_DeepCopy (
        LASCAN_DATA       *this
    );


    int32_t         LAScan_InputLookAhead (
        LASCAN_DATA     *this,
        uint16_t        index
    );


#ifdef  LASCAN_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    LASCAN_DATA *       LAScan_ParseJsonObject (
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
    ERESULT         LAScan_ParseJsonFields (
        JSONIN_DATA     *pParser,
        LASCAN_DATA     *pObject
    );
#endif


    void *          LAScan_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  LASCAN_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = LAScan_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     LAScan_ToJson (
        LASCAN_DATA      *this
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
    ERESULT         LAScan_ToJsonFields (
        LASCAN_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool            LAScan_Validate (
        LASCAN_DATA       *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* LASCAN_INTERNAL_H */

