#include <lua.hpp>
#include <stdlib.h>                             /* For function exit() */
#include <iostream>
#include "template_file_parser.h"
#include "../cmdparser/cmdparser.hpp"

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

void configure_parser(cli::Parser& parser) {
    parser.set_required<std::string>("t", "template", "Template file to be replaced.");
    parser.set_required<std::string>("d", "data", "Data JSON file that includes data.");
}

void parse_and_exit(cli::Parser& parser) {
    if (parser.run(std::cout, std::cout) == false) {
        exit(1);
    }
}


int main(int argc, char *argv[]) {

    cli::Parser parser(argc, argv);
    configure_parser(parser);
    parser.run_and_exit_if_error();

    std::string templateFile = parser.get<std::string>("t");
    std::cout << "templateFile: " <<  templateFile << "\n";

    std::string inputJsonFile = parser.get<std::string>("d");
    std::cout << "inputJsonFile: " <<  inputJsonFile << "\n";

    lua_State *L;

    L = luaL_newstate();                        /* Create Lua state variable */
    luaL_openlibs(L);                           /* Load Lua libraries */
    luaopen_luamylib(L);

    parseTemplateFile(L, templateFile);

    lua_close(L);                               /* Clean up, free the Lua state var */

    return 0;
}