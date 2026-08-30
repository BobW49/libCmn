// vi: nu:noai:ts=4:sw=4

//****************************************************************
//              Abstract Syntax Tree (Ast) Object Support
//****************************************************************

//  Class Object Metods and Tables for 'Ast'
//  Generated 02/04/2023 09:41:47


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




#define         AST_OBJECT_C       1
#include        <Ast_internal.h>
#ifdef  AST_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct Ast_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  AST_SINGLETON
    volatile
    AST_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          AstClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        Ast_Info;            // Forward Reference




static
bool            AstClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_AST_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(Ast_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        AstClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_AST_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
AST_CLASS_VTBL    class_Vtbl = {
    {
        &Ast_Info,
        AstClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        Ast_Class,
        AstClass_WhoAmI,
        (P_OBJ_QUERYINFO)AstClass_QueryInfo,
        NULL                        // AstClass_ToDebugString
    },
    (void *)Ast_New
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

AST_CLASS_DATA  Ast_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(AST_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  AST_SINGLETON
extern
const
AST_VTBL       Ast_VtblShared;


AST_DATA *     Ast_getSingleton (
    void
)
{
    return (OBJ_ID)(Ast_ClassObj.pSingleton);
}


bool            Ast_setSingleton (
    AST_DATA       *pValue
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
    if (Ast_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(Ast_ClassObj.pSingleton));
    }
    Ast_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



AST_DATA *     Ast_Shared (
    void
)
{
    AST_DATA       *this = (OBJ_ID)(Ast_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = Ast_New( );
        obj_setVtbl(this, (void *)&Ast_VtblShared);
        Ast_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // Ast_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            Ast_SharedReset (
    void
)
{
    AST_DATA       *this = (OBJ_ID)(Ast_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&Ast_Vtbl);
        obj_Release(this);
        Ast_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          AstClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    AST_CLASS_DATA *this = objId;
    const
    char            *pStrA = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(AST_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStrA) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStrA) == 0) {
                        return (void *)&Ast_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStrA) == 0) {
                        return (void *)&Ast_Info.pClassSuperObject;
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
                        return Ast_New;
                    }
                    break;
                    
                case 'P':
#ifdef  AST_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStrA) == 0) {
                        return Ast_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStrA) == 0) {
                        return Ast_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  AST_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStrA) == 0) {
                        return Ast_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStrA) == 0) {
                        return Ast_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStrA) == 0) {
                        return AstClass_WhoAmI;
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
bool            Ast_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_AST == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(Ast_Class())->pClassSuperObject;
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
void            Ast_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          Ast_Class (
    void
)
{
    return (OBJ_ID)&Ast_ClassObj;
}


static
uint16_t        Ast_WhoAmI (
    void
)
{
    return OBJ_IDENT_AST;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  AST_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
AST_VTBL     Ast_VtblShared = {
    {
        &Ast_Info,
        Ast_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        Ast_Dealloc,
        Ast_Class,
        Ast_WhoAmI,
        (P_OBJ_QUERYINFO)Ast_QueryInfo,
        (P_OBJ_TOSTRING)Ast_ToDebugString,
        NULL,           // Ast_Enable,
        NULL,           // Ast_Disable,
        NULL,           // (P_OBJ_ASSIGN)Ast_Assign,
        NULL,           // (P_OBJ_COMPARE)Ast_Compare,
        NULL,           // (P_OBJ_PTR)Ast_Copy,
        NULL,           // (P_OBJ_PTR)Ast_DeepCopy,
        NULL            // (P_OBJ_HASH)Ast_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Ast_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
AST_VTBL     Ast_Vtbl = {
    {
        &Ast_Info,
        Ast_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        Ast_Dealloc,
        Ast_Class,
        Ast_WhoAmI,
        (P_OBJ_QUERYINFO)Ast_QueryInfo,
        (P_OBJ_TOSTRING)Ast_ToDebugString,
        NULL,           // Ast_Enable,
        NULL,           // Ast_Disable,
        NULL,           // (P_OBJ_ASSIGN)Ast_Assign,
        NULL,           // (P_OBJ_COMPARE)Ast_Compare,
        NULL,           // (P_OBJ_PTR)Ast_Copy,
        NULL,           // (P_OBJ_PTR)Ast_DeepCopy,
        NULL            // (P_OBJ_HASH)Ast_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Ast_IsEnabled,
 
};



static
const
OBJ_INFO        Ast_Info = {
    "Ast",
    "Abstract Syntax Tree",
    (OBJ_DATA *)&Ast_ClassObj,
#ifdef  AST_SUPER_DEFINED
    (OBJ_DATA *)&Blocks_ClassObj,
#else
    (OBJ_DATA *)&obj_ClassObj,
#endif
    (OBJ_IUNKNOWN *)&Ast_Vtbl,
    sizeof(AST_DATA)
};





