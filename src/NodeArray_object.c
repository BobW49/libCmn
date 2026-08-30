// vi: nu:noai:ts=4:sw=4

//****************************************************************
//              An Array of Nodes (NodeArray) Object Support
//****************************************************************

//  Class Object Metods and Tables for 'NodeArray'
//  Generated 06/21/2026 10:23:02


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




#define         NODEARRAY_OBJECT_C       1
#include        <NodeArray_internal.h>
#ifdef  NODEARRAY_SINGLETON
#include        <psxLock.h>
#endif


#ifdef  __cplusplus
extern "C" {
#endif
        
        

    //===========================================================
    //                  Class Object Definition
    //===========================================================

    struct NodeArray_class_data_s    {
        // Warning - OBJ_DATA must be first in this object!
        OBJ_DATA        super;
        
        // Common Data
    #ifdef  NODEARRAY_SINGLETON
        volatile
        NODEARRAY_DATA  *pSingleton;
    #endif
        //uint32_t       misc;
        //OBJ_ID         pObjCatalog;
    };




    //-----------------------------------------------------------
    //                  Class Methods
    //-----------------------------------------------------------



    static
    void *          NodeArrayClass_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    static
    const
    OBJ_INFO            NodeArray_Info;            // Forward Reference




    static
    bool            NodeArrayClass_IsKindOf (
        uint16_t        classID
    )
    {
        OBJ_DATA        *pObj;
        
        if (OBJ_IDENT_NODEARRAY_CLASS == classID) {
           return true;
        }
        if (OBJ_IDENT_OBJ_CLASS == classID) {
           return true;
        }
        
        pObj = obj_getInfo(NodeArray_Class())->pClassSuperObject;
        if (pObj == obj_BaseClass())
            ;
        else {
            return obj_getVtbl(pObj)->pIsKindOf(classID);
        }
        
        return false;
    }


    static
    uint16_t        NodeArrayClass_WhoAmI (
        void
    )
    {
        return OBJ_IDENT_NODEARRAY_CLASS;
    }




    //===========================================================
    //                 Class Object Vtbl Definition
    //===========================================================

    static
    const
    NODEARRAY_CLASS_VTBL 
                        class_Vtbl = {
        {
            &NodeArray_Info,
            NodeArrayClass_IsKindOf,
            obj_RetainNull,
            obj_ReleaseNull,
            NULL,
            NodeArray_Class,
            NodeArrayClass_WhoAmI,
            (P_OBJ_QUERYINFO)NodeArrayClass_QueryInfo,
            NULL                        // NodeArrayClass_ToDebugString
        },
        (void *)NodeArray_New
    };



    //-----------------------------------------------------------
    //                      Class Object
    //-----------------------------------------------------------

    NODEARRAY_CLASS_DATA 
                        NodeArray_ClassObj = {
        {
            (const OBJ_IUNKNOWN *)&class_Vtbl,      // pVtbl
            sizeof(NODEARRAY_CLASS_DATA),           // cbSize
            0,                                      // cbFlags
            1,                                      // cbRetainCount
            {0}                                     // cbMisc
        },
        //0
    };



    //---------------------------------------------------------------
    //          S i n g l e t o n  M e t h o d s
    //---------------------------------------------------------------

    #ifdef  NODEARRAY_SINGLETON
    extern
    const
    NODEARRAY_VTBL      NodeArray_VtblShared;


    NODEARRAY_DATA * 
                    NodeArray_getSingleton (
        void
    )
    {
        return (OBJ_ID)(NodeArray_ClassObj.pSingleton);
    }


    bool            NodeArray_setSingleton (
        NODEARRAY_DATA  *pValue
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
        if (NodeArray_ClassObj.pSingleton) {
            obj_Release((OBJ_ID)(NodeArray_ClassObj.pSingleton));
        }
        NodeArray_ClassObj.pSingleton = pValue;
        
        fRc = psxLock_Unlock(pLock);
        obj_Release(pLock);
        pLock = OBJ_NIL;
        return true;
    }



    NODEARRAY_DATA * 
                    NodeArray_Shared (
        void
    )
    {
        NODEARRAY_DATA  *this = (OBJ_ID)(NodeArray_ClassObj.pSingleton);
        
        if (NULL == this) {
            this = NodeArray_New( );
            obj_setVtbl(this, (void *)&NodeArray_VtblShared);
            NodeArray_setSingleton(this);
            obj_Release(this);          // Shared controls object retention now.
            // NodeArray_ClassObj.pSingleton = OBJ_NIL;
        }
        
        return this;
    }



    void            NodeArray_SharedReset (
        void
    )
    {
        NODEARRAY_DATA  *this = (OBJ_ID)(NodeArray_ClassObj.pSingleton);
        
        if (this) {
            obj_setVtbl(this, (void *)&NodeArray_Vtbl);
            obj_Release(this);
            NodeArray_ClassObj.pSingleton = OBJ_NIL;
        }
        
    }



    #endif



    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------

    static
    void *          NodeArrayClass_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        NODEARRAY_CLASS_DATA 
                        *this = objId;
        const
        char            *pStrA = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
        
        switch (type) {
          
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(NODEARRAY_DATA);
                break;
                
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return this;
                break;
                
            // Query for an address to specific data within the object.  
            case OBJ_QUERYINFO_TYPE_DATA_PTR:
                switch (*pStrA) {
     
                    case 'C':
                        if (str_Compare("ClassInfo", (char *)pStrA) == 0) {
                            return (void *)&NodeArray_Info;
                        }
                        break;
                        
                    case 'S':
                        if (str_Compare("SuperClass", (char *)pStrA) == 0) {
                            return (void *)&NodeArray_Info.pClassSuperObject;
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
                            return NodeArray_New;
                        }
                        break;
                        
                    case 'P':
    #ifdef  NODEARRAY_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStrA) == 0) {
                            return NodeArray_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStrA) == 0) {
                            return NodeArray_ParseJsonObject;
                        }
    #endif
                        break;

                    case 'T':
    #ifdef  NODEARRAY_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStrA) == 0) {
                            return NodeArray_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStrA) == 0) {
                            return NodeArray_ToJson;
                        }
    #endif
                        break;

                     case 'W':
                        if (str_Compare("WhoAmI", (char *)pStrA) == 0) {
                            return NodeArrayClass_WhoAmI;
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
    bool            NodeArray_IsKindOf (
        uint16_t        classID
    )
    {
        OBJ_DATA        *pObj;
        const
        OBJ_INFO        *pInfo;

        if (OBJ_IDENT_NODEARRAY == classID) {
           return true;
        }
        if (OBJ_IDENT_OBJ == classID) {
           return true;
        }

        pObj = obj_getInfo(NodeArray_Class())->pClassSuperObject;
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
    void            NodeArray_Dealloc (
        OBJ_ID          objId
    );


    OBJ_ID          NodeArray_Class (
        void
    )
    {
        return (OBJ_ID)&NodeArray_ClassObj;
    }


    static
    uint16_t        NodeArray_WhoAmI (
        void
    )
    {
        return OBJ_IDENT_NODEARRAY;
    }





    //===========================================================
    //                  Object Vtbl Definition
    //===========================================================

    #ifdef  NODEARRAY_SINGLETON
    // A Shared object ignores Retain() and Release() except for
    // initialization and termination. So, there must be an
    // independent VTbl from the normal which does support Retain()
    // and Release().
    const
    NODEARRAY_VTBL      NodeArray_VtblShared = {
        {
            &NodeArray_Info,
            NodeArray_IsKindOf,
            obj_RetainNull,
            obj_ReleaseNull,
            NodeArray_Dealloc,
            NodeArray_Class,
            NodeArray_WhoAmI,
            (P_OBJ_QUERYINFO)NodeArray_QueryInfo,
            (P_OBJ_TOSTRING)NodeArray_ToDebugString,
            NULL,           // NodeArray_Enable,
            NULL,           // NodeArray_Disable,
            NULL,           // (P_OBJ_ASSIGN)NodeArray_Assign,
            NULL,           // (P_OBJ_COMPARE)NodeArray_Compare,
            NULL,           // (P_OBJ_PTR)NodeArray_Copy,
            NULL,           // (P_OBJ_PTR)NodeArray_DeepCopy,
            NULL            // (P_OBJ_HASH)NodeArray_Hash,
        },
        // Put other object method names below this.
        // Properties:
        // Methods:
        //NodeArray_IsEnabled,
     
    };
    #endif


    // This VTbl supports Retain() and Release() which is
    // used by objects other than the Shared object. These
    // objects can still be shared among other objects. It
    // just that they are deleted when their usage count
    // goes to zero.
    const
    NODEARRAY_VTBL      NodeArray_Vtbl = {
        {
            &NodeArray_Info,
            NodeArray_IsKindOf,
            obj_RetainStandard,
            obj_ReleaseStandard,
            NodeArray_Dealloc,
            NodeArray_Class,
            NodeArray_WhoAmI,
            (P_OBJ_QUERYINFO)NodeArray_QueryInfo,
            (P_OBJ_TOSTRING)NodeArray_ToDebugString,
            NULL,           // NodeArray_Enable,
            NULL,           // NodeArray_Disable,
            NULL,           // (P_OBJ_ASSIGN)NodeArray_Assign,
            NULL,           // (P_OBJ_COMPARE)NodeArray_Compare,
            NULL,           // (P_OBJ_PTR)NodeArray_Copy,
            NULL,           // (P_OBJ_PTR)NodeArray_DeepCopy,
            NULL            // (P_OBJ_HASH)NodeArray_Hash,
        },
        // Put other object method names below this.
        // Properties:
        // Methods:
        //NodeArray_IsEnabled,
     
    };



    static
    const
    OBJ_INFO            NodeArray_Info = {
        "NodeArray",
        "An Array of Nodes",
        (OBJ_DATA *)&NodeArray_ClassObj,
    #ifdef  NODEARRAY_SUPER_DEFINED
        (OBJ_DATA *)&Node_ClassObj,
    #else
        (OBJ_DATA *)&obj_ClassObj,
    #endif
        (OBJ_IUNKNOWN *)&NodeArray_Vtbl,
        sizeof(NODEARRAY_DATA)
    };



#ifdef  __cplusplus
}
#endif


