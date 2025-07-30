# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "E:/Code/Playing/Minesweeper_Clone/vendor/loggingad-src")
  file(MAKE_DIRECTORY "E:/Code/Playing/Minesweeper_Clone/vendor/loggingad-src")
endif()
file(MAKE_DIRECTORY
  "E:/Code/Playing/Minesweeper_Clone/vendor/loggingad-build"
  "E:/Code/Playing/Minesweeper_Clone/vendor/loggingad-subbuild/loggingad-populate-prefix"
  "E:/Code/Playing/Minesweeper_Clone/vendor/loggingad-subbuild/loggingad-populate-prefix/tmp"
  "E:/Code/Playing/Minesweeper_Clone/vendor/loggingad-subbuild/loggingad-populate-prefix/src/loggingad-populate-stamp"
  "E:/Code/Playing/Minesweeper_Clone/vendor/loggingad-subbuild/loggingad-populate-prefix/src"
  "E:/Code/Playing/Minesweeper_Clone/vendor/loggingad-subbuild/loggingad-populate-prefix/src/loggingad-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "E:/Code/Playing/Minesweeper_Clone/vendor/loggingad-subbuild/loggingad-populate-prefix/src/loggingad-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "E:/Code/Playing/Minesweeper_Clone/vendor/loggingad-subbuild/loggingad-populate-prefix/src/loggingad-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
