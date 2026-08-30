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
#include    <PrepStrW32_internal.h>
#include    <JsonIn.h>
#include    <SrcErrors.h>
#include    <szBT.h>
#include    <szTbl.h>


static
SZBT_DATA       *pDict = OBJ_NIL;

static
ERESULT         DeleteExit(OBJ_ID x, void *pKey, void *pData)
{
    // Both, pKey is  string constant. pData is an AStr object.
    obj_Release(pData);
    return ERESULT_SUCCESS;
}


static
ERESULT         TearDown(TEST_DATA *pTest)
{
    obj_Release(pDict);
    pDict = OBJ_NIL;
    return ERESULT_SUCCESS;
}

static
ERESULT         DictAddA(
    OBJ_ID          x, 
    const 
    char            *pKey, 
    const 
    char            *pDataA
)
{
    ERESULT         eRc;
    ASTR_DATA       *pStr = OBJ_NIL;
    
    pStr = AStr_NewA(pDataA);
    if (pStr) {
        eRc = szBT_AddA(pDict, pKey, pStr);
    }
    return ERESULT_SUCCESS;
}

static
ASTR_DATA *     DictFindA(
    OBJ_ID          x, 
    const 
    char            *pKey
)
{
    ASTR_DATA       *pStr = OBJ_NIL;

    if (OBJ_NIL == pDict) {
        pDict = szBT_New();
        if (pDict) {
            szBT_setDeleteExit(pDict, DeleteExit, OBJ_NIL);
        }
    }
    
    if (pDict) {
        pStr = szBT_FindA(pDict, pKey);
    }
    return pStr;
}

static
ERESULT         Setup (
    TEST_DATA       *this
)
{
    ERESULT         eRc;

    obj_Release(pDict);
    //pDict = OBJ_NIL;
    
    pDict = szBT_New();
    if (pDict) {
        szBT_setDeleteExit(pDict, DeleteExit, OBJ_NIL);
    } else {
        return ERESULT_OUT_OF_MEMORY;
    }
    
    eRc = DictAddA(OBJ_NIL, "AL", "abc");
    if (ERESULT_FAILED(eRc)) {
        return eRc;
    }
    eRc = DictAddA(OBJ_NIL, "AU", "ABC");
    if (ERESULT_FAILED(eRc)) {
        return eRc;
    }
    eRc = DictAddA(OBJ_NIL, "BL", "${AL}ghi");
    if (ERESULT_FAILED(eRc)) {
        return eRc;
    }
    eRc = DictAddA(OBJ_NIL, "BU", "${AU}GHI");
    if (ERESULT_FAILED(eRc)) {
        return eRc;
    }
    eRc = DictAddA(OBJ_NIL, "DL", "def");
    if (ERESULT_FAILED(eRc)) {
        return eRc;
    }
    eRc = DictAddA(OBJ_NIL, "DU", "DEF");
    if (ERESULT_FAILED(eRc)) {
        return eRc;
    }
    eRc = DictAddA(OBJ_NIL, "NAMEL", "Xyzzy");
    if (ERESULT_FAILED(eRc)) {
        return eRc;
    }
    eRc = DictAddA(OBJ_NIL, "NAMEU", "XYZZY");
    //TODO: eRc = DictAddA(OBJ_NIL, "NAMEU", "${NAMEL}.upper()");
    if (ERESULT_FAILED(eRc)) {
        return eRc;
    }
    
    return ERESULT_SUCCESS;
}







