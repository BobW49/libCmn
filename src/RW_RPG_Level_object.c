// vi: nu:noai:ts=4:sw=4

//****************************************************************
// Report Program Generator (RPG) Level (RW_RPG_Level) Object Support
//****************************************************************

//  Class Object Metods and Tables for 'RW_RPG_Level'
//  Generated 05/31/2026 14:28:59


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




#define         RW_RPG_LEVEL_OBJECT_C       1
#include        <RW_RPG_Level_internal.h>
#ifdef  RW_RPG_LEVEL_SINGLETON
#include        <psxLock.h>
#endif


#ifdef  __cplusplus
extern "C" {
#endif
        
        

    //===========================================================
    //                  Class Object Definition
    //===========================================================

    struct RW_RPG_Level_class_data_s    {
        // Warning - OBJ_DATA must be first in this object!
        OBJ_DATA        super;
        
        // Common Data
    #ifdef  RW_RPG_LEVEL_SINGLETON
        volatile
        RW_RPG_LEVEL_DATA 
                        *pSingleton;
    #endif
        //uint32_t       misc;
        //OBJ_ID         pObjCatalog;
    };




    //-----------------------------------------------------------
    //                  Class Methods
    //-----------------------------------------------------------



    static
    void *          RW_RPG_LevelClass_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    static
    const
    OBJ_INFO            RW_RPG_Level_Info;            // Forward Reference




    static
    bool            RW_RPG_LevelClass_IsKindOf (
        uint16_t        classID
    )
    {
        OBJ_DATA        *pObj;
        
        if (OBJ_IDENT_RW_RPG_LEVEL_CLASS == classID) {
           return true;
        }
        if (OBJ_IDENT_OBJ_CLASS == classID) {
           return true;
        }
        
        pObj = obj_getInfo(RW_RPG_Level_Class())->pClassSuperObject;
        if (pObj == obj_BaseClass())
            ;
        else {
            return obj_getVtbl(pObj)->pIsKindOf(classID);
        }
        
        return false;
    }


    static
    uint16_t        RW_RPG_LevelClass_WhoAmI (
        void
    )
    {
        return OBJ_IDENT_RW_RPG_LEVEL_CLASS;
    }




    //===========================================================
    //                 Class Object Vtbl Definition
    //===========================================================

    static
    const
    RW_RPG_LEVEL_CLASS_VTBL 
                        class_Vtbl = {
        {
            &RW_RPG_Level_Info,
            RW_RPG_LevelClass_IsKindOf,
            obj_RetainNull,
            obj_ReleaseNull,
            NULL,
            RW_RPG_Level_Class,
            RW_RPG_LevelClass_WhoAmI,
            (P_OBJ_QUERYINFO)RW_RPG_LevelClass_QueryInfo,
            NULL                        // RW_RPG_LevelClass_ToDebugString
        },
        (void *)RW_RPG_Level_New
    };



    //-----------------------------------------------------------
    //                      Class Object
    //-----------------------------------------------------------

    RW_RPG_LEVEL_CLASS_DATA 
                        RW_RPG_Level_ClassObj = {
        {
            (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
            sizeof(RW_RPG_LEVEL_CLASS_DATA),        // cbSize
            0,                                      // cbFlags
            1,                                      // cbRetainCount
            {0}                                     // cbMisc
        },
        //0
    };



    //---------------------------------------------------------------
    //          S i n g l e t o n  M e t h o d s
    //---------------------------------------------------------------

    #ifdef  RW_RPG_LEVEL_SINGLETON
    extern
    const
    RW_RPG_LEVEL_VTBL   RW_RPG_Level_VtblShared;


    RW_RPG_LEVEL_DATA * 
                    RW_RPG_Level_getSingleton (
        void
    )
    {
        return (OBJ_ID)(RW_RPG_Level_ClassObj.pSingleton);
    }


    bool            RW_RPG_Level_setSingleton (
        RW_RPG_LEVEL_DATA 
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
        if (RW_RPG_Level_ClassObj.pSingleton) {
            obj_Release((OBJ_ID)(RW_RPG_Level_ClassObj.pSingleton));
        }
        RW_RPG_Level_ClassObj.pSingleton = pValue;
        
        fRc = psxLock_Unlock(pLock);
        obj_Release(pLock);
        pLock = OBJ_NIL;
        return true;
    }



    RW_RPG_LEVEL_DATA * 
                    RW_RPG_Level_Shared (
        void
    )
    {
        RW_RPG_LEVEL_DATA 
                        *this = (OBJ_ID)(RW_RPG_Level_ClassObj.pSingleton);
        
        if (NULL == this) {
            this = RW_RPG_Level_New( );
            obj_setVtbl(this, (void *)&RW_RPG_Level_VtblShared);
            RW_RPG_Level_setSingleton(this);
            obj_Release(this);          // Shared controls object retention now.
            // RW_RPG_Level_ClassObj.pSingleton = OBJ_NIL;
        }
        
        return this;
    }



    void            RW_RPG_Level_SharedReset (
        void
    )
    {
        RW_RPG_LEVEL_DATA 
                        *this = (OBJ_ID)(RW_RPG_Level_ClassObj.pSingleton);
        
        if (this) {
            obj_setVtbl(this, (void *)&RW_RPG_Level_Vtbl);
            obj_Release(this);
            RW_RPG_Level_ClassObj.pSingleton = OBJ_NIL;
        }
        
    }



    #endif



    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------

    static
    void *          RW_RPG_LevelClass_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        RW_RPG_LEVEL_CLASS_DATA 
                        *this = objId;
        const
        char            *pStrA = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
        
        switch (type) {
          
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(RW_RPG_LEVEL_DATA);
                break;
                
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return this;
                break;
                
            // Query for an address to specific data within the object.  
            case OBJ_QUERYINFO_TYPE_DATA_PTR:
                switch (*pStrA) {
     
                    case 'C':
                        if (str_Compare("ClassInfo", (char *)pStrA) == 0) {
                            return (void *)&RW_RPG_Level_Info;
                        }
                        break;
                        
                    case 'S':
                        if (str_Compare("SuperClass", (char *)pStrA) == 0) {
                            return (void *)&RW_RPG_Level_Info.pClassSuperObject;
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
                            return RW_RPG_Level_New;
                        }
                        break;
                        
                    case 'P':
    #ifdef  RW_RPG_LEVEL_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStrA) == 0) {
                            return RW_RPG_Level_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStrA) == 0) {
                            return RW_RPG_Level_ParseJsonObject;
                        }
    #endif
                        break;

                    case 'T':
    #ifdef  RW_RPG_LEVEL_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStrA) == 0) {
                            return RW_RPG_Level_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStrA) == 0) {
                            return RW_RPG_Level_ToJson;
                        }
    #endif
                        break;

                     case 'W':
                        if (str_Compare("WhoAmI", (char *)pStrA) == 0) {
                            return RW_RPG_LevelClass_WhoAmI;
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
    bool            RW_RPG_Level_IsKindOf (
        uint16_t        classID
    )
    {
        OBJ_DATA        *pObj;
        const
        OBJ_INFO        *pInfo;

        if (OBJ_IDENT_RW_RPG_LEVEL == classID) {
           return true;
        }
        if (OBJ_IDENT_OBJ == classID) {
           return true;
        }

        pObj = obj_getInfo(RW_RPG_Level_Class())->pClassSuperObject;
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
    void            RW_RPG_Level_Dealloc (
        OBJ_ID          objId
    );


    OBJ_ID          RW_RPG_Level_Class (
        void
    )
    {
        return (OBJ_ID)&RW_RPG_Level_ClassObj;
    }


    static
    uint16_t        RW_RPG_Level_WhoAmI (
        void
    )
    {
        return OBJ_IDENT_RW_RPG_LEVEL;
    }





    //===========================================================
    //                  Object Vtbl Definition
    //===========================================================

    #ifdef  RW_RPG_LEVEL_SINGLETON
    // A Shared object ignores Retain() and Release() except for
    // initialization and termination. So, there must be an
    // independent VTbl from the normal which does support Retain()
    // and Release().
    const
    RW_RPG_LEVEL_VTBL   RW_RPG_Level_VtblShared = {
        {
            &RW_RPG_Level_Info,
            RW_RPG_Level_IsKindOf,
            obj_RetainNull,
            obj_ReleaseNull,
            RW_RPG_Level_Dealloc,
            RW_RPG_Level_Class,
            RW_RPG_Level_WhoAmI,
            (P_OBJ_QUERYINFO)RW_RPG_Level_QueryInfo,
            (P_OBJ_TOSTRING)RW_RPG_Level_ToDebugString,
            NULL,           // RW_RPG_Level_Enable,
            NULL,           // RW_RPG_Level_Disable,
            NULL,           // (P_OBJ_ASSIGN)RW_RPG_Level_Assign,
            NULL,           // (P_OBJ_COMPARE)RW_RPG_Level_Compare,
            NULL,           // (P_OBJ_PTR)RW_RPG_Level_Copy,
            NULL,           // (P_OBJ_PTR)RW_RPG_Level_DeepCopy,
            NULL            // (P_OBJ_HASH)RW_RPG_Level_Hash,
        },
        // Put other object method names below this.
        // Properties:
        // Methods:
        //RW_RPG_Level_IsEnabled,
     
    };
    #endif


    // This VTbl supports Retain() and Release() which is
    // used by objects other than the Shared object. These
    // objects can still be shared among other objects. It
    // just that they are deleted when their usage count
    // goes to zero.
    const
    RW_RPG_LEVEL_VTBL   RW_RPG_Level_Vtbl = {
        {
            &RW_RPG_Level_Info,
            RW_RPG_Level_IsKindOf,
            obj_RetainStandard,
            obj_ReleaseStandard,
            RW_RPG_Level_Dealloc,
            RW_RPG_Level_Class,
            RW_RPG_Level_WhoAmI,
            (P_OBJ_QUERYINFO)RW_RPG_Level_QueryInfo,
            (P_OBJ_TOSTRING)RW_RPG_Level_ToDebugString,
            NULL,           // RW_RPG_Level_Enable,
            NULL,           // RW_RPG_Level_Disable,
            NULL,           // (P_OBJ_ASSIGN)RW_RPG_Level_Assign,
            NULL,           // (P_OBJ_COMPARE)RW_RPG_Level_Compare,
            NULL,           // (P_OBJ_PTR)RW_RPG_Level_Copy,
            NULL,           // (P_OBJ_PTR)RW_RPG_Level_DeepCopy,
            NULL            // (P_OBJ_HASH)RW_RPG_Level_Hash,
        },
        // Put other object method names below this.
        // Properties:
        // Methods:
        //RW_RPG_Level_IsEnabled,
     
    };



    static
    const
    OBJ_INFO            RW_RPG_Level_Info = {
        "RW_RPG_Level",
        "Report Program Generator (RPG) Level",
        (OBJ_DATA *)&RW_RPG_Level_ClassObj,
    #ifdef  RW_RPG_LEVEL_SUPER_DEFINED
        (OBJ_DATA *)&obj_ClassObj,
    #else
        (OBJ_DATA *)&obj_ClassObj,
    #endif
        (OBJ_IUNKNOWN *)&RW_RPG_Level_Vtbl,
        sizeof(RW_RPG_LEVEL_DATA)
    };



#ifdef  __cplusplus
}
#endif


