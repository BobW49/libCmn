// vi: nu:noai:ts=4:sw=4

//****************************************************************
//              Look-Ahead Scanner (LAScan) Object Support
//****************************************************************

//  Class Object Metods and Tables for 'LAScan'
//  Generated 02/26/2023 10:04:02


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




#define         LASCAN_OBJECT_C       1
#include        <LAScan_internal.h>
#ifdef  LASCAN_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct LAScan_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  LASCAN_SINGLETON
    volatile
    LASCAN_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          LAScanClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        LAScan_Info;            // Forward Reference




static
bool            LAScanClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_LASCAN_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(LAScan_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        LAScanClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_LASCAN_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
LASCAN_CLASS_VTBL    class_Vtbl = {
    {
        &LAScan_Info,
        LAScanClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        LAScan_Class,
        LAScanClass_WhoAmI,
        (P_OBJ_QUERYINFO)LAScanClass_QueryInfo,
        NULL                        // LAScanClass_ToDebugString
    },
    (void *)LAScan_New
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

LASCAN_CLASS_DATA  LAScan_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(LASCAN_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  LASCAN_SINGLETON
extern
const
LASCAN_VTBL       LAScan_VtblShared;


LASCAN_DATA *     LAScan_getSingleton (
    void
)
{
    return (OBJ_ID)(LAScan_ClassObj.pSingleton);
}


bool            LAScan_setSingleton (
    LASCAN_DATA       *pValue
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
    if (LAScan_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(LAScan_ClassObj.pSingleton));
    }
    LAScan_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



LASCAN_DATA *     LAScan_Shared (
    void
)
{
    LASCAN_DATA       *this = (OBJ_ID)(LAScan_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = LAScan_New( );
        obj_setVtbl(this, (void *)&LAScan_VtblShared);
        LAScan_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // LAScan_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            LAScan_SharedReset (
    void
)
{
    LASCAN_DATA       *this = (OBJ_ID)(LAScan_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&LAScan_Vtbl);
        obj_Release(this);
        LAScan_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          LAScanClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    LASCAN_CLASS_DATA *this = objId;
    const
    char            *pStrA = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(LASCAN_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStrA) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStrA) == 0) {
                        return (void *)&LAScan_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStrA) == 0) {
                        return (void *)&LAScan_Info.pClassSuperObject;
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
                        return LAScan_New;
                    }
                    break;
                    
                case 'P':
#ifdef  LASCAN_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStrA) == 0) {
                        return LAScan_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStrA) == 0) {
                        return LAScan_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  LASCAN_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStrA) == 0) {
                        return LAScan_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStrA) == 0) {
                        return LAScan_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStrA) == 0) {
                        return LAScanClass_WhoAmI;
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
bool            LAScan_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_LASCAN == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(LAScan_Class())->pClassSuperObject;
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
void            LAScan_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          LAScan_Class (
    void
)
{
    return (OBJ_ID)&LAScan_ClassObj;
}


static
uint16_t        LAScan_WhoAmI (
    void
)
{
    return OBJ_IDENT_LASCAN;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  LASCAN_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
LASCAN_VTBL     LAScan_VtblShared = {
    {
        &LAScan_Info,
        LAScan_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        LAScan_Dealloc,
        LAScan_Class,
        LAScan_WhoAmI,
        (P_OBJ_QUERYINFO)LAScan_QueryInfo,
        (P_OBJ_TOSTRING)LAScan_ToDebugString,
        NULL,           // LAScan_Enable,
        NULL,           // LAScan_Disable,
        NULL,           // (P_OBJ_ASSIGN)LAScan_Assign,
        NULL,           // (P_OBJ_COMPARE)LAScan_Compare,
        NULL,           // (P_OBJ_PTR)LAScan_Copy,
        NULL,           // (P_OBJ_PTR)LAScan_DeepCopy,
        NULL            // (P_OBJ_HASH)LAScan_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //LAScan_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
LASCAN_VTBL     LAScan_Vtbl = {
    {
        &LAScan_Info,
        LAScan_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        LAScan_Dealloc,
        LAScan_Class,
        LAScan_WhoAmI,
        (P_OBJ_QUERYINFO)LAScan_QueryInfo,
        (P_OBJ_TOSTRING)LAScan_ToDebugString,
        NULL,           // LAScan_Enable,
        NULL,           // LAScan_Disable,
        NULL,           // (P_OBJ_ASSIGN)LAScan_Assign,
        NULL,           // (P_OBJ_COMPARE)LAScan_Compare,
        NULL,           // (P_OBJ_PTR)LAScan_Copy,
        NULL,           // (P_OBJ_PTR)LAScan_DeepCopy,
        NULL            // (P_OBJ_HASH)LAScan_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //LAScan_IsEnabled,
 
};



static
const
OBJ_INFO        LAScan_Info = {
    "LAScan",
    "Look-Ahead Scanner",
    (OBJ_DATA *)&LAScan_ClassObj,
#ifdef  LASCAN_SUPER_DEFINED
    (OBJ_DATA *)&obj_ClassObj,
#else
    (OBJ_DATA *)&obj_ClassObj,
#endif
    (OBJ_IUNKNOWN *)&LAScan_Vtbl,
    sizeof(LASCAN_DATA)
};





