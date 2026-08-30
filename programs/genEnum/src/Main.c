// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   Main.c
 *  Generated 10/31/2021 16:52:50
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
#include        <Main_internal.h>
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

    static
    CMDUTL_OPTION       pPgmOptions[] = {
        {
            "files",
            0,
            CMDUTL_ARG_OPTION_NONE,
            CMDUTL_TYPE_BOOL,
            0,
            offsetof(MAIN_DATA, fFiles),
            NULL,
            (void *)"Generate enum files"
        },
        {
            "libs",
            'l',
            CMDUTL_ARG_OPTION_REQUIRED,
            CMDUTL_TYPE_STRING,
            0,
            offsetof(MAIN_DATA, pLibs),
            NULL,
            (void *)"Prefix to include file paths (default: \"~/git/\")"
        },
        {
            "name",
            'n',
            CMDUTL_ARG_OPTION_REQUIRED,
            CMDUTL_TYPE_STRING,
            0,
            offsetof(MAIN_DATA, pName),
            NULL,
            (void *)"Enumeration Name (normally the name of the enum)"
        },
        {
            "prefix",
            'p',
            CMDUTL_ARG_OPTION_REQUIRED,
            CMDUTL_TYPE_STRING,
            0,
            offsetof(MAIN_DATA, pPrefix),
            NULL,
            (void *)"Prefix Name (normally an object prefix which prefixes the name)"
        },
        {
            "start",
            0,
            CMDUTL_ARG_OPTION_REQUIRED,
            CMDUTL_TYPE_STRING,
            0,
            offsetof(MAIN_DATA, pStart),
            NULL,
            (void *)"Optional Enumeration Starting Value"
        },
        {
            "suffix",
            'n',
            CMDUTL_ARG_OPTION_REQUIRED,
            CMDUTL_TYPE_STRING,
            0,
            offsetof(MAIN_DATA, pSuffix),
            NULL,
            (void *)"A suffix string to be added to the end of each generated enumeration"
        },
        {0}
    };



 
    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/



    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            Main_task_body (
        void            *pData
    )
    {
        //MAIN_DATA  *this = pData;
        
    }
