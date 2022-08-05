import platform
import os.path as p
import subprocess

DIR_OF_THIS_SCRIPT = p.abspath( p.dirname( __file__ ) )
SOURCE_EXTENSIONS = [ '.cpp', '.cxx', '.cc', '.c', '.ino', '.m', '.mm' ]

database = None
compilation_database_folder = ''

flags = [
  '-Wall',
  '-Wextra',
  '-Werror',
  '-Wpedantic',
  '-std=c11',
  '-xc',
  '-xc++',
  '--O0',
  '-Wstrict-aliasing'
  '-Wno-pointer-arith',
  '-Wno-newline-eof',
  '-Wno-unused-parameter',
  '-Wno-gnu-statement-expression',
  '-Wno-gnu-compound-literal-initializer',
  '-Wno-gnu-zero-variadic-macro-arguments'
  '-Ilib/glfw/include',
  '-Iinclude',
  '-Ilib/glad/include'

]

lib_dirs_project = [
  'lib',
  'src'
]


def IsHeaderFile( filename ):
  extension = p.splitext( filename )[ 1 ]
  return extension in [ '.h', '.hxx', '.hpp', '.hh' ]


def FindCorrespondingSourceFile( filename ):
  if IsHeaderFile( filename ):
    basename = p.splitext( filename )[ 0 ]
    for extension in SOURCE_EXTENSIONS:
      replacement_file = basename + extension
      if p.exists( replacement_file ):
        return replacement_file
  return filename


def GetIncludeFlagsFromDirList( dir_list ):
  include_flags = []

  for current_dir in dir_list:
    for path, dirs, files in os.walk(current_dir):
      for d in dirs:
        include_flag = '-I' + os.path.join(path, d)
        if "examples" not in include_flag and "extras" not in include_flag:
          include_flags.append(include_flag)

  return include_flags

def Settings( **kwargs ):
  # Do NOT import ycm_core at module scope.
  import ycm_core

  global database
  if database is None and p.exists( compilation_database_folder ):
    database = ycm_core.CompilationDatabase( compilation_database_folder )

  language = kwargs[ 'language' ]

  if language == 'cfamily':
    # If the file is a header, try to find the corresponding source file and
    # retrieve its flags from the compilation database if using one. This is
    # necessary since compilation databases don't have entries for header files.
    # In addition, use this source file as the translation unit. This makes it
    # possible to jump from a declaration in the header file to its definition
    # in the corresponding source file.
    filename = FindCorrespondingSourceFile( kwargs[ 'filename' ] )

    if not database:
      return {
        'flags': flags,
        'include_paths_relative_to_dir': DIR_OF_THIS_SCRIPT,
        'override_filename': filename
      }

    compilation_info = database.GetCompilationInfoForFile( filename )
    if not compilation_info.compiler_flags_:
      return {}

    final_flags = list( compilation_info.compiler_flags_ )

    return {
      'flags': final_flags,
      'include_paths_relative_to_dir': compilation_info.compiler_working_dir_,
      'override_filename': filename
    }


  return {}

