# vi:nu:et:sts=4 ts=4 sw=4
# NodeHash.pxd
# distutils: language = c


cdef extern from "NodeHash.h":
    ctypedef struct NODEHASH_DATA:
        pass

    ctypedef struct NODEHASH_CLASS_DATA:
        pass

    ctypedef struct NODE_DATA:
        pass

    ctypedef struct ASTR_DATA:
        pass

    ctypedef struct NAME_DATA:
        pass

    ctypedef struct PATH_DATA:
        pass

    cdef enum:
        NODEHASH_JSON_SUPPORT = 1

    NODEHASH_DATA* NodeHash_Alloc()

    NODEHASH_DATA* NodeHash_New()

    NODEHASH_DATA* NodeHash_NewWithSize(uint16_t size)

    ERESULT NodeHash_AddA(NODEHASH_DATA* this, const char* pNameA, NODE_DATA* pNode)

    ERESULT NodeHash_AddUtf8(NODEHASH_DATA* this, const char* pNameA, NODE_DATA* pNode)

    ERESULT NodeHash_AddName(NODEHASH_DATA* this, NAME_DATA* pName, NODE_DATA* pNode)

    ERESULT NodeHash_DeleteA(NODEHASH_DATA* this, const char* pNameA)

    NODE_DATA* NodeHash_FindA(NODEHASH_DATA* this, const char* pNameA)

    NODE_DATA* NodeHash_FindUtf8(NODEHASH_DATA* this, const char* pNameA)

    NODEHASH_DATA* NodeHash_Copy(NODEHASH_DATA* this)

    ASTR_DATA* NodeHash_ToDebugString(NODEHASH_DATA* this, int indent)

