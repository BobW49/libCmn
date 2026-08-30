// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Command Base (Cmd) Header
//****************************************************************
/*
 * Program
 *          Command Base (Cmd)
 * Purpose
 *          This object provides a standardized command base object
 *          whose responsibility is to provide a uniform interface
 *          for commands and optionally provide undo/redo support.
 *
 *          This is not a standalone object. It is intended to be
 *          inherited with the class methods added as well as the
 *          CMD_EXEC_VTBL methods. If Undo/Redo is not to be used,
 *          then you need not implement those methods.
 *
 *          Undo/Redo is one of the nicest things to implement in
 *          commands that cause changes.  To support this, a change
 *          stack must be maintained which contains the before state
 *          of what is being changed. JSON is easy to implement and
 *          makes saving and restoring state relatively easy. We
 *          define the state stack using NodeList objects so that
 *          the state can be saved in Nodes maybe using JSON AStr's.
 *
 * Remarks
 *  1.      The inheriting class object must support the methods shown in
 *          the class VTBLs, CMD_CLASS_VTBL and CMD_VTBL, shown below.
 *  2.      If the Cmd Class supports QueryInfo() for OBJ_QUERYINFO_TYPE_DATA_PTR
 *          and names, "Desc", "LongName" and "ShortName" that can be
 *          used by the Cmds object.
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





//#define   CMD_IS_IMMUTABLE     1
//#define   CMD_JSON_SUPPORT     1
//#define   CMD_SINGLETON        1
//#define       CMD_MSGS   1
#define   CMD_SUPER_DEFINED     1


#include        <cmn_defs.h>
#include        <AStr.h>
#ifdef  CMD_SUPER_DEFINED
#include        <Node.h>
#endif
#include        <CmdUtl.h>
#include        <NodeList.h>
#include        <Value.h>


#ifndef         CMD_H
#define         CMD_H





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct Cmd_data_s  CMD_DATA;          // Inherits from Node
    typedef struct Cmd_class_data_s CMD_CLASS_DATA;  // Inherits from obj

    /* IMPORTANT: The inheritting class must implement the methods in
                    this struct!
     */
    typedef struct Cmd_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        //obj_VTBL    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Cmd_object.c.
        // Properties:
        // Methods:
        OBJ_ID          (*pGetMisc)(OBJ_ID);
        bool            (*pSetMisc)(OBJ_ID, OBJ_ID);
    } CMD_VTBL;

    /* IMPORTANT: The inheritting class must implement the methods in
                    this struct!
     */
    typedef struct Cmd_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Cmd_object.c.
        // Properties:
        // Methods:
        CMD_DATA        *(*pNew)(void);
        CMDUTL_OPTION   *(*pCmdDef)(void);      // Return option definition for this command itself
        CMDUTL_OPTION   *(*pOptionDefs)(void);  // Return the option definitions for this command
        //                                      //  (NULL terminated list)
    } CMD_CLASS_VTBL;


    // An option must have at a minimum either a short name or a long name. Both
    // may be provided.  CmdUtl_ProcessOption() will correctly handle these
    // three situations.
    // Note - The end of an option table is denoted by a pLongName of NULL
    // and a shortName of 0.
    typedef struct Cmd_option_s {
        char            *pLongName;         // command full name (optional, may be NULL)
        W32CHR_T        shortName;          // command short name (optional, may be '\0')
        // Note - either a long or short name must be specified. Both may be specified.
        CMDUTL_OPTION   *pOptions;          // Pointer to CMDUTL_OPTION list ended with
        //                                  // an entry of NULL in pLongName and 0 in
        //                                  // shortName.
        uint16_t        optSize;            // Option Area Size
        const
        char            *pDesc;             // Command Description
    } CMDPROC_CMD;


    /*!         Execution Interface
     This object is supplied externally and defines the execution
     interface exit points that will be called at the appropriate
     times.
     */
    typedef struct Cmd_Exec_interface_s CMD_EXEC_INTERFACE;

    typedef struct Cmd_Exec_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // All methods must be defined to return bool.
        // Properties:
        // Methods:
        ERESULT     (*pPrsAStr)(CMD_EXEC_INTERFACE *, ASTR_DATA *pStr);
        ERESULT     (*pExec)(CMD_EXEC_INTERFACE *, void *pOptions);
        ERESULT     (*pRedo)(CMD_EXEC_INTERFACE *);
        ERESULT     (*pUndo)(CMD_EXEC_INTERFACE *);
    } CMD_EXEC_VTBL;

    #pragma pack(push, 1)
    struct Cmd_Exec_interface_s    {
        CMD_EXEC_VTBL   *pVtbl;
    };
    #pragma pack(pop)

    //#define Rpg_ExecVtbl(ptr)   ((RPGBASE_EXEC_INTERFACE *)ptr)->pVtbl


    typedef enum Cmd_states_e {
        CMDPROC_STATE_UNKNOWN=0,
        CMDPROC_STATE_COMPLETED,
        CMDPROC_STATE_WORKING,
    } CMD_STATES;





    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  CMD_SINGLETON
    CMD_DATA *      Cmd_Shared (
        void
    );

    void            Cmd_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to Cmd object if successful, otherwise OBJ_NIL.
     */
    CMD_DATA *      Cmd_Alloc (
        void
    );
    
    
    OBJ_ID          Cmd_Class (
        void
    );
    
    
    CMD_DATA *      Cmd_New (
        void
    );
    
    
