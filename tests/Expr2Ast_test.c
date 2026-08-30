// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//  Parse an Expression into an AST (Expr2Ast)  Test Program
//****************************************************************

/*
 * Program
 *          Test Object Program
 * Purpose
 *          This program tests a particular object given certain
 *          parameters.
 *
 * Remarks
 *  1.      This relies on the fact that we can add to the Test
 *          Object by simply coding methods that use the Test
 *          Object.
 *
 * History
 *  08/29/2021 Generated
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




/*
 TestForFail(error_sttring)         <= Tests eRc for failure
 TestForFalse(test, error_sttring)
 TestForNotNull(test, error)
 TestForNull(test, error)
 TestForSuccess(error)              <= Tests eRc for success
 TestForTrue(test, error)
 */





#include    <test_defs.h>
#include    <Test_internal.h>
#include    <Ast_internal.h>
#include    <trace.h>
#include    <Expr2Ast_internal.h>
#include    <JsonIn.h>
#include    <SrcErrors.h>
#include    <szTbl.h>






TOKEN_FIELDS    fields[64] = {0};
int             cFields = 0;
int             current = 0;


typedef struct expr_data_s {
    uint16_t    colNo;
    uint16_t    cls;
    int64_t     integer;
    const
    char        *pStrA;
}   EXPR_DATA;




//----------------------------------------------------------------
//                      Token Utilities
//----------------------------------------------------------------
static
void            TokenBuildEOL (
    TOKEN_FIELDS    *pFields,
    int16_t         colNo
)
{
    // Source Location
    pFields->src.pFileNameA = "SomeFile.txt";
    pFields->src.colNo = colNo;
    pFields->src.unused16 = 0;
    pFields->src.lineNo = 1;
    pFields->src.unused32 = 0;
    pFields->src.offset = 0;

    // Token
    pFields->cls = C_EXPR_CLASS_EOL;
    pFields->type = TOKEN_TYPE_CHAR;
    pFields->len = 0;
    pFields->misc = 0;
    str_Copy(pFields->chr, 8, "\n");

}


static
void            TokenBuildIdentifier (
    TOKEN_FIELDS    *pFields,
    int16_t         colNo,
    const
    char            *pStrA
)
{
    // Source Location
    pFields->src.pFileNameA = "SomeFile.txt";
    pFields->src.colNo = colNo;
    pFields->src.unused16 = 0;
    pFields->src.lineNo = 1;
    pFields->src.unused32 = 0;
    pFields->src.offset = 0;

    // Token
    pFields->cls = C_EXPR_CLASS_SYM_INT;
    pFields->type = TOKEN_TYPE_STATIC_STRING8;
    pFields->len = 0;
    pFields->misc = 0;
    pFields->pStrA = pStrA;
}


static
void            TokenBuildInteger (
    TOKEN_FIELDS    *pFields,
    int16_t         colNo,
    int64_t         integer
)
{
    // Source Location
    pFields->src.pFileNameA = "SomeFile.txt";
    pFields->src.colNo = colNo;
    pFields->src.unused16 = 0;
    pFields->src.lineNo = 1;
    pFields->src.unused32 = 0;
    pFields->src.offset = 0;

    // Token
    pFields->cls = C_EXPR_CLASS_CON_INT;
    pFields->type = TOKEN_TYPE_INTEGER;
    pFields->len = 0;
    pFields->misc = 0;
    pFields->integer = integer;
}


static
void            TokenBuildOperator (
    TOKEN_FIELDS    *pFields,
    int16_t         colNo,
    int16_t         cls,
    const
    char            *pStrA
)
{
    // Source Location
    pFields->src.pFileNameA = "SomeFile.txt";
    pFields->src.colNo = colNo;
    pFields->src.unused16 = 0;
    pFields->src.lineNo = 1;
    pFields->src.unused32 = 0;
    pFields->src.offset = 0;

    // Token
    pFields->cls = cls;
    pFields->type = TOKEN_TYPE_CHAR;
    pFields->len = 0;
    pFields->misc = 0;
    str_Copy(pFields->chr, 8, pStrA);
}


static
void            TokenDump (
    TOKEN_FIELDS    *pFields
)
{
    ASTR_DATA       *pStr = Token_FieldsToDebugString(pFields, 0);
    if (pStr) {
        fputs(AStr_getData(pStr), stderr);
        obj_Release(pStr);
    }

}


