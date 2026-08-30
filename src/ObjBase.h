// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//              Base for All Objects (ObjBase) Header
//****************************************************************

/*
 * Program
 *          Base for All Objects (ObjBase)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate ObjBase to run things without complications
 *          of interfering with the main ObjBase. A ObjBase may be 
 *          called a ObjBase on other O/S's.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  02/24/2025 Generated
 */


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


/*----------------------------------------------------------------
    The following should be added to the appropriate _defs.h file
    in the _idents_e enum:
        OBJ_IDENT_OBJBASE,             // Base for All Objects
        OBJ_IDENT_OBJBASE_CLASS,
    The following should be added to the appropriate objects.json.txt
    or program.json.txt file:
        {name:"ObjBase",  desc:"Base for All Objects"},
 *----------------------------------------------------------------*/



//#define   %{NAMEU}_IS_IMMUTABLE     1
//#define   %{NAMEU}_JSON_SUPPORT     1
//#define   %{NAMEU}_SINGLETON        1
//#define       OBJBASE_MSGS   1
//#define   %{NAMEU}_SUPER_DEFINED     1


#define OBJBASE_NEEDED 1
#include        <cmn_defs.h>
#include        <AStr.h>


#ifndef         OBJBASE_H
#define         OBJBASE_H





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************

#ifndef ERESULT_DEFN
    typedef int32_t ERESULT;
#define ERESULT_DEFN 1
#endif
    
typedef void *  OBJ_PTR;
typedef void *  OBJ_ID;
#define             OBJ_NIL ((OBJ_ID)0)
typedef struct obj_iunknown_s  OBJ_IUNKNOWN;
typedef struct obj_info_s  OBJ_INFO;
typedef struct obj_prop_s  OBJ_PROP;            // Property
typedef void (*DEALLOC_METHOD)(void *);

typedef struct obj_data_s   OBJ_DATA;   /* One Interface */

typedef ERESULT     (*P_OBJ_ASSIGN)(OBJ_ID, OBJ_ID);
typedef int         (*P_OBJ_COMPARE)(OBJ_ID, OBJ_ID);
// @return    0 if this == other
//           <0 if this < other
//           >0 if this > other
typedef ERESULT     (*P_OBJ_EXEC)(OBJ_ID);
typedef OBJ_ID      (*P_OBJ_COPY)(OBJ_ID);
typedef OBJ_ID      (*P_OBJ_DEEPCOPY)(OBJ_ID);
typedef bool        (*P_OBJ_DISABLE)(OBJ_ID);
typedef bool        (*P_OBJ_ENABLE)(OBJ_ID);
typedef uint32_t    (*P_OBJ_HASH)(OBJ_ID);
typedef OBJ_ID      (*P_OBJ_PTR)(OBJ_ID);
typedef OBJ_ID      (*P_OBJ_TOSTRING)(OBJ_ID, int);
typedef void *      (*P_OBJ_QUERYINFO)(OBJ_ID, uint32_t, void *);


#if !defined(__arm64__) && !defined(__x86_64__)
#pragma pack(push, 2)
#endif

/*
    Notes:
    1.  This structure must ALWAYS be first in the object's data structure.
    2.  Inheritance uses on one struct ObjBase_data_s which must be located
        in the highest Super of the inheritance stack only. However, a
        pSuperVtbl should always follow it in the object's data struture
        (ie It should be immediately following the Super's definition.
 */

    struct ObjBase_data_s {
        const
        OBJ_IUNKNOWN    *pVtbl;
        uint16_t        cbSize;         /* Total Control Block Size */
        uint16_t        cbFlags;        /* Control Flags */
        uint32_t        cbRetainCount;
#ifndef XYZZY
        union {
            uint32_t        cbMisc;
            struct {
                uint16_t        cbMisc1;
                uint16_t        cbMisc2;
            };
        };
#else
        uint32_t        cbMisc;
        uint16_t        cbMisc1;
        uint16_t        cbMisc2;
#endif
    };