ERESULT         Test_PrepStrW32_OpenClose (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    PREPSTRW32_DATA       
                    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = PrepStrW32_Alloc( );
    TestForNotNull(pObj, "Missing Test Alloc() object");
    pObj = PrepStrW32_Init( pObj );
    TestForNotNull(pObj, "Missing Test Init() object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_PREPSTRW32);
        TestForTrue(fRc, "Failed Ident Test");
#ifdef   PREPSTRW32_MSGS
        PrepStrW32_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
        
        // Test something.
        TestForSuccess("test failed");

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_PrepStrW32_Copy01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    PREPSTRW32_DATA       
                    *pObj1 = OBJ_NIL;
    PREPSTRW32_DATA       
                    *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(PREPSTRW32_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA       *pStr = OBJ_NIL;
#endif
    //int             iRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = PrepStrW32_New( );
    TestForNotNull(pObj1, "Missing Test object");
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_PREPSTRW32);
        TestForTrue(fRc, "Failed Ident Test");
#ifdef   PREPSTRW32_MSGS
        PrepStrW32_setMsg(pObj1, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
        
        // Test assign.
        pObj2 = PrepStrW32_New();
        TestForNotNull(pObj2, "Missing copied object");
        eRc = PrepStrW32_Assign(pObj1, pObj2);
        TestForFalse((ERESULT_FAILED(eRc)), "Assignment failed");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_PREPSTRW32);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = PrepStrW32_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = PrepStrW32_Copy(pObj1);
        TestForNotNull(pObj2, "Missing copied object");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_PREPSTRW32);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = PrepStrW32_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(PREPSTRW32_JSON_SUPPORT) && defined(XYZZY)
        pStr = PrepStrW32_ToJson(pObj1);
        TestForNotNull(pStr, "Missing JSON output");
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = PrepStrW32_NewFromJsonString(pStr);
        TestForNotNull(pObj2, "Missing JSON created object");
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_PREPSTRW32);
        TestForTrue(fRc, "Failed Ident Test");
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //iRc = PrepStrW32_Compare(pObj1, pObj2);
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



ERESULT         Test_PrepStrW32_Test01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    PREPSTRW32_DATA *pObj = OBJ_NIL;
    SCANNER_DATA    *pScan = OBJ_NIL;
    //ASTR_DATA       *pStr  = OBJ_NIL;
    bool            fRc;
    const
    char            *pStr1A = "abc";
    const
    char            *pStr2A = "NAMEL";
    const
    char            *pStr3A = "abc || NAMEL";
    const
    char            *pStr4A = "NAMEL && abc";
    const
    char            *pStr5A = "NAMEL && !abc";

    fprintf(stderr, "Performing: %s\n", pTestName);
    TestForNotNull(pDict, "");

    //Note: Dictionary is set up with default entries.
    //      See Setup() above.

    pObj = PrepStrW32_New( );
    
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_PREPSTRW32);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("test failed");
#ifdef   PREPSTRW32_MSGS
        PrepStrW32_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
        PrepStrW32_setFindValue(pObj, DictFindA, OBJ_NIL);
                
        pScan = Scanner_NewA(pStr1A);
        TestForNotNull(pScan, "");
        if (pScan) {
            obj_TraceSet(pScan, true);
            fRc = PrepStrW32_PreProcBoolEvalScan(pObj, pScan);
            TestForFalse(fRc, "");
            obj_Release(pScan);
            pScan = OBJ_NIL;
        }

        pScan = Scanner_NewA(pStr2A);
        TestForNotNull(pScan, "");
        if (pScan) {
            obj_TraceSet(pScan, true);
            fRc = PrepStrW32_PreProcBoolEvalScan(pObj, pScan);
            TestForTrue(fRc, "");
            obj_Release(pScan);
            pScan = OBJ_NIL;
        }

        pScan = Scanner_NewA(pStr3A);
        TestForNotNull(pScan, "");
        if (pScan) {
            obj_TraceSet(pScan, true);
            fRc = PrepStrW32_PreProcBoolEvalScan(pObj, pScan);
            TestForTrue(fRc, "");
            obj_Release(pScan);
            pScan = OBJ_NIL;
        }

        pScan = Scanner_NewA(pStr4A);
        TestForNotNull(pScan, "");
        if (pScan) {
            obj_TraceSet(pScan, true);
            fRc = PrepStrW32_PreProcBoolEvalScan(pObj, pScan);
            TestForFalse(fRc, "");
            obj_Release(pScan);
            pScan = OBJ_NIL;
        }

        pScan = Scanner_NewA(pStr5A);
        TestForNotNull(pScan, "");
        if (pScan) {
            obj_TraceSet(pScan, true);
            fRc = PrepStrW32_PreProcBoolEvalScan(pObj, pScan);
            TestForTrue(fRc, "");
            obj_Release(pScan);
            pScan = OBJ_NIL;
        }

        {
            ASTR_DATA       *pStr = PrepStrW32_ToDebugString(pObj, 4);
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



ERESULT         Test_PrepStrW32_Test02 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    int             iRc;
    PREPSTRW32_DATA *pObj = OBJ_NIL;
    TEXTIN_DATA     *pInput = OBJ_NIL;
    bool            fRc;
    const
    char            *pTestA =
    "%ifdef NAMEL\n"
    "\ttest true line\n"
    "%else\n"
    "\ttest false line\n"
    "%endif\n"
    "xyzzy\n";
    const
    char            *pAns = "    test true line\nxyzzy\n";
    TEXTOUT_DATA    *pOutput = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    uint32_t        count = 0;

    fprintf(stderr, "Performing: %s\n", pTestName);
    TestForNotNull(pDict, "");
    pStr = DictFindA(OBJ_NIL, "NAMEL");
    TestForNotNull(pStr, "");
    TestForZero(AStr_CompareA(pStr, "Xyzzy"), "");
    pStr = OBJ_NIL;

    //Note: Dictionary is set up with default entries.
    //      See Setup() above.

    pObj = PrepStrW32_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_PREPSTRW32);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("test failed");
