// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          16-bit Variable Sized Tuples (Tuple16)  Test Program
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
#include    <Tuple16_internal.h>
#include    <JsonIn.h>
#include    <SrcErrors.h>
#include    <szTbl.h>






//----------------------------------------------------------------
//                      Test Open/Close
//----------------------------------------------------------------

ERESULT         Test_Tuple16_OpenClose (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    TUPLE16_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Tuple16_Alloc( );
    TestForNotNull(pObj, "Missing Test Alloc() object");
    pObj = Tuple16_Init( pObj );
    TestForNotNull(pObj, "Missing Test Init() object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_TUPLE16);
        TestForTrue(fRc, "Failed Ident Test");
#ifdef   TUPLE16_MSGS
        Tuple16_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
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

ERESULT         Test_Tuple16_Copy01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    TUPLE16_DATA       *pObj1 = OBJ_NIL;
    TUPLE16_DATA       *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(TUPLE16_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA       *pStr = OBJ_NIL;
#endif
    //int             iRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = Tuple16_New( );
    TestForNotNull(pObj1, "Missing Test object");
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_TUPLE16);
        TestForTrue(fRc, "Failed Ident Test");
#ifdef   TUPLE16_MSGS
        Tuple16_setMsg(pObj1, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
        
        // Test assign.
        pObj2 = Tuple16_New();
        TestForNotNull(pObj2, "Missing copied object");
        eRc = Tuple16_Assign(pObj1, pObj2);
        TestForFalse((ERESULT_FAILED(eRc)), "Assignment failed");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_TUPLE16);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = Tuple16_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = Tuple16_Copy(pObj1);
        TestForNotNull(pObj2, "Missing copied object");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_TUPLE16);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = Tuple16_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(TUPLE16_JSON_SUPPORT) && defined(XYZZY)
        pStr = Tuple16_ToJson(pObj1);
        TestForNotNull(pStr, "Missing JSON output");
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = Tuple16_NewFromJsonString(pStr);
        TestForNotNull(pObj2, "Missing JSON created object");
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_TUPLE16);
        TestForTrue(fRc, "Failed Ident Test");
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //iRc = Tuple16_Compare(pObj1, pObj2);
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

