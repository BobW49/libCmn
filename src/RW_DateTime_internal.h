// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//      Specific Date and Time (RW_DateTime) Internal Header
//****************************************************************

/* 
 * File:   RW_DateTime_internal.h
 *  Generated 05/31/2026 10:01:12
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




#include        <RW_DateTime.h>
#ifdef  RW_DATETIME_SUPER_DEFINED
#include        <obj_internal.h>
#endif
#include        <JsonIn.h>


#ifndef RW_DATETIME_INTERNAL_H
#define RW_DATETIME_INTERNAL_H





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
struct RW_DateTime_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
#ifdef  RW_DATETIME_SUPER_DEFINED
    OBJ_DATA        super;
#else
    OBJ_DATA        super;
#endif
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    uint64_t        time;           // UTC Date & Time encoded to binary
    //                              // See RW_DateTime_FromUInt64() & RW_DateTime_ToUInt64()
    //                              // for details.

#ifdef   RW_DATETIME_MSGS
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
    struct RW_DateTime_class_data_s  
                        RW_DateTime_ClassObj;

    extern
    const
    RW_DATETIME_VTBL    RW_DateTime_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  RW_DATETIME_SINGLETON
    RW_DATETIME_DATA * 
                    RW_DateTime_getSingleton (
        void
    );

    bool            RW_DateTime_setSingleton (
     RW_DATETIME_DATA   *pValue
);
#endif


    /*  
        +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
        Define internal routines here so that they can be used
        in testing. Make sure that they have the object name
        prefixing the routine names to avoid conflicts.
        +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    */

    ERESULT         RW_DateTime_FromGregorian(
        int16_t         iYear,
        int16_t         iMonth,
        int16_t         iDay,
        int16_t         *piJulianDay
    );

    
    ERESULT         RW_DateTime_FromHHMMSS (
        int16_t         Hour,
        int16_t         Minute,
        int16_t         Second,
        int16_t         Milli,
        int32_t         *pMilSec
    );

    
    ERESULT         RW_DateTime_ToGregorian (
        int32_t         JulNum,
        int16_t         *pDay,
        int16_t         *pMonth,
        int16_t         *pYear
    );

    
    ERESULT         RW_DateTime_ToHHMMSS (
        int32_t         milSec,
        int16_t         *Hour,
        int16_t         *Minute,
        int16_t         *Second,
        int16_t         *Milli
    );

    
    ERESULT         RW_DateTime_FromUInt64 (
        uint64_t        time,
        int16_t         *pYear,
        int16_t         *pMonth,
        int16_t         *pDay,
        int16_t         *pHours,
        int16_t         *pMins,
        int16_t         *pSecs,
        int16_t         *pMilli
    );


    ERESULT         RW_DateTime_ToUInt64 (
        int16_t         year,
        int16_t         month,
        int16_t         day,
        int16_t         hours,
        int16_t         mins,
        int16_t         secs,
        int16_t         milli,
        uint64_t        *pTime
    );

    

    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  RW_DATETIME_SUPER_DEFINED
    OBJ_DATA *      RW_DateTime_getSuper (
        RW_DATETIME_DATA 
                        *this
    );
#else
    OBJ_DATA *      RW_DateTime_getSuper (
        RW_DATETIME_DATA 
                        *this
    );
#endif


    OBJ_IUNKNOWN *  RW_DateTime_getSuperVtbl (
        RW_DATETIME_DATA 
                        *this
    );


    ERESULT         RW_DateTime_Assign (
        RW_DATETIME_DATA 
                        *this,
        RW_DATETIME_DATA 
                        *pOther
    );


    RW_DATETIME_DATA *       
                    RW_DateTime_Copy (
        RW_DATETIME_DATA 
                        *this
    );


    void            RW_DateTime_Dealloc (
        OBJ_ID          objId
    );


    RW_DATETIME_DATA * 
                    RW_DateTime_DeepCopy (
        RW_DATETIME_DATA  
                        *this
    );


    uint32_t        RW_DateTime_Hash(
        RW_DATETIME_DATA 
                        *this
    );

    
    RW_DATETIME_DATA * 
                    RW_DateTime_Init (
        RW_DATETIME_DATA 
                        *this
    );


    RW_DATETIME_DATA * 
                    RW_DateTime_New (
        void
    );
   
 
 #ifdef  RW_DATETIME_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    RW_DATETIME_DATA * 
                    RW_DateTime_ParseJsonObject (
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
    ERESULT         RW_DateTime_ParseJsonFields (
        JSONIN_DATA     *pParser,
        RW_DATETIME_DATA 
                        *pObject
    );
#endif


    void *          RW_DateTime_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  RW_DATETIME_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = RW_DateTime_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     RW_DateTime_ToJson (
        RW_DATETIME_DATA 
                        *this
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
    ERESULT         RW_DateTime_ToJsonFields (
        RW_DATETIME_DATA 
                        *this,
        ASTR_DATA       *pStr
    );
#endif


    ASTR_DATA *     RW_DateTime_ToDebugString (
        RW_DATETIME_DATA 
                        *this,
        int             indent
    );


#ifdef NDEBUG
#else
    bool            RW_DateTime_Validate (
        RW_DATETIME_DATA 
                        *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* RW_DATETIME_INTERNAL_H */

