#include <lua.hpp>
#include <stdlib.h>                             /* For function exit() */
#include <iostream>
#include "template_file_parser.h"

extern std::vector<std::string> gLuaPrints;

static int l_my_print(lua_State* L) {
    int nargs = lua_gettop(L);

    for (int i=1; i <= nargs; i++) {
        if (lua_isstring(L, i)) {
            /* Pop the next arg using lua_tostring(L, i) and do your print */
            //printf("From LUA: %s", lua_tostring(L, i));
            //sprintf(gLuaPrint, "%s", lua_tostring(L, i));
            gLuaPrints.emplace_back(lua_tostring(L, i));
        }
        else {
        /* Do something with non-strings if you like */
        }
    }

    return 0;
}

static const struct luaL_Reg printlib [] = {
  {"print", l_my_print},
  {NULL, NULL} /* end of array */
};

extern int luaopen_luamylib(lua_State *L)
{
  lua_getglobal(L, "_G");
  // luaL_register(L, NULL, printlib); // for Lua versions < 5.2
  luaL_setfuncs(L, printlib, 0);  // for Lua versions 5.2 or greater
  lua_pop(L, 1);
  return 0;
}


int main(int argc, char *argv[]) {

    if (argc != 3) {
        printf("Usage: %s <templateFile> <inputJsonFile>\n", argv[0]);
        return 1;
    }

    char *templateFile = argv[1];
    printf("templateFile: %s\n", templateFile);

    char *inputJsonFile = argv[2];
    printf("inputJsonFile: %s\n", inputJsonFile);


    lua_State *L;

    L = luaL_newstate();                        /* Create Lua state variable */
    luaL_openlibs(L);                           /* Load Lua libraries */
    luaopen_luamylib(L);

    parseTemplateFile(L, templateFile);

    lua_close(L);                               /* Clean up, free the Lua state var */

    return 0;
}