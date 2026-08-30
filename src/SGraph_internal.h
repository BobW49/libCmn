// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//              A Simple Graph (SGraph) Internal Header
//****************************************************************

/* 
 * File:   SGraph_internal.h
 *  Generated 10/21/2022 02:32:39
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




#include        <SGraph.h>
#ifdef  SGRAPH_SUPER_DEFINED
#include        <obj_internal.h>
#endif
#include        <JsonIn.h>


#ifndef SGRAPH_INTERNAL_H
#define SGRAPH_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------


#if !defined(__arm64__)
#pragma pack(push, 1)
#endif
struct SGraph_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
#ifdef  SGRAPH_SUPER_DEFINED
    OBJ_DATA  super;
#else
    OBJ_DATA        super;
#endif
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    ASTR_DATA       *pStr;
    BITMATRIX_DATA  *pEdges;
    NODEARRAY_DATA  *pNodes;
    uint16_t        size;           // maximum number of elements
    uint16_t        rsvd16;

#ifdef   SGRAPH_MSGS
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
    struct SGraph_class_data_s  SGraph_ClassObj;

    extern
    const
    SGRAPH_VTBL         SGraph_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  SGRAPH_SINGLETON
    SGRAPH_DATA *     SGraph_getSingleton (
        void
    );

    bool            SGraph_setSingleton (
     SGRAPH_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  SGRAPH_SUPER_DEFINED
    OBJ_DATA *  SGraph_getSuper (
        SGRAPH_DATA     *this
    );
#else
    OBJ_DATA *  SGraph_getSuper (
        SGRAPH_DATA     *this
    );
#endif


    OBJ_IUNKNOWN *  SGraph_getSuperVtbl (
        SGRAPH_DATA     *this
    );


    ERESULT         SGraph_Assign (
        SGRAPH_DATA    *this,
        SGRAPH_DATA    *pOther
    );


    SGRAPH_DATA *       SGraph_Copy (
        SGRAPH_DATA     *this
    );


    void            SGraph_Dealloc (
        OBJ_ID          objId
    );


    SGRAPH_DATA *     SGraph_DeepCopy (
        SGRAPH_DATA       *this
    );


#ifdef  SGRAPH_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    SGRAPH_DATA *       SGraph_ParseJsonObject (
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
    ERESULT         SGraph_ParseJsonFields (
        JSONIN_DATA     *pParser,
        SGRAPH_DATA     *pObject
    );
#endif


    void *          SGraph_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  SGRAPH_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = SGraph_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     SGraph_ToJson (
        SGRAPH_DATA      *this
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
    ERESULT         SGraph_ToJsonFields (
        SGRAPH_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool            SGraph_Validate (
        SGRAPH_DATA       *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* SGRAPH_INTERNAL_H */

