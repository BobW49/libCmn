// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Program Generation Node (NodePgm)  Test Program
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
#include    <NodePgm_internal.h>
#include    <hjson.h>
#include    <JsonIn.h>
#include    <SrcErrors.h>
#include    <szTbl.h>



#ifdef  __cplusplus
extern "C" {
#endif
        


ERESULT_DATA *  InputStrToJSON(
    const
    char            *pStrA,
    NODE_DATA       **ppNodes
)
{
    ERESULT_DATA    *pErr = OBJ_NIL;
    HJSON_DATA      *pObj = OBJ_NIL;
    NODEHASH_DATA   *pHash;
    NODE_DATA       *pFileNode = OBJ_NIL;

    // Do initialization.
#ifdef NDEBUG
#else
    if (NULL == pStrA) {
        DEBUG_BREAK();
        pErr = eResult_NewStrA(ERESULT_INVALID_PARAMETER,
                                    "Error: Missing String!");
        return pErr;
    }
#endif

    pObj = hjson_NewA(pStrA, 4);
    if (pObj) {
        pFileNode = hjson_ParseFileValue(pObj);
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    SrcErrors_ExitOnFatal(OBJ_NIL);

    if (pFileNode) {
        pHash = Node_getData(pFileNode);
        if (OBJ_NIL == pHash) {
            fprintf(stderr, "ERROR - No JSON Nodes to process\n\n\n");
            exit(12);
        }
        if (!obj_IsKindOf(pHash, OBJ_IDENT_NODEHASH)) {
            fprintf(stderr, "ERROR - Missing JSON Hash to process\n\n\n");
            exit(12);
        }
    }
    else {
        fprintf(stderr, "ERROR - No JSON Nodes to process\n\n\n");
        exit(12);
    }

    // Return to caller.
    if (ppNodes) {
        *ppNodes = pFileNode;
    }
    return pErr;
}




    //----------------------------------------------------------------
    //                      Test Open/Close
    //----------------------------------------------------------------

    ERESULT         Test_NodePgm_OpenClose (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        NODEPGM_DATA    *pObj = OBJ_NIL;
        bool            fRc;
       
        fprintf(stderr, "Performing: %s\n", pTestName);

        pObj = NodePgm_Alloc( );
        TestForNotNull(pObj, "Missing Test Alloc() object");
        pObj = NodePgm_Init( pObj );
        TestForNotNull(pObj, "Missing Test Init() object");
        if (pObj) {

            //obj_TraceSet(pObj, true);       
            fRc = obj_IsKindOf(pObj, OBJ_IDENT_NODEPGM);
            TestForTrue(fRc, "Failed Ident Test");
    #ifdef   NODEPGM_MSGS
            NodePgm_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
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

    ERESULT         Test_NodePgm_Copy01 (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        NODEPGM_DATA    *pObj1 = OBJ_NIL;
        NODEPGM_DATA    *pObj2 = OBJ_NIL;
        bool            fRc;
    #if defined(NODEPGM_JSON_SUPPORT) && defined(XYZZY)
        ASTR_DATA       *pStr = OBJ_NIL;
    #endif
        //int             iRc;
       
        fprintf(stderr, "Performing: %s\n", pTestName);

        pObj1 = NodePgm_New( );
        TestForNotNull(pObj1, "Missing Test object");
        if (pObj1) {

            //obj_TraceSet(pObj1, true);       
            fRc = obj_IsKindOf(pObj1, OBJ_IDENT_NODEPGM);
            TestForTrue(fRc, "Failed Ident Test");
    #ifdef   NODEPGM_MSGS
            NodePgm_setMsg(pObj1, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
    #endif
            
            // Test assign.
            pObj2 = NodePgm_New();
            TestForNotNull(pObj2, "Missing copied object");
            //eRc = NodePgm_Assign(pObj1, pObj2);
            TestForFalse((ERESULT_FAILED(eRc)), "Assignment failed");

            fRc = obj_IsKindOf(pObj2, OBJ_IDENT_NODEPGM);
            TestForTrue(fRc, "Failed Ident Test");
            //iRc = NodePgm_Compare(pObj1, pObj2);
            //TestForTrue((0 == iRc), "Failed Compare");
            //TODO: Add More tests here!

            obj_Release(pObj2);
            pObj2 = OBJ_NIL;

            // Test copy.
            //pObj2 = NodePgm_Copy(pObj1);
            TestForNotNull(pObj2, "Missing copied object");

            fRc = obj_IsKindOf(pObj2, OBJ_IDENT_NODEPGM);
            TestForTrue(fRc, "Failed Ident Test");
            //iRc = NodePgm_Compare(pObj1, pObj2);
            //TestForTrue((0 == iRc), "Failed Compare");
            //TODO: Add More tests here!

            obj_Release(pObj2);
            pObj2 = OBJ_NIL;

            // Test json support.
    #if defined(NODEPGM_JSON_SUPPORT) && defined(XYZZY)
            pStr = NodePgm_ToJson(pObj1);
            TestForNotNull(pStr, "Missing JSON output");
            fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
            pObj2 = NodePgm_NewFromJsonString(pStr);
            TestForNotNull(pObj2, "Missing JSON created object");
            fRc = obj_IsKindOf(pObj2, OBJ_IDENT_NODEPGM);
            TestForTrue(fRc, "Failed Ident Test");
            obj_Release(pStr);
            pStr = OBJ_NIL;
            //iRc = NodePgm_Compare(pObj1, pObj2);
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

    ERESULT         Test_NodePgm_Test01 (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        ERESULT_DATA    *pErr = OBJ_NIL;
        bool            fRc;
        NODEPGM_DATA    *pObj = OBJ_NIL;
        NODE_DATA       *pNodes = OBJ_NIL;
        NODEHASH_DATA   *pHash = OBJ_NIL;
        ASTRCARRAY_DATA *pStrCArray = OBJ_NIL;
        ASTRC_DATA      *pStrC = OBJ_NIL;
        const
        char            *pGoodJsonObject1 =
            "{name:\"genMake\", "
            "\"deps\":[\"Cmn\"], "
            "\"hdrs\":[\"genMake.h\"], "
            "\"main\":\"mainProgram.c\""
            "}\n";
        bool            fDumpNodes = true;
       
        fprintf(stderr, "Performing: %s\n", pTestName);

        // Process the JSON data.
        pErr = InputStrToJSON(pGoodJsonObject1, &pNodes);
        TestForTrue( (OBJ_NIL == pErr), "" );
        TestForFalse( (OBJ_NIL == pNodes), "" );
        TestForTrue( (obj_IsKindOf(pNodes, OBJ_IDENT_NODE)), "" );
        pHash = Node_getData(pNodes);
        TestForFalse( (OBJ_NIL == pHash), "" );
        TestForTrue( (obj_IsKindOf(pHash, OBJ_IDENT_NODEHASH)), "" );

        if (fDumpNodes) {
            ASTR_DATA       *pWrk = OBJ_NIL;
            pWrk = Node_ToDebugString(pNodes, 0);
            fprintf(stderr, "Parsed JSON:\n%s\n\n\n", AStr_getData(pWrk));
            obj_Release(pWrk);
            pWrk = OBJ_NIL;
        }

        // Parse the Object.
        //obj_TraceSet(pBase, true);
        pErr = NodePgm_Parse(pNodes, &pObj);
        if (pErr) {
            fprintf(stderr, "%s\n", eResult_getErrorA(pErr));
        }
        //pObj = NodePgm_New( );
        TestForNotNull(pObj, "");
        if (pObj) {

            //obj_TraceSet(pObj, true);       
            fRc = obj_IsKindOf(pObj, OBJ_IDENT_NODEPGM);
            TestForFalse(!fRc, "");
            TestForTrue(fRc, "");
            TestForSuccess("");
    #ifdef   NODEPGM_MSGS
            NodePgm_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
    #endif
                    
            // Display the Output.
            {
                fprintf(stderr, "===> NodeObj:\n\n");
                ASTR_DATA   *pStr = NodePgm_ToDebugString(pObj, 0);
                fprintf(stderr, "%s\n", AStr_getData(pStr));
                obj_Release(pStr);
                //pStr = OBJ_NIL;
            }

            // Validate the output.
            pStrC = NodePgm_getName(pObj);
            TestForFalse( (OBJ_NIL == pStrC), "" );
            TestForTrue((0 == AStrC_CompareA(pStrC,"genMake")), "");
            pStrCArray = NodePgm_getArches(pObj);
            TestForFalse( (OBJ_NIL == pStrCArray), "" );
            if (pStrCArray) {
                TestForTrue((0 == AStrCArray_getSize(pStrCArray)), "");
            }
            pStrCArray = NodePgm_getOSs(pObj);
            TestForFalse( (OBJ_NIL == pStrCArray), "" );
            if (pStrCArray) {
                TestForTrue((0 == AStrCArray_getSize(pStrCArray)), "");
            }
            pStrCArray = NodePgm_getDeps(pObj);
            TestForFalse( (OBJ_NIL == pStrCArray), "" );
            if (pStrCArray) {
                TestForTrue((1 == AStrCArray_getSize(pStrCArray)), "");
                pStrC = AStrCArray_Get(pStrCArray, 1);
                fprintf(stderr, "Deps1: %s\n", AStrC_getData(pStrC));
                TestForTrue((0 == AStrC_CompareA(pStrC,"Cmn")), "");
            }
            pStrCArray = NodePgm_getHdrs(pObj);
            TestForFalse( (OBJ_NIL == pStrCArray), "" );
            if (pStrCArray) {
                TestForTrue((2 == AStrCArray_getSize(pStrCArray)), "");
                pStrC = AStrCArray_Get(pStrCArray, 1);
                fprintf(stderr, "Hdrs1: %s\n", AStrC_getData(pStrC));
                TestForTrue((0 == AStrC_CompareA(pStrC,"$(SRCDIR)/genMake.h")), "");
                pStrC = AStrCArray_Get(pStrCArray, 2);
                fprintf(stderr, "Hdrs2: %s\n", AStrC_getData(pStrC));
                TestForTrue((0 ==
                               AStrC_CompareA(pStrC,"$(LIBCMN_BASE)/include/cmn_defs.h")), "");
            }
            pStrC = NodePgm_getMain(pObj);
            TestForFalse( (OBJ_NIL == pStrC), "" );
            TestForTrue((0 == AStrC_CompareA(pStrC,"mainProgram.c")), "");

            obj_Release(pNodes);
            pNodes = OBJ_NIL;
             obj_Release(pObj);
            pObj = OBJ_NIL;
        }

        fprintf(stderr, "...%s completed.\n\n\n", pTestName);
        return eRc;
    }



    //----------------------------------------------------------------
    //                          Test 2
    //----------------------------------------------------------------

    ERESULT         Test_NodePgm_Test02 (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        int             iRc;
        NODEPGM_DATA    *pObj = OBJ_NIL;
        ERESULT_DATA    *pErr = OBJ_NIL;
        DICT_DATA       *pDict = OBJ_NIL;
        NODE_DATA       *pNodes = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
        bool            fDump = true;
        int             offset = 0;
        uint32_t        i;
        const
        char            *pChr;
       
        const
        char            *pJsonObject =
            "{name:\"genMake\", "
            "\"deps\":[Cmn], "
            "}\n";
        const
        char            *pGenCheck =
        //"# Generated file - edits may be discarded!\n"
        //"# (11/30/2019  4:09:40.000)\n\n\n"
        ".DEFAULT_GOAL := all\n"
        "SHELL=/bin/sh\n\n"
        "PGMNAM=genMake\n"
        "SYS=macos\n"
        "ARCH=x86_64\n"
        "BUILD=./.build\n"
        "BASE_OBJ = $(BUILD)/$(PGMNAM)/$(SYS)/$(ARCH)\n"
        "SRCDIR = ./src\n"
        "TEST_SRC = ./tests\n"
        "INSTALL_BASE = $(HOME)/Support/bin/$(ARCH)\n"
        "LIB_BASE = $(HOME)/git/lib/$(SYS)/$(ARCH)\n\n"

        "CFLAGS += -g -Werror -I$(SRCDIR)\n"
        "ifdef  NDEBUG\n"
        "CFLAGS += -DNDEBUG\n"
        "else   #DEBUG\n"
        "CFLAGS += -D_DEBUG\n"
        "endif  #NDEBUG\n"
        "CFLAGS += -D__MACOS64_ENV__\n"
        "CFLAGS_LIBS = \n"
        "# libCmn\n"
        "LIBCMN_BASE = $(LIB_BASE)/libCmn\n"
        "CFLAGS += -I$(LIBCMN_BASE)/include\n"
        "CFLAGS_LIBS += -lCmn -L$(LIBCMN_BASE)\n"
        "CFLAGS_TEST = -I$(TEST_SRC) $(CFLAGS_LIBS) -lcurses -lsqlite3\n\n"
        
        "LIBOBJ = $(BASE_OBJ)\n"
        "ifdef  NDEBUG\n"
        "LIB_FILENAME=$(PGMNAM)R.a\n"
        "OBJDIR = $(LIBOBJ)/o/r\n"
        "else   #DEBUG\n"
        "LIB_FILENAME=$(PGMNAM)D.a\n"
        "OBJDIR = $(LIBOBJ)/o/d\n"
        "endif  #NDEBUG\n"
        "TEST_OBJ = $(OBJDIR)/obj\n"
        "TEST_BIN = $(OBJDIR)/bin\n"
        "LIB_PATH = $(LIBOBJ)/$(LIB_FILENAME)\n\n"
        
        ".SUFFIXES:\n"
        ".SUFFIXES: .asm .c .cpp .o\n\n"
        
        "OBJS =\n\n"
        "TESTS =\n\n\n";

        fprintf(stderr, "Performing: %s\n", pTestName);

        pErr = InputStrToJSON(pJsonObject, &pNodes);
        eResult_Fprint(pErr, stderr);
        TestForTrue( (OBJ_NIL == pErr), "" );
        TestForFalse( (OBJ_NIL == pNodes), "" );

        pDict = Dict_New();
        TestForNotNull(pDict, "");
        eRc = Dict_Defaults(pDict);
        TestForFalse( (ERESULT_FAILED(eRc)), "" );

        pObj = NodePgm_New( );
        TestForNotNull(pObj, "");
        if (pObj) {

            //obj_TraceSet(pObj, true);       
            fRc = obj_IsKindOf(pObj, OBJ_IDENT_NODEPGM);
            TestForFalse(!fRc, "");
            TestForTrue(fRc, "");
            TestForSuccess("");
    #ifdef   NODEPGM_MSGS
            NodePgm_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
    #endif
                    
            {
                ASTR_DATA       *pStr = NodePgm_ToDebugString(pObj, 4);
                if (pStr) {
                    fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                }
            }

            pErr = NodeBase_Parse(pNodes, (NODEBASE_DATA **)&pObj);
            eResult_Fprint(pErr, stderr);
            TestForNull(pErr, "");
            if (fDump) {
                ASTR_DATA       *pWrk = OBJ_NIL;
                pWrk = NodePgm_ToDebugString(pObj, 0);
                fprintf(stderr, "\n====> TSTA Input:\n%s\n\n\n", AStr_getData(pWrk));
                obj_Release(pWrk);
                pWrk = OBJ_NIL;
            }

            pStr = NodePgm_GenMacBegin(pObj, pDict);
            TestForNotNull(pStr, "");

            if (pStr && fDump) {
                fprintf(stderr, "0         1         2         3\n");
                fprintf(stderr, "0123456789012345678901234567890\n");
                fprintf(stderr, "Generated:\n%s...End of Generated\n\n", AStr_getData(pStr));
            }

            // Skip first 3 lines of output.
            pChr = AStr_getData(pStr);
            for (i=0; i<3; i++) {
                while (*pChr && (*pChr != '\n')) {
                    pChr++;
                }
                pChr++;
            }

            // Compare the remainder.
            iRc = str_CompareSpcl(pChr, pGenCheck, &offset);
            if (iRc) {
                fprintf(stderr, "Compare offset: %d\n", offset);
            }
            TestForTrue((0 == iRc), "");

            obj_Release(pStr);
            obj_Release(pDict);
            obj_Release(pNodes);

            obj_Release(pObj);
            pObj = OBJ_NIL;
        }

        fprintf(stderr, "...%s completed.\n\n\n", pTestName);
        return eRc;
    }



    //----------------------------------------------------------------
    //                          Test 3
    //----------------------------------------------------------------

    ERESULT         Test_NodePgm_Test03 (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        NODEPGM_DATA    *pObj = OBJ_NIL;
        ERESULT_DATA    *pErr = OBJ_NIL;
        DICT_DATA       *pDict = OBJ_NIL;
        NODE_DATA       *pNodes = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
        bool            fDump = true;
        int             iRc;
        int             offset = 0;
        uint32_t        i;
        const
        char            *pChr;
       
        const
        char            *pJsonObject =
            "{name:\"genMake\", "
            "\"deps\":[Cmn] "
            //"\"hdrs\":[\"cmn_defs.h\"] "
            "}\n";
        const
        char            *pGenCheck =
        //"# Generated file - edits may be discarded!\n"
        //"# (11/30/2019  4:09:40.000)\n\n\n"
        ".DEFAULT_GOAL := all\n"
        "SHELL=/bin/sh\n\n"
        "PGMNAM=genMake\n"
        "SYS=macos\n"
        "ARCH=x86_64\n"
        "BUILD=./.build\n"
        "BASE_OBJ = $(BUILD)/$(PGMNAM)/$(SYS)/$(ARCH)\n"
        "SRCDIR = ./src\n"
        "TEST_SRC = ./tests\n"
        "INSTALL_BASE = $(HOME)/Support/bin/$(ARCH)\n"
        "LIB_BASE = $(HOME)/git/lib/$(SYS)/$(ARCH)\n\n"
        
        "CFLAGS += -g -Werror -I$(SRCDIR)\n"
        "ifdef  NDEBUG\n"
        "CFLAGS += -DNDEBUG\n"
        "else   #DEBUG\n"
        "CFLAGS += -D_DEBUG\n"
        "endif  #NDEBUG\n"
        "CFLAGS += -D__MACOS64_ENV__\n"
        "CFLAGS_LIBS = \n"
        "# libCmn\n"
        "LIBCMN_BASE = $(LIB_BASE)/libCmn\n"
        "CFLAGS += -I$(LIBCMN_BASE)/include\n"
        "CFLAGS_LIBS += -lCmn -L$(LIBCMN_BASE)\n"
        "CFLAGS_TEST = -I$(TEST_SRC) $(CFLAGS_LIBS) -lcurses -lsqlite3\n\n"
        
        "LIBOBJ = $(BASE_OBJ)\n"
        "ifdef  NDEBUG\n"
        "LIB_FILENAME=$(PGMNAM)R.a\n"
        "OBJDIR = $(LIBOBJ)/o/r\n"
        "else   #DEBUG\n"
        "LIB_FILENAME=$(PGMNAM)D.a\n"
        "OBJDIR = $(LIBOBJ)/o/d\n"
        "endif  #NDEBUG\n"
        "TEST_OBJ = $(OBJDIR)/obj\n"
        "TEST_BIN = $(OBJDIR)/bin\n"
        "LIB_PATH = $(LIBOBJ)/$(LIB_FILENAME)\n\n"
        
        ".SUFFIXES:\n"
        ".SUFFIXES: .asm .c .cpp .o\n\n"
        
        "OBJS =\n\n"
        "TESTS =\n\n\n";

        fprintf(stderr, "Performing: %s\n", pTestName);

        pErr = InputStrToJSON(pJsonObject, &pNodes);
        eResult_Fprint(pErr, stderr);
        TestForTrue( (OBJ_NIL == pErr), "" );
        TestForFalse( (OBJ_NIL == pNodes), "" );

        pDict = Dict_New();
        TestForNotNull(pDict, "");
        eRc = Dict_Defaults(pDict);
        TestForFalse( (ERESULT_FAILED(eRc)), "" );

        pObj = NodePgm_New( );
        TestForNotNull(pObj, "");
        if (pObj) {

            //obj_TraceSet(pObj, true);       
            fRc = obj_IsKindOf(pObj, OBJ_IDENT_NODEPGM);
            TestForFalse(!fRc, "");
            TestForTrue(fRc, "");
            TestForSuccess("");
    #ifdef   NODEPGM_MSGS
            NodePgm_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
    #endif
                    
            {
                ASTR_DATA       *pStr = NodePgm_ToDebugString(pObj, 4);
                if (pStr) {
                    fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                }
            }

            pErr = NodeBase_Parse(pNodes, (NODEBASE_DATA **)&pObj);
            eResult_Fprint(pErr, stderr);
            TestForNull(pErr, "");
            if (fDump) {
                ASTR_DATA       *pWrk = OBJ_NIL;
                pWrk = NodePgm_ToDebugString(pObj, 0);
                fprintf(stderr, "\n====> TSTA Input:\n%s\n\n\n", AStr_getData(pWrk));
                obj_Release(pWrk);
                pWrk = OBJ_NIL;
            }

            pStr = NodePgm_GenMacBegin(pObj, pDict);
            TestForNotNull(pStr, "");

            if (pStr && fDump) {
                fprintf(stderr, "0         1         2         3\n");
                fprintf(stderr, "0123456789012345678901234567890\n");
                fprintf(stderr, "Generated:\n%s...End of Generated\n\n", AStr_getData(pStr));
            }

            // Skip first 3 lines of output.
            pChr = AStr_getData(pStr);
            for (i=0; i<3; i++) {
                while (*pChr && (*pChr != '\n')) {
                    pChr++;
                }
                pChr++;
            }

            // Compare the remainder.
            iRc = str_CompareSpcl(pChr, pGenCheck, &offset);
            if (iRc) {
                fprintf(stderr, "Compare offset: %d\n", offset);
            }
            TestForTrue((0 == iRc), "");

            obj_Release(pStr);
            obj_Release(pDict);
            obj_Release(pNodes);

            obj_Release(pObj);
            pObj = OBJ_NIL;
        }

        fprintf(stderr, "...%s completed.\n\n\n", pTestName);
        return eRc;
    }



    //----------------------------------------------------------------
    //                          Test 4
    //----------------------------------------------------------------

    ERESULT         Test_NodePgm_Test04 (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        NODEPGM_DATA    *pObj = OBJ_NIL;
        ERESULT_DATA    *pErr = OBJ_NIL;
        DICT_DATA       *pDict = OBJ_NIL;
        NODE_DATA       *pNodes = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
        bool            fDump = true;
        int             iRc;
        int             offset = 0;
        uint32_t        i;
        const
        char            *pChr;       

        const
        char            *pJsonObject =
            "{name:\"genMake\", "
            "\"deps\":[Cmn] "
            "}\n";
        const
        char            *pGenCheck =
        ".PHONY: all\n"
        "all:  create_dirs link\n\n\n"
        ".PHONY: build\n"
        "build:  create_dirs link\n\n\n"
        ".PHONY: check\n"
        "check: $(TESTS)\n\n\n"
        ".PHONY: clean\n"
        "clean:\n"
        "\t-rm -fr $(BUILD)/$(PGMNAM)/$(SYS)/$(ARCH)\n\n\n"
        ".PHONY: create_dirs\n"
        "create_dirs:\n"
        "\t-mkdir -p $(BUILD)\n"
        "\t-mkdir -p $(TEST_OBJ)\n"
        "\t-mkdir -p $(TEST_BIN)\n\n\n"
            ".PHONY: install\n"
            "install:\n"
            "\tcp $(OBJDIR)/bin/$(PGMNAM) $(INSTALL_BASE)/$(PGMNAM)\n\n\n"
            ".PHONY: link\n"
            "link: $(OBJS) $(SRCDIR)/mainProgram.c\n"
            "\tCC -o $(OBJDIR)/bin/$(PGMNAM) $(CFLAGS) $(CFLAGS_LIBS) $^\n\n\n"
        ".PHONY: test\n"
        "test: $(TESTS)\n\n\n"
        ;

        fprintf(stderr, "Performing: %s\n", pTestName);

        pErr = InputStrToJSON(pJsonObject, &pNodes);
        eResult_Fprint(pErr, stderr);
        TestForTrue( (OBJ_NIL == pErr), "" );
        TestForFalse( (OBJ_NIL == pNodes), "" );

        pDict = Dict_New();
        TestForNotNull(pDict, "");
        eRc = Dict_Defaults(pDict);
        TestForFalse( (ERESULT_FAILED(eRc)), "" );

        pObj = NodePgm_New( );
        TestForNotNull(pObj, "");
        if (pObj) {

            //obj_TraceSet(pObj, true);       
            fRc = obj_IsKindOf(pObj, OBJ_IDENT_NODEPGM);
            TestForFalse(!fRc, "");
            TestForTrue(fRc, "");
            TestForSuccess("");
    #ifdef   NODEPGM_MSGS
            NodePgm_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
    #endif
                    
            {
                ASTR_DATA       *pStr = NodePgm_ToDebugString(pObj, 4);
                if (pStr) {
                    fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                }
            }

            pErr = NodeBase_Parse(pNodes, (NODEBASE_DATA **)&pObj);
            eResult_Fprint(pErr, stderr);
            TestForNull(pErr, "");
            if (fDump) {
                ASTR_DATA       *pWrk = OBJ_NIL;
                pWrk = NodePgm_ToDebugString(pObj, 0);
                fprintf(stderr, "\n====> TSTA Input:\n%s\n\n\n", AStr_getData(pWrk));
                obj_Release(pWrk);
                pWrk = OBJ_NIL;
            }

            pStr = NodePgm_GenMacEnd(pObj, pDict);
            TestForNotNull(pStr, "");

            if (pStr && fDump) {
                fprintf(stderr, "0         1         2         3\n");
                fprintf(stderr, "0123456789012345678901234567890\n");
                fprintf(stderr, "Generated:\n%s...End of Generated\n\n", AStr_getData(pStr));
            }

            // Compare the remainder.
            pChr = AStr_getData(pStr);
            iRc = str_CompareSpcl(pChr, pGenCheck, &offset);
            if (iRc) {
                fprintf(stderr, "Compare offset: %d\n", offset);
            }
            TestForTrue((0 == iRc), "");

            obj_Release(pStr);
            obj_Release(pDict);
            obj_Release(pNodes);

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
        //                                             Setup TearDown
        TestExec("OpenClose", Test_NodePgm_OpenClose, NULL,   NULL);
        //TestExec("Copy01", Test_NodePgm_Copy01,       NULL,   NULL);
        TestExec("Test01", Test_NodePgm_Test01,       NULL,   NULL);
        TestExec("Test02", Test_NodePgm_Test02,       NULL,   NULL);
        TestExec("Test03", Test_NodePgm_Test03,       NULL,   NULL);
        TestExec("Test04", Test_NodePgm_Test04,       NULL,   NULL);

        obj_Release(pTest);
        pTest = OBJ_NIL;

        // Return to Operating System.
        return 0;
    }


#ifdef  __cplusplus
}
#endif

