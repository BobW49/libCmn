// vi: nu:noai:ts=4:sw=4

//****************************************************************
// Report Program Generator (RPG) Base (RW_RPG_Base) Object Support
//****************************************************************

//  Class Object Metods and Tables for 'RW_RPG_Base'
//  Generated 05/31/2026 14:28:22


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




#define         RW_RPG_BASE_OBJECT_C       1
#include        <RW_RPG_Base_internal.h>
#ifdef  RW_RPG_BASE_SINGLETON
#include        <psxLock.h>
#endif


#ifdef  __cplusplus
extern "C" {
#endif
        
        

    //===========================================================
    //                  Class Object Definition
    //===========================================================

    struct RW_RPG_Base_class_data_s    {
        // Warning - OBJ_DATA must be first in this object!
        OBJ_DATA        super;
        
        // Common Data
    #ifdef  RW_RPG_BASE_SINGLETON
        volatile
        RW_RPG_BASE_DATA 
                        *pSingleton;
    #endif
        //uint32_t       misc;
        //OBJ_ID         pObjCatalog;
    };




    //-----------------------------------------------------------
    //                  Class Methods
    //-----------------------------------------------------------



    static
    void *          RW_RPG_BaseClass_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    static
    const
    OBJ_INFO            RW_RPG_Base_Info;            // Forward Reference




    static
    bool            RW_RPG_BaseClass_IsKindOf (
        uint16_t        classID
    )
    {
        OBJ_DATA        *pObj;
        
        if (OBJ_IDENT_RW_RPG_BASE_CLASS == classID) {
           return true;
        }
        if (OBJ_IDENT_OBJ_CLASS == classID) {
           return true;
        }
        
        pObj = obj_getInfo(RW_RPG_Base_Class())->pClassSuperObject;
        if (pObj == obj_BaseClass())
            ;
        else {
            return obj_getVtbl(pObj)->pIsKindOf(classID);
        }
        
        return false;
    }


    static
    uint16_t        RW_RPG_BaseClass_WhoAmI (
        void
    )
    {
        return OBJ_IDENT_RW_RPG_BASE_CLASS;
    }




    //===========================================================
    //                 Class Object Vtbl Definition
    //===========================================================

    static
    const
    RW_RPG_BASE_CLASS_VTBL 
                        class_Vtbl = {
        {
            &RW_RPG_Base_Info,
            RW_RPG_BaseClass_IsKindOf,
            obj_RetainNull,
            obj_ReleaseNull,
            NULL,
            RW_RPG_Base_Class,
            RW_RPG_BaseClass_WhoAmI,
            (P_OBJ_QUERYINFO)RW_RPG_BaseClass_QueryInfo,
            NULL                        // RW_RPG_BaseClass_ToDebugString
        },
        (void *)RW_RPG_Base_New
    };



    //-----------------------------------------------------------
    //                      Class Object
    //-----------------------------------------------------------

    RW_RPG_BASE_CLASS_DATA 
                        RW_RPG_Base_ClassObj = {
        {
            (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
            sizeof(RW_RPG_BASE_CLASS_DATA),         // cbSize
            0,                                      // cbFlags
            1,                                      // cbRetainCount
            {0}                                     // cbMisc
        },
        //0
    };



    //---------------------------------------------------------------
    //          S i n g l e t o n  M e t h o d s
    //---------------------------------------------------------------

    #ifdef  RW_RPG_BASE_SINGLETON
    extern
    const
    RW_RPG_BASE_VTBL    RW_RPG_Base_VtblShared;


    RW_RPG_BASE_DATA * 
                    RW_RPG_Base_getSingleton (
        void
    )
    {
        return (OBJ_ID)(RW_RPG_Base_ClassObj.pSingleton);
    }


    bool            RW_RPG_Base_setSingleton (
        RW_RPG_BASE_DATA 
                        *pValue
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
        if (RW_RPG_Base_ClassObj.pSingleton) {
            obj_Release((OBJ_ID)(RW_RPG_Base_ClassObj.pSingleton));
        }
        RW_RPG_Base_ClassObj.pSingleton = pValue;
        
        fRc = psxLock_Unlock(pLock);
        obj_Release(pLock);
        pLock = OBJ_NIL;
        return true;
    }



    RW_RPG_BASE_DATA * 
                    RW_RPG_Base_Shared (
        void
    )
    {
        RW_RPG_BASE_DATA 
                        *this = (OBJ_ID)(RW_RPG_Base_ClassObj.pSingleton);
        
        if (NULL == this) {
            this = RW_RPG_Base_New( );
            obj_setVtbl(this, (void *)&RW_RPG_Base_VtblShared);
            RW_RPG_Base_setSingleton(this);
            obj_Release(this);          // Shared controls object retention now.
            // RW_RPG_Base_ClassObj.pSingleton = OBJ_NIL;
        }
        
        return this;
    }



    void            RW_RPG_Base_SharedReset (
        void
    )
    {
        RW_RPG_BASE_DATA 
                        *this = (OBJ_ID)(RW_RPG_Base_ClassObj.pSingleton);
        
        if (this) {
            obj_setVtbl(this, (void *)&RW_RPG_Base_Vtbl);
            obj_Release(this);
            RW_RPG_Base_ClassObj.pSingleton = OBJ_NIL;
        }
        
    }



    #endif



    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------

    static
    void *          RW_RPG_BaseClass_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        RW_RPG_BASE_CLASS_DATA 
                        *this = objId;
        const
        char            *pStrA = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
        
        switch (type) {
          
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(RW_RPG_BASE_DATA);
                break;
                
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return this;
                break;
                
            // Query for an address to specific data within the object.  
            case OBJ_QUERYINFO_TYPE_DATA_PTR:
                switch (*pStrA) {
     
                    case 'C':
                        if (str_Compare("ClassInfo", (char *)pStrA) == 0) {
                            return (void *)&RW_RPG_Base_Info;
                        }
                        break;
                        
                    case 'S':
                        if (str_Compare("SuperClass", (char *)pStrA) == 0) {
                            return (void *)&RW_RPG_Base_Info.pClassSuperObject;
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
                            return RW_RPG_Base_New;
                        }
                        break;
                        
                    case 'P':
    #ifdef  RW_RPG_BASE_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStrA) == 0) {
                            return RW_RPG_Base_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStrA) == 0) {
                            return RW_RPG_Base_ParseJsonObject;
                        }
    #endif
                        break;

                    case 'T':
    #ifdef  RW_RPG_BASE_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStrA) == 0) {
                            return RW_RPG_Base_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStrA) == 0) {
                            return RW_RPG_Base_ToJson;
                        }
    #endif
                        break;

                     case 'W':
                        if (str_Compare("WhoAmI", (char *)pStrA) == 0) {
                            return RW_RPG_BaseClass_WhoAmI;
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
    bool            RW_RPG_Base_IsKindOf (
        uint16_t        classID
    )
    {
        OBJ_DATA        *pObj;
        const
        OBJ_INFO        *pInfo;

        if (OBJ_IDENT_RW_RPG_BASE == classID) {
           return true;
        }
        if (OBJ_IDENT_OBJ == classID) {
           return true;
        }

        pObj = obj_getInfo(RW_RPG_Base_Class())->pClassSuperObject;
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
    void            RW_RPG_Base_Dealloc (
        OBJ_ID          objId
    );


    OBJ_ID          RW_RPG_Base_Class (
        void
    )
    {
        return (OBJ_ID)&RW_RPG_Base_ClassObj;
    }


    static
    uint16_t        RW_RPG_Base_WhoAmI (
        void
    )
    {
        return OBJ_IDENT_RW_RPG_BASE;
    }





    //===========================================================
    //                  Object Vtbl Definition
    //===========================================================

    #ifdef  RW_RPG_BASE_SINGLETON
    // A Shared object ignores Retain() and Release() except for
    // initialization and termination. So, there must be an
    // independent VTbl from the normal which does support Retain()
    // and Release().
    const
    RW_RPG_BASE_VTBL    RW_RPG_Base_VtblShared = {
        {
            &RW_RPG_Base_Info,
            RW_RPG_Base_IsKindOf,
            obj_RetainNull,
            obj_ReleaseNull,
            RW_RPG_Base_Dealloc,
            RW_RPG_Base_Class,
            RW_RPG_Base_WhoAmI,
            (P_OBJ_QUERYINFO)RW_RPG_Base_QueryInfo,
            (P_OBJ_TOSTRING)RW_RPG_Base_ToDebugString,
            NULL,           // RW_RPG_Base_Enable,
            NULL,           // RW_RPG_Base_Disable,
            NULL,           // (P_OBJ_ASSIGN)RW_RPG_Base_Assign,
            NULL,           // (P_OBJ_COMPARE)RW_RPG_Base_Compare,
            NULL,           // (P_OBJ_PTR)RW_RPG_Base_Copy,
            NULL,           // (P_OBJ_PTR)RW_RPG_Base_DeepCopy,
            NULL            // (P_OBJ_HASH)RW_RPG_Base_Hash,
        },
        // Put other object method names below this.
        // Properties:
        // Methods:
        //RW_RPG_Base_IsEnabled,
     
    };
    #endif


    // This VTbl supports Retain() and Release() which is
    // used by objects other than the Shared object. These
    // objects can still be shared among other objects. It
    // just that they are deleted when their usage count
    // goes to zero.
    const
    RW_RPG_BASE_VTBL    RW_RPG_Base_Vtbl = {
        {
            &RW_RPG_Base_Info,
            RW_RPG_Base_IsKindOf,
            obj_RetainStandard,
            obj_ReleaseStandard,
            RW_RPG_Base_Dealloc,
            RW_RPG_Base_Class,
            RW_RPG_Base_WhoAmI,
            (P_OBJ_QUERYINFO)RW_RPG_Base_QueryInfo,
            (P_OBJ_TOSTRING)RW_RPG_Base_ToDebugString,
            NULL,           // RW_RPG_Base_Enable,
            NULL,           // RW_RPG_Base_Disable,
            NULL,           // (P_OBJ_ASSIGN)RW_RPG_Base_Assign,
            NULL,           // (P_OBJ_COMPARE)RW_RPG_Base_Compare,
            NULL,           // (P_OBJ_PTR)RW_RPG_Base_Copy,
            NULL,           // (P_OBJ_PTR)RW_RPG_Base_DeepCopy,
            NULL            // (P_OBJ_HASH)RW_RPG_Base_Hash,
        },
        // Put other object method names below this.
        // Properties:
        // Methods:
        //RW_RPG_Base_IsEnabled,
     
    };



    static
    const
    OBJ_INFO            RW_RPG_Base_Info = {
        "RW_RPG_Base",
        "Report Program Generator (RPG) Base",
        (OBJ_DATA *)&RW_RPG_Base_ClassObj,
    #ifdef  RW_RPG_BASE_SUPER_DEFINED
        (OBJ_DATA *)&obj_ClassObj,
    #else
        (OBJ_DATA *)&obj_ClassObj,
    #endif
        (OBJ_IUNKNOWN *)&RW_RPG_Base_Vtbl,
        sizeof(RW_RPG_BASE_DATA)
    };



#ifdef  __cplusplus
}
#endif


