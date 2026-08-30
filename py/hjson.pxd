# vi:nu:et:sts=4 ts=4 sw=4
# hjson.pxd
# distutils: language = c

cimport     AStr
cimport     Node
cimport     NodeHash
cimport     Path

cdef extern from "hjson.h":
    ctypedef struct HJSON_DATA:
        pass


    HJSON_DATA* hjson_Alloc()

    HJSON_DATA* hjson_NewA(const char* pSzStr, uint16_t tabSize)

    HJSON_DATA* hjson_NewAStr(AStr.ASTR_DATA* pSzStr, uint16_t tabSize)

    HJSON_DATA* hjson_NewFromPath(Path.PATH_DATA* pPath, uint16_t tabSize)

    NodeHash.NODEHASH_DATA* hjson_getFileObject(HJSON_DATA* this)

    Path.PATH_DATA* hjson_getPath(HJSON_DATA* this)

    bint hjson_setPath(HJSON_DATA* this, Path.PATH_DATA* pValue)

    NODE_DATA* hjson_ParseFileHash(HJSON_DATA* this)

    NODE_DATA* hjson_ParseFileValue(HJSON_DATA* this)

    AStr.ASTR_DATA* hjson_ToDebugString(HJSON_DATA* this, int indent)

