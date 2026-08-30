# vi:nu:et:sts=4 ts=4 sw=4
# libCmn.pyx
# distutils: language = c
#!cythonize
# cython: language_level=3


from cpython cimport bool
ctypedef int int32_t
ctypedef unsigned int uint32_t
ctypedef unsigned short uint16_t
ctypedef long long int64_t
ctypedef unsigned long long uint64_t
ctypedef char W32CHR_T
ctypedef int ERESULT



cimport     AStr
cimport     Path
cimport     hjson
cimport     Name
cimport     Node
cimport     NodeArray
cimport     NodeHash
cimport     SrcLoc


cdef extern from "cmn_defs.h":
    ctypedef struct TOKEN_DATA:
        pass
    ctypedef struct TEXTIN_DATA:
        pass
    ctypedef struct ARRAY_DATA:
        pass
    ctypedef struct DEC_DATA:
        pass
    ctypedef struct W32STR_DATA:
        pass
    ctypedef struct OBJ_IUNKNOWN:
        void (*pRelease)(void *)


cdef extern from "obj.h":
    void obj_Release(void *obj)


cdef extern from "Token.h":
    TOKEN_DATA * Token_New()
    TOKEN_DATA * Token_Copy(TOKEN_DATA *this)
    ASTR_DATA * Token_getTextAStr(TOKEN_DATA *this)
    uint16_t Token_getType(TOKEN_DATA *this)
    ASTR_DATA * Token_ToDebugString(TOKEN_DATA *this, int indent)
    ASTR_DATA * Token_ToJson(TOKEN_DATA *this)

cdef extern from "TextIn.h":
    TEXTIN_DATA * TextIn_New()
    TEXTIN_DATA * TextIn_NewFromAStr(PATH_DATA *pFilePath, ASTR_DATA *pStr, uint16_t fileIndex, uint16_t tabSize)
    ERESULT TextIn_GetLineAStr(TEXTIN_DATA *this, ASTR_DATA **ppStr, SRCLOC *pLoc)
    bint TextIn_IsAtEOF(TEXTIN_DATA *this)
    ASTR_DATA * TextIn_ToDebugString(TEXTIN_DATA *this, int indent)

cdef extern from "array.h":
    ARRAY_DATA * array_New()
    ARRAY_DATA * array_NewWithSize(uint16_t elemSize)
    uint32_t array_getSize(ARRAY_DATA *this)
    ERESULT array_Push(ARRAY_DATA *this, void *pData)
    ERESULT array_Pop(ARRAY_DATA *this, void *pData)
    ASTR_DATA * array_ToDebugString(ARRAY_DATA *this, int indent)

cdef extern from "dec.h":
    DEC_DATA * dec_New()
    int32_t dec_getInt32A(const char *pStr)
    uint64_t dec_getUint64A(const char *pStr)
    ASTR_DATA * dec_UInt64ToJson(uint64_t data)
    ASTR_DATA * dec_ToDebugString(DEC_DATA *this, int indent)



#---------------------------------------------------------------
#                       A S t r
#---------------------------------------------------------------

cdef class AStr:
    cdef ASTR_DATA *c_ptr
    cdef bint _own

    def __cinit__(self):
        self.c_ptr = NULL
        self._own = False

    def __dealloc__(self):
        if self.c_ptr and self._own:
            obj_Release(self.c_ptr)
            self.c_ptr = NULL

    @staticmethod
    def new():
        cdef AStr obj = AStr()
        obj.c_ptr = AStr_New()
        obj._own = True
        if not obj.c_ptr:
            raise MemoryError("Failed to create AStr")
        return obj

    @staticmethod
    def new_from_str(str s):
        cdef AStr obj = AStr()
        obj.c_ptr = AStr_NewA(s.encode('utf-8'))
        obj._own = True
        if not obj.c_ptr:
            raise MemoryError("Failed to create AStr from string")
        return obj

    @property
    def data(self):
        if self.c_ptr:
            return AStr_getData(self.c_ptr).decode('utf-8')
        return None

    @property
    def length(self):
        if self.c_ptr:
            return AStr_getLength(self.c_ptr)
        return 0

    def append(self, str s):
        if not self.c_ptr:
            raise ValueError("AStr object is not initialized")
        if AStr_AppendA(self.c_ptr, s.encode('utf-8')) != 0:
            raise RuntimeError("Failed to append string")

    def to_json(self):
        if not self.c_ptr:
            raise ValueError("AStr object is not initialized")
        cdef ASTR_DATA *json_ptr = AStr_ToJson(self.c_ptr)
        if not json_ptr:
            raise RuntimeError("Failed to convert to JSON")
        cdef AStr json_obj = AStr()
        json_obj.c_ptr = json_ptr
        json_obj._own = True
        return json_obj

    def to_debug_string(self, int indent=0):
        if not self.c_ptr:
            raise ValueError("AStr object is not initialized")
        cdef ASTR_DATA *str_ptr = AStr_ToDebugString(self.c_ptr, indent)
        if not str_ptr:
            raise RuntimeError("Failed to create debug string")
        cdef AStr str_obj = AStr()
        str_obj.c_ptr = str_ptr
        str_obj._own = True
        return str_obj



