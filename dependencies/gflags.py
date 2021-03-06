# -*- python -*-
# Author: Christoph Lassner.
import os
Import(["env"])

# Create a temporary environment to be able to modify it locally.
gflags_lib_env = env.Clone()
gflags_lib_env['CPPPATH'] = ''
gflags_lib_env['CPPDEFINES'] = ''
# Activate symbol exporting.
if gflags_lib_env['CC'] == 'cl':
  # Set warning level to 3 (highest, before all warnings).
  gflags_lib_env.AppendUnique(CPPFLAGS='/W3')
  gflags_lib_env.AppendUnique(CPPFLAGS='/TP')
  gflags_lib_env.AppendUnique(CPPFLAGS='/GL')
  gflags_lib_env.AppendUnique(CPPFLAGS=['/nologo'])
  gflags_lib_env.AppendUnique(CPPDEFINES='WIN32;_WINDOWS;GFLAGS_IS_A_DLL=0'.split(';'))
  if GetOption('debug_build'):
    # Link against debug system libraries.
    env.AppendUnique(CPPDEFINES=['_DEBUG', '_SCL_SECURE_NO_WARNINGS'])
    env.Append(CCFLAGS = ["/MDd"])
  else:
    # Link against non-debug system libraries.
    env.AppendUnique(CPPFLAGS=['/MD'])
else:
  gflags_lib_env.AppendUnique(CCFLAGS=['-O2','-std=c++11','-g','-fPIC'])
if os.name == 'nt':
    subfolder = 'gflags-2.1.1'
else:
    subfolder = 'gflags-2.1.1-linux'
gflags_lib_env.AppendUnique(CPPPATH='%s' % subfolder)
gflags_lib_env.AppendUnique(CPPPATH=['%s/include/gflags' % subfolder])
# Create the build file list.
file_list = Glob('%s/*.cc' % subfolder)
headers = Glob('%s/include' % subfolder)
# The library.
libfile = gflags_lib_env.StaticLibrary('gflags', file_list)
installed_libfile = gflags_lib_env.InstallAs(os.path.join(str(Dir('../lib').srcnode()),
                                                          os.path.basename(str(libfile[0]))), libfile[0])
Return("installed_libfile", "headers")
