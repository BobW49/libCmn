// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//    Line Index into File or Buffer (LineIndex)  Test Program
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
#include    <LineIndex_internal.h>
#include    <JsonIn.h>
#include    <SrcErrors.h>
#include    <szTbl.h>


#define     TEST_ASSIGN_COPY    1


#ifdef  __cplusplus
extern "C" {
#endif
        



    //----------------------------------------------------------------
    //                      Test Open/Close
    //----------------------------------------------------------------

    ERESULT         Test_LineIndex_OpenClose (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        LINEINDEX_DATA  *pObj = OBJ_NIL;
       
        fprintf(stderr, "Performing: %s\n", pTestName);

        pObj = LineIndex_Alloc( );
        TestForNotNull(pObj, "Missing Test Alloc() object");
        pObj = LineIndex_Init( pObj );
        TestForNotNull(pObj, "Missing Test Init() object");
        if (pObj) {

            //obj_TraceSet(pObj, true);       
            fRc = obj_IsKindOf(pObj, OBJ_IDENT_LINEINDEX);
            TestForTrue(fRc, "Failed Ident Test");
    #ifdef   LINEINDEX_MSGS
            LineIndex_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
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

#ifdef  TEST_ASSIGN_COPY
    ERESULT         Test_LineIndex_Copy01 (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        //int             iRc;
        LINEINDEX_DATA  *pObj1 = OBJ_NIL;
        LINEINDEX_DATA  *pObj2 = OBJ_NIL;
    #if defined(LINEINDEX_JSON_SUPPORT)
        ASTR_DATA       *pStr = OBJ_NIL;
    #endif
        SRCLOC          loc = {0};
        SRCLOC          *pFnd;
        const
        int             max = 4;
        int             i;
        int             iMax;
       
        fprintf(stderr, "Performing: %s\n", pTestName);

        pObj1 = LineIndex_NewWithMax(max);
        TestForNotNull(pObj1, "Missing Test object");
        if (pObj1) {

            //obj_TraceSet(pObj1, true);       
            fRc = obj_IsKindOf(pObj1, OBJ_IDENT_LINEINDEX);
            TestForTrue(fRc, "Failed Ident Test");
    #ifdef   LINEINDEX_MSGS
            LineIndex_setMsg(pObj1, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
    #endif
            iMax = 7;
            for (i=0; i<iMax; ++i) {
                loc.lineNo = i;
                loc.offset = i << 1;
                eRc = LineIndex_Add(pObj1, &loc);
                TestForSuccess("");
                {
                    ASTR_DATA       *pStr = LineIndex_ToDebugString(pObj1, 4);
                    if (pStr) {
                        fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                        obj_Release(pStr);
                        pStr = OBJ_NIL;
                    }
                }
                pFnd = LineIndex_FindLine(pObj1, i);
                TestForNotNull(pFnd, "");
            }
            TestForTrue((4 == LineIndex_getSize(pObj1)), "");
            TestForTrue((4 == LineIndex_getMax(pObj1)), "");
            TestForTrue((2 == LineIndex_getInterval(pObj1)), "");
            
            // Test assign.
            pObj2 = LineIndex_New();
            TestForNotNull(pObj2, "Missing copied object");
            eRc = LineIndex_Assign(pObj1, pObj2);
            TestForFalse((ERESULT_FAILED(eRc)), "Assignment failed");

            fRc = obj_IsKindOf(pObj2, OBJ_IDENT_LINEINDEX);
            TestForTrue(fRc, "Failed Ident Test");
            //iRc = LineIndex_Compare(pObj1, pObj2);
            //TestForTrue((0 == iRc), "Failed Compare");
            //TODO: Add More tests here!
            {
                ASTR_DATA       *pStr = LineIndex_ToDebugString(pObj1, 4);
                if (pStr) {
                    fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                }
            }
            pFnd = LineIndex_FindLine(pObj2, 3);
            TestForNotNull(pFnd, "");
            TestForTrue((2 == pFnd->lineNo), "");
            TestForTrue((4 == pFnd->offset), "");
            pFnd = LineIndex_FindLine(pObj2, 7);
            TestForNotNull(pFnd, "");
            TestForTrue((6 == pFnd->lineNo), "");
            TestForTrue((12 == pFnd->offset), "");

            obj_Release(pObj2);
            pObj2 = OBJ_NIL;

            // Test copy.
            pObj2 = LineIndex_Copy(pObj1);
            TestForNotNull(pObj2, "Missing copied object");

            fRc = obj_IsKindOf(pObj2, OBJ_IDENT_LINEINDEX);
            TestForTrue(fRc, "Failed Ident Test");
            //iRc = LineIndex_Compare(pObj1, pObj2);
            //TestForTrue((0 == iRc), "Failed Compare");
            //TODO: Add More tests here!
            pFnd = LineIndex_FindLine(pObj2, 3);
            TestForNotNull(pFnd, "");
            TestForTrue((2 == pFnd->lineNo), "");
            TestForTrue((4 == pFnd->offset), "");
            pFnd = LineIndex_FindLine(pObj2, 7);
            TestForNotNull(pFnd, "");
            TestForTrue((6 == pFnd->lineNo), "");
            TestForTrue((12 == pFnd->offset), "");

            obj_Release(pObj2);
            pObj2 = OBJ_NIL;

            // Test json support.
    #if defined(LINEINDEX_JSON_SUPPORT)
            pStr = LineIndex_ToJson(pObj1);
            TestForNotNull(pStr, "Missing JSON output");
            fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
            pObj2 = LineIndex_NewFromJsonString(pStr);
            TestForNotNull(pObj2, "Missing JSON created object");
            fRc = obj_IsKindOf(pObj2, OBJ_IDENT_LINEINDEX);
            TestForTrue(fRc, "Failed Ident Test");
            obj_Release(pStr);
            pStr = OBJ_NIL;
            //iRc = LineIndex_Compare(pObj1, pObj2);
            //TestForTrue((0 == iRc), "Failed Compare");
            {
                ASTR_DATA       *pStr = LineIndex_ToDebugString(pObj2, 4);
                if (pStr) {
                    fprintf(stderr, "JSON Debug: %s\n", AStr_getData(pStr));
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                }
            }

            pFnd = LineIndex_FindLine(pObj2, 3);
            TestForNotNull(pFnd, "");
            TestForTrue((2 == pFnd->lineNo), "");
            TestForTrue((4 == pFnd->offset), "");
            pFnd = LineIndex_FindLine(pObj2, 7);
            TestForNotNull(pFnd, "");
            TestForTrue((6 == pFnd->lineNo), "");
            TestForTrue((12 == pFnd->offset), "");

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



    //----------------------------------------------------------------
    //                          Test 1
    //----------------------------------------------------------------

    ERESULT         Test_LineIndex_Test01 (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        LINEINDEX_DATA  *pObj = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
        SRCLOC          loc = {0};
        SRCLOC          *pFnd;
        const
        int             max = 4;
        int             i;
        int             iMax;
       
        fprintf(stderr, "Performing: %s\n", pTestName);
        TestForNull(pStr, "");

        pObj =LineIndex_NewWithMax(max);
        TestForNotNull(pObj, "");
        if (pObj) {

            //obj_TraceSet(pObj, true);       
            fRc = obj_IsKindOf(pObj, OBJ_IDENT_LINEINDEX);
            TestForFalse(!fRc, "");
            TestForTrue(fRc, "");
            TestForSuccess("");
    #ifdef   LINEINDEX_MSGS
            LineIndex_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
    #endif
                    
            TestForTrue((4 == LineIndex_getMax(pObj)), "");

            iMax = 4;
            for (i=0; i<iMax; ++i) {
                loc.lineNo = i;
                loc.offset = i << 1;
                eRc = LineIndex_Add(pObj, &loc);
                TestForSuccess("");
                pFnd = LineIndex_FindLine(pObj, i);
                TestForNotNull(pFnd, "");
            }
            TestForTrue((4 == LineIndex_getSize(pObj)), "");
            TestForTrue((4 == LineIndex_getMax(pObj)), "");
            TestForTrue((1 == LineIndex_getInterval(pObj)), "");

            {
                ASTR_DATA       *pStr = LineIndex_ToDebugString(pObj, 4);
                if (pStr) {
                    fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                }
            }

            // Find by LineNo.
            pFnd = LineIndex_FindLine(pObj, 0);
            TestForNotNull(pFnd, "");
            fprintf(stderr, "\t0 - l=%u o=%lli\n", pFnd->lineNo, pFnd->offset);
            TestForTrue((0 == pFnd->lineNo), "");
            TestForTrue((0 == pFnd->offset), "");
            pFnd = LineIndex_FindLine(pObj, 1);
            TestForNotNull(pFnd, "");
            fprintf(stderr, "\t1 - l=%u o=%lli\n", pFnd->lineNo, pFnd->offset);
            TestForTrue((1 == pFnd->lineNo), "");
            TestForTrue((2 == pFnd->offset), "");
            pFnd = LineIndex_FindLine(pObj, 2);
            TestForNotNull(pFnd, "");
            fprintf(stderr, "\t2 - l=%u o=%lli\n", pFnd->lineNo, pFnd->offset);
            TestForTrue((2 == pFnd->lineNo), "");
            TestForTrue((4 == pFnd->offset), "");
            pFnd = LineIndex_FindLine(pObj, 3);
            TestForNotNull(pFnd, "");
            fprintf(stderr, "\t3 - l=%u o=%lli\n", pFnd->lineNo, pFnd->offset);
            TestForTrue((3 == pFnd->lineNo), "");
            TestForTrue((6 == pFnd->offset), "");
            pFnd = LineIndex_FindLine(pObj, 7);
            TestForNotNull(pFnd, "");
            fprintf(stderr, "\t7 - l=%u o=%lli\n", pFnd->lineNo, pFnd->offset);
            TestForTrue((3 == pFnd->lineNo), "");
            TestForTrue((6 == pFnd->offset), "");

            obj_Release(pObj);
            pObj = OBJ_NIL;
        }

        fprintf(stderr, "...%s completed.\n\n\n", pTestName);
        return eRc;
    }



    //----------------------------------------------------------------
    //                          Test 2
    //----------------------------------------------------------------

    ERESULT         Test_LineIndex_Test02 (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        LINEINDEX_DATA  *pObj = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
        SRCLOC          loc = {0};
        SRCLOC          *pFnd;
        const
        int             max = 4;
        int             i;
        int             iMax;
       
        fprintf(stderr, "Performing: %s\n", pTestName);
        TestForNull(pStr, "");

        pObj = LineIndex_NewWithMax(max);
        TestForNotNull(pObj, "");
        if (pObj) {

            //obj_TraceSet(pObj, true);       
            fRc = obj_IsKindOf(pObj, OBJ_IDENT_LINEINDEX);
            TestForFalse(!fRc, "");
            TestForTrue(fRc, "");
            TestForSuccess("");
    #ifdef   LINEINDEX_MSGS
            LineIndex_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
    #endif
                    
            iMax = 4;
            for (i=0; i<iMax; ++i) {
                loc.lineNo = i;
                loc.offset = i << 1;
                eRc = LineIndex_Add(pObj, &loc);
                TestForSuccess("");
                pFnd = LineIndex_FindLine(pObj, i);
                TestForNotNull(pFnd, "");
            }
            TestForTrue((4 == LineIndex_getSize(pObj)), "");
            TestForTrue((4 == LineIndex_getMax(pObj)), "");
            TestForTrue((1 == LineIndex_getInterval(pObj)), "");

            {
                ASTR_DATA       *pStr = LineIndex_ToDebugString(pObj, 4);
                if (pStr) {
                    fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                }
            }

            pFnd = LineIndex_FindOffset(pObj, 0);
            TestForNotNull(pFnd, "");
            fprintf(stderr, "\t0 - l=%u o=%lli\n", pFnd->lineNo, pFnd->offset);
            TestForTrue((0 == pFnd->lineNo), "");
            TestForTrue((0 == pFnd->offset), "");
            pFnd = LineIndex_FindOffset(pObj, 1);
            TestForNotNull(pFnd, "");
            fprintf(stderr, "\t1 - l=%u o=%lli\n", pFnd->lineNo, pFnd->offset);
            TestForTrue((0 == pFnd->lineNo), "");
            TestForTrue((0 == pFnd->offset), "");
            pFnd = LineIndex_FindOffset(pObj, 2);
            TestForNotNull(pFnd, "");
            fprintf(stderr, "\t2 - l=%u o=%lli\n", pFnd->lineNo, pFnd->offset);
            TestForTrue((1 == pFnd->lineNo), "");
            TestForTrue((2 == pFnd->offset), "");
            pFnd = LineIndex_FindOffset(pObj, 3);
            TestForNotNull(pFnd, "");
            fprintf(stderr, "\t3 - l=%u o=%lli\n", pFnd->lineNo, pFnd->offset);
            TestForTrue((1 == pFnd->lineNo), "");
            TestForTrue((2 == pFnd->offset), "");
            pFnd = LineIndex_FindOffset(pObj, 7);
            TestForNotNull(pFnd, "");
            fprintf(stderr, "\t7 - l=%u o=%lli\n", pFnd->lineNo, pFnd->offset);
            TestForTrue((3 == pFnd->lineNo), "");
            TestForTrue((6 == pFnd->offset), "");
            obj_Release(pObj);
            pObj = OBJ_NIL;
        }

        fprintf(stderr, "...%s completed.\n\n\n", pTestName);
        return eRc;
    }



    //----------------------------------------------------------------
    //                          Test 3
    //----------------------------------------------------------------

    ERESULT         Test_LineIndex_Test03 (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        LINEINDEX_DATA  *pObj = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
       
        fprintf(stderr, "Performing: %s\n", pTestName);
        TestForNull(pStr, "");

        pObj = LineIndex_New( );
        TestForNotNull(pObj, "");
        if (pObj) {

            //obj_TraceSet(pObj, true);       
            fRc = obj_IsKindOf(pObj, OBJ_IDENT_LINEINDEX);
            TestForFalse(!fRc, "");
            TestForTrue(fRc, "");
            TestForSuccess("");
    #ifdef   LINEINDEX_MSGS
            LineIndex_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
    #endif
                    
            {
                ASTR_DATA       *pStr = LineIndex_ToDebugString(pObj, 4);
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

    ERESULT         Test_LineIndex_Test04 (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        LINEINDEX_DATA  *pObj = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
       
        fprintf(stderr, "Performing: %s\n", pTestName);
        TestForNull(pStr, "");

        pObj = LineIndex_New( );
        TestForNotNull(pObj, "");
        if (pObj) {

            //obj_TraceSet(pObj, true);       
            fRc = obj_IsKindOf(pObj, OBJ_IDENT_LINEINDEX);
            TestForFalse(!fRc, "");
            TestForTrue(fRc, "");
            TestForSuccess("");
    #ifdef   LINEINDEX_MSGS
            LineIndex_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
    #endif
                    
            {
                ASTR_DATA       *pStr = LineIndex_ToDebugString(pObj, 4);
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

    int             main (
        int             cArgs,
        const
        char            *ppArgs[],
        const
        char            *ppEnv[]
    )
    {
        ERESULT         eRc;
        int             i;
        TEST_DATA       test = {0};
        TEST_DATA       *pTest = OBJ_NIL;
        const
        char            *pTestNameA = NULL;

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
            /***
            if (0 == strcmp("--debug", ppArgs[i])) {
                Test_setDebug(pTest, true);
            }
            ***/
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
        TestExec("OpenClose", Test_LineIndex_OpenClose, NULL,   NULL);
#ifdef  TEST_ASSIGN_COPY
        TestExec("Copy01", Test_LineIndex_Copy01,       NULL,   NULL);
#endif
        TestExec("Test01", Test_LineIndex_Test01,       NULL,   NULL);
        TestExec("Test02", Test_LineIndex_Test02,       NULL,   NULL);
        TestExec("Test03", Test_LineIndex_Test03,       NULL,   NULL);
        TestExec("Test04", Test_LineIndex_Test04,       NULL,   NULL);

        obj_Release(pTest);
        pTest = OBJ_NIL;

        // Return to Operating System.
        return 0;
    }


#ifdef  __cplusplus
}
#endif

