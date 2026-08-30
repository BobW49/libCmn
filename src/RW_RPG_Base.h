// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//   Report Program Generator (RPG) Base (RW_RPG_Base) Header
//****************************************************************

/*
 * Program
 *          Report Program Generator (RPG) Base (RW_RPG_Base)
 * Purpose
    This object supports generating an IBM System 3/Burroughs 1700 like RPG II 
    program. We have slightly altered the algorithm to conform to RPG IV. When
    a 'step' is noted in the comments, it is from the RPG IV flowchart. See
    ILE RPG Reference. SuperGrok helped with some of the logic. 

    Each level is self-contained in self.levels. The 'index' field indicates
    if the level is active or not. Level 1, L1, is the highest level; Level
    2, L2, is the second highest; ... If level breaks are used, you must start
    at the highest and go down in priority. Otherwise, the algorithm will not
    work properly. Any level indicator which is 0 or None means that a no
    operation is use for that phase whatever that field controlled.

    The main run-time has look-ahead for the input record. The current record
    is in self.record and the next record is in self.next_record. If the next
    record is None, the end-of-file has occurred (ie LR).

    NOTES:
        *   This does NOT support multiple input files nor MR.
        *   This does NOT support Halt Indicators, Hn.
        *   This does NOT support Overflow and associated indicators.
        *   This does NOT support RT indicator.
        *   This does NOT support Execute Support.
        *   You must supply all file output including printing.

 *
 * Remarks
 *  1.      Currently, this object only supports single file input and the 
 *          print side of RPG. It does not support:
 *          *   Multiple Input Files nor MR
 *          *   Halt Indicators, Hn
 *          *   Overflow and associated indicators
 *          *   RT Indicator
 *          *   Execute Support
 *
 * History
 *  05/31/2026 Generated
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
        OBJ_IDENT_RW_RPG_BASE,             // Report Program Generator (RPG) Base
        OBJ_IDENT_RW_RPG_BASE_CLASS,
    The following should be added to the appropriate objects.json.txt
    or program.json.txt file:
        {name:"RW_RPG_Base",  desc:"Report Program Generator (RPG) Base"},
 *----------------------------------------------------------------*/



//#define   RW_RPG_BASE_IS_IMMUTABLE        1
//#define   RW_RPG_BASE_JSON_SUPPORT        1
//#define   RW_RPG_BASE_SINGLETON           1
//#define   RW_RPG_BASE_MSGS                1
//#define   RW_RPG_BASE_SUPER_DEFINED       1


#include        <cmn_defs.h>
#include        <AStr.h>
#ifdef  RW_RPG_BASE_SUPER_DEFINED
#include        <obj.h>
#endif
#include        <prt.h>
#include        <ValueArray.h>