static
void            TokenBuildExpr (
    const
    EXPR_DATA   *pExprData
)
{
    int         i = 0;
    
    cFields = 0;
    current = 0;
    for (i=0; i<16; i++) {
        if (0 == pExprData[i].colNo) {
            memset(&fields[i], 0, sizeof(TOKEN_FIELDS));
            break;
        }
        switch (pExprData[i].cls) {
            case C_EXPR_CLASS_ADD:
            case C_EXPR_CLASS_MUL:
                TokenBuildOperator(
                                   &fields[i],
                                   pExprData[i].colNo,
                                   pExprData[i].cls,
                                   pExprData[i].pStrA
                );
                break;
            case C_EXPR_CLASS_EOL:
                TokenBuildEOL(
                                   &fields[i],
                                   pExprData[i].colNo
                );
                break;
            case C_EXPR_CLASS_SYM_INT:
                TokenBuildIdentifier(
                                   &fields[i],
                                   pExprData[i].colNo,
                                   pExprData[i].pStrA
                );
                break;
            case C_EXPR_CLASS_CON_INT:
            case C_EXPR_CLASS_INTEGER:
                TokenBuildInteger(
                                   &fields[i],
                                   pExprData[i].colNo,
                                   pExprData[i].integer
                );
                break;
        }
        cFields++;
    }
}



// int32_t         (*pInputAdvance)(OBJ_ID, uint16_t, TOKEN_FIELDS **);
// int32_t         (*pInputLookAhead)(OBJ_ID, uint16_t, TOKEN_FIELDS **);

static
int32_t     ExprAdvance (
    TEST_DATA       *this,
    uint16_t        num,
    TOKEN_FIELDS    **ppToken
)
{
    TOKEN_FIELDS    *pToken;

    if ((num + current) < cFields) {
        current += num;
    } else {
        return 0;
    }
    pToken = &fields[current];

    if (ppToken)
        *ppToken = pToken;
    return pToken->cls;
}


static
int32_t     ExprLookahead (
    TEST_DATA       *this,
    uint16_t        num,
    TOKEN_FIELDS    **ppToken
)
{
    int             i = 0;
    TOKEN_FIELDS    *pToken;

    if ((num + current - 1) < cFields) {
        i = current + num - 1;
    } else {
        return 0;
    }
    pToken = &fields[i];

    if (ppToken)
        *ppToken = pToken;
    return pToken->cls;
}



static
void            printAfter (
    OBJ_ID          pObject,            // Object supplied below
    AST_DATA        *pTree,             // Our Tree
    AST_ENTRY       *pEntry,
    uint32_t        indent,
    uint32_t        level,
    void            *pOther
)
{
    ASTR_DATA       *pStr = AStr_New();
    
    if (pStr) {
        if (indent) {
            AStr_AppendCharRepeatA(pStr, (indent << 2), ' ');
        }
        fprintf(stderr, "%s)\n", AStr_getData(pStr));
        obj_Release(pStr);
    }
}


static
void            printBefore (
    OBJ_ID          pObject,            // Object supplied below
    AST_DATA        *pTree,             // Our Tree
    AST_ENTRY       *pEntry,
    uint32_t        indent,
    uint32_t        level,
    void            *pOther
)
{
    ASTR_DATA       *pStr = AStr_New();
    
    if (pStr) {
        if (indent) {
            AStr_AppendCharRepeatA(pStr, (indent << 2), ' ');
        }
        fprintf(stderr, "%s(\n", AStr_getData(pStr));
        obj_Release(pStr);
    }
}


static
void            printVisit (
    OBJ_ID          pObject,            // Object supplied below
    AST_DATA        *pTree,             // Our Tree
    AST_ENTRY       *pEntry,
    uint32_t        indent,
    uint32_t        level,
    void            *pOther
)
{
    ASTR_DATA       *pStr = Ast_EntryToAStrDebug(pTree, pEntry, (indent << 2));
    
    if (pStr) {
        fprintf(stderr, "%s", AStr_getData(pStr));
        obj_Release(pStr);
    }
}


//----------------------------------------------------------------
//                      Test Open/Close
//----------------------------------------------------------------