#endif



    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    MAIN_DATA *     Main_Alloc (
        void
    )
    {
        MAIN_DATA       *this;
        uint32_t        cbSize = sizeof(MAIN_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    MAIN_DATA *     Main_New (
        void
    )
    {
        MAIN_DATA       *this;
        
        this = Main_Alloc( );
        if (this) {
            this = Main_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                            A p p l
    //---------------------------------------------------------------

    APPL_DATA *     Main_getAppl (
        MAIN_DATA       *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Main_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return (APPL_DATA *)this;
    }


    //---------------------------------------------------------------
    //                            D i c t
    //---------------------------------------------------------------

#ifdef  MAIN_USE_DICT
    DICT_DATA *     Main_getDict (
        MAIN_DATA       *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Main_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pDict;
    }


    bool            Main_setDict (
        MAIN_DATA       *this,
        DICT_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Main_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pDict) {
            obj_Release(this->pDict);
        }
        this->pDict = pValue;

        return true;
    }
#endif



    //---------------------------------------------------------------
    //                            L i b s
    //---------------------------------------------------------------

    ASTR_DATA *     Main_getLibs (
        MAIN_DATA       *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Main_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pLibs;
    }


    bool            Main_setLibs (
        MAIN_DATA       *this,
        ASTR_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Main_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pLibs) {
            obj_Release(this->pLibs);
        }
        this->pLibs = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                            N a m e
    //---------------------------------------------------------------

    ASTR_DATA *     Main_getName (
        MAIN_DATA       *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Main_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pName;
    }


    bool            Main_setName (
        MAIN_DATA       *this,
        ASTR_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Main_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pName) {
            obj_Release(this->pName);
        }
        this->pName = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                           P r e f i x
    //---------------------------------------------------------------

    ASTR_DATA *     Main_getPrefix (
        MAIN_DATA       *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Main_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pPrefix;
    }


    bool            Main_setPrefix (
        MAIN_DATA       *this,
        ASTR_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Main_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pPrefix) {
            obj_Release(this->pPrefix);
        }
        this->pPrefix = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        Main_getPriority (
        MAIN_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Main_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            Main_setPriority (
        MAIN_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!Main_Validate(this)) {
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
    
    uint32_t        Main_getSize (
        MAIN_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!Main_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S t a r t
    //---------------------------------------------------------------

    ASTR_DATA *     Main_getStart (
        MAIN_DATA       *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Main_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pStart;
    }


    bool            Main_setStart (
        MAIN_DATA       *this,
        ASTR_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Main_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pStart) {
            obj_Release(this->pStart);
        }
        this->pStart = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA *     Main_getStr (
        MAIN_DATA       *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Main_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStr;
    }
    
    
    bool            Main_setStr (
        MAIN_DATA       *this,
        ASTR_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Main_Validate(this)) {
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
    //                          S u f f i x
    //---------------------------------------------------------------
    
    ASTR_DATA *     Main_getSuffix (
        MAIN_DATA       *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Main_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pSuffix;
    }
    
    
    bool            Main_setSuffix (
        MAIN_DATA       *this,
        ASTR_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Main_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pSuffix) {
            obj_Release(this->pSuffix);
        }
        this->pSuffix = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  Main_getSuperVtbl (
        MAIN_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Main_Validate(this)) {
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
        ERESULT eRc = Main_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another MAIN object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         Main_Assign (
        MAIN_DATA       *this,
        MAIN_DATA       *pOther
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Main_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Main_Validate(pOther)) {
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
    //               C r e a t e  I n p u t  P a t h
    //---------------------------------------------------------------

    PATH_DATA *     Main_CheckInputPath (
        MAIN_DATA       *this,
        ASTR_DATA       *pStr
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        PATH_DATA       *pPath = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Main_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
        if (OBJ_NIL == pStr) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return OBJ_NIL;
        }
#endif
        TRC_OBJ(this, "Main_CreateInputPath(%s)\n", pStr ? AStr_getData(pStr) : "");

        pPath = Path_NewFromAStr(pStr);
        Appl_ErrorFatalOnBool(
                    (OBJ_NIL == pPath),
                    "FATAL - Failed to create path \"from\" \n"
        );
        eRc = Path_Clean(pPath, NULL, OBJ_NIL);
        Appl_ErrorFatalOnEresult(
                    eRc,
                    "FATAL - File, %s, does not exist or is not a file!\n",
                    Path_getData(pPath)
        );
        eRc = Path_IsFile(pPath);
        Appl_ErrorFatalOnEresult(
                    eRc,
                    "FATAL - File, %s, does not exist or is not a file!\n",
                    Path_getData(pPath)
        );

        // Return to caller.
        return pPath;
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
    int             Main_Compare (
        MAIN_DATA       *this,
        MAIN_DATA       *pOther
    )
    {
        int             iRc = -1;
#ifdef  xyzzy        
        const
        char            *pStr1;
        const
        char            *pStr2;
#endif
        
#ifdef NDEBUG
#else
        if (!Main_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!Main_Validate(pOther)) {
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
        Main      *pCopy = Main_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a MAIN object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    MAIN_DATA *     Main_Copy (
        MAIN_DATA       *this
    )
    {
        MAIN_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Main_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef MAIN_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = Main_New( );
        if (pOther) {
            eRc = Main_Assign(this, pOther);
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

    void            Main_Dealloc (
        OBJ_ID          objId
    )
    {
        MAIN_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!Main_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((MAIN_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

#ifdef  MAIN_USE_DICT
        Main_setDict(this, OBJ_NIL);
#endif
        Main_setLibs(this, OBJ_NIL);
        Main_setName(this, OBJ_NIL);
        Main_setPrefix(this, OBJ_NIL);
        Main_setStart(this, OBJ_NIL);
        Main_setStr(this, OBJ_NIL);
        Main_setSuffix(this, OBJ_NIL);

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
        Main      *pDeepCopy = Main_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a MAIN object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    MAIN_DATA *     Main_DeepCopy (
        MAIN_DATA       *this
    )
    {
        MAIN_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Main_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = Main_New( );
        if (pOther) {
            eRc = Main_Assign(this, pOther);
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
    ERESULT         Main_Disable (
        MAIN_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this,"%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!Main_Validate(this)) {
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
    ERESULT         Main_Enable (
        MAIN_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this,"%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!Main_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        TRC_OBJ(this,"\tEnabled?: %s:\n", obj_Enable(this) ? "true" : "false");
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          E x e c
    //---------------------------------------------------------------

    int             Main_Exec (
        MAIN_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;
        int             iRc;
        ASTR_DATA       *pStr = OBJ_NIL;
        char            *pChrStr;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !Main_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif

        eRc = Main_ParseArgsDefault(this);
        if (ERESULT_FAILED(eRc)) {
            Appl_Usage((APPL_DATA *)this, "ERROR - Failed to properly set defaults!");
            exit(8);
        }

        for (;;) {

            fRc = Appl_IsMore((APPL_DATA *)this);
            if (!fRc) {
                break;
            }

            eRc = Appl_ProcessOptions((APPL_DATA *)this);
            if (ERESULT_FAILED(eRc)) {
                Appl_Usage((APPL_DATA *)this, "ERROR - Failed to properly parse command line!");
                exit(8);
            }

            pChrStr = Appl_NextArg((APPL_DATA *)this);
            if (NULL == pChrStr) {
                break;
            }
            pStr = AStr_NewA(pChrStr);
            iRc = Main_ProcessArg(this, pStr);
            obj_Release(pStr);
            pStr = OBJ_NIL;
            if (iRc) {
                return iRc;
            }
        }

        // Return to caller.
        return 0;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    MAIN_DATA *   Main_Init (
        MAIN_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(MAIN_DATA);
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

        this = (OBJ_ID)Appl_Init((APPL_DATA *)this);        // Needed for Inheritance
        // If you use inheritance, remember to change the obj_ClassObj reference 
        // in the OBJ_INFO at the end of Main_object.c
        // this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_MAIN);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&Main_Vtbl);
#ifdef  MAIN_JSON_SUPPORT
        JsonIn_RegisterClass(Main_Class());
#endif
        
        /*
        this->pArray = ObjArray_New( );
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        */

#ifdef  MAIN_USE_DICT
        this->pDict = Dict_New( );
        if (OBJ_NIL == this->pDict) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#endif

        Appl_setArgDefs((APPL_DATA *)this, pPgmOptions);
        Appl_setUsage(
                      (APPL_DATA *)this,
                      this,
                      (void *)Main_UsageDesc,
                      (void *)Main_UsageProgLine,
                      (void *)Main_UsageOptions,
                      NULL
        );
        ((APPL_DATA *)this)->iVerbose++;
        
#ifdef NDEBUG
#else
        if (!Main_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "Main::sizeof(MAIN_DATA) = %lu\n", 
                sizeof(MAIN_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(MAIN_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                      I s  E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         Main_IsEnabled (
        MAIN_DATA       *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Main_Validate(this)) {
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
    //              P a r s e  A r g s  D e f a u l t
    //---------------------------------------------------------------

    /*! Set default values for arguments just prior to them being parsed.
     This is called by Appl_SetupFromArgV() and Appl_SetupFromStr().
     Parsed arguments may replace any value set here.
     @return    If successful, then ERESULT_SUCESS. Otherwise, an ERESULT_*
                error. Note: this is ignored in Appl.
     */
    ERESULT         Main_ParseArgsDefault (
        MAIN_DATA        *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Main_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Setup initial arguments.
        /*
         * set initial argumeent values here
         */ 

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //              P r o c e s s  A r g s
    //---------------------------------------------------------------

    ERESULT         Main_ProcessInit (
        MAIN_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Main_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif


        // Return to caller.
        return eRc;
    }


    /*!
     Process each command line argument, parsing the JSON file and
     generating the Makefile.
     @param     this    object pointer
     @return    If successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Main_ProcessArg (
        MAIN_DATA       *this,
        ASTR_DATA       *pStr
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        PATH_DATA       *pPath = OBJ_NIL;
        EXEC_DATA       *pExec;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Main_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pStr) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        TRC_OBJ(this, "Main_ProcessArg(%s)\n", pStr ? AStr_getData(pStr) : "");

        if (!Appl_getQuiet((APPL_DATA *)this)) {
            fprintf(stderr, "\tProcessing - %s...\n", AStr_getData(pStr));
        }

        pPath = Main_CheckInputPath(this, pStr);
        Appl_ErrorFatalOnBool(
                    (OBJ_NIL == pPath),
                    "FATAL - Failed to create path \"from\" \n"
        );

        pExec = Exec_New();
        Appl_ErrorFatalOnBool(
                    (OBJ_NIL == pExec),
                    "FATAL - Failed to create Exec object\n"
        );
        Exec_setFiles(pExec, this->fFiles);

        Appl_ErrorFatalOnBool(
                    (OBJ_NIL == this->pPrefix),
                    "FATAL - --prefix is required!\n"
        );
        Appl_ErrorFatalOnBool(
                    (OBJ_NIL == this->pName),
                    "FATAL - --name is required!\n"
        );
        if (this->pStart) {
            Exec_setStart(pExec, this->pStart);
        }
        eRc =   Exec_Exec(
                          pExec,
                          pPath,
                          OBJ_NIL,
                          AStr_getData(this->pPrefix),
                          AStr_getData(this->pName),
                          (this->pLibs ? AStr_getData(this->pLibs) : "~/git/"),
                          (this->pSuffix ? AStr_getData(this->pSuffix) : NULL)
                );
        Appl_ErrorFatalOnEresult(
                    eRc,
                    "FATAL - Failed to create enumeration for &s\n",
                    Path_getData(pPath)
        );

        // Return to caller.
        obj_Release(pExec);
        //pExec = OBJ_NIL;
        obj_Release(pPath);
        //pPath = OBJ_NIL;
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
        void        *pMethod = Main_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "Main", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          Main_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        MAIN_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!Main_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(MAIN_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)Main_Class();
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
                            return Main_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return Main_Enable;
                        }
                        break;

                    case 'P':
#ifdef  MAIN_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return Main_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return Main_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return Main_ToDebugString;
                        }
#ifdef  MAIN_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return Main_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return Main_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == Main_ToDebugString)
                    return "ToDebugString";
#ifdef  MAIN_JSON_SUPPORT
                if (pData == Main_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                  S e t u p  F r o m  A r g V
    //---------------------------------------------------------------

    ERESULT         Main_SetupFromArgV (
        MAIN_DATA       *this,
        uint16_t        cArgs,
        char            *ppArgV[],
        char            **ppEnv
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Main_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        eRc = Appl_SetupFromArgV((APPL_DATA *)this, cArgs, ppArgV, ppEnv);

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
        ASTR_DATA      *pDesc = Main_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     Main_ToDebugString (
        MAIN_DATA      *this,
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
        if (!Main_Validate(this)) {
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
                    Main_getSize(this),
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
    //                  U s a g e  H e l p
    //---------------------------------------------------------------

    /*!
     Print the program description with a trailing '\n' and leading "  ".
     @param     this        Object Pointer
     @param     pOutput     File to write to
     @param     pPgmPath    Program's Path
     @return    ERESULT_SUCCESS if successful, otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Main_UsageDesc (
        MAIN_DATA       *this,
        FILE            *pOutput,
        PATH_DATA       *pPgmPath
    )
    {

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Main_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        fprintf(
                pOutput,
                "  Generate an enumeration and supporting tables plus routines\n"
        );
        fprintf(
                pOutput,
                "  to use the tables. --prefix and --name options are required.\n\n"
        );
        fprintf(
                pOutput,
                "  The input file should consist of Comment lines (which start with\n"
                "  an '#' and are skipped.), Comment Lines passed to the output\n"
                "  (which start with '*' and are passed through to the output before\n"
                "  any enumeation items.), Line number setup (which is denoted by '='\n"
                "  followed by a number used as the next line number.), or an Enumeration\n"
                "  items as explained next. External genEnum input files can be included\n"
                "  in the current file by including the file path (which is prefixed\n"
                "  by the \"libs\" option). The numbering for the included file will\n"
                "  start with the current line number not from 0.\n\n"
        );
        fprintf(
                pOutput,
                "  The Enumeration items should consist of the enumeration item name\n"
                "  without the prefix and name specified above. Those will be\n"
                "  prefixed to make the enumerations unique. Optionally, a description\n"
                "  and constant can be added. A value for the enumeration item may be\n"
                "  specified as well as a translation value.\n\n"
        );
        fprintf(
                pOutput,
                "  The line format is now:\n"
                "  enum_name [',' [description] [',' [enum_value] [',' xlate_value]]]\n"
                "  The description can contain blanks, but if it contains\n"
                "  a comma or special characters, then it must be surrouned\n"
                "  with double quoates. The optional enum_value will be in\n"
                "  lieu of the normal generated number and must be unique\n"
                "  within the enumeration.\n\n"
        );
        fprintf(
                pOutput,
                "  A blank line will be counted for the enum value, but will not\n"
                "  have an enum entry.\n"
                "  Be careful with empty lines because of this.\n\n"
        );
        fprintf(
                pOutput,
                "  Example: genEnum --prefix=Test --name=Prim ./tests/files/enum_test.txt\n"
                "  which will cause a line of 'xyzzy' to be generated as TEST_PRIM_XYZZY.\n\n"
        );

        // Return to caller.
        return ERESULT_SUCCESS;
    }


    // Note: --debug(-d), --force(-f), --help(-?,-h), --verbose(-v) are already
    //      taken care of in appl_Usage().
    ERESULT         Main_UsageOptions (
        MAIN_DATA       *this,
        FILE            *pOutput
    )
    {
        uint32_t        i = 0;
        //CMDUTL_OPTION   *pPgmOption = pPgmOptions;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Main_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        for (i=0; pPgmOptions[i].pLongName || pPgmOptions[i].shortName; i++) {
            char            shortOpt[3] = "";
            char            longOpt[20] = "";
            if (pPgmOptions[i].shortName) {
                shortOpt[0] = '-';
                shortOpt[1] = pPgmOptions[i].shortName;
                shortOpt[2] = '\0';
            }
            if (pPgmOptions[i].pLongName) {
                longOpt[0] = '-';
                longOpt[1] = '-';
                strcpy(longOpt+2, pPgmOptions[i].pLongName);
            }
            fprintf(pOutput, "  %-3s %-20s %s\n", shortOpt, longOpt, pPgmOptions[i].pDesc);
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }


    /*!
     Print the program usage line with a trailing '\n' and leading "  ".
     @param     this        Object Pointer
     @param     pOutput     File to write to
     @param     pPgmPath    Program's Path
     @param     pNameA      Program's name
     @return    ERESULT_SUCCESS if successful, otherwise, an ERESULT_*
     error code.
     */
    ERESULT         Main_UsageProgLine (
        MAIN_DATA       *this,
        FILE            *pOutput,
        PATH_DATA       *pPgmPath,
        const
        char            *pNameA
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Main_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        fprintf(pOutput, "  %s [options] input_path\n", pNameA);

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

#ifdef NDEBUG
#else
    bool            Main_Validate (
        MAIN_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_MAIN))
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


        if (!(obj_getSize(this) >= sizeof(MAIN_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef  __cplusplus
}
#endif


