// vi: nu:noai:ts=4:sw=4

//****************************************************************
//              A Simple Graph (SGraph) Object Support
//****************************************************************

//  Class Object Metods and Tables for 'SGraph'
//  Generated 10/21/2022 02:32:39


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




#define         SGRAPH_OBJECT_C       1
#include        <SGraph_internal.h>
#ifdef  SGRAPH_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct SGraph_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  SGRAPH_SINGLETON
    volatile
    SGRAPH_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          SGraphClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        SGraph_Info;            // Forward Reference




static
bool            SGraphClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_SGRAPH_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(SGraph_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        SGraphClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_SGRAPH_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
SGRAPH_CLASS_VTBL    class_Vtbl = {
    {
        &SGraph_Info,
        SGraphClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        SGraph_Class,
        SGraphClass_WhoAmI,
        (P_OBJ_QUERYINFO)SGraphClass_QueryInfo,
        NULL                        // SGraphClass_ToDebugString
    },
    (void *)SGraph_New
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

SGRAPH_CLASS_DATA  SGraph_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(SGRAPH_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  SGRAPH_SINGLETON
extern
const
SGRAPH_VTBL       SGraph_VtblShared;


SGRAPH_DATA *     SGraph_getSingleton (
    void
)
{
    return (OBJ_ID)(SGraph_ClassObj.pSingleton);
}


bool            SGraph_setSingleton (
    SGRAPH_DATA       *pValue
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
    if (SGraph_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(SGraph_ClassObj.pSingleton));
    }
    SGraph_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



SGRAPH_DATA *     SGraph_Shared (
    void
)
{
    SGRAPH_DATA       *this = (OBJ_ID)(SGraph_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = SGraph_New( );
        obj_setVtbl(this, (void *)&SGraph_VtblShared);
        SGraph_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // SGraph_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            SGraph_SharedReset (
    void
)
{
    SGRAPH_DATA       *this = (OBJ_ID)(SGraph_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&SGraph_Vtbl);
        obj_Release(this);
        SGraph_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          SGraphClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    SGRAPH_CLASS_DATA *this = objId;
    const
    char            *pStrA = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(SGRAPH_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStrA) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStrA) == 0) {
                        return (void *)&SGraph_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStrA) == 0) {
                        return (void *)&SGraph_Info.pClassSuperObject;
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
                        return SGraph_New;
                    }
                    break;
                    
                case 'P':
#ifdef  SGRAPH_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStrA) == 0) {
                        return SGraph_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStrA) == 0) {
                        return SGraph_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  SGRAPH_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStrA) == 0) {
                        return SGraph_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStrA) == 0) {
                        return SGraph_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStrA) == 0) {
                        return SGraphClass_WhoAmI;
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
bool            SGraph_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_SGRAPH == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(SGraph_Class())->pClassSuperObject;
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
void            SGraph_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          SGraph_Class (
    void
)
{
    return (OBJ_ID)&SGraph_ClassObj;
}


static
uint16_t        SGraph_WhoAmI (
    void
)
{
    return OBJ_IDENT_SGRAPH;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  SGRAPH_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
SGRAPH_VTBL     SGraph_VtblShared = {
    {
        &SGraph_Info,
        SGraph_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        SGraph_Dealloc,
        SGraph_Class,
        SGraph_WhoAmI,
        (P_OBJ_QUERYINFO)SGraph_QueryInfo,
        (P_OBJ_TOSTRING)SGraph_ToDebugString,
        NULL,           // SGraph_Enable,
        NULL,           // SGraph_Disable,
        NULL,           // (P_OBJ_ASSIGN)SGraph_Assign,
        NULL,           // (P_OBJ_COMPARE)SGraph_Compare,
        NULL,           // (P_OBJ_PTR)SGraph_Copy,
        NULL,           // (P_OBJ_PTR)SGraph_DeepCopy,
        NULL            // (P_OBJ_HASH)SGraph_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //SGraph_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
SGRAPH_VTBL     SGraph_Vtbl = {
    {
        &SGraph_Info,
        SGraph_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        SGraph_Dealloc,
        SGraph_Class,
        SGraph_WhoAmI,
        (P_OBJ_QUERYINFO)SGraph_QueryInfo,
        (P_OBJ_TOSTRING)SGraph_ToDebugString,
        NULL,           // SGraph_Enable,
        NULL,           // SGraph_Disable,
        NULL,           // (P_OBJ_ASSIGN)SGraph_Assign,
        NULL,           // (P_OBJ_COMPARE)SGraph_Compare,
        NULL,           // (P_OBJ_PTR)SGraph_Copy,
        NULL,           // (P_OBJ_PTR)SGraph_DeepCopy,
        NULL            // (P_OBJ_HASH)SGraph_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //SGraph_IsEnabled,
 
};



static
const
OBJ_INFO        SGraph_Info = {
    "SGraph",
    "A Simple Graph",
    (OBJ_DATA *)&SGraph_ClassObj,
#ifdef  SGRAPH_SUPER_DEFINED
    (OBJ_DATA *)&obj_ClassObj,
#else
    (OBJ_DATA *)&obj_ClassObj,
#endif
    (OBJ_IUNKNOWN *)&SGraph_Vtbl,
    sizeof(SGRAPH_DATA)
};





