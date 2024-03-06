cmake_minimum_required(VERSION 3.7)

project( LuaLib )

# set(LUA_VERSION "5.4.6")
# set(LUA_URL "https://www.lua.org/ftp/lua-${LUA_VERSION}.tar.gz")
# set(LUA_ARCHIVE "${CMAKE_BINARY_DIR}/lua/lua-${LUA_VERSION}.tar.gz")
# set(LUA_SRC_DIR "${CMAKE_SOURCE_DIR}/lua-${LUA_VERSION}")
# set(LUA_NAME "lua-${LUA_VERSION}")

# find_program(WGET_PROGRAM wget)

# if(NOT WGET_PROGRAM)
#     message(FATAL_ERROR "wget not found")
# endif()

# add_custom_command(
#     OUTPUT ${LUA_ARCHIVE}
#     COMMAND ${WGET_PROGRAM} -O ${LUA_ARCHIVE} ${LUA_URL}
#     COMMENT "Downloading Lua..."
# )

# add_custom_command(
#     OUTPUT ${LUA_SRC_DIR}
#     COMMAND ${CMAKE_COMMAND} -E tar xzf ${LUA_ARCHIVE} ${LUA_NAME}/src
#     WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/lua
#     DEPENDS ${LUA_ARCHIVE}
#     COMMENT "Extracting Lua..."
# )

# add_custom_target(
#     download_lua ALL
#     DEPENDS ${LUA_SRC_DIR}
# )

# The recommended way to collect sources in variable by explicitly specifying the source files
set  (LUA_RUNTIME_SOURCES
"src/lapi.c"
"src/lapi.h"
"src/lauxlib.c"
"src/lauxlib.h"
"src/lbaselib.c"
#"src/lbitlib.c"
"src/lcode.c"
"src/lcode.h"
"src/lcorolib.c"
"src/lctype.c"
"src/lctype.h"
"src/ldblib.c"
"src/ldebug.c"
"src/ldebug.h"
"src/ldo.c"
"src/ldo.h"
"src/ldump.c"
"src/lfunc.c"
"src/lfunc.h"
"src/lgc.c"
"src/lgc.h"
"src/linit.c"
"src/liolib.c"
"src/llex.c"
"src/llex.h"
"src/llimits.h"
"src/lmathlib.c"
"src/lmem.c"
"src/lmem.h"
"src/loadlib.c"
"src/lobject.c"
"src/lobject.h"
"src/lopcodes.c"
"src/lopcodes.h"
"src/loslib.c"
"src/lparser.c"
"src/lparser.h"
"src/lprefix.h"
"src/lstate.c"
"src/lstate.h"
"src/lstring.c"
"src/lstring.h"
"src/lstrlib.c"
"src/ltable.c"
"src/ltable.h"
"src/ltablib.c"
"src/ltm.c"
"src/ltm.h"
#"src/lua.c"
#"src/lua.h"
"src/lua.hpp"
#"src/luac.c"
"src/luaconf.h"
"src/lualib.h"
"src/lundump.c"
"src/lundump.h"
"src/lutf8lib.c"
"src/lvm.c"
"src/lvm.h"
"src/lzio.c"
"src/lzio.h")
  
add_library( LuaLib ${LUA_RUNTIME_SOURCES})

# add_dependencies(LuaLib download_lua)

target_include_directories ( LuaLib PUBLIC "${PROJECT_SOURCE_DIR}/src")

