// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//              An Array of Nodes (NodeArray) Object Support
//****************************************************************


/*
 * File:   NodeArray.c
 *  Generated 06/21/2026 10:23:02
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
#include        <NodeArray_internal.h>
#include        <JsonIn.h>
#include        <NodeEnum_internal.h>
#include        <trace.h>
#include        <utf8.h>






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

    //---------------------------------------------------------------
    //              F i n d  i n  N o d e  S e t 
    //---------------------------------------------------------------

    NODE_DATA *     NodeArray_FindInNodeSet(
        NODE_DATA       *pNode,
        NODE_DATA       **ppNodeSet     // NULL-terminated Set of Nodes
    )
    {
        int             cmp;
        NODE_DATA       *pFound = OBJ_NIL;
        OBJ_IUNKNOWN    *pNodeVtbl;

        // Do initialization.
#ifdef NDEBUG
#else
        if (OBJ_NIL == pNode) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
#ifdef NDEBUG
#else
        if (NULL == ppNodeSet) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pNodeVtbl = obj_getVtbl(pNode);
#ifdef NDEBUG
#else
        if (NULL == pNodeVtbl->pCompare) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        while (*ppNodeSet) {
            cmp = pNodeVtbl->pCompare(pNode, *ppNodeSet);
            if(0 == cmp) {
                pFound = *ppNodeSet;
                break;
            }
            ++ppNodeSet;
        }

        // Return to caller.
        return pFound;
    }





    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    NODEARRAY_DATA * 
                    NodeArray_Alloc (
        void
    )
    {
        NODEARRAY_DATA  *this;
        uint32_t        cbSize = sizeof(NODEARRAY_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    NODEARRAY_DATA * 
                    NodeArray_New (
        void
    )
    {
        NODEARRAY_DATA  *this;
        
        this = NodeArray_Alloc( );
        if (this) {
            this = NodeArray_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          A r r a y
    //---------------------------------------------------------------
    
    OBJARRAY_DATA *     NodeArray_getArray (
        NODEARRAY_DATA  *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeArray_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pArray;
    }
    
    
    bool            NodeArray_setArray (
        NODEARRAY_DATA  *this,
        OBJARRAY_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!NodeArray_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pArray) {
            obj_Release(this->pArray);
        }
        this->pArray = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                      C o m p a r e
    //---------------------------------------------------------------

    bool            NodeArray_setCompare (
        NODEARRAY_DATA  *this,
        int             (*pCompare)(NODE_DATA *, NODE_DATA *)
    )
    {
#ifdef NDEBUG
#else
        if( !NodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->pCompare = pCompare;

        return true;
    }



    //---------------------------------------------------------------
    //                          F l a g
    //---------------------------------------------------------------
    
#ifdef  NEED_ALL_GENERATED_CODE
    // @property Flag
    //  assumes a 1-byte flag in this object.

    bool            NodeArray_getFlag (
        NODEARRAY_DATA  *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeArray_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->flag ? true : false;
    }


    bool            NodeArray_setFlag (
        NODEARRAY_DATA  *this,
        bool            fValue
    )
    {
#ifdef NDEBUG
#else
        if (!NodeArray_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = fValue ? 1 : 0;

        return true;
    }
#endif



    //---------------------------------------------------------------
    //                      M e s s a g e s
    //---------------------------------------------------------------

#ifdef   NODEARRAY_MSGS
    bool            NodeArray_setMsgs (
        NODEARRAY_DATA  *this,
        void            (*pMsgInfo)(OBJ_ID, const char *, ...),
        void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...),
        OBJ_ID          pObj
    )
    {
#ifdef NDEBUG
#else
        if (!NodeArray_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->pMsgInfo = pMsgInfo;
        this->pMsgWarn = pMsgWarn;
        this->pMsgObj = pObj;

        return true;
    }
#endif



    //---------------------------------------------------------------
    //                        O t h e r
    //---------------------------------------------------------------

    OBJ_ID          NodeArray_getOther (
        NODEARRAY_DATA  *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !NodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return ObjArray_getOther(this->pArray);
    }


    bool            NodeArray_setOther (
        NODEARRAY_DATA  *this,
        OBJ_ID          pValue
    )
    {
        bool            fRc;

#ifdef NDEBUG
#else
        if( !NodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        fRc = ObjArray_setOther(this->pArray, pValue);

        return fRc;
    }



    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
#ifdef  NEED_ALL_GENERATED_CODE
    uint16_t        NodeArray_getPriority (
        NODEARRAY_DATA  *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeArray_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            NodeArray_setPriority (
        NODEARRAY_DATA  *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!NodeArray_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        return true;
    }
#endif



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        NodeArray_getSize (
        NODEARRAY_DATA  *this
    )
    {
#ifdef NDEBUG
#else
        if (!NodeArray_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return ObjArray_getSize(this->pArray);
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
#ifdef  NODEARRAY_SUPER_DEFINED
    NODE_DATA *     NodeArray_getSuper (
        NODEARRAY_DATA  *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeArray_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return (NODE_DATA *)this;
    }
#else
    OBJ_DATA *      NodeArray_getSuper (
        NODEARRAY_DATA  *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeArray_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return (OBJ_DATA *)this;
    }
#endif

    
    OBJ_IUNKNOWN *  NodeArray_getSuperVtbl (
        NODEARRAY_DATA  *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeArray_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                          A d d
    //---------------------------------------------------------------



    //---------------------------------------------------------------
    //                       A p p e n d
    //---------------------------------------------------------------

    ERESULT         NodeArray_Append(
        NODEARRAY_DATA  *this,
        NODEARRAY_DATA  *pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        uint32_t        i;
        uint32_t        max;
        NODE_DATA       *pNode;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !NodeArray_Validate(pOther) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        max = NodeArray_getSize(pOther);

        for (i=0; i<max; ++i) {
            pNode = NodeArray_Get(pOther, i+1);
            if (pNode) {
                eRc = NodeArray_AppendNode(this, pNode, NULL);
                if (ERESULT_FAILED(eRc)) {
                    return eRc;
                }
            }
        }

        // Return to caller.
        return eRc;
    }


    ERESULT         NodeArray_AppendNode(
        NODEARRAY_DATA  *this,
        NODE_DATA       *pObject,
        uint32_t        *pIndex
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if((pObject == OBJ_NIL) || (!obj_IsKindOf(pObject, OBJ_IDENT_NODE))) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        if (OBJ_NIL == this->pArray) {
            this->pArray = (void *)ObjArray_New();
            if (OBJ_NIL == this->pArray) {
                DEBUG_BREAK();
                return ERESULT_MEMORY_EXCEEDED;
            }
        }

        eRc = ObjArray_AppendObj(this->pArray, pObject, pIndex);

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before 
     a copy of the object is performed.
     Example:
     @code 
        ERESULT eRc = NodeArray_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another NODEARRAY object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         NodeArray_Assign (
        NODEARRAY_DATA  *this,
        NODEARRAY_DATA  *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!NodeArray_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!NodeArray_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Assign any Super(s).
        if (this->pSuperVtbl && (this->pSuperVtbl->pWhoAmI() != OBJ_IDENT_OBJ)) {
            if (this->pSuperVtbl->pAssign) {
                eRc = this->pSuperVtbl->pAssign(this, pOther);
                if (ERESULT_FAILED(eRc)) {
                    return eRc;
                }
            }
        }

        // Release objects and areas in other object.
        if (pOther->pArray) {
            obj_Release(pOther->pArray);
            pOther->pArray = OBJ_NIL;
        }

        // Create a copy of objects and areas in this object placing
        // them in pOther.
        if (this->pArray) {
            if (obj_getVtbl(this->pArray)->pCopy) {
                pOther->pArray = obj_getVtbl(this->pArray)->pCopy(this->pArray);
            }
            else {
                obj_Retain(this->pArray);
                pOther->pArray = this->pArray;
            }
        }

        // Copy other data from this object to other.
        pOther->pCompare     = this->pCompare; 

        // Return to caller.
        eRc = ERESULT_SUCCESS;
    //eom:
        return eRc;
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
    int             NodeArray_Compare (
        NODEARRAY_DATA  *this,
        NODEARRAY_DATA  *pOther
    )
    {
        int             iRc = -1;
        uint32_t        max;
        uint32_t        i;
#ifdef  xyzzy        
        const
        char            *pStr1;
        const
        char            *pStr2;
#endif
        
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  NODEARRAY_SINGLETON
        if (OBJ_NIL == this) {
            this = NodeArray_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!NodeArray_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!NodeArray_Validate(pOther)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -2;
        }
#endif
        max = NodeArray_getSize(this);

        for (i=0; i<max; i++) {
            NODE_DATA       *pNode1 = NodeArray_Get(this, i+1);
            NODE_DATA       *pNode2 = NodeArray_Get(this, i+1);
            if (OBJ_NIL == pNode1) {
                return -2;
            }
            if (OBJ_NIL == pNode2) {
                return 1;
            }
            iRc = this->pCompare(pNode1, pNode2);
            if (0 == iRc) {
                continue;
            }
            break;
        }
     
        return iRc;
    }
    
   
 
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        NodeArray      *pCopy = NodeArray_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a NODEARRAY object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    NODEARRAY_DATA * 
                    NodeArray_Copy (
        NODEARRAY_DATA  *this
    )
    {
        NODEARRAY_DATA  *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!NodeArray_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef NODEARRAY_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = NodeArray_New( );
        if (pOther) {
            eRc = NodeArray_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
#endif
        
        // Return to caller.
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            NodeArray_Dealloc (
        OBJ_ID          objId
    )
    {
        NODEARRAY_DATA  *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!NodeArray_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((NODEARRAY_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        NodeArray_setArray(this, OBJ_NIL);

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                         D e e p  C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        NodeArray      *pDeepCopy = NodeArray_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a NODEARRAY object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    NODEARRAY_DATA * 
                    NodeArray_DeepCopy (
        NODEARRAY_DATA  *this
    )
    {
        NODEARRAY_DATA  *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!NodeArray_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = NodeArray_New( );
        if (pOther) {
            eRc = NodeArray_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e l e t e
    //---------------------------------------------------------------

    NODE_DATA *     NodeArray_Delete (
        NODEARRAY_DATA  *this,
        uint32_t        index
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        if (this->pArray) {
            pNode = ObjArray_Delete(this->pArray, index);
        }

        // Return to caller.
        return pNode;
    }


    NODE_DATA *     NodeArray_DeleteFirst (
        NODEARRAY_DATA  *this
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        if (this->pArray) {
            pNode = ObjArray_DeleteFirst(this->pArray);
        }

        // Return to caller.
        return pNode;
    }


    NODE_DATA *     NodeArray_DeleteLast (
        NODEARRAY_DATA    *this
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        if (this->pArray) {
            pNode = ObjArray_DeleteLast(this->pArray);
        }

        // Return to caller.
        return pNode;
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    /*!
     Disable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         NodeArray_Disable (
        NODEARRAY_DATA  *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  NODEARRAY_SINGLETON
        if (OBJ_NIL == this) {
            this = NodeArray_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!NodeArray_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Put code here...

        TRC_OBJ(this,"\tEnabled?: %s:\n", obj_Enable(this) ? "true" : "false");
        obj_Disable(this);
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    /*!
     Enable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         NodeArray_Enable (
        NODEARRAY_DATA  *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  NODEARRAY_SINGLETON
        if (OBJ_NIL == this) {
            this = NodeArray_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!NodeArray_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        TRC_OBJ(this,"\tEnabled?: %s:\n", obj_Enable(this) ? "true" : "false");
#ifdef   NODEARRAY_MSGS
        if (this->pMsgInfo) {
            this->pMsgInfo(this->pMsgObj, "Enabling object!\n");
        }
#endif
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          E n q u e u e
    //---------------------------------------------------------------

    /*!
     Enqueue the given node.  Enqueue inserts the node as the first
     element of the array.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         NodeArray_Enqueue (
        NODEARRAY_DATA  *this,
        NODE_DATA       *pNode
    )
    {
        ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!NodeArray_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (pNode && obj_IsKindOf(pNode, OBJ_IDENT_NODE)) {
        } else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
    #endif
        
        eRc = NodeArray_InsertAfter(this, 0, pNode);

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                        E n u m
    //---------------------------------------------------------------

    NODEENUM_DATA * NodeArray_Enum (
        NODEARRAY_DATA  *this
    )
    {
        ERESULT         eRc;
        NODEENUM_DATA   *pEnum = OBJ_NIL;
        uint32_t        size;
        uint32_t        index;
        NODE_DATA       *pNode;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        if (this->pArray) {
            pEnum = NodeEnum_New();
            size = ObjArray_getSize(this->pArray);
            for (index = 0; index < size; ++index) {
                pNode = ObjArray_Get(this->pArray, index+1);
                eRc = NodeEnum_Append(pEnum, pNode, index+1);
            }
        }

        // Return to caller.
        return pEnum;
    }



    //---------------------------------------------------------------
    //                      E x p a n d
    //---------------------------------------------------------------

    ERESULT         NodeArray_Expand (
        NODEARRAY_DATA  *this,
        uint32_t        min
    )
    {
        ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!NodeArray_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif

        eRc = ObjArray_Expand(this->pArray, min);

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          F i n d
    //---------------------------------------------------------------

    NODE_DATA *     NodeArray_Find (
        NODEARRAY_DATA  *this,
        NODE_DATA       *pNode
    )
    {
        NODE_DATA       *pWork = OBJ_NIL;
        uint32_t        size;
        uint32_t        i;
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeArray_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
        if( OBJ_NIL == pNode ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return OBJ_NIL;
        }
#endif

        size = NodeArray_getSize(this);
        for (i=0; i<size; ++i) {
            pWork = (NODE_DATA *)ObjArray_Get(this->pArray, i+1);
            if (pWork) {
                eRc = this->pCompare(pNode, pWork);
                if( eRc == 0 ) {
                    return pWork;
                }
            }
        }

        // Return to caller.
        return OBJ_NIL;
    }


    NODE_DATA *     NodeArray_FindA (
        NODEARRAY_DATA  *this,
        int32_t         cls,
        const
        char            *pNameA
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;
        NODE_DATA       *pFound = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeArray_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
        if( OBJ_NIL == pNameA ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return OBJ_NIL;
        }
#endif

        pNode = Node_NewWithUTF8AndClass(cls, pNameA, OBJ_NIL);
        pFound = NodeArray_Find(this, pNode);
        obj_Release(pNode);
        pNode = OBJ_NIL;

        // Return to caller.
        return pFound;
    }



    //---------------------------------------------------------------
    //                     F o r  E a c h
    //---------------------------------------------------------------

    ERESULT         NodeArray_ForEach (
        NODEARRAY_DATA  *this,
        P_ERESULT_EXIT3 pScan,
        OBJ_ID          pObj,            // Used as first parameter of scan method
        void            *pArg3
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        uint32_t        index;
        uint32_t        size;
        NODE_DATA       *pNode = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        if (this->pArray && pScan) {
            size = ObjArray_getSize(this->pArray);
            for (index = 0; index < size; ++index) {
                pNode = ObjArray_Get(this->pArray, (index + 1));
                eRc = pScan(pObj, pNode, pArg3);
                if (ERESULT_FAILED(eRc))
                    break;
            }
        }

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                        G e t
    //---------------------------------------------------------------

    NODE_DATA *     NodeArray_Get (
        NODEARRAY_DATA  *this,
        uint32_t        index       // Relative to 1
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        if (this->pArray) {
            pNode = ObjArray_Get(this->pArray, index);
        }

        // Return to caller.
        return pNode;
    }


    NODE_DATA *     NodeArray_GetFirst (
        NODEARRAY_DATA  *this
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;

        // Do initialization.
        if (NULL == this) {
            return OBJ_NIL;
        }
#ifdef NDEBUG
#else
        if( !NodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        if (this->pArray) {
            pNode = ObjArray_GetFirst(this->pArray);
        }

        // Return to caller.
        return pNode;
    }


    NODE_DATA *     NodeArray_GetLast (
        NODEARRAY_DATA  *this
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;

        // Do initialization.
        if (NULL == this) {
            return OBJ_NIL;
        }
#ifdef NDEBUG
#else
        if( !NodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        if (this->pArray) {
            pNode = ObjArray_GetLast(this->pArray);
        }

        // Return to caller.
        return pNode;
    }



    //---------------------------------------------------------------
    //                          H a s h
    //---------------------------------------------------------------
    
    uint32_t        NodeArray_Hash(
        NODEARRAY_DATA  *this
    )
    {
        uint32_t        hash = 0;
        char            *pStr = NULL;
        
#ifdef NDEBUG
#else
        if( !NodeArray_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
       
        /* 
        pStr = array_Ptr(this->pData, 1);
        if (pStr) {
            hash = str_HashAcmA(pStr, NULL);
        }
        */
        
        return hash;
    }
    
    

    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    NODEARRAY_DATA * 
                    NodeArray_Init (
        NODEARRAY_DATA  *this
    )
    {
        uint32_t        cbSize = sizeof(NODEARRAY_DATA);
        //ERESULT         eRc;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        /* cbSize can be zero if Alloc() was not called and we are
         * are passed the address of a zero'd area.
         */
        //cbSize = obj_getSize(this);       // cbSize must be set in Alloc().
        if (cbSize == 0) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

#ifdef  NODEARRAY_SUPER_DEFINED
        this = (OBJ_ID)Node_Init((NODE_DATA *)this);   // Needed for Inheritance
#else
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_NODEARRAY);
#endif
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&NodeArray_Vtbl);
#ifdef  NODEARRAY_JSON_SUPPORT
        JsonIn_RegisterClass(NodeArray_Class());
