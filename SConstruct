import glob
import os
import commands

target = './src/win.a'
sources = glob.glob( os.path.join( './', 'src', '*.cpp' ) )
include_dir = [ './inc' ]
env = Environment()
env.ParseConfig( 'pkg-config --cflags opencv' )
env.Append( CPPPATH = include_dir )
env.StaticLibrary( target, sources, LIBPREFIX = "" )
