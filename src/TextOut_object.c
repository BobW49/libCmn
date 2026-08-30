// vi: nu:noai:ts=4:sw=4

//****************************************************************
//              Output UTF-8 Textual Data (TextOut) Object Support
//****************************************************************

//  Class Object Metods and Tables for 'TextOut'
//  Generated 08/03/2023 22:53:34


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




#define         TEXTOUT_OBJECT_C       1
#include        <TextOut_internal.h>
#ifdef  TEXTOUT_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct TextOut_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  TEXTOUT_SINGLETON
    volatile
    TEXTOUT_DATA       *pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
void *          TextOutClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        TextOut_Info;            // Forward Reference




static
bool            TextOutClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_TEXTOUT_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(TextOut_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        TextOutClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_TEXTOUT_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
TEXTOUT_CLASS_VTBL    class_Vtbl = {
    {
        &TextOut_Info,
        TextOutClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        TextOut_Class,
        TextOutClass_WhoAmI,
        (P_OBJ_QUERYINFO)TextOutClass_QueryInfo,
        NULL                        // TextOutClass_ToDebugString
    },
    (void *)TextOut_New
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

TEXTOUT_CLASS_DATA  TextOut_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(TEXTOUT_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    //0
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  TEXTOUT_SINGLETON
extern
const
TEXTOUT_VTBL       TextOut_VtblShared;


TEXTOUT_DATA *     TextOut_getSingleton (
    void
)
{
    return (OBJ_ID)(TextOut_ClassObj.pSingleton);
}


bool            TextOut_setSingleton (
    TEXTOUT_DATA       *pValue
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
    if (TextOut_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(TextOut_ClassObj.pSingleton));
    }
    TextOut_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



TEXTOUT_DATA *     TextOut_Shared (
    void
)
{
    TEXTOUT_DATA       *this = (OBJ_ID)(TextOut_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = TextOut_New( );
        obj_setVtbl(this, (void *)&TextOut_VtblShared);
        TextOut_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // TextOut_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            TextOut_SharedReset (
    void
)
{
    TEXTOUT_DATA       *this = (OBJ_ID)(TextOut_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&TextOut_Vtbl);
        obj_Release(this);
        TextOut_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          TextOutClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    TEXTOUT_CLASS_DATA *this = objId;
    const
    char            *pStrA = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(TEXTOUT_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStrA) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStrA) == 0) {
                        return (void *)&TextOut_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStrA) == 0) {
                        return (void *)&TextOut_Info.pClassSuperObject;
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
                        return TextOut_New;
                    }
                    break;
                    
                case 'P':
#ifdef  TEXTOUT_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStrA) == 0) {
                        return TextOut_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStrA) == 0) {
                        return TextOut_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  TEXTOUT_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStrA) == 0) {
                        return TextOut_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStrA) == 0) {
                        return TextOut_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStrA) == 0) {
                        return TextOutClass_WhoAmI;
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
bool            TextOut_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_TEXTOUT == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(TextOut_Class())->pClassSuperObject;
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
void            TextOut_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          TextOut_Class (
    void
)
{
    return (OBJ_ID)&TextOut_ClassObj;
}


static
uint16_t        TextOut_WhoAmI (
    void
)
{
    return OBJ_IDENT_TEXTOUT;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  TEXTOUT_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
TEXTOUT_VTBL     TextOut_VtblShared = {
    {
        &TextOut_Info,
        TextOut_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        TextOut_Dealloc,
        TextOut_Class,
        TextOut_WhoAmI,
        (P_OBJ_QUERYINFO)TextOut_QueryInfo,
        (P_OBJ_TOSTRING)TextOut_ToDebugString,
        NULL,           // TextOut_Enable,
        NULL,           // TextOut_Disable,
        NULL,           // (P_OBJ_ASSIGN)TextOut_Assign,
        NULL,           // (P_OBJ_COMPARE)TextOut_Compare,
        NULL,           // (P_OBJ_PTR)TextOut_Copy,
        NULL,           // (P_OBJ_PTR)TextOut_DeepCopy,
        NULL            // (P_OBJ_HASH)TextOut_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //TextOut_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
TEXTOUT_VTBL     TextOut_Vtbl = {
    {
        &TextOut_Info,
        TextOut_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        TextOut_Dealloc,
        TextOut_Class,
        TextOut_WhoAmI,
        (P_OBJ_QUERYINFO)TextOut_QueryInfo,
        (P_OBJ_TOSTRING)TextOut_ToDebugString,
        NULL,           // TextOut_Enable,
        NULL,           // TextOut_Disable,
        NULL,           // (P_OBJ_ASSIGN)TextOut_Assign,
        NULL,           // (P_OBJ_COMPARE)TextOut_Compare,
        NULL,           // (P_OBJ_PTR)TextOut_Copy,
        NULL,           // (P_OBJ_PTR)TextOut_DeepCopy,
        NULL            // (P_OBJ_HASH)TextOut_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //TextOut_IsEnabled,
 
};



static
const
OBJ_INFO        TextOut_Info = {
    "TextOut",
    "Output UTF-8 Textual Data",
    (OBJ_DATA *)&TextOut_ClassObj,
#ifdef  TEXTOUT_SUPER_DEFINED
    (OBJ_DATA *)&obj_ClassObj,
#else
    (OBJ_DATA *)&obj_ClassObj,
#endif
    (OBJ_IUNKNOWN *)&TextOut_Vtbl,
    sizeof(TEXTOUT_DATA)
};





