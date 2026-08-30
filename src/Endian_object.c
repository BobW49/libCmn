// vi: nu:noai:ts=4:sw=4

//  Class Object Metods and Tables for 'Endian'
//  Generated 09/19/2021 09:04:28


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




#define         ENDIAN_OBJECT_C       1
#include        <Endian_internal.h>
#ifdef  ENDIAN_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Class Object Definition
//===========================================================

struct Endian_class_data_s    {
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
#ifdef  ENDIAN_SINGLETON
    volatile
    ENDIAN_DATA  	*pSingleton;
#endif
    //uint32_t        misc;
    //OBJ_ID          pObjCatalog;
	uint8_t			flags;
#define	ENDIAN_CALC	0x80		/* Endianness has been calculated */
#define ENDIAN_BIG	0x40
	uint8_t			filler8[3];
};




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------


#ifdef __GNUC__
#else
static inline uint16_t __builtin_bswap16(uint16_t x) {
    return (x >> 8) | (x << 8);
}

static inline uint32_t __builtin_bswap32(uint32_t x) {
    return ((x & 0x000000FFU) << 24) |
           ((x & 0x0000FF00U) <<  8) |
           ((x & 0x00FF0000U) >>  8) |
           ((x & 0xFF000000U) >> 24);
}

static inline uint64_t __builtin_bswap64(uint64_t x) {
    return ((x & 0x00000000000000FFULL) << 56) |
           ((x & 0x000000000000FF00ULL) << 40) |
           ((x & 0x0000000000FF0000ULL) << 24) |
           ((x & 0x00000000FF000000ULL) <<  8) |
           ((x & 0x000000FF00000000ULL) >>  8) |
           ((x & 0x0000FF0000000000ULL) >> 24) |
           ((x & 0x00FF000000000000ULL) >> 40) |
           ((x & 0xFF00000000000000ULL) >> 56);
}
#endif


//---------------------------------------------------------------
//               Byte Swap Functions (Little <-> Big)
//---------------------------------------------------------------

uint16_t        Endian_Swap16(uint16_t value)
{
    return __builtin_bswap16(value);
}

uint32_t        Endian_Swap32(uint32_t value)
{
    return __builtin_bswap32(value);
}

uint64_t        Endian_Swap64(uint64_t value)
{
    return __builtin_bswap64(value);
}


//---------------------------------------------------------------
//               Other Class Objects
//---------------------------------------------------------------

static
void *          EndianClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


static
const
OBJ_INFO        Endian_Info;            // Forward Reference




static
bool            EndianClass_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    
    if (OBJ_IDENT_ENDIAN_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    
    pObj = obj_getInfo(Endian_Class())->pClassSuperObject;
    if (pObj == obj_BaseClass())
        ;
    else {
        return obj_getVtbl(pObj)->pIsKindOf(classID);
    }
    
    return false;
}


static
uint16_t        EndianClass_WhoAmI (
    void
)
{
    return OBJ_IDENT_ENDIAN_CLASS;
}




//===========================================================
//                 Class Object Vtbl Definition
//===========================================================

static
const
ENDIAN_CLASS_VTBL    class_Vtbl = {
    {
        &Endian_Info,
        EndianClass_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        NULL,
        Endian_Class,
        EndianClass_WhoAmI,
        (P_OBJ_QUERYINFO)EndianClass_QueryInfo,
        NULL                        // EndianClass_ToDebugString
    },
};



//-----------------------------------------------------------
//                      Class Object
//-----------------------------------------------------------

ENDIAN_CLASS_DATA  Endian_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
        sizeof(ENDIAN_CLASS_DATA),                  // cbSize
        0,                                      // cbFlags
        1,                                      // cbRetainCount
        {0}                                     // cbMisc
    },
    0											// Flags
};



//---------------------------------------------------------------
//          S i n g l e t o n  M e t h o d s
//---------------------------------------------------------------

#ifdef  ENDIAN_SINGLETON
extern
const
ENDIAN_VTBL       Endian_VtblShared;


ENDIAN_DATA *     Endian_getSingleton (
    void
)
{
    return (OBJ_ID)(Endian_ClassObj.pSingleton);
}


bool            Endian_setSingleton (
    ENDIAN_DATA       *pValue
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
    if (Endian_ClassObj.pSingleton) {
        obj_Release((OBJ_ID)(Endian_ClassObj.pSingleton));
    }
    Endian_ClassObj.pSingleton = pValue;
    
    fRc = psxLock_Unlock(pLock);
    obj_Release(pLock);
    pLock = OBJ_NIL;
    return true;
}