#ifdef   PREPSTRW32_MSGS
        PrepStrW32_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
        PrepStrW32_setFindValue(pObj, DictFindA, OBJ_NIL);
        //PrepStrW32_setPrepChar(pObj,'%');
        pInput = TextIn_NewFromStrA(OBJ_NIL, pTestA, 1, 4);
        TestForNotNull(pInput, "");

        pOutput = TextOut_NewAStr(OBJ_NIL);
        TestForNotNull(pOutput, "");
        eRc = PrepStrW32_PreprocInput(pObj, pInput, pOutput, &count);
        TestForSuccess("test failed");
        pStr = TextOut_getStr(pOutput);
        TestForNotNull(pStr, "");
        fprintf(stderr, "\tOutput : \"%s\"\n", AStr_getData(pStr));
        fprintf(stderr, "\tCorrect: \"%s\"\n", pAns);
        iRc = AStr_CompareA(pStr, pAns);
        fprintf(stderr, "iRc: %d\n", iRc);
        TestForTrue((0 == iRc), "");
        fprintf(stderr, "count: %d\n", count);
        obj_Release(pOutput);
        pOutput = OBJ_NIL;
        
        obj_Release(pInput);
        pInput = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_PrepStrW32_Test03 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    int             iRc;
    PREPSTRW32_DATA *pObj = OBJ_NIL;
    TEXTIN_DATA     *pInput = OBJ_NIL;
    bool            fRc;
    const
    char            *pTestA =
    "%ifdef NAMELL\n"               // NAMELL does not exist!
    "\ttest true line\n"
    "%else\n"
    "\ttest false line\n"
    "%endif\n"
    "xyzzy\n";
    const
    char            *pAns = "    test false line\nxyzzy\n";
    TEXTOUT_DATA    *pOutput = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    uint32_t        count = 0;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    TestForNotNull(pDict, "");
    pStr = DictFindA(OBJ_NIL, "NAMEL");
    TestForNotNull(pStr, "");
    TestForZero(AStr_CompareA(pStr, "Xyzzy"), "");
    pStr = OBJ_NIL;

    //Note: Dictionary is set up with default entries.
    //      See Setup() above.

    pObj = PrepStrW32_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_PREPSTRW32);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("test failed");
