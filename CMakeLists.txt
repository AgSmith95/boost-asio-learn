cmake_minimum_required(VERSION 3.23)
project(boost-asio-learn)

find_package(asio REQUIRED)

set(SOURCE_FILES main.cpp)
set(EXECUTABLE_NAME boost-asio-learn)
add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})

set_target_properties(${EXECUTABLE_NAME} PROPERTIES
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED ON
)

target_link_libraries(${EXECUTABLE_NAME} asio::asio)

if(MSVC)
  target_compile_options(${EXECUTABLE_NAME} PRIVATE /W4 /WX)
else()
  target_compile_options(${EXECUTABLE_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
