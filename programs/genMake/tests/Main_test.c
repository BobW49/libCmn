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
 TestForNotTrue(test, error)
 TestForZero(test, error)
 TestForNotZero(test, error)
 */





#include    <test_defs.h>
#include    <Test_internal.h>
#include    <trace.h>
#include    <Main_internal.h>
#include    <JsonIn.h>
#include    <SrcErrors.h>
#include    <szTbl.h>



//#define     TEST_ASSIGN_COPY    1



ERESULT         Test_Main_OpenClose (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    MAIN_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Main_Alloc( );
    TestForNotNull(pObj, "Missing Test Alloc() object");
    pObj = Main_Init( pObj );
    TestForNotNull(pObj, "Missing Test Init() object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_MAIN);
        TestForTrue(fRc, "Failed Ident Test");
        
        // Test something.
        TestForSuccess("test failed");

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



#ifdef  TEST_ASSIGN_COPY
ERESULT         Test_Main_Copy01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    MAIN_DATA       *pObj1 = OBJ_NIL;
    MAIN_DATA       *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(MAIN_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA       *pStr = OBJ_NIL;
#endif
    //int             iRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = Main_New( );
    TestForNotNull(pObj1, "Missing Test object");
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_MAIN);
        TestForTrue(fRc, "Failed Ident Test");
        
        // Test assign.
        pObj2 = Main_New();
        TestForNotNull(pObj2, "Missing copied object");
        eRc = Main_Assign(pObj1, pObj2);
        TestForFalse((ERESULT_FAILED(eRc)), "Assignment failed");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_MAIN);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = Main_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = Main_Copy(pObj1);
        TestForNotNull(pObj2, "Missing copied object");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_MAIN);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = Main_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(MAIN_JSON_SUPPORT) && defined(XYZZY)
        pStr = Main_ToJson(pObj1);
        TestForNotNull(pStr, "Missing JSON output");
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = Main_NewFromJsonString(pStr);
        TestForNotNull(pObj2, "Missing JSON created object");
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_MAIN);
        TestForTrue(fRc, "Failed Ident Test");
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //iRc = Main_Compare(pObj1, pObj2);
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
#endif



