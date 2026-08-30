// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Specific Date and Time (RW_DateTime) Header
//****************************************************************

/*
 * Program
 *          Specific Date and Time (RW_DateTime)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate RW_DateTime to run things without complications
 *          of interfering with the main RW_DateTime. A RW_DateTime may be 
 *          called a RW_DateTime on other O/S's.
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
        OBJ_IDENT_RW_DATETIME,             // Specific Date and Time
        OBJ_IDENT_RW_DATETIME_CLASS,
    The following should be added to the appropriate objects.json.txt
    or program.json.txt file:
        {name:"RW_DateTime",  desc:"Specific Date and Time"},
 *----------------------------------------------------------------*/



//#define   RW_DATETIME_IS_IMMUTABLE       1
#define   RW_DATETIME_JSON_SUPPORT       1
//#define   RW_DATETIME_SINGLETON          1
//#define   RW_DATETIME_MSGS               1
//#define   RW_DATETIME_SUPER_DEFINED      1


#include        <cmn_defs.h>
#include        <AStr.h>
#ifdef  RW_DATETIME_SUPER_DEFINED
#include        <obj.h>
#endif


#ifndef         RW_DATETIME_H
#define         RW_DATETIME_H





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct RW_DateTime_data_s  RW_DATETIME_DATA;          // Inherits from obj
    typedef struct RW_DateTime_class_data_s RW_DATETIME_CLASS_DATA;  // Inherits from obj

    typedef struct RW_DateTime_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        //obj_VTBL    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in RW_DateTime_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(RW_DATETIME_DATA *);
    } RW_DATETIME_VTBL;

    typedef struct RW_DateTime_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in RW_DateTime_object.c.
        // Properties:
        // Methods:
        RW_DATETIME_DATA *(*pNew)(void);
        //bool        (*pIsEnabled)(RW_DATETIME_DATA *);
    } RW_DATETIME_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  RW_DATETIME_SINGLETON
    RW_DATETIME_DATA * 
                    RW_DateTime_Shared (
        void
    );

    void            RW_DateTime_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to RW_DateTime object if successful, otherwise OBJ_NIL.
     */
    RW_DATETIME_DATA * 
                    RW_DateTime_Alloc (
        void
    );
    
    
    OBJ_ID          RW_DateTime_Class (
        void
    );
    
    
    RW_DATETIME_DATA * 
                    RW_DateTime_New (
        void
    );
    
    
    RW_DATETIME_DATA * 
                    RW_DateTime_NewCurrent (
        void
    );


    RW_DATETIME_DATA * 
                    RW_DateTime_NewFromTimeT (
        const
        time_t          time
    );


#ifdef  RW_DATETIME_JSON_SUPPORT
    RW_DATETIME_DATA * 
                    RW_DateTime_NewFromJsonString (
        ASTR_DATA       *pString
    );

    RW_DATETIME_DATA * 
                    RW_DateTime_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    int16_t         RW_DateTime_getDay (
        RW_DATETIME_DATA
                        *this
    );

    bool            RW_DateTime_setDay (
        RW_DATETIME_DATA
                        *this,
        int16_t         pValue
    );


    int16_t         RW_DateTime_getMonth (
        RW_DATETIME_DATA
                        *this
    );

    bool            RW_DateTime_setMonth (
        RW_DATETIME_DATA
                        *this,
        int16_t         pValue
    );


    int16_t         RW_DateTime_getYear (
        RW_DATETIME_DATA
                        *this
    );

    bool            RW_DateTime_setYear (
        RW_DATETIME_DATA
                        *this,
        int16_t         pValue
    );


    int16_t         RW_DateTime_getHour (
        RW_DATETIME_DATA
                        *this
    );

    bool            RW_DateTime_setHour (
        RW_DATETIME_DATA
                        *this,
        int16_t         pValue
    );


    int16_t         RW_DateTime_getMin (
        RW_DATETIME_DATA
                        *this
    );

    bool            RW_DateTime_setMin (
        RW_DATETIME_DATA
                        *this,
        int16_t         pValue
    );


    int16_t         RW_DateTime_getSec (
        RW_DATETIME_DATA
                        *this
    );

    bool            RW_DateTime_setSec (
        RW_DATETIME_DATA
                        *this,
        int16_t         pValue
    );


    int16_t         RW_DateTime_getMilli (
        RW_DATETIME_DATA
                        *this
    );

    bool            RW_DateTime_setMilli (
        RW_DATETIME_DATA
                        *this,
        int16_t         pValue
    );


