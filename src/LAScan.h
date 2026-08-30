// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//              Look-Ahead Scanner (LAScan) Header
//****************************************************************

/*
 * Program
 *          Look-Ahead Scanner (LAScan)
 * Purpose
 *          This object provides a standardized way of parsing an
 *          input source into various components.
 *
 * Remarks
 *  1.      Each scan is destrutive in that it absorbs characters
 *          during the scan that fit its scanning criteria.
 *
 * History
 *  02/26/2023 Generated
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
        OBJ_IDENT_LASCAN,         //  Look-Ahead Scanner
        OBJ_IDENT_LASCAN_CLASS,
    The following should be added to the appropriate objects.json.txt
    or program.json.txt file:
        {name:"LAScan",  desc:"Look-Ahead Scanner"},
 *----------------------------------------------------------------*/



//#define   LASCAN_IS_IMMUTABLE     1
//#define   LASCAN_JSON_SUPPORT     1
//#define   LASCAN_SINGLETON        1
//#define       LASCAN_MSGS   1
//#define   LASCAN_SUPER_DEFINED     1


#include        <cmn_defs.h>
#include        <AStr.h>
#ifdef  LASCAN_SUPER_DEFINED
#include        <obj.h>
#endif
#include        <Token.h>


#ifndef         LASCAN_H
#define         LASCAN_H





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct LAScan_data_s  LASCAN_DATA;          // Inherits from obj
    typedef struct LAScan_class_data_s LASCAN_CLASS_DATA;  // Inherits from obj

    typedef struct LAScan_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        //obj_VTBL    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in LAScan_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(LASCAN_DATA *);
    } LASCAN_VTBL;

    typedef struct LAScan_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in LAScan_object.c.
        // Properties:
        // Methods:
        LASCAN_DATA *(*pNew)(void);
        //bool        (*pIsEnabled)(LASCAN_DATA *);
    } LASCAN_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  LASCAN_SINGLETON
    LASCAN_DATA *   LAScan_Shared (
        void
    );

    void            LAScan_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to LAScan object if successful, otherwise OBJ_NIL.
     */
    LASCAN_DATA *   LAScan_Alloc (
        void
    );
    
    
    OBJ_ID          LAScan_Class (
        void
    );
    
    
    LASCAN_DATA *   LAScan_New (
        void
    );
    
    
#ifdef  LASCAN_JSON_SUPPORT
    LASCAN_DATA *   LAScan_NewFromJsonString (
        ASTR_DATA       *pString
    );

    LASCAN_DATA *   LAScan_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    /*! @property Accum
        Accumulated string used by several scanners to accumulate a
        string.
     */
    const
    uint8_t *       LAScan_getAccum (
        LASCAN_DATA     *this
    );


#ifdef LASCAN_MSGS
    /*! @property   Messages
        Allows information and warning messages to be issued.
     */
    bool            LAScan_setMsgs (
        LASCAN_DATA     *this,
        void            (*pMsgInfo)(OBJ_ID, const char *, ...),
        void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...),
        OBJ_ID          pObj
    );
#endif


#ifdef  LASCAN_SUPER_DEFINED
    OBJ_DATA *      LAScan_getSuper (
        LASCAN_DATA     *this
    );
#else
    OBJ_DATA *      LAScan_getSuper (
        LASCAN_DATA     *this
    );