#ifdef   PREPSTRW32_MSGS
        PrepStrW32_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
        PrepStrW32_setFindValue(pObj, DictFindA, OBJ_NIL);
        //PrepStrW32_setPrepChar(pObj,'%');
        
        pInput = TextIn_NewFromStrA(OBJ_NIL, pTestA, 1, 4);
        TestForNotNull(pInput, "");
        pOutput = TextOut_NewAStr(OBJ_NIL);
        TestForNotNull(pOutput, "");
                
        eRc = PrepStrW32_PreprocInput(pObj, pInput, pOutput, &count);
        TestForSuccess("test failed");
        pStr = TextOut_getStr(pOutput);
        TestForNotNull(pStr, "");
        fprintf(stderr, "\tOutput___: \"%s\"\n", AStr_getData(pStr));
        fprintf(stderr, "\tShould be: \"%s\"\n", pAns);
        iRc = AStr_CompareA(pStr, pAns);
        fprintf(stderr, "iRc: %d\n", iRc);
        TestForTrue((0 == iRc), "");
        fprintf(stderr, "count: %d\n", count);
        
        obj_Release(pOutput);
        pOutput = OBJ_NIL;
        obj_Release(pInput);
        pInput = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_PrepStrW32_Test04 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    PREPSTRW32_DATA *pObj = OBJ_NIL;
    SCANNER_DATA    *pScan = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    bool            fRc;
    int             iRc;
    const
    char            *pHomeA = NULL;
    int             len = 0;
    const
    char            *pTestA = "%{HOME}";
    TEXTOUT_DATA    *pOut = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);
    fprintf(stderr, "\t Test PrepStrW32_ExpandVars()\n");
    TestForNotNull(pDict, "");
    pStr = DictFindA(OBJ_NIL, "NAMEL");
    TestForNotNull(pStr, "");
    TestForZero(AStr_CompareA(pStr, "Xyzzy"), "");
    pStr = OBJ_NIL;

    //Note: Dictionary is set up with default entries.
    //      See Setup() above.

    pHomeA = getenv("HOME");
    TestForNotNull((void *)pHomeA, "");
    if (pHomeA) {
        len = (int)strlen(pHomeA);
    }
    pScan = Scanner_NewA(pTestA);
    TestForNotNull(pScan, "");
    
    pObj = PrepStrW32_New();
    TestForNotNull(pObj, "");
    if (pObj) {

        obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_PREPSTRW32);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("test failed");
#ifdef   PREPSTRW32_MSGS
        PrepStrW32_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif

        pOut = TextOut_NewAStr(OBJ_NIL);
        eRc = PrepStrW32_ExpandVars(pObj, pScan, pOut);
        TestForSuccess("test failed");
        pStr = TextOut_getStr(pOut);
        TestForNotNull(pStr, "");
        fprintf(stderr, "\tfound:     \"%s\"\n", AStr_getData(pStr));
        fprintf(stderr, "\tshould be: \"%s\"\n", pHomeA);
        iRc = AStr_CompareA(pStr, pHomeA);
        TestForTrue((0 == iRc), "");
        //obj_Release(pStr);
        pStr = OBJ_NIL;
        obj_Release(pOut);
        pOut = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    obj_Release(pScan);
    pScan = OBJ_NIL;
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_PrepStrW32_Test05 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    PREPSTRW32_DATA *pObj = OBJ_NIL;
    bool            fRc;
    int             iRc;
    SCANNER_DATA    *pInput = OBJ_NIL;
    const
    char            *pTest1A = "\ttest %{NAMEL} line\n";    // $NAMEL = "Xyzzy"
    const
    char            *pAns1A =  "    test Xyzzy line\n";
    const
    char            *pTest2A = "%{col(5);NAMEU}\n";
    const
    char            *pAns2A = "    XYZZY\n";
    const
    char            *pTest3A = "%{spc(4);NAMEU}\n";
    const
    char            *pAns3A = "    XYZZY\n";
    char            *pTest4A = "\ttest %{NAMEL} line\n%{NAMEU}\n";
    const
    char            *pAns4A = "    test Xyzzy line\nXYZZY\n";
    TEXTOUT_DATA    *pOutput = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    uint32_t        count = 0;

    fprintf(stderr, "Performing: %s\n", pTestName);
    fprintf(stderr, "\t Test PrepStrW32_ExpandVars()\n");
    TestForNotNull(pDict, "");
    pStr = DictFindA(OBJ_NIL, "NAMEL");
    TestForNotNull(pStr, "");
    TestForZero(AStr_CompareA(pStr, "Xyzzy"), "");
    pStr = OBJ_NIL;

    //Note: Dictionary is set up with default entries.
    //      See Setup() above.

    pObj = PrepStrW32_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_PREPSTRW32);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("test failed");
