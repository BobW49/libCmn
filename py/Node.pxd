# vi:nu:et:sts=4 ts=4 sw=4
# Node.pxd
cimport AStr
cimport Name

cdef extern from "cmn_defs.h":
    ctypedef struct NODE_DATA:
        pass
    ctypedef int ERESULT
    void obj_Release(void *obj)

cdef extern from "Node.h":
    NODE_DATA * Node_New()
    NODE_DATA * Node_NewWithAStr(AStr.ASTR_DATA *pName, void *pData)
    void * Node_getData(NODE_DATA *this)
    Name.NAME_DATA * Node_getName(NODE_DATA *this)
    AStr.ASTR_DATA * Node_ToJson(NODE_DATA *this)
    AStr.ASTR_DATA * Node_ToDebugString(NODE_DATA *this, int indent)
    ERESULT Node_Assign(NODE_DATA *this, NODE_DATA *pOther)
    NODE_DATA * Node_Copy(NODE_DATA *this)
