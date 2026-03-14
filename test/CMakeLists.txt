include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.1
)

set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
set(BUILD_GMOCK   OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME}.test
  AllTests.cpp
  tests.cpp)

target_link_libraries(${PROJECT_NAME}.test
  ST-2
  gtest
  gtest_main
  pthread)

target_include_directories(${PROJECT_NAME}.test
  PUBLIC ${${PROJECT_NAME}_SOURCE_DIR}/include)

target_compile_definitions(${PROJECT_NAME}.test
  PRIVATE TEST_DIR="${CMAKE_CURRENT_LIST_DIR}")

install(TARGETS ${PROJECT_NAME}.test
        DESTINATION "${tool_dest}")