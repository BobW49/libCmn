// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//     Operator Precedence Parser (OpPrec) Internal Header
//****************************************************************

/* 
 * File:   OpPrec_internal.h
 *  Generated 03/04/2023 08:33:53
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




#include        <OpPrec.h>
#ifdef  OPPREC_SUPER_DEFINED
#include        <obj_internal.h>
#endif
#include        <JsonIn.h>


#ifndef OPPREC_INTERNAL_H
#define OPPREC_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------


#if !defined(__arm64__)
#pragma pack(push, 1)
#endif
struct OpPrec_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
#ifdef  OPPREC_SUPER_DEFINED
    OBJ_DATA        super;
#else
    OBJ_DATA        super;
#endif
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    AST_DATA        *pAst;
    uint16_t        size;           // maximum number of elements
    uint16_t        rsvd16;
#define OP_STACKMAX    16

    // Parser Methods
    /*! Parse the next Operand returning its AST entry which is
        not connected to any other AST entry.  The AST entry should
        include the Token fields information from it's parse. The
        internal parser will take care of connecting the returned
        entry.
     @param     this    Object Pointer given by pObjParse below.
     @param     pAst    Abstract Syntax Tree Object Pointer created
                        within this object
     @return    Return the precedence of an acknowledged binary operator.
                If it is not a known operator, return -1.
     */
    AST_ENTRY *     (*pNextOperand) (OBJ_ID this, AST_DATA *pAst);
    /*! Parse the next Operator returning its Token data if possible.
     @param     this    Object Pointer given by pObjParse below.
     @return    Return the Token Fields if successful; otherwise,
                NULL.
     */
    TOKEN_FIELDS *  (*pNextOperator) (OBJ_ID this);
    /*! Determine the precedence of binary operators given the operator's
        class.
     @param     this    Object Pointer given by pObjParse below.
     @param     cls     Operator Token Class
     @return    Return the precedence of an acknowledged binary operator.
                If it is not a known operator, return -1.
     */
    int32_t         (*pPrecedence) (OBJ_ID this, int32_t cls);
    OBJ_ID          pObjParse;
    /*! Convert a Token class to a displayable name.
     */
    const
    char *          (*pClass2Name) (int32_t cls);


#ifdef   OPPREC_MSGS
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
    struct OpPrec_class_data_s  OpPrec_ClassObj;

    extern
    const
    OPPREC_VTBL         OpPrec_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  OPPREC_SINGLETON
    OPPREC_DATA *     OpPrec_getSingleton (
        void
    );

    bool            OpPrec_setSingleton (
     OPPREC_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  OPPREC_SUPER_DEFINED
    OBJ_DATA *  OpPrec_getSuper (
        OPPREC_DATA     *this
    );
#else
    OBJ_DATA *  OpPrec_getSuper (
        OPPREC_DATA     *this
    );
#endif


    OBJ_IUNKNOWN *  OpPrec_getSuperVtbl (
        OPPREC_DATA     *this
    );


    ERESULT         OpPrec_Assign (
        OPPREC_DATA    *this,
        OPPREC_DATA    *pOther
    );


    OPPREC_DATA *       OpPrec_Copy (
        OPPREC_DATA     *this
    );


    void            OpPrec_Dealloc (
        OBJ_ID          objId
    );


    OPPREC_DATA *     OpPrec_DeepCopy (
        OPPREC_DATA       *this
    );


#ifdef  OPPREC_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    OPPREC_DATA *       OpPrec_ParseJsonObject (
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
    ERESULT         OpPrec_ParseJsonFields (
        JSONIN_DATA     *pParser,
        OPPREC_DATA     *pObject
    );
#endif


    void *          OpPrec_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  OPPREC_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = OpPrec_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     OpPrec_ToJson (
        OPPREC_DATA      *this
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
    ERESULT         OpPrec_ToJsonFields (
        OPPREC_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool            OpPrec_Validate (
        OPPREC_DATA       *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* OPPREC_INTERNAL_H */

