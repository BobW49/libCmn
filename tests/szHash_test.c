/*
 *	Generated 06/30/2017 09:01:13
 */





// All code under test must be linked into the Unit Test bundle
// Test Macros:
//      TINYTEST_ASSERT(condition)
//      TINYTEST_ASSERT_MSG(condition,msg)
//      TINYTEST_EQUAL(expected, actual)
//      TINYTEST_EQUAL_MSG(expected, actual, msg)
//      TINYTEST_FALSE_MSG(condition,msg)
//      TINYTEST_FALSE(condition)
//      TINYTEST_TRUE_MSG(pointer,msg)
//      TINYTEST_TRUE(condition)





#include    <tinytest.h>
#include    <cmn_defs.h>
#include    <trace.h>
#include    <szHash_internal.h>
#include    <str.h>
#include    <utf8.h>



static
const
char        *strings[] = {
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






int         setUp(
    const
    char        *pTestName
)
{
    mem_Init( );
    trace_Shared( ); 
    // Put setup code here. This method is called before the invocation of each
    // test method in the class.
    
    return 1; 
}


int         tearDown(
    const
    char        *pTestName
)
{
    // Put teardown code here. This method is called after the invocation of each
    // test method in the class.

    
    trace_SharedReset( ); 
     if (mem_Dump( ) ) {
        fprintf(
                stderr,
                "\x1b[1m"
                "\x1b[31m"
                "ERROR: "
                "\x1b[0m"
                "Leaked memory areas were found!\n"
        );
        exitCode = 4;
        return 0;
    }
    mem_Release( );
    
    return 1; 
}






int         test_szHash_OpenClose(
    const
    char        *pTestName
)
{
    SZHASH_DATA	*pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = szHash_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = szHash_Init( pObj, 5 );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_szHash_AddFindDelete1(
    const
    char        *pTestName
)
{
    SZHASH_DATA     *pHash;
    uint32_t        i;
    uint32_t        cnt;
    ERESULT         eRc;
    void            *pVoid;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pHash = szHash_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pHash) );
    pHash = szHash_Init( pHash, 5 );
    TINYTEST_FALSE( (OBJ_NIL == pHash) );
    if (pHash) {
        
        szHash_setComputeHash( pHash, str_HashA, str_HashW32 );
        szHash_setCompare( pHash, utf8_StrCmp, utf8_StrCmpAW32 );

        for (i=0; i<10; ++i) {
            eRc = szHash_AddA(pHash, strings[i], (void *)strings[i]);
            TINYTEST_TRUE( (ERESULT_IS_SUCCESSFUL(eRc)) );
            cnt = szHash_getSize(pHash);
            TINYTEST_TRUE( (cnt == (i+1)) );
        }
        
        for (i=0; i<10; ++i) {
            pVoid = szHash_FindA(pHash, strings[i]);
            TINYTEST_TRUE( (pVoid == strings[i]) );
        }
        
        pVoid = szHash_FindA(pHash, strings[3]);
        TINYTEST_TRUE( (pVoid == strings[3]) );
        pVoid = szHash_FindA(pHash, strings[9]);
        TINYTEST_TRUE( (pVoid == strings[9]) );
        pVoid = szHash_FindA(pHash, strings[6]);
        TINYTEST_TRUE( (pVoid == strings[6]) );
        
        eRc = szHash_DeleteA(pHash, strings[5]);
        TINYTEST_TRUE( (ERESULT_IS_SUCCESSFUL(eRc)) );
        cnt = szHash_getSize(pHash);
        TINYTEST_TRUE( (cnt == 9) );
        pVoid = szHash_FindA(pHash, strings[5]);
        TINYTEST_TRUE( (pVoid == NULL) );
        
        eRc = szHash_DeleteA(pHash, strings[8]);
        TINYTEST_TRUE( (ERESULT_IS_SUCCESSFUL(eRc)) );
        cnt = szHash_getSize(pHash);
        TINYTEST_TRUE( (cnt == 8) );
        pVoid = szHash_FindA(pHash, strings[8]);
        TINYTEST_TRUE( (pVoid == NULL) );
        
        obj_Release(pHash);
        pHash = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_szHash);
  TINYTEST_ADD_TEST(test_szHash_AddFindDelete1,setUp,tearDown);
  TINYTEST_ADD_TEST(test_szHash_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_szHash);





