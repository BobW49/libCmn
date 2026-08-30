// vi: nu:noai:ts=4:sw=4

//****************************************************************
//              Scan an AST for various manipulations (AstScan) Object Support
//****************************************************************

//  Class Object Metods and Tables for 'AstScan'
//  Generated 02/12/2023 09:19:30


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




#define         ASTSCAN_OBJECT_C       1
#include        <AstScan_internal.h>
#ifdef  ASTSCAN_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct AstScan_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  ASTSCAN_SINGLETON
    volatile
    ASTSCAN_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          AstScanClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        AstScan_Info;            // Forward Reference




static
bool            AstScanClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_ASTSCAN_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(AstScan_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        AstScanClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_ASTSCAN_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
ASTSCAN_CLASS_VTBL    class_Vtbl = {
    {
        &AstScan_Info,
        AstScanClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        AstScan_Class,
        AstScanClass_WhoAmI,
        (P_OBJ_QUERYINFO)AstScanClass_QueryInfo,
        NULL                        // AstScanClass_ToDebugString
    },
    (void *)AstScan_New
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

ASTSCAN_CLASS_DATA  AstScan_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(ASTSCAN_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  ASTSCAN_SINGLETON
extern
const
ASTSCAN_VTBL       AstScan_VtblShared;


ASTSCAN_DATA *     AstScan_getSingleton (
    void
)
{
    return (OBJ_ID)(AstScan_ClassObj.pSingleton);
}


bool            AstScan_setSingleton (
    ASTSCAN_DATA       *pValue
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
    if (AstScan_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(AstScan_ClassObj.pSingleton));
    }
    AstScan_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



ASTSCAN_DATA *     AstScan_Shared (
    void
)
{
    ASTSCAN_DATA       *this = (OBJ_ID)(AstScan_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = AstScan_New( );
        obj_setVtbl(this, (void *)&AstScan_VtblShared);
        AstScan_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // AstScan_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            AstScan_SharedReset (
    void
)
{
    ASTSCAN_DATA       *this = (OBJ_ID)(AstScan_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&AstScan_Vtbl);
        obj_Release(this);
        AstScan_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          AstScanClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    ASTSCAN_CLASS_DATA *this = objId;
    const
    char            *pStrA = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(ASTSCAN_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStrA) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStrA) == 0) {
                        return (void *)&AstScan_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStrA) == 0) {
                        return (void *)&AstScan_Info.pClassSuperObject;
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
                        return AstScan_New;
                    }
                    break;
                    
                case 'P':
#ifdef  ASTSCAN_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStrA) == 0) {
                        return AstScan_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStrA) == 0) {
                        return AstScan_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  ASTSCAN_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStrA) == 0) {
                        return AstScan_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStrA) == 0) {
                        return AstScan_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStrA) == 0) {
                        return AstScanClass_WhoAmI;
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
bool            AstScan_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_ASTSCAN == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(AstScan_Class())->pClassSuperObject;
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
void            AstScan_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          AstScan_Class (
    void
)
{
    return (OBJ_ID)&AstScan_ClassObj;
}


static
uint16_t        AstScan_WhoAmI (
    void
)
{
    return OBJ_IDENT_ASTSCAN;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  ASTSCAN_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
ASTSCAN_VTBL     AstScan_VtblShared = {
    {
        &AstScan_Info,
        AstScan_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        AstScan_Dealloc,
        AstScan_Class,
        AstScan_WhoAmI,
        (P_OBJ_QUERYINFO)AstScan_QueryInfo,
        (P_OBJ_TOSTRING)AstScan_ToDebugString,
        NULL,           // AstScan_Enable,
        NULL,           // AstScan_Disable,
        NULL,           // (P_OBJ_ASSIGN)AstScan_Assign,
        NULL,           // (P_OBJ_COMPARE)AstScan_Compare,
        NULL,           // (P_OBJ_PTR)AstScan_Copy,
        NULL,           // (P_OBJ_PTR)AstScan_DeepCopy,
        NULL            // (P_OBJ_HASH)AstScan_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //AstScan_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
ASTSCAN_VTBL     AstScan_Vtbl = {
    {
        &AstScan_Info,
        AstScan_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        AstScan_Dealloc,
        AstScan_Class,
        AstScan_WhoAmI,
        (P_OBJ_QUERYINFO)AstScan_QueryInfo,
        (P_OBJ_TOSTRING)AstScan_ToDebugString,
        NULL,           // AstScan_Enable,
        NULL,           // AstScan_Disable,
        NULL,           // (P_OBJ_ASSIGN)AstScan_Assign,
        NULL,           // (P_OBJ_COMPARE)AstScan_Compare,
        NULL,           // (P_OBJ_PTR)AstScan_Copy,
        NULL,           // (P_OBJ_PTR)AstScan_DeepCopy,
        NULL            // (P_OBJ_HASH)AstScan_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //AstScan_IsEnabled,
 
};



static
const
OBJ_INFO        AstScan_Info = {
    "AstScan",
    "Scan an AST for various manipulations",
    (OBJ_DATA *)&AstScan_ClassObj,
#ifdef  ASTSCAN_SUPER_DEFINED
    (OBJ_DATA *)&obj_ClassObj,
#else
    (OBJ_DATA *)&obj_ClassObj,
#endif
    (OBJ_IUNKNOWN *)&AstScan_Vtbl,
    sizeof(ASTSCAN_DATA)
};





