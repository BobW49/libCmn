// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//              Source File Location (SrcLoc) Header
//****************************************************************

/*
 * Program
 *          Source File Location (SrcLoc)
 * Purpose
 *          This object provides a location within a source file.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  01/01/2016  Generated
 *  11/25/2019  Changed fileIndex to uint32_t from uint16_t to make
 *              it compatible with szTbl.
 *  12/25/2022 Regenerated and changed File Name Index to the actual
 *              file path which is saved in szTbl.
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
        OBJ_IDENT_SRCLOC,         //  Source File Location
        OBJ_IDENT_SRCLOC_CLASS,
    The following should be added to the appropriate objects.json.txt
    or program.json.txt file:
        {name:"SrcLoc",  desc:"Source File Location"},
 *----------------------------------------------------------------*/



//#define   SRCLOC_IS_IMMUTABLE     1
#define   SRCLOC_JSON_SUPPORT       1
//#define   SRCLOC_SINGLETON        1
//#define       SRCLOC_MSGS   1
//#define   SRCLOC_SUPER_DEFINED     1


#include        <cmn_defs.h>
#include        <AStr.h>
#ifdef  SRCLOC_SUPER_DEFINED
#include        <obj.h>
#endif


#ifndef         SRCLOC_H
#define         SRCLOC_H





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct SrcLoc_data_s  SRCLOC_DATA;          // Inherits from obj
    typedef struct SrcLoc_class_data_s SRCLOC_CLASS_DATA;  // Inherits from obj

    typedef struct SrcLoc_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        //obj_VTBL    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in SrcLoc_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SRCLOC_DATA *);
    } SRCLOC_VTBL;

    typedef struct SrcLoc_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in SrcLoc_object.c.
        // Properties:
        // Methods:
        SRCLOC_DATA *(*pNew)(void);
        //bool        (*pIsEnabled)(SRCLOC_DATA *);
    } SRCLOC_CLASS_VTBL;


//  SRCLOC size must be a multiple of 8.
#if !defined(__arm64__)
#pragma pack(push, 1)
#endif
    typedef struct SrcLoc_s    {
        const
        char            *pFileNameA;        // File Name (stored in szTbl)
        //                                  // Note: If zero, then the entire
        //                                  //      location is ignored.
        uint16_t        colNo;              // Source Input Column Number (relative to 1)
        //                                  // If empty line, colNo is 0.
        uint16_t        unused16;
        uint32_t        lineNo;             // Source Input Line Number (relative to 0)
        uint32_t        unused32;
        int64_t         offset;             // File Offset (zero based)
    } SRCLOC;
#if !defined(__arm64__)
#pragma pack(pop)
#endif
    
    


    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  SRCLOC_SINGLETON
    SRCLOC_DATA *   SrcLoc_Shared (
        void
    );

    void            SrcLoc_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to SrcLoc object if successful, otherwise OBJ_NIL.
     */
    SRCLOC_DATA *   SrcLoc_Alloc (
        void
    );
    
    
    OBJ_ID          SrcLoc_Class (
        void
    );
    
    
    SRCLOC_DATA *   SrcLoc_New (
        void
    );
    
    
    SRCLOC_DATA *   SrcLoc_NewFLC (
        const
        char            *pFileNameA,
        int64_t         offset,
        uint32_t        lineNo,
        uint16_t        colNo
    );


    SRCLOC_DATA *   SrcLoc_NewSrcLoc (
        SRCLOC          *pSrc
    );


#ifdef  SRCLOC_JSON_SUPPORT
    SRCLOC_DATA *   SrcLoc_NewFromJsonString (
        ASTR_DATA       *pString
    );

    SRCLOC_DATA *   SrcLoc_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint16_t        SrcLoc_getColNo (
        SRCLOC_DATA     *this
    );

    bool            SrcLoc_setColNo (
        SRCLOC_DATA     *this,
        uint16_t        value
    );


    const
    char *          SrcLoc_getFileName (
        SRCLOC_DATA     *this
    );

    bool            SrcLoc_setFileName (
        SRCLOC_DATA     *this,
        const
        char            *pValue
    );


    uint32_t        SrcLoc_getLineNo (
        SRCLOC_DATA     *this
    );

    bool            SrcLoc_setLineNo (
        SRCLOC_DATA     *this,
        uint32_t        value
    );


#ifdef SRCLOC_MSGS
    /*! @property   Messages
        Allows information and warning messages to be issued.
     */
    bool            SrcLoc_setMsgs (
        SRCLOC_DATA    *this,
        void            (*pMsgInfo)(OBJ_ID, const char *, ...),
        void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...),
        OBJ_ID          pObj
    );
#endif


    int64_t         SrcLoc_getOffset (
        SRCLOC_DATA     *this
    );

    bool            SrcLoc_setOffset (
        SRCLOC_DATA     *this,
        int64_t         value
    );


    SRCLOC *        SrcLoc_getSrc (
        SRCLOC_DATA     *this
    );


#ifdef  SRCLOC_SUPER_DEFINED
    OBJ_DATA *      SrcLoc_getSuper (
        SRCLOC_DATA     *this
    );
#else
    OBJ_DATA *      SrcLoc_getSuper (
        SRCLOC_DATA     *this
    );
#endif


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before
     a copy of the object is performed.
     Example:
     @code
        ERESULT eRc = SrcLoc_Assign(this,pOther);
     @endcode
     @param     this    object pointer
     @param     pOther  a pointer to another SRCLOC object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT         SrcLoc_Assign (
        SRCLOC_DATA     *this,
        SRCLOC_DATA     *pOther
    );


    /*!
     Compare the two provided objects.
     @return    0  if this == other
                <0 if this < other
                >0 if this > other
     */
    int             SrcLoc_Compare (
        SRCLOC_DATA     *this,
        SRCLOC_DATA     *pOther
    );


    /*!
     Copy the current object creating a new object.
     Example:
     @code
        SrcLoc      *pCopy = SrcLoc_Copy(this);
     @endcode
     @param     this    object pointer
     @return    If successful, a SRCLOC object which must be
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    SRCLOC_DATA *     SrcLoc_Copy (
        SRCLOC_DATA       *this
    );

   
    SRCLOC_DATA *     SrcLoc_Init (
        SRCLOC_DATA       *this
    );


#ifdef  SRCLOC_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = SrcLoc_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     SrcLoc_ToJson (
        SRCLOC_DATA     *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = SrcLoc_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     SrcLoc_ToDebugString (
        SRCLOC_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* SRCLOC_H */

