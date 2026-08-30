from setuptools import setup
from Cython.Build import cythonize

setup(
    ext_modules=cythonize(["hjson.pyx", "AStr.pyx", "Node.pyx"]),
    include_dirs=["/path/to/your/c/include"],
    extra_link_args=["-L/path/to/your/c/lib", "-lhjson"]
)
