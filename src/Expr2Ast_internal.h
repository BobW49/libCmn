// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
// Parse an Expression into an AST (Expr2Ast) Internal Header
//****************************************************************

/* 
 * File:   Expr2Ast_internal.h
 *  Generated 02/10/2023 10:03:03
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




#include        <Expr2Ast.h>
#ifdef  EXPR2AST_SUPER_DEFINED
#include        <OpPrec_internal.h>
#endif
#include        <JsonIn.h>


#ifndef EXPR2AST_INTERNAL_H
#define EXPR2AST_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif


#ifdef NDEBUG
#   define     LOOKAHEAD(num)   this->pInputLookAhead(this->pObjInput, num, &this->pFields)
#   define     ADVANCE(num)     this->pInputAdvance(this->pObjInput, num, &this->pFields)
#   define     ADVLOOK(num)     Expr2Ast_InputAdvLook(this, num)
#else
#   define     LOOKAHEAD(num)   Expr2Ast_LookAhead(this, num)
#   define     ADVANCE(num)     this->pInputAdvance(this->pObjInput, num, &this->pFields)
#   define     ADVLOOK(num)     Expr2Ast_InputAdvLook(this, num)
#endif






    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------


#if !defined(__arm64__)
#pragma pack(push, 1)
#endif
struct Expr2Ast_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
#ifdef  EXPR2AST_SUPER_DEFINED
    OPPREC_DATA     super;
#else
    OBJ_DATA        super;
#endif
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    NODEARRAY_DATA  *pArray;
    TOKEN_FIELDS    *pFields;   // Look-Ahead Token Fields
    TOKEN_FIELDS    fields;     // Saved Look-Ahead Token Fields
#define OP_STACKMAX    16
    
    // Symbol Exit
    SYM_DATA *      (*pFindSymA)(OBJ_ID, const char *);
    OBJ_ID          pObjSym;

    // Find an Identifier. If not found, return 0.
    int32_t         (*pFindValueA)(OBJ_ID, const char *);
    OBJ_ID          pObjFind;

    // Input the next Scanned Token.
    int32_t         (*pInputAdvance)(OBJ_ID, uint16_t, TOKEN_FIELDS **);
    int32_t         (*pInputLookAhead)(OBJ_ID, uint16_t, TOKEN_FIELDS **);
    OBJ_ID          pObjInput;

#ifdef   EXPR2AST_MSGS
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
    struct Expr2Ast_class_data_s  Expr2Ast_ClassObj;

    extern
    const
    EXPR2AST_VTBL         Expr2Ast_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  EXPR2AST_SINGLETON
    EXPR2AST_DATA * Expr2Ast_getSingleton (
        void
    );

    bool            Expr2Ast_setSingleton (
     EXPR2AST_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  EXPR2AST_SUPER_DEFINED
    OPPREC_DATA *   Expr2Ast_getSuper (
        EXPR2AST_DATA   *this
    );
#else
    OBJ_DATA *  Expr2Ast_getSuper (
        EXPR2AST_DATA   *this
    );
#endif


    OBJ_IUNKNOWN *  Expr2Ast_getSuperVtbl (
        EXPR2AST_DATA   *this
    );


    ERESULT         Expr2Ast_Assign (
        EXPR2AST_DATA   *this,
        EXPR2AST_DATA   *pOther
    );


    EXPR2AST_DATA * Expr2Ast_Copy (
        EXPR2AST_DATA   *this
    );


    void            Expr2Ast_Dealloc (
        OBJ_ID          objId
    );


    EXPR2AST_DATA * Expr2Ast_DeepCopy (
        EXPR2AST_DATA   *this
    );


    AST_ENTRY *     Expr2Ast_ExprInternal (
        EXPR2AST_DATA    *this
    );


    AST_ENTRY *     Expr2Ast_NextOperand (
        EXPR2AST_DATA   *this,
        AST_DATA        *pAst
    );


    /*! Determine the precedence of binary operators.
     @return    Return the precedence of an acknowledged binary operator.
                If it is not an known operator, return -1.
     */
    int32_t         Expr2Ast_Precedence (
        EXPR2AST_DATA   *this,
        int32_t         op
    );


#ifdef  EXPR2AST_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    EXPR2AST_DATA * Expr2Ast_ParseJsonObject (
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
    ERESULT         Expr2Ast_ParseJsonFields (
        JSONIN_DATA     *pParser,
        EXPR2AST_DATA   *pObject
    );
#endif


    void *          Expr2Ast_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
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


    /*!
     Append the json representation of the object's fields to the given
     string. This helps facilitate parsing the fields from an inheriting 
     object.
     @param this        Object Pointer
     @param pStr        String Pointer to be appended to.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Expr2Ast_ToJsonFields (
        EXPR2AST_DATA   *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool            Expr2Ast_Validate (
        EXPR2AST_DATA       *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* EXPR2AST_INTERNAL_H */