ERESULT         Test_Main_Test01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    MAIN_DATA       *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    bool            fRc;
    bool            fDump = true;
    int             iRc;
    NODELIB_DATA    *pLib = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    ASTR_DATA       *pInput = OBJ_NIL;
    ASTR_DATA       *pCheck = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pPath = Path_NewA(TEST_FILES_DIR "/libJson01.txt");
    TestForNotNull(pPath, "");
    fprintf(stderr, "\tInput Path: \"%s\"\n", Path_getData(pPath));
    pInput = AStr_NewFromUtf8File(pPath);
    TestForNotNull(pInput, "");
    obj_Release(pPath);
    pPath = OBJ_NIL;
    pPath = Path_NewA(TEST_FILES_DIR "/libJson01_macos64_x86_64.txt");
    TestForNotNull(pPath, "");
    fprintf(stderr, "\tCheck Path: \"%s\"\n", Path_getData(pPath));
    pCheck = AStr_NewFromUtf8File(pPath);
    TestForNotNull(pCheck, "");
    obj_Release(pPath);
    pPath = OBJ_NIL;

    pObj = Main_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_MAIN);
        TestForTrue(fRc, "Failed Ident Test");
        
        {
            ASTR_DATA       *pStr = Main_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        pObj->pOutput = TextOut_NewAStr(OBJ_NIL);
        TestForNotNull(pObj->pOutput, "");
        TextOut_setTabExpand(pObj->pOutput, false);

        //appl_setDebug((APPL_DATA *)pObj, true);
        if (fDump) {
            fprintf(stderr, "INPUT_BEGIN:\n%sINPUT_END:\n\n\n", AStr_getData(pInput));
        }
        eRc = Main_ParseInputStrA(pObj, AStr_getData(pInput));
        TestForSuccess("");
        TestForNotNull(pObj->pParser, "");

        pLib = SrcParse_getLib(pObj->pParser);
        TestForNotNull(pLib, "");

        eRc = Main_SetupArch(pObj, OSARCH_X86_64);
        TestForSuccess("");
        eRc = Main_SetupType(pObj, OSTYPE_MACOS64);
        TestForSuccess("");
        eRc = Main_GenMakefile(pObj);
        TestForSuccess("");
        
        if (fDump) {
            pStr = Main_getStr(pObj);
            TestForNotNull(pStr, "");
            fprintf(stderr, "GEN_BEGIN:\n%sGEN_END:\n\n\n", AStr_getData(pStr));
        }
       
        iRc = Test_CheckStrings(this, pCheck, Main_getStr(pObj), 4);
        TestForZero(iRc, "");

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    obj_Release(pCheck);
    pCheck = OBJ_NIL;
    obj_Release(pInput);
    pInput = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_Main_Test02 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    MAIN_DATA       *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    bool            fRc;
    bool            fDump = true;
    int             iRc;
    NODELIB_DATA    *pLib = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    ASTR_DATA       *pInput = OBJ_NIL;
    ASTR_DATA       *pCheck = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pPath = Path_NewA(TEST_FILES_DIR "/libJson02.txt");
    TestForNotNull(pPath, "");
    fprintf(stderr, "\tInput Path: \"%s\"\n", Path_getData(pPath));
    pInput = AStr_NewFromUtf8File(pPath);
    TestForNotNull(pInput, "");
    obj_Release(pPath);
    pPath = OBJ_NIL;
    pPath = Path_NewA(TEST_FILES_DIR "/libJson02_macos64_x86_64.txt");
    TestForNotNull(pPath, "");
    fprintf(stderr, "\tCheck Path: \"%s\"\n", Path_getData(pPath));
    pCheck = AStr_NewFromUtf8File(pPath);
    TestForNotNull(pCheck, "");
    obj_Release(pPath);
    pPath = OBJ_NIL;

    pObj = Main_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_MAIN);
        TestForTrue(fRc, "Failed Ident Test");
        
        {
            ASTR_DATA       *pStr = Main_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        pObj->pOutput = TextOut_NewAStr(OBJ_NIL);
        TestForNotNull(pObj->pOutput, "");
        TextOut_setTabExpand(pObj->pOutput, false);

        //appl_setDebug((APPL_DATA *)pObj, true);
        if (fDump) {
            fprintf(stderr, "INPUT_BEGIN:\n%sINPUT_END:\n\n\n", AStr_getData(pInput));
        }
        eRc = Main_ParseInputStrA(pObj, AStr_getData(pInput));
        TestForSuccess("");
        TestForNotNull(pObj->pParser, "");

        pLib = SrcParse_getLib(pObj->pParser);
        TestForNotNull(pLib, "");

        eRc = Main_SetupArch(pObj, OSARCH_X86_64);
        TestForSuccess("");
        eRc = Main_SetupType(pObj, OSTYPE_MACOS64);
        TestForSuccess("");
        eRc = Main_GenMakefile(pObj);
        TestForSuccess("");
        
        if (fDump) {
            pStr = Main_getStr(pObj);
            TestForNotNull(pStr, "");
            fprintf(stderr, "GEN_BEGIN:\n%sGEN_END:\n\n\n", AStr_getData(pStr));
        }
       
        iRc = Test_CheckStrings(this, pCheck, Main_getStr(pObj), 4);
        TestForZero(iRc, "");

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    obj_Release(pCheck);
    pCheck = OBJ_NIL;
    obj_Release(pInput);
    pInput = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_Main_Test03 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    MAIN_DATA       *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    bool            fRc;
    bool            fDump = true;
    int             iRc;
    NODEPGM_DATA    *pPgm = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    ASTR_DATA       *pInput = OBJ_NIL;
    ASTR_DATA       *pCheck = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pPath = Path_NewA(TEST_FILES_DIR "/pgmJson01.txt");
    TestForNotNull(pPath, "");
    fprintf(stderr, "\tInput Path: \"%s\"\n", Path_getData(pPath));
    pInput = AStr_NewFromUtf8File(pPath);
    TestForNotNull(pInput, "");
    obj_Release(pPath);
    pPath = OBJ_NIL;
    pPath = Path_NewA(TEST_FILES_DIR "/pgmJson01_macos64_x86_64.txt");
    TestForNotNull(pPath, "");
    fprintf(stderr, "\tCheck Path: \"%s\"\n", Path_getData(pPath));
    pCheck = AStr_NewFromUtf8File(pPath);
    TestForNotNull(pCheck, "");
    obj_Release(pPath);
    pPath = OBJ_NIL;

    pObj = Main_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_MAIN);
        TestForTrue(fRc, "Failed Ident Test");
        
        {
            ASTR_DATA       *pStr = Main_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        pObj->pOutput = TextOut_NewAStr(OBJ_NIL);
        TestForNotNull(pObj->pOutput, "");
        TextOut_setTabExpand(pObj->pOutput, false);

        //appl_setDebug((APPL_DATA *)pObj, true);
        if (fDump) {
            fprintf(stderr, "INPUT_BEGIN:\n%sINPUT_END:\n\n\n", AStr_getData(pInput));
        }
        eRc = Main_ParseInputStrA(pObj, AStr_getData(pInput));
        TestForSuccess("");
        TestForNotNull(pObj->pParser, "");

        pPgm = SrcParse_getPgm(pObj->pParser);
        TestForNotNull(pPgm, "");

        eRc = Main_SetupArch(pObj, OSARCH_X86_64);
        TestForSuccess("");
        eRc = Main_SetupType(pObj, OSTYPE_MACOS64);
        TestForSuccess("");
        eRc = Main_GenMakefile(pObj);
        TestForSuccess("");
        
        if (fDump) {
            pStr = Main_getStr(pObj);
            TestForNotNull(pStr, "");
            fprintf(stderr, "GEN_BEGIN:\n%sGEN_END:\n\n\n", AStr_getData(pStr));
        }
       
        iRc = Test_CheckStrings(this, pCheck, Main_getStr(pObj), 4);
        TestForZero(iRc, "");

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    obj_Release(pCheck);
    pCheck = OBJ_NIL;
    obj_Release(pInput);
    pInput = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_Main_Test04 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    MAIN_DATA       *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    TestForNull(pStr, "");

    pObj = Main_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_MAIN);
        TestForTrue(fRc, "Failed Ident Test");
        
        {
            ASTR_DATA       *pStr = Main_ToDebugString(pObj, 4);
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



ERESULT         Test_Main_Test05 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    MAIN_DATA       *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    bool            fRc;
    bool            fDump = true;
    int             iRc;
    NODELIB_DATA    *pLib = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    ASTR_DATA       *pInput = OBJ_NIL;
    ASTR_DATA       *pCheck = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pPath = Path_NewA(TEST_FILES_DIR "/libJson01.txt");
    TestForNotNull(pPath, "");
    fprintf(stderr, "\tInput Path: \"%s\"\n", Path_getData(pPath));
    pInput = AStr_NewFromUtf8File(pPath);
    TestForNotNull(pInput, "");
    obj_Release(pPath);
    pPath = OBJ_NIL;
    pPath = Path_NewA(TEST_FILES_DIR "/libJson01_macos64_arm64.txt");
    TestForNotNull(pPath, "");
    fprintf(stderr, "\tCheck Path: \"%s\"\n", Path_getData(pPath));
    pCheck = AStr_NewFromUtf8File(pPath);
    TestForNotNull(pCheck, "");
    obj_Release(pPath);
    pPath = OBJ_NIL;

    pObj = Main_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_MAIN);
        TestForTrue(fRc, "Failed Ident Test");
        
        {
            ASTR_DATA       *pStr = Main_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        pObj->pOutput = TextOut_NewAStr(OBJ_NIL);
        TestForNotNull(pObj->pOutput, "");
        TextOut_setTabExpand(pObj->pOutput, false);

        //appl_setDebug((APPL_DATA *)pObj, true);
        if (fDump) {
            fprintf(stderr, "INPUT_BEGIN:\n%sINPUT_END:\n\n\n", AStr_getData(pInput));
        }
        eRc = Main_ParseInputStrA(pObj, AStr_getData(pInput));
        TestForSuccess("");
        TestForNotNull(pObj->pParser, "");

        pLib = SrcParse_getLib(pObj->pParser);
        TestForNotNull(pLib, "");

        eRc = Main_SetupArch(pObj, OSARCH_X86_64);
        TestForSuccess("");
        eRc = Main_SetupType(pObj, OSTYPE_MACOS64);
        TestForSuccess("");
        eRc = Main_GenMakefile(pObj);
        TestForSuccess("");
        
        if (fDump) {
            pStr = Main_getStr(pObj);
            TestForNotNull(pStr, "");
            fprintf(stderr, "GEN_BEGIN:\n%sGEN_END:\n\n\n", AStr_getData(pStr));
        }
       
        iRc = Test_CheckStrings(this, pCheck, Main_getStr(pObj), 4);
        TestForZero(iRc, "");

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    obj_Release(pCheck);
    pCheck = OBJ_NIL;
    obj_Release(pInput);
    pInput = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_Main_Test06 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    MAIN_DATA       *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    TestForNull(pStr, "");

    pObj = Main_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_MAIN);
        TestForTrue(fRc, "Failed Ident Test");
        
        {
            ASTR_DATA       *pStr = Main_ToDebugString(pObj, 4);
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



ERESULT         Test_Main_Test07 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    MAIN_DATA       *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    TestForNull(pStr, "");

    pObj = Main_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_MAIN);
        TestForTrue(fRc, "Failed Ident Test");
        
        {
            ASTR_DATA       *pStr = Main_ToDebugString(pObj, 4);
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



ERESULT         Test_Main_Test08 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    MAIN_DATA       *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    TestForNull(pStr, "");

    pObj = Main_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_MAIN);
        TestForTrue(fRc, "Failed Ident Test");
        
        {
            ASTR_DATA       *pStr = Main_ToDebugString(pObj, 4);
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
    TestExec("OpenClose", Test_Main_OpenClose, NULL, NULL);
#ifdef  TEST_ASSIGN_COPY
    TestExec("Copy01", Test_Main_Copy01, pTest, NULL, NULL);
#endif
    TestExec("Test01", Test_Main_Test01, NULL, NULL);
    TestExec("Test02", Test_Main_Test02, NULL, NULL);
    TestExec("Test03", Test_Main_Test03, NULL, NULL);
    TestExec("Test04", Test_Main_Test04, NULL, NULL);
    TestExec("Test05", Test_Main_Test05, NULL, NULL);
    TestExec("Test06", Test_Main_Test06, NULL, NULL);
    TestExec("Test07", Test_Main_Test07, NULL, NULL);
    TestExec("Test08", Test_Main_Test08, NULL, NULL);

    obj_Release(pTest);
    pTest = OBJ_NIL;

    // Return to Operating System.
    return 0;
}



