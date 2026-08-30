// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'Cmds'
//  Generated 08/30/2022 00:22:12


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




#define         CMDS_OBJECT_C       1
#include        <Cmds_internal.h>
#ifdef  CMDS_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct Cmds_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  CMDS_SINGLETON
    volatile
    CMDS_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          CmdsClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        Cmds_Info;            // Forward Reference




static
bool            CmdsClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_CMDS_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(Cmds_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        CmdsClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_CMDS_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
CMDS_CLASS_VTBL    class_Vtbl = {
    {
        &Cmds_Info,
        CmdsClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        Cmds_Class,
        CmdsClass_WhoAmI,
        (P_OBJ_QUERYINFO)CmdsClass_QueryInfo,
        NULL                        // CmdsClass_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

CMDS_CLASS_DATA  Cmds_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(CMDS_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  CMDS_SINGLETON
extern
const
CMDS_VTBL       Cmds_VtblShared;


CMDS_DATA *     Cmds_getSingleton (
    void
)
{
    return (OBJ_ID)(Cmds_ClassObj.pSingleton);
}


bool            Cmds_setSingleton (
    CMDS_DATA       *pValue
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
    if (Cmds_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(Cmds_ClassObj.pSingleton));
    }
    Cmds_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



CMDS_DATA *     Cmds_Shared (
    void
)
{
    CMDS_DATA       *this = (OBJ_ID)(Cmds_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = Cmds_New( );
        obj_setVtbl(this, (void *)&Cmds_VtblShared);
        Cmds_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // Cmds_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            Cmds_SharedReset (
    void
)
{
    CMDS_DATA       *this = (OBJ_ID)(Cmds_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&Cmds_Vtbl);
        obj_Release(this);
        Cmds_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          CmdsClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    CMDS_CLASS_DATA *this = objId;
    const
    char            *pStrA = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(CMDS_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStrA) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStrA) == 0) {
                        return (void *)&Cmds_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStrA) == 0) {
                        return (void *)&Cmds_Info.pClassSuperObject;
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
                        return Cmds_New;
                    }
                    break;
                    
                case 'P':
#ifdef  CMDS_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStrA) == 0) {
                        return Cmds_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStrA) == 0) {
                        return Cmds_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  CMDS_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStrA) == 0) {
                        return Cmds_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStrA) == 0) {
                        return Cmds_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStrA) == 0) {
                        return CmdsClass_WhoAmI;
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
bool            Cmds_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_CMDS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(Cmds_Class())->pClassSuperObject;
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
void            Cmds_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          Cmds_Class (
    void
)
{
    return (OBJ_ID)&Cmds_ClassObj;
}


static
uint16_t        Cmds_WhoAmI (
    void
)
{
    return OBJ_IDENT_CMDS;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  CMDS_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
CMDS_VTBL     Cmds_VtblShared = {
    {
        &Cmds_Info,
        Cmds_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        Cmds_Dealloc,
        Cmds_Class,
        Cmds_WhoAmI,
        (P_OBJ_QUERYINFO)Cmds_QueryInfo,
        (P_OBJ_TOSTRING)Cmds_ToDebugString,
        NULL,           // Cmds_Enable,
        NULL,           // Cmds_Disable,
        NULL,           // (P_OBJ_ASSIGN)Cmds_Assign,
        NULL,           // (P_OBJ_COMPARE)Cmds_Compare,
        NULL,           // (P_OBJ_PTR)Cmds_Copy,
        NULL,           // (P_OBJ_PTR)Cmds_DeepCopy,
        NULL            // (P_OBJ_HASH)Cmds_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Cmds_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
CMDS_VTBL     Cmds_Vtbl = {
    {
        &Cmds_Info,
        Cmds_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        Cmds_Dealloc,
        Cmds_Class,
        Cmds_WhoAmI,
        (P_OBJ_QUERYINFO)Cmds_QueryInfo,
        (P_OBJ_TOSTRING)Cmds_ToDebugString,
        NULL,           // Cmds_Enable,
        NULL,           // Cmds_Disable,
        NULL,           // (P_OBJ_ASSIGN)Cmds_Assign,
        NULL,           // (P_OBJ_COMPARE)Cmds_Compare,
        NULL,           // (P_OBJ_PTR)Cmds_Copy,
        NULL,           // (P_OBJ_PTR)Cmds_DeepCopy,
        NULL            // (P_OBJ_HASH)Cmds_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Cmds_IsEnabled,
 
};



static
const
OBJ_INFO        Cmds_Info = {
    "Cmds",
    "Command Parser and Executor",
    (OBJ_DATA *)&Cmds_ClassObj,
#ifdef  CMDS_SUPER_DEFINED
    (OBJ_DATA *)&obj_ClassObj,
#else
    (OBJ_DATA *)&obj_ClassObj,
#endif
    (OBJ_IUNKNOWN *)&Cmds_Vtbl,
    sizeof(CMDS_DATA)
};