#ifdef  CMD_JSON_SUPPORT
    CMD_DATA *      Cmd_NewFromJsonString (
        ASTR_DATA       *pString
    );

    CMD_DATA *      Cmd_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    /*! @property Misc
        is an object that will be passed to each
        Command (Cmd) to be executed. This provides
        a mechanism for passing common data to the
        command process.
     */
    OBJ_ID          Cmd_getMisc (
        CMD_DATA        *this
    );

    bool            Cmd_setMisc (
        CMD_DATA        *this,
        OBJ_ID          pValue
    );


#ifdef CMD_MSGS
    /*! @property   Messages
        Allows information and warning messages to be issued.
     */
    bool            Cmd_setMsgs (
        CMD_DATA        *this,
        void            (*pMsgInfo)(OBJ_ID, const char *, ...),
        void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...),
        OBJ_ID          pObj
    );
#endif


    /*! @property State
        is used to indicate the execution state of
        the command processor. See CMDPROC_STATES
        above for appropriate values.
     */
    uint16_t        Cmd_getState (
        CMD_DATA        *this
    );

    bool            Cmd_setState (
        CMD_DATA        *this,
        uint16_t        value
    );


    OBJ_DATA *      Cmd_getSuper (
        CMD_DATA        *this
    );


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Identifies if this object supports Undo/Redo
     @param     this    object pointer
     @return    if true, it supports Undo/Redo; otherwise, false.
     */
    bool            Cmd_CanUndo (
        CMD_DATA        *this
    );


    /*!
     Perform the speficic command supported by this object. Insure
     that the change state is pushed onto the undo stack before
     actually making the changes if undo/redo is supported.
     The Options for the command are parsed by CmdUtl and returned
     in pOptions which needs to be freed by mem_Free().
     @param     this        object pointer
     @param     pOptions    Option Area pointer
     @return    If successful, ERESULT_SUCCESS. Otherwise, return an
                ERESULT_* error code.
     */
    ERESULT         Cmd_Exec (
        CMD_DATA        *this,
        void            *pOptions
    );


    /*!
     Indicates whether this command supports undo/redo.
     @param     this    object pointer
     @return    If this command supports undo, return true. Otherwise, return
                false.
     */
    bool            Cmd_HasUndo (
        CMD_DATA        *this
    );


    CMD_DATA *      Cmd_Init (
        CMD_DATA        *this
    );


    ERESULT         Cmd_IsEnabled (
        CMD_DATA        *this
    );
    
 
    ERESULT         Cmd_Redo (
        CMD_DATA        *this
    );


    VALUE_DATA *    Cmd_RedoPop (
        CMD_DATA        *this
    );


    ERESULT         Cmd_RedoPush (
        CMD_DATA        *this,
        VALUE_DATA      *pData
    );


#ifdef  CMD_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Cmd_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Cmd_ToJson (
        CMD_DATA        *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Cmd_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Cmd_ToDebugString (
        CMD_DATA        *this,
        int             indent
    );
    
    
    ERESULT         Cmd_Undo (
        CMD_DATA        *this
    );


    VALUE_DATA *    Cmd_UndoPop (
        CMD_DATA        *this
    );


    ERESULT         Cmd_UndoPush (
        CMD_DATA        *this,
        VALUE_DATA      *pData
    );



    
#ifdef  __cplusplus
}
#endif

#endif  /* CMD_H */

