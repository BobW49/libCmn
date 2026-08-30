// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//              Abstract Syntax Tree (Ast) Header
//****************************************************************

/*
 * Program
 *          Abstract Syntax Tree (Ast)
 * Purpose
 *          This object provides support for a memory-based
 *          Abstract Syntax Tree (Ast) with fast access by
 *          using pointers. Also, this implementation provides
 *          support for generalized Trees using a binary tree.
 *          Forests are supported, but will be in a slightly
 *          dirrent format than having all children at each
 *          node rather than linked using binary (two) pointers.
 *
 *          Other versions of this object have been attempted using
 *          numeric indices instead of pointers. This required much
 *          more overhead than just using pointers and requiring
 *          everything to be in memory.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  02/04/2023 Generated
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
        OBJ_IDENT_AST,         //  Abstract Syntax Tree
        OBJ_IDENT_AST_CLASS,
    The following should be added to the appropriate objects.json.txt
    or program.json.txt file:
        {name:"Ast",  desc:"Abstract Syntax Tree"},
 *----------------------------------------------------------------*/



//#define   AST_IS_IMMUTABLE     1
//#define   AST_JSON_SUPPORT     1
//#define   AST_SINGLETON        1
//#define       AST_MSGS   1
#define   AST_SUPER_DEFINED   1


#include        <cmn_defs.h>
#include        <AStr.h>
#ifdef  AST_SUPER_DEFINED
#include        <Blocks.h>
#endif
#include        <Node.h>
#include        <ptrArray.h>
#include        <Opcode.h>
#include        <Sym.h>
#include        <Token.h>


#ifndef         AST_H
#define         AST_H





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct Ast_data_s  AST_DATA;          // Inherits from Blocks
    typedef struct Ast_class_data_s AST_CLASS_DATA;  // Inherits from obj

    typedef struct Ast_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        //Blocks_VTBL    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Ast_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(AST_DATA *);
    } AST_VTBL;

    typedef struct Ast_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Ast_object.c.
        // Properties:
        // Methods:
        AST_DATA *(*pNew)(void);
        //bool        (*pIsEnabled)(AST_DATA *);
    } AST_CLASS_VTBL;

    typedef enum Ast_Entry_Types {
        AST_ENTRY_KIND_NO_DATA=0,
        AST_ENTRY_KIND_CHARS,               // A string up to 7 chars long
        AST_ENTRY_KIND_INTEGER,
        AST_ENTRY_KIND_NUMBER,
        AST_ENTRY_KIND_OBJECT,
        AST_ENTRY_KIND_OPCODE,
        AST_ENTRY_KIND_POINTER,
        AST_ENTRY_KIND_STRING,
        AST_ENTRY_KIND_SYMBOL,
    } AST_ENTRY_TYPES;

    typedef struct Ast_Entry_s AST_ENTRY;
    struct Ast_Entry_s {
        AST_ENTRY       *pParent;
        AST_ENTRY       *pChild;            // First Child
        AST_ENTRY       *pSibling;          // First Sibling
        TOKEN_FIELDS    def;                // Where entry was defined
        int16_t         type;               // User-defined Type
        int16_t         kind;               // Kind of this entry (see u below);
        union {
            char            chrs[8];            // Short String (up to 7 chars long)
            void            *pVoid;             // Pointer
            char            *pStr;              // String
            double          num;                // Floating point number
            int64_t         integer;            // Integer
            OBJ_DATA        *pObj;              // Object Pointer
            OPCODE_DATA     *pOpcode;           // Opcode Object Pointer
            SYM_DATA        *pSym;              // Symbol Object Pointer
        } u;
    };


    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  AST_SINGLETON
    AST_DATA *      Ast_Shared (
        void
    );

    void            Ast_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to Ast object if successful, otherwise OBJ_NIL.
     */
    AST_DATA *      Ast_Alloc (
        void
    );
    
    
    OBJ_ID          Ast_Class (
        void
    );
    
    
    AST_DATA *      Ast_New (
        void
    );
    
    
