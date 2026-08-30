// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//              Abstract Syntax Tree (Ast) Object Support
//****************************************************************


/*
 * File:   Ast.c
 *  Generated 02/04/2023 09:41:47
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
#include        <Ast_internal.h>
#include        <array.h>
#include        <JsonIn.h>
#include        <ptrArray.h>
#include        <trace.h>
#include        <utf8.h>






#ifdef  __cplusplus
extern "C" {
#endif
    

#define USE_STATE_MACHINE_POST  1
#define USE_STATE_MACHINE_PRE   1
    
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

    //---------------------------------------------------------------
    //                  D e l e t e  E x i t
    //---------------------------------------------------------------

    ERESULT         Ast_DeleteExit (
        AST_DATA        *this,
        AST_ENTRY       *pRecord,
        void            *pArg3
    )
    {

        switch (pRecord->kind) {
            case AST_ENTRY_KIND_OBJECT:
                obj_Release(pRecord->u.pObj);
                pRecord->u.pObj = OBJ_NIL;
                pRecord->kind = AST_ENTRY_KIND_NO_DATA;
                break;
            case AST_ENTRY_KIND_OPCODE:
                obj_Release(pRecord->u.pOpcode);
                pRecord->u.pSym = OBJ_NIL;
                pRecord->kind = AST_ENTRY_KIND_NO_DATA;
                break;
             case AST_ENTRY_KIND_SYMBOL:
                obj_Release(pRecord->u.pSym);
                pRecord->u.pSym = OBJ_NIL;
                pRecord->kind = AST_ENTRY_KIND_NO_DATA;
                break;
            default:
                break;
        }

        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          E n t r y
    //---------------------------------------------------------------

    AST_ENTRY *     Ast_EntryNewInternal (
        AST_DATA        *this
    )
    {
        //ERESULT         eRc;
        AST_ENTRY       *pRcd = NULL;
        uint32_t        indexRcd = 0;


        pRcd = Blocks_RecordNew((BLOCKS_DATA *)this, &indexRcd);
        if (NULL == pRcd) {
            return 0;
        }
        memset(pRcd, 0, sizeof(AST_ENTRY));

        return pRcd;
    }


    // EntryVisit Compatible Print Method
    ERESULT         Ast_EntryPrint (
        AST_DATA        *this,              // visit.pObjectVisit
        AST_DATA        *this2,             // this object
        AST_ENTRY       *pEntry,
        uint16_t        indent,
        int             level,
        ASTR_DATA       *pStr
    )
    {
        ERESULT         eRc;
        //uint32_t        indexRcd = 0;

        if (OBJ_NIL == pStr)
            return ERESULT_INVALID_PARAMETER;
        
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        if (level) {
            AStr_AppendCharRepeatA(pStr, (level << 2), '-');
        }

        if (this->pClassToName) {
            eRc = AStr_AppendPrint(
                                   pStr,
                                   "(%d)%s  ",
                                   pEntry->type,
                                   this->pClassToName(pEntry->type)
                                   );
            USE_VAR(eRc);
        }
        
        switch (pEntry->kind) {
            case AST_ENTRY_KIND_CHARS:               // A string up to 7 chars long
                eRc = AStr_AppendPrint(pStr, "chrs: %s\n", pEntry->u.chrs);
                break;
            case AST_ENTRY_KIND_INTEGER:
                eRc = AStr_AppendPrint(pStr, "integer: %d\n", pEntry->u.integer);
                break;
            case AST_ENTRY_KIND_NUMBER:
                eRc = AStr_AppendPrint(pStr, "number: %f\n", pEntry->u.num);
                break;
            case AST_ENTRY_KIND_OBJECT:
                eRc = AStr_AppendPrint(pStr, "object: %p\n", pEntry->u.pObj);
                break;
            case AST_ENTRY_KIND_OPCODE:
                eRc =   AStr_AppendPrint(
                                         pStr,
                                         "opcode: %p - %s\n",
                                         pEntry->u.pOpcode,
                                         (pEntry->u.pOpcode ? Opcode_getNameA(pEntry->u.pOpcode) : "")
                        );
                break;
            case AST_ENTRY_KIND_POINTER:
                eRc = AStr_AppendPrint(pStr, "pointer: %p\n", pEntry->u.pVoid);
                break;
            case AST_ENTRY_KIND_STRING:
                eRc = AStr_AppendPrint(pStr, "string: %s\n", pEntry->u.pStr);
                break;
            case AST_ENTRY_KIND_SYMBOL:
                eRc =   AStr_AppendPrint(
                                         pStr,
                                         "symbol: %p - %s\n",
                                         pEntry->u.pSym,
                                         (pEntry->u.pSym ? Sym_getNameA(pEntry->u.pSym) : "")
                        );
                break;
            default:
                break;
        }
        USE_VAR(eRc);

        return ERESULT_SUCCESS;
    }


    ASTR_DATA *     Ast_EntryToAStrDebug (
        AST_DATA        *this,
        AST_ENTRY       *pEntry,
        uint16_t        indent
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        //uint32_t        indexRcd = 0;

        pStr = AStr_New();
        if (OBJ_NIL == pStr)
            return pStr;
        
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }

        eRc = AStr_AppendPrint(
                    pStr,
                    "{%p(%s) type=%d  (parent=%p child=%p sibling=%p) ",
                    this,
                    "AST_ENTRY",
                    pEntry->type,
                    pEntry->pParent,
                    pEntry->pChild,
                    pEntry->pSibling
            );
        USE_VAR(eRc);

        switch (pEntry->kind) {
            case AST_ENTRY_KIND_CHARS:               // A string up to 7 chars long
                eRc = AStr_AppendPrint(pStr, "chrs: %s\n", pEntry->u.chrs);
                break;
            case AST_ENTRY_KIND_INTEGER:
                eRc = AStr_AppendPrint(pStr, "integer: %d\n", pEntry->u.integer);
                break;
            case AST_ENTRY_KIND_NUMBER:
                eRc = AStr_AppendPrint(pStr, "number: %f\n", pEntry->u.num);
                break;
            case AST_ENTRY_KIND_OBJECT:
                eRc = AStr_AppendPrint(pStr, "object: %p\n", pEntry->u.pObj);
                break;
            case AST_ENTRY_KIND_POINTER:
                eRc = AStr_AppendPrint(pStr, "pointer: %p\n", pEntry->u.pVoid);
                break;
            case AST_ENTRY_KIND_STRING:
                eRc = AStr_AppendPrint(pStr, "string: %s\n", pEntry->u.pStr);
                break;
            case AST_ENTRY_KIND_SYMBOL:
                eRc = AStr_AppendPrint(pStr, "symbol: %p\n", pEntry->u.pSym);
                break;
            default:
                break;
        }
        USE_VAR(eRc);

        return pStr;
    }



    ERESULT         Ast_EntryVisitClose (
        AST_DATA        *this,
        AST_VISIT       *pVisit,
        AST_ENTRY       *pEntry
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        
        if (NULL == pVisit->pChildClose) {
            return eRc;
        }
        
        switch (pVisit->type) {
            case AST_VISIT_TYPE_EXTERNAL:
                pVisit->pChildClose(
                                 pVisit->pObjectClose,
                                 this,
                                 pEntry,
                                 pVisit->indent,
                                 pVisit->level,
                                 pVisit->pOther
                );
                break;
            case AST_VISIT_TYPE_INTERNAL:
                pVisit->pChildClose(
                                 pVisit->pObjectClose,
                                 this,
                                 pEntry,
                                 pVisit->indent,
                                 pVisit->level,
                                 pVisit
                );
                break;
        }
        
        return eRc;
    }
    
    
    ERESULT         Ast_EntryVisitEntry (
        AST_DATA        *this,
        AST_VISIT       *pVisit,
        AST_ENTRY       *pEntry
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        
        if (NULL == pVisit->pVisitor) {
            return eRc;
        }
        
        switch (pVisit->type) {
            case AST_VISIT_TYPE_EXTERNAL:
                pVisit->pVisitor(
                                   pVisit->pObjectVisit,
                                   this,
                                   pEntry,
                                   pVisit->indent,
                                   pVisit->level,
                                   pVisit->pOther
                                   );
                break;
            case AST_VISIT_TYPE_INTERNAL:
                pVisit->pVisitor(
                                   pVisit->pObjectVisit,
                                   this,
                                   pEntry,
                                   pVisit->indent,
                                   pVisit->level,
                                   pVisit
                                   );
                break;
        }
        
        return eRc;
    }
    
    
    ERESULT         Ast_EntryVisitOpen (
        AST_DATA        *this,
        AST_VISIT       *pVisit,
        AST_ENTRY       *pEntry
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        if (NULL == pVisit->pChildOpen) {
            return eRc;
        }
        
        switch (pVisit->type) {
            case AST_VISIT_TYPE_EXTERNAL:
                pVisit->pChildOpen(
                                   pVisit->pObjectOpen,
                                   this,
                                   pEntry,
                                   pVisit->indent,
                                   pVisit->level,
                                   pVisit->pOther
                                   );
                break;
            case AST_VISIT_TYPE_INTERNAL:
                pVisit->pChildOpen(
                                   pVisit->pObjectOpen,
                                   this,
                                   pEntry,
                                   pVisit->indent,
                                   pVisit->level,
                                   pVisit
                                   );
                break;
        }
        
        return eRc;
    }
    
    

    //---------------------------------------------------------------
    //        P o s t - O r d e r  E n t r y  V i s i t o r s
    //---------------------------------------------------------------

    /*
     We are representing a general tree using an unordered binary tree.
     Therefore, an inorder traveral of the binary tree is the same as
     a port-order traversal of a general tree. See page 296 of "Data
     Strructures Using C", Tenenbaum et al, Prentice-Hall, 1990,
     ISBN 0-13-199746-7.
     */
