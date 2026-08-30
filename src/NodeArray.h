// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//              An Array of Nodes (NodeArray) Header
//****************************************************************

/*
 * Program
 *          An Array of Nodes (NodeArray)
 * Purpose
 *          This object provides an array of node pointers. It
 *          does not store the actual node, just a pointer to
 *          it.
 *
 * Remarks
 *    1.    You can create a Queue of Nodes by using AppendNode()
 *          to add nodes to the queue and DeleteFirst() to
 *          remove nodes from the queue.
 *    2.    You can create a Stack of Nodes by using AppendNode()
 *          to add nodes to the stack and DeleteLast() to
 *          remove nodes from the stack.
 *
 * History
 *  08/08/2015 Generated
 *	01/10/2020 Regenerated
 *  06/21/2026 Regenerated to inherit from Node.
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


/*----------------------------------------------------------------
    The following should be added to the appropriate _defs.h file
    in the _idents_e enum:
        OBJ_IDENT_NODEARRAY,             // An Array of Nodes
        OBJ_IDENT_NODEARRAY_CLASS,
    The following should be added to the appropriate objects.json.txt
    or program.json.txt file:
        {name:"NodeArray",  desc:"An Array of Nodes"},
 *----------------------------------------------------------------*/



//#define   NODEARRAY_IS_IMMUTABLE     1
#define   NODEARRAY_JSON_SUPPORT    1
//#define   NODEARRAY_SINGLETON        1
//#define       NODEARRAY_MSGS         1
#define   NODEARRAY_SUPER_DEFINED   1


#include        <cmn_defs.h>
#include        <AStr.h>
#include        <I32Array.h>
#ifdef  NODEARRAY_SUPER_DEFINED
#include        <Node.h>
#endif


#ifndef         NODEARRAY_H
#define         NODEARRAY_H





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct NodeArray_data_s  NODEARRAY_DATA;          // Inherits from Node
    typedef struct NodeArray_class_data_s NODEARRAY_CLASS_DATA;  // Inherits from obj

    typedef struct NodeArray_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        //Node_VTBL    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in NodeArray_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODEARRAY_DATA *);
    } NODEARRAY_VTBL;

    typedef struct NodeArray_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in NodeArray_object.c.
        // Properties:
        // Methods:
        NODEARRAY_DATA *(*pNew)(void);
        //bool        (*pIsEnabled)(NODEARRAY_DATA *);
    } NODEARRAY_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  NODEARRAY_SINGLETON
    NODEARRAY_DATA * 
                    NodeArray_Shared (
        void
    );

    void            NodeArray_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to NodeArray object if successful, otherwise OBJ_NIL.
     */
    NODEARRAY_DATA * 
                    NodeArray_Alloc (
        void
    );
    
    
    OBJ_ID          NodeArray_Class (
        void
    );
    
    
    NODEARRAY_DATA * 
                    NodeArray_New (
        void
    );
    
    
#ifdef  NODEARRAY_JSON_SUPPORT
    NODEARRAY_DATA * 
                    NodeArray_NewFromJsonString (
        ASTR_DATA       *pString
    );

    NODEARRAY_DATA * 
                    NodeArray_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    /*! @property   Compare
        comparess 2 nodes for equality. This is needed for any method
        using comparison because the node may be a specific type that
        inherited from Node but with differing comparison needs than
        the default Node comparison. This routine will have to take
        that into consideration.
     */
    bool            NodeArray_setCompare (
        NODEARRAY_DATA  *this,
        int             (*pCompare)(NODE_DATA *,NODE_DATA *)
    );


#ifdef NODEARRAY_MSGS
    /*! @property   Messages
        Allows information and warning messages to be issued.
     */
    bool            NodeArray_setMsgs (
        NODEARRAY_DATA  *this,
        void            (*pMsgInfo)(OBJ_ID, const char *, ...),
        void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...),
        OBJ_ID          pObj
    );
