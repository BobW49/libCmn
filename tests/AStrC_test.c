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
#include    <AStrC_internal.h>
#include    <JsonIn.h>
#include    <SrcErrors.h>
#include    <szTbl.h>






ERESULT         Test_AStrC_OpenClose (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTRC_DATA      *pObj = OBJ_NIL;
    bool            fRc;
    ASTRC_DATA	    *pCopy = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AStrC_Alloc( );
    TestForNotNull(pObj, "Missing Test Alloc() object");
    pObj = AStrC_Init( pObj );
    TestForNotNull(pObj, "Missing Test Init() object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTRC);
        TestForTrue(fRc, "Failed Ident Test");
#ifdef   ASTRC_MSGS
        AStrC_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
        
        // Test something.
        TestForSuccess("test failed");

        pCopy = AStrC_Copy(pObj);
        XCTAssertTrue( (pCopy == pObj) );
        XCTAssertTrue( (2 == obj_getRetainCount(pObj)) );
        obj_Release(pCopy);
        pCopy = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_AStrC_Copy01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTRC_DATA       *pObj1 = OBJ_NIL;
    ASTRC_DATA       *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(ASTRC_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA       *pStr = OBJ_NIL;
#endif
    //int             iRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = AStrC_New( );
    TestForNotNull(pObj1, "Missing Test object");
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_ASTRC);
        TestForTrue(fRc, "Failed Ident Test");
#ifdef   ASTRC_MSGS
        AStrC_setMsg(pObj1, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
        
        // Test assign.
        pObj2 = AStrC_New();
        TestForNotNull(pObj2, "Missing copied object");
        //eRc = AStrC_Assign(pObj1, pObj2);
        //TestForFalse((ERESULT_FAILED(eRc)), "Assignment failed");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_ASTRC);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = AStrC_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = AStrC_Copy(pObj1);
        TestForNotNull(pObj2, "Missing copied object");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_ASTRC);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = AStrC_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(ASTRC_JSON_SUPPORT) && defined(XYZZY)
        pStr = AStrC_ToJson(pObj1);
        TestForNotNull(pStr, "Missing JSON output");
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = AStrC_NewFromJsonString(pStr);
        TestForNotNull(pObj2, "Missing JSON created object");
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_ASTRC);
        TestForTrue(fRc, "Failed Ident Test");
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //iRc = AStrC_Compare(pObj1, pObj2);
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



ERESULT         Test_AStrC_Test01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTRC_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AStrC_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTRC);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("test failed");
#ifdef   ASTRC_MSGS
        AStrC_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        {
            ASTR_DATA       *pStr = AStrC_ToDebugString(pObj, 4);
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



ERESULT         Test_AStrC_Test02 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTRC_DATA      *pObj = OBJ_NIL;
    bool            fRc;
    ASTRC_DATA	    *pCopy = OBJ_NIL;
    const
    char            *pStrA;
    uint32_t        len;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AStrC_NewA("abc");
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTRC);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("test failed");
#ifdef   ASTRC_MSGS
        AStrC_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        len = AStrC_getLength(pObj);
        //fprintf(stderr, "len=%d\n",len);
        XCTAssertTrue( (3 == len) );
        pStrA = AStrC_getData(pObj);
        XCTAssertTrue( (0 == strcmp(pStrA, "abc")) );
        pCopy = AStrC_Copy(pObj);
        XCTAssertTrue( (pCopy == pObj) );
        XCTAssertTrue( (2 == obj_getRetainCount(pObj)) );
        len = AStrC_getLength(pCopy);
        XCTAssertTrue( (3 == len) );
        pStrA = AStrC_getData(pCopy);
        XCTAssertTrue( (0 == strcmp(pStrA, "abc")) );
        obj_Release(pCopy);
        pCopy = OBJ_NIL;

        {
            ASTR_DATA       *pStr = AStrC_ToDebugString(pObj, 4);
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



ERESULT         Test_AStrC_Test03 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTRC_DATA      *pObj = OBJ_NIL;
    bool            fRc;
    ASTRC_DATA      *pObj2 = OBJ_NIL;
    const
    char            *pStr;
    uint32_t        len;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AStrC_NewA("abc");
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTRC);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("test failed");
#ifdef   ASTRC_MSGS
        AStrC_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        len = AStrC_getLength(pObj);
        //fprintf(stderr, "len=%d\n",len);
        XCTAssertTrue( (3 == len) );
        pStr = AStrC_getData(pObj);
        XCTAssertTrue( (0 == strcmp(pStr, "abc")) );
        pObj2 = AStrC_AppendA(pObj, "def");
        XCTAssertFalse( (OBJ_NIL == pObj2) );
        len = AStrC_getLength(pObj2);
        XCTAssertTrue( (6 == len) );
        pStr = AStrC_getData(pObj2);
        XCTAssertTrue( (0 == strcmp(pStr, "abcdef")) );
        obj_Release(pObj2);
        pObj2 = OBJ_NIL;
        
        {
            ASTR_DATA       *pStr = AStrC_ToDebugString(pObj, 4);
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



ERESULT         Test_AStrC_Test04 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTRC_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    ASTRC_DATA      *pObj2 = OBJ_NIL;
    ASTRC_DATA      *pObj3 = OBJ_NIL;
    const
    char            *pStr;
    uint32_t        len;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AStrC_NewA("abc");
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTRC);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("test failed");
#ifdef   ASTRC_MSGS
        AStrC_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        len = AStrC_getLength(pObj);
        //fprintf(stderr, "len=%d\n",len);
        XCTAssertTrue( (3 == len) );
        pStr = AStrC_getData(pObj);
        XCTAssertTrue( (0 == strcmp(pStr, "abc")) );
        pObj2 = AStrC_NewA("def");
        XCTAssertFalse( (OBJ_NIL == pObj2) );
        if (pObj2) {
            len = AStrC_getLength(pObj2);
            XCTAssertTrue( (3 == len) );
            pStr = AStrC_getData(pObj2);
            XCTAssertTrue( (0 == strcmp(pStr, "def")) );
            
            pObj3 = AStrC_Append(pObj, pObj2);
            XCTAssertFalse( (OBJ_NIL == pObj3) );
            len = AStrC_getLength(pObj3);
            XCTAssertTrue( (6 == len) );
            pStr = AStrC_getData(pObj3);
            XCTAssertTrue( (0 == strcmp(pStr, "abcdef")) );
            obj_Release(pObj3);
            pObj3 = OBJ_NIL;
        }
        obj_Release(pObj2);
        pObj2 = OBJ_NIL;
        
        {
            ASTR_DATA       *pStr = AStrC_ToDebugString(pObj, 4);
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



ERESULT         Test_AStrC_Test05 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTRC_DATA      *pObj = OBJ_NIL;
    bool            fRc;
    ASTRC_DATA      *pOtr = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AStrC_NewA("abcdef");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    XCTAssertTrue( (6 == AStrC_getLength(pObj)) );
    XCTAssertTrue( (0 == strcmp("abcdef", AStrC_getData(pObj))) );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTRC);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("test failed");
