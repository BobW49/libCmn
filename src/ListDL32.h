// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//    Doubly-Linked List using 32-bit Indices (ListDL32) Header
//****************************************************************

/*
 * Program
 *          Doubly-Linked List using 32-bit Indices (ListDL32)
 * Purpose
 *          These subroutines provide a general purpose set of Doubly-
 *          Linked List Manipulation routines. The linkage between the
 *          entries is done using a 32-bit index. It is assumed that
 *          the caller provides all areas and a routine to access the
 *          entries using an index relative to one.
 *
 *          No memory allocation will be performed in these routines.
 *          They were designed to be utilized in other routines/objects
 *          and for its areas needed to be created/freed by the
 *          controlling routines/object.
 *
 *          Enqueue()/Dequeue() create a FIFO stack (First In First Out).
 *          Push()/Pop() create a LIFO stack (Last In First Out).
 *
 * Remarks
 *  1.      These routines are potentially reentrant.  Protection
 *          must be provided if two threads are accessing/updating
 *          at the same time.
 *  2.      All indices are relative to 1. The 0 index is left for
 *          end of list or empty list.
 *  3.      The entries and LISTDL32_DATA are not controlled by these
 *          routines. Therefore, the user is responsible for deleting
 *          /freeing them when the list is no longer needed.
 *
 * History
 *  09/30/2023 Generated
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


/*----------------------------------------------------------------
    The following should be added to the appropriate _defs.h file
    in the _idents_e enum:
        OBJ_IDENT_LISTDL32,         //  Doubly-Linked List using 32-bit Indices
        OBJ_IDENT_LISTDL32_CLASS,
    The following should be added to the appropriate objects.json.txt
    or program.json.txt file:
        {name:"ListDL32",  desc:"Doubly-Linked List using 32-bit Indices"},
 *----------------------------------------------------------------*/



//#define   %{NAMEU}_IS_IMMUTABLE     1
//#define   %{NAMEU}_JSON_SUPPORT     1
//#define   %{NAMEU}_SINGLETON        1
//#define       LISTDL32_MSGS   1
//#define   %{NAMEU}_SUPER_DEFINED     1


#include        <cmn_defs.h>
#include        <AStr.h>
#ifdef  LISTDL32_SUPER_DEFINED
#include        <obj.h>
#endif


#ifndef         LISTDL32_H
#define         LISTDL32_H





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


#define    LISTDL32_INDEX    uint32_t
    
    //                  *** Node Entry ***
    // This control block must be included in each of the nodes that you
    // add to the list. It is found by the functions below providing a
    // pointer to a valid record which contaains this data and the offset
    // from the LISTDL32_DATA which denotes where this data can be found
    // within that record.
#if !defined(__arm64__)
#pragma pack(push, 1)
#endif
    typedef struct ListDL32_Node_s {
        LISTDL32_INDEX    prev;
        LISTDL32_INDEX    next;
    } LISTDL32_NODE;
#if !defined(__arm64__)
#pragma pack(pop)
#endif


    //                  *** Main Control Block ***
    // This control block must be provided on entry to every function
    // in this system.  It must be initialized to binary zeroes prior
    // to the first call to any functions within this system.
    // Warning -- Do not add any fields before head and tail since
    //          they may be used in place of LISTDL32_NODE.
#if !defined(__arm64__)
#pragma pack(push, 1)
#endif
    typedef struct  ListDL32_data_s {
        LISTDL32_INDEX  head;
        LISTDL32_INDEX  tail;
        uint32_t        size;
        uint32_t        iOffset;
        /*
         * Index2Ptr() converts an index to a valid record pointer.
         * It uses an optional Object Pointer to help with that
         * conversion. It is a required routine.
         */
        void *          (*pIndex2Ptr)(OBJ_ID, LISTDL32_INDEX);
        OBJ_ID          pIndex2PtrObj;
    } LISTDL32_DATA;
