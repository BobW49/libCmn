# vi:nu:et:sts=4 ts=4 sw=4
# test_SrcLoc.py

from libCmn import AStr, Path, Name, SrcLoc

# Test AStr
astr = AStr.new_from_str("hello")
print(astr.data)  # Prints "hello"

# Test Path
path = Path.new_from_str("/home/user")
print(path.data)  # Prints "/home/user"

# Test Name
name = Name.new_from_utf8("example")
print(name.utf8)  # Prints "example"

# Test SrcLoc
srcloc = SrcLoc.new(filename="/test/file.c", offset=100, line_no=10, col_no=5)
print(srcloc.filename)  # Prints "/test/file.c"
print(srcloc.line_no)  # Prints 10
print(srcloc.col_no)  # Prints 5
print(srcloc.offset)  # Prints 100
srcloc.set_filename("/new/file.c")
print(srcloc.filename)  # Prints "/new/file.c"
print(srcloc.to_json().data)  # Prints JSON representation
print(srcloc.to_debug_string(indent=2).data)  # Prints debug string
srcloc_copy = srcloc.copy()
print(srcloc_copy.filename)  # Prints "/new/file.c"
