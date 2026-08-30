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
#include    <AStr_internal.h>
#include    <AStrArray.h>
#include    <JsonIn.h>
#include    <SrcErrors.h>
#include    <szTbl.h>




static
ASTR_DATA       *pStrTest1 = OBJ_NIL;
static
ASTR_DATA       *pStrTest2 = OBJ_NIL;
static
ASTR_DATA       *pStrTest3 = OBJ_NIL;


ASTR_DATA *     findTest(
    OBJ_ID          id,
    const
    char            *pTestNameA
)
{
    if (0 == strcmp(pTestNameA, "test1"))
        return pStrTest1;
    if (0 == strcmp(pTestNameA, "test2"))
        return pStrTest2;
    if (0 == strcmp(pTestNameA, "test3"))
        return pStrTest3;
    return OBJ_NIL;
}





int         setUp1(
    TEST_DATA   *pTest
)
{
    
    pStrTest1 = AStr_NewA("TestString1");
    pStrTest2 = AStr_NewA("TestString2");
    pStrTest3 = AStr_NewA("TestString3");
    
    return 1;
}


int         tearDown1(
    TEST_DATA   *pTest
)
{
    // Put teardown code here. This method is called after the invocation of each
    // test method in the class.

    obj_Release(pStrTest1);
    pStrTest1 = OBJ_NIL;
    obj_Release(pStrTest2);
    pStrTest2 = OBJ_NIL;
    obj_Release(pStrTest3);
    pStrTest3 = OBJ_NIL;
    
    return 1;
}





ERESULT         Test_AStr_OpenClose (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTR_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    W32CHR_T        chrW;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AStr_Alloc( );
    TestForNotNull(pObj, "Missing Test Alloc() object");
    pObj = AStr_Init( pObj );
    TestForNotNull(pObj, "Missing Test Init() object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTR);
        TestForTrue(fRc, "Failed Ident Test");
#ifdef   ASTR_MSGS
        AStr_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
        
        // Test something.
        TestForSuccess("test failed");

        eRc = AStr_AppendA( pObj, "abc" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (3 == AStr_getLength(pObj)) );
        XCTAssertTrue( (0 == strcmp("abc", AStr_getData(pObj))) );
        
        eRc = AStr_AppendA( pObj, "def" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (6 == AStr_getLength(pObj)) );
        XCTAssertTrue( (0 == strcmp("abcdef", AStr_getData(pObj))) );
        
        eRc = AStr_AppendCharRepeatA( pObj, 2, 'z' );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (8 == AStr_getLength(pObj)) );
        XCTAssertTrue( (0 == strcmp("abcdefzz", AStr_getData(pObj))) );
        
        eRc = AStr_AppendCharRepeatW32( pObj, 2, 'y' );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (10 == AStr_getLength(pObj)) );
        XCTAssertTrue( (0 == strcmp("abcdefzzyy", AStr_getData(pObj))) );
        
        eRc = AStr_CharPutW32( pObj, 2, 'x' );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (10 == AStr_getLength(pObj)) );
        XCTAssertTrue( (0 == strcmp("axcdefzzyy", AStr_getData(pObj))) );
        
        eRc = AStr_CharPutW32( pObj, 2, 'b' );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (10 == AStr_getLength(pObj)) );
        XCTAssertTrue( (0 == strcmp("abcdefzzyy", AStr_getData(pObj))) );
        
        eRc = AStr_Truncate( pObj, 6 );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (6 == AStr_getLength(pObj)) );
        XCTAssertTrue( (0 == strcmp("abcdef", AStr_getData(pObj))) );
        
        eRc = AStr_CompareA(pObj, "abcdef");
        XCTAssertTrue( (0 == eRc) );
        
        eRc = AStr_CompareA(pObj, "aaaaaa");
        XCTAssertTrue( (eRc > 0) );
        
        eRc = AStr_CompareA(pObj, "zzzzzz");
        XCTAssertTrue( (eRc < 0) );
        
        chrW = AStr_CharGetW32( pObj, 0 );
        XCTAssertTrue( (-1 == chrW) );
        
        chrW = AStr_CharGetW32( pObj, 1 );
        XCTAssertTrue( ('a' == chrW) );
        
        chrW = AStr_CharGetW32( pObj, 6 );
        XCTAssertTrue( ('f' == chrW) );
        
        chrW = AStr_CharGetW32( pObj, 7 );
        XCTAssertTrue( (-1 == chrW) );
        
        eRc = AStr_Remove( pObj, 4, 2 );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (4 == AStr_getLength(pObj)) );
        XCTAssertTrue( (0 == strcmp("abcf", AStr_getData(pObj))) );
        
        eRc = AStr_Remove( pObj, 4, 1 );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (3 == AStr_getLength(pObj)) );
        XCTAssertTrue( (0 == strcmp("abc", AStr_getData(pObj))) );
        
        eRc = AStr_Remove( pObj, 1, 1 );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (2 == AStr_getLength(pObj)) );
        XCTAssertTrue( (0 == strcmp("bc", AStr_getData(pObj))) );
        
        eRc = AStr_Remove( pObj, 1, 2 );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (0 == AStr_getLength(pObj)) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_AStr_Copy01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTR_DATA       *pObj1 = OBJ_NIL;
    ASTR_DATA       *pObj2 = OBJ_NIL;
    bool            fRc;
    ASTR_DATA       *pStr = OBJ_NIL;
    int             iRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = AStr_NewA("abcdef");
    TestForNotNull(pObj1, "Missing Test object");
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_ASTR);
        TestForTrue(fRc, "Failed Ident Test");
