// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//  Parse an Expression into an AST (Expr2Ast) Object Support
//****************************************************************


/*
 * File:   Expr2Ast.c
 *  Generated 02/10/2023 10:03:03
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




//*****************************************************************
//* * * * * * * * * * * *  Data Definitions   * * * * * * * * * * *
//*****************************************************************

/* Header File Inclusion */
#include        <Expr2Ast_internal.h>
#include        <JsonIn.h>
#include        <Misc.h>
#include        <trace.h>
#include        <utf8.h>






#ifdef  __cplusplus
extern "C" {
#endif
    

    
    //****************************************************************
    // * * * * * * * * * * *    Internal Data    * * * * * * * * * * *
    //****************************************************************

    // Place constant internal data here. Generally, it should be
    // 'static' so that it does not interfere with other objects.

#include        <C_Expr_Class_tables.c>

 
    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/



    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#include        <C_Expr_Class_routines.c>

    int32_t         Expr2Ast_LookAhead (
        EXPR2AST_DATA   *this,
        uint16_t        num
    )
    {
        int32_t         cls;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
        
        cls = this->pInputLookAhead(this->pObjInput, num, &this->pFields);
       
        if (obj_Trace(this)) {
            ASTR_DATA       *pStr = Token_FieldsToDebugString(this->pFields, 0);
            if (pStr) {
                fputs(AStr_getData(pStr), stderr);
                obj_Release(pStr);
            }
        }

        return cls;
    }


    int32_t         Expr2Ast_AdvLook (
        EXPR2AST_DATA   *this,
        uint16_t        num
    )
    {
        int32_t         cls;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
        
        ADVANCE(num);       // Overlays LookAhead Token Fields
        cls = LOOKAHEAD(1);

        // Return to caller.
        return cls;
    }



    AST_ENTRY *     Expr2Ast_NextOperand (
        EXPR2AST_DATA   *this,
        AST_DATA        *pAst
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        AST_ENTRY       *pExpr1 = NULL;
        AST_ENTRY       *pExpr2 = NULL;
        int32_t         cls;
        //AST_ENTRY       *pEntry;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);

        cls = this->pFields->cls;
        switch (cls) {
            case C_EXPR_CLASS_LOG_NOT:               // Unary Op ! (Logical Not)
            case C_EXPR_CLASS_NEG:                   // Unary Op - (2s complement)
            case C_EXPR_CLASS_NOT:                   // Unary Op ~ (1s complement)
            case C_EXPR_CLASS_SUB: {                 // Unary Op - (2s complement)
                TRC_OBJ(this, "\tUnary op: %s\n", this->pFields->chr);
                if (C_EXPR_CLASS_SUB == cls)
                    cls = C_EXPR_CLASS_NEG;
                pExpr1 = Ast_EntryNewPointer(pAst, NULL, cls, this->pFields);
                Expr2Ast_AdvLook(this, 1);          // Overlays LookAhead Token Fields
                if (
                    (this->pFields->cls == C_EXPR_CLASS_SYM_INT)
                    ||  (this->pFields->cls == C_EXPR_CLASS_CON_INT)
                    ||  (this->pFields->cls == C_EXPR_CLASS_CON_REAL)
                    ||  (this->pFields->cls == C_EXPR_CLASS_PAREN_LEFT)
                ) {
                    if (C_EXPR_CLASS_INTEGER == this->pFields->cls) {
                        switch (cls) {
                            case C_EXPR_CLASS_LOG_NOT:
                                this->pFields->integer = !this->pFields->integer;
                                break;
                            case C_EXPR_CLASS_NEG:
                                this->pFields->integer = -this->pFields->integer;
                                break;
                            case C_EXPR_CLASS_NOT:
                                this->pFields->integer = ~this->pFields->integer;
                                break;
                            default:
                                //TODO: Internal Error
                                break;
                        }
                        pExpr1->type = C_EXPR_CLASS_CON_INT;
                        pExpr1->kind = AST_ENTRY_KIND_INTEGER;
                        pExpr1->u.integer = this->pFields->integer;
                        pExpr1->def = *this->pFields;
                        return pExpr1;
                    }
                } else {
                    TRC_OBJ(
                            this,
                            "ERROR - Unary op: %s followed by illegal %s\n",
                            C_Expr_ClassToName(cls),
                            C_Expr_ClassToName(this->pFields->cls)
                    );
                    DEBUG_BREAK();
                    return NULL;
                }
                pExpr2 = Expr2Ast_NextOperand(this, pAst);
                if (pExpr2) {
                    //FIXME: eRc = NodeTree_ChildAppendIndex(AsmExpr_getSuper(this), expr1, expr2);
                    if (ERESULT_FAILED(eRc)) {
#ifdef FIX_ME
                        TRC_OBJ(this, "\tAdd_expr2: ADD - %d child add: %d\n", pExpr1, AsmExpr_DumpEntry(this, pExpr2));
#endif
                        DEBUG_BREAK();
                        return NULL;
                    }
                }
                return pExpr1;
            }
            case C_EXPR_CLASS_CON_INT:
            case C_EXPR_CLASS_INTEGER:
                pExpr1 =    Ast_EntryNewInteger(
                                                pAst,
                                                this->pFields->integer,
                                                cls,
                                                this->pFields
                            );
                Expr2Ast_AdvLook(this, 1);              // Overlays LookAhead Token Fields
                return pExpr1;
            case C_EXPR_CLASS_CON_REAL: {
                pExpr1 =    Ast_EntryNewNumber(
                                                pAst,
                                                this->pFields->flt,
                                                cls,
                                                this->pFields
                            );
                Expr2Ast_AdvLook(this, 1);              // Overlays LookAhead Token Fields
                return pExpr1;
            }
            case C_EXPR_CLASS_PAREN_LEFT: {            // (
                Expr2Ast_AdvLook(this, 1);              // Overlays LookAhead Token Fields
                //FIXME: expr1 = AsmExpr_ExprInternal(this);
                cls = this->pFields->cls;
                if (C_EXPR_CLASS_PAREN_RIGHT == cls) {
                    Expr2Ast_AdvLook(this, 1);              // Overlays LookAhead Token Fields
                } else {
                    TRC_OBJ(this, "ERROR - Syntax Error - Missing matching ')'!\n");
                    DEBUG_BREAK();
                    return NULL;
                }
                return pExpr1;
            }
            default:
                TRC_OBJ(this, "ERROR - Syntax Error - Invalid Operand Type!\n");
                DEBUG_BREAK();
                return NULL;
                break;
        }
        

        // Return to caller.
        return NULL;
    }
    

    TOKEN_FIELDS *  Expr2Ast_NextOperator (
        EXPR2AST_DATA   *this
    )
    {
        //ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);

        this->fields = *this->pFields;      // Save current Lookahead.
        Expr2Ast_AdvLook(this, 1);          // Overlays LookAhead Token Fields

        // Return to caller.
        return &this->fields;
    }
    

    //---------------------------------------------------------------
    //                     P r e c e d e n c e
    //---------------------------------------------------------------
    
    /*! Determine the precedence of binary operators.
     @return    Return the precedence of an acknowledged binary operator.
                If it is not an known operator, return -1.
     */
    int32_t         Expr2Ast_Precedence (
        EXPR2AST_DATA   *this,
        int32_t         op
    )
    {
        // Do initialization.
        TRC_OBJ(this, "%s: %s\n", __func__, C_Expr_ClassToName(op));

        // The following operators are Left-to-Right associativity.
        switch (op) {
            case C_EXPR_CLASS_ADD:
            case C_EXPR_CLASS_SUB:
                return 4;
            case C_EXPR_CLASS_AND:
                return 8;
            case C_EXPR_CLASS_DIV:
            case C_EXPR_CLASS_MOD:
            case C_EXPR_CLASS_MUL:
                return 3;
            case C_EXPR_CLASS_EQ:
            case C_EXPR_CLASS_NE:
                return 7;
            case C_EXPR_CLASS_GE:
            case C_EXPR_CLASS_GT:
            case C_EXPR_CLASS_LE:
            case C_EXPR_CLASS_LT:
                return 6;
            case C_EXPR_CLASS_LOG_AND:
                return 11;
            case C_EXPR_CLASS_LOG_OR:
                return 10;
            case C_EXPR_CLASS_OR:
                return 12;
            case C_EXPR_CLASS_SHIFT_LEFT:
            case C_EXPR_CLASS_SHIFT_RIGHT:
                return 5;
            case C_EXPR_CLASS_XOR:
                return 9;
            default:
                return -1;
            }

        return 0;

    }



    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    EXPR2AST_DATA *     Expr2Ast_Alloc (
        void
    )
    {
        EXPR2AST_DATA       *this;
        uint32_t        cbSize = sizeof(EXPR2AST_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    EXPR2AST_DATA *     Expr2Ast_New (
        void
    )
    {
        EXPR2AST_DATA       *this;
        
        this = Expr2Ast_Alloc( );
        if (this) {
            this = Expr2Ast_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                              A s t
    //---------------------------------------------------------------
    
    AST_DATA *      Expr2Ast_getAst (
        EXPR2AST_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Expr2Ast_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return OpPrec_getAst((OPPREC_DATA *)this);
    }
    
    
    bool            Expr2Ast_setAst (
        EXPR2AST_DATA   *this,
        AST_DATA        *pValue
    )
    {
        bool            fRc;
#ifdef NDEBUG
#else
        if (!Expr2Ast_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        fRc = OpPrec_setAst((OPPREC_DATA *)this, pValue);
        
        return fRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n p u t
    //---------------------------------------------------------------
    
    bool            Expr2Ast_setInput (
        EXPR2AST_DATA   *this,
        int32_t         (*pInputAdvance)(OBJ_ID, uint16_t, TOKEN_FIELDS **),
        int32_t         (*pInputLookAhead)(OBJ_ID, uint16_t, TOKEN_FIELDS **),
        OBJ_ID          pObjInput
    )
    {
#ifdef NDEBUG
#else
        if (!Expr2Ast_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->pInputAdvance = pInputAdvance;
        this->pInputLookAhead = pInputLookAhead;
        this->pObjInput = pObjInput;

        return true;
    }



    //---------------------------------------------------------------
    //                      M e s s a g e s
    //---------------------------------------------------------------

#ifdef   EXPR2AST_MSGS
    bool            Expr2Ast_setMsgs (
        EXPR2AST_DATA    *this,
        void            (*pMsgInfo)(OBJ_ID, const char *, ...),
        void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...),
        OBJ_ID          pObj
    )
    {
#ifdef NDEBUG
#else
        if (!Expr2Ast_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->pMsgInfo = pMsgInfo;
        this->pMsgWarn = pMsgWarn;
        this->pMsgObj = pObj;

        return true;
    }
#endif



    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        Expr2Ast_getPriority (
        EXPR2AST_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Expr2Ast_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            Expr2Ast_setPriority (
        EXPR2AST_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!Expr2Ast_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        Expr2Ast_getSize (
        EXPR2AST_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!Expr2Ast_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
#ifdef  EXPR2AST_SUPER_DEFINED
    OPPREC_DATA *   Expr2Ast_getSuper (
        EXPR2AST_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Expr2Ast_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return (OPPREC_DATA *)this;
    }
#else
    OBJ_DATA *  Expr2Ast_getSuper (
        EXPR2AST_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Expr2Ast_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return (OBJ_DATA *)this;
    }
#endif

    
    OBJ_IUNKNOWN *  Expr2Ast_getSuperVtbl (
        EXPR2AST_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Expr2Ast_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before 
     a copy of the object is performed.
     Example:
     @code 
        ERESULT eRc = Expr2Ast_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another EXPR2AST object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         Expr2Ast_Assign (
        EXPR2AST_DATA       *this,
        EXPR2AST_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!Expr2Ast_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Expr2Ast_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Assign any Super(s).
        if (this->pSuperVtbl && (this->pSuperVtbl->pWhoAmI() != OBJ_IDENT_OBJ)) {
            if (this->pSuperVtbl->pAssign) {
                eRc = this->pSuperVtbl->pAssign(this, pOther);
                if (ERESULT_FAILED(eRc)) {
                    return eRc;
                }
            }
        }

        // Release objects and areas in other object.
#ifdef  XYZZY
        if (pOther->pArray) {
            obj_Release(pOther->pArray);
            pOther->pArray = OBJ_NIL;
        }
#endif

        // Create a copy of objects and areas in this object placing
        // them in other.
#ifdef  XYZZY
        if (this->pArray) {
            if (obj_getVtbl(this->pArray)->pCopy) {
                pOther->pArray = obj_getVtbl(this->pArray)->pCopy(this->pArray);
            }
            else {
                obj_Retain(this->pArray);
                pOther->pArray = this->pArray;
            }
        }
#endif

        // Copy other data from this object to other.
        //pOther->x     = this->x; 

        // Return to caller.
        eRc = ERESULT_SUCCESS;
    //eom:
        //FIXME: Implement the assignment.        
        eRc = ERESULT_NOT_IMPLEMENTED;
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                      C o m p a r e
    //---------------------------------------------------------------
    
    /*!
     Compare the two provided objects.
     @return    0  if this == other
                <0 if this < other
                >0 if this > other
     */
    int             Expr2Ast_Compare (
        EXPR2AST_DATA     *this,
        EXPR2AST_DATA     *pOther
    )
    {
        int             iRc = -1;
#ifdef  xyzzy        
        const
        char            *pStr1;
        const
        char            *pStr2;
#endif
        
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  EXPR2AST_SINGLETON
        if (OBJ_NIL == this) {
            this = Expr2Ast_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Expr2Ast_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!Expr2Ast_Validate(pOther)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -2;
        }
#endif

        //TODO: iRc = utf8_StrCmp(AStr_getData(this->pStr), AStr_getData(pOther->pStr));
     
        return iRc;
    }
    
   
 
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        Expr2Ast      *pCopy = Expr2Ast_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a EXPR2AST object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    EXPR2AST_DATA *     Expr2Ast_Copy (
        EXPR2AST_DATA       *this
    )
    {
        EXPR2AST_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!Expr2Ast_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef EXPR2AST_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = Expr2Ast_New( );
        if (pOther) {
            eRc = Expr2Ast_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
#endif
        
        // Return to caller.
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            Expr2Ast_Dealloc (
        OBJ_ID          objId
    )
    {
        EXPR2AST_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!Expr2Ast_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((EXPR2AST_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        //Expr2Ast_setAst(this, OBJ_NIL);  <= OpPrec should handle this for us.

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                         D e e p  C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        Expr2Ast      *pDeepCopy = Expr2Ast_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a EXPR2AST object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    EXPR2AST_DATA *     Expr2Ast_DeepCopy (
        EXPR2AST_DATA       *this
    )
    {
        EXPR2AST_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!Expr2Ast_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = Expr2Ast_New( );
        if (pOther) {
            eRc = Expr2Ast_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    /*!
     Disable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Expr2Ast_Disable (
        EXPR2AST_DATA   *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  EXPR2AST_SINGLETON
        if (OBJ_NIL == this) {
            this = Expr2Ast_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Expr2Ast_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Put code here...

        TRC_OBJ(this,"\tEnabled?: %s:\n", obj_Enable(this) ? "true" : "false");
        obj_Disable(this);
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    /*!
     Enable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Expr2Ast_Enable (
        EXPR2AST_DATA   *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  EXPR2AST_SINGLETON
        if (OBJ_NIL == this) {
            this = Expr2Ast_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Expr2Ast_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        TRC_OBJ(this,"\tEnabled?: %s:\n", obj_Enable(this) ? "true" : "false");
#ifdef   EXPR2AST_MSGS
        if (this->pMsgInfo) {
            this->pMsgInfo(this->pMsgObj, "Enabling object!\n");
        }
#endif
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    EXPR2AST_DATA *   Expr2Ast_Init (
        EXPR2AST_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(EXPR2AST_DATA);
        //ERESULT         eRc;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        /* cbSize can be zero if Alloc() was not called and we are
         * are passed the address of a zero'd area.
         */
        //cbSize = obj_getSize(this);       // cbSize must be set in Alloc().
        if (cbSize == 0) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

#ifdef  EXPR2AST_SUPER_DEFINED
        this = (OBJ_ID)OpPrec_Init((OPPREC_DATA *)this);   // Needed for Inheritance
#else
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_EXPR2AST);
#endif
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&Expr2Ast_Vtbl);
#ifdef  EXPR2AST_JSON_SUPPORT
        JsonIn_RegisterClass(Expr2Ast_Class());
#endif
        
        /*
        this->pArray = ObjArray_New( );
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        */

#ifdef NDEBUG
#else
        if (!Expr2Ast_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "Expr2Ast::sizeof(EXPR2AST_DATA) = %lu\n", 
                sizeof(EXPR2AST_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(EXPR2AST_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                      I s  E n a b l e d
    //---------------------------------------------------------------
    
    bool                Expr2Ast_IsEnabled (
        EXPR2AST_DATA       *this
    )
    {
        //ERESULT         eRc;
        bool            fRc = false;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  EXPR2AST_SINGLETON
        if (OBJ_NIL == this) {
            this = Expr2Ast_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Expr2Ast_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return fRc;
        }
#endif
        
        if (obj_IsEnabled(this)) {
            fRc = true;
        }
        
        // Return to caller.
        return fRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          P a r s e
    //---------------------------------------------------------------

    AST_ENTRY *     Expr2Ast_Parse (
        EXPR2AST_DATA   *this
    )
    {
        //ERESULT         eRc = ERESULT_SUCCESS;
        AST_ENTRY       *pEntry = OBJ_NIL;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  EXPR2AST_SINGLETON
        if (OBJ_NIL == this) {
            this = Expr2Ast_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Expr2Ast_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return pEntry;
        }
        if ((NULL == this->pInputAdvance) || (NULL == this->pInputAdvance)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return pEntry;
        }
#endif
        Expr2Ast_LookAhead(this, 1);    // Set up Lookahead.
        pEntry = OpPrec_Parse((OPPREC_DATA *)this);
        
        // Return to caller.
        return pEntry;
    }



    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    /*!
     Return information about this object. This method can translate
     methods to strings and vice versa, return the address of the
     object information structure.
     Example:
     @code
        // Return a method pointer for a string or NULL if not found. 
        void        *pMethod = Expr2Ast_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_DATA, an object's data is returned
                        if it fits in a "void *".
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "Expr2Ast", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          Expr2Ast_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        EXPR2AST_DATA     *this = objId;
        const
        char            *pStrA = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!Expr2Ast_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(EXPR2AST_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)Expr2Ast_Class();
                break;

            case OBJ_QUERYINFO_TYPE_DATA:
                switch (*pStrA) {
     
                    case 'L':
                        if (str_Compare("LookAhead", (char *)pStrA) == 0) {
                            return (void *)this->pFields;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;

                              
            case OBJ_QUERYINFO_TYPE_DATA_PTR:
                switch (*pStrA) {
     
                    case 'S':
                        if (str_Compare("SuperClass", (char *)pStrA) == 0) {
                            return (void *)(obj_getInfo(this)->pClassSuperObject);
                        }
                        break;
                        
                    default:
                        break;
                }
                break;

            case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStrA) {
                        
                    case 'C':
                        if (str_Compare("Class2Name", (char *)pStrA) == 0) {
                            return C_Expr_ClassToName;
                        }
                        break;

                    case 'D':
                        if (str_Compare("Disable", (char *)pStrA) == 0) {
                            return Expr2Ast_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStrA) == 0) {
                            return Expr2Ast_Enable;
                        }
                        break;

                    case 'N':
                        if (str_Compare("NextOperand", (char *)pStrA) == 0) {
                            return Expr2Ast_NextOperand;
                        }
                        if (str_Compare("NextOperator", (char *)pStrA) == 0) {
                            return Expr2Ast_NextOperator;
                        }
                        break;

                    case 'P':
                        if (str_Compare("Precedence", (char *)pStrA) == 0) {
                            return Expr2Ast_Precedence;
                        }
#ifdef  EXPR2AST_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStrA) == 0) {
                            return Expr2Ast_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStrA) == 0) {
                            return Expr2Ast_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStrA) == 0) {
                            return Expr2Ast_ToDebugString;
                        }
#ifdef  EXPR2AST_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStrA) == 0) {
                            return Expr2Ast_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStrA) == 0) {
                            return Expr2Ast_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == Expr2Ast_ToDebugString)
                    return "ToDebugString";
#ifdef  EXPR2AST_JSON_SUPPORT
                if (pData == Expr2Ast_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
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
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     Expr2Ast_ToDebugString (
        EXPR2AST_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        //uint32_t        i;
        //uint32_t        j;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Expr2Ast_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pInfo = obj_getInfo(this);
        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc = AStr_AppendPrint(
                    pStr,
                    "{%p(%s) size=%d retain=%d\n",
                    this,
                    pInfo->pClassName,
                    Expr2Ast_getSize(this),
                    obj_getRetainCount(this)
            );

#ifdef  XYZZY        
        if (this->pData) {
            if (((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString(
                                                    this->pData,
                                                    indent+3
                            );
                if (pWrkStr) {
                    AStr_Append(pStr, pWrkStr);
                    obj_Release(pWrkStr);
                }
            }
        }
#endif
        
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc =   AStr_AppendPrint(
                    pStr,
                    " %p(%s)}\n", 
                    this, 
                    pInfo->pClassName
                );
        USE_VAR(eRc);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

#ifdef NDEBUG
#else
    bool            Expr2Ast_Validate (
        EXPR2AST_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_EXPR2AST))
                ;
            else {
                // 'this' is not our kind of data. We really don't
                // know what that it is at this point. 
                return false;
            }
        }
        else {
            // 'this' is NULL.
            return false;
        }
        // Now, we have validated that we have a valid pointer in
        // 'this'.


        if (!(obj_getSize(this) >= sizeof(EXPR2AST_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef  __cplusplus
}
#endif


