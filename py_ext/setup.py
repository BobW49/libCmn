##!/usr/bin/env python3 setup.py build_ext --inplace
# vi:nu:et:sts=4 ts=4 sw=4
# setup.py

""" 
    Execute using: python3 setup.py build_ext --inplace
"""

from setuptools import setup
from setuptools.extension import Extension
import os

import macos_defs


ext_name = 'hjson_ext'
os_name = macos_defs.os_name()
arch = macos_defs.arch()
user_name = macos_defs.user_name()
if os_name == 'macos':
    if arch == 'arm64' or arch == 'x86_64':
        os_name = 'macos64'
        dir_os = f"{os_name}/{arch}"
        ENV_CONSTANT = '__MACOS64_ENV__'
        if arch == 'arm64':
            ENV_CONSTANT = '__MACOS64_ARM64_ENV__'
    else:
        raise ValueError(f"{os_name} and {arch} are unsupported!")
else:
    raise ValueError(f"{os_name} and {arch} are unsupported!")


# Paths to your C headers and source files
include_dirs = [f"/Users/{user_name}/git/lib/{dir_os}/lib{lib_name}/include"]
library_dirs = [f"/Users/{user_name}/git/lib/{dir_os}/lib{lib_name}"]
libraries = [f"{lib_name}"]

# Define preprocessor macros
define_macros = [
    ['ASTR_JSON_SUPPORT', '1'],
    ['TOKEN_JSON_SUPPORT', '1'],
    ['SRCLOC_JSON_SUPPORT', '1'],
    ['FALSE_JSON_SUPPORT', '1'],
    [ENV_CONSTANT, '1']
]
extra_compile_args = []
for key, value in define_macros:
    if value is None:
        extra_compile_args.append(f'-D{key}')
    else:
        extra_compile_args.append(f'-D{key}={value}')
extra_compile_args.append('-std=c99')

# Define the Cython extension
extensions = [
    Extension(
        name=f"lib{lib_name}",
        sources=[f"lib{lib_name}.pyx"],
        include_dirs=include_dirs,
        library_dirs=library_dirs,
        libraries=libraries,
        extra_compile_args=extra_compile_args,
    )
]

setup(
    name=f"lib{lib_name}",
    ext_modules=cythonize(
        extensions,
        compiler_directives={'language_level': '3'},
    ),
    include_dirs=include_dirs,
)