#---------------------------------------------------------------
#                       N a m e
#---------------------------------------------------------------

cdef class Name:
    cdef Name.NAME_DATA *c_ptr
    cdef bint _own

    def __cinit__(self):
        self.c_ptr = NULL
        self._own = False

    def __dealloc__(self):
        if self.c_ptr and self._own:
            Name.obj_Release(self.c_ptr)
            self.c_ptr = NULL

    @staticmethod
    def new():
        cdef Name obj = Name()
        obj.c_ptr = Name.Name_New()
        obj._own = True
        if not obj.c_ptr:
            raise MemoryError("Failed to create Name")
        return obj

    @staticmethod
    def new_from_astr(AStr astr):
        if not astr.c_ptr:
            raise ValueError("AStr object is not initialized")
        cdef Name obj = Name()
        obj.c_ptr = Name.Name_NewAStr(astr.c_ptr)
        obj._own = True
        if not obj.c_ptr:
            raise MemoryError("Failed to create Name from AStr")
        return obj

    @staticmethod
    def new_from_utf8(str s):
        cdef Name obj = Name()
        obj.c_ptr = Name.Name_NewUTF8(s.encode('utf-8'))
        obj._own = True
        if not obj.c_ptr:
            raise MemoryError("Failed to create Name from UTF-8 string")
        return obj

    @staticmethod
    def new_from_utf8_con(str s):
        cdef Name obj = Name()
        obj.c_ptr = Name.Name_NewUTF8Con(s.encode('utf-8'))
        obj._own = True
        if not obj.c_ptr:
            raise MemoryError("Failed to create Name from UTF-8 constant")
        return obj

    @property
    def str(self):
        if not self.c_ptr:
            raise ValueError("Name object is not initialized")
        cdef AStr.ASTR_DATA *str_ptr = Name.Name_getStr(self.c_ptr)
        if not str_ptr:
            raise RuntimeError("Failed to get AStr string")
        cdef AStr str_obj = AStr()
        str_obj.c_ptr = str_ptr
        str_obj._own = True
        return str_obj

    @property
    def utf8(self):
        if not self.c_ptr:
            raise ValueError("Name object is not initialized")
        cdef char *utf8_ptr = Name.Name_getUTF8(self.c_ptr)
        if not utf8_ptr:
            raise RuntimeError("Failed to get UTF-8 string")
        try:
            result = utf8_ptr.decode('utf-8')
        finally:
            # Assuming Name_getUTF8 requires freeing the returned string
            # If mem_Free is needed, add it to cmn_defs.h and pxd files
            pass
        return result

    @property
    def int(self):
        if not self.c_ptr:
            raise ValueError("Name object is not initialized")
        return Name.Name_getInt(self.c_ptr)

    @property
    def hash(self):
        if not self.c_ptr:
            raise ValueError("Name object is not initialized")
        return Name.Name_getHash(self.c_ptr)

    def assign(self, Name other):
        if not self.c_ptr or not other.c_ptr:
            raise ValueError("Name object is not initialized")
        if Name.Name_Assign(self.c_ptr, other.c_ptr) != 0:
            raise RuntimeError("Failed to assign Name")

    def copy(self):
        if not self.c_ptr:
            raise ValueError("Name object is not initialized")
        cdef Name obj = Name()
        obj.c_ptr = Name.Name_Copy(self.c_ptr)
        obj._own = True
        if not obj.c_ptr:
            raise MemoryError("Failed to copy Name")
        return obj

    def to_json(self):
        if not self.c_ptr:
            raise ValueError("Name object is not initialized")
        cdef AStr.ASTR_DATA *json_ptr = Name.Name_ToJson(self.c_ptr)
        if not json_ptr:
            raise RuntimeError("Failed to convert to JSON")
        cdef AStr json_obj = AStr()
        json_obj.c_ptr = json_ptr
        json_obj._own = True
        return json_obj

    def to_debug_string(self, int indent=0):
        if not self.c_ptr:
            raise ValueError("Name object is not initialized")
        cdef AStr.ASTR_DATA *str_ptr = Name.Name_ToDebugString(self.c_ptr, indent)
        if not str_ptr:
            raise RuntimeError("Failed to create debug string")
        cdef AStr str_obj = AStr()
        str_obj.c_ptr = str_ptr
        str_obj._own = True
        return str_obj

    def to_astr(self):
        if not self.c_ptr:
            raise ValueError("Name object is not initialized")
        cdef AStr.ASTR_DATA *str_ptr = Name.Name_ToAStr(self.c_ptr)
        if not str_ptr:
            raise RuntimeError("Failed to create AStr")
        cdef AStr str_obj = AStr()
        str_obj.c_ptr = str_ptr
        str_obj._own = True
        return str_obj

    def to_utf8(self):
        if not self.c_ptr:
            raise ValueError("Name object is not initialized")
        cdef char *utf8_ptr = Name.Name_ToUTF8(self.c_ptr)
        if not utf8_ptr:
            raise RuntimeError("Failed to create UTF-8 string")
        try:
            result = utf8_ptr.decode('utf-8')
        finally:
            # Assuming Name_ToUTF8 requires freeing the returned string
            # If mem_Free is needed, add it to cmn_defs.h and pxd files
            pass
        return result