/*
 WARNING: For inheritance to work properly pSuperVtbl must be outside of
        the above structure. It should immediately follow that structure.
 */
//OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance
#if !defined(__arm64__) && !defined(__x86_64__)
#pragma pack(pop)
#endif


#if defined(__arm64__) || defined(__86_64__)
#define OBJBASE_DATA_GEN(vtbl_name, size_name, flags, retain_count) \
        {                                                           \
            (const OBJ_IUNKNOWN *)&vtbl_name,                       \
            sizeof(size_name),                                      \
            flags,                                                  \
            retain_count,                                           \
            {0}                                                     \
        }
#else
#define OBJBASE_DATA_GEN(vtbl_name, size_name, flags, retain_count) \
        {                                                           \
            (const OBJ_IUNKNOWN *)&vtbl_name,                       \
            sizeof(size_name),                                      \
            flags,                                                  \
            retain_count,                                           \
            {0}
        }
#endif


    /*  Object Information Structure
    The first address of the Object's VTbl will point
    to this structure and it forms a chain upwards in
    the Inheritance List. This is true in both the
     object's data and the object's class data.
    */
#if !defined(__arm64__) && !defined(__x86_64__)
#pragma pack(push, 1)
#endif
    struct obj_info_s {
        const
        char            *pClassName;
        const
        char            *pClassDesc;        // Class Description
        OBJ_DATA        *pClassObject;      // This object's Class Object
        OBJ_DATA        *pClassSuperObject; // Super's class definition
        OBJ_IUNKNOWN    *pDefaultVtbls;     // Default Object VTBL
        uint32_t        defaultObjectSize;  // Default Object Size for objects
        //                                  // created (non-class)
    };
#if !defined(__arm64__) && !defined(__x86_64__)
#pragma pack(pop)
#endif

    
    // Object Property Definition
#if !defined(__arm64__) && !defined(__x86_64__)
#pragma pack(push, 1)
#endif
    struct obj_prop_s {
        const
        char            *pName;             // Name
        const
        char            *pInternal;         // Internal Name (if object, use p${titled.pName})
        const
        char            *pExternal;         // External Name (used for JSON/HJSON, etc)
        const
        char            *pDesc;             // Description
        const
        char            *pType;             // Type (if object, use ${object.upper}_DATA)
        const
        char            *pInit;             // Initialization Code
        const
        char            *pVis;              // Visibility - public,private,read-only,ro,none
        const
        char            *pBase;             // Base Structure/Pointer
        uint32_t        offset;             // Offset into Base
        // If property is part of a combined field, we can generate a mask and shift
        // amount to add, extract or delete the property from the combined field.
        uint32_t        sizeInBits;         // Size of property in bits if integer
        uint32_t        shiftAmt;           // Amount to shift right to put in lowest bits
        uint8_t         fObject;            // true == object
        uint8_t         filler8[3];
    };