ERESULT         Test_Expr2Ast_OpenClose (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    EXPR2AST_DATA   *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Expr2Ast_Alloc( );
    TestForNotNull(pObj, "Missing Test Alloc() object");
    pObj = Expr2Ast_Init( pObj );
    TestForNotNull(pObj, "Missing Test Init() object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_EXPR2AST);
        TestForTrue(fRc, "Failed Ident Test");
#ifdef   EXPR2AST_MSGS
        Expr2Ast_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
        
        // Test something.
        TestForSuccess("");

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



//----------------------------------------------------------------
//                      Test Copy/JSON
//----------------------------------------------------------------

ERESULT         Test_Expr2Ast_Copy01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    EXPR2AST_DATA   *pObj1 = OBJ_NIL;
    EXPR2AST_DATA   *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(EXPR2AST_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA       *pStr = OBJ_NIL;
#endif
    //int             iRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = Expr2Ast_New( );
    TestForNotNull(pObj1, "Missing Test object");
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_EXPR2AST);
        TestForTrue(fRc, "Failed Ident Test");
#ifdef   EXPR2AST_MSGS
        Expr2Ast_setMsg(pObj1, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
        
        // Test assign.
        pObj2 = Expr2Ast_New();
        TestForNotNull(pObj2, "Missing copied object");
        eRc = Expr2Ast_Assign(pObj1, pObj2);
        TestForFalse((ERESULT_FAILED(eRc)), "Assignment failed");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_EXPR2AST);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = Expr2Ast_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = Expr2Ast_Copy(pObj1);
        TestForNotNull(pObj2, "Missing copied object");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_EXPR2AST);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = Expr2Ast_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(EXPR2AST_JSON_SUPPORT) && defined(XYZZY)
        pStr = Expr2Ast_ToJson(pObj1);
        TestForNotNull(pStr, "Missing JSON output");
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = Expr2Ast_NewFromJsonString(pStr);
        TestForNotNull(pObj2, "Missing JSON created object");
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_EXPR2AST);
        TestForTrue(fRc, "Failed Ident Test");
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //iRc = Expr2Ast_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;
#endif

        obj_Release(pObj1);
        pObj1 = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



//----------------------------------------------------------------
//                          Test 1
//----------------------------------------------------------------