#---------------------------------------------------------------
#                       N o d e
#---------------------------------------------------------------

cdef class Node:
    cdef Node.NODE_DATA *c_ptr
    cdef bint _own

    def __cinit__(self):
        self.c_ptr = NULL
        self._own = False

    def __dealloc__(self):
        if self.c_ptr and self._own:
            Node.obj_Release(self.c_ptr)
            self.c_ptr = NULL

    @staticmethod
    def new():
        cdef Node obj = Node()
        obj.c_ptr = Node.Node_New()
        obj._own = True
        if not obj.c_ptr:
            raise MemoryError("Failed to create Node")
        return obj

    @staticmethod
    def new_with_astr(AStr astr, object data=None):
        if not astr.c_ptr:
            raise ValueError("AStr object is not initialized")
        cdef Node obj = Node()
        obj.c_ptr = Node.Node_NewWithAStr(astr.c_ptr, <void *>data if data is not None else NULL)
        obj._own = True
        if not obj.c_ptr:
            raise MemoryError("Failed to create Node with AStr")
        return obj

    @property
    def data(self):
        if self.c_ptr:
            return <object>Node.Node_getData(self.c_ptr)
        return None

    @property
    def name(self):
        if not self.c_ptr:
            raise ValueError("Node object is not initialized")
        cdef Name.NAME_DATA *name_ptr = Node.Node_getName(self.c_ptr)
        if not name_ptr:
            raise RuntimeError("Failed to get Name")
        cdef Name name_obj = Name()
        name_obj.c_ptr = name_ptr
        name_obj._own = True
        return name_obj

    def to_json(self):
        if not self.c_ptr:
            raise ValueError("Node object is not initialized")
        cdef AStr.ASTR_DATA *json_ptr = Node.Node_ToJson(self.c_ptr)
        if not json_ptr:
            raise RuntimeError("Failed to convert to JSON")
        cdef AStr json_obj = AStr()
        json_obj.c_ptr = json_ptr
        json_obj._own = True
        return json_obj

    def to_debug_string(self, int indent=0):
        if not self.c_ptr:
            raise ValueError("Node object is not initialized")
        cdef AStr.ASTR_DATA *str_ptr = Node.Node_ToDebugString(self.c_ptr, indent)
        if not str_ptr:
            raise RuntimeError("Failed to create debug string")
        cdef AStr str_obj = AStr()
        str_obj.c_ptr = str_ptr
        str_obj._own = True
        return str_obj

    def assign(self, Node other):
        if not self.c_ptr or not other.c_ptr:
            raise ValueError("Node object is not initialized")
        if Node.Node_Assign(self.c_ptr, other.c_ptr) != 0:
            raise RuntimeError("Failed to assign Node")

    def copy(self):
        if not self.c_ptr:
            raise ValueError("Node object is not initialized")
        cdef Node obj = Node()
        obj.c_ptr = Node.Node_Copy(self.c_ptr)
        obj._own = True
        if not obj.c_ptr:
            raise MemoryError("Failed to copy Node")
        return obj



