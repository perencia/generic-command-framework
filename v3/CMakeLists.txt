cmake_minimum_required(VERSION 3.5)

project(test-commands-3-templates LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(test-commands-3-templates main.cpp
    command_container.h
    App.h
    command.h
    main.cpp
    StorageManager.h)

include(GNUInstallDirs)
install(TARGETS test-commands-3-templates
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
