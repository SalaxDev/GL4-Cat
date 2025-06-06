#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "soil2::soil2" for configuration "Release"
set_property(TARGET soil2::soil2 APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(soil2::soil2 PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C;CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libsoil2.a"
  )

list(APPEND _cmake_import_check_targets soil2::soil2 )
list(APPEND _cmake_import_check_files_for_soil2::soil2 "${_IMPORT_PREFIX}/lib/libsoil2.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
