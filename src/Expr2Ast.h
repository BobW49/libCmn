// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//       Parse an Expression into an AST (Expr2Ast) Header
//****************************************************************

/*
 * Program
 *          Parse an Expression into an AST (Expr2Ast)
 * Purpose
 *          This object parses an expression into an AST.
 *          a separate Expr2Ast to run things without complications
 *          of interfering with the main Expr2Ast. A Expr2Ast may be 
 *          called a Expr2Ast on other O/S's.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  02/10/2023 Generated
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
        OBJ_IDENT_EXPR2AST,         //  Parse an Expression into an AST
        OBJ_IDENT_EXPR2AST_CLASS,
    The following should be added to the appropriate objects.json.txt
    or program.json.txt file:
        {name:"Expr2Ast",  desc:"Parse an Expression into an AST"},
 *----------------------------------------------------------------*/



//#define   EXPR2AST_IS_IMMUTABLE     1
//#define   EXPR2AST_JSON_SUPPORT     1
//#define   EXPR2AST_SINGLETON        1
//#define       EXPR2AST_MSGS   1
#define   EXPR2AST_SUPER_DEFINED     1


#include        <cmn_defs.h>
#include        <Ast.h>
#ifdef  EXPR2AST_SUPER_DEFINED
#include        <OpPrec.h>
#endif
#include        <Sym.h>


#ifndef         EXPR2AST_H
#define         EXPR2AST_H





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct Expr2Ast_data_s  EXPR2AST_DATA;          // Inherits from obj
    typedef struct Expr2Ast_class_data_s EXPR2AST_CLASS_DATA;  // Inherits from obj

    typedef struct Expr2Ast_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        //obj_VTBL    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Expr2Ast_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(EXPR2AST_DATA *);
    } EXPR2AST_VTBL;

    typedef struct Expr2Ast_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Expr2Ast_object.c.
        // Properties:
        // Methods:
        EXPR2AST_DATA *(*pNew)(void);
        //bool        (*pIsEnabled)(EXPR2AST_DATA *);
    } EXPR2AST_CLASS_VTBL;


#include        <C_Expr_Class.h>


    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  EXPR2AST_SINGLETON
    EXPR2AST_DATA * Expr2Ast_Shared (
        void
    );

    void            Expr2Ast_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to Expr2Ast object if successful, otherwise OBJ_NIL.
     */
    EXPR2AST_DATA * Expr2Ast_Alloc (
        void
    );
    
    
    OBJ_ID          Expr2Ast_Class (
        void
    );
    
    
    EXPR2AST_DATA * Expr2Ast_New (
        void
    );
    
    
#ifdef  EXPR2AST_JSON_SUPPORT
    EXPR2AST_DATA *   Expr2Ast_NewFromJsonString (
        ASTR_DATA       *pString
    );

    EXPR2AST_DATA *   Expr2Ast_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    /*! @property Abstract Syntax Tree (Ast)
     THis is built by setting up and input source and then executing
     the method, Parse(). Parse() can be used to return this tree or
     you can use these methods to access/modify it.
     */
    AST_DATA *      Expr2Ast_getAst (
        EXPR2AST_DATA   *this
    );

    bool            Expr2Ast_setAst (
        EXPR2AST_DATA   *this,
        AST_DATA        *pValue
    );


    bool            Expr2Ast_setInput (
        EXPR2AST_DATA   *this,
        int32_t         (*pInputAdvance)(OBJ_ID, uint16_t, TOKEN_FIELDS **),
        int32_t         (*pInputLookAhead)(OBJ_ID, uint16_t, TOKEN_FIELDS **),
        OBJ_ID          pObjInput
    );


#ifdef EXPR2AST_MSGS
    /*! @property   Messages
        Allows information and warning messages to be issued.
     */
    bool            Expr2Ast_setMsgs (
        EXPR2AST_DATA    *this,
        void            (*pMsgInfo)(OBJ_ID, const char *, ...),
        void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...),
        OBJ_ID          pObj
    );
#endif


#ifdef  EXPR2AST_SUPER_DEFINED
    OPPREC_DATA *   Expr2Ast_getSuper (
        EXPR2AST_DATA   *this
    );
#else
    OBJ_DATA *      Expr2Ast_getSuper (
        EXPR2AST_DATA   *this
    );
#endif


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         Expr2Ast_Enable (
        EXPR2AST_DATA   *this
    );

   
    EXPR2AST_DATA *     Expr2Ast_Init (
        EXPR2AST_DATA       *this
    );


    bool                Expr2Ast_IsEnabled (
        EXPR2AST_DATA       *this
    );
    
 
    /*!
     Parse the input creating the Abstract Syntax Tree (Ast). This
     requires that the input source be established before calling
     this method.
     @param     this    object pointer
     @return    if successful, pointer to the Abstract Syntax Tree
                entry that should be the root of the tree. Otherwise,
                NULL.
     */
    AST_ENTRY *     Expr2Ast_Parse (
        EXPR2AST_DATA   *this
    );


#ifdef  EXPR2AST_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Expr2Ast_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Expr2Ast_ToJson (
        EXPR2AST_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Expr2Ast_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Expr2Ast_ToDebugString (
        EXPR2AST_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* EXPR2AST_H */

