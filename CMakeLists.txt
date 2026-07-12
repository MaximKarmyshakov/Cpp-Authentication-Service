cmake_minimum_required(VERSION 3.25)

project(
  cpp-auth-service
  VERSION 0.1.0
  DESCRIPTION "Production-ready C++ authentication service"
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(fmt CONFIG REQUIRED)
find_package(Crow CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(libpqxx CONFIG REQUIRED)

add_executable(
  cpp-auth-service
  src/main.cpp
  src/config/app_config.cpp
  src/database/database.cpp
)

target_include_directories(
  cpp-auth-service
  PRIVATE
    include
)

target_link_libraries(
  cpp-auth-service
  PRIVATE
    fmt::fmt
    Crow::Crow
    spdlog::spdlog
    libpqxx::pqxx
)