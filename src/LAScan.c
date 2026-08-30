// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//              Look-Ahead Scanner (LAScan) Object Support
//****************************************************************


/*
 * File:   LAScan.c
 *  Generated 02/26/2023 10:04:02
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
#include        <LAScan_internal.h>
#include        <ascii.h>
#include        <JsonIn.h>
#include        <Misc.h>
#include        <Syms.h>
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
    //               A c c u m u l a t e  S t r i n g
    //---------------------------------------------------------------
    
    bool            LAScan_AccumStr (
        LASCAN_DATA     *this,
        const
        W32CHR_T        wrk
    )
    {
        ERESULT         eRc;

        if (wrk) {
            int         len = utf8_W32ToUtf8(wrk, NULL);
            while ((this->cAccum + len) >= (this->maxAccum - 1)) {
                eRc =   Misc_ExpandArray(
                                       0,
                                       &this->maxAccum,
                                       (this->maxAccum + 64),
                                       sizeof(uint8_t),
                                       false,
                                       (void **)&this->pAccum
                        );
                if (ERESULT_FAILED(eRc)) {
                    return false;
                }
            }
            if (len && ((this->cAccum + len) < this->maxAccum)) {
                utf8_W32ToUtf8(ascii_toUpperW32(wrk), (char *)this->pAccum+this->cAccum);
                this->cAccum += len;
                this->pAccum[this->cAccum] = '\0';
            }
        }
        return true;
    }


#ifdef NDEBUG
#else
    int32_t         LAScan_InputLookAhead (
        LASCAN_DATA     *this,
        uint16_t        index
    )
    {
        int32_t         cls;

        cls = this->pInputLookAhead(this->pInputObj, index, &this->input);
        this->inputCls = cls;

        if (obj_Trace(this)) {
            ASTR_DATA      *pDesc = Token_FieldsToDebugString(&this->input, 4);
            if (pDesc) {
                fprintf(stderr, "\tLookAhead Fields:\n%s\n", AStr_getData(pDesc));
                obj_Release(pDesc);
            }
        }
        
        return cls;
    }
#endif


    int32_t         LAScan_InputAdvLook (
        LASCAN_DATA     *this,
        int             num                 // Number of tokens to advance
    )
    {
        int32_t         cls;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
        
        ADVANCE(num);       // Overlays LookAhead Token Fields
        cls = LOOKAHEAD(1);

        // Return to caller.
        return cls;
    }
    
    



    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    LASCAN_DATA *     LAScan_Alloc (
        void
    )
    {
        LASCAN_DATA       *this;
        uint32_t        cbSize = sizeof(LASCAN_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    LASCAN_DATA *     LAScan_New (
        void
    )
    {
        LASCAN_DATA       *this;
        
        this = LAScan_Alloc( );
        if (this) {
            this = LAScan_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                         A c c u m
    //---------------------------------------------------------------
    
    const
    uint8_t *       LAScan_getAccum (
        LASCAN_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!LAScan_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->pAccum;
    }



    //---------------------------------------------------------------
    //                      M e s s a g e s
    //---------------------------------------------------------------

#ifdef   LASCAN_MSGS
    bool            LAScan_setMsgs (
        LASCAN_DATA    *this,
        void            (*pMsgInfo)(OBJ_ID, const char *, ...),
        void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...),
        OBJ_ID          pObj
    )
    {
#ifdef NDEBUG
#else
        if (!LAScan_Validate(this)) {
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
    
    uint16_t        LAScan_getPriority (
        LASCAN_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!LAScan_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            LAScan_setPriority (
        LASCAN_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!LAScan_Validate(this)) {
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
    
    uint32_t        LAScan_getSize (
        LASCAN_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!LAScan_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA * LAScan_getStr (
        LASCAN_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!LAScan_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStr;
    }
    
    
    bool        LAScan_setStr (
        LASCAN_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!LAScan_Validate(this)) {
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
    
#ifdef  LASCAN_SUPER_DEFINED
    OBJ_DATA *  LAScan_getSuper (
        LASCAN_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!LAScan_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return (OBJ_DATA *)this;
    }
#else
    OBJ_DATA *  LAScan_getSuper (
        LASCAN_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!LAScan_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return (OBJ_DATA *)this;
    }
#endif

    
    OBJ_IUNKNOWN *  LAScan_getSuperVtbl (
        LASCAN_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!LAScan_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    //---------------------------------------------------------------
    //                     S c a n  W S
    //---------------------------------------------------------------

    bool            LAScan_getWS (
       LASCAN_DATA      *this
    )
    {
#ifdef NDEBUG
#else
        if (!LAScan_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->fWS ? true : false;
    }

    
    bool            LAScan_setWS(
        LASCAN_DATA     *this,
        bool            fValue
    )
    {
#ifdef NDEBUG
#else
        if( !LAScan_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->fWS = fValue ? 1 : 0;

        return true;
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
        ERESULT eRc = LAScan_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another LASCAN object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         LAScan_Assign (
        LASCAN_DATA       *this,
        LASCAN_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!LAScan_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!LAScan_Validate(pOther)) {
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
    int             LAScan_Compare (
        LASCAN_DATA     *this,
        LASCAN_DATA     *pOther
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
#ifdef  LASCAN_SINGLETON
        if (OBJ_NIL == this) {
            this = LAScan_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!LAScan_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!LAScan_Validate(pOther)) {
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
        LAScan      *pCopy = LAScan_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a LASCAN object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    LASCAN_DATA *     LAScan_Copy (
        LASCAN_DATA       *this
    )
    {
        LASCAN_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!LAScan_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef LASCAN_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = LAScan_New( );
        if (pOther) {
            eRc = LAScan_Assign(this, pOther);
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

    void            LAScan_Dealloc (
        OBJ_ID          objId
    )
    {
        LASCAN_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!LAScan_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((LASCAN_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        LAScan_setStr(this, OBJ_NIL);

        if (this->pAccum) {
            mem_Free(this->pAccum);
            this->pAccum = NULL;
            this->cAccum = 0;
        }

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
        LAScan      *pDeepCopy = LAScan_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a LASCAN object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    LASCAN_DATA *     LAScan_DeepCopy (
        LASCAN_DATA       *this
    )
    {
        LASCAN_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!LAScan_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = LAScan_New( );
        if (pOther) {
            eRc = LAScan_Assign(this, pOther);
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
    ERESULT         LAScan_Disable (
        LASCAN_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  LASCAN_SINGLETON
        if (OBJ_NIL == this) {
            this = LAScan_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!LAScan_Validate(this)) {
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
    ERESULT         LAScan_Enable (
        LASCAN_DATA     *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  LASCAN_SINGLETON
        if (OBJ_NIL == this) {
            this = LAScan_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!LAScan_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        TRC_OBJ(this,"\tEnabled?: %s:\n", obj_Enable(this) ? "true" : "false");
#ifdef   LASCAN_MSGS
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

    LASCAN_DATA *   LAScan_Init (
        LASCAN_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(LASCAN_DATA);
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

#ifdef  LASCAN_SUPER_DEFINED
        this = (OBJ_ID)obj_Init((OBJ_DATA *)this);   // Needed for Inheritance
#else
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_LASCAN);
#endif
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&LAScan_Vtbl);
#ifdef  LASCAN_JSON_SUPPORT
        JsonIn_RegisterClass(LAScan_Class());
#endif
        
        this->maxAccum = 256 * 4;           // Max case for 256 UTF-8 Chars
        this->cAccum = 0;
        this->pAccum = mem_Malloc(this->maxAccum * sizeof(uint8_t));
        if (NULL == this->pAccum) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

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
        if (!LAScan_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "LAScan::sizeof(LASCAN_DATA) = %lu\n", 
                sizeof(LASCAN_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(LASCAN_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                      I s  E n a b l e d
    //---------------------------------------------------------------
    
    bool                LAScan_IsEnabled (
        LASCAN_DATA       *this
    )
    {
        //ERESULT         eRc;
        bool            fRc = false;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  LASCAN_SINGLETON
        if (OBJ_NIL == this) {
            this = LAScan_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!LAScan_Validate(this)) {
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
    //                      I s  S e p a r a t o r
    //---------------------------------------------------------------
    
    bool                LAScan_IsSeparator (
        LASCAN_DATA         *this,
        bool                fTermWS
    )
    {
        //ERESULT         eRc;
        bool            fRc = false;
        W32CHR_T        chr;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  LASCAN_SINGLETON
        if (OBJ_NIL == this) {
            this = LAScan_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!LAScan_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return fRc;
        }
#endif
        
        chr = this->input.w32chr[0];
        if ((chr == '\0') || (',' == chr)) {
            fRc = true;
        } else if  (fTermWS && ascii_isWhiteSpaceW32(chr)) {
            fRc = true;
        }

        // Return to caller.
        return fRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                      L o o k  A h e a d
    //---------------------------------------------------------------

    int32_t         LAScan_LookAhead (
        LASCAN_DATA     *this,
        uint16_t        index,
        W32CHR_T        *pChr
    )
    {
        //ERESULT         eRc = ERESULT_SUCCESS;
        int32_t         cls;
        TOKEN_FIELDS    fields;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  LASCAN_SINGLETON
        if (OBJ_NIL == this) {
            this = LAScan_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!LAScan_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -1;
        }
        if ((index < 1) || (index > 4)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -1;
        }
#endif
        
        cls = this->pInputLookAhead(this->pInputObj, index, &fields);
        if (pChr) {
            *pChr = fields.w32chr[0];
        }
        
        // Return to caller.
        return cls;
    }



    //---------------------------------------------------------------
    //                          M a t c h
    //---------------------------------------------------------------

    bool            LAScan_MatchChrW32(
        LASCAN_DATA     *this,
        W32CHR_T        chr
    )
    {
        bool            fMatch = false;
        W32CHR_T        chr2;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!LAScan_Validate(this)) {
            DEBUG_BREAK();
            // return ERESULT_INVALID_OBJECT;
            return fMatch;
        }
#endif

        // Scan off leading white-space.
        if (this->fWS) {
            LAScan_SkipWS(this);
        }

        chr2 = this->input.w32chr[0];
        if (chr2 == chr) {
            this->inputBeginLoc = this->input.src;
            fMatch = true;
            ADVLOOK(1);
        }

        return fMatch;
    }


    bool            LAScan_MatchChrsW32(
        LASCAN_DATA     *this,
        W32CHR_T        *pChrs
    )
    {
        bool            fMatch = false;
        W32CHR_T        chr;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!LAScan_Validate(this)) {
            DEBUG_BREAK();
            // return ERESULT_INVALID_OBJECT;
            return 0;
        }
#endif

        // Scan off leading white-space.
        if (this->fWS) {
            LAScan_SkipWS(this);
        }

        chr = this->input.w32chr[0];
        while (!fMatch && *pChrs) {
            if (chr == *pChrs) {
                this->inputBeginLoc = this->input.src;
                fMatch = true;
                ADVLOOK(1);
                break;
            }
            pChrs++;
        }

        return fMatch;
    }


    bool            LAScan_MatchClass (
        LASCAN_DATA     *this,
        int32_t         cls
    )
    {
        bool            fMatch = false;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!LAScan_Validate(this)) {
            DEBUG_BREAK();
            // return ERESULT_INVALID_OBJECT;
            return fMatch;
        }
#endif

        // Scan off leading white-space.
        if (this->fWS) {
            LAScan_SkipWS(this);
        }

        if (cls == this->input.cls) {
            this->inputBeginLoc = this->input.src;
            fMatch = true;
            ADVLOOK(1);
        }

        return fMatch;
    }


    bool            LAScan_MatchClasses (
        LASCAN_DATA     *this,
        int32_t         *pClasses
    )
    {
        bool            fMatch = false;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!LAScan_Validate(this)) {
            DEBUG_BREAK();
            // return ERESULT_INVALID_OBJECT;
            return fMatch;
        }
#endif

        // Scan off leading white-space.
        if (this->fWS) {
            LAScan_SkipWS(this);
        }

        while (!fMatch && *pClasses) {
            if (this->input.cls == *pClasses) {
                this->inputBeginLoc = this->input.src;
                fMatch = true;
                ADVLOOK(1);
                break;
            }
            pClasses++;
        }

        return fMatch;
    }


    int             LAScan_MatchHex(
        LASCAN_DATA     *this
    )
    {
        //bool            fMatch = false;
        int             digit = -1;
        W32CHR_T        chr;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!LAScan_Validate(this)) {
            DEBUG_BREAK();
            // return ERESULT_INVALID_OBJECT;
            return digit;
        }
#endif

        // Scan off leading white-space.
        if (this->fWS) {
            LAScan_SkipWS(this);
        }

        chr = this->input.w32chr[0];
        if (ascii_isHexW32(chr)) {
            this->inputBeginLoc = this->input.src;
            digit = chr;
            ADVLOOK(1);
        }

        return digit;
    }


    bool             LAScan_MatchWS (
        LASCAN_DATA     *this
    )
    {
        bool            fMatch = false;
        W32CHR_T        chr;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!LAScan_Validate(this)) {
            DEBUG_BREAK();
            // return ERESULT_INVALID_OBJECT;
            return fMatch;
        }
#endif

        chr = this->input.w32chr[0];
        if (chr && ascii_isWhiteSpaceW32(chr)) {
            this->inputBeginLoc = this->input.src;
            fMatch = true;
            ADVLOOK(1);
        }

        return fMatch;
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
        void        *pMethod = LAScan_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_DATA, an object's data is returned
                        if it fits in a "void *".
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "LAScan", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          LAScan_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        LASCAN_DATA     *this = objId;
        const
        char            *pStrA = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!LAScan_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(LASCAN_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)LAScan_Class();
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
                            return LAScan_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStrA) == 0) {
                            return LAScan_Enable;
                        }
                        break;

                    case 'P':
#ifdef  LASCAN_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStrA) == 0) {
                            return LAScan_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStrA) == 0) {
                            return LAScan_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStrA) == 0) {
                            return LAScan_ToDebugString;
                        }
#ifdef  LASCAN_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStrA) == 0) {
                            return LAScan_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStrA) == 0) {
                            return LAScan_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == LAScan_ToDebugString)
                    return "ToDebugString";
#ifdef  LASCAN_JSON_SUPPORT
                if (pData == LAScan_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                    S c a n  A s m  S y m b o l
    //---------------------------------------------------------------

    bool            LAScan_ScanAsmIbmSymbol (
        LASCAN_DATA     *this,
        const
        uint8_t         **ppStrA
    )
    {
        bool            fRc = false;
        //ASTR_DATA       *pStr = OBJ_NIL;
        SYM_DATA        *pSym = OBJ_NIL;
        W32CHR_T        chr;
        W32CHR_T        chr2;
        uint32_t        len = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !LAScan_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->cAccum = 0;
        this->pAccum[0] = '\0';

        // Scan off leading white-space.
        if (this->fWS) {
            LAScan_SkipWS(this);
        }

        // Scan the paramter.
        chr = this->input.w32chr[0];
        if (chr) {
            if (
                (ASCII_LEXICAL_ALPHA_LOWER == this->input.cls)
                || (ASCII_LEXICAL_ALPHA_UPPER == this->input.cls)
                || ('$' == chr) || ('#' == chr)
                || ('@' == chr) || ('_' == chr)
            ) {
                LAScan_AccumStr(this, chr);
                ADVLOOK(1);
                fRc = true;
                chr2 = this->input.w32chr[0];
                if ('\'' == chr2) {
                    switch (chr) {
                        case 'i':                       // Integer
                        case 'I':
                            ADVLOOK(2);
                            //FIXME: pSym = Syms_FindA(AsmCmn_getCmn(this->pCmn)->pGlobals, 0, "I'");
                            return pSym;
                            break;
                        case 'k':                       // Count
                        case 'K':
                            ADVLOOK(2);
                            //FIXME: pSym = Syms_FindA(AsmCmn_getCmn(this->pCmn)->pGlobals, 0, "I'");
                            return pSym;
                            break;
                        case 'l':                       // Length
                        case 'L':
                            ADVLOOK(2);
                            //FIXME: pSym = Syms_FindA(AsmCmn_getCmn(this->pCmn)->pGlobals, 0, "L'");
                            return pSym;
                            break;
                        case 'n':                       // Number
                        case 'N':
                            ADVLOOK(2);
                            //FIXME: pSym = Syms_FindA(AsmCmn_getCmn(this->pCmn)->pGlobals, 0, "N'");
                            return pSym;
                            break;
                        case 's':                       // Scaling
                        case 'S':
                            ADVLOOK(2);
                            //FIXME: pSym = Syms_FindA(AsmCmn_getCmn(this->pCmn)->pGlobals, 0, "S'");
                            return pSym;
                            break;
                        case 't':                       // Type
                        case 'T':
                            ADVLOOK(2);
                            //FIXME: pSym = Syms_FindA(AsmCmn_getCmn(this->pCmn)->pGlobals, 0, "T'");
                            return pSym;
                            break;
                        default:
                            //FIXME: TRC_OBJ(this, "ERROR - Invalid Attribute - %c\n", wrk2);
                            DEBUG_BREAK();
                    }
                }
                for (;;) {
                    chr = this->input.w32chr[0];
                    if (
                        (ASCII_LEXICAL_ALPHA_LOWER == this->input.cls)
                        || (ASCII_LEXICAL_ALPHA_UPPER == this->input.cls)
                        || (ASCII_LEXICAL_NUMBER == this->input.cls)
                        || ('$' == chr) || ('#' == chr)
                        || ('@' == chr) || ('_' == chr)
                    ) {
                        LAScan_AccumStr(this, chr);
                        ADVLOOK(1);
                        len += 1;
                        fRc = true;
                    } else {
                        break;
                    }
                }
            }
        }

        // Return to caller.
        if (ppStrA) {
            *ppStrA = this->pAccum;
        }
        return fRc;
    }


    bool            LAScan_ScanAsmIbmSymbolSeq (
        LASCAN_DATA     *this,
        const
        uint8_t         **ppStrA
    )
    {
        bool            fRc = false;
        //ASTR_DATA       *pStr = OBJ_NIL;
        W32CHR_T        chr;
        uint32_t        len = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !LAScan_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->cAccum = 0;
        this->pAccum[0] = '\0';

        // Scan off leading white-space.
        if (this->fWS) {
            LAScan_SkipWS(this);
        }

        // Scan the paramter.
        chr = this->input.w32chr[0];
        if (chr) {
            if ('.' == chr) {
                LAScan_AccumStr(this, chr);
                ADVLOOK(1);
                fRc = true;
                for (;;) {
                    chr = this->input.w32chr[0];
                    if (
                        (ASCII_LEXICAL_ALPHA_LOWER == this->input.cls)
                        || (ASCII_LEXICAL_ALPHA_UPPER == this->input.cls)
                        || (ASCII_LEXICAL_NUMBER == this->input.cls)
                        || ('$' == chr) || ('#' == chr)
                        || ('@' == chr) || ('_' == chr)
                    ) {
                        LAScan_AccumStr(this, chr);
                        ADVLOOK(1);
                        len += 1;
                        fRc = true;
                    } else {
                        break;
                    }
                }
            }
        }

        // Return to caller.
        if (ppStrA) {
            *ppStrA = this->pAccum;
        }
        return fRc;
    }


    bool            LAScan_ScanAsmIbmSymbolSet (
        LASCAN_DATA     *this,
        const
        uint8_t         **ppStrA
    )
    {
        bool            fRc = false;
        //ASTR_DATA       *pStr = OBJ_NIL;
        W32CHR_T        chr;
        uint32_t        len = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !LAScan_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->cAccum = 0;
        this->pAccum[0] = '\0';

        // Scan off leading white-space.
        if (this->fWS) {
            LAScan_SkipWS(this);
        }

        // Scan the paramter.
        chr = this->input.w32chr[0];
        if (chr) {
            if ('&' == chr) {
                LAScan_AccumStr(this, chr);
                ADVLOOK(1);
                fRc = true;
                for (;;) {
                    chr = this->input.w32chr[0];
                    if (
                        (ASCII_LEXICAL_ALPHA_LOWER == this->input.cls)
                        || (ASCII_LEXICAL_ALPHA_UPPER == this->input.cls)
                        || (ASCII_LEXICAL_NUMBER == this->input.cls)
                        || ('$' == chr) || ('#' == chr)
                        || ('@' == chr) || ('_' == chr)
                    ) {
                        LAScan_AccumStr(this, chr);
                        ADVLOOK(1);
                        len += 1;
                        fRc = true;
                    } else {
                        break;
                    }
                }
            }
        }

        // Return to caller.
        if (ppStrA) {
            *ppStrA = this->pAccum;
        }
        return fRc;
    }



    //---------------------------------------------------------------
    //                    S c a n  C  I n t e g e r 3 2
    //---------------------------------------------------------------

    bool            LAScan_ScanCInteger32(
        LASCAN_DATA     *this,
        int32_t         *pValue             // (returned) Scanned Number
    )
    {
        bool            fRc = false;
        int32_t         value = 0;
        W32CHR_T        chr;
        //W32CHR_T        chr2;
        uint32_t        len = 0;
        bool            fNegative = false;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !LAScan_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        // Scan off leading white-space.
        if (this->fWS) {
            LAScan_SkipWS(this);
        }

        
        chr = this->input.w32chr[0];
        if( '-' == chr ) {
            fNegative = true;
            len += 1;
            ADVLOOK(1);
        }
        else if( '+' == chr ) {
            len += 1;
            ADVLOOK(1);
        }
        chr = this->input.w32chr[0];
        if ('0' == chr) {
            LOOKAHEAD(2);
            chr = this->input.w32chr[0];
            if (('x' == chr) || ('X' == chr)) { // *** Hex ***
                ADVLOOK(2);
                for (;;) {
                    chr = this->input.w32chr[0];
                    if (ascii_isHexW32(chr)) {
                        value <<= 4;
                        value |= ascii_FromHexW32(chr);
                        ADVLOOK(1);
                        fRc = true;
                    } else {
                        break;
                    }
                }
                goto Exit;
            } else {                            // *** OCTAL ***
                ADVLOOK(1);
                for (;;) {
                    chr = this->input.w32chr[0];
                    if( ('0' <= chr) && ('7' >= chr) ) {
                        value = (value << 3) + (chr - '0');
                        len += 1;
                        ADVLOOK(1);
                    } else {
                        break;
                    }
                }
                fRc = true;
                goto Exit;
            }
        } else {                                // *** Decimal ***
            for (;;) {
                chr = this->input.w32chr[0];
                if( ('0' <= chr) && ('9' >= chr) ) {
                    value = (value << 3) + (value << 1) + (chr - '0');
                    len += 1;
                    fRc = true;
                }
                else
                    break;
                ADVLOOK(1);
            }
        }
        if (fNegative) {
            value = -value;
        }
        

        // Return to caller.
    Exit:
        if(pValue) {
            *pValue = value;
        }
        return fRc;
    }



    //---------------------------------------------------------------
    //                      C S t r i n g
    //---------------------------------------------------------------

    /*!
     Enable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         LAScan_ScanCStr (
        LASCAN_DATA     *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc = false;
        W32CHR_T        Quote = 0;
        //ASTR_DATA       *pStr = OBJ_NIL;
        W32CHR_T        chr;
        W32CHR_T        chr2;
        W32CHR_T        chr3;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  LASCAN_SINGLETON
        if (OBJ_NIL == this) {
            this = LAScan_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!LAScan_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        TRC_OBJ(this,"\tEnabled?: %s:\n", obj_Enable(this) ? "true" : "false");
#ifdef   LASCAN_MSGS
        if (this->pMsgInfo) {
            this->pMsgInfo(this->pMsgObj, "Enabling object!\n");
        }
#endif

        // Scan off leading white-space.
        if (this->fWS) {
            LAScan_SkipWS(this);
        }

        // Scan the paramter.
        this->cAccum = 0;
        this->inputBeginLoc = this->input.src;
        chr = this->input.w32chr[0];
        // Handle Quoted Arguments.
        if( ('"' == chr) || ('\'' == chr) ) {
            Quote = chr;
            ADVLOOK(1);
            for (;;) {
                chr = this->input.w32chr[0];
                if (chr == '\0') {
                    // ERROR - End of String in middle of quoted string
                    fRc = false;
                    break;
                }
                if (chr == Quote) {
                    ADVLOOK(1);
                    chr = this->input.w32chr[0];
                    if (chr == Quote) {
                        LAScan_AccumStr(this, chr);
                        ADVLOOK(1);
                        chr = this->input.w32chr[0];
                        fRc = true;
                    } else {
                        break;
                    }
                }
                else if (chr == '\\') {
                    ADVLOOK(1);
                    chr = this->input.w32chr[0];
                    if (chr == Quote) {
                    } else if (chr == '\\') {
                        LAScan_AccumStr(this, '\\');
                        fRc = true;
                        continue;
                    } else if( chr == '0' ) {
                        LAScan_AccumStr(this, '\0');
                        fRc = true;
                    } else if( chr == 'b' ) {
                        LAScan_AccumStr(this, '\b');
                        fRc = true;
                        continue;
                    } else if( chr == 'f' ) {
                        LAScan_AccumStr(this, '\f');
                        fRc = true;
                        continue;
                    } else if( chr == 'n' ) {
                        LAScan_AccumStr(this, '\n');
                        fRc = true;
                        continue;
                    } else if( chr == 'r' ) {
                        LAScan_AccumStr(this, '\r');
                        fRc = true;
                        continue;
                    } else if( chr == 't' ) {
                        LAScan_AccumStr(this, '\t');
                        fRc = true;
                        continue;
                    } else if( chr == 'x' ) {
                        // At this point, we need two more characters of
                        // 0..9,a..f,A..F to give us our hex character.
                        LOOKAHEAD(1);
                        chr = this->input.w32chr[0];
                        LOOKAHEAD(2);
                        chr2 = this->input.w32chr[0];
                        if (('\0' == chr) || ('\0' == chr2)) {
                            // ERROR - End of String in middle of quoted string
                            break;
                        }
                        if (ascii_isHexW32(chr) && ascii_isHexW32(chr2)) {
                            chr3 = ascii_FromHexW32(chr);
                            chr3 <<= 4;
                            chr3 |= ascii_FromHexW32(chr2);
                            LAScan_AccumStr(this, chr3);
                            ADVLOOK(2);
                            fRc = true;
                        } else {
                            // ERROR - Invalid escaped character
                            fRc = false;
                            break;
                        }
                        continue;
                    }
                } else {
                    LAScan_AccumStr(this, chr);
                    fRc = true;
                }
            }       // for
        }
            
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                    S c a n  C  S y m b o l
    //---------------------------------------------------------------

    bool            LAScan_ScanCSymbol (
        LASCAN_DATA     *this,
        const
        uint8_t         **ppStrA
    )
    {
        bool            fRc = false;
        //ASTR_DATA       *pStr = OBJ_NIL;
        W32CHR_T        chr;
        uint32_t        len = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !LAScan_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->cAccum = 0;
        this->pAccum[0] = '\0';

        // Scan off leading white-space.
        if (this->fWS) {
            LAScan_SkipWS(this);
        }

        // Scan the paramter.
        chr = this->input.w32chr[0];
        if (chr) {
            if (ascii_isAlphaW32(chr) || ('_' == chr)) {
                LAScan_AccumStr(this, chr);
                ADVLOOK(1);
                fRc = true;
                for (;;) {
                    chr = this->input.w32chr[0];
                    if (ascii_isAlphanumericW32(chr) || ('_' == chr)) {
                        LAScan_AccumStr(this, chr);
                        ADVLOOK(1);
                        len += 1;
                        fRc = true;
                    } else {
                        break;
                    }
                }
            }
        }

        // Return to caller.
        if (ppStrA) {
            *ppStrA = this->pAccum;
        }
        return fRc;
    }



    //---------------------------------------------------------------
    //                    S c a n  C  U n s i g n e d 3 2
    //---------------------------------------------------------------

    bool            LAScan_ScanCUnsigned32(
        LASCAN_DATA     *this,
        uint32_t        *pValue             // (returned) Scanned Number
    )
    {
        bool            fRc = false;
        uint32_t        value = 0;
        W32CHR_T        chr;
        //W32CHR_T        chr2;
        uint32_t        len = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !LAScan_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        // Scan off leading white-space.
        if (this->fWS) {
            LAScan_SkipWS(this);
        }
        
        chr = this->input.w32chr[0];
        if ('0' == chr) {
            LOOKAHEAD(2);
            chr = this->input.w32chr[0];
            if (('x' == chr) || ('X' == chr)) { // *** Hex ***
                ADVLOOK(2);
                for (;;) {
                    chr = this->input.w32chr[0];
                    if (ascii_isHexW32(chr)) {
                        value <<= 4;
                        value |= ascii_FromHexW32(chr);
                        ADVLOOK(1);
                        fRc = true;
                    } else {
                        break;
                    }
                }
                goto Exit;
            } else {                            // *** OCTAL ***
                ADVLOOK(1);
                for (;;) {
                    chr = this->input.w32chr[0];
                    if( ('0' <= chr) && ('7' >= chr) ) {
                        value = (value << 3) + (chr - '0');
                        len += 1;
                        ADVLOOK(1);
                    } else {
                        break;
                    }
                }
                fRc = true;
                goto Exit;
            }
        } else {                                // *** Decimal ***
            for (;;) {
                chr = this->input.w32chr[0];
                if( ('0' <= chr) && ('9' >= chr) ) {
                    value = (value << 3) + (value << 1) + (chr - '0');
                    len += 1;
                    fRc = true;
                }
                else
                    break;
                ADVLOOK(1);
            }
        }

        // Return to caller.
    Exit:
        if(pValue) {
            *pValue = value;
        }
        return fRc;
    }



    //---------------------------------------------------------------
    //                    S c a n  W h i t e  S p a c e
    //---------------------------------------------------------------

    bool            LAScan_SkipWS (
        LASCAN_DATA     *this
    )
    {
        W32CHR_T        chr;
        //int32_t         cls;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !LAScan_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        // Scan off leading white-space.
        for (;;) {
            chr = this->input.w32chr[0];
            if (chr && ascii_isWhiteSpaceW32(chr)) {
            } else {
                break;
            }
            ADVLOOK(1);
        }

        // Return to caller.
        return true;
    }



    //---------------------------------------------------------------
    //                          S e t u p
    //---------------------------------------------------------------

    ERESULT         LAScan_Setup (
        LASCAN_DATA     *this,
        int32_t         (*pInputAdvance)(OBJ_ID, uint16_t, TOKEN_FIELDS *),
        int32_t         (*pInputLookAhead)(OBJ_ID, uint16_t, TOKEN_FIELDS *),
        OBJ_ID          pInputObj
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!LAScan_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        this->pInputAdvance = pInputAdvance;
        this->pInputLookAhead = pInputLookAhead;
        this->pInputObj = pInputObj;
        LOOKAHEAD(1);

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
        ASTR_DATA      *pDesc = LAScan_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     LAScan_ToDebugString (
        LASCAN_DATA      *this,
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
        if (!LAScan_Validate(this)) {
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
                    LAScan_getSize(this),
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
    bool            LAScan_Validate (
        LASCAN_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_LASCAN))
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


        if (!(obj_getSize(this) >= sizeof(LASCAN_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef  __cplusplus
}
#endif


