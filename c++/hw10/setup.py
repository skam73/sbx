from setuptools import setup, Extension
import pybind11

setup(
    name='vectoralgebra',
    version='0.1',
    description='Python module for vector algebra operations',
    ext_modules=[
        Extension(
            'vectoralgebra', 
            ['vectoralgebra.cpp'],
            include_dirs=[pybind11.get_include()],
        )],
    zip_safe=False
)
