// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//              File Input - Line at a time (LineIn) Object Support
//****************************************************************


/*
 * File:    LineIn.c
 *  Generated 03/31/2023 08:27:53
 *
 * Todo:
 *          Finish Seek()
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
#include        <LineIn_internal.h>
#include        <ascii.h>
#include        <JsonIn.h>
#include        <Misc.h>
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
    //                        LineIn_AccumChar
    //---------------------------------------------------------------
    


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    LINEIN_DATA *     LineIn_Alloc (
        void
    )
    {
        LINEIN_DATA       *this;
        uint32_t        cbSize = sizeof(LINEIN_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    LINEIN_DATA *     LineIn_New (
        void
    )
    {
        LINEIN_DATA       *this;
        
        this = LineIn_Alloc( );
        if (this) {
            this = LineIn_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          L o c a t i o n
    //---------------------------------------------------------------
    
    SRCLOC *        LineIn_getLoc (
        LINEIN_DATA     *this
    )
    {
#ifdef NDEBUG
#else
        if (!LineIn_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return &this->loc;
    }



    //---------------------------------------------------------------
    //                      M e s s a g e s
    //---------------------------------------------------------------

#ifdef   LINEIN_MSGS
    bool            LineIn_setMsgs (
        LINEIN_DATA    *this,
        void            (*pMsgInfo)(OBJ_ID, const char *, ...),
        void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...),
        OBJ_ID          pObj
    )
    {
#ifdef NDEBUG
#else
        if (!LineIn_Validate(this)) {
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
    //                         O f f s e t
    //---------------------------------------------------------------
    
    uint32_t        LineIn_getOffset (
        LINEIN_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!LineIn_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->iBuffer;
    }



    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        LineIn_getPriority (
        LINEIN_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!LineIn_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            LineIn_setPriority (
        LINEIN_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!LineIn_Validate(this)) {
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
    
    uint32_t        LineIn_getSize (
        LINEIN_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!LineIn_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                         I n d e x
    //---------------------------------------------------------------
    
    LINEINDEX_DATA * LineIn_getIndex (
        LINEIN_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!LineIn_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pIndex;
    }
    
    
    bool            LineIn_setIndex (
        LINEIN_DATA     *this,
        LINEINDEX_DATA  *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!LineIn_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pIndex) {
            obj_Release(this->pIndex);
        }
        this->pIndex = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
#ifdef  LINEIN_SUPER_DEFINED
    FILEIO_DATA *  LineIn_getSuper (
        LINEIN_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!LineIn_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return (FILEIO_DATA *)this;
    }
#else
    OBJ_DATA *  LineIn_getSuper (
        LINEIN_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!LineIn_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return (OBJ_DATA *)this;
    }
#endif

    
    OBJ_IUNKNOWN *  LineIn_getSuperVtbl (
        LINEIN_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!LineIn_Validate(this)) {
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
        ERESULT eRc = LineIn_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another LINEIN object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         LineIn_Assign (
        LINEIN_DATA       *this,
        LINEIN_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!LineIn_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!LineIn_Validate(pOther)) {
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
    int             LineIn_Compare (
        LINEIN_DATA     *this,
        LINEIN_DATA     *pOther
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
#ifdef  LINEIN_SINGLETON
        if (OBJ_NIL == this) {
            this = LineIn_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!LineIn_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!LineIn_Validate(pOther)) {
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
        LineIn      *pCopy = LineIn_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a LINEIN object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    LINEIN_DATA *     LineIn_Copy (
        LINEIN_DATA       *this
    )
    {
        LINEIN_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!LineIn_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef LINEIN_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = LineIn_New( );
        if (pOther) {
            eRc = LineIn_Assign(this, pOther);
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

    void            LineIn_Dealloc (
        OBJ_ID          objId
    )
    {
        LINEIN_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!LineIn_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((LINEIN_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        LineIn_setIndex(this, OBJ_NIL);
        
        if (this->pBuffer) {
            mem_Free(this->pBuffer);
            this->pBuffer = NULL;
            this->cBuffer = 0;
            this->iBuffer = 0;
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
        LineIn      *pDeepCopy = LineIn_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a LINEIN object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    LINEIN_DATA *     LineIn_DeepCopy (
        LINEIN_DATA       *this
    )
    {
        LINEIN_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!LineIn_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = LineIn_New( );
        if (pOther) {
            eRc = LineIn_Assign(this, pOther);
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
    ERESULT         LineIn_Disable (
        LINEIN_DATA     *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  LINEIN_SINGLETON
        if (OBJ_NIL == this) {
            this = LineIn_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!LineIn_Validate(this)) {
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
    ERESULT         LineIn_Enable (
        LINEIN_DATA     *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  LINEIN_SINGLETON
        if (OBJ_NIL == this) {
            this = LineIn_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!LineIn_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        TRC_OBJ(this,"\tEnabled?: %s:\n", obj_Enable(this) ? "true" : "false");
#ifdef   LINEIN_MSGS
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
    //                          G e t s
    //---------------------------------------------------------------

    /*!
     Get the next line stripping any '\r' or \n' from it and terminate
     the line with '\0'.
     @param     this    object pointer
     @param     len     line buffer size in bytes
     @param     pData   line buffer pointer (optional) If NULL, return
                        line size.
     @return    if successful, the line's length.  Otherwise, -1 (EOF)
                or -2 (ERROR).
     */
    int             LineIn_Gets (
        LINEIN_DATA     *this,
        uint32_t        len,
        char            *pData
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        int             curLen = 0;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  LINEIN_SINGLETON
        if (OBJ_NIL == this) {
            this = LineIn_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!LineIn_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if ((0 == len) || (NULL == pData)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        if (this->fEOF && (this->iBuffer >= this->cBuffer)) {
            return -1;
        }
        len--;              // Leave room for trailing null.
       
        // Read the line
        this->loc.offset = this->iPos + this->iBuffer;
        this->loc.lineNo++;
        while (curLen <= len) {
            // Get the next buffer if needed.
            if (this->iBuffer >= this->cBuffer) {
                eRc = LineIn_Read(this);
                if (ERESULT_FAILED(eRc) || (0 == this->cBuffer)) {
                    return -1;
                }
            }
            // Handle EOL ('\n', "\n\r", "\r\n")
            if ('\r' == this->pBuffer[this->iBuffer]) {
                if ((this->iBuffer + 1) >= this->cBuffer) {
                    if ('\n' == this->pBuffer[this->iBuffer + 1]) {
                        this->iBuffer += 2;
                        break;
                    }
                }
                continue;
            }
            if ('\n' == this->pBuffer[this->iBuffer]) {
                this->iBuffer++;
                if (this->iBuffer >= this->cBuffer) {
                    if ('\r' == this->pBuffer[this->iBuffer]) {
                        this->iBuffer++;
                    }
                }
                break;
            }
            // Add character to external buffer.
            if (curLen < len) {
                *pData++ = this->pBuffer[this->iBuffer++];
            }
            curLen++;
        }
        if (pData) {
            *pData++ = '\0';
        }
        if (curLen) {
            eRc = LineIndex_Add(this->pIndex, &this->loc);
        }

        // Return to caller.
        return curLen;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    LINEIN_DATA *   LineIn_Init (
        LINEIN_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(LINEIN_DATA);
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

#ifdef  LINEIN_SUPER_DEFINED
        this = (OBJ_ID)FileIO_Init((FILEIO_DATA *)this);   // Needed for Inheritance
#else
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_LINEIN);
#endif
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&LineIn_Vtbl);
#ifdef  LINEIN_JSON_SUPPORT
        JsonIn_RegisterClass(LineIn_Class());
#endif
        
        this->maxBuffer = 2048;
        this->pBuffer = mem_Malloc(this->maxBuffer);
        if (NULL == this->pBuffer) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
        this->pIndex = LineIndex_NewWithMax(128);
        if (OBJ_NIL == this->pIndex) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }


#ifdef NDEBUG
#else
        if (!LineIn_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "LineIn::sizeof(LINEIN_DATA) = %lu\n", 
                sizeof(LINEIN_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(LINEIN_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                      I s  E n a b l e d
    //---------------------------------------------------------------
    
    bool                LineIn_IsEnabled (
        LINEIN_DATA       *this
    )
    {
        //ERESULT         eRc;
        bool            fRc = false;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  LINEIN_SINGLETON
        if (OBJ_NIL == this) {
            this = LineIn_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!LineIn_Validate(this)) {
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
    //                        O p e n
    //---------------------------------------------------------------

    ERESULT         LineIn_Open (
        LINEIN_DATA     *this,
        PATH_DATA       *pPath,
        bool            fMem
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  LINEIN_SINGLETON
        if (OBJ_NIL == this) {
            this = LineIn_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!LineIn_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        eRc = FileIO_Open((FILEIO_DATA *)this, pPath, fMem);
        if (ERESULT_FAILED(eRc)) {
            return eRc;
        }
        
        eRc = LineIn_Read(this);
        if (ERESULT_FAILED(eRc)) {
            FileIO_Close((FILEIO_DATA *)this, false);
            return ERESULT_IO_ERROR;
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
        void        *pMethod = LineIn_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_DATA, an object's data is returned
                        if it fits in a "void *".
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "LineIn", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          LineIn_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        LINEIN_DATA     *this = objId;
        const
        char            *pStrA = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!LineIn_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(LINEIN_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)LineIn_Class();
                break;

            case OBJ_QUERYINFO_TYPE_DATA:
                switch (*pStrA) {
     
                    case 'B':
                        if (str_Compare("Buffer", (char *)pStrA) == 0) {
                            return (void *)this->pBuffer;
                        }
                        break;
                        
                    case 'I':
                        if (str_Compare("Index", (char *)pStrA) == 0) {
                            return (void *)this->pIndex;
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
                            return LineIn_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStrA) == 0) {
                            return LineIn_Enable;
                        }
                        break;

                    case 'P':
#ifdef  LINEIN_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStrA) == 0) {
                            return LineIn_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStrA) == 0) {
                            return LineIn_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStrA) == 0) {
                            return LineIn_ToDebugString;
                        }
#ifdef  LINEIN_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStrA) == 0) {
                            return LineIn_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStrA) == 0) {
                            return LineIn_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == LineIn_ToDebugString)
                    return "ToDebugString";
#ifdef  LINEIN_JSON_SUPPORT
                if (pData == LineIn_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                        R e a d
    //---------------------------------------------------------------

    /*!
     Read the next input buffer.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         LineIn_Read (
        LINEIN_DATA     *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  LINEIN_SINGLETON
        if (OBJ_NIL == this) {
            this = LineIn_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!LineIn_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == this->pBuffer) {
            return ERESULT_INTERNAL_ERROR;
        }
#endif
        
        // We have to get the positon before it changes from the read.
        this->iPos = (uint32_t)FileIO_Tell((FILEIO_DATA *)this);
       
        // Read the next buffer of data.
        eRc = FileIO_Read((FILEIO_DATA *)this, this->maxBuffer, this->pBuffer, &this->cBuffer);
        if (ERESULT_FAILED(eRc) || (0 == this->cBuffer)) {
            this->fEOF = 1;
        } else {
            this->iBuffer = 0;
        }
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                        S e e k
    //---------------------------------------------------------------

    /*!
     Restart input at specified line number.
     @param     this    object pointer
     @param     lineNo  lineNo to seek to (1+)
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         LineIn_Seek (
        LINEIN_DATA     *this,
        uint32_t        lineNo
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        SRCLOC          loc = {0};
        SRCLOC          *pFnd;
        off_t           offsetOld;
        off_t           offset;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  LINEIN_SINGLETON
        if (OBJ_NIL == this) {
            this = LineIn_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!LineIn_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (0 == lineNo) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        offsetOld = FileIO_Tell((FILEIO_DATA *)this);
        
        pFnd = LineIndex_FindLine(this->pIndex, lineNo);
        if (pFnd) {
            loc = *pFnd;
            offset = FileIO_SeekBegin((FILEIO_DATA *)this, loc.offset);
            if (offset == loc.offset) {
                loc.lineNo--;
                this->loc = loc;
                eRc = LineIn_Read(this);
                if (ERESULT_FAILED(eRc) || (0 == this->cBuffer)) {
                    return ERESULT_IO_ERROR;
                }
                while (this->loc.lineNo < lineNo) {
                    DEBUG_BREAK();          //TODO: Finish me!
                }
            } else {
                offset = FileIO_SeekBegin((FILEIO_DATA *)this, offsetOld);
                eRc = ERESULT_INTERNAL_ERROR;
            }
        }
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          T e l l
    //---------------------------------------------------------------

    /*!
     Enable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    uint32_t        LineIn_Tell (
        LINEIN_DATA     *this
    )
    {
        //ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  LINEIN_SINGLETON
        if (OBJ_NIL == this) {
            this = LineIn_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!LineIn_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        // Return to caller.
        return (this->iPos + this->iBuffer);
    }



    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = LineIn_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     LineIn_ToDebugString (
        LINEIN_DATA      *this,
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
        if (!LineIn_Validate(this)) {
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
                    LineIn_getSize(this),
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
    bool            LineIn_Validate (
        LINEIN_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_LINEIN))
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


        if (!(obj_getSize(this) >= sizeof(LINEIN_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef  __cplusplus
}
#endif


