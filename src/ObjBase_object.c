// vi: nu:noai:ts=4:sw=4

//****************************************************************
//          Base for All Objects (ObjBase) Object Support
//****************************************************************

//  Class Object Metods and Tables for 'ObjBase'
//  Generated 02/24/2025 10:18:39


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




#define         OBJBASE_OBJECT_C       1
#include        <ObjBase_internal.h>
#ifdef  OBJBASE_SINGLETON
#include        <psxLock.h>
#endif


#ifdef  __cplusplus
extern "C" {
#endif
        
        

    //===========================================================
    //                  Class Object Definition
    //===========================================================

    struct ObjBase_class_data_s    {
        // Warning - OBJ_DATA must be first in this object!
        OBJBASE_DATA    super;
        
        // Common Data
    #ifdef  OBJBASE_SINGLETON
        volatile
        OBJBASE_DATA    *pSingleton;
    #endif
        //uint32_t       misc;
        //OBJ_ID         pObjCatalog;
    };




    //-----------------------------------------------------------
    //                  Class Methods
    //-----------------------------------------------------------



    static
    void *          ObjBaseClass_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    static
    const
    OBJ_INFO            ObjBase_Info;            // Forward Reference




    static
    bool            ObjBaseClass_IsKindOf (
        uint16_t        classID
    )
    {
        OBJBASE_DATA    *pObj;
        const
        OBJ_INFO        *pInfo = NULL;

        if (OBJ_IDENT_OBJBASE_CLASS == classID) {
           return true;
        }
        if (OBJ_IDENT_OBJ_CLASS == classID) {
           return true;
        }
        
        pInfo = ObjBase_getInfo(ObjBase_Class());
        if (pInfo) {
            pObj = ObjBase_getInfo(ObjBase_Class())->pClassSuperObject;
            if (pObj == ObjBase_BaseClass())
                ;
            else {
                return ObjBase_getVtbl(pObj)->pIsKindOf(classID);
            }
        }
        
        return false;
    }


    static
    uint16_t        ObjBaseClass_WhoAmI (
        void
    )
    {
        return OBJ_IDENT_OBJBASE_CLASS;
    }




    //===========================================================
    //                 Class Object Vtbl Definition
    //===========================================================

    static
    const
    OBJBASE_CLASS_VTBL  class_Vtbl = {
        {
            &ObjBase_Info,
            ObjBaseClass_IsKindOf,
            obj_RetainNull,
            obj_ReleaseNull,
            NULL,
            ObjBase_Class,
            ObjBaseClass_WhoAmI,
            (P_OBJ_QUERYINFO)ObjBaseClass_QueryInfo,
            NULL                        // ObjBaseClass_ToDebugString
        },
        (void *)ObjBase_New
    };



    //-----------------------------------------------------------
    //                      Class Object
    //-----------------------------------------------------------

    OBJBASE_CLASS_DATA  ObjBase_ClassObj = {
        OBJBASE_DATA_GEN(class_Vtbl, OBJBASE_CLASS_DATA, 0, 1),
        //0
    };



    //---------------------------------------------------------------
    //          S i n g l e t o n  M e t h o d s
    //---------------------------------------------------------------

    #ifdef  OBJBASE_SINGLETON
    extern
    const
    OBJBASE_VTBL        ObjBase_VtblShared;


    OBJBASE_DATA *  ObjBase_getSingleton (
        void
    )
    {
        return (OBJ_ID)(ObjBase_ClassObj.pSingleton);
    }


    bool            ObjBase_setSingleton (
        OBJBASE_DATA    *pValue
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
        if (ObjBase_ClassObj.pSingleton) {
            obj_Release((OBJ_ID)(ObjBase_ClassObj.pSingleton));
        }
        ObjBase_ClassObj.pSingleton = pValue;
        
        fRc = psxLock_Unlock(pLock);
        obj_Release(pLock);
        pLock = OBJ_NIL;
        return true;
    }



    OBJBASE_DATA *  ObjBase_Shared (
        void
    )
    {
        OBJBASE_DATA    *this = (OBJ_ID)(ObjBase_ClassObj.pSingleton);
        
        if (NULL == this) {
            this = ObjBase_New( );
            obj_setVtbl(this, (void *)&ObjBase_VtblShared);
            ObjBase_setSingleton(this);
            obj_Release(this);          // Shared controls object retention now.
            // ObjBase_ClassObj.pSingleton = OBJ_NIL;
        }
        
        return this;
    }



    void            ObjBase_SharedReset (
        void
    )
    {
        OBJBASE_DATA    *this = (OBJ_ID)(ObjBase_ClassObj.pSingleton);
        
        if (this) {
            obj_setVtbl(this, (void *)&ObjBase_Vtbl);
            obj_Release(this);
            ObjBase_ClassObj.pSingleton = OBJ_NIL;
        }
        
    }



    #endif



    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------

    static
    void *          ObjBaseClass_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        OBJBASE_CLASS_DATA 
                        *this = objId;
        const
        char            *pStrA = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
        
        switch (type) {
          
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(OBJBASE_DATA);
                break;
                
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return this;
                break;
                
            // Query for an address to specific data within the object.  
            case OBJ_QUERYINFO_TYPE_DATA_PTR:
                switch (*pStrA) {
     
                    case 'C':
                        if (str_Compare("ClassInfo", (char *)pStrA) == 0) {
                            return (void *)&ObjBase_Info;
                        }
                        break;
                        
                    case 'S':
                        if (str_Compare("SuperClass", (char *)pStrA) == 0) {
                            return (void *)&ObjBase_Info.pClassSuperObject;
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
                            return ObjBase_New;
                        }
                        break;
                        
                    case 'P':
    #ifdef  OBJBASE_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStrA) == 0) {
                            return ObjBase_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStrA) == 0) {
                            return ObjBase_ParseJsonObject;
                        }
    #endif
                        break;

                    case 'T':
    #ifdef  OBJBASE_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStrA) == 0) {
                            return ObjBase_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStrA) == 0) {
                            return ObjBase_ToJson;
                        }
    #endif
                        break;

                     case 'W':
                        if (str_Compare("WhoAmI", (char *)pStrA) == 0) {
                            return ObjBaseClass_WhoAmI;
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
    bool            ObjBase_IsKindOf (
        uint16_t        classID
    )
    {
        OBJ_DATA        *pObj;
        const
        OBJ_INFO        *pInfo;

        if (OBJ_IDENT_OBJBASE == classID) {
           return true;
        }
        if (OBJ_IDENT_OBJ == classID) {
           return true;
        }

        pObj = obj_getInfo(ObjBase_Class())->pClassSuperObject;
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
    void            ObjBase_Dealloc (
        OBJ_ID          objId
    );


    OBJ_ID          ObjBase_Class (
        void
    )
    {
        return (OBJ_ID)&ObjBase_ClassObj;
    }


    static
    uint16_t        ObjBase_WhoAmI (
        void
    )
    {
        return OBJ_IDENT_OBJBASE;
    }





    //===========================================================
    //                  Object Vtbl Definition
    //===========================================================

    #ifdef  OBJBASE_SINGLETON
    // A Shared object ignores Retain() and Release() except for
    // initialization and termination. So, there must be an
    // independent VTbl from the normal which does support Retain()
    // and Release().
    const
    OBJBASE_VTBL        ObjBase_VtblShared = {
        {
            &ObjBase_Info,
            ObjBase_IsKindOf,
            obj_RetainNull,
            obj_ReleaseNull,
            ObjBase_Dealloc,
            ObjBase_Class,
            ObjBase_WhoAmI,
            (P_OBJ_QUERYINFO)ObjBase_QueryInfo,
            (P_OBJ_TOSTRING)ObjBase_ToDebugString,
            NULL,           // ObjBase_Enable,
            NULL,           // ObjBase_Disable,
            NULL,           // (P_OBJ_ASSIGN)ObjBase_Assign,
            NULL,           // (P_OBJ_COMPARE)ObjBase_Compare,
            NULL,           // (P_OBJ_PTR)ObjBase_Copy,
            NULL,           // (P_OBJ_PTR)ObjBase_DeepCopy,
            NULL            // (P_OBJ_HASH)ObjBase_Hash,
        },
        // Put other object method names below this.
        // Properties:
        // Methods:
        //ObjBase_IsEnabled,
     
    };
    #endif


    // This VTbl supports Retain() and Release() which is
    // used by objects other than the Shared object. These
    // objects can still be shared among other objects. It
    // just that they are deleted when their usage count
    // goes to zero.
    const
    OBJBASE_VTBL        ObjBase_Vtbl = {
        {
            &ObjBase_Info,
            ObjBase_IsKindOf,
            obj_RetainStandard,
            obj_ReleaseStandard,
            ObjBase_Dealloc,
            ObjBase_Class,
            ObjBase_WhoAmI,
            (P_OBJ_QUERYINFO)ObjBase_QueryInfo,
            (P_OBJ_TOSTRING)ObjBase_ToDebugString,
            NULL,           // ObjBase_Enable,
            NULL,           // ObjBase_Disable,
            NULL,           // (P_OBJ_ASSIGN)ObjBase_Assign,
            NULL,           // (P_OBJ_COMPARE)ObjBase_Compare,
            NULL,           // (P_OBJ_PTR)ObjBase_Copy,
            NULL,           // (P_OBJ_PTR)ObjBase_DeepCopy,
            NULL            // (P_OBJ_HASH)ObjBase_Hash,
        },
        // Put other object method names below this.
        // Properties:
        // Methods:
        //ObjBase_IsEnabled,
     
    };



    static
    const
    OBJ_INFO            ObjBase_Info = {
        "ObjBase",
        "Base for All Objects",
        (OBJ_DATA *)&ObjBase_ClassObj,
    #ifdef  OBJBASE_SUPER_DEFINED
        (OBJ_DATA *)&obj_ClassObj,
    #else
        (OBJ_DATA *)&obj_ClassObj,
    #endif
        (OBJ_IUNKNOWN *)&ObjBase_Vtbl,
        sizeof(OBJBASE_DATA)
    };



#ifdef  __cplusplus
}
#endif