#ifdef   ASTR_MSGS
        AStr_setMsg(pObj1, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
        XCTAssertTrue( (6 == AStr_getLength(pObj1)) );
        XCTAssertTrue( (0 == strcmp("abcdef", AStr_getData(pObj1))) );

        // Test assign.
        pObj2 = AStr_New();
        TestForNotNull(pObj2, "Missing copied object");
        eRc = AStr_Assign(pObj1, pObj2);
        TestForFalse((ERESULT_FAILED(eRc)), "Assignment failed");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_ASTR);
        TestForTrue(fRc, "Failed Ident Test");
        XCTAssertTrue( (6 == AStr_getLength(pObj2)) );
        XCTAssertTrue( (0 == strcmp("abcdef", AStr_getData(pObj2))) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = AStr_Copy(pObj1);
        TestForNotNull(pObj2, "Missing copied object");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_ASTR);
        TestForTrue(fRc, "Failed Ident Test");
        XCTAssertTrue( (6 == AStr_getLength(pObj2)) );
        XCTAssertTrue( (0 == strcmp("abcdef", AStr_getData(pObj2))) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
        pStr = AStr_ToJson(pObj1);
        TestForNotNull(pStr, "Missing JSON output");
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = AStr_NewFromJsonString(pStr);
        TestForNotNull(pObj2, "Missing JSON created object");
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_ASTR);
        TestForTrue(fRc, "Failed Ident Test");
        obj_Release(pStr);
        pStr = OBJ_NIL;
        iRc = AStr_Compare(pObj1, pObj2);
        TestForTrue((0 == iRc), "Failed Compare");

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        obj_Release(pObj1);
        pObj1 = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_AStr_Test01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTR_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    uint32_t        i = 0;
    uint32_t        iMax = 5000;
    const
    char            *pLowerA = "abcdefghijklmnopqrstuvwxyz";
    const
    char            *pUpperA = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const
    char            *pNumbersA = "0123456789";
    ASTR_DATA       *pLower = OBJ_NIL;
    ASTR_DATA       *pUpper = OBJ_NIL;
    ASTR_DATA       *pNumbers = OBJ_NIL;
    ASTR_DATA       *pBase = OBJ_NIL;
    const
    char        *pChrs;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pLower = AStr_NewA(pLowerA);
    XCTAssertFalse( (OBJ_NIL == pLower) );
    XCTAssertTrue( (26 == AStr_getLength(pLower)) );
    XCTAssertTrue( (0 == strcmp(pLowerA, AStr_getData(pLower))) );
    
    pUpper = AStr_NewA(pUpperA);
    XCTAssertFalse( (OBJ_NIL == pUpper) );
    XCTAssertTrue( (26 == AStr_getLength(pUpper)) );
    XCTAssertTrue( (0 == strcmp(pUpperA, AStr_getData(pUpper))) );
    
    pNumbers = AStr_NewA(pNumbersA);
    XCTAssertFalse( (OBJ_NIL == pNumbers) );
    XCTAssertTrue( (10 == AStr_getLength(pNumbers)) );
    XCTAssertTrue( (0 == strcmp(pNumbersA, AStr_getData(pNumbers))) );
    
    pBase = AStr_New();
    XCTAssertFalse( (OBJ_NIL == pBase) );
    XCTAssertTrue( (0 == AStr_getLength(pBase)) );
    eRc = AStr_Append( pBase, pNumbers );
    XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
    XCTAssertTrue( (10 == AStr_getLength(pBase)) );
    pChrs = AStr_getData(pBase);
    XCTAssertTrue( (0 == strncmp(AStr_getData(pNumbers), pChrs, AStr_getLength(pNumbers))) );
    eRc = AStr_Append( pBase, pLower );
    XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
    XCTAssertTrue( (36 == AStr_getLength(pBase)) );
    pChrs = AStr_getData(pBase);
    XCTAssertTrue( (0 == strncmp(AStr_getData(pNumbers), pChrs, AStr_getLength(pNumbers))) );
    pChrs = AStr_getData(pBase) + AStr_getLength(pNumbers);
    XCTAssertTrue( (0 == strncmp(AStr_getData(pLower), pChrs, AStr_getLength(pLower))) );
    eRc = AStr_Append( pBase, pUpper );
    XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
    XCTAssertTrue( (62 == AStr_getLength(pBase)) );
    pChrs = AStr_getData(pBase);
    XCTAssertTrue( (0 == strncmp(AStr_getData(pNumbers), pChrs, AStr_getLength(pNumbers))) );
    pChrs = AStr_getData(pBase) + AStr_getLength(pNumbers);
    XCTAssertTrue( (0 == strncmp(AStr_getData(pLower), pChrs, AStr_getLength(pLower))) );
    pChrs = AStr_getData(pBase) + AStr_getLength(pNumbers) + AStr_getLength(pLower);
    XCTAssertTrue( (0 == strncmp(AStr_getData(pUpper), pChrs, AStr_getLength(pUpper))) );

    pObj = AStr_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTR);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("test failed");
#ifdef   ASTR_MSGS
        AStr_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        for (i=0; i<iMax; ++i) {
            eRc = AStr_Append( pObj, pBase );
            XCTAssertTrue( (ERESULT_OK(eRc)) );
            XCTAssertTrue( (((i+1) * AStr_getLength(pBase)) == AStr_getLength(pObj)) );
        }
        for (i=0; i<iMax; ++i) {
            pChrs = AStr_getData(pObj) + (i * AStr_getLength(pBase));
            XCTAssertTrue( (0 == strncmp(AStr_getData(pBase), pChrs, AStr_getLength(pBase))) );
        }
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    obj_Release(pBase);
    pBase = OBJ_NIL;
    obj_Release(pNumbers);
    pNumbers = OBJ_NIL;
    obj_Release(pUpper);
    pUpper = OBJ_NIL;
    obj_Release(pLower);
    pLower = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_AStr_Test02 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTR_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    const                   // 1234567890123456
    char            *pChrs =  "abcdefghijklmnop";
    ASTR_DATA       *pStr = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AStr_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTR);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("test failed");
