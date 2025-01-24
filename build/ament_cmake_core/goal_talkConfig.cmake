# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_goal_talk_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED goal_talk_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(goal_talk_FOUND FALSE)
  elseif(NOT goal_talk_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(goal_talk_FOUND FALSE)
  endif()
  return()
endif()
set(_goal_talk_CONFIG_INCLUDED TRUE)

# output package information
if(NOT goal_talk_FIND_QUIETLY)
  message(STATUS "Found goal_talk: 0.0.0 (${goal_talk_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'goal_talk' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${goal_talk_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(goal_talk_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${goal_talk_DIR}/${_extra}")
endforeach()
