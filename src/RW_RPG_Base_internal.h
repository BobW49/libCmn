// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
// Report Program Generator (RPG) Base (RW_RPG_Base) Internal Header
//****************************************************************

/* 
 * File:   RW_RPG_Base_internal.h
 *  Generated 05/31/2026 14:28:22
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




#include        <RW_RPG_Base.h>
#ifdef  RW_RPG_BASE_SUPER_DEFINED
#include        <obj_internal.h>
#endif
#include        <JsonIn.h>


#ifndef RW_RPG_BASE_INTERNAL_H
#define RW_RPG_BASE_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif


	typedef enum RW_RPG_STEP_e {
		RW_RPG_STEP_00=0,
		RW_RPG_STEP_01=1,
		RW_RPG_STEP_02=2,
		RW_RPG_STEP_03=3,
		RW_RPG_STEP_04=4,
		RW_RPG_STEP_05=5,
		RW_RPG_STEP_06=6,
		RW_RPG_STEP_07=7,
		RW_RPG_STEP_08=8,
		RW_RPG_STEP_09=9,
		RW_RPG_STEP_10=10,
		RW_RPG_STEP_11=11,
		RW_RPG_STEP_12=12,
		RW_RPG_STEP_13=13,
		RW_RPG_STEP_14=14,
		RW_RPG_STEP_15=15,
		RW_RPG_STEP_16=16,
		RW_RPG_STEP_17=17,
		RW_RPG_STEP_18=18,
		RW_RPG_STEP_19=19,
		RW_RPG_STEP_20=20,
		RW_RPG_STEP_21=21,
		RW_RPG_STEP_22=22,
		RW_RPG_STEP_23=23,
		RW_RPG_STEP_24=24,
		RW_RPG_STEP_25=25,
		RW_RPG_STEP_26=26,
		RW_RPG_STEP_27=27,
		RW_RPG_STEP_28=28,
		RW_RPG_STEP_29=29,
		RW_RPG_STEP_30=30,
		RW_RPG_STEP_31=31,
		RW_RPG_STEP_32=32,
		RW_RPG_STEP_33=33,
		RW_RPG_STEP_34=34,
		RW_RPG_STEP_35=35,
		RW_RPG_STEP_36=36,
		RW_RPG_STEP_37=37,
		RW_RPG_STEP_38=38,
		RW_RPG_STEP_39=39,
		RW_RPG_STEP_40=40,
		RW_RPG_STEP_41=41,
		RW_RPG_STEP_42=42,
		RW_RPG_STEP_43=43,
		RW_RPG_STEP_44=44,
		RW_RPG_STEP_45=45,
		RW_RPG_STEP_46=46,
		RW_RPG_STEP_47=47,
		RW_RPG_STEP_48=48,
		RW_RPG_STEP_49=49,
	} RW_RPG_STEPS;


    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

    /*  
        +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
        Remember that if you change the fields of this struct that
        you probably need to change the JSON support as well!
        +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    */

#if !defined(__arm64__)
#pragma pack(push, 1)
#endif
struct RW_RPG_Base_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
#ifdef  RW_RPG_BASE_SUPER_DEFINED
    OBJ_DATA        super;
#else
    OBJ_DATA        super;
#endif
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    ASTR_DATA       *pStr;
    VALUEARRAY_DATA *pRecord;
    VALUEARRAY_DATA *pRecordNext;

#ifdef   RW_RPG_BASE_MSGS
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
    struct RW_RPG_Base_class_data_s  
                        RW_RPG_Base_ClassObj;

    extern
    const
    RW_RPG_BASE_VTBL    RW_RPG_Base_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  RW_RPG_BASE_SINGLETON
    RW_RPG_BASE_DATA * 
                    RW_RPG_Base_getSingleton (
        void
    );

    bool            RW_RPG_Base_setSingleton (
     RW_RPG_BASE_DATA   *pValue
);
#endif


    /*  
        +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
        Define internal routines here so that they can be used
        in testing. Make sure that they have the object name
        prefixing the routine names to avoid conflicts.
        +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    */



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  RW_RPG_BASE_SUPER_DEFINED
    OBJ_DATA *      RW_RPG_Base_getSuper (
        RW_RPG_BASE_DATA 
                        *this
    );
#else
    OBJ_DATA *      RW_RPG_Base_getSuper (
        RW_RPG_BASE_DATA 
                        *this
    );
#endif


    OBJ_IUNKNOWN *  RW_RPG_Base_getSuperVtbl (
        RW_RPG_BASE_DATA 
                        *this
    );


    ERESULT         RW_RPG_Base_Assign (
        RW_RPG_BASE_DATA 
                        *this,
        RW_RPG_BASE_DATA 
                        *pOther
    );


    RW_RPG_BASE_DATA *       
                    RW_RPG_Base_Copy (
        RW_RPG_BASE_DATA 
                        *this
    );


    void            RW_RPG_Base_Dealloc (
        OBJ_ID          objId
    );


    RW_RPG_BASE_DATA * 
                    RW_RPG_Base_DeepCopy (
        RW_RPG_BASE_DATA  
                        *this
    );


    RW_RPG_BASE_DATA * 
                    RW_RPG_Base_Init (
        RW_RPG_BASE_DATA 
                        *this
    );


    RW_RPG_BASE_DATA * 
                    RW_RPG_Base_New (
        void
    );
   
 
 #ifdef  RW_RPG_BASE_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    RW_RPG_BASE_DATA * 
                    RW_RPG_Base_ParseJsonObject (
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
    ERESULT         RW_RPG_Base_ParseJsonFields (
        JSONIN_DATA     *pParser,
        RW_RPG_BASE_DATA 
                        *pObject
    );
#endif


    void *          RW_RPG_Base_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  RW_RPG_BASE_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = RW_RPG_Base_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     RW_RPG_Base_ToJson (
        RW_RPG_BASE_DATA 
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
    ERESULT         RW_RPG_Base_ToJsonFields (
        RW_RPG_BASE_DATA 
                        *this,
        ASTR_DATA       *pStr
    );
#endif


    ASTR_DATA *     RW_RPG_Base_ToDebugString (
        RW_RPG_BASE_DATA 
                        *this,
        int             indent
    );


#ifdef NDEBUG
#else
    bool            RW_RPG_Base_Validate (
        RW_RPG_BASE_DATA 
                        *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* RW_RPG_BASE_INTERNAL_H */

