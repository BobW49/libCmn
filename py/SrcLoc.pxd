# vi:nu:et:sts=4 ts=4 sw=4
# SrcLoc.pxd

cimport AStr

cdef extern from "cmn_defs.h":
    ctypedef struct SRCLOC_DATA:
        pass
    ctypedef int ERESULT
    void obj_Release(void *obj)

cdef extern from "SrcLoc.h":
    ctypedef struct SrcLoc_s:
        const char *pFileNameA
        uint16_t colNo
        uint32_t lineNo
        int64_t offset

    SRCLOC_DATA * SrcLoc_New()
    SRCLOC_DATA * SrcLoc_NewFLC(const char *pFileNameA, int64_t offset, uint32_t lineNo, uint16_t colNo)
    const char * SrcLoc_getFileName(SRCLOC_DATA *this)
    uint16_t SrcLoc_getColNo(SRCLOC_DATA *this)
    uint32_t SrcLoc_getLineNo(SRCLOC_DATA *this)
    int64_t SrcLoc_getOffset(SRCLOC_DATA *this)
    ERESULT SrcLoc_setFileName(SRCLOC_DATA *this, const char *pValue)
    ERESULT SrcLoc_setColNo(SRCLOC_DATA *this, uint16_t value)
    ERESULT SrcLoc_setLineNo(SRCLOC_DATA *this, uint32_t value)
    ERESULT SrcLoc_setOffset(SRCLOC_DATA *this, int64_t value)
    ERESULT SrcLoc_Assign(SRCLOC_DATA *this, SRCLOC_DATA *pOther)
    SRCLOC_DATA * SrcLoc_Copy(SRCLOC_DATA *this)
    AStr.ASTR_DATA * SrcLoc_ToJson(SRCLOC_DATA *this)
    AStr.ASTR_DATA * SrcLoc_ToDebugString(SRCLOC_DATA *this, int indent)
