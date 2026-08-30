from libCmn import Path, AStr

# Create a Path
path = Path.new_from_str("/home/user")
print(path.data)  # Prints "/home/user"
print(path.length)  # Prints length of "/home/user"

# Use inherited AStr method
path.append("/docs")  # Calls Path_AppendA (overridden) or AStr_AppendA (inherited)
print(path.data)  # Prints "/home/user/docs"

# Get AStr explicitly
astr = path.get_astr()
print(astr.data)  # Prints "/home/user/docs"

# Use inherited AStr methods
json_str = path.to_json()  # Calls Path_ToJson
print(json_str.data)  # Prints JSON representation
debug_str = path.to_debug_string(indent=2)  # Calls Path_ToDebugString
print(debug_str.data)  # Prints debug representation

# Test additional Path methods (if exposed)
# path.exists()  # Add to Path class if needed

