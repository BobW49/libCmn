// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          A List of Tokens (TokenList)  Test Program
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
#include    <TokenList_internal.h>
#include    <JsonIn.h>
#include    <SrcErrors.h>
#include    <szTbl.h>
#include    <ascii.h>


//#define     TEST_ASSIGN_COPY    1


#ifdef  __cplusplus
extern "C" {
#endif
        



    //----------------------------------------------------------------
    //                      Test Open/Close
    //----------------------------------------------------------------

    ERESULT         Test_TokenList_OpenClose (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        TOKENLIST_DATA  *pObj = OBJ_NIL;
       
        fprintf(stderr, "Performing: %s\n", pTestName);

        pObj = TokenList_Alloc( );
        TestForNotNull(pObj, "Missing Test Alloc() object");
        pObj = TokenList_Init( pObj );
        TestForNotNull(pObj, "Missing Test Init() object");
        if (pObj) {

            //obj_TraceSet(pObj, true);       
            fRc = obj_IsKindOf(pObj, OBJ_IDENT_TOKENLIST);
            TestForTrue(fRc, "Failed Ident Test");
    #ifdef   TOKENLIST_MSGS
            TokenList_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
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
    ERESULT         Test_TokenList_Copy01 (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        //int             iRc;
        TOKENLIST_DATA  *pObj1 = OBJ_NIL;
        TOKENLIST_DATA  *pObj2 = OBJ_NIL;
    #if defined(TOKENLIST_JSON_SUPPORT)
        ASTR_DATA       *pStr = OBJ_NIL;
    #endif
       
        fprintf(stderr, "Performing: %s\n", pTestName);

        pObj1 = TokenList_New( );
        TestForNotNull(pObj1, "Missing Test object");
        if (pObj1) {

            //obj_TraceSet(pObj1, true);       
            fRc = obj_IsKindOf(pObj1, OBJ_IDENT_TOKENLIST);
            TestForTrue(fRc, "Failed Ident Test");
    #ifdef   TOKENLIST_MSGS
            TokenList_setMsg(pObj1, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
    #endif
            
            // Test assign.
            pObj2 = TokenList_New();
            TestForNotNull(pObj2, "Missing copied object");
            eRc = TokenList_Assign(pObj1, pObj2);
            TestForFalse((ERESULT_FAILED(eRc)), "Assignment failed");

            fRc = obj_IsKindOf(pObj2, OBJ_IDENT_TOKENLIST);
            TestForTrue(fRc, "Failed Ident Test");
            //iRc = TokenList_Compare(pObj1, pObj2);
            //TestForTrue((0 == iRc), "Failed Compare");
            //TODO: Add More tests here!

            obj_Release(pObj2);
            pObj2 = OBJ_NIL;

            // Test copy.
            pObj2 = TokenList_Copy(pObj1);
            TestForNotNull(pObj2, "Missing copied object");

            fRc = obj_IsKindOf(pObj2, OBJ_IDENT_TOKENLIST);
            TestForTrue(fRc, "Failed Ident Test");
            //iRc = TokenList_Compare(pObj1, pObj2);
            //TestForTrue((0 == iRc), "Failed Compare");
            //TODO: Add More tests here!

            obj_Release(pObj2);
            pObj2 = OBJ_NIL;

            // Test json support.
    #if defined(TOKENLIST_JSON_SUPPORT)
            pStr = TokenList_ToJson(pObj1);
            TestForNotNull(pStr, "Missing JSON output");
            fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
            pObj2 = TokenList_NewFromJsonString(pStr);
            TestForNotNull(pObj2, "Missing JSON created object");
            fRc = obj_IsKindOf(pObj2, OBJ_IDENT_TOKENLIST);
            TestForTrue(fRc, "Failed Ident Test");
            obj_Release(pStr);
            pStr = OBJ_NIL;
            //iRc = TokenList_Compare(pObj1, pObj2);
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



    //----------------------------------------------------------------
    //                          Test 1
    //----------------------------------------------------------------

    ERESULT         Test_TokenList_Test01 (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        TOKENLIST_DATA  *pObj = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
        TOKEN_DATA      *pToken;
        TOKEN_DATA      *pToken2;
        uint32_t        i;
        uint32_t        cnt;
        int32_t         chr = '0';
        SRCLOC          src = {"abc",2,3,4};
       
        fprintf(stderr, "Performing: %s\n", pTestName);
        TestForNull(pStr, "");

        pObj = TokenList_New( );
        TestForNotNull(pObj, "");
        if (pObj) {

            //obj_TraceSet(pObj, true);       
            fRc = obj_IsKindOf(pObj, OBJ_IDENT_TOKENLIST);
            TestForFalse(!fRc, "");
            TestForTrue(fRc, "");
            TestForSuccess("");
    #ifdef   TOKENLIST_MSGS
            TokenList_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
    #endif
                    
            for (i=0; i<10; ++i) {
                pToken = Token_NewCharW32(&src, ascii_toLexicalClassW32(chr+i), (chr+i));
                eRc = TokenList_Add2Head(pObj, pToken);
                TestForSuccess("");
                cnt = TokenList_getSize(pObj);
                TestForTrue((cnt == (i+1)), "");
                pToken2 = TokenList_Head(pObj);
                eRc = Token_Compare(pToken, pToken2);
                TestForSuccess("");
                obj_Release(pToken);
                pToken = OBJ_NIL;
            }

            {
                ASTR_DATA       *pStr = TokenList_ToDebugString(pObj, 4);
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

    ERESULT         Test_TokenList_Test02 (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        TOKENLIST_DATA  *pObj = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
        TOKEN_DATA      *pToken;
        TOKEN_DATA      *pToken2;
        uint32_t        i;
        uint32_t        cnt;
        int32_t         chr = '0';
        SRCLOC          src = {"abc",2,3,4};
       
        fprintf(stderr, "Performing: %s\n", pTestName);
        TestForNull(pStr, "");

        pObj = TokenList_New( );
        TestForNotNull(pObj, "");
        if (pObj) {

            //obj_TraceSet(pObj, true);       
            fRc = obj_IsKindOf(pObj, OBJ_IDENT_TOKENLIST);
            TestForFalse(!fRc, "");
            TestForTrue(fRc, "");
            TestForSuccess("");
    #ifdef   TOKENLIST_MSGS
            TokenList_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
    #endif
                    
            for (i=0; i<10; ++i) {
                pToken = Token_NewCharW32(&src, ascii_toLexicalClassW32(chr+i), (chr+i));
                eRc = TokenList_Add2Tail(pObj, pToken);
                TestForSuccess("");
                cnt = TokenList_getSize(pObj);
                TestForTrue((cnt == (i+1)), "");
                pToken2 = TokenList_Tail(pObj);
                eRc = Token_Compare(pToken, pToken2);
                TestForSuccess("");
                obj_Release(pToken);
                pToken = OBJ_NIL;
            }

            {
                ASTR_DATA       *pStr = TokenList_ToDebugString(pObj, 4);
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

    ERESULT         Test_TokenList_Test03 (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        TOKENLIST_DATA  *pObj = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
        TOKENLIST_DATA  *pObj2 = OBJ_NIL;
        TOKEN_DATA      *pNameA = OBJ_NIL;
        TOKEN_DATA      *pNameB = OBJ_NIL;
        TOKEN_DATA      *pNameC = OBJ_NIL;
        TOKEN_DATA      *pNameD = OBJ_NIL;
        TOKEN_DATA      *pNameE = OBJ_NIL;
        TOKEN_DATA      *pEntry;

       
        fprintf(stderr, "Performing: %s\n", pTestName);
        TestForNull(pStr, "");

        pObj = TokenList_New( );
        TestForNotNull(pObj, "");
        if (pObj) {

            //obj_TraceSet(pObj, true);       
            fRc = obj_IsKindOf(pObj, OBJ_IDENT_TOKENLIST);
            TestForFalse(!fRc, "");
            TestForTrue(fRc, "");
            TestForSuccess("");
    #ifdef   TOKENLIST_MSGS
            TokenList_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
    #endif
                    
            pNameA = Token_NewCharW32(NULL, 'A', 'A');
            TestForNotNull(pNameA, "");
            pNameB = Token_NewCharW32(NULL, 'B', 'B');
            TestForNotNull(pNameB, "");
            pNameC = Token_NewCharW32(NULL, 'C', 'C');
            TestForNotNull(pNameC, "");
            pNameD = Token_NewCharW32(NULL, 'D', 'D');
            TestForNotNull(pNameD, "");
            pNameE = Token_NewCharW32(NULL, 'E', 'E');
            TestForNotNull(pNameE, "");

            eRc = TokenList_Add2Tail(pObj, pNameA);
            TestForSuccess("");
            eRc = TokenList_Add2Tail(pObj, pNameB);
            TestForSuccess("");
            eRc = TokenList_Add2Tail(pObj, pNameC);
            TestForSuccess("");
            eRc = TokenList_Add2Tail(pObj, pNameD);
            TestForSuccess("");
            eRc = TokenList_Add2Tail(pObj, pNameE);
            TestForSuccess("");

            {
                ASTR_DATA       *pStr = TokenList_ToDebugString(pObj, 4);
                if (pStr) {
                    fprintf(stderr, "Debug1: %s\n", AStr_getData(pStr));
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                }
            }

            pStr = TokenList_ToJson(pObj);
            TestForNotNull(pStr, "");
            if (pStr) {
                fprintf(stderr, "Json = %s\n\n\n", AStr_getData(pStr));
            }

            pObj2 = TokenList_NewFromJsonString(pStr);
            TestForNotNull(pObj2, "");
            obj_Release(pStr);
            pStr = OBJ_NIL;
            TestForTrue((!(pObj == pObj2)), "");
            TestForTrue((TokenList_getSize(pObj) == TokenList_getSize(pObj2)), "");

            pStr = TokenList_ToDebugString(pObj2, 0);
            fprintf(stderr, "Debug2 = %s\n\n\n",AStr_getData(pStr));
            obj_Release(pStr);
            pStr = OBJ_NIL;

            obj_Release(pObj2);
            pObj2 = OBJ_NIL;

            obj_Release(pNameE);
            pNameE = OBJ_NIL;
            obj_Release(pNameD);
            pNameD = OBJ_NIL;
            obj_Release(pNameC);
            pNameC = OBJ_NIL;
            obj_Release(pNameB);
            pNameB = OBJ_NIL;
            obj_Release(pNameA);
            pNameA = OBJ_NIL;

            obj_Release(pObj);
            pObj = OBJ_NIL;
        }

        fprintf(stderr, "...%s completed.\n\n\n", pTestName);
        return eRc;
    }



    //----------------------------------------------------------------
    //                          Test 4
    //----------------------------------------------------------------

    ERESULT         Test_TokenList_Test04 (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        TOKENLIST_DATA  *pObj = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
       
        fprintf(stderr, "Performing: %s\n", pTestName);
        TestForNull(pStr, "");

        pObj = TokenList_New( );
        TestForNotNull(pObj, "");
        if (pObj) {

            //obj_TraceSet(pObj, true);       
            fRc = obj_IsKindOf(pObj, OBJ_IDENT_TOKENLIST);
            TestForFalse(!fRc, "");
            TestForTrue(fRc, "");
            TestForSuccess("");
    #ifdef   TOKENLIST_MSGS
            TokenList_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
    #endif
                    
            {
                ASTR_DATA       *pStr = TokenList_ToDebugString(pObj, 4);
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
        TestExec("OpenClose", Test_TokenList_OpenClose, NULL,   NULL);
#ifdef  TEST_ASSIGN_COPY
        TestExec("Copy01", Test_TokenList_Copy01,       NULL,   NULL);
#endif
        TestExec("Test01", Test_TokenList_Test01,       NULL,   NULL);
        TestExec("Test02", Test_TokenList_Test02,       NULL,   NULL);
        TestExec("Test03", Test_TokenList_Test03,       NULL,   NULL);
        TestExec("Test04", Test_TokenList_Test04,       NULL,   NULL);

        obj_Release(pTest);
        pTest = OBJ_NIL;

        // Return to Operating System.
        return 0;
    }


#ifdef  __cplusplus
}
#endif

