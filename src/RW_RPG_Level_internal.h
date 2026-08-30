// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
// Report Program Generator (RPG) Level (RW_RPG_Level) Internal Header
//****************************************************************

/* 
 * File:   RW_RPG_Level_internal.h
 *  Generated 05/31/2026 14:28:59
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




#include        <RW_RPG_Level.h>
#ifdef  RW_RPG_LEVEL_SUPER_DEFINED
#include        <obj_internal.h>
#endif
#include        <JsonIn.h>
#include        <Value.h>


#ifndef RW_RPG_LEVEL_INTERNAL_H
#define RW_RPG_LEVEL_INTERNAL_H





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
struct RW_RPG_Level_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
#ifdef  RW_RPG_LEVEL_SUPER_DEFINED
    OBJ_DATA        super;
#else
    OBJ_DATA        super;
#endif
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    uint16_t        level;          // Level Number
    VALUE_DATA      *pOld;
    VALUE_DATA      *pNew;
    int16_t         dataI16;
    int32_t         dataI32;
    int64_t         dataI64;
    OBJ_ID          pObj1;
    OBJ_ID          pObj2;
    ASTR_DATA       *pStr;

#ifdef   RW_RPG_LEVEL_MSGS
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
    struct RW_RPG_Level_class_data_s  
                        RW_RPG_Level_ClassObj;

    extern
    const
    RW_RPG_LEVEL_VTBL   RW_RPG_Level_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  RW_RPG_LEVEL_SINGLETON
    RW_RPG_LEVEL_DATA * 
                    RW_RPG_Level_getSingleton (
        void
    );

    bool            RW_RPG_Level_setSingleton (
     RW_RPG_LEVEL_DATA  *pValue
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

#ifdef  RW_RPG_LEVEL_SUPER_DEFINED
    OBJ_DATA *      RW_RPG_Level_getSuper (
        RW_RPG_LEVEL_DATA 
                        *this
    );
#else
    OBJ_DATA *      RW_RPG_Level_getSuper (
        RW_RPG_LEVEL_DATA 
                        *this
    );
#endif


    OBJ_IUNKNOWN *  RW_RPG_Level_getSuperVtbl (
        RW_RPG_LEVEL_DATA 
                        *this
    );


    ERESULT         RW_RPG_Level_Assign (
        RW_RPG_LEVEL_DATA 
                        *this,
        RW_RPG_LEVEL_DATA 
                        *pOther
    );


    RW_RPG_LEVEL_DATA *       
                    RW_RPG_Level_Copy (
        RW_RPG_LEVEL_DATA 
                        *this
    );


    void            RW_RPG_Level_Dealloc (
        OBJ_ID          objId
    );


    RW_RPG_LEVEL_DATA * 
                    RW_RPG_Level_DeepCopy (
        RW_RPG_LEVEL_DATA  
                        *this
    );


    RW_RPG_LEVEL_DATA * 
                    RW_RPG_Level_Init (
        RW_RPG_LEVEL_DATA 
                        *this
    );


    RW_RPG_LEVEL_DATA * 
                    RW_RPG_Level_New (
        void
    );
   
 
 #ifdef  RW_RPG_LEVEL_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    RW_RPG_LEVEL_DATA * 
                    RW_RPG_Level_ParseJsonObject (
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
    ERESULT         RW_RPG_Level_ParseJsonFields (
        JSONIN_DATA     *pParser,
        RW_RPG_LEVEL_DATA 
                        *pObject
    );
#endif


    void *          RW_RPG_Level_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  RW_RPG_LEVEL_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = RW_RPG_Level_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     RW_RPG_Level_ToJson (
        RW_RPG_LEVEL_DATA 
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
    ERESULT         RW_RPG_Level_ToJsonFields (
        RW_RPG_LEVEL_DATA 
                        *this,
        ASTR_DATA       *pStr
    );
#endif


    ASTR_DATA *     RW_RPG_Level_ToDebugString (
        RW_RPG_LEVEL_DATA 
                        *this,
        int             indent
    );


#ifdef NDEBUG
#else
    bool            RW_RPG_Level_Validate (
        RW_RPG_LEVEL_DATA 
                        *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* RW_RPG_LEVEL_INTERNAL_H */

