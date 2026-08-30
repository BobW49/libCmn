// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
// Doubly-Linked List using 32-bit Indices (ListDL32) Object Support
//****************************************************************


/*
 * File:   ListDL32.c
 *  Generated 09/30/2023 07:24:49
 *
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




//*****************************************************************
//* * * * * * * * * * * *  Data Definitions   * * * * * * * * * * *
//*****************************************************************

/* Header File Inclusion */
#include        <ListDL32.h>
#include        <trace.h>
#include        <utf8.h>


#define            Index2Node(index)    ((LISTDL32_NODE *)\
                                        (((uint8_t *)this->pIndex2Ptr(this->pIndex2PtrObj,index))\
                                        + this->iOffset))
#define            Node2Entry(Node)     ((void *)((uint8_t *)Node - this->iOffset))
#define            Entry2Node(Entry)    ((void *)((uint8_t *)Entry + this->iOffset))




#ifdef  __cplusplus
extern "C" {
#endif
    

    
    //****************************************************************
    // * * * * * * * * * * *    Internal Data    * * * * * * * * * * *
    //****************************************************************

    // Place constant internal data here. Generally, it should be
    // 'static' so that it does not interfere with other objects.





    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/



    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            ListDL32_task_body (
        void            *pData
    )
    {
        LISTDL32_DATA   *this = pData;
        TRC_OBJ(this, "%s(%p):\n", __func__, this);
        
    }
#endif



    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    LISTDL32_DATA * ListDL32_Alloc (
        void
    )
    {
        LISTDL32_DATA   *this;
        uint32_t        cbSize = sizeof(LISTDL32_DATA);
        
        // Do initialization.
        
         this = mem_Calloc(1, cbSize);
        
        // Return to caller.
        return this;
    }



    LISTDL32_DATA * ListDL32_New (
        uint32_t        offset,     // Offset of Node Field within Structure
        void *          (*pIndex2Ptr)(OBJ_ID, LISTDL32_INDEX),
        OBJ_ID          pIndex2PtrObj
    )
    {
        LISTDL32_DATA   *this;
        bool            fRc;
        
        this = ListDL32_Alloc( );
        if (this) {
            fRc = ListDL32_Init(this, offset, pIndex2Ptr, pIndex2PtrObj);
            if (!fRc) {
                mem_Free(this);
                this = NULL;
            }
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                      S i z e
    //---------------------------------------------------------------
    
    uint32_t         ListDL32_getSize(
        LISTDL32_DATA   *this
    )
    {
        uint32_t        iRet;

        // Do initialization.
        iRet = this->size;

        // Return to caller.
        return iRet;
    }



    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                      A d d
    //---------------------------------------------------------------

    bool             ListDL32_Add2Head (
        LISTDL32_DATA   *this,
        LISTDL32_INDEX  index
    )
    {
        LISTDL32_NODE   *pNode;

        // Do initialization.
        if (index && this->pIndex2Ptr)
            ;
        else
            return false;
        pNode = Index2Node(index);

        // Chain it to the top of the list.
        pNode->next = this->head;
        pNode->prev = 0;
        if (0 == this->head)
            this->tail = index;
        else
            Index2Node(this->head)->prev = index;
        this->head = index;
        this->size++;

        // Return to caller.
        return true;
    }


    bool             ListDL32_Add2Tail (
        LISTDL32_DATA   *this,
        LISTDL32_INDEX  index
    )
    {
        LISTDL32_NODE   *pNode;

        // Do initialization.
        if (index && this->pIndex2Ptr)
            ;
        else
            return false;
        pNode = Index2Node(index);

        // Chain it to the top of the list.
        pNode->prev = this->tail;
        pNode->next = 0;
        if (0 == this->tail)
            this->head = index;
        else
            Index2Node(this->tail)->next = index;
        this->tail = index;
        this->size++;

        // Return to caller.
        return true;
    }



    //---------------------------------------------------------------
    //                      C o m p a r e
    //---------------------------------------------------------------
    
    /*!
     Compare the two provided objects.
     @return    0  if this == other
                <0 if this < other
                >0 if this > other
     */
    int             ListDL32_Compare (
        LISTDL32_DATA   *this,
        LISTDL32_DATA   *pOther
    )
    {
        int             iRc = -1;
#ifdef  xyzzy        
        const
        char            *pStr1;
        const
        char            *pStr2;
#endif
        

        //TODO: iRc = utf8_StrCmp(AStr_getData(this->pStr), AStr_getData(pOther->pStr));
     
        return iRc;
    }
    
   
 
    //---------------------------------------------------------------
    //                    C o n t a i n s
    //---------------------------------------------------------------

    bool            ListDL32_Contains (
        LISTDL32_DATA   *this,
        void            *pRecord
    )
    {
        LISTDL32_NODE   *pRecordNode;
        LISTDL32_NODE   *pCurNode;
        
        // Do initialization.
        if( NULL == pRecord ) {
            return false;
        }
        pRecordNode = Entry2Node( pRecord );
        
        pCurNode = this->head ? Index2Node(this->head) : NULL;
        while (pCurNode) {
            if (pCurNode == pRecordNode) {
                return true;
            }
            pCurNode = Index2Node(pCurNode->next);
        }
        
        // Return to caller.
        return false;
    }



    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            ListDL32_Dealloc (
        OBJ_ID          objId
    )
    {
        LISTDL32_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }
        
        mem_Free(this);
        this = NULL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D e l e t e
    //---------------------------------------------------------------

    bool            ListDL32_Delete (
        LISTDL32_DATA   *this,
        LISTDL32_INDEX  index
    )
    {
        LISTDL32_NODE   *pNode;
        
        // Do initialization.
        if (index && this->pIndex2Ptr)
            ;
        else
            return false;
        pNode = Index2Node(index);

        if ((pNode->prev == 0) && (Index2Node(this->head) == pNode)) {  /*** First Element ***/
            this->head = pNode->next;
        } else {
            Index2Node(pNode->prev)->next = pNode->next;
        }
        if ((pNode->next == 0) && (Index2Node(this->tail) == pNode)) {  /*** Last Element ***/
            this->tail = pNode->prev;
        } else {
            Index2Node(pNode->next)->prev = pNode->prev;
        }
        this->size--;
        pNode->next = 0;
        pNode->prev = 0;
        
        // Return to caller.
        return true;
    }


    bool             ListDL32_DeleteEntry (
        LISTDL32_DATA   *this,
        void            *pRecord
    )
    {
        LISTDL32_NODE   *pNode;
        LISTDL32_NODE   *pCurNode;
        
        // Do initialization.
        if( NULL == pRecord ) {
            return false;
        }
        pNode = Entry2Node( pRecord );
        
        pCurNode = this->head ? Index2Node(this->head) : NULL;
        while (pCurNode) {
            if (pCurNode == pNode) {
                if ((pNode->prev == 0) && (Index2Node(this->head) == pNode)) {  /*** First Element ***/
                    this->head = pNode->next;
                } else {
                    Index2Node(pNode->prev)->next = pNode->next;
                }
                if ((pNode->next == 0) && (Index2Node(this->tail) == pNode)) {  /*** Last Element ***/
                    this->tail = pNode->prev;
                } else {
                    Index2Node(pNode->next)->prev = pNode->prev;
                }
                this->size--;
                pNode->next = 0;
                pNode->prev = 0;
                return true;
            }
            pCurNode = Index2Node(pCurNode->next);
        }
        
        // Return to caller.
        return false;
    }


    void *          ListDL32_DeleteHead (
        LISTDL32_DATA   *this
    )
    {
        LISTDL32_NODE   *pNode;

        // Do initialization.
        if (this->head && this->pIndex2Ptr)
            ;
        else
            return NULL;
        pNode = Index2Node(this->head);

        // Remove it from the head of the list.
        this->head = pNode->next;
        if (pNode->next == 0) {         /*** Last Element ***/
            this->tail = pNode->prev;
        }
        else {
            Index2Node(pNode->next)->prev = pNode->prev;
        }
        this->size--;
        pNode->next = 0;
        pNode->prev = 0;
        
        // Return to caller.
        return Node2Entry(pNode);
    }


    void *          ListDL32_DeleteTail (
        LISTDL32_DATA   *this
    )
    {
        LISTDL32_NODE   *pNode;

        // Do initialization.
        if (this->tail && this->pIndex2Ptr)
            ;
        else
            return NULL;
        pNode = Index2Node(this->tail);

        // Remove it from the head of the list.
        this->tail = pNode->prev;
        if (pNode->prev == 0) {         /*** Last Element ***/
            this->head = pNode->next;
        }
        else {
            Index2Node(pNode->prev)->next = pNode->next;
        }
        this->size--;
        pNode->next = 0;
        pNode->prev = 0;
        
        // Return to caller.
        return Node2Entry(pNode);
    }



    //---------------------------------------------------------------
    //                      E n t r y
    //---------------------------------------------------------------

    void *          ListDL32_Entry (
        LISTDL32_DATA   *this,
        LISTDL32_INDEX  index
    )
    {
        LISTDL32_NODE   *pNode;

        // Do initialization.
        if (index && this->pIndex2Ptr)
            ;
        else
            return NULL;
        pNode = Index2Node(index);

        // Return to caller.
        return Node2Entry(pNode);
    }


    
    //---------------------------------------------------------------
    //                          H e a d
    //---------------------------------------------------------------

    void *          ListDL32_Head (
        LISTDL32_DATA   *this
    )
    {
        LISTDL32_NODE   *pNode;

        // Do initialization.
        if (this->head && this->pIndex2Ptr)
            ;
        else
            return NULL;
        pNode = Index2Node(this->head);

        // Return to caller.
        return Node2Entry(pNode);
    }


    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    bool            ListDL32_Init (
        LISTDL32_DATA   *this,
        uint32_t        iOffset,        // Offset of Node Field within Structure
        void *          (*pIndex2Ptr)(OBJ_ID, LISTDL32_INDEX),
        OBJ_ID          pIndex2PtrObj
    )
    {
        //uint32_t        cbSize = sizeof(LISTDL32_DATA);
        //ERESULT         eRc;
        
        if (OBJ_NIL == this) {
            return false;
        }
        if (NULL == pIndex2Ptr) {
            DEBUG_BREAK();
            return false;
        }

        // Set up the areas.
        this->head = 0;
        this->tail = 0;
        this->size = 0;
        this->iOffset = iOffset;
        this->pIndex2Ptr = pIndex2Ptr;
        this->pIndex2PtrObj = pIndex2PtrObj;
        
        return true;
    }

     

    //---------------------------------------------------------------
    //                    I s V a l i d L i s t
    //---------------------------------------------------------------
    
    bool            ListDL32_IsValidList (
        LISTDL32_DATA   *this
    )
    {
        LISTDL32_NODE   *pNode = NULL;
        uint32_t        size = 0;
        LISTDL32_INDEX  index;

        // Do initialization.
        if (NULL == this) {
            return false;
        }
        
        // Point to the indexed node.
        index = this->head;
        while (index) {
            pNode = Index2Node(index);
            if (pNode->next) {
                if (Index2Node(pNode->next)->prev == index)
                    ;
                else
                    return false;
            } else {
                if (index == this->tail)
                    ;
                else
                    return false;
            }
            if (pNode->prev) {
                if (Index2Node(pNode->prev)->next == index)
                    ;
                else
                    return false;
            } else {
                if (index == this->head)
                    ;
                else
                    return false;
            }
            index = pNode->next;
            size++;
        }
        if (size == this->size)
            ;
        else
            return false;

        // Return to caller.
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                  M o v e 2 H e a d
    //---------------------------------------------------------------

    bool             ListDL32_Move2Head(
        LISTDL32_DATA   *this,
        LISTDL32_INDEX  index
    )
    {
        LISTDL32_NODE   *pNode;
        bool            fRc;
        
        // Do initialization.
        if (index && (index <= this->size) && this->pIndex2Ptr)
            ;
        else
            return false;
        pNode = Index2Node(index);
        
        if (this->head == index) {
            return true;
        }
        
        fRc = ListDL32_Delete(this, index);
        if (!fRc) {
            return false;
        }
        fRc = ListDL32_Add2Head(this, index);
        if (!fRc) {
            return false;
        }
        
        // Return to caller.
        return true;
    }



    //---------------------------------------------------------------
    //                        N e x t
    //---------------------------------------------------------------

    void *          ListDL32_Next (
        LISTDL32_DATA   *this,
        void            *pEntry
    )
    {
        LISTDL32_NODE   *pNode;

        // Do initialization.

        // Point to the Next Node.
        if (NULL == pEntry) {
            pNode = Index2Node(this->head);
        } else {
            pNode = Entry2Node(pEntry);
            if (pNode->next) {
                pNode = Index2Node(pNode->next);
            } else {
                pNode = NULL;
            }
        }
        if (pNode && (this->size > 0))
            ;
        else
            return NULL;

        // Return to caller.
        return Node2Entry(pNode);
    }



    //---------------------------------------------------------------
    //                        P r e v
    //---------------------------------------------------------------

    void *          ListDL32_Prev (
        LISTDL32_DATA   *this,
        void            *pEntry
    )
    {
        LISTDL32_NODE   *pNode;

        // Do initialization.

        // Point to the Next Node.
        if (NULL == pEntry) {
            pNode = Index2Node(this->tail);
        } else {
            pNode = Entry2Node(pEntry);
            if (pNode->prev) {
                pNode = Index2Node(pNode->prev);
            } else {
                pNode = NULL;
            }
        }
        if (pNode && (this->size > 0))
            ;
        else
            return NULL;

        // Return to caller.
        return Node2Entry(pNode);
    }



    //---------------------------------------------------------------
    //                          S h i f t
    //---------------------------------------------------------------

    bool            ListDL32_Shift2Head (
        LISTDL32_DATA   *this
    )
    {
        LISTDL32_INDEX  index;
        bool            fRc;

        // Do initialization.
        if (NULL == this) {
            return false;
        }
        if (2 > this->size)
            return true;

        index = this->tail;
        fRc = ListDL32_Delete(this, index);
        if (!fRc)
            return false;
        fRc = ListDL32_Add2Head(this, index);
        
        // Return to caller.
        return fRc;
    }


    bool            ListDL32_Shift2Tail (
        LISTDL32_DATA   *this
    )
    {
        LISTDL32_INDEX  index;
        bool            fRc;

        // Do initialization.
        if (NULL == this) {
            return false;
        }
        if (2 > this->size)
            return true;

        index = this->head;
        fRc = ListDL32_Delete(this, index);
        if (!fRc)
            return false;
        fRc = ListDL32_Add2Tail(this, index);
        
        // Return to caller.
        return fRc;
    }



    //---------------------------------------------------------------
    //                        S o r t
    //---------------------------------------------------------------

    bool            ListDL32_Sort (
        LISTDL32_DATA   *this,
        int             (*pCompare)(void *, void *)
    )
    {
        LISTDL32_NODE   *pNode0;
        LISTDL32_NODE   *pNode1;
        LISTDL32_INDEX  index0;
        LISTDL32_INDEX  index1;
        int             iRc;
        int             i;

        /*      Insertion Sort from Wikipedia
         *
         *  for i = 1 to length(A)
         *      j = i
         *      while j > 0 and A[j-1] > A[j]
         *          swap A[j] and A[j-1]
         *          j = j - 1
         *      end while
         *  end for
         */
            
        // Do initialization.
        if (NULL == this)
            return false;
        if (2 > this->size)
            return true;

        for (i=1; i<this->size; i++) {
            index1 = i + 1;
            pNode1 = Index2Node(index1);
            while (pNode1->prev) {
                index0 = pNode1->prev;
                pNode0 = Index2Node(index0);
                iRc = (*pCompare)(Node2Entry(pNode0), Node2Entry(pNode1));
                if (iRc > 0) {
                    if (pNode0->prev) {
                        Index2Node(pNode0->prev)->next = index1;
                    }
                    else {
                        this->head = index1;
                    }
                    if (pNode1->next) {
                        Index2Node(pNode1->next)->prev = index0;
                    }
                    else {
                        this->tail = index0;
                    }
                    // Swap the two entries.
                    pNode0->next = pNode1->next;
                    pNode1->next = index0;
                    pNode1->prev = pNode0->prev;
                    pNode0->prev = index1;
                }
                else
                    break;
            }
        }
        
        // Return to caller.
        return true;
    }



    //---------------------------------------------------------------
    //                          T a i l
    //---------------------------------------------------------------

    void *          ListDL32_Tail (
        LISTDL32_DATA   *this
    )
    {
        LISTDL32_NODE   *pNode;

        // Do initialization.
        if (this->tail && this->pIndex2Ptr)
            ;
        else
            return NULL;
        pNode = Index2Node(this->tail);

        // Return to caller.
        return Node2Entry(pNode);
    }


    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = ListDL32_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     ListDL32_ToDebugString (
        LISTDL32_DATA   *this,
        int             indent
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        //uint32_t        i;
        //uint32_t        j;
        LISTDL32_NODE   *pNode;
        LISTDL32_INDEX  index;

        // Do initialization.
              
        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc = AStr_AppendPrint(
                    pStr,
                    "{%p(%s) size=%d head=%d tail=%d offset=%d\n",
                    this,
                    "ListDL32",
                    ListDL32_getSize(this),
                    this->head,
                    this->tail,
                    this->iOffset
            );
        
        if (this->head) {
            if (indent) {
                AStr_AppendCharRepeatA(pStr, indent+8, ' ');
            }
            eRc = AStr_AppendA(pStr,"Nodes\n");
        }
        for (index=this->head; index;) {
            if (index) {
                pNode = Index2Node(index);
                if (indent) {
                    AStr_AppendCharRepeatA(pStr, indent+4, ' ');
                }
                eRc = AStr_AppendPrint(
                            pStr,
                            "%4d(%p) prev=%d next=%d\n",
                            index,
                            Node2Entry(pNode),
                            pNode->prev,
                            pNode->next
                    );
                index = pNode->next;
            }
        }
        
#ifdef  XYZZY
        if (this->pData) {
            if (((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString(
                                                    this->pData,
                                                    indent+3
                            );
                if (pWrkStr) {
                    AStr_Append(pStr, pWrkStr);
                    obj_Release(pWrkStr);
                }
            }
        }
#endif
        
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc =   AStr_AppendPrint(
                    pStr,
                    " %p(%s)}\n", 
                    this, 
                    "ListDL32"
                );
        
        return pStr;
    }
    
    
    
    
    
#ifdef  __cplusplus
}
#endif


