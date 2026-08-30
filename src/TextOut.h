// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//              Output UTF-8 Textual Data (TextOut) Header
//****************************************************************

/*
 * Program
 *          Output UTF-8 Textual Data (TextOut)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate TextOut to run things without complications
 *          of interfering with the main TextOut. A TextOut may be 
 *          called a TextOut on other O/S's.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  08/03/2023 Generated
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


/*----------------------------------------------------------------
    The following should be added to the appropriate _defs.h file
    in the _idents_e enum:
        OBJ_IDENT_TEXTOUT,         //  Output UTF-8 Textual Data
        OBJ_IDENT_TEXTOUT_CLASS,
    The following should be added to the appropriate objects.json.txt
    or program.json.txt file:
        {name:"TextOut",  desc:"Output UTF-8 Textual Data"},
 *----------------------------------------------------------------*/



//#define   TEXTOUT_IS_IMMUTABLE     1
//#define   TEXTOUT_JSON_SUPPORT     1
//#define   TEXTOUT_SINGLETON        1
//#define       TEXTOUT_MSGS   1
//#define   TEXTOUT_SUPER_DEFINED     1


#include        <cmn_defs.h>
#include        <AStr.h>
#ifdef  TEXTOUT_SUPER_DEFINED
#include        <obj.h>
#endif


#ifndef         TEXTOUT_H
#define         TEXTOUT_H





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct TextOut_data_s  TEXTOUT_DATA;          // Inherits from obj
    typedef struct TextOut_class_data_s TEXTOUT_CLASS_DATA;  // Inherits from obj

    typedef struct TextOut_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        //obj_VTBL    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in TextOut_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(TEXTOUT_DATA *);
    } TEXTOUT_VTBL;

    typedef struct TextOut_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in TextOut_object.c.
        // Properties:
        // Methods:
        TEXTOUT_DATA *(*pNew)(void);
        //bool        (*pIsEnabled)(TEXTOUT_DATA *);
    } TEXTOUT_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  TEXTOUT_SINGLETON
    TEXTOUT_DATA *  TextOut_Shared (
        void
    );

    void            TextOut_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to TextOut object if successful, otherwise OBJ_NIL.
     */
    TEXTOUT_DATA *  TextOut_Alloc (
        void
    );
    
    
    OBJ_ID          TextOut_Class (
        void
    );
    
    
    TEXTOUT_DATA *  TextOut_New (
        void
    );
    
    /*!
     Create a new TextOut object that accumulates to an AStr object. If OBJ_NIL is
     provided for the pStr parameter, a new AStr object is created with zero length.
     @param     pStr    an optional AStr object pointer which will be appended to
     @return    If successful, an TextOut object which must be released,
                otherwise OBJ_NIL.
     @warning   Remember to release the returned TextOut object.
     */
    TEXTOUT_DATA *  TextOut_NewAStr (
        ASTR_DATA       *pStr
    );


#ifdef  TEXTOUT_JSON_SUPPORT
    TEXTOUT_DATA *   TextOut_NewFromJsonString (
        ASTR_DATA       *pString
    );

    TEXTOUT_DATA *   TextOut_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    /*! @property   ColMax
        specifies the maximum column number (relative to 1) allowed
        which causes a new-line to be generated. A value of 0 which
        is the default causes the maximum column to be ignored.
     */
    uint16_t        TextOut_getColMax (
        TEXTOUT_DATA    *this
    );

    bool            TextOut_setColMax (
        TEXTOUT_DATA    *this,
        uint16_t        value
    );


    /*! @property   ColNo
        specifies the current column number.
     */
    uint16_t        TextOut_getColMax (
        TEXTOUT_DATA    *this
    );

    bool            TextOut_setColMax (
        TEXTOUT_DATA    *this,
        uint16_t        value
    );


    /*! @property   MaxExpand
        sets whether a NL character should expand to colMax or not.
        If true, then fixed size records will be output.
        The default is false.
     */
    bool            TextOut_getMaxExpand (
        TEXTOUT_DATA    *this
    );

    bool            TextOut_setMaxExpand (
        TEXTOUT_DATA    *this,
        bool            fValue
    );


#ifdef TEXTOUT_MSGS
    /*! @property   Messages
        Allows information and warning messages to be issued.
     */
    bool            TextOut_setMsgs (
        TEXTOUT_DATA    *this,
        void            (*pMsgInfo)(OBJ_ID, const char *, ...),
        void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...),
        OBJ_ID          pObj
    );