#ifndef         RW_RPG_BASE_H
#define         RW_RPG_BASE_H





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct RW_RPG_Base_data_s  RW_RPG_BASE_DATA;          // Inherits from obj
    typedef struct RW_RPG_Base_class_data_s RW_RPG_BASE_CLASS_DATA;  // Inherits from obj

    typedef struct RW_RPG_Base_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        //obj_VTBL    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in RW_RPG_Base_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(RW_RPG_BASE_DATA *);
    } RW_RPG_BASE_VTBL;

    typedef struct RW_RPG_Base_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in RW_RPG_Base_object.c.
        // Properties:
        // Methods:
        RW_RPG_BASE_DATA *(*pNew)(void);
        //bool        (*pIsEnabled)(RW_RPG_BASE_DATA *);
    } RW_RPG_BASE_CLASS_VTBL;



    /*!                 Record Interface
     This object is supplied externally and defines the data
     interface for each "record" of information. Primarily,
     this interface provides reading and writing of each "record"
     as well as access to the individual fields within the "record"
     by name. A "record" is defined as a grouping of related fields
     where a field represents one piece of data.
     */

    typedef struct RW_RPG_BASE_record_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in RpgBase_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(RPGBASE_DATA *);
        void *          (*pDataGet)(
                                    OBJ_ID      this,
                                    const
                                    char        *pName
                        );
        ERESULT         (*pDataUpdate)(
                                    OBJ_ID      this,
                                    const
                                    char        *pName,
                                    void        *pData
                        );
        ERESULT         (*pAdd)(
                                    OBJ_ID      this, 
                                    void *
                        );
        ERESULT         (*pDelete)(
                                    OBJ_ID      this
                        );
        ERESULT         (*pUpdate)(
                                    OBJ_ID      this, 
                                    void *
                        );
    } RW_RPG_BASE_RECORD_VTBL;

    /*!             Level Interface
     This object is supplied externally and defines the execution
     interface exit points that will be called at the appropriate
     times in the RPG cycle.

     It is based on levels, 1 being the highest. Each level should
     be thought of as a unit and is conditioned on a particular
     field of data.

     Dtl entries are executed with eacch new record. Sum entries
     are for grand totals. Note that Dtl and Sum entries are not
     included in all the groupings.
     */

    /*!     Definitions from RpgLvl.h
     */
    typedef struct RW_RPG_LEVEL_vtbl_s  RW_RPG_LEVEL_DATA;      // Inherits from OBJ

    typedef struct RW_RPG_LEVEL_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in RpgLvl_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(RPGLVL_DATA *);
        // Break() methods are called when a break for that level occurs
        // or a higher level.
        bool        (*pBreak)(
                        OBJ_ID          this, 
                        RW_RPG_BASE_DATA    
                                        *pBase
                    );
        // Calc() methods performs the calculations for
        // this level that are ?????
        bool        (*pCalc)(
                        OBJ_ID          this, 
                        RW_RPG_BASE_DATA    
                                        *pBase
                    );
        // Check() methods check to see if their level break has
        // occurred and return true if so.  They are not responsible
        // for saving the level data since that occurs later in the
        // RPG cycle.
        bool        (*pCheck)(
                        OBJ_ID          this, 
                        RW_RPG_BASE_DATA    
                                        *pBase,
                        void            *pRecord
                    );
        // Data() methods stores the data from the current
        // input record for use in checking future level breaks.
        bool        (*pData)(
                        OBJ_ID          this, 
                        RW_RPG_BASE_DATA    
                                        *pBase,
                        void            *pRecord
                    );
        // Out() methods performs the output for the particular level.
        bool        (*pOut)(
                        OBJ_ID          this, 
                        RW_RPG_BASE_DATA    
                                        *pBase
                    );
        // Zero() methods establishes or zeroes the accumulation data
        // which is used at the given level.
        bool        (*pZero)(
                        OBJ_ID          this, 
                        RW_RPG_BASE_DATA    
                                        *pBase
                    );
    } RW_RPG_LEVEL_VTBL;

    
    typedef enum RpgBase_Levels_e {
        RW_RPG_BASE_LEVEL_1=1,              // Most important level
        RW_RPG_BASE_LEVEL_2,
        RW_RPG_BASE_LEVEL_3,
        RW_RPG_BASE_LEVEL_4,
        RW_RPG_BASE_LEVEL_5,
        RW_RPG_BASE_LEVEL_6,
        RW_RPG_BASE_LEVEL_7,
        RW_RPG_BASE_LEVEL_8,
        RW_RPG_BASE_LEVEL_9,                 // Least importand level
        RW_RPG_BASE_LEVEL_DETAIL,            // Required
        RW_RPG_BASE_LEVEL_SUM                // Required
    } RW_RPG_BASE_LEVELS;





    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  RW_RPG_BASE_SINGLETON
    RW_RPG_BASE_DATA * 
                    RW_RPG_Base_Shared (
        void
    );

    void            RW_RPG_Base_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to RW_RPG_Base object if successful, otherwise OBJ_NIL.
     */
    RW_RPG_BASE_DATA * 
                    RW_RPG_Base_Alloc (
        void
    );
    
    
    OBJ_ID          RW_RPG_Base_Class (
        void
    );
    
    
    RW_RPG_BASE_DATA * 
                    RW_RPG_Base_New (
        void
    );
    
    
#ifdef  RW_RPG_BASE_JSON_SUPPORT
    RW_RPG_BASE_DATA * 
                    RW_RPG_Base_NewFromJsonString (
        ASTR_DATA       *pString
    );

    RW_RPG_BASE_DATA * 
                    RW_RPG_Base_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

#ifdef RW_RPG_BASE_MSGS
    /*! @property   Messages
        Allows information and warning messages to be issued.
     */
    bool            RW_RPG_Base_setMsgs (
        RW_RPG_BASE_DATA 
                        *this,
        void            (*pMsgInfo)(OBJ_ID, const char *, ...),
        void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...),
        OBJ_ID          pObj
    );
#endif


    /*! @property   Record
        is the current record in the cycle.
     */
    VALUEARRAY_DATA * 
                    RW_RPG_Base_getRecord (
        RW_RPG_BASE_DATA 
                        *this
    );

    bool            RW_RPG_Base_setRecord (
        RW_RPG_BASE_DATA 
                        *this,
        VALUEARRAY_DATA *pValue
    );

    
#ifdef  RW_RPG_BASE_SUPER_DEFINED
    OBJ_DATA *      RW_RPG_Base_getSuper (
        RW_RPG_BASE_DATA 
                        *this
    );
#else
    OBJ_DATA *      RW_RPG_Base_getSuper (
        RW_RPG_BASE_DATA 
                        *this
    );
#endif


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         RW_RPG_Base_Disable (
        RW_RPG_BASE_DATA 
                        *this
    );


    ERESULT         RW_RPG_Base_Enable (
        RW_RPG_BASE_DATA 
                        *this
    );

   
    RW_RPG_BASE_DATA * 
                    RW_RPG_Base_Init (
        RW_RPG_BASE_DATA 
                        *this
    );


    bool            RW_RPG_Base_IsEnabled (
        RW_RPG_BASE_DATA 
                        *this
    );
    
 
#ifdef  RW_RPG_BASE_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = RW_RPG_Base_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     RW_RPG_Base_ToJson (
        RW_RPG_BASE_DATA 
                        *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = RW_RPG_Base_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     RW_RPG_Base_ToDebugString (
        RW_RPG_BASE_DATA 
                        *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* RW_RPG_BASE_H */