ENDIAN_DATA *     Endian_Shared (
    void
)
{
    ENDIAN_DATA       *this = (OBJ_ID)(Endian_ClassObj.pSingleton);
    
    if (NULL == this) {
        this = Endian_New( );
        obj_setVtbl(this, (void *)&Endian_VtblShared);
        Endian_setSingleton(this);
        obj_Release(this);          // Shared controls object retention now.
        // Endian_ClassObj.pSingleton = OBJ_NIL;
    }
    
    return this;
}



void            Endian_SharedReset (
    void
)
{
    ENDIAN_DATA       *this = (OBJ_ID)(Endian_ClassObj.pSingleton);
    
    if (this) {
        obj_setVtbl(this, (void *)&Endian_Vtbl);
        obj_Release(this);
        Endian_ClassObj.pSingleton = OBJ_NIL;
    }
    
}



#endif



//---------------------------------------------------------------
//                     I s  B i g
//---------------------------------------------------------------

bool            Endian_IsBig (
    void
)
{
	struct Endian_class_data_s
					*pObj = &Endian_ClassObj;
    uint16_t        value;
	uint8_t			*pBytes;
	bool			fBig = false;

    // Do initialization.
    if ((pObj->flags & ENDIAN_CALC) == 0) {
        pObj->flags &= 0xFF - ENDIAN_BIG;
        value = 0x1234;
        // Big Endian is stored 0x12,0x34
        // Little Endian is stored 0x34,0x12
        pBytes = (uint8_t *)&value;
        if (pBytes[0] == 0x12) {
            pObj->flags |= ENDIAN_BIG;
            fBig = true;
			fprintf(stderr, "Endian is BIG!");
        }
        pObj->flags |= ENDIAN_CALC;
    }
    
    if (pObj->flags & ENDIAN_BIG) {
        fBig = true;
    }

    // Return to caller.
    return fBig;
}


//---------------------------------------------------------------
//                       G e t U 1 6
//---------------------------------------------------------------

uint16_t        Endian_GetU16Big (
    void            *pValue
)
{
    uint16_t        value;
    uint8_t         *pByte = pValue;

    // Do initialization.
	if (Endian_IsBig()) {
        value  = (*(uint16_t *)pValue);
	} else {
        value  = (*pByte++ & 0xFF) << 8;
        value |= (*pByte & 0xFF);
	}

    // Return to caller.
    return value;
}


uint16_t        Endian_GetU16Little(
    void            *pValue
)
{
    uint16_t        value;
    uint8_t         *pByte = pValue;

    // Do initialization.

    if (Endian_IsBig()) {
        value  = (*pByte++ & 0xFF);
        value |= (*pByte & 0xFF) << 8;
    } else {
        value  = (*(uint16_t *)pValue);
    }

    // Return to caller.
    return value;
}



//---------------------------------------------------------------
//                       G e t U 2 4
//---------------------------------------------------------------

uint32_t        Endian_GetU24Big(
    void            *pValue
)
{
    uint32_t        value;
    uint8_t         *pByte = pValue;

    // Do initialization.

    if (Endian_IsBig()) {
        value  = (*(uint32_t *)pValue) >> 8;
    } else {
        value  = (*pByte++ & 0xFF) << 16;
        value |= (*pByte++ & 0xFF) << 8;
        value |= (*pByte & 0xFF);
    }

    // Return to caller.
    return value;
}


uint32_t        Endian_GetU24Little(
    void            *pValue
)
{
    uint32_t        value;
    uint8_t         *pByte = pValue;

    // Do initialization.

    if (Endian_IsBig()) {
        value  = (*pByte++ & 0xFF);
        value |= (*pByte++ & 0xFF) << 8;
        value |= (*pByte & 0xFF) << 16;
    } else {
        value  = (*(uint32_t *)pValue) >> 8;
    }

    // Return to caller.
    return value;
}



//---------------------------------------------------------------
//                       G e t U 3 2
//---------------------------------------------------------------

uint32_t        Endian_GetU32Big(
    void            *pValue
)
{
    uint32_t        value;
    uint8_t         *pByte = pValue;

    // Do initialization.

    if (Endian_IsBig()) {
        value  = (*(uint32_t *)pValue);
    } else {
        value  = (*pByte++ & 0xFF) << 24;
        value |= (*pByte++ & 0xFF) << 16;
        value |= (*pByte++ & 0xFF) << 8;
        value |= (*pByte & 0xFF);
    }

    // Return to caller.
    return value;
}


