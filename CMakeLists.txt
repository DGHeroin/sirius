project(Sirius)
cmake_minimum_required(VERSION 2.8)

SET(TARGET_EXECUTABLE  Sirius)
SET(SOURCE_DIR  ${CMAKE_SOURCE_DIR})

SET(TARGET_SAHRED_LIB libsirius)

# Include
INCLUDE_DIRECTORIES(include)

if ( CMAKE_COMPILER_IS_GNUCC )
    link_directories(${SOURCE_DIR}/prebuild/linux/lib)
endif ( CMAKE_COMPILER_IS_GNUCC )
if ( MSVC )
    link_directories(${SOURCE_DIR}/prebuild/windows/lib)
endif ( MSVC )

# Compiler flags
if ( CMAKE_COMPILER_IS_GNUCC )
    add_definitions(/Wall)
endif ( CMAKE_COMPILER_IS_GNUCC )
if ( MSVC )
    add_definitions(/W3)
endif ( MSVC )


# Source code folder
# Sirius core
aux_source_directory(sirius/base/core BASE_SRC_LIST)
aux_source_directory(sirius/base/thread BASE_SRC_LIST)

add_library (sirius_base STATIC ${BASE_SRC_LIST})
set(ALL_SRC_LIST ${ALL_SRC_LIST} ${BASE_SRC_LIST})
set(DEP_LIBRARIES ${DEP_LIBRARIES} sirius_base)

#
# Internal module
#
function(decare_sirius_internal_module module_name dep_libs)
    set(this_module_name sirius_${module_name})
    aux_source_directory(${SOURCE_DIR}/sirius/${module_name} INTERNAL_MODULE_SRC_LIST)

    add_library (${this_module_name} STATIC ${INTERNAL_MODULE_SRC_LIST})
    set(ALL_SRC_LIST ${ALL_SRC_LIST} ${INTERNAL_MODULE_SRC_LIST} PARENT_SCOPE) # make sure add to PARENT_SCOPE
    set(DEP_LIBRARIES ${DEP_LIBRARIES} ${this_module_name} PARENT_SCOPE) # make sure add to PARENT_SCOPE
    # depend libs
    FOREACH( var ${dep_libs} )
        target_link_libraries(${this_module_name} ${var})
    endforeach()

    message(STATUS "================================")
    message(STATUS "decare internal module: " ${this_module_name})
    message(STATUS "src list: " ${INTERNAL_MODULE_SRC_LIST})
    message(STATUS "dep_libs: " ${dep_libs})
    message(STATUS "ARGC: " ${ARGV})
    message(STATUS "*******************************")
endfunction()

#lua
decare_sirius_internal_module(lua "lua53;sirius_base" )
#net
decare_sirius_internal_module(net "sirius_base")

add_library (libsirius STATIC ${ALL_SRC_LIST})

# Examples
aux_source_directory(example EXAMPLE_SRC_LIST)
aux_source_directory(example/echo EXAMPLE_SRC_LIST)
aux_source_directory(example/lua EXAMPLE_SRC_LIST)
aux_source_directory(example/net EXAMPLE_SRC_LIST)
aux_source_directory(example/thread EXAMPLE_SRC_LIST)

set(ALL_SRC_LIST ${ALL_SRC_LIST} ${EXAMPLE_SRC_LIST})

include(${SOURCE_DIR}/extends/CMakeLists.txt)

MESSAGE( STATUS "Source folder:         " ${SOURCE_DIR})
MESSAGE( STATUS "depends libs :         " ${DEP_LIBRARIES})
MESSAGE( STATUS "all src list :         " ${ALL_SRC_LIST} )

add_executable(${TARGET_EXECUTABLE} ${ALL_SRC_LIST})
target_link_libraries(${TARGET_EXECUTABLE} ${DEP_LIBRARIES})


