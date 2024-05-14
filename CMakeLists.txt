cmake_minimum_required(VERSION 3.10)
project(Minesweeper)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#set(SFML_DIR "C:/Users/myper/source/repos/2dminesweeper/external/SFML-2.6.1/lib/cmake/SFML")

find_package(SFML COMPONENTS graphics window system CONFIG REQUIRED)

set(SOURCES 
	${CMAKE_CURRENT_SOURCE_DIR}/source/main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/source/GamePlay.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/source/GameField.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/source/Enums.h
	${CMAKE_CURRENT_SOURCE_DIR}/source/GameField.h
	${CMAKE_CURRENT_SOURCE_DIR}/source/GamePlay.h

)

add_executable(Minesweeper ${SOURCES})

target_include_directories(Minesweeper PRIVATE ${SFML_INCLUDE_DIRS})
target_link_libraries(Minesweeper PRIVATE sfml-graphics sfml-window sfml-system)