#if !defined(__arm64__)
#pragma pack(pop)
#endif





    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

   /*!
     Allocate a new Data Area and partially initialize.
     @return    pointer to LISTDL32_DATA if successful, otherwise OBJ_NIL.
     @warning    Remember to free this area with Mem_Free();
     */
    LISTDL32_DATA * ListDL32_Alloc (
        void
    );
    
    
    // listdl_DataLength() returns the size of the Object's Main Area which must
    // be supplied to all functions.
    // Returns:
    //    Number of Nodes
    uint32_t        ListDL32_DataLength (
        void
    );


    LISTDL32_DATA * ListDL32_New (
        uint32_t        offset,     // Offset of Node Field within Structure
        void *          (*pIndex2Ptr)(OBJ_ID, LISTDL32_INDEX),
        OBJ_ID          pIndex2PtrObj
    );
    
    
#ifdef  LISTDL32_JSON_SUPPORT
    LISTDL32_DATA * ListDL32_NewFromJsonString (
        ASTR_DATA       *pString
    );

    LISTDL32_DATA * ListDL32_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    // @property Size contains the current number of entries in the
    // Doubly-Linked List.
    uint32_t         ListDL32_getSize (
        LISTDL32_DATA   *this
    );


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*! Add2Head() adds a new entry to the Doubly-Linked list as
        the new Head of the List. It is also a synonym for Enqueue()
        and Push();
        @param      this    main data area pointer
        @param      index   index number to be added
        @returns    true for Successful Completion or false for any errors
     */
    bool            ListDL32_Add2Head (
        LISTDL32_DATA   *this,
        LISTDL32_INDEX  index
    );
#define ListDL32_Enqueue(this,index) ListDL32_Add2Head(this,index)
#define ListDL32_Push(this,index) ListDL32_Add2Head(this,index)


    /*! Add2Tail() adds a new entry to the Doubly-Linked list as
        the Last Entry in the List.
     @param      this    main data area pointer
     @param      index   index number to be added
     @returns    true for Successful Completion or false for any errors
    */
    bool            ListDL32_Add2Tail (
        LISTDL32_DATA   *this,
        LISTDL32_INDEX  index
    );


    /*! Contains() checks to see if an entry is linked into the Doubly-Linked
        list.
        @param      this    main data area pointer
        @param      pEntry  Entry Address
        @returns    true for Entry is in the list or false for any errors
     */
    bool            ListDL32_Contains (
        LISTDL32_DATA   *this,
        void            *pEntry
    );


    bool             ListDL32_Delete (
        LISTDL32_DATA   *this,
        LISTDL32_INDEX  index
    );


    bool             ListDL32_DeleteEntry (
        LISTDL32_DATA   *this,
        void            *pRecord
    );


    /*! DeleteHead() removes/deletes the entry from the list head
     and turns the address of the indicated entry in the list.
     @param      this    main data area pointer
     @returns    address of the entry or NULL for any errors
    */
    void *          ListDL32_DeleteHead (
        LISTDL32_DATA   *this
    );
#define ListDL32_Pop(this) ListDL32_DeleteHead(this)


    /*! DeleteTail() removes/deletes the entry from the list tail
     and turns the address of the indicated entry in the list.
     @param      this    main data area pointer
     @returns    address of the entry or NULL for any errors
    */
    void *          ListDL32_DeleteTail (
        LISTDL32_DATA   *this
    );
#define ListDL32_Dequeue(this) ListDL32_DeleteTail(this)



    /*! Entry() returns the address of the indicated entry in the list.
     @param      this    main data area pointer
     @param      index   index number to be added
     @returns    address of the entry or NULL for any errors
    */
    void *          ListDL32_Entry (
        LISTDL32_DATA   *this,
        LISTDL32_INDEX  index
    );

   
    /*! Head() returns the address of the list's head entry.
     @param      this    main data area pointer
     @returns    address of the entry or NULL for any errors
    */
    void *          ListDL32_Head (
        LISTDL32_DATA   *this
    );