#endif


    /*!
     @property other to be used to associate some other object to
     this array as needed.
     */
    OBJ_ID          NodeArray_getOther (
        NODEARRAY_DATA  *this
    );

    bool            NodeArray_setOther (
        NODEARRAY_DATA  *this,
        OBJ_ID          pValue
    );


    /*!
     @property size is the number of Nodes in the Array.
     */
    uint32_t        NodeArray_getSize (
        NODEARRAY_DATA    *this
    );


#ifdef  NODEARRAY_SUPER_DEFINED
    NODE_DATA *     NodeArray_getSuper (
        NODEARRAY_DATA  *this
    );
#else
    OBJ_DATA *      NodeArray_getSuper (
        NODEARRAY_DATA  *this
    );
#endif


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         NodeArray_AddToTop (
        NODEARRAY_DATA  *this,
        NODE_DATA       *pObject,
        uint32_t        *pIndex
    );


    /*!
     Append the contents of the other array to this array. This is
     the same as AddToTop() of each element of the other array.
     @return    If successful, return ERESULT_SUCCESSFUL_COMPLETION
                otherwise an eResult error code.
     */
    ERESULT         NodeArray_Append (
        NODEARRAY_DATA  *this,
        NODEARRAY_DATA  *pOther
    );

    ERESULT         NodeArray_AppendNode (
        NODEARRAY_DATA  *this,
        NODE_DATA       *pObject,
        uint32_t        *pIndex
    );


    /*!
     Assign the contents of this array to the other array. The
     contents of the other array are released. Then we simply
     retain them so that they are in both arrays.
     @return    If successful, return ERESULT_SUCCESSFUL_COMPLETION
                otherwise an eResult error code.
     */
    ERESULT         NodeArray_Assign (
        NODEARRAY_DATA    *this,
        NODEARRAY_DATA    *pOther
    );


    /*!
     Copy this array. Any element of the array that has a copy method
     will have that used to create a new object. Otherwise, the object
     is just retained and added to the new array.
     @return    If successful, return a new array that must be released
                 otherwise return OBJ_NIL.
     */
    NODEARRAY_DATA * NodeArray_Copy (
        NODEARRAY_DATA  *this
    );


    NODEARRAY_DATA * NodeArray_DeepCopy (
        NODEARRAY_DATA  *this
    );


    /*!
     Remove the index'th element from the array and return it.
     @return    If successful, an object pointer, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    NODE_DATA *     NodeArray_Delete (
        NODEARRAY_DATA  *this,
        uint32_t        index
    );


    /*! Return the top element after deleting it from the array,
        but not releasing it. It needs to be released before it is
        discarded.
     @param     this    Object Pointer
     */
    NODE_DATA *     NodeArray_DeleteFirst (
        NODEARRAY_DATA  *this
    );


    // DeleteFromTop() returns the top element after deleting it,
    // but not releasing it. It needs to be released before it is
    // discarded.
    NODE_DATA *     NodeArray_DeleteLast (
        NODEARRAY_DATA  *this
    );


    /*! Create an enumerator for the array.
     @param     this    Object Pointer
     @return    If successful, an ENUM object is returned.  Otherwise,
                 OBJ_NIL.
     @warning   Remember to release the returned ENUM object.
     */
    NODEENUM_DATA * NodeArray_Enum (
        NODEARRAY_DATA  *this
    );


    /*!
     Expand the array to minimum size provided.  Array expansion is done
     by a power of 2 (ie 2, 4, 8, 16, 32, 64, 128, 256, 512, ...). The
     added space is zeroed. The array is expanded, but the usage count
     (ie size) is not affected.
     @param     this    Object Pointer
     @param     min     minimum number of array elements needed
     @return:   If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error.
     */
    ERESULT         NodeArray_Expand (
        NODEARRAY_DATA  *this,
        uint32_t        min
    );


    /*!
     Find the first occurrence of a node in the array by name.
     @param     this    Object Pointer
     @return    If successful, ERESULT_SUCCESS is returned and
                ppNode will contain the node ptr otherwise an error code
                will be returned.
     */
    NODE_DATA *     NodeArray_Find (
        NODEARRAY_DATA  *this,
        NODE_DATA       *pNode
    );

    NODE_DATA *     NodeArray_FindA (
        NODEARRAY_DATA  *this,
        int32_t         cls,
        const
        char             *pName
    );


    /*!
     Scan the array applying the given routine to each member of the
     array.  Second parameter to the Scan routine is the actual node
     address. Halt the scan if an error return code is returned
     by the scan routine.
     @param     this    Object Pointer
     @param     pScan   Scan Routine Address
     @param     pObj    First Parameter for the Scan Routine (optional)
     @param     pArg3   Third Parameter for the Scan Routine (optional)
     @return:   If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error.
     */
    ERESULT         NodeArray_ForEach (
        NODEARRAY_DATA  *this,
        P_ERESULT_EXIT3 pScan,         // ERESULT pScan(pObj, pNode, pArg3) return ERESULT_SUCCESS to continue
                                       // and any ERESULT_* error to abort scan.
        OBJ_ID          pObj,          // Used as first parameter of scan method
        void            *pArg3
    );


    NODE_DATA *     NodeArray_Get (
        NODEARRAY_DATA  *this,
        uint32_t        index       // Relative to 1
    );

    NODE_DATA *     NodeArray_GetFirst (
        NODEARRAY_DATA  *this
    );

    NODE_DATA *     NodeArray_GetLast (
        NODEARRAY_DATA  *this
    );


    NODEARRAY_DATA * 
                    NodeArray_Init (
        NODEARRAY_DATA  *this
    );


    /*!
     Add the given node after the index'th node of the array.
     @param     this    object pointer
     @param     index   range is 0 to Size. If 0, then object is added before
                        the first object in the array.
     @return    If successful, ERESULT_SUCCESS, otherwise an ERESULT_*
                error.
     */
    ERESULT         NodeArray_InsertAfter (
        NODEARRAY_DATA  *this,
        uint32_t        index,
        NODE_DATA       *pObject
    );


    /*!
     Delete the last object from the array and return it.
     @param     this    object pointer
     @return    If successful, last Node of the array, otherwise OBJ_NIL.
     */
    NODE_DATA *      NodeArray_Pop (
        NODEARRAY_DATA   *this
    );


    /*!
     Add the given node to the end of the array.
     @param     this    object pointer
     @param     pNode object pointer to be pushed
     @return    If successful, ERESULT_SUCCESS, otherwise an ERESULT_*
                error.
     */
    ERESULT         NodeArray_Push (
        NODEARRAY_DATA   *this,
        NODE_DATA        *pNode
    );


    ERESULT         NodeArray_Put (
        NODEARRAY_DATA  *this,
        uint32_t        index,
        NODE_DATA       *pObject
    );


    /*!
     Reverse the order of the array.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         NodeArray_Reverse (
        NODEARRAY_DATA  *this
    );


    /*!
     Sort the array using the Compare() method of the node.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         NodeArray_SortAscending (
        NODEARRAY_DATA    *this
    );


    /*!
     Create an new int32_t array of the classes from all nodes in this array.
     The relative position of each class in the new array should coincide with
     the relative position of the node in this array.
     @return    If successful, an i32Array object which must be released,
                otherwise OBJ_NIL.
     @warning   Remember to release the returned i32Array object.
     */
    I32ARRAY_DATA * NodeArray_ToClassArray (
        NODEARRAY_DATA  *this
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
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = NodeArray_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     NodeArray_ToDebugString (
        NODEARRAY_DATA  *this,
        int             indent
    );
    
    ASTR_DATA *     NodeArray_ToString(
        NODEARRAY_DATA  *this
    );


    /*!
     Visit each node of the array in ascending index order.  Terminate
     the visiting is an ERESULT_* error code is returned by the visitor.
     @return    If successful, ERESULT_SUCCESS is returned,
                otherwise an ERESULT_* error code.
     */
    ERESULT         NodeArray_VisitAscending(
        NODEARRAY_DATA    *this,
        ERESULT         (pVisitor)(
                                   OBJ_ID,             // Object supplied below
                                   NODE_DATA *         // Current Node
                        ),
        OBJ_ID          pObject
    );
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* NODEARRAY_H */

