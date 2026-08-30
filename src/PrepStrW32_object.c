// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'PrepStrW32'
//  Generated 04/23/2022 09:45:13


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




#define         PREPSTRW32_OBJECT_C       1
#include        <PrepStrW32_internal.h>
#ifdef  PREPSTRW32_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct PrepStrW32_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  PREPSTRW32_SINGLETON
    volatile
    PREPSTRW32_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          PrepStrW32Class_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        PrepStrW32_Info;            // Forward Reference




static
bool            PrepStrW32Class_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_PREPSTRW32_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(PrepStrW32_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        PrepStrW32Class_WhoAmI (
    void
)
{
    return OBJ_IDENT_PREPSTRW32_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
PREPSTRW32_CLASS_VTBL    class_Vtbl = {
    {
        &PrepStrW32_Info,
        PrepStrW32Class_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        PrepStrW32_Class,
        PrepStrW32Class_WhoAmI,
        (P_OBJ_QUERYINFO)PrepStrW32Class_QueryInfo,
        NULL                        // PrepStrW32Class_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

PREPSTRW32_CLASS_DATA  PrepStrW32_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(PREPSTRW32_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  PREPSTRW32_SINGLETON
extern
const
PREPSTRW32_VTBL       PrepStrW32_VtblShared;


PREPSTRW32_DATA *     PrepStrW32_getSingleton (
    void
)
{
    return (OBJ_ID)(PrepStrW32_ClassObj.pSingleton);
}


bool            PrepStrW32_setSingleton (
    PREPSTRW32_DATA       *pValue
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
    if (PrepStrW32_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(PrepStrW32_ClassObj.pSingleton));
    }
    PrepStrW32_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



PREPSTRW32_DATA *     PrepStrW32_Shared (
    void
)
{
    PREPSTRW32_DATA       *this = (OBJ_ID)(PrepStrW32_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = PrepStrW32_New( );
        obj_setVtbl(this, (void *)&PrepStrW32_VtblShared);
        PrepStrW32_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // PrepStrW32_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            PrepStrW32_SharedReset (
    void
)
{
    PREPSTRW32_DATA       *this = (OBJ_ID)(PrepStrW32_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&PrepStrW32_Vtbl);
        obj_Release(this);
        PrepStrW32_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          PrepStrW32Class_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    PREPSTRW32_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(PREPSTRW32_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&PrepStrW32_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&PrepStrW32_Info.pClassSuperObject;
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
            switch (*pStr) {
                    
                case 'N':
                    if (str_Compare("New", (char *)pStr) == 0) {
                        return PrepStrW32_New;
                    }
                    break;
                    
                case 'P':
#ifdef  PREPSTRW32_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return PrepStrW32_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return PrepStrW32_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  PREPSTRW32_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return PrepStrW32_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return PrepStrW32_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return PrepStrW32Class_WhoAmI;
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
bool            PrepStrW32_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_PREPSTRW32 == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(PrepStrW32_Class())->pClassSuperObject;
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
void            PrepStrW32_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          PrepStrW32_Class (
    void
)
{
    return (OBJ_ID)&PrepStrW32_ClassObj;
}


static
uint16_t        PrepStrW32_WhoAmI (
    void
)
{
    return OBJ_IDENT_PREPSTRW32;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  PREPSTRW32_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
PREPSTRW32_VTBL     PrepStrW32_VtblShared = {
    {
        &PrepStrW32_Info,
        PrepStrW32_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        PrepStrW32_Dealloc,
        PrepStrW32_Class,
        PrepStrW32_WhoAmI,
        (P_OBJ_QUERYINFO)PrepStrW32_QueryInfo,
        (P_OBJ_TOSTRING)PrepStrW32_ToDebugString,
        NULL,           // PrepStrW32_Enable,
        NULL,           // PrepStrW32_Disable,
        NULL,           // (P_OBJ_ASSIGN)PrepStrW32_Assign,
        NULL,           // (P_OBJ_COMPARE)PrepStrW32_Compare,
        NULL,           // (P_OBJ_PTR)PrepStrW32_Copy,
        NULL,           // (P_OBJ_PTR)PrepStrW32_DeepCopy,
        NULL            // (P_OBJ_HASH)PrepStrW32_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //PrepStrW32_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
PREPSTRW32_VTBL     PrepStrW32_Vtbl = {
    {
        &PrepStrW32_Info,
        PrepStrW32_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        PrepStrW32_Dealloc,
        PrepStrW32_Class,
        PrepStrW32_WhoAmI,
        (P_OBJ_QUERYINFO)PrepStrW32_QueryInfo,
        (P_OBJ_TOSTRING)PrepStrW32_ToDebugString,
        NULL,           // PrepStrW32_Enable,
        NULL,           // PrepStrW32_Disable,
        NULL,           // (P_OBJ_ASSIGN)PrepStrW32_Assign,
        NULL,           // (P_OBJ_COMPARE)PrepStrW32_Compare,
        NULL,           // (P_OBJ_PTR)PrepStrW32_Copy,
        NULL,           // (P_OBJ_PTR)PrepStrW32_DeepCopy,
        NULL            // (P_OBJ_HASH)PrepStrW32_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //PrepStrW32_IsEnabled,
 
};



static
const
OBJ_INFO        PrepStrW32_Info = {
    "PrepStrW32",
    "Preprocess a Source String",
    (OBJ_DATA *)&PrepStrW32_ClassObj,
#ifdef PREPSTRW32_SUPER_DEFINED
    (OBJ_DATA *)&Scanner_ClassObj,
#else
    (OBJ_DATA *)&obj_ClassObj,
#endif
    (OBJ_IUNKNOWN *)&PrepStrW32_Vtbl,
    sizeof(PREPSTRW32_DATA)
};





