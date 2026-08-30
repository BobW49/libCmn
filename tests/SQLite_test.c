// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          SQLite Interface (SQLite)  Test Program
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
#include    <SQLite_internal.h>
#include    <JsonIn.h>
#include    <SrcErrors.h>
#include    <szTbl.h>


//#define     TEST_ASSIGN_COPY    1


#ifdef  __cplusplus
extern "C" {
#endif
        

    // int (*pCallback)(void*,int,char**,char**)
    static
    int             SQLite_dump_callback (
        void            *pData,
        int             numCols,
        char            **pColText,
        char            **pColName
    )
    {
        //SQLITE_DATA     *this = pData;
        uint32_t        i;

        fprintf(stderr, "\nnumber of columns: %d\n", numCols);
        fprintf(stderr, "\t%15s: Data\n", "Column Names");
        for (i=0; i<numCols; ++i) {
            fprintf(stderr, "\t%15s: %s\n", pColName[i], pColText[i]);
        }
        fprintf(stderr, "\n");

        return SQLITE_OK;
    }


    // int (*pCallback)(void *, SQLROW_DATA *)
    // Note: The SqlRow object is released immediately after this
    //      callback returns. So, if it is needed, then it needs
    //      to be retained.
    static
    int             SQLite_step_callback (
        void            *pObj,
        SQLROW_DATA     *pRow
    )
    {
        //SQLITE_DATA     *this = pData;
        uint32_t        i;
        SQLCOL_DATA     *pCol;
        VALUE_DATA      *pVal;
        ASTR_DATA       *pStr = OBJ_NIL;

        if (pRow) {
            for (i=0; i<SqlRow_getSize(pRow); ++i) {
                pCol = SqlRow_Get(pRow, i+1);
                if (pCol) {
                    pVal = SqlCol_getValue(pCol);
                    if (pVal) {
                        pStr = Value_ToString(pVal);
                        if (pStr) {
                            fprintf(
                                    stderr,
                                    "\t%15s: %s\n",
                                    AStr_getData(SqlCol_getName(pCol)),
                                    AStr_getData(pStr)
                            );
                            obj_Release(pStr);
                            pStr = OBJ_NIL;
                        }
                    }
                }
            }
            fprintf(stderr, "\n");
        }

        return SQLITE_OK;
    }


    // int (*pCallback)(void*,int,char**,char**)
    static
    int             SQLite_table_callback (
        void            *pData,
        int             numCols,
        char            **pColText,
        char            **pColName
    )
    {
        //SQLITE_DATA     *this = pData;
        int             i;
        bool            fDisplay = false;
        const
        char            *pName = NULL;
        const
        char            *pTblName = NULL;
        bool            fSqliteName = false;

        // The sqlite_master.tbl_name column holds the name of a table or view that the
        // object is associated with. For a table or view, the tbl_name column is a copy
        // of the name column. For an index, the tbl_name is the name of the table that
        // is indexed. For a trigger, the tbl_name column stores the name of the table or
        // view that causes the trigger to fire.

        for (i=0; i<numCols; ++i) {
            if (((strcmp(pColName[i], "type") == 0) && (strcmp(pColText[i], "table") == 0))) {
                fDisplay = true;
            }
            if ((strcmp(pColName[i], "name") == 0) && (strncmp(pColText[i], "sqlite_", 7) == 0))
                fSqliteName = true;
            if (strcmp(pColName[i], "name") == 0) {
                pName = pColText[i];
            }
            if (strcmp(pColName[i], "tbl_name") == 0) {
                pTblName = pColText[i];
            }
        }
        if (fDisplay) {
            if (pName && !fSqliteName)
                fprintf(stderr, "\tName: %s\n", pName);
            if (pTblName && !fSqliteName)
                fprintf(stderr, "\tTbl_Name: %s\n", pTblName);
        }

        return SQLITE_OK;
    }





    //----------------------------------------------------------------
    //                      Test Open/Close
    //----------------------------------------------------------------

    ERESULT         Test_SQLite_OpenClose (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        SQLITE_DATA     *pObj = OBJ_NIL;
       
        fprintf(stderr, "Performing: %s\n", pTestName);

        pObj = SQLite_Alloc( );
        TestForNotNull(pObj, "Missing Test Alloc() object");
        pObj = SQLite_Init( pObj );
        TestForNotNull(pObj, "Missing Test Init() object");
        if (pObj) {

            //obj_TraceSet(pObj, true);       
            fRc = obj_IsKindOf(pObj, OBJ_IDENT_SQLITE);
            TestForTrue(fRc, "Failed Ident Test");
    #ifdef   SQLITE_MSGS
            SQLite_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
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
    ERESULT         Test_SQLite_Copy01 (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        //int             iRc;
        SQLITE_DATA     *pObj1 = OBJ_NIL;
        SQLITE_DATA     *pObj2 = OBJ_NIL;
    #if defined(SQLITE_JSON_SUPPORT)
        ASTR_DATA       *pStr = OBJ_NIL;
    #endif
       
        fprintf(stderr, "Performing: %s\n", pTestName);

        pObj1 = SQLite_New( );
        TestForNotNull(pObj1, "Missing Test object");
        if (pObj1) {

            //obj_TraceSet(pObj1, true);       
            fRc = obj_IsKindOf(pObj1, OBJ_IDENT_SQLITE);
            TestForTrue(fRc, "Failed Ident Test");
    #ifdef   SQLITE_MSGS
            SQLite_setMsg(pObj1, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
    #endif
            
            // Test assign.
            pObj2 = SQLite_New();
            TestForNotNull(pObj2, "Missing copied object");
            eRc = SQLite_Assign(pObj1, pObj2);
            TestForFalse((ERESULT_FAILED(eRc)), "Assignment failed");

            fRc = obj_IsKindOf(pObj2, OBJ_IDENT_SQLITE);
            TestForTrue(fRc, "Failed Ident Test");
            //iRc = SQLite_Compare(pObj1, pObj2);
            //TestForTrue((0 == iRc), "Failed Compare");
            //TODO: Add More tests here!

            obj_Release(pObj2);
            pObj2 = OBJ_NIL;

            // Test copy.
            pObj2 = SQLite_Copy(pObj1);
            TestForNotNull(pObj2, "Missing copied object");

            fRc = obj_IsKindOf(pObj2, OBJ_IDENT_SQLITE);
            TestForTrue(fRc, "Failed Ident Test");
            //iRc = SQLite_Compare(pObj1, pObj2);
            //TestForTrue((0 == iRc), "Failed Compare");
            //TODO: Add More tests here!

            obj_Release(pObj2);
            pObj2 = OBJ_NIL;

            // Test json support.
    #if defined(SQLITE_JSON_SUPPORT)
            pStr = SQLite_ToJson(pObj1);
            TestForNotNull(pStr, "Missing JSON output");
            fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
            pObj2 = SQLite_NewFromJsonString(pStr);
            TestForNotNull(pObj2, "Missing JSON created object");
            fRc = obj_IsKindOf(pObj2, OBJ_IDENT_SQLITE);
            TestForTrue(fRc, "Failed Ident Test");
            obj_Release(pStr);
            pStr = OBJ_NIL;
            //iRc = SQLite_Compare(pObj1, pObj2);
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

    ERESULT         Test_SQLite_Test01 (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        SQLITE_DATA     *pObj = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
        const
        char            *pDatabasePath = TEST_FILES_DIR "/db/ae.db";
        PATH_DATA       *pPath = OBJ_NIL;
        const
        char            *pSqlA = NULL;
       
        fprintf(stderr, "Performing: %s\n", pTestName);
        TestForNull(pStr, "");

        pPath = Path_NewA(pDatabasePath);
        TestForFalse( (OBJ_NIL == pPath), "" );
        eRc = Path_Clean(pPath, NULL, OBJ_NIL);
        TestForFalse( (ERESULT_FAILED(eRc)), "" );

        pObj = SQLite_NewPath(pPath);
        TestForNotNull(pObj, "");
        if (pObj) {

            //obj_TraceSet(pObj, true);       
            fRc = obj_IsKindOf(pObj, OBJ_IDENT_SQLITE);
            TestForFalse(!fRc, "");
            TestForTrue(fRc, "");
            TestForSuccess("");
    #ifdef   SQLITE_MSGS
            SQLite_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
    #endif
                    
            pSqlA = "SELECT * FROM sqlite_master;";
            fprintf(stderr, "==> SQL: %s\n", pSqlA);
            eRc = SQLite_Exec(pObj, SQLite_dump_callback, NULL, pSqlA);
            TestForFalse( (ERESULT_FAILED(eRc)), "" );

            pSqlA = "SELECT * FROM sqlite_master;";
            fprintf(stderr, "==> TABLE SQL: %s\n", pSqlA);
            eRc = SQLite_Exec(pObj, SQLite_table_callback, NULL, pSqlA);
            TestForFalse( (ERESULT_FAILED(eRc)), "" );

            {
                ASTR_DATA       *pStr = SQLite_ToDebugString(pObj, 4);
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
    //                          Test 2
    //----------------------------------------------------------------

    ERESULT         Test_SQLite_Test02 (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        SQLITE_DATA     *pObj = OBJ_NIL;
        const
        char            *pDatabasePath = TEST_FILES_DIR "/db/ae.db";
        PATH_DATA       *pPath = OBJ_NIL;
        ASTRCARRAY_DATA *pArray = OBJ_NIL;
        int             i;
        ASTRC_DATA      *pStr = OBJ_NIL;
       
        fprintf(stderr, "Performing: %s\n", pTestName);
        TestForNull(pStr, "");

        pPath = Path_NewA(pDatabasePath);
        TestForFalse( (OBJ_NIL == pPath), "" );
        eRc = Path_Clean(pPath, NULL, OBJ_NIL);
        TestForFalse( (ERESULT_FAILED(eRc)), "" );

        pObj = SQLite_NewPath(pPath);
        TestForNotNull(pObj, "");
        if (pObj) {

            //obj_TraceSet(pObj, true);       
            fRc = obj_IsKindOf(pObj, OBJ_IDENT_SQLITE);
            TestForFalse(!fRc, "");
            TestForTrue(fRc, "");
            TestForSuccess("");
    #ifdef   SQLITE_MSGS
            SQLite_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
    #endif
                    
            {
                ASTR_DATA       *pStr = SQLite_ToDebugString(pObj, 4);
                if (pStr) {
                    fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                }
            }

            pArray = SQLite_TableNames(pObj);
            TestForFalse( (OBJ_NIL == pArray), "" );
            fprintf(stderr, "Array Size: %d\n", AStrCArray_getSize(pArray));
            TestForTrue( (1 == AStrCArray_getSize(pArray)), "" );
            for (i=0; i<1; ++i) {
                pStr = AStrCArray_Get(pArray, i+1);
                if (pStr) {
                    fprintf(stderr, "\t%s\n", AStrC_getData(pStr));
                }
            }
            obj_Release(pArray);
            pArray = OBJ_NIL;

            obj_Release(pObj);
            pObj = OBJ_NIL;
        }

        obj_Release(pPath);
        pPath = OBJ_NIL;

        fprintf(stderr, "...%s completed.\n\n\n", pTestName);
        return eRc;
    }



    //----------------------------------------------------------------
    //                          Test 3
    //----------------------------------------------------------------

    ERESULT         Test_SQLite_Test03 (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        SQLITE_DATA     *pObj = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
        const
        char            *pDatabasePath = TEST_FILES_DIR "/db/ae.db";
        PATH_DATA       *pPath = OBJ_NIL;
        uint32_t        count;
       
        fprintf(stderr, "Performing: %s\n", pTestName);
        TestForNull(pStr, "");

        pPath = Path_NewA(pDatabasePath);
        TestForFalse( (OBJ_NIL == pPath), "" );
        eRc = Path_Clean(pPath, NULL, OBJ_NIL);
        TestForFalse( (ERESULT_FAILED(eRc)), "" );

        pObj = SQLite_NewPath(pPath);
        TestForNotNull(pObj, "");
        if (pObj) {

            //obj_TraceSet(pObj, true);       
            fRc = obj_IsKindOf(pObj, OBJ_IDENT_SQLITE);
            TestForFalse(!fRc, "");
            TestForTrue(fRc, "");
            TestForSuccess("");
    #ifdef   SQLITE_MSGS
            SQLite_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
    #endif
                    
            count = SQLite_TableRowCount(pObj, "Items");
            fprintf(stderr, "Count: %d\n", count);
            TestForTrue( (31 == count), "" );

            {
                ASTR_DATA       *pStr = SQLite_ToDebugString(pObj, 4);
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

    ERESULT         Test_SQLite_Test04 (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        SQLITE_DATA     *pObj = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
        int             iRc;
        static
        SQLCOL_STRUCT     rowCols[] = {
            {
                "rowId",                                // Name
                "Row Identifier",                       // Description
                "Trades",                               // Table Name
                "Accts",                                // Database Name
                SQLCOL_TYPE_INTEGER,                    // Type
                1,                                      // Key Sequence
                0,                                      // Decimal Places
                1,                                      // Column Sequence Number
                0,                                      // Length
                0,                                      // Minimum Length
                SQLCOL_FLAG_UNIQUE                      // Flags
                | SQLCOL_FLAG_NOT_NULL
                | SQLCOL_FLAG_AUTO_INC
                | SQLCOL_FLAG_PRIM_KEY,
                NULL,                                   // Default Value
                NULL                                    // Check Expression
            },
            {
                "trdSymbol",                            // Name
                "Trade Symbol",                         // Description
                "Trades",                               // Table Name
                "Accts",                                // Database Name
                SQLCOL_TYPE_NVARCHAR,                   // Type
                0,                                      // Key Sequence
                0,                                      // Decimal Places
                3,                                      // Column Sequence Number
                20,                                     // Length
                0,                                      // Minimum Length
                SQLCOL_FLAG_UNIQUE                      // Flags
                | SQLCOL_FLAG_NOT_NULL,
                NULL,                                   // Default Value
                NULL                                    // Check Expression
            },
            {
                "trdDate",                              // Name
                "Trade Date",                           // Description
                "Trades",                               // Table Name
                "Accts",                                // Database Name
                SQLCOL_TYPE_DATE,                       // Type
                0,                                      // Key Sequence
                0,                                      // Decimal Places
                3,                                      // Column Sequence Number
                0,                                      // Length
                0,                                      // Minimum Length
                SQLCOL_FLAG_NOT_NULL,                   // Flags
                NULL,                                   // Default Value
                NULL                                    // Check Expression
            },
            {
                "trdNum",                               // Name
                "Trade Number",                         // Description
                "Trades",                               // Table Name
                "Accts",                                // Database Name
                SQLCOL_TYPE_INTEGER,                    // Type
                0,                                      // Key Sequence
                0,                                      // Decimal Places
                3,                                      // Column Sequence Number
                0,                                      // Length
                0,                                      // Minimum Length
                SQLCOL_FLAG_NOT_NULL,                   // Flags
                NULL,                                   // Default Value
                NULL                                    // Check Expression
            },
            {
                "trdRef",                               // Name
                "Trade Reference",                      // Description
                "Trades",                               // Table Name
                "Accts",                                // Database Name
                SQLCOL_TYPE_NVARCHAR,                   // Type
                0,                                      // Key Sequence
                0,                                      // Decimal Places
                3,                                      // Column Sequence Number
                20,                                     // Length
                0,                                      // Minimum Length
                SQLCOL_FLAG_UNIQUE                      // Flags
                | SQLCOL_FLAG_NOT_NULL,
                NULL,                                   // Default Value
                NULL                                    // Check Expression
            },
            {
                "trdCls",                               // Name
                "Trade Closes",                         // Description
                "Trades",                               // Table Name
                "Accts",                                // Database Name
                SQLCOL_TYPE_NVARCHAR,                   // Type
                0,                                      // Key Sequence
                0,                                      // Decimal Places
                3,                                      // Column Sequence Number
                20,                                     // Length
                0,                                      // Minimum Length
                SQLCOL_FLAG_UNIQUE                      // Flags
                | SQLCOL_FLAG_NOT_NULL,
                NULL,                                   // Default Value
                NULL                                    // Check Expression
            },
            {
                "trdOrder",                             // Name
                "Trade Order",                          // Description
                "Trades",                               // Table Name
                "Accts",                                // Database Name
                SQLCOL_TYPE_NVARCHAR,                   // Type
                0,                                      // Key Sequence
                0,                                      // Decimal Places
                3,                                      // Column Sequence Number
                100,                                    // Length
                0,                                      // Minimum Length
                SQLCOL_FLAG_UNIQUE                      // Flags
                | SQLCOL_FLAG_NOT_NULL,
                NULL,                                   // Default Value
                NULL                                    // Check Expression
            },
            {
                "trdStop",                              // Name
                "Trade Stop Price",                     // Description
                "Trades",                               // Table Name
                "Accts",                                // Database Name
                SQLCOL_TYPE_INTEGER,                    // Type
                0,                                      // Key Sequence
                0,                                      // Decimal Places
                3,                                      // Column Sequence Number
                0,                                      // Length
                0,                                      // Minimum Length
                SQLCOL_FLAG_NOT_NULL,                   // Flags
                NULL,                                   // Default Value
                NULL                                    // Check Expression
            },
        };
       
        fprintf(stderr, "Performing: %s\n", pTestName);
        TestForNull(pStr, "");

        pObj = SQLite_New( );
        TestForNotNull(pObj, "");
        if (pObj) {

            //obj_TraceSet(pObj, true);       
            fRc = obj_IsKindOf(pObj, OBJ_IDENT_SQLITE);
            TestForFalse(!fRc, "");
            TestForTrue(fRc, "");
            TestForSuccess("");
    #ifdef   SQLITE_MSGS
            SQLite_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
    #endif
                    
            {
                ASTR_DATA       *pStr = SQLite_ToDebugString(pObj, 4);
                if (pStr) {
                    fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                }
            }

            obj_Release(pObj);
            pObj = OBJ_NIL;
        }

        pStr = SQLite_SQL_ColCreate(&rowCols[0]);
        TestForFalse( (OBJ_NIL == pStr), "" );
        fprintf(stderr, "\t0 - %s\n", AStr_getData(pStr));
        iRc = AStr_CompareA(pStr, "rowId INTEGER AUTOINCREMENT NOT NULL UNIQUE PRIMARY KEY");
        TestForTrue( (0 == iRc), "" );
        obj_Release(pStr);
        pStr = OBJ_NIL;

        pStr = SQLite_SQL_ColCreate(&rowCols[1]);
        TestForFalse( (OBJ_NIL == pStr), "" );
        fprintf(stderr, "\t1 - %s\n", AStr_getData(pStr));
        iRc = AStr_CompareA(pStr, "trdSymbol NVARCHAR(20) NOT NULL UNIQUE");
        TestForTrue( (0 == iRc), "" );
        obj_Release(pStr);
        pStr = OBJ_NIL;

        pStr = SQLite_SQL_ColCreate(&rowCols[2]);
        TestForFalse( (OBJ_NIL == pStr), "" );
        fprintf(stderr, "\t2 - %s\n", AStr_getData(pStr));
        iRc = AStr_CompareA(pStr, "trdDate DATE NOT NULL");
        TestForTrue( (0 == iRc), "" );
        obj_Release(pStr);
        pStr = OBJ_NIL;

        pStr = SQLite_SQL_ColCreate(&rowCols[3]);
        TestForFalse( (OBJ_NIL == pStr), "" );
        fprintf(stderr, "\t3 - %s\n", AStr_getData(pStr));
        iRc = AStr_CompareA(pStr, "trdNum INTEGER NOT NULL");
        TestForTrue( (0 == iRc), "" );
        obj_Release(pStr);
        pStr = OBJ_NIL;

        fprintf(stderr, "...%s completed.\n\n\n", pTestName);
        return eRc;
    }



    //----------------------------------------------------------------
    //                          Test 5
    //----------------------------------------------------------------

    ERESULT         Test_SQLite_Test05 (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        SQLITE_DATA     *pObj = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
        const
        char            *pDatabasePath = TEST_FILES_DIR "/db/ae.db";
        PATH_DATA       *pPath = OBJ_NIL;
        const
        char            *pSqlA = NULL;
       
        fprintf(stderr, "Performing: %s\n", pTestName);
        TestForNull(pStr, "");

        pPath = Path_NewA(pDatabasePath);
        TestForFalse( (OBJ_NIL == pPath), "" );
        eRc = Path_Clean(pPath, NULL, OBJ_NIL);
        TestForFalse( (ERESULT_FAILED(eRc)), "" );

        pObj = SQLite_NewPath(pPath);
        TestForNotNull(pObj, "");
        if (pObj) {

            //obj_TraceSet(pObj, true);       
            fRc = obj_IsKindOf(pObj, OBJ_IDENT_SQLITE);
            TestForFalse(!fRc, "");
            TestForTrue(fRc, "");
            TestForSuccess("");
    #ifdef   SQLITE_MSGS
            SQLite_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
    #endif
                    
            pSqlA = "SELECT * FROM Items;";
            fprintf(stderr, "Exec() ==> SQL: %s\n", pSqlA);
            eRc = SQLite_Exec(pObj, SQLite_dump_callback, NULL, pSqlA);
            TestForFalse( (ERESULT_FAILED(eRc)), "" );

            pSqlA = "SELECT * FROM Items;";
            fprintf(stderr, "Step() ==> SQL: %s\n", pSqlA);
            eRc = SQLite_Step(pObj, SQLite_step_callback, NULL, pSqlA, OBJ_NIL);
            TestForFalse( (ERESULT_FAILED(eRc)), "" );

            {
                ASTR_DATA       *pStr = SQLite_ToDebugString(pObj, 4);
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
    //                          Test 6
    //----------------------------------------------------------------

    ERESULT         Test_SQLite_Test06 (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        SQLITE_DATA     *pObj = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
        const
        char            *pDatabasePath = TEST_FILES_DIR "/db/ae.db";
        PATH_DATA       *pPath = OBJ_NIL;
        const
        char            *pSqlA = NULL;
       
        fprintf(stderr, "Performing: %s\n", pTestName);
        TestForNull(pStr, "");

        pPath = Path_NewA(pDatabasePath);
        TestForFalse( (OBJ_NIL == pPath), "" );
        eRc = Path_Clean(pPath, NULL, OBJ_NIL);
        TestForFalse( (ERESULT_FAILED(eRc)), "" );

        pObj = SQLite_NewPath(pPath);
        TestForNotNull(pObj, "");
        if (pObj) {

            //obj_TraceSet(pObj, true);       
            fRc = obj_IsKindOf(pObj, OBJ_IDENT_SQLITE);
            TestForFalse(!fRc, "");
            TestForTrue(fRc, "");
            TestForSuccess("");
    #ifdef   SQLITE_MSGS
            SQLite_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
    #endif
                    
            pSqlA = "SELECT * FROM Items;";
            fprintf(stderr, "Exec() ==> SQL: %s\n", pSqlA);
            eRc = SQLite_Exec(pObj, SQLite_dump_callback, NULL, pSqlA);
            TestForFalse( (ERESULT_FAILED(eRc)), "" );

            pSqlA = "SELECT * FROM Items;";
            fprintf(stderr, "Step() ==> SQL: %s\n", pSqlA);
            eRc = SQLite_Step(pObj, SQLite_step_callback, NULL, pSqlA, OBJ_NIL);
            TestForFalse( (ERESULT_FAILED(eRc)), "" );

            {
                ASTR_DATA       *pStr = SQLite_ToDebugString(pObj, 4);
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
    //                          Test 7
    //----------------------------------------------------------------

    ERESULT         Test_SQLite_Test07 (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        SQLITE_DATA     *pObj = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
       
        fprintf(stderr, "Performing: %s\n", pTestName);
        TestForNull(pStr, "");

        pObj = SQLite_New( );
        TestForNotNull(pObj, "");
        if (pObj) {

            //obj_TraceSet(pObj, true);       
            fRc = obj_IsKindOf(pObj, OBJ_IDENT_SQLITE);
            TestForFalse(!fRc, "");
            TestForTrue(fRc, "");
            TestForSuccess("");
    #ifdef   SQLITE_MSGS
            SQLite_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
    #endif
                    
            {
                ASTR_DATA       *pStr = SQLite_ToDebugString(pObj, 4);
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

    ERESULT         Test_SQLite_Test08 (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        SQLITE_DATA     *pObj = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
       
        fprintf(stderr, "Performing: %s\n", pTestName);
        TestForNull(pStr, "");

        pObj = SQLite_New( );
        TestForNotNull(pObj, "");
        if (pObj) {

            //obj_TraceSet(pObj, true);       
            fRc = obj_IsKindOf(pObj, OBJ_IDENT_SQLITE);
            TestForFalse(!fRc, "");
            TestForTrue(fRc, "");
            TestForSuccess("");
    #ifdef   SQLITE_MSGS
            SQLite_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
    #endif
                    
            {
                ASTR_DATA       *pStr = SQLite_ToDebugString(pObj, 4);
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

    ERESULT         Test_SQLite_Test09 (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        SQLITE_DATA     *pObj = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
       
        fprintf(stderr, "Performing: %s\n", pTestName);
        TestForNull(pStr, "");

        pObj = SQLite_New( );
        TestForNotNull(pObj, "");
        if (pObj) {

            //obj_TraceSet(pObj, true);       
            fRc = obj_IsKindOf(pObj, OBJ_IDENT_SQLITE);
            TestForFalse(!fRc, "");
            TestForTrue(fRc, "");
            TestForSuccess("");
    #ifdef   SQLITE_MSGS
            SQLite_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
    #endif
                    
            {
                ASTR_DATA       *pStr = SQLite_ToDebugString(pObj, 4);
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
        TestExec("OpenClose", Test_SQLite_OpenClose, NULL,   NULL);
#ifdef  TEST_ASSIGN_COPY
        TestExec("Copy01", Test_SQLite_Copy01,       NULL,   NULL);
#endif
        TestExec("Test01", Test_SQLite_Test01,       NULL,   NULL);
        TestExec("Test02", Test_SQLite_Test02,       NULL,   NULL);
        TestExec("Test03", Test_SQLite_Test03,       NULL,   NULL);
        TestExec("Test04", Test_SQLite_Test04,       NULL,   NULL);
        TestExec("Test05", Test_SQLite_Test05,       NULL,   NULL);
        TestExec("Test06", Test_SQLite_Test06,       NULL,   NULL);
        TestExec("Test07", Test_SQLite_Test07,       NULL,   NULL);
        TestExec("Test08", Test_SQLite_Test08,       NULL,   NULL);
        TestExec("Test09", Test_SQLite_Test09,       NULL,   NULL);

        obj_Release(pTest);
        pTest = OBJ_NIL;

        // Return to Operating System.
        return 0;
    }


#ifdef  __cplusplus
}
#endif