#endif
        
        this->pArray = ObjArray_New( );
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        this->pCompare = &Node_Compare;


#ifdef NDEBUG
#else
        if (!NodeArray_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "NodeArray::sizeof(NODEARRAY_DATA) = %lu\n", 
                sizeof(NODEARRAY_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(NODEARRAY_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                          I n s e r t
    //---------------------------------------------------------------

    ERESULT         NodeArray_InsertAfter(
        NODEARRAY_DATA  *this,
        uint32_t        index,
        NODE_DATA       *pObject
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if((pObject == OBJ_NIL) || (!obj_IsKindOf(pObject, OBJ_IDENT_NODE))) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        if (OBJ_NIL == this->pArray) {
            this->pArray = ObjArray_New();
            if (OBJ_NIL == this->pArray) {
                DEBUG_BREAK();
                return ERESULT_MEMORY_EXCEEDED;
            }
        }

        eRc = ObjArray_InsertObj(this->pArray, index, pObject);

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                      I s  E n a b l e d
    //---------------------------------------------------------------
    
    bool            NodeArray_IsEnabled (
        NODEARRAY_DATA  *this
    )
    {
        //ERESULT         eRc;
        bool            fRc = false;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  NODEARRAY_SINGLETON
        if (OBJ_NIL == this) {
            this = NodeArray_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!NodeArray_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return fRc;
        }
#endif
        
        if (obj_IsEnabled(this)) {
            fRc = true;
        }
        
        // Return to caller.
        return fRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          P u t
    //---------------------------------------------------------------

    ERESULT         NodeArray_Put(
        NODEARRAY_DATA  *this,
        uint32_t        index,
        NODE_DATA       *pObject
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (pObject == OBJ_NIL)
            ;
        else if (!obj_IsKindOf(pObject, OBJ_IDENT_NODE)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        if (OBJ_NIL == this->pArray) {
            this->pArray = ObjArray_New();
            if (OBJ_NIL == this->pArray) {
                DEBUG_BREAK();
                return ERESULT_MEMORY_EXCEEDED;
            }
        }

        eRc = ObjArray_Put(this->pArray, index, pObject);

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    /*!
     Return information about this object. This method can translate
     methods to strings and vice versa, return the address of the
     object information structure.
     Example:
     @code
        // Return a method pointer for a string or NULL if not found. 
        void        *pMethod = NodeArray_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_DATA, an object's data is returned
                        if it fits in a "void *".
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "NodeArray", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          NodeArray_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        NODEARRAY_DATA  *this = objId;
        const
        char            *pStrA = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!NodeArray_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(NODEARRAY_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)NodeArray_Class();
                break;

            case OBJ_QUERYINFO_TYPE_DATA:
                switch (*pStrA) {
     
                    case 'A':
                        if (str_Compare("Array", (char *)pStrA) == 0) {
                            return (void *)this->pArray;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;

                              
            case OBJ_QUERYINFO_TYPE_DATA_PTR:
                switch (*pStrA) {
     
                    case 'S':
                        if (str_Compare("SuperClass", (char *)pStrA) == 0) {
                            return (void *)(obj_getInfo(this)->pClassSuperObject);
                        }
                        break;
                        
                    default:
                        break;
                }
                break;

            case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStrA) {
                        
                    case 'D':
                        if (str_Compare("Disable", (char *)pStrA) == 0) {
                            return NodeArray_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStrA) == 0) {
                            return NodeArray_Enable;
                        }
                        break;

                    case 'P':
#ifdef  NODEARRAY_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStrA) == 0) {
                            return NodeArray_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStrA) == 0) {
                            return NodeArray_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStrA) == 0) {
                            return NodeArray_ToDebugString;
                        }
#ifdef  NODEARRAY_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStrA) == 0) {
                            return NodeArray_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStrA) == 0) {
                            return NodeArray_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == NodeArray_ToDebugString)
                    return "ToDebugString";
#ifdef  NODEARRAY_JSON_SUPPORT
                if (pData == NodeArray_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                         R e v e r s e
    //---------------------------------------------------------------

    /*!
     Reverse the order of the array.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         NodeArray_Reverse (
        NODEARRAY_DATA  *this
    )
    {
        ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!NodeArray_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif

        eRc = ObjArray_Reverse(this->pArray);

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                         S o r t
    //---------------------------------------------------------------

    ERESULT         NodeArray_SortAscending(
        NODEARRAY_DATA  *this
    )
    {
        ERESULT         eRc = ERESULT_FAILURE;
        NODE_DATA       *pNode = OBJ_NIL;

        // Do initialization.
        if (NULL == this) {
            return ERESULT_INVALID_OBJECT;
        }
#ifdef NDEBUG
#else
        if( !NodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        if (this->pArray) {
            if (NodeArray_getSize(this)) {
                pNode = ObjArray_GetFirst(this->pArray);
                if (pNode) {
                    if (this->pCompare) {
                        eRc = ObjArray_SortAscending(this->pArray, (OBJ_COMPARE)this->pCompare);
                    }
                }
            }
        }

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                    T o  C l a s s  A r r a y
    //---------------------------------------------------------------

    I32ARRAY_DATA * NodeArray_ToClassArray(
        NODEARRAY_DATA  *this
    )
    {
        int             j;
        I32ARRAY_DATA   *pArray = OBJ_NIL;
        NODE_DATA       *pNode;
        int32_t         chr;

        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }

        pArray = I32Array_New( );

        if (pArray && this->pArray) {
            for (j=0; j<ObjArray_getSize(this->pArray); ++j) {
                pNode = ObjArray_Get(this->pArray, j+1);
                if (pNode) {
                    chr = Node_getClass(pNode);
                }
                else {
                    chr = 0;
                }
                I32Array_AppendData(pArray, chr);
            }
        }


        return pArray;
    }



    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = NodeArray_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     NodeArray_ToDebugString (
        NODEARRAY_DATA  *this,
        int             indent
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        uint32_t        j;
        uint32_t        jMax;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!NodeArray_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pInfo = obj_getInfo(this);
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
                    "{%p(%s) size=%d retain=%d\n",
                    this,
                    pInfo->pClassName,
                    NodeArray_getSize(this),
                    obj_getRetainCount(this)
            );
        USE_VAR(eRc);

        if (this->pArray) {
            jMax = ObjArray_getSize(this->pArray);
            for (j=0; j<jMax; ++j) {
                NODE_DATA       *pNode = ObjArray_Get(this->pArray, j+1);
                if (pNode) {
                    ASTR_DATA       *pWrk = Node_ToDebugString(pNode, indent+4);
                    if (pWrk) {
                        AStr_AppendA(pStr, "  ");
                        AStr_Append(pStr, pWrk);
                        obj_Release(pWrk);
                    }
                }
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
                    pInfo->pClassName
                );
        USE_VAR(eRc);
        
        return pStr;
    }
    
    
    ASTR_DATA *     NodeArray_ToString(
        NODEARRAY_DATA  *this
    )
    {
        int             j;
        ASTR_DATA       *pStr;

        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }

        pStr = AStr_New();
        AStr_AppendA(pStr, "Array[\n");

        if (this->pArray) {
            for (j=0; j<ObjArray_getSize(this->pArray); ++j) {
                NODE_DATA       *pNode = ObjArray_Get(this->pArray, j+1);
                if (pNode) {
                    ASTR_DATA       *pWrk = Node_ToString(pNode);
                    if (pWrk) {
                        AStr_AppendA(pStr, "  ");
                        AStr_Append(pStr, pWrk);
                        obj_Release(pWrk);
                    }
                }
            }
        }

        AStr_AppendA(pStr, "]\n\n");

        return pStr;
    }



    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

#ifdef NDEBUG
#else
    bool            NodeArray_Validate (
        NODEARRAY_DATA  *this
    )
    {
        bool            fRc;
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_NODEARRAY)) {
                if (!obj_IsKindOf(this, OBJ_IDENT_NODE))
                    return false;
            } else {
                // 'this' is not our kind of data. We really don't
                // know what that it is at this point. 
                return false;
            }
        }
        else {
            // 'this' is NULL.
            return false;
        }
        // Now, we have validated that we have a valid pointer in
        // 'this'.
        
        if (!obj_IsKindOf(this->pArray, OBJ_IDENT_OBJARRAY))
            return false;



        // Return to caller.
        return true;
    }
#endif


    
    //---------------------------------------------------------------
    //                   V i s i t  A s c e n d i n g
    //---------------------------------------------------------------

    ERESULT         NodeArray_VisitAscending(
        NODEARRAY_DATA  *this,
        ERESULT         (pVisitor)(
                                   OBJ_ID,             // Object supplied below
                                   NODE_DATA *         // Current Node
                        ),
        OBJ_ID          pObject
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        NODE_DATA       *pNode = OBJ_NIL;
        uint32_t        i;
        uint32_t        iMax;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeArray_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
;
        }
        BREAK_NULL(this->pArray);
#endif

        iMax = ObjArray_getSize(this->pArray);
        for (i=0; i<iMax; ++i) {
            pNode = ObjArray_Get(this->pArray, (i+1));
            eRc = pVisitor(pObject, pNode);
            if (ERESULT_FAILED(eRc)) {
                break;
            }
        }

        // Return to caller.
        return eRc;
    }



    
#ifdef  __cplusplus
}
#endif


