// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
// Python Interface to/from Objects (PythonInter) Internal Header
//****************************************************************

/* 
 * File:   PythonInter_internal.h
 *  Generated 05/21/2026 07:03:39
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




#include        <PythonInter.h>
#ifdef  PYTHONINTER_SUPER_DEFINED
#include        <obj_internal.h>
#endif
#include        <AStr.h>
#include        <JsonIn.h>


#include        <Python.h>


#ifndef PYTHONINTER_INTERNAL_H
#define PYTHONINTER_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------


#if !defined(__arm64__)
#pragma pack(push, 1)
#endif
struct PythonInter_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
#ifdef  PYTHONINTER_SUPER_DEFINED
    OBJ_DATA        super;
#else
    OBJ_DATA        super;
#endif
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    ASTR_DATA       *pStr;

#ifdef   PYTHONINTER_MSGS
    // Informational and Warning Log Messages
    void            (*pMsgInfo)(OBJ_ID, const char *, ...);
    void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...);
    OBJ_ID          pMsgObj;
#endif

    uint16_t        size;           // maximum number of elements
    uint16_t        rsvd16;
};
#if !defined(__arm64__)
#pragma pack(pop)
#endif

    extern
    struct PythonInter_class_data_s  
                        PythonInter_ClassObj;

    extern
    const
    PYTHONINTER_VTBL    PythonInter_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  PYTHONINTER_SINGLETON
    PYTHONINTER_DATA * 
                    PythonInter_getSingleton (
        void
    );

    bool            PythonInter_setSingleton (
     PYTHONINTER_DATA   *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

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


    OBJ_IUNKNOWN *  PythonInter_getSuperVtbl (
        PYTHONINTER_DATA 
                        *this
    );


    ERESULT         PythonInter_Assign (
        PYTHONINTER_DATA 
                        *this,
        PYTHONINTER_DATA 
                        *pOther
    );


    PYTHONINTER_DATA *       
                    PythonInter_Copy (
        PYTHONINTER_DATA 
                        *this
    );


    void            PythonInter_Dealloc (
        OBJ_ID          objId
    );


    PYTHONINTER_DATA * 
                    PythonInter_DeepCopy (
        PYTHONINTER_DATA  
                        *this
    );


    PYTHONINTER_DATA * 
                    PythonInter_Init (
        PYTHONINTER_DATA 
                        *this
    );


    PYTHONINTER_DATA * 
                    PythonInter_New (
        void
    );
   
 
 #ifdef  PYTHONINTER_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    PYTHONINTER_DATA * 
                    PythonInter_ParseJsonObject (
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
    ERESULT         PythonInter_ParseJsonFields (
        JSONIN_DATA     *pParser,
        PYTHONINTER_DATA 
                        *pObject
    );
#endif


    void *          PythonInter_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
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


    /*!
     Append the json representation of the object's fields to the given
     string. This helps facilitate parsing the fields from an inheriting 
     object.
     @param this        Object Pointer
     @param pStr        String Pointer to be appended to.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         PythonInter_ToJsonFields (
        PYTHONINTER_DATA 
                        *this,
        ASTR_DATA       *pStr
    );
#endif


    ASTR_DATA *     PythonInter_ToDebugString (
        PYTHONINTER_DATA 
                        *this,
        int             indent
    );


#ifdef NDEBUG
#else
    bool            PythonInter_Validate (
        PYTHONINTER_DATA 
                        *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* PYTHONINTER_INTERNAL_H */

