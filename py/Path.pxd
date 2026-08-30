# vi:nu:et:sts=4 ts=4 sw=4
# Path.pxd
# distutils: language = c

cimport     AStr

cdef extern from "cmn_defs.h":
    ctypedef struct PATH_DATA:
        pass
    ctypedef int ERESULT
    ctypedef unsigned int uint32_t
    void obj_Release(void *obj)

cdef extern from "AStr.h":
    ctypedef struct ASTR_DATA:
        pass

cdef extern from "Path.h":
    PATH_DATA *  Path_New()
    PATH_DATA *  Path_NewA(const char *pszInA)
    PATH_DATA *  Path_NewFromAStr(AStr.ASTR_DATA *pStr)
    const char * Path_getData(PATH_DATA *this)
    uint32_t     Path_getLength(PATH_DATA *this)
    ERESULT      Path_AppendA(PATH_DATA *this, const char *pStr)
    ERESULT      Path_AppendAStr(PATH_DATA *this, AStr.ASTR_DATA *pStr)
    AStr.ASTR_DATA *  Path_getAStr(PATH_DATA *this)
    AStr.ASTR_DATA *  Path_ToJson(PATH_DATA *this)
    AStr.ASTR_DATA *  Path_ToDebugString(PATH_DATA *this, int indent)
    ERESULT      Path_Clean(PATH_DATA *this, AStr.ASTR_DATA *(*pFindA)(void *, const char *), void *pFindObj)
    ERESULT      Path_Split(PATH_DATA *this, AStr.ASTR_DATA **ppDrive, AStr.ASTR_DATA **ppDir, AStr.ASTR_DATA **ppFileName, AStr.ASTR_DATA **ppFileExt)
    int          Path_Exists(PATH_DATA *this)
    ERESULT      Path_CreateEmpty(PATH_DATA *this)
    ERESULT      Path_Delete(PATH_DATA *this)
