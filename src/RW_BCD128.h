// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//  Binary Coded Decimal based on int128_t (RW_BCD128) Header
//****************************************************************

/*
 * Program
 *          Binary Coded Decimal based on int128_t (RW_BCD128)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate RW_BCD128 to run things without complications
 *          of interfering with the main RW_BCD128. A RW_BCD128 may be 
 *          called a RW_BCD128 on other O/S's.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  06/03/2026 Generated
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
        OBJ_IDENT_RW_BCD128,             // Binary Coded Decimal based on int128_t
        OBJ_IDENT_RW_BCD128_CLASS,
    The following should be added to the appropriate objects.json.txt
    or program.json.txt file:
        {name:"RW_BCD128",  desc:"Binary Coded Decimal based on int128_t"},
 *----------------------------------------------------------------*/



//#define   RW_BCD128_IS_IMMUTABLE      1
//#define   RW_BCD128_JSON_SUPPORT      1
//#define   RW_BCD128_SINGLETON         1
//#define   RW_BCD128_MSGS              1
//#define   RW_BCD128_SUPER_DEFINED     1


#include        <cmn_defs.h>
#include        <AStr.h>
#ifdef  RW_BCD128_SUPER_DEFINED
#include        <obj.h>
#endif


#ifndef         RW_BCD128_H
#define         RW_BCD128_H





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct RW_BCD128_data_s  RW_BCD128_DATA;          // Inherits from obj
    typedef struct RW_BCD128_class_data_s RW_BCD128_CLASS_DATA;  // Inherits from obj

    typedef struct RW_BCD128_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        //obj_VTBL    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in RW_BCD128_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(RW_BCD128_DATA *);
    } RW_BCD128_VTBL;

    typedef struct RW_BCD128_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in RW_BCD128_object.c.
        // Properties:
        // Methods:
        RW_BCD128_DATA *(*pNew)(void);
        //bool        (*pIsEnabled)(RW_BCD128_DATA *);
    } RW_BCD128_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  RW_BCD128_SINGLETON
    RW_BCD128_DATA * 
                    RW_BCD128_Shared (
        void
    );

    void            RW_BCD128_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to RW_BCD128 object if successful, otherwise OBJ_NIL.
     */
    RW_BCD128_DATA * 
                    RW_BCD128_Alloc (
        void
    );
    
    
    OBJ_ID          RW_BCD128_Class (
        void
    );
    
    
    RW_BCD128_DATA * 
                    RW_BCD128_New (
        void
    );
    
    
#ifdef  RW_BCD128_JSON_SUPPORT
    RW_BCD128_DATA * 
                    RW_BCD128_NewFromJsonString (
        ASTR_DATA       *pString
    );

    RW_BCD128_DATA * 
                    RW_BCD128_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

#ifdef RW_BCD128_MSGS
    /*! @property   Messages
        Allows information and warning messages to be issued.
     */
    bool            RW_BCD128_setMsgs (
        RW_BCD128_DATA  *this,
        void            (*pMsgInfo)(OBJ_ID, const char *, ...),
        void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...),
        OBJ_ID          pObj
    );
#endif


#ifdef  RW_BCD128_SUPER_DEFINED
    OBJ_DATA *      RW_BCD128_getSuper (
        RW_BCD128_DATA  *this
    );
#else
    OBJ_DATA *      RW_BCD128_getSuper (
        RW_BCD128_DATA  *this
    );
#endif


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         RW_BCD128_Disable (
        RW_BCD128_DATA  *this
    );


    ERESULT         RW_BCD128_Enable (
        RW_BCD128_DATA  *this
    );

   
    RW_BCD128_DATA * 
                    RW_BCD128_Init (
        RW_BCD128_DATA  *this
    );


    bool            RW_BCD128_IsEnabled (
        RW_BCD128_DATA  *this
    );
    
 
#ifdef  RW_BCD128_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = RW_BCD128_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     RW_BCD128_ToJson (
        RW_BCD128_DATA  *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = RW_BCD128_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     RW_BCD128_ToDebugString (
        RW_BCD128_DATA  *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* RW_BCD128_H */

