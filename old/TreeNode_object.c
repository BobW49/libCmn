// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'TreeNode'
//  Generated 06/18/2022 09:52:39


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




#define         TREENODE_OBJECT_C       1
#include        <TreeNode_internal.h>
#ifdef  TREENODE_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct TreeNode_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  TREENODE_SINGLETON
    volatile
    TREENODE_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          TreeNodeClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        TreeNode_Info;            // Forward Reference




static
bool            TreeNodeClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_TREENODE_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(TreeNode_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        TreeNodeClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_TREENODE_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
TREENODE_CLASS_VTBL    class_Vtbl = {
    {
        &TreeNode_Info,
        TreeNodeClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        TreeNode_Class,
        TreeNodeClass_WhoAmI,
        (P_OBJ_QUERYINFO)TreeNodeClass_QueryInfo,
        NULL                        // TreeNodeClass_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

TREENODE_CLASS_DATA  TreeNode_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(TREENODE_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  TREENODE_SINGLETON
extern
const
TREENODE_VTBL       TreeNode_VtblShared;


TREENODE_DATA *     TreeNode_getSingleton (
    void
)
{
    return (OBJ_ID)(TreeNode_ClassObj.pSingleton);
}


bool            TreeNode_setSingleton (
    TREENODE_DATA       *pValue
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
    if (TreeNode_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(TreeNode_ClassObj.pSingleton));
    }
    TreeNode_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



TREENODE_DATA *     TreeNode_Shared (
    void
)
{
    TREENODE_DATA       *this = (OBJ_ID)(TreeNode_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = TreeNode_New( );
        obj_setVtbl(this, (void *)&TreeNode_VtblShared);
        TreeNode_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // TreeNode_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            TreeNode_SharedReset (
    void
)
{
    TREENODE_DATA       *this = (OBJ_ID)(TreeNode_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&TreeNode_Vtbl);
        obj_Release(this);
        TreeNode_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          TreeNodeClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    TREENODE_CLASS_DATA *this = objId;
    const
    char            *pStrA = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(TREENODE_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStrA) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStrA) == 0) {
                        return (void *)&TreeNode_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStrA) == 0) {
                        return (void *)&TreeNode_Info.pClassSuperObject;
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
                        return TreeNode_New;
                    }
                    break;
                    
                case 'P':
#ifdef  TREENODE_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStrA) == 0) {
                        return TreeNode_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStrA) == 0) {
                        return TreeNode_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  TREENODE_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStrA) == 0) {
                        return TreeNode_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStrA) == 0) {
                        return TreeNode_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStrA) == 0) {
                        return TreeNodeClass_WhoAmI;
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
bool            TreeNode_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_TREENODE == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(TreeNode_Class())->pClassSuperObject;
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
void            TreeNode_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          TreeNode_Class (
    void
)
{
    return (OBJ_ID)&TreeNode_ClassObj;
}


static
uint16_t        TreeNode_WhoAmI (
    void
)
{
    return OBJ_IDENT_TREENODE;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  TREENODE_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
TREENODE_VTBL     TreeNode_VtblShared = {
    {
        &TreeNode_Info,
        TreeNode_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        TreeNode_Dealloc,
        TreeNode_Class,
        TreeNode_WhoAmI,
        (P_OBJ_QUERYINFO)TreeNode_QueryInfo,
        (P_OBJ_TOSTRING)TreeNode_ToDebugString,
        NULL,           // TreeNode_Enable,
        NULL,           // TreeNode_Disable,
        NULL,           // (P_OBJ_ASSIGN)TreeNode_Assign,
        NULL,           // (P_OBJ_COMPARE)TreeNode_Compare,
        NULL,           // (P_OBJ_PTR)TreeNode_Copy,
        NULL,           // (P_OBJ_PTR)TreeNode_DeepCopy,
        NULL            // (P_OBJ_HASH)TreeNode_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //TreeNode_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
TREENODE_VTBL     TreeNode_Vtbl = {
    {
        &TreeNode_Info,
        TreeNode_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        TreeNode_Dealloc,
        TreeNode_Class,
        TreeNode_WhoAmI,
        (P_OBJ_QUERYINFO)TreeNode_QueryInfo,
        (P_OBJ_TOSTRING)TreeNode_ToDebugString,
        NULL,           // TreeNode_Enable,
        NULL,           // TreeNode_Disable,
        NULL,           // (P_OBJ_ASSIGN)TreeNode_Assign,
        NULL,           // (P_OBJ_COMPARE)TreeNode_Compare,
        NULL,           // (P_OBJ_PTR)TreeNode_Copy,
        NULL,           // (P_OBJ_PTR)TreeNode_DeepCopy,
        NULL            // (P_OBJ_HASH)TreeNode_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //TreeNode_IsEnabled,
 
};



static
const
OBJ_INFO        TreeNode_Info = {
    "TreeNode",
    "NodeTree Node/Entry",
    (OBJ_DATA *)&TreeNode_ClassObj,
#ifdef  TREENODE_SUPER_DEFINED
    (OBJ_DATA *)&obj_ClassObj,
#else
    (OBJ_DATA *)&obj_ClassObj,
#endif
    (OBJ_IUNKNOWN *)&TreeNode_Vtbl,
    sizeof(TREENODE_DATA)
};





