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

add_executable(test_student
               tests/test_student.c
               src/student.c
               src/group.c
               src/utils.c
)

add_executable(test_student_groups
               tests/test_student_groups.c
               src/student.c
               src/group.c
               src/utils.c
)

add_executable(test_faculty
               tests/test_faculty.c
               src/university.c
               src/faculty.c
               src/group.c
               src/utils.c
)

add_executable(test_university
               tests/test_uni.c
               src/university.c
               src/faculty.c
               src/group.c
               src/utils.c
)   

target_include_directories(uni PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_include_directories(test_student PRIVATE 
                           ${CMAKE_SOURCE_DIR}/include
                           ${CHECK_INLCUDE_DIRS})

target_link_libraries(test_student PRIVATE ${CHECK_LIBRARIES})

target_include_directories(test_student_groups PRIVATE 
                           ${CMAKE_SOURCE_DIR}/include
                           ${CHECK_INLCUDE_DIRS})

target_link_libraries(test_student_groups PRIVATE ${CHECK_LIBRARIES})

target_include_directories(test_faculty PRIVATE 
                           ${CMAKE_SOURCE_DIR}/include
                           ${CHECK_INLCUDE_DIRS})

target_link_libraries(test_faculty PRIVATE ${CHECK_LIBRARIES})

target_include_directories(test_university PRIVATE 
                           ${CMAKE_SOURCE_DIR}/include
                           ${CHECK_INLCUDE_DIRS})

target_link_libraries(test_university PRIVATE ${CHECK_LIBRARIES})

target_compile_options(uni PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Wundef -Wcast-align)
target_compile_options(test_student PRIVATE ${CHECK_CFLAGS_OTHER})
target_compile_options(test_student_groups PRIVATE ${CHECK_CFLAGS_OTHER})
target_compile_options(test_faculty PRIVATE ${CHECK_CFLAGS_OTHER})
target_compile_options(test_university PRIVATE ${CHECK_CFLAGS_OTHER})