#---------------------------------------------------------------
#                   N o d e  A r r a y
#---------------------------------------------------------------

cdef class NodeArray:
    cdef NodeArray.NODEARRAY_DATA *c_ptr
    cdef bint _own

    def __cinit__(self):
        self.c_ptr = NULL
        self._own = False

    def __dealloc__(self):
        if self.c_ptr and self._own:
            NodeArray.obj_Release(self.c_ptr)
            self.c_ptr = NULL

    @staticmethod
    def new():
        cdef NodeArray obj = NodeArray()
        obj.c_ptr = NodeArray.NodeArray_New()
        obj._own = True
        if not obj.c_ptr:
            raise MemoryError("Failed to create NodeArray")
        return obj

    @property
    def size(self):
        if self.c_ptr:
            return NodeArray.NodeArray_getSize(self.c_ptr)
        return 0

    def append(self, Node node):
        if not self.c_ptr or not node.c_ptr:
            raise ValueError("NodeArray or Node object is not initialized")
        if NodeArray.NodeArray_AppendNode(self.c_ptr, node.c_ptr) != 0:
            raise RuntimeError("Failed to append Node")

    def get(self, uint32_t index):
        if not self.c_ptr:
            raise ValueError("NodeArray object is not initialized")
        cdef Node.NODE_DATA *node_ptr = NodeArray.NodeArray_Get(self.c_ptr, index)
        if not node_ptr:
            return None
        cdef Node node_obj = Node()
        node_obj.c_ptr = node_ptr
        node_obj._own = True
        return node_obj

    def get_first(self):
        if not self.c_ptr:
            raise ValueError("NodeArray object is not initialized")
        cdef Node.NODE_DATA *node_ptr = NodeArray.NodeArray_GetFirst(self.c_ptr)
        if not node_ptr:
            return None
        cdef Node node_obj = Node()
        node_obj.c_ptr = node_ptr
        node_obj._own = True
        return node_obj

    def get_last(self):
        if not self.c_ptr:
            raise ValueError("NodeArray object is not initialized")
        cdef Node.NODE_DATA *node_ptr = NodeArray.NodeArray_GetLast(self.c_ptr)
        if not node_ptr:
            return None
        cdef Node node_obj = Node()
        node_obj.c_ptr = node_ptr
        node_obj._own = True
        return node_obj

    def delete_first(self):
        if not self.c_ptr:
            raise ValueError("NodeArray object is not initialized")
        cdef Node.NODE_DATA *node_ptr = NodeArray.NodeArray_DeleteFirst(self.c_ptr)
        if not node_ptr:
            return None
        cdef Node node_obj = Node()
        node_obj.c_ptr = node_ptr
        node_obj._own = True
        return node_obj

    def delete_last(self):
        if not self.c_ptr:
            raise ValueError("NodeArray object is not initialized")
        cdef Node.NODE_DATA *node_ptr = NodeArray.NodeArray_DeleteLast(self.c_ptr)
        if not node_ptr:
            return None
        cdef Node node_obj = Node()
        node_obj.c_ptr = node_ptr
        node_obj._own = True
        return node_obj

    def assign(self, NodeArray other):
        if not self.c_ptr or not other.c_ptr:
            raise ValueError("NodeArray object is not initialized")
        if NodeArray.NodeArray_Assign(self.c_ptr, other.c_ptr) != 0:
            raise RuntimeError("Failed to assign NodeArray")

    def copy(self):
        if not self.c_ptr:
            raise ValueError("NodeArray object is not initialized")
        cdef NodeArray obj = NodeArray()
        obj.c_ptr = NodeArray.NodeArray_Copy(self.c_ptr)
        obj._own = True
        if not obj.c_ptr:
            raise MemoryError("Failed to copy NodeArray")
        return obj

    def to_json(self):
        if not self.c_ptr:
            raise ValueError("NodeArray object is not initialized")
        cdef AStr.ASTR_DATA *json_ptr = NodeArray.NodeArray_ToJson(self.c_ptr)
        if not json_ptr:
            raise RuntimeError("Failed to convert to JSON")
        cdef AStr json_obj = AStr()
        json_obj.c_ptr = json_ptr
        json_obj._own = True
        return json_obj

    def to_debug_string(self, int indent=0):
        if not self.c_ptr:
            raise ValueError("NodeArray object is not initialized")
        cdef AStr.ASTR_DATA *str_ptr = NodeArray.NodeArray_ToDebugString(self.c_ptr, indent)
        if not str_ptr:
            raise RuntimeError("Failed to create debug string")
        cdef AStr str_obj = AStr()
        str_obj.c_ptr = str_ptr
        str_obj._own = True
        return str_obj


