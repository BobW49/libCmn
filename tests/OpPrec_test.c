// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Operator Precedence Parser (OpPrec)  Test Program
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
#include    <Misc.h>
#include    <trace.h>
#include    <OpPrec_internal.h>
#include    <JsonIn.h>
#include    <SrcErrors.h>
#include    <szTbl.h>



#include    "C_Expr_Class.h"
//#include    "C_Expr_Class_tables.c"
//#include    "C_Expr_Class_routines.c"





typedef struct expr_data_s {
    uint16_t    colNo;
    uint16_t    cls;
    int64_t     integer;
    const
    char        *pStrA;
}   EXPR_DATA;


TOKEN_FIELDS    fields[16] = {0};
int             cFields = 0;
int             current = 0;


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
    pFields->cls = C_EXPR_CLASS_INTEGER;
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





//----------------------------------------------------------------
//                      Test Open/Close
//----------------------------------------------------------------

ERESULT         Test_OpPrec_OpenClose (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    OPPREC_DATA     *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = OpPrec_Alloc( );
    TestForNotNull(pObj, "Missing Test Alloc() object");
    pObj = OpPrec_Init( pObj );
    TestForNotNull(pObj, "Missing Test Init() object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_OPPREC);
        TestForTrue(fRc, "Failed Ident Test");
#ifdef   OPPREC_MSGS
        OpPrec_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
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

ERESULT         Test_OpPrec_Copy01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    OPPREC_DATA     *pObj1 = OBJ_NIL;
    OPPREC_DATA     *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(OPPREC_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA       *pStr = OBJ_NIL;
#endif
    //int             iRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = OpPrec_New( );
    TestForNotNull(pObj1, "Missing Test object");
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_OPPREC);
        TestForTrue(fRc, "Failed Ident Test");
#ifdef   OPPREC_MSGS
        OpPrec_setMsg(pObj1, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
        
        // Test assign.
        pObj2 = OpPrec_New();
        TestForNotNull(pObj2, "Missing copied object");
        eRc = OpPrec_Assign(pObj1, pObj2);
        TestForFalse((ERESULT_FAILED(eRc)), "Assignment failed");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_OPPREC);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = OpPrec_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = OpPrec_Copy(pObj1);
        TestForNotNull(pObj2, "Missing copied object");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_OPPREC);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = OpPrec_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(OPPREC_JSON_SUPPORT) && defined(XYZZY)
        pStr = OpPrec_ToJson(pObj1);
        TestForNotNull(pStr, "Missing JSON output");
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = OpPrec_NewFromJsonString(pStr);
        TestForNotNull(pObj2, "Missing JSON created object");
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_OPPREC);
        TestForTrue(fRc, "Failed Ident Test");
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //iRc = OpPrec_Compare(pObj1, pObj2);
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

ERESULT         Test_OpPrec_Test01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    OPPREC_DATA     *pObj = OBJ_NIL;
    bool            fRc;
    int             i;
    static
    const
    EXPR_DATA   expr1_data[] = {            // 4 + 2 * 3 == 10
        //{1, ASM_CLASS_IDENTIFIER, 0, "xyz"},
        {1, C_EXPR_CLASS_INTEGER, 4, NULL},
        {5, C_EXPR_CLASS_ADD, 0, "+"},
        {7, C_EXPR_CLASS_INTEGER, 2, NULL},
        {10, C_EXPR_CLASS_MUL, 0, "*"},
        {12, C_EXPR_CLASS_INTEGER, 3, NULL},
        {20, C_EXPR_CLASS_EOL, 0, "\n"},
        {0, 0, 0, 0},
    };


   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = OpPrec_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_OPPREC);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   OPPREC_MSGS
        OpPrec_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        TokenBuildExpr(expr1_data);
        for (i=0; i<cFields; i++) {
            TokenDump(&fields[i]);
        }
        
        {
            ASTR_DATA       *pStr = OpPrec_ToDebugString(pObj, 4);
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

ERESULT         Test_OpPrec_Test02 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    OPPREC_DATA     *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = OpPrec_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_OPPREC);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   OPPREC_MSGS
        OpPrec_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        {
            ASTR_DATA       *pStr = OpPrec_ToDebugString(pObj, 4);
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

ERESULT         Test_OpPrec_Test03 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    OPPREC_DATA     *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = OpPrec_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_OPPREC);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   OPPREC_MSGS
        OpPrec_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        {
            ASTR_DATA       *pStr = OpPrec_ToDebugString(pObj, 4);
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

ERESULT         Test_OpPrec_Test04 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    OPPREC_DATA     *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = OpPrec_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_OPPREC);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   OPPREC_MSGS
        OpPrec_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        {
            ASTR_DATA       *pStr = OpPrec_ToDebugString(pObj, 4);
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
    TestExec("OpenClose", Test_OpPrec_OpenClose, NULL,   NULL);
    //TestExec("Copy01", Test_OpPrec_Copy01,       NULL,   NULL);
    TestExec("Test01", Test_OpPrec_Test01,       NULL,   NULL);
    TestExec("Test02", Test_OpPrec_Test02,       NULL,   NULL);
    TestExec("Test03", Test_OpPrec_Test03,       NULL,   NULL);
    TestExec("Test04", Test_OpPrec_Test04,       NULL,   NULL);

    obj_Release(pTest);
    pTest = OBJ_NIL;

    // Return to Operating System.
    return 0;
}