ERESULT         Test_Expr2Ast_Test01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    EXPR2AST_DATA   *pObj = OBJ_NIL;
    bool            fRc;
    PTRARRAY_DATA   *pArray = OBJ_NIL;
    int             indent;
    int             i;
    int             iMax;
    AST_ENTRY       *pEntry = NULL;
    AST_DATA        *pAst = OBJ_NIL;
    static
    const
    EXPR_DATA   expr1_data[] = {         // 4 + 2 * 3 == 10
        //{1, C_EXPR_CLASS_SYM_INT, 0, "xyz"},
        {1, C_EXPR_CLASS_CON_INT, 4, NULL},
        {5, C_EXPR_CLASS_ADD, 0, "+"},
        {7, C_EXPR_CLASS_CON_INT, 2, NULL},
        {10, C_EXPR_CLASS_MUL, 0, "*"},
        {12, C_EXPR_CLASS_CON_INT, 3, NULL},
        {20, C_EXPR_CLASS_EOL, 0, "\n"},
        {0, 0, 0, 0},
    };
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Expr2Ast_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_EXPR2AST);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   EXPR2AST_MSGS
        Expr2Ast_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
        
        TokenBuildExpr(expr1_data);
        for (i=0; i<cFields; i++) {
            TokenDump(&fields[i]);
        }
        
        fRc = Expr2Ast_setInput(pObj, (void *)ExprAdvance, (void *)ExprLookahead, this);
        TestForTrue(fRc, "");
        pEntry = Expr2Ast_Parse(pObj);
        TestForSuccess("");

        pAst = Expr2Ast_getAst(pObj);
        if (pAst) {
            ASTR_DATA       *pStr = Ast_ToDebugString(pAst, 4);
            if (pStr) {
                fprintf(stderr, "\n\nAST: %s\n\n\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        fprintf(stderr, "\n\n\nPost-order Traversal\n");
        eRc = Ast_VisitPostOrder(
                                     pAst,
                                     printVisit,
                                     printBefore,
                                     printAfter,
                                     OBJ_NIL,
                                     NULL,
                                     0,
                                     Ast_getRoot(pAst)
                                     );
        TestForSuccess("");

        fprintf(stderr, "\n\n\nPre-order Traversal\n");
        pAst = Expr2Ast_getAst(pObj);
        eRc = Ast_VisitPreOrder(
                                     pAst,
                                     printVisit,
                                     printBefore,
                                     printAfter,
                                     OBJ_NIL,
                                     NULL,
                                     0,
                                     Ast_getRoot(pAst)
                                     );
        TestForSuccess("");

        fprintf(stderr, "\n\n\nPre-order Linearization:\n");
        pAst = Expr2Ast_getAst(pObj);
        pArray = Ast_ToLinearizationPre(pAst, pEntry);
        TestForNotNull(pArray, "");
        iMax = ptrArray_getSize(pArray);
        fprintf(stderr, "\tsize: %d\n", iMax);
        TestForTrue((11 == iMax), "");
        indent = 4;
        for (i=0; i<iMax; i++) {
            AST_ENTRY           *pEntry = ptrArray_GetData(pArray, i+1);
            if (pEntry) {
                int16_t             type = pEntry->type;
                int                 j;
                if (type == C_EXPR_CLASS_OPEN) {
                    for (j=0; j<indent; j++)
                        fputc(' ', stderr);
                    fputc('(', stderr);
                    fputc('\n', stderr);
                    indent += 4;
                    continue;
                }
                if (type == C_EXPR_CLASS_CLOSE) {
                    indent -= 4;
                    for (j=0; j<indent; j++)
                        fputc(' ', stderr);
                    fputc(')', stderr);
                    fputc('\n', stderr);
                    continue;
                }
                for (j=0; j<indent; j++)
                    fputc(' ', stderr);
                switch (type) {
                    case C_EXPR_CLASS_CON_INT:
                        fprintf(stderr, "%lld\n", pEntry->u.integer);
                    default:
                        if (pEntry->kind == AST_ENTRY_KIND_CHARS) {
                            fprintf(stderr, "%s\n", pEntry->u.chrs);
                        }
                }
            }
        }
        obj_Release(pArray);
        pArray = OBJ_NIL;
        pAst = OBJ_NIL;
        
        {
            ASTR_DATA       *pStr = Expr2Ast_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



//----------------------------------------------------------------
//                          Test 2
//----------------------------------------------------------------

ERESULT         Test_Expr2Ast_Test02 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    EXPR2AST_DATA   *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Expr2Ast_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_EXPR2AST);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   EXPR2AST_MSGS
        Expr2Ast_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        {
            ASTR_DATA       *pStr = Expr2Ast_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



//----------------------------------------------------------------
//                          Test 3
//----------------------------------------------------------------

ERESULT         Test_Expr2Ast_Test03 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    EXPR2AST_DATA   *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Expr2Ast_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_EXPR2AST);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   EXPR2AST_MSGS
        Expr2Ast_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        {
            ASTR_DATA       *pStr = Expr2Ast_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



//----------------------------------------------------------------
//                          Test 4
//----------------------------------------------------------------

ERESULT         Test_Expr2Ast_Test04 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    EXPR2AST_DATA   *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Expr2Ast_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_EXPR2AST);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   EXPR2AST_MSGS
        Expr2Ast_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        {
            ASTR_DATA       *pStr = Expr2Ast_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}




//----------------------------------------------------------------
//                              Main
//----------------------------------------------------------------

int     main (
    int         cArgs,
    const
    char        *ppArgs[],
    const
    char        *ppEnv[]
)
{
    ERESULT     eRc;
    TEST_DATA   test = {0};
    TEST_DATA   *pTest = OBJ_NIL;
    int         i;
    const
    char        *pTestNameA = NULL;

    pTest = Test_Init(&test);
    if (OBJ_NIL == pTest) {
        fprintf(
                stderr,
                "\x1b[1m\x1b[31mFATAL\x1b[0m: Could not create Test object!\n\n\n"
        );
        exit(201);
    }

    // Scan args.
    for (i=0; i<cArgs; i++) {
        if (0 == strcmp("--no_int3", ppArgs[i])) {
            Test_setAllowInt3(pTest, false);
        }
    }

    // Execute tests.
    // Note: 
    //  Test_Setup() is called before the optional supplied setup
    //  in this table. Likewise, the optional teardown routine is
    //  called before Test_TearDown().
    //                                             Setup TearDown
    TestExec("OpenClose", Test_Expr2Ast_OpenClose, NULL,   NULL);
    //TestExec("Copy01", Test_Expr2Ast_Copy01,       NULL,   NULL);
    TestExec("Test01", Test_Expr2Ast_Test01,       NULL,   NULL);
    TestExec("Test02", Test_Expr2Ast_Test02,       NULL,   NULL);
    TestExec("Test03", Test_Expr2Ast_Test03,       NULL,   NULL);
    TestExec("Test04", Test_Expr2Ast_Test04,       NULL,   NULL);

    obj_Release(pTest);
    pTest = OBJ_NIL;

    // Return to Operating System.
    return 0;
}



