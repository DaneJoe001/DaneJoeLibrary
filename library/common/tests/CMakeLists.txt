cmake_minimum_required(VERSION 3.20)

add_executable(danejoe_common_demo
  "${CMAKE_CURRENT_LIST_DIR}/source/main.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/source/demo_common.cpp"
)

target_link_libraries(danejoe_common_demo PRIVATE DaneJoe::Commons)
target_include_directories(danejoe_common_demo PRIVATE
  "${CMAKE_CURRENT_LIST_DIR}/include"
)

add_test(NAME common.demo COMMAND danejoe_common_demo)
