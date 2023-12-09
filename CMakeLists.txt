cmake_minimum_required(VERSION 3.5)

project(generic-command-framework_II LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(generic-command-framework_II main.cpp
    command.h
    processor.h

    jsondoc.h
    loradoc.h
    doc_type_traits.h

    IProcessor.h

    command_container.h
    command2.h
    command3.h )

include(GNUInstallDirs)
install(TARGETS generic-command-framework_II
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
