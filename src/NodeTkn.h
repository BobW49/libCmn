// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//              Node based on a Token (NodeTkn) Header
//****************************************************************

/*
 * Program
 *          Node based on a Token (NodeTkn)
 * Purpose
 *          This object provides a Node with Source Token information.
 *          It is meant to be used by any of the Node groupings
 *          and TreeExpr.
 *
 *          Additionally, it has the ability to retain its index
 *          within that grouping. The way enumerations can provide
 *          fast access back the node within the grouping. Only one
 *          index is provided. So, it should be used by the controlling
 *          grouping.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  01/27/2023 Generated
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
        OBJ_IDENT_NODETKN,         //  Node based on a Token
        OBJ_IDENT_NODETKN_CLASS,
    The following should be added to the appropriate objects.json.txt
    or program.json.txt file:
        {name:"NodeTkn",  desc:"Node based on a Token"},
 *----------------------------------------------------------------*/



//#define   NODETKN_IS_IMMUTABLE     1
//#define   NODETKN_JSON_SUPPORT     1
//#define   NODETKN_SINGLETON        1
//#define       NODETKN_MSGS   1
#define   NODETKN_SUPER_DEFINED   1


#include        <cmn_defs.h>
#include        <AStr.h>
#ifdef  NODETKN_SUPER_DEFINED
#include        <Node.h>
#endif
#include        <Token.h>


#ifndef         NODETKN_H
#define         NODETKN_H





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct NodeTkn_data_s  NODETKN_DATA;          // Inherits from Node
    typedef struct NodeTkn_class_data_s NODETKN_CLASS_DATA;  // Inherits from obj

    typedef struct NodeTkn_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        //Node_VTBL    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in NodeTkn_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODETKN_DATA *);
    } NODETKN_VTBL;

    typedef struct NodeTkn_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in NodeTkn_object.c.
        // Properties:
        // Methods:
        NODETKN_DATA *(*pNew)(void);
        //bool        (*pIsEnabled)(NODETKN_DATA *);
    } NODETKN_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  NODETKN_SINGLETON
    NODETKN_DATA *  NodeTkn_Shared (
        void
    );

    void            NodeTkn_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to NodeTkn object if successful, otherwise OBJ_NIL.
     */
    NODETKN_DATA *  NodeTkn_Alloc (
        void
    );
    
    
    OBJ_ID          NodeTkn_Class (
        void
    );
    
    
    NODETKN_DATA *  NodeTkn_New (
        void
    );
    
    
    NODETKN_DATA *  NodeTkn_NewFromToken (
        TOKEN_DATA     *pToken
    );


    NODETKN_DATA *  NodeTkn_NewFromTokenFields (
        TOKEN_FIELDS    *pTF
    );


#ifdef  NODETKN_JSON_SUPPORT
    NODETKN_DATA *   NodeTkn_NewFromJsonString (
        ASTR_DATA       *pString
    );

    NODETKN_DATA *   NodeTkn_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    /*! @property Class
     Is used to categorize the Node with some kind of identification
     if needed.
     */
    int32_t         NodeTkn_getClass (
        NODETKN_DATA    *this
    );

    bool            NodeTkn_setClass (
        NODETKN_DATA    *this,
        int32_t         value
    );


    /*! @property   Index
        Is integer index within a controlling Array, Graph, Tree, etc.
     */
    int32_t         NodeTkn_getIndex (
        NODETKN_DATA    *this
    );

    bool            NodeTkn_setIndex (
        NODETKN_DATA    *this,
        int32_t         value
    );


#ifdef NODETKN_MSGS
    /*! @property   Messages
        Allows information and warning messages to be issued.
     */
    bool            NodeTkn_setMsgs (
        NODETKN_DATA    *this,
        void            (*pMsgInfo)(OBJ_ID, const char *, ...),
        void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...),
        OBJ_ID          pObj
    );
#endif


#ifdef  NODETKN_SUPER_DEFINED
    NODE_DATA *     NodeTkn_getSuper (
        NODETKN_DATA    *this
    );
#else
    OBJ_DATA *      NodeTkn_getSuper (
        NODETKN_DATA    *this
    );
#endif


    /*! @property   Token
        Is the information provided by a Source Token.
     */
    TOKEN_FIELDS *  NodeTkn_getToken (
        NODETKN_DATA    *this
    );

    bool            NodeTkn_setToken (
        NODETKN_DATA    *this,
        TOKEN_FIELDS    *pValue
    );



    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         NodeTkn_Disable (
        NODETKN_DATA       *this
    );


    ERESULT         NodeTkn_Enable (
        NODETKN_DATA       *this
    );

   
    NODETKN_DATA *     NodeTkn_Init (
        NODETKN_DATA       *this
    );


    bool                NodeTkn_IsEnabled (
        NODETKN_DATA       *this
    );
    
 
#ifdef  NODETKN_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = NodeTkn_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     NodeTkn_ToJson (
        NODETKN_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = NodeTkn_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     NodeTkn_ToDebugString (
        NODETKN_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* NODETKN_H */

