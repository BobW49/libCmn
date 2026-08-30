// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          16-bit Variable Sized Tuples (Tuple16) Header
//****************************************************************

/*
 * Program
 *          16-bit Variable Sized Tuples (Tuple16)
 * Purpose
 *          This object facilitates creating and manipulating 16-bit
 *          Tuples based on the structures defined below. It was designed
 *          to simply wrap the Tuple when it's manipulation is needed.
 *          Tuples can be grouped with ptrArray. However, this object
 *          can be used in other groups such as ObjArray if needed.
 *
 *          A tuple consists of a base segment which has a user defined
 *          operator/type and control information. Optionally, following
 *          the base segment, there are zero or more data segments which
 *          each have their own operator/type as well as the associated
 *          data. It is imperative that the operator/type for the data
 *          segments identifies the type of data within the segment.
 *
 *          All tuples must be freed with mem_Free() if they are removed
 *          from this object and are used standalone. Any tuple connected
 *          with this object will automatically be freed when the object
 *          is released to a use count of zero.
 *
 *          The maximum length of any tupple is 65535 (ie 16-bit unsigned
 *          length).
 * Remarks
 *  1.      No objects stored in segments are retained. Therefore, it is
 *          important that they be retained in some other object which
 *          will be released after this tuple.
 *
 * History
 *  01/28/2023 Generated
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
        OBJ_IDENT_TUPLE16,         //  16-bit Variable Sized Tuples
        OBJ_IDENT_TUPLE16_CLASS,
    The following should be added to the appropriate objects.json.txt
    or program.json.txt file:
        {name:"Tuple16",  desc:"16-bit Variable Sized Tuples"},
 *----------------------------------------------------------------*/



//#define   TUPLE16_IS_IMMUTABLE     1
//#define   TUPLE16_JSON_SUPPORT     1
//#define   TUPLE16_SINGLETON        1
//#define       TUPLE16_MSGS   1
//#define   TUPLE16_SUPER_DEFINED     1


#include        <cmn_defs.h>
#include        <AStr.h>
#ifdef  TUPLE16_SUPER_DEFINED
#include        <obj.h>
#endif
#include        <Opcode.h>
#include        <Sym.h>
#include        <Token.h>


#ifndef         TUPLE16_H
#define         TUPLE16_H





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct Tuple16_data_s  TUPLE16_DATA;          // Inherits from obj
    typedef struct Tuple16_class_data_s TUPLE16_CLASS_DATA;  // Inherits from obj

    typedef struct Tuple16_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        //obj_VTBL    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Tuple16_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(TUPLE16_DATA *);
    } TUPLE16_VTBL;

    typedef struct Tuple16_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Tuple16_object.c.
        // Properties:
        // Methods:
        TUPLE16_DATA *(*pNew)(void);
        //bool        (*pIsEnabled)(TUPLE16_DATA *);
    } TUPLE16_CLASS_VTBL;


