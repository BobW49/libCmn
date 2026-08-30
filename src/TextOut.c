// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//              Output UTF-8 Textual Data (TextOut) Object Support
//****************************************************************


/*
 * File:   TextOut.c
 *  Generated 08/03/2023 22:53:34
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
#include        <TextOut_internal.h>
#include        <ascii.h>
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

    ERESULT         TextOut_OutW32 (
        TEXTOUT_DATA    *this,
        const
        W32CHR_T        chr
    )
    {
        ERESULT         eRc;
        int             iRc;
        
        // Do initialization.
        
        if (('\n' == chr) || (0x0085 == chr)) {
            if (this->colMax && this->fExpandMax) {
                while (this->colNo < (this->colMax - 1)) {
                    eRc = TextOut_OutW32(this, this->fillChar);
                    this->colNo++;
                }
            }
            this->lineNo++;
            this->colNo = 0;
        } else {
            if (this->colMax && (this->colNo >= this->colMax)) {
                eRc = TextOut_OutW32(this, '\n');
                this->lineNo++;
                this->colNo = 0;
            }
        }
        
        switch (this->type) {

            case TEXTOUT_TYPE_ASTR:
                eRc = AStr_AppendCharW32(this->pStr, chr);
                break;

            case TEXTOUT_TYPE_FILE:
            case TEXTOUT_TYPE_FILE_CLOSE:
                if (chr < 128) {
                    iRc = putc(chr, this->pFile);
                }
                else {
                    iRc = putw(chr, this->pFile);
                }
                eRc = ERESULT_SUCCESS;
               if (iRc == EOF) {
                    eRc = ERESULT_WRITE_ERROR;
                }
                break;
                
            default:
                eRc = ERESULT_GENERAL_FAILURE;
                break;
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    TEXTOUT_DATA *     TextOut_Alloc (
        void
    )
    {
        TEXTOUT_DATA       *this;
        uint32_t        cbSize = sizeof(TEXTOUT_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    TEXTOUT_DATA *     TextOut_New (
        void
    )
    {
        TEXTOUT_DATA       *this;
        
        this = TextOut_Alloc( );
        if (this) {
            this = TextOut_Init(this);
        } 
        return this;
    }


    TEXTOUT_DATA *  TextOut_NewAStr (
        ASTR_DATA       *pStr
    )
    {
        TEXTOUT_DATA    *this;
        
        this = TextOut_Alloc( );
        if (this) {
            this = TextOut_Init(this);
            if (this) {
                if (pStr) {
                    TextOut_setStr(this, pStr);
                } else {
                    this->pStr = AStr_New();
                    this->type = TEXTOUT_TYPE_ASTR;
                }
           }
       }
        return this;
    }
    
    
    TEXTOUT_DATA *  TextOut_NewFromPath (
        PATH_DATA       *pPath
    )
    {
        TEXTOUT_DATA    *this;
        ERESULT         eRc = ERESULT_FAILURE;
        
        this = TextOut_Alloc( );
        if (this) {
            this = TextOut_Init(this);
            if (this) {
                //FIXME: eRc = TextOut_SetupPath(this, pPath);
                if (ERESULT_FAILED(eRc)) {
                    obj_Release(this);
                    this = OBJ_NIL;
                }
            }
        }
        return this;
    }
    
    

    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                  C o l u m n  N u m b e r
    //---------------------------------------------------------------
    
    uint16_t        TextOut_getColMax (
        TEXTOUT_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!TextOut_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->colMax;
    }


    bool            TextOut_setColMax (
        TEXTOUT_DATA    *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!TextOut_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->colMax = value;

        return true;
    }



    uint16_t        TextOut_getColNo (
        TEXTOUT_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!TextOut_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->colNo;
    }


    bool            TextOut_setColNo (
        TEXTOUT_DATA    *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!TextOut_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->colNo = value;

        return true;
    }



    //---------------------------------------------------------------
    //                     E x p a n d  M a x
    //---------------------------------------------------------------

    bool            TextOut_getMaxExpand (
        TEXTOUT_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!TextOut_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        return this->fExpandMax ? true : false;
    }


    bool            TextOut_setMaxExpand (
        TEXTOUT_DATA    *this,
        bool            fValue
    )
    {
#ifdef NDEBUG
#else
        if (!TextOut_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->fExpandMax = fValue ? 1 : 0;

        return true;
    }


    //---------------------------------------------------------------
    //                      M e s s a g e s
    //---------------------------------------------------------------

#ifdef   TEXTOUT_MSGS
    bool            TextOut_setMsgs (
        TEXTOUT_DATA    *this,
        void            (*pMsgInfo)(OBJ_ID, const char *, ...),
        void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...),
        OBJ_ID          pObj
    )
    {
#ifdef NDEBUG
#else
        if (!TextOut_Validate(this)) {
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
    
    uint16_t        TextOut_getPriority (
        TEXTOUT_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!TextOut_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            TextOut_setPriority (
        TEXTOUT_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!TextOut_Validate(this)) {
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
    
    uint32_t        TextOut_getSize (
        TEXTOUT_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!TextOut_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA *     TextOut_getStr (
        TEXTOUT_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!TextOut_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStr;
    }
    
    
    bool            TextOut_setStr (
        TEXTOUT_DATA    *this,
        ASTR_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!TextOut_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        switch (this->type) {
            case TEXTOUT_TYPE_FILE_CLOSE:
                fclose(this->pFile);
                break;
            case TEXTOUT_TYPE_U8ARRAY:
                obj_Release(this->pU8Array);
                break;
        }
        if (this->pStr) {
            obj_Release(this->pStr);
        }
        this->pStr = pValue;
        this->type = TEXTOUT_TYPE_ASTR;

        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
#ifdef  TEXTOUT_SUPER_DEFINED
    OBJ_DATA *  TextOut_getSuper (
        TEXTOUT_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!TextOut_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return (OBJ_DATA *)this;
    }
#else
    OBJ_DATA *  TextOut_getSuper (
        TEXTOUT_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!TextOut_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return (OBJ_DATA *)this;
    }
#endif

    
    OBJ_IUNKNOWN *  TextOut_getSuperVtbl (
        TEXTOUT_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!TextOut_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    //---------------------------------------------------------------
    //                          T a b
    //---------------------------------------------------------------
    
    bool            TextOut_getTabExpand (
        TEXTOUT_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!TextOut_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        return this->fExpandTabs ? true : false;
    }


    bool            TextOut_setTabExpand (
        TEXTOUT_DATA    *this,
        bool            fValue
    )
    {
#ifdef NDEBUG
#else
        if (!TextOut_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->fExpandTabs = fValue ? 1 : 0;

        return true;
    }


    uint16_t        TextOut_getTabSize (
        TEXTOUT_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!TextOut_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->tabSize;
    }


    bool            TextOut_setTabSize (
        TEXTOUT_DATA    *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!TextOut_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->tabSize = value;

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
        ERESULT eRc = TextOut_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another TEXTOUT object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         TextOut_Assign (
        TEXTOUT_DATA       *this,
        TEXTOUT_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!TextOut_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!TextOut_Validate(pOther)) {
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
    //                      C o l u m n
    //---------------------------------------------------------------

    /*!
     Output enough filler characters to get to the given column number.
     If we are already beyond that column number, go to the next line
     and again proceed to that column number.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         TextOut_Col (
        TEXTOUT_DATA    *this,
        uint16_t        col
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  TEXTOUT_SINGLETON
        if (OBJ_NIL == this) {
            this = TextOut_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!TextOut_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (this->colMax && (col >= this->colMax)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if ((0 == col)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        BREAK_ZERO(this->type);
        BREAK_NULL(this->pStr);
#endif
        col--;
        
        if (this->colNo > col) {
            TextOut_OutW32(this, '\n');
        }
        while (this->colNo < col) {
            TextOut_OutW32(this, this->fillChar);
            this->colNo++;
        }
        
        // Return to caller.
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
    int             TextOut_Compare (
        TEXTOUT_DATA     *this,
        TEXTOUT_DATA     *pOther
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
#ifdef  TEXTOUT_SINGLETON
        if (OBJ_NIL == this) {
            this = TextOut_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!TextOut_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!TextOut_Validate(pOther)) {
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
        TextOut      *pCopy = TextOut_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a TEXTOUT object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    TEXTOUT_DATA *     TextOut_Copy (
        TEXTOUT_DATA       *this
    )
    {
        TEXTOUT_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!TextOut_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef TEXTOUT_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = TextOut_New( );
        if (pOther) {
            eRc = TextOut_Assign(this, pOther);
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

    void            TextOut_Dealloc (
        OBJ_ID          objId
    )
    {
        TEXTOUT_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!TextOut_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((TEXTOUT_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        switch (this->type) {
            case TEXTOUT_TYPE_ASTR:
                obj_Release(this->pStr);
                break;
            case TEXTOUT_TYPE_FILE_CLOSE:
                fclose(this->pFile);
                break;
            case TEXTOUT_TYPE_U8ARRAY:
                obj_Release(this->pU8Array);
                break;
        }
        this->type = 0;
        this->pFile = NULL;

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
        TextOut      *pDeepCopy = TextOut_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a TEXTOUT object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    TEXTOUT_DATA *     TextOut_DeepCopy (
        TEXTOUT_DATA       *this
    )
    {
        TEXTOUT_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!TextOut_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = TextOut_New( );
        if (pOther) {
            eRc = TextOut_Assign(this, pOther);
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
    ERESULT         TextOut_Disable (
        TEXTOUT_DATA    *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  TEXTOUT_SINGLETON
        if (OBJ_NIL == this) {
            this = TextOut_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!TextOut_Validate(this)) {
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
    ERESULT         TextOut_Enable (
        TEXTOUT_DATA    *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  TEXTOUT_SINGLETON
        if (OBJ_NIL == this) {
            this = TextOut_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!TextOut_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        TRC_OBJ(this,"\tEnabled?: %s:\n", obj_Enable(this) ? "true" : "false");
#ifdef   TEXTOUT_MSGS
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

    TEXTOUT_DATA *   TextOut_Init (
        TEXTOUT_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(TEXTOUT_DATA);
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

#ifdef  TEXTOUT_SUPER_DEFINED
        this = (OBJ_ID)obj_Init((OBJ_DATA *)this);   // Needed for Inheritance
#else
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_TEXTOUT);
#endif
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&TextOut_Vtbl);
#ifdef  TEXTOUT_JSON_SUPPORT
        JsonIn_RegisterClass(TextOut_Class());
#endif
        
        this->fillChar = ' ';
        this->tabSize = 4;
        this->fExpandTabs = 1;
 
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
        if (!TextOut_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "TextOut::sizeof(TEXTOUT_DATA) = %lu\n", 
                sizeof(TEXTOUT_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(TEXTOUT_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                      I s  E n a b l e d
    //---------------------------------------------------------------
    
    bool                TextOut_IsEnabled (
        TEXTOUT_DATA       *this
    )
    {
        //ERESULT         eRc;
        bool            fRc = false;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  TEXTOUT_SINGLETON
        if (OBJ_NIL == this) {
            this = TextOut_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!TextOut_Validate(this)) {
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
    //                      I s  S t r i n g
    //---------------------------------------------------------------
    
    bool                TextOut_IsString (
        TEXTOUT_DATA       *this
    )
    {
        //ERESULT         eRc;
        bool            fRc = false;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  TEXTOUT_SINGLETON
        if (OBJ_NIL == this) {
            this = TextOut_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!TextOut_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return fRc;
        }
#endif
        
        if ((this->type == TEXTOUT_TYPE_ASTR) || (this->type == TEXTOUT_TYPE_U8ARRAY)) {
            fRc = true;
        }
        
        // Return to caller.
        return fRc;
    }
    
    
     //---------------------------------------------------------------
    //                          P r i n t
    //---------------------------------------------------------------
    
    ERESULT         TextOut_Print (
        TEXTOUT_DATA    *this,
        const
        char            *pFormat,
        ...
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        char            str[256];
        int             size;
        va_list         arg_ptr;
        char            *pStr = NULL;
        char            *pWrk = NULL;
        W32CHR_T        chr;
        int             len;
        bool            fAlloc = false;

        // Do Initialization.
#ifdef NDEBUG
#else
        if( !TextOut_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if ((NULL == pFormat)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        BREAK_ZERO(this->type);
        BREAK_NULL(this->pStr);
#endif
        
        va_start(arg_ptr, pFormat);
        str[0] = '\0';
        size = vsnprintf(str, sizeof(str), pFormat, arg_ptr);
        va_end(arg_ptr);
        if (size >= sizeof(str)) {
            ++size;
            pStr = (char *)mem_Malloc(size);
            if( pStr == NULL ) {
                return ERESULT_INSUFFICIENT_MEMORY;
            }
            va_start(arg_ptr, pFormat);
            size = vsnprintf(pStr, size, pFormat, arg_ptr);
            va_end( arg_ptr );
            pWrk = pStr;
            fAlloc = true;
        }
        else {
            pWrk = str;
        }
        if (pWrk) {
            while (*pWrk) {
                len = utf8_Utf8ToW32(pWrk, &chr);
                if (len < 0) {
                    eRc = ERESULT_DATA_ERROR;
                    break;
                }
                eRc = TextOut_PutW32(this, chr);
                if (ERESULT_FAILED(eRc)) {
                    break;
                }
                pWrk += len;
            }
        }
        if (fAlloc) {
            mem_Free(pStr);
            pStr = NULL;
        }

        return eRc;
    }
    
    

    //---------------------------------------------------------------
    //                          P u t
    //---------------------------------------------------------------
    
    ERESULT             TextOut_PutStrA(
        TEXTOUT_DATA        *this,
        const
        char                *pStrA
    )
    {
        ERESULT             eRc = ERESULT_INVALID_PARAMETER;
        W32CHR_T            chr;
        int                 len;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if(!TextOut_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if(NULL == pStrA) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        BREAK_ZERO(this->type);
        BREAK_NULL(this->pStr);
#endif
        
        while (*pStrA) {
            len = utf8_Utf8ToW32(pStrA, &chr);
            if (len < 0) {
                eRc = ERESULT_DATA_ERROR;
                break;
            }
            eRc = TextOut_PutW32(this, chr);
            if (ERESULT_FAILED(eRc)) {
                break;
            }
            pStrA += len;
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    ERESULT             TextOut_PutAStr(
        TEXTOUT_DATA        *this,
        ASTR_DATA           *pStr
    )
    {
        ERESULT             eRc = ERESULT_INVALID_PARAMETER;
        const
        char                *pStrA;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if(!TextOut_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if(OBJ_NIL == pStr) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        pStrA = AStr_getData(pStr);
        
        eRc = TextOut_PutStrA(this, pStrA);
        
        // Return to caller.
        return eRc;
    }
    
    
    
    ERESULT         TextOut_PutA (
        TEXTOUT_DATA    *this,
        const
        char            chr
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !TextOut_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        BREAK_ZERO(this->type);
        BREAK_NULL(this->pStr);
#endif
        
        eRc = TextOut_PutW32(this, chr);
        
        // Return to caller.
        return eRc;
    }
    

    
    ERESULT         TextOut_PutStrW32 (
        TEXTOUT_DATA    *this,
        uint32_t        len,
        const
        W32CHR_T        *pStrW32
    )
    {
        ERESULT             eRc = ERESULT_INVALID_PARAMETER;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if(!TextOut_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if(OBJ_NIL == pStrW32) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        if (0 == len) {
            len = utf8_StrLenW32(pStrW32);
        }
        while (*pStrW32 && len) {
            eRc = TextOut_PutW32(this, *pStrW32);
            if (ERESULT_FAILED(eRc))
                break;
            pStrW32++;
            len--;
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    
    ERESULT         TextOut_PutW32 (
        TEXTOUT_DATA    *this,
        const
        W32CHR_T        chr
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        //int             iRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !TextOut_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        BREAK_ZERO(this->type);
        BREAK_NULL(this->pStr);
#endif
        
        switch (chr) {
            case '\b':
                fprintf(stderr, "ERROR - Back-Space characters are illegal!\n\n");
                exit(99);
                break;
            case '\f':
                fprintf(stderr, "ERROR - Form-Feed characters are illegal!\n\n");
                exit(99);
                break;
            case '\n':
            case 0x0085:            // NEL - Next Line (same as ebcdic NL)
                eRc = TextOut_OutW32(this, '\n');
                break;
            case '\r':
                this->colNo = 0;
                break;
            case '\t':
                if (this->fExpandTabs) {
                    eRc = TextOut_OutW32(this, this->fillChar);
                    this->colNo++;
                    while (this->colNo % this->tabSize) {
                        eRc = TextOut_OutW32(this, this->fillChar);
                        this->colNo++;
                    }
                } else {
                    eRc = TextOut_OutW32(this, '\t');
                    this->colNo = (this->colNo + this->tabSize - 1) / this->tabSize;
                    this->colNo *= this->tabSize;
                }
                break;
            default:
                eRc = TextOut_OutW32(this, chr);
                this->colNo++;
                break;
        }
        
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
        void        *pMethod = TextOut_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_DATA, an object's data is returned
                        if it fits in a "void *".
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "TextOut", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          TextOut_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        TEXTOUT_DATA     *this = objId;
        const
        char            *pStrA = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!TextOut_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(TEXTOUT_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)TextOut_Class();
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
                            return TextOut_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStrA) == 0) {
                            return TextOut_Enable;
                        }
                        break;

                    case 'P':
#ifdef  TEXTOUT_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStrA) == 0) {
                            return TextOut_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStrA) == 0) {
                            return TextOut_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStrA) == 0) {
                            return TextOut_ToDebugString;
                        }
#ifdef  TEXTOUT_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStrA) == 0) {
                            return TextOut_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStrA) == 0) {
                            return TextOut_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == TextOut_ToDebugString)
                    return "ToDebugString";
#ifdef  TEXTOUT_JSON_SUPPORT
                if (pData == TextOut_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                       S p a c e
    //---------------------------------------------------------------
    
    ERESULT         TextOut_Space (
        TEXTOUT_DATA    *this,
        uint16_t        num
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        uint32_t        lineNo = this->lineNo;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !TextOut_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        BREAK_ZERO(this->type);
        BREAK_NULL(this->pStr);
#endif
        
        while (num && (lineNo == this->lineNo)) {
            eRc = TextOut_PutW32(this, this->fillChar);
            if (ERESULT_FAILED(eRc)) {
                break;
            }
            num--;
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
        ASTR_DATA      *pDesc = TextOut_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     TextOut_ToDebugString (
        TEXTOUT_DATA      *this,
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
        if (!TextOut_Validate(this)) {
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
                    TextOut_getSize(this),
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
    bool            TextOut_Validate (
        TEXTOUT_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_TEXTOUT))
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


        if (!(obj_getSize(this) >= sizeof(TEXTOUT_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
#ifdef  __cplusplus
}
#endif


