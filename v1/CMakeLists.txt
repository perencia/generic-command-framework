cmake_minimum_required(VERSION 3.5)

project(commands LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(commands main.cpp


    json_parser.h
    commands.h
    common.h
    commandDoA.h
    message.h  )

include(GNUInstallDirs)
install(TARGETS commands
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
