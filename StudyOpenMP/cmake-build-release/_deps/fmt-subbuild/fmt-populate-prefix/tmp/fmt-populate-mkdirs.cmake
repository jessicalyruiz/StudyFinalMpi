# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/Users/PERSONAL/CLionProjects/StudyOpenMP/cmake-build-release/_deps/fmt-src"
  "D:/Users/PERSONAL/CLionProjects/StudyOpenMP/cmake-build-release/_deps/fmt-build"
  "D:/Users/PERSONAL/CLionProjects/StudyOpenMP/cmake-build-release/_deps/fmt-subbuild/fmt-populate-prefix"
  "D:/Users/PERSONAL/CLionProjects/StudyOpenMP/cmake-build-release/_deps/fmt-subbuild/fmt-populate-prefix/tmp"
  "D:/Users/PERSONAL/CLionProjects/StudyOpenMP/cmake-build-release/_deps/fmt-subbuild/fmt-populate-prefix/src/fmt-populate-stamp"
  "D:/Users/PERSONAL/CLionProjects/StudyOpenMP/cmake-build-release/_deps/fmt-subbuild/fmt-populate-prefix/src"
  "D:/Users/PERSONAL/CLionProjects/StudyOpenMP/cmake-build-release/_deps/fmt-subbuild/fmt-populate-prefix/src/fmt-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/Users/PERSONAL/CLionProjects/StudyOpenMP/cmake-build-release/_deps/fmt-subbuild/fmt-populate-prefix/src/fmt-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/Users/PERSONAL/CLionProjects/StudyOpenMP/cmake-build-release/_deps/fmt-subbuild/fmt-populate-prefix/src/fmt-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
