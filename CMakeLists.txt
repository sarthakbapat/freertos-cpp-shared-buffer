cmake_minimum_required(VERSION 3.19)
project(FreeRTOS_Shared_Data)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/FreeRTOS-kernel/include
    ${CMAKE_SOURCE_DIR}/FreeRTOS-kernel/portable/ThirdParty/GCC/Posix
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/inc
    ${CMAKE_SOURCE_DIR}
)

# Source files
set(SRC
    src/main.cpp
    src/SharedBuffer.cpp
    src/Sensor.cpp
    inc/SensorUtility.hpp
    inc/SharedBuffer.hpp
    inc/Sensor.hpp
    FreeRTOS-kernel/tasks.c
    FreeRTOS-kernel/list.c
    FreeRTOS-kernel/queue.c
    FreeRTOS-kernel/timers.c
    FreeRTOS-kernel/event_groups.c
    FreeRTOS-kernel/portable/MemMang/heap_4.c
    FreeRTOS-kernel/portable/ThirdParty/GCC/Posix/port.c
    FreeRTOS-kernel/portable/ThirdParty/GCC/Posix/utils/wait_for_event.c
)

add_executable(freertos_shared_data ${SRC})

# Link POSIX threads (required)
target_link_libraries(freertos_shared_data pthread)