#ifdef  AST_JSON_SUPPORT
    AST_DATA *      Ast_NewFromJsonString (
        ASTR_DATA       *pString
    );

    AST_DATA *      Ast_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

#ifdef AST_MSGS
    /*! @property   Messages
        Allows information and warning messages to be issued.
     */
    bool            Ast_setMsgs (
        AST_DATA        *this,
        void            (*pMsgInfo)(OBJ_ID, const char *, ...),
        void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...),
        OBJ_ID          pObj
    );
#endif


    /*! @property   Root
        Is set by the user. It is for their convenience and is not used
        in any methods.
     */
    AST_ENTRY *     Ast_getRoot (
        AST_DATA        *this
    );

    bool            Ast_setRoot (
        AST_DATA        *this,
        AST_ENTRY       *pValue
    );


#ifdef  AST_SUPER_DEFINED
    BLOCKS_DATA *   Ast_getSuper (
        AST_DATA        *this
    );
#else
    OBJ_DATA *      Ast_getSuper (
        AST_DATA        *this
    );
#endif



    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // The methods beginning with entry provide various mechanisms for
    // adding, deleting, accessing and updating the AST_ENTRYs that
    // make up one of more trees. The entries are maintained within
    // this object and will be deleted when it is released. Normally,
    // this object does not control these entries other than providing
    // the backing store except for object entries. Object entries are
    // released when this object is released.
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    /*!
     Add child(ren) to a parent.
     @param     this    object pointer
     @param     pParent required parent entry pointer
     @param     pChild1 required child entry pointer
     @param     pChild2 optional child entry pointer
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT         Ast_EntryAddChild (
        AST_DATA        *this,
        AST_ENTRY       *pParent,
        AST_ENTRY       *pChild1,
        AST_ENTRY       *pChild2
    );


    /*!
     Add sibling(s) to an entry.
     @param     this        object pointer
     @param     pRoot       required entry pointer
     @param     pSibling1   required entry pointer
     @param     pSibling2   optional entry pointer
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT         Ast_EntryAddSibling (
        AST_DATA        *this,
        AST_ENTRY       *pRoot,
        AST_ENTRY       *pSibling1,
        AST_ENTRY       *pSibling2
    );


    /*!
     Creates a copy of an entry and its sub-tree.
     @param     this    object pointer
     @param     pRoot   Root Entry pointer
     @return    if successful, the entry's address.  Otherwise, NULL.
     */
    AST_ENTRY *     Ast_EntryCopy (
        AST_DATA        *this,
        AST_ENTRY       *pRoot
    );


    /*!
     Creates a string (ie less than 8 char string).
     @param     this    object pointer
     @param     pStrA   the string pointer to be put in the entry
     @param     type    the optional entry type (ASM_CLASS_*, 0 == None)
     @param     pToken  optional pointer to the defining token
     @return    if successful, the entry's address.  Otherwise, NULL.
     */
    AST_ENTRY *     Ast_EntryNewChars (
        AST_DATA        *this,
        const
        char            *pStrA,
        int16_t         type,
        TOKEN_FIELDS    *pToken
    );


    /*!
     Creates an integer entry.
     @param     this    object pointer
     @param     integer the integer to be put in the entry
     @param     type    the optional entry type (ASM_CLASS_*, 0 == None)
     @param     pToken  optional pointer to the defining token
     @return    if successful, the entry's address.  Otherwise, NULL.
     */
    AST_ENTRY *     Ast_EntryNewInteger (
        AST_DATA        *this,
        int64_t         integer,
        int16_t         type,
        TOKEN_FIELDS    *pToken
    );


    /*!
     Creates an floating point entry.
     @param     this    object pointer
     @param     number  the number to be put in the entry
     @param     type    the optional entry type (ASM_CLASS_*, 0 == None)
     @param     pToken  optional pointer to the defining token
     @return    if successful, the entry's address.  Otherwise, NULL.
     */
    AST_ENTRY *     Ast_EntryNewNumber (
        AST_DATA        *this,
        double          number,
        int16_t         type,
        TOKEN_FIELDS    *pToken
    );


    /*!
     Creates an object pointer entry.
     @param     this    object pointer
     @param     pObj    the object pointer to be put in the entry
     @param     type    the optional entry type (ASM_CLASS_*, 0 == None)
     @param     pToken  optional pointer to the defining token
     @return    if successful, the entry's address.  Otherwise, NULL.
     */
    AST_ENTRY *     Ast_EntryNewObject (
        AST_DATA        *this,
        OBJ_ID          pObj,
        int16_t         type,
        TOKEN_FIELDS    *pToken
    );


    /*!
     Creates an operation entry.
     @param     this    object pointer
     @param     pOpcode the object pointer to be put in the entry
     @param     type    the optional entry type (ASM_CLASS_*, 0 == None)
     @param     pToken  optional pointer to the defining token
     @return    if successful, the entry's address.  Otherwise, NULL.
     */
    AST_ENTRY *     Ast_EntryNewOpcode (
        AST_DATA        *this,
        OPCODE_DATA     *pOpcode,
        int16_t         type,
        TOKEN_FIELDS    *pToken
    );


    /*!
     Creates an operator entry.
     @param     this    object pointer
     @param     pStrA   the string pointer to be put in the entry
     @param     type    the optional entry type (ASM_CLASS_*, 0 == None)
     @param     pToken  optional pointer to the defining token
     @return    if successful, the entry's address.  Otherwise, NULL.
     */
    AST_ENTRY *     Ast_EntryNewOperator (
        AST_DATA        *this,
        const
        char            *pStrA,
        int16_t         type,
        TOKEN_FIELDS    *pToken
    );


    /*!
     Creates an pointer entry.
     @param     this    object pointer
     @param     pVoid   the pointer to be put in the entry
     @param     type    the optional entry type (ASM_CLASS_*, 0 == None)
     @param     pToken  optional pointer to the defining token
     @return    if successful, the entry's address.  Otherwise, NULL.
     */
    AST_ENTRY *     Ast_EntryNewPointer (
        AST_DATA        *this,
        void            *pVoid,
        int16_t         type,
        TOKEN_FIELDS    *pToken
    );

   
    /*!
     Creates an pointer entry.
     @param     this    object pointer
     @param     pSym    the symbol object pointer to be put in the entry
     @param     type    the optional entry type (ASM_CLASS_*, 0 == None)
     @param     pToken  optional pointer to the defining token
     @return    if successful, the entry's address.  Otherwise, NULL.
     */
    AST_ENTRY *     Ast_EntryNewSymbol (
        AST_DATA        *this,
        SYM_DATA        *pSym,
        int16_t         type,
        TOKEN_FIELDS    *pToken
    );


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
        ASTR_DATA      *pDesc = Ast_ToDebugString(this,4);
     @endcode
     @param     this    object pointer
     @param     pEntry  pointer to entry to be displayed
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Ast_EntryToDebugString (
        AST_DATA        *this,
        AST_ENTRY       *pEntry
    );




    AST_DATA *      Ast_Init (
        AST_DATA        *this
    );


    bool            Ast_IsEnabled (
        AST_DATA        *this
    );
    
 
    /*!
     Setup this object for debugging and Linearization.
     @param     this        object pointer
     @param     typeClose   Type which specifies the Close Element ')'
                            for Linearization
     @param     typeOpen    Type which specifies the Open Element '('
                            for Linearization
     @param     pClassToName    Used for debugging only, translates a
                            type to a string constant
     @return    If successful, ERESULT_SUCCESS; otherwise an ERESULT_*
                error code.
     */
    bool            Ast_Setup (
        AST_DATA        *this,
        int16_t         typeClose,      // Normally means ')'
        int16_t         typeOpen,       // Normally means '('
        const
        char *          (*pClassToName)(int32_t)
    );