#include        <Tuple16_Type.h>

    /*! A Tuple consists of a Base Segment which includes zero or more
        segments. Segment is the defining structure of the list. It is a recursive
        definition. In that sub-segments can be in the "data" portion of
        the structure. All other segment types must adher to this layout.
     */
    typedef struct Tuple16_Segment_s {
        uint16_t            segLen;         // Segment length
        uint8_t             type;           // Segment Type (see Tuple16_Type.h)
        uint8_t             op;             // Segment Operator
        uint8_t             data[0];
    } TUPLE16_SEGMENT;

    typedef struct Tuple16_Segment_Base_s {
        uint16_t            segLen;         // Base Segment length
        uint8_t             type;           // Segment Type - TUPLE16_TYPE_BASE
        uint8_t             op;             // Segment Operator
        uint16_t            alloc;          // Total Allocated Base Segment length
        //                                  // including sub-segments
        uint16_t            cTuples;        // Number of Segments
        TUPLE16_SEGMENT     tuples[0];
    } TUPLE16_SEGMENT_BASE;


    // Specific Tuple Types
    // Note: Indicated types are suggested.
    typedef struct Tuple16_Double_s {
        uint16_t            segLen;         // Segment length - sizeof(TUPLE16_DOUBLE)
        uint8_t             type;           // Segment Type - TUPLE16_TYPE_DOUBLE
        uint8_t             op;             // Segment Operator
        double              data;
    } TUPLE16_DOUBLE;

    typedef struct Tuple16_Integer8_s {
        uint16_t            segLen;         // Segment length - sizeof(TUPLE16_INTEGER8)
        uint8_t             type;           // Segment Type - TUPLE16_TYPE_INT8
        uint8_t             op;             // Segment Operator
        int8_t              data;
    } TUPLE16_INTEGER8;

    typedef struct Tuple16_Integer16_s {
        uint16_t            segLen;         // Segment length - sizeof(TUPLE16_INTEGER16)
        uint8_t             type;           // Segment Type - TUPLE16_TYPE_INT16
        uint8_t             op;             // Segment Operator
        int16_t             data;
    } TUPLE16_INTEGER16;

    typedef struct Tuple16_Integer32_s {
        uint16_t            segLen;         // Segment length - sizeof(TUPLE16_INTEGER32)
        uint8_t             type;           // Segment Type - TUPLE16_TYPE_INT32
        uint8_t             op;             // Segment Operator
        int32_t             data;
    } TUPLE16_INTEGER32;

    typedef struct Tuple16_Integer64_s {
        uint16_t            segLen;         // Segment length - sizeof(TUPLE16_INTEGER64)
        uint8_t             type;           // Segment Type - TUPLE16_TYPE_INT64
        uint8_t             op;             // Segment Operator
        int64_t             data;
    } TUPLE16_INTEGER64;

    typedef struct Tuple16_Object_s {
        uint16_t            segLen;         // Segment length - sizeof(TUPLE16_POINTER)
        uint8_t             type;           // Segment Type - TUPLE16_TYPE_OBJECT
        uint8_t             op;             // Segment Operator
        OBJ_ID              pData;
    } TUPLE16_OBJECT;

    typedef struct Tuple16_Opcode_s {
        uint16_t            segLen;         // Segment length - sizeof(TUPLE16_POINTER)
        uint8_t             type;           // Segment Type - TUPLE16_TYPE_OPCODE
        uint8_t             op;             // Segment Operator
        OPCODE_DATA         *pData;
    } TUPLE16_OPCODE;

    typedef struct Tuple16_Pointer_s {
        uint16_t            segLen;         // Segment length - sizeof(TUPLE16_POINTER)
        uint8_t             type;           // Segment Type - TUPLE16_TYPE_PTR
        uint8_t             op;             // Segment Operator
        void                *pData;
    } TUPLE16_POINTER;

    typedef struct Tuple16_Symbol_s {
        uint16_t            segLen;         // Segment length - sizeof(TUPLE16_SYMBOL)
        uint8_t             type;           // Segment Type - TUPLE16_TYPE_SYMBOL
        uint8_t             op;             // Segment Operator
        SYM_DATA            *pData;
    } TUPLE16_SYMBOL;

    typedef struct Tuple16_Token_s {
        uint16_t            segLen;         // Segment length - sizeof(TUPLE16_TOKEN)
        uint8_t             type;           // Segment Type - TUPLE16_TYPE_TOKEN
        uint8_t             op;             // Segment Operator
        TOKEN_FIELDS        data;
    } TUPLE16_TOKEN;

    typedef struct Tuple16_UTF8_s {
        uint16_t            segLen;         // Segment length - sizeof(TUPLE16_UTF8) + len(data)
        uint8_t             type;           // Segment Type - TUPLE16_TYPE_UTF8
        uint8_t             op;             // Segment Operator
        uint16_t            dataLen;        // data length in bytes
        uint8_t             data[0];
    } TUPLE16_UTF8;

    typedef struct Tuple16_UTF32_s {
        uint16_t            segLen;         // Segment length - sizeof(TUPLE16_UTF32)
        //                                  //                  + (len(data) * 4)
        uint8_t             type;           // Segment Type - TUPLE16_TYPE_UTF32
        uint8_t             op;             // Segment Operator
        uint16_t            dataLen;        // data length in bytes
        int32_t             data[0];
    } TUPLE16_UTF32;



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  TUPLE16_SINGLETON
    TUPLE16_DATA *  Tuple16_Shared (
        void
    );

    void            Tuple16_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to Tuple16 object if successful, otherwise OBJ_NIL.
     */
    TUPLE16_DATA *  Tuple16_Alloc (
        void
    );
    
    
    OBJ_ID          Tuple16_Class (
        void
    );
    
    
    TUPLE16_DATA *  Tuple16_New (
        void
    );
    
    TUPLE16_DATA *  Tuple16_NewBase (
        uint16_t        op
    );


#ifdef  TUPLE16_JSON_SUPPORT
    TUPLE16_DATA *  Tuple16_NewFromJsonString (
        ASTR_DATA       *pString
    );

    TUPLE16_DATA *  Tuple16_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif


    const
    char *          Tuple16_TypeToName (
        uint32_t        value
    );



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

#ifdef TUPLE16_MSGS
    /*! @property   Messages
        Allows information and warning messages to be issued.
     */
    bool            Tuple16_setMsgs (
        TUPLE16_DATA    *this,
        void            (*pMsgInfo)(OBJ_ID, const char *, ...),
        void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...),
        OBJ_ID          pObj
    );
