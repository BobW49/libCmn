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
#include    <CmdUtl_internal.h>
#include    <JsonIn.h>
#include    <SrcErrors.h>
#include    <szTbl.h>






ERESULT         Test_CmdUtl_OpenClose (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    CMDUTL_DATA     *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = CmdUtl_Alloc( );
    TestForNotNull(pObj, "Missing Test Alloc() object");
    pObj = CmdUtl_Init( pObj );
    TestForNotNull(pObj, "Missing Test Init() object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_CMDUTL);
        TestForTrue(fRc, "Failed Ident Test");
#ifdef   CMDUTL_MSGS
        CmdUtl_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
        
        // Test something.
        TestForSuccess("test failed");

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_CmdUtl_Copy01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    CMDUTL_DATA     *pObj1 = OBJ_NIL;
    CMDUTL_DATA     *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(CMDUTL_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA       *pStr = OBJ_NIL;
#endif
    //int             iRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = CmdUtl_New( );
    TestForNotNull(pObj1, "Missing Test object");
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_CMDUTL);
        TestForTrue(fRc, "Failed Ident Test");
#ifdef   CMDUTL_MSGS
        CmdUtl_setMsg(pObj1, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
        
        // Test assign.
        pObj2 = CmdUtl_New();
        TestForNotNull(pObj2, "Missing copied object");
        eRc = CmdUtl_Assign(pObj1, pObj2);
        TestForFalse((ERESULT_FAILED(eRc)), "Assignment failed");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_CMDUTL);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = CmdUtl_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = CmdUtl_Copy(pObj1);
        TestForNotNull(pObj2, "Missing copied object");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_CMDUTL);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = CmdUtl_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(CMDUTL_JSON_SUPPORT) && defined(XYZZY)
        pStr = CmdUtl_ToJson(pObj1);
        TestForNotNull(pStr, "Missing JSON output");
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = CmdUtl_NewFromJsonString(pStr);
        TestForNotNull(pObj2, "Missing JSON created object");
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_CMDUTL);
        TestForTrue(fRc, "Failed Ident Test");
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //iRc = CmdUtl_Compare(pObj1, pObj2);
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



