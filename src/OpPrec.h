// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//            Operator Precedence Parser (OpPrec) Header
//****************************************************************

/*
 * Program
 *          Operator Precedence Parser (OpPrec)
 * Purpose
 *          This object provides support to parse Operands and
 *          Operators using Operator Precedence building an
 *          an Abstract Syntax Tree (AST). This parser operates
 *          in the normal pull mode of asking the supplied
 *          NextOperand() and NextOperator() methods for its
 *          input. See Setup() below for an explanation of them.
 *
 *          Operator Precedence requires that the input consist
 *          alternating operands and operators. The first and
 *          last elements must be operands (ie operand operator
 *          operand operator operand EOF). All operators are
 *          considered to be binary operators and must never
 *          have two in a row. Unary operators should be handled
 *          in the "NextOperand" method.
 *
 *          The AST is created and controlled by this object. It
 *          should be retained by a controlling object since it
 *          is released when this object is release.
 *
 *          Another object provides the lexical input stream of
 *          Tokens for the parser. Expr2Ast and its test program
 *          illustrate an example of using this object.
 *
 * Remarks
 *  1.      This object is designed to be inherited. If it is, it
 *          will automatically establish it's Setup() parameters
 *          by querying for methods, "Class2Name", "NextOperand",
 *          "NextOperator" and "Precedence".
 *  2.      This object does not create the AST entry for the operands,
 *          because those might require one or more AST entries linked
 *          to higher level entries. The highest level entry is what
 *          is returned and processed by this object. This allows the
 *          NextOperand() method to process unary operators as well
 *          as specialized operands such as parenthesis.
 *
 * History
 *  03/04/2023 Generated
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
        OBJ_IDENT_OPPREC,         //  Operator Precedence Parser
        OBJ_IDENT_OPPREC_CLASS,
    The following should be added to the appropriate objects.json.txt
    or program.json.txt file:
        {name:"OpPrec",  desc:"Operator Precedence Parser"},
 *----------------------------------------------------------------*/



//#define   OPPREC_IS_IMMUTABLE     1
//#define   OPPREC_JSON_SUPPORT     1
//#define   OPPREC_SINGLETON        1
//#define       OPPREC_MSGS   1
//#define   OPPREC_SUPER_DEFINED     1


#include        <cmn_defs.h>
#include        <Ast.h>
#include        <AStr.h>
#ifdef  OPPREC_SUPER_DEFINED
#include        <obj.h>
#endif


#ifndef         OPPREC_H
#define         OPPREC_H





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct OpPrec_data_s  OPPREC_DATA;          // Inherits from obj
    typedef struct OpPrec_class_data_s OPPREC_CLASS_DATA;  // Inherits from obj

    typedef struct OpPrec_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        //obj_VTBL    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in OpPrec_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(OPPREC_DATA *);
    } OPPREC_VTBL;

    typedef struct OpPrec_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in OpPrec_object.c.
        // Properties:
        // Methods:
        OPPREC_DATA *(*pNew)(void);
        //bool        (*pIsEnabled)(OPPREC_DATA *);
    } OPPREC_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  OPPREC_SINGLETON
    OPPREC_DATA *   OpPrec_Shared (
        void
    );

    void            OpPrec_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to OpPrec object if successful, otherwise OBJ_NIL.
     */
    OPPREC_DATA *   OpPrec_Alloc (
        void
    );
    
    
    OBJ_ID          OpPrec_Class (
        void
    );
    
    
    OPPREC_DATA *   OpPrec_New (
        void
    );
    
    
#ifdef  OPPREC_JSON_SUPPORT
    OPPREC_DATA *   OpPrec_NewFromJsonString (
        ASTR_DATA       *pString
    );

    OPPREC_DATA *   OpPrec_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    AST_DATA *      OpPrec_getAst (
        OPPREC_DATA     *this
    );

    bool            OpPrec_setAst (
        OPPREC_DATA     *this,
        AST_DATA        *pValue
    );


#ifdef OPPREC_MSGS
    /*! @property   Messages
        Allows information and warning messages to be issued.
     */
    bool            OpPrec_setMsgs (
        OPPREC_DATA     *this,
        void            (*pMsgInfo)(OBJ_ID, const char *, ...),
        void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...),
        OBJ_ID          pObj
    );
#endif


#ifdef  OPPREC_SUPER_DEFINED
    OBJ_DATA *      OpPrec_getSuper (
        OPPREC_DATA     *this
    );
#else
    OBJ_DATA *      OpPrec_getSuper (
        OPPREC_DATA     *this
    );
#endif


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    OPPREC_DATA *   OpPrec_Init (
        OPPREC_DATA     *this
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
    AST_ENTRY *     OpPrec_Parse (
        OPPREC_DATA     *this
    );


    /*!
     Setup this object with the necessary support for parsing. NOTE:
     this method does not need to be called if this object is inherited
     and the necessary method queries work. See the Notes section above.
     @param     this            object pointer
     @param     pNextOperand    method pointer based from pObjParse
     @param     pPrecedence     method pointer based from pObjParse
     @param     pObjParse       object pointer for above methods
     @param     pClass2Name     routine pointer that converts a token
                                class to a displable name which will
                                not be altered. This is used for
                                debugging purposes if supplied.
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         OpPrec_Setup (
        OPPREC_DATA     *this,
        /*! Parse the next Operand returning its AST entry which is
          not connected to any other AST entry.  The AST entry should
          include the Token fields information from it's parse. The
          internal parser will take care of connecting the returned
          entry.
        @param     this    Object Pointer given by pObjParse below.
        @param     pAst    Abstract Syntax Tree Object Pointer created
                          within this object
        @return    Return the precedence of an acknowledged binary operator.
                  If it is not a known operator, return -1.
        */
        AST_ENTRY *     (*pNextOperand) (OBJ_ID this, AST_DATA *pAst),
        /*! Determine the precedence of binary operators given the operator's
          class.
        @param     this    Object Pointer given by pObjParse below.
        @param     cls     Operator Token Class
        @return    Return the precedence of an acknowledged binary operator.
                  If it is not a known operator, return -1.
        */
        int32_t         (*pPrecedence) (OBJ_ID this, int32_t cls),
        OBJ_ID          pObjParse,
        /*! Convert a Token class to a displayable name.
        */
        const
        char *          (*pClass2Name) (int32_t cls)
    );


#ifdef  OPPREC_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = OpPrec_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     OpPrec_ToJson (
        OPPREC_DATA     *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = OpPrec_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     OpPrec_ToDebugString (
        OPPREC_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* OPPREC_H */

