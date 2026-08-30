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
#include    <Base64_internal.h>
#include    <JsonIn.h>
#include    <SrcErrors.h>
#include    <szTbl.h>






ERESULT         Test_Base64_OpenClose (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BASE64_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Base64_Alloc( );
    TestForNotNull(pObj, "Missing Test Alloc() object");
    pObj = Base64_Init( pObj );
    TestForNotNull(pObj, "Missing Test Init() object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_BASE64);
        TestForTrue(fRc, "Failed Ident Test");
#ifdef   BASE64_MSGS
        Base64_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
        
        // Test something.
        TestForSuccess("test failed");

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_Base64_Copy01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BASE64_DATA       *pObj1 = OBJ_NIL;
    BASE64_DATA       *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(BASE64_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA       *pStr = OBJ_NIL;
#endif
    //int             iRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = Base64_New( );
    TestForNotNull(pObj1, "Missing Test object");
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_BASE64);
        TestForTrue(fRc, "Failed Ident Test");
#ifdef   BASE64_MSGS
        Base64_setMsg(pObj1, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
        
        // Test assign.
        pObj2 = Base64_New();
        TestForNotNull(pObj2, "Missing copied object");
        eRc = Base64_Assign(pObj1, pObj2);
        TestForFalse((ERESULT_FAILED(eRc)), "Assignment failed");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_BASE64);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = Base64_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = Base64_Copy(pObj1);
        TestForNotNull(pObj2, "Missing copied object");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_BASE64);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = Base64_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(BASE64_JSON_SUPPORT) && defined(XYZZY)
        pStr = Base64_ToJson(pObj1);
        TestForNotNull(pStr, "Missing JSON output");
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = Base64_NewFromJsonString(pStr);
        TestForNotNull(pObj2, "Missing JSON created object");
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_BASE64);
        TestForTrue(fRc, "Failed Ident Test");
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //iRc = Base64_Compare(pObj1, pObj2);
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



ERESULT         Test_Base64_Test01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BASE64_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Base64_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_BASE64);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("test failed");
#ifdef   BASE64_MSGS
        Base64_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        {
            ASTR_DATA       *pStr = Base64_ToDebugString(pObj, 4);
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



ERESULT         Test_Base64_Test02 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BASE64_DATA     *pObj = OBJ_NIL;
    bool            fRc;
    const
    char            *pData = "Man";
    const
    char            *pBase64 = "TWFu";
    ASTR_DATA       *pStr = OBJ_NIL;
    U8ARRAY_DATA    *pArray = OBJ_NIL;
    int             i;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Base64_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_BASE64);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("test failed");
