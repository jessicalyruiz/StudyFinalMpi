# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/Users/PERSONAL/CLionProjects/StudyOpenMP/cmake-build-debug/_deps/fort-src"
  "D:/Users/PERSONAL/CLionProjects/StudyOpenMP/cmake-build-debug/_deps/fort-build"
  "D:/Users/PERSONAL/CLionProjects/StudyOpenMP/cmake-build-debug/_deps/fort-subbuild/fort-populate-prefix"
  "D:/Users/PERSONAL/CLionProjects/StudyOpenMP/cmake-build-debug/_deps/fort-subbuild/fort-populate-prefix/tmp"
  "D:/Users/PERSONAL/CLionProjects/StudyOpenMP/cmake-build-debug/_deps/fort-subbuild/fort-populate-prefix/src/fort-populate-stamp"
  "D:/Users/PERSONAL/CLionProjects/StudyOpenMP/cmake-build-debug/_deps/fort-subbuild/fort-populate-prefix/src"
  "D:/Users/PERSONAL/CLionProjects/StudyOpenMP/cmake-build-debug/_deps/fort-subbuild/fort-populate-prefix/src/fort-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/Users/PERSONAL/CLionProjects/StudyOpenMP/cmake-build-debug/_deps/fort-subbuild/fort-populate-prefix/src/fort-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/Users/PERSONAL/CLionProjects/StudyOpenMP/cmake-build-debug/_deps/fort-subbuild/fort-populate-prefix/src/fort-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
