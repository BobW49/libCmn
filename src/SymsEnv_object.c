// vi: nu:noai:ts=4:sw=4

//****************************************************************
//              Symbol Table Environment ADT (SymsEnv) Object Support
//****************************************************************

//  Class Object Metods and Tables for 'SymsEnv'
//  Generated 05/29/2023 10:14:40


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




#define         SYMSENV_OBJECT_C       1
#include        <SymsEnv_internal.h>
#ifdef  SYMSENV_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct SymsEnv_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  SYMSENV_SINGLETON
    volatile
    SYMSENV_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          SymsEnvClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        SymsEnv_Info;            // Forward Reference




static
bool            SymsEnvClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_SYMSENV_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(SymsEnv_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        SymsEnvClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_SYMSENV_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
SYMSENV_CLASS_VTBL    class_Vtbl = {
    {
        &SymsEnv_Info,
        SymsEnvClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        SymsEnv_Class,
        SymsEnvClass_WhoAmI,
        (P_OBJ_QUERYINFO)SymsEnvClass_QueryInfo,
        NULL                        // SymsEnvClass_ToDebugString
    },
    (void *)SymsEnv_New
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

SYMSENV_CLASS_DATA  SymsEnv_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(SYMSENV_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  SYMSENV_SINGLETON
extern
const
SYMSENV_VTBL       SymsEnv_VtblShared;


SYMSENV_DATA *     SymsEnv_getSingleton (
    void
)
{
    return (OBJ_ID)(SymsEnv_ClassObj.pSingleton);
}


bool            SymsEnv_setSingleton (
    SYMSENV_DATA       *pValue
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
    if (SymsEnv_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(SymsEnv_ClassObj.pSingleton));
    }
    SymsEnv_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



SYMSENV_DATA *     SymsEnv_Shared (
    void
)
{
    SYMSENV_DATA       *this = (OBJ_ID)(SymsEnv_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = SymsEnv_New( );
        obj_setVtbl(this, (void *)&SymsEnv_VtblShared);
        SymsEnv_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // SymsEnv_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            SymsEnv_SharedReset (
    void
)
{
    SYMSENV_DATA       *this = (OBJ_ID)(SymsEnv_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&SymsEnv_Vtbl);
        obj_Release(this);
        SymsEnv_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          SymsEnvClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    SYMSENV_CLASS_DATA *this = objId;
    const
    char            *pStrA = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(SYMSENV_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStrA) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStrA) == 0) {
                        return (void *)&SymsEnv_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStrA) == 0) {
                        return (void *)&SymsEnv_Info.pClassSuperObject;
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
                        return SymsEnv_New;
                    }
                    break;
                    
                case 'P':
#ifdef  SYMSENV_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStrA) == 0) {
                        return SymsEnv_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStrA) == 0) {
                        return SymsEnv_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  SYMSENV_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStrA) == 0) {
                        return SymsEnv_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStrA) == 0) {
                        return SymsEnv_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStrA) == 0) {
                        return SymsEnvClass_WhoAmI;
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
bool            SymsEnv_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_SYMSENV == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(SymsEnv_Class())->pClassSuperObject;
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
void            SymsEnv_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          SymsEnv_Class (
    void
)
{
    return (OBJ_ID)&SymsEnv_ClassObj;
}


static
uint16_t        SymsEnv_WhoAmI (
    void
)
{
    return OBJ_IDENT_SYMSENV;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  SYMSENV_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
SYMSENV_VTBL     SymsEnv_VtblShared = {
    {
        &SymsEnv_Info,
        SymsEnv_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        SymsEnv_Dealloc,
        SymsEnv_Class,
        SymsEnv_WhoAmI,
        (P_OBJ_QUERYINFO)SymsEnv_QueryInfo,
        (P_OBJ_TOSTRING)SymsEnv_ToDebugString,
        NULL,           // SymsEnv_Enable,
        NULL,           // SymsEnv_Disable,
        NULL,           // (P_OBJ_ASSIGN)SymsEnv_Assign,
        NULL,           // (P_OBJ_COMPARE)SymsEnv_Compare,
        NULL,           // (P_OBJ_PTR)SymsEnv_Copy,
        NULL,           // (P_OBJ_PTR)SymsEnv_DeepCopy,
        NULL            // (P_OBJ_HASH)SymsEnv_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //SymsEnv_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
SYMSENV_VTBL     SymsEnv_Vtbl = {
    {
        &SymsEnv_Info,
        SymsEnv_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        SymsEnv_Dealloc,
        SymsEnv_Class,
        SymsEnv_WhoAmI,
        (P_OBJ_QUERYINFO)SymsEnv_QueryInfo,
        (P_OBJ_TOSTRING)SymsEnv_ToDebugString,
        NULL,           // SymsEnv_Enable,
        NULL,           // SymsEnv_Disable,
        NULL,           // (P_OBJ_ASSIGN)SymsEnv_Assign,
        NULL,           // (P_OBJ_COMPARE)SymsEnv_Compare,
        NULL,           // (P_OBJ_PTR)SymsEnv_Copy,
        NULL,           // (P_OBJ_PTR)SymsEnv_DeepCopy,
        NULL            // (P_OBJ_HASH)SymsEnv_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //SymsEnv_IsEnabled,
 
};



static
const
OBJ_INFO        SymsEnv_Info = {
    "SymsEnv",
    "Symbol Table Environment ADT",
    (OBJ_DATA *)&SymsEnv_ClassObj,
#ifdef  SYMSENV_SUPER_DEFINED
    (OBJ_DATA *)&Blocks_ClassObj,
#else
    (OBJ_DATA *)&obj_ClassObj,
#endif
    (OBJ_IUNKNOWN *)&SymsEnv_Vtbl,
    sizeof(SYMSENV_DATA)
};





