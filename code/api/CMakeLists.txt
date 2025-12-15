add_library(hal_api STATIC
    src/hal_api.c
)

target_link_libraries(hal_api PRIVATE
    stack
)
target_include_directories(hal_api PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
)