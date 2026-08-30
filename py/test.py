#!/usr/bin/env python3
# vi:nu:et:sts=4 ts=4 sw=4

import  os
import  sys

from libCmn import AStr, Path

# Create an AStr from a string
astr = AStr.new_from_str("Hello, HJSON!")
print(f"AStr data: {astr.data}, length: {astr.length}")

# Append to the AStr
astr.append(" World!")
print(f"Updated AStr: {astr.data}")

sys.exit(0)


# Create a TextIn object from the AStr
textin = TextIn.new_from_astr(astr, file_index=1, tab_size=4)

# Read lines and their source locations
while not textin.is_at_eof():
    line, srcloc = textin.get_line()
    if line:
        print(f"Line: {line.data}, Location: {srcloc.filename}:{srcloc.line_no}:{srcloc.col_no}")

# Create a Token (example, assuming you set it up externally)
token = Token.new()
# Further token processing would depend on your Token setup logic

# Debug output
debug_str = astr.to_debug_string(indent=4)
print(f"Debug AStr: {debug_str.data}")
