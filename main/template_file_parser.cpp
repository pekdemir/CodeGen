#include "template_file_parser.h"

std::vector<std::string> gLuaPrints{};

void bail(lua_State *L, const char *msg){
	fprintf(stderr, "\nFATAL ERROR:\n  %s: %s\n\n",
		msg, lua_tostring(L, -1));
	exit(1);
}

std::string readFile(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        std::cout << "Failed to open file: " << filePath << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    std::string fileContents = buffer.str();
    return fileContents;
}

std::vector<MatchData> findTripleBrackets(const std::string& input) {
    std::vector<MatchData> matches;
    //std::regex pattern("\\[\\[\\[(.*?)\\]\\]\\]"); // Regex pattern to match [[[...]]]
    std::regex pattern("\\[\\[\\[([\\s\\S]*?)\\]\\]\\]"); // Regex pattern to match [[[...]]] [\\s\\S] for multiline match

    // std::smatch match;
    // std::string::const_iterator searchStart(input.cbegin());
    // while (std::regex_search(searchStart, input.cend(), match, pattern)) {
    //     searchStart = match.suffix().first; // Update the search start position
    //     matches.push_back(match); // Add the captured match to the vector
    // }


    size_t pos = 0;
    std::string::const_iterator input_begin = input.cbegin();
    for (std::smatch sm; std::regex_search(input_begin, input.cend(), sm, pattern);)
    {
        pos += sm.prefix().str().size();
        MatchData data = {sm[1].str(), pos, sm.length(0)};
        matches.push_back(data);
        pos += sm.length(0);
        
        input_begin = sm.suffix().first; // Update the search start position
    }

    // for(const auto& match : matches) {
    //     std::cout << "Match: " << match.text << " pos: " << match.pos << " len: " << match.len << std::endl;
    // }

    return matches;
}

// int main() {
//     std::string input = "Some text [[[match1]]] more text [[[match2]]] and [[[match3]]]";

//     std::vector<std::string> matches = findTripleBrackets(input);
//     for (const std::string& match : matches) {
//         std::cout << "Match: " << match << std::endl;
//     }

//     return 0;
// }

int parseTemplateFile(lua_State *L, const std::string& filePath) {
    std::string fileContents = readFile(filePath);
    if (fileContents.empty()) {
        std::cout << "Failed to read file: " << filePath << std::endl;
        return 1;
    }

    std::vector<MatchData> matches = findTripleBrackets(fileContents);
    std::vector<std::vector<std::string>> luaProgramOutputs{};
    int match_index = 0;
    for (const auto match : matches) {
        std::cout << "Match: " << match.text << std::endl;
        if (luaL_loadstring(L, match.text.c_str()))    /* Load but don't run the Lua script */
            bail(L, "luaL_loadfile() failed");      /* Error out if file can't be read */

        if (lua_pcall(L, 0, 0, 0))                  /* Run the loaded Lua script */
            bail(L, "lua_pcall() failed");          /* Error out if Lua file has an error */

        luaProgramOutputs.push_back(gLuaPrints);
        gLuaPrints.clear();    
    }


    size_t shift_amount = 0;
    for (const auto match : matches) {
        std::cout << "Match: " << match.text << std::endl;

        fileContents.erase(match.pos + shift_amount, match.len);


        size_t offset = match.pos + shift_amount;
        for(const auto& output : luaProgramOutputs[match_index])
        {
            fileContents.insert(offset, output);
            offset += output.size();
        }
        shift_amount += offset - match.pos - shift_amount - match.len;
        match_index++;
    }

    std::cout << "Intermediate Template: \n" << fileContents << std::endl;

    return 0;
}
