import glob
import os
import commands

target = './src/win.a'
sources = [ './src/win.cpp', './src/win_highgui.cpp' ]
include_dir = [ './inc' ]
env = Environment()
env.ParseConfig( 'pkg-config --cflags opencv' )
env.Append( CPPPATH = include_dir )
env.StaticLibrary( target, sources, LIBPREFIX = "" )
