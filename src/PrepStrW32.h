// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Preprocess a Source String (PrepStrW32) Header
//****************************************************************
/*
 * Program
 *          Preprocess a Source String (PrepStrW32)
 * Purpose
 *          This object provides a C-like preprocessor.
 *
 *          The initial version of this preprocessor was taken from "lemon"
 *          by Richard Hipp which is part of SQLite, a great SQL tool. SQLite
 *          and this code was placed in the Public Domain by its author.
 *
 * Remarks
 *  1.      This is a first step. We will build on it.
 *
 * History
 *  04/23/2022 Generated
 */

/*
                        Preprocessor Grammar
 
 stmts          :   preproc_char [WS] preproc_cmd stmts
                |   stmt stmts
                |
                ;
 preproc_line   :   preproc_char [WS] preproc_cmd NL
                |   stmts
                ;
 preproc_cmd    :   "ifdef" WS def_expr [WS] NL stmts ifdef_body
                |   "ifndef" WS def_expr [WS] NL stmts ifdef_body
                |   "macro" [WS] NL [WS] identifier [WS] macro_args NL macro_body NL mend_stmt
                ;
 ifdef_body     :
                    {NL [WS] preproc_char [WS] "elifdef" WS def_expr [WS] NL stmts*} <== Not Supported yet
                    [NL [WS] preproc_char [WS] "else" def_expr [WS] NL stmts*]
                    stmts* NL [WS] preproc_char [WS] "endif" [WS] NL
                ;
 macro_args     :   [prm_char mac_ident [',' prm_char mac_ident]*]
                ;
 macro_body     :   macro_stmt* NL [WS] 
                ;
 marco_stmt     :   [WS] stmt [WS] NL
                ;
 mend_stmt      :   preproc_char [WS] "mend" [WS] NL
                ;
 def_expr       :   identifier {def_expr_and}
                ;
 def_expr_or    :   {"||"  identifier def_expr_and}
                ;
 def_expr_and   :   {"&&" identifier}
                ;
 identifier     :   preproc_char ident_first {ident_chars}
                ;
 variable       :   (identifier | 'char string' | "char string")  ['.' modifier]
                ;
 modifier       :   'camel(' ')' | 'lower(' ')' | 'upper(' ')'
                ;
 ident_first    :   [a..z] | [A..Z] | '$' | '@'
                ;
 ident_chars    :   [a..z] | [A..Z] | [0..9] | '$' | '@'
                ;
 prep_char      :   char is defined by object caller (default '%')
                ;
 prm_char       :   macro parameter prefix character is defined by object caller (default '&')
                ;
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


//#define   PREPSTRW32_IS_IMMUTABLE     1
//#define   PREPSTRW32_JSON_SUPPORT     1
//#define   PREPSTRW32_SINGLETON        1
//#define   PREPSTRW32_MSGS             1
//#define   PREPSTRW32_SUPER_DEFINED    1




#include        <cmn_defs.h>
#include        <AStr.h>
#ifdef PREPSTRW32_SUPER_DEFINED
#include        <Scanner.h>
#endif
#include        <TextIn.h>
#include        <TextOut.h>


#ifndef         PREPSTRW32_H
#define         PREPSTRW32_H






#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


#ifdef PREPSTRW32_SUPER_DEFINED
    typedef struct PrepStrW32_data_s  PREPSTRW32_DATA;          // Inherits from Scanner
#else
    typedef struct PrepStrW32_data_s  PREPSTRW32_DATA;          // Inherits from obj
#endif
    typedef struct PrepStrW32_class_data_s PREPSTRW32_CLASS_DATA;  // Inherits from obj

    typedef struct PrepStrW32_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        //Scanner_VTBL    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in PrepStrW32_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(PREPSTRW32_DATA *);
    } PREPSTRW32_VTBL;

    typedef struct PrepStrW32_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in PrepStrW32_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(PREPSTRW32_DATA *);
    } PREPSTRW32_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  PREPSTRW32_SINGLETON
    PREPSTRW32_DATA * PrepStrW32_Shared (
        void
    );

    void            PrepStrW32_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to PrepStrW32 object if successful, otherwise OBJ_NIL.
     */
    PREPSTRW32_DATA * PrepStrW32_Alloc (
        void
    );
    
    
    OBJ_ID          PrepStrW32_Class (
        void
    );
    
    
    PREPSTRW32_DATA * PrepStrW32_New (
        void
    );
    
    
#ifdef  PREPSTRW32_JSON_SUPPORT
    PREPSTRW32_DATA * PrepStrW32_NewFromJsonString (
        ASTR_DATA       *pString
    );

    PREPSTRW32_DATA * PrepStrW32_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    bool            PrepStrW32_setFindValue (
        PREPSTRW32_DATA *this,
        ASTR_DATA       *(*pFindValueA)(OBJ_ID, const char *),
        OBJ_ID          pObjFind
    );


/*! @property   GrpCharE
    is the first character that identifies the end of a Preprocess
    expansion grouping. The default value is '}'.
 */
    W32CHR_T        PrepStrW32_getGrpCharE (
        PREPSTRW32_DATA *this
    );

    bool            PrepStrW32_setGrpCharE (
        PREPSTRW32_DATA *this,
        W32CHR_T        value
    );


/*! @property   GrpCharS
    is the first character that identifies the beginning of a Preprocess
    expansion grouping. The default value is '{'.
 */
    W32CHR_T        PrepStrW32_getGrpCharS (
        PREPSTRW32_DATA *this
    );

    bool            PrepStrW32_setGrpCharS (
        PREPSTRW32_DATA *this,
        W32CHR_T        value
    );


#ifdef PREPSTRW32_MSGS
    /*! @property   Messages
        Allows information and warning messages to be issued.
     */
    bool            PrepStrW32_setMsgs (
        PREPSTRW32_DATA *this,
        void            (*pMsgInfo)(OBJ_ID, const char *, ...),
        void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...),
        OBJ_ID          pObj
    );
#endif


/*! @property   PrepChar
    is the first character that identifies a Preprocess command. The
    default value is '%'.
 */
    W32CHR_T        PrepStrW32_getPrepChar (
        PREPSTRW32_DATA *this
    );

    bool            PrepStrW32_setPrepChar (
        PREPSTRW32_DATA *this,
        W32CHR_T        value
    );


    SCANNER_DATA *  PrepStrW32_getSuper (
        PREPSTRW32_DATA     *this
    );

    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

  
    PREPSTRW32_DATA * PrepStrW32_Init (
        PREPSTRW32_DATA *this
    );



    /*!
     Preprocess the Input creating the Ouput. "ifdef", "ifndef", "else" and "endif"
     commands are proessed.  Substitution within the lines that are output is supported
     via the "%{" variable_name "}" normal processing.
     @param     this    object pointer
     @param     pInput  Text Input object pointer
     @param     pOutput Text Output object pointer
     @return    If successful, the output text is accumulated in pOutput and ERESULT_SUCCESS
                is returned. Otherwise, an ERESULT_* error is returned.
     */
    ERESULT         PrepStrW32_PreprocInput (
        PREPSTRW32_DATA *this,
        TEXTIN_DATA     *pInput,
        TEXTOUT_DATA    *pOutput,
        uint32_t        *pCount
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
#endif


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
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     PrepStrW32_ToDebugString (
        PREPSTRW32_DATA *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* PREPSTRW32_H */