#---------------------------------------------------------------
#                   N o d e  H a s h
#---------------------------------------------------------------

cdef class NodeHash:
    cdef NodeHash.NODEHASH_DATA *c_ptr
    cdef bint _own

    def __cinit__(self):
        self.c_ptr = NULL
        self._own = False

    def __dealloc__(self):
        if self.c_ptr and self._own:
            NodeHash.obj_Release(self.c_ptr)
            self.c_ptr = NULL

    @staticmethod
    def new():
        cdef NodeHash obj = NodeHash()
        obj.c_ptr = NodeHash.NodeHash_New()
        obj._own = True
        if not obj.c_ptr:
            raise MemoryError("Failed to create NodeHash")
        return obj

    @property
    def size(self):
        if self.c_ptr:
            return NodeHash.NodeHash_getSize(self.c_ptr)
        return 0

    def add(self, Node node):
        if not self.c_ptr or not node.c_ptr:
            raise ValueError("NodeHash or Node object is not initialized")
        if NodeHash.NodeHash_AddNode(self.c_ptr, node.c_ptr) != 0:
            raise RuntimeError("Failed to add Node")

    def get(self, str name):
        if not self.c_ptr:
            raise ValueError("NodeHash object is not initialized")
        cdef Node.NODE_DATA *node_ptr = NodeHash.NodeHash_GetA(self.c_ptr, name.encode('utf-8'))
        if not node_ptr:
            return None
        cdef Node node_obj = Node()
        node_obj.c_ptr = node_ptr
        node_obj._own = True
        return node_obj

    def assign(self, NodeHash other):
        if not self.c_ptr or not other.c_ptr:
            raise ValueError("NodeHash object is not initialized")
        if NodeHash.NodeHash_Assign(self.c_ptr, other.c_ptr) != 0:
            raise RuntimeError("Failed to assign NodeHash")

    def copy(self):
        if not self.c_ptr:
            raise ValueError("NodeHash object is not initialized")
        cdef NodeHash obj = NodeHash()
        obj.c_ptr = NodeHash.NodeHash_Copy(self.c_ptr)
        obj._own = True
        if not obj.c_ptr:
            raise MemoryError("Failed to copy NodeHash")
        return obj

    def to_json(self):
        if not self.c_ptr:
            raise ValueError("NodeHash object is not initialized")
        cdef AStr.ASTR_DATA *json_ptr = NodeHash.NodeHash_ToJson(self.c_ptr)
        if not json_ptr:
            raise RuntimeError("Failed to convert to JSON")
        cdef AStr json_obj = AStr()
        json_obj.c_ptr = json_ptr
        json_obj._own = True
        return json_obj

    def to_debug_string(self, int indent=0):
        if not self.c_ptr:
            raise ValueError("NodeHash object is not initialized")
        cdef AStr.ASTR_DATA *str_ptr = NodeHash.NodeHash_ToDebugString(self.c_ptr, indent)
        if not str_ptr:
            raise RuntimeError("Failed to create debug string")
        cdef AStr str_obj = AStr()
        str_obj.c_ptr = str_ptr
        str_obj._own = True
        return str_obj


#---------------------------------------------------------------
#                       P a t h
#---------------------------------------------------------------

