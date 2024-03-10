

# Conan automatically generated toolchain file
# DO NOT EDIT MANUALLY, it will be overwritten

# Avoid including toolchain file several times (bad if appending to variables like
#   CMAKE_CXX_FLAGS. See https://github.com/android/ndk/issues/323
include_guard()

message(STATUS "Using Conan toolchain: ${CMAKE_CURRENT_LIST_FILE}")

if(${CMAKE_VERSION} VERSION_LESS "3.15")
    message(FATAL_ERROR "The 'CMakeToolchain' generator only works with CMake >= 3.15")
endif()




########## generic_system block #############
# Definition of system, platform and toolset
#############################################





set(CMAKE_C_COMPILER "C:/mingw64/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "C:/mingw64/bin/c++.exe")


string(APPEND CONAN_CXX_FLAGS " -m64")
string(APPEND CONAN_C_FLAGS " -m64")
string(APPEND CONAN_SHARED_LINKER_FLAGS " -m64")
string(APPEND CONAN_EXE_LINKER_FLAGS " -m64")



message(STATUS "Conan toolchain: C++ Standard 17 with extensions OFF")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Conan conf flags start: 
# Conan conf flags end

foreach(config ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${config} config)
    if(DEFINED CONAN_CXX_FLAGS_${config})
      string(APPEND CMAKE_CXX_FLAGS_${config}_INIT " ${CONAN_CXX_FLAGS_${config}}")
    endif()
    if(DEFINED CONAN_C_FLAGS_${config})
      string(APPEND CMAKE_C_FLAGS_${config}_INIT " ${CONAN_C_FLAGS_${config}}")
    endif()
    if(DEFINED CONAN_SHARED_LINKER_FLAGS_${config})
      string(APPEND CMAKE_SHARED_LINKER_FLAGS_${config}_INIT " ${CONAN_SHARED_LINKER_FLAGS_${config}}")
    endif()
    if(DEFINED CONAN_EXE_LINKER_FLAGS_${config})
      string(APPEND CMAKE_EXE_LINKER_FLAGS_${config}_INIT " ${CONAN_EXE_LINKER_FLAGS_${config}}")
    endif()
endforeach()

if(DEFINED CONAN_CXX_FLAGS)
  string(APPEND CMAKE_CXX_FLAGS_INIT " ${CONAN_CXX_FLAGS}")
endif()
if(DEFINED CONAN_C_FLAGS)
  string(APPEND CMAKE_C_FLAGS_INIT " ${CONAN_C_FLAGS}")
endif()
if(DEFINED CONAN_SHARED_LINKER_FLAGS)
  string(APPEND CMAKE_SHARED_LINKER_FLAGS_INIT " ${CONAN_SHARED_LINKER_FLAGS}")
endif()
if(DEFINED CONAN_EXE_LINKER_FLAGS)
  string(APPEND CMAKE_EXE_LINKER_FLAGS_INIT " ${CONAN_EXE_LINKER_FLAGS}")
endif()


get_property( _CMAKE_IN_TRY_COMPILE GLOBAL PROPERTY IN_TRY_COMPILE )
if(_CMAKE_IN_TRY_COMPILE)
    message(STATUS "Running toolchain IN_TRY_COMPILE")
    return()
endif()

set(CMAKE_FIND_PACKAGE_PREFER_CONFIG ON)

# Definition of CMAKE_MODULE_PATH
# the generators folder (where conan generates files, like this toolchain)
list(PREPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

# Definition of CMAKE_PREFIX_PATH, CMAKE_XXXXX_PATH
# The Conan local "generators" folder, where this toolchain is saved.
list(PREPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_LIST_DIR} )
list(PREPEND CMAKE_LIBRARY_PATH "C:/Users/PERSONAL/.conan2/p/b/sfmldf46f88b39c22/p/lib" "C:/Users/PERSONAL/.conan2/p/b/freetd9cad48348b5f/p/lib" "C:/Users/PERSONAL/.conan2/p/b/libpn573fd6e3ecb6d/p/lib" "C:/Users/PERSONAL/.conan2/p/b/zlib4d28542ff4e21/p/lib" "C:/Users/PERSONAL/.conan2/p/b/bzip2a74f3931bd55a/p/lib" "C:/Users/PERSONAL/.conan2/p/b/brotl3be1f092095a7/p/lib" "lib" "C:/Users/PERSONAL/.conan2/p/b/flacdaac82fb5c719/p/lib" "C:/Users/PERSONAL/.conan2/p/b/opena585aed6eddfa8/p/lib" "C:/Users/PERSONAL/.conan2/p/b/vorbid69cbf5bb2bb0/p/lib" "C:/Users/PERSONAL/.conan2/p/b/ogg6567aea319a1c/p/lib" "lib")
list(PREPEND CMAKE_INCLUDE_PATH "C:/Users/PERSONAL/.conan2/p/b/sfmldf46f88b39c22/p/include" "C:/Users/PERSONAL/.conan2/p/b/freetd9cad48348b5f/p/include" "C:/Users/PERSONAL/.conan2/p/b/freetd9cad48348b5f/p/include/freetype2" "C:/Users/PERSONAL/.conan2/p/b/libpn573fd6e3ecb6d/p/include" "C:/Users/PERSONAL/.conan2/p/b/zlib4d28542ff4e21/p/include" "C:/Users/PERSONAL/.conan2/p/b/bzip2a74f3931bd55a/p/include" "C:/Users/PERSONAL/.conan2/p/b/brotl3be1f092095a7/p/include" "C:/Users/PERSONAL/.conan2/p/b/brotl3be1f092095a7/p/include/brotli" "include" "C:/Users/PERSONAL/.conan2/p/b/flacdaac82fb5c719/p/include" "C:/Users/PERSONAL/.conan2/p/b/opena585aed6eddfa8/p/include" "C:/Users/PERSONAL/.conan2/p/b/opena585aed6eddfa8/p/include/AL" "C:/Users/PERSONAL/.conan2/p/b/vorbid69cbf5bb2bb0/p/include" "C:/Users/PERSONAL/.conan2/p/b/ogg6567aea319a1c/p/include" "include")



if (DEFINED ENV{PKG_CONFIG_PATH})
set(ENV{PKG_CONFIG_PATH} "${CMAKE_CURRENT_LIST_DIR};$ENV{PKG_CONFIG_PATH}")
else()
set(ENV{PKG_CONFIG_PATH} "${CMAKE_CURRENT_LIST_DIR};")
endif()




# Variables
# Variables  per configuration


# Preprocessor definitions
# Preprocessor definitions per configuration


if(CMAKE_POLICY_DEFAULT_CMP0091)  # Avoid unused and not-initialized warnings
endif()