#ifdef   ASTR_MSGS
        AStr_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        eRc = AStr_AppendMidA(pObj, pChrs, 0, 16);
        fprintf(stderr, "pObj = \"%s\"\n", AStr_getData(pObj));
        XCTAssertTrue( (ERESULT_OK(eRc)) );
        XCTAssertTrue( (16 == AStr_getLength(pObj)) );
        XCTAssertTrue( (0 == strcmp(pChrs, AStr_getData(pObj))) );
        AStr_Truncate(pObj, 0);
        
        eRc = AStr_AppendMidA(pObj, pChrs, 0, 5);
        fprintf(stderr, "pObj = \"%s\"\n", AStr_getData(pObj));
        XCTAssertTrue( (ERESULT_OK(eRc)) );
        XCTAssertTrue( (5 == AStr_getLength(pObj)) );
        XCTAssertTrue( (0 == strcmp("abcde", AStr_getData(pObj))) );

        pStr = AStr_NewFromMidA(pChrs, 0, 5);
        TestForNotNull(pStr, "");
        XCTAssertTrue( (5 == AStr_getLength(pStr)) );
        XCTAssertTrue( (0 == strcmp("abcde", AStr_getData(pStr))) );
        obj_Release(pStr);
        pStr = OBJ_NIL;

        eRc = AStr_AppendMidA(pObj, pChrs, 6, 2);
        fprintf(stderr, "pObj = \"%s\"\n", AStr_getData(pObj));
        XCTAssertTrue( (ERESULT_OK(eRc)) );
        XCTAssertTrue( (7 == AStr_getLength(pObj)) );
        XCTAssertTrue( (0 == strcmp("abcdefg", AStr_getData(pObj))) );
        AStr_Truncate(pObj, 0);
 
        pStr = AStr_NewFromMidA(pChrs, 6, 2);
        TestForNotNull(pStr, "");
        XCTAssertTrue( (2 == AStr_getLength(pStr)) );
        XCTAssertTrue( (0 == strcmp("fg", AStr_getData(pStr))) );
        obj_Release(pStr);
        pStr = OBJ_NIL;

        {
            ASTR_DATA       *pStr = AStr_ToDebugString(pObj, 4);
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



ERESULT         Test_AStr_Test03 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTR_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AStr_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTR);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("test failed");
#ifdef   ASTR_MSGS
        AStr_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        eRc = AStr_AppendPrint(pObj, "%03d,%03d", 54, 113);
        fprintf(stderr, "pObj=%s\n", AStr_getData(pObj));
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (7 == AStr_getLength(pObj)) );
        XCTAssertTrue( (0 == strcmp("054,113", AStr_getData(pObj))) );
        
        {
            ASTR_DATA       *pStr = AStr_ToDebugString(pObj, 4);
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



ERESULT         Test_AStr_Test04 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTR_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AStr_NewFromPrint("%03d,%03d", 54, 113);
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTR);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("test failed");
#ifdef   ASTR_MSGS
        AStr_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        XCTAssertTrue( (7 == AStr_getLength(pObj)) );
        fprintf(stderr, "pObj=%s\n", AStr_getData(pObj));
        XCTAssertTrue( (0 == strcmp("054,113", AStr_getData(pObj))) );

        {
            ASTR_DATA       *pStr = AStr_ToDebugString(pObj, 4);
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



ERESULT         Test_AStr_Test05 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTR_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    uint32_t        index;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AStr_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTR);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("test failed");
#ifdef   ASTR_MSGS
        AStr_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        eRc = AStr_AppendA( pObj, "xABCxDEFxG" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        index = 0;      // Start at the beginning.
        eRc = AStr_CharFindNextW32(pObj, &index, 'x');
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (1 == index) );
        
        ++index;
        eRc = AStr_CharFindNextW32(pObj, &index, 'x');
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (5 == index) );
        
        ++index;
        eRc = AStr_CharFindNextW32(pObj, &index, 'x');
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (9 == index) );
        
        ++index;
        eRc = AStr_CharFindNextW32(pObj, &index, 'x');
        XCTAssertTrue( (ERESULT_HAS_FAILED(eRc)) );
        XCTAssertTrue( (0 == index) );
        
        eRc = AStr_CharReplaceAllW32(pObj, 'x', 'y');
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (10 == AStr_getLength(pObj)) );
        XCTAssertTrue( (0 == strcmp("yABCyDEFyG", AStr_getData(pObj))) );
        
        {
            ASTR_DATA       *pStr = AStr_ToDebugString(pObj, 4);
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



ERESULT         Test_AStr_Test06 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTR_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    uint32_t        index;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AStr_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTR);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("test failed");
#ifdef   ASTR_MSGS
        AStr_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        eRc = AStr_AppendA( pObj, "xABCxDEFxG" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        index = 0;      // Start at the beginning.
        eRc = AStr_CharFindPrevW32(pObj, &index, 'x');
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (9 == index) );
        
        --index;
        eRc = AStr_CharFindPrevW32(pObj, &index, 'x');
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (5 == index) );
        
        --index;
        eRc = AStr_CharFindPrevW32(pObj, &index, 'x');
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (1 == index) );
        
        {
            ASTR_DATA       *pStr = AStr_ToDebugString(pObj, 4);
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



ERESULT         Test_AStr_Test07 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTR_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AStr_NewA("abcdefghijklmnop");
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTR);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("test failed");
#ifdef   ASTR_MSGS
        AStr_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        //eRc = AStr_CompareRightA(pObj, NULL);
        //XCTAssertTrue( (ERESULT_FAILED(eRc)) );
        eRc = AStr_CompareRightA(pObj, "abc");
        XCTAssertTrue( (eRc > 0) );
        eRc = AStr_CompareRightA(pObj, "nop");
        XCTAssertTrue( (eRc == 0) );
        eRc = AStr_CompareRightA(pObj, "xyz");
        XCTAssertTrue( (eRc < 0) );
        eRc = ERESULT_SUCCESS;
        
        {
            ASTR_DATA       *pStr = AStr_ToDebugString(pObj, 4);
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



ERESULT         Test_AStr_Test08 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTR_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    PATH_DATA       *pPath = OBJ_NIL;
    ASTR_DATA       *pOther = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AStr_NewFromEnv("HOME");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pPath = Path_NewA("~");
    XCTAssertFalse( (OBJ_NIL == pPath) );
    eRc = Path_Clean(pPath, NULL, NULL);
    XCTAssertTrue( (ERESULT_SUCCESSFUL(eRc)) );
    fprintf(stderr, "\tastr: \"%s\"\n", AStr_getData(pObj));
    fprintf(stderr, "\tPath: \"%s\"\n", Path_getData(pPath));
    eRc = AStr_Compare(pObj, (ASTR_DATA *)pPath);
    XCTAssertTrue( (0 == eRc) );
    obj_Release(pPath);
    pPath = OBJ_NIL;
    obj_Release(pObj);
    pObj = OBJ_NIL;

    pObj = AStr_NewA(TEST_FILES_DIR "/test.txt");
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTR);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("test failed");
#ifdef   ASTR_MSGS
        AStr_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        pPath = Path_NewFromAStr(pObj);
        XCTAssertFalse( (OBJ_NIL == pPath) );
        if (pPath) {
            eRc = AStr_ToUtf8File(pObj, pPath);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            pOther = AStr_NewFromUtf8File(pPath);
            XCTAssertFalse( (OBJ_NIL == pOther) );
            if (pOther) {
                eRc = AStr_Compare(pObj, pOther);
                XCTAssertTrue( (0 == eRc) );
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
            obj_Release(pPath);
            pPath = OBJ_NIL;
        }
        
        {
            ASTR_DATA       *pStr = AStr_ToDebugString(pObj, 4);
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



ERESULT         Test_AStr_Test09 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTR_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    uint16_t        num = 0xF0F0;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AStr_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTR);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("test failed");
#ifdef   ASTR_MSGS
        AStr_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        eRc = AStr_AppendHex16(pObj, num);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (4 == AStr_getLength(pObj)) );
        XCTAssertTrue( (0 == strcmp("F0F0", AStr_getData(pObj))) );
        
        {
            ASTR_DATA       *pStr = AStr_ToDebugString(pObj, 4);
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



ERESULT         Test_AStr_Test10 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTR_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    uint32_t        num = 0xF0F0F0F0;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AStr_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTR);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("test failed");
#ifdef   ASTR_MSGS
        AStr_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        eRc = AStr_AppendHex32(pObj, num);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        fprintf(stderr, "hex32 (%d)%s\n", AStr_getLength(pObj), AStr_getData(pObj));
        XCTAssertTrue( (8 == AStr_getLength(pObj)) );
        XCTAssertTrue( (0 == strcmp("F0F0F0F0", AStr_getData(pObj))) );
        
        {
            ASTR_DATA       *pStr = AStr_ToDebugString(pObj, 4);
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



ERESULT         Test_AStr_Test11 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTR_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AStr_NewA("def");
    TestForNotNull(pObj, "");
    XCTAssertTrue( (3 == AStr_getLength(pObj)) );
    XCTAssertTrue( (0 == strcmp("def", AStr_getData(pObj))) );
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTR);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("test failed");
#ifdef   ASTR_MSGS
        AStr_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        eRc = AStr_InsertA( pObj, 1, "abc" );
        XCTAssertTrue( (ERESULT_OK(eRc)) );
        XCTAssertTrue( (6 == AStr_getLength(pObj)) );
        XCTAssertTrue( (0 == strcmp("abcdef", AStr_getData(pObj))) );
        
        eRc = AStr_InsertA(pObj, 6, "ghi");
        XCTAssertTrue( (ERESULT_OK(eRc)) );
        XCTAssertTrue( (9 == AStr_getLength(pObj)) );
        XCTAssertTrue( (0 == strcmp("abcdeghif", AStr_getData(pObj))) );

        {
            ASTR_DATA       *pStr = AStr_ToDebugString(pObj, 4);
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



ERESULT         Test_AStr_Test12 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTR_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    ASTR_DATA       *pOtr = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AStr_NewA("abcdef");
    TestForNotNull(pObj, "");
    XCTAssertTrue( (6 == AStr_getLength(pObj)) );
    XCTAssertTrue( (0 == strcmp("abcdef", AStr_getData(pObj))) );
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTR);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("test failed");
#ifdef   ASTR_MSGS
        AStr_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        eRc = AStr_Left( pObj, 3, &pOtr );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertFalse( (OBJ_NIL == pOtr) );
        XCTAssertTrue( (3 == AStr_getLength(pOtr)) );
        XCTAssertTrue( (0 == strcmp("abc", AStr_getData(pOtr))) );
        obj_Release(pOtr);
        pOtr = OBJ_NIL;
        
        eRc = AStr_Mid( pObj, 4, 2, &pOtr );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertFalse( (OBJ_NIL == pOtr) );
        XCTAssertTrue( (2 == AStr_getLength(pOtr)) );
        XCTAssertTrue( (0 == strcmp("de", AStr_getData(pOtr))) );
        obj_Release(pOtr);
        pOtr = OBJ_NIL;
        
        eRc = AStr_Right(pObj, 3, &pOtr);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertFalse( (OBJ_NIL == pOtr) );
        XCTAssertTrue( (3 == AStr_getLength(pOtr)) );
        XCTAssertTrue( (0 == strcmp("def", AStr_getData(pOtr))) );
        obj_Release(pOtr);
        pOtr = OBJ_NIL;
        
        {
            ASTR_DATA       *pStr = AStr_ToDebugString(pObj, 4);
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



ERESULT         Test_AStr_Test13 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTR_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    ASTR_DATA       *pNew = OBJ_NIL;
    char            *pWrk;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AStr_NewA("kind:\"xyzzy\"\n");
    TestForNotNull(pObj, "");
    XCTAssertTrue( (13 == AStr_getLength(pObj)) );
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTR);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("test failed");
#ifdef   ASTR_MSGS
        AStr_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        fprintf(stderr, "pObj(%d)=%s\n", AStr_getLength(pObj), AStr_getData(pObj));
        
        pNew = AStr_NewParenthesizedFromAStr(pObj);
        XCTAssertFalse( (OBJ_NIL == pNew) );
        if (pNew) {
            fprintf(stderr, "pNew(%d)=%s\n", AStr_getLength(pNew), AStr_getData(pNew));
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            XCTAssertTrue( (18 == AStr_getLength(pNew)) );
            pWrk = "\"kind:\\\"xyzzy\\\"\\n\"";
            fprintf(stderr, "pWrk(%lu)=%s\n", strlen(pWrk), pWrk);
            XCTAssertTrue( (0 == strcmp(pWrk, AStr_getData(pNew))) );
            obj_Release(pNew);
            pNew = OBJ_NIL;
        }
        
        {
            ASTR_DATA       *pStr = AStr_ToDebugString(pObj, 4);
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



ERESULT         Test_AStr_Test14 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTR_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AStr_NewA("def");
    TestForNotNull(pObj, "");
    XCTAssertTrue( (3 == AStr_getLength(pObj)) );
    XCTAssertTrue( (0 == strcmp("def", AStr_getData(pObj))) );
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTR);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("test failed");
#ifdef   ASTR_MSGS
        AStr_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        eRc = AStr_Remove( pObj, 1, 1 );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (2 == AStr_getLength(pObj)) );
        XCTAssertTrue( (0 == strcmp("ef", AStr_getData(pObj))) );
        
        eRc = AStr_Remove( pObj, 2, 1 );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (1 == AStr_getLength(pObj)) );
        XCTAssertTrue( (0 == strcmp("e", AStr_getData(pObj))) );
        
        {
            ASTR_DATA       *pStr = AStr_ToDebugString(pObj, 4);
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



ERESULT         Test_AStr_Test15 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTR_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AStr_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTR);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("test failed");
#ifdef   ASTR_MSGS
        AStr_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        // Leading Spaces
        eRc = AStr_AppendA( pObj, "   bb" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (5 == AStr_getLength(pObj)) );
        
        eRc = AStr_Trim( pObj );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (2 == AStr_getLength(pObj)) );
        eRc = AStr_CompareA( pObj, "bb" );
        XCTAssertTrue( (0 == eRc) );
        
        // Trailing spaces
        eRc = AStr_AppendA( pObj, "   " );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (5 == AStr_getLength(pObj)) );
        
        eRc = AStr_Trim( pObj );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (2 == AStr_getLength(pObj)) );
        eRc = AStr_CompareA( pObj, "bb" );
        XCTAssertTrue( (0 == eRc) );
        
        eRc = AStr_Truncate( pObj, 0 );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (0 == AStr_getLength(pObj)) );
        
        // Leading and Trailing spaces
        eRc = AStr_AppendA( pObj, "   bb   " );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (8 == AStr_getLength(pObj)) );
        
        eRc = AStr_Trim( pObj );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (2 == AStr_getLength(pObj)) );
        eRc = AStr_CompareA( pObj, "bb" );
        XCTAssertTrue( (0 == eRc) );
        
        {
            ASTR_DATA       *pStr = AStr_ToDebugString(pObj, 4);
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



ERESULT         Test_AStr_Test16 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTR_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    ASTR_DATA       *pNew;
    const
    char            *pChrConA = "def\u0414\n";
    const
    char            *pChrConA2 = "def\\u0414\\n";

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AStr_NewA("def");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    eRc = AStr_AppendCharW32(pObj, 0x0414);   // Cyrillic Capital D
    XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
    eRc = AStr_AppendCharA(pObj, '\n');
    fprintf(stderr, "inputLen=%d\n", AStr_getLength(pObj));
    XCTAssertTrue( (5 == AStr_getLength(pObj)) );
    XCTAssertTrue( (0 == memcmp(pChrConA, AStr_getData(pObj), 5)) );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTR);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("test failed");
