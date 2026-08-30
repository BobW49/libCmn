// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//              Operator Precedence Parser (OpPrec) Object Support
//****************************************************************


/*
 * File:   OpPrec.c
 *  Generated 03/04/2023 08:33:53
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
#include        <OpPrec_internal.h>
#include        <JsonIn.h>
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


 
    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/



    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            OpPrec_task_body (
        void            *pData
    )
    {
        //OPPREC_DATA  *this = pData;
        TRC_OBJ(this, "%s:\n", __func__);
        
    }
#endif



    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    OPPREC_DATA *     OpPrec_Alloc (
        void
    )
    {
        OPPREC_DATA       *this;
        uint32_t        cbSize = sizeof(OPPREC_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    OPPREC_DATA *     OpPrec_New (
        void
    )
    {
        OPPREC_DATA       *this;
        
        this = OpPrec_Alloc( );
        if (this) {
            this = OpPrec_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                              A s t
    //---------------------------------------------------------------
    
    AST_DATA *          OpPrec_getAst (
        OPPREC_DATA         *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!OpPrec_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pAst;
    }
    
    
    bool                OpPrec_setAst (
        OPPREC_DATA         *this,
        AST_DATA            *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!OpPrec_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pAst) {
            obj_Release(this->pAst);
        }
        this->pAst = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                      M e s s a g e s
    //---------------------------------------------------------------

#ifdef   OPPREC_MSGS
    bool            OpPrec_setMsgs (
        OPPREC_DATA    *this,
        void            (*pMsgInfo)(OBJ_ID, const char *, ...),
        void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...),
        OBJ_ID          pObj
    )
    {
#ifdef NDEBUG
#else
        if (!OpPrec_Validate(this)) {
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
    
    uint16_t        OpPrec_getPriority (
        OPPREC_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!OpPrec_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            OpPrec_setPriority (
        OPPREC_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!OpPrec_Validate(this)) {
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
    
    uint32_t        OpPrec_getSize (
        OPPREC_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!OpPrec_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
#ifdef  OPPREC_SUPER_DEFINED
    OBJ_DATA *  OpPrec_getSuper (
        OPPREC_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!OpPrec_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return (OBJ_DATA *)this;
    }
#else
    OBJ_DATA *  OpPrec_getSuper (
        OPPREC_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!OpPrec_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return (OBJ_DATA *)this;
    }
#endif

    
    OBJ_IUNKNOWN *  OpPrec_getSuperVtbl (
        OPPREC_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!OpPrec_Validate(this)) {
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
        ERESULT eRc = OpPrec_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another OPPREC object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         OpPrec_Assign (
        OPPREC_DATA       *this,
        OPPREC_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!OpPrec_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!OpPrec_Validate(pOther)) {
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
    eom:
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
    int             OpPrec_Compare (
        OPPREC_DATA     *this,
        OPPREC_DATA     *pOther
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
#ifdef  OPPREC_SINGLETON
        if (OBJ_NIL == this) {
            this = OpPrec_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!OpPrec_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!OpPrec_Validate(pOther)) {
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
        OpPrec      *pCopy = OpPrec_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a OPPREC object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    OPPREC_DATA *     OpPrec_Copy (
        OPPREC_DATA       *this
    )
    {
        OPPREC_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!OpPrec_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef OPPREC_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = OpPrec_New( );
        if (pOther) {
            eRc = OpPrec_Assign(this, pOther);
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

    void            OpPrec_Dealloc (
        OBJ_ID          objId
    )
    {
        OPPREC_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!OpPrec_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((OPPREC_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        OpPrec_setAst(this, OBJ_NIL);

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
        OpPrec      *pDeepCopy = OpPrec_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a OPPREC object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    OPPREC_DATA *     OpPrec_DeepCopy (
        OPPREC_DATA       *this
    )
    {
        OPPREC_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!OpPrec_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = OpPrec_New( );
        if (pOther) {
            eRc = OpPrec_Assign(this, pOther);
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
    ERESULT         OpPrec_Disable (
        OPPREC_DATA     *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  OPPREC_SINGLETON
        if (OBJ_NIL == this) {
            this = OpPrec_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!OpPrec_Validate(this)) {
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
    ERESULT         OpPrec_Enable (
        OPPREC_DATA     *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  OPPREC_SINGLETON
        if (OBJ_NIL == this) {
            this = OpPrec_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!OpPrec_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        TRC_OBJ(this,"\tEnabled?: %s:\n", obj_Enable(this) ? "true" : "false");
#ifdef   OPPREC_MSGS
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
    //                  E x p r  P a r s e
    //---------------------------------------------------------------
 
    /*! Builds an AST from an expression parse.
     @return    topmost node index within tree of expression
     */
    AST_ENTRY *     OpPrec_ExprParse (
        OPPREC_DATA     *this
    )
    {
        ERESULT         eRc;
        AST_ENTRY       *pIndex = NULL;
        AST_ENTRY       *pExpr1 = NULL;
        AST_ENTRY       *pExpr2 = NULL;
        AST_ENTRY       *pExpr3 = NULL;
        AST_ENTRY       *pValueStk[OP_STACKMAX * 2];  // Operand Node Index Stack
        struct {
            int32_t         prec;
            AST_ENTRY       *pOper;
        }               operStk[OP_STACKMAX-1];     // Operator Class Stack
        //                                          // Need 2 values per operator
        int             cVal = 0;
        int             cOp = 0;
        int             i;
        int32_t         cls;
        int             prec;
        TOKEN_FIELDS    *pOperToken = NULL;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);

        // Operator Precedence relies on the fact that operands and opertors must
        // alternate and never be successive. So, the only acceptable sequence is:
        // <operand> <operator> <operand> (<operator> <operand>)*
        // where * == zero or more occurances. This also implies that this type of
        // parsing only recognizes binary operator (ie two operands for each operator).
        // Therefore, unary operators must be recognized and handled within the
        // NextOperand() method.
        for (;;) {
            
            //            *** GET AN OPERAND ***
            pExpr1 = this->pNextOperand(
                                        this->pObjParse,
                                        this->pAst
                                        );
            if (NULL == pExpr1) {
                if ((1 == cVal) && (0 == cOp)) {
                    // Everything has been reduced and we do not have a
                    // new operand. So, we are done parsing!
                    break;
                } else {
                    //TODO: Error
                    TRC_OBJ(this, "%s: ERROR - missing operand!\n", __func__);
                    DEBUG_BREAK();
                    return 0;
                }
            }
            pValueStk[cVal++] = pExpr1;
#ifdef NDEBUG
#else
                if (obj_Trace(this)) {
                    ASTR_DATA       *pStr = OBJ_NIL;
                    pStr = Ast_EntryToDebugString(this->pAst, pExpr1);
                    if (pStr) {
                        fprintf(stderr, "Push Operand: %s\n", AStr_getData(pStr));
                        obj_Release(pStr);
                        pStr = OBJ_NIL;
                    }
                }
#endif
#ifdef NDEBUG
#else
            if (obj_Trace(this)) {
                ASTR_DATA       *pStr = OBJ_NIL;
                fprintf(stderr, "Operand read - stack contains (bottom to top):\n");
                for (i = 0; i < cVal || i < cOp; i++) {
                    if (i < cVal) {
                        pStr = Ast_EntryToDebugString(this->pAst, pValueStk[i]);
                        if (pStr) {
                            fprintf(stderr, "%2d: %s\n\t", i, AStr_getData(pStr));
                            obj_Release(pStr);
                            pStr = OBJ_NIL;
                        }
                    }
                    if (i < cOp) {
                        pStr = Ast_EntryToDebugString(this->pAst, operStk[i].pOper);
                        if (pStr) {
                            fprintf(stderr, "%2d: %s\n\t", i, AStr_getData(pStr));
                            obj_Release(pStr);
                            pStr = OBJ_NIL;
                        }
                    }
                }
            }
#endif
            
            //              *** GET AN OPERATOR ***
#ifdef NDEBUG
#else
            if (obj_Trace(this)) {
                fprintf(stderr, "\tOperator Fields:\n");
                //FIXME: Expr2Ast_DumpToken(this, this->pFields);
            }
#endif
            pOperToken = this->pNextOperator(this->pObjParse);
            cls = pOperToken->cls;
            prec = this->pPrecedence(this->pObjParse, cls);
            if (-1 == prec) {       // NOT a valid binary operator
                TRC_OBJ(this, "\tOperator not found!\n");
                break;
            }
            pIndex =    Ast_EntryNewOperator(
                                    this->pAst,
                                    pOperToken->chr,
                                    cls,
                                    pOperToken
                        );
            /* Reduce all stacked operations that are of higher
             precedence than the current operator. */
            TRC_OBJ(this, "\tReducing stacked operations before stacking new operator...\n");
            while ((cVal > 1) && cOp && (prec > operStk[cOp-1].prec)) {
                // Reduce the stack.
                pExpr2 = pValueStk[--cVal];
                pExpr3 = pValueStk[--cVal];
                pExpr1 = operStk[--cOp].pOper;
                TRC_OBJ(this, "\tPop: operand %d\n", pExpr2);
                TRC_OBJ(this, "\tPop: operand %d\n", pExpr3);
                TRC_OBJ(this, "\tPop: operator %d\n", pExpr1);
                if (pExpr2 || pExpr3) {
                    eRc = Ast_EntryAddChild(this->pAst, pExpr1, pExpr2, pExpr3);
                }
                pValueStk[cVal++] = pExpr1;
#ifdef NDEBUG
#else
                if (obj_Trace(this)) {
                    ASTR_DATA       *pStr = OBJ_NIL;
                    pStr = Ast_EntryToDebugString(this->pAst, pExpr1);
                    if (pStr) {
                        fprintf(stderr, "Push Operand: %s\n", AStr_getData(pStr));
                        obj_Release(pStr);
                        pStr = OBJ_NIL;
                    }
                }
#endif
            }
            
#ifdef NDEBUG
#else
            if (obj_Trace(this)) {
                ASTR_DATA       *pStr = OBJ_NIL;
                fprintf(stderr, "Operator processed - stack contains (bottom to top):\n");
                for (i = 0; i < cVal || i < cOp; i++) {
                    if (i < cVal) {
                        pStr = Ast_EntryToDebugString(this->pAst, pValueStk[i]);
                        if (pStr) {
                            fprintf(stderr, "%2d: %s\n\t", i, AStr_getData(pStr));
                            obj_Release(pStr);
                            pStr = OBJ_NIL;
                        }
                    }
                    if (i < cOp) {
                        pStr = Ast_EntryToDebugString(this->pAst, operStk[i].pOper);
                        if (pStr) {
                            fprintf(stderr, "%2d: %s\n\t", i, AStr_getData(pStr));
                            obj_Release(pStr);
                            pStr = OBJ_NIL;
                        }
                    }
                }
            }
#endif
        
            if (prec > 0) {
                operStk[cOp].pOper = pIndex;
                operStk[cOp].prec = prec;
                cOp++;
#ifdef NDEBUG
#else
                if (obj_Trace(this)) {
                    ASTR_DATA       *pStr = OBJ_NIL;
                    pStr = Ast_EntryToDebugString(this->pAst, pIndex);
                    if (pStr) {
                        fprintf(stderr, "Push Operator: %s  prec:%d\n", AStr_getData(pStr), prec);
                        obj_Release(pStr);
                        pStr = OBJ_NIL;
                    }
                }
#endif
            } else {
                if ((1 == cVal) && (0 == cOp)) {
                    cVal--;
#ifdef NDEBUG
#else
                    if (obj_Trace(this)) {
                        ASTR_DATA       *pStr = OBJ_NIL;
                        pStr = Ast_EntryToDebugString(this->pAst, pValueStk[cVal]);
                        if (pStr) {
                            fprintf(stderr, "\tSUCCESS: root: %s\n", AStr_getData(pStr));
                            obj_Release(pStr);
                            pStr = OBJ_NIL;
                        }
                    }
#endif
                    return pValueStk[cVal];
                } else {
                    TRC_OBJ(this, "\tERROR - Left-over operations/operands (Incomplete operations)!\n");
                    DEBUG_BREAK();
                    return NULL;
                }
            }
        }       // End of for(;;)

        // Reduce all stacked operations.
        while ((cVal > 1) && cOp) {
            TRC_OBJ(this, "\tReducing left-over stacked operations...\n");
            // Reduce the stack.
            pExpr2 = pValueStk[--cVal];
            pExpr3 = pValueStk[--cVal];
            pExpr1 = operStk[--cOp].pOper;
            TRC_OBJ(this, "\tPop: operand %p\n", pExpr2);
            TRC_OBJ(this, "\tPop: operand %p\n", pExpr3);
            TRC_OBJ(this, "\tPop: operator %p\n", pExpr1);
            if (pExpr2 || pExpr3) {
                eRc = Ast_EntryAddChild(this->pAst, pExpr1, pExpr2, pExpr3);
            }
#ifdef NDEBUG
#else
            if (obj_Trace(this)) {
                ASTR_DATA       *pStr = OBJ_NIL;
                pStr = Ast_EntryToDebugString(this->pAst, pExpr1);
                if (pStr) {
                    fprintf(stderr, "Push Operand: %s\n", AStr_getData(pStr));
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                }
            }
#endif
            pValueStk[cVal++] = pExpr1;
        }
        
        if ((1 == cVal) && (0 == cOp)) {
            cVal--;
#ifdef NDEBUG
#else
            if (obj_Trace(this)) {
                ASTR_DATA       *pStr = OBJ_NIL;
                pStr = Ast_EntryToDebugString(this->pAst, pValueStk[cVal]);
                if (pStr) {
                    fprintf(stderr, "\tSUCCESS: root: %s\n", AStr_getData(pStr));
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                }
            }
#endif
            return pValueStk[cVal];
        } else {
            TRC_OBJ(this, "\tERROR - Left-over operations/operands (Incomplete operations)!\n");
            DEBUG_BREAK();
            return NULL;
        }
            
        return NULL;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    OPPREC_DATA *       OpPrec_Init (
        OPPREC_DATA         *this
    )
    {
        uint32_t            cbSize = sizeof(OPPREC_DATA);
        //ERESULT           eRc;
        
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

#ifdef  OPPREC_SUPER_DEFINED
        this = (OBJ_ID)obj_Init((OBJ_DATA *)this);   // Needed for Inheritance
#else
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_OPPREC);
#endif
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&OpPrec_Vtbl);
#ifdef  OPPREC_JSON_SUPPORT
        JsonIn_RegisterClass(OpPrec_Class());