#if !defined(__arm64__) && !defined(__x86_64__)
#pragma pack(pop)
#endif


    /*      Minimal VTbl Definition
     The VTbl contains access to the information structure as
     defined above, struct obj_info_s, as well as the base
     routines that should be supplied if possible. The routines
     are optional and should be NULL if not present. The VTbl
     supplies the same functioonalisty as Virtual methods in
     C++ and are used mostly when Interface support is provided.
     All objects and class objects must have a VTbl.
     */
    struct obj_iunknown_s {
        const
        OBJ_INFO    *pInfo;                 // (Optional for Now)
        bool        (*pIsKindOf)(uint16_t);
        OBJ_ID      (*pRetain)(OBJ_ID);
        OBJ_ID      (*pRelease)(OBJ_ID);
        void        (*pDealloc)(OBJ_ID);
        // Return the Class Object for this object. If the object is already
        // a Class Object, then it simply returns itself. The Info address
        // then allows you to find Super objects if needed.
        OBJ_ID      (*pClassObject)(void);
        uint16_t    (*pWhoAmI)(void);
        // Everything before this is required and does not need to be
        // tested to see if it exists.  Everything after this must be
        // tested to see if it exists, because it may not be implemented
        // (ie NULL).
        // ------- Beginning of Methods likely to be in all objects -------
        // Query an object for specific data including object size,
        // method name(s) in character format, etc.  See obj_QueryInfoType_e
        // for more information.
        void *      (*pQueryInfo)(OBJ_ID, uint32_t, void *);
        OBJ_ID      (*pToDebugString)(OBJ_ID, int);
        // ------- End of Methods likely to be in all objects -------
        bool        (*pEnable)(OBJ_ID);
        bool        (*pDisable)(OBJ_ID);
        // Assigns data within 1st object to 2nd object.
        ERESULT     (*pAssign)(OBJ_ID, OBJ_ID);  // P_OBJ_ASSIGN
        // Compares 1st object to 2nd object.
        // Returns:
        //          ERESULT_SUCCESS_LESS_THAN        1st <  2nd
        //          ERESULT_SUCCESS_EQUAL            1st == 2nd
        //          ERESULT_SUCCESS_GREATER_THAN     1st >  2nd
        int         (*pCompare)(OBJ_ID, OBJ_ID); // P_OBJ_COMPARE
        // Creates a new copy of the object. If the object is
        // immmutable (ie can not be changed) then it just returns
        // a retained self. Objects within this object will simply
        // be retained.
        OBJ_ID      (*pCopy)(OBJ_ID);           // P_OBJ_COPY
        // Creates a new copy of the object. If the object is
        // immmutable (ie can not be changed) then it just returns
        // a retained self. Objects within this object will be
        // recreated in a new object unless they are read-only.
        OBJ_ID      (*pDeepCopy)(OBJ_ID);       // P_OBJ_DEEPCOPY
        // Creates hash of this object.
        uint32_t    (*pHash)(OBJ_ID);           // P_OBJ_HASH
    };


    /* Object QueryInfo Types
     Used as the first parameter of an object's
     QueryInfo() method.
     */
    typedef enum obj_QueryInfoType_e {
        OBJ_QUERYINFO_TYPE_UNKNOWN=0,
        OBJ_QUERYINFO_TYPE_OBJECT_SIZE,     // Return size of object
        OBJ_QUERYINFO_TYPE_CLASS_OBJECT,    // Return class object
        OBJ_QUERYINFO_TYPE_DATA,            // If the given string matches a data name and
        //                                  // the data will fit within "void *",
        //                                  // return the data
        OBJ_QUERYINFO_TYPE_DATA_PTR,        // If the given string matches a data name,
        //                                  // return a pointer to the data
        OBJ_QUERYINFO_TYPE_INFO,            // Return class info structure
        OBJ_QUERYINFO_TYPE_METHOD,          // Search for a Method by using the string
        //                                  // which is the method name without object prefix
        OBJ_QUERYINFO_TYPE_PTR,             // Search for a Method by using its address and
        //                                  // returning a string which represents the method
    } OBJ_QUERYINFO_TYPE;


/* Object QueryInfo Types
 Used as the first parameter of an object's
 QueryInfo() method.
 */
typedef enum obj_Flags_e {
        OBJ_FLAG_ALLOC=0,           /* Object was allocated in obj_Alloc(). */
        OBJ_FLAG_INIT,              /* Object is initialized. */
        OBJ_FLAG_ENABLED,           /* Object is enabled. */
        OBJ_FLAG_TEST,              /* Object testing */
        OBJ_FLAG_TRACE,             /* Object tracing */
        OBJ_FLAG_RO,                /* Object is Read-Only (ie immutable). */
        OBJ_FLAG_COM,               /* Object is COM compatible. */
        OBJ_FLAG_RSVD1,
        OBJ_FLAG_USER1,             /* First User Useable flag */
        OBJ_FLAG_USER2,
        OBJ_FLAG_USER3,
        OBJ_FLAG_USER4,
        OBJ_FLAG_USER5,
        OBJ_FLAG_USER6,
        OBJ_FLAG_USER7,
        OBJ_FLAG_USER8              /* Last User Useable flag */
} OBJ_FLAGS;



