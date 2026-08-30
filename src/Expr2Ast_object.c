// vi: nu:noai:ts=4:sw=4

//****************************************************************
//  Parse an Expression into an AST (Expr2Ast) Object Support
//****************************************************************

//  Class Object Metods and Tables for 'Expr2Ast'
//  Generated 02/10/2023 10:03:03


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




#define         EXPR2AST_OBJECT_C       1
#include        <Expr2Ast_internal.h>
#ifdef  EXPR2AST_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct Expr2Ast_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  EXPR2AST_SINGLETON
    volatile
    EXPR2AST_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          Expr2AstClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        Expr2Ast_Info;            // Forward Reference




static
bool            Expr2AstClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_EXPR2AST_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(Expr2Ast_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        Expr2AstClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_EXPR2AST_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
EXPR2AST_CLASS_VTBL    class_Vtbl = {
    {
        &Expr2Ast_Info,
        Expr2AstClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        Expr2Ast_Class,
        Expr2AstClass_WhoAmI,
        (P_OBJ_QUERYINFO)Expr2AstClass_QueryInfo,
        NULL                        // Expr2AstClass_ToDebugString
    },
    (void *)Expr2Ast_New
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

EXPR2AST_CLASS_DATA  Expr2Ast_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(EXPR2AST_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  EXPR2AST_SINGLETON
extern
const
EXPR2AST_VTBL       Expr2Ast_VtblShared;


EXPR2AST_DATA *     Expr2Ast_getSingleton (
    void
)
{
    return (OBJ_ID)(Expr2Ast_ClassObj.pSingleton);
}


bool            Expr2Ast_setSingleton (
    EXPR2AST_DATA       *pValue
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
    if (Expr2Ast_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(Expr2Ast_ClassObj.pSingleton));
    }
    Expr2Ast_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



EXPR2AST_DATA *     Expr2Ast_Shared (
    void
)
{
    EXPR2AST_DATA       *this = (OBJ_ID)(Expr2Ast_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = Expr2Ast_New( );
        obj_setVtbl(this, (void *)&Expr2Ast_VtblShared);
        Expr2Ast_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // Expr2Ast_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            Expr2Ast_SharedReset (
    void
)
{
    EXPR2AST_DATA       *this = (OBJ_ID)(Expr2Ast_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&Expr2Ast_Vtbl);
        obj_Release(this);
        Expr2Ast_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          Expr2AstClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    EXPR2AST_CLASS_DATA *this = objId;
    const
    char            *pStrA = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(EXPR2AST_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStrA) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStrA) == 0) {
                        return (void *)&Expr2Ast_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStrA) == 0) {
                        return (void *)&Expr2Ast_Info.pClassSuperObject;
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
                        return Expr2Ast_New;
                    }
                    break;
                    
                case 'P':
#ifdef  EXPR2AST_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStrA) == 0) {
                        return Expr2Ast_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStrA) == 0) {
                        return Expr2Ast_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  EXPR2AST_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStrA) == 0) {
                        return Expr2Ast_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStrA) == 0) {
                        return Expr2Ast_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStrA) == 0) {
                        return Expr2AstClass_WhoAmI;
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
bool            Expr2Ast_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_EXPR2AST == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(Expr2Ast_Class())->pClassSuperObject;
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
void            Expr2Ast_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          Expr2Ast_Class (
    void
)
{
    return (OBJ_ID)&Expr2Ast_ClassObj;
}


static
uint16_t        Expr2Ast_WhoAmI (
    void
)
{
    return OBJ_IDENT_EXPR2AST;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  EXPR2AST_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
EXPR2AST_VTBL     Expr2Ast_VtblShared = {
    {
        &Expr2Ast_Info,
        Expr2Ast_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        Expr2Ast_Dealloc,
        Expr2Ast_Class,
        Expr2Ast_WhoAmI,
        (P_OBJ_QUERYINFO)Expr2Ast_QueryInfo,
        (P_OBJ_TOSTRING)Expr2Ast_ToDebugString,
        NULL,           // Expr2Ast_Enable,
        NULL,           // Expr2Ast_Disable,
        NULL,           // (P_OBJ_ASSIGN)Expr2Ast_Assign,
        NULL,           // (P_OBJ_COMPARE)Expr2Ast_Compare,
        NULL,           // (P_OBJ_PTR)Expr2Ast_Copy,
        NULL,           // (P_OBJ_PTR)Expr2Ast_DeepCopy,
        NULL            // (P_OBJ_HASH)Expr2Ast_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Expr2Ast_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
EXPR2AST_VTBL     Expr2Ast_Vtbl = {
    {
        &Expr2Ast_Info,
        Expr2Ast_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        Expr2Ast_Dealloc,
        Expr2Ast_Class,
        Expr2Ast_WhoAmI,
        (P_OBJ_QUERYINFO)Expr2Ast_QueryInfo,
        (P_OBJ_TOSTRING)Expr2Ast_ToDebugString,
        NULL,           // Expr2Ast_Enable,
        NULL,           // Expr2Ast_Disable,
        NULL,           // (P_OBJ_ASSIGN)Expr2Ast_Assign,
        NULL,           // (P_OBJ_COMPARE)Expr2Ast_Compare,
        NULL,           // (P_OBJ_PTR)Expr2Ast_Copy,
        NULL,           // (P_OBJ_PTR)Expr2Ast_DeepCopy,
        NULL            // (P_OBJ_HASH)Expr2Ast_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Expr2Ast_IsEnabled,
 
};



static
const
OBJ_INFO        Expr2Ast_Info = {
    "Expr2Ast",
    "Parse an Expression into an AST",
    (OBJ_DATA *)&Expr2Ast_ClassObj,
#ifdef  EXPR2AST_SUPER_DEFINED
    (OBJ_DATA *)&OpPrec_ClassObj,
#else
    (OBJ_DATA *)&obj_ClassObj,
#endif
    (OBJ_IUNKNOWN *)&Expr2Ast_Vtbl,
    sizeof(EXPR2AST_DATA)
};





