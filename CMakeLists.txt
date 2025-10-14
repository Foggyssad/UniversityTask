cmake_minimum_required(VERSION 3.16)
project(uni C)
include(CTest)
find_package(PkgConfig REQUIRED)
pkg_check_modules(CHECK REQUIRED check)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(uni
               src/main.c
               src/university.c
               src/faculty.c
               src/group.c
               src/student.c
               src/utils.c
               src/app.c
               src/cli.c
)

set(TEST_SOURCES
    test_student
    test_student_groups
    test_faculty
    test_uni
)

target_include_directories(uni PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_compile_options(uni PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Wundef -Wcast-align)

foreach(t IN LISTS TEST_SOURCES)
    add_executable(${t}
        tests/${t}.c
        src/university.c
        src/faculty.c
        src/group.c
        src/student.c
        src/utils.c
    )
    target_include_directories(${t} PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CHECK_INCLUDE_DIRS}
    )

    target_link_libraries(${t} PRIVATE
        ${CHECK_LIBRARIES}
        m
        pthread
    )

    target_compile_options(${t} PRIVATE ${CHECK_CFLAGS_OTHER})

    add_test(NAME ${t} COMMAND ${t})

endforeach()