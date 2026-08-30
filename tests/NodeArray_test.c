// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          An Array of Nodes (NodeArray)  Test Program
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
#include    <NodeArray_internal.h>
#include    <JsonIn.h>
#include    <SrcErrors.h>
#include    <szTbl.h>


//#define     TEST_ASSIGN_COPY    1


#ifdef  __cplusplus
extern "C" {
#endif
        
    static
    uint32_t    cStrings = 33;

    static
    const
    char        *ppStrings[] = {
        "bob",
        "bobby",
        "iryana",
        "dashsa",
        "dasha",
        "name",
        "way",
        "bigger",
        "Now",
        "is",
        "the",
        "time",
        "for",
        "all",
        "good",
        "men",
        "to",
        "come",
        "aid",
        "of",
        "their",
        "country",
        "We",
        "need",
        "another",
        "item",
        "in",
        "here",
        "Are",
        "you",
        "alright",
        "with",
        "this",
        (char *)NULL
    };

    static
    const
    char        *ppStrings_sorted[] = {
        "Are",
        "Now",
        "We",
        "aid",
        "all",
        "alright",
        "another",
        "bigger",
        "bob",
        "bobby",
        "come",
        "country",
        "dasha",
        "dashsa",
        "for",
        "good",
        "here",
        "in",
        "iryana",
        "is",
        "item",
        "men",
        "name",
        "need",
        "of",
        "the",
        "their",
        "this",
        "time",
        "to",
        "way",
        "with",
        "you",
        (char *)NULL
    };




    //----------------------------------------------------------------
    //                      Test Open/Close
    //----------------------------------------------------------------

    ERESULT         Test_NodeArray_OpenClose (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        NODEARRAY_DATA  *pObj = OBJ_NIL;
       
        fprintf(stderr, "Performing: %s\n", pTestName);

        pObj = NodeArray_Alloc( );
        TestForNotNull(pObj, "Missing Test Alloc() object");
        pObj = NodeArray_Init( pObj );
        TestForNotNull(pObj, "Missing Test Init() object");
        if (pObj) {

            //obj_TraceSet(pObj, true);       
            fRc = obj_IsKindOf(pObj, OBJ_IDENT_NODEARRAY);
            TestForTrue(fRc, "Failed Ident Test");
            fRc = obj_IsKindOf(pObj, OBJ_IDENT_NODE);
            TestForTrue(fRc, "Failed Ident Test");
    #ifdef   NODEARRAY_MSGS
            NodeArray_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
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
    ERESULT         Test_NodeArray_Copy01 (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        //int             iRc;
        NODEARRAY_DATA  *pObj1 = OBJ_NIL;
        NODEARRAY_DATA  *pObj2 = OBJ_NIL;
    #if defined(NODEARRAY_JSON_SUPPORT)
        ASTR_DATA       *pStr = OBJ_NIL;
    #endif
       
        fprintf(stderr, "Performing: %s\n", pTestName);

        pObj1 = NodeArray_New( );
        TestForNotNull(pObj1, "Missing Test object");
        if (pObj1) {

            //obj_TraceSet(pObj1, true);       
            fRc = obj_IsKindOf(pObj1, OBJ_IDENT_NODEARRAY);
            TestForTrue(fRc, "Failed Ident Test");
    #ifdef   NODEARRAY_MSGS
            NodeArray_setMsg(pObj1, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
    #endif
            
            // Test assign.
            pObj2 = NodeArray_New();
            TestForNotNull(pObj2, "Missing copied object");
            eRc = NodeArray_Assign(pObj1, pObj2);
            TestForFalse((ERESULT_FAILED(eRc)), "Assignment failed");

            fRc = obj_IsKindOf(pObj2, OBJ_IDENT_NODEARRAY);
            TestForTrue(fRc, "Failed Ident Test");
            //iRc = NodeArray_Compare(pObj1, pObj2);
            //TestForTrue((0 == iRc), "Failed Compare");
            //TODO: Add More tests here!

            obj_Release(pObj2);
            pObj2 = OBJ_NIL;

            // Test copy.
            pObj2 = NodeArray_Copy(pObj1);
            TestForNotNull(pObj2, "Missing copied object");

            fRc = obj_IsKindOf(pObj2, OBJ_IDENT_NODEARRAY);
            TestForTrue(fRc, "Failed Ident Test");
            //iRc = NodeArray_Compare(pObj1, pObj2);
            //TestForTrue((0 == iRc), "Failed Compare");
            //TODO: Add More tests here!

            obj_Release(pObj2);
            pObj2 = OBJ_NIL;

            // Test json support.
    #if defined(NODEARRAY_JSON_SUPPORT)
            pStr = NodeArray_ToJson(pObj1);
            TestForNotNull(pStr, "Missing JSON output");
            fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
            pObj2 = NodeArray_NewFromJsonString(pStr);
            TestForNotNull(pObj2, "Missing JSON created object");
            fRc = obj_IsKindOf(pObj2, OBJ_IDENT_NODEARRAY);
            TestForTrue(fRc, "Failed Ident Test");
            obj_Release(pStr);
            pStr = OBJ_NIL;
            //iRc = NodeArray_Compare(pObj1, pObj2);
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

    ERESULT         Test_NodeArray_Test01 (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        int             iRc;
        NODEARRAY_DATA  *pObj = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
        NODE_DATA       *pNode;
        NODE_DATA       *pNode2;
        uint32_t        i;
        uint32_t        cnt;
        int32_t         cls;
        uint32_t        idx;
        I32ARRAY_DATA   *pClasses = OBJ_NIL;

       
        fprintf(stderr, "Performing: %s\n", pTestName);
        TestForNull(pStr, "");

        pObj = NodeArray_New( );
        TestForNotNull(pObj, "");
        if (pObj) {

            //obj_TraceSet(pObj, true);       
            fRc = obj_IsKindOf(pObj, OBJ_IDENT_NODEARRAY);
            TestForFalse(!fRc, "");
            TestForTrue(fRc, "");
            TestForSuccess("");
    #ifdef   NODEARRAY_MSGS
            NodeArray_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
    #endif
                    
            for (i=0; i<cStrings; ++i) {
                pNode = Node_NewWithUTF8ConAndClass(0, ppStrings[i], OBJ_NIL);
                eRc = NodeArray_AppendNode(pObj, pNode, &idx);
                TestForTrue( (ERESULT_IS_SUCCESSFUL(eRc)), "" );
                cnt = NodeArray_getSize(pObj);
                TestForTrue( (idx == (i+1)), "" );
                TestForTrue( (cnt == (i+1)), "" );
                pNode2 = NodeArray_Get(pObj, i+1);
                TestForTrue( (pNode == pNode2), "" );
                obj_Release(pNode);
                pNode = OBJ_NIL;
            }
            cnt = NodeArray_getSize(pObj);
            TestForTrue( (cnt == cStrings), "" );

            for (i=0; i<cStrings; ++i) {
                pNode = OBJ_NIL;
                pNode = NodeArray_FindA(pObj, 0, ppStrings[i]);
                TestForFalse( (pNode == OBJ_NIL), "" );
            }

            for (i=0; i<cStrings; ++i) {
                pNode = OBJ_NIL;
                pNode = NodeArray_Get(pObj, i+1);
                TestForFalse( (pNode == OBJ_NIL), "" );
                Node_setClass(pNode, i+1);
            }

            pClasses = NodeArray_ToClassArray(pObj);
            TestForNotNull(pClasses, "");
            for (i=0; i<cStrings; ++i) {
                cls = I32Array_Get(pClasses, i+1);
                TestForTrue( (cls == (i+1)), "" );
            }
            obj_Release(pClasses);
            pClasses = OBJ_NIL;

            for (i=0; i<cStrings; ++i) {
                pNode = OBJ_NIL;
                pNode = NodeArray_Get(pObj, i+1);
                TestForFalse( (pNode == OBJ_NIL), "" );
                Node_setClass(pNode, 0);
            }

            pNode = OBJ_NIL;
            pNode = NodeArray_FindA(pObj, 0, "xyzzy");
            TestForTrue( (pNode == OBJ_NIL), "" );

           {
                ASTR_DATA       *pStr = NodeArray_ToDebugString(pObj, 4);
                if (pStr) {
                    fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                }
            }

            eRc = NodeArray_SortAscending(pObj);
            TestForTrue( (ERESULT_IS_SUCCESSFUL(eRc)), "" );
            cnt = NodeArray_getSize(pObj);
            TestForTrue( (cnt == cStrings), "" );
            
           {
                ASTR_DATA       *pStr = NodeArray_ToDebugString(pObj, 4);
                if (pStr) {
                    fprintf(stderr, "Sorted: %s\n", AStr_getData(pStr));
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                }
            }

            for (i=0; i<cStrings; ++i) {
                pNode = NodeArray_Get(pObj, i+1);
                TestForNotNull(pNode, "");
                //fprintf(stderr, "Compare: %d %s\n", i, ppStrings_sorted[i]);
                iRc = Node_CompareA(pNode, 0, ppStrings_sorted[i]);
                TestForTrue( (0 == iRc), "" );
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

    ERESULT         Test_NodeArray_Test02 (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        NODEARRAY_DATA  *pObj = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
       
        fprintf(stderr, "Performing: %s\n", pTestName);
        TestForNull(pStr, "");

        pObj = NodeArray_New( );
        TestForNotNull(pObj, "");
        if (pObj) {

            //obj_TraceSet(pObj, true);       
            fRc = obj_IsKindOf(pObj, OBJ_IDENT_NODEARRAY);
            TestForFalse(!fRc, "");
            TestForTrue(fRc, "");
            TestForSuccess("");
    #ifdef   NODEARRAY_MSGS
            NodeArray_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
    #endif
                    
            {
                ASTR_DATA       *pStr = NodeArray_ToDebugString(pObj, 4);
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

    ERESULT         Test_NodeArray_Test03 (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        NODEARRAY_DATA  *pObj = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
       
        fprintf(stderr, "Performing: %s\n", pTestName);
        TestForNull(pStr, "");

        pObj = NodeArray_New( );
        TestForNotNull(pObj, "");
        if (pObj) {

            //obj_TraceSet(pObj, true);       
            fRc = obj_IsKindOf(pObj, OBJ_IDENT_NODEARRAY);
            TestForFalse(!fRc, "");
            TestForTrue(fRc, "");
            TestForSuccess("");
    #ifdef   NODEARRAY_MSGS
            NodeArray_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
    #endif
                    
            {
                ASTR_DATA       *pStr = NodeArray_ToDebugString(pObj, 4);
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

    ERESULT         Test_NodeArray_Test04 (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        NODEARRAY_DATA  *pObj = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
       
        fprintf(stderr, "Performing: %s\n", pTestName);
        TestForNull(pStr, "");

        pObj = NodeArray_New( );
        TestForNotNull(pObj, "");
        if (pObj) {

            //obj_TraceSet(pObj, true);       
            fRc = obj_IsKindOf(pObj, OBJ_IDENT_NODEARRAY);
            TestForFalse(!fRc, "");
            TestForTrue(fRc, "");
            TestForSuccess("");
    #ifdef   NODEARRAY_MSGS
            NodeArray_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
    #endif
                    
            {
                ASTR_DATA       *pStr = NodeArray_ToDebugString(pObj, 4);
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
        char            *pTestNameA = NULL;     // Used in TestExec() macro

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
        TestExec("OpenClose", Test_NodeArray_OpenClose, NULL,   NULL);
#ifdef  TEST_ASSIGN_COPY
        TestExec("Copy01", Test_NodeArray_Copy01,       NULL,   NULL);
#endif
        TestExec("Test01", Test_NodeArray_Test01,       NULL,   NULL);
        TestExec("Test02", Test_NodeArray_Test02,       NULL,   NULL);
        TestExec("Test03", Test_NodeArray_Test03,       NULL,   NULL);
        TestExec("Test04", Test_NodeArray_Test04,       NULL,   NULL);

        obj_Release(pTest);
        pTest = OBJ_NIL;

        // Return to Operating System.
        return 0;
    }


#ifdef  __cplusplus
}
#endif

