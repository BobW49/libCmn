// vi: nu:noai:ts=4:sw=4

//****************************************************************
//              Base Object which everything inherits from (Object) Object Support
//****************************************************************

//  Class Object Metods and Tables for 'Object'
//  Generated 06/21/2026 13:29:28


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




#define         OBJECT_OBJECT_C       1
#include        <Object_internal.h>
#ifdef  OBJECT_SINGLETON
#include        <psxLock.h>
#endif


#ifdef  __cplusplus
extern "C" {
#endif
        
        

    //===========================================================
    //                  Class Object Definition
    //===========================================================

    struct Object_class_data_s    {
        // Warning - OBJ_DATA must be first in this object!
        OBJ_DATA        super;
        
        // Common Data
    #ifdef  OBJECT_SINGLETON
        volatile
        OBJECT_DATA     *pSingleton;
    #endif
        //uint32_t       misc;
        //OBJ_ID         pObjCatalog;
    };




    //-----------------------------------------------------------
    //                  Class Methods
    //-----------------------------------------------------------



    static
    void *          ObjectClass_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    static
    const
    OBJ_INFO            Object_Info;            // Forward Reference




    static
    bool            ObjectClass_IsKindOf (
        uint16_t        classID
    )
    {
        OBJ_DATA        *pObj;
        
        if (OBJ_IDENT_OBJECT_CLASS == classID) {
           return true;
        }
        if (OBJ_IDENT_OBJ_CLASS == classID) {
           return true;
        }
        
        pObj = obj_getInfo(Object_Class())->pClassSuperObject;
        if (pObj == obj_BaseClass())
            ;
        else {
            return obj_getVtbl(pObj)->pIsKindOf(classID);
        }
        
        return false;
    }


    static
    uint16_t        ObjectClass_WhoAmI (
        void
    )
    {
        return OBJ_IDENT_OBJECT_CLASS;
    }




    //===========================================================
    //                 Class Object Vtbl Definition
    //===========================================================

    static
    const
    OBJECT_CLASS_VTBL   class_Vtbl = {
        {
            &Object_Info,
            ObjectClass_IsKindOf,
            obj_RetainNull,
            obj_ReleaseNull,
            NULL,
            Object_Class,
            ObjectClass_WhoAmI,
            (P_OBJ_QUERYINFO)ObjectClass_QueryInfo,
            NULL                        // ObjectClass_ToDebugString
        },
        (void *)Object_New
    };



    //-----------------------------------------------------------
    //                      Class Object
    //-----------------------------------------------------------

    OBJECT_CLASS_DATA   Object_ClassObj = {
        {
            (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
            sizeof(OBJECT_CLASS_DATA),              // cbSize
            0,                                      // cbFlags
            1,                                      // cbRetainCount
            {0}                                     // cbMisc
        },
        //0
    };



    //---------------------------------------------------------------
    //          S i n g l e t o n  M e t h o d s
    //---------------------------------------------------------------

    #ifdef  OBJECT_SINGLETON
    extern
    const
    OBJECT_VTBL         Object_VtblShared;


    OBJECT_DATA *   Object_getSingleton (
        void
    )
    {
        return (OBJ_ID)(Object_ClassObj.pSingleton);
    }


    bool            Object_setSingleton (
        OBJECT_DATA     *pValue
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
        if (Object_ClassObj.pSingleton) {
            obj_Release((OBJ_ID)(Object_ClassObj.pSingleton));
        }
        Object_ClassObj.pSingleton = pValue;
        
        fRc = psxLock_Unlock(pLock);
        obj_Release(pLock);
        pLock = OBJ_NIL;
        return true;
    }



    OBJECT_DATA *   Object_Shared (
        void
    )
    {
        OBJECT_DATA     *this = (OBJ_ID)(Object_ClassObj.pSingleton);
        
        if (NULL == this) {
            this = Object_New( );
            obj_setVtbl(this, (void *)&Object_VtblShared);
            Object_setSingleton(this);
            obj_Release(this);          // Shared controls object retention now.
            // Object_ClassObj.pSingleton = OBJ_NIL;
        }
        
        return this;
    }



    void            Object_SharedReset (
        void
    )
    {
        OBJECT_DATA     *this = (OBJ_ID)(Object_ClassObj.pSingleton);
        
        if (this) {
            obj_setVtbl(this, (void *)&Object_Vtbl);
            obj_Release(this);
            Object_ClassObj.pSingleton = OBJ_NIL;
        }
        
    }



    #endif



    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------

    static
    void *          ObjectClass_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        OBJECT_CLASS_DATA 
                        *this = objId;
        const
        char            *pStrA = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
        
        switch (type) {
          
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(OBJECT_DATA);
                break;
                
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return this;
                break;
                
            // Query for an address to specific data within the object.  
            case OBJ_QUERYINFO_TYPE_DATA_PTR:
                switch (*pStrA) {
     
                    case 'C':
                        if (str_Compare("ClassInfo", (char *)pStrA) == 0) {
                            return (void *)&Object_Info;
                        }
                        break;
                        
                    case 'S':
                        if (str_Compare("SuperClass", (char *)pStrA) == 0) {
                            return (void *)&Object_Info.pClassSuperObject;
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
                            return Object_New;
                        }
                        break;
                        
                    case 'P':
    #ifdef  OBJECT_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStrA) == 0) {
                            return Object_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStrA) == 0) {
                            return Object_ParseJsonObject;
                        }
    #endif
                        break;

                    case 'T':
    #ifdef  OBJECT_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStrA) == 0) {
                            return Object_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStrA) == 0) {
                            return Object_ToJson;
                        }
    #endif
                        break;

                     case 'W':
                        if (str_Compare("WhoAmI", (char *)pStrA) == 0) {
                            return ObjectClass_WhoAmI;
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
    bool            Object_IsKindOf (
        uint16_t        classID
    )
    {
        OBJ_DATA        *pObj;
        const
        OBJ_INFO        *pInfo;

        if (OBJ_IDENT_OBJECT == classID) {
           return true;
        }
        if (OBJ_IDENT_OBJ == classID) {
           return true;
        }

        pObj = obj_getInfo(Object_Class())->pClassSuperObject;
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
    void            Object_Dealloc (
        OBJ_ID          objId
    );


    OBJ_ID          Object_Class (
        void
    )
    {
        return (OBJ_ID)&Object_ClassObj;
    }


    static
    uint16_t        Object_WhoAmI (
        void
    )
    {
        return OBJ_IDENT_OBJECT;
    }





    //===========================================================
    //                  Object Vtbl Definition
    //===========================================================

    #ifdef  OBJECT_SINGLETON
    // A Shared object ignores Retain() and Release() except for
    // initialization and termination. So, there must be an
    // independent VTbl from the normal which does support Retain()
    // and Release().
    const
    OBJECT_VTBL         Object_VtblShared = {
        {
            &Object_Info,
            Object_IsKindOf,
            obj_RetainNull,
            obj_ReleaseNull,
            Object_Dealloc,
            Object_Class,
            Object_WhoAmI,
            (P_OBJ_QUERYINFO)Object_QueryInfo,
            (P_OBJ_TOSTRING)Object_ToDebugString,
            NULL,           // Object_Enable,
            NULL,           // Object_Disable,
            NULL,           // (P_OBJ_ASSIGN)Object_Assign,
            NULL,           // (P_OBJ_COMPARE)Object_Compare,
            NULL,           // (P_OBJ_PTR)Object_Copy,
            NULL,           // (P_OBJ_PTR)Object_DeepCopy,
            NULL            // (P_OBJ_HASH)Object_Hash,
        },
        // Put other object method names below this.
        // Properties:
        // Methods:
        //Object_IsEnabled,
     
    };
    #endif


    // This VTbl supports Retain() and Release() which is
    // used by objects other than the Shared object. These
    // objects can still be shared among other objects. It
    // just that they are deleted when their usage count
    // goes to zero.
    const
    OBJECT_VTBL         Object_Vtbl = {
        {
            &Object_Info,
            Object_IsKindOf,
            obj_RetainStandard,
            obj_ReleaseStandard,
            Object_Dealloc,
            Object_Class,
            Object_WhoAmI,
            (P_OBJ_QUERYINFO)Object_QueryInfo,
            (P_OBJ_TOSTRING)Object_ToDebugString,
            NULL,           // Object_Enable,
            NULL,           // Object_Disable,
            NULL,           // (P_OBJ_ASSIGN)Object_Assign,
            NULL,           // (P_OBJ_COMPARE)Object_Compare,
            NULL,           // (P_OBJ_PTR)Object_Copy,
            NULL,           // (P_OBJ_PTR)Object_DeepCopy,
            NULL            // (P_OBJ_HASH)Object_Hash,
        },
        // Put other object method names below this.
        // Properties:
        // Methods:
        //Object_IsEnabled,
     
    };



    static
    const
    OBJ_INFO            Object_Info = {
        "Object",
        "Base Object which everything inherits from",
        (OBJ_DATA *)&Object_ClassObj,
    #ifdef  OBJECT_SUPER_DEFINED
        (OBJ_DATA *)&obj_ClassObj,
    #else
        (OBJ_DATA *)&obj_ClassObj,
    #endif
        (OBJ_IUNKNOWN *)&Object_Vtbl,
        sizeof(OBJECT_DATA)
    };



#ifdef  __cplusplus
}
#endif


