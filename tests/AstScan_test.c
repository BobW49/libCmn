// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
// Scan an AST for various manipulations (AstScan)  Test Program
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
#include    <C_Expr_Class.h>
#include    <trace.h>
#include    <AstScan_internal.h>
#include    <JsonIn.h>
#include    <SrcErrors.h>
#include    <szTbl.h>



// Example from "Algorithms + Data Structures = Programs" by Niklaus Wirth
// Page 193 and 199
// Tree representation of: (a + b / c) * (d - e * f)
// Note - Each node must be unique.  Therefore, we must have two nodes for '*'.
static
AST_DATA *      createTestTree01 (
    TEST_DATA       *this
)
{
    AST_DATA        *pTree = OBJ_NIL;
    AST_ENTRY       *pNodeA = OBJ_NIL;
    AST_ENTRY       *pNodeB = OBJ_NIL;
    AST_ENTRY       *pNodeC = OBJ_NIL;
    AST_ENTRY       *pNodeD = OBJ_NIL;
    AST_ENTRY       *pNodeE = OBJ_NIL;
    AST_ENTRY       *pNodeF = OBJ_NIL;
    AST_ENTRY       *pNodeG = OBJ_NIL;
    AST_ENTRY       *pNodeH = OBJ_NIL;
    AST_ENTRY       *pNodeI = OBJ_NIL;
    AST_ENTRY       *pNodeJ = OBJ_NIL;
    AST_ENTRY       *pNodeK = OBJ_NIL;
    //uint32_t        i;
    ERESULT         eRc;
    //NODETREE_RECORD *pRcd = NULL;

    pTree = Ast_New( );
    if  (OBJ_NIL == pTree) {
        return pTree;
    }

    pNodeA = Ast_EntryNewChars(pTree, "a", 0, NULL);
    TestForNotNull(pNodeA, "");
    pNodeB = Ast_EntryNewChars(pTree, "b", 0, NULL);
    TestForNotNull(pNodeB, "");
    pNodeC = Ast_EntryNewChars(pTree, "c", 0, NULL);
    TestForNotNull(pNodeC, "");
    pNodeD = Ast_EntryNewChars(pTree, "d", 0, NULL);
    TestForNotNull(pNodeD, "");
    pNodeE = Ast_EntryNewChars(pTree, "e", 0, NULL);
    TestForNotNull(pNodeE, "");
    pNodeF = Ast_EntryNewChars(pTree, "f", 0, NULL);
    TestForNotNull(pNodeF, "");
    pNodeG = Ast_EntryNewChars(pTree, "*1", 0, NULL);
    TestForNotNull(pNodeG, "");
    pNodeH = Ast_EntryNewChars(pTree, "+", 0, NULL);
    TestForNotNull(pNodeH, "");
    pNodeI = Ast_EntryNewChars(pTree, "/", 0, NULL);
    TestForNotNull(pNodeI, "");
    pNodeJ = Ast_EntryNewChars(pTree, "-", 0, NULL);
    TestForNotNull(pNodeJ, "");
    pNodeK = Ast_EntryNewChars(pTree, "*2", 0, NULL);
    TestForNotNull(pNodeK, "");
    
    fprintf(stderr, "\n\nCreate the tree:\n");
    fprintf(stderr, "Tree            Index  Sibling  Child  Parent\n");
    fprintf(stderr, "'*1'         G    1       0       2       0\n");
    fprintf(stderr, "--'+'        H    2       3       4       1\n");
    fprintf(stderr, "----'a'      A    4       5       0       2\n");
    fprintf(stderr, "----'/'      I    5       0       6       2\n");
    fprintf(stderr, "------'b'    B    6       7       0       5\n");
    fprintf(stderr, "------'c'    C    7       0       0       5\n");
    fprintf(stderr, "--'-'        J    3       0       8       1\n");
    fprintf(stderr, "----'d'      D    8       9       0       3\n");
    fprintf(stderr, "----'*2'     K    9       0      10       3\n");
    fprintf(stderr, "------'e'    E   10      11       0       9\n");
    fprintf(stderr, "------'f'    F   11       0       0       9\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "Preorder Traversal:  *1 + a / b c - d *2 e f\n");
    fprintf(stderr, "Inorder Traversal:   a + b / c *1 d - e *2 f\n");
    fprintf(stderr, "Postorder Traversal: a b c / + d e f *2 - *1\n");
    fprintf(stderr, "Breadth First Traversal: ((*1), (+,-), (a,/,d,*2), (b,c,e,f)\n");
    fprintf(stderr, "\n\n\n");

    eRc = Ast_EntryAddChild(pTree, pNodeG, pNodeH, pNodeJ);
    TestForSuccess("");
    TestForTrue((pNodeH == pNodeG->pChild), "");
    TestForTrue((NULL   == pNodeG->pSibling), "");
    TestForTrue((NULL   == pNodeG->pParent), "");
    TestForTrue((NULL   == pNodeH->pChild), "");
    TestForTrue((pNodeJ == pNodeH->pSibling), "");
    TestForTrue((pNodeG == pNodeH->pParent), "");
    TestForTrue((NULL   == pNodeJ->pChild), "");
    TestForTrue((NULL   == pNodeJ->pSibling), "");
    TestForTrue((pNodeG == pNodeJ->pParent), "");

    eRc = Ast_EntryAddChild(pTree, pNodeH, pNodeA, pNodeI);
    TestForSuccess("");
    TestForTrue((pNodeA == pNodeH->pChild), "");
    TestForTrue((pNodeJ == pNodeH->pSibling), "");
    TestForTrue((pNodeG == pNodeH->pParent), "");
    TestForTrue((NULL   == pNodeA->pChild), "");
    TestForTrue((pNodeI == pNodeA->pSibling), "");
    TestForTrue((pNodeH == pNodeA->pParent), "");
    TestForTrue((NULL   == pNodeI->pChild), "");
    TestForTrue((NULL   == pNodeI->pSibling), "");
    TestForTrue((pNodeH == pNodeI->pParent), "");

    eRc = Ast_EntryAddChild(pTree, pNodeI, pNodeB, pNodeC);
    TestForSuccess("");
    TestForTrue((pNodeB == pNodeI->pChild), "");
    TestForTrue((NULL   == pNodeI->pSibling), "");
    TestForTrue((pNodeH == pNodeI->pParent), "");
    TestForTrue((NULL   == pNodeB->pChild), "");
    TestForTrue((pNodeC == pNodeB->pSibling), "");
    TestForTrue((pNodeI == pNodeB->pParent), "");
    TestForTrue((NULL   == pNodeC->pChild), "");
    TestForTrue((NULL   == pNodeC->pSibling), "");
    TestForTrue((pNodeI == pNodeC->pParent), "");

    eRc = Ast_EntryAddChild(pTree, pNodeJ, pNodeD, pNodeK);
    TestForSuccess("");
    TestForTrue((pNodeD == pNodeJ->pChild), "");
    TestForTrue((NULL   == pNodeJ->pSibling), "");
    TestForTrue((pNodeG == pNodeJ->pParent), "");
    TestForTrue((NULL   == pNodeD->pChild), "");
    TestForTrue((pNodeK == pNodeD->pSibling), "");
    TestForTrue((pNodeJ == pNodeD->pParent), "");
    TestForTrue((NULL   == pNodeK->pChild), "");
    TestForTrue((NULL   == pNodeK->pSibling), "");
    TestForTrue((pNodeJ == pNodeK->pParent), "");

    eRc = Ast_EntryAddChild(pTree, pNodeK, pNodeE, pNodeF);
    TestForSuccess("");
    TestForTrue((pNodeE == pNodeK->pChild), "");
    TestForTrue((NULL   == pNodeK->pSibling), "");
    TestForTrue((pNodeJ == pNodeK->pParent), "");
    TestForTrue((NULL   == pNodeE->pChild), "");
    TestForTrue((pNodeF == pNodeE->pSibling), "");
    TestForTrue((pNodeK == pNodeE->pParent), "");
    TestForTrue((NULL   == pNodeF->pChild), "");
    TestForTrue((NULL   == pNodeF->pSibling), "");
    TestForTrue((pNodeK == pNodeF->pParent), "");

    Ast_setRoot(pTree, pNodeG);
    return pTree;
}






//----------------------------------------------------------------
//                      Test Open/Close
//----------------------------------------------------------------

ERESULT         Test_AstScan_OpenClose (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTSCAN_DATA    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AstScan_Alloc( );
    TestForNotNull(pObj, "Missing Test Alloc() object");
    pObj = AstScan_Init( pObj );
    TestForNotNull(pObj, "Missing Test Init() object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTSCAN);
        TestForTrue(fRc, "Failed Ident Test");
#ifdef   ASTSCAN_MSGS
        AstScan_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
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

ERESULT         Test_AstScan_Copy01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTSCAN_DATA    *pObj1 = OBJ_NIL;
    ASTSCAN_DATA    *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(ASTSCAN_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA       *pStr = OBJ_NIL;
#endif
    //int             iRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = AstScan_New( );
    TestForNotNull(pObj1, "Missing Test object");
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_ASTSCAN);
        TestForTrue(fRc, "Failed Ident Test");
#ifdef   ASTSCAN_MSGS
        AstScan_setMsg(pObj1, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
        
        // Test assign.
        pObj2 = AstScan_New();
        TestForNotNull(pObj2, "Missing copied object");
        eRc = AstScan_Assign(pObj1, pObj2);
        TestForFalse((ERESULT_FAILED(eRc)), "Assignment failed");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_ASTSCAN);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = AstScan_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = AstScan_Copy(pObj1);
        TestForNotNull(pObj2, "Missing copied object");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_ASTSCAN);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = AstScan_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(ASTSCAN_JSON_SUPPORT) && defined(XYZZY)
        pStr = AstScan_ToJson(pObj1);
        TestForNotNull(pStr, "Missing JSON output");
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = AstScan_NewFromJsonString(pStr);
        TestForNotNull(pObj2, "Missing JSON created object");
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_ASTSCAN);
        TestForTrue(fRc, "Failed Ident Test");
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //iRc = AstScan_Compare(pObj1, pObj2);
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

ERESULT         Test_AstScan_Test01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTSCAN_DATA    *pObj = OBJ_NIL;
    AST_DATA        *pTree = OBJ_NIL;
    bool            fRc;
    PTRARRAY_DATA   *pArray = OBJ_NIL;
    int             indent;
    int             i;
    int             iMax;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pTree = createTestTree01(this);
    TestForNotNull(pTree, "");
    
    pObj = AstScan_NewPre(pTree, Ast_getRoot(pTree));
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTSCAN);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   ASTSCAN_MSGS
        AstScan_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        fprintf(stderr, "\n\nPre-order Linearization:\n");
        fprintf(stderr, "Preorder Traversal:  *1 + a / b c - d *2 e f\n");
        pArray = Ast_ToLinearizationPre(pTree, Ast_getRoot(pTree));
        TestForNotNull(pArray, "");
        iMax = ptrArray_getSize(pArray);
        fprintf(stderr, "\tsize: %d\n", iMax);
        TestForTrue((23 == iMax), "");
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
                    case C_EXPR_CLASS_INTEGER:
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
        
        {
            ASTR_DATA       *pStr = AstScan_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    obj_Release(pTree);
    pTree = OBJ_NIL;
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



//----------------------------------------------------------------
//                          Test 2
//----------------------------------------------------------------

ERESULT         Test_AstScan_Test02 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTSCAN_DATA    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AstScan_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTSCAN);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   ASTSCAN_MSGS
        AstScan_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        {
            ASTR_DATA       *pStr = AstScan_ToDebugString(pObj, 4);
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

ERESULT         Test_AstScan_Test03 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTSCAN_DATA    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AstScan_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTSCAN);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   ASTSCAN_MSGS
        AstScan_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        {
            ASTR_DATA       *pStr = AstScan_ToDebugString(pObj, 4);
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

ERESULT         Test_AstScan_Test04 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTSCAN_DATA    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AstScan_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTSCAN);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   ASTSCAN_MSGS
        AstScan_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        {
            ASTR_DATA       *pStr = AstScan_ToDebugString(pObj, 4);
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
    TestExec("OpenClose", Test_AstScan_OpenClose, NULL,   NULL);
    //TestExec("Copy01", Test_AstScan_Copy01,       NULL,   NULL);
    TestExec("Test01", Test_AstScan_Test01,       NULL,   NULL);
    TestExec("Test02", Test_AstScan_Test02,       NULL,   NULL);
    TestExec("Test03", Test_AstScan_Test03,       NULL,   NULL);
    TestExec("Test04", Test_AstScan_Test04,       NULL,   NULL);

    obj_Release(pTest);
    pTest = OBJ_NIL;

    // Return to Operating System.
    return 0;
}



