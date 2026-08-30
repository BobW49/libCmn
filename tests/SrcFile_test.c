// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Tokenize a TextIn Stream (SrcFile)  Test Program
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
#include    <SrcFile_internal.h>
#include    <JsonIn.h>
#include    <SrcErrors.h>
#include    <szTbl.h>


//#define     TEST_ASSIGN_COPY    1


#ifdef  __cplusplus
extern "C" {
#endif
        

static
const
char        *pFilePath = TEST_FILES_DIR "/test_expand_01.txt";
// Currently 853 bytes


static
char        *pTest01 =  "class abc {\n"
                            "\tint a;\n"
                            "\tchar\t\txyzzy(void);\n"
                        "}\n";


static
char        *pTest02 =  "\xC2\xA0" "class" "\xE2\x81\xA0" "abc;\n";





    //----------------------------------------------------------------
    //                      Test Open/Close
    //----------------------------------------------------------------

    ERESULT         Test_SrcFile_OpenClose (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        SRCFILE_DATA    *pObj = OBJ_NIL;
       
        fprintf(stderr, "Performing: %s\n", pTestName);

        pObj = SrcFile_Alloc( );
        TestForNotNull(pObj, "Missing Test Alloc() object");
        pObj = SrcFile_Init( pObj );
        TestForNotNull(pObj, "Missing Test Init() object");
        if (pObj) {

            //obj_TraceSet(pObj, true);       
            fRc = obj_IsKindOf(pObj, OBJ_IDENT_SRCFILE);
            TestForTrue(fRc, "Failed Ident Test");
    #ifdef   SRCFILE_MSGS
            SrcFile_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
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
    ERESULT         Test_SrcFile_Copy01 (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        //int             iRc;
        SRCFILE_DATA    *pObj1 = OBJ_NIL;
        SRCFILE_DATA    *pObj2 = OBJ_NIL;
    #if defined(SRCFILE_JSON_SUPPORT)
        ASTR_DATA       *pStr = OBJ_NIL;
    #endif
       
        fprintf(stderr, "Performing: %s\n", pTestName);

        pObj1 = SrcFile_New( );
        TestForNotNull(pObj1, "Missing Test object");
        if (pObj1) {

            //obj_TraceSet(pObj1, true);       
            fRc = obj_IsKindOf(pObj1, OBJ_IDENT_SRCFILE);
            TestForTrue(fRc, "Failed Ident Test");
    #ifdef   SRCFILE_MSGS
            SrcFile_setMsg(pObj1, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
    #endif
            
            // Test assign.
            pObj2 = SrcFile_New();
            TestForNotNull(pObj2, "Missing copied object");
            eRc = SrcFile_Assign(pObj1, pObj2);
            TestForFalse((ERESULT_FAILED(eRc)), "Assignment failed");

            fRc = obj_IsKindOf(pObj2, OBJ_IDENT_SRCFILE);
            TestForTrue(fRc, "Failed Ident Test");
            //iRc = SrcFile_Compare(pObj1, pObj2);
            //TestForTrue((0 == iRc), "Failed Compare");
            //TODO: Add More tests here!

            obj_Release(pObj2);
            pObj2 = OBJ_NIL;

            // Test copy.
            pObj2 = SrcFile_Copy(pObj1);
            TestForNotNull(pObj2, "Missing copied object");

            fRc = obj_IsKindOf(pObj2, OBJ_IDENT_SRCFILE);
            TestForTrue(fRc, "Failed Ident Test");
            //iRc = SrcFile_Compare(pObj1, pObj2);
            //TestForTrue((0 == iRc), "Failed Compare");
            //TODO: Add More tests here!

            obj_Release(pObj2);
            pObj2 = OBJ_NIL;

            // Test json support.
    #if defined(SRCFILE_JSON_SUPPORT)
            pStr = SrcFile_ToJson(pObj1);
            TestForNotNull(pStr, "Missing JSON output");
            fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
            pObj2 = SrcFile_NewFromJsonString(pStr);
            TestForNotNull(pObj2, "Missing JSON created object");
            fRc = obj_IsKindOf(pObj2, OBJ_IDENT_SRCFILE);
            TestForTrue(fRc, "Failed Ident Test");
            obj_Release(pStr);
            pStr = OBJ_NIL;
            //iRc = SrcFile_Compare(pObj1, pObj2);
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

    ERESULT         Test_SrcFile_Test01 (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        SRCFILE_DATA    *pObj = OBJ_NIL;
        //ASTR_DATA       *pStr = OBJ_NIL;
        ASTR_DATA       *pBuf = OBJ_NIL;
        PATH_DATA       *pPath = OBJ_NIL;
        TOKEN_DATA      *pToken;
       
        fprintf(stderr, "Performing: %s\n", pTestName);

        pPath = Path_NewA("abc");
        TestForNotNull(pPath, "");
        pBuf = AStr_NewA(pTest01);
        TestForNotNull(pBuf, "");

        pObj = SrcFile_NewFromAStr(pPath, pBuf, 1, 4);
        TestForNotNull(pObj, "");
        if (pObj) {

            //obj_TraceSet(pObj, true);       
            fRc = obj_IsKindOf(pObj, OBJ_IDENT_SRCFILE);
            TestForFalse(!fRc, "");
            TestForTrue(fRc, "");
            TestForSuccess("");
    #ifdef   SRCFILE_MSGS
            SrcFile_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
    #endif
                    
            {
                ASTR_DATA       *pStr = SrcFile_ToDebugString(pObj, 4);
                if (pStr) {
                    fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                }
            }

            pToken = SrcFile_InputLookAhead(pObj, 1);
            TestForNotNull(pToken, "");
            TestForTrue((ASCII_LEXICAL_ALPHA_LOWER == Token_getClass(pToken)), "");
            fprintf(stderr, "\tchr: %c\n", Token_getChrW32(pToken));
            TestForTrue(('c' == Token_getChrW32(pToken)), "");
            pToken = SrcFile_InputLookAhead(pObj, 2);
            TestForNotNull(pToken, "");
            TestForTrue((ASCII_LEXICAL_ALPHA_LOWER == Token_getClass(pToken)), "");
            TestForTrue(('l' == Token_getChrW32(pToken)), "");
            pToken = SrcFile_InputLookAhead(pObj, 3);
            TestForNotNull(pToken, "");
            TestForTrue((ASCII_LEXICAL_ALPHA_LOWER == Token_getClass(pToken)), "");
            TestForTrue(('a' == Token_getChrW32(pToken)), "");

            // Checkpoint to position 0 (ie beginning of file)
            eRc = SrcFile_CheckPoint(pObj);
            TestForSuccess("");
            
            // Advance over 'cla' and check for proper characters, 'ss'.
            pToken = SrcFile_InputAdvance(pObj, 3);
            TestForNotNull(pToken, "");
            TestForTrue((ASCII_LEXICAL_ALPHA_LOWER == Token_getClass(pToken)), "");
            TestForTrue(('s' == Token_getChrW32(pToken)), "");
            pToken = SrcFile_InputAdvance(pObj, 1);
            TestForNotNull(pToken, "");
            TestForTrue((ASCII_LEXICAL_ALPHA_LOWER == Token_getClass(pToken)), "");
            TestForTrue(('s' == Token_getChrW32(pToken)), "");

            eRc = SrcFile_Restart(pObj);
            TestForSuccess("");

            pToken = SrcFile_InputLookAhead(pObj, 1);
            TestForNotNull(pToken, "");
            TestForTrue((ASCII_LEXICAL_ALPHA_LOWER == Token_getClass(pToken)), "");
            fprintf(stderr, "\tchr: %c\n", Token_getChrW32(pToken));
            TestForTrue(('c' == Token_getChrW32(pToken)), "");
            pToken = SrcFile_InputLookAhead(pObj, 2);
            TestForNotNull(pToken, "");
            TestForTrue((ASCII_LEXICAL_ALPHA_LOWER == Token_getClass(pToken)), "");
            TestForTrue(('l' == Token_getChrW32(pToken)), "");
            pToken = SrcFile_InputLookAhead(pObj, 3);
            TestForNotNull(pToken, "");
            TestForTrue((ASCII_LEXICAL_ALPHA_LOWER == Token_getClass(pToken)), "");
            TestForTrue(('a' == Token_getChrW32(pToken)), "");

            {
                ASTR_DATA       *pStr = SrcFile_ToDebugString(pObj, 4);
                if (pStr) {
                    fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                }
            }

            obj_Release(pObj);
            pObj = OBJ_NIL;
        }

        obj_Release(pBuf);
        pBuf = OBJ_NIL;
        obj_Release(pPath);
        pPath = OBJ_NIL;

        fprintf(stderr, "...%s completed.\n\n\n", pTestName);
        return eRc;
    }



    //----------------------------------------------------------------
    //                          Test 2
    //----------------------------------------------------------------

    ERESULT         Test_SrcFile_Test02 (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        SRCFILE_DATA    *pObj = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
        ASTR_DATA       *pBuf = OBJ_NIL;
        TOKEN_DATA      *pToken;
        int32_t         cls = 1;
        char            chr;
        PATH_DATA       *pPath = OBJ_NIL;
        uint16_t        colNo;
        uint32_t        lineNo;
        uint32_t        i;
        const
        char            *pFileNameA;
       
        fprintf(stderr, "Performing: %s\n", pTestName);
        TestForNull(pStr, "");

        pPath = Path_NewA("abc");
        TestForNotNull(pPath, "");
        pBuf = AStr_NewA("/*/*/* abc */*/*/");
        TestForNotNull(pBuf, "");
        i = AStr_getLength(pBuf);
        TestForTrue((17 == i), "");
        fprintf(stderr, "\tpBuf = %p\n", pBuf);

        pObj = SrcFile_NewFromAStr(pPath, pBuf, 1, 4);
        TestForNotNull(pObj, "");
        if (pObj) {

            obj_TraceSet(pObj, true);
            fRc = obj_IsKindOf(pObj, OBJ_IDENT_SRCFILE);
            TestForFalse(!fRc, "");
            TestForTrue(fRc, "");
            TestForSuccess("");
    #ifdef   SRCFILE_MSGS
            SrcFile_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
    #endif
                    
            while (!(cls == -1)) {
                pToken = SrcFile_InputLookAhead(pObj, 1);
                TestForTrue((Token_Validate(pToken)), "");
                chr = Token_getChrW32(pToken);
                cls = Token_getClass(pToken);
                colNo = Token_getColNo(pToken);
                lineNo = Token_getLineNo(pToken);
                pFileNameA = Token_getFileName(pToken);
                fprintf(
                        stderr,
                        "\tfile: %s, line: %2d col: %2d cls: %08X chr: %02X\n",
                        pFileNameA ? pFileNameA : "",
                        lineNo,
                        colNo,
                        cls,
                        chr
                        );
                SrcFile_InputAdvance(pObj, 1);
            }

            {
                ASTR_DATA       *pStr = SrcFile_ToDebugString(pObj, 4);
                if (pStr) {
                    fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                }
            }

            obj_Release(pObj);
            pObj = OBJ_NIL;
        }

        obj_Release(pBuf);
        pBuf = OBJ_NIL;
        obj_Release(pPath);
        pPath = OBJ_NIL;

        fprintf(stderr, "...%s completed.\n\n\n", pTestName);
        return eRc;
    }



    //----------------------------------------------------------------
    //                          Test 3
    //----------------------------------------------------------------

    ERESULT         Test_SrcFile_Test03 (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        SRCFILE_DATA    *pObj = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
        PATH_DATA       *pPath = OBJ_NIL;
        uint32_t        count  = 0;
        TOKEN_DATA      *pToken;
        int32_t         chr;

        fprintf(stderr, "Performing: %s\n", pTestName);
        TestForNull(pStr, "");

        pPath = Path_NewA(pFilePath);
        TestForNotNull(pPath, "");

        pObj = SrcFile_NewFromPath(pPath, 1, 4);
        TestForNotNull(pObj, "");
        if (pObj) {

            //obj_TraceSet(pObj, true);       
            fRc = obj_IsKindOf(pObj, OBJ_IDENT_SRCFILE);
            TestForFalse(!fRc, "");
            TestForTrue(fRc, "");
            TestForSuccess("");
    #ifdef   SRCFILE_MSGS
            SrcFile_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
    #endif
                    
            for ( ;; ) {
                pToken = SrcFile_InputLookAhead(pObj, 1);
                if (OBJ_NIL == pToken) {
                    break;
                }
                TestForTrue((Token_Validate(pToken)), "");
                chr = Token_getChrW32(pToken);
                if (-1 == chr) {
                    break;
                }
                ++count;
                SrcFile_InputAdvance(pObj, 1);
            }
            fprintf(stderr,"Number of bytes read: %d\n", count);
            TestForTrue((79 == count), "");

            {
                ASTR_DATA       *pStr = SrcFile_ToDebugString(pObj, 4);
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

    ERESULT         Test_SrcFile_Test04 (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        SRCFILE_DATA    *pObj = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
        ASTR_DATA       *pBuf = OBJ_NIL;
        TOKEN_DATA      *pToken;
        int32_t         cls = 1;
        int32_t         chr;
        uint16_t        colNo;
        uint32_t        lineNo;
        uint32_t        i;
        PATH_DATA       *pPath = OBJ_NIL;
        const
        char            *pFileNameA;

        fprintf(stderr, "Performing: %s\n", pTestName);
        TestForNull(pStr, "");
        
        pBuf = AStr_NewA(pTest02);
        TestForNotNull(pBuf, "");
        i = AStr_getLength(pBuf);
        TestForTrue((12 == i), "");
        fprintf(stderr,"pBuf length: %d\n", i);

        pPath = Path_NewA("abc");
        TestForNotNull(pPath, "");

        pObj = SrcFile_NewFromAStr(pPath, pBuf, 1, 4);
        TestForNotNull(pObj, "");
        if (pObj) {

            obj_TraceSet(pObj, true);
            fRc = obj_IsKindOf(pObj, OBJ_IDENT_SRCFILE);
            TestForFalse(!fRc, "");
            TestForTrue(fRc, "");
            TestForSuccess("");
    #ifdef   SRCFILE_MSGS
            SrcFile_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
    #endif
                    
            pToken = SrcFile_InputLookAhead(pObj, 1);
            TestForNotNull(pToken, "");
            TestForTrue((Token_Validate(pToken)), "");
            chr = Token_getChrW32(pToken);
            TestForTrue((0xA0 == chr), "");
            cls = Token_getClass(pToken);
            TestForTrue((ASCII_LEXICAL_WHITESPACE == cls), "");
            colNo = Token_getColNo(pToken);
            lineNo = Token_getLineNo(pToken);
            pFileNameA = Token_getFileName(pToken);
            SrcFile_InputAdvance(pObj, 1);

            pToken = SrcFile_InputLookAhead(pObj, 1);
            TestForNotNull(pToken, "");
            TestForTrue((Token_Validate(pToken)), "");
            chr = Token_getChrW32(pToken);
            TestForTrue(('c' == chr), "");
            cls = Token_getClass(pToken);
            TestForTrue((ASCII_LEXICAL_ALPHA_LOWER == cls), "");
            colNo = Token_getColNo(pToken);
            lineNo = Token_getLineNo(pToken);
            pFileNameA = Token_getFileName(pToken);
            SrcFile_InputAdvance(pObj, 1);

            pToken = SrcFile_InputLookAhead(pObj, 1);
            TestForNotNull(pToken, "");
            TestForTrue((Token_Validate(pToken)), "");
            chr = Token_getChrW32(pToken);
            TestForTrue(('l' == chr), "");
            cls = Token_getClass(pToken);
            TestForTrue((ASCII_LEXICAL_ALPHA_LOWER == cls), "");
            colNo = Token_getColNo(pToken);
            lineNo = Token_getLineNo(pToken);
            pFileNameA = Token_getFileName(pToken);
            SrcFile_InputAdvance(pObj, 1);

            pToken = SrcFile_InputLookAhead(pObj, 1);
            TestForNotNull(pToken, "");
            TestForTrue((Token_Validate(pToken)), "");
            chr = Token_getChrW32(pToken);
            TestForTrue(('a' == chr), "");
            cls = Token_getClass(pToken);
            TestForTrue((ASCII_LEXICAL_ALPHA_LOWER == cls), "");
            colNo = Token_getColNo(pToken);
            lineNo = Token_getLineNo(pToken);
            pFileNameA = Token_getFileName(pToken);
            SrcFile_InputAdvance(pObj, 1);

            pToken = SrcFile_InputLookAhead(pObj, 1);
            TestForNotNull(pToken, "");
            TestForTrue((Token_Validate(pToken)), "");
            chr = Token_getChrW32(pToken);
            TestForTrue(('s' == chr), "");
            cls = Token_getClass(pToken);
            TestForTrue((ASCII_LEXICAL_ALPHA_LOWER == cls), "");
            colNo = Token_getColNo(pToken);
            lineNo = Token_getLineNo(pToken);
            pFileNameA = Token_getFileName(pToken);
            SrcFile_InputAdvance(pObj, 1);

            pToken = SrcFile_InputLookAhead(pObj, 1);
            TestForNotNull(pToken, "");
            TestForTrue((Token_Validate(pToken)), "");
            chr = Token_getChrW32(pToken);
            TestForTrue(('s' == chr), "");
            cls = Token_getClass(pToken);
            TestForTrue((ASCII_LEXICAL_ALPHA_LOWER == cls), "");
            colNo = Token_getColNo(pToken);
            lineNo = Token_getLineNo(pToken);
            pFileNameA = Token_getFileName(pToken);
            SrcFile_InputAdvance(pObj, 1);

            pToken = SrcFile_InputLookAhead(pObj, 1);
            TestForNotNull(pToken, "");
            TestForTrue((Token_Validate(pToken)), "");
            chr = Token_getChrW32(pToken);
            TestForTrue((0x2060 == chr), "");
            cls = Token_getClass(pToken);
            TestForTrue((ASCII_LEXICAL_UNKNOWN == cls), "");
            colNo = Token_getColNo(pToken);
            lineNo = Token_getLineNo(pToken);
            pFileNameA = Token_getFileName(pToken);
            SrcFile_InputAdvance(pObj, 1);

            pToken = SrcFile_InputLookAhead(pObj, 1);
            TestForNotNull(pToken, "");
            TestForTrue((Token_Validate(pToken)), "");
            chr = Token_getChrW32(pToken);
            TestForTrue(('a' == chr), "");
            cls = Token_getClass(pToken);
            TestForTrue((ASCII_LEXICAL_ALPHA_LOWER == cls), "");
            colNo = Token_getColNo(pToken);
            lineNo = Token_getLineNo(pToken);
            pFileNameA = Token_getFileName(pToken);
            SrcFile_InputAdvance(pObj, 1);

            pToken = SrcFile_InputLookAhead(pObj, 1);
            TestForNotNull(pToken, "");
            TestForTrue((Token_Validate(pToken)), "");
            chr = Token_getChrW32(pToken);
            TestForTrue(('b' == chr), "");
            cls = Token_getClass(pToken);
            TestForTrue((ASCII_LEXICAL_ALPHA_LOWER == cls), "");
            colNo = Token_getColNo(pToken);
            lineNo = Token_getLineNo(pToken);
            pFileNameA = Token_getFileName(pToken);
            SrcFile_InputAdvance(pObj, 1);

            pToken = SrcFile_InputLookAhead(pObj, 1);
            TestForNotNull(pToken, "");
            TestForTrue((Token_Validate(pToken)), "");
            chr = Token_getChrW32(pToken);
            TestForTrue(('c' == chr), "");
            cls = Token_getClass(pToken);
            TestForTrue((ASCII_LEXICAL_ALPHA_LOWER == cls), "");
            colNo = Token_getColNo(pToken);
            lineNo = Token_getLineNo(pToken);
            pFileNameA = Token_getFileName(pToken);
            SrcFile_InputAdvance(pObj, 1);

            pToken = SrcFile_InputLookAhead(pObj, 1);
            TestForNotNull(pToken, "");
            TestForTrue((Token_Validate(pToken)), "");
            chr = Token_getChrW32(pToken);
            TestForTrue((';' == chr), "");
            cls = Token_getClass(pToken);
            TestForTrue((';' == cls), "");
            colNo = Token_getColNo(pToken);
            lineNo = Token_getLineNo(pToken);
            pFileNameA = Token_getFileName(pToken);
            SrcFile_InputAdvance(pObj, 1);

            pToken = SrcFile_InputLookAhead(pObj, 1);
            TestForNotNull(pToken, "");
            TestForTrue((Token_Validate(pToken)), "");
            chr = Token_getChrW32(pToken);
            TestForTrue(('\n' == chr), "");
            cls = Token_getClass(pToken);
            TestForTrue((ASCII_LEXICAL_EOL == cls), "");
            colNo = Token_getColNo(pToken);
            lineNo = Token_getLineNo(pToken);
            pFileNameA = Token_getFileName(pToken);
            SrcFile_InputAdvance(pObj, 1);

            pToken = SrcFile_InputLookAhead(pObj, 1);
            TestForNotNull(pToken, "");
            TestForTrue((Token_Validate(pToken)), "");
            chr = Token_getChrW32(pToken);
            TestForTrue((-1 == chr), "");
            cls = Token_getClass(pToken);
            TestForTrue((-1 == cls), "");
            colNo = Token_getColNo(pToken);
            lineNo = Token_getLineNo(pToken);
            pFileNameA = Token_getFileName(pToken);
            SrcFile_InputAdvance(pObj, 1);

         {
                ASTR_DATA       *pStr = SrcFile_ToDebugString(pObj, 4);
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
        obj_Release(pBuf);
        pBuf = OBJ_NIL;
        
        fprintf(stderr, "...%s completed.\n\n\n", pTestName);
        return eRc;
    }




    //----------------------------------------------------------------
    //                          Test 5
    //----------------------------------------------------------------

    ERESULT         Test_SrcFile_Test05 (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        SRCFILE_DATA    *pObj = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
        ASTR_DATA       *pBuf = OBJ_NIL;
        TOKEN_DATA      *pToken;
        int32_t         cls = 1;
        int32_t         chr;
        uint16_t        colNo;
        uint32_t        lineNo;
        uint32_t        i;
        PATH_DATA       *pPath = OBJ_NIL;
        const
        char            *pFileNameA;

        fprintf(stderr, "Performing: %s\n", pTestName);
        TestForNull(pStr, "");

        pBuf = AStr_NewA("{oNe: +123}\n");
        TestForNotNull(pBuf, "");
        i = AStr_getLength(pBuf);
        TestForTrue((12 == i), "");
        fprintf(stderr,"pBuf length: %d\n", i);

        pPath = Path_NewA("abc");
        TestForNotNull(pPath, "");

        pObj = SrcFile_NewFromAStr(pPath, pBuf, 1, 4);
        TestForNotNull(pObj, "");
        if (pObj) {

            //obj_TraceSet(pObj, true);       
            fRc = obj_IsKindOf(pObj, OBJ_IDENT_SRCFILE);
            TestForFalse(!fRc, "");
            TestForTrue(fRc, "");
            TestForSuccess("");
    #ifdef   SRCFILE_MSGS
            SrcFile_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
    #endif
                    
            pToken = SrcFile_InputLookAhead(pObj, 1);
            TestForNotNull(pToken, "");
            TestForTrue((Token_Validate(pToken)), "");
            chr = Token_getChrW32(pToken);
            TestForTrue(('{' == chr), "");
            cls = Token_getClass(pToken);
            TestForTrue(('{' == cls), "");
            colNo = Token_getColNo(pToken);
            lineNo = Token_getLineNo(pToken);
            pFileNameA = Token_getFileName(pToken);
            SrcFile_InputAdvance(pObj, 1);

            pToken = SrcFile_InputLookAhead(pObj, 1);
            TestForNotNull(pToken, "");
            TestForTrue((Token_Validate(pToken)), "");
            chr = Token_getChrW32(pToken);
            TestForTrue(('o' == chr), "");
            cls = Token_getClass(pToken);
            TestForTrue((ASCII_LEXICAL_ALPHA_LOWER == cls), "");
            colNo = Token_getColNo(pToken);
            lineNo = Token_getLineNo(pToken);
            pFileNameA = Token_getFileName(pToken);
            SrcFile_InputAdvance(pObj, 1);

            pToken = SrcFile_InputLookAhead(pObj, 1);
            TestForNotNull(pToken, "");
            TestForTrue((Token_Validate(pToken)), "");
            chr = Token_getChrW32(pToken);
            TestForTrue(('N' == chr), "");
            cls = Token_getClass(pToken);
            TestForTrue((ASCII_LEXICAL_ALPHA_UPPER == cls), "");
            colNo = Token_getColNo(pToken);
            lineNo = Token_getLineNo(pToken);
            pFileNameA = Token_getFileName(pToken);
            SrcFile_InputAdvance(pObj, 1);

            pToken = SrcFile_InputLookAhead(pObj, 1);
            TestForNotNull(pToken, "");
            TestForTrue((Token_Validate(pToken)), "");
            chr = Token_getChrW32(pToken);
            TestForTrue(('e' == chr), "");
            cls = Token_getClass(pToken);
            TestForTrue((ASCII_LEXICAL_ALPHA_LOWER == cls), "");
            colNo = Token_getColNo(pToken);
            lineNo = Token_getLineNo(pToken);
            pFileNameA = Token_getFileName(pToken);
            SrcFile_InputAdvance(pObj, 1);

            pToken = SrcFile_InputLookAhead(pObj, 1);
            TestForNotNull(pToken, "");
            TestForTrue((Token_Validate(pToken)), "");
            chr = Token_getChrW32(pToken);
            TestForTrue((':' == chr), "");
            cls = Token_getClass(pToken);
            TestForTrue((':' == cls), "");
            colNo = Token_getColNo(pToken);
            lineNo = Token_getLineNo(pToken);
            pFileNameA = Token_getFileName(pToken);
            SrcFile_InputAdvance(pObj, 1);

            pToken = SrcFile_InputLookAhead(pObj, 1);
            TestForNotNull(pToken, "");
            TestForTrue((Token_Validate(pToken)), "");
            chr = Token_getChrW32(pToken);
            TestForTrue((' ' == chr), "");
            cls = Token_getClass(pToken);
            TestForTrue((ASCII_LEXICAL_WHITESPACE == cls), "");
            colNo = Token_getColNo(pToken);
            lineNo = Token_getLineNo(pToken);
            pFileNameA = Token_getFileName(pToken);
            SrcFile_InputAdvance(pObj, 1);

            pToken = SrcFile_InputLookAhead(pObj, 1);
            TestForNotNull(pToken, "");
            TestForTrue((Token_Validate(pToken)), "");
            chr = Token_getChrW32(pToken);
            TestForTrue(('+' == chr), "");
            cls = Token_getClass(pToken);
            TestForTrue(('+' == cls), "");
            colNo = Token_getColNo(pToken);
            lineNo = Token_getLineNo(pToken);
            pFileNameA = Token_getFileName(pToken);
            SrcFile_InputAdvance(pObj, 1);

            pToken = SrcFile_InputLookAhead(pObj, 1);
            TestForNotNull(pToken, "");
            TestForTrue((Token_Validate(pToken)), "");
            chr = Token_getChrW32(pToken);
            TestForTrue(('1' == chr), "");
            cls = Token_getClass(pToken);
            TestForTrue((ASCII_LEXICAL_NUMBER == cls), "");
            colNo = Token_getColNo(pToken);
            lineNo = Token_getLineNo(pToken);
            pFileNameA = Token_getFileName(pToken);
            SrcFile_InputAdvance(pObj, 1);

            pToken = SrcFile_InputLookAhead(pObj, 1);
            TestForNotNull(pToken, "");
            TestForTrue((Token_Validate(pToken)), "");
            chr = Token_getChrW32(pToken);
            TestForTrue(('2' == chr), "");
            cls = Token_getClass(pToken);
            TestForTrue((ASCII_LEXICAL_NUMBER == cls), "");
            colNo = Token_getColNo(pToken);
            lineNo = Token_getLineNo(pToken);
            pFileNameA = Token_getFileName(pToken);
            SrcFile_InputAdvance(pObj, 1);

            pToken = SrcFile_InputLookAhead(pObj, 1);
            TestForNotNull(pToken, "");
            TestForTrue((Token_Validate(pToken)), "");
            chr = Token_getChrW32(pToken);
            TestForTrue(('3' == chr), "");
            cls = Token_getClass(pToken);
            TestForTrue((ASCII_LEXICAL_NUMBER == cls), "");
            colNo = Token_getColNo(pToken);
            lineNo = Token_getLineNo(pToken);
            pFileNameA = Token_getFileName(pToken);
            SrcFile_InputAdvance(pObj, 1);

            pToken = SrcFile_InputLookAhead(pObj, 1);
            TestForNotNull(pToken, "");
            TestForTrue((Token_Validate(pToken)), "");
            chr = Token_getChrW32(pToken);
            TestForTrue(('}' == chr), "");
            cls = Token_getClass(pToken);
            TestForTrue(('}' == cls), "");
            colNo = Token_getColNo(pToken);
            lineNo = Token_getLineNo(pToken);
            pFileNameA = Token_getFileName(pToken);
            SrcFile_InputAdvance(pObj, 1);

            pToken = SrcFile_InputLookAhead(pObj, 1);
            TestForNotNull(pToken, "");
            TestForTrue((Token_Validate(pToken)), "");
            chr = Token_getChrW32(pToken);
            TestForTrue(('\n' == chr), "");
            cls = Token_getClass(pToken);
            TestForTrue((ASCII_LEXICAL_EOL == cls), "");
            colNo = Token_getColNo(pToken);
            lineNo = Token_getLineNo(pToken);
            pFileNameA = Token_getFileName(pToken);
            SrcFile_InputAdvance(pObj, 1);

            pToken = SrcFile_InputLookAhead(pObj, 1);
            TestForNotNull(pToken, "");
            TestForTrue((Token_Validate(pToken)), "");
            chr = Token_getChrW32(pToken);
            TestForTrue((-1 == chr), "");
            cls = Token_getClass(pToken);
            TestForTrue((-1 == cls), "");
            colNo = Token_getColNo(pToken);
            lineNo = Token_getLineNo(pToken);
            pFileNameA = Token_getFileName(pToken);
            SrcFile_InputAdvance(pObj, 1);

           {
                ASTR_DATA       *pStr = SrcFile_ToDebugString(pObj, 4);
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
        obj_Release(pBuf);
        pBuf = OBJ_NIL;
        
        fprintf(stderr, "...%s completed.\n\n\n", pTestName);
        return eRc;
    }



    //----------------------------------------------------------------
    //                          Test 6
    //----------------------------------------------------------------

    ERESULT         Test_SrcFile_Test06 (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        SRCFILE_DATA    *pObj = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
       
        fprintf(stderr, "Performing: %s\n", pTestName);
        TestForNull(pStr, "");

        pObj = SrcFile_New( );
        TestForNotNull(pObj, "");
        if (pObj) {

            //obj_TraceSet(pObj, true);       
            fRc = obj_IsKindOf(pObj, OBJ_IDENT_SRCFILE);
            TestForFalse(!fRc, "");
            TestForTrue(fRc, "");
            TestForSuccess("");
    #ifdef   SRCFILE_MSGS
            SrcFile_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
    #endif
                    
            {
                ASTR_DATA       *pStr = SrcFile_ToDebugString(pObj, 4);
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
    //                          Test 7
    //----------------------------------------------------------------

    ERESULT         Test_SrcFile_Test07 (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        SRCFILE_DATA    *pObj = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
       
        fprintf(stderr, "Performing: %s\n", pTestName);
        TestForNull(pStr, "");

        pObj = SrcFile_New( );
        TestForNotNull(pObj, "");
        if (pObj) {

            //obj_TraceSet(pObj, true);       
            fRc = obj_IsKindOf(pObj, OBJ_IDENT_SRCFILE);
            TestForFalse(!fRc, "");
            TestForTrue(fRc, "");
            TestForSuccess("");
    #ifdef   SRCFILE_MSGS
            SrcFile_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
    #endif
                    
            {
                ASTR_DATA       *pStr = SrcFile_ToDebugString(pObj, 4);
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

    ERESULT         Test_SrcFile_Test08 (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        SRCFILE_DATA    *pObj = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
       
        fprintf(stderr, "Performing: %s\n", pTestName);
        TestForNull(pStr, "");

        pObj = SrcFile_New( );
        TestForNotNull(pObj, "");
        if (pObj) {

            //obj_TraceSet(pObj, true);       
            fRc = obj_IsKindOf(pObj, OBJ_IDENT_SRCFILE);
            TestForFalse(!fRc, "");
            TestForTrue(fRc, "");
            TestForSuccess("");
    #ifdef   SRCFILE_MSGS
            SrcFile_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
    #endif
                    
            {
                ASTR_DATA       *pStr = SrcFile_ToDebugString(pObj, 4);
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

    ERESULT         Test_SrcFile_Test09 (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        SRCFILE_DATA    *pObj = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
       
        fprintf(stderr, "Performing: %s\n", pTestName);
        TestForNull(pStr, "");

        pObj = SrcFile_New( );
        TestForNotNull(pObj, "");
        if (pObj) {

            //obj_TraceSet(pObj, true);       
            fRc = obj_IsKindOf(pObj, OBJ_IDENT_SRCFILE);
            TestForFalse(!fRc, "");
            TestForTrue(fRc, "");
            TestForSuccess("");
    #ifdef   SRCFILE_MSGS
            SrcFile_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
    #endif
                    
            {
                ASTR_DATA       *pStr = SrcFile_ToDebugString(pObj, 4);
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
    //                          Test 10
    //----------------------------------------------------------------

    ERESULT         Test_SrcFile_Test10 (
        TEST_DATA       *this,
        const
        char            *pTestName
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        SRCFILE_DATA    *pObj = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
       
        fprintf(stderr, "Performing: %s\n", pTestName);
        TestForNull(pStr, "");

        pObj = SrcFile_New( );
        TestForNotNull(pObj, "");
        if (pObj) {

            //obj_TraceSet(pObj, true);       
            fRc = obj_IsKindOf(pObj, OBJ_IDENT_SRCFILE);
            TestForFalse(!fRc, "");
            TestForTrue(fRc, "");
            TestForSuccess("");
    #ifdef   SRCFILE_MSGS
            SrcFile_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
    #endif
                    
            {
                ASTR_DATA       *pStr = SrcFile_ToDebugString(pObj, 4);
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
        TestExec("OpenClose", Test_SrcFile_OpenClose, NULL,   NULL);
#ifdef  TEST_ASSIGN_COPY
        TestExec("Copy01", Test_SrcFile_Copy01,       NULL,   NULL);
#endif
        TestExec("Test01", Test_SrcFile_Test01,       NULL,   NULL);
        TestExec("Test02", Test_SrcFile_Test02,       NULL,   NULL);
        TestExec("Test03", Test_SrcFile_Test03,       NULL,   NULL);
        TestExec("Test04", Test_SrcFile_Test04,       NULL,   NULL);
        TestExec("Test05", Test_SrcFile_Test05,       NULL,   NULL);
        TestExec("Test06", Test_SrcFile_Test06,       NULL,   NULL);
        TestExec("Test07", Test_SrcFile_Test07,       NULL,   NULL);
        TestExec("Test08", Test_SrcFile_Test08,       NULL,   NULL);
        TestExec("Test09", Test_SrcFile_Test09,       NULL,   NULL);
        TestExec("Test10", Test_SrcFile_Test10,       NULL,   NULL);

        obj_Release(pTest);
        pTest = OBJ_NIL;

        // Return to Operating System.
        return 0;
    }


#ifdef  __cplusplus
}
#endif

