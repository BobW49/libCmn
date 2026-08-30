// vi: nu:noai:ts=4:sw=4

//****************************************************************
//  B-Plus Tree Internal Request Processor (BPTReq) Object Support
//****************************************************************

//  Class Object Metods and Tables for 'BPTReq'
//  Generated 01/31/2023 20:11:00


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




#define         BPTREQ_OBJECT_C       1
#include        <BPTReq_internal.h>
#ifdef  BPTREQ_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct BPTReq_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  BPTREQ_SINGLETON
    volatile
    BPTREQ_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          BPTReqClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        BPTReq_Info;            // Forward Reference




static
bool            BPTReqClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_BPTREQ_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(BPTReq_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        BPTReqClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_BPTREQ_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
BPTREQ_CLASS_VTBL    class_Vtbl = {
    {
        &BPTReq_Info,
        BPTReqClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        BPTReq_Class,
        BPTReqClass_WhoAmI,
        (P_OBJ_QUERYINFO)BPTReqClass_QueryInfo,
        NULL                        // BPTReqClass_ToDebugString
    },
    (void *)BPTReq_New
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

BPTREQ_CLASS_DATA  BPTReq_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(BPTREQ_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  BPTREQ_SINGLETON
extern
const
BPTREQ_VTBL       BPTReq_VtblShared;


BPTREQ_DATA *     BPTReq_getSingleton (
    void
)
{
    return (OBJ_ID)(BPTReq_ClassObj.pSingleton);
}


bool            BPTReq_setSingleton (
    BPTREQ_DATA       *pValue
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
    if (BPTReq_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(BPTReq_ClassObj.pSingleton));
    }
    BPTReq_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



BPTREQ_DATA *     BPTReq_Shared (
    void
)
{
    BPTREQ_DATA       *this = (OBJ_ID)(BPTReq_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = BPTReq_New( );
        obj_setVtbl(this, (void *)&BPTReq_VtblShared);
        BPTReq_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // BPTReq_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            BPTReq_SharedReset (
    void
)
{
    BPTREQ_DATA       *this = (OBJ_ID)(BPTReq_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&BPTReq_Vtbl);
        obj_Release(this);
        BPTReq_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          BPTReqClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    BPTREQ_CLASS_DATA *this = objId;
    const
    char            *pStrA = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(BPTREQ_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStrA) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStrA) == 0) {
                        return (void *)&BPTReq_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStrA) == 0) {
                        return (void *)&BPTReq_Info.pClassSuperObject;
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
                        return BPTReq_New;
                    }
                    break;
                    
                case 'P':
#ifdef  BPTREQ_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStrA) == 0) {
                        return BPTReq_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStrA) == 0) {
                        return BPTReq_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  BPTREQ_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStrA) == 0) {
                        return BPTReq_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStrA) == 0) {
                        return BPTReq_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStrA) == 0) {
                        return BPTReqClass_WhoAmI;
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
bool            BPTReq_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_BPTREQ == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(BPTReq_Class())->pClassSuperObject;
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
void            BPTReq_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          BPTReq_Class (
    void
)
{
    return (OBJ_ID)&BPTReq_ClassObj;
}


static
uint16_t        BPTReq_WhoAmI (
    void
)
{
    return OBJ_IDENT_BPTREQ;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  BPTREQ_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
BPTREQ_VTBL     BPTReq_VtblShared = {
    {
        &BPTReq_Info,
        BPTReq_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        BPTReq_Dealloc,
        BPTReq_Class,
        BPTReq_WhoAmI,
        (P_OBJ_QUERYINFO)BPTReq_QueryInfo,
        (P_OBJ_TOSTRING)BPTReq_ToDebugString,
        NULL,           // BPTReq_Enable,
        NULL,           // BPTReq_Disable,
        NULL,           // (P_OBJ_ASSIGN)BPTReq_Assign,
        NULL,           // (P_OBJ_COMPARE)BPTReq_Compare,
        NULL,           // (P_OBJ_PTR)BPTReq_Copy,
        NULL,           // (P_OBJ_PTR)BPTReq_DeepCopy,
        NULL            // (P_OBJ_HASH)BPTReq_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //BPTReq_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
BPTREQ_VTBL     BPTReq_Vtbl = {
    {
        &BPTReq_Info,
        BPTReq_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        BPTReq_Dealloc,
        BPTReq_Class,
        BPTReq_WhoAmI,
        (P_OBJ_QUERYINFO)BPTReq_QueryInfo,
        (P_OBJ_TOSTRING)BPTReq_ToDebugString,
        NULL,           // BPTReq_Enable,
        NULL,           // BPTReq_Disable,
        NULL,           // (P_OBJ_ASSIGN)BPTReq_Assign,
        NULL,           // (P_OBJ_COMPARE)BPTReq_Compare,
        NULL,           // (P_OBJ_PTR)BPTReq_Copy,
        NULL,           // (P_OBJ_PTR)BPTReq_DeepCopy,
        NULL            // (P_OBJ_HASH)BPTReq_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //BPTReq_IsEnabled,
 
};



static
const
OBJ_INFO        BPTReq_Info = {
    "BPTReq",
    "B-Plus Tree Internal Request Processor",
    (OBJ_DATA *)&BPTReq_ClassObj,
#ifdef  BPTREQ_SUPER_DEFINED
    (OBJ_DATA *)&obj_ClassObj,
#else
    (OBJ_DATA *)&obj_ClassObj,
#endif
    (OBJ_IUNKNOWN *)&BPTReq_Vtbl,
    sizeof(BPTREQ_DATA)
};





