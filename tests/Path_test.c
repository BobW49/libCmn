// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Disk Directory or File Path (Path)  Test Program
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
#include    <Path_internal.h>
#include    <JsonIn.h>
#include    <SrcErrors.h>
#include    <szTbl.h>






//----------------------------------------------------------------
//                      Test Open/Close
//----------------------------------------------------------------

ERESULT         Test_Path_OpenClose (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    PATH_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Path_Alloc( );
    TestForNotNull(pObj, "Missing Test Alloc() object");
    pObj = Path_Init( pObj );
    TestForNotNull(pObj, "Missing Test Init() object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_PATH);
        TestForTrue(fRc, "Failed Ident Test");
#ifdef   PATH_MSGS
        Path_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
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

ERESULT         Test_Path_Copy01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    PATH_DATA       *pObj1 = OBJ_NIL;
    PATH_DATA       *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(PATH_JSON_SUPPORT)
    ASTR_DATA       *pStr = OBJ_NIL;
#endif
    //int             iRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = Path_NewA("/Applications");
    TestForNotNull(pObj1, "Missing Test object");
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_PATH);
        TestForTrue(fRc, "Failed Ident Test");
#ifdef   PATH_MSGS
        Path_setMsg(pObj1, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
        
        // Test assign.
        pObj2 = Path_New();
        TestForNotNull(pObj2, "Missing copied object");
        eRc = Path_Assign(pObj1, pObj2);
        TestForFalse((ERESULT_FAILED(eRc)), "Assignment failed");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_PATH);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = Path_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = Path_Copy(pObj1);
        TestForNotNull(pObj2, "Missing copied object");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_PATH);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = Path_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(PATH_JSON_SUPPORT)
        pStr = Path_ToJson(pObj1);
        TestForNotNull(pStr, "Missing JSON output");
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = Path_NewFromJsonString(pStr);
        TestForNotNull(pObj2, "Missing JSON created object");
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_PATH);
        TestForTrue(fRc, "Failed Ident Test");
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //iRc = Path_Compare(pObj1, pObj2);
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

