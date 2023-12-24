cmake_minimum_required(VERSION 3.5)

project(squirrel-lsp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core)

add_subdirectory(external/qtlanguageserver)
add_subdirectory(external/squirrel)

qt_standard_project_setup()
qt_add_executable(squirrel-lsp)

file(GLOB SRC src/*.cpp src/*.h)
target_sources(squirrel-lsp PRIVATE ${SRC})

file(GLOB NUTS tests/*.nut) # Funny.
target_sources(squirrel-lsp PUBLIC ${NUTS})
source_group(Tests FILES ${NUTS})

link_qtlanguageserver(squirrel-lsp external/qtlanguageserver/src/languageserver/)
target_link_libraries(squirrel-lsp PRIVATE Qt::Core squirrel)

# Oh, don't mind me!
target_include_directories(squirrel-lsp PRIVATE external/squirrel/)
