# vi:nu:et:sts=4 ts=4 sw=4
# Name.pxd

cimport     AStr

cdef extern from "cmn_defs.h":
    ctypedef struct NAME_DATA:
        pass
    ctypedef int ERESULT
    ctypedef unsigned int uint32_t
    ctypedef long long int64_t
    void obj_Release(void *obj)

cdef extern from "Name.h":
    ctypedef enum Name_type_e:
        NAME_TYPE_UNKNOWN = 0
        NAME_TYPE_INTEGER
        NAME_TYPE_UTF8
        NAME_TYPE_UTF8_CON
        NAME_TYPE_ASTR

    NAME_DATA * Name_New()
    NAME_DATA * Name_NewAStr(AStr.ASTR_DATA *pValue)
    NAME_DATA * Name_NewUTF8(const char *pValueA)
    NAME_DATA * Name_NewUTF8Con(const char *pValue)
    AStr.ASTR_DATA * Name_getStr(NAME_DATA *this)
    char * Name_getUTF8(NAME_DATA *this)
    int64_t Name_getInt(NAME_DATA *this)
    uint32_t Name_getHash(NAME_DATA *this)
    ERESULT Name_Assign(NAME_DATA *this, NAME_DATA *pOther)
    NAME_DATA * Name_Copy(NAME_DATA *this)
    AStr.ASTR_DATA * Name_ToJson(NAME_DATA *this)
    AStr.ASTR_DATA * Name_ToDebugString(NAME_DATA *this, int indent)
    AStr.ASTR_DATA * Name_ToAStr(NAME_DATA *this)
    char * Name_ToUTF8(NAME_DATA *this)
