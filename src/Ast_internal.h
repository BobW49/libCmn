// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//              Abstract Syntax Tree (Ast) Internal Header
//****************************************************************

/* 
 * File:   Ast_internal.h
 *  Generated 02/04/2023 09:41:47
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




#include        <Ast.h>
#ifdef  AST_SUPER_DEFINED
#include        <Blocks_internal.h>
#endif
#include        <JsonIn.h>
#include        <ptrArray.h>


#ifndef AST_INTERNAL_H
#define AST_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif


typedef struct Ast_bfs_s {
    AST_ENTRY       *pEntry;
    uint32_t        level;
} AST_BFS;


typedef struct  Ast_visit_s {
    // Visit the node associated with pRcd;
    void            (*pVisitor)(
        OBJ_ID          ,               // Object supplied below
        AST_DATA        *,              // Our Tree
        AST_ENTRY       *,              // Current Node
        uint32_t        ,               // Indent
        uint32_t        ,               // level
        void            *               // Other area pointer
    );
    OBJ_ID          pObjectVisit;
    // Optionally execute this before descending in the child chain.
    void            (*pChildOpen)(
        OBJ_ID          ,               // Object supplied below
        AST_DATA        *,              // Our Tree
        AST_ENTRY       *,              // Current Node
        uint32_t        ,               // Indent
        uint32_t        ,               // level
        void            *               // Other area pointer
    );
    OBJ_ID          pObjectOpen;
    // Optionally execute this after descending in the child chain.
    void            (*pChildClose)(
        OBJ_ID          ,               // Object supplied below
        AST_DATA        *,              // Our Tree
        AST_ENTRY       *,              // Current Node
        uint32_t        ,               // Indent
        uint32_t        ,               // level
        void            *               // Other area pointer
    );
    OBJ_ID          pObjectClose;
    void            *pOther;
    uint32_t        indent;
    uint32_t        level;
    uint32_t        type;               // Scan Type
#define AST_VISIT_TYPE_EXTERNAL     0        // External Visitor
#define AST_VISIT_TYPE_INTERNAL     1        // Internal Visitor
    uint32_t        state;              // Scan Type
#define AST_VISIT_STATE_DOWN_LEFT   1
#define AST_VISIT_STATE_DOWN_RIGHT  2
#define AST_VISIT_STATE_UP_LEFT     3
#define AST_VISIT_STATE_UP_RIGHT    4
} AST_VISIT;





    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------


#if !defined(__arm64__)
#pragma pack(push, 1)
#endif
struct Ast_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
#ifdef  AST_SUPER_DEFINED
    BLOCKS_DATA  super;
#else
    OBJ_DATA        super;
#endif
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    PTRARRAY_DATA   *pStk;
    AST_ENTRY       *pRoot;
    AST_ENTRY       *pClose;
    AST_ENTRY       *pOpen;
    int16_t         typeClose;
    int16_t         typeOpen;

#ifdef   AST_MSGS
    // Informational and Warning Log Messages
    void            (*pMsgInfo)(OBJ_ID, const char *, ...);
    void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...);
    OBJ_ID          pMsgObj;
#endif
    const
    char *          (*pClassToName)(int32_t);
};
#if !defined(__arm64__)
#pragma pack(pop)
#endif

    extern
    struct Ast_class_data_s  Ast_ClassObj;

    extern
    const
    AST_VTBL         Ast_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  AST_SINGLETON
    AST_DATA *     Ast_getSingleton (
        void
    );

    bool            Ast_setSingleton (
     AST_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  AST_SUPER_DEFINED
    BLOCKS_DATA *  Ast_getSuper (
        AST_DATA     *this
    );
#else
    OBJ_DATA *  Ast_getSuper (
        AST_DATA     *this
    );
#endif


    OBJ_IUNKNOWN *  Ast_getSuperVtbl (
        AST_DATA     *this
    );


    ERESULT         Ast_Assign (
        AST_DATA    *this,
        AST_DATA    *pOther
    );


    AST_DATA *       Ast_Copy (
        AST_DATA     *this
    );


    void            Ast_Dealloc (
        OBJ_ID          objId
    );


    AST_DATA *     Ast_DeepCopy (
        AST_DATA       *this
    );


    ASTR_DATA *     Ast_EntryToAStrDebug (
        AST_DATA        *this,
        AST_ENTRY       *pEntry,
        uint16_t        indent
    );


#ifdef  AST_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    AST_DATA *       Ast_ParseJsonObject (
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
    ERESULT         Ast_ParseJsonFields (
        JSONIN_DATA     *pParser,
        AST_DATA     *pObject
    );
#endif


    void *          Ast_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  AST_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Ast_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Ast_ToJson (
        AST_DATA      *this
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
    ERESULT         Ast_ToJsonFields (
        AST_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool            Ast_Validate (
        AST_DATA       *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* AST_INTERNAL_H */