#define ListDL32_Top(this) ListDL32_Head(this)


    /*!
     Initialize the main control block to an empty list.
     Example:
     @code
        bool  fRc = listdl_Init(&freeList, offsetof(LRU_SECTOR, lruList));
     @endcode
     @param     this    list control block pointer
     @param     offset  number of bytes displacement into the list entry to
                        find the LISTDL_NODE.
     @param     pIndex2Ptr converts an index to a valid record pointer.
                It may use the optional Object Pointer to help with that
                conversion. It is a required routine.
     @param     pIndex2PtrObj is the optional object pointer which will
                be provided as the first parameter of the Index2Ptr()
                routine.
     @return    If successful, true. Otherwise, false.
     */
    bool            ListDL32_Init (
        LISTDL32_DATA   *this,
        uint32_t        offset,     // Offset of Node Field within Structure
        void *          (*pIndex2Ptr)(OBJ_ID, LISTDL32_INDEX),
        OBJ_ID          pIndex2PtrObj
    );


    bool            ListDL32_IsValidList (
        LISTDL32_DATA   *this
    );


    /*! Move2Head() moves the indicated entry from its current position to
        the head of the list.
         @param      this    main data area pointer
         @param      index   index number to be moved
         @return    If successful, true. Otherwise, false.
    */
    bool             ListDL32_Move2Head (
        LISTDL32_DATA   *this,
        LISTDL32_INDEX  index
    );


    /*! Next() returns the next entry from the current entry in the
        Doubly-Linked List.    The current pointer is updated to the
        Next Entry.    If the Current Entry is NULL (ie end of list),
        then the Head Entry is returned next. To scan the list from
        head to tail, use:
        @code
            for (void *pEntry = ListDL32_Next(this,NULL); pEntry; pEntry=ListDL32_Next(this,pEntry)) {
                        // Process the entry!
            }
        @endcode
        @param      this    main data area pointer
        @param      pEntry  Entry Address
        @returns    Entry pointer if successful or false for any errors
     */
    void *          ListDL32_Next (
        LISTDL32_DATA   *this,
        void            *pEntry
    );


    /*! Prev() returns the previous entry from the current entry in the
        Doubly-Linked List.    The current pointer is updated to the
        Previous Entry.    If the Current Entry is NULL (ie end of list),
        then the Tail Entry is returned next. To scan the list from
        tail to head, use:
        @code
            for (void *pEntry = ListDL32_Prev(this,NULL); pEntry; pEntry=ListDL32_Prev(this,pEntry)) {
                        // Process the entry!
            }
        @endcode
        @param      this    main data area pointer
        @param      pEntry  Entry Address
        @returns    Entry pointer if successful or false for any errors
     */
    void *          ListDL32_Prev (
        LISTDL32_DATA   *this,
        void            *pEntry
    );


    /*! Shift2Head() moves the tail entry from its current position to
        the head of the list.
         @param      this    main data area pointer
         @return    If successful, true. Otherwise, false.
    */
    bool            ListDL32_Shift2Head (
        LISTDL32_DATA   *this
    );


    /*! Shift2Tail() moves the head entry from its current position to
        the tail of the list.
         @param      this    main data area pointer
         @return    If successful, true. Otherwise, false.
    */
    bool            ListDL32_Shift2Tail (
        LISTDL32_DATA   *this
    );


    bool            ListDL32_Sort (
        LISTDL32_DATA   *this,
        int             (*pCompare)(void *, void *)
    );


    /*! Tail() returns the address of the list's tail entry.
     @param      this    main data area pointer
     @returns    address of the entry or NULL for any errors
    */
    void *          ListDL32_Tail (
        LISTDL32_DATA   *this
    );


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
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     ListDL32_ToDebugString (
        LISTDL32_DATA   *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* LISTDL32_H */

