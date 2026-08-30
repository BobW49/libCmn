# vi:nu:et:sts=4 ts=4 sw=4
# NodeArray.pxd
# distutils: language = c

cdef extern from "NodeArray.h":
    ctypedef struct NODEARRAY_DATA:
        pass

    ctypedef struct NODEARRAY_CLASS_DATA:
        pass

    ctypedef struct NODE_DATA:
        pass

    ctypedef struct ASTR_DATA:
        pass

    cdef enum:
        NODEARRAY_JSON_SUPPORT = 1

    NODEARRAY_DATA* NodeArray_Alloc()
    
    NODEARRAY_DATA* NodeArray_New()

    NODEARRAY_DATA* NodeArray_NewWithSize(uint16_t size)

    ERESULT NodeArray_Append(NODEARRAY_DATA* this, NODE_DATA* pNode)

    ERESULT NodeArray_Delete(NODEARRAY_DATA* this, uint32_t index)

    uint32_t NodeArray_getSize(NODEARRAY_DATA *this)

    NODE_DATA* NodeArray_Get(NODEARRAY_DATA* this, uint32_t index)

    NODEARRAY_DATA* NodeArray_Copy(NODEARRAY_DATA* this)

    AStr.ASTR_DATA* NodeArray_ToDebugString(NODEARRAY_DATA* this, int indent)

