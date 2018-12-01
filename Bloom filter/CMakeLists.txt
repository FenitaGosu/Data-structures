cmake_minimum_required(VERSION 2.8)

project(BloomFilter)

file(GLOB files "*.h" "*.cpp")

add_executable(${PROJECT_NAME} ${files})