#endif
        
#ifdef NDEBUG
#else
        if (!OpPrec_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "OpPrec::sizeof(OPPREC_DATA) = %lu\n", 
                sizeof(OPPREC_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(OPPREC_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                      I s  E n a b l e d
    //---------------------------------------------------------------
    
    bool                OpPrec_IsEnabled (
        OPPREC_DATA       *this
    )
    {
        //ERESULT         eRc;
        bool            fRc = false;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  OPPREC_SINGLETON
        if (OBJ_NIL == this) {
            this = OpPrec_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!OpPrec_Validate(this)) {
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

    AST_ENTRY *     OpPrec_Parse (
        OPPREC_DATA     *this
    )
    {
        //ERESULT         eRc = ERESULT_SUCCESS;
        AST_DATA        *pTree = Ast_New();
        AST_ENTRY       *pEntry = OBJ_NIL;
        OBJ_IUNKNOWN    *pUnk = NULL;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  EXPR2AST_SINGLETON
        if (OBJ_NIL == this) {
            this = OpPrec_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!OpPrec_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return pEntry;
        }
#endif
        if (pTree) {
            OpPrec_setAst(this, pTree);
            obj_Release(pTree);
        }
       
        if ((NULL == this->pNextOperand) || (NULL == this->pNextOperator)) {
            pUnk = obj_getVtbl(this);
            if (pUnk) {
                this->pObjParse = this;
                this->pNextOperand = pUnk->pQueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "NextOperand");
                this->pNextOperator = pUnk->pQueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "NextOperator");
                this->pPrecedence = pUnk->pQueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "Precedence");
                this->pClass2Name = pUnk->pQueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "Class2Name");
                if ((NULL == this->pNextOperand) || (NULL == this->pPrecedence)) {
                    this->pObjParse = OBJ_NIL;
                    this->pNextOperand = NULL;
                    this->pPrecedence = NULL;
                }
            }
        }
        if ((NULL == this->pNextOperand) || (NULL == this->pPrecedence)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return pEntry;
        }

        pEntry = OpPrec_ExprParse(this);
        
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
        void        *pMethod = OpPrec_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_DATA, an object's data is returned
                        if it fits in a "void *".
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "OpPrec", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          OpPrec_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        OPPREC_DATA     *this = objId;
        const
        char            *pStrA = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!OpPrec_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(OPPREC_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)OpPrec_Class();
                break;

            case OBJ_QUERYINFO_TYPE_DATA:
                switch (*pStrA) {
     
                    case 'A':
                        if (str_Compare("Ast", (char *)pStrA) == 0) {
                            return (void *)this->pAst;
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
                        
                    case 'D':
                        if (str_Compare("Disable", (char *)pStrA) == 0) {
                            return OpPrec_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStrA) == 0) {
                            return OpPrec_Enable;
                        }
                        break;

                    case 'P':
#ifdef  OPPREC_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStrA) == 0) {
                            return OpPrec_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStrA) == 0) {
                            return OpPrec_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStrA) == 0) {
                            return OpPrec_ToDebugString;
                        }
#ifdef  OPPREC_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStrA) == 0) {
                            return OpPrec_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStrA) == 0) {
                            return OpPrec_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == OpPrec_ToDebugString)
                    return "ToDebugString";
#ifdef  OPPREC_JSON_SUPPORT
                if (pData == OpPrec_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                      S e t u p
    //---------------------------------------------------------------

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
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  OPPREC_SINGLETON
        if (OBJ_NIL == this) {
            this = OpPrec_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!OpPrec_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        this->pObjParse = pObjParse;
        this->pNextOperand = pNextOperand;
        this->pPrecedence = pPrecedence;
        this->pClass2Name = pClass2Name;

        // Return to caller.
        return eRc;
    }


    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
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
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     OpPrec_ToDebugString (
        OPPREC_DATA      *this,
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
        if (!OpPrec_Validate(this)) {
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
                    OpPrec_getSize(this),
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
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

#ifdef NDEBUG
#else
    bool            OpPrec_Validate (
        OPPREC_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_OPPREC))
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


        if (!(obj_getSize(this) >= sizeof(OPPREC_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef  __cplusplus
}
#endif


