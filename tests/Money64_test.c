// vi:nu:et:sts=4 ts=4 sw=4
//****************************************************************
//                      Test Object Program
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
#include    <trace.h>
#include    <Money64_internal.h>
#include    <JsonIn.h>
#include    <SrcErrors.h>
#include    <szTbl.h>


/*
    Example Data for Binary String Search
 */
typedef enum Item_Type_e {
    ITEM_TYPE_UNKNOWN=0,
    ITEM_TYPE_COMMENT=1,
    ITEM_TYPE_GENERAL=2,
    ITEM_TYPE_HEADING=3,
    ITEM_TYPE_LINK=4,
    ITEM_TYPE_TITLE=5,
    ITEM_TYPE_WEBSITES=6,
} ITEM_TYPES;

typedef struct {
    const
    char            *pEnum;
    char            *pDesc;
    char            *pName;
    uint32_t        value;
} Item_Type_entry;

static
const
Item_Type_entry    Item_Type_entries[] = {
    {"ITEM_TYPE_COMMENT", "", "COMMENT", 1},
    {"ITEM_TYPE_GENERAL", "", "GENERAL", 2},
    {"ITEM_TYPE_HEADING", "", "HEADING", 3},
    {"ITEM_TYPE_LINK", "", "LINK", 4},
    {"ITEM_TYPE_TITLE", "", "TITLE", 5},
    {"ITEM_TYPE_UNKNOWN", "", "UNKNOWN", 0},
    {"ITEM_TYPE_WEBSITES", "", "WEBSITES", 6},
};

static
uint32_t    cItem_Type_entries = 7;





ERESULT         Test_Money64_OpenClose (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    MONEY64_DATA    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Money64_Alloc( );
    TestForNotNull(pObj, "Missing Test Alloc() object");
    pObj = Money64_Init( pObj );
    TestForNotNull(pObj, "Missing Test Init() object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_MONEY64);
        TestForTrue(fRc, "Failed Ident Test");
#ifdef   MISC_MSGS
        Money64_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
        
        // Test something.
        TestForSuccess("test failed");

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_Money64_Copy01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    MONEY64_DATA    *pObj1 = OBJ_NIL;
    MONEY64_DATA    *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(MISC_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA       *pStr = OBJ_NIL;
#endif
    //int             iRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = Money64_New( );
    TestForNotNull(pObj1, "Missing Test object");
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_MONEY64);
        TestForTrue(fRc, "Failed Ident Test");
#ifdef   MISC_MSGS
        Money64_setMsg(pObj1, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
        
        // Test assign.
        pObj2 = Money64_New();
        TestForNotNull(pObj2, "Missing copied object");
        eRc = Money64_Assign(pObj1, pObj2);
        TestForFalse((ERESULT_FAILED(eRc)), "Assignment failed");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_MONEY64);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = Money64_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = Money64_Copy(pObj1);
        TestForNotNull(pObj2, "Missing copied object");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_MONEY64);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = Money64_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(MISC_JSON_SUPPORT) && defined(XYZZY)
        pStr = Money64_ToJson(pObj1);
        TestForNotNull(pStr, "Missing JSON output");
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = Money64_NewFromJsonString(pStr);
        TestForNotNull(pObj2, "Missing JSON created object");
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_MONEY64);
        TestForTrue(fRc, "Failed Ident Test");
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //iRc = Money64_Compare(pObj1, pObj2);
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



ERESULT         Test_Money64_Test01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    MONEY64_DATA    *pObj = OBJ_NIL;
    bool            fRc;
    int             iRc;
    ASTR_DATA       *pStr = OBJ_NIL;
    const
    Item_Type_entry *pEntry = NULL;
    uint32_t        value = 0;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Money64_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_MONEY64);
        TestForTrue(fRc, "Failed Ident Test");
        TestForSuccess("");
#ifdef   MISC_LOG
        Money64_setLog(pObj, this);
