// vi: nu:noai:ts=4:sw=4

//****************************************************************
//              Operator Precedence Parser (OpPrec) Object Support
//****************************************************************

//  Class Object Metods and Tables for 'OpPrec'
//  Generated 03/04/2023 08:33:53


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




#define         OPPREC_OBJECT_C       1
#include        <OpPrec_internal.h>
#ifdef  OPPREC_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct OpPrec_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  OPPREC_SINGLETON
    volatile
    OPPREC_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          OpPrecClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        OpPrec_Info;            // Forward Reference




static
bool            OpPrecClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_OPPREC_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(OpPrec_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        OpPrecClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_OPPREC_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
OPPREC_CLASS_VTBL    class_Vtbl = {
    {
        &OpPrec_Info,
        OpPrecClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        OpPrec_Class,
        OpPrecClass_WhoAmI,
        (P_OBJ_QUERYINFO)OpPrecClass_QueryInfo,
        NULL                        // OpPrecClass_ToDebugString
    },
    (void *)OpPrec_New
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

OPPREC_CLASS_DATA  OpPrec_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(OPPREC_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  OPPREC_SINGLETON
extern
const
OPPREC_VTBL       OpPrec_VtblShared;


OPPREC_DATA *     OpPrec_getSingleton (
    void
)
{
    return (OBJ_ID)(OpPrec_ClassObj.pSingleton);
}


bool            OpPrec_setSingleton (
    OPPREC_DATA       *pValue
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
    if (OpPrec_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(OpPrec_ClassObj.pSingleton));
    }
    OpPrec_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



OPPREC_DATA *     OpPrec_Shared (
    void
)
{
    OPPREC_DATA       *this = (OBJ_ID)(OpPrec_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = OpPrec_New( );
        obj_setVtbl(this, (void *)&OpPrec_VtblShared);
        OpPrec_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // OpPrec_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            OpPrec_SharedReset (
    void
)
{
    OPPREC_DATA       *this = (OBJ_ID)(OpPrec_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&OpPrec_Vtbl);
        obj_Release(this);
        OpPrec_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          OpPrecClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    OPPREC_CLASS_DATA *this = objId;
    const
    char            *pStrA = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(OPPREC_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStrA) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStrA) == 0) {
                        return (void *)&OpPrec_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStrA) == 0) {
                        return (void *)&OpPrec_Info.pClassSuperObject;
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
                        return OpPrec_New;
                    }
                    break;
                    
                case 'P':
#ifdef  OPPREC_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStrA) == 0) {
                        return OpPrec_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStrA) == 0) {
                        return OpPrec_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  OPPREC_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStrA) == 0) {
                        return OpPrec_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStrA) == 0) {
                        return OpPrec_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStrA) == 0) {
                        return OpPrecClass_WhoAmI;
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
bool            OpPrec_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_OPPREC == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(OpPrec_Class())->pClassSuperObject;
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
void            OpPrec_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          OpPrec_Class (
    void
)
{
    return (OBJ_ID)&OpPrec_ClassObj;
}


static
uint16_t        OpPrec_WhoAmI (
    void
)
{
    return OBJ_IDENT_OPPREC;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  OPPREC_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
OPPREC_VTBL     OpPrec_VtblShared = {
    {
        &OpPrec_Info,
        OpPrec_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        OpPrec_Dealloc,
        OpPrec_Class,
        OpPrec_WhoAmI,
        (P_OBJ_QUERYINFO)OpPrec_QueryInfo,
        (P_OBJ_TOSTRING)OpPrec_ToDebugString,
        NULL,           // OpPrec_Enable,
        NULL,           // OpPrec_Disable,
        NULL,           // (P_OBJ_ASSIGN)OpPrec_Assign,
        NULL,           // (P_OBJ_COMPARE)OpPrec_Compare,
        NULL,           // (P_OBJ_PTR)OpPrec_Copy,
        NULL,           // (P_OBJ_PTR)OpPrec_DeepCopy,
        NULL            // (P_OBJ_HASH)OpPrec_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //OpPrec_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
OPPREC_VTBL     OpPrec_Vtbl = {
    {
        &OpPrec_Info,
        OpPrec_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        OpPrec_Dealloc,
        OpPrec_Class,
        OpPrec_WhoAmI,
        (P_OBJ_QUERYINFO)OpPrec_QueryInfo,
        (P_OBJ_TOSTRING)OpPrec_ToDebugString,
        NULL,           // OpPrec_Enable,
        NULL,           // OpPrec_Disable,
        NULL,           // (P_OBJ_ASSIGN)OpPrec_Assign,
        NULL,           // (P_OBJ_COMPARE)OpPrec_Compare,
        NULL,           // (P_OBJ_PTR)OpPrec_Copy,
        NULL,           // (P_OBJ_PTR)OpPrec_DeepCopy,
        NULL            // (P_OBJ_HASH)OpPrec_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //OpPrec_IsEnabled,
 
};



static
const
OBJ_INFO        OpPrec_Info = {
    "OpPrec",
    "Operator Precedence Parser",
    (OBJ_DATA *)&OpPrec_ClassObj,
#ifdef  OPPREC_SUPER_DEFINED
    (OBJ_DATA *)&obj_ClassObj,
#else
    (OBJ_DATA *)&obj_ClassObj,
#endif
    (OBJ_IUNKNOWN *)&OpPrec_Vtbl,
    sizeof(OPPREC_DATA)
};