#endif


    /*! @property   Str
        sets the object to output to a given AStr object if pValue is not OBJ_NIL.
        This will replace any prior output.
     */
    ASTR_DATA *     TextOut_getStr (
        TEXTOUT_DATA    *this
    );

    bool            TextOut_setStr (
        TEXTOUT_DATA    *this,
        ASTR_DATA       *pValue
    );


#ifdef  TEXTOUT_SUPER_DEFINED
    OBJ_DATA *  TextOut_getSuper (
        TEXTOUT_DATA     *this
    );
#else
    OBJ_DATA *  TextOut_getSuper (
        TEXTOUT_DATA     *this
    );
#endif


    /*! @property   TabExpand
        sets whether tab character are to be expanded with the fill character
        or just passed through.
        The default is true.
     */
    bool            TextOut_getTabExpand (
        TEXTOUT_DATA    *this
    );

    bool            TextOut_setTabExpand (
        TEXTOUT_DATA    *this,
        bool            fValue
    );


    /*! @property   TabSize
        sets the number of columns to expand to the right per tab character.
        The default is 4. If ColMax is set and it is reached with the tab
        expansion, no further expansion happens on the following line.
     */
    uint16_t        TextOut_getTabSize (
        TEXTOUT_DATA    *this
    );

    bool            TextOut_setTabSize (
        TEXTOUT_DATA    *this,
        uint16_t        value
    );



    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Output enough filler characters to get to the given column number.
     If we are already beyond that column number, go to the next line
     and again proceed to that column number.
     @param     this    object pointer
     @param     col     Column Number (relative to 1)
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         TextOut_Col (
        TEXTOUT_DATA    *this,
        uint16_t        col
    );


    TEXTOUT_DATA *  TextOut_Init (
        TEXTOUT_DATA    *this
    );


    bool            TextOut_IsString (
        TEXTOUT_DATA    *this
    );


    /*!
     Format and output the given UTF-8 format string and it's
     following data.
     @param     this        Object Pointer
     @param     pFormatStr  Pointer to format string
     @return    If successful, ERESULT_SUCCESS.  Otherwise,
     an ERESULT_* error code
     */
    ERESULT         TextOut_Print (
        TEXTOUT_DATA    *this,
        const
        char            *pFormatStr,
        ...
    );


    /*!
     Output the given UTF-8 character.
     @param     this    Object Pointer
     @param     chr     character
     @return    If successful, ERESULT_SUCCESS.  Otherwise,
     an ERESULT_* error code
     */
    ERESULT         TextOut_PutA (
        TEXTOUT_DATA    *this,
        const
        char            chr
    );


    /*!
     Output the given UTF-8 string.
     @param     this    Object Pointer
     @param     pStr    Pointer to string
     @return    If successful, ERESULT_SUCCESS.  Otherwise,
     an ERESULT_* error code
     */
    ERESULT         TextOut_PutStrA (
        TEXTOUT_DATA    *this,
        const
        char            *pStr
    );


    /*!
     Output the given UTF-8 string.
     @param     this    Object Pointer
     @param     pStr    Pointer to string
     @return    If successful, ERESULT_SUCCESS.  Otherwise,
     an ERESULT_* error code
     */
    ERESULT         TextOut_PutAStr (
        TEXTOUT_DATA    *this,
        ASTR_DATA       *pStr
    );


    /*!
     Output the given UTF-8 character.
     @param     this    Object Pointer
     @param     chr     UTF-8 Character to output
     @return    If successful, ERESULT_SUCCESS.  Otherwise,
     an ERESULT_* error code
     */
    ERESULT         TextOut_PutW32 (
        TEXTOUT_DATA    *this,
        const
        W32CHR_T        chr
    );


    /*!
     Output the given UTF-8 character.
     @param     this    Object Pointer
     @param     len     Optional length of character string. If > 0, then
                        the string is output until the length is met or
                        a NUL is found.
     @param     pStrW32 Wide Characters to output
     @return    If successful, ERESULT_SUCCESS.  Otherwise,
     an ERESULT_* error code
     */
    ERESULT         TextOut_PutStrW32 (
        TEXTOUT_DATA    *this,
        uint32_t        len,
        const
        W32CHR_T        *pStrW32
    );


#ifdef  TEXTOUT_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = TextOut_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     TextOut_ToJson (
        TEXTOUT_DATA    *this
    );
#endif


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
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     TextOut_ToDebugString (
        TEXTOUT_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* TEXTOUT_H */

