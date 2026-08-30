// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//   Scan an AST for various manipulations (AstScan) Header
//****************************************************************

/*
 * Program
 *          Scan an AST for various manipulations (AstScan)
 * Purpose
 *          This object provides a standardized way of scanning
 *          an AST.
 *
 * Remarks
 *  1.      Remember that when scanning that ASM_CLASS_OPEN and
 *          ASM_CLASS_CLOSE classes may be recognized.
 *
 * History
 *  02/12/2023 Generated
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
        OBJ_IDENT_ASTSCAN,         //  Scan an AST for various manipulations
        OBJ_IDENT_ASTSCAN_CLASS,
    The following should be added to the appropriate objects.json.txt
    or program.json.txt file:
        {name:"AstScan",  desc:"Scan an AST for various manipulations"},
 *----------------------------------------------------------------*/



//#define   ASTSCAN_IS_IMMUTABLE     1
//#define   ASTSCAN_JSON_SUPPORT     1
//#define   ASTSCAN_SINGLETON        1
//#define       ASTSCAN_MSGS   1
//#define   ASTSCAN_SUPER_DEFINED     1


#include        <cmn_defs.h>
#include        <Ast.h>
#include        <AStr.h>
#ifdef  ASTSCAN_SUPER_DEFINED
#include        <obj.h>
#endif


#ifndef         ASTSCAN_H
#define         ASTSCAN_H





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct AstScan_data_s  ASTSCAN_DATA;          // Inherits from obj
    typedef struct AstScan_class_data_s ASTSCAN_CLASS_DATA;  // Inherits from obj

    typedef struct AstScan_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        //obj_VTBL    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in AstScan_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(ASTSCAN_DATA *);
    } ASTSCAN_VTBL;

    typedef struct AstScan_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in AstScan_object.c.
        // Properties:
        // Methods:
        ASTSCAN_DATA *(*pNew)(void);
        //bool        (*pIsEnabled)(ASTSCAN_DATA *);
    } ASTSCAN_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  ASTSCAN_SINGLETON
    ASTSCAN_DATA *  AstScan_Shared (
        void
    );

    void            AstScan_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to AstScan object if successful, otherwise OBJ_NIL.
     */
    ASTSCAN_DATA *  AstScan_Alloc (
        void
    );
    
    
    OBJ_ID          AstScan_Class (
        void
    );
    
    
    ASTSCAN_DATA *  AstScan_New (
        void
    );
    
    /*! Create a new AstScan object with a Preorder
     array set up.
     @param     pTree   Required AST Object Pointer
     @param     pRoot   Required AST Root Pointer
     @return    If successful, an AST object which must be released,
                otherwise OBJ_NIL.
     @warning   Remember to release the returned AST object.
     */
    ASTSCAN_DATA *  AstScan_NewPre (
        AST_DATA        *pTree,
        AST_ENTRY       *pRoot
    );


#ifdef  ASTSCAN_JSON_SUPPORT
    ASTSCAN_DATA *   AstScan_NewFromJsonString (
        ASTR_DATA       *pString
    );

    ASTSCAN_DATA *   AstScan_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    PTRARRAY_DATA * AstScan_getArray (
        ASTSCAN_DATA    *this
    );

    bool            AstScan_setArray (
        ASTSCAN_DATA    *this,
        PTRARRAY_DATA   *pValue
    );


    /*! @property Abstract Syntax Tree (Ast)
     */
    AST_DATA *      AstScan_getAst (
        ASTSCAN_DATA    *this
    );

    bool            AstScan_setAst (
        ASTSCAN_DATA    *this,
        AST_DATA        *pValue
    );


    uint32_t        AstScan_getIndex (
        ASTSCAN_DATA    *this
    );

    bool            AstScan_setIndex (
        ASTSCAN_DATA    *this,
        uint32_t        value
    );


    AST_ENTRY *      AstScan_getRoot (
        ASTSCAN_DATA    *this
    );


    uint32_t        AstScan_getSize (
        ASTSCAN_DATA    *this
    );


    uint32_t        AstScan_getStart (
        ASTSCAN_DATA    *this
    );

    bool            AstScan_setStart (
        ASTSCAN_DATA    *this,
        uint32_t        value
    );


#ifdef  ASTSCAN_SUPER_DEFINED
    OBJ_DATA *      AstScan_getSuper (
        ASTSCAN_DATA    *this
    );
#else
    OBJ_DATA *      AstScan_getSuper (
        ASTSCAN_DATA    *this
    );
#endif


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ASTSCAN_DATA *  AstScan_Init (
        ASTSCAN_DATA    *this
    );


    /*!
     Advance the scan the provided number of nodes.
     @param     this    Object Pointer
     @param     num     The number of entries to advance over
     @return    If successful, the current node, otherwise OBJ_NIL
                and Last Error contains an error reason.
     */
    AST_ENTRY *     AstScan_InputAdvance (
        ASTSCAN_DATA    *this,
        uint32_t        num
    );


    /*!
     Provide the node that is the provided number of nodes ahead of the current
     one without affecting the current index or node.
     @param     this    Object Pointer
     @param     num     The number of entries to look ahead
     @return    If successful, the node in advance of the current one, otherwise
                OBJ_NIL and Last Error contains an error reason.
     */
    AST_ENTRY *     AstScan_InputLookAhead (
        ASTSCAN_DATA    *this,
        uint32_t        num
    );


    /*!
     Look at the next entry to see if it matches the
     given class.
     @param     this    Object Pointer
     @param     cls     An ASM_CLASS_*
     @return    If successful, the entry found; otherwise NULL.
     */
    AST_ENTRY *     AstScan_MatchClass (
        ASTSCAN_DATA    *this,
        int32_t         cls
    );


    /*!
     Look at the next entry to see if it matches one of
     the given classes.
     @param     this    Object Pointer
     @param     pSet    A zero terminated list of ASM_CLASS_* classes
     @return    If successful, the entry found; otherwise NULL.
     */
    AST_ENTRY *     AstScan_MatchClasses (
        ASTSCAN_DATA    *this,
        int32_t         *pSet
    );


    /*!
     Scan forward until an entry matches one of the given classes
     or the end of the array occurs.
     @param     this    Object Pointer
     @param     pSet    A zero terminated list of ASM_CLASS_* classes
     @return    If successful, the entry found; otherwise NULL.
     */
    AST_ENTRY *     AstScan_MatchClassesUntil (
        ASTSCAN_DATA    *this,
        int32_t         *pSet
    );


    /*!
     Reset the scan back to the beginning.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         AstScan_Reset (
        ASTSCAN_DATA    *this
    );


    /*!
     Assuming that this object is connected to a TreeExpr, generate
     the pre-order array and set up this scanner to use it. Pre-order
     is described here, NodeTree_ToLinearizationPre().
     @param     this    object pointer
     @param     pRoot   Root Entry pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         AstScan_SetupPre (
        ASTSCAN_DATA    *this,
        AST_ENTRY       *pRoot
    );


#ifdef  ASTSCAN_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = AstScan_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     AstScan_ToJson (
        ASTSCAN_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = AstScan_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     AstScan_ToDebugString (
        ASTSCAN_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* ASTSCAN_H */