cdef class Path(AStr):
    cdef Path.PATH_DATA *c_ptr

    def __cinit__(self):
        self.c_ptr = NULL
        self._own = False

    def __dealloc__(self):
        if self.c_ptr and self._own:
            Path.obj_Release(self.c_ptr)
            self.c_ptr = NULL

    @staticmethod
    def new():
        cdef Path obj = Path()
        obj.c_ptr = Path.Path_New()
        obj._own = True
        if not obj.c_ptr:
            raise MemoryError("Failed to create Path")
        return obj

    @staticmethod
    def new_from_str(str s):
        cdef Path obj = Path()
        obj.c_ptr = Path.Path_NewA(s.encode('utf-8'))
        obj._own = True
        if not obj.c_ptr:
            raise MemoryError("Failed to create Path from string")
        return obj

    @property
    def data(self):
        if self.c_ptr:
            return Path.Path_getData(self.c_ptr).decode('utf-8')
        return None

    @property
    def length(self):
        if self.c_ptr:
            return Path.Path_getLength(self.c_ptr)
        return 0

    def get_astr(self):
        if not self.c_ptr:
            raise ValueError("Path object is not initialized")
        cdef AStr.ASTR_DATA *str_ptr = Path.Path_getAStr(self.c_ptr)
        if not str_ptr:
            raise RuntimeError("Failed to create AStr string")
        cdef AStr str_obj = AStr()
        str_obj.c_ptr = str_ptr
        str_obj._own = True
        return str_obj

    def append(self, str s):
        if not self.c_ptr:
            raise ValueError("Path object is not initialized")
        if Path.Path_AppendA(self.c_ptr, s.encode('utf-8')) != 0:
            raise RuntimeError("Failed to append string")

    def to_json(self):
        if not self.c_ptr:
            raise ValueError("Path object is not initialized")
        cdef AStr.ASTR_DATA *json_ptr = Path.Path_ToJson(self.c_ptr)
        if not json_ptr:
            raise RuntimeError("Failed to convert to JSON")
        cdef AStr json_obj = AStr()
        json_obj.c_ptr = json_ptr
        json_obj._own = True
        return json_obj

    def to_debug_string(self, int indent=0):
        if not self.c_ptr:
            raise ValueError("Path object is not initialized")
        cdef AStr.ASTR_DATA *str_ptr = Path.Path_ToDebugString(self.c_ptr, indent)
        if not str_ptr:
            raise RuntimeError("Failed to create debug string")
        cdef AStr str_obj = AStr()
        str_obj.c_ptr = str_ptr
        str_obj._own = True
        return str_obj



#---------------------------------------------------------------
#                       S r c L o c
#---------------------------------------------------------------

cdef class SrcLoc:
    cdef SrcLoc.SRCLOC_DATA *c_ptr
    cdef bint _own

    def __cinit__(self):
        self.c_ptr = NULL
        self._own = False

    def __dealloc__(self):
        if self.c_ptr and self._own:
            SrcLoc.obj_Release(self.c_ptr)
            self.c_ptr = NULL

    @staticmethod
    def new(str filename=None, int64_t offset=0, uint32_t line_no=0, uint16_t col_no=0):
        cdef SrcLoc obj = SrcLoc()
        if filename:
            obj.c_ptr = SrcLoc.SrcLoc_NewFLC(filename.encode('utf-8'), offset, line_no, col_no)
        else:
            obj.c_ptr = SrcLoc.SrcLoc_New()
        obj._own = True
        if not obj.c_ptr:
            raise MemoryError("Failed to create SrcLoc")
        return obj

    @property
    def filename(self):
        if self.c_ptr:
            return SrcLoc.SrcLoc_getFileName(self.c_ptr).decode('utf-8')
        return None

    @property
    def line_no(self):
        if self.c_ptr:
            return SrcLoc.SrcLoc_getLineNo(self.c_ptr)
        return 0

    @property
    def col_no(self):
        if self.c_ptr:
            return SrcLoc.SrcLoc_getColNo(self.c_ptr)
        return 0

    @property
    def offset(self):
        if self.c_ptr:
            return SrcLoc.SrcLoc_getOffset(self.c_ptr)
        return 0

    def set_filename(self, str filename):
        if not self.c_ptr:
            raise ValueError("SrcLoc object is not initialized")
        if SrcLoc.SrcLoc_setFileName(self.c_ptr, filename.encode('utf-8')) != 0:
            raise RuntimeError("Failed to set filename")

    def set_col_no(self, uint16_t col_no):
        if not self.c_ptr:
            raise ValueError("SrcLoc object is not initialized")
        if SrcLoc.SrcLoc_setColNo(self.c_ptr, col_no) != 0:
            raise RuntimeError("Failed to set column number")

    def set_line_no(self, uint32_t line_no):
        if not self.c_ptr:
            raise ValueError("SrcLoc object is not initialized")
        if SrcLoc.SrcLoc_setLineNo(self.c_ptr, line_no) != 0:
            raise RuntimeError("Failed to set line number")

    def set_offset(self, int64_t offset):
        if not self.c_ptr:
            raise ValueError("SrcLoc object is not initialized")
        if SrcLoc.SrcLoc_setOffset(self.c_ptr, offset) != 0:
            raise RuntimeError("Failed to set offset")

    def assign(self, SrcLoc other):
        if not self.c_ptr or not other.c_ptr:
            raise ValueError("SrcLoc object is not initialized")
        if SrcLoc.SrcLoc_Assign(self.c_ptr, other.c_ptr) != 0:
            raise RuntimeError("Failed to assign SrcLoc")

    def copy(self):
        if not self.c_ptr:
            raise ValueError("SrcLoc object is not initialized")
        cdef SrcLoc obj = SrcLoc()
        obj.c_ptr = SrcLoc.SrcLoc_Copy(self.c_ptr)
        obj._own = True
        if not obj.c_ptr:
            raise MemoryError("Failed to copy SrcLoc")
        return obj

    def to_json(self):
        if not self.c_ptr:
            raise ValueError("SrcLoc object is not initialized")
        cdef AStr.ASTR_DATA *json_ptr = SrcLoc.SrcLoc_ToJson(self.c_ptr)
        if not json_ptr:
            raise RuntimeError("Failed to convert to JSON")
        cdef AStr json_obj = AStr()
        json_obj.c_ptr = json_ptr
        json_obj._own = True
        return json_obj

    def to_debug_string(self, int indent=0):
        if not self.c_ptr:
            raise ValueError("SrcLoc object is not initialized")
        cdef AStr.ASTR_DATA *str_ptr = SrcLoc.SrcLoc_ToDebugString(self.c_ptr, indent)
        if not str_ptr:
            raise RuntimeError("Failed to create debug string")
        cdef AStr str_obj = AStr()
        str_obj.c_ptr = str_ptr
        str_obj._own = True
        return str_obj



