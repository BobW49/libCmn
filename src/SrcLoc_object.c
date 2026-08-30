// vi: nu:noai:ts=4:sw=4

//****************************************************************
//              Source File Location (SrcLoc) Object Support
//****************************************************************

//  Class Object Metods and Tables for 'SrcLoc'
//  Generated 12/25/2022 08:43:29


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




#define         SRCLOC_OBJECT_C       1
#include        <SrcLoc_internal.h>
#ifdef  SRCLOC_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct SrcLoc_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  SRCLOC_SINGLETON
    volatile
    SRCLOC_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          SrcLocClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        SrcLoc_Info;            // Forward Reference




static
bool            SrcLocClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_SRCLOC_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(SrcLoc_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        SrcLocClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_SRCLOC_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
SRCLOC_CLASS_VTBL    class_Vtbl = {
    {
        &SrcLoc_Info,
        SrcLocClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        SrcLoc_Class,
        SrcLocClass_WhoAmI,
        (P_OBJ_QUERYINFO)SrcLocClass_QueryInfo,
        NULL                        // SrcLocClass_ToDebugString
    },
    (void *)SrcLoc_New
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

SRCLOC_CLASS_DATA  SrcLoc_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(SRCLOC_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  SRCLOC_SINGLETON
extern
const
SRCLOC_VTBL       SrcLoc_VtblShared;


SRCLOC_DATA *     SrcLoc_getSingleton (
    void
)
{
    return (OBJ_ID)(SrcLoc_ClassObj.pSingleton);
}


bool            SrcLoc_setSingleton (
    SRCLOC_DATA       *pValue
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
    if (SrcLoc_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(SrcLoc_ClassObj.pSingleton));
    }
    SrcLoc_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



SRCLOC_DATA *     SrcLoc_Shared (
    void
)
{
    SRCLOC_DATA       *this = (OBJ_ID)(SrcLoc_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = SrcLoc_New( );
        obj_setVtbl(this, (void *)&SrcLoc_VtblShared);
        SrcLoc_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // SrcLoc_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            SrcLoc_SharedReset (
    void
)
{
    SRCLOC_DATA       *this = (OBJ_ID)(SrcLoc_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&SrcLoc_Vtbl);
        obj_Release(this);
        SrcLoc_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          SrcLocClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    SRCLOC_CLASS_DATA *this = objId;
    const
    char            *pStrA = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(SRCLOC_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStrA) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStrA) == 0) {
                        return (void *)&SrcLoc_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStrA) == 0) {
                        return (void *)&SrcLoc_Info.pClassSuperObject;
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
                        return SrcLoc_New;
                    }
                    break;
                    
                case 'P':
#ifdef  SRCLOC_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStrA) == 0) {
                        return SrcLoc_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStrA) == 0) {
                        return SrcLoc_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  SRCLOC_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStrA) == 0) {
                        return SrcLoc_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStrA) == 0) {
                        return SrcLoc_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStrA) == 0) {
                        return SrcLocClass_WhoAmI;
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
bool            SrcLoc_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_SRCLOC == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(SrcLoc_Class())->pClassSuperObject;
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
void            SrcLoc_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          SrcLoc_Class (
    void
)
{
    return (OBJ_ID)&SrcLoc_ClassObj;
}


static
uint16_t        SrcLoc_WhoAmI (
    void
)
{
    return OBJ_IDENT_SRCLOC;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  SRCLOC_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
SRCLOC_VTBL     SrcLoc_VtblShared = {
    {
        &SrcLoc_Info,
        SrcLoc_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        SrcLoc_Dealloc,
        SrcLoc_Class,
        SrcLoc_WhoAmI,
        (P_OBJ_QUERYINFO)SrcLoc_QueryInfo,
        (P_OBJ_TOSTRING)SrcLoc_ToDebugString,
        NULL,           // SrcLoc_Enable,
        NULL,           // SrcLoc_Disable,
        NULL,           // (P_OBJ_ASSIGN)SrcLoc_Assign,
        NULL,           // (P_OBJ_COMPARE)SrcLoc_Compare,
        NULL,           // (P_OBJ_PTR)SrcLoc_Copy,
        NULL,           // (P_OBJ_PTR)SrcLoc_DeepCopy,
        NULL            // (P_OBJ_HASH)SrcLoc_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //SrcLoc_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
SRCLOC_VTBL     SrcLoc_Vtbl = {
    {
        &SrcLoc_Info,
        SrcLoc_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        SrcLoc_Dealloc,
        SrcLoc_Class,
        SrcLoc_WhoAmI,
        (P_OBJ_QUERYINFO)SrcLoc_QueryInfo,
        (P_OBJ_TOSTRING)SrcLoc_ToDebugString,
        NULL,           // SrcLoc_Enable,
        NULL,           // SrcLoc_Disable,
        (P_OBJ_ASSIGN)SrcLoc_Assign,
        (P_OBJ_COMPARE)SrcLoc_Compare,
        (P_OBJ_PTR)SrcLoc_Copy,
        NULL,           // (P_OBJ_PTR)SrcLoc_DeepCopy,
        NULL            // (P_OBJ_HASH)SrcLoc_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //SrcLoc_IsEnabled,
 
};



static
const
OBJ_INFO        SrcLoc_Info = {
    "SrcLoc",
    "Source File Location",
    (OBJ_DATA *)&SrcLoc_ClassObj,
#ifdef  SRCLOC_SUPER_DEFINED
    (OBJ_DATA *)&obj_ClassObj,
#else
    (OBJ_DATA *)&obj_ClassObj,
#endif
    (OBJ_IUNKNOWN *)&SrcLoc_Vtbl,
    sizeof(SRCLOC_DATA)
};