#ifdef   BASE64_MSGS
        Base64_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        fprintf(stderr, "\tInput    : (%d)\"%s\"\n", (int)strlen(pData), pData);
        fprintf(stderr, "\tShould be: (%d)\"%s\"\n", (int)strlen(pBase64), pBase64);
        pStr = Base64_EncodeData((int)strlen(pData), (void *)pData);
        TestForNotNull(pStr, "");
        fprintf(stderr, "\tBase64   : (%d)\"%s\"\n\n", AStr_getSize(pStr), AStr_getData(pStr));
        i = AStr_CompareA(pStr, pBase64);
        XCTAssertTrue( (0 == i) );
        obj_Release(pStr);
        pStr = OBJ_NIL;

        fprintf(stderr, "\tInput    : (%d)\"%s\"\n", (int)strlen(pBase64), pBase64);
        fprintf(stderr, "\tShould be: (%d)\"%s\"\n", (int)strlen(pData), pData);
        pArray = Base64_DecodeData((int)strlen(pBase64), (void *)pBase64);
        TestForNotNull(pArray, "");
        pStr = u8Array_ToString(pArray);
        TestForNotNull(pStr, "");
        fprintf(stderr, "\tData     : (%d)\"%s\"\n", AStr_getSize(pStr), AStr_getData(pStr));
        i = AStr_CompareA(pStr, pData);
        XCTAssertTrue( (0 == i) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        obj_Release(pArray);
        pArray = OBJ_NIL;

        {
            ASTR_DATA       *pStr = Base64_ToDebugString(pObj, 4);
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



ERESULT         Test_Base64_Test03 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BASE64_DATA     *pObj = OBJ_NIL;
    bool            fRc;
    const
    char            *pData = "pleasure.";
    const
    char            *pBase64 = "cGxlYXN1cmUu";
    ASTR_DATA       *pStr = OBJ_NIL;
    U8ARRAY_DATA    *pArray = OBJ_NIL;
    int             i;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Base64_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_BASE64);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("test failed");
#ifdef   BASE64_MSGS
        Base64_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        fprintf(stderr, "\tInput    : (%d)\"%s\"\n", (int)strlen(pData), pData);
        fprintf(stderr, "\tShould be: (%d)\"%s\"\n", (int)strlen(pBase64), pBase64);
        pStr = Base64_EncodeData((int)strlen(pData), (void *)pData);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        fprintf(stderr, "\tBase64   : (%d)\"%s\"\n", AStr_getSize(pStr), AStr_getData(pStr));
        i = AStr_CompareA(pStr, pBase64);
        XCTAssertTrue( (0 == i) );
        obj_Release(pStr);
        pStr = OBJ_NIL;

        {
            ASTR_DATA       *pStr = Base64_ToDebugString(pObj, 4);
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



ERESULT         Test_Base64_Test04 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BASE64_DATA     *pObj = OBJ_NIL;
    bool            fRc;
    const
    char            *pData0 = "leasure.";
    const
    char            *pBase64_0 = "bGVhc3VyZS4=";
    const
    char            *pData1 = "easure.";
    const
    char            *pBase64_1 = "ZWFzdXJlLg==";
    const
    char            *pData2 = "asure.";
    const
    char            *pBase64_2 = "YXN1cmUu";
    const
    char            *pData3 = "sure.";
    const
    char            *pBase64_3 = "c3VyZS4=";
    ASTR_DATA       *pStr = OBJ_NIL;
    U8ARRAY_DATA    *pArray = OBJ_NIL;
    int             i;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Base64_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_BASE64);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("test failed");
#ifdef   BASE64_MSGS
        Base64_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        fprintf(stderr, "\tInput    : (%d)\"%s\"\n", (int)strlen(pData0), pData0);
        fprintf(stderr, "\tShould be: (%d)\"%s\"\n", (int)strlen(pBase64_0), pBase64_0);
        pStr = Base64_EncodeData((int)strlen(pData0), (void *)pData0);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        fprintf(stderr, "\tBase64   : (%d)\"%s\"\n", AStr_getSize(pStr), AStr_getData(pStr));
        i = AStr_CompareA(pStr, pBase64_0);
        XCTAssertTrue( (0 == i) );
        obj_Release(pStr);
        pStr = OBJ_NIL;

        fprintf(stderr, "\tInput    : (%d)\"%s\"\n", (int)strlen(pData1), pData1);
        fprintf(stderr, "\tShould be: (%d)\"%s\"\n", (int)strlen(pBase64_1), pBase64_1);
        pStr = Base64_EncodeData((int)strlen(pData1), (void *)pData1);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        fprintf(stderr, "\tBase64   : (%d)\"%s\"\n", AStr_getSize(pStr), AStr_getData(pStr));
        i = AStr_CompareA(pStr, pBase64_1);
        XCTAssertTrue( (0 == i) );
        obj_Release(pStr);
        pStr = OBJ_NIL;

        fprintf(stderr, "\tInput    : (%d)\"%s\"\n", (int)strlen(pData2), pData2);
        fprintf(stderr, "\tShould be: (%d)\"%s\"\n", (int)strlen(pBase64_2), pBase64_2);
        pStr = Base64_EncodeData((int)strlen(pData2), (void *)pData2);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        fprintf(stderr, "\tBase64   : (%d)\"%s\"\n", AStr_getSize(pStr), AStr_getData(pStr));
        i = AStr_CompareA(pStr, pBase64_2);
        XCTAssertTrue( (0 == i) );
        obj_Release(pStr);
        pStr = OBJ_NIL;

        fprintf(stderr, "\tInput    : (%d)\"%s\"\n", (int)strlen(pData3), pData3);
        fprintf(stderr, "\tShould be: (%d)\"%s\"\n", (int)strlen(pBase64_3), pBase64_3);
        pStr = Base64_EncodeData((int)strlen(pData3), (void *)pData3);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        fprintf(stderr, "\tBase64   : (%d)\"%s\"\n", AStr_getSize(pStr), AStr_getData(pStr));
        i = AStr_CompareA(pStr, pBase64_3);
        XCTAssertTrue( (0 == i) );
        obj_Release(pStr);
        pStr = OBJ_NIL;

        fprintf(stderr, "\tInput    : (%d)\"%s\"\n", (int)strlen(pBase64_0), pBase64_0);
        fprintf(stderr, "\tShould be: (%d)\"%s\"\n", (int)strlen(pData0), pData0);
        pArray = Base64_DecodeData((int)strlen(pBase64_0), (void *)pBase64_0);
        XCTAssertFalse( (OBJ_NIL == pArray) );
        pStr = u8Array_ToString(pArray);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        fprintf(stderr, "\tData     : (%d)\"%s\"\n", AStr_getSize(pStr), AStr_getData(pStr));
        i = AStr_CompareA(pStr, pData0);
        XCTAssertTrue( (0 == i) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        obj_Release(pArray);
        pArray = OBJ_NIL;

        fprintf(stderr, "\tInput    : (%d)\"%s\"\n", (int)strlen(pBase64_1), pBase64_1);
        fprintf(stderr, "\tShould be: (%d)\"%s\"\n", (int)strlen(pData1), pData1);
        pArray = Base64_DecodeData((int)strlen(pBase64_1), (void *)pBase64_1);
        XCTAssertFalse( (OBJ_NIL == pArray) );
        pStr = u8Array_ToString(pArray);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        fprintf(stderr, "\tData     : (%d)\"%s\"\n", AStr_getSize(pStr), AStr_getData(pStr));
        i = AStr_CompareA(pStr, pData1);
        XCTAssertTrue( (0 == i) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        obj_Release(pArray);
        pArray = OBJ_NIL;

        fprintf(stderr, "\tInput    : (%d)\"%s\"\n", (int)strlen(pBase64_2), pBase64_2);
        fprintf(stderr, "\tShould be: (%d)\"%s\"\n", (int)strlen(pData2), pData2);
        pArray = Base64_DecodeData((int)strlen(pBase64_2), (void *)pBase64_2);
        XCTAssertFalse( (OBJ_NIL == pArray) );
        pStr = u8Array_ToString(pArray);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        fprintf(stderr, "\tData     : (%d)\"%s\"\n", AStr_getSize(pStr), AStr_getData(pStr));
        i = AStr_CompareA(pStr, pData2);
        XCTAssertTrue( (0 == i) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        obj_Release(pArray);
        pArray = OBJ_NIL;

        fprintf(stderr, "\tInput    : (%d)\"%s\"\n", (int)strlen(pBase64_3), pBase64_3);
        fprintf(stderr, "\tShould be: (%d)\"%s\"\n", (int)strlen(pData3), pData3);
        pArray = Base64_DecodeData((int)strlen(pBase64_3), (void *)pBase64_3);
        XCTAssertFalse( (OBJ_NIL == pArray) );
        pStr = u8Array_ToString(pArray);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        fprintf(stderr, "\tData     : (%d)\"%s\"\n", AStr_getSize(pStr), AStr_getData(pStr));
        i = AStr_CompareA(pStr, pData3);
        XCTAssertTrue( (0 == i) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        obj_Release(pArray);
        pArray = OBJ_NIL;

        {
            ASTR_DATA       *pStr = Base64_ToDebugString(pObj, 4);
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



ERESULT         Test_Base64_Test05 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BASE64_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Base64_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_BASE64);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("test failed");
#ifdef   BASE64_MSGS
        Base64_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        {
            ASTR_DATA       *pStr = Base64_ToDebugString(pObj, 4);
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
    TestExec("OpenClose", Test_Base64_OpenClose, NULL, NULL);
    //TestExec("Copy01", Test_Base64_Copy01, NULL, NULL);
    TestExec("Test01", Test_Base64_Test01, NULL, NULL);
    TestExec("Test02", Test_Base64_Test02, NULL, NULL);
    TestExec("Test03", Test_Base64_Test03, NULL, NULL);
    TestExec("Test04", Test_Base64_Test04, NULL, NULL);
    TestExec("Test05", Test_Base64_Test05, NULL, NULL);

    obj_Release(pTest);
    pTest = OBJ_NIL;

    // Return to Operating System.
    return 0;
}



