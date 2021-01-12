# -*- coding: utf-8 -*- 
import distutils 
from distutils.core import setup, Extension 
setup(name = "Simple example from the SWIG website", 
	version = "0.007", 
	ext_modules = [Extension( 
	"_MyString", 
	["MyString.i","MyString.cxx"], 
	swig_opts=['-threads', '-c++'],
	)] 
);