#ifdef   PREPSTRW32_MSGS
        PrepStrW32_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
        PrepStrW32_setFindValue(pObj, DictFindA, OBJ_NIL);
        
        pInput = Scanner_NewA(pTest1A);
        TestForNotNull(pInput, "");
        Scanner_setWS(pInput, false);
        pOutput = TextOut_NewAStr(OBJ_NIL);
        TestForNotNull(pOutput, "");
        eRc = PrepStrW32_ExpandVars(pObj, pInput, pOutput);
        TestForNotNull(pOutput, "");
        pStr = TextOut_getStr(pOutput);
        TestForNotNull(pStr, "");
        fprintf(stderr, "\tOutput1: \"%s\"\n", AStr_getData(pStr));
        fprintf(stderr, "\tCorrect: \"%s\"\n", pAns1A);
        TestForSuccess("test failed");
        iRc = AStr_CompareA(pStr, pAns1A);
        fprintf(stderr, "Answer iRc: %d\n", iRc);
        TestForTrue((0 == iRc), "");
        obj_Release(pOutput);
        pOutput = OBJ_NIL;
        obj_Release(pInput);
        pInput = OBJ_NIL;

        pInput = Scanner_NewA(pTest2A);
        TestForNotNull(pInput, "");
        Scanner_setWS(pInput, false);
        pOutput = TextOut_NewAStr(OBJ_NIL);
        TestForNotNull(pOutput, "");
        eRc = PrepStrW32_ExpandVars(pObj, pInput, pOutput);
        TestForSuccess("test failed");
        pStr = TextOut_getStr(pOutput);
        TestForNotNull(pStr, "");
        fprintf(stderr, "\tOutput2: \"%s\"\n", AStr_getData(pStr));
        fprintf(stderr, "\tCorrect: \"%s\"\n", pAns2A);
        iRc = AStr_CompareA(pStr, pAns2A);
        fprintf(stderr, "Answer iRc: %d\n", iRc);
        TestForTrue((0 == iRc), "");
        obj_Release(pOutput);
        pOutput = OBJ_NIL;
        obj_Release(pInput);
        pInput = OBJ_NIL;

        pInput = Scanner_NewA(pTest3A);
        TestForNotNull(pInput, "");
        Scanner_setWS(pInput, false);
        pOutput = TextOut_NewAStr(OBJ_NIL);
        TestForNotNull(pOutput, "");
        eRc = PrepStrW32_ExpandVars(pObj, pInput, pOutput);
        TestForSuccess("test failed");
        pStr = TextOut_getStr(pOutput);
        TestForNotNull(pStr, "");
        fprintf(stderr, "\tOutput3: \"%s\"\n", AStr_getData(pStr));
        fprintf(stderr, "\tCorrect: \"%s\"\n", pAns3A);
        iRc = AStr_CompareA(pStr, pAns3A);
        fprintf(stderr, "Answer iRc: %d\n", iRc);
        TestForTrue((0 == iRc), "");
        obj_Release(pOutput);
        pOutput = OBJ_NIL;
        obj_Release(pInput);
        pInput = OBJ_NIL;

        pInput = Scanner_NewA(pTest4A);
        TestForNotNull(pInput, "");
        Scanner_setWS(pInput, false);
        pOutput = TextOut_NewAStr(OBJ_NIL);
        TestForNotNull(pOutput, "");
        eRc = PrepStrW32_ExpandVars(pObj, pInput, pOutput);
        TestForSuccess("test failed");
        pStr = TextOut_getStr(pOutput);
        TestForNotNull(pStr, "");
        fprintf(stderr, "\tOutput4: \"%s\"\n", AStr_getData(pStr));
        fprintf(stderr, "\tCorrect: \"%s\"\n", pAns4A);
        iRc = AStr_CompareA(pStr, pAns4A);
        fprintf(stderr, "Answer iRc: %d\n", iRc);
        TestForTrue((0 == iRc), "");
        obj_Release(pOutput);
        pOutput = OBJ_NIL;
        obj_Release(pInput);
        pInput = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_PrepStrW32_Test06 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    PREPSTRW32_DATA *pObj = OBJ_NIL;
    bool            fRc;
    int             iRc;
    TEXTIN_DATA     *pInput = OBJ_NIL;
    const
    char            *pTest1A =
    "%ifdef NAMELL\n"           // This will fail, NAMELL is undefined
    "\ttest true line\n"
    "%else\n"
    "\ttest %{NAMEL} line\n"
    "%endif\n"
    "%{NAMEU}\n";
    const
    char            *pAns1A = "    test Xyzzy line\nXYZZY\n";
    const
    char            *pTest2A =
    "\tTRC_OBJ(this, \\\"%s:\\n\\\", __func__);\n"
    "%{NAMEU}\n";
    const
    char            *pAns2A = "    TRC_OBJ(this, \\\"%s:\\n\\\", __func__);\nXYZZY\n";
    TEXTOUT_DATA    *pOutput = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    uint32_t        count = 0;

    fprintf(stderr, "Performing: %s\n", pTestName);
    fprintf(stderr, "\t Test PrepStrW32_PreprocInput()\n");
    TestForNotNull(pDict, "");
    pStr = DictFindA(OBJ_NIL, "NAMEL");
    TestForNotNull(pStr, "");
    TestForZero(AStr_CompareA(pStr, "Xyzzy"), "");
    pStr = OBJ_NIL;

    //Note: Dictionary is set up with default entries.
    //      See Setup() above.

    pObj = PrepStrW32_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_PREPSTRW32);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("test failed");