#ifdef   ASTRC_MSGS
        AStrC_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
#ifdef XYZZY
        eRc = AStrC_Left( pObj, 3, &pOtr );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertFalse( (OBJ_NIL == pOtr) );
        XCTAssertTrue( (3 == AStrC_getLength(pOtr)) );
        XCTAssertTrue( (0 == strcmp("abc", AStrC_getData(pOtr))) );
        obj_Release(pOtr);
        pOtr = OBJ_NIL;
#endif
        
        fprintf(stderr, "\tThis will cause a breakpoint, just continue on.\n");
        pOtr = AStrC_Mid(OBJ_NIL, 4, 2);
        XCTAssertTrue( (OBJ_NIL == pOtr) );
        
        pOtr = AStrC_Mid(pObj, 4, 2);
        XCTAssertFalse( (OBJ_NIL == pOtr) );
        XCTAssertTrue( (2 == AStrC_getLength(pOtr)) );
        XCTAssertTrue( (0 == strcmp("de", AStrC_getData(pOtr))) );
        obj_Release(pOtr);
        pOtr = OBJ_NIL;
        
#ifdef XYZZY
        eRc = AStr_Right(pObj, 3, &pOtr);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertFalse( (OBJ_NIL == pOtr) );
        XCTAssertTrue( (3 == AStr_getLength(pOtr)) );
        XCTAssertTrue( (0 == strcmp("def", AStr_getData(pOtr))) );
        obj_Release(pOtr);
        pOtr = OBJ_NIL;
#endif

        {
            ASTR_DATA       *pStr = AStrC_ToDebugString(pObj, 4);
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



ERESULT         Test_AStrC_Test06 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTRC_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AStrC_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTRC);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("test failed");
#ifdef   ASTRC_MSGS
        AStrC_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        {
            ASTR_DATA       *pStr = AStrC_ToDebugString(pObj, 4);
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
    TestExec("OpenClose", Test_AStrC_OpenClose, NULL, NULL);
    //TestExec("Copy01", Test_AStrC_Copy01, NULL, NULL);
    TestExec("Test01", Test_AStrC_Test01, NULL, NULL);
    TestExec("Test02", Test_AStrC_Test02, NULL, NULL);
    TestExec("Test03", Test_AStrC_Test03, NULL, NULL);
    TestExec("Test04", Test_AStrC_Test04, NULL, NULL);

    obj_Release(pTest);
    pTest = OBJ_NIL;

    // Return to Operating System.
    return 0;
}



