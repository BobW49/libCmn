// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Command Parser and Executor (Cmds) Header
//****************************************************************
/*
 * Program
 *          Command Parser and Executor (Cmds)
 * Purpose
 *          This object accepts command requests, creates the
 *          appropriate command processor and optionally sup-
 *          ports undo/redo. Command requests are made in
 *          textual format.  It is assumed that they come from
 *          a file or keyboard, but that processing is extraneous
 *          to this object.  The command input is parsed using
 *          CmdUtl and then delegated to the appropriate command
 *          processor (CmdProc).
 *
 *          Part of command process support is the ability to
 *          undo/redo any command. If this is to be implemented,
 *          there are generally two techniques that can be used.
 *          The first is to implement the command with a "not"
 *          command name and implement that as a separate
 *          command. The other way is to implement a "not" flag
 *          within the command that tells it to undo/redo itself.
 *
 *          In the first case above, the undo/redo stacks need
 *          to be implemented within this object.  The latter
 *          technique allows the undo/redo stacks to be im-
 *          plemented within the command process object.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  08/30/2022 Generated
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





//#define   CMDS_IS_IMMUTABLE     1
//#define   CMDS_JSON_SUPPORT     1
//#define   CMDS_SINGLETON        1
//#define       CMDS_MSGS   1
//#define   CMDS_SUPER_DEFINED     1


#include        <cmn_defs.h>
#include        <AStr.h>
#include        <Cmd.h>
#ifdef  CMDS_SUPER_DEFINED
#include        <obj.h>
#endif
#include        <NodeList.h>


#ifndef         CMDS_H
#define         CMDS_H





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct Cmds_data_s  CMDS_DATA;          // Inherits from obj
    typedef struct Cmds_class_data_s CMDS_CLASS_DATA;  // Inherits from obj

    typedef struct Cmds_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        //obj_VTBL    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Cmds_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(CMDS_DATA *);
    } CMDS_VTBL;

    typedef struct Cmds_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Cmds_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(CMDS_DATA *);
    } CMDS_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  CMDS_SINGLETON
    CMDS_DATA *     Cmds_Shared (
        void
    );

    void            Cmds_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to Cmds object if successful, otherwise OBJ_NIL.
     */
    CMDS_DATA *     Cmds_Alloc (
        void
    );
    
    
    OBJ_ID          Cmds_Class (
        void
    );
    
    
    CMDS_DATA *     Cmds_New (
        void
    );
    
    
#ifdef  CMDS_JSON_SUPPORT
    CMDS_DATA *     Cmds_NewFromJsonString (
        ASTR_DATA       *pString
    );

    CMDS_DATA *     Cmds_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

#ifdef CMDS_MSGS
    /*! @property   Messages
        Allows information and warning messages to be issued.
     */
    bool            Cmds_setMsgs (
        CMDS_DATA       *this,
        void            (*pMsgInfo)(OBJ_ID, const char *, ...),
        void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...),
        OBJ_ID          pObj
    );
#endif


    OBJ_DATA *      Cmds_getSuper (
        CMDS_DATA       *this
    );


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Add a command from the given data. Either the long name, the
     short bame or both must be present.
     @param     this        object pointer
     @param     pLongName   Optional long command name
     @param     shortName   Optional short command name charactrr
     @param     pDesc       Optional string pointer that describes
                            the command and its syntax
     @param     pClass      Class object pointer for the command
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Cmds_AddData (
        CMDS_DATA       *this,
        char            *pLongName,
        W32CHR_T        shortName,
        char            *pDesc,
        OBJ_ID          *pClass
    );


    /*!
     Add a command from the data in its class object. If the Cmd
     Class supports QueryInfo() for OBJ_QUERYINFO_TYPE_DATA_PTR
     and names, "Desc", "LongName" and "ShortName" that can be
     used by the Cmds object as in AddData() above.
     @param     this    object pointer
     @param     pClass  class object pointer for command
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Cmds_AddObj (
        CMDS_DATA       *this,
        OBJ_ID          *pClass
    );


    /*!
     Create an enumerator for the command array.
     @param     this    Object Pointer
     @return    If successful, an ENUM object is returned.  Otherwise,
                 OBJ_NIL.
     @warning   Remember to release the returned ENUM object.
     */
    NODEENUM_DATA * Cmds_Enum (
         CMDS_DATA      *this
    );


    /*!
     Parse and eexecute the given command.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Cmds_Exec (
        CMDS_DATA       *this,
        ASTR_DATA       *pCmd
    );


    /*!
     Find the first occurrence of a node in the array by either
     the short or long name. The long name, short name or both
     can be specified, but one of them must be present.
     @param     this        Object Pointer
     @param     shortName   Short naame character or 0
     @param     pLongNameA  Long name utf-8 pointer or NULL
     @return    If successful, a Node pointer is returned; otherwise
                an OBJ_NIL is returned.
     */
    NODE_DATA *     Cmds_Find (
       CMDS_DATA        *this,
        W32CHR_T        shortName,
        const
        char            *pLongNameA
    );


    CMDS_DATA *     Cmds_Init (
        CMDS_DATA       *this
    );


    /*!
     Redo a previously undone command.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Cmds_Redo (
        CMDS_DATA       *this
    );


    /*!
     Sort the Node array for faster searching.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Cmds_Sort (
        CMDS_DATA       *this
    );


#ifdef  CMDS_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Cmds_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Cmds_ToJson (
        CMDS_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Cmds_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Cmds_ToDebugString (
        CMDS_DATA       *this,
        int             indent
    );
    
    
    /*!
     Undo a previously executed command.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Cmds_Undo (
        CMDS_DATA       *this
    );



    
#ifdef  __cplusplus
}
#endif

#endif  /* CMDS_H */

