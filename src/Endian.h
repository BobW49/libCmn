// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Endianess Support (Big/Little) (Endian) Header
//****************************************************************
/*
 * Program
 *          Endianess Support (Big/Little) (Endian)
 * Purpose
 *          This object provides methods to transform numbers from
 *          big endian format to little endian format and vice versa.
 *          See https://en.wikipedia.org/wiki/Endianness for a good
 *          description of endianness.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  10/25/2016 Generated
 *  09/19/2021 Regenerated with new naming
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





#include        <cmn_defs.h>
#include        <AStr.h>


#ifndef         ENDIAN_H
#define         ENDIAN_H

#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
#elif defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
#else
    #error  Unsupported Environemt!
#endif

//#define   ENDIAN_IS_IMMUTABLE     1
//#define   ENDIAN_JSON_SUPPORT     1
//#define   ENDIAN_SINGLETON        1



#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct Endian_data_s  ENDIAN_DATA;            // Inherits from OBJ
    typedef struct Endian_class_data_s ENDIAN_CLASS_DATA;   // Inherits from OBJ

    typedef struct Endian_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Endian_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(ENDIAN_DATA *);
    } ENDIAN_VTBL;

    typedef struct Endian_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Endian_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(ENDIAN_DATA *);
    } ENDIAN_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    OBJ_ID          Endian_Class (
        void
    );
    
    
    /*!
     Convert a Big Endian uint16_t into the appropriate uint16_t for
     this machine.
     @return    the adjusted number
     */
    uint16_t        Endian_GetU16Big (
        void            *pValue
    );

    /*!
     Convert a Little Endian uint16_t into the appropriate uint16_t for
     this machine.
     @return    the adjusted number
     */
    uint16_t        Endian_GetU16Little (
        void            *pValue
    );


    uint32_t        Endian_GetU24Big (
        void            *pValue
    );

    uint32_t        Endian_GetU24Little (
        void            *pValue
    );


    uint32_t        Endian_GetU32Big (
        void            *pValue
    );

    uint32_t        Endian_GetU32Little (
        void            *pValue
    );


    uint64_t        Endian_GetU64Big (
        void            *pValue
    );

    uint64_t        Endian_GetU64Little (
        void            *pValue
    );


    /*!
     Check if the current machine to see if it is Big Endian.
     @return    If the current environment is Big Endian, return true.
                Otherwise, return false.
     */
    bool            Endian_IsBig (
        void
    );

    /*!
     Check if the current environment is Little Endian.
     @return    If the current environment is Little Endian, return true.
                Otherwise, return false.
     */
    bool            Endian_IsLittle (
        void
    );


    ERESULT         Endian_PutU16Big(
        void            *pValue,        // Out
        uint16_t        value           // In
    );

    ERESULT         Endian_PutU16Little(
        void            *pValue,        // Out
        uint16_t        value           // In
    );


    ERESULT         Endian_PutU24Big(
        void            *pValue,        // Out
        uint32_t        value           // In
    );

    ERESULT         Endian_PutU24Little(
        void            *pValue,        // Out
        uint32_t        value           // In
    );


    ERESULT         Endian_PutU32Big(
        void            *pValue,        // Out
        uint32_t        value           // In
    );

    ERESULT         Endian_PutU32Little(
        void            *pValue,        // Out
        uint32_t        value           // In
    );


    ERESULT         Endian_PutU64Big(
        void            *pValue,        // Out
        uint64_t        value           // In
    );

    ERESULT         Endian_PutU64Little(
        void            *pValue,        // Out
        uint64_t        value           // In
    );

    
    uint16_t        Endian_Swap16(uint16_t value);
    uint32_t        Endian_Swap32(uint32_t value);
    uint64_t        Endian_Swap64(uint64_t value);



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    

    
#ifdef  __cplusplus
}
#endif

#endif  /* ENDIAN_H */

