// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//              Base Object which everything inherits from (Object) Header
//****************************************************************

/*
 * Program
 *          Base Object which everything inherits from (Object)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate Object to run things without complications
 *          of interfering with the main Object. A Object may be 
 *          called a Object on other O/S's.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  06/21/2026 Generated
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
        OBJ_IDENT_OBJECT,             // Base Object which everything inherits from
        OBJ_IDENT_OBJECT_CLASS,
    The following should be added to the appropriate objects.json.txt
    or program.json.txt file:
        {name:"Object",  desc:"Base Object which everything inherits from"},
 *----------------------------------------------------------------*/



//#define   %{NAMEU}_IS_IMMUTABLE     1
#define   %{NAMEU}_JSON_SUPPORT       1
//#define   %{NAMEU}_SINGLETON        1
//#define       OBJECT_MSGS   1
//#define   %{NAMEU}_SUPER_DEFINED     1


#include        <cmn_defs.h>
#include        <AStr.h>
#ifdef  OBJECT_SUPER_DEFINED
#include        <obj.h>
#endif


#ifndef         OBJECT_H
#define         OBJECT_H





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct Object_data_s  OBJECT_DATA;          // Inherits from obj
    typedef struct Object_class_data_s OBJECT_CLASS_DATA;  // Inherits from obj

    typedef struct Object_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        //obj_VTBL    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Object_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(OBJECT_DATA *);
    } OBJECT_VTBL;

    typedef struct Object_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Object_object.c.
        // Properties:
        // Methods:
        OBJECT_DATA *(*pNew)(void);
        //bool        (*pIsEnabled)(OBJECT_DATA *);
    } OBJECT_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  OBJECT_SINGLETON
    OBJECT_DATA *   Object_Shared (
        void
    );

    void            Object_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to Object object if successful, otherwise OBJ_NIL.
     */
    OBJECT_DATA *   Object_Alloc (
        void
    );
    
    
    OBJ_ID          Object_Class (
        void
    );
    
    
    OBJECT_DATA *   Object_New (
        void
    );
    
    
#ifdef  OBJECT_JSON_SUPPORT
    OBJECT_DATA *   Object_NewFromJsonString (
        ASTR_DATA       *pString
    );

    OBJECT_DATA *   Object_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

#ifdef OBJECT_MSGS
    /*! @property   Messages
        Allows information and warning messages to be issued.
     */
    bool            Object_setMsgs (
        OBJECT_DATA     *this,
        void            (*pMsgInfo)(OBJ_ID, const char *, ...),
        void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...),
        OBJ_ID          pObj
    );
#endif


#ifdef  OBJECT_SUPER_DEFINED
    OBJ_DATA *      Object_getSuper (
        OBJECT_DATA     *this
    );
#else
    OBJ_DATA *      Object_getSuper (
        OBJECT_DATA     *this
    );
#endif


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         Object_Disable (
        OBJECT_DATA     *this
    );


    ERESULT         Object_Enable (
        OBJECT_DATA     *this
    );

   
    OBJECT_DATA *   Object_Init (
        OBJECT_DATA     *this
    );


    bool            Object_IsEnabled (
        OBJECT_DATA     *this
    );
    
 
#ifdef  OBJECT_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Object_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Object_ToJson (
        OBJECT_DATA     *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Object_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Object_ToDebugString (
        OBJECT_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* OBJECT_H */

