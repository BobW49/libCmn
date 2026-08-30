// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   PrepStrW32_internal.h
 *  Generated 04/23/2022 09:45:13
 *
 * Notes:
 *  --  N/A
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




#include        <PrepStrW32.h>
#include        <JsonIn.h>
#include        <Scanner_internal.h>




#ifndef PREPSTRW32_INTERNAL_H
#define PREPSTRW32_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif


    //-----------------------------------------------
    //              Macro Name Table
    //-----------------------------------------------
    /*  The Macro Name Table contains an entry for each
        defined macro and is indexed by name. Each mnt
        entry contains the macro name  and an index into
        the Macro Definition Table for the first line of
        the actual Macro Definition.
    */
    typedef struct MacroNameTable {
        char        *pName;
        int         index;          // Macro Definition Table
        bool        fSkipFlag;
    } MacroNameTable_T;



    //-----------------------------------------------
    //          Macro Definition Table
    //-----------------------------------------------
    /*  The Macro Definition Table contains one entry
        for every line of the macro definition and will
        be called upon when macro expansion is necessary.
        A macro is stored verbatim in this table one line
        at a time with the "mend" entry determining the
        end of the macro text.
    */
    typedef struct MacroDefinitionTable {
        int         srno;
        char        inst[20];
    }   MacroDefinitionTable_T;



    //-----------------------------------------------
    //              Argument List Array
    //-----------------------------------------------
    /*  
        The Argument List Array contains one entry for
        each argument of a macro call. These arguments
        will then be substituted in the macro text as
        used in the Macro Definition Table.
    */ 
    typedef struct ArgumentListArray {
        int         index;
        char        arg[20];
    }   ArgumentListArray_T;




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#if !defined(__arm64__)
#pragma pack(push, 1)
#endif
struct PrepStrW32_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
#ifdef PREPSTRW32_SUPER_DEFINED
    SCANNER_DATA    super;
#else
    OBJ_DATA        super;
#endif
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    W32CHR_T        prepChar;       // Character Prefix to denote preprocessor lines and variables ('%')
    W32CHR_T        grpCharS;       // Character Prefix to denote the start of a variable group ('{')
    W32CHR_T        grpCharE;       // Character Prefix to denote the end of a variable group ('}')
    W32CHR_T        prmChar;        // Macro Parameter Prefix Character
    ASTR_DATA       *pStr;
    SCANNER_DATA    *pScan;

    ASTR_DATA       *(*pFindValueA)(OBJ_ID, const char *);
    OBJ_ID          pObjFind;
#define FIND_NAME_MAXLEN 127
    
#ifdef   PREPSTRW32_MSGS
    // Informational and Warning Log Messages
    void            (*pMsgInfo)(OBJ_ID, const char *, ...);
    void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...);
    OBJ_ID          pMsgObj;
#endif
};
#if !defined(__arm64__)
#pragma pack(pop)
#endif

    extern
    struct PrepStrW32_class_data_s  PrepStrW32_ClassObj;

    extern
    const
    PREPSTRW32_VTBL         PrepStrW32_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  PREPSTRW32_SINGLETON
    PREPSTRW32_DATA * PrepStrW32_getSingleton (
        void
    );

    bool            PrepStrW32_setSingleton (
     PREPSTRW32_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    SCANNER_DATA *  PrepStrW32_getSuper (
        PREPSTRW32_DATA *this
    );


    OBJ_IUNKNOWN *  PrepStrW32_getSuperVtbl (
        PREPSTRW32_DATA *this
    );


    ERESULT         PrepStrW32_Assign (
        PREPSTRW32_DATA *this,
        PREPSTRW32_DATA *pOther
    );


    PREPSTRW32_DATA * PrepStrW32_Copy (
        PREPSTRW32_DATA *this
    );


    void            PrepStrW32_Dealloc (
        OBJ_ID          objId
    );


    PREPSTRW32_DATA * PrepStrW32_DeepCopy (
        PREPSTRW32_DATA *this
    );


    /*!
     Process the current string substituting the names which are
     prefixed with the prep char or prep_char '{' name '}' and sub-
     stituting the data found in the dictionary for the variable if
     found in the dictionary.
     @param     this    object pointer
     @param     pScan   the input string
     @param     pOut    TextOut object pointer where text will be written
     @return    If successful, ERESULT_SUCCESS; otherwise, an ERESULT_*
                error.
     */
    ERESULT         PrepStrW32_ExpandVars (
        PREPSTRW32_DATA *this,
        SCANNER_DATA    *pScan,
        TEXTOUT_DATA    *pOut
    );


    /*!
     Process the current string substituting the names which are
     prefixed with the prep char or prep_char '{' name '}' and sub-
     stituting the data found in the dictionary for the variable if
     found in the dictionary.
     @param     this    object pointer
     @param     pOut    TextOut object pointer where text will be written
     @return    If successful, ERESULT_SUCCESS; otherwise, an ERESULT_*
                error.
     */
    ERESULT         PrepStrW32_ExpandVar (
        PREPSTRW32_DATA *this,
        uint32_t        len,
        const
        W32CHR_T        *pStrW32,
        ASTR_DATA *     (*pFindA)(OBJ_ID, const char *pName),
        OBJ_ID          pFindObj,
        TEXTOUT_DATA    *pOut
    );


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
    );


#ifdef  PREPSTRW32_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    PREPSTRW32_DATA * PrepStrW32_ParseJsonObject (
        JSONIN_DATA     *pParser
    );


    /*!
     Parse the object from an established parser. This helps facilitate
     parsing the fields from an inheriting object.
     @param pParser     an established jsonIn Parser Object
     @param pObject     an Object to be filled in with the
                        parsed fields.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         PrepStrW32_ParseJsonFields (
        JSONIN_DATA     *pParser,
        PREPSTRW32_DATA *pObject
    );
#endif


    int             PrepStrW32_PreProcBoolEvalScan (
        PREPSTRW32_DATA *this,
        SCANNER_DATA    *pLine
    );


    void *          PrepStrW32_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  PREPSTRW32_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = PrepStrW32_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     PrepStrW32_ToJson (
        PREPSTRW32_DATA *this
    );


    /*!
     Append the json representation of the object's fields to the given
     string. This helps facilitate parsing the fields from an inheriting 
     object.
     @param this        Object Pointer
     @param pStr        String Pointer to be appended to.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         PrepStrW32_ToJsonFields (
        PREPSTRW32_DATA *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool            PrepStrW32_Validate (
        PREPSTRW32_DATA *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* PREPSTRW32_INTERNAL_H */