#endif
                
        pObj->amt = 1234567890001;
        pStr = Money64_ToAStr(pObj);
        fprintf(stderr, " 1234567890001: %s\n", AStr_getData(pStr));
        iRc = AStr_CompareA(pStr, " 123,456,789.0001");
        TestForTrue( (0 == iRc), "" );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        pObj->amt = -1234567890001;
        pStr = Money64_ToAStr(pObj);
        fprintf(stderr, "-1234567890001: %s\n", AStr_getData(pStr));
        iRc = AStr_CompareA(pStr, "-123,456,789.0001");
        TestForTrue( (0 == iRc), "" );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        pObj->amt = 1234567890055;
        pStr = Money64_ToAStrDec2(pObj);
        fprintf(stderr, " 1234567890055: %s\n", AStr_getData(pStr));
        iRc = AStr_CompareA(pStr, " 123,456,789.01");
        TestForTrue( (0 == iRc), "" );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        pObj->amt = -1234567890055;
        pStr = Money64_ToAStrDec2(pObj);
        fprintf(stderr, "-1234567890055: %s\n", AStr_getData(pStr));
        iRc = AStr_CompareA(pStr, "-123,456,789.01");
        TestForTrue( (0 == iRc), "" );
        obj_Release(pStr);
        pStr = OBJ_NIL;

        pStr = AStr_NewA("-123,456,789.0001");
        TestForFalse( (OBJ_NIL == pStr), "" );
        eRc = Money64_FromAStr(pObj, pStr);
        TestForFalse( (ERESULT_FAILED(eRc)), "" );
        fprintf(stderr, "-1234567890001: %lld\n", pObj->amt);
        TestForTrue( (-1234567890001 == pObj->amt), "" );
        obj_Release(pStr);
        pStr = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_Money64_Test02 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    MONEY64_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    int             iRc;
    ASTR_DATA       *pStr = OBJ_NIL;
    uint64_t        amt;
    uint64_t        amt2;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Money64_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_MONEY64);
        TestForTrue(fRc, "Failed Ident Test");
        TestForSuccess("");

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_Money64_Test03 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    MONEY64_DATA    *pObj = OBJ_NIL;
    bool            fRc;
    int             iRc;
    ASTR_DATA       *pStr = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Money64_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_MONEY64);
        TestForTrue(fRc, "Failed Ident Test");
        TestForSuccess("");

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_Money64_Test04 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    MONEY64_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    int             iRc;
    ASTR_DATA       *pStr = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Money64_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_MONEY64);
        TestForTrue(fRc, "Failed Ident Test");
        TestForSuccess("");

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_Money64_Test05 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    MONEY64_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    int             iRc;
    ASTR_DATA       *pStr = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Money64_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_MONEY64);
        TestForTrue(fRc, "Failed Ident Test");
        TestForSuccess("");

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_Money64_Test06 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    MONEY64_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    int             iRc;
    ASTR_DATA       *pStr = OBJ_NIL;
    uint32_t        u32;
    uint64_t        u64;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Money64_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_MONEY64);
        TestForTrue(fRc, "Failed Ident Test");
        TestForSuccess("");
#ifdef   MISC_LOG
        Money64_setLog(pObj, this);
#endif

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_Money64_Test07 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    MONEY64_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    int             iRc;
    ASTR_DATA       *pStr = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Money64_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_MONEY64);
        TestForTrue(fRc, "Failed Ident Test");
        TestForSuccess("");
#ifdef   MISC_LOG
        Money64_setLog(pObj, this);
#endif

        {
            ASTR_DATA       *pStr = Money64_ToDebugString(pObj, 4);
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



ERESULT         Test_Money64_Test08 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    MONEY64_DATA    *pObj = OBJ_NIL;
    bool            fRc;
    int             iRc;
    ASTR_DATA       *pStr = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Money64_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_MONEY64);
        TestForTrue(fRc, "Failed Ident Test");
        TestForSuccess("");
#ifdef   MISC_LOG
        Money64_setLog(pObj, this);
#endif

        {
            ASTR_DATA       *pStr = Money64_ToDebugString(pObj, 4);
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
    TestExec("OpenClose", Test_Money64_OpenClose, NULL, NULL);
    TestExec("Copy01", Test_Money64_Copy01, NULL, NULL);
    TestExec("Test01", Test_Money64_Test01, NULL, NULL);
    TestExec("Test02", Test_Money64_Test02, NULL, NULL);
    TestExec("Test03", Test_Money64_Test03, NULL, NULL);
    TestExec("Test04", Test_Money64_Test04, NULL, NULL);
    TestExec("Test05", Test_Money64_Test05, NULL, NULL);
    TestExec("Test06", Test_Money64_Test06, NULL, NULL);
    TestExec("Test07", Test_Money64_Test07, NULL, NULL);
    TestExec("Test08", Test_Money64_Test08, NULL, NULL);

    obj_Release(pTest);
    pTest = OBJ_NIL;

    // Return to Operating System.
    return 0;
}