ERESULT         Test_CmdUtl_Test01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    CMDUTL_DATA     *pObj = OBJ_NIL;
    bool            fRc;
    ASTR_DATA       *pStr = OBJ_NIL;
    ASTRARRAY_DATA  *pArray = OBJ_NIL;
    uint32_t        cArray;
    bool            fDebug = true;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    fprintf(stderr, "\tTesting: CmdUtl_CommandStringToArray\n");

    pObj = CmdUtl_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_CMDUTL);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   CMDUTL_MSGS
        CmdUtl_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
    pArray = CmdUtl_CommandStringToArray(" a b --c d,,e");
    TestForNotNull(pArray, "");
    cArray = AStrArray_getSize(pArray);
    fprintf(stderr, "\tArray Count: %d\n", cArray);
    TestForTrue((7 == cArray), "");

    if (pArray) {

        pStr = AStrArray_Get(pArray, 1);
        TestForNotNull(pStr, "");
        TestForTrue((0 == AStr_CompareA(pStr, "")), "");

        pStr = AStrArray_Get(pArray, 2);
        TestForNotNull(pStr, "");
        TestForTrue((0 == AStr_CompareA(pStr, "a")), "");

        pStr = AStrArray_Get(pArray, 3);
        TestForNotNull(pStr, "");
        TestForTrue((0 == AStr_CompareA(pStr, "b")), "");

        pStr = AStrArray_Get(pArray, 4);
        TestForNotNull(pStr, "");
        TestForTrue((0 == AStr_CompareA(pStr, "--c")), "");

        pStr = AStrArray_Get(pArray, 5);
        TestForNotNull(pStr, "");
        TestForTrue((0 == AStr_CompareA(pStr, "d")), "");

        pStr = AStrArray_Get(pArray, 6);
        TestForNotNull(pStr, "");
        TestForTrue((0 == AStr_CompareA(pStr, "")), "");

        pStr = AStrArray_Get(pArray, 7);
        TestForNotNull(pStr, "");
        TestForTrue((0 == AStr_CompareA(pStr, "e")), "");

        obj_Release(pArray);
        pArray = OBJ_NIL;
    }

    pArray = CmdUtl_CommandStringToArray(" --define xx=\"yy yy\" abc");
    TestForNotNull(pArray, "");
    cArray = AStrArray_getSize(pArray);
    TestForTrue((5 == cArray), "");

    if (pArray) {

        if (fDebug) {
            ASTR_DATA       *pDump;
            pDump = AStrArray_ToDebugString(pArray, 0);
            if (pDump) {
                fprintf(stderr, "%s\n", AStr_getData(pDump));
                obj_Release(pDump);
            }
        }
        pStr = AStrArray_Get(pArray, 1);
        TestForNotNull(pStr, "");
        TestForTrue((0 == AStr_CompareA(pStr, "")), "");

        pStr = AStrArray_Get(pArray, 2);
        TestForNotNull(pStr, "");
        TestForTrue((0 == AStr_CompareA(pStr, "--define")), "");

        pStr = AStrArray_Get(pArray, 3);
        TestForNotNull(pStr, "");
        TestForTrue((0 == AStr_CompareA(pStr, "xx=")), "");

        pStr = AStrArray_Get(pArray, 4);
        TestForNotNull(pStr, "");
        TestForTrue((0 == AStr_CompareA(pStr, "yy yy")), "");

        pStr = AStrArray_Get(pArray, 5);
        TestForNotNull(pStr, "");
        TestForTrue((0 == AStr_CompareA(pStr, "abc")), "");

        obj_Release(pArray);
        pArray = OBJ_NIL;
    }

        {
            ASTR_DATA       *pStr = CmdUtl_ToDebugString(pObj, 4);
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



ERESULT         Test_CmdUtl_Test02 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    CMDUTL_DATA     *pObj = OBJ_NIL;
    bool            fRc;
    char            *ppArgs[] = {
        "./test",
        "-vv",
        "-f",
        "xyzzy",
        "abc",
        "def",
        NULL
    };
    const
    char            *pOptString = "df::hv";
    int             iRc;
    char            *pArg;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    fprintf(stderr, "\tTesting: CmdUtl_NewArgs() and CmdUtl_Parse()\n");

    pObj = CmdUtl_NewArgs(6, ppArgs);
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_CMDUTL);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   CMDUTL_MSGS
        CmdUtl_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        iRc = CmdUtl_Parse(pObj, pOptString);
        TestForTrue(('v' == iRc), "");
        TestForTrue(('v' == pObj->optopt), "");
        TestForTrue((NULL == pObj->pOptArg), "");
        TestForTrue((pObj->optIndex == 1), "");
        TestForTrue((pObj->subopt == 1), "");

        fRc = CmdUtl_IsMore(pObj);
        TestForTrue((fRc), "");

        iRc = CmdUtl_Parse(pObj, pOptString);
        TestForTrue(('v' == iRc), "");
        TestForTrue(('v' == pObj->optopt), "");
        TestForTrue((NULL == pObj->pOptArg), "");
        TestForTrue((pObj->optIndex == 2), "");
        TestForTrue((pObj->subopt == 0), "");

        iRc = CmdUtl_Parse(pObj, pOptString);
        TestForTrue(('f' == iRc), "");
        TestForTrue(('f' == pObj->optopt), "");
        TestForTrue((pObj->pOptArg), "");
        TestForTrue((0 == strcmp(pObj->pOptArg, "xyzzy")), "");

        iRc = CmdUtl_Parse(pObj, pOptString);
        TestForTrue((-1 == iRc), "");
        TestForTrue((0 == pObj->optopt), "");
        TestForTrue((NULL == pObj->pOptArg), "");

        pArg = CmdUtl_NextArg(pObj);
        TestForTrue((0 == pObj->optopt), "");
        TestForTrue((pArg), "");
        TestForTrue((0 == strcmp(pArg, "abc")), "");

        fRc = CmdUtl_IsMore(pObj);
        TestForTrue((fRc), "");

        pArg = CmdUtl_NextArg(pObj);
        TestForTrue((0 == pObj->optopt), "");
        TestForTrue((pArg), "");
        TestForTrue((0 == strcmp(pArg, "def")), "");

        fRc = CmdUtl_IsMore(pObj);
        TestForTrue((!fRc), "");

        pArg = CmdUtl_NextArg(pObj);
        TestForTrue((0 == pObj->optopt), "");
        TestForTrue((NULL == pArg), "");

        {
            ASTR_DATA       *pStr = CmdUtl_ToDebugString(pObj, 4);
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



ERESULT         Test_CmdUtl_Test03 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    CMDUTL_DATA     *pObj = OBJ_NIL;
    bool            fRc;
    CMDUTL_OPTION   longDefns[5] = {
        {"debug",   'd', CMDUTL_ARG_OPTION_NONE},
        {"file",    'f', CMDUTL_ARG_OPTION_REQUIRED},
        {"help",    'h', CMDUTL_ARG_OPTION_NONE},
        {"verbose", 'v', CMDUTL_ARG_OPTION_NONE},
        {0, 0, 0}
    };
    char            *ppArgs[] = {
        "./test",
        "--verbose",
        "--file",
        "xyzzy",
        "abc",
        "-f",
        "xyzzy2",
        "def",
        NULL
    };
    int             iRc;
    char            *pArg;
    int             longIndex;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    fprintf(stderr, "\tTesting: CmdUtl_NewArgs() and CmdUtl_ParseLong()\n");

    pObj = CmdUtl_NewArgs(8, ppArgs);
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_CMDUTL);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   CMDUTL_MSGS
        CmdUtl_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        iRc = CmdUtl_ParseLong(pObj, longDefns, &longIndex);
        TestForTrue(('v' == iRc), "");
        TestForTrue(('v' == pObj->optopt), "");
        TestForTrue((NULL == pObj->pOptArg), "");
        TestForTrue((pObj->optIndex == 2), "");
        TestForTrue((3 == longIndex), "");

        fRc = CmdUtl_IsMore(pObj);
        TestForTrue((fRc), "");

        iRc = CmdUtl_ParseLong(pObj, longDefns, &longIndex);
        TestForTrue(('f' == iRc), "");
        TestForTrue(('f' == pObj->optopt), "");
        TestForTrue((pObj->pOptArg), "");
        TestForTrue((0 == strcmp(pObj->pOptArg, "xyzzy")), "");
        TestForTrue((1 == longIndex), "");

        iRc = CmdUtl_ParseLong(pObj, longDefns, &longIndex);
        TestForTrue((-1 == iRc), "");
        TestForTrue((0 == pObj->optopt), "");
        TestForTrue((NULL == pObj->pOptArg), "");

        pArg = CmdUtl_NextArg(pObj);
        TestForTrue((0 == pObj->optopt), "");
        TestForTrue((pArg), "");
        TestForTrue((0 == strcmp(pArg, "abc")), "");

        fRc = CmdUtl_IsMore(pObj);
        TestForTrue((fRc), "");

        iRc = CmdUtl_ParseLong(pObj, longDefns, &longIndex);
        TestForTrue(('f' == iRc), "");
        //TestForTrue(('f' == pObj->optopt), "");
        TestForTrue((pObj->pOptArg), "");
        TestForTrue((0 == strcmp(pObj->pOptArg, "xyzzy2")), "");
        TestForTrue((1 == longIndex), "");

        pArg = CmdUtl_NextArg(pObj);
        TestForTrue((0 == pObj->optopt), "");
        TestForTrue((pArg), "");
        TestForTrue((0 == strcmp(pArg, "def")), "");

        fRc = CmdUtl_IsMore(pObj);
        TestForTrue((!fRc), "");

        pArg = CmdUtl_NextArg(pObj);
        TestForTrue((0 == pObj->optopt), "");
        TestForTrue((NULL == pArg), "");

        {
            ASTR_DATA       *pStr = CmdUtl_ToDebugString(pObj, 4);
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



ERESULT         Test_CmdUtl_Test04 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    CMDUTL_DATA     *pObj = OBJ_NIL;
    bool            fRc;
       CMDUTL_OPTION   longDefns1[4] = {
        {"debug",   'd', CMDUTL_ARG_OPTION_NONE},
        {"file",    'f', CMDUTL_ARG_OPTION_REQUIRED},
        {"verbose", 'v', CMDUTL_ARG_OPTION_NONE},
        {0, 0, 0}
    };
    CMDUTL_OPTION   longDefns2[4] = {
        {NULL,      'D', CMDUTL_ARG_OPTION_NONE},
        {"help",    'h', CMDUTL_ARG_OPTION_NONE},
        {NULL,      'V', CMDUTL_ARG_OPTION_NONE},
        {0, 0, 0}
    };
    char            *ppArgs[] = {
        "./test",
        "--verbose",
        "--file",
        "xyzzy",
        "abc",
        "-f",
        "xyzzy2",
        "def",
        NULL
    };
    int             iRc;
    char            *pArg;
    int             longIndex;

    fprintf(stderr, "Performing: %s\n", pTestName);
    fprintf(stderr, "\tTesting: CmdUtl_NewArgs() and CmdUtl_ParseLong()\n");

    pObj = CmdUtl_NewArgs(8, ppArgs);
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_CMDUTL);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   CMDUTL_MSGS
        CmdUtl_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        eRc = CmdUtl_SetupOptions(pObj, longDefns1, longDefns2);
        TestForSuccess("");

        iRc = CmdUtl_ParseLong(pObj, CmdUtl_getOptionDefinitions(pObj), &longIndex);
        TestForTrue(('v' == iRc), "");
        TestForTrue(('v' == pObj->optopt), "");
        TestForTrue((NULL == pObj->pOptArg), "");
        TestForTrue((pObj->optIndex == 2), "");
        TestForTrue((2 == longIndex), "");

        fRc = CmdUtl_IsMore(pObj);
        TestForTrue((fRc), "");

        iRc = CmdUtl_ParseLong(pObj, CmdUtl_getOptionDefinitions(pObj), &longIndex);
        TestForTrue(('f' == iRc), "");
        TestForTrue(('f' == pObj->optopt), "");
        TestForTrue((pObj->pOptArg), "");
        TestForTrue((0 == strcmp(pObj->pOptArg, "xyzzy")), "");
        TestForTrue((1 == longIndex), "");

        iRc = CmdUtl_ParseLong(pObj, CmdUtl_getOptionDefinitions(pObj), &longIndex);
        TestForTrue((-1 == iRc), "");
        TestForTrue((0 == pObj->optopt), "");
        TestForTrue((NULL == pObj->pOptArg), "");

        pArg = CmdUtl_NextArg(pObj);
        TestForTrue((0 == pObj->optopt), "");
        TestForTrue((pArg), "");
        TestForTrue((0 == strcmp(pArg, "abc")), "");

        fRc = CmdUtl_IsMore(pObj);
        TestForTrue((fRc), "");

        iRc = CmdUtl_ParseLong(pObj, CmdUtl_getOptionDefinitions(pObj), &longIndex);
        TestForTrue(('f' == iRc), "");
        //TestForTrue(('f' == pObj->optopt), "");
        TestForTrue((pObj->pOptArg), "");
        TestForTrue((0 == strcmp(pObj->pOptArg, "xyzzy2")), "");
        TestForTrue((1 == longIndex), "");

        pArg = CmdUtl_NextArg(pObj);
        TestForTrue((0 == pObj->optopt), "");
        TestForTrue((pArg), "");
        TestForTrue((0 == strcmp(pArg, "def")), "");

        fRc = CmdUtl_IsMore(pObj);
        TestForTrue((!fRc), "");

        pArg = CmdUtl_NextArg(pObj);
        TestForTrue((0 == pObj->optopt), "");
        TestForTrue((NULL == pArg), "");

        {
            ASTR_DATA       *pStr = CmdUtl_ToDebugString(pObj, 4);
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



ERESULT         Test_CmdUtl_Test05 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    CMDUTL_DATA     *pObj = OBJ_NIL;
    bool            fRc;
    typedef struct options_s {
        uint16_t        fDebug;
        uint16_t        fVerbose;
        PATH_DATA       *pFilePath;
    } OPTIONS;
    OPTIONS         options = {0};
    CMDUTL_OPTION   longDefns1[4] = {
        {"debug",   'd', CMDUTL_ARG_OPTION_NONE, CMDUTL_TYPE_BOOL,
            0, offsetof(OPTIONS, fDebug), NULL, NULL},
        {"file",    'f', CMDUTL_ARG_OPTION_REQUIRED, CMDUTL_TYPE_PATH,
            0, offsetof(OPTIONS, pFilePath), NULL, NULL},
        {"verbose", 'v', CMDUTL_ARG_OPTION_NONE, CMDUTL_TYPE_INCR,
            0, offsetof(OPTIONS, fVerbose), NULL, NULL},
        {0}
    };
    CMDUTL_OPTION   longDefns2[4] = {
        {NULL,      'D', CMDUTL_ARG_OPTION_NONE},
        {"help",    'h', CMDUTL_ARG_OPTION_NONE},
        {NULL,      'V', CMDUTL_ARG_OPTION_NONE},
        {0, 0, 0}
    };
    char            *ppArgs[] = {
        "./test",
        "-vv",
        "--file",
        "xyzzy",
        "abc",
        "-f",
        "xyzzy2",
        "def",
        NULL
    };
    //int             iRc;
    char            *pArg;
    //int             longIndex;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    fprintf(stderr, "\tTesting: CmdUtl_NewArgs() and CmdUtl_ProcessOptions()\n");

    pObj = CmdUtl_NewArgs(8, ppArgs);
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_CMDUTL);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   CMDUTL_MSGS
        CmdUtl_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        eRc = CmdUtl_SetupOptions(pObj, longDefns1, longDefns2);
        TestForSuccess("");
        pObj->pObj = &options;

        eRc = CmdUtl_ProcessOptions(pObj);
        TestForSuccess("");
        TestForTrue((0 == options.fDebug), "");
        TestForTrue((2 == options.fVerbose), "");
        TestForFalse((OBJ_NIL == options.pFilePath), "");
        TestForTrue((obj_IsKindOf(options.pFilePath, OBJ_IDENT_PATH)), "");
        TestForTrue((0 == strcmp(Path_getData(options.pFilePath), "xyzzy")), "");
        obj_Release(options.pFilePath);
        options.pFilePath = OBJ_NIL;

        fRc = CmdUtl_IsMore(pObj);
        TestForTrue((fRc), "");

        pArg = CmdUtl_NextArg(pObj);
        TestForTrue((0 == pObj->optopt), "");
        TestForTrue((pArg), "");
        TestForTrue((0 == strcmp(pArg, "abc")), "");

        fRc = CmdUtl_IsMore(pObj);
        TestForTrue((fRc), "");

        eRc = CmdUtl_ProcessOptions(pObj);
        TestForSuccess("");
        TestForTrue((0 == options.fDebug), "");
        TestForTrue((2 == options.fVerbose), "");
        TestForFalse((OBJ_NIL == options.pFilePath), "");
        TestForTrue((obj_IsKindOf(options.pFilePath, OBJ_IDENT_PATH)), "");
        TestForTrue((0 == strcmp(Path_getData(options.pFilePath), "xyzzy2")), "");
        obj_Release(options.pFilePath);
        options.pFilePath = OBJ_NIL;


        pArg = CmdUtl_NextArg(pObj);
        TestForTrue((0 == pObj->optopt), "");
        TestForTrue((pArg), "");
        TestForTrue((0 == strcmp(pArg, "def")), "");

        fRc = CmdUtl_IsMore(pObj);
        TestForTrue((!fRc), "");

        pArg = CmdUtl_NextArg(pObj);
        TestForTrue((0 == pObj->optopt), "");
        TestForTrue((NULL == pArg), "");

        {
            ASTR_DATA       *pStr = CmdUtl_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        pObj->pObj = NULL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_CmdUtl_Test06 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    CMDUTL_DATA     *pObj = OBJ_NIL;
    bool            fRc;
    typedef struct options_s {
        uint16_t        fDebug;
        uint16_t        fVerbose;
        ASTR_DATA       *pDefine;
        PATH_DATA       *pFilePath;
    } OPTIONS;
    OPTIONS         options = {0};
    CMDUTL_OPTION   longDefns1[5] = {
        {"debug",   0, CMDUTL_ARG_OPTION_NONE, CMDUTL_TYPE_BOOL,
            0, offsetof(OPTIONS, fDebug), NULL, NULL},
        {"define",    'f', CMDUTL_ARG_OPTION_REQUIRED, CMDUTL_TYPE_STRING,
            0, offsetof(OPTIONS, pDefine), NULL, NULL},
        {"file",    'f', CMDUTL_ARG_OPTION_REQUIRED, CMDUTL_TYPE_PATH,
            0, offsetof(OPTIONS, pFilePath), NULL, NULL},
        {"verbose", 'v', CMDUTL_ARG_OPTION_NONE, CMDUTL_TYPE_INCR,
            0, offsetof(OPTIONS, fVerbose), NULL, NULL},
        {0}
    };
    CMDUTL_OPTION   longDefns2[4] = {
        {NULL,      'D', CMDUTL_ARG_OPTION_NONE},
        {"help",    'h', CMDUTL_ARG_OPTION_NONE},
        {NULL,      'V', CMDUTL_ARG_OPTION_NONE},
        {0, 0, 0}
    };
    char            *ppArgs[] = {
        "./test",
        "--debug",
        "-vv",
        "--file",
        "xyzzy",
        "--define",
        "xxx=\"yy yy\"",
        "abc",
        "-f",
        "xyzzy2",
        "def",
        NULL
    };
    //int             iRc;
    char            *pArg;
    //int             longIndex;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    fprintf(stderr, "\tTesting: CmdUtl_NewArgs() and CmdUtl_ProcessOptions()\n");

    pObj = CmdUtl_NewArgs(8, ppArgs);
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_CMDUTL);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   CMDUTL_MSGS
        CmdUtl_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        eRc = CmdUtl_SetupOptions(pObj, longDefns1, longDefns2);
        TestForSuccess("");
        pObj->pObj = &options;

        eRc = CmdUtl_ProcessOptions(pObj);
        TestForSuccess("");
        TestForTrue((1 == options.fDebug), "");
        TestForTrue((2 == options.fVerbose), "");
        TestForFalse((OBJ_NIL == options.pFilePath), "");
        TestForTrue((obj_IsKindOf(options.pFilePath, OBJ_IDENT_PATH)), "");
        TestForTrue((0 == strcmp(Path_getData(options.pFilePath), "xyzzy")), "");
        obj_Release(options.pFilePath);
        options.pFilePath = OBJ_NIL;

        fRc = CmdUtl_IsMore(pObj);
        TestForTrue((fRc), "");

        pArg = CmdUtl_NextArg(pObj);
        TestForTrue((0 == pObj->optopt), "");
        TestForTrue((pArg), "");
        TestForTrue((0 == strcmp(pArg, "abc")), "");

        fRc = CmdUtl_IsMore(pObj);
        TestForTrue((fRc), "");

        eRc = CmdUtl_ProcessOptions(pObj);
        TestForSuccess("");
        TestForTrue((1 == options.fDebug), "");
        TestForTrue((2 == options.fVerbose), "");
        TestForFalse((OBJ_NIL == options.pDefine), "");
        TestForTrue((obj_IsKindOf(options.pDefine, OBJ_IDENT_ASTR)), "");
        TestForTrue((0 == strcmp(AStr_getData(options.pDefine), "xxx=\"yy yy\"")), "");
        obj_Release(options.pDefine);
        options.pDefine = OBJ_NIL;
        TestForFalse((OBJ_NIL == options.pFilePath), "");
        TestForTrue((obj_IsKindOf(options.pFilePath, OBJ_IDENT_PATH)), "");
        TestForTrue((0 == strcmp(Path_getData(options.pFilePath), "xyzzy2")), "");
        obj_Release(options.pFilePath);
        options.pFilePath = OBJ_NIL;

        pArg = CmdUtl_NextArg(pObj);
        TestForTrue((0 == pObj->optopt), "");
        TestForTrue((pArg), "");
        TestForTrue((0 == strcmp(pArg, "def")), "");

        fRc = CmdUtl_IsMore(pObj);
        TestForTrue((!fRc), "");

        pArg = CmdUtl_NextArg(pObj);
        TestForTrue((0 == pObj->optopt), "");
        TestForTrue((NULL == pArg), "");

        {
            ASTR_DATA       *pStr = CmdUtl_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        pObj->pObj = NULL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_CmdUtl_Test07 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    CMDUTL_DATA     *pObj = OBJ_NIL;
    bool            fRc;
    typedef struct options_s {
        uint16_t        fDebug;
        uint16_t        fVerbose;
        ASTRARRAY_DATA  *pDefines;
        PATH_DATA       *pFilePath;
    } OPTIONS;
    OPTIONS         options = {0};
    CMDUTL_OPTION   longDefns1[5] = {
        {"debug",   '\0', CMDUTL_ARG_OPTION_NONE, CMDUTL_TYPE_BOOL,
            0, offsetof(OPTIONS, fDebug), NULL, NULL},
        {"define",    'D', CMDUTL_ARG_OPTION_REQUIRED, CMDUTL_TYPE_STRING_ARRAY,
            0, offsetof(OPTIONS, pDefines), NULL, NULL},
        {"file",    'f', CMDUTL_ARG_OPTION_REQUIRED, CMDUTL_TYPE_PATH,
            0, offsetof(OPTIONS, pFilePath), NULL, NULL},
        {"verbose", 'v', CMDUTL_ARG_OPTION_NONE, CMDUTL_TYPE_INCR,
            0, offsetof(OPTIONS, fVerbose), NULL, NULL},
        {0}
    };
    CMDUTL_OPTION   longDefns2[4] = {
        {NULL,      'd', CMDUTL_ARG_OPTION_NONE},
        {"help",    'h', CMDUTL_ARG_OPTION_NONE},
        {NULL,      'V', CMDUTL_ARG_OPTION_NONE},
        {0, 0, 0}
    };
    char            *ppArgs[] = {
        "./test",
        "--debug",
        "-vv",
        "--file",
        "xyzzy",
        "--define",
        "xxx=\"yy yy\"",
        "-DXYZ=123",
        "abc",
        "-f",
        "xyzzy2",
        "def",
        NULL
    };
    //int             iRc;
    char            *pArg;
    ASTR_DATA       *pStr;
    ASTR_DATA       *pOther;
    //int             longIndex;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    fprintf(stderr, "\tTesting: CmdUtl_NewArgs() and CmdUtl_ProcessOptions()\n");

    pObj = CmdUtl_NewArgs(8, ppArgs);
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_CMDUTL);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   CMDUTL_MSGS
        CmdUtl_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        eRc = CmdUtl_SetupOptions(pObj, longDefns1, longDefns2);
        TestForSuccess("");
        pObj->pObj = &options;

        eRc = CmdUtl_ProcessOptions(pObj);
        TestForSuccess("");
        TestForTrue((1 == options.fDebug), "");
        TestForTrue((2 == options.fVerbose), "");
        TestForFalse((OBJ_NIL == options.pFilePath), "");
        TestForTrue((obj_IsKindOf(options.pFilePath, OBJ_IDENT_PATH)), "");
        TestForTrue((0 == strcmp(Path_getData(options.pFilePath), "xyzzy")), "");
        obj_Release(options.pFilePath);
        options.pFilePath = OBJ_NIL;

        fRc = CmdUtl_IsMore(pObj);
        TestForTrue((fRc), "");

        pArg = CmdUtl_NextArg(pObj);
        TestForTrue((0 == pObj->optopt), "");
        TestForTrue((pArg), "");
        TestForTrue((0 == strcmp(pArg, "abc")), "");

        fRc = CmdUtl_IsMore(pObj);
        TestForTrue((fRc), "");

        eRc = CmdUtl_ProcessOptions(pObj);
        TestForSuccess("");
        TestForTrue((1 == options.fDebug), "");
        TestForTrue((2 == options.fVerbose), "");
        TestForFalse((OBJ_NIL == options.pDefines), "");
        TestForTrue((obj_IsKindOf(options.pDefines, OBJ_IDENT_ASTRARRAY)), "");
        TestForTrue((2 == AStrArray_getSize(options.pDefines)), "");
        pStr = AStrArray_Get(options.pDefines, 1);
        pOther = AStr_getOther(pStr);
        TestForNotNull(pOther, "");
        TestForTrue((0 == strcmp(AStr_getData(pOther), "\"yy yy\"")), "");
        pStr = AStrArray_Get(options.pDefines, 2);
        pOther = AStr_getOther(pStr);
        TestForNotNull(pOther, "");
        TestForTrue((0 == strcmp(AStr_getData(pOther), "123")), "");
        obj_Release(options.pDefines);
        options.pDefines = OBJ_NIL;
        TestForFalse((OBJ_NIL == options.pFilePath), "");
        TestForTrue((obj_IsKindOf(options.pFilePath, OBJ_IDENT_PATH)), "");
        TestForTrue((0 == strcmp(Path_getData(options.pFilePath), "xyzzy2")), "");
        obj_Release(options.pFilePath);
        options.pFilePath = OBJ_NIL;


        pArg = CmdUtl_NextArg(pObj);
        TestForTrue((0 == pObj->optopt), "");
        TestForTrue((pArg), "");
        TestForTrue((0 == strcmp(pArg, "def")), "");

        fRc = CmdUtl_IsMore(pObj);
        TestForTrue((!fRc), "");

        pArg = CmdUtl_NextArg(pObj);
        TestForTrue((0 == pObj->optopt), "");
        TestForTrue((NULL == pArg), "");

        {
            ASTR_DATA       *pStr = CmdUtl_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        pObj->pObj = NULL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_CmdUtl_Test08 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    CMDUTL_DATA     *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    fprintf(stderr, "\tTesting: ??? CmdUtl_NewArgs() and CmdUtl_ProcessOptions()\n");

    pObj = CmdUtl_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_CMDUTL);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   CMDUTL_MSGS
        CmdUtl_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        {
            ASTR_DATA       *pStr = CmdUtl_ToDebugString(pObj, 4);
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



ERESULT         Test_CmdUtl_Test09 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    CMDUTL_DATA     *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = CmdUtl_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_CMDUTL);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   CMDUTL_MSGS
        CmdUtl_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        {
            ASTR_DATA       *pStr = CmdUtl_ToDebugString(pObj, 4);
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
    // Note: 
    //  Test_Setup() is called before the optional supplied setup
    //  in this table. Likewise, the optional teardown routine is
    //  called before Test_TearDown().
    //                                             Setup TearDown
    TestExec("OpenClose", Test_CmdUtl_OpenClose, NULL,   NULL);
    //TestExec("Copy01", Test_CmdUtl_Copy01,       NULL,   NULL);
    TestExec("Test01", Test_CmdUtl_Test01,       NULL,   NULL);
    TestExec("Test02", Test_CmdUtl_Test02,       NULL,   NULL);
    TestExec("Test03", Test_CmdUtl_Test03,       NULL,   NULL);
    TestExec("Test04", Test_CmdUtl_Test04,       NULL,   NULL);
    TestExec("Test05", Test_CmdUtl_Test05,       NULL,   NULL);
    TestExec("Test06", Test_CmdUtl_Test06,       NULL,   NULL);
    TestExec("Test07", Test_CmdUtl_Test07,       NULL,   NULL);
    TestExec("Test08", Test_CmdUtl_Test08,       NULL,   NULL);
    TestExec("Test09", Test_CmdUtl_Test09,       NULL,   NULL);

    obj_Release(pTest);
    pTest = OBJ_NIL;

    // Return to Operating System.
    return 0;
}



