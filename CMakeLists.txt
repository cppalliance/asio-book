# Copyright (c) 2023 Klemens D. Morgenstern
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

# this is to get writing, don't @ me.

cmake_minimum_required(VERSION 3.12...3.20)

project(asio-book VERSION 0.1 LANGUAGES CXX)

find_package(Boost REQUIRED system)
include_directories(${Boost_INCLUDE_DIRS})

if(${CMAKE_SYSTEM_NAME} STREQUAL Linux)
    find_path(LIBURING_INCLUDE_DIR NAMES liburing.h)
    mark_as_advanced(LIBURING_INCLUDE_DIR)

    find_library(LIBURING_LIBRARY NAMES uring)
    mark_as_advanced(LIBURING_LIBRARY)

    if (NOT LIBURING_LIBRARY STREQUAL LIBURING_LIBRARY-NOTFOUND)
        include_directories(${LIBURING_INCLUDE_DIR})
        link_libraries(${LIBURING_LIBRARY})
        add_definitions(-DBOOST_ASIO_HAS_IO_URING=1)
    endif()
endif()

add_custom_target(01_sync_examples)
file(GLOB_RECURSE 01_sync_examples_sources book/01_sync/code/*.cpp)
foreach(example_src ${01_sync_examples_sources})
    get_filename_component(example ${example_src} NAME_WE)
    add_library(01_sync_${example} ${example_src})
    add_dependencies(01_sync_examples 01_sync_${example})
endforeach ()


file(GLOB_RECURSE ADOC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/book *.adoc)
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/book/index.html
                   COMMAND asciidoctor ${CMAKE_CURRENT_SOURCE_DIR}/book/index.adoc --require asciidoctor-diagram --require asciidoctor-multipage -b multipage_html5  -o ${CMAKE_CURRENT_BINARY_DIR}/book/index.html
                   DEPENDS ${ADOC_FILES})
add_custom_target(asio_book_html DEPENDS  ${CMAKE_CURRENT_BINARY_DIR}/book/index.html)

file(GLOB_RECURSE ADOC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/book *.adoc)
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/book.pdf
                   COMMAND asciidoctor-pdf ${CMAKE_CURRENT_SOURCE_DIR}/book/index.adoc --require asciidoctor-diagram --require asciidoctor-pdf -o ${CMAKE_CURRENT_BINARY_DIR}/book.pdf
                   DEPENDS ${ADOC_FILES})
add_custom_target(asio_book_pdf DEPENDS  ${CMAKE_CURRENT_BINARY_DIR}/book.pdf)