uint32_t        Endian_GetU32Little(
    void            *pValue
)
{
    uint32_t        value;
    uint8_t         *pByte = pValue;

    // Do initialization.

    if (Endian_IsBig()) {
        value  = (*pByte++ & 0xFF);
        value |= (*pByte++ & 0xFF) << 8;
        value |= (*pByte++ & 0xFF) << 16;
        value |= (*pByte & 0xFF) << 24;
    } else {
        value  = (*(uint32_t *)pValue);
    }

    // Return to caller.
    return value;
}



//---------------------------------------------------------------
//                       G e t U 6 4
//---------------------------------------------------------------

uint64_t        Endian_GetU64Big(
    void            *pValue
)
{
    uint64_t        value;
    uint8_t         *pByte = pValue;

    // Do initialization.

    if (Endian_IsBig()) {
        value  = (*(uint64_t *)pValue);
    } else {
        value  = ((uint64_t)(*pByte++ & 0xFF)) << 56;
        value |= ((uint64_t)(*pByte++ & 0xFF)) << 48;
        value |= ((uint64_t)(*pByte++ & 0xFF)) << 40;
        value |= ((uint64_t)(*pByte++ & 0xFF)) << 32;
        value |= ((uint64_t)(*pByte++ & 0xFF)) << 24;
        value |= ((uint64_t)(*pByte++ & 0xFF)) << 16;
        value |= ((uint64_t)(*pByte++ & 0xFF)) << 8;
        value |= ((uint64_t)(*pByte++ & 0xFF));
    }

    // Return to caller.
    return value;
}


uint64_t        Endian_GetU64Little(
    void            *pValue
)
{
    uint64_t        value;
    uint8_t         *pByte = pValue;

    // Do initialization.

    if (Endian_IsBig()) {
        value  = ((uint64_t)(*pByte++ & 0xFF)) << 56;
        value |= ((uint64_t)(*pByte++ & 0xFF)) << 48;
        value |= ((uint64_t)(*pByte++ & 0xFF)) << 40;
        value |= ((uint64_t)(*pByte++ & 0xFF)) << 32;
        value |= ((uint64_t)(*pByte++ & 0xFF)) << 24;
        value |= ((uint64_t)(*pByte++ & 0xFF)) << 16;
        value |= ((uint64_t)(*pByte++ & 0xFF)) << 8;
        value |= ((uint64_t)(*pByte++ & 0xFF));
    } else {
        value  = (*(uint64_t *)pValue);
    }

    // Return to caller.
    return value;
}



//---------------------------------------------------------------
//                     I s  L i t t l e
//---------------------------------------------------------------

bool            Endian_IsLittle(
    void
)
{

    // Do initialization.

    // Return to caller.
    return !Endian_IsBig();
}



//---------------------------------------------------------------
//                       P u t U 1 6
//---------------------------------------------------------------

ERESULT         Endian_PutU16Big(
    void            *pValue,        // Out
    uint16_t        value           // In
)
{

    // Do initialization.
#ifdef NDEBUG
#else
    if (NULL == pValue) {
        DEBUG_BREAK();
        return ERESULT_INVALID_PARAMETER;
    }
#endif

    if (Endian_IsBig()) {
        *(uint16_t *)pValue = value;
    } else {
        *(uint8_t *)pValue++ = (value >> 8) & 0xFF;
        *(uint8_t *)pValue++ = value & 0xFF;
    }

    // Return to caller.
    return ERESULT_SUCCESS;
}


ERESULT         Endian_PutU16Little(
    void            *pValue,        // Out
    uint16_t        value           // In
)
{

    // Do initialization.
#ifdef NDEBUG
#else
    if (NULL == pValue) {
        DEBUG_BREAK();
        return ERESULT_INVALID_PARAMETER;
    }
#endif

    if (Endian_IsLittle()) {
        *(uint16_t *)pValue = value;
    } else {
        *(uint8_t *)pValue++ = value & 0xFF;
        *(uint8_t *)pValue++ = (value >> 8) & 0xFF;
    }

    // Return to caller.
    return ERESULT_SUCCESS;
}



//---------------------------------------------------------------
//                       P u t U 2 4
//---------------------------------------------------------------

ERESULT         Endian_PutU24Big(
    void            *pValue,        // Out
    uint32_t        value           // In
)
{

    // Do initialization.
#ifdef NDEBUG
#else
    if (NULL == pValue) {
        DEBUG_BREAK();
        return ERESULT_INVALID_PARAMETER;
    }
#endif

    *(uint8_t *)pValue++ = (value >> 16) & 0xFF;
    *(uint8_t *)pValue++ = (value >> 8) & 0xFF;
    *(uint8_t *)pValue++ = value & 0xFF;

    // Return to caller.
    return ERESULT_SUCCESS;
}


