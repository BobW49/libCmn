// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//              Base for All Objects (ObjBase) Internal Header
//****************************************************************

/* 
 * File:   ObjBase_internal.h
 *  Generated 02/24/2025 10:18:39
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




#include        <ObjBase.h>
#ifdef  OBJBASE_SUPER_DEFINED
#include        <obj_internal.h>
#endif
#include        <JsonIn.h>


#ifndef OBJBASE_INTERNAL_H
#define OBJBASE_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif



    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------


    extern
    struct ObjBase_class_data_s  
                        ObjBase_ClassObj;

    extern
    const
    OBJBASE_VTBL        ObjBase_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  OBJBASE_SINGLETON
    OBJBASE_DATA *  ObjBase_getSingleton (
        void
    );

    bool            ObjBase_setSingleton (
     OBJBASE_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJBASE_DATA *  ObjBase_getSuper (
        OBJBASE_DATA    *this
    );


    const
    OBJ_IUNKNOWN *  ObjBase_getSuperVtbl (
        OBJBASE_DATA    *this
    );


    ERESULT         ObjBase_Assign (
        OBJBASE_DATA    *this,
        OBJBASE_DATA    *pOther
    );


    OBJBASE_DATA *       
                    ObjBase_Copy (
        OBJBASE_DATA    *this
    );


    void            ObjBase_Dealloc (
        OBJ_ID          objId
    );


    OBJBASE_DATA *  ObjBase_DeepCopy (
        OBJBASE_DATA    *this
    );


    OBJBASE_DATA *  ObjBase_Init (
        OBJBASE_DATA    *this
    );


    OBJBASE_DATA *  ObjBase_New (
        void
    );
   
 
 #ifdef  OBJBASE_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    OBJBASE_DATA *  ObjBase_ParseJsonObject (
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
    ERESULT         ObjBase_ParseJsonFields (
        JSONIN_DATA     *pParser,
        OBJBASE_DATA    *pObject
    );
#endif


    void *          ObjBase_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  OBJBASE_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = ObjBase_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     ObjBase_ToJson (
        OBJBASE_DATA    *this
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
    ERESULT         ObjBase_ToJsonFields (
        OBJBASE_DATA    *this,
        ASTR_DATA       *pStr
    );
#endif


    ASTR_DATA *     ObjBase_ToDebugString (
        OBJBASE_DATA    *this,
        int             indent
    );


#ifdef NDEBUG
#else
    bool            ObjBase_Validate (
        OBJBASE_DATA    *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* OBJBASE_INTERNAL_H */