ERESULT         Test_Path_Test01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    PATH_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Path_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_PATH);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   PATH_MSGS
        Path_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        {
            ASTR_DATA       *pStr = Path_ToDebugString(pObj, 4);
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

ERESULT         Test_Path_Test02 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    PATH_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    uint32_t        index;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Path_NewA("file://Users/bob/x/tmp.txt");
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_PATH);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   PATH_MSGS
        Path_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        index = 0;
        eRc = AStr_CharFindNextW32(Path_getAStr(pObj), &index, '/');
        TestForSuccess("");
        TestForTrue((6 == index), "");
        
        {
            ASTR_DATA       *pStr = Path_ToDebugString(pObj, 4);
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

ERESULT         Test_Path_Test03 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    PATH_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    uint32_t        index;
    RW_DATETIME_DATA   
                    *pTime = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    const
    char            *pStrA;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Path_NewA(TEST_FILES_DIR "/test_ebcdic.txt");
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_PATH);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   PATH_MSGS
        Path_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        eRc = Path_Clean(pObj, NULL, OBJ_NIL);
        index = 0;      // Start at the beginning.
        eRc = Path_DateLastUpdated(pObj, &pTime);
        TestForSuccess("");
        TestForNotNull(pTime, "");
        if (pTime) {
            pStr = RW_DateTime_ToString(pTime);
            if (pStr) {
                pStrA = AStr_getData(pStr);
                fprintf(stderr, "\tDate = \"%s\"\n", pStrA);
                //TINYTEST_TRUE( (0 == strcmp(" 4/ 3/2000  1:37:14.000", AStr_getData(pStr))) );
                TestForTrue( ((*pStrA == ' ') || (*pStrA == '1')), "" );
                ++pStrA;
                TestForTrue( ((*pStrA >= '0') && (*pStrA <= '9')), "" );
                ++pStrA;
                TestForTrue( (*pStrA == '/'), "" );
                ++pStrA;
                TestForTrue( ((*pStrA == ' ') || ((*pStrA >= '1') && (*pStrA <= '3'))), "" );
                ++pStrA;
                TestForTrue( ((*pStrA >= '0') && (*pStrA <= '9')), "" );
                ++pStrA;
                TestForTrue( (*pStrA == '/'), "" );
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
            obj_Release(pTime);
            pTime = OBJ_NIL;
        }

        {
            ASTR_DATA       *pStr = Path_ToDebugString(pObj, 4);
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

ERESULT         Test_Path_Test04 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    PATH_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Path_NewFromEnv("HOME");
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_PATH);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   PATH_MSGS
        Path_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        eRc = Path_CompareA(pObj, getenv("HOME"));
        TestForTrue((0 == eRc), "");
        
        {
            ASTR_DATA       *pStr = Path_ToDebugString(pObj, 4);
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
//                          Test 5
//----------------------------------------------------------------

ERESULT         Test_Path_Test05 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    PATH_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    ASTR_DATA       *pDrive = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    PATH_DATA       *pFileName = OBJ_NIL;
    ASTR_DATA       *pFileN = OBJ_NIL;
    ASTR_DATA       *pFileE = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Path_NewA("file://Users/bob/x/tmp.txt");
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_PATH);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   PATH_MSGS
        Path_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif

        eRc = Path_SplitPath(pObj, &pDrive, &pPath, &pFileName);
        TestForSuccess("");

        TestForNotNull(pDrive, "");
        TestForTrue( (4 == AStr_getLength(pDrive)), "");
        TestForTrue( (0 == strcmp(AStr_getData(pDrive), "file")), "");
        if (pDrive) {
            obj_Release(pDrive);
            pDrive = OBJ_NIL;
        }
        
        TestForNotNull( (pPath), "" );
        TestForTrue( (12 == AStr_getLength((ASTR_DATA *)pPath)), "" );
        TestForTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pPath), "/Users/bob/x")), "" );
        if (pPath) {
            obj_Release(pPath);
            pPath = OBJ_NIL;
        }

        TestForNotNull( (pFileName), "" );
        TestForTrue( (7 == AStr_getLength((ASTR_DATA *)pFileName)), "");
        TestForTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pFileName), "tmp.txt")), "" );
        
        eRc = Path_SplitFile(pFileName, &pFileN, &pFileE);
        TestForSuccess("");
        if (pFileName) {
            obj_Release(pFileName);
            pFileName = OBJ_NIL;
        }
        
        TestForNotNull( (pFileN), "" );
        TestForTrue( (3 == AStr_getLength(pFileN)), "" );
        TestForTrue( (0 == strcmp(AStr_getData(pFileN), "tmp")), "" );
        if (pFileN) {
            obj_Release(pFileN);
            pFileN = OBJ_NIL;
        }
        
        TestForNotNull( (pFileE), "" );
        TestForTrue( (3 == AStr_getLength(pFileE)), "" );
        TestForTrue( (0 == strcmp(AStr_getData(pFileE), "txt")), "" );
        if (pFileE) {
            obj_Release(pFileE);
            pFileE = OBJ_NIL;
        }
       
        {
            ASTR_DATA       *pStr = Path_ToDebugString(pObj, 4);
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
//                          Test 6
//----------------------------------------------------------------

ERESULT         Test_Path_Test06 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    PATH_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    ASTR_DATA       *pDrive = OBJ_NIL;
    ASTR_DATA       *pDir = OBJ_NIL;
    ASTR_DATA       *pFileName = OBJ_NIL;
    ASTR_DATA       *pExt = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Path_NewA("/Users/bob/git/libCmn/programs/genEnum/tests/files/enum_test_old.txt");
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_PATH);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   PATH_MSGS
        Path_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        eRc = Path_Split(pObj, &pDrive, &pDir, &pFileName, &pExt);
        TestForSuccess("");
        
        TestForNull(pDrive, "");

        TestForNotNull(pDir, "");
        fprintf(stderr, "\tdir(%d): %s\n", AStr_getLength(pDir), AStr_getData(pDir));
        TestForTrue( (50 == AStr_getLength(pDir)), "" );
        TestForTrue( (0 == strcmp(AStr_getData(pDir), "/Users/bob/git/libCmn/programs/genEnum/tests/files")), "" );
        if (pDir) {
            obj_Release(pDir);
            pDir = OBJ_NIL;
        }

        TestForNotNull(pFileName, "");
        fprintf(stderr, "\tFileName(%d): %s\n", AStr_getLength(pFileName), AStr_getData(pFileName));
        TestForTrue( (13 == AStr_getLength(pFileName)), "" );
        TestForTrue( (0 == strcmp(AStr_getData(pFileName), "enum_test_old")), "" );
        if (pFileName) {
            obj_Release(pFileName);
            pFileName = OBJ_NIL;
        }

        TestForNotNull(pExt, "");
        fprintf(stderr, "\tExt(%d): %s\n", AStr_getLength(pExt), AStr_getData(pExt));
        TestForTrue( (3 == AStr_getLength(pExt)), "" );
        TestForTrue( (0 == strcmp(AStr_getData(pExt), "txt")), "" );
        if (pExt) {
            obj_Release(pExt);
            pExt = OBJ_NIL;
        }

        {
            ASTR_DATA       *pStr = Path_ToDebugString(pObj, 4);
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
//                          Test 7
//----------------------------------------------------------------

ERESULT         Test_Path_Test07 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    PATH_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    ASTR_DATA       *pDrive = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    PATH_DATA       *pFileName = OBJ_NIL;
    ASTR_DATA       *pFileN = OBJ_NIL;
    ASTR_DATA       *pFileE = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Path_NewA("/Users/bob/x/tmp.txt");
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_PATH);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   PATH_MSGS
        Path_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        eRc = Path_SplitPath(pObj, &pDrive, &pPath, &pFileName);
        TestForSuccess("");

        TestForNull(pDrive, "");
        
        TestForNotNull( (pPath), "" );
        TestForTrue( (12 == AStr_getLength((ASTR_DATA *)pPath)), "" );
        TestForTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pPath), "/Users/bob/x")), "" );
        if (pPath) {
            obj_Release(pPath);
            pPath = OBJ_NIL;
        }

        TestForNotNull( (pFileName), "" );
        TestForTrue( (7 == AStr_getLength((ASTR_DATA *)pFileName)), "");
        TestForTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pFileName), "tmp.txt")), "" );
        
        eRc = Path_SplitFile(pFileName, &pFileN, &pFileE);
        TestForSuccess("");
        if (pFileName) {
            obj_Release(pFileName);
            pFileName = OBJ_NIL;
        }
        
        TestForNotNull( (pFileN), "" );
        TestForTrue( (3 == AStr_getLength(pFileN)), "" );
        TestForTrue( (0 == strcmp(AStr_getData(pFileN), "tmp")), "" );
        if (pFileN) {
            obj_Release(pFileN);
            pFileN = OBJ_NIL;
        }
        
        TestForNotNull( (pFileE), "" );
        TestForTrue( (3 == AStr_getLength(pFileE)), "" );
        TestForTrue( (0 == strcmp(AStr_getData(pFileE), "txt")), "" );
        if (pFileE) {
            obj_Release(pFileE);
            pFileE = OBJ_NIL;
        }
       
        {
            ASTR_DATA       *pStr = Path_ToDebugString(pObj, 4);
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
//                          Test 8
//----------------------------------------------------------------

ERESULT         Test_Path_Test08 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    PATH_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    ASTR_DATA       *pDrive = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    PATH_DATA       *pFileName = OBJ_NIL;
    ASTR_DATA       *pFileN = OBJ_NIL;
    ASTR_DATA       *pFileE = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Path_NewA("tmp.txt");
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_PATH);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   PATH_MSGS
        Path_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        eRc = Path_SplitPath(pObj, &pDrive, &pPath, &pFileName);
        TestForSuccess("");

        TestForNull(pDrive, "");
        
        TestForNull(pPath, "");

        TestForNotNull( (pFileName), "" );
        TestForTrue( (7 == AStr_getLength((ASTR_DATA *)pFileName)), "");
        TestForTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pFileName), "tmp.txt")), "" );
        
        eRc = Path_SplitFile(pFileName, &pFileN, &pFileE);
        TestForSuccess("");
        if (pFileName) {
            obj_Release(pFileName);
            pFileName = OBJ_NIL;
        }
        
        TestForNotNull( (pFileN), "" );
        TestForTrue( (3 == AStr_getLength(pFileN)), "" );
        TestForTrue( (0 == strcmp(AStr_getData(pFileN), "tmp")), "" );
        if (pFileN) {
            obj_Release(pFileN);
            pFileN = OBJ_NIL;
        }
        
        TestForNotNull( (pFileE), "" );
        TestForTrue( (3 == AStr_getLength(pFileE)), "" );
        TestForTrue( (0 == strcmp(AStr_getData(pFileE), "txt")), "" );
        if (pFileE) {
            obj_Release(pFileE);
            pFileE = OBJ_NIL;
        }
       
        {
            ASTR_DATA       *pStr = Path_ToDebugString(pObj, 4);
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
//                          Test 9
//----------------------------------------------------------------

ERESULT         Test_Path_Test09 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    PATH_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    ASTR_DATA       *pDrive = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    PATH_DATA       *pFileName = OBJ_NIL;
    ASTR_DATA       *pFileN = OBJ_NIL;
    ASTR_DATA       *pFileE = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Path_NewA("/tmp.txt");
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_PATH);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   PATH_MSGS
        Path_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        eRc = Path_SplitPath(pObj, &pDrive, &pPath, &pFileName);
        TestForSuccess("");

        TestForNull(pDrive, "");
        
        TestForNotNull(pPath, "");
        TestForTrue( (1 == AStr_getLength((ASTR_DATA *)pPath)), "" );
        TestForTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pPath), "/")), "" );
        if (pPath) {
            obj_Release(pPath);
            pPath = OBJ_NIL;
        }

        TestForNotNull( (pFileName), "" );
        TestForTrue( (7 == AStr_getLength((ASTR_DATA *)pFileName)), "");
        TestForTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pFileName), "tmp.txt")), "" );
        
        eRc = Path_SplitFile(pFileName, &pFileN, &pFileE);
        TestForSuccess("");
        if (pFileName) {
            obj_Release(pFileName);
            pFileName = OBJ_NIL;
        }
        
        TestForNotNull( (pFileN), "" );
        TestForTrue( (3 == AStr_getLength(pFileN)), "" );
        TestForTrue( (0 == strcmp(AStr_getData(pFileN), "tmp")), "" );
        if (pFileN) {
            obj_Release(pFileN);
            pFileN = OBJ_NIL;
        }
        
        TestForNotNull( (pFileE), "" );
        TestForTrue( (3 == AStr_getLength(pFileE)), "" );
        TestForTrue( (0 == strcmp(AStr_getData(pFileE), "txt")), "" );
        if (pFileE) {
            obj_Release(pFileE);
            pFileE = OBJ_NIL;
        }
       
        {
            ASTR_DATA       *pStr = Path_ToDebugString(pObj, 4);
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
//                          Test 10
//----------------------------------------------------------------

ERESULT         Test_Path_Test10 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    PATH_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    ASTR_DATA       *pDrive = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    PATH_DATA       *pFileName = OBJ_NIL;
    ASTR_DATA       *pFileN = OBJ_NIL;
    ASTR_DATA       *pFileE = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Path_NewA("file:tmp.txt");
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_PATH);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   PATH_MSGS
        Path_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        eRc = Path_SplitPath(pObj, &pDrive, &pPath, &pFileName);
        TestForSuccess("");

        TestForNotNull(pDrive, "");
        TestForTrue( (4 == AStr_getLength((ASTR_DATA *)pDrive)), "" );
        TestForTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pDrive), "file")), "" );
        if (pDrive) {
            obj_Release(pDrive);
            pDrive = OBJ_NIL;
        }

        TestForNull(pPath, "");

        TestForNotNull( (pFileName), "" );
        TestForTrue( (7 == AStr_getLength((ASTR_DATA *)pFileName)), "");
        TestForTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pFileName), "tmp.txt")), "" );
        
        eRc = Path_SplitFile(pFileName, &pFileN, &pFileE);
        TestForSuccess("");
        if (pFileName) {
            obj_Release(pFileName);
            pFileName = OBJ_NIL;
        }
        
        TestForNotNull( (pFileN), "" );
        TestForTrue( (3 == AStr_getLength(pFileN)), "" );
        TestForTrue( (0 == strcmp(AStr_getData(pFileN), "tmp")), "" );
        if (pFileN) {
            obj_Release(pFileN);
            pFileN = OBJ_NIL;
        }
        
        TestForNotNull( (pFileE), "" );
        TestForTrue( (3 == AStr_getLength(pFileE)), "" );
        TestForTrue( (0 == strcmp(AStr_getData(pFileE), "txt")), "" );
        if (pFileE) {
            obj_Release(pFileE);
            pFileE = OBJ_NIL;
        }
       
        {
            ASTR_DATA       *pStr = Path_ToDebugString(pObj, 4);
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
//                          Test 11
//----------------------------------------------------------------

ERESULT         Test_Path_Test11 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    PATH_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    ASTR_DATA       *pDrive = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    PATH_DATA       *pFileName = OBJ_NIL;
    ASTR_DATA       *pFileN = OBJ_NIL;
    ASTR_DATA       *pFileE = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Path_NewA("file:/tmp.txt");
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_PATH);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   PATH_MSGS
        Path_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        eRc = Path_SplitPath(pObj, &pDrive, &pPath, &pFileName);
        TestForSuccess("");

        TestForNotNull(pDrive, "");
        TestForTrue( (4 == AStr_getLength((ASTR_DATA *)pDrive)), "" );
        TestForTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pDrive), "file")), "" );
        if (pDrive) {
            obj_Release(pDrive);
            pDrive = OBJ_NIL;
        }

        TestForNotNull(pPath, "");
        TestForTrue( (1 == AStr_getLength((ASTR_DATA *)pPath)), "" );
        TestForTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pPath), "/")), "" );
        if (pPath) {
            obj_Release(pPath);
            pPath = OBJ_NIL;
        }

        TestForNotNull( (pFileName), "" );
        TestForTrue( (7 == AStr_getLength((ASTR_DATA *)pFileName)), "");
        TestForTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pFileName), "tmp.txt")), "" );
        
        eRc = Path_SplitFile(pFileName, &pFileN, &pFileE);
        TestForSuccess("");
        if (pFileName) {
            obj_Release(pFileName);
            pFileName = OBJ_NIL;
        }
        
        TestForNotNull( (pFileN), "" );
        TestForTrue( (3 == AStr_getLength(pFileN)), "" );
        TestForTrue( (0 == strcmp(AStr_getData(pFileN), "tmp")), "" );
        if (pFileN) {
            obj_Release(pFileN);
            pFileN = OBJ_NIL;
        }
        
        TestForNotNull( (pFileE), "" );
        TestForTrue( (3 == AStr_getLength(pFileE)), "" );
        TestForTrue( (0 == strcmp(AStr_getData(pFileE), "txt")), "" );
        if (pFileE) {
            obj_Release(pFileE);
            pFileE = OBJ_NIL;
        }
       
        {
            ASTR_DATA       *pStr = Path_ToDebugString(pObj, 4);
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
//                          Test 12
//----------------------------------------------------------------

ERESULT         Test_Path_Test12 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    PATH_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    ASTR_DATA       *pDrive = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    PATH_DATA       *pFileName = OBJ_NIL;
    ASTR_DATA       *pFileN = OBJ_NIL;
    ASTR_DATA       *pFileE = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Path_NewA(":/tmp.txt");
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_PATH);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   PATH_MSGS
        Path_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        eRc = Path_SplitPath(pObj, &pDrive, &pPath, &pFileName);
        TestForSuccess("");

        TestForNull(pDrive, "");

        TestForNotNull(pPath, "");
        TestForTrue( (1 == AStr_getLength((ASTR_DATA *)pPath)), "" );
        TestForTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pPath), "/")), "" );
        if (pPath) {
            obj_Release(pPath);
            pPath = OBJ_NIL;
        }

        TestForNotNull( (pFileName), "" );
        TestForTrue( (7 == AStr_getLength((ASTR_DATA *)pFileName)), "");
        TestForTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pFileName), "tmp.txt")), "" );
        
        eRc = Path_SplitFile(pFileName, &pFileN, &pFileE);
        TestForSuccess("");
        if (pFileName) {
            obj_Release(pFileName);
            pFileName = OBJ_NIL;
        }
        
        TestForNotNull( (pFileN), "" );
        TestForTrue( (3 == AStr_getLength(pFileN)), "" );
        TestForTrue( (0 == strcmp(AStr_getData(pFileN), "tmp")), "" );
        if (pFileN) {
            obj_Release(pFileN);
            pFileN = OBJ_NIL;
        }
        
        TestForNotNull( (pFileE), "" );
        TestForTrue( (3 == AStr_getLength(pFileE)), "" );
        TestForTrue( (0 == strcmp(AStr_getData(pFileE), "txt")), "" );
        if (pFileE) {
            obj_Release(pFileE);
            pFileE = OBJ_NIL;
        }
       
        {
            ASTR_DATA       *pStr = Path_ToDebugString(pObj, 4);
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
//                          Test 13
//----------------------------------------------------------------

ERESULT         Test_Path_Test13 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    PATH_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    ASTR_DATA       *pDrive = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    PATH_DATA       *pFileName = OBJ_NIL;
    ASTR_DATA       *pFileN = OBJ_NIL;
    ASTR_DATA       *pFileE = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Path_NewA("tmp");
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_PATH);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   PATH_MSGS
        Path_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        eRc = Path_SplitPath(pObj, &pDrive, &pPath, &pFileName);
        TestForSuccess("");

        TestForNull(pDrive, "");
        //TestForTrue( (4 == AStr_getLength((ASTR_DATA *)pDrive)), "" );
        //TestForTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pDrive), "file")), "" );
        if (pDrive) {
            obj_Release(pDrive);
            pDrive = OBJ_NIL;
        }

        TestForNull(pPath, "");
        //TestForTrue( (1 == AStr_getLength((ASTR_DATA *)pPath)), "" );
        //TestForTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pPath), "/")), "" );
        if (pPath) {
            obj_Release(pPath);
            pPath = OBJ_NIL;
        }

        TestForNotNull( (pFileName), "" );
        TestForTrue( (3 == AStr_getLength((ASTR_DATA *)pFileName)), "");
        TestForTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pFileName), "tmp")), "" );
        
        eRc = Path_SplitFile(pFileName, &pFileN, &pFileE);
        TestForSuccess("");
        if (pFileName) {
            obj_Release(pFileName);
            pFileName = OBJ_NIL;
        }
        
        TestForNotNull( (pFileN), "" );
        TestForTrue( (3 == AStr_getLength(pFileN)), "" );
        TestForTrue( (0 == strcmp(AStr_getData(pFileN), "tmp")), "" );
        if (pFileN) {
            obj_Release(pFileN);
            pFileN = OBJ_NIL;
        }
        
        TestForNull( (pFileE), "" );
        //TestForTrue( (3 == AStr_getLength(pFileE)), "" );
        //TestForTrue( (0 == strcmp(AStr_getData(pFileE), "txt")), "" );
        if (pFileE) {
            obj_Release(pFileE);
            pFileE = OBJ_NIL;
        }
       
        {
            ASTR_DATA       *pStr = Path_ToDebugString(pObj, 4);
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
//                          Test 14
//----------------------------------------------------------------

ERESULT         Test_Path_Test14 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    PATH_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    ASTR_DATA       *pDrive = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    PATH_DATA       *pFileName = OBJ_NIL;
    ASTR_DATA       *pFileN = OBJ_NIL;
    ASTR_DATA       *pFileE = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Path_NewA("/tmp/x/");
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_PATH);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   PATH_MSGS
        Path_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        eRc = Path_SplitPath(pObj, &pDrive, &pPath, &pFileName);
        TestForSuccess("");

        TestForNull(pDrive, "");
        //TestForTrue( (4 == AStr_getLength((ASTR_DATA *)pDrive)), "" );
        //TestForTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pDrive), "file")), "" );
        if (pDrive) {
            obj_Release(pDrive);
            pDrive = OBJ_NIL;
        }

        TestForNotNull(pPath, "");
        TestForTrue( (6 == AStr_getLength((ASTR_DATA *)pPath)), "" );
        TestForTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pPath), "/tmp/x")), "" );
        if (pPath) {
            obj_Release(pPath);
            pPath = OBJ_NIL;
        }

        TestForNull( (pFileName), "" );
        //TestForTrue( (3 == AStr_getLength((ASTR_DATA *)pFileName)), "");
        //TestForTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pFileName), "tmp")), "" );
        
        if (pFileName) {
            eRc = Path_SplitFile(pFileName, &pFileN, &pFileE);
            TestForSuccess("");
            if (pFileName) {
                obj_Release(pFileName);
                pFileName = OBJ_NIL;
            }
            
            TestForNotNull( (pFileN), "" );
            TestForTrue( (3 == AStr_getLength(pFileN)), "" );
            TestForTrue( (0 == strcmp(AStr_getData(pFileN), "tmp")), "" );
            if (pFileN) {
                obj_Release(pFileN);
                pFileN = OBJ_NIL;
            }
            
            TestForNull( (pFileE), "" );
            //TestForTrue( (3 == AStr_getLength(pFileE)), "" );
            //TestForTrue( (0 == strcmp(AStr_getData(pFileE), "txt")), "" );
            if (pFileE) {
                obj_Release(pFileE);
                pFileE = OBJ_NIL;
            }
        }
       
        {
            ASTR_DATA       *pStr = Path_ToDebugString(pObj, 4);
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
//                          Test 15
//----------------------------------------------------------------

ERESULT         Test_Path_Test15 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    PATH_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    ASTR_DATA       *pDrive = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    PATH_DATA       *pFileName = OBJ_NIL;
    ASTR_DATA       *pFileN = OBJ_NIL;
    ASTR_DATA       *pFileE = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Path_NewA("/tmp/x/*.h");
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_PATH);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   PATH_MSGS
        Path_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        eRc = Path_SplitPath(pObj, &pDrive, &pPath, &pFileName);
        TestForSuccess("");

        TestForNull(pDrive, "");
        //TestForTrue( (4 == AStr_getLength((ASTR_DATA *)pDrive)), "" );
        //TestForTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pDrive), "file")), "" );
        if (pDrive) {
            obj_Release(pDrive);
            pDrive = OBJ_NIL;
        }

        TestForNotNull(pPath, "");
        TestForTrue( (6 == AStr_getLength((ASTR_DATA *)pPath)), "" );
        TestForTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pPath), "/tmp/x")), "" );
        if (pPath) {
            obj_Release(pPath);
            pPath = OBJ_NIL;
        }

        TestForNotNull( (pFileName), "" );
        TestForTrue( (3 == AStr_getLength((ASTR_DATA *)pFileName)), "");
        TestForTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pFileName), "*.h")), "" );
        
        if (pFileName) {
            eRc = Path_SplitFile(pFileName, &pFileN, &pFileE);
            TestForSuccess("");
            if (pFileName) {
                obj_Release(pFileName);
                pFileName = OBJ_NIL;
            }
            
            TestForNotNull( (pFileN), "" );
            TestForTrue( (1 == AStr_getLength(pFileN)), "" );
            TestForTrue( (0 == strcmp(AStr_getData(pFileN), "*")), "" );
            if (pFileN) {
                obj_Release(pFileN);
                pFileN = OBJ_NIL;
            }
            
            TestForNotNull( (pFileE), "" );
            TestForTrue( (1 == AStr_getLength(pFileE)), "" );
            TestForTrue( (0 == strcmp(AStr_getData(pFileE), "h")), "" );
            if (pFileE) {
                obj_Release(pFileE);
                pFileE = OBJ_NIL;
            }
        }
       
        {
            ASTR_DATA       *pStr = Path_ToDebugString(pObj, 4);
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
//                          Test 16
//----------------------------------------------------------------

ERESULT         Test_Path_Test16 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    PATH_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    ASTR_DATA       *pDrive = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    PATH_DATA       *pFileName = OBJ_NIL;
    ASTR_DATA       *pFileN = OBJ_NIL;
    ASTR_DATA       *pFileE = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Path_NewA("/tmp/x/a*.h");
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_PATH);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   PATH_MSGS
        Path_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        eRc = Path_SplitPath(pObj, &pDrive, &pPath, &pFileName);
        TestForSuccess("");

        TestForNull(pDrive, "");
        //TestForTrue( (4 == AStr_getLength((ASTR_DATA *)pDrive)), "" );
        //TestForTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pDrive), "file")), "" );
        if (pDrive) {
            obj_Release(pDrive);
            pDrive = OBJ_NIL;
        }

        TestForNotNull(pPath, "");
        TestForTrue( (6 == AStr_getLength((ASTR_DATA *)pPath)), "" );
        TestForTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pPath), "/tmp/x")), "" );
        if (pPath) {
            obj_Release(pPath);
            pPath = OBJ_NIL;
        }

        TestForNotNull( (pFileName), "" );
        TestForTrue( (4 == AStr_getLength((ASTR_DATA *)pFileName)), "");
        TestForTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pFileName), "a*.h")), "" );
        
        if (pFileName) {
            eRc = Path_SplitFile(pFileName, &pFileN, &pFileE);
            TestForSuccess("");
            if (pFileName) {
                obj_Release(pFileName);
                pFileName = OBJ_NIL;
            }
            
            TestForNotNull( (pFileN), "" );
            TestForTrue( (2 == AStr_getLength(pFileN)), "" );
            TestForTrue( (0 == strcmp(AStr_getData(pFileN), "a*")), "" );
            if (pFileN) {
                obj_Release(pFileN);
                pFileN = OBJ_NIL;
            }
            
            TestForNotNull( (pFileE), "" );
            TestForTrue( (1 == AStr_getLength(pFileE)), "" );
            TestForTrue( (0 == strcmp(AStr_getData(pFileE), "h")), "" );
            if (pFileE) {
                obj_Release(pFileE);
                pFileE = OBJ_NIL;
            }
        }
       
        {
            ASTR_DATA       *pStr = Path_ToDebugString(pObj, 4);
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
//                          Test 17
//----------------------------------------------------------------

ERESULT         Test_Path_Test17 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    PATH_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    ASTR_DATA       *pDrive = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    PATH_DATA       *pFileName = OBJ_NIL;
    ASTR_DATA       *pFileN = OBJ_NIL;
    ASTR_DATA       *pFileE = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Path_NewA("/tmp/x/?a*.??h");
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_PATH);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   PATH_MSGS
        Path_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        eRc = Path_SplitPath(pObj, &pDrive, &pPath, &pFileName);
        TestForSuccess("");

        TestForNull(pDrive, "");
        //TestForTrue( (4 == AStr_getLength((ASTR_DATA *)pDrive)), "" );
        //TestForTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pDrive), "file")), "" );
        if (pDrive) {
            obj_Release(pDrive);
            pDrive = OBJ_NIL;
        }

        TestForNotNull(pPath, "");
        TestForTrue( (6 == AStr_getLength((ASTR_DATA *)pPath)), "" );
        TestForTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pPath), "/tmp/x")), "" );
        if (pPath) {
            obj_Release(pPath);
            pPath = OBJ_NIL;
        }

        TestForNotNull( (pFileName), "" );
        TestForTrue( (7 == AStr_getLength((ASTR_DATA *)pFileName)), "");
        TestForTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pFileName), "?a*.??h")), "" );
        
        if (pFileName) {
            eRc = Path_SplitFile(pFileName, &pFileN, &pFileE);
            TestForSuccess("");
            if (pFileName) {
                obj_Release(pFileName);
                pFileName = OBJ_NIL;
            }
            
            TestForNotNull( (pFileN), "" );
            TestForTrue( (3 == AStr_getLength(pFileN)), "" );
            TestForTrue( (0 == strcmp(AStr_getData(pFileN), "?a*")), "" );
            if (pFileN) {
                obj_Release(pFileN);
                pFileN = OBJ_NIL;
            }
            
            TestForNotNull( (pFileE), "" );
            TestForTrue( (3 == AStr_getLength(pFileE)), "" );
            TestForTrue( (0 == strcmp(AStr_getData(pFileE), "??h")), "" );
            if (pFileE) {
                obj_Release(pFileE);
                pFileE = OBJ_NIL;
            }
        }
       
        {
            ASTR_DATA       *pStr = Path_ToDebugString(pObj, 4);
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
//                          Test 18
//----------------------------------------------------------------

ERESULT         Test_Path_Test18 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    PATH_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    ASTR_DATA       *pDrive = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    PATH_DATA       *pFileName = OBJ_NIL;
    ASTR_DATA       *pFileN = OBJ_NIL;
    ASTR_DATA       *pFileE = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Path_NewA("/x/y/z.txt");
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_PATH);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   PATH_MSGS
        Path_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        eRc = Path_SplitFile(pObj, &pFileN, &pFileE);
        TestForSuccess("");
        if (pFileName) {
            obj_Release(pFileName);
            pFileName = OBJ_NIL;
        }
        
        TestForNotNull( (pFileN), "" );
        TestForTrue( (6 == AStr_getLength(pFileN)), "" );
        TestForTrue( (0 == strcmp(AStr_getData(pFileN), "/x/y/z")), "" );
        if (pFileN) {
            obj_Release(pFileN);
            pFileN = OBJ_NIL;
        }
        
        TestForNotNull( (pFileE), "" );
        TestForTrue( (3 == AStr_getLength(pFileE)), "" );
        TestForTrue( (0 == strcmp(AStr_getData(pFileE), "txt")), "" );
        if (pFileE) {
            obj_Release(pFileE);
            pFileE = OBJ_NIL;
        }
        {
            ASTR_DATA       *pStr = Path_ToDebugString(pObj, 4);
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
//                          Test 19
//----------------------------------------------------------------

ERESULT         Test_Path_Test19 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    PATH_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Path_NewA("//tmp/");
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_PATH);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   PATH_MSGS
        Path_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
        
        eRc = Path_Clean(pObj, NULL, OBJ_NIL);
        TestForSuccess("");
        TestForTrue( (4 == AStr_getLength((ASTR_DATA *)pObj)), "" );
        TestForTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pObj), "/tmp")), "" );

        {
            ASTR_DATA       *pStr = Path_ToDebugString(pObj, 4);
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
//                          Test 20
//----------------------------------------------------------------

ERESULT         Test_Path_Test20 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    PATH_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Path_NewA("/");
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_PATH);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   PATH_MSGS
        Path_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        eRc = Path_Clean(pObj, NULL, OBJ_NIL);
        TestForSuccess("");
        TestForTrue( (1 == AStr_getLength((ASTR_DATA *)pObj)), "" );
        TestForTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pObj), "/")), "" );

        {
            ASTR_DATA       *pStr = Path_ToDebugString(pObj, 4);
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
//                          Test 21
//----------------------------------------------------------------

ERESULT         Test_Path_Test21 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    PATH_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Path_NewA("/./");
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_PATH);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   PATH_MSGS
        Path_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        eRc = Path_Clean(pObj, NULL, OBJ_NIL);
        TestForSuccess("");
        TestForTrue( (1 == AStr_getLength((ASTR_DATA *)pObj)), "" );
        TestForTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pObj), "/")), "" );

        {
            ASTR_DATA       *pStr = Path_ToDebugString(pObj, 4);
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
//                          Test 22
//----------------------------------------------------------------

ERESULT         Test_Path_Test22 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    PATH_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Path_NewA("x/./y");
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_PATH);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   PATH_MSGS
        Path_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        eRc = Path_Clean(pObj, NULL, OBJ_NIL);
        TestForSuccess("");
        TestForTrue( (3 == AStr_getLength((ASTR_DATA *)pObj)), "" );
        TestForTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pObj), "x/y")), "" );

        {
            ASTR_DATA       *pStr = Path_ToDebugString(pObj, 4);
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
//                          Test 23
//----------------------------------------------------------------

ERESULT         Test_Path_Test23 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    PATH_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Path_NewA("x//y");
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_PATH);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   PATH_MSGS
        Path_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        eRc = Path_Clean(pObj, NULL, OBJ_NIL);
        TestForSuccess("");
        TestForTrue( (3 == AStr_getLength((ASTR_DATA *)pObj)), "" );
        TestForTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pObj), "x/y")), "" );

        {
            ASTR_DATA       *pStr = Path_ToDebugString(pObj, 4);
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
//                          Test 24
//----------------------------------------------------------------

ERESULT         Test_Path_Test24 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    PATH_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    char            nameA[256];
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Path_NewA("~/y.tmp");
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_PATH);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   PATH_MSGS
        Path_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        eRc = Path_Clean(pObj, NULL, OBJ_NIL);
        TestForSuccess("");
        strcpy(nameA, getenv("HOME"));
        strcat(nameA, "/y.tmp");
        //TestForTrue( (3 == AStr_getLength((ASTR_DATA *)pObj)), "" );
        TestForTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pObj), nameA)), "" );

        {
            ASTR_DATA       *pStr = Path_ToDebugString(pObj, 4);
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
//                          Test 25
//----------------------------------------------------------------

ERESULT         Test_Path_Test25 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    PATH_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    const
    char            *pszStr;
    uint32_t        i;
    char            nameA[256];

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Path_NewA("./y.tmp");
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_PATH);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   PATH_MSGS
        Path_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        fprintf(stderr, "\tBefore: %s\n", Path_getData(pObj));
        eRc = Path_Clean(pObj, NULL, OBJ_NIL);
        TestForSuccess("");
        fprintf(stderr, "\tAfter: %s\n", Path_getData(pObj));
        strcpy(nameA, getenv("HOME"));
        strcat(nameA, "/y.tmp");
        //TestForTrue( (3 == AStr_getLength((ASTR_DATA *)pObj)), "" );
        //TestForTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pObj), nameA)), "" );

        {
            ASTR_DATA       *pStr = Path_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    pObj = Path_NewA("../y.tmp");
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_PATH);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   PATH_MSGS
        Path_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        fprintf(stderr, "\tBefore: %s\n", Path_getData(pObj));
        eRc = Path_Clean(pObj, NULL, OBJ_NIL);
        TestForSuccess("");
        fprintf(stderr, "\tAfter: %s\n", Path_getData(pObj));
        strcpy(nameA, getenv("HOME"));
        strcat(nameA, "/y.tmp");
        //TestForTrue( (3 == AStr_getLength((ASTR_DATA *)pObj)), "" );
        //TestForTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pObj), nameA)), "" );

        {
            ASTR_DATA       *pStr = Path_ToDebugString(pObj, 4);
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
//                          Test 26
//----------------------------------------------------------------

ERESULT         Test_Path_Test26 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    PATH_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    ASTR_DATA       *pStr;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Path_NewA("xy z.txt");
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_PATH);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   PATH_MSGS
        Path_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        eRc = Path_ToBash(pObj,&pStr);
        TestForSuccess("");
        TestForTrue( (9 == AStr_getLength(pStr)), "" );
        TestForTrue( (0 == AStr_CompareA(pStr, "xy\\ z.txt")), "" );
        obj_Release(pStr);
        pStr = NULL;
        
        {
            ASTR_DATA       *pStr = Path_ToDebugString(pObj, 4);
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
//                          Test 27
//----------------------------------------------------------------

ERESULT         Test_Path_Test27 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    PATH_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    char            nameA[256];

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Path_NewA("${HOME}");
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_PATH);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   PATH_MSGS
        Path_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        fprintf(stderr, "\tBefore: %s\n", Path_getData(pObj));
        eRc = Path_ExpandVars(pObj, NULL, OBJ_NIL);
        TestForSuccess("");
        fprintf(stderr, "\tAfter: %s\n", Path_getData(pObj));
        strcpy(nameA, getenv("HOME"));
        //strcat(nameA, "/y.tmp");
        //TestForTrue( (3 == AStr_getLength((ASTR_DATA *)pObj)), "" );
        TestForTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pObj), nameA)), "" );
        
        {
            ASTR_DATA       *pStr = Path_ToDebugString(pObj, 4);
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
//                          Test 28
//----------------------------------------------------------------

ERESULT         Test_Path_Test28 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    PATH_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    char            nameA[256];

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Path_NewA("${HOME}$${HOME}");
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_PATH);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   PATH_MSGS
        Path_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        fprintf(stderr, "\tBefore: %s\n", Path_getData(pObj));
        eRc = Path_ExpandVars(pObj, NULL, OBJ_NIL);
        TestForSuccess("");
        fprintf(stderr, "\tAfter: %s\n", Path_getData(pObj));
        strcpy(nameA, getenv("HOME"));
        strcat(nameA, "$");
        strcat(nameA, getenv("HOME"));
        //TestForTrue( (3 == AStr_getLength((ASTR_DATA *)pObj)), "" );
        TestForTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pObj), nameA)), "" );
        
        {
            ASTR_DATA       *pStr = Path_ToDebugString(pObj, 4);
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
//                          Test 29
//----------------------------------------------------------------

ERESULT         Test_Path_Test29 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    PATH_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    const
    char            *pConfirmA = "/Users/bob/git/compiler/tools/lemon/tests/files";
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Path_NewA("/Users/bob/git/compiler/tools/lemon/tests/files/Expr80.y");
    TestForNotNull(pObj, "");
    if (pObj) {

        obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_PATH);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   PATH_MSGS
        Path_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        fprintf(stderr, "\tBefore: %s\n", Path_getData(pObj));
        eRc = Path_RemoveFileName(pObj);
        TestForSuccess("");
        fprintf(stderr, "\tAfter: %s\n", Path_getData(pObj));
        TestForTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pObj), pConfirmA)), "" );

        {
            ASTR_DATA       *pStr = Path_ToDebugString(pObj, 4);
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
//                          Test 30
//----------------------------------------------------------------

ERESULT         Test_Path_Test30 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    PATH_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Path_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_PATH);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   PATH_MSGS
        Path_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        {
            ASTR_DATA       *pStr = Path_ToDebugString(pObj, 4);
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
//                          Test 31
//----------------------------------------------------------------

ERESULT         Test_Path_Test31 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    PATH_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Path_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_PATH);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   PATH_MSGS
        Path_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        {
            ASTR_DATA       *pStr = Path_ToDebugString(pObj, 4);
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
//                          Test 32
//----------------------------------------------------------------

ERESULT         Test_Path_Test32 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    PATH_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Path_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_PATH);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   PATH_MSGS
        Path_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        {
            ASTR_DATA       *pStr = Path_ToDebugString(pObj, 4);
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
//                          Test 33
//----------------------------------------------------------------

ERESULT         Test_Path_Test33 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    PATH_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Path_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_PATH);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   PATH_MSGS
        Path_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        {
            ASTR_DATA       *pStr = Path_ToDebugString(pObj, 4);
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
//                          Test 34
//----------------------------------------------------------------

ERESULT         Test_Path_Test34 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    PATH_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Path_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_PATH);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   PATH_MSGS
        Path_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        {
            ASTR_DATA       *pStr = Path_ToDebugString(pObj, 4);
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
//                          Test 35
//----------------------------------------------------------------

ERESULT         Test_Path_Test35 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    PATH_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Path_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_PATH);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   PATH_MSGS
        Path_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        {
            ASTR_DATA       *pStr = Path_ToDebugString(pObj, 4);
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
//                          Test 36
//----------------------------------------------------------------

ERESULT         Test_Path_Test36 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    PATH_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Path_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_PATH);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   PATH_MSGS
        Path_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        {
            ASTR_DATA       *pStr = Path_ToDebugString(pObj, 4);
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
//                          Test 37
//----------------------------------------------------------------

ERESULT         Test_Path_Test37 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    PATH_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Path_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_PATH);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   PATH_MSGS
        Path_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        {
            ASTR_DATA       *pStr = Path_ToDebugString(pObj, 4);
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
//                          Test 38
//----------------------------------------------------------------

ERESULT         Test_Path_Test38 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    PATH_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Path_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_PATH);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   PATH_MSGS
        Path_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        {
            ASTR_DATA       *pStr = Path_ToDebugString(pObj, 4);
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
//                          Test 39
//----------------------------------------------------------------

ERESULT         Test_Path_Test39 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    PATH_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Path_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_PATH);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   PATH_MSGS
        Path_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        {
            ASTR_DATA       *pStr = Path_ToDebugString(pObj, 4);
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
    TestExec("OpenClose", Test_Path_OpenClose, NULL,   NULL);
    TestExec("Copy01", Test_Path_Copy01,       NULL,   NULL);
    TestExec("Test01", Test_Path_Test01,       NULL,   NULL);
    TestExec("Test02", Test_Path_Test02,       NULL,   NULL);
    TestExec("Test03", Test_Path_Test03,       NULL,   NULL);
    TestExec("Test04", Test_Path_Test04,       NULL,   NULL);
    TestExec("Test05", Test_Path_Test05,       NULL,   NULL);
    TestExec("Test06", Test_Path_Test06,       NULL,   NULL);
    TestExec("Test07", Test_Path_Test07,       NULL,   NULL);
    TestExec("Test08", Test_Path_Test08,       NULL,   NULL);
    TestExec("Test09", Test_Path_Test09,       NULL,   NULL);
    TestExec("Test10", Test_Path_Test10,       NULL,   NULL);
    TestExec("Test11", Test_Path_Test11,       NULL,   NULL);
    TestExec("Test12", Test_Path_Test12,       NULL,   NULL);
    TestExec("Test13", Test_Path_Test13,       NULL,   NULL);
    TestExec("Test14", Test_Path_Test14,       NULL,   NULL);
    TestExec("Test15", Test_Path_Test15,       NULL,   NULL);
    TestExec("Test16", Test_Path_Test16,       NULL,   NULL);
    TestExec("Test17", Test_Path_Test17,       NULL,   NULL);
    TestExec("Test18", Test_Path_Test18,       NULL,   NULL);
    TestExec("Test19", Test_Path_Test19,       NULL,   NULL);
    TestExec("Test20", Test_Path_Test20,       NULL,   NULL);
    TestExec("Test21", Test_Path_Test21,       NULL,   NULL);
    TestExec("Test22", Test_Path_Test22,       NULL,   NULL);
    TestExec("Test23", Test_Path_Test23,       NULL,   NULL);
    TestExec("Test24", Test_Path_Test24,       NULL,   NULL);
    TestExec("Test25", Test_Path_Test25,       NULL,   NULL);
    TestExec("Test26", Test_Path_Test26,       NULL,   NULL);
    TestExec("Test27", Test_Path_Test27,       NULL,   NULL);
    TestExec("Test28", Test_Path_Test28,       NULL,   NULL);
    TestExec("Test29", Test_Path_Test29,       NULL,   NULL);
    TestExec("Test30", Test_Path_Test30,       NULL,   NULL);
    TestExec("Test31", Test_Path_Test31,       NULL,   NULL);
    TestExec("Test32", Test_Path_Test32,       NULL,   NULL);
    TestExec("Test33", Test_Path_Test33,       NULL,   NULL);
    TestExec("Test34", Test_Path_Test34,       NULL,   NULL);
    TestExec("Test35", Test_Path_Test35,       NULL,   NULL);
    TestExec("Test36", Test_Path_Test36,       NULL,   NULL);
    TestExec("Test37", Test_Path_Test37,       NULL,   NULL);
    TestExec("Test38", Test_Path_Test38,       NULL,   NULL);
    TestExec("Test39", Test_Path_Test39,       NULL,   NULL);

    obj_Release(pTest);
    pTest = OBJ_NIL;

    // Return to Operating System.
    return 0;
}