#define OBJ_INIT_SHARED(this, cbSize)\
if (!(obj_getFlags(this) & OBJ_FLAG_INIT)) {        \
    memset(this, 0, cbSize);                        \
    obj_setVtbl(this, obj_StaticVtblShared());      \
    obj_setSize(this, cbSize);                      \
    obj_setRetainCount(this, -1);                   \
    obj_setFlags(this, OBJ_FLAG_INIT);              \
}


    typedef struct ObjBase_data_s  OBJBASE_DATA;
    typedef struct ObjBase_data_s  OBJ_DATA;
    typedef struct ObjBase_class_data_s OBJBASE_CLASS_DATA;

    typedef struct ObjBase_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        //obj_VTBL    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in ObjBase_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(OBJBASE_DATA *);
    } OBJBASE_VTBL;

    typedef struct ObjBase_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in ObjBase_object.c.
        // Properties:
        // Methods:
        OBJBASE_DATA *(*pNew)(void);
        //bool        (*pIsEnabled)(OBJBASE_DATA *);
    } OBJBASE_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  OBJBASE_SINGLETON
    OBJBASE_DATA *  ObjBase_Shared (
        void
    );

    void            ObjBase_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to ObjBase object if successful, otherwise OBJ_NIL.
     */
    OBJBASE_DATA *  ObjBase_Alloc (
        void
    );
    
    
    OBJ_ID          ObjBase_Class (
        void
    );
    
    
    OBJBASE_DATA *  ObjBase_New (
        void
    );
    
    
#ifdef  OBJBASE_JSON_SUPPORT
    OBJBASE_DATA *  ObjBase_NewFromJsonString (
        ASTR_DATA       *pString
    );

    OBJBASE_DATA *  ObjBase_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    // @property Flag
    // The flag_number is defined by OBJ_FLAGS above.

    bool            ObjBase_getFlag (
        OBJBASE_DATA    *this,
        uint16_t        flag_number
    );

    bool            ObjBase_setFlag (
        OBJBASE_DATA    *this,
        uint16_t        flag_number,
        bool            fValue
    );


    /*!
     @property Info - Object Information as defined in struct obj_info_s
                        above and is gotten from the Vtbl
     */
    const
    OBJ_INFO *      ObjBase_getInfo (
        OBJBASE_DATA    *this
    );


    /*!
     @property Size - defines the size of the Object's Data Area. This should
                        be the largest size of all inherited object data areas.
     */
    uint32_t        ObjBase_getSize (
        OBJBASE_DATA    *this
    );

    bool            ObjBase_setSize (
        OBJBASE_DATA    *this,
        uint16_t        value
    );


    OBJBASE_DATA *  ObjBase_getSuper (
        OBJBASE_DATA    *this
    );

    /*!
     @property Type - Object Type as defined in OBJ_IDENTS
                        found in cmn_defs.h
     */
    uint16_t        ObjBase_getType (
        OBJBASE_DATA    *this
    );



    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         ObjBase_Disable (
        OBJBASE_DATA    *this
    );


    ERESULT         ObjBase_Enable (
        OBJBASE_DATA    *this
    );

   
    OBJBASE_DATA *  ObjBase_Init (
        OBJBASE_DATA    *this
    );


    bool            ObjBase_IsEnabled (
        OBJBASE_DATA    *this
    );
    
 
    bool            ObjBase_IsKindOf (
        OBJ_ID          objId,
        uint16_t        type
    );


#ifdef  OBJBASE_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = ObjBase_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     ObjBase_ToJson (
        OBJBASE_DATA    *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = ObjBase_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     ObjBase_ToDebugString (
        OBJBASE_DATA    *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* OBJBASE_H */

