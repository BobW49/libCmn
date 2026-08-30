// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   PrepStrW32.c
 *  Generated 04/23/2022 09:45:13
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
#include        <PrepStrW32_internal.h>
#include        <ascii.h>
#include        <AStr_internal.h>
#include        <JsonIn.h>
//#include        <Macros.h>
#include        <trace.h>
#include        <utf8.h>
#include        <W32Str.h>






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
    void            PrepStrW32_task_body (
        void            *pData
    )
    {
        //PREPSTRW32_DATA  *this = pData;
        TRC_OBJ(this, "%s:\n", __func__);
        
    }
#endif



    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    PREPSTRW32_DATA *     PrepStrW32_Alloc (
        void
    )
    {
        PREPSTRW32_DATA       *this;
        uint32_t        cbSize = sizeof(PREPSTRW32_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    PREPSTRW32_DATA *     PrepStrW32_New (
        void
    )
    {
        PREPSTRW32_DATA       *this;
        
        this = PrepStrW32_Alloc( );
        if (this) {
            this = PrepStrW32_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                    F i n d  V a l u e
    //---------------------------------------------------------------
    
    bool            PrepStrW32_setFindValue (
        PREPSTRW32_DATA *this,
        ASTR_DATA       *(*pFindValueA)(OBJ_ID, const char *),
        OBJ_ID          pObjFind
    )
    {
#ifdef NDEBUG
#else
        if (!PrepStrW32_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->pFindValueA = pFindValueA;
        this->pObjFind = pObjFind;

        return true;
    }



    //---------------------------------------------------------------
    //                      G r o u p  C h a r s
    //---------------------------------------------------------------
    
    W32CHR_T        PrepStrW32_getGrpCharE (
        PREPSTRW32_DATA *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!PrepStrW32_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->grpCharE;
    }


    bool            PrepStrW32_setGrpCharE (
        PREPSTRW32_DATA *this,
        W32CHR_T        value
    )
    {
#ifdef NDEBUG
#else
        if (!PrepStrW32_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->grpCharE = value;

        return true;
    }


    W32CHR_T        PrepStrW32_getGrpCharS (
        PREPSTRW32_DATA *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!PrepStrW32_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->grpCharS;
    }


    bool            PrepStrW32_setGrpCharS (
        PREPSTRW32_DATA *this,
        W32CHR_T        value
    )
    {
#ifdef NDEBUG
#else
        if (!PrepStrW32_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->grpCharS = value;

        return true;
    }



    //---------------------------------------------------------------
    //                      M e s s a g e s
    //---------------------------------------------------------------

#ifdef   PREPSTRW32_MSGS
    bool            PrepStrW32_setMsgs (
        PREPSTRW32_DATA    *this,
        void            (*pMsgInfo)(OBJ_ID, const char *, ...),
        void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...),
        OBJ_ID          pObj
    )
    {
#ifdef NDEBUG
#else
        if (!PrepStrW32_Validate(this)) {
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
    //                          P r e p  C h a r
    //---------------------------------------------------------------
    
    W32CHR_T        PrepStrW32_getPrepChar (
        PREPSTRW32_DATA *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!PrepStrW32_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->prepChar;
    }


    bool            PrepStrW32_setPrepChar (
        PREPSTRW32_DATA *this,
        W32CHR_T        value
    )
    {
#ifdef NDEBUG
#else
        if (!PrepStrW32_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->prepChar = value;

        return true;
    }



    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        PrepStrW32_getPriority (
        PREPSTRW32_DATA *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!PrepStrW32_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            PrepStrW32_setPriority (
        PREPSTRW32_DATA *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!PrepStrW32_Validate(this)) {
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
    
    uint32_t        PrepStrW32_getSize (
        PREPSTRW32_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!PrepStrW32_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA * PrepStrW32_getStr (
        PREPSTRW32_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!PrepStrW32_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStr;
    }
    
    
    bool        PrepStrW32_setStr (
        PREPSTRW32_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!PrepStrW32_Validate(this)) {
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
    
    SCANNER_DATA *  PrepStrW32_getSuper (
        PREPSTRW32_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!PrepStrW32_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return (SCANNER_DATA *)this;
    }

    
    OBJ_IUNKNOWN *  PrepStrW32_getSuperVtbl (
        PREPSTRW32_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!PrepStrW32_Validate(this)) {
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
        ERESULT eRc = PrepStrW32_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another PREPSTRW32 object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         PrepStrW32_Assign (
        PREPSTRW32_DATA       *this,
        PREPSTRW32_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!PrepStrW32_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!PrepStrW32_Validate(pOther)) {
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
    int             PrepStrW32_Compare (
        PREPSTRW32_DATA     *this,
        PREPSTRW32_DATA     *pOther
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
#ifdef  PREPSTRW32_SINGLETON
        if (OBJ_NIL == this) {
            this = PrepStrW32_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!PrepStrW32_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!PrepStrW32_Validate(pOther)) {
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
        PrepStrW32      *pCopy = PrepStrW32_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a PREPSTRW32 object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    PREPSTRW32_DATA *     PrepStrW32_Copy (
        PREPSTRW32_DATA       *this
    )
    {
        PREPSTRW32_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!PrepStrW32_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef PREPSTRW32_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = PrepStrW32_New( );
        if (pOther) {
            eRc = PrepStrW32_Assign(this, pOther);
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

    void            PrepStrW32_Dealloc (
        OBJ_ID          objId
    )
    {
        PREPSTRW32_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!PrepStrW32_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((PREPSTRW32_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        PrepStrW32_setStr(this, OBJ_NIL);

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
        PrepStrW32      *pDeepCopy = PrepStrW32_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a PREPSTRW32 object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    PREPSTRW32_DATA *     PrepStrW32_DeepCopy (
        PREPSTRW32_DATA       *this
    )
    {
        PREPSTRW32_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!PrepStrW32_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = PrepStrW32_New( );
        if (pOther) {
            eRc = PrepStrW32_Assign(this, pOther);
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
    ERESULT         PrepStrW32_Disable (
        PREPSTRW32_DATA *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  PREPSTRW32_SINGLETON
        if (OBJ_NIL == this) {
            this = PrepStrW32_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!PrepStrW32_Validate(this)) {
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
    ERESULT         PrepStrW32_Enable (
        PREPSTRW32_DATA *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  PREPSTRW32_SINGLETON
        if (OBJ_NIL == this) {
            this = PrepStrW32_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!PrepStrW32_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        TRC_OBJ(this,"\tEnabled?: %s:\n", obj_Enable(this) ? "true" : "false");
#ifdef   PREPSTRW32_MSGS
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
    //                  E x p a n d  V a r i a b l e s
    //---------------------------------------------------------------
    
    /*!
     Process the current string substituting the names which are
     prefixed with the prep char or prep_char '{' name '}' and sub-
     stituting the data found in the dictionary for the variable if
     found in the dictionary.
     @param     this    object pointer
     @param     pScan   Scanner object pointer
     @param     pOut    TextOut object pointer where text will be written
     @return    If successful, ERESULT_SUCCESS; otherwise, an ERESULT_*
                error.
     */
//#define USE_EXPAND_VARS_PREFIX 1
    ERESULT         PrepStrW32_ExpandVars (
        PREPSTRW32_DATA *this,
        SCANNER_DATA    *pScan,
        TEXTOUT_DATA    *pOut
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
#ifdef USE_EXPAND_VARS_PREFIX
#else
        bool            fMore = true;
        W32CHR_T        chr;
#endif

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!PrepStrW32_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pScan) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
       
        while (fMore && Scanner_IsMore(pScan)) {
            uint32_t        len = 0;
            const
            W32CHR_T        *pChrs;
            fMore = false;
            
            pChrs = Scanner_MatchUntilChrW32(pScan, this->prepChar, &len);
            if (pChrs && len) {
#ifdef NDEBUG
#else
                if (obj_Trace(this)) {
                    ASTR_DATA       *pStr = AStr_NewFromW32(len, pChrs);
                    if (pStr) {
                        fprintf(stderr, "\tOut: \"%s\"\n", AStr_getData(pStr));
                    }
                    obj_Release(pStr);
                }
#endif
                eRc = TextOut_PutStrW32(pOut, len, pChrs);
                if (ERESULT_FAILED(eRc)) {
                    DEBUG_BREAK();
                    return eRc;
                }
            }
            
            fRc = Scanner_MatchChrW32(pScan, this->prepChar);
            if (fRc) {
                TRC_OBJ(this, "\tMatched %lc at %d\n", this->prepChar, obj_getMisc(pScan));
                chr = Scanner_LookAhead(pScan, 1);
                if (this->grpCharS == chr) {
                    TRC_OBJ(this, "\tMatched '%lc' at %d\n", this->grpCharS, obj_getMisc(pScan));
                    Scanner_Advance(pScan, 1);      // Advance over '{'
                    pChrs = Scanner_MatchUntilChrW32(pScan, this->grpCharE, &len);
                    if (pChrs && len) {
#ifdef NDEBUG
#else
                        if (obj_Trace(this)) {
                            ASTR_DATA       *pStr = AStr_NewFromW32(len, pChrs);
                            if (pStr) {
                                fprintf(stderr, "\tFound: \"%s\"\n", AStr_getData(pStr));
                            }
                            obj_Release(pStr);
                        }
#endif
                        eRc = PrepStrW32_ExpandVar(this, len, pChrs, this->pFindValueA, this->pObjFind, pOut);
                        if (ERESULT_FAILED(eRc)) {
                            DEBUG_BREAK();
                            return eRc;
                        }
                        Scanner_Advance(pScan, 1);  // Advance over '}'
                        fMore = true;
                    } else {
                        break;
                    }
                } else {
                    TRC_OBJ(this, "\tNo match of '%lc'\n", this->grpCharS);
#ifdef NDEBUG
#else
                    if (obj_Trace(this)) {
                        fprintf(stderr, "\tOut: \"%lc\"\n", this->prepChar);
                    }
#endif
                    eRc = TextOut_PutW32(pOut, this->prepChar);
                    if (ERESULT_FAILED(eRc)) {
                        DEBUG_BREAK();
                        return eRc;
                    }
                    fMore = true;
                    continue;
                }
                
            }
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    ERESULT         PrepStrW32_ExpandVar (
        PREPSTRW32_DATA *this,
        uint32_t        len,
        const
        W32CHR_T        *pStrW32,
        ASTR_DATA *     (*pFindA)(OBJ_ID, const char *pName),
        OBJ_ID          pFindObj,
        TEXTOUT_DATA    *pOut
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        bool            fExpanded = false;
        bool            fReleaseEnvVar = false;
        uint32_t        num32 = 0;
        SCANNER_DATA    *pScan = OBJ_NIL;
        ASTR_DATA       *pName = OBJ_NIL;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if( !PrepStrW32_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        pScan = Scanner_NewFromW32(len, pStrW32);
        if (OBJ_NIL == pScan) {
            eRc = ERESULT_INTERNAL_ERROR;
            goto exit00;
        }
        //Scanner_setWS(pScan, false);        // Return white-space 
        //                                    // instead of skipping.
#ifdef NDEBUG
#else
        if (obj_Trace(this)) {
            obj_TraceSet(pScan, true);
        }
#endif
        TRC_OBJ(this, "\tInput: \"%ls\"\n", Scanner_getData(pScan));

        fRc = Scanner_MatchStrA(pScan, "col(");
        if (fRc) {
            fRc = Scanner_ScanUnsigned32(pScan, &num32);
            if (fRc) {
                eRc = TextOut_Col(pOut, num32);
                if (ERESULT_FAILED(eRc)) {
                    eRc = ERESULT_INTERNAL_ERROR;
                    goto exit00;
                }
            } else {
                //TODO: Handle syntax error!
                eRc = ERESULT_INVALID_SYNTAX;
                goto exit00;
            }
            fRc = Scanner_MatchChrW32(pScan, ')');
            if (!fRc) {
                //TODO: Handle syntax error!
                eRc = ERESULT_INVALID_SYNTAX;
                goto exit00;
            }
            fRc = Scanner_MatchChrW32(pScan, ';');
            if (!fRc) {
                //TODO: Handle syntax error!
                eRc = ERESULT_INVALID_SYNTAX;
                goto exit00;
            }
            fExpanded = true;
        }
        
        fRc = Scanner_MatchStrA(pScan, "spc(");
        if (fRc) {
            fRc = Scanner_ScanUnsigned32(pScan, &num32);
            if (fRc) {
                for (int i=0; i<num32; i++) {
                    eRc = TextOut_PutA(pOut, ' ');
                    if (ERESULT_FAILED(eRc)) {
                        eRc = ERESULT_INTERNAL_ERROR;
                        goto exit00;
                    }
                }
            } else {
                //TODO: Handle syntax error!
                eRc = ERESULT_INVALID_SYNTAX;
                goto exit00;
            }
            fRc = Scanner_MatchChrW32(pScan, ')');
            if (!fRc) {
                //TODO: Handle syntax error!
                eRc = ERESULT_INVALID_SYNTAX;
                goto exit00;
            }
            fRc = Scanner_MatchChrW32(pScan, ';');
            if (!fRc) {
                //TODO: Handle syntax error!
                eRc = ERESULT_INVALID_SYNTAX;
                goto exit00;
            }
            fExpanded = true;
        }
        
        pName = Scanner_ScanIdentifierToAStr(pScan);
        if (pName) {
            ASTR_DATA       *pEnvVar = OBJ_NIL;
            if (pFindA) {
                TRC_OBJ(this, "Find::Looking for (%p)  %s:\n", pName, AStr_getData(pName));
                pEnvVar = pFindA(pFindObj, AStr_getData(pName));
                if (pEnvVar) {
                    TRC_OBJ(this, "\tFound (%p) \"%s\":\n", pEnvVar, AStr_getData(pEnvVar));
                    //pEnvVar = OBJ_NIL;
                } else {
                    TRC_OBJ(this, "\tNot Found\n");
                }
            }
            if (OBJ_NIL == pEnvVar) {
                TRC_OBJ(this, "GetEnv (%p) %s:\n", pName, AStr_getData(pName));
                pEnvVar = AStr_NewA(getenv(AStr_getData(pName)));
                if (OBJ_NIL == pEnvVar) {
                    eRc = ERESULT_DATA_NOT_FOUND;
                    goto exit00;
                }
                TRC_OBJ(this, "\tFound (%p) \"%s\":\n", pEnvVar, AStr_getData(pEnvVar));
                fReleaseEnvVar = true;
            }
            if (pEnvVar) {
#ifdef NDEBUG
#else
                if (obj_Trace(this)) {
                    fprintf(stderr, "\tOut: \"%s\"\n", AStr_getData(pEnvVar));
                }
#endif
                // Handle modifiers.
                fRc = Scanner_MatchChrW32(pScan, '.');
                if (fRc) {
                    pName = Scanner_ScanIdentifierToAStr(pScan);
                    if (pName) {
                        if (0 == AStr_CompareA(pName, "lower()")) {
                            eRc = AStr_Lower(pEnvVar);
                            if (ERESULT_FAILED(eRc)) {
                                eRc = ERESULT_INTERNAL_ERROR;
                                goto exit00;
                            }
                            fRc = Scanner_MatchChrW32(pScan, ';');
                        } else if (0 == AStr_CompareA(pName, "upper()")) {
                            eRc = AStr_Upper(pEnvVar);
                            if (ERESULT_FAILED(eRc)) {
                                eRc = ERESULT_INTERNAL_ERROR;
                                goto exit00;
                            }
                            fRc = Scanner_MatchChrW32(pScan, ';');
                        } else {
                            // Invalid string modifier found (in pName).
                            eRc = ERESULT_INVALID_SYNTAX;
                            goto exit00;
                        }
                    } else {
                        // Found '.' but missing modifier function
                        eRc = ERESULT_INVALID_SYNTAX;
                        goto exit00;
                    }
                }
                eRc = TextOut_PutStrA(pOut, AStr_getData(pEnvVar));
                if (fReleaseEnvVar) {
                    TRC_OBJ(this, "\tReleasing (%p)\n", pEnvVar);
                    obj_Release(pEnvVar);
                    pEnvVar = OBJ_NIL;
                    fReleaseEnvVar = false;
                }
                if (ERESULT_FAILED(eRc)) {
                    eRc = ERESULT_INTERNAL_ERROR;
                    goto exit00;
                }
            }
            fExpanded = true;
        }
        
        if (!fExpanded) {
            eRc = ERESULT_DATA_NOT_FOUND;
        }
        
        // Return to caller.
    exit00:
        obj_Release(pName);
        obj_Release(pScan);
        return eRc;
    }
    
    


    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    PREPSTRW32_DATA *   PrepStrW32_Init (
        PREPSTRW32_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(PREPSTRW32_DATA);
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

        // If you use inheritance, remember to change the obj_ClassObj reference 
        // in the OBJ_INFO at the end of PrepStrW32_object.c
#ifdef PREPSTRW32_SUPER_DEFINED
        //this = (OBJ_ID)Scanner_Init((SCANNER_DATA *)this);   // Needed for Inheritance
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_PREPSTRW32);
#else
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_PREPSTRW32);
#endif
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&PrepStrW32_Vtbl);
#ifdef  PREPSTRW32_JSON_SUPPORT
        JsonIn_RegisterClass(PrepStrW32_Class());
#endif
       
        this->prepChar = '%';
        this->grpCharS = '{';
        this->grpCharE = '}';

        /*
        this->pArray = ObjArray_New( );
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        */

#ifdef NDEBUG
#else
        if (!PrepStrW32_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "PrepStrW32::sizeof(PREPSTRW32_DATA) = %lu\n", 
                sizeof(PREPSTRW32_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(PREPSTRW32_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                      I s  E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         PrepStrW32_IsEnabled (
        PREPSTRW32_DATA       *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  PREPSTRW32_SINGLETON
        if (OBJ_NIL == this) {
            this = PrepStrW32_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!PrepStrW32_Validate(this)) {
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
    //                     L i n e  O u t
    //---------------------------------------------------------------

    /*!
     Enable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         PrepStrW32_LineOut (
        PREPSTRW32_DATA *this,
        SCANNER_DATA    *pScan,
        TEXTOUT_DATA    *pOut
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        ASTR_DATA       *pStr = OBJ_NIL;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  PREPSTRW32_SINGLETON
        if (OBJ_NIL == this) {
            this = PrepStrW32_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!PrepStrW32_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pScan) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if (OBJ_NIL == pOut) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
            eRc = PrepStrW32_ExpandVars(this, pScan, pOut);
            if (ERESULT_FAILED(eRc)) {
#ifdef NDEBUG
#else
                if (obj_Trace(this)) {
                    ASTR_DATA       *pStr = Scanner_ToAStr(pScan);
                    if (pStr) {
                        fprintf(stderr, "\tScan: \"%s\"\n", AStr_getData(pStr));
                    }
                    obj_Release(pStr);
                }
#endif
                DEBUG_BREAK();
                return ERESULT_INVALID_SYNTAX;
            }
#ifdef NDEBUG
#else
            if (obj_Trace(this)) {
                if (pStr) {
                    fprintf(stderr, "\tOutput: \"%s\"\n", AStr_getData(TextOut_getStr(pOut)));
                }
            }
#endif

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                      N e x t  L i n e
    //---------------------------------------------------------------

    /*!
     Read the next line from the provided input.
     @param     this    object pointer
     @param     pInput  Text Input object pointer
     @return    if successful, a Scanner object with the new line.
                Otherwise, OBJ_NIL.
     */
    SCANNER_DATA *  PrepStrW32_NextLine (
        PREPSTRW32_DATA *this,
        TEXTIN_DATA     *pInput
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        ASTR_DATA       *pStr = OBJ_NIL;
        SRCLOC          loc;
        SCANNER_DATA    *pScan = OBJ_NIL;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  PREPSTRW32_SINGLETON
        if (OBJ_NIL == this) {
            this = PrepStrW32_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!PrepStrW32_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
#endif

        eRc = TextIn_GetLineAStr(pInput, &pStr, &loc);
        if (ERESULT_FAILED(eRc))
            return OBJ_NIL;
        AStr_AppendCharA(pStr, '\n');               // TextIn removes this.
        pScan = Scanner_NewA(AStr_getData(pStr));
        if (pScan) {
            Scanner_setSrcLoc(pScan, &loc);
        }
#ifdef NDEBUG
#else
        if (obj_Trace(this)) {
            ASTR_DATA       *pStr = Scanner_ToAStr(pScan);
            if (pStr) {
                fprintf(stderr, "\tLine:\"%s\"\n", AStr_getData(pStr));
                obj_Release(pStr);
            }
        }
#endif

        // Return to caller.
        obj_Release(pStr);
        return pScan;
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
        void        *pMethod = PrepStrW32_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "PrepStrW32", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          PrepStrW32_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        PREPSTRW32_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!PrepStrW32_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(PREPSTRW32_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)PrepStrW32_Class();
                break;
                              
            case OBJ_QUERYINFO_TYPE_DATA_PTR:
                switch (*pStr) {
     
                    case 'S':
                        if (str_Compare("SuperClass", (char *)pStr) == 0) {
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
                switch (*pStr) {
                        
                    case 'D':
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return PrepStrW32_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return PrepStrW32_Enable;
                        }
                        break;

                    case 'P':
#ifdef  PREPSTRW32_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return PrepStrW32_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return PrepStrW32_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return PrepStrW32_ToDebugString;
                        }
#ifdef  PREPSTRW32_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return PrepStrW32_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return PrepStrW32_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == PrepStrW32_ToDebugString)
                    return "ToDebugString";
#ifdef  PREPSTRW32_JSON_SUPPORT
                if (pData == PrepStrW32_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                     T e x t  P r e p r o c
    //---------------------------------------------------------------

    /*!
     Parse the given expression which is the argument of an %ifdef or %ifndef.
     Evaluate the text as a boolean expression.  Return true or false.
     @param     this    object pointer
     @param     pLine   Scanner object pointer which contains the expression
     @return    exprssion evaluates to a true (1+) or false (0). If the value
                returned is less than zero, it indicates an error occurred.
     */
    int             PrepStrW32_PreProcBoolEvalScan (
        PREPSTRW32_DATA *this,
        SCANNER_DATA    *pLine
    )
    {
        //ERESULT         eRc = ERESULT_SUCCESS;
        W32CHR_T        chr3;
        int             col      = 0;
        int             neg      = 0;
        int             res      = 0;
        int             okTerm   = 1;
        uint32_t        len      = Scanner_getSize(pLine);
        ASTR_DATA       *pName   = OBJ_NIL;

        // Do initialization.
        TRC_OBJ(this,"%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!PrepStrW32_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -1;
        }
        if (OBJ_NIL == pLine) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -1;
        }
#endif

        while (Scanner_IsMore(pLine)) {
            
            Scanner_ScanWS(pLine);
            if (!Scanner_IsMore(pLine))
                break;
            
            // !term
            if (Scanner_MatchChrW32(pLine, '!')) {
                if (!okTerm)
                    goto syntax_error;
                neg = !neg;
                continue;
            }
            
            // term || term
            if (Scanner_MatchStrA(pLine, "||")) {
                if (okTerm)
                    goto syntax_error;
                if (res)
                    return 1;
                okTerm = 1;
                continue;
            }
            
            // term && term
            if (Scanner_MatchStrA(pLine, "&&")) {
                if (okTerm)
                    goto syntax_error;
                if (!res)
                    return 0;
                okTerm = 1;
                continue;
            }
            
            // ( terms )
            if (Scanner_MatchChrW32(pLine, '(')) {
                int         k;
                int         nParens = 1;

                if (!okTerm) {
                    goto syntax_error;
                }

                Scanner_ScanWS(pLine);
                for (k=Scanner_getIndex(pLine); k<len; k++) {
                    chr3 = Scanner_LookAhead(pLine, k+1);
                    if (chr3 == ')') {
                        nParens--;
                        if (nParens == 0) {
                            W32CHR_T        *pStrW32;
                            SCANNER_DATA    *pScan= OBJ_NIL;
                            pStrW32 = (W32CHR_T *)(Scanner_getData(pLine) + Scanner_getIndex(pLine));
                            pScan = Scanner_NewFromW32((k), pStrW32);
                            res = PrepStrW32_PreProcBoolEvalScan(this, pScan);
                            obj_Release(pScan);
                            pScan = OBJ_NIL;
                            if (res < 0) {
                                col = col-res;
                                goto syntax_error;
                            }
                            col = k;
                            break;
                        }
                    } else if (chr3 == '(') {
                        nParens++;
                    } else if (chr3 == '\0') {     // End of Line
                        col = k;
                        goto syntax_error;
                    }
                }
                if (neg) {
                    res = !res;
                    neg = 0;
                }
                okTerm = 0;
                continue;
            }

            // term := (bool)found define_name
            if ((pName = Scanner_ScanIdentifierToAStr(pLine))) {
                ASTR_DATA       *pStrDef = OBJ_NIL;

                if (!okTerm) {
                    obj_Release(pName);
                    goto syntax_error;
                }
                
                // Search the defines to see if the one that we scanned exists.
                // Set res=1 if found
                res = 0;
                TRC_OBJ(this,"\tLooking for: %s\n", AStr_getData(pName));
                if (this->pFindValueA) {
                    pStrDef = this->pFindValueA(this->pObjFind, AStr_getData(pName));
                }
                obj_Release(pName);
                if (pStrDef) {
                    res = 1;
                    pStrDef = OBJ_NIL;
                }
                if (neg) {
                    res = !res;
                    neg = 0;
                }
                okTerm = 0;
                continue;

            }
            
            goto syntax_error;
        }

        // Return to caller.
        return res;
    syntax_error:
        if (Scanner_getSrcLoc(pLine)->lineNo > 0) {
            fprintf(stderr, "\"if | ifdef\" syntax error on line %d.\n", Scanner_getSrcLoc(pLine)->lineNo);
            fprintf(stderr, "  %.*ls <-- syntax error here\n", col+1, Scanner_getData(pLine));
            return(-1);
        } else {
            return -(col+1);
        }

    }


    ERESULT         PrepStrW32_PreprocInput (
        PREPSTRW32_DATA *this,
        TEXTIN_DATA     *pInput,
        TEXTOUT_DATA    *pOutput,
        uint32_t        *pCount
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        int             cDef = 0;           // Depth of "ifdef" and/or "ifndef"
        int             cSkip = 0;          // Skip source until "else" or "endif"
        uint32_t        count = 0;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  PREPSTRW32_SINGLETON
        if (OBJ_NIL == this) {
            this = PrepStrW32_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!PrepStrW32_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        for (;;) {
            SCANNER_DATA    *pScan = PrepStrW32_NextLine(this, pInput);
            //W32CHR_T        chr;
            if (OBJ_NIL == pScan) {
                break;
            }
            Scanner_setWS(pScan, false);
#ifdef NDEBUG
#else
            if (obj_Trace(this)) {
                obj_TraceSet(pScan, true);
            }
#endif

            Scanner_Save(pScan);
            fRc = Scanner_MatchChrW32(pScan, this->prepChar);
            if (fRc) {
                if (Scanner_MatchStrA(pScan, "endif") && Scanner_ScanWS(pScan)) {
                    TRC_OBJ(this, "\tFound \"endif\"  cSkip:%d\n", cSkip);
                    if (cSkip) {
                        cSkip--;
                    }
                    cDef--;
                    if (0 == cSkip) {
                        TRC_OBJ(this, "\t...Not within expansion now. cSkip:%d\n", cSkip);
                    } else {
                        TRC_OBJ(this, "\t...Still expanding now.  cSkip:%d\n", cSkip);
                    }
                } else if (Scanner_MatchStrA(pScan, "else") && Scanner_ScanWS(pScan)) {
                        TRC_OBJ(this, "\tFound \"else\"  cSkip:%d\n", cSkip);
                        if (0 == cSkip) {
                            cSkip++;
                        } else {
                            cSkip--;
                        }
                        if (0 == cSkip) {
                            TRC_OBJ(this, "\t...Not within expansion now.  cSkip:%d\n", cSkip);
                        } else {
                            TRC_OBJ(this, "\t...Expanding now.  cSkip:%d\n", cSkip);
                        }
                } else if (Scanner_MatchStrA(pScan, "ifdef")) {
                    TRC_OBJ(this, "\tFound \"ifdef\"  cSkip:%d\n", cSkip);
                    Scanner_ScanWS(pScan);
                    fRc = PrepStrW32_PreProcBoolEvalScan(this, pScan);
                    if (fRc) {
                        cSkip++;
                    }
                    cDef++;
                    if (0 == cSkip) {
                        TRC_OBJ(this, "\t...Not within expansion now.  cSkip:%d\n", cSkip);
                    } else {
                        TRC_OBJ(this, "\t...Expanding now.  cSkip:%d\n", cSkip);
                    }
                } else if (Scanner_MatchStrA(pScan, "ifndef")) {
                    TRC_OBJ(this, "\tFound \"ifndef\"  cSkip:%d\n", cSkip);
                    Scanner_ScanWS(pScan);
                    fRc = PrepStrW32_PreProcBoolEvalScan(this, pScan);
                    if (!fRc) {
                        cSkip++;
                    }
                    cDef++;
                    if (0 == cSkip) {
                        TRC_OBJ(this, "\t...Not within expansion now.  cSkip:%d\n", cSkip);
                    } else {
                        TRC_OBJ(this, "\t...Expanding now.  cSkip:%d\n", cSkip);
                    }
                } else {
                    Scanner_Restore(pScan);     // Back up to the prepChar.
                    TRC_OBJ(this, "\t...Prep char, %lc, is without command!\n", this->prepChar);
                    eRc = PrepStrW32_ExpandVars(this, pScan, pOutput);
                    if (ERESULT_FAILED(eRc)) {
                        //TODO: Error - Prep Char without command!
                        return ERESULT_INVALID_SYNTAX;
                    }
                    count++;
                }
            } else {
                if (cSkip || (0 == cDef)) {
                    eRc = PrepStrW32_LineOut(this, pScan, pOutput);
                    if (ERESULT_FAILED(eRc)) {
                        //TODO: Handle error!
                        return ERESULT_IO_ERROR;
                    }
                    count++;
                }
            }
            obj_Release(pScan);
        }
        if (cSkip) {
            TRC_OBJ(this, "ERROR - Unmatched ifdef or ifndef!\n");
            //TODO: Unmatched ifdef or ifndef!
            return ERESULT_INVALID_SYNTAX;
        }
        eRc = ERESULT_SUCCESS;
        
        // Return to caller.
        if (pCount)
            *pCount = count;
        return eRc;
    }



    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = PrepStrW32_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     PrepStrW32_ToDebugString (
        PREPSTRW32_DATA *this,
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
        if (!PrepStrW32_Validate(this)) {
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
                    PrepStrW32_getSize(this),
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
    //                      V a l i d a t e
    //---------------------------------------------------------------

#ifdef NDEBUG
#else
    bool            PrepStrW32_Validate (
        PREPSTRW32_DATA *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_PREPSTRW32))
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


        if (!(obj_getSize(this) >= sizeof(PREPSTRW32_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef  __cplusplus
}
#endif


