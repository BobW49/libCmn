// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  NodeTree Node/Entry (TreeNode) Header
//****************************************************************
/*
 * Program
 *          NodeTree Node/Entry (TreeNode)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate TreeNode to run things without complications
 *          of interfering with the main TreeNode. A TreeNode may be 
 *          called a TreeNode on other O/S's.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  06/18/2022 Generated
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





//#define   TREENODE_IS_IMMUTABLE     1
//#define   TREENODE_JSON_SUPPORT     1
//#define   TREENODE_SINGLETON        1
//#define       TREENODE_MSGS   1
//#define   TREENODE_SUPER_DEFINED     1


#include        <cmn_defs.h>
#include        <AStr.h>
#ifdef  TREENODE_SUPER_DEFINED
#include        <obj.h>
#endif


#ifndef         TREENODE_H
#define         TREENODE_H





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct TreeNode_data_s  TREENODE_DATA;          // Inherits from obj
    typedef struct TreeNode_class_data_s TREENODE_CLASS_DATA;  // Inherits from obj

    typedef struct TreeNode_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        //obj_VTBL    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in TreeNode_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(TREENODE_DATA *);
    } TREENODE_VTBL;

    typedef struct TreeNode_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in TreeNode_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(TREENODE_DATA *);
    } TREENODE_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  TREENODE_SINGLETON
    TREENODE_DATA * TreeNode_Shared (
        void
    );

    void            TreeNode_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to TreeNode object if successful, otherwise OBJ_NIL.
     */
    TREENODE_DATA * TreeNode_Alloc (
        void
    );
    
    
    OBJ_ID          TreeNode_Class (
        void
    );
    
    
    TREENODE_DATA * TreeNode_New (
        void
    );
    
    
#ifdef  TREENODE_JSON_SUPPORT
    TREENODE_DATA * TreeNode_NewFromJsonString (
        ASTR_DATA       *pString
    );

    TREENODE_DATA * TreeNode_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

#ifdef TREENODE_MSGS
    /*! @property   Messages
        Allows information and warning messages to be issued.
     */
    bool            TreeNode_setMsgs (
        TREENODE_DATA    *this,
        void            (*pMsgInfo)(OBJ_ID, const char *, ...),
        void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...),
        OBJ_ID          pObj
    );
#endif


    /*! @property   Parent
        Pointer to Parent's Tree Node.
        Note: this pointer is not owned.
     */
    TREENODE_DATA * TreeNode_getParent (
        TREENODE_DATA   *this
    );

    bool            TreeNode_setParent (
        TREENODE_DATA   *this,
        TREENODE_DATA   *pValue
    );


    OBJ_DATA *  TreeNode_getSuper (
        TREENODE_DATA     *this
    );


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT     TreeNode_Disable (
        TREENODE_DATA       *this
    );


    ERESULT     TreeNode_Enable (
        TREENODE_DATA       *this
    );

   
    TREENODE_DATA *   TreeNode_Init (
        TREENODE_DATA     *this
    );


    ERESULT     TreeNode_IsEnabled (
        TREENODE_DATA       *this
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
        TREENODE_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = TreeNode_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     TreeNode_ToDebugString (
        TREENODE_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* TREENODE_H */

