// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//              A Simple Graph (SGraph) Header
//****************************************************************

/*
 * Program
 *          A Simple Graph (SGraph)
 * Purpose
 *          A Simple Graph is one in which there is no additional
 *          information for edges other than one exists. There is
 *          no edge count or weighting. However, the nodes can be
 *          be expanded to contain any information needed. The best
 *          usage for this graph system is for things like grammar
 *          relationships, code flows, etc. that do not require
 *          extra information for edges.
 *
 *          The graph relationship between nodes is kept in the
 *          BitMatrix.
 * Remarks
 *  1.      None
 *
 * History
 *  10/21/2022 Generated
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
        OBJ_IDENT_SGRAPH,         //  A Simple Graph
        OBJ_IDENT_SGRAPH_CLASS,
    The following should be added to the appropriate objects.json.txt
    or program.json.txt file:
        {name:"SGraph",  desc:"A Simple Graph"},
 *----------------------------------------------------------------*/



//#define   SGRAPH_IS_IMMUTABLE     1
//#define   SGRAPH_JSON_SUPPORT     1
//#define   SGRAPH_SINGLETON        1
//#define       SGRAPH_MSGS   1
//#define   SGRAPH_SUPER_DEFINED     1


#include        <cmn_defs.h>
#include        <AStr.h>
#ifdef  SGRAPH_SUPER_DEFINED
#include        <obj.h>
#endif
#include        <BitMatrix.h>
#include        <BitSet.h>
#include        <NodeArray.h>


#ifndef         SGRAPH_H
#define         SGRAPH_H





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct SGraph_data_s  SGRAPH_DATA;          // Inherits from obj
    typedef struct SGraph_class_data_s SGRAPH_CLASS_DATA;  // Inherits from obj

    typedef struct SGraph_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        //obj_VTBL    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in SGraph_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SGRAPH_DATA *);
    } SGRAPH_VTBL;

    typedef struct SGraph_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in SGraph_object.c.
        // Properties:
        // Methods:
        SGRAPH_DATA *(*pNew)(void);
        //bool        (*pIsEnabled)(SGRAPH_DATA *);
    } SGRAPH_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  SGRAPH_SINGLETON
    SGRAPH_DATA *     SGraph_Shared (
        void
    );

    void            SGraph_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to SGraph object if successful, otherwise OBJ_NIL.
     */
    SGRAPH_DATA *   SGraph_Alloc (
        void
    );
    
    
    OBJ_ID          SGraph_Class (
        void
    );
    
    
    SGRAPH_DATA *   SGraph_New (
        void
    );
    
    
#ifdef  SGRAPH_JSON_SUPPORT
    SGRAPH_DATA *   SGraph_NewFromJsonString (
        ASTR_DATA       *pString
    );

    SGRAPH_DATA *   SGraph_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    BITMATRIX_DATA * SGraph_getEdges(
        SGRAPH_DATA     *this
    );

    bool            SGraph_setEdges(
        SGRAPH_DATA     *this,
        BITMATRIX_DATA  *pValue
    );


    NODEARRAY_DATA * SGraph_getNodes(
        SGRAPH_DATA     *this
    );

    bool            SGraph_setNodes(
        SGRAPH_DATA     *this,
        NODEARRAY_DATA  *pValue
    );


#ifdef SGRAPH_MSGS
    /*! @property   Messages
        Allows information and warning messages to be issued.
     */
    bool            SGraph_setMsgs (
        SGRAPH_DATA     *this,
        void            (*pMsgInfo)(OBJ_ID, const char *, ...),
        void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...),
        OBJ_ID          pObj
    );
#endif


#ifdef  SGRAPH_SUPER_DEFINED
    OBJ_DATA *      SGraph_getSuper (
        SGRAPH_DATA     *this
    );
#else
    OBJ_DATA *      SGraph_getSuper (
        SGRAPH_DATA     *this
    );
#endif


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    uint32_t        SGraph_Degree(
        SGRAPH_DATA     *this,
        uint32_t        n
    );


    /*!
     Add an edge to the graph.
     @param     this    object pointer
     @param     from    From Node number (relative to 1)
     @param     to      To Node number  (relative to 1)
     @return    If successful, ERESULT_SUCCESS.  Otherwise,
                an ERESULT_* error code.
     */
    ERESULT         SGraph_EdgeAdd(
        SGRAPH_DATA     *this,
        uint32_t        from,
        uint32_t        to
    );


    ERESULT         SGraph_EdgeDelete(
        SGRAPH_DATA     *this,
        uint32_t        from,
        uint32_t        to
    );


    /*!
     Check to see if an edge exists in the graph.
     @param     this    object pointer
     @param     from    From Node number (relative to 1)
     @param     to      To Node number  (relative to 1)
     @return    If it exists, true.  Otherwise, false.
     */
    bool            SGraph_EdgeExists(
        SGRAPH_DATA     *this,
        uint32_t        from,
        uint32_t        to
    );


    SGRAPH_DATA *   SGraph_Init (
        SGRAPH_DATA     *this
    );


    NODE_DATA *     SGraph_Node(
        SGRAPH_DATA     *this,
        uint32_t        n
    );


    /*!
     Add a node to the graph.
     @param     this    object pointer
     @param     pNode   Node object pointer to be added
     @return    If successful, a unique number that identifies the node
     in the graph.  Otherwise, zero.
     */
    uint32_t        SGraph_NodeAdd(
        SGRAPH_DATA     *this,
        NODE_DATA       *pNode
    );


    /*!
     Calculate the set of nodes that are successors or predecessors of the
     given node in the graph.
     @param     this    object pointer
     @param     n       Node number (relative to 1)
     @return    If successful, an array of node numbers which are members of
                the set. Otherwise, OBJ_NIL.
     */
    U32ARRAY_DATA *  SGraph_NodeAdj(
        SGRAPH_DATA     *this,
        uint32_t        n
    );


    /*!
     Calculate the number of nodes that are successors or predecessors of the
     given node in the graph.  This is basically the size of the set calculated
     by NodeAdj().
     @param     this    object pointer
     @param     n       Node number (relative to 1)
     @return    If successful, an integer which is the size of the set.
     */
    uint32_t         SGraph_NodeDegree(
        SGRAPH_DATA     *this,
        uint32_t        n
    );


    /*!
     Calculate the set of nodes that are predecessors of the given node in
     the graph.
     @param     this    object pointer
     @param     n       Node number (relative to 1)
     @return    If successful, an array of node numbers which are members of
                the set. Otherwise, OBJ_NIL.
     */
    U32ARRAY_DATA *  SGraph_NodePred(
        SGRAPH_DATA     *this,
        uint32_t        n
    );


    /*!
     Calculate the set of nodes that are successors of the given node in
     the graph.
     @param     this    object pointer
     @param     n       Node number (relative to 1)
     @return    If successful, an array of node numbers which are members of
     the set. Otherwise, OBJ_NIL.
     */
    U32ARRAY_DATA *  SGraph_NodeSucc(
        SGRAPH_DATA     *this,
        uint32_t        n
    );


    /*!
     Calculatte the Reflective Transitive Closure of the Graph.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         SGraph_ReflectiveTransitiveClosure (
        SGRAPH_DATA     *this
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
        SGRAPH_DATA     *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = SGraph_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     SGraph_ToDebugString (
        SGRAPH_DATA     *this,
        int             indent
    );
    
    
    /*!
     Calculatte the Transitive Closure of the Graph.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         SGraph_TransitiveClosure (
        SGRAPH_DATA       *this
    );



    
#ifdef  __cplusplus
}
#endif

#endif  /* SGRAPH_H */

