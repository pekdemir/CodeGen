cmake_minimum_required(VERSION 3.7)

project( CodeGen )

if(MSVC)
	add_compile_options(/MP)				#Use multiple processors when building
	add_compile_options(/W4 /wd4201 /WX)	#Warning level 4, all warnings are errors
else()
	add_compile_options(-W -Wall -Werror) #All Warnings, all warnings are errors
endif()

add_compile_options(
    -Wall
    -Wextra
    -Werror
    -Wno-unknown-pragmas
)

# source for the test executable
set  (CODEGEN_SOURCES
		"main.cpp"
		"template_file_parser.cpp"
)
		
source_group("src" FILES ${CODEGEN_SOURCES})
		
add_executable( CodeGen
	${CODEGEN_SOURCES} 
	)

target_link_libraries( CodeGen PUBLIC LuaLib )