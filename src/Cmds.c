// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   Cmds.c
 *  Generated 08/30/2022 00:22:12
 *
 * Remarks:
 *   1. We use Nodes to store the Command data. The long name is the
 *      Node::Name, the short name is the Node::Class and the Descrip-
 *      tion is the Node::Other.
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
#include        <Cmds_internal.h>
#include        <JsonIn.h>
#include        <trace.h>
#include        <utf8.h>



typedef struct {
    W32CHR_T        shortName;
    NODE_DATA       *pFound;
}       CMDS_FINDSCAN_DATA;



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
    //                    F i n d  S c a n
    //---------------------------------------------------------------

    /*!
     Enable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Cmds_FindScan (
        CMDS_DATA       *this,
        NODE_DATA       *pNode,
        CMDS_FINDSCAN_DATA
                        *pData
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);

        if (Node_getClass(pNode) == pData->shortName) {
            pData->pFound = pNode;
            eRc = ERESULT_GENERAL_FAILURE;
        }
        
        // Return to caller.
        return eRc;
    }




    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    CMDS_DATA *     Cmds_Alloc (
        void
    )
    {
        CMDS_DATA       *this;
        uint32_t        cbSize = sizeof(CMDS_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    CMDS_DATA *     Cmds_New (
        void
    )
    {
        CMDS_DATA       *this;
        
        this = Cmds_Alloc( );
        if (this) {
            this = Cmds_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                           C m d s
    //---------------------------------------------------------------
    
    NODEARRAY_DATA *    Cmds_getCmds (
        CMDS_DATA           *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Cmds_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pCmds;
    }
    
    
    bool            Cmds_setCmds (
        CMDS_DATA       *this,
        NODEARRAY_DATA  *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Cmds_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pCmds) {
            obj_Release(this->pCmds);
        }
        this->pCmds = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                           C o m p l e t e d
    //---------------------------------------------------------------
    
    NODELIST_DATA *     Cmds_getCompleted (
        CMDS_DATA           *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Cmds_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pCompleted;
    }
    
    
    bool            Cmds_setCompleted (
        CMDS_DATA       *this,
        NODELIST_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Cmds_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pCompleted) {
            obj_Release(this->pCompleted);
        }
        this->pCompleted = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                      M e s s a g e s
    //---------------------------------------------------------------

#ifdef   CMDS_MSGS
    bool            Cmds_setMsgs (
        CMDS_DATA    *this,
        void            (*pMsgInfo)(OBJ_ID, const char *, ...),
        void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...),
        OBJ_ID          pObj
    )
    {
#ifdef NDEBUG
#else
        if (!Cmds_Validate(this)) {
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
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        Cmds_getPriority (
        CMDS_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Cmds_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            Cmds_setPriority (
        CMDS_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!Cmds_Validate(this)) {
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
    
    uint32_t        Cmds_getSize (
        CMDS_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!Cmds_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA * Cmds_getStr (
        CMDS_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Cmds_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStr;
    }
    
    
    bool        Cmds_setStr (
        CMDS_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Cmds_Validate(this)) {
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
    
#ifdef  CMDS_SUPER_DEFINED
    OBJ_DATA *  Cmds_getSuper (
        CMDS_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Cmds_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return (OBJ_DATA *)this;
    }
#else
    OBJ_DATA *  Cmds_getSuper (
        CMDS_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Cmds_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return (OBJ_DATA *)this;
    }
#endif

    
    OBJ_IUNKNOWN *  Cmds_getSuperVtbl (
        CMDS_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Cmds_Validate(this)) {
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

    /*!
     Add a command from the given data. Either the long name, the
     short bame or both must be present.
     @param     this        object pointer
     @param     pLongName   Optional long command name
     @param     shortName   Optional short command name charactrr
     @param     pDesc       Optional string pointer that describes
                            the command and its syntax
     @param     pClass      Class object pointer for the command
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Cmds_AddData (
        CMDS_DATA       *this,
        char            *pLongName,
        W32CHR_T        shortName,
        char            *pDesc,
        OBJ_ID          *pClass
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        NODE_DATA       *pNode = OBJ_NIL;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  CMDS_SINGLETON
        if (OBJ_NIL == this) {
            this = Cmds_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Cmds_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pClass) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        if ((NULL == pLongName) && (0 == shortName)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }

        pNode = Node_NewWithUTF8AndClass(shortName, pLongName, pClass);
        if (OBJ_NIL == pNode) {
            DEBUG_BREAK();
            return ERESULT_OUT_OF_MEMORY;
        }
        if (pDesc) {
            ASTR_DATA       *pStr = AStr_NewA(pDesc);
            Node_setOther(pNode, pStr);
            obj_Release(pStr);
        }
        eRc = NodeArray_AppendNode(this->pCmds, pNode, NULL);
        obj_Release(pNode);
        pNode = OBJ_NIL;
        this->fSort = 1;
        
        // Return to caller.
        return eRc;
    }


    /*!
     Add a command from the data in its class object.
     @param     this    object pointer
     @param     pClass  class object pointer for command
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Cmds_AddObj (
        CMDS_DATA       *this,
        OBJ_ID          *pClass
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        char            *pDesc = NULL;
        char            *pLongName = NULL;
        W32CHR_T        shortName = 0;
        W32CHR_T        *pShortName;
        NODE_DATA       *pNode = OBJ_NIL;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  CMDS_SINGLETON
        if (OBJ_NIL == this) {
            this = Cmds_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Cmds_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pClass) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if (!obj_IsKindOf(pClass, OBJ_IDENT_CMD_CLASS)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        pDesc     = obj_QueryInfo(pClass, OBJ_QUERYINFO_TYPE_DATA, "Desc");
        pLongName = obj_QueryInfo(pClass, OBJ_QUERYINFO_TYPE_DATA, "LongName");
        pShortName = obj_QueryInfo(pClass, OBJ_QUERYINFO_TYPE_DATA, "ShortName");
        if (pShortName)
            shortName = *pShortName;
        if ((NULL == pLongName) && (0 == shortName)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }

        pNode = Node_NewWithUTF8AndClass(shortName, pLongName, pClass);
        if (OBJ_NIL == pNode) {
            DEBUG_BREAK();
            return ERESULT_OUT_OF_MEMORY;
        }
        if (pDesc) {
            ASTR_DATA       *pStr = AStr_NewA(pDesc);
            Node_setOther(pNode, pStr);
            obj_Release(pStr);
        }
        eRc = NodeArray_AppendNode(this->pCmds, pNode, NULL);
        obj_Release(pNode);
        pNode = OBJ_NIL;
        this->fSort = 1;
        
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
        ERESULT eRc = Cmds_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another CMDS object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         Cmds_Assign (
        CMDS_DATA       *this,
        CMDS_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!Cmds_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Cmds_Validate(pOther)) {
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
    //eom:
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
    int             Cmds_Compare (
        CMDS_DATA     *this,
        CMDS_DATA     *pOther
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
#ifdef  CMDS_SINGLETON
        if (OBJ_NIL == this) {
            this = Cmds_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Cmds_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!Cmds_Validate(pOther)) {
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
        Cmds      *pCopy = Cmds_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a CMDS object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    CMDS_DATA *     Cmds_Copy (
        CMDS_DATA       *this
    )
    {
        CMDS_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!Cmds_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef CMDS_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = Cmds_New( );
        if (pOther) {
            eRc = Cmds_Assign(this, pOther);
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

    void            Cmds_Dealloc (
        OBJ_ID          objId
    )
    {
        CMDS_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!Cmds_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((CMDS_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        Cmds_setCmds(this, OBJ_NIL);
        Cmds_setCompleted(this, OBJ_NIL);
        Cmds_setStr(this, OBJ_NIL);

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
        Cmds      *pDeepCopy = Cmds_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a CMDS object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    CMDS_DATA *     Cmds_DeepCopy (
        CMDS_DATA       *this
    )
    {
        CMDS_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!Cmds_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = Cmds_New( );
        if (pOther) {
            eRc = Cmds_Assign(this, pOther);
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
    ERESULT         Cmds_Disable (
        CMDS_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  CMDS_SINGLETON
        if (OBJ_NIL == this) {
            this = Cmds_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Cmds_Validate(this)) {
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
    ERESULT         Cmds_Enable (
        CMDS_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  CMDS_SINGLETON
        if (OBJ_NIL == this) {
            this = Cmds_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Cmds_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        TRC_OBJ(this,"\tEnabled?: %s:\n", obj_Enable(this) ? "true" : "false");
#ifdef   CMDS_MSGS
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
    //                          E n u m
    //---------------------------------------------------------------

    /*!
     Enable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    NODEENUM_DATA * Cmds_Enum (
        CMDS_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        NODEENUM_DATA   *pEnum = OBJ_NIL;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  CMDS_SINGLETON
        if (OBJ_NIL == this) {
            this = Cmds_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Cmds_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return pEnum;
        }
#endif
        
        if (this->fSort) {
            eRc = Cmds_Sort(this);
            if (ERESULT_SUCCESSFUL(eRc)) {
                pEnum = NodeArray_Enum(this->pCmds);
            }
        }
        
        // Return to caller.
        return pEnum;
    }



    //---------------------------------------------------------------
    //                          F i n d
    //---------------------------------------------------------------

    /*!
     Enable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    NODE_DATA *     Cmds_Find (
       CMDS_DATA        *this,
        W32CHR_T        shortName,
        const
        char            *pLongNameA
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        CMDS_FINDSCAN_DATA
                        data;

        NODE_DATA       *pNode = OBJ_NIL;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  CMDS_SINGLETON
        if (OBJ_NIL == this) {
            this = Cmds_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Cmds_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return pNode;
        }
        if ((NULL == pLongNameA) && (0 == shortName)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return pNode;
        }
#endif
        
        if (pLongNameA) {
            pNode = NodeArray_FindA(this->pCmds, 0, pLongNameA);
            if (pNode)
                return pNode;
        }
        
        data.shortName = shortName;
        data.pFound = OBJ_NIL;
        eRc = NodeArray_ForEach(this->pCmds, (void *)Cmds_FindScan, this, &data);
        USE_VAR(eRc);
        if (data.pFound)
            pNode = data.pFound;
        
        // Return to caller.
        return pNode;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    CMDS_DATA *   Cmds_Init (
        CMDS_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(CMDS_DATA);
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

#ifdef  CMDS_SUPER_DEFINED
        this = (OBJ_ID)obj_Init((OBJ_DATA *)this);   // Needed for Inheritance
#else
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_CMDS);
#endif
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&Cmds_Vtbl);
#ifdef  CMDS_JSON_SUPPORT
        JsonIn_RegisterClass(Cmds_Class());
#endif
        
        this->pCmds = NodeArray_New( );
        if (OBJ_NIL == this->pCmds) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

        this->pCompleted = NodeList_New( );
        if (OBJ_NIL == this->pCompleted) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

#ifdef NDEBUG
#else
        if (sizeof(W32CHR_T) > sizeof(int32_t)) {
            DEBUG_BREAK();
            fprintf(stderr, "W32CHR_T is too big for Node::Class property!\n\n");
            obj_Release(this);
            return OBJ_NIL;
        }
        if (!Cmds_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "Cmds::sizeof(CMDS_DATA) = %lu\n", 
                sizeof(CMDS_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(CMDS_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                      I s  E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         Cmds_IsEnabled (
        CMDS_DATA       *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  CMDS_SINGLETON
        if (OBJ_NIL == this) {
            this = Cmds_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Cmds_Validate(this)) {
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
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    /*!
     Return information about this object. This method can translate
     methods to strings and vice versa, return the address of the
     object information structure.
     Example:
     @code
        // Return a method pointer for a string or NULL if not found. 
        void        *pMethod = Cmds_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_DATA, an object's data is returned
                        if it fits in a "void *".
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "Cmds", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          Cmds_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        CMDS_DATA     *this = objId;
        const
        char            *pStrA = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!Cmds_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(CMDS_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)Cmds_Class();
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
                            return Cmds_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStrA) == 0) {
                            return Cmds_Enable;
                        }
                        break;

                    case 'P':
#ifdef  CMDS_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStrA) == 0) {
                            return Cmds_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStrA) == 0) {
                            return Cmds_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStrA) == 0) {
                            return Cmds_ToDebugString;
                        }
#ifdef  CMDS_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStrA) == 0) {
                            return Cmds_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStrA) == 0) {
                            return Cmds_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == Cmds_ToDebugString)
                    return "ToDebugString";
#ifdef  CMDS_JSON_SUPPORT
                if (pData == Cmds_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                      S o r t
    //---------------------------------------------------------------

    /*!
     Sort the Node array for faster searching.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Cmds_Sort (
        CMDS_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  CMDS_SINGLETON
        if (OBJ_NIL == this) {
            this = Cmds_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Cmds_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        if (this->fSort) {
            eRc = NodeArray_SortAscending(this->pCmds);
            if (ERESULT_SUCCESSFUL(eRc))
                this->fSort = 0;
        }

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
        ASTR_DATA      *pDesc = Cmds_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     Cmds_ToDebugString (
        CMDS_DATA      *this,
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
        if (!Cmds_Validate(this)) {
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
                    Cmds_getSize(this),
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
        USE_VAR(eRc);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

#ifdef NDEBUG
#else
    bool            Cmds_Validate (
        CMDS_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_CMDS))
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


        if (!(obj_getSize(this) >= sizeof(CMDS_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef  __cplusplus
}
#endif


