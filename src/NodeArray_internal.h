// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//              An Array of Nodes (NodeArray) Internal Header
//****************************************************************

/* 
 * File:   NodeArray_internal.h
 *  Generated 06/21/2026 10:23:02
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




#include        <NodeArray.h>
#ifdef  NODEARRAY_SUPER_DEFINED
#include        <Node_internal.h>
#endif
#include        <JsonIn.h>
#include        <ObjArray.h>


#ifndef NODEARRAY_INTERNAL_H
#define NODEARRAY_INTERNAL_H





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
struct NodeArray_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
#ifdef  NODEARRAY_SUPER_DEFINED
    NODE_DATA       super;
#else
    OBJ_DATA        super;
#endif
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    OBJARRAY_DATA   *pArray;
    int             (*pCompare)(NODE_DATA *,NODE_DATA *);
    /*  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
        We need pCompare because the nodes in an array might be of 
        differing types which all inherit from Node. In that case, 
        each type may use a compare method based on its specific type.
        +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ */

#ifdef   NODEARRAY_MSGS
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
    struct NodeArray_class_data_s  
                        NodeArray_ClassObj;

    extern
    const
    NODEARRAY_VTBL      NodeArray_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  NODEARRAY_SINGLETON
    NODEARRAY_DATA * 
                    NodeArray_getSingleton (
        void
    );

    bool            NodeArray_setSingleton (
     NODEARRAY_DATA     *pValue
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

#ifdef  NODEARRAY_SUPER_DEFINED
    NODE_DATA *     NodeArray_getSuper (
        NODEARRAY_DATA  *this
    );
#else
    OBJ_DATA *      NodeArray_getSuper (
        NODEARRAY_DATA  *this
    );
#endif


    OBJ_IUNKNOWN *  NodeArray_getSuperVtbl (
        NODEARRAY_DATA  *this
    );


    ERESULT         NodeArray_Assign (
        NODEARRAY_DATA  *this,
        NODEARRAY_DATA  *pOther
    );


    NODEARRAY_DATA *       
                    NodeArray_Copy (
        NODEARRAY_DATA  *this
    );


    void            NodeArray_Dealloc (
        OBJ_ID          objId
    );


    NODEARRAY_DATA * 
                    NodeArray_DeepCopy (
        NODEARRAY_DATA  *this
    );


    NODEARRAY_DATA * 
                    NodeArray_Init (
        NODEARRAY_DATA  *this
    );


    NODEARRAY_DATA * 
                    NodeArray_New (
        void
    );
   
 
 #ifdef  NODEARRAY_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    NODEARRAY_DATA * 
                    NodeArray_ParseJsonObject (
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
    ERESULT         NodeArray_ParseJsonFields (
        JSONIN_DATA     *pParser,
        NODEARRAY_DATA  *pObject
    );
#endif


    void *          NodeArray_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  NODEARRAY_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = NodeArray_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     NodeArray_ToJson (
        NODEARRAY_DATA  *this
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
    ERESULT         NodeArray_ToJsonFields (
        NODEARRAY_DATA  *this,
        ASTR_DATA       *pStr
    );
#endif


    ASTR_DATA *     NodeArray_ToDebugString (
        NODEARRAY_DATA  *this,
        int             indent
    );


#ifdef NDEBUG
#else
    bool            NodeArray_Validate (
        NODEARRAY_DATA  *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* NODEARRAY_INTERNAL_H */

