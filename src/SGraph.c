// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//              A Simple Graph (SGraph) Object Support
//****************************************************************


/*
 * File:   SGraph.c
 *  Generated 10/21/2022 02:32:39
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
#include        <SGraph_internal.h>
#include        <JsonIn.h>
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

#ifdef XYZZY
    static
    void            SGraph_task_body (
        void            *pData
    )
    {
        //SGRAPH_DATA  *this = pData;
        TRC_OBJ(this, "%s:\n", __func__);
        
    }
#endif



    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    SGRAPH_DATA *     SGraph_Alloc (
        void
    )
    {
        SGRAPH_DATA       *this;
        uint32_t        cbSize = sizeof(SGRAPH_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    SGRAPH_DATA *     SGraph_New (
        void
    )
    {
        SGRAPH_DATA       *this;
        
        this = SGraph_Alloc( );
        if (this) {
            this = SGraph_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                         E d g e s
    //---------------------------------------------------------------
    
    BITMATRIX_DATA * SGraph_getEdges(
        SGRAPH_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !SGraph_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pEdges;
    }
    
    
    bool            SGraph_setEdges(
        SGRAPH_DATA     *this,
        BITMATRIX_DATA  *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !SGraph_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pEdges) {
            obj_Release(this->pEdges);
        }
        this->pEdges = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                      M e s s a g e s
    //---------------------------------------------------------------

#ifdef   SGRAPH_MSGS
    bool            SGraph_setMsgs (
        SGRAPH_DATA    *this,
        void            (*pMsgInfo)(OBJ_ID, const char *, ...),
        void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...),
        OBJ_ID          pObj
    )
    {
#ifdef NDEBUG
#else
        if (!SGraph_Validate(this)) {
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
    //                         N o d e s
    //---------------------------------------------------------------
    
    NODEARRAY_DATA * SGraph_getNodes(
        SGRAPH_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !SGraph_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pNodes;
    }
    
    
    bool        SGraph_setNodes(
        SGRAPH_DATA     *this,
        NODEARRAY_DATA  *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !SGraph_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pNodes) {
            obj_Release(this->pNodes);
        }
        this->pNodes = pValue;
        
        return true;
    }
        
        
        
    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        SGraph_getPriority (
        SGRAPH_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SGraph_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            SGraph_setPriority (
        SGRAPH_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!SGraph_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        SGraph_getSize (
        SGRAPH_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!SGraph_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA * SGraph_getStr (
        SGRAPH_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SGraph_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStr;
    }
    
    
    bool        SGraph_setStr (
        SGRAPH_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!SGraph_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pStr) {
            obj_Release(this->pStr);
        }
        this->pStr = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
#ifdef  SGRAPH_SUPER_DEFINED
    OBJ_DATA *  SGraph_getSuper (
        SGRAPH_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SGraph_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return (OBJ_DATA *)this;
    }
#else
    OBJ_DATA *  SGraph_getSuper (
        SGRAPH_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SGraph_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return (OBJ_DATA *)this;
    }
#endif

    
    OBJ_IUNKNOWN *  SGraph_getSuperVtbl (
        SGRAPH_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SGraph_Validate(this)) {
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
    //                       A s s i g n
    //---------------------------------------------------------------
    
    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before 
     a copy of the object is performed.
     Example:
     @code 
        ERESULT eRc = SGraph_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another SGRAPH object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         SGraph_Assign (
        SGRAPH_DATA       *this,
        SGRAPH_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!SGraph_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!SGraph_Validate(pOther)) {
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
#ifdef  XYZZY
        if (pOther->pArray) {
            obj_Release(pOther->pArray);
            pOther->pArray = OBJ_NIL;
        }
#endif

        // Create a copy of objects and areas in this object placing
        // them in other.
#ifdef  XYZZY
        if (this->pArray) {
            if (obj_getVtbl(this->pArray)->pCopy) {
                pOther->pArray = obj_getVtbl(this->pArray)->pCopy(this->pArray);
            }
            else {
                obj_Retain(this->pArray);
                pOther->pArray = this->pArray;
            }
        }
#endif

        // Copy other data from this object to other.
        //pOther->x     = this->x; 

        // Return to caller.
        eRc = ERESULT_SUCCESS;
    eom:
        //FIXME: Implement the assignment.        
        eRc = ERESULT_NOT_IMPLEMENTED;
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
    int             SGraph_Compare (
        SGRAPH_DATA     *this,
        SGRAPH_DATA     *pOther
    )
    {
        int             iRc = -1;
#ifdef  xyzzy        
        const
        char            *pStr1;
        const
        char            *pStr2;
#endif
        
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  SGRAPH_SINGLETON
        if (OBJ_NIL == this) {
            this = SGraph_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!SGraph_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!SGraph_Validate(pOther)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -2;
        }
#endif

        //TODO: iRc = utf8_StrCmp(AStr_getData(this->pStr), AStr_getData(pOther->pStr));
     
        return iRc;
    }
    
   
 
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        SGraph      *pCopy = SGraph_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a SGRAPH object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    SGRAPH_DATA *     SGraph_Copy (
        SGRAPH_DATA       *this
    )
    {
        SGRAPH_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!SGraph_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef SGRAPH_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = SGraph_New( );
        if (pOther) {
            eRc = SGraph_Assign(this, pOther);
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

    void            SGraph_Dealloc (
        OBJ_ID          objId
    )
    {
        SGRAPH_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!SGraph_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((SGRAPH_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        SGraph_setEdges(this, OBJ_NIL);
        SGraph_setNodes(this, OBJ_NIL);
        SGraph_setStr(this, OBJ_NIL);

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
        SGraph      *pDeepCopy = SGraph_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a SGRAPH object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    SGRAPH_DATA *     SGraph_DeepCopy (
        SGRAPH_DATA       *this
    )
    {
        SGRAPH_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!SGraph_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = SGraph_New( );
        if (pOther) {
            eRc = SGraph_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        return pOther;
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
    ERESULT         SGraph_Disable (
        SGRAPH_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  SGRAPH_SINGLETON
        if (OBJ_NIL == this) {
            this = SGraph_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!SGraph_Validate(this)) {
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
    //                       E d g e  A d d
    //---------------------------------------------------------------
    
    ERESULT         SGraph_EdgeAdd(
        SGRAPH_DATA     *this,
        uint32_t        from,
        uint32_t        to
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !SGraph_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (0 == from) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if (0 == to) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if (OBJ_NIL == this->pNodes) {
            DEBUG_BREAK();
            return ERESULT_GENERAL_FAILURE;
        }
#endif
        
        if (OBJ_NIL == this->pEdges) {
            this->pEdges = BitMatrix_NewSquare(NodeArray_getSize(this->pNodes));
            if (OBJ_NIL == this->pEdges) {
                DEBUG_BREAK();
                return ERESULT_OUT_OF_MEMORY;
            }
        }
        
        eRc = BitMatrix_Set(this->pEdges, from, to, true);
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                       E d g e  E x i s t s
    //---------------------------------------------------------------
    
    bool            SGraph_EdgeExists(
        SGRAPH_DATA     *this,
        uint32_t        from,
        uint32_t        to
    )
    {
        bool            fRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !SGraph_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return false;
        }
        if (0 == from) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return false;
        }
        if (0 == to) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return false;
        }
#endif
        
        fRc = BitMatrix_Get(this->pEdges, from, to);
        
        // Return to caller.
        return fRc;
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
    ERESULT         SGraph_Enable (
        SGRAPH_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  SGRAPH_SINGLETON
        if (OBJ_NIL == this) {
            this = SGraph_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!SGraph_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        TRC_OBJ(this,"\tEnabled?: %s:\n", obj_Enable(this) ? "true" : "false");
#ifdef   SGRAPH_MSGS
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
    //                          I n i t
    //---------------------------------------------------------------

    SGRAPH_DATA *   SGraph_Init (
        SGRAPH_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(SGRAPH_DATA);
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

#ifdef  SGRAPH_SUPER_DEFINED
        this = (OBJ_ID)obj_Init((OBJ_DATA *)this);   // Needed for Inheritance
#else
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_SGRAPH);
#endif
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&SGraph_Vtbl);
#ifdef  SGRAPH_JSON_SUPPORT
        JsonIn_RegisterClass(SGraph_Class());
#endif
        
        /*
        this->pArray = ObjArray_New( );
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        */

        this->pEdges = BitMatrix_NewSquare(1);
        if (OBJ_NIL == this->pEdges) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

        this->pNodes = NodeArray_New( );
        if (OBJ_NIL == this->pNodes) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