#ifdef RW_DATETIME_MSGS
    /*! @property   Messages
        Allows information and warning messages to be issued.
     */
    bool            RW_DateTime_setMsgs (
        RW_DATETIME_DATA 
                        *this,
        void            (*pMsgInfo)(OBJ_ID, const char *, ...),
        void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...),
        OBJ_ID          pObj
    );
#endif


#ifdef  RW_DATETIME_SUPER_DEFINED
    OBJ_DATA *      RW_DateTime_getSuper (
        RW_DATETIME_DATA 
                        *this
    );
#else
    OBJ_DATA *      RW_DateTime_getSuper (
        RW_DATETIME_DATA 
                        *this
    );
#endif


    uint64_t        RW_DateTime_getTime (
        RW_DATETIME_DATA 
                        *this
    );

    bool            RW_DateTime_setTime (
        RW_DATETIME_DATA 
                        *this,
        uint64_t        value
    );

    
    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before 
     a copy of the object is performed.
     Example:
     @code 
        ERESULT eRc = RW_DateTime_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another RW_DATETIME object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         RW_DateTime_Assign (
        RW_DATETIME_DATA 
                        *this,
        RW_DATETIME_DATA 
                        *pOther
    );
    
 
    /*!
     Compare the two provided objects.
     @return    0  if this == other
                <0 if this < other
                >0 if this > other
     */
    int             RW_DateTime_Compare (
        RW_DATETIME_DATA 
                        *this,
        RW_DATETIME_DATA 
                        *pOther
    );

    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        RW_DateTime      *pCopy = RW_DateTime_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a RW_DATETIME object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    RW_DATETIME_DATA * 
                    RW_DateTime_Copy (
        RW_DATETIME_DATA 
                        *this
    );

    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        RW_DateTime      *pDeepCopy = RW_DateTime_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a RW_DATETIME object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    RW_DATETIME_DATA * 
                    RW_DateTime_DeepCopy (
        RW_DATETIME_DATA 
                        *this
    );

    
    RW_DATETIME_DATA * 
                    RW_DateTime_Init (
        RW_DATETIME_DATA 
                        *this
    );


    bool            RW_DateTime_IsEnabled (
        RW_DATETIME_DATA 
                        *this
    );
    
 
#ifdef  RW_DATETIME_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = RW_DateTime_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     RW_DateTime_ToJson (
        RW_DATETIME_DATA 
                        *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = RW_DateTime_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     RW_DateTime_ToDebugString (
        RW_DATETIME_DATA 
                        *this,
        int             indent
    );
    
    
    /*!
     Create a string that has the date formatted as MM/DD/YYYY_HH:MM:SS.III which
     can then be used in a file path.
     Example:
     @code
     ASTR_DATA      *pDesc = DateTime_ToDebugString(pObj,4);
     @endcode
     @param     this    DateTime object pointer
     @return    If successful, an AStr object which must be released containing the
     string, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     RW_DateTime_ToFileString (
        RW_DATETIME_DATA   
                        *this
    );


    /*!
     Create a string that has the date formatted as MM/DD/YYYY HH:MM:SS.III.
     Example:
     @code
     ASTR_DATA      *pDesc = DateTime_ToDebugString(pObj,4);
     @endcode
     @param     this    DateTime object pointer
     @return    If successful, an AStr object which must be released containing the
                string, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     RW_DateTime_ToString (
        RW_DATETIME_DATA   
                        *this
    );



    
#ifdef  __cplusplus
}
#endif

#endif  /* RW_DATETIME_H */