#ifdef USE_STATE_MACHINE_POST
    ERESULT         Ast_EntryPostOrder (
        AST_DATA        *this,
        AST_VISIT       *pVisit,
        AST_ENTRY       *pEntry
    )
    {
        //ERESULT         eRc;
        uint32_t        state;              // Scan Type

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Ast_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        state = AST_VISIT_STATE_DOWN_LEFT;

        if (NULL == pEntry) {
            return ERESULT_SUCCESS;
        }
        
        while (pEntry) {
            switch (state) {
                    
                case AST_VISIT_STATE_DOWN_LEFT:
                    pVisit->level++;
                    if (pVisit->pChildOpen) {
                        Ast_EntryVisitOpen(this, pVisit, pEntry);
                    }
                    if (pEntry->pChild) {
                        pEntry = pEntry->pChild;
                        // state = AST_VISIT_STATE_DOWN_LEFT;
                        break;
                    }
                    if (pVisit->pVisitor) {
                        Ast_EntryVisitEntry(this, pVisit, pEntry);
                    }
                    if (pEntry->pSibling) {
                        pEntry = pEntry->pSibling;
                        state = AST_VISIT_STATE_DOWN_RIGHT;
                        break;
                    }
                    if (pEntry->pParent) {
                        pEntry = pEntry->pParent;
                        state = AST_VISIT_STATE_UP_RIGHT;
                        break;
                    } else {
                        pEntry = NULL;
                    }
                    break;
                    
                case AST_VISIT_STATE_DOWN_RIGHT:
                    pVisit->level++;
                    if (pVisit->pChildOpen) {
                        Ast_EntryVisitOpen(this, pVisit, pEntry);
                    }
                    if (pEntry->pChild) {
                        pEntry = pEntry->pChild;
                        state = AST_VISIT_STATE_DOWN_LEFT;
                        break;
                    }
                    if (pVisit->pVisitor) {
                        Ast_EntryVisitEntry(this, pVisit, pEntry);
                    }
                    if (pEntry->pSibling) {
                        pEntry = pEntry->pSibling;
                        // state = AST_VISIT_STATE_DOWN_RIGHT;
                        break;
                    }
                    if (pEntry->pParent) {
                        pEntry = pEntry->pParent;
                        state = AST_VISIT_STATE_UP_RIGHT;
                    } else {
                        pEntry = NULL;
                    }
                    break;
                case AST_VISIT_STATE_UP_RIGHT:
                    pVisit->level--;
                    if (pVisit->pChildClose) {
                        Ast_EntryVisitClose(this, pVisit, pEntry);
                    }
                    if (pVisit->pVisitor) {
                        Ast_EntryVisitEntry(this, pVisit, pEntry);
                    }
                    if (pEntry->pSibling) {
                        pEntry = pEntry->pSibling;
                        state = AST_VISIT_STATE_DOWN_RIGHT;
                        break;
                    }
                    if (pEntry->pParent) {
                        pEntry = pEntry->pParent;
                        // state = AST_VISIT_STATE_UP_RIGHT;
                        break;
                    } else {
                        pEntry = NULL;
                        break;
                    }
                    break;
            }
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }
#else
    ERESULT         Ast_EntryPostOrder (
        AST_DATA        *this,
        AST_VISIT       *pVisit,
        AST_ENTRY       *pEntry
    )
    {
        ERESULT         eRc;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
        if (NULL == pEntry) {
            return ERESULT_SUCCESS;
        }
#ifdef NDEBUG
#else
        if (AST_ENTRY_KIND_CHARS == pEntry->kind) {
            TRC_OBJ(this, "\tchrs: %s\n", pEntry->u.chrs);
        }
#endif
        
        // Follow Child chain.
        if (pEntry->pChild) {
            pVisit->level++;
            if (pVisit->pChildOpen) {
                Ast_EntryVisitOpen(this, pVisit, pEntry);
            }
#ifdef NDEBUG
#else
        if (AST_ENTRY_KIND_CHARS == pEntry->pChild->kind) {
            TRC_OBJ(this, "\tRecurse chrs: %s\n", pEntry->pChild->u.chrs);
        }
#endif
            eRc = Ast_EntryPostOrder(this, pVisit, pEntry->pChild);
            if (ERESULT_FAILED(eRc)) {
                return eRc;
            }
            pVisit->level--;
            if (pVisit->pChildClose) {
                Ast_EntryVisitClose(this, pVisit, pEntry);
            }
        }

        // visit current node.
        if (pVisit->pVisitor) {
            Ast_EntryVisitEntry(this, pVisit, pEntry);
        }

        // Follow Sibling chain.
        if (pEntry->pSibling) {
            eRc = Ast_EntryPostOrder(this, pVisit, pEntry->pSibling);
            if (ERESULT_FAILED(eRc)) {
                return eRc;
            }
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }
#endif





    //---------------------------------------------------------------
    //          P r e - O r d e r  E n t r y  V i s i t o r s
    //---------------------------------------------------------------

    /*!
     Visit the root (or current node) then visit each child recursively.
     This is also known as a depth-first traversal.
     @param     this    NODETREE_DATA object pointer
     @param     pVisit  Visit Information
     @return    If successful, ERESULT_SUCCESS otherwise an ERESULT_*
                error.
     */
#ifdef USE_STATE_MACHINE_PRE
    ERESULT         Ast_EntryPreOrder (
        AST_DATA        *this,
        AST_VISIT       *pVisit,
        AST_ENTRY       *pEntry
    )
    {
        //ERESULT         eRc;
        uint32_t        state;              // Scan Type

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Ast_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        state = AST_VISIT_STATE_DOWN_LEFT;

        if (NULL == pEntry) {
            return ERESULT_SUCCESS;
        }
        
        while (pEntry) {
            switch (state) {
                case AST_VISIT_STATE_DOWN_LEFT:
                    pVisit->level++;
                    if (pVisit->pChildOpen) {
                        Ast_EntryVisitOpen(this, pVisit, pEntry);
                    }
                    if (pVisit->pVisitor) {
                        Ast_EntryVisitEntry(this, pVisit, pEntry);
                    }
                    if (pEntry->pChild) {
                        pEntry = pEntry->pChild;
                        // state = AST_VISIT_STATE_DOWN_LEFT;
                        break;
                    }
                    if (pEntry->pSibling) {
                        pEntry = pEntry->pSibling;
                        state = AST_VISIT_STATE_DOWN_RIGHT;
                    } else {
                        pEntry = pEntry->pParent;
                        state = AST_VISIT_STATE_UP_RIGHT;
                    }
                    break;
                case AST_VISIT_STATE_DOWN_RIGHT:
                    pVisit->level++;
                    if (pVisit->pChildOpen) {
                        Ast_EntryVisitOpen(this, pVisit, pEntry);
                    }
                    if (pVisit->pVisitor) {
                        Ast_EntryVisitEntry(this, pVisit, pEntry);
                    }
                    if (pEntry->pChild) {
                        pEntry = pEntry->pChild;
                        state = AST_VISIT_STATE_DOWN_LEFT;
                        break;
                    }
                    if (pEntry->pSibling) {
                        pEntry = pEntry->pSibling;
                        // state = AST_VISIT_STATE_DOWN_RIGHT;
                    } else {
                        pEntry = pEntry->pParent;
                        state = AST_VISIT_STATE_UP_RIGHT;
                    }
                    break;
                    /*** Not needed for this traversal
                case AST_VISIT_STATE_UP_LEFT:
                    pVisit->level--;
                    if (pEntry->pParent) {
                        if (pEntry->pParent->pSibling == pEntry) {
                            pEntry = pEntry->pParent;
                            // state = AST_VISIT_STATE_UP_LEFT;
                            break;
                        } else if (pEntry->pParent->pChild == pEntry) {
                            pEntry = pEntry->pParent;
                            state = AST_VISIT_STATE_UP_RIGHT;
                            break;
                        }
                    } else {
                        pEntry = NULL;
                        break;
                    }
                    break;
                     ***/
                case AST_VISIT_STATE_UP_RIGHT:
                    pVisit->level--;
                    if (pVisit->pChildClose) {
                        Ast_EntryVisitClose(this, pVisit, pEntry);
                    }
                    if (pEntry->pSibling) {
                        pEntry = pEntry->pSibling;
                        state = AST_VISIT_STATE_DOWN_RIGHT;
                        break;
                    }
                    if (pEntry->pParent) {
                        pEntry = pEntry->pParent;
                        // state = AST_VISIT_STATE_UP_RIGHT;
                        break;
                    } else {
                        pEntry = NULL;
                        break;
                    }
                    break;
            }
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }
#else
    ERESULT         Ast_EntryPreOrder (
        AST_DATA        *this,
        AST_VISIT       *pVisit,
        AST_ENTRY       *pEntry
    )
    {
        ERESULT         eRc;

        // Do initialization.
        if (NULL == pEntry) {
            return ERESULT_SUCCESS;
        }

        // visit current node.
        if (pVisit->pVisitor) {
            Ast_EntryVisitEntry(this, pVisit, pEntry);
        }

        // Follow Child chain.
        if (pEntry->pChild) {
            pVisit->level++;
            if (pVisit->pChildOpen) {
                Ast_EntryVisitOpen(this, pVisit, pEntry);
            }
            eRc = Ast_EntryPreOrder(this, pVisit, pEntry->pChild);
            if (ERESULT_FAILED(eRc)) {
                return eRc;
            }
            if (pVisit->pChildClose) {
                Ast_EntryVisitClose(this, pVisit, pEntry);
            }
            pVisit->level--;
        }

        // Follow Sibling chain.
        if (pEntry->pSibling) {
            eRc = Ast_EntryPreOrder(this, pVisit, pEntry->pSibling);
            if (ERESULT_FAILED(eRc)) {
                return eRc;
            }
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }
#endif



    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    AST_DATA *     Ast_Alloc (
        void
    )
    {
        AST_DATA       *this;
        uint32_t        cbSize = sizeof(AST_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    AST_DATA *     Ast_New (
        void
    )
    {
        AST_DATA       *this;
        
        this = Ast_Alloc( );
        if (this) {
            this = Ast_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                      M e s s a g e s
    //---------------------------------------------------------------

#ifdef   AST_MSGS
    bool            Ast_setMsgs (
        AST_DATA    *this,
        void            (*pMsgInfo)(OBJ_ID, const char *, ...),
        void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...),
        OBJ_ID          pObj
    )
    {
#ifdef NDEBUG
#else
        if (!Ast_Validate(this)) {
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
    
    uint16_t        Ast_getPriority (
        AST_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Ast_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            Ast_setPriority (
        AST_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!Ast_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        return true;
    }



    //---------------------------------------------------------------
    //                          R o o t
    //---------------------------------------------------------------
    
    AST_ENTRY *     Ast_getRoot (
        AST_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Ast_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->pRoot;
    }


    bool            Ast_setRoot (
        AST_DATA        *this,
        AST_ENTRY       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Ast_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->pRoot = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        Ast_getSize (
        AST_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!Ast_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                         S t a c k
    //---------------------------------------------------------------
    
    PTRARRAY_DATA * Ast_getStk (
        AST_DATA        *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Ast_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStk;
    }
    
    
    bool            Ast_setStk (
        AST_DATA        *this,
        PTRARRAY_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Ast_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pStk) {
            obj_Release(this->pStk);
        }
        this->pStk = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
#ifdef  AST_SUPER_DEFINED
    BLOCKS_DATA *  Ast_getSuper (
        AST_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Ast_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return (BLOCKS_DATA *)this;
    }
#else
    OBJ_DATA *  Ast_getSuper (
        AST_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Ast_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return (OBJ_DATA *)this;
    }
#endif

    
    OBJ_IUNKNOWN *  Ast_getSuperVtbl (
        AST_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Ast_Validate(this)) {
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
        ERESULT eRc = Ast_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another AST object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         Ast_Assign (
        AST_DATA       *this,
        AST_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!Ast_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Ast_Validate(pOther)) {
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
    int             Ast_Compare (
        AST_DATA     *this,
        AST_DATA     *pOther
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
#ifdef  AST_SINGLETON
        if (OBJ_NIL == this) {
            this = Ast_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Ast_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!Ast_Validate(pOther)) {
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
        Ast      *pCopy = Ast_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a AST object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    AST_DATA *     Ast_Copy (
        AST_DATA       *this
    )
    {
        AST_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!Ast_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef AST_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = Ast_New( );
        if (pOther) {
            eRc = Ast_Assign(this, pOther);
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

    void            Ast_Dealloc (
        OBJ_ID          objId
    )
    {
        AST_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!Ast_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((AST_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        Ast_setStk(this, OBJ_NIL);

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
        Ast      *pDeepCopy = Ast_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a AST object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    AST_DATA *     Ast_DeepCopy (
        AST_DATA       *this
    )
    {
        AST_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!Ast_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = Ast_New( );
        if (pOther) {
            eRc = Ast_Assign(this, pOther);
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
    ERESULT         Ast_Disable (
        AST_DATA        *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  AST_SINGLETON
        if (OBJ_NIL == this) {
            this = Ast_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Ast_Validate(this)) {
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
    ERESULT         Ast_Enable (
        AST_DATA        *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  AST_SINGLETON
        if (OBJ_NIL == this) {
            this = Ast_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Ast_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        TRC_OBJ(this,"\tEnabled?: %s:\n", obj_Enable(this) ? "true" : "false");
#ifdef   AST_MSGS
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
    //                          E n t r y
    //---------------------------------------------------------------

    ERESULT         Ast_EntryAddChild (
        AST_DATA        *this,
        AST_ENTRY       *pParent,
        AST_ENTRY       *pChild1,
        AST_ENTRY       *pChild2
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        AST_ENTRY       *pEntry = NULL;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!Ast_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        if (pParent && pChild1) {
            if (NULL == pParent->pChild) {
                pParent->pChild = pChild1;
            } else {
                pEntry = pParent->pChild;
                while (pEntry->pSibling) {
                    pEntry = pEntry->pSibling;
                }
                pEntry->pSibling = pChild1;
            }
            pChild1->pParent = pParent;
        } else {
            return ERESULT_DATA_MISSING;
        }

        if (pParent && pChild2) {
            if (NULL == pParent->pChild) {
                pParent->pChild = pChild2;
            } else {
                if (NULL == pEntry) {
                    pEntry = pParent->pChild;
                }
                while (pEntry->pSibling) {
                    pEntry = pEntry->pSibling;
                }
                pEntry->pSibling = pChild2;
            }
            pChild2->pParent = pParent;
        }
        
        // Return to caller.
        return eRc;
    }


    ERESULT         Ast_EntryAddSibling (
        AST_DATA        *this,
        AST_ENTRY       *pRoot,
        AST_ENTRY       *pSibling1,
        AST_ENTRY       *pSibling2
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        AST_ENTRY       *pEntry = NULL;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!Ast_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        if (pRoot && pSibling1) {
            if (NULL == pRoot->pSibling) {
                pRoot->pSibling = pSibling1;
            } else {
                pEntry = pRoot;
                while (pEntry->pSibling) {
                    pEntry = pEntry->pSibling;
                }
                pEntry->pSibling = pSibling1;
            }
            pSibling1->pParent = pRoot->pParent;
        } else {
            return ERESULT_DATA_MISSING;
        }

        if (pRoot && pSibling2) {
            if (NULL == pRoot->pSibling) {
                pRoot->pSibling = pSibling2;
            } else {
                if (NULL == pEntry) {
                    pEntry = pRoot->pSibling;
                }
                while (pEntry->pSibling) {
                    pEntry = pEntry->pSibling;
                }
                pEntry->pSibling = pSibling2;
            }
            pSibling2->pParent = pRoot->pParent;
        }
        
        // Return to caller.
        return eRc;
    }


    AST_ENTRY *     Ast_EntryCopy (
        AST_DATA        *this,
        AST_ENTRY       *pRoot
    )
    {
        //ERESULT         eRc = ERESULT_SUCCESS;
        AST_ENTRY       *pEntry = NULL;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!Ast_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return NULL;
        }
#endif

        pEntry = Ast_EntryNewInternal(this);
        pEntry->type = pRoot->type;
        pEntry->kind = pRoot->kind;
        pEntry->u = pRoot->u;
        switch (pRoot->kind) {
            case AST_ENTRY_KIND_OBJECT:
                obj_Retain(pEntry->u.pObj);
                break;
            case AST_ENTRY_KIND_OPCODE:
                obj_Retain(pEntry->u.pOpcode);
                break;
            case AST_ENTRY_KIND_SYMBOL:
                obj_Retain(pEntry->u.pSym);
                break;
            default:
                break;
        }
        
        if (pRoot->pSibling != pRoot)    
            pEntry->pSibling = Ast_EntryCopy(this, pRoot->pSibling);
        if (pRoot->pChild != pRoot)
            pEntry->pChild = Ast_EntryCopy(this, pRoot->pChild);
        
        // Return to caller.
        return pEntry;
    }


    AST_ENTRY *     Ast_EntryNewChars (
        AST_DATA        *this,
        const
        char            *pStr,
        int16_t         type,
        TOKEN_FIELDS    *pToken
    )
    {
        //ERESULT         eRc = ERESULT_SUCCESS;
        AST_ENTRY       *pEntry = NULL;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!Ast_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return NULL;
        }
#endif
        if (strlen(pStr) > 7)
            return NULL;

        pEntry = Ast_EntryNewInternal(this);
        if (pEntry) {
            if (pToken) {
                memmove(&pEntry->def, pToken, sizeof(TOKEN_FIELDS));
            }
            pEntry->type = type;
            pEntry->kind = AST_ENTRY_KIND_CHARS;
            strcpy(pEntry->u.chrs, pStr);
        }

        // Return to caller.
        return pEntry;
    }


    AST_ENTRY *     Ast_EntryNewClose (
        AST_DATA        *this
    )
    {
        //ERESULT         eRc = ERESULT_SUCCESS;
        AST_ENTRY       *pEntry = NULL;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!Ast_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return NULL;
        }
#endif
        pEntry = Ast_EntryNewInternal(this);
        if (pEntry) {
            pEntry->type = this->typeClose;
            pEntry->kind = AST_ENTRY_KIND_CHARS;
            strcpy(pEntry->u.chrs, ")");
        }

        // Return to caller.
        return pEntry;
    }


    AST_ENTRY *     Ast_EntryNewInteger (
        AST_DATA        *this,
        int64_t         integer,
        int16_t         type,
        TOKEN_FIELDS    *pToken
    )
    {
        //ERESULT         eRc = ERESULT_SUCCESS;
        AST_ENTRY       *pEntry = NULL;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!Ast_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return NULL;
        }
#endif

        pEntry = Ast_EntryNewInternal(this);
        if (pEntry) {
            if (pToken) {
                memmove(&pEntry->def, pToken, sizeof(TOKEN_FIELDS));
            }
            pEntry->type = type;
            pEntry->kind = AST_ENTRY_KIND_INTEGER;
            pEntry->u.integer = integer;
        }

        // Return to caller.
        return pEntry;
    }


    AST_ENTRY *     Ast_EntryNewNumber (
        AST_DATA        *this,
        double          number,
        int16_t         type,
        TOKEN_FIELDS    *pToken
    )
    {
        //ERESULT         eRc = ERESULT_SUCCESS;
        AST_ENTRY       *pEntry = NULL;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!Ast_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return NULL;
        }
#endif

        pEntry = Ast_EntryNewInternal(this);
        if (pEntry) {
            if (pToken) {
                memmove(&pEntry->def, pToken, sizeof(TOKEN_FIELDS));
            }
            pEntry->type = type;
            pEntry->kind = AST_ENTRY_KIND_NUMBER;
            pEntry->u.num = number;
        }

        // Return to caller.
        return pEntry;
    }


    AST_ENTRY *     Ast_EntryNewObject (
        AST_DATA        *this,
        OBJ_ID          pObj,
        int16_t         type,
        TOKEN_FIELDS    *pToken
    )
    {
        //ERESULT         eRc = ERESULT_SUCCESS;
        AST_ENTRY       *pEntry = NULL;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!Ast_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return NULL;
        }
#endif

        pEntry = Ast_EntryNewInternal(this);
        if (pEntry) {
            if (pToken) {
                memmove(&pEntry->def, pToken, sizeof(TOKEN_FIELDS));
            }
            pEntry->type = type;
            pEntry->kind = AST_ENTRY_KIND_SYMBOL;
            if (pObj) {
                obj_Retain(pObj);
                pEntry->u.pObj = pObj;
            }
        }

        // Return to caller.
        return pEntry;
    }


    AST_ENTRY *     Ast_EntryNewOpcode (
        AST_DATA        *this,
        OPCODE_DATA     *pOpcode,
        int16_t         type,
        TOKEN_FIELDS    *pToken
    )
    {
        //ERESULT         eRc = ERESULT_SUCCESS;
        AST_ENTRY       *pEntry = NULL;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!Ast_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return NULL;
        }
#endif

        pEntry = Ast_EntryNewInternal(this);
        if (pEntry) {
            if (pToken) {
                memmove(&pEntry->def, pToken, sizeof(TOKEN_FIELDS));
            }
            pEntry->type = type;
            pEntry->kind = AST_ENTRY_KIND_SYMBOL;
            if (pOpcode) {
                obj_Retain(pOpcode);
                pEntry->u.pOpcode = pOpcode;
            }
        }

        // Return to caller.
        return pEntry;
    }


    AST_ENTRY *     Ast_EntryNewOpen (
        AST_DATA        *this
    )
    {
        //ERESULT         eRc = ERESULT_SUCCESS;
        AST_ENTRY       *pEntry = NULL;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!Ast_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return NULL;
        }
#endif
        pEntry = Ast_EntryNewInternal(this);
        if (pEntry) {
            pEntry->type = this->typeOpen;
            pEntry->kind = AST_ENTRY_KIND_CHARS;
            strcpy(pEntry->u.chrs, "(");
        }

        // Return to caller.
        return pEntry;
    }


    AST_ENTRY *     Ast_EntryNewOperator (
        AST_DATA        *this,
        const
        char            *pStrA,
        int16_t         type,
        TOKEN_FIELDS    *pToken
    )
    {
        //ERESULT         eRc = ERESULT_SUCCESS;
        AST_ENTRY       *pEntry = NULL;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!Ast_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return NULL;
        }
#endif
        if (strlen(pStrA) > 7)
            return NULL;

        pEntry = Ast_EntryNewInternal(this);
        if (pEntry) {
            if (pToken) {
                memmove(&pEntry->def, pToken, sizeof(TOKEN_FIELDS));
            }
            pEntry->type = type;
            pEntry->kind = AST_ENTRY_KIND_CHARS;
            strcpy(pEntry->u.chrs, pStrA);
        }

        // Return to caller.
        return pEntry;
    }


    AST_ENTRY *     Ast_EntryNewPointer (
        AST_DATA        *this,
        void            *pVoid,
        int16_t         type,
        TOKEN_FIELDS    *pToken
    )
    {
        //ERESULT         eRc = ERESULT_SUCCESS;
        AST_ENTRY       *pEntry = NULL;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!Ast_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return NULL;
        }
#endif

        pEntry = Ast_EntryNewInternal(this);
        if (pEntry) {
            if (pToken) {
                memmove(&pEntry->def, pToken, sizeof(TOKEN_FIELDS));
            }
            pEntry->type = type;
            pEntry->kind = AST_ENTRY_KIND_POINTER;
            pEntry->u.pVoid = pVoid;
        }

        // Return to caller.
        return pEntry;
    }


    AST_ENTRY *     Ast_EntryNewString (
        AST_DATA        *this,
        char            *pStr,
        int16_t         type,
        TOKEN_FIELDS    *pToken
    )
    {
        //ERESULT         eRc = ERESULT_SUCCESS;
        AST_ENTRY       *pEntry = NULL;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!Ast_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return NULL;
        }
#endif

        pEntry = Ast_EntryNewInternal(this);
        if (pEntry) {
            if (pToken) {
                memmove(&pEntry->def, pToken, sizeof(TOKEN_FIELDS));
            }
            pEntry->type = type;
            pEntry->kind = AST_ENTRY_KIND_POINTER;
            pEntry->u.pStr = pStr;
        }

        // Return to caller.
        return pEntry;
    }


    AST_ENTRY *     Ast_EntryNewSymbol (
        AST_DATA        *this,
        SYM_DATA        *pSym,
        int16_t         type,
        TOKEN_FIELDS    *pToken
    )
    {
        //ERESULT         eRc = ERESULT_SUCCESS;
        AST_ENTRY       *pEntry = NULL;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!Ast_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return NULL;
        }
#endif

        pEntry = Ast_EntryNewInternal(this);
        if (pEntry) {
            if (pToken) {
                memmove(&pEntry->def, pToken, sizeof(TOKEN_FIELDS));
            }
            pEntry->type = type;
            pEntry->kind = AST_ENTRY_KIND_SYMBOL;
            if (pSym) {
                obj_Retain(pSym);
                pEntry->u.pSym = pSym;
            }
        }

        // Return to caller.
        return pEntry;
    }


    ASTR_DATA *     Ast_EntryToDebugString (
        AST_DATA        *this,
        AST_ENTRY       *pEntry
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        ASTR_DATA       *pStr = AStr_New();

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  AST_SINGLETON
        if (OBJ_NIL == this) {
            this = Ast_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Ast_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
#endif
        if (OBJ_NIL == pStr) {
            return OBJ_NIL;
        }

        if (this->pClassToName) {
            eRc =   AStr_AppendPrint(
                                     pStr,
                                     "AST_Entry: %p  %d:%s ",
                                     pEntry,
                                     pEntry->type,
                                     this->pClassToName(pEntry->type)
                                     );
            USE_VAR(eRc);
        }
        switch (pEntry->kind) {
            case AST_ENTRY_KIND_NO_DATA:
                break;
            case AST_ENTRY_KIND_CHARS:               // A string up to 7 chars long
                eRc = AStr_AppendPrint(pStr, "chars: %s\n", pEntry->u.chrs);
                break;
            case AST_ENTRY_KIND_INTEGER:
                eRc = AStr_AppendPrint(pStr, "integer: %d\n", pEntry->u.integer);
                break;
            case AST_ENTRY_KIND_NUMBER:
                eRc = AStr_AppendPrint(pStr, "number: %f\n", pEntry->u.num);
                break;
            case AST_ENTRY_KIND_OBJECT:
                eRc = AStr_AppendPrint(pStr, "object: %p\n", pEntry->u.pObj);
                break;
            case AST_ENTRY_KIND_OPCODE:
                eRc = AStr_AppendPrint(pStr, "object: %p\n", pEntry->u.pOpcode);
                break;
            case AST_ENTRY_KIND_POINTER:
                eRc = AStr_AppendPrint(pStr, "pointer: %p\n", pEntry->u.pVoid);
                break;
            case AST_ENTRY_KIND_STRING:
                eRc = AStr_AppendPrint(pStr, "string: %s\n", pEntry->u.pStr);
                break;
            case AST_ENTRY_KIND_SYMBOL:
                eRc = AStr_AppendPrint(pStr, "symbol: %p\n", pEntry->u.pSym);
                break;
        }
        USE_VAR(eRc);
        
        // Return to caller.
        return pStr;
    }


    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    AST_DATA *   Ast_Init (
        AST_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(AST_DATA);
        ERESULT         eRc;
        bool            fRc;
        
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

#ifdef  AST_SUPER_DEFINED
        this = (OBJ_ID)Blocks_Init((BLOCKS_DATA *)this);   // Needed for Inheritance
#else
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_AST);
#endif
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&Ast_Vtbl);
#ifdef  AST_JSON_SUPPORT
        JsonIn_RegisterClass(Ast_Class());
#endif
        
        fRc =   Blocks_setDeleteExit(
                                   (BLOCKS_DATA *)this,
                                   (void *)Ast_DeleteExit,
                                   this,
                                   NULL
                );
        USE_VAR(fRc);
        eRc = Blocks_SetupSizes((BLOCKS_DATA *)this, 0, sizeof(AST_ENTRY));
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

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
        if (!Ast_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "Ast::sizeof(AST_DATA) = %lu\n", 
                sizeof(AST_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(AST_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                      I s  E n a b l e d
    //---------------------------------------------------------------
    
    bool                Ast_IsEnabled (
        AST_DATA       *this
    )
    {
        //ERESULT         eRc;
        bool            fRc = false;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  AST_SINGLETON
        if (OBJ_NIL == this) {
            this = Ast_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Ast_Validate(this)) {
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
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    /*!
     Return information about this object. This method can translate
     methods to strings and vice versa, return the address of the
     object information structure.
     Example:
     @code
        // Return a method pointer for a string or NULL if not found. 
        void        *pMethod = Ast_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_DATA, an object's data is returned
                        if it fits in a "void *".
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "Ast", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          Ast_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        AST_DATA     *this = objId;
        const
        char            *pStrA = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!Ast_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(AST_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)Ast_Class();
                break;

            case OBJ_QUERYINFO_TYPE_DATA:
                switch (*pStrA) {
     
                    case 'S':
                        if (str_Compare("Stack", (char *)pStrA) == 0) {
                            return (void *)this->pStk;
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
                            return Ast_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStrA) == 0) {
                            return Ast_Enable;
                        }
                        break;

                    case 'P':
#ifdef  AST_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStrA) == 0) {
                            return Ast_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStrA) == 0) {
                            return Ast_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStrA) == 0) {
                            return Ast_ToDebugString;
                        }
#ifdef  AST_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStrA) == 0) {
                            return Ast_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStrA) == 0) {
                            return Ast_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == Ast_ToDebugString)
                    return "ToDebugString";
#ifdef  AST_JSON_SUPPORT
                if (pData == Ast_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                          S e t u p
    //---------------------------------------------------------------
    
    bool            Ast_Setup (
        AST_DATA        *this,
        int16_t         typeClose,
        int16_t         typeOpen,       // Normally means '('
        const
        char *          (*pClassToName)(int32_t)
    )
    {
#ifdef NDEBUG
#else
        if (!Ast_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->typeClose    = typeClose;
        this->typeOpen     = typeOpen;
        this->pClassToName = pClassToName;

        return true;
    }



    //---------------------------------------------------------------
    //                T o  L i n e a r i z a t i o n
    //---------------------------------------------------------------

    PTRARRAY_DATA * Ast_ToLinearizationPost(
        AST_DATA        *this,
        AST_ENTRY       *pRoot
    )
    {
        PTRARRAY_DATA   *pArray = ptrArray_New();
        AST_ENTRY       *pEntry = NULL;
        uint32_t        state;              // Scan Type

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Ast_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        if (NULL == pRoot) {
            if (NULL == this->pRoot) {
                obj_Release(pArray);
                return OBJ_NIL;
            }
            pRoot = this->pRoot;
        }
        pEntry = pRoot;
        if (NULL == this->pClose) {
            this->pClose = Ast_EntryNewClose(this);
        }
        if (NULL == this->pOpen) {
            this->pOpen = Ast_EntryNewOpen(this);
        }
        state = AST_VISIT_STATE_DOWN_LEFT;

        if (NULL == pEntry) {
            obj_Release(pArray);
            return OBJ_NIL;
        }
        
        while (pEntry) {
            switch (state) {
                    
                case AST_VISIT_STATE_DOWN_LEFT:
                    ptrArray_AppendData(pArray, this->pOpen, NULL);
                    if (pEntry->pChild) {
                        pEntry = pEntry->pChild;
                        state = AST_VISIT_STATE_DOWN_LEFT;
                        break;
                    }
                    ptrArray_AppendData(pArray, pEntry, NULL);  // Visit node.
                    if (pEntry->pSibling) {
                        pEntry = pEntry->pSibling;
                        state = AST_VISIT_STATE_DOWN_RIGHT;
                        break;
                    }
                    if (pEntry->pParent) {
                        pEntry = pEntry->pParent;
                        state = AST_VISIT_STATE_UP_RIGHT;
                        break;
                    } else {
                        pEntry = NULL;
                    }
                    break;
                    
                case AST_VISIT_STATE_DOWN_RIGHT:
                    ptrArray_AppendData(pArray, this->pOpen, NULL);
                    if (pEntry->pChild) {
                        pEntry = pEntry->pChild;
                        state = AST_VISIT_STATE_DOWN_LEFT;
                        break;
                    }
                    ptrArray_AppendData(pArray, pEntry, NULL);  // Visit node.
                    if (pEntry->pSibling) {
                        pEntry = pEntry->pSibling;
                        // state = AST_VISIT_STATE_DOWN_RIGHT;
                        break;
                    }
                    if (pEntry->pParent) {
                        pEntry = pEntry->pParent;
                        state = AST_VISIT_STATE_UP_RIGHT;
                    } else {
                        pEntry = NULL;
                    }
                    break;
                case AST_VISIT_STATE_UP_RIGHT:
                    ptrArray_AppendData(pArray, this->pClose, NULL);
                    ptrArray_AppendData(pArray, pEntry, NULL);  // Visit node.
                    if (pEntry->pSibling) {
                        pEntry = pEntry->pSibling;
                        state = AST_VISIT_STATE_DOWN_RIGHT;
                        break;
                    }
                    if (pEntry->pParent) {
                        pEntry = pEntry->pParent;
                        // state = AST_VISIT_STATE_UP_RIGHT;
                        break;
                    } else {
                        pEntry = NULL;
                        break;
                    }
                    break;
            }
        }

        // Return to caller.
        return pArray;
    }



    PTRARRAY_DATA * Ast_ToLinearizationPre(
        AST_DATA        *this,
        AST_ENTRY       *pRoot
    )
    {
        PTRARRAY_DATA   *pStack = ptrArray_New();
        PTRARRAY_DATA   *pArray = ptrArray_New();
        AST_ENTRY       *pEntry;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Ast_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        if ((OBJ_NIL == pStack) || (OBJ_NIL == pArray)) {
            obj_Release(pStack);
            obj_Release(pArray);
            return NULL;
        }
        if (NULL == pRoot) {
            obj_Release(pStack);
            obj_Release(pArray);
            return NULL;
        }
        if (NULL == this->pClose) {
            this->pClose = Ast_EntryNewClose(this);
        }
        if (NULL == this->pOpen) {
            this->pOpen = Ast_EntryNewOpen(this);
        }

        /*  Pre-order traversal visits the current or parent node of the
            children first, then the left children and lastly, the right
            children.
         */
        pEntry = pRoot;
        ptrArray_AppendData(pArray, this->pOpen, NULL);
        for (;;) {
            if (NULL == pEntry) {
                if (0 == ptrArray_getSize(pStack)) {
                    break;
                }
                pEntry = ptrArray_Pop(pStack);
                pEntry = pEntry->pSibling;
                if (NULL == pEntry) {
                    ptrArray_AppendData(pArray, this->pClose, NULL);
                }
            } else {
                ptrArray_AppendData(pArray, pEntry, NULL);  // Visit current/parent.
                ptrArray_Push(pStack, pEntry);              // Push Parent.
                // Now explore left-most child.
                pEntry = pEntry->pChild;
                if (pEntry) {
                    ptrArray_AppendData(pArray, this->pOpen, NULL);
                }
            }
        }

        // Return to caller.
        obj_Release(pStack);
        return pArray;
    }



    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
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
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     Ast_ToDebugString (
        AST_DATA      *this,
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
        if (!Ast_Validate(this)) {
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
                    Ast_getSize(this),
                    obj_getRetainCount(this)
            );
        USE_VAR(eRc);

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
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        PTRARRAY_DATA   *pArray;
        //ASTR_DATA       *pWrkStr;
        uint32_t        i;
        uint32_t        iMax;
        //uint32_t        j;
        //uint32_t        jMax;
        int             lvl = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Ast_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pArray = Ast_ToLinearizationPre(this, pRoot);
        if (OBJ_NIL == pArray) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        pStr = AStr_New();
        if (NULL == pPrintEntry) {
            pPrintEntry = (void *)Ast_EntryPrint;
            pPrintObj  = this;
        }
        
        if (pStr && pArray) {
            iMax = ptrArray_getSize(pArray);
            for (i=0; i<iMax; i++) {
                AST_ENTRY           *pNode = ptrArray_GetData(pArray, i+1);
                if (pNode) {
                    if (this->pOpen == pNode) {
                        lvl++;
                    } else if (this->pClose == pNode) {
                        lvl--;
                    } else {
                        eRc = pPrintEntry(pPrintObj, (void *)this, pNode, indent, lvl, pStr);
                        if (ERESULT_FAILED(eRc)) {
                            break;
                        }
                    }
                }
            }
        }
        
        obj_Release(pArray);
        //pArray = OBJ_NIL;
        return pStr;
    }
    
    

    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

#ifdef NDEBUG
#else
    bool            Ast_Validate (
        AST_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_AST))
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


        if (!(obj_getSize(this) >= sizeof(AST_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    //---------------------------------------------------------------
    //                      V i s i t
    //---------------------------------------------------------------

    ERESULT         Ast_VisitBreadthFirst (
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
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        ARRAY_DATA      *pQueue = OBJ_NIL;
        AST_BFS         visit;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Ast_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        if (NULL == pEntry) {
            if (NULL == this->pRoot) {
                return ERESULT_SUCCESS;
            }
            pEntry = this->pRoot;
        }

        pQueue = array_NewWithSize(sizeof(AST_BFS));
        if (pQueue == OBJ_NIL) {
            DEBUG_BREAK();
            return ERESULT_OUT_OF_MEMORY;
        }

        if (NULL == pVisitor) {
            pVisitor = (void *)Ast_EntryPrint;
            pObject = this;
        }
        visit.pEntry = pEntry;
        visit.level = 0;
        eRc = array_Enqueue(pQueue, &visit);
        
        while (array_getSize(pQueue)) {
            eRc = array_Dequeue(pQueue, &visit);
            if (ERESULT_OK(eRc)) {
                pVisitor(pObject, this, visit.pEntry, visit.level, indent, pOther);
                if (visit.pEntry->pChild) {
                    AST_BFS         visit2;
                    visit2.pEntry = visit.pEntry->pChild;
                    visit2.level = visit.level + 1;
                    eRc = array_Enqueue(pQueue, &visit2);
                }
                if (visit.pEntry->pSibling) {
                    // Since this is a sibling, we need to visit it next.
                    visit.pEntry = visit.pEntry->pSibling;
                    eRc = array_Push(pQueue, &visit);
                }
            } else {
                break;
            }
        }

        obj_Release(pQueue);
        pQueue = OBJ_NIL;

        // Return to caller.
        return ERESULT_SUCCESS;
    }


    ERESULT         Ast_VisitPostOrder(
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
        uint32_t        indent,
        AST_ENTRY       *pRoot
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        //AST_ENTRY       *pEntry = NULL;
        AST_VISIT       visit = {0};

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!Ast_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        if (NULL == pRoot)
            return eRc;
        
        if (pVisitor)
            visit.pVisitor = (void *)pVisitor;
        else
            visit.pVisitor = (void *)Ast_EntryPrint;
        visit.pObjectVisit = pObject;
        visit.pChildClose = pClose;
        visit.pObjectClose = pObject;
        visit.pChildOpen = pOpen;
        visit.pObjectOpen = pObject;
        visit.pOther = pOther;
        visit.type = AST_VISIT_TYPE_EXTERNAL;
        visit.level = 0;
        visit.indent = indent;
        visit.pChildOpen = NULL;
       
        eRc =   Ast_EntryPostOrder(this, &visit, pRoot);
        if (ERESULT_FAILED(eRc)) {
            return eRc;
        }
        
        // Return to caller.
        return eRc;
    }


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
        uint32_t        indent,
        AST_ENTRY       *pRoot
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        AST_VISIT       visit = {0};

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!Ast_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        if (pVisitor)
            visit.pVisitor = (void *)pVisitor;
        else
            visit.pVisitor = (void *)Ast_EntryPrint;
        visit.pObjectVisit = pObject;
        visit.pChildClose = pClose;
        visit.pObjectClose = pObject;
        visit.pChildOpen = pOpen;
        visit.pObjectOpen = pObject;
        visit.pOther = pOther;
        visit.type = AST_VISIT_TYPE_EXTERNAL;
        //visit.level = 0;
        visit.indent = indent;
        
        eRc = Ast_EntryPreOrder(this, &visit, pRoot);
        if (ERESULT_FAILED(eRc)) {
            return eRc;
        }
            
        // Return to caller.
        return eRc;
    }




    
#ifdef  __cplusplus
}
#endif


