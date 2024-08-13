cmake_minimum_required(VERSION 3.21) # cmake最低版本  3.15以上才支持armcc
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_SYSTEM_PROCESSOR arm) # 目标平台处理器为arm

set(CPU Cortex-M4)

set(CMAKE_C_FLAGS "--cpu=${CPU}  --c99")
set(CMAKE_CXX_FLAGS "--cpu=${CPU} --cpp11")
set(CMAKE_ASM_FLAGS "--cpu=${CPU} -c")

project(template C CXX ASM)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(--thumb)

include_directories(
    ${PROJECT_SOURCE_DIR}/CMSIS
    ${PROJECT_SOURCE_DIR}/Code
    ${PROJECT_SOURCE_DIR}/User
    ${PROJECT_SOURCE_DIR}/STM32F4_HALLIB/Inc
    ${PROJECT_SOURCE_DIR}/STM32F4_HALLIB/Inc/Legacy
)

add_compile_definitions(USE_HAL_DRIVER STM32F429xx) # 定义全局宏

# add_compile_definitions(__EVAL)
# add_link_options(--cpu Cortex-M4.fp.sp *.o --library_type=microlib --strict --summary_stderr --info summarysizes --map --xref --callgraph --symbols --info sizes --info totals --info unused --info veneers -o ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.axf)

add_link_options(--branchpatch=sdcomp-29491-629360 --strict --summary_stderr 
                 --info sizes,totals,unused,veneers --load_addr_map_info --xref --callgraph --symbols)
add_link_options(--scatter=${CMAKE_SOURCE_DIR}/Project/Obj/${PROJECT_NAME}.sct)

add_compile_options(--apcs=interwork --split_sections)

file(GLOB_RECURSE SOURCES
    "${PROJECT_SOURCE_DIR}/Startup/startup_stm32f429xx.s"
    "${PROJECT_SOURCE_DIR}/Code/*.c"
    "${PROJECT_SOURCE_DIR}/STM32F4_HALLIB/Src/*.c"
    "${PROJECT_SOURCE_DIR}/STM32F4_HALLIB/Src/Legacy/*.c"
    "${PROJECT_SOURCE_DIR}/User/*.c")

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES}
)

set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${ARMCC_FROMELF} --text -z $<TARGET_FILE:${PROJECT_NAME}>
    COMMENT "Print memory info")
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${ARMCC_FROMELF} --output ${HEX_FILE} --i32 $<TARGET_FILE:${PROJECT_NAME}>
    COMMAND ${ARMCC_FROMELF} --output ${BIN_FILE} --bin $<TARGET_FILE:${PROJECT_NAME}>
    COMMENT "Building ${HEX_FILE} and ${BIN_FILE}")
