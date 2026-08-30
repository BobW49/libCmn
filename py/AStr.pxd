# vi:nu:et:sts=4 ts=4 sw=4
# AStr.pxd



cdef extern from "cmn_defs.h":
    ctypedef struct ASTR_DATA:
        pass
    ctypedef int ERESULT
    ctypedef unsigned int uint32_t
    void obj_Release(void *obj)

cdef extern from "AStr.h":
    ASTR_DATA *  AStr_New()
    ASTR_DATA *  AStr_NewA(const char *pszInA)
    ASTR_DATA *  AStr_NewFromMidA(const char *pszIn, uint32_t offset, uint32_t len)
    const char * AStr_getData(ASTR_DATA *this)
    uint32_t     AStr_getLength(ASTR_DATA *this)
    ERESULT      AStr_AppendA(ASTR_DATA *this, const char *pStr)
    ASTR_DATA *  AStr_ToJson(ASTR_DATA *this)
    ASTR_DATA *  AStr_ToDebugString(ASTR_DATA *this, int indent)

