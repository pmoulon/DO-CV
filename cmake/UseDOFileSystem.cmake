macro (do_set_filesystem_source_dir)
  set(DO_FileSystem_SOURCE_DIR ${DO_SOURCE_DIR}/FileSystem)
endmacro (do_set_filesystem_source_dir)

macro (do_list_filesystem_source_files)
  # Master header file
  set(DO_FileSystem_MASTER_HEADER ${DO_SOURCE_DIR}/FileSystem.hpp)
  source_group("Master Header File" FILES ${DO_FileSystem_MASTER_HEADER})
  # Header files
  file(GLOB DO_FileSystem_HEADER_FILES
       ${DO_FileSystem_SOURCE_DIR}/*.hpp)
  # Source files
  file(GLOB DO_FileSystem_SOURCE_FILES
       ${DO_FileSystem_SOURCE_DIR}/*.cpp)
  # All header files here
  set(DO_FileSystem_HEADER_FILES
      ${DO_FileSystem_MASTER_HEADER}
      ${DO_FileSystem_HEADER_FILES})
endmacro (do_list_filesystem_source_files)

macro (do_load_packages_for_filesystem_library)
endmacro (do_load_packages_for_filesystem_library)

macro (do_create_variables_for_filesystem_library)
  set(DO_FileSystem_LIBRARIES DO_FileSystem)
  set(DO_FileSystem_LINK_LIBRARIES stlplus)
endmacro (do_create_variables_for_filesystem_library)

do_load_packages_for_filesystem_library()

if (DO_USE_FROM_SOURCE)
  get_property(DO_FileSystem_ADDED GLOBAL PROPERTY _DO_FileSystem_INCLUDED)
  if (NOT DO_FileSystem_ADDED)
    do_set_filesystem_source_dir()
    do_list_filesystem_source_files()
    do_create_variables_for_filesystem_library()
    
    # Static library
    do_append_library(
      FileSystem STATIC
      "${DO_SOURCE_DIR}"
      "${DO_FileSystem_HEADER_FILES}"
      "${DO_FileSystem_SOURCE_FILES}"
      "${DO_FileSystem_LINK_LIBRARIES}"
    )
    do_set_specific_target_properties(DO_FileSystem DO_STATIC)

    # Shared library
    if (DO_BUILD_SHARED_LIBS)
      do_append_library(
        FileSystem_SHARED SHARED
        "${DO_SOURCE_DIR}"
        "${DO_FileSystem_HEADER_FILES}"
        "${DO_FileSystem_SOURCE_FILES}"
        "${DO_FileSystem_LINK_LIBRARIES}"
      )
      do_set_specific_target_properties(DO_FileSystem_SHARED DO_EXPORTS)
    endif ()
  endif ()
endif ()