#ifdef NDEBUG
#else
        if (!SGraph_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "SGraph::sizeof(SGRAPH_DATA) = %lu\n", 
                sizeof(SGRAPH_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(SGRAPH_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                      I s  E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         SGraph_IsEnabled (
        SGRAPH_DATA       *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  SGRAPH_SINGLETON
        if (OBJ_NIL == this) {
            this = SGraph_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!SGraph_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (obj_IsEnabled(this)) {
            return ERESULT_SUCCESS_TRUE;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS_FALSE;
    }
    
    
    
    //---------------------------------------------------------------
    //                       N o d e  A d d
    //---------------------------------------------------------------
    
    uint32_t        SGraph_NodeAdd(
        SGRAPH_DATA     *this,
        NODE_DATA       *pNode
    )
    {
        ERESULT         eRc;
        uint32_t        index = 0;
        uint32_t        amt;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !SGraph_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pNode) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        eRc = NodeArray_AppendNode(this->pNodes, pNode, &index);
        if (ERESULT_FAILED(eRc)) {
            return eRc;
        }
        
        // Expand the Edges matrix if needed.
        if (index > BitMatrix_getXSize(this->pEdges)) {
            amt = index - BitMatrix_getXSize(this->pEdges);
            BitMatrix_InflateX(this->pEdges, amt);
            BitMatrix_InflateY(this->pEdges, amt);
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                       N o d e  A d j
    //---------------------------------------------------------------
    
    U32ARRAY_DATA *  SGraph_NodeAdj(
        SGRAPH_DATA     *this,
        uint32_t        n
    )
    {
        U32ARRAY_DATA   *pSet = OBJ_NIL;
        U32ARRAY_DATA   *pPred = OBJ_NIL;
        U32ARRAY_DATA   *pSucc = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !SGraph_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return pSet;
        }
        if ((0 == n) || (n > NodeArray_getSize(this->pNodes))) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return pSet;
        }
#endif
        
        pPred = SGraph_NodePred(this, n);
        if (OBJ_NIL == pPred) {
            return pSet;
        }
        
        pSucc = SGraph_NodeSucc(this, n);
        if (OBJ_NIL == pPred) {
            obj_Release(pPred);
            return pSet;
        }
        
        // Calculate the set.
        pSet = u32Array_Merge(pPred, pSucc);
        if (OBJ_NIL == pSet) {
            obj_Release(pPred);
            obj_Release(pSucc);
            return pSet;
        }
        
        // Return to caller.
        obj_Release(pPred);
        obj_Release(pSucc);
        return pSet;
    }
    
    
    
    //---------------------------------------------------------------
    //                       N o d e  D e g r e e
    //---------------------------------------------------------------
    
    uint32_t        SGraph_NodeDegree(
        SGRAPH_DATA     *this,
        uint32_t        n
    )
    {
        uint32_t        size = 0;
        U32ARRAY_DATA   *pSet = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !SGraph_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return size;
        }
        if ((0 == n) || (n > NodeArray_getSize(this->pNodes))) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return size;
        }
#endif
        
        pSet = SGraph_NodeAdj(this, n);
        if (OBJ_NIL == pSet) {
            return size;
        }
        
        size = u32Array_getSize(pSet);
        
        // Return to caller.
        obj_Release(pSet);
        return size;
    }
    
    
    
    //---------------------------------------------------------------
    //                       N o d e  P r e d
    //---------------------------------------------------------------
    
    U32ARRAY_DATA *  SGraph_NodePred(
        SGRAPH_DATA     *this,
        uint32_t        n
    )
    {
        uint32_t        index = 0;
        BITSET_DATA     *pBitSet = OBJ_NIL;
        U32ARRAY_DATA   *pSet = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !SGraph_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return pSet;
        }
        if ((0 == n) || (n > NodeArray_getSize(this->pNodes))) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return pSet;
        }
#endif
        
        //                                       y  x  len
        pBitSet = BitMatrix_GetCol(this->pEdges, 1, n,  0);
        if (OBJ_NIL == pBitSet) {
            return pSet;
        }
        
        // Calculate the set.
        pSet = u32Array_New( );
        if (OBJ_NIL == pSet) {
            return pSet;
        }
        for (index=0; index < BitSet_getSize(pBitSet); ++index) {
            if (BitSet_Get(pBitSet, index+1)) {
                u32Array_AppendData(pSet, index+1);
            }
        }
        
        // Return to caller.
        obj_Release(pBitSet);
        pBitSet = OBJ_NIL;
        return pSet;
    }
    
    
    
    //---------------------------------------------------------------
    //                       N o d e  S u c c
    //---------------------------------------------------------------
    
    U32ARRAY_DATA *  SGraph_NodeSucc(
        SGRAPH_DATA     *this,
        uint32_t        n
    )
    {
        uint32_t        index = 0;
        BITSET_DATA     *pBitSet = OBJ_NIL;
        U32ARRAY_DATA   *pSet = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !SGraph_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return pSet;
        }
        if ((0 == n) || (n > NodeArray_getSize(this->pNodes))) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return pSet;
        }