#ifdef   ASTR_MSGS
        AStr_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        pNew = AStr_ToChrCon(pObj);
        XCTAssertFalse( (OBJ_NIL == pNew) );
        XCTAssertTrue( (11 == AStr_getLength(pNew)) );
        fprintf(stderr, "outputLen=%d\n", AStr_getLength(pNew));
        fprintf(stderr, "output=%s\n", AStr_getData(pNew));
        XCTAssertTrue( (0 == memcmp(pChrConA2, AStr_getData(pNew), 11)) );
        obj_Release(pNew);
        pNew = OBJ_NIL;
        
        {
            ASTR_DATA       *pStr = AStr_ToDebugString(pObj, 4);
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



ERESULT         Test_AStr_Test17 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTR_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    uint32_t        crc;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AStr_NewA("abc");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    XCTAssertTrue( (3 == AStr_getLength(pObj)) );
    XCTAssertTrue( (0 == strcmp("abc", AStr_getData(pObj))) );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTR);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("test failed");
#ifdef   ASTR_MSGS
        AStr_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        crc = AStr_getCrcIEEE(pObj);
        fprintf(stderr, "\tcrc(\"abc\") = %u\n", crc);
        XCTAssertTrue( (2807916624 == crc) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    pObj = AStr_NewA("");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    XCTAssertTrue( (0 == AStr_getLength(pObj)) );
    XCTAssertTrue( (0 == strcmp("", AStr_getData(pObj))) );
    if (pObj) {
        
        crc = AStr_getCrcIEEE(pObj);
        fprintf(stderr, "\tcrc(\"\") = %u\n", crc);
        //XCTAssertTrue( (2807916624 == crc) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_AStr_Test18 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTR_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    ASTR_DATA       *pJsonStr = OBJ_NIL;
    ASTR_DATA       *pJsonStrOut = OBJ_NIL;
    const
    char            *pJsonStrA = "{ "
        "\"objectType\":\"AStr\", "
        "\"len\":3, "
        "\"crc\":2807916624, "
        "\"data\":\"abc\""
    
    "}\n";
    uint32_t        iRc;
    int             index = 0;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AStr_NewA("abc");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    XCTAssertTrue( (1 == obj_getRetainCount(pObj)) );
    XCTAssertTrue( (3 == AStr_getLength(pObj)) );
    XCTAssertTrue( (0 == strcmp("abc", AStr_getData(pObj))) );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTR);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("test failed");
#ifdef   ASTR_MSGS
        AStr_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        pJsonStr = AStr_ToJson(pObj);
        fprintf(
                stderr,
                "\tJSON(\"abc\") = (%p) \"%s\"\n",
                pJsonStr,
                AStr_getData(pJsonStr)
        );
        iRc = str_CompareSpcl(AStr_getData(pJsonStr), pJsonStrA, &index);
        fprintf(stderr, "\tCompareSpcl: %d, index=%d\n", iRc, index);
        XCTAssertTrue( (0 == iRc) );
        pJsonStrOut = AStr_NewFromJsonString(pJsonStr);
        XCTAssertFalse( (OBJ_NIL == pJsonStrOut) );
        fprintf(
                stderr,
                "\tJSON_OUT(\"abc\") = (%p) \"%s\"\n",
                pJsonStrOut,
                AStr_getData(pJsonStrOut)
        );
        XCTAssertTrue( (3 == AStr_getLength(pJsonStrOut)) );
        XCTAssertTrue( (0 == strcmp("abc", AStr_getData(pJsonStrOut))) );
        XCTAssertTrue( (1 == obj_getRetainCount(pJsonStrOut)) );
        obj_Release(pJsonStrOut);
        pJsonStrOut = OBJ_NIL;
        XCTAssertTrue( (1 == obj_getRetainCount(pJsonStr)) );
        obj_Release(pJsonStr);
        pJsonStr = OBJ_NIL;

        XCTAssertTrue( (1 == obj_getRetainCount(pObj)) );
        
        {
            ASTR_DATA       *pStr = AStr_ToDebugString(pObj, 4);
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



ERESULT         Test_AStr_Test19 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTR_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    ASTR_DATA       *pJsonStr = OBJ_NIL;
    ASTR_DATA       *pJsonStrOut = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AStr_NewA("");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    XCTAssertTrue( (0 == AStr_getLength(pObj)) );
    XCTAssertTrue( (0 == strcmp("", AStr_getData(pObj))) );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTR);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("test failed");
#ifdef   ASTR_MSGS
        AStr_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        pJsonStr = AStr_ToJson(pObj);
        fprintf(stderr, "\tJSON(\"\") = %s\n", AStr_getData(pJsonStr));
        pJsonStrOut = AStr_NewFromJsonString(pJsonStr);
        XCTAssertFalse( (OBJ_NIL == pJsonStrOut) );
        XCTAssertTrue( (0 == AStr_getLength(pJsonStrOut)) );
        XCTAssertTrue( (0 == strcmp("", AStr_getData(pJsonStrOut))) );
        obj_Release(pJsonStrOut);
        pJsonStrOut = OBJ_NIL;
        obj_Release(pJsonStr);
        pJsonStr = OBJ_NIL;

        {
            ASTR_DATA       *pStr = AStr_ToDebugString(pObj, 4);
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



ERESULT         Test_AStr_Test20 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTR_DATA       *pStr = OBJ_NIL;
    //bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pStr = AStr_NewA("xyzzy.dmg");
    XCTAssertFalse( (OBJ_NIL == pStr) );
    if (pStr) {
        eRc = AStr_MatchA(pStr, "*.dmg");
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
    }
    pStr = AStr_NewA("xyzzy.txt");
    XCTAssertFalse( (OBJ_NIL == pStr) );
    if (pStr) {
        eRc = AStr_MatchA(pStr, "*.dmg");
        XCTAssertTrue( (ERESULT_FAILED(eRc)) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
    }
    pStr = AStr_NewA("xyzzy.dmg");
    XCTAssertFalse( (OBJ_NIL == pStr) );
    if (pStr) {
        eRc = AStr_MatchA(pStr, "x?zz?.dmg");
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
    }
    pStr = AStr_NewA("xyzzy.dmg");
    XCTAssertFalse( (OBJ_NIL == pStr) );
    if (pStr) {
        eRc = AStr_MatchA(pStr, "x?zy?.dmg");
        XCTAssertTrue( (ERESULT_FAILED(eRc)) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
    }
    pStr = AStr_NewA("xyzzy.dmg");
    XCTAssertFalse( (OBJ_NIL == pStr) );
    if (pStr) {
        eRc = AStr_MatchA(pStr, "x?zy?.*");
        XCTAssertTrue( (ERESULT_FAILED(eRc)) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
    }
    
    eRc = ERESULT_SUCCESS;
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_AStr_Test21 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTR_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    const
    char            *pHomeA = NULL;
    int             len = 0;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pHomeA = getenv("HOME");
    if (pHomeA) {
        len = (int)strlen(pHomeA);
    }
    pObj = AStr_NewA("${HOME}");
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTR);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("test failed");
#ifdef   ASTR_MSGS
        AStr_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        eRc = AStr_ExpandVars(pObj, NULL, OBJ_NIL);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (len == AStr_getLength((ASTR_DATA *)pObj)) );
        XCTAssertTrue( (0 == AStr_CompareA((ASTR_DATA *)pObj, pHomeA)) );
        {
            ASTR_DATA       *pStr = AStr_ToDebugString(pObj, 4);
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



ERESULT         Test_AStr_Test22 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTR_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    ASTR_DATA       *pStr = OBJ_NIL;
    const
    char            *pHomeA = NULL;
    int             len = 0;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pHomeA = getenv("HOME");
    if (pHomeA) {
        len = (int)strlen(pHomeA);
        pStr = AStr_NewA(pHomeA);
        eRc = AStr_AppendA(pStr, "$");
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        eRc = AStr_AppendA(pStr, pHomeA);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
    }
    pObj = AStr_NewA("${HOME}$${HOME}");
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTR);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("test failed");
#ifdef   ASTR_MSGS
        AStr_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        eRc = AStr_ExpandVars(pObj, NULL, OBJ_NIL);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (AStr_getLength(pStr) == AStr_getLength((ASTR_DATA *)pObj)) );
        XCTAssertTrue( (0 == AStr_Compare((ASTR_DATA *)pObj, pStr)) );
        
        {
            ASTR_DATA       *pStr = AStr_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    obj_Release(pStr);
    pStr = NULL;

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_AStr_Test23 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    //ASTR_DATA       *pObj = OBJ_NIL;
    //bool            fRc;
    int             iRc;
    const
    char            *pTest1A = "/${test1}";
    const
    char            *pAns1A = "/TestString1";
    const
    char            *pTest2A = "/${test1}/${test2}";
    const
    char            *pAns2A = "/TestString1/TestString2";
    ASTR_DATA       *pTest = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pTest = AStr_NewA(pTest1A);
    XCTAssertFalse( (OBJ_NIL == pTest) );
    obj_TraceSet(pTest, true);
    eRc = AStr_ExpandVars(pTest, findTest, OBJ_NIL);
    fprintf(stderr, "expanded: \"%s\"\n", AStr_getData(pTest));
    XCTAssertTrue( (ERESULT_OK(eRc)) );
    iRc = strcmp(AStr_getData(pTest), pAns1A);
    XCTAssertTrue( (0 == iRc) );
    obj_Release(pTest);
    pTest = OBJ_NIL;
    
    pTest = AStr_NewA(pTest2A);
    XCTAssertFalse( (OBJ_NIL == pTest) );
    obj_TraceSet(pTest, true);
    eRc = AStr_ExpandVars(pTest, findTest, OBJ_NIL);
    fprintf(stderr, "expanded: \"%s\"\n", AStr_getData(pTest));
    XCTAssertTrue( (ERESULT_OK(eRc)) );
    iRc = strcmp(AStr_getData(pTest), pAns2A);
    XCTAssertTrue( (0 == iRc) );
    obj_Release(pTest);
    pTest = OBJ_NIL;
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_AStr_Test24 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTR_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    ASTR_DATA       *pStr = OBJ_NIL;
    ASTRARRAY_DATA  *pArray = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AStr_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTR);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("test failed");
#ifdef   ASTR_MSGS
        AStr_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        pArray = AStr_SplitOnCharW32(pObj, '/');
        XCTAssertFalse( (OBJ_NIL == pArray) );
        //eRc = obj_getLastError(pObj);
        //XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        //XCTAssertTrue( (AStr_getLength(pStr) == AStr_getLength((ASTR_DATA *)pObj)) );
        XCTAssertTrue( (0 == AStrArray_getSize(pArray)) );
        
        obj_Release(pArray);
        pArray = OBJ_NIL;
        
        {
            ASTR_DATA       *pStr = AStr_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    obj_Release(pStr);
    pStr = NULL;
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_AStr_Test25 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTR_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    ASTR_DATA       *pStr = OBJ_NIL;
    ASTRARRAY_DATA  *pArray = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AStr_NewA("123");
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTR);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("test failed");
#ifdef   ASTR_MSGS
        AStr_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        pArray = AStr_SplitOnCharW32(pObj, '/');
        XCTAssertFalse( (OBJ_NIL == pArray) );
        //eRc = obj_getLastError(pObj);
        //XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        //XCTAssertTrue( (AStr_getLength(pStr) == AStr_getLength((ASTR_DATA *)pObj)) );
        XCTAssertTrue( (1 == AStrArray_getSize(pArray)) );
        pStr = AStrArray_Get(pArray, 1);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        XCTAssertTrue( (0 == AStr_CompareA(pStr, "123")) );

        obj_Release(pArray);
        pArray = OBJ_NIL;
        {
            ASTR_DATA       *pStr = AStr_ToDebugString(pObj, 4);
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



ERESULT         Test_AStr_Test26 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTR_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    ASTR_DATA       *pStr = OBJ_NIL;
    ASTRARRAY_DATA  *pArray = OBJ_NIL;
    //int             len = 0;
    const
    char            *pTestStringA = "1/2/3/4/5";

    fprintf(stderr, "Performing: %s\n", pTestName);

    fprintf(stderr, "\tTest String: %s\n", pTestStringA);
    pObj = AStr_NewA(pTestStringA);
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTR);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("test failed");
#ifdef   ASTR_MSGS
        AStr_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        pArray = AStr_SplitOnCharW32(pObj, '/');
        XCTAssertFalse( (OBJ_NIL == pArray) );
        //eRc = obj_getLastError(pObj);
        //XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        //XCTAssertTrue( (AStr_getLength(pStr) == AStr_getLength((ASTR_DATA *)pObj)) );
        fprintf(stderr, "\tArray Size = %d\n", AStrArray_getSize(pArray));
        XCTAssertTrue( (5 == AStrArray_getSize(pArray)) );
        pStr = AStrArray_Get(pArray, 1);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        XCTAssertTrue( (0 == AStr_CompareA(pStr, "1")) );
        pStr = AStrArray_Get(pArray, 2);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        XCTAssertTrue( (0 == AStr_CompareA(pStr, "2")) );
        pStr = AStrArray_Get(pArray, 3);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        XCTAssertTrue( (0 == AStr_CompareA(pStr, "3")) );
        pStr = AStrArray_Get(pArray, 4);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        XCTAssertTrue( (0 == AStr_CompareA(pStr, "4")) );
        pStr = AStrArray_Get(pArray, 5);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        XCTAssertTrue( (0 == AStr_CompareA(pStr, "5")) );

        obj_Release(pArray);
        pArray = OBJ_NIL;
        {
            ASTR_DATA       *pStr = AStr_ToDebugString(pObj, 4);
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



ERESULT         Test_AStr_Test27 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTR_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    ASTR_DATA       *pStr = OBJ_NIL;
    ASTRARRAY_DATA  *pArray = OBJ_NIL;
    //int             len = 0;
    const
    char            *pTestStringA = "1/";

    fprintf(stderr, "Performing: %s\n", pTestName);

    fprintf(stderr, "\tTest String: %s\n", pTestStringA);
    pObj = AStr_NewA(pTestStringA);
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTR);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("test failed");
#ifdef   ASTR_MSGS
        AStr_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        pArray = AStr_SplitOnCharW32(pObj, '/');
        XCTAssertFalse( (OBJ_NIL == pArray) );
        //eRc = obj_getLastError(pObj);
        //XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        //XCTAssertTrue( (AStr_getLength(pStr) == AStr_getLength((ASTR_DATA *)pObj)) );
        fprintf(stderr, "\tArray Size = %d\n", AStrArray_getSize(pArray));
        XCTAssertTrue( (1 == AStrArray_getSize(pArray)) );
        pStr = AStrArray_Get(pArray, 1);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        XCTAssertTrue( (0 == AStr_CompareA(pStr, "1")) );
        
        obj_Release(pArray);
        pArray = OBJ_NIL;
        
        {
            ASTR_DATA       *pStr = AStr_ToDebugString(pObj, 4);
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



ERESULT         Test_AStr_Test28 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTR_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    ASTR_DATA       *pStr = OBJ_NIL;
    ASTRARRAY_DATA  *pArray = OBJ_NIL;
    //int             len = 0;
    const
    char            *pTestStringA = "/";

    fprintf(stderr, "Performing: %s\n", pTestName);

    fprintf(stderr, "\tTest String: %s\n", pTestStringA);
    pObj = AStr_NewA(pTestStringA);
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTR);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("test failed");
#ifdef   ASTR_MSGS
        AStr_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        pArray = AStr_SplitOnCharW32(pObj, '/');
        XCTAssertFalse( (OBJ_NIL == pArray) );
        //eRc = obj_getLastError(pObj);
        //XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        //XCTAssertTrue( (AStr_getLength(pStr) == AStr_getLength((ASTR_DATA *)pObj)) );
        fprintf(stderr, "\tArray Size = %d\n", AStrArray_getSize(pArray));
        XCTAssertTrue( (1 == AStrArray_getSize(pArray)) );
        pStr = AStrArray_Get(pArray, 1);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        XCTAssertTrue( (0 == AStr_getLength(pStr)) );

        obj_Release(pArray);
        pArray = OBJ_NIL;

        {
            ASTR_DATA       *pStr = AStr_ToDebugString(pObj, 4);
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



ERESULT         Test_AStr_Test29 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTR_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    W32CHR_T        chr;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj =  AStr_NewA("abc");
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTR);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("test failed");
#ifdef   ASTR_MSGS
        AStr_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        chr = AStr_CharGetFirstW32(pObj);
        fprintf(stderr, "\tFirst = (0x%04X)%c\n", chr, chr);
        XCTAssertTrue( ('a' == chr) );
        
        chr = AStr_CharGetLastW32(pObj);
        fprintf(stderr, "\tLast = (0x%04X)%c\n", chr, chr);
        XCTAssertTrue( ('c' == chr) );
        
        {
            ASTR_DATA       *pStr = AStr_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    pObj = AStr_NewA("a");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        chr = AStr_CharGetFirstW32(pObj);
        fprintf(stderr, "\tFirst = (0x%04X)%c\n", chr, chr);
        XCTAssertTrue( ('a' == chr) );
        
        chr = AStr_CharGetLastW32(pObj);
        fprintf(stderr, "\tLast = (0x%04X)%c\n", chr, chr);
        XCTAssertTrue( ('a' == chr) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    pObj = AStr_New( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        chr = AStr_CharGetFirstW32(pObj);
        fprintf(stderr, "\tFirst = (0x%08X)%c\n", chr, chr);
        XCTAssertTrue( (-1 == chr) );
        
        chr = AStr_CharGetLastW32(pObj);
        fprintf(stderr, "\tLast = (0x%08X)%c\n", chr, chr);
        XCTAssertTrue( (-1 == chr) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_AStr_Test30 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTR_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    const
    char            *pLowerA = "abcdefghijklmnopqrstuvwxyz";
    const
    char            *pUpperA = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    ASTR_DATA       *pLower = OBJ_NIL;
    ASTR_DATA       *pUpper = OBJ_NIL;
    ASTR_DATA       *pWrk = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AStr_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTR);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("test failed");
#ifdef   ASTR_MSGS
        AStr_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        pLower = AStr_NewA(pLowerA);
        XCTAssertFalse( (OBJ_NIL == pLower) );
        XCTAssertTrue( (26 == AStr_getLength(pLower)) );
        XCTAssertTrue( (0 == strcmp(pLowerA, AStr_getData(pLower))) );
        
        pUpper = AStr_NewA(pUpperA);
        XCTAssertFalse( (OBJ_NIL == pUpper) );
        XCTAssertTrue( (26 == AStr_getLength(pUpper)) );
        XCTAssertTrue( (0 == strcmp(pUpperA, AStr_getData(pUpper))) );

        pWrk = AStr_ToLower(pUpper);
        XCTAssertFalse( (OBJ_NIL == pWrk) );
        XCTAssertTrue( (26 == AStr_getLength(pWrk)) );
        XCTAssertTrue( (0 == strcmp(pLowerA, AStr_getData(pWrk))) );
        obj_Release(pWrk);
        pWrk = OBJ_NIL;
        
        pWrk = AStr_ToUpper(pLower);
        XCTAssertFalse( (OBJ_NIL == pWrk) );
        XCTAssertTrue( (26 == AStr_getLength(pWrk)) );
        XCTAssertTrue( (0 == strcmp(pUpperA, AStr_getData(pWrk))) );
        obj_Release(pWrk);
        pWrk = OBJ_NIL;
        
        obj_Release(pUpper);
        pUpper = OBJ_NIL;
        obj_Release(pLower);
        pLower = OBJ_NIL;

        {
            ASTR_DATA       *pStr = AStr_ToDebugString(pObj, 4);
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



ERESULT         Test_AStr_Test31 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTR_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    //                                  1111111111222222222
    //                         1234567890123456789012345678
    const
    char            *pStr1A = "isa isa isa";
    const
    W32CHR_T        szSrchW32[] = {'i','s','a',0};
    const
    char            *pSrchA = "isa";
    uint32_t        offset = 0;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AStr_NewA(pStr1A);
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTR);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("test failed");
#ifdef   ASTR_MSGS
        AStr_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        eRc = AStr_FindNextW32(pObj, szSrchW32, &offset);
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        XCTAssertTrue( (1 == offset) );
        offset += utf8_StrLenW32(szSrchW32);

        eRc = AStr_FindNextW32(pObj, szSrchW32, &offset);
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        XCTAssertTrue( (5 == offset) );
        offset += utf8_StrLenW32(szSrchW32);

        eRc = AStr_FindNextW32(pObj, szSrchW32, &offset);
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        XCTAssertTrue( (9 == offset) );
        offset += utf8_StrLenW32(szSrchW32);

        eRc = AStr_FindNextW32(pObj, szSrchW32, &offset);
        XCTAssertTrue( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (0 == offset) );

        eRc = AStr_FindNextA(pObj, pSrchA, &offset);
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        XCTAssertTrue( (1 == offset) );
        offset += utf8_StrLenA(pSrchA);

        eRc = AStr_FindNextA(pObj, pSrchA, &offset);
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        XCTAssertTrue( (5 == offset) );
        offset += utf8_StrLenA(pSrchA);

        eRc = AStr_FindNextA(pObj, pSrchA, &offset);
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        XCTAssertTrue( (9 == offset) );
        offset += utf8_StrLenA(pSrchA);

        eRc = AStr_FindNextA(pObj, pSrchA, &offset);
        XCTAssertTrue( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (0 == offset) );

        {
            ASTR_DATA       *pStr = AStr_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        eRc = ERESULT_SUCCESS;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_AStr_Test32 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTR_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    //                             1111111111222222222
    //                    1234567890123456789012345678
    const
    char            *pStr1A = "isa isa isa";
    const
    W32CHR_T        szSrchW32[] = {'i','s','a',0};
    const
    char            *pSrchA = "isa";
    uint32_t        offset = 0;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AStr_NewA(pStr1A);
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTR);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("test failed");
#ifdef   ASTR_MSGS
        AStr_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        eRc = AStr_FindNextW32(pObj, szSrchW32, &offset);
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        XCTAssertTrue( (1 == offset) );
        offset += utf8_StrLenW32(szSrchW32);

        eRc = AStr_FindNextW32(pObj, szSrchW32, &offset);
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        XCTAssertTrue( (5 == offset) );
        offset += utf8_StrLenW32(szSrchW32);

        eRc = AStr_FindNextW32(pObj, szSrchW32, &offset);
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        XCTAssertTrue( (9 == offset) );
        offset += utf8_StrLenW32(szSrchW32);

        eRc = AStr_FindNextW32(pObj, szSrchW32, &offset);
        XCTAssertTrue( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (0 == offset) );

        eRc = AStr_FindNextA(pObj, pSrchA, &offset);
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        XCTAssertTrue( (1 == offset) );
        offset += utf8_StrLenA(pSrchA);

        eRc = AStr_FindNextA(pObj, pSrchA, &offset);
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        XCTAssertTrue( (5 == offset) );
        offset += utf8_StrLenA(pSrchA);

        eRc = AStr_FindNextA(pObj, pSrchA, &offset);
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        XCTAssertTrue( (9 == offset) );
        offset += utf8_StrLenA(pSrchA);

        eRc = AStr_FindNextA(pObj, pSrchA, &offset);
        XCTAssertTrue( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (0 == offset) );

        {
            ASTR_DATA       *pStr = AStr_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    eRc = ERESULT_SUCCESS;
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_AStr_Test33 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTR_DATA       *pObj = OBJ_NIL;
    bool            fRc;
    ASTR_DATA       *pSQL = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AStr_NewA("Hi there!");
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTR);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("test failed");
#ifdef   ASTR_MSGS
        AStr_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        pSQL = AStr_ToSQL(pObj);
        XCTAssertFalse( (OBJ_NIL == pSQL) );
        XCTAssertTrue( (0 == AStr_CompareA(pSQL, "'Hi there!'")) );
        obj_Release(pSQL);
        pSQL = OBJ_NIL;
        
        {
            ASTR_DATA       *pStr = AStr_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    pObj = AStr_NewA("Hidden 'quotes'");
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTR);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("test failed");
#ifdef   ASTR_MSGS
        AStr_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        pSQL = AStr_ToSQL(pObj);
        XCTAssertFalse( (OBJ_NIL == pSQL) );
        XCTAssertTrue( (0 == AStr_CompareA(pSQL, "'Hidden ''quotes'''")) );
        obj_Release(pSQL);
        pSQL = OBJ_NIL;
        
        {
            ASTR_DATA       *pStr = AStr_ToDebugString(pObj, 4);
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



ERESULT         Test_AStr_Test34 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTR_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AStr_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTR);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("test failed");
#ifdef   ASTR_MSGS
        AStr_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        {
            ASTR_DATA       *pStr = AStr_ToDebugString(pObj, 4);
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



ERESULT         Test_AStr_Test35 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTR_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AStr_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTR);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("test failed");
#ifdef   ASTR_MSGS
        AStr_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        {
            ASTR_DATA       *pStr = AStr_ToDebugString(pObj, 4);
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



ERESULT         Test_AStr_Test36 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTR_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AStr_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTR);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("test failed");
#ifdef   ASTR_MSGS
        AStr_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        {
            ASTR_DATA       *pStr = AStr_ToDebugString(pObj, 4);
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



ERESULT         Test_AStr_Test37 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTR_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AStr_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTR);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("test failed");
#ifdef   ASTR_MSGS
        AStr_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        {
            ASTR_DATA       *pStr = AStr_ToDebugString(pObj, 4);
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



ERESULT         Test_AStr_Test38 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTR_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AStr_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTR);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("test failed");
#ifdef   ASTR_MSGS
        AStr_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        {
            ASTR_DATA       *pStr = AStr_ToDebugString(pObj, 4);
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



ERESULT         Test_AStr_Test39 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTR_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AStr_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_ASTR);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("test failed");
#ifdef   ASTR_MSGS
        AStr_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        {
            ASTR_DATA       *pStr = AStr_ToDebugString(pObj, 4);
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
    TestExec("OpenClose", Test_AStr_OpenClose, NULL, NULL);
    //TestExec("Copy01", Test_AStr_Copy01, NULL, NULL);
    TestExec("Test01", Test_AStr_Test01, NULL, NULL);
    TestExec("Test02", Test_AStr_Test02, NULL, NULL);
    TestExec("Test03", Test_AStr_Test03, NULL, NULL);
    TestExec("Test04", Test_AStr_Test04, NULL, NULL);
    TestExec("Test05", Test_AStr_Test05, NULL, NULL);
    TestExec("Test06", Test_AStr_Test06, NULL, NULL);
    TestExec("Test07", Test_AStr_Test07, NULL, NULL);
    TestExec("Test08", Test_AStr_Test08, NULL, NULL);
    TestExec("Test09", Test_AStr_Test09, NULL, NULL);
    TestExec("Test10", Test_AStr_Test10, NULL, NULL);
    TestExec("Test11", Test_AStr_Test11, NULL, NULL);
    TestExec("Test12", Test_AStr_Test12, NULL, NULL);
    TestExec("Test13", Test_AStr_Test13, NULL, NULL);
    TestExec("Test14", Test_AStr_Test14, NULL, NULL);
    TestExec("Test15", Test_AStr_Test15, NULL, NULL);
    TestExec("Test16", Test_AStr_Test16, NULL, NULL);
    TestExec("Test17", Test_AStr_Test17, NULL, NULL);
    TestExec("Test18", Test_AStr_Test18, NULL, NULL);
    TestExec("Test19", Test_AStr_Test19, NULL, NULL);
    TestExec("Test20", Test_AStr_Test20, NULL, NULL);
    TestExec("Test21", Test_AStr_Test21, NULL, NULL);
    TestExec("Test22", Test_AStr_Test22, NULL, NULL);
    TestExec("Test23", Test_AStr_Test23, setUp1, tearDown1);
    TestExec("Test24", Test_AStr_Test24, NULL, NULL);
    TestExec("Test25", Test_AStr_Test25, NULL, NULL);
    TestExec("Test26", Test_AStr_Test26, NULL, NULL);
    TestExec("Test27", Test_AStr_Test27, NULL, NULL);
    TestExec("Test28", Test_AStr_Test28, NULL, NULL);
    TestExec("Test29", Test_AStr_Test29, NULL, NULL);
    TestExec("Test30", Test_AStr_Test30, NULL, NULL);
    TestExec("Test31", Test_AStr_Test31, NULL, NULL);
    TestExec("Test32", Test_AStr_Test32, NULL, NULL);
    TestExec("Test33", Test_AStr_Test33, NULL, NULL);
    TestExec("Test34", Test_AStr_Test34, NULL, NULL);
    TestExec("Test35", Test_AStr_Test35, NULL, NULL);
    TestExec("Test36", Test_AStr_Test36, NULL, NULL);
    TestExec("Test37", Test_AStr_Test37, NULL, NULL);
    TestExec("Test38", Test_AStr_Test38, NULL, NULL);
    TestExec("Test39", Test_AStr_Test39, NULL, NULL);

    obj_Release(pTest);
    pTest = OBJ_NIL;

    // Return to Operating System.
    return 0;
}