#endif


#ifdef  TUPLE16_SUPER_DEFINED
    OBJ_DATA *      Tuple16_getSuper (
        TUPLE16_DATA    *this
    );
#else
    OBJ_DATA *      Tuple16_getSuper (
        TUPLE16_DATA    *this
    );
#endif


    TUPLE16_SEGMENT_BASE *
                    Tuple16_getTuple (
        TUPLE16_DATA    *this
    );




    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Append a new segment to the tuple.
     @param     this    object pointer
     @param     op      Segment Operator/Type
                        (0 == Use default type from TUPLE16_TYPES)
     @param     data    pointer to data to copied into the segment.
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Tuple16_AppendInteger8 (
        TUPLE16_DATA    *this,
        uint8_t         op,
        int8_t          data
    );

    ERESULT         Tuple16_AppendInteger16 (
        TUPLE16_DATA    *this,
        uint8_t         op,
        int16_t         data
    );

    ERESULT         Tuple16_AppendInteger32 (
        TUPLE16_DATA    *this,
        uint8_t         op,
        int32_t         data
    );

    ERESULT         Tuple16_AppendInteger64 (
        TUPLE16_DATA    *this,
        uint8_t         op,
        int64_t         data
    );

    ERESULT         Tuple16_AppendObject (
        TUPLE16_DATA    *this,
        uint8_t         op,
        OBJ_ID          pData
    );

    ERESULT         Tuple16_AppendOpcode (
        TUPLE16_DATA    *this,
        uint8_t         op,
        OPCODE_DATA     *pData
    );

    ERESULT         Tuple16_AppendPointer (
        TUPLE16_DATA    *this,
        uint8_t         op,
        void            *pData
    );

    ERESULT         Tuple16_AppendSymbol (
        TUPLE16_DATA    *this,
        uint8_t         op,
        SYM_DATA        *pData
    );

    ERESULT         Tuple16_AppendToken (
        TUPLE16_DATA    *this,
        uint8_t         op,
        TOKEN_FIELDS    *pData
    );


    ERESULT         Tuple16_DeleteSegment (
        TUPLE16_DATA    *this,
        uint8_t         index
    );

   
    TUPLE16_DATA *  Tuple16_Init (
        TUPLE16_DATA    *this
    );


    /*!
     Insert a new segment into the tuple.
     @param     this    object pointer
     @param     index   Segment Index to insert before (relative to 1)
     @param     op      Segment Operator/Type
                        (0 == Use default type from TUPLE16_TYPES)
     @param     data    pointer to data to copied into the segment.
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Tuple16_InsertInteger8 (
        TUPLE16_DATA    *this,
        uint8_t         index,
        uint8_t         op,
        int8_t          data
    );

    ERESULT         Tuple16_InsertInteger16 (
        TUPLE16_DATA    *this,
        uint8_t         index,
        uint8_t         op,
        int16_t         data
    );

    ERESULT         Tuple16_InsertInteger32 (
        TUPLE16_DATA    *this,
        uint8_t         index,
        uint8_t         op,
        int32_t         data
    );

    ERESULT         Tuple16_InsertInteger64 (
        TUPLE16_DATA    *this,
        uint8_t         index,
        uint8_t         op,
        int64_t         data
    );

    ERESULT         Tuple16_InsertOpcode (
        TUPLE16_DATA    *this,
        uint8_t         index,
        uint8_t         op,
        OPCODE_DATA     *pData
    );

    ERESULT         Tuple16_InsertPointer (
        TUPLE16_DATA    *this,
        uint8_t         index,
        uint8_t         op,
        void            *pData
    );

    ERESULT         Tuple16_InsertSymbol (
        TUPLE16_DATA    *this,
        uint8_t         index,
        uint8_t         op,
        SYM_DATA        *pData
    );

    ERESULT         Tuple16_InsertToken (
        TUPLE16_DATA    *this,
        uint8_t         index,
        uint8_t         op,
        TOKEN_FIELDS    *pData
    );


    bool            Tuple16_IsEnabled (
        TUPLE16_DATA    *this
    );
    
 
    /*!
     Return the address of a segment within the tuple.
     @param     this    object pointer
     @param     index   Segment Index to insert before (relative to 1)
     @return    if successful, segment address.  Otherwise, NULL.
     */
    TUPLE16_SEGMENT * Tuple16_Segment (
        TUPLE16_DATA    *this,
        uint8_t         index
    );


#ifdef  TUPLE16_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Tuple16_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Tuple16_ToJson (
        TUPLE16_DATA    *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Tuple16_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Tuple16_ToDebugString (
        TUPLE16_DATA    *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* TUPLE16_H */