ERESULT         Endian_PutU24Little(
    void            *pValue,        // Out
    uint32_t        value           // In
)
{

    // Do initialization.
#ifdef NDEBUG
#else
    if (NULL == pValue) {
        DEBUG_BREAK();
        return ERESULT_INVALID_PARAMETER;
    }
#endif

    *(uint8_t *)pValue++ = value & 0xFF;
    *(uint8_t *)pValue++ = (value >> 8) & 0xFF;
    *(uint8_t *)pValue++ = (value >> 16) & 0xFF;

    // Return to caller.
    return ERESULT_SUCCESS;
}



//---------------------------------------------------------------
//                       P u t U 3 2
//---------------------------------------------------------------

ERESULT         Endian_PutU32Big(
    void            *pValue,        // Out
    uint32_t        value           // In
)
{

    // Do initialization.
#ifdef NDEBUG
#else
    if (NULL == pValue) {
        DEBUG_BREAK();
        return ERESULT_INVALID_PARAMETER;
    }
#endif

    if (Endian_IsBig()) {
        *(uint32_t *)pValue = value;
    } else {
        *(uint8_t *)pValue++ = (value >> 24) & 0xFF;
        *(uint8_t *)pValue++ = (value >> 16) & 0xFF;
        *(uint8_t *)pValue++ = (value >> 8) & 0xFF;
        *(uint8_t *)pValue++ = value & 0xFF;
    }

    // Return to caller.
    return ERESULT_SUCCESS;
}


ERESULT         Endian_PutU32Little(
    void            *pValue,        // Out
    uint32_t        value           // In
)
{

    // Do initialization.
#ifdef NDEBUG
#else
    if (NULL == pValue) {
        DEBUG_BREAK();
        return ERESULT_INVALID_PARAMETER;
    }
#endif

    if (Endian_IsLittle()) {
        *(uint32_t *)pValue = value;
    } else {
        *(uint8_t *)pValue++ = value & 0xFF;
        *(uint8_t *)pValue++ = (value >> 8) & 0xFF;
        *(uint8_t *)pValue++ = (value >> 16) & 0xFF;
        *(uint8_t *)pValue++ = (value >> 24) & 0xFF;
    }

    // Return to caller.
    return ERESULT_SUCCESS;
}



//---------------------------------------------------------------
//                       P u t U 6 4
//---------------------------------------------------------------

ERESULT         Endian_PutU64Big(
    void            *pValue,        // Out
    uint64_t        value           // In
)
{

    // Do initialization.
#ifdef NDEBUG
#else
    if (NULL == pValue) {
        DEBUG_BREAK();
        return ERESULT_INVALID_PARAMETER;
    }
#endif

    if (Endian_IsBig()) {
        *(uint64_t *)pValue = value;
    } else {
        *(uint8_t *)pValue++ = (value >> 56) & 0xFF;
        *(uint8_t *)pValue++ = (value >> 48) & 0xFF;
        *(uint8_t *)pValue++ = (value >> 40) & 0xFF;
        *(uint8_t *)pValue++ = (value >> 32) & 0xFF;
        *(uint8_t *)pValue++ = (value >> 24) & 0xFF;
        *(uint8_t *)pValue++ = (value >> 16) & 0xFF;
        *(uint8_t *)pValue++ = (value >> 8) & 0xFF;
        *(uint8_t *)pValue++ = value & 0xFF;
    }

    // Return to caller.
    return ERESULT_SUCCESS;
}


ERESULT         Endian_PutU64Little(
    void            *pValue,        // Out
    uint64_t        value           // In
)
{

    // Do initialization.
#ifdef NDEBUG
#else
    if (NULL == pValue) {
        DEBUG_BREAK();
        return ERESULT_INVALID_PARAMETER;
    }
#endif

    if (Endian_IsLittle()) {
        *(uint64_t *)pValue = value;
    } else {
        *(uint8_t *)pValue++ = value & 0xFF;
        *(uint8_t *)pValue++ = (value >> 8) & 0xFF;
        *(uint8_t *)pValue++ = (value >> 16) & 0xFF;
        *(uint8_t *)pValue++ = (value >> 24) & 0xFF;
        *(uint8_t *)pValue++ = (value >> 32) & 0xFF;
        *(uint8_t *)pValue++ = (value >> 40) & 0xFF;
        *(uint8_t *)pValue++ = (value >> 48) & 0xFF;
        *(uint8_t *)pValue++ = (value >> 56) & 0xFF;
    }

    // Return to caller.
    return ERESULT_SUCCESS;
}



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

