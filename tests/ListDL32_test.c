// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
// Doubly-Linked List using 32-bit Indices (ListDL32)  Test Program
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
#include    <ListDL32.h>
#include    <array.h>
#include    <JsonIn.h>
#include    <SrcErrors.h>
#include    <szTbl.h>



#ifdef  __cplusplus
extern "C" {
#endif
        
    static
    const
    char    *pStringTable[] = {
        "now",
        "before",
        "after",
        "tomorrow",
        "today",
        "someday",
    };
    enum { cStringTable = 6 };

    typedef struct list_entry_s {
        LISTDL32_NODE   node;
        const
        char            *pString;
    } LIST_ENTRY;


    static
    LIST_ENTRY  listTable[cStringTable] = {0};
    static
    int         cListTable = 0;


    int             compare (
        void            *p1,
        void            *p2
    )
    {
        LIST_ENTRY  *pNode1 = p1;
        LIST_ENTRY  *pNode2 = p2;
        int         rc;
        
        rc = strcmp(pNode1->pString, pNode2->pString);
        return rc;
    }



    int             setup_List (
        TEST_DATA       *this
    )
    {
        int             i;
        
        cListTable = cStringTable;
        for (i=0; i<cStringTable; i++) {
            listTable[i].pString = pStringTable[i];
            listTable[i].node.next = 0;
            listTable[i].node.prev = 0;
        }
        
        return 1;
    }


    int             teardown_List (
        TEST_DATA       *this
    )
    {
        return 1;
    }


    void *          index_List (
        void            *this,
        LISTDL32_INDEX  index
    )
    {
        void            *pEntry = NULL;
        
        pEntry = &listTable[index-1];
        
        return pEntry;
    }

    //----------------------------------------------------------------
    //                      Test Open/Close
    //----------------------------------------------------------------

    ERESULT         Test_ListDL32_OpenClose (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        LISTDL32_DATA   *pObj = OBJ_NIL;
        bool            fRc;
       
        fprintf(stderr, "Performing: %s\n", pTestName);

        pObj = ListDL32_Alloc( );
        TestForNotNull(pObj, "Missing Test Alloc() object");
        fRc = ListDL32_Init(pObj, 0, index_List, NULL);
        TestForTrue(pObj, "Missing Test Init() object");
        if (pObj) {

            //obj_TraceSet(pObj, true);       
            
            // Test something.
            TestForSuccess("");

            mem_Free(pObj);
            pObj = OBJ_NIL;
        }

        fprintf(stderr, "...%s completed.\n\n\n", pTestName);
        return eRc;
    }



    //----------------------------------------------------------------
    //                          Test 1
    //----------------------------------------------------------------

    ERESULT         Test_ListDL32_Test01 (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        LISTDL32_DATA   *pObj = OBJ_NIL;
        bool            fRc = true;
        LISTDL32_NODE   *pNode;

        fprintf(stderr, "Performing: %s\n", pTestName);

        pObj = ListDL32_New(0, index_List, NULL);
        TestForNotNull(pObj, "");
        if (pObj) {

            //obj_TraceSet(pObj, true);       
            TestForFalse(!fRc, "");
            TestForTrue(fRc, "");
            TestForSuccess("");
                    
            fRc = ListDL32_Add2Head(pObj, 1);
            TestForTrue(fRc, "");
            pNode = ListDL32_Entry(pObj, 1);
            TestForTrue((pNode->next == 0), "");
            TestForTrue((pNode->prev == 0), "");
            TestForTrue((pObj->head == 1), "");
            TestForTrue((pObj->tail == 1), "");
            fRc = ListDL32_Add2Tail(pObj, 2);
            TestForTrue(fRc, "");
            pNode = ListDL32_Entry(pObj, 1);
            TestForTrue((pNode->next == 2), "");
            TestForTrue((pNode->prev == 0), "");
            pNode = ListDL32_Entry(pObj, 2);
            TestForTrue((pNode->next == 0), "");
            TestForTrue((pNode->prev == 1), "");
            TestForTrue((pObj->head == 1), "");
            TestForTrue((pObj->tail == 2), "");
            TestForTrue((pObj->size == 2), "");

            fRc = ListDL32_Add2Head(pObj, 3);
            TestForTrue(fRc, "");
            fRc = ListDL32_Add2Tail(pObj, 4);
            TestForTrue(fRc, "");
            fRc = ListDL32_Add2Head(pObj, 5);
            TestForTrue(fRc, "");
            fRc = ListDL32_Add2Tail(pObj, 6);
            TestForTrue(fRc, "");
            TestForTrue((pObj->head == 5), "");
            TestForTrue((pObj->tail == 6), "");
            TestForTrue((pObj->size == 6), "");
            pNode = ListDL32_Entry(pObj, 1);
            TestForTrue((pNode->next == 2), "");
            TestForTrue((pNode->prev == 3), "");
            pNode = ListDL32_Entry(pObj, 2);
            TestForTrue((pNode->next == 4), "");
            TestForTrue((pNode->prev == 1), "");
            pNode = ListDL32_Entry(pObj, 3);
            TestForTrue((pNode->next == 1), "");
            TestForTrue((pNode->prev == 5), "");
            pNode = ListDL32_Entry(pObj, 4);
            TestForTrue((pNode->next == 6), "");
            TestForTrue((pNode->prev == 2), "");
            pNode = ListDL32_Entry(pObj, 5);
            TestForTrue((pNode->next == 3), "");
            TestForTrue((pNode->prev == 0), "");
            pNode = ListDL32_Entry(pObj, 6);
            TestForTrue((pNode->next == 0), "");
            TestForTrue((pNode->prev == 4), "");

            fRc = ListDL32_IsValidList(pObj);
            TestForTrue(fRc, "");
            
            {
                ASTR_DATA       *pStr = ListDL32_ToDebugString(pObj, 4);
                if (pStr) {
                    fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                }
            }

            fRc = ListDL32_DeleteHead(pObj);
            TestForTrue(fRc, "");
            TestForTrue((pObj->head == 3), "");
            TestForTrue((pObj->tail == 6), "");
            TestForTrue((pObj->size == 5), "");
            pNode = ListDL32_Entry(pObj, 1);
            TestForTrue((pNode->next == 2), "");
            TestForTrue((pNode->prev == 3), "");
            pNode = ListDL32_Entry(pObj, 2);
            TestForTrue((pNode->next == 4), "");
            TestForTrue((pNode->prev == 1), "");
            pNode = ListDL32_Entry(pObj, 3);
            TestForTrue((pNode->next == 1), "");
            TestForTrue((pNode->prev == 0), "");
            pNode = ListDL32_Entry(pObj, 4);
            TestForTrue((pNode->next == 6), "");
            TestForTrue((pNode->prev == 2), "");
            pNode = ListDL32_Entry(pObj, 5);
            TestForTrue((pNode->next == 0), "");
            TestForTrue((pNode->prev == 0), "");
            pNode = ListDL32_Entry(pObj, 6);
            TestForTrue((pNode->next == 0), "");
            TestForTrue((pNode->prev == 4), "");

            {
                ASTR_DATA       *pStr = ListDL32_ToDebugString(pObj, 4);
                if (pStr) {
                    fprintf(stderr, "DeleteHead: %s\n", AStr_getData(pStr));
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                }
            }

            fRc = ListDL32_DeleteTail(pObj);
            TestForTrue(fRc, "");
            TestForTrue((pObj->head == 3), "");
            TestForTrue((pObj->tail == 4), "");
            TestForTrue((pObj->size == 4), "");
            pNode = ListDL32_Entry(pObj, 1);
            TestForTrue((pNode->next == 2), "");
            TestForTrue((pNode->prev == 3), "");
            pNode = ListDL32_Entry(pObj, 2);
            TestForTrue((pNode->next == 4), "");
            TestForTrue((pNode->prev == 1), "");
            pNode = ListDL32_Entry(pObj, 3);
            TestForTrue((pNode->next == 1), "");
            TestForTrue((pNode->prev == 0), "");
            pNode = ListDL32_Entry(pObj, 4);
            TestForTrue((pNode->next == 0), "");
            TestForTrue((pNode->prev == 2), "");
            pNode = ListDL32_Entry(pObj, 5);
            TestForTrue((pNode->next == 0), "");
            TestForTrue((pNode->prev == 0), "");
            pNode = ListDL32_Entry(pObj, 6);
            TestForTrue((pNode->next == 0), "");
            TestForTrue((pNode->prev == 0), "");

            {
                ASTR_DATA       *pStr = ListDL32_ToDebugString(pObj, 4);
                if (pStr) {
                    fprintf(stderr, "DeleteTail: %s\n", AStr_getData(pStr));
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                }
            }

            fRc = ListDL32_Sort(pObj, compare);
            TestForTrue(fRc, "");
            fRc = ListDL32_IsValidList(pObj);
            TestForTrue(fRc, "");

            {
                ASTR_DATA       *pStr = ListDL32_ToDebugString(pObj, 4);
                if (pStr) {
                    fprintf(stderr, "Sorted: %s\n", AStr_getData(pStr));
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                }
            }

            mem_Free(pObj);
            pObj = OBJ_NIL;
        }

        fprintf(stderr, "...%s completed.\n\n\n", pTestName);
        return eRc;
    }



    //----------------------------------------------------------------
    //                          Test 2
    //----------------------------------------------------------------

    ERESULT         Test_ListDL32_Test02 (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        LISTDL32_DATA   *pObj = OBJ_NIL;
        bool            fRc = true;
        LIST_ENTRY      *pEntry;
        int             i;
       
        fprintf(stderr, "Performing: %s\n", pTestName);

        pObj = ListDL32_New(0, index_List, NULL);
        TestForNotNull(pObj, "");
        if (pObj) {

            //obj_TraceSet(pObj, true);       
            TestForFalse(!fRc, "");
            TestForTrue(fRc, "");
            TestForSuccess("");
            
            for (i=0; i<cStringTable; i++) {
                fRc = ListDL32_Add2Tail(pObj, i+1);
            }
                    
            fprintf(stderr, "\tBefore Sort:\n");
            for (pEntry = ListDL32_Next(pObj,NULL); pEntry; pEntry=ListDL32_Next(pObj,pEntry)) {
                fprintf(stderr, "\t\t%s\n", pEntry->pString);
            }
            
            fRc = ListDL32_Sort(pObj, compare);
            TestForTrue(fRc, "");
            fRc = ListDL32_IsValidList(pObj);
            TestForTrue(fRc, "");

            fprintf(stderr, "\tAfter Sort:\n");
            for (pEntry = ListDL32_Next(pObj,NULL); pEntry; pEntry=ListDL32_Next(pObj,pEntry)) {
                fprintf(stderr, "\t\t%s\n", pEntry->pString);
            }
            
            {
                ASTR_DATA       *pStr = ListDL32_ToDebugString(pObj, 4);
                if (pStr) {
                    fprintf(stderr, "Sorted: %s\n", AStr_getData(pStr));
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                }
            }

            mem_Free(pObj);
            pObj = OBJ_NIL;
        }

        fprintf(stderr, "...%s completed.\n\n\n", pTestName);
        return eRc;
    }



    //----------------------------------------------------------------
    //                          Test 3
    //----------------------------------------------------------------

    ERESULT         Test_ListDL32_Test03 (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        LISTDL32_DATA   *pObj = OBJ_NIL;
        bool            fRc = true;
       
        fprintf(stderr, "Performing: %s\n", pTestName);

        pObj = ListDL32_New(0, index_List, NULL);
        TestForNotNull(pObj, "");
        if (pObj) {

            //obj_TraceSet(pObj, true);       
            TestForFalse(!fRc, "");
            TestForTrue(fRc, "");
            TestForSuccess("");
                    
            {
                ASTR_DATA       *pStr = ListDL32_ToDebugString(pObj, 4);
                if (pStr) {
                    fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                }
            }

            mem_Free(pObj);
            pObj = OBJ_NIL;
        }

        fprintf(stderr, "...%s completed.\n\n\n", pTestName);
        return eRc;
    }



    //----------------------------------------------------------------
    //                          Test 4
    //----------------------------------------------------------------

    ERESULT         Test_ListDL32_Test04 (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        LISTDL32_DATA   *pObj = OBJ_NIL;
        bool            fRc = true;
       
        fprintf(stderr, "Performing: %s\n", pTestName);

        pObj = ListDL32_New(0, index_List, NULL);
        TestForNotNull(pObj, "");
        if (pObj) {

            //obj_TraceSet(pObj, true);       
            TestForFalse(!fRc, "");
            TestForTrue(fRc, "");
            TestForSuccess("");
                    
            {
                ASTR_DATA       *pStr = ListDL32_ToDebugString(pObj, 4);
                if (pStr) {
                    fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                }
            }

            mem_Free(pObj);
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
        TEST_DATA       test = {0};
        TEST_DATA       *pTest = OBJ_NIL;
        int             i;
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
            if (0 == strcmp("--no_int3", ppArgs[i])) {
                Test_setAllowInt3(pTest, false);
            }
        }

        // Execute tests.
        // Note: 
        //  Test_Setup() is called before the optional supplied setup
        //  in this table. Likewise, the optional teardown routine is
        //  called before Test_TearDown().
        //                                             Setup        TearDown
        TestExec("OpenClose", Test_ListDL32_OpenClose, setup_List,  teardown_List);
        TestExec("Test01",    Test_ListDL32_Test01,    setup_List,  teardown_List);
        TestExec("Test02", Test_ListDL32_Test02,       setup_List,  teardown_List);
        TestExec("Test03", Test_ListDL32_Test03,       setup_List,  teardown_List);
        TestExec("Test04", Test_ListDL32_Test04,       setup_List,  teardown_List);

        obj_Release(pTest);
        pTest = OBJ_NIL;

        // Return to Operating System.
        return 0;
    }


#ifdef  __cplusplus
}
#endif

