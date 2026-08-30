// vi: nu:noai:ts=4:sw=4

//****************************************************************
// Binary Coded Decimal based on int128_t (RW_BCD128) Object Support
//****************************************************************

//  Class Object Metods and Tables for 'RW_BCD128'
//  Generated 06/03/2026 08:40:22


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




#define         RW_BCD128_OBJECT_C       1
#include        <RW_BCD128_internal.h>
#ifdef  RW_BCD128_SINGLETON
#include        <psxLock.h>
#endif


#ifdef  __cplusplus
extern "C" {
#endif
        
        

    //===========================================================
    //                  Class Object Definition
    //===========================================================

    struct RW_BCD128_class_data_s    {
        // Warning - OBJ_DATA must be first in this object!
        OBJ_DATA        super;
        
        // Common Data
    #ifdef  RW_BCD128_SINGLETON
        volatile
        RW_BCD128_DATA  *pSingleton;
    #endif
        //uint32_t       misc;
        //OBJ_ID         pObjCatalog;
    };




    //-----------------------------------------------------------
    //                  Class Methods
    //-----------------------------------------------------------



    static
    void *          RW_BCD128Class_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    static
    const
    OBJ_INFO            RW_BCD128_Info;            // Forward Reference




    static
    bool            RW_BCD128Class_IsKindOf (
        uint16_t        classID
    )
    {
        OBJ_DATA        *pObj;
        
        if (OBJ_IDENT_RW_BCD128_CLASS == classID) {
           return true;
        }
        if (OBJ_IDENT_OBJ_CLASS == classID) {
           return true;
        }
        
        pObj = obj_getInfo(RW_BCD128_Class())->pClassSuperObject;
        if (pObj == obj_BaseClass())
            ;
        else {
            return obj_getVtbl(pObj)->pIsKindOf(classID);
        }
        
        return false;
    }


    static
    uint16_t        RW_BCD128Class_WhoAmI (
        void
    )
    {
        return OBJ_IDENT_RW_BCD128_CLASS;
    }




    //===========================================================
    //                 Class Object Vtbl Definition
    //===========================================================

    static
    const
    RW_BCD128_CLASS_VTBL 
                        class_Vtbl = {
        {
            &RW_BCD128_Info,
            RW_BCD128Class_IsKindOf,
            obj_RetainNull,
            obj_ReleaseNull,
            NULL,
            RW_BCD128_Class,
            RW_BCD128Class_WhoAmI,
            (P_OBJ_QUERYINFO)RW_BCD128Class_QueryInfo,
            NULL                        // RW_BCD128Class_ToDebugString
        },
        (void *)RW_BCD128_New
    };



    //-----------------------------------------------------------
    //                      Class Object
    //-----------------------------------------------------------

    RW_BCD128_CLASS_DATA 
                        RW_BCD128_ClassObj = {
        {
            (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
            sizeof(RW_BCD128_CLASS_DATA),           // cbSize
            0,                                      // cbFlags
            1,                                      // cbRetainCount
            {0}                                     // cbMisc
        },
        //0
    };



    //---------------------------------------------------------------
    //          S i n g l e t o n  M e t h o d s
    //---------------------------------------------------------------

    #ifdef  RW_BCD128_SINGLETON
    extern
    const
    RW_BCD128_VTBL      RW_BCD128_VtblShared;


    RW_BCD128_DATA * 
                    RW_BCD128_getSingleton (
        void
    )
    {
        return (OBJ_ID)(RW_BCD128_ClassObj.pSingleton);
    }


    bool            RW_BCD128_setSingleton (
        RW_BCD128_DATA  *pValue
    )
    {
        PSXLOCK_DATA    *pLock = OBJ_NIL;
        bool            fRc;
        
        pLock = psxLock_New( );
        if (OBJ_NIL == pLock) {
            DEBUG_BREAK();
            return false;
        }
        fRc = psxLock_Lock(pLock);
        if (!fRc) {
            DEBUG_BREAK();
            obj_Release(pLock);
            pLock = OBJ_NIL;
            return false;
        }
        
        obj_Retain(pValue);
        if (RW_BCD128_ClassObj.pSingleton) {
            obj_Release((OBJ_ID)(RW_BCD128_ClassObj.pSingleton));
        }
        RW_BCD128_ClassObj.pSingleton = pValue;
        
        fRc = psxLock_Unlock(pLock);
        obj_Release(pLock);
        pLock = OBJ_NIL;
        return true;
    }



    RW_BCD128_DATA * 
                    RW_BCD128_Shared (
        void
    )
    {
        RW_BCD128_DATA  *this = (OBJ_ID)(RW_BCD128_ClassObj.pSingleton);
        
        if (NULL == this) {
            this = RW_BCD128_New( );
            obj_setVtbl(this, (void *)&RW_BCD128_VtblShared);
            RW_BCD128_setSingleton(this);
            obj_Release(this);          // Shared controls object retention now.
            // RW_BCD128_ClassObj.pSingleton = OBJ_NIL;
        }
        
        return this;
    }



    void            RW_BCD128_SharedReset (
        void
    )
    {
        RW_BCD128_DATA  *this = (OBJ_ID)(RW_BCD128_ClassObj.pSingleton);
        
        if (this) {
            obj_setVtbl(this, (void *)&RW_BCD128_Vtbl);
            obj_Release(this);
            RW_BCD128_ClassObj.pSingleton = OBJ_NIL;
        }
        
    }



    #endif



    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------

    static
    void *          RW_BCD128Class_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        RW_BCD128_CLASS_DATA 
                        *this = objId;
        const
        char            *pStrA = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
        
        switch (type) {
          
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(RW_BCD128_DATA);
                break;
                
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return this;
                break;
                
            // Query for an address to specific data within the object.  
            case OBJ_QUERYINFO_TYPE_DATA_PTR:
                switch (*pStrA) {
     
                    case 'C':
                        if (str_Compare("ClassInfo", (char *)pStrA) == 0) {
                            return (void *)&RW_BCD128_Info;
                        }
                        break;
                        
                    case 'S':
                        if (str_Compare("SuperClass", (char *)pStrA) == 0) {
                            return (void *)&RW_BCD128_Info.pClassSuperObject;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStrA) {
                        
                    case 'N':
                        if (str_Compare("New", (char *)pStrA) == 0) {
                            return RW_BCD128_New;
                        }
                        break;
                        
                    case 'P':
    #ifdef  RW_BCD128_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStrA) == 0) {
                            return RW_BCD128_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStrA) == 0) {
                            return RW_BCD128_ParseJsonObject;
                        }
    #endif
                        break;

                    case 'T':
    #ifdef  RW_BCD128_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStrA) == 0) {
                            return RW_BCD128_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStrA) == 0) {
                            return RW_BCD128_ToJson;
                        }
    #endif
                        break;

                     case 'W':
                        if (str_Compare("WhoAmI", (char *)pStrA) == 0) {
                            return RW_BCD128Class_WhoAmI;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            default:
                break;
        }
        
        return NULL;
    }




    static
    bool            RW_BCD128_IsKindOf (
        uint16_t        classID
    )
    {
        OBJ_DATA        *pObj;
        const
        OBJ_INFO        *pInfo;

        if (OBJ_IDENT_RW_BCD128 == classID) {
           return true;
        }
        if (OBJ_IDENT_OBJ == classID) {
           return true;
        }

        pObj = obj_getInfo(RW_BCD128_Class())->pClassSuperObject;
        if (pObj == obj_BaseClass())
            ;
        else {
            pInfo = obj_getInfo(pObj);
            return pInfo->pDefaultVtbls->pIsKindOf(classID);
        }
        
        return false;
    }


    // Dealloc() should be put into the Internal Header as well
    // for classes that get inherited from.
    void            RW_BCD128_Dealloc (
        OBJ_ID          objId
    );


    OBJ_ID          RW_BCD128_Class (
        void
    )
    {
        return (OBJ_ID)&RW_BCD128_ClassObj;
    }


    static
    uint16_t        RW_BCD128_WhoAmI (
        void
    )
    {
        return OBJ_IDENT_RW_BCD128;
    }





    //===========================================================
    //                  Object Vtbl Definition
    //===========================================================

    #ifdef  RW_BCD128_SINGLETON
    // A Shared object ignores Retain() and Release() except for
    // initialization and termination. So, there must be an
    // independent VTbl from the normal which does support Retain()
    // and Release().
    const
    RW_BCD128_VTBL      RW_BCD128_VtblShared = {
        {
            &RW_BCD128_Info,
            RW_BCD128_IsKindOf,
            obj_RetainNull,
            obj_ReleaseNull,
            RW_BCD128_Dealloc,
            RW_BCD128_Class,
            RW_BCD128_WhoAmI,
            (P_OBJ_QUERYINFO)RW_BCD128_QueryInfo,
            (P_OBJ_TOSTRING)RW_BCD128_ToDebugString,
            NULL,           // RW_BCD128_Enable,
            NULL,           // RW_BCD128_Disable,
            NULL,           // (P_OBJ_ASSIGN)RW_BCD128_Assign,
            NULL,           // (P_OBJ_COMPARE)RW_BCD128_Compare,
            NULL,           // (P_OBJ_PTR)RW_BCD128_Copy,
            NULL,           // (P_OBJ_PTR)RW_BCD128_DeepCopy,
            NULL            // (P_OBJ_HASH)RW_BCD128_Hash,
        },
        // Put other object method names below this.
        // Properties:
        // Methods:
        //RW_BCD128_IsEnabled,
     
    };
    #endif


    // This VTbl supports Retain() and Release() which is
    // used by objects other than the Shared object. These
    // objects can still be shared among other objects. It
    // just that they are deleted when their usage count
    // goes to zero.
    const
    RW_BCD128_VTBL      RW_BCD128_Vtbl = {
        {
            &RW_BCD128_Info,
            RW_BCD128_IsKindOf,
            obj_RetainStandard,
            obj_ReleaseStandard,
            RW_BCD128_Dealloc,
            RW_BCD128_Class,
            RW_BCD128_WhoAmI,
            (P_OBJ_QUERYINFO)RW_BCD128_QueryInfo,
            (P_OBJ_TOSTRING)RW_BCD128_ToDebugString,
            NULL,           // RW_BCD128_Enable,
            NULL,           // RW_BCD128_Disable,
            NULL,           // (P_OBJ_ASSIGN)RW_BCD128_Assign,
            NULL,           // (P_OBJ_COMPARE)RW_BCD128_Compare,
            NULL,           // (P_OBJ_PTR)RW_BCD128_Copy,
            NULL,           // (P_OBJ_PTR)RW_BCD128_DeepCopy,
            NULL            // (P_OBJ_HASH)RW_BCD128_Hash,
        },
        // Put other object method names below this.
        // Properties:
        // Methods:
        //RW_BCD128_IsEnabled,
     
    };



    static
    const
    OBJ_INFO            RW_BCD128_Info = {
        "RW_BCD128",
        "Binary Coded Decimal based on int128_t",
        (OBJ_DATA *)&RW_BCD128_ClassObj,
    #ifdef  RW_BCD128_SUPER_DEFINED
        (OBJ_DATA *)&obj_ClassObj,
    #else
        (OBJ_DATA *)&obj_ClassObj,
    #endif
        (OBJ_IUNKNOWN *)&RW_BCD128_Vtbl,
        sizeof(RW_BCD128_DATA)
    };



#ifdef  __cplusplus
}
#endif


