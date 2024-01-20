cmake_minimum_required(VERSION 3.5)

project(test-commands-3-templates LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(test-commands-3-templates main.cpp
)

include(GNUInstallDirs)
install(TARGETS test-commands-3-templates
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
