cmake_minimum_required(VERSION 3.10)
project(libparserutils C)

# Generate aliases.inc
find_package(Perl REQUIRED)
set(ALIASES_INC ${CMAKE_CURRENT_SOURCE_DIR}/src/charset/aliases.inc)
add_custom_command(
    OUTPUT ${ALIASES_INC}
    COMMAND ${PERL_EXECUTABLE} build/make-aliases.pl
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/build/make-aliases.pl ${CMAKE_CURRENT_SOURCE_DIR}/build/Aliases
    COMMENT "Generating charset aliases"
)

file(GLOB_RECURSE SOURCES src/*.c)

add_library(parserutils ${SOURCES} ${ALIASES_INC})

target_include_directories(parserutils PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_compile_definitions(parserutils PRIVATE WITHOUT_ICONV_FILTER)

if(MSVC)
    # Keep MSVC shims PRIVATE so C++ targets that link css are not polluted.
    target_compile_definitions(parserutils PRIVATE
        _CRT_SECURE_NO_WARNINGS
        strncasecmp=_strnicmp
        strcasecmp=_stricmp)
endif()

install(TARGETS parserutils DESTINATION lib)
install(DIRECTORY include/parserutils DESTINATION include)
