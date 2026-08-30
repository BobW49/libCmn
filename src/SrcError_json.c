// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   SrcError.c
 *	Generated 05/26/2015 13:40:16
 *
 * Created on December 30, 2014
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




//*****************************************************************
//* * * * * * * * * * * *  Data Definitions   * * * * * * * * * * *
//*****************************************************************

/* Header File Inclusion */
#include    <SrcError_internal.h>
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <AStr_internal.h>
#include    <dec.h>
#include    <JsonIn.h>
#include    <Node.h>
#include    <NodeHash.h>
#include    <szTbl.h>
#include    <utf8.h>




#ifdef	__cplusplus
extern "C" {
#endif
    
    
    
    
    
    
    /****************************************************************
     * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
     ****************************************************************/
    
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    SRCERROR_DATA * SrcError_ParseJsonObject(
        JSONIN_DATA     *pParser
    )
    {
        ERESULT         eRc;
        SRCERROR_DATA   *pObject = OBJ_NIL;
        const
        OBJ_INFO        *pInfo;
        int64_t         intIn;
        ASTR_DATA       *pWrk = OBJ_NIL;

        pInfo = obj_getInfo(SrcError_Class());
        
        eRc = JsonIn_ConfirmObjectTypeA(pParser, pInfo->pClassName);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR - objectType is invalid!\n");
            goto exit00;
        }
        

        pObject = SrcError_New( );
        if (OBJ_NIL == pObject) {
            goto exit00;
        }
        
        eRc = JsonIn_FindStrNodeInHashA(pParser, "filename", &pWrk);
        if (ERESULT_OK(eRc)) {
            if (pWrk && AStr_getLength(pWrk)) {
                pObject->loc.pFileNameA = szTbl_StringToString(szTbl_Shared(), AStr_getData(pWrk));
            }
            obj_Release(pWrk);
            pWrk = OBJ_NIL;
        }
        eRc = JsonIn_FindIntegerNodeInHashA(pParser, "offset", &pObject->loc.offset);
        eRc = JsonIn_FindIntegerNodeInHashA(pParser, "lineNo", &intIn);
        pObject->loc.lineNo = (uint32_t)intIn;
        eRc = JsonIn_FindIntegerNodeInHashA(pParser, "colNo", &intIn);
        pObject->loc.colNo = (uint16_t)intIn;
        eRc = JsonIn_FindIntegerNodeInHashA(pParser, "severity", &intIn);
        pObject->severity = (uint16_t)intIn;

        eRc = JsonIn_FindStrNodeInHashA(pParser, "errorStr", &pWrk);
        if (ERESULT_OK(eRc)) {
            obj_Retain(pWrk);
            pObject->pErrorStr = pWrk;
            pWrk = OBJ_NIL;
        }

        // Return to caller.
    exit00:
        return pObject;
    }
    
    
    

    
    
    /****************************************************************
     * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
     ****************************************************************/
    
    
    //===============================================================
    //                      *** Class Methods ***
    //===============================================================
    

    SRCERROR_DATA *   SrcError_NewFromJsonString(
        ASTR_DATA       *pString
    )
    {
        JSONIN_DATA     *pParser;
        ERESULT         eRc;
        SRCERROR_DATA   *pObject = OBJ_NIL;
        
        pParser = JsonIn_New();
        eRc = JsonIn_ParseAStr(pParser, pString);
        if (ERESULT_FAILED(eRc)) {
            goto exit00;
        }
        
        pObject = SrcError_ParseJsonObject(pParser);
        
        // Return to caller.
    exit00:
        if (pParser) {
            obj_Release(pParser);
            pParser = OBJ_NIL;
        }
        return pObject;
    }
    
    

    SRCERROR_DATA * SrcError_NewFromJsonStringA(
        const
        char            *pString
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        SRCERROR_DATA   *pObject = OBJ_NIL;
        
        if (pString) {
            pStr = AStr_NewA(pString);
            pObject = SrcError_NewFromJsonString(pStr);
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        
        // Return to caller.
        return pObject;
    }
    
    
    
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = SrcLoc_ToJSON(this);
     @endcode
     @param     this    SRCLOC object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     SrcError_ToJson(
        SRCERROR_DATA   *this
    )
    {
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
#ifdef XYZZY
        void *          (*pQueryInfo)(
            OBJ_ID          objId,
            uint32_t        type,
            void            *pData
        );
#endif
        //ASTR_DATA       *pWrkStr;
#ifdef XYZZY
        ASTR_DATA *     (*pToJSON)(
            OBJ_ID          objId
        );
#endif

#ifdef NDEBUG
#else
        if( !SrcError_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pInfo = obj_getInfo(this);
        
        pStr = AStr_New();
        AStr_AppendPrint(pStr,
                         "{ \"objectType\":\"%s\", "
                         "\"filename\":\"%s\", "
                         "\"offset\":%lld, "
                         "\"lineNo\":%d, "
                         "\"colNo\":%d "
                         "\"severity\":%d ",
                         pInfo->pClassName,
                         this->loc.pFileNameA ? this->loc.pFileNameA : "",
                         this->loc.offset,
                         this->loc.lineNo,
                         this->loc.colNo,
                         this->severity
        );
        
        if (this->pErrorStr) {
            AStr_AppendPrint(pStr,
                             "\"errorStr\":\"%s\", ",
                             AStr_getData(this->pErrorStr)
            );
        }
        
        AStr_AppendA(pStr, "}\n");
        
        return pStr;
    }
    
    
    
    
    
#ifdef	__cplusplus
}
#endif

