cmake_minimum_required(VERSION 3.9)
project(chatAppTcp C)

set(CMAKE_C_STANDARD 99)

add_executable(chatAppTcp main.c server.c client.c)