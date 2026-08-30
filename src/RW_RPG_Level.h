// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
// Report Program Generator (RPG) Level (RW_RPG_Level) Header
//****************************************************************

/*
 * Program
 *          Report Program Generator (RPG) Level (RW_RPG_Level)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate RW_RPG_Level to run things without complications
 *          of interfering with the main RW_RPG_Level. A RW_RPG_Level may be 
 *          called a RW_RPG_Level on other O/S's.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  05/31/2026 Generated
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
        OBJ_IDENT_RW_RPG_LEVEL,             // Report Program Generator (RPG) Level
        OBJ_IDENT_RW_RPG_LEVEL_CLASS,
    The following should be added to the appropriate objects.json.txt
    or program.json.txt file:
        {name:"RW_RPG_Level",  desc:"Report Program Generator (RPG) Level"},
 *----------------------------------------------------------------*/



//#define   RW_RPG_LEVEL_IS_IMMUTABLE       1
//#define   RW_RPG_LEVEL_JSON_SUPPORT       1
//#define   RW_RPG_LEVEL_SINGLETON          1
//#define   RW_RPG_LEVEL_MSGS               1
//#define   RW_RPG_LEVEL_SUPER_DEFINED      1


#include        <cmn_defs.h>
#include        <AStr.h>
#ifdef  RW_RPG_LEVEL_SUPER_DEFINED
#include        <obj.h>
#endif
#include        <ValueArray.h>


#ifndef         RW_RPG_LEVEL_H
#define         RW_RPG_LEVEL_H





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct RW_RPG_Level_data_s  RW_RPG_LEVEL_DATA;          // Inherits from obj
    typedef struct RW_RPG_Level_class_data_s RW_RPG_LEVEL_CLASS_DATA;  // Inherits from obj

    typedef struct RW_RPG_Level_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        //obj_VTBL    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in RW_RPG_Level_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(RW_RPG_LEVEL_DATA *);
    } RW_RPG_LEVEL_VTBL;

    typedef struct RW_RPG_Level_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in RW_RPG_Level_object.c.
        // Properties:
        // Methods:
        RW_RPG_LEVEL_DATA *(*pNew)(void);
        //bool        (*pIsEnabled)(RW_RPG_LEVEL_DATA *);
    } RW_RPG_LEVEL_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  RW_RPG_LEVEL_SINGLETON
    RW_RPG_LEVEL_DATA * 
                    RW_RPG_Level_Shared (
        void
    );

    void            RW_RPG_Level_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to RW_RPG_Level object if successful, otherwise OBJ_NIL.
     */
    RW_RPG_LEVEL_DATA * 
                    RW_RPG_Level_Alloc (
        void
    );
    
    
    OBJ_ID          RW_RPG_Level_Class (
        void
    );
    
    
    RW_RPG_LEVEL_DATA * 
                    RW_RPG_Level_New (
        void
    );
    
    
#ifdef  RW_RPG_LEVEL_JSON_SUPPORT
    RW_RPG_LEVEL_DATA * 
                    RW_RPG_Level_NewFromJsonString (
        ASTR_DATA       *pString
    );

    RW_RPG_LEVEL_DATA * 
                    RW_RPG_Level_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    /*! @property   DataI16
        is a general data field.
     */
    int16_t         RW_RPG_Level_getDataI16 (
        RW_RPG_LEVEL_DATA 
                        *this
    );

    bool            RW_RPG_Level_setDataI16 (
        RW_RPG_LEVEL_DATA 
                        *this,
        int16_t         value
    );

    
    /*! @property   DataI32
        is a general data field.
     */
    int32_t         RW_RPG_Level_getDataI32 (
        RW_RPG_LEVEL_DATA 
                        *this
    );

    bool            RW_RPG_Level_setDataI32 (
        RW_RPG_LEVEL_DATA 
                        *this,
        int32_t         value
    );


    /*! @property   DataI64
        is a general data field.
     */
    int64_t         RW_RPG_Level_getDataI64 (
        RW_RPG_LEVEL_DATA 
                        *this
    );

    bool            RW_RPG_Level_setDataI64 (
        RW_RPG_LEVEL_DATA 
                        *this,
        int64_t         value
    );


    /*! @property   Level
        is the RPG Level Number for this object.
     */
    uint16_t        RW_RPG_Level_getLevel (
        RW_RPG_LEVEL_DATA 
                        *this
    );

  #ifdef RW_RPG_LEVEL_MSGS
    /*! @property   Messages
        Allows information and warning messages to be issued.
     */
    bool            RW_RPG_Level_setMsgs (
        RW_RPG_LEVEL_DATA 
                        *this,
        void            (*pMsgInfo)(OBJ_ID, const char *, ...),
        void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...),
        OBJ_ID          pObj
    );
#endif


#ifdef  RW_RPG_LEVEL_SUPER_DEFINED
    OBJ_DATA *      RW_RPG_Level_getSuper (
        RW_RPG_LEVEL_DATA 
                        *this
    );
#else
    OBJ_DATA *      RW_RPG_Level_getSuper (
        RW_RPG_LEVEL_DATA 
                        *this
    );
#endif


    VALUE_DATA *    RW_RPG_Level_getValueNew (
        RW_RPG_LEVEL_DATA 
                        *this
    );

    bool            RW_RPG_Level_setValueNew (
        RW_RPG_LEVEL_DATA 
                        *this,
        VALUE_DATA      *pValue
    );
    
    
    VALUE_DATA *    RW_RPG_Level_getValueOld (
        RW_RPG_LEVEL_DATA 
                        *this
    );

    bool            RW_RPG_Level_setValueOld (
        RW_RPG_LEVEL_DATA 
                        *this,
        VALUE_DATA      *pValue
    );
 


     //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         RW_RPG_Level_Disable (
        RW_RPG_LEVEL_DATA 
                        *this
    );


    ERESULT         RW_RPG_Level_Enable (
        RW_RPG_LEVEL_DATA 
                        *this
    );

   
    RW_RPG_LEVEL_DATA * 
                    RW_RPG_Level_Init (
        RW_RPG_LEVEL_DATA 
                        *this
    );


    bool            RW_RPG_Level_IsEnabled (
        RW_RPG_LEVEL_DATA 
                        *this
    );
    
 
#ifdef  RW_RPG_LEVEL_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = RW_RPG_Level_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     RW_RPG_Level_ToJson (
        RW_RPG_LEVEL_DATA 
                        *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = RW_RPG_Level_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     RW_RPG_Level_ToDebugString (
        RW_RPG_LEVEL_DATA 
                        *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* RW_RPG_LEVEL_H */

