# vi:nu:et:sts=4 ts=4 sw=4
# test_Name.py

from libCmn import AStr, Path, Name

# Test AStr
astr = AStr.new_from_str("hello")
print(astr.data)  # Prints "hello"

# Test Path
path = Path.new_from_str("/home/user")
print(path.data)  # Prints "/home/user"

# Test Name
name = Name.new_from_utf8("example")
print(name.utf8)  # Prints "example"
print(name.str.data)  # Prints "example" (via AStr)
name_astr = Name.new_from_astr(astr)
print(name_astr.str.data)  # Prints "hello"
print(name.to_json().data)  # Prints JSON representation
print(name.to_debug_string(indent=2).data)  # Prints debug string
name_copy = name.copy()
print(name_copy.utf8)  # Prints "example"
