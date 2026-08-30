// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Abstract Syntax Tree (Ast)  Test Program
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
#include    <Ast_internal.h>
#include    <JsonIn.h>
#include    <SrcErrors.h>
#include    <szTbl.h>


//#define     STATE_MACHINE   1


static
uint32_t        count = 0;
static
AST_ENTRY       *pEntries[64];
static
const
char            *pCorrect = NULL;
static
int             correctLen = 0;
static
int             correctCur = 0;
static
bool            fPrintVisits = true;



static
AST_DATA *      createTestTree01 (
    TEST_DATA       *this
)
{
    AST_DATA        *pTree  = OBJ_NIL;
    AST_ENTRY       *pNodeA = OBJ_NIL;
    AST_ENTRY       *pNodeB = OBJ_NIL;
    AST_ENTRY       *pNodeC = OBJ_NIL;
    AST_ENTRY       *pNodeD = OBJ_NIL;
    AST_ENTRY       *pNodeE = OBJ_NIL;
    AST_ENTRY       *pNodeF = OBJ_NIL;
    AST_ENTRY       *pNodeG = OBJ_NIL;
    AST_ENTRY       *pNodeH = OBJ_NIL;
    AST_ENTRY       *pNodeI = OBJ_NIL;
    AST_ENTRY       *pNodeJ = OBJ_NIL;
    AST_ENTRY       *pNodeK = OBJ_NIL;
    AST_ENTRY       *pNodeL = OBJ_NIL;
    AST_ENTRY       *pNodeM = OBJ_NIL;
    AST_ENTRY       *pNodeN = OBJ_NIL;
    AST_ENTRY       *pNodeO = OBJ_NIL;
    AST_ENTRY       *pNodeP = OBJ_NIL;
    AST_ENTRY       *pNodeQ = OBJ_NIL;
    AST_ENTRY       *pNodeR = OBJ_NIL;
    //uint32_t        i;
    ERESULT         eRc;
    //AST_ENTRY       *pRcd   = NULL;

    pTree = Ast_New( );
    TestForNotNull(pTree, "");

    pNodeA = Ast_EntryNewChars(pTree, "A", 0, NULL);
    TestForNotNull(pNodeA, "");
    pNodeB = Ast_EntryNewChars(pTree, "B", 0, NULL);
    TestForNotNull(pNodeB, "");
    pNodeC = Ast_EntryNewChars(pTree, "C", 0, NULL);
    TestForNotNull(pNodeC, "");
    pNodeD = Ast_EntryNewChars(pTree, "D", 0, NULL);
    TestForNotNull(pNodeD, "");
    pNodeE = Ast_EntryNewChars(pTree, "E", 0, NULL);
    TestForNotNull(pNodeE, "");
    pNodeF = Ast_EntryNewChars(pTree, "F", 0, NULL);
    TestForNotNull(pNodeF, "");
    pNodeG = Ast_EntryNewChars(pTree, "G", 0, NULL);
    TestForNotNull(pNodeG, "");
    pNodeH = Ast_EntryNewChars(pTree, "H", 0, NULL);
    TestForNotNull(pNodeH, "");
    pNodeI = Ast_EntryNewChars(pTree, "I", 0, NULL);
    TestForNotNull(pNodeI, "");
    pNodeJ = Ast_EntryNewChars(pTree, "J", 0, NULL);
    TestForNotNull(pNodeJ, "");
    pNodeK = Ast_EntryNewChars(pTree, "K", 0, NULL);
    TestForNotNull(pNodeK, "");
    pNodeL = Ast_EntryNewChars(pTree, "L", 0, NULL);
    TestForNotNull(pNodeL, "");
    pNodeM = Ast_EntryNewChars(pTree, "M", 0, NULL);
    TestForNotNull(pNodeM, "");
    pNodeN = Ast_EntryNewChars(pTree, "N", 0, NULL);
    TestForNotNull(pNodeN, "");
    pNodeO = Ast_EntryNewChars(pTree, "O", 0, NULL);
    TestForNotNull(pNodeO, "");
    pNodeP = Ast_EntryNewChars(pTree, "P", 0, NULL);
    TestForNotNull(pNodeP, "");
    pNodeQ = Ast_EntryNewChars(pTree, "Q", 0, NULL);
    TestForNotNull(pNodeQ, "");
    pNodeR = Ast_EntryNewChars(pTree, "R", 0, NULL);
    TestForNotNull(pNodeR, "");

    fprintf(stderr, "\n\nExample from \"Data Structures Using C\", Taenenbaum et al, 1990,\n");
    fprintf(stderr, "page 295(b). This is a forest of 3 trees in binary tree format (ie\n");
    fprintf(stderr, "a general ordered tree represented by a binary tree).\n");
    fprintf(stderr, "Separate:\n");
    fprintf(stderr, "    A        G        L\n");
    fprintf(stderr, "   / \\       |       /|\\\n");
    fprintf(stderr, "  B   C      H      M N O\n");
    fprintf(stderr, "     /|\\    /|\\    / \\\n");
    fprintf(stderr, "    D E F  I J K   P  Q\n");
    fprintf(stderr, "                   |\n");
    fprintf(stderr, "                   R\n");
    fprintf(stderr, "Binary Tree Forest:\n");
    fprintf(stderr, "    A--------------G-------------L \n");
    fprintf(stderr, "    |              |             | \n");
    fprintf(stderr, "    |              |             | \n");
    fprintf(stderr, "    B---C          H             M---N---O\n");
    fprintf(stderr, "        |          |             |  \n");
    fprintf(stderr, "        D---E---F  I---J---K     P---Q  \n");
    fprintf(stderr, "                                 |  \n");
    fprintf(stderr, "                                 R  \n");
    fprintf(stderr, "\n");
    fprintf(stderr, " | == Child Link\n");
    fprintf(stderr, " - == Sibling Link\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "Preorder Traversal:  ABCDEFGHIJKLMPRQNO\n");
    fprintf(stderr, "Postorder Traversal: BDEFCAIJKHGRPQMNOL\n");
    fprintf(stderr, "Breadth First Traversal: AGLBCHMNODEFIJKPQR\n");
    fprintf(stderr, "\n\n\n");

    eRc = Ast_EntryAddChild(pTree, pNodeA, pNodeB, pNodeC);
    TestForSuccess("");
    TestForTrue((pNodeB == pNodeA->pChild), "");
    TestForTrue((NULL   == pNodeA->pSibling), "");
    TestForTrue((NULL   == pNodeA->pParent), "");
    TestForTrue((NULL   == pNodeB->pChild), "");
    TestForTrue((pNodeC == pNodeB->pSibling), "");
    TestForTrue((pNodeA == pNodeB->pParent), "");
    TestForTrue((NULL   == pNodeC->pChild), "");
    TestForTrue((NULL   == pNodeC->pSibling), "");
    TestForTrue((pNodeA == pNodeC->pParent), "");

    eRc = Ast_EntryAddSibling(pTree, pNodeA, pNodeG, pNodeL);
    TestForSuccess("");
    TestForTrue((pNodeB == pNodeA->pChild), "");
    TestForTrue((pNodeG == pNodeA->pSibling), "");
    TestForTrue((NULL   == pNodeA->pParent), "");
    TestForTrue((NULL   == pNodeG->pChild), "");
    TestForTrue((pNodeL == pNodeG->pSibling), "");
    TestForTrue((NULL   == pNodeG->pParent), "");
    TestForTrue((NULL   == pNodeL->pChild), "");
    TestForTrue((NULL   == pNodeL->pSibling), "");
    TestForTrue((NULL   == pNodeL->pParent), "");

    eRc = Ast_EntryAddChild(pTree, pNodeC, pNodeD, pNodeE);
    TestForSuccess("");
    TestForTrue((pNodeD == pNodeC->pChild), "");
    TestForTrue((NULL   == pNodeC->pSibling), "");
    TestForTrue((pNodeA == pNodeC->pParent), "");
    TestForTrue((NULL   == pNodeD->pChild), "");
    TestForTrue((pNodeE == pNodeD->pSibling), "");
    TestForTrue((pNodeC == pNodeD->pParent), "");
    TestForTrue((NULL   == pNodeE->pChild), "");
    TestForTrue((NULL   == pNodeE->pSibling), "");
    TestForTrue((pNodeC == pNodeE->pParent), "");

    eRc = Ast_EntryAddChild(pTree, pNodeC, pNodeF, NULL);
    TestForSuccess("");
    TestForTrue((pNodeF == pNodeE->pSibling), "");
    TestForTrue((NULL   == pNodeF->pChild), "");
    TestForTrue((NULL   == pNodeF->pSibling), "");
    TestForTrue((pNodeC == pNodeF->pParent), "");

    eRc = Ast_EntryAddChild(pTree, pNodeG, pNodeH, NULL);
    TestForSuccess("");
    TestForTrue((pNodeH == pNodeG->pChild), "");
    TestForTrue((pNodeL == pNodeG->pSibling), "");
    TestForTrue((NULL   == pNodeG->pParent), "");
    TestForTrue((NULL   == pNodeH->pChild), "");
    TestForTrue((NULL   == pNodeH->pSibling), "");
    TestForTrue((pNodeG == pNodeH->pParent), "");

    eRc = Ast_EntryAddChild(pTree, pNodeH, pNodeI, NULL);
    TestForSuccess("");
    TestForTrue((pNodeI == pNodeH->pChild), "");
    TestForTrue((NULL   == pNodeH->pSibling), "");
    TestForTrue((pNodeG == pNodeH->pParent), "");
    TestForTrue((NULL   == pNodeI->pChild), "");
    TestForTrue((NULL   == pNodeI->pSibling), "");
    TestForTrue((pNodeH == pNodeI->pParent), "");

    eRc = Ast_EntryAddSibling(pTree, pNodeI, pNodeJ, pNodeK);
    TestForSuccess("");
    TestForTrue((NULL   == pNodeI->pChild), "");
    TestForTrue((pNodeJ == pNodeI->pSibling), "");
    TestForTrue((pNodeH == pNodeI->pParent), "");
    TestForTrue((NULL   == pNodeJ->pChild), "");
    TestForTrue((pNodeK == pNodeJ->pSibling), "");
    TestForTrue((pNodeH == pNodeJ->pParent), "");
    TestForTrue((NULL   == pNodeK->pChild), "");
    TestForTrue((NULL   == pNodeK->pSibling), "");
    TestForTrue((pNodeH == pNodeK->pParent), "");

    eRc = Ast_EntryAddChild(pTree, pNodeL, pNodeM, NULL);
    TestForSuccess("");
    TestForTrue((pNodeM == pNodeL->pChild), "");
    TestForTrue((NULL   == pNodeL->pSibling), "");
    TestForTrue((NULL   == pNodeL->pParent), "");
    TestForTrue((NULL   == pNodeM->pChild), "");
    TestForTrue((NULL   == pNodeM->pSibling), "");
    TestForTrue((pNodeL == pNodeM->pParent), "");

    eRc = Ast_EntryAddSibling(pTree, pNodeM, pNodeN, pNodeO);
    TestForSuccess("");
    TestForTrue((NULL   == pNodeM->pChild), "");
    TestForTrue((pNodeN == pNodeM->pSibling), "");
    TestForTrue((pNodeL == pNodeM->pParent), "");
    TestForTrue((NULL   == pNodeN->pChild), "");
    TestForTrue((pNodeO == pNodeN->pSibling), "");
    TestForTrue((pNodeL == pNodeN->pParent), "");
    TestForTrue((NULL   == pNodeO->pChild), "");
    TestForTrue((NULL   == pNodeO->pSibling), "");
    TestForTrue((pNodeL == pNodeO->pParent), "");

    eRc = Ast_EntryAddChild(pTree, pNodeM, pNodeP, pNodeQ);
    TestForSuccess("");
    TestForTrue((pNodeP == pNodeM->pChild), "");
    TestForTrue((pNodeN == pNodeM->pSibling), "");
    TestForTrue((pNodeL == pNodeM->pParent), "");
    TestForTrue((NULL   == pNodeP->pChild), "");
    TestForTrue((pNodeQ == pNodeP->pSibling), "");
    TestForTrue((pNodeM == pNodeP->pParent), "");
    TestForTrue((NULL   == pNodeQ->pChild), "");
    TestForTrue((NULL   == pNodeQ->pSibling), "");
    TestForTrue((pNodeM == pNodeQ->pParent), "");

    eRc = Ast_EntryAddChild(pTree, pNodeP, pNodeR, NULL);
    TestForSuccess("");
    TestForTrue((pNodeR == pNodeP->pChild), "");
    TestForTrue((pNodeQ == pNodeP->pSibling), "");
    TestForTrue((pNodeM == pNodeP->pParent), "");
    TestForTrue((NULL   == pNodeR->pChild), "");
    TestForTrue((NULL   == pNodeR->pSibling), "");
    TestForTrue((pNodeP == pNodeR->pParent), "");

    Ast_setRoot(pTree, pNodeA);
    return pTree;
}



// Example from "Algorithms + Data Structures = Programs" by Niklaus Wirth
// Page 193 and 199
// Tree representation of: (a + b / c) * (d - e * f)
// Note - Each node must be unique.  Therefore, we must have two nodes for '*'.
static
AST_DATA *      createTestTree02 (
    TEST_DATA       *this
)
{
    AST_DATA        *pTree = OBJ_NIL;
    AST_ENTRY       *pNodeA = OBJ_NIL;
    AST_ENTRY       *pNodeB = OBJ_NIL;
    AST_ENTRY       *pNodeC = OBJ_NIL;
    AST_ENTRY       *pNodeD = OBJ_NIL;
    AST_ENTRY       *pNodeE = OBJ_NIL;
    AST_ENTRY       *pNodeF = OBJ_NIL;
    AST_ENTRY       *pNodeG = OBJ_NIL;
    AST_ENTRY       *pNodeH = OBJ_NIL;
    AST_ENTRY       *pNodeI = OBJ_NIL;
    AST_ENTRY       *pNodeJ = OBJ_NIL;
    AST_ENTRY       *pNodeK = OBJ_NIL;
    //uint32_t        i;
    ERESULT         eRc;
    //NODETREE_RECORD *pRcd = NULL;

    pTree = Ast_New( );
    if  (OBJ_NIL == pTree) {
        return pTree;
    }

    pNodeA = Ast_EntryNewChars(pTree, "a", 0, NULL);
    TestForNotNull(pNodeA, "");
    pNodeB = Ast_EntryNewChars(pTree, "b", 0, NULL);
    TestForNotNull(pNodeB, "");
    pNodeC = Ast_EntryNewChars(pTree, "c", 0, NULL);
    TestForNotNull(pNodeC, "");
    pNodeD = Ast_EntryNewChars(pTree, "d", 0, NULL);
    TestForNotNull(pNodeD, "");
    pNodeE = Ast_EntryNewChars(pTree, "e", 0, NULL);
    TestForNotNull(pNodeE, "");
    pNodeF = Ast_EntryNewChars(pTree, "f", 0, NULL);
    TestForNotNull(pNodeF, "");
    pNodeG = Ast_EntryNewChars(pTree, "*1", 0, NULL);
    TestForNotNull(pNodeG, "");
    pNodeH = Ast_EntryNewChars(pTree, "+", 0, NULL);
    TestForNotNull(pNodeH, "");
    pNodeI = Ast_EntryNewChars(pTree, "/", 0, NULL);
    TestForNotNull(pNodeI, "");
    pNodeJ = Ast_EntryNewChars(pTree, "-", 0, NULL);
    TestForNotNull(pNodeJ, "");
    pNodeK = Ast_EntryNewChars(pTree, "*2", 0, NULL);
    TestForNotNull(pNodeK, "");
    
    fprintf(stderr, "\n\nCreate the tree:\n");
    fprintf(stderr, "Tree            Index  Sibling  Child  Parent\n");
    fprintf(stderr, "'*1'         G    1       0       2       0\n");
    fprintf(stderr, "--'+'        H    2       3       4       1\n");
    fprintf(stderr, "----'a'      A    4       5       0       2\n");
    fprintf(stderr, "----'/'      I    5       0       6       2\n");
    fprintf(stderr, "------'b'    B    6       7       0       5\n");
    fprintf(stderr, "------'c'    C    7       0       0       5\n");
    fprintf(stderr, "--'-'        J    3       0       8       1\n");
    fprintf(stderr, "----'d'      D    8       9       0       3\n");
    fprintf(stderr, "----'*2'     K    9       0      10       3\n");
    fprintf(stderr, "------'e'    E   10      11       0       9\n");
    fprintf(stderr, "------'f'    F   11       0       0       9\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "Preorder Traversal:  *1 + a / b c - d *2 e f\n");
    fprintf(stderr, "Inorder Traversal:   a + b / c *1 d - e *2 f\n");
    fprintf(stderr, "Postorder Traversal: a b c / + d e f *2 - *1\n");
    fprintf(stderr, "Breadth First Traversal: ((*1), (+,-), (a,/,d,*2), (b,c,e,f)\n");
    fprintf(stderr, "\n\n\n");

    eRc = Ast_EntryAddChild(pTree, pNodeG, pNodeH, pNodeJ);
    TestForSuccess("");
    TestForTrue((pNodeH == pNodeG->pChild), "");
    TestForTrue((NULL   == pNodeG->pSibling), "");
    TestForTrue((NULL   == pNodeG->pParent), "");
    TestForTrue((NULL   == pNodeH->pChild), "");
    TestForTrue((pNodeJ == pNodeH->pSibling), "");
    TestForTrue((pNodeG == pNodeH->pParent), "");
    TestForTrue((NULL   == pNodeJ->pChild), "");
    TestForTrue((NULL   == pNodeJ->pSibling), "");
    TestForTrue((pNodeG == pNodeJ->pParent), "");

    eRc = Ast_EntryAddChild(pTree, pNodeH, pNodeA, pNodeI);
    TestForSuccess("");
    TestForTrue((pNodeA == pNodeH->pChild), "");
    TestForTrue((pNodeJ == pNodeH->pSibling), "");
    TestForTrue((pNodeG == pNodeH->pParent), "");
    TestForTrue((NULL   == pNodeA->pChild), "");
    TestForTrue((pNodeI == pNodeA->pSibling), "");
    TestForTrue((pNodeH == pNodeA->pParent), "");
    TestForTrue((NULL   == pNodeI->pChild), "");
    TestForTrue((NULL   == pNodeI->pSibling), "");
    TestForTrue((pNodeH == pNodeI->pParent), "");

    eRc = Ast_EntryAddChild(pTree, pNodeI, pNodeB, pNodeC);
    TestForSuccess("");
    TestForTrue((pNodeB == pNodeI->pChild), "");
    TestForTrue((NULL   == pNodeI->pSibling), "");
    TestForTrue((pNodeH == pNodeI->pParent), "");
    TestForTrue((NULL   == pNodeB->pChild), "");
    TestForTrue((pNodeC == pNodeB->pSibling), "");
    TestForTrue((pNodeI == pNodeB->pParent), "");
    TestForTrue((NULL   == pNodeC->pChild), "");
    TestForTrue((NULL   == pNodeC->pSibling), "");
    TestForTrue((pNodeI == pNodeC->pParent), "");

    eRc = Ast_EntryAddChild(pTree, pNodeJ, pNodeD, pNodeK);
    TestForSuccess("");
    TestForTrue((pNodeD == pNodeJ->pChild), "");
    TestForTrue((NULL   == pNodeJ->pSibling), "");
    TestForTrue((pNodeG == pNodeJ->pParent), "");
    TestForTrue((NULL   == pNodeD->pChild), "");
    TestForTrue((pNodeK == pNodeD->pSibling), "");
    TestForTrue((pNodeJ == pNodeD->pParent), "");
    TestForTrue((NULL   == pNodeK->pChild), "");
    TestForTrue((NULL   == pNodeK->pSibling), "");
    TestForTrue((pNodeJ == pNodeK->pParent), "");

    eRc = Ast_EntryAddChild(pTree, pNodeK, pNodeE, pNodeF);
    TestForSuccess("");
    TestForTrue((pNodeE == pNodeK->pChild), "");
    TestForTrue((NULL   == pNodeK->pSibling), "");
    TestForTrue((pNodeJ == pNodeK->pParent), "");
    TestForTrue((NULL   == pNodeE->pChild), "");
    TestForTrue((pNodeF == pNodeE->pSibling), "");
    TestForTrue((pNodeK == pNodeE->pParent), "");
    TestForTrue((NULL   == pNodeF->pChild), "");
    TestForTrue((NULL   == pNodeF->pSibling), "");
    TestForTrue((pNodeK == pNodeF->pParent), "");

    Ast_setRoot(pTree, pNodeG);
    return pTree;
}




static
void            after (
    OBJ_ID          pObject,            // Object supplied below
    AST_DATA        *pTree,             // Our Tree
    AST_ENTRY       *pEntry,
    uint32_t        indent,
    uint32_t        level,
    void            *pOther
)
{
    ASTR_DATA       *pStr = AStr_New();
    
    if (pStr && fPrintVisits) {
        if (indent) {
            AStr_AppendCharRepeatA(pStr, (indent << 2), ' ');
        }
        fprintf(stderr, "%s)\n", AStr_getData(pStr));
    }
    obj_Release(pStr);
}


static
void            before (
    OBJ_ID          pObject,            // Object supplied below
    AST_DATA        *pTree,             // Our Tree
    AST_ENTRY       *pEntry,
    uint32_t        indent,
    uint32_t        level,
    void            *pOther
)
{
    ASTR_DATA       *pStr = AStr_New();
    
    if (pStr && fPrintVisits) {
        if (indent) {
            AStr_AppendCharRepeatA(pStr, (indent << 2), ' ');
        }
        fprintf(stderr, "%s(\n", AStr_getData(pStr));
    }
    obj_Release(pStr);
}


static
void            visitor (
    OBJ_ID          pObject,            // Object supplied below
    AST_DATA        *pTree,             // Our Tree
    AST_ENTRY       *pEntry,
    uint32_t        indent,
    uint32_t        level,
    void            *pOther
)
{
    ASTR_DATA       *pStr = Ast_EntryToAStrDebug(pTree, pEntry, (indent << 2));
    
    if (correctCur >= correctLen) {
        fprintf(stderr, "\nERROR - Too many characters(%c) in visitation!\n\n", pEntry->u.chrs[0]);
        exit(95);
    }
    
    switch (pEntry->kind) {
        case AST_ENTRY_KIND_INTEGER:
            if (fPrintVisits) {
                fprintf(stderr, "%lld", pEntry->u.integer);
            }
            break;
        case AST_ENTRY_KIND_CHARS:
            if (fPrintVisits) {
                fprintf(stderr, "%c", pEntry->u.chrs[0]);
            }
            if (pEntry->u.chrs[0] == pCorrect[correctCur++])
                ;
            else {
                fprintf(
                        stderr,
                        "\nERROR - Current: %c should be %c\n\n",
                        pEntry->u.chrs[0],
                        pCorrect[correctCur++]
                        );
                exit(95);
            }
            break;
        default:
            break;
    }

    if (pStr && fPrintVisits) {
        fprintf(stderr, "%s", AStr_getData(pStr));
    }
    obj_Release(pStr);
}


static
void            visitorReset (
    const
    char        *pCorrectA,
    int         correctNum
)
{
    pCorrect = pCorrectA;
    if (correctNum)
        correctLen = correctNum;
    else
        correctLen = (int)strlen(pCorrectA);
    correctCur = 0;
}







//----------------------------------------------------------------
//                      Test Open/Close
//----------------------------------------------------------------

ERESULT         Test_Ast_OpenClose (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    AST_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Ast_Alloc( );
    TestForNotNull(pObj, "Missing Test Alloc() object");
    pObj = Ast_Init( pObj );
    TestForNotNull(pObj, "Missing Test Init() object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_AST);
        TestForTrue(fRc, "Failed Ident Test");
#ifdef   AST_MSGS
        Ast_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
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

ERESULT         Test_Ast_Copy01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    AST_DATA       *pObj1 = OBJ_NIL;
    AST_DATA       *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(AST_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA       *pStr = OBJ_NIL;
#endif
    //int             iRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = Ast_New( );
    TestForNotNull(pObj1, "Missing Test object");
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_AST);
        TestForTrue(fRc, "Failed Ident Test");
#ifdef   AST_MSGS
        Ast_setMsg(pObj1, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
        
        // Test assign.
        pObj2 = Ast_New();
        TestForNotNull(pObj2, "Missing copied object");
        eRc = Ast_Assign(pObj1, pObj2);
        TestForFalse((ERESULT_FAILED(eRc)), "Assignment failed");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_AST);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = Ast_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = Ast_Copy(pObj1);
        TestForNotNull(pObj2, "Missing copied object");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_AST);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = Ast_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(AST_JSON_SUPPORT) && defined(XYZZY)
        pStr = Ast_ToJson(pObj1);
        TestForNotNull(pStr, "Missing JSON output");
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = Ast_NewFromJsonString(pStr);
        TestForNotNull(pObj2, "Missing JSON created object");
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_AST);
        TestForTrue(fRc, "Failed Ident Test");
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //iRc = Ast_Compare(pObj1, pObj2);
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

ERESULT         Test_Ast_Test01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    AST_DATA        *pObj = OBJ_NIL;
    bool            fRc;
    PTRARRAY_DATA   *pArray = OBJ_NIL;
    int             indent;
    int             i;
    int             iMax;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = createTestTree01(this);
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_AST);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   AST_MSGS
        Ast_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
        Ast_Setup(pObj, 3000, 3001, NULL);

        fprintf(stderr, "\n\nPost-order Linearization:  BDEFCAIJKHGRPQMNOL\n");
        visitorReset("BDEFCAIJKHGRPQMNOL", 0);
        pArray = Ast_ToLinearizationPost(pObj, NULL);
        TestForNotNull(pArray, "");
        iMax = ptrArray_getSize(pArray);
        fprintf(stderr, "\tsize: %d\n", iMax);
        TestForTrue((43 == iMax), "");
        indent = 4;
        for (i=0; i<iMax; i++) {
            AST_ENTRY           *pEntry = ptrArray_GetData(pArray, i+1);
            if (pEntry) {
                int16_t             type = pEntry->type;
                if (type == 3001) {             // See Setup() above!
#ifdef INDENTED_LINEARIZATION
                    for (int j=0; j<indent; j++)
                        fputc(' ', stderr);
                    fputc('(', stderr);
                    fputc('\n', stderr);
                    indent += 4;
#else
                    fputc('(', stderr);
#endif
                    continue;
                }
                if (type == 3000) {             // See Setup() above!
#ifdef INDENTED_LINEARIZATION
                    indent -= 4;
                    for (int j=0; j<indent; j++)
                        fputc(' ', stderr);
                    fputc(')', stderr);
                    fputc('\n', stderr);
#else
                    fputc(')', stderr);
#endif
                    continue;
                }
#ifdef INDENTED_LINEARIZATION
                for (int j=0; j<indent; j++)
                    fputc(' ', stderr);
                switch (pEntry->kind) {
                    case AST_ENTRY_KIND_INTEGER:
                        fprintf(stderr, "%lld\n", pEntry->u.integer);
                        break;
                    case AST_ENTRY_KIND_CHARS:
                        if (correctCur >= correctLen) {
                            fprintf(stderr, "\nERROR - Too many characters(%c) in visitation!\n\n", pEntry->u.chrs[0]);
                            exit(95);
                        }
                        if (pEntry->u.chrs[0] == pCorrect[correctCur++])
                            ;
                        else {
                            fprintf(
                                    stderr,
                                    "\nERROR - Current: %c should be %c\n\n",
                                    pEntry->u.chrs[0],
                                    pCorrect[correctCur++]
                                    );
                            exit(95);
                        }
                        fprintf(stderr, "%s\n", pEntry->u.chrs);
                        break;
                    default:
                        break;
                }
#else
                switch (pEntry->kind) {
                    case AST_ENTRY_KIND_INTEGER:
                        fprintf(stderr, "%lld", pEntry->u.integer);
                        break;
                    case AST_ENTRY_KIND_CHARS:
                        if (correctCur >= correctLen) {
                            fprintf(stderr, "\nERROR - Too many characters(%c) in visitation!\n\n", pEntry->u.chrs[0]);
                            exit(95);
                        }
                        if (pEntry->u.chrs[0] == pCorrect[correctCur++])
                            ;
                        else {
                            fprintf(
                                    stderr,
                                    "\nERROR - Current: %c should be %c\n\n",
                                    pEntry->u.chrs[0],
                                    pCorrect[correctCur++]
                                    );
                            exit(95);
                        }
                        fprintf(stderr, "%s", pEntry->u.chrs);
                        break;
                    default:
                        break;
                }
#endif
            }
        }
        obj_Release(pArray);
        pArray = OBJ_NIL;
        if (correctCur != correctLen) {
            fprintf(stderr, "\nERROR - Not enough characters in visitation!\n\n");
            exit(95);
        }

        fprintf(stderr, "\n\nPreorder Linearization:  ABCDEFGHIJKLMPRQNO\n");
        visitorReset("ABCDEFGHIJKLMPRQNO", 18);
        pArray = Ast_ToLinearizationPre(pObj, Ast_getRoot(pObj));
        TestForNotNull(pArray, "");
        iMax = ptrArray_getSize(pArray);
        fprintf(stderr, "\tsize: %d\n", iMax);
        TestForTrue((34 == iMax), "");
        indent = 4;
        for (i=0; i<iMax; i++) {
            AST_ENTRY           *pEntry = ptrArray_GetData(pArray, i+1);
            if (pEntry) {
                int16_t             type = pEntry->type;
                if (type == 3001) {             // See Setup() above!
#ifdef INDENTED_LINEARIZATION
                    for (int j=0; j<indent; j++)
                        fputc(' ', stderr);
                    fputc('(', stderr);
                    fputc('\n', stderr);
                    indent += 4;
#else
                    fputc('(', stderr);
#endif
                    continue;
                }
                if (type == 3000) {             // See Setup() above!
#ifdef INDENTED_LINEARIZATION
                    indent -= 4;
                    for (int j=0; j<indent; j++)
                        fputc(' ', stderr);
                    fputc(')', stderr);
                    fputc('\n', stderr);
#else
                    fputc(')', stderr);
#endif
                    continue;
                }
#ifdef INDENTED_LINEARIZATION
                for (int j=0; j<indent; j++)
                    fputc(' ', stderr);
                switch (pEntry->kind) {
                    case AST_ENTRY_KIND_INTEGER:
                        fprintf(stderr, "%lld\n", pEntry->u.integer);
                        break;
                    case AST_ENTRY_KIND_CHARS:
                        if (correctCur >= correctLen) {
                            fprintf(stderr, "\nERROR - Too many characters(%c) in visitation!\n\n", pEntry->u.chrs[0]);
                            exit(95);
                        }
                        if (pEntry->u.chrs[0] == pCorrect[correctCur++])
                            ;
                        else {
                            fprintf(
                                    stderr,
                                    "\nERROR - Current: %c should be %c\n\n",
                                    pEntry->u.chrs[0],
                                    pCorrect[correctCur++]
                                    );
                            exit(95);
                        }
                        fprintf(stderr, "%s\n", pEntry->u.chrs);
                        break;
                    default:
                        break;
                }
#else
                switch (pEntry->kind) {
                    case AST_ENTRY_KIND_INTEGER:
                        fprintf(stderr, "%lld", pEntry->u.integer);
                        break;
                    case AST_ENTRY_KIND_CHARS:
                        if (correctCur >= correctLen) {
                            fprintf(stderr, "\nERROR - Too many characters(%c) in visitation!\n\n", pEntry->u.chrs[0]);
                            exit(95);
                        }
                        if (pEntry->u.chrs[0] == pCorrect[correctCur++])
                            ;
                        else {
                            fprintf(
                                    stderr,
                                    "\nERROR - Current: %c should be %c\n\n",
                                    pEntry->u.chrs[0],
                                    pCorrect[correctCur++]
                                    );
                            exit(95);
                        }
                        fprintf(stderr, "%s", pEntry->u.chrs);
                        break;
                    default:
                        break;
                }
#endif
            }
        }
        obj_Release(pArray);
        pArray = OBJ_NIL;
        if (correctCur != correctLen) {
            fprintf(stderr, "\nERROR - Not enough characters in visitation!\n\n");
            exit(95);
        }

        fprintf(stderr, "\n\n\nBreadth First Traversal:\n");
        fprintf(stderr, "Breadth First Traversal: AGLBCHMNODEFIJKPQR\n");
        visitorReset("AGLBCHMNODEFIJKPQR", 18);
        //fPrintVisits = false;
        eRc = Ast_VisitBreadthFirst(
                                     pObj,
                                     visitor,
                                     OBJ_NIL,
                                     NULL,
                                     0,
                                     NULL
                                     );
        TestForSuccess("");

        fprintf(stderr, "\n\n\nPost-order Traversal:\n");
        fprintf(stderr, "Postorder Traversal: BDEFCAIJKHGRPQMNOL\n");
        visitorReset("BDEFCAIJKHGRPQMNOL", 18);
        //fPrintVisits = false;
        eRc = Ast_VisitPostOrder(
                                     pObj,
                                     visitor,
                                     before,
                                     after,
                                     OBJ_NIL,
                                     NULL,
                                     0,
                                     Ast_getRoot(pObj)
                                     );
        TestForSuccess("");

        fprintf(stderr, "\n\nPre-order Traversal:\n");
        fprintf(stderr, "Preorder Traversal:  ABCDEFGHIJKLMPRQNO\n");
        visitorReset("ABCDEFGHIJKLMPRQNO", 18);
        eRc = Ast_VisitPreOrder(
                                     pObj,
                                     visitor,
                                     before,
                                     after,
                                     OBJ_NIL,
                                     NULL,
                                     0,
                                     Ast_getRoot(pObj)
                                     );
        TestForSuccess("");
        if (correctCur != correctLen) {
            fprintf(stderr, "\nERROR - Not enough characters in visitation!\n\n");
            exit(95);
        }

        {
            ASTR_DATA       *pStr = Ast_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "\n\n\nDebug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        if (correctCur != correctLen) {
            fprintf(stderr, "\nERROR - Not enough characters in visitation!\n\n");
            exit(95);
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

ERESULT         Test_Ast_Test02 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    AST_DATA        *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    fprintf(stderr, "// Tree representation of: (a + b / c) * (d - e * f)\n");

    pObj = createTestTree02(this);
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_AST);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   AST_MSGS
        Ast_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
        Ast_Setup(pObj, 3000, 3001, NULL);

        fprintf(stderr, "\n\nPreorder Traversal:  *1 + a / b c - d *2 e f\n");
        visitorReset("*+a/bc-d*ef", 0);
        eRc = Ast_VisitPreOrder(
                                     pObj,
                                     visitor,
                                     before,
                                     after,
                                     OBJ_NIL,
                                     NULL,
                                     0,
                                     Ast_getRoot(pObj)
                                     );
        TestForSuccess("");

        fprintf(stderr, "\n\nPostorder Traversal: a b c / + d e f *2 - *1\n");
        visitorReset("abc/+def*-*", 0);
        eRc = Ast_VisitPostOrder(
                                     pObj,
                                     visitor,
                                     before,
                                     after,
                                     OBJ_NIL,
                                     NULL,
                                     0,
                                     Ast_getRoot(pObj)
                                     );
        TestForSuccess("");

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



//----------------------------------------------------------------
//                          Test 3
//----------------------------------------------------------------

ERESULT         Test_Ast_Test03 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    AST_DATA        *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Ast_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_AST);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   AST_MSGS
        Ast_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        {
            ASTR_DATA       *pStr = Ast_ToDebugString(pObj, 4);
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

ERESULT         Test_Ast_Test04 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    AST_DATA        *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Ast_New( );
    TestForNotNull(pObj, "");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_AST);
        TestForFalse(!fRc, "");
        TestForTrue(fRc, "");
        TestForSuccess("");
#ifdef   AST_MSGS
        Ast_setMsg(pObj, (void *)Test_MsgInfo, (void *)Test_MsgWarn, this);
#endif
                
        {
            ASTR_DATA       *pStr = Ast_ToDebugString(pObj, 4);
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
    // Note: 
    //  Test_Setup() is called before the optional supplied setup
    //  in this table. Likewise, the optional teardown routine is
    //  called before Test_TearDown().
    //                                             Setup TearDown
    TestExec("OpenClose", Test_Ast_OpenClose, NULL,   NULL);
    //TestExec("Copy01", Test_Ast_Copy01,       NULL,   NULL);
    TestExec("Test01", Test_Ast_Test01,       NULL,   NULL);
    TestExec("Test02", Test_Ast_Test02,       NULL,   NULL);
    TestExec("Test03", Test_Ast_Test03,       NULL,   NULL);
    TestExec("Test04", Test_Ast_Test04,       NULL,   NULL);

    obj_Release(pTest);
    pTest = OBJ_NIL;

    // Return to Operating System.
    return 0;
}



