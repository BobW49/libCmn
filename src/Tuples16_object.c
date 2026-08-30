// vi: nu:noai:ts=4:sw=4

//****************************************************************
// a List of 16-bit Variable Sized Tuples (Tuples16) Object Support
//****************************************************************

//  Class Object Metods and Tables for 'Tuples16'
//  Generated 01/28/2023 10:52:55


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




#define         TUPLES16_OBJECT_C       1
#include        <Tuples16_internal.h>
#ifdef  TUPLES16_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct Tuples16_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  TUPLES16_SINGLETON
    volatile
    TUPLES16_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          Tuples16Class_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        Tuples16_Info;            // Forward Reference




static
bool            Tuples16Class_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_TUPLES16_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(Tuples16_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        Tuples16Class_WhoAmI (
    void
)
{
    return OBJ_IDENT_TUPLES16_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
TUPLES16_CLASS_VTBL    class_Vtbl = {
    {
        &Tuples16_Info,
        Tuples16Class_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        Tuples16_Class,
        Tuples16Class_WhoAmI,
        (P_OBJ_QUERYINFO)Tuples16Class_QueryInfo,
        NULL                        // Tuples16Class_ToDebugString
    },
    (void *)Tuples16_New
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

TUPLES16_CLASS_DATA  Tuples16_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(TUPLES16_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  TUPLES16_SINGLETON
extern
const
TUPLES16_VTBL       Tuples16_VtblShared;


TUPLES16_DATA *     Tuples16_getSingleton (
    void
)
{
    return (OBJ_ID)(Tuples16_ClassObj.pSingleton);
}


bool            Tuples16_setSingleton (
    TUPLES16_DATA       *pValue
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
    if (Tuples16_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(Tuples16_ClassObj.pSingleton));
    }
    Tuples16_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



TUPLES16_DATA *     Tuples16_Shared (
    void
)
{
    TUPLES16_DATA       *this = (OBJ_ID)(Tuples16_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = Tuples16_New( );
        obj_setVtbl(this, (void *)&Tuples16_VtblShared);
        Tuples16_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // Tuples16_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            Tuples16_SharedReset (
    void
)
{
    TUPLES16_DATA       *this = (OBJ_ID)(Tuples16_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&Tuples16_Vtbl);
        obj_Release(this);
        Tuples16_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          Tuples16Class_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    TUPLES16_CLASS_DATA *this = objId;
    const
    char            *pStrA = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(TUPLES16_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStrA) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStrA) == 0) {
                        return (void *)&Tuples16_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStrA) == 0) {
                        return (void *)&Tuples16_Info.pClassSuperObject;
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
                        return Tuples16_New;
                    }
                    break;
                    
                case 'P':
#ifdef  TUPLES16_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStrA) == 0) {
                        return Tuples16_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStrA) == 0) {
                        return Tuples16_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  TUPLES16_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStrA) == 0) {
                        return Tuples16_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStrA) == 0) {
                        return Tuples16_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStrA) == 0) {
                        return Tuples16Class_WhoAmI;
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
bool            Tuples16_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_TUPLES16 == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(Tuples16_Class())->pClassSuperObject;
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
void            Tuples16_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          Tuples16_Class (
    void
)
{
    return (OBJ_ID)&Tuples16_ClassObj;
}


static
uint16_t        Tuples16_WhoAmI (
    void
)
{
    return OBJ_IDENT_TUPLES16;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  TUPLES16_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
TUPLES16_VTBL     Tuples16_VtblShared = {
    {
        &Tuples16_Info,
        Tuples16_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        Tuples16_Dealloc,
        Tuples16_Class,
        Tuples16_WhoAmI,
        (P_OBJ_QUERYINFO)Tuples16_QueryInfo,
        (P_OBJ_TOSTRING)Tuples16_ToDebugString,
        NULL,           // Tuples16_Enable,
        NULL,           // Tuples16_Disable,
        NULL,           // (P_OBJ_ASSIGN)Tuples16_Assign,
        NULL,           // (P_OBJ_COMPARE)Tuples16_Compare,
        NULL,           // (P_OBJ_PTR)Tuples16_Copy,
        NULL,           // (P_OBJ_PTR)Tuples16_DeepCopy,
        NULL            // (P_OBJ_HASH)Tuples16_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Tuples16_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
TUPLES16_VTBL     Tuples16_Vtbl = {
    {
        &Tuples16_Info,
        Tuples16_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        Tuples16_Dealloc,
        Tuples16_Class,
        Tuples16_WhoAmI,
        (P_OBJ_QUERYINFO)Tuples16_QueryInfo,
        (P_OBJ_TOSTRING)Tuples16_ToDebugString,
        NULL,           // Tuples16_Enable,
        NULL,           // Tuples16_Disable,
        NULL,           // (P_OBJ_ASSIGN)Tuples16_Assign,
        NULL,           // (P_OBJ_COMPARE)Tuples16_Compare,
        NULL,           // (P_OBJ_PTR)Tuples16_Copy,
        NULL,           // (P_OBJ_PTR)Tuples16_DeepCopy,
        NULL            // (P_OBJ_HASH)Tuples16_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Tuples16_IsEnabled,
 
};



static
const
OBJ_INFO        Tuples16_Info = {
    "Tuples16",
    "a List of 16-bit Variable Sized Tuples",
    (OBJ_DATA *)&Tuples16_ClassObj,
#ifdef  TUPLES16_SUPER_DEFINED
    (OBJ_DATA *)&obj_ClassObj,
#else
    (OBJ_DATA *)&obj_ClassObj,
#endif
    (OBJ_IUNKNOWN *)&Tuples16_Vtbl,
    sizeof(TUPLES16_DATA)
};