#endif
        
        //                                       y  x  len
        pBitSet = BitMatrix_GetRow(this->pEdges, n, 1,  0);
        if (OBJ_NIL == pBitSet) {
            return pSet;
        }
        
        // Calculate the set.
        pSet = u32Array_New( );
        if (OBJ_NIL == pSet) {
            return pSet;
        }
        for (index=0; index < BitSet_getSize(pBitSet); ++index) {
            if (BitSet_Get(pBitSet, index+1)) {
                u32Array_AppendData(pSet, index+1);
            }
        }
        
        // Return to caller.
        obj_Release(pBitSet);
        pBitSet = OBJ_NIL;
        return pSet;
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
        void        *pMethod = SGraph_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_DATA, an object's data is returned
                        if it fits in a "void *".
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "SGraph", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          SGraph_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        SGRAPH_DATA     *this = objId;
        const
        char            *pStrA = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!SGraph_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(SGRAPH_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)SGraph_Class();
                break;

            case OBJ_QUERYINFO_TYPE_DATA:
                switch (*pStrA) {
     
                    case 'S':
                        if (str_Compare("Str", (char *)pStrA) == 0) {
                            return (void *)this->pStr;
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
                            return SGraph_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStrA) == 0) {
                            return SGraph_Enable;
                        }
                        break;

                    case 'P':
