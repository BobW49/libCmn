// vi: nu:noai:ts=4:sw=4

//****************************************************************
//              Node based on a Token (NodeTkn) Object Support
//****************************************************************

//  Class Object Metods and Tables for 'NodeTkn'
//  Generated 01/27/2023 11:11:57


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




#define         NODETKN_OBJECT_C       1
#include        <NodeTkn_internal.h>
#ifdef  NODETKN_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct NodeTkn_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  NODETKN_SINGLETON
    volatile
    NODETKN_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          NodeTknClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        NodeTkn_Info;            // Forward Reference




static
bool            NodeTknClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_NODETKN_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(NodeTkn_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        NodeTknClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_NODETKN_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
NODETKN_CLASS_VTBL    class_Vtbl = {
    {
        &NodeTkn_Info,
        NodeTknClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        NodeTkn_Class,
        NodeTknClass_WhoAmI,
        (P_OBJ_QUERYINFO)NodeTknClass_QueryInfo,
        NULL                        // NodeTknClass_ToDebugString
    },
    (void *)NodeTkn_New
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

NODETKN_CLASS_DATA  NodeTkn_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(NODETKN_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  NODETKN_SINGLETON
extern
const
NODETKN_VTBL       NodeTkn_VtblShared;


NODETKN_DATA *     NodeTkn_getSingleton (
    void
)
{
    return (OBJ_ID)(NodeTkn_ClassObj.pSingleton);
}


bool            NodeTkn_setSingleton (
    NODETKN_DATA       *pValue
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
    if (NodeTkn_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(NodeTkn_ClassObj.pSingleton));
    }
    NodeTkn_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



NODETKN_DATA *     NodeTkn_Shared (
    void
)
{
    NODETKN_DATA       *this = (OBJ_ID)(NodeTkn_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = NodeTkn_New( );
        obj_setVtbl(this, (void *)&NodeTkn_VtblShared);
        NodeTkn_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // NodeTkn_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            NodeTkn_SharedReset (
    void
)
{
    NODETKN_DATA       *this = (OBJ_ID)(NodeTkn_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&NodeTkn_Vtbl);
        obj_Release(this);
        NodeTkn_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          NodeTknClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    NODETKN_CLASS_DATA *this = objId;
    const
    char            *pStrA = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(NODETKN_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStrA) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStrA) == 0) {
                        return (void *)&NodeTkn_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStrA) == 0) {
                        return (void *)&NodeTkn_Info.pClassSuperObject;
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
                        return NodeTkn_New;
                    }
                    break;
                    
                case 'P':
#ifdef  NODETKN_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStrA) == 0) {
                        return NodeTkn_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStrA) == 0) {
                        return NodeTkn_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  NODETKN_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStrA) == 0) {
                        return NodeTkn_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStrA) == 0) {
                        return NodeTkn_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStrA) == 0) {
                        return NodeTknClass_WhoAmI;
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
bool            NodeTkn_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_NODETKN == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(NodeTkn_Class())->pClassSuperObject;
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
void            NodeTkn_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          NodeTkn_Class (
    void
)
{
    return (OBJ_ID)&NodeTkn_ClassObj;
}


static
uint16_t        NodeTkn_WhoAmI (
    void
)
{
    return OBJ_IDENT_NODETKN;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  NODETKN_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
NODETKN_VTBL     NodeTkn_VtblShared = {
    {
        &NodeTkn_Info,
        NodeTkn_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NodeTkn_Dealloc,
        NodeTkn_Class,
        NodeTkn_WhoAmI,
        (P_OBJ_QUERYINFO)NodeTkn_QueryInfo,
        (P_OBJ_TOSTRING)NodeTkn_ToDebugString,
        NULL,           // NodeTkn_Enable,
        NULL,           // NodeTkn_Disable,
        NULL,           // (P_OBJ_ASSIGN)NodeTkn_Assign,
        NULL,           // (P_OBJ_COMPARE)NodeTkn_Compare,
        NULL,           // (P_OBJ_PTR)NodeTkn_Copy,
        NULL,           // (P_OBJ_PTR)NodeTkn_DeepCopy,
        NULL            // (P_OBJ_HASH)NodeTkn_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //NodeTkn_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
NODETKN_VTBL     NodeTkn_Vtbl = {
    {
        &NodeTkn_Info,
        NodeTkn_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        NodeTkn_Dealloc,
        NodeTkn_Class,
        NodeTkn_WhoAmI,
        (P_OBJ_QUERYINFO)NodeTkn_QueryInfo,
        (P_OBJ_TOSTRING)NodeTkn_ToDebugString,
        NULL,           // NodeTkn_Enable,
        NULL,           // NodeTkn_Disable,
        NULL,           // (P_OBJ_ASSIGN)NodeTkn_Assign,
        NULL,           // (P_OBJ_COMPARE)NodeTkn_Compare,
        NULL,           // (P_OBJ_PTR)NodeTkn_Copy,
        NULL,           // (P_OBJ_PTR)NodeTkn_DeepCopy,
        NULL            // (P_OBJ_HASH)NodeTkn_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //NodeTkn_IsEnabled,
 
};



static
const
OBJ_INFO        NodeTkn_Info = {
    "NodeTkn",
    "Node based on a Token",
    (OBJ_DATA *)&NodeTkn_ClassObj,
#ifdef  NODETKN_SUPER_DEFINED
    (OBJ_DATA *)&Node_ClassObj,
#else
    (OBJ_DATA *)&obj_ClassObj,
#endif
    (OBJ_IUNKNOWN *)&NodeTkn_Vtbl,
    sizeof(NODETKN_DATA)
};





