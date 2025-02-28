# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(Embarca-Tuner C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(Embarca-Tuner Embarca-Tuner.c )

add_subdirectory(src)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

pico_set_program_name(Embarca-Tuner "Embarca-Tuner")
pico_set_program_version(Embarca-Tuner "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(Embarca-Tuner 1)
pico_enable_stdio_usb(Embarca-Tuner 1)

# Add the standard library to the build
target_link_libraries(Embarca-Tuner
        pico_stdlib)

# Add any user requested libraries
target_link_libraries(Embarca-Tuner 
    hardware_adc
    hardware_i2c
    hardware_pio
    hardware_pwm
)
pico_generate_pio_header(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/include/tunerPIO.pio)
pico_add_extra_outputs(Embarca-Tuner)

pico_enable_stdio_uart(${PROJECT_NAME} 1)
pico_enable_stdio_usb(${PROJECT_NAME} 1)

