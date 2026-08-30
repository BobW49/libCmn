// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Comma Delimited File Parser (CsvFile)  Test Program
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
#include    <CsvFile_internal.h>
#include    <JsonIn.h>
#include    <SrcErrors.h>
#include    <szTbl.h>


//#define     TEST_ASSIGN_COPY    1


#ifdef  __cplusplus
extern "C" {
#endif
        

static
const
char        *pTestInput01 = "a,10,\"def\"\n";


static
const
char        *pTestInput02 =
"#x,y,a\n"
"a,b,c,\"def\"\n"
"d,e,f,55\n"
"h,i,j,77\n";




    //----------------------------------------------------------------
    //                      Test Open/Close
    //----------------------------------------------------------------

    ERESULT         Test_CsvFile_OpenClose (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        CSVFILE_DATA    *pObj = OBJ_NIL;
       
        fprintf(stderr, "Performing: %s\n", pTestName);

        pObj = CsvFile_Alloc( );
        TestForNotNull(pObj, "Missing Test Alloc() object");
        pObj = CsvFile_Init( pObj );
        TestForNotNull(pObj, "Missing Test Init() object");
        if (pObj) {

            //obj_TraceSet(pObj, true);       
            fRc = obj_IsKindOf(pObj, OBJ_IDENT_CSVFILE);
            TestForTrue(fRc, "Failed Ident Test");
    #ifdef   CSVFILE_MSGS
            CsvFile_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
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
    ERESULT         Test_CsvFile_Copy01 (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        //int             iRc;
        CSVFILE_DATA    *pObj1 = OBJ_NIL;
        CSVFILE_DATA    *pObj2 = OBJ_NIL;
    #if defined(CSVFILE_JSON_SUPPORT)
        ASTR_DATA       *pStr = OBJ_NIL;
    #endif
       
        fprintf(stderr, "Performing: %s\n", pTestName);

        pObj1 = CsvFile_New( );
        TestForNotNull(pObj1, "Missing Test object");
        if (pObj1) {

            //obj_TraceSet(pObj1, true);       
            fRc = obj_IsKindOf(pObj1, OBJ_IDENT_CSVFILE);
            TestForTrue(fRc, "Failed Ident Test");
    #ifdef   CSVFILE_MSGS
            CsvFile_setMsg(pObj1, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
    #endif
            
            // Test assign.
            pObj2 = CsvFile_New();
            TestForNotNull(pObj2, "Missing copied object");
            eRc = CsvFile_Assign(pObj1, pObj2);
            TestForFalse((ERESULT_FAILED(eRc)), "Assignment failed");

            fRc = obj_IsKindOf(pObj2, OBJ_IDENT_CSVFILE);
            TestForTrue(fRc, "Failed Ident Test");
            //iRc = CsvFile_Compare(pObj1, pObj2);
            //TestForTrue((0 == iRc), "Failed Compare");
            //TODO: Add More tests here!

            obj_Release(pObj2);
            pObj2 = OBJ_NIL;

            // Test copy.
            pObj2 = CsvFile_Copy(pObj1);
            TestForNotNull(pObj2, "Missing copied object");

            fRc = obj_IsKindOf(pObj2, OBJ_IDENT_CSVFILE);
            TestForTrue(fRc, "Failed Ident Test");
            //iRc = CsvFile_Compare(pObj1, pObj2);
            //TestForTrue((0 == iRc), "Failed Compare");
            //TODO: Add More tests here!

            obj_Release(pObj2);
            pObj2 = OBJ_NIL;

            // Test json support.
    #if defined(CSVFILE_JSON_SUPPORT)
            pStr = CsvFile_ToJson(pObj1);
            TestForNotNull(pStr, "Missing JSON output");
            fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
            pObj2 = CsvFile_NewFromJsonString(pStr);
            TestForNotNull(pObj2, "Missing JSON created object");
            fRc = obj_IsKindOf(pObj2, OBJ_IDENT_CSVFILE);
            TestForTrue(fRc, "Failed Ident Test");
            obj_Release(pStr);
            pStr = OBJ_NIL;
            //iRc = CsvFile_Compare(pObj1, pObj2);
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

    ERESULT         Test_CsvFile_Test01 (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        CSVFILE_DATA    *pObj = OBJ_NIL;
        PATH_DATA       *pPath = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
        ASTRARRAY_DATA  *pRecord;
        OBJARRAY_DATA   *pRecords;
        ASTR_DATA       *pField;
        uint32_t        i;
        uint32_t        iMax;
        uint32_t        j;
        uint32_t        jMax;

       
        fprintf(stderr, "Performing: %s\n", pTestName);
        TestForNull(pStr, "");

        pStr = AStr_NewA("  a,   10,   \"def\"  \n");
        TestForNotNull(pStr, "");
        pPath = Path_NewA("abc");
        TestForNotNull(pPath, "");

        pObj = CsvFile_NewFromAStr( pStr, pPath, 4 );
        TestForNotNull(pObj, "");
        if (pObj) {

            //obj_TraceSet(pObj, true);       
            fRc = obj_IsKindOf(pObj, OBJ_IDENT_CSVFILE);
            TestForFalse(!fRc, "");
            TestForTrue(fRc, "");
            TestForSuccess("");
    #ifdef   CSVFILE_MSGS
            CsvFile_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
    #endif
                    
            pRecords = CsvFile_ParseFile(pObj);
            TestForNotNull(pRecords, "");
            if (pRecords) {
                pField = ObjArray_ToDebugString(pRecords, 0);
                fprintf(stderr, "%s\n\n\n", AStr_getData(pField));
                obj_Release(pField);
                pField = OBJ_NIL;
                iMax = ObjArray_getSize(pRecords);
                for (i=1; i<=iMax; ++i) {
                    pRecord = ObjArray_Get(pRecords,i);
                    TestForNotNull(pRecord, "");
                    if (pRecord) {
                        jMax = AStrArray_getSize(pRecord);
                        for (j=1; j<=jMax; ++j) {
                            pField = AStrArray_Get(pRecord,j);
                            TestForNotNull(pField, "");
                            if (pField) {
                                fprintf(
                                        stderr,
                                        "line %d, field %d, %s\n",
                                        i,
                                        j,
                                        AStr_getData(pField)
                                );
                            }
                            switch (i) {
                                case 1:
                                    switch (j) {
                                        case 1:
                                            TestForTrue( (0 == strcmp("a",AStr_getData(pField))), "" );
                                            break;

                                        case 2:
                                            TestForTrue( (0 == strcmp("10",AStr_getData(pField))), "" );
                                            break;

                                        case 3:
                                            TestForTrue( (0 == strcmp("def",AStr_getData(pField))), "" );
                                            break;

                                        default:
                                            break;
                                    }
                                    break;

                                default:
                                    break;
                            }
                        }

                    }
                }

                obj_Release(pRecords);
                pRecords = OBJ_NIL;
            }

            {
                ASTR_DATA       *pStr = CsvFile_ToDebugString(pObj, 4);
                if (pStr) {
                    fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                }
            }

            obj_Release(pObj);
            pObj = OBJ_NIL;
        }

        obj_Release(pPath);
        pPath = OBJ_NIL;
        obj_Release(pStr);
        pStr = OBJ_NIL;

        fprintf(stderr, "...%s completed.\n\n\n", pTestName);
        return eRc;
    }



    //----------------------------------------------------------------
    //                          Test 2
    //----------------------------------------------------------------

    ERESULT         Test_CsvFile_Test02 (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        CSVFILE_DATA    *pObj = OBJ_NIL;
        PATH_DATA       *pPath = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
        ASTRARRAY_DATA  *pRecord;
        OBJARRAY_DATA   *pRecords;
        ASTR_DATA       *pField;
        uint32_t        i;
        uint32_t        iMax;
        uint32_t        j;
        uint32_t        jMax;
       
        fprintf(stderr, "Performing: %s\n", pTestName);
        TestForNull(pStr, "");

        pStr = AStr_NewA(pTestInput02);
        TestForNotNull(pStr, "");
        pPath = Path_NewA("abc");
        TestForNotNull(pPath, "");

        pObj = CsvFile_NewFromAStr( pStr, pPath, 4 );
        TestForNotNull(pObj, "");
        if (pObj) {

            //obj_TraceSet(pObj, true);       
            fRc = obj_IsKindOf(pObj, OBJ_IDENT_CSVFILE);
            TestForFalse(!fRc, "");
            TestForTrue(fRc, "");
            TestForSuccess("");
    #ifdef   CSVFILE_MSGS
            CsvFile_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
    #endif
                    
            pRecords = CsvFile_ParseFile(pObj);
            TestForNotNull(pRecords, "");
            if (pRecords) {
                iMax = ObjArray_getSize(pRecords);
                for (i=1; i<=iMax; ++i) {
                    pRecord = ObjArray_Get(pRecords,i);
                    TestForNotNull(pRecord, "");
                    if (pRecord) {
                        jMax = AStrArray_getSize(pRecord);
                        for (j=1; j<=jMax; ++j) {
                            pField = AStrArray_Get(pRecord,j);
                            TestForNotNull(pField, "");
                            if (pField) {
                                fprintf(
                                        stderr,
                                        "line %d, field %d, %s\n",
                                        i,
                                        j,
                                        AStr_getData(pField)
                                        );
                            }
                            switch (i) {
                                case 1:
                                    switch (j) {
                                        case 1:
                                            TestForTrue( (0 == strcmp("a",AStr_getData(pField))), "" );
                                            break;

                                        case 2:
                                            TestForTrue( (0 == strcmp("b",AStr_getData(pField))), "" );
                                            break;

                                        case 3:
                                            TestForTrue( (0 == strcmp("c",AStr_getData(pField))), "" );
                                            break;

                                        case 4:
                                            TestForTrue( (0 == strcmp("def",AStr_getData(pField))), "" );
                                            break;

                                        default:
                                            break;
                                    }
                                    break;

                                case 2:
                                    switch (j) {
                                        case 1:
                                            TestForTrue( (0 == strcmp("d",AStr_getData(pField))), "" );
                                            break;

                                        case 2:
                                            TestForTrue( (0 == strcmp("e",AStr_getData(pField))), "" );
                                            break;

                                        case 3:
                                            TestForTrue( (0 == strcmp("f",AStr_getData(pField))), "" );
                                            break;

                                        case 4:
                                            TestForTrue( (0 == strcmp("55",AStr_getData(pField))), "" );
                                            break;

                                        default:
                                            break;
                                    }
                                    break;

                                case 3:
                                    switch (j) {
                                        case 1:
                                            TestForTrue( (0 == strcmp("h",AStr_getData(pField))), "" );
                                            break;

                                        case 2:
                                            TestForTrue( (0 == strcmp("i",AStr_getData(pField))), "" );
                                            break;

                                        case 3:
                                            TestForTrue( (0 == strcmp("j",AStr_getData(pField))), "" );
                                            break;

                                        case 4:
                                            TestForTrue( (0 == strcmp("77",AStr_getData(pField))), "" );
                                            break;

                                        default:
                                            break;
                                    }
                                    break;

                                default:
                                    break;
                            }
                        }

                    }
                }

            }

            obj_Release(pRecords);
            pRecords = OBJ_NIL;

            {
                ASTR_DATA       *pStr = CsvFile_ToDebugString(pObj, 4);
                if (pStr) {
                    fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                }
            }

            obj_Release(pObj);
            pObj = OBJ_NIL;
        }

        obj_Release(pPath);
        pPath = OBJ_NIL;
        obj_Release(pStr);
        pStr = OBJ_NIL;

        fprintf(stderr, "...%s completed.\n\n\n", pTestName);
        return eRc;
    }



    //----------------------------------------------------------------
    //                          Test 3
    //----------------------------------------------------------------

    ERESULT         Test_CsvFile_Test03 (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        CSVFILE_DATA    *pObj = OBJ_NIL;
        PATH_DATA       *pPath = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
        ASTRARRAY_DATA  *pRecord;
        OBJARRAY_DATA   *pRecords;
        ASTR_DATA       *pField;
        uint32_t        i;
        uint32_t        iMax;
        uint32_t        j;
        uint32_t        jMax;
       
        fprintf(stderr, "Performing: %s\n", pTestName);
        TestForNull(pStr, "");

        pPath = Path_NewA(TEST_FILES_DIR "/csv_e360_opcodes.txt");
        TestForNotNull(pPath, "");
        eRc = Path_Clean(pPath, NULL, OBJ_NIL);
        eRc = Path_IsFile(pPath);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "Warning: %s missing, test skipped.\n", Path_getData(pPath));
            return 1;
        }

        pObj = CsvFile_NewFromPath(pPath, 4);
        TestForNotNull(pObj, "");
        if (pObj) {

            //obj_TraceSet(pObj, true);       
            fRc = obj_IsKindOf(pObj, OBJ_IDENT_CSVFILE);
            TestForFalse(!fRc, "");
            TestForTrue(fRc, "");
            TestForSuccess("");
    #ifdef   CSVFILE_MSGS
            CsvFile_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
    #endif
                    
            pRecords = CsvFile_ParseFile(pObj);
            TestForNotNull(pRecords, "");
            if (pRecords) {
                iMax = ObjArray_getSize(pRecords);
                for (i=1; i<=iMax; ++i) {
                    pRecord = ObjArray_Get(pRecords,i);
                    TestForNotNull(pRecord, "");
                    if (pRecord) {
                        jMax = AStrArray_getSize(pRecord);
                        for (j=1; j<=jMax; ++j) {
                            pField = AStrArray_Get(pRecord,j);
                            TestForNotNull(pField, "");
                            if (pField) {
                                fprintf(
                                        stderr,
                                        "line %d, field %d, %s\n",
                                        i,
                                        j,
                                        AStr_getData(pField)
                                );
                            }
                        }

                    }
                }

            }

            obj_Release(pRecords);
            pRecords = OBJ_NIL;

            {
                ASTR_DATA       *pStr = CsvFile_ToDebugString(pObj, 4);
                if (pStr) {
                    fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                }
            }

            obj_Release(pObj);
            pObj = OBJ_NIL;
        }

        obj_Release(pPath);
        pPath = OBJ_NIL;

        fprintf(stderr, "...%s completed.\n\n\n", pTestName);
        return eRc;
    }



    //----------------------------------------------------------------
    //                          Test 4
    //----------------------------------------------------------------

    ERESULT         Test_CsvFile_Test04 (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        CSVFILE_DATA    *pObj = OBJ_NIL;
        PATH_DATA       *pPath = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
        ASTRARRAY_DATA  *pRecord;
        OBJARRAY_DATA   *pRecords;
        ASTR_DATA       *pField;
        uint32_t        i;
        uint32_t        iMax;
        uint32_t        j;
        uint32_t        jMax;
       
        fprintf(stderr, "Performing: %s\n", pTestName);
        TestForNull(pStr, "");

        pStr = AStr_NewA("a, \"d,e,f\"\n");
        TestForNotNull(pStr, "");
        pPath = Path_NewA("abc");
        TestForNotNull(pPath, "");

        pObj = CsvFile_NewFromAStr( pStr, pPath, 4 );
        TestForNotNull(pObj, "");
        if (pObj) {

            //obj_TraceSet(pObj, true);       
            fRc = obj_IsKindOf(pObj, OBJ_IDENT_CSVFILE);
            TestForFalse(!fRc, "");
            TestForTrue(fRc, "");
            TestForSuccess("");
    #ifdef   CSVFILE_MSGS
            CsvFile_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
    #endif
                    
            pRecords = CsvFile_ParseFile(pObj);
            TestForNotNull(pRecords, "");
            if (pRecords) {
                pField = ObjArray_ToDebugString(pRecords, 0);
                fprintf(stderr, "%s\n\n\n", AStr_getData(pField));
                obj_Release(pField);
                pField = OBJ_NIL;
                iMax = ObjArray_getSize(pRecords);
                for (i=1; i<=iMax; ++i) {
                    pRecord = ObjArray_Get(pRecords,i);
                    TestForNotNull(pRecord, "");
                    if (pRecord) {
                        jMax = AStrArray_getSize(pRecord);
                        for (j=1; j<=jMax; ++j) {
                            pField = AStrArray_Get(pRecord,j);
                            TestForNotNull(pField, "");
                            if (pField) {
                                fprintf(
                                        stderr,
                                        "line %d, field %d, %s\n",
                                        i,
                                        j,
                                        AStr_getData(pField)
                                        );
                            }
                            switch (i) {
                                case 1:
                                    switch (j) {
                                        case 1:
                                            TestForTrue( (0 == strcmp("a",AStr_getData(pField))), "" );
                                            break;

                                        case 2:
                                            TestForTrue( (0 == strcmp("d,e,f",AStr_getData(pField))), "" );
                                            break;

                                        default:
                                            break;
                                    }
                                    break;

                                default:
                                    break;
                            }
                        }

                    }
                }

            }

            obj_Release(pRecords);
            pRecords = OBJ_NIL;

            {
                ASTR_DATA       *pStr = CsvFile_ToDebugString(pObj, 4);
                if (pStr) {
                    fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                }
            }

            obj_Release(pObj);
            pObj = OBJ_NIL;
        }

        obj_Release(pPath);
        pPath = OBJ_NIL;
        obj_Release(pStr);
        pStr = OBJ_NIL;

        fprintf(stderr, "...%s completed.\n\n\n", pTestName);
        return eRc;
    }



    //----------------------------------------------------------------
    //                          Test 5
    //----------------------------------------------------------------

    ERESULT         Test_CsvFile_Test05 (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        CSVFILE_DATA    *pObj = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
       
        fprintf(stderr, "Performing: %s\n", pTestName);
        TestForNull(pStr, "");

        pObj = CsvFile_New( );
        TestForNotNull(pObj, "");
        if (pObj) {

            //obj_TraceSet(pObj, true);       
            fRc = obj_IsKindOf(pObj, OBJ_IDENT_CSVFILE);
            TestForFalse(!fRc, "");
            TestForTrue(fRc, "");
            TestForSuccess("");
    #ifdef   CSVFILE_MSGS
            CsvFile_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
    #endif
                    
            {
                ASTR_DATA       *pStr = CsvFile_ToDebugString(pObj, 4);
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
        TestExec("OpenClose", Test_CsvFile_OpenClose, NULL,   NULL);
#ifdef  TEST_ASSIGN_COPY
        TestExec("Copy01", Test_CsvFile_Copy01,       NULL,   NULL);
#endif
        TestExec("Test01", Test_CsvFile_Test01,       NULL,   NULL);
        TestExec("Test02", Test_CsvFile_Test02,       NULL,   NULL);
        TestExec("Test03", Test_CsvFile_Test03,       NULL,   NULL);
        TestExec("Test04", Test_CsvFile_Test04,       NULL,   NULL);
        TestExec("Test05", Test_CsvFile_Test05,       NULL,   NULL);

        obj_Release(pTest);
        pTest = OBJ_NIL;

        // Return to Operating System.
        return 0;
    }


#ifdef  __cplusplus
}
#endif

