// vi: nu:noai:ts=4:sw=4

//****************************************************************
//              File Input - Line at a time (LineIn) Object Support
//****************************************************************

//  Class Object Metods and Tables for 'LineIn'
//  Generated 03/31/2023 08:27:53


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




#define         LINEIN_OBJECT_C       1
#include        <LineIn_internal.h>
#ifdef  LINEIN_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct LineIn_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  LINEIN_SINGLETON
    volatile
    LINEIN_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          LineInClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        LineIn_Info;            // Forward Reference




static
bool            LineInClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_LINEIN_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(LineIn_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        LineInClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_LINEIN_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
LINEIN_CLASS_VTBL    class_Vtbl = {
    {
        &LineIn_Info,
        LineInClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        LineIn_Class,
        LineInClass_WhoAmI,
        (P_OBJ_QUERYINFO)LineInClass_QueryInfo,
        NULL                        // LineInClass_ToDebugString
    },
    (void *)LineIn_New
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

LINEIN_CLASS_DATA  LineIn_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(LINEIN_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  LINEIN_SINGLETON
extern
const
LINEIN_VTBL       LineIn_VtblShared;


LINEIN_DATA *     LineIn_getSingleton (
    void
)
{
    return (OBJ_ID)(LineIn_ClassObj.pSingleton);
}


bool            LineIn_setSingleton (
    LINEIN_DATA       *pValue
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
    if (LineIn_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(LineIn_ClassObj.pSingleton));
    }
    LineIn_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



LINEIN_DATA *     LineIn_Shared (
    void
)
{
    LINEIN_DATA       *this = (OBJ_ID)(LineIn_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = LineIn_New( );
        obj_setVtbl(this, (void *)&LineIn_VtblShared);
        LineIn_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // LineIn_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            LineIn_SharedReset (
    void
)
{
    LINEIN_DATA       *this = (OBJ_ID)(LineIn_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&LineIn_Vtbl);
        obj_Release(this);
        LineIn_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          LineInClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    LINEIN_CLASS_DATA *this = objId;
    const
    char            *pStrA = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(LINEIN_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStrA) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStrA) == 0) {
                        return (void *)&LineIn_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStrA) == 0) {
                        return (void *)&LineIn_Info.pClassSuperObject;
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
                        return LineIn_New;
                    }
                    break;
                    
                case 'P':
#ifdef  LINEIN_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStrA) == 0) {
                        return LineIn_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStrA) == 0) {
                        return LineIn_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  LINEIN_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStrA) == 0) {
                        return LineIn_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStrA) == 0) {
                        return LineIn_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStrA) == 0) {
                        return LineInClass_WhoAmI;
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
bool            LineIn_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_LINEIN == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(LineIn_Class())->pClassSuperObject;
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
void            LineIn_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          LineIn_Class (
    void
)
{
    return (OBJ_ID)&LineIn_ClassObj;
}


static
uint16_t        LineIn_WhoAmI (
    void
)
{
    return OBJ_IDENT_LINEIN;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  LINEIN_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
LINEIN_VTBL     LineIn_VtblShared = {
    {
        &LineIn_Info,
        LineIn_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        LineIn_Dealloc,
        LineIn_Class,
        LineIn_WhoAmI,
        (P_OBJ_QUERYINFO)LineIn_QueryInfo,
        (P_OBJ_TOSTRING)LineIn_ToDebugString,
        NULL,           // LineIn_Enable,
        NULL,           // LineIn_Disable,
        NULL,           // (P_OBJ_ASSIGN)LineIn_Assign,
        NULL,           // (P_OBJ_COMPARE)LineIn_Compare,
        NULL,           // (P_OBJ_PTR)LineIn_Copy,
        NULL,           // (P_OBJ_PTR)LineIn_DeepCopy,
        NULL            // (P_OBJ_HASH)LineIn_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //LineIn_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
LINEIN_VTBL     LineIn_Vtbl = {
    {
        &LineIn_Info,
        LineIn_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        LineIn_Dealloc,
        LineIn_Class,
        LineIn_WhoAmI,
        (P_OBJ_QUERYINFO)LineIn_QueryInfo,
        (P_OBJ_TOSTRING)LineIn_ToDebugString,
        NULL,           // LineIn_Enable,
        NULL,           // LineIn_Disable,
        NULL,           // (P_OBJ_ASSIGN)LineIn_Assign,
        NULL,           // (P_OBJ_COMPARE)LineIn_Compare,
        NULL,           // (P_OBJ_PTR)LineIn_Copy,
        NULL,           // (P_OBJ_PTR)LineIn_DeepCopy,
        NULL            // (P_OBJ_HASH)LineIn_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //LineIn_IsEnabled,
 
};



static
const
OBJ_INFO        LineIn_Info = {
    "LineIn",
    "File Input - Line at a time",
    (OBJ_DATA *)&LineIn_ClassObj,
#ifdef  LINEIN_SUPER_DEFINED
    (OBJ_DATA *)&FileIO_ClassObj,
#else
    (OBJ_DATA *)&obj_ClassObj,
#endif
    (OBJ_IUNKNOWN *)&LineIn_Vtbl,
    sizeof(LINEIN_DATA)
};