#---------------------------------------------------------------
#                       T o k e n
#---------------------------------------------------------------

cdef class Token:
    cdef TOKEN_DATA *c_ptr
    cdef bint _own

    def __cinit__(self):
        self.c_ptr = NULL
        self._own = False

    def __dealloc__(self):
        if self.c_ptr and self._own:
            obj_Release(self.c_ptr)
            self.c_ptr = NULL

    @staticmethod
    def new():
        cdef Token obj = Token()
        obj.c_ptr = Token_New()
        obj._own = True
        if not obj.c_ptr:
            raise MemoryError("Failed to create Token")
        return obj

    def copy(self):
        if not self.c_ptr:
            raise ValueError("Token object is not initialized")
        cdef Token obj = Token()
        obj.c_ptr = Token_Copy(self.c_ptr)
        obj._own = True
        if not obj.c_ptr:
            raise MemoryError("Failed to copy Token")
        return obj

    @property
    def text(self):
        if not self.c_ptr:
            raise ValueError("Token object is not initialized")
        cdef ASTR_DATA *astr_ptr = Token_getTextAStr(self.c_ptr)
        if not astr_ptr:
            raise RuntimeError("Failed to get token text")
        cdef AStr astr = AStr()
        astr.c_ptr = astr_ptr
        astr._own = True
        return astr

    @property
    def type(self):
        if self.c_ptr:
            return Token_getType(self.c_ptr)
        return 0

    def to_debug_string(self, int indent=0):
        if not self.c_ptr:
            raise ValueError("Token object is not initialized")
        cdef ASTR_DATA *str_ptr = Token_ToDebugString(self.c_ptr, indent)
        if not str_ptr:
            raise RuntimeError("Failed to create debug string")
        cdef AStr str_obj = AStr()
        str_obj.c_ptr = str_ptr
        str_obj._own = True
        return str_obj


#---------------------------------------------------------------
#                       T e x t I n
#---------------------------------------------------------------