/*! Convert the tree to an array with open/close nodes interjected to
    to show the tree structure. An open node is added if the current
    node has children. A close node is added after all the children
    are added. The tree is visited in post-order mode. This can be used
    to scan the tree as if it was an array looking for patterns.
    Postfix traversal is normally considered the way to translate a tree
    to Reverse Polish Notation (RPN).
    @param     this     object pointer
    @param     pRoot    Root Entry Pointer (NULL causes the Root property to
                        be used)
    @return    If successful, an ptrArray of AST_ENTRY objects which must be
                released, otherwise OBJ_NIL.
    @warning   Remember to release the returned ptrArray object.
 */
    PTRARRAY_DATA * Ast_ToLinearizationPost(
        AST_DATA        *this,
        AST_ENTRY       *pRoot
    );


    /*!
     Build an array of entries from  the root (or current node) then visit
     each child recursively starting at the given index. Prefix traversal
     is normally considered the way to translate a tree to Reverse Polish
     Notation (RPN).
     @param     this     object pointer
     @param     pRoot   Root Entry Pointer
     @return    LastError (If successful, LastError == ERESULT_SUCCESS,
                otherwise LastError == ERESULT_* error code).
     */
    PTRARRAY_DATA * Ast_ToLinearizationPre(
        AST_DATA        *this,
        AST_ENTRY       *pRoot
    );


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Ast_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Ast_ToDebugString (
        AST_DATA        *this,
        int             indent
    );
    
    
    /*!
     Create a string that shows the structure of the tree in a horizontal format.
     @param     this        object pointer
     @param     indent      number of characters to indent every line of output, can be 0
     @param     pPrintEntry Entry print routine which should try to print information for
                            the entry on one line if possible. The level spacing should
                            be '-' for the first line and ' ' for any line after it.
                            The indent spacing should be ' '. If NULL is provided, a
                            default routine which prints the node's name is used.
     @param     pPrintObj   object pointer for pPrintNodde
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     Ast_ToStringHorz (
        AST_DATA        *this,
        AST_ENTRY       *pRoot,
        uint16_t        indent,
        ERESULT         (*pPrintEntry)(
            OBJ_ID          ,
            ASTR_DATA       *,                      // String to append to
            AST_ENTRY       *,
            uint16_t        indent,                 // indent amount for entire tree
            int             level,                  // indedt level for this node
            void            *
        ),
        OBJ_ID          pPrintObj
    );

    
    /*!
     Visit every node on each level of the tree level by level starting
     at the given index.
     This is also known as a breadth-first traversal.
     @param     this        object pointer
     @param     pVisitor    Function pointer to the routine called as each
                            node is visited
     @param     pObject     First parameter of pVisitor
     @param     pOther      5th parameeter of pVisitor
     @param     indent      amount to indent per level
     @param     pEntry      root object pointer for tree (NULL == Use root property)
     @return    If success, ERESULT_SUCCESS. Otherwise an ERESULT_*
                error code.
     */
    ERESULT         Ast_VisitBreadthFirst(
        AST_DATA        *this,
        void            (*pVisitor)(
            OBJ_ID          ,               // Object supplied below
            AST_DATA        *,              // Our Tree
            AST_ENTRY       *,              // Current Node
            uint32_t        ,               // Indent
            uint32_t        ,               // Indent level
            void            *               // optional other data
        ),
        OBJ_ID          pObject,
        void            *pOther,
        uint32_t        indent,
        AST_ENTRY       *pEntry
    );


    /*!
     Visit the root (or current node) then visit each child recursively
     starting at the given index. The Root property must be set for this
     to work. Postfix traversal is normally considered the way to trans-
     late a tree to Reverse Polish Notation (RPN).
     @param     this     object pointer
     @param     pVisitor Function pointer to the routine called as each
                        entry is visited
     @param     pOpen   Function pointer to the routine called after
                        a level is increased
     @param     pClose  Function pointer to the routine called after
                        a level is decreased
     @param     pObject First parameter of pVisitor
     @param     pOther  5th parameeter of pVisitor
     @param     indent  amount to indent per level
     @param     pRoot   Root Entry Pointer  (NULL == Use root property)
     @return    LastError (If successful, LastError == ERESULT_SUCCESS,
                otherwise LastError == ERESULT_* error code).
     */
    ERESULT         Ast_VisitPostOrder (
        AST_DATA        *this,
        void            (*pVisitor) (
                                   OBJ_ID,              // Object supplied below
                                   AST_DATA *,          // Tree Object
                                   AST_ENTRY *,         // Current Entry
                                   uint32_t ,           // Indent
                                   uint32_t ,           // Indent level
                                   void *               // other data
                                  ),
        void            (*pOpen) (
                                 OBJ_ID,              // Object supplied below
                                 AST_DATA *,          // Tree Object
                                 AST_ENTRY *,         // Current Entry
                                 uint32_t ,           // Indent
                                 uint32_t ,           // Indent level
                                 void *               // other data
                                ),
        void            (*pClose) (
                               OBJ_ID,              // Object supplied below
                               AST_DATA *,          // Tree Object
                               AST_ENTRY *,         // Current Entry
                               uint32_t ,           // Indent
                               uint32_t ,           // Indent level
                               void *               // other data
                              ),
        OBJ_ID          pObject,                // Object supplied as 1st argument
        void            *pOther,
        uint32_t        indent,                 // Current Indent level
        AST_ENTRY       *pRoot
    );


    /*!
     Visit the root (or current node) then visit each child recursively
     starting at the given index. The Root property must be set for this
     to work. This is also known as a depth-first traversal or Dynastic
     order.
     @param     this     object pointer
     @param     pVisitor Function pointer to the routine called as each
                        entry is visited
     @param     pOpen   Function pointer to the routine called after
                        a level is increased
     @param     pClose  Function pointer to the routine called after
                        a level is decreased
     @param     pObject First parameter of pVisitor
     @param     pOther  5th parameeter of pVisitor
     @param     indent      amount to indent per level
     @param     pRoot   Root Entry Pointer  (NULL == Use root property)
     @return    LastError (If successful, LastError == ERESULT_SUCCESS,
                otherwise LastError == ERESULT_* error code).
     */
    ERESULT         Ast_VisitPreOrder (
        AST_DATA        *this,
        void            (*pVisitor) (
                                   OBJ_ID,              // Object supplied below
                                   AST_DATA *,          // Tree Object
                                   AST_ENTRY *,         // Current Entry
                                   uint32_t ,           // Indent
                                   uint32_t ,           // Indent level
                                   void *               // other data
                                  ),
        void            (*pOpen) (
                                 OBJ_ID,              // Object supplied below
                                 AST_DATA *,          // Tree Object
                                 AST_ENTRY *,         // Current Entry
                                 uint32_t ,           // Indent
                                 uint32_t ,           // Indent level
                                 void *               // other data
                                ),
        void            (*pClose) (
                               OBJ_ID,              // Object supplied below
                               AST_DATA *,          // Tree Object
                               AST_ENTRY *,         // Current Entry
                               uint32_t ,           // Indent
                               uint32_t ,           // Indent level
                               void *               // other data
                              ),
        OBJ_ID          pObject,                // Object supplied as 1st argument
        void            *pOther,
        uint32_t        indent,                 // Current Indent level
        AST_ENTRY       *pRoot
    );


#ifdef  __cplusplus
}
#endif

#endif  /* AST_H */

