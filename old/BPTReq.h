// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//    B-Plus Tree Internal Request Processor (BPTReq) Header
//****************************************************************

/*
 * Program
 *          B-Plus Tree Internal Request Processor (BPTReq)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate BPTReq to run things without complications
 *          of interfering with the main BPTReq. A BPTReq may be 
 *          called a BPTReq on other O/S's.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  01/31/2023 Generated
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
        OBJ_IDENT_BPTREQ,         //  B-Plus Tree Internal Request Processor
        OBJ_IDENT_BPTREQ_CLASS,
    The following should be added to the appropriate objects.json.txt
    or program.json.txt file:
        {name:"BPTReq",  desc:"B-Plus Tree Internal Request Processor"},
 *----------------------------------------------------------------*/



//#define   BPTREQ_IS_IMMUTABLE     1
//#define   BPTREQ_JSON_SUPPORT     1
//#define   BPTREQ_SINGLETON        1
//#define       BPTREQ_MSGS   1
//#define   BPTREQ_SUPER_DEFINED     1


#include        <cmn_defs.h>
#include        <AStr.h>
#include        <BPT.h>
#ifdef  BPTREQ_SUPER_DEFINED
#include        <obj.h>
#endif


#ifndef         BPTREQ_H
#define         BPTREQ_H





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct BPTReq_data_s  BPTREQ_DATA;          // Inherits from obj
    typedef struct BPTReq_class_data_s BPTREQ_CLASS_DATA;  // Inherits from obj

    typedef struct BPTReq_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        //obj_VTBL    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in BPTReq_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(BPTREQ_DATA *);
    } BPTREQ_VTBL;

    typedef struct BPTReq_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in BPTReq_object.c.
        // Properties:
        // Methods:
        BPTREQ_DATA *(*pNew)(void);
        //bool        (*pIsEnabled)(BPTREQ_DATA *);
    } BPTREQ_CLASS_VTBL;


    typedef enum BPT_request_e {
        BPT_REQUEST_UNKNOWN=0,
        BPT_REQUEST_NEW_LBN,              // Return a new Logical Block Number not
        //                                  // currently allocated.
        //                                  //  obj   - ignored
        //                                  //  parm1 - ignored
        //                                  //  parm2 - ignored
        //                                  //  parm3 - lbn return pointer (uint32_t *)
        BPT_REQUEST_NEW_INDEX,            // Return a new empty index block.
        BPT_REQUEST_NEW_LEAF,             // Return a new empty leaf block.
        BPT_REQUEST_PARENT,               // Get Parent after a search
        BPT_REQUEST_READ,                 // Read a buffer from disk
        //                                  //  obj   - object requesting write
        //                                  //        (lbn and block are gotten from vtbl)
        //                                  //  parm1 - ignored
        //                                  //  parm2 - ignored
        //                                  //  parm3 - ignored
        BPT_REQUEST_SPLIT,                // A Block Split occurred so
        //                                  // handle the index block update(s)
        //                                  //  obj   - Left Block  (index or leaf)
        //                                  //  parm1 - Right Block (index or leaf)
        //                                  //  parm2 - ignored
        //                                  //  parm3 - ignored
        BPT_REQUEST_SET_TAIL,             // Change Data Tail to given block.
        //                                  //  obj   - object requesting tail
        //                                  //        (lbn is gotten from vtbl)
        //                                  //  parm1 - ignored
        //                                  //  parm2 - ignored
        //                                  //  parm3 - ignored
        BPT_REQUEST_WRITE,                // Write a buffer to disk.
        //                                  //  obj   - object requesting write
        //                                  //        (lbn and block are gotten from vtbl)
        //                                  //  parm1 - ignored
        //                                  //  parm2 - ignored
        //                                  //  parm3 - ignored
    } BPT_REQUEST;





    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  BPTREQ_SINGLETON
    BPTREQ_DATA *   BPTReq_Shared (
        void
    );

    void            BPTReq_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to BPTReq object if successful, otherwise OBJ_NIL.
     */
    BPTREQ_DATA *   BPTReq_Alloc (
        void
    );
    
    
    OBJ_ID          BPTReq_Class (
        void
    );
    
    
    BPTREQ_DATA *   BPTReq_New (
        void
    );
    
    
#ifdef  BPTREQ_JSON_SUPPORT
    BPTREQ_DATA *   BPTReq_NewFromJsonString (
        ASTR_DATA       *pString
    );

    BPTREQ_DATA *   BPTReq_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

#ifdef BPTREQ_MSGS
    /*! @property   Messages
        Allows information and warning messages to be issued.
     */
    bool            BPTReq_setMsgs (
        BPTREQ_DATA     *this,
        void            (*pMsgInfo)(OBJ_ID, const char *, ...),
        void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...),
        OBJ_ID          pObj
    );
#endif


#ifdef  BPTREQ_SUPER_DEFINED
    OBJ_DATA *      BPTReq_getSuper (
        BPTREQ_DATA     *this
    );
#else
    OBJ_DATA *      BPTReq_getSuper (
        BPTREQ_DATA     *this
    );
#endif


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         BPTReq_Disable (
        BPTREQ_DATA     *this
    );


    ERESULT         BPTReq_Enable (
        BPTREQ_DATA     *this
    );

   
    BPTREQ_DATA *   BPTReq_Init (
        BPTREQ_DATA     *this
    );


    bool            BPTReq_IsEnabled (
        BPTREQ_DATA     *this
    );
    
 
#ifdef  BPTREQ_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = BPTReq_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     BPTReq_ToJson (
        BPTREQ_DATA     *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = BPTReq_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     BPTReq_ToDebugString (
        BPTREQ_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* BPTREQ_H */