cdef class TextIn:
    cdef TEXTIN_DATA *c_ptr
    cdef bint _own

    def __cinit__(self):
        self.c_ptr = NULL
        self._own = False

    def __dealloc__(self):
        if self.c_ptr and self._own:
            obj_Release(self.c_ptr)
            self.c_ptr = NULL

    @staticmethod
    def new():
        cdef TextIn obj = TextIn()
        obj.c_ptr = TextIn_New()
        obj._own = True
        if not obj.c_ptr:
            raise MemoryError("Failed to create TextIn")
        return obj

    @staticmethod
    def new_from_astr(AStr astr, file_index=0, tab_size=4):
        if not astr.c_ptr:
            raise ValueError("AStr object is not initialized")
        cdef TextIn obj = TextIn()
        obj.c_ptr = TextIn_NewFromAStr(NULL, astr.c_ptr, file_index, tab_size)
        obj._own = True
        if not obj.c_ptr:
            raise MemoryError("Failed to create TextIn from AStr")
        return obj

    def get_line(self):
        if not self.c_ptr:
            raise ValueError("TextIn object is not initialized")
        cdef ASTR_DATA *str_ptr = NULL
        cdef SRCLOC loc
        if TextIn_GetLineAStr(self.c_ptr, &str_ptr, &loc) != 0:
            raise RuntimeError("Failed to get line")
        if not str_ptr:
            return None, None
        cdef AStr astr = AStr()
        astr.c_ptr = str_ptr
        astr._own = True
        cdef SrcLoc srcloc = SrcLoc()
        srcloc.c_ptr = SrcLoc_NewFLC(loc.pFileNameA, loc.offset, loc.lineNo, loc.colNo)
        srcloc._own = True
        return astr, srcloc

    def is_at_eof(self):
        if not self.c_ptr:
            raise ValueError("TextIn object is not initialized")
        return TextIn_IsAtEOF(self.c_ptr)

    def to_debug_string(self, int indent=0):
        if not self.c_ptr:
            raise ValueError("TextIn object is not initialized")
        cdef ASTR_DATA *str_ptr = TextIn_ToDebugString(self.c_ptr, indent)
        if not str_ptr:
            raise RuntimeError("Failed to create debug string")
        cdef AStr str_obj = AStr()
        str_obj.c_ptr = str_ptr
        str_obj._own = True
        return str_obj



#---------------------------------------------------------------
#                       A r r a y
#---------------------------------------------------------------

cdef class Array:
    cdef ARRAY_DATA *c_ptr
    cdef bint _own

    def __cinit__(self):
        self.c_ptr = NULL
        self._own = False

    def __dealloc__(self):
        if self.c_ptr and self._own:
            obj_Release(self.c_ptr)
            self.c_ptr = NULL

    @staticmethod
    def new(uint16_t elem_size=0):
        cdef Array obj = Array()
        if elem_size:
            obj.c_ptr = array_NewWithSize(elem_size)
        else:
            obj.c_ptr = array_New()
        obj._own = True
        if not obj.c_ptr:
            raise MemoryError("Failed to create Array")
        return obj

    @property
    def size(self):
        if self.c_ptr:
            return array_getSize(self.c_ptr)
        return 0

    def to_debug_string(self, int indent=0):
        if not self.c_ptr:
            raise ValueError("Array object is not initialized")
        cdef ASTR_DATA *str_ptr = array_ToDebugString(self.c_ptr, indent)
        if not str_ptr:
            raise RuntimeError("Failed to create debug string")
        cdef AStr str_obj = AStr()
        str_obj.c_ptr = str_ptr
        str_obj._own = True
        return str_obj



#---------------------------------------------------------------
#                       D e c
#---------------------------------------------------------------

cdef class Dec:
    cdef DEC_DATA *c_ptr
    cdef bint _own

    def __cinit__(self):
        self.c_ptr = NULL
        self._own = False

    def __dealloc__(self):
        if self.c_ptr and self._own:
            obj_Release(self.c_ptr)
            self.c_ptr = NULL

    @staticmethod
    def new():
        cdef Dec obj = Dec()
        obj.c_ptr = dec_New()
        obj._own = True
        if not obj.c_ptr:
            raise MemoryError("Failed to create Dec")
        return obj

    def get_int32(self, str s):
        return dec_getInt32A(s.encode('utf-8'))

    def get_uint64(self, str s):
        return dec_getUint64A(s.encode('utf-8'))

    def uint64_to_json(self, uint64_t value):
        cdef ASTR_DATA *json_ptr = dec_UInt64ToJson(value)
        if not json_ptr:
            raise RuntimeError("Failed to convert to JSON")
        cdef AStr json_obj = AStr()
        json_obj.c_ptr = json_ptr
        json_obj._own = True
        return json_obj

    def to_debug_string(self, int indent=0):
        if not self.c_ptr:
            raise ValueError("Dec object is not initialized")
        cdef ASTR_DATA *str_ptr = dec_ToDebugString(self.c_ptr, indent)
        if not str_ptr:
            raise RuntimeError("Failed to create debug string")
        cdef AStr str_obj = AStr()
        str_obj.c_ptr = str_ptr
        str_obj._own = True
        return str_obj
        
    
