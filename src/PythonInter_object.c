// vi: nu:noai:ts=4:sw=4

//****************************************************************
// Python Interface to/from Objects (PythonInter) Object Support
//****************************************************************

//  Class Object Metods and Tables for 'PythonInter'
//  Generated 05/21/2026 07:03:39


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




#define         PYTHONINTER_OBJECT_C       1
#include        <PythonInter_internal.h>
#ifdef  PYTHONINTER_SINGLETON
#include        <psxLock.h>
#endif


#ifdef  __cplusplus
extern "C" {
#endif
        
        

    //===========================================================
    //                  Class Object Definition
    //===========================================================

    struct PythonInter_class_data_s    {
        // Warning - OBJ_DATA must be first in this object!
        OBJ_DATA        super;
        
        // Common Data
    #ifdef  PYTHONINTER_SINGLETON
        volatile
        PYTHONINTER_DATA 
                        *pSingleton;
    #endif
        //uint32_t       misc;
        //OBJ_ID         pObjCatalog;
    };




    //-----------------------------------------------------------
    //                  Class Methods
    //-----------------------------------------------------------



    static
    void *          PythonInterClass_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    static
    const
    OBJ_INFO            PythonInter_Info;            // Forward Reference




    static
    bool            PythonInterClass_IsKindOf (
        uint16_t        classID
    )
    {
        OBJ_DATA        *pObj;
        
        if (OBJ_IDENT_PYTHONINTER_CLASS == classID) {
           return true;
        }
        if (OBJ_IDENT_OBJ_CLASS == classID) {
           return true;
        }
        
        pObj = obj_getInfo(PythonInter_Class())->pClassSuperObject;
        if (pObj == obj_BaseClass())
            ;
        else {
            return obj_getVtbl(pObj)->pIsKindOf(classID);
        }
        
        return false;
    }


    static
    uint16_t        PythonInterClass_WhoAmI (
        void
    )
    {
        return OBJ_IDENT_PYTHONINTER_CLASS;
    }




    //===========================================================
    //                 Class Object Vtbl Definition
    //===========================================================

    static
    const
    PYTHONINTER_CLASS_VTBL 
                        class_Vtbl = {
        {
            &PythonInter_Info,
            PythonInterClass_IsKindOf,
            obj_RetainNull,
            obj_ReleaseNull,
            NULL,
            PythonInter_Class,
            PythonInterClass_WhoAmI,
            (P_OBJ_QUERYINFO)PythonInterClass_QueryInfo,
            NULL                        // PythonInterClass_ToDebugString
        },
        (void *)PythonInter_New
    };



    //-----------------------------------------------------------
    //                      Class Object
    //-----------------------------------------------------------

    PYTHONINTER_CLASS_DATA 
                        PythonInter_ClassObj = {
        {
            (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
            sizeof(PYTHONINTER_CLASS_DATA),         // cbSize
            0,                                      // cbFlags
            1,                                      // cbRetainCount
            {0}                                     // cbMisc
        },
        //0
    };



    //---------------------------------------------------------------
    //          S i n g l e t o n  M e t h o d s
    //---------------------------------------------------------------

    #ifdef  PYTHONINTER_SINGLETON
    extern
    const
    PYTHONINTER_VTBL    PythonInter_VtblShared;


    PYTHONINTER_DATA * 
                    PythonInter_getSingleton (
        void
    )
    {
        return (OBJ_ID)(PythonInter_ClassObj.pSingleton);
    }


    bool            PythonInter_setSingleton (
        PYTHONINTER_DATA 
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
        if (PythonInter_ClassObj.pSingleton) {
            obj_Release((OBJ_ID)(PythonInter_ClassObj.pSingleton));
        }
        PythonInter_ClassObj.pSingleton = pValue;
        
        fRc = psxLock_Unlock(pLock);
        obj_Release(pLock);
        pLock = OBJ_NIL;
        return true;
    }



    PYTHONINTER_DATA * 
                    PythonInter_Shared (
        void
    )
    {
        PYTHONINTER_DATA 
                        *this = (OBJ_ID)(PythonInter_ClassObj.pSingleton);
        
        if (NULL == this) {
            this = PythonInter_New( );
            obj_setVtbl(this, (void *)&PythonInter_VtblShared);
            PythonInter_setSingleton(this);
            obj_Release(this);          // Shared controls object retention now.
            // PythonInter_ClassObj.pSingleton = OBJ_NIL;
        }
        
        return this;
    }



    void            PythonInter_SharedReset (
        void
    )
    {
        PYTHONINTER_DATA 
                        *this = (OBJ_ID)(PythonInter_ClassObj.pSingleton);
        
        if (this) {
            obj_setVtbl(this, (void *)&PythonInter_Vtbl);
            obj_Release(this);
            PythonInter_ClassObj.pSingleton = OBJ_NIL;
        }
        
    }



    #endif



    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------

    static
    void *          PythonInterClass_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        PYTHONINTER_CLASS_DATA 
                        *this = objId;
        const
        char            *pStrA = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
        
        switch (type) {
          
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(PYTHONINTER_DATA);
                break;
                
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return this;
                break;
                
            // Query for an address to specific data within the object.  
            case OBJ_QUERYINFO_TYPE_DATA_PTR:
                switch (*pStrA) {
     
                    case 'C':
                        if (str_Compare("ClassInfo", (char *)pStrA) == 0) {
                            return (void *)&PythonInter_Info;
                        }
                        break;
                        
                    case 'S':
                        if (str_Compare("SuperClass", (char *)pStrA) == 0) {
                            return (void *)&PythonInter_Info.pClassSuperObject;
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
                            return PythonInter_New;
                        }
                        break;
                        
                    case 'P':
    #ifdef  PYTHONINTER_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStrA) == 0) {
                            return PythonInter_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStrA) == 0) {
                            return PythonInter_ParseJsonObject;
                        }
    #endif
                        break;

                    case 'T':
    #ifdef  PYTHONINTER_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStrA) == 0) {
                            return PythonInter_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStrA) == 0) {
                            return PythonInter_ToJson;
                        }
    #endif
                        break;

                     case 'W':
                        if (str_Compare("WhoAmI", (char *)pStrA) == 0) {
                            return PythonInterClass_WhoAmI;
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
    bool            PythonInter_IsKindOf (
        uint16_t        classID
    )
    {
        OBJ_DATA        *pObj;
        const
        OBJ_INFO        *pInfo;

        if (OBJ_IDENT_PYTHONINTER == classID) {
           return true;
        }
        if (OBJ_IDENT_OBJ == classID) {
           return true;
        }

        pObj = obj_getInfo(PythonInter_Class())->pClassSuperObject;
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
    void            PythonInter_Dealloc (
        OBJ_ID          objId
    );


    OBJ_ID          PythonInter_Class (
        void
    )
    {
        return (OBJ_ID)&PythonInter_ClassObj;
    }


    static
    uint16_t        PythonInter_WhoAmI (
        void
    )
    {
        return OBJ_IDENT_PYTHONINTER;
    }





    //===========================================================
    //                  Object Vtbl Definition
    //===========================================================

    #ifdef  PYTHONINTER_SINGLETON
    // A Shared object ignores Retain() and Release() except for
    // initialization and termination. So, there must be an
    // independent VTbl from the normal which does support Retain()
    // and Release().
    const
    PYTHONINTER_VTBL    PythonInter_VtblShared = {
        {
            &PythonInter_Info,
            PythonInter_IsKindOf,
            obj_RetainNull,
            obj_ReleaseNull,
            PythonInter_Dealloc,
            PythonInter_Class,
            PythonInter_WhoAmI,
            (P_OBJ_QUERYINFO)PythonInter_QueryInfo,
            (P_OBJ_TOSTRING)PythonInter_ToDebugString,
            NULL,           // PythonInter_Enable,
            NULL,           // PythonInter_Disable,
            NULL,           // (P_OBJ_ASSIGN)PythonInter_Assign,
            NULL,           // (P_OBJ_COMPARE)PythonInter_Compare,
            NULL,           // (P_OBJ_PTR)PythonInter_Copy,
            NULL,           // (P_OBJ_PTR)PythonInter_DeepCopy,
            NULL            // (P_OBJ_HASH)PythonInter_Hash,
        },
        // Put other object method names below this.
        // Properties:
        // Methods:
        //PythonInter_IsEnabled,
     
    };
    #endif


    // This VTbl supports Retain() and Release() which is
    // used by objects other than the Shared object. These
    // objects can still be shared among other objects. It
    // just that they are deleted when their usage count
    // goes to zero.
    const
    PYTHONINTER_VTBL    PythonInter_Vtbl = {
        {
            &PythonInter_Info,
            PythonInter_IsKindOf,
            obj_RetainStandard,
            obj_ReleaseStandard,
            PythonInter_Dealloc,
            PythonInter_Class,
            PythonInter_WhoAmI,
            (P_OBJ_QUERYINFO)PythonInter_QueryInfo,
            (P_OBJ_TOSTRING)PythonInter_ToDebugString,
            NULL,           // PythonInter_Enable,
            NULL,           // PythonInter_Disable,
            NULL,           // (P_OBJ_ASSIGN)PythonInter_Assign,
            NULL,           // (P_OBJ_COMPARE)PythonInter_Compare,
            NULL,           // (P_OBJ_PTR)PythonInter_Copy,
            NULL,           // (P_OBJ_PTR)PythonInter_DeepCopy,
            NULL            // (P_OBJ_HASH)PythonInter_Hash,
        },
        // Put other object method names below this.
        // Properties:
        // Methods:
        //PythonInter_IsEnabled,
     
    };



    static
    const
    OBJ_INFO            PythonInter_Info = {
        "PythonInter",
        "Python Interface to/from Objects",
        (OBJ_DATA *)&PythonInter_ClassObj,
    #ifdef  PYTHONINTER_SUPER_DEFINED
        (OBJ_DATA *)&obj_ClassObj,
    #else
        (OBJ_DATA *)&obj_ClassObj,
    #endif
        (OBJ_IUNKNOWN *)&PythonInter_Vtbl,
        sizeof(PYTHONINTER_DATA)
    };



#ifdef  __cplusplus
}
#endif