#ifdef  SGRAPH_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStrA) == 0) {
                            return SGraph_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStrA) == 0) {
                            return SGraph_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStrA) == 0) {
                            return SGraph_ToDebugString;
                        }
#ifdef  SGRAPH_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStrA) == 0) {
                            return SGraph_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStrA) == 0) {
                            return SGraph_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == SGraph_ToDebugString)
                    return "ToDebugString";
#ifdef  SGRAPH_JSON_SUPPORT
                if (pData == SGraph_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //     R e f l e x i v e  T r a n s i t i v e  C l o r u r e
    //---------------------------------------------------------------

    /*!
     Calculatte the Reflective Transitive Closure of the Graph.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         SGraph_ReflectiveTransitiveClosure (
        SGRAPH_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  SGRAPH_SINGLETON
        if (OBJ_NIL == this) {
            this = SGraph_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!SGraph_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        eRc = BitMatrix_ReflectiveTransitiveClosure(this->pEdges);
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = SGraph_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     SGraph_ToDebugString (
        SGRAPH_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        //uint32_t        i;
        //uint32_t        j;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!SGraph_Validate(this)) {
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
                    SGraph_getSize(this),
                    obj_getRetainCount(this)
            );

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
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //              T r a n s i t i v e  C l o r u r e
    //---------------------------------------------------------------

    /*!
     Calculatte the Transitive Closure of the Graph.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         SGraph_TransitiveClosure (
        SGRAPH_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  SGRAPH_SINGLETON
        if (OBJ_NIL == this) {
            this = SGraph_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!SGraph_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        eRc = BitMatrix_TransitiveClosure(this->pEdges);
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

#ifdef NDEBUG
#else
    bool            SGraph_Validate (
        SGRAPH_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_SGRAPH))
                ;
            else {
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


        if (!(obj_getSize(this) >= sizeof(SGRAPH_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef  __cplusplus
}
#endif


