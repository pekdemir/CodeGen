#include <iostream>
#include <fstream>
#include <string>
#include <optional>
#include <vector>
#include <regex>
extern "C" {
    #include <lua.h>                                /* Always include this when calling Lua */
    #include <lauxlib.h>                            /* Always include this when calling Lua */
    #include <lualib.h>                             /* Always include this when calling Lua */
}

struct MatchData
{
    std::string text;
    size_t pos;
    int64_t len;
};

void bail(lua_State *L, char *msg);

std::string readFile(const std::string& filePath);

std::vector<MatchData> findTripleBrackets(const std::string& input);

// int main() {
//     std::string input = "Some text [[[match1]]] more text [[[match2]]] and [[[match3]]]";

//     std::vector<std::string> matches = findTripleBrackets(input);
//     for (const std::string& match : matches) {
//         std::cout << "Match: " << match << std::endl;
//     }

//     return 0;
// }

int parseTemplateFile(lua_State *L, const std::string& filePath) ;