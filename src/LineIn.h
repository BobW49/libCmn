// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//              File Input - Line at a time (LineIn) Header
//****************************************************************

/*
 * Program
 *          File Input - Line at a time (LineIn)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate LineIn to run things without complications
 *          of interfering with the main LineIn. A LineIn may be 
 *          called a LineIn on other O/S's.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  03/31/2023 Generated
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
        OBJ_IDENT_LINEIN,         //  File Input - Line at a time
        OBJ_IDENT_LINEIN_CLASS,
    The following should be added to the appropriate objects.json.txt
    or program.json.txt file:
        {name:"LineIn",  desc:"File Input - Line at a time"},
 *----------------------------------------------------------------*/



//#define   LINEIN_IS_IMMUTABLE     1
//#define   LINEIN_JSON_SUPPORT     1
//#define   LINEIN_SINGLETON        1
//#define       LINEIN_MSGS   1
#define   LINEIN_SUPER_DEFINED   1


#include        <cmn_defs.h>
#include        <AStr.h>
#ifdef  LINEIN_SUPER_DEFINED
#include        <FileIO.h>
#endif
#include        <LineIndex.h>
#include        <SrcLoc.h>


#ifndef         LINEIN_H
#define         LINEIN_H





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct LineIn_data_s  LINEIN_DATA;          // Inherits from FileIO
    typedef struct LineIn_class_data_s LINEIN_CLASS_DATA;  // Inherits from obj

    typedef struct LineIn_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        //FileIO_VTBL    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in LineIn_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(LINEIN_DATA *);
    } LINEIN_VTBL;

    typedef struct LineIn_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in LineIn_object.c.
        // Properties:
        // Methods:
        LINEIN_DATA *(*pNew)(void);
        //bool        (*pIsEnabled)(LINEIN_DATA *);
    } LINEIN_CLASS_VTBL;

#define LineIn_Close(this,fDelete)      FileIO_Close((FILEIO_DATA *)this,fDelete)
#define LineIn_IsOpen(this)             FileIO_IsOpen((FILEIO_DATA *)this)


    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  LINEIN_SINGLETON
    LINEIN_DATA *   LineIn_Shared (
        void
    );

    void            LineIn_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to LineIn object if successful, otherwise OBJ_NIL.
     */
    LINEIN_DATA *   LineIn_Alloc (
        void
    );
    
    
    OBJ_ID          LineIn_Class (
        void
    );
    
    
    LINEIN_DATA *   LineIn_New (
        void
    );
    
    
#ifdef  LINEIN_JSON_SUPPORT
    LINEIN_DATA *   LineIn_NewFromJsonString (
        ASTR_DATA       *pString
    );

    LINEIN_DATA *   LineIn_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    SRCLOC *        LineIn_getLoc (
        LINEIN_DATA     *this
    );


#ifdef LINEIN_MSGS
    /*! @property   Messages
        Allows information and warning messages to be issued.
     */
    bool            LineIn_setMsgs (
        LINEIN_DATA     *this,
        void            (*pMsgInfo)(OBJ_ID, const char *, ...),
        void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...),
        OBJ_ID          pObj
    );
#endif


#ifdef  LINEIN_SUPER_DEFINED
    FILEIO_DATA *   LineIn_getSuper (
        LINEIN_DATA     *this
    );
#else
    OBJ_DATA *      LineIn_getSuper (
        LINEIN_DATA     *this
    );
#endif


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         LineIn_Disable (
        LINEIN_DATA     *this
    );


    ERESULT         LineIn_Enable (
        LINEIN_DATA     *this
    );

   
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
    );


    LINEIN_DATA *   LineIn_Init (
        LINEIN_DATA     *this
    );


    /*!
     Open an existing file for reading/writing.
     @param     this    object pointer
     @param     pPath   Path object pointer
     @param     fMem    true == open file as memory based,
                        false == disk based
     @return    If successful, ERESULT_SUCCESS; otherwise ERESULT_* error.
     */
    ERESULT         LineIn_Open (
        LINEIN_DATA     *this,
        PATH_DATA       *pPath,
        bool            fMem
    );
    
 
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
    );


#ifdef  LINEIN_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = LineIn_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     LineIn_ToJson (
        LINEIN_DATA     *this
    );
#endif


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
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     LineIn_ToDebugString (
        LINEIN_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* LINEIN_H */