static
void *          EndianClass_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    ENDIAN_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;
    
    if (OBJ_NIL == this) {
        return NULL;
    }
    
    switch (type) {
      
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(ENDIAN_DATA);
            break;
            
        case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
            return this;
            break;
            
        // Query for an address to specific data within the object.  
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'C':
                    if (str_Compare("ClassInfo", (char *)pStr) == 0) {
                        return (void *)&Endian_Info;
                    }
                    break;
                    
                case 'S':
                    if (str_Compare("SuperClass", (char *)pStr) == 0) {
                        return (void *)&Endian_Info.pClassSuperObject;
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
            switch (*pStr) {
                    
                case 'N':
                    if (str_Compare("New", (char *)pStr) == 0) {
                        return Endian_New;
                    }
                    break;
                    
                case 'P':
#ifdef  ENDIAN_JSON_SUPPORT
                    if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                        return Endian_ParseJsonFields;
                    }
                    if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                        return Endian_ParseJsonObject;
                    }
#endif
                    break;

                case 'T':
#ifdef  ENDIAN_JSON_SUPPORT
                    if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                        return Endian_ToJsonFields;
                    }
                    if (str_Compare("ToJson", (char *)pStr) == 0) {
                        return Endian_ToJson;
                    }
#endif
                    break;

                 case 'W':
                    if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                        return EndianClass_WhoAmI;
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
bool            Endian_IsKindOf (
    uint16_t        classID
)
{
    OBJ_DATA        *pObj;
    const
    OBJ_INFO        *pInfo;

    if (OBJ_IDENT_ENDIAN == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }

    pObj = obj_getInfo(Endian_Class())->pClassSuperObject;
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
void            Endian_Dealloc (
    OBJ_ID          objId
);


OBJ_ID          Endian_Class (
    void
)
{
    return (OBJ_ID)&Endian_ClassObj;
}


static
uint16_t        Endian_WhoAmI (
    void
)
{
    return OBJ_IDENT_ENDIAN;
}





//===========================================================
//                  Object Vtbl Definition
//===========================================================

#ifdef  ENDIAN_SINGLETON
// A Shared object ignores Retain() and Release() except for
// initialization and termination. So, there must be an
// independent VTbl from the normal which does support Retain()
// and Release().
const
ENDIAN_VTBL     Endian_VtblShared = {
    {
        &Endian_Info,
        Endian_IsKindOf,
        obj_RetainNull,
        obj_ReleaseNull,
        Endian_Dealloc,
        Endian_Class,
        Endian_WhoAmI,
        (P_OBJ_QUERYINFO)Endian_QueryInfo,
        (P_OBJ_TOSTRING)Endian_ToDebugString,
        NULL,           // Endian_Enable,
        NULL,           // Endian_Disable,
        NULL,           // (P_OBJ_ASSIGN)Endian_Assign,
        NULL,           // (P_OBJ_COMPARE)Endian_Compare,
        NULL,           // (P_OBJ_PTR)Endian_Copy,
        NULL,           // (P_OBJ_PTR)Endian_DeepCopy,
        NULL            // (P_OBJ_HASH)Endian_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Endian_IsEnabled,
 
};
#endif


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
const
ENDIAN_VTBL     Endian_Vtbl = {
    {
        &Endian_Info,
        Endian_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        Endian_Dealloc,
        Endian_Class,
        Endian_WhoAmI,
        (P_OBJ_QUERYINFO)Endian_QueryInfo,
        (P_OBJ_TOSTRING)Endian_ToDebugString,
        NULL,           // Endian_Enable,
        NULL,           // Endian_Disable,
        NULL,           // (P_OBJ_ASSIGN)Endian_Assign,
        NULL,           // (P_OBJ_COMPARE)Endian_Compare,
        NULL,           // (P_OBJ_PTR)Endian_Copy,
        NULL,           // (P_OBJ_PTR)Endian_DeepCopy,
        NULL            // (P_OBJ_HASH)Endian_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //Endian_IsEnabled,
 
};



static
const
OBJ_INFO        Endian_Info = {
    "Endian",
    "Endianess Support (Big/Little)",
    (OBJ_DATA *)&Endian_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&Endian_Vtbl,
    sizeof(ENDIAN_DATA)
};





