cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(thermometer_project)

pico_sdk_init()

add_executable(thermo
        thermo.c
        )

target_link_libraries(thermo pico_stdlib hardware_adc)

# create map/bin/hex file etc.
pico_add_extra_outputs(thermo)

pico_enable_stdio_usb(thermo 1)