ERESULT         Test_Tuple16_Test01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    TUPLE16_DATA    *pObj = OBJ_NIL;
    bool            fRc;
    TUPLE16_SEGMENT_BASE
                    *pBase = NULL;
    TUPLE16_INTEGER16
                    *pSeg = NULL;
    TUPLE16_INTEGER16
                    *pSeg2 = NULL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Tuple16_NewBase(23);
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_TUPLE16);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef  TUPLE16_MSGS
        Tuple16_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
         
        pBase = Tuple16_getTuple(pObj);
        TestForNotNull(pBase, "");
        TestForTrue((pBase->op == 23), "");
        fprintf(stderr, "Base len: %d\n", pBase->segLen);
        TestForTrue((pBase->alloc == 8), "");
        TestForTrue((pBase->segLen == 8), "");
        
        {
            ASTR_DATA       *pStr = Tuple16_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        eRc = Tuple16_AppendInteger16(pObj, 'S', 2);
        TestForSuccess("");

        pBase = Tuple16_getTuple(pObj);
        TestForNotNull(pBase, "");
        TestForTrue((pBase->op == 23), "");
        fprintf(stderr, "Base len: %d\n", pBase->segLen);
        TestForTrue((pBase->alloc == 14), "");
        TestForTrue((pBase->segLen == 14), "");
        TestForTrue((pBase->cTuples == 1), "");
        
        pSeg2 = (TUPLE16_INTEGER16 *)offsetPtr(Tuple16_getTuple(pObj),
                                               Tuple16_SegmentOffset(pObj, 0));
        TestForTrue(((TUPLE16_INTEGER16 *)(pBase+1) == pSeg2), "");
        TestForTrue((pSeg2->segLen == sizeof(TUPLE16_INTEGER16)), "");
        TestForTrue((pSeg2->op == 'S'), "");
        TestForTrue((pSeg2->data == 2), "");

        pSeg2 = (TUPLE16_INTEGER16 *)Tuple16_Segment(pObj, 1);
        TestForNotNull(pSeg2, "");
        TestForTrue((pSeg2->segLen == 6), "");
        TestForTrue((pSeg2->op == 'S'), "");
        TestForTrue((pSeg2->data == 2), "");

        {
            ASTR_DATA       *pStr = Tuple16_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        eRc = Tuple16_InsertInteger16(pObj, 0, 'R', 1);
        TestForSuccess("");
        
        pBase = Tuple16_getTuple(pObj);
        TestForNotNull(pBase, "");
        TestForTrue((pBase->op == 23), "");
        fprintf(stderr, "Base len: %d\n", pBase->segLen);
        TestForTrue((pBase->alloc == 20), "");
        TestForTrue((pBase->segLen == 20), "");
        TestForTrue((pBase->cTuples == 2), "");
        
        pSeg2 = (TUPLE16_INTEGER16 *)Tuple16_Segment(pObj, 1);
        TestForNotNull(pSeg2, "");
        TestForTrue((pSeg2->segLen == 6), "");
        TestForTrue((pSeg2->op == 'R'), "");
        TestForTrue((pSeg2->data == 1), "");

        pSeg2 = (TUPLE16_INTEGER16 *)Tuple16_Segment(pObj, 2);
        TestForNotNull(pSeg2, "");
        TestForTrue((pSeg2->segLen == 6), "");
        TestForTrue((pSeg2->op == 'S'), "");
        TestForTrue((pSeg2->data == 2), "");

        eRc = Tuple16_InsertInteger16(pObj, 2, 'T', 3);
        TestForSuccess("");
        pBase = Tuple16_getTuple(pObj);
        TestForNotNull(pBase, "");
        TestForTrue((pBase->op == 23), "");
        fprintf(stderr, "Base len: %d\n", pBase->segLen);
        TestForTrue((pBase->alloc == 26), "");
        TestForTrue((pBase->segLen == 26), "");
        TestForTrue((pBase->cTuples == 3), "");
        
        {
            ASTR_DATA       *pStr = Tuple16_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        
        pSeg2 = (TUPLE16_INTEGER16 *)Tuple16_Segment(pObj, 1);
        TestForNotNull(pSeg2, "");
        TestForTrue((pSeg2->segLen == 6), "");
        TestForTrue((pSeg2->op == 'R'), "");
        TestForTrue((pSeg2->data == 1), "");

        pSeg2 = (TUPLE16_INTEGER16 *)Tuple16_Segment(pObj, 2);
        TestForNotNull(pSeg2, "");
        TestForTrue((pSeg2->segLen == 6), "");
        TestForTrue((pSeg2->op == 'S'), "");
        TestForTrue((pSeg2->data == 2), "");

        pSeg2 = (TUPLE16_INTEGER16 *)Tuple16_Segment(pObj, 3);
        TestForNotNull(pSeg2, "");
        TestForTrue((pSeg2->segLen == 6), "");
        TestForTrue((pSeg2->op == 'T'), "");
        TestForTrue((pSeg2->data == 3), "");

        eRc = Tuple16_DeleteSegment(pObj, 2);
        TestForSuccess("");
        
        pBase = Tuple16_getTuple(pObj);
        TestForNotNull(pBase, "");
        TestForTrue((pBase->op == 23), "");
        fprintf(stderr, "Base len: %d\n", pBase->segLen);
        TestForTrue((pBase->alloc == 26), "");
        TestForTrue((pBase->segLen == 20), "");
        TestForTrue((pBase->cTuples == 2), "");

        {
            ASTR_DATA       *pStr = Tuple16_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        
        if (pSeg) {
            mem_Free(pSeg);
            pSeg = NULL;
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

ERESULT         Test_Tuple16_Test02 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    TUPLE16_DATA    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Tuple16_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_TUPLE16);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   TUPLE16_MSGS
        Tuple16_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        {
            ASTR_DATA       *pStr = Tuple16_ToDebugString(pObj, 4);
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

ERESULT         Test_Tuple16_Test03 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    TUPLE16_DATA    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Tuple16_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_TUPLE16);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   TUPLE16_MSGS
        Tuple16_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        {
            ASTR_DATA       *pStr = Tuple16_ToDebugString(pObj, 4);
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

ERESULT         Test_Tuple16_Test04 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    TUPLE16_DATA    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n\n", pTestName);

    pObj = Tuple16_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_TUPLE16);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   TUPLE16_MSGS
        Tuple16_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        {
            ASTR_DATA       *pStr = Tuple16_ToDebugString(pObj, 4);
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
    TestExec("OpenClose", Test_Tuple16_OpenClose, NULL,   NULL);
    //TestExec("Copy01", Test_Tuple16_Copy01,       NULL,   NULL);
    TestExec("Test01", Test_Tuple16_Test01,       NULL,   NULL);
    TestExec("Test02", Test_Tuple16_Test02,       NULL,   NULL);
    TestExec("Test03", Test_Tuple16_Test03,       NULL,   NULL);
    TestExec("Test04", Test_Tuple16_Test04,       NULL,   NULL);

    obj_Release(pTest);
    pTest = OBJ_NIL;

    // Return to Operating System.
    return 0;
}



