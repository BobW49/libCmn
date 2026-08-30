// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   TreeNode_internal.h
 *  Generated 06/18/2022 09:52:39
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




#include        <TreeNode.h>
#ifdef  TREENODE_SUPER_DEFINED
#include        <obj_internal.h>
#endif
#include        <JsonIn.h>


#ifndef TREENODE_INTERNAL_H
#define TREENODE_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct TreeNode_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
#ifdef  TREENODE_SUPER_DEFINED
    OBJ_DATA        super;
#else
    OBJ_DATA        super;
#endif
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    ASTR_DATA       *pStr;
    TREENODE_DATA   *pParent;

#ifdef   TREENODE_MSGS
    // Informational and Warning Log Messages
    void            (*pMsgInfo)(OBJ_ID, const char *, ...);
    void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...);
    OBJ_ID          pMsgObj;
#endif
};
#pragma pack(pop)

    extern
    struct TreeNode_class_data_s  TreeNode_ClassObj;

    extern
    const
    TREENODE_VTBL         TreeNode_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  TREENODE_SINGLETON
    TREENODE_DATA *     TreeNode_getSingleton (
        void
    );

    bool            TreeNode_setSingleton (
     TREENODE_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  TREENODE_SUPER_DEFINED
    OBJ_DATA *  TreeNode_getSuper (
        TREENODE_DATA     *this
    );
#else
    OBJ_DATA *  TreeNode_getSuper (
        TREENODE_DATA     *this
    );
#endif


    OBJ_IUNKNOWN *  TreeNode_getSuperVtbl (
        TREENODE_DATA     *this
    );


    ERESULT         TreeNode_Assign (
        TREENODE_DATA    *this,
        TREENODE_DATA    *pOther
    );


    TREENODE_DATA *       TreeNode_Copy (
        TREENODE_DATA     *this
    );


    void            TreeNode_Dealloc (
        OBJ_ID          objId
    );


    TREENODE_DATA *     TreeNode_DeepCopy (
        TREENODE_DATA       *this
    );


#ifdef  TREENODE_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    TREENODE_DATA *       TreeNode_ParseJsonObject (
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
    ERESULT         TreeNode_ParseJsonFields (
        JSONIN_DATA     *pParser,
        TREENODE_DATA     *pObject
    );
#endif


    void *          TreeNode_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  TREENODE_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = TreeNode_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     TreeNode_ToJson (
        TREENODE_DATA      *this
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
    ERESULT         TreeNode_ToJsonFields (
        TREENODE_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool            TreeNode_Validate (
        TREENODE_DATA       *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* TREENODE_INTERNAL_H */

