// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
// Python Interface to/from Objects (PythonInter) Header
//****************************************************************

/*
 * Program
 *          Python Interface to/from Objects (PythonInter)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate PythonInter to run things without complications
 *          of interfering with the main PythonInter. A PythonInter may be 
 *          called a PythonInter on other O/S's.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  05/21/2026 Generated
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
        OBJ_IDENT_PYTHONINTER,             // Python Interface to/from Objects
        OBJ_IDENT_PYTHONINTER_CLASS,
    The following should be added to the appropriate objects.json.txt
    or program.json.txt file:
        {name:"PythonInter",  desc:"Python Interface to/from Objects"},
 *----------------------------------------------------------------*/



//#define   PYTHONINTER_IS_IMMUTABLE    1
//#define   PYTHONINTER_JSON_SUPPORT    1
//#define   PYTHONINTER_SINGLETON       1
//#define   PYTHONINTER_MSGS            1
//#define   PYTHONINTER_SUPER_DEFINED   1


#include        <cmn_defs.h>
#include        <AStr.h>
#ifdef  PYTHONINTER_SUPER_DEFINED
#include        <obj.h>
#endif


#ifndef         PYTHONINTER_H
#define         PYTHONINTER_H


#include        <Python.h>


#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct PythonInter_data_s  PYTHONINTER_DATA;          // Inherits from obj
    typedef struct PythonInter_class_data_s PYTHONINTER_CLASS_DATA;  // Inherits from obj

    typedef struct PythonInter_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        //obj_VTBL    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in PythonInter_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(PYTHONINTER_DATA *);
    } PYTHONINTER_VTBL;

    typedef struct PythonInter_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in PythonInter_object.c.
        // Properties:
        // Methods:
        PYTHONINTER_DATA *(*pNew)(void);
        //bool        (*pIsEnabled)(PYTHONINTER_DATA *);
    } PYTHONINTER_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  PYTHONINTER_SINGLETON
    PYTHONINTER_DATA * 
                    PythonInter_Shared (
        void
    );

    void            PythonInter_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to PythonInter object if successful, otherwise OBJ_NIL.
     */
    PYTHONINTER_DATA * 
                    PythonInter_Alloc (
        void
    );
    
    
    OBJ_ID          PythonInter_Class (
        void
    );
    
    
    PYTHONINTER_DATA * 
                    PythonInter_New (
        void
    );
    
    
    PyObject *      PythonInter_AStrToPy (
        ASTR_DATA       *pAStr
    );

    
    PyObject *      PythonInter_StringToPy (
        const 
        char            *pUtf8,
        size_t          len
    );


#ifdef  PYTHONINTER_JSON_SUPPORT
    PYTHONINTER_DATA * 
                    PythonInter_NewFromJsonString (
        ASTR_DATA       *pString
    );

    PYTHONINTER_DATA * 
                    PythonInter_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

#ifdef PYTHONINTER_MSGS
    /*! @property   Messages
        Allows information and warning messages to be issued.
     */
    bool            PythonInter_setMsgs (
        PYTHONINTER_DATA 
                        *this,
        void            (*pMsgInfo)(OBJ_ID, const char *, ...),
        void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...),
        OBJ_ID          pObj
    );
#endif


#ifdef  PYTHONINTER_SUPER_DEFINED
    OBJ_DATA *      PythonInter_getSuper (
        PYTHONINTER_DATA 
                        *this
    );
#else
    OBJ_DATA *      PythonInter_getSuper (
        PYTHONINTER_DATA 
                        *this
    );
#endif


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         PythonInter_Disable (
        PYTHONINTER_DATA 
                        *this
    );


    ERESULT         PythonInter_Enable (
        PYTHONINTER_DATA 
                        *this
    );

   
    PYTHONINTER_DATA * 
                    PythonInter_Init (
        PYTHONINTER_DATA 
                        *this
    );


    bool            PythonInter_IsEnabled (
        PYTHONINTER_DATA 
                        *this
    );
    
 
#ifdef  PYTHONINTER_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = PythonInter_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     PythonInter_ToJson (
        PYTHONINTER_DATA 
                        *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = PythonInter_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     PythonInter_ToDebugString (
        PYTHONINTER_DATA 
                        *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* PYTHONINTER_H */

