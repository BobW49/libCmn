// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   Cmds_internal.h
 *  Generated 08/30/2022 00:22:12
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




#include        <Cmds.h>
#ifdef  CMDS_SUPER_DEFINED
#include        <obj_internal.h>
#endif
#include        <JsonIn.h>
#include        <NodeArray.h>


#ifndef CMDS_INTERNAL_H
#define CMDS_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif


    typedef struct Cmds_cmd_s    {
        char            *pLongName;         // command long name (optional, may be NULL)
        W32CHR_T        shortName;          // command short name (optional, may be '\0')
        OBJ_ID          classObj;           // Class Object must have New() as first entry of VTBL.
        //                                  // Created object must inherit from Cmd and support its
        //                                  // VTBL.
    } CMDS_CMD;




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#if !defined(__arm64__)
#pragma pack(push, 1)
#endif
struct Cmds_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
#ifdef  CMDS_SUPER_DEFINED
    OBJ_DATA        super;
#else
    OBJ_DATA        super;
#endif
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    ASTR_DATA       *pStr;
    uint16_t        size;           // maximum number of elements
    uint8_t         fSort;
    uint8_t         rsvd8;
    NODEARRAY_DATA  *pCmds;

    NODELIST_DATA   *pCompleted;    // Completed Command Stack
    OBJ_ID          pMisc;
    
#ifdef   CMDS_MSGS
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
    struct Cmds_class_data_s  Cmds_ClassObj;

    extern
    const
    CMDS_VTBL         Cmds_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  CMDS_SINGLETON
    CMDS_DATA *     Cmds_getSingleton (
        void
    );

    bool            Cmds_setSingleton (
     CMDS_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  CMDS_SUPER_DEFINED
    OBJ_DATA *  Cmds_getSuper (
        CMDS_DATA     *this
    );
#else
    OBJ_DATA *  Cmds_getSuper (
        CMDS_DATA     *this
    );
#endif


    OBJ_IUNKNOWN *  Cmds_getSuperVtbl (
        CMDS_DATA     *this
    );


    ERESULT         Cmds_Assign (
        CMDS_DATA    *this,
        CMDS_DATA    *pOther
    );


    CMDS_DATA *       Cmds_Copy (
        CMDS_DATA     *this
    );


    void            Cmds_Dealloc (
        OBJ_ID          objId
    );


    CMDS_DATA *     Cmds_DeepCopy (
        CMDS_DATA       *this
    );


#ifdef  CMDS_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    CMDS_DATA *       Cmds_ParseJsonObject (
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
    ERESULT         Cmds_ParseJsonFields (
        JSONIN_DATA     *pParser,
        CMDS_DATA     *pObject
    );
#endif


    void *          Cmds_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  CMDS_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Cmds_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Cmds_ToJson (
        CMDS_DATA      *this
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
    ERESULT         Cmds_ToJsonFields (
        CMDS_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool            Cmds_Validate (
        CMDS_DATA       *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* CMDS_INTERNAL_H */