#endif


    bool            LAScan_getWS (
       LASCAN_DATA      *this
    );

    bool            LAScan_setWS(
        LASCAN_DATA     *this,
        bool            fValue
    );



    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         LAScan_Disable (
        LASCAN_DATA     *this
    );


    ERESULT         LAScan_Enable (
        LASCAN_DATA     *this
    );

   
    LASCAN_DATA *   LAScan_Init (
        LASCAN_DATA     *this
    );


    /*! Lookahead in the scan for the indexth character. The intent
     of this method was so that one could check for potential scans
     based on their first or second characters before initiating the
     actual scan.
     @param     this    object pointer
     @param     index   index into the scan (relative to 1)
     @param     pChr    Optional area to return the indexth character
     @return    if successful, the class for the indexth character.
                Otherwise, -1.
     */
    int32_t         LAScan_LookAhead (
        LASCAN_DATA     *this,
        uint16_t        index,
        W32CHR_T        *pChr
    );


    /*!
     Match the given character against the current obj's Misc
     index into the string.  If they match, advance the scan.
     @param     this    object pointer
     @param     chr     character to be matched
     @return    If they match, return true otherwise false.
     */
    bool            LAScan_MatchChrW32 (
        LASCAN_DATA     *this,
        W32CHR_T        chr
    );


    /*!
     Match each of the given character(s) against the current look-
     ahead. If they match, advance the scan and return true. Otherwise,
     try the next charactere in the list terminating when NUL is found.
     @param     this    object pointer
     @param     pChrs   pointer to a NUL-terminaed list of characters
                        to be matched
     @return    If they match, return true; otherwise false.
     */
    bool            LAScan_MatchChrsW32 (
        LASCAN_DATA     *this,
        W32CHR_T        *pChrs
    );


    /*!
     Match the given character class against the current look-ahead.
     If they match, advance the scan.
     @param     this    object pointer
     @param     cls     class to be matched
     @return    If they match, return true otherwise false.
     */
    bool            LAScan_MatchClass (
        LASCAN_DATA     *this,
        int32_t         cls
    );


    /*!
     Match each of the given character(s) against the current look-
     ahead. If they match, advance the scan and return true. Otherwise,
     try the next charactere in the list terminating when NUL is found.
     @param     this    object pointer
     @param     pClasses pointer to a NUL-terminaed list of character
                        classes to be matched
     @return    If they match, return true; otherwise false.
     */
    bool            LAScan_MatchClasses (
        LASCAN_DATA     *this,
        int32_t         *pClasses
    );


    /*!
     Scan an IBM Asm-like UTF-8 identifier such as:
                [a-zA-Z_$#@] [0-9a-zA-Z_$#@]*
     The value scanned is returned if scan is successful and the next
     scan will start immediately after this one. No terminator is con-
     sidered since the scan is well defined.
     Nothing is changed if the scan is unsuccessful.
     @param     this    object pointer
     @param     ppStrA  Optional pointer to where the identifier value will be returned
     @return    If successful, true and *pValue contains a pointer to the identifier,
                otherwise false.
     @warning   The identifier returned iw only valid until the next scan method is
                called. You should copy it out if you want it retained.
     */
    bool            LAScan_ScanAsmIbmSymbol (
        LASCAN_DATA     *this,
        const
        uint8_t         **ppStrA
    );


    /*!
     Scan an IBM Asm-like UTF-8 identifier such as:
                [.] [0-9a-zA-Z_$#@]*
     The value scanned is returned if scan is successful and the next
     scan will start immediately after this one. No terminator is con-
     sidered since the scan is well defined.
     Nothing is changed if the scan is unsuccessful.
     @param     this    object pointer
     @param     ppStrA  Optional pointer to where the identifier value will be returned
     @return    If successful, true and *pValue contains a pointer to the identifier,
                otherwise false.
     @warning   The identifier returned iw only valid until the next scan method is
                called. You should copy it out if you want it retained.
     */
    bool            LAScan_ScanAsmIbmSymbolSeq (
        LASCAN_DATA     *this,
        const
        uint8_t         **ppStrA
    );


    /*!
     Scan an IBM Asm-like UTF-8 identifier such as:
                [&] [0-9a-zA-Z_$#@]*
     The value scanned is returned if scan is successful and the next
     scan will start immediately after this one. No terminator is con-
     sidered since the scan is well defined.
     Nothing is changed if the scan is unsuccessful.
     @param     this    object pointer
     @param     ppStrA  Optional pointer to where the identifier value will be returned
     @return    If successful, true and *pValue contains a pointer to the identifier,
                otherwise false.
     @warning   The identifier returned iw only valid until the next scan method is
                called. You should copy it out if you want it retained.
     */
    bool            LAScan_ScanAsmIbmSymbolSet (
        LASCAN_DATA     *this,
        const
        uint8_t         **ppStrA
    );


    /*!
     Scan an C-like UTF-8 identifier such as:
                [a-zA-Z_] [0-9a-zA-Z_]*
     The value scanned is returned if scan is successful and the next
     scan will start immediately after this one. No terminator is con-
     sidered since the scan is well defined.
     Nothing is changed if the scan is unsuccessful.
     @param     this    object pointer
     @param     ppStrA  Optional pointer to where the identifier value will be returned
     @return    If successful, true and *pValue contains a pointer to the identifier,
                otherwise false.
     @warning   The identifier returned iw only valid until the next scan method is
                called. You should copy it out if you want it retained.
     */
    bool            LAScan_ScanCIdentifier (
        LASCAN_DATA     *this,
        const
        uint8_t         **ppStrA
    );


    /*!
     Scan a C-like UTF-8 identifier such as:
                [a-zA-Z_] [0-9a-zA-Z_]*
     The value scanned is returned if scan is successful and the next
     scan will start immediately after this one. No terminator is con-
     sidered since the scan is well defined.
     Nothing is changed if the scan is unsuccessful.
     @param     this    object pointer
     @param     ppStrA  Optional pointer to where the identifier value will be returned
     @return    If successful, true and *pValue contains a pointer to the identifier,
                otherwise false.
     @warning   The identifier returned iw only valid until the next scan method is
                called. You should copy it out if you want it retained.
     */
    bool            LAScan_ScanCIdentifier (
        LASCAN_DATA     *this,
        const
        uint8_t         **ppStrA
    );


    /*!
     Scan a C-like UTF-8 signed decimal value such as:
                [+-]? ('0' ('x' | 'X') [0-9a-fA-F]*)      ** Hexadecimal **
            |   [+-]? ('0' [0-7]*)                        ** Octal **
            |   [+-]? [1-9][0-9]+)                        ** Decimal **
     The value scanned is returned if scan is successful and the next
     scan will start immediately after this one. No terminator is con-
     sidered since the scan is well defined.
     Nothing is changed if the scan is unsuccessful.
     @param     this    object pointer
     @param     pValue      Optional pointer to where value will be returned
     @return    If successful, true and *pValue contains the amount converted,
                otherwise false.
     */
    bool            LAScan_ScanCInteger32 (
        LASCAN_DATA     *this,
        int32_t         *pValue
    );


    /*!
     Scan a C-like UTF-8 unsigned decimal value such as:
                ('0' ('x' | 'X') [0-9a-fA-F]*)      ** Hexadecimal **
            |   ('0' [0-7]*)                        ** Octal **
            |   [1-9][0-9]+)                        ** Decimal **
     The value scanned is returned if scan is successful and the next
     scan will start immediately after this one. No terminator is con-
     sidered since the scan is well defined.
     Nothing is changed if the scan is unsuccessful.
     @param     this    object pointer
     @param     pValue      Optional pointer to where value will be returned
     @return    If successful, true and *pValue contains the amount converted,
                otherwise false.
     */
    bool            LAScan_ScanCUnsigned32 (
        LASCAN_DATA     *this,
        uint32_t        *pValue
    );


    ERESULT         LAScan_Setup (
        LASCAN_DATA     *this,
        int32_t         (*pInputAdvance)(OBJ_ID, uint16_t, TOKEN_FIELDS *),
        int32_t         (*pInputLookAhead)(OBJ_ID, uint16_t, TOKEN_FIELDS *),
        OBJ_ID          pInputObj
    );


    /*!
     Skip over White-space moving the scan point past the white-space.
     @param     this    object pointer
     @return    If successful, true, otherwise false.
     */
    bool            LAScan_SkipWS (
        LASCAN_DATA     *this
    );


#ifdef  LASCAN_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = LAScan_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     LAScan_ToJson (
        LASCAN_DATA   *this
    );
#endif


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
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     LAScan_ToDebugString (
        LASCAN_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* LASCAN_H */