#ifdef   PREPSTRW32_MSGS
        PrepStrW32_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
        PrepStrW32_setFindValue(pObj, DictFindA, OBJ_NIL);
        //PrepStrW32_setPrepChar(pObj,'%');

        // Perform 1st test
        fprintf(stderr, "%s::Test1:\n", pTestName);
        pInput = TextIn_NewFromStrA(OBJ_NIL, pTest1A, 1, 4);
        TestForNotNull(pInput, "");
        pOutput = TextOut_NewAStr(OBJ_NIL);
        TestForNotNull(pOutput, "");
        eRc = PrepStrW32_PreprocInput(pObj, pInput, pOutput, &count);
        pStr = TextOut_getStr(pOutput);
        TestForNotNull(pStr, "");
        fprintf(stderr, "\tOutput : \"%s\"\n", AStr_getData(pStr));
        fprintf(stderr, "\tCorrect: \"%s\"\n", pAns1A);
        TestForSuccess("test failed");
        iRc = AStr_CompareA(pStr, pAns1A);
        fprintf(stderr, "iRc: %d\n", iRc);
        TestForTrue((0 == iRc), "");
        fprintf(stderr, "count: %d\n", count);
        obj_Release(pOutput);
        pOutput = OBJ_NIL;
        obj_Release(pInput);
        pInput = OBJ_NIL;

        // Perform 2nd test
        pInput = TextIn_NewFromStrA(OBJ_NIL, pTest2A, 1, 4);
        TestForNotNull(pInput, "");
        pOutput = TextOut_NewAStr(OBJ_NIL);
        TestForNotNull(pOutput, "");
        eRc = PrepStrW32_PreprocInput(pObj, pInput, pOutput, &count);
        TestForSuccess("test failed");
        pStr = TextOut_getStr(pOutput);
        TestForNotNull(pStr, "");
        fprintf(stderr, "\tOutput : \"%s\"\n", AStr_getData(pStr));
        fprintf(stderr, "\tCorrect: \"%s\"\n", pAns2A);
        iRc = AStr_CompareA(pStr, pAns2A);
        fprintf(stderr, "iRc: %d\n", iRc);
        TestForTrue((0 == iRc), "");
        fprintf(stderr, "count: %d\n", count);
        obj_Release(pOutput);
        pOutput = OBJ_NIL;
        obj_Release(pInput);
        pInput = OBJ_NIL;

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
    TestExec("OpenClose", Test_PrepStrW32_OpenClose, NULL, NULL);
    //TestExec("Copy01", Test_PrepStrW32_Copy01, NULL, NULL);
    TestExec("Test01", Test_PrepStrW32_Test01, Setup, TearDown);
    TestExec("Test02", Test_PrepStrW32_Test02, Setup, TearDown);
    TestExec("Test03", Test_PrepStrW32_Test03, Setup, TearDown);
    TestExec("Test04", Test_PrepStrW32_Test04, Setup, TearDown);
    TestExec("Test05", Test_PrepStrW32_Test05, Setup, TearDown);
    TestExec("Test06", Test_PrepStrW32_Test06, Setup, TearDown);

    obj_Release(pTest);
    pTest = OBJ_NIL;

    // Return to Operating System.
    return 0;
}



