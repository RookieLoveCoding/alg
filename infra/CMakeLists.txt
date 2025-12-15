add_subdirectory(stack)

# add_library(infra_virtual OBJECT)
# target_link_libraries(infra_virtual PRIVATE
#     stack
# )

# add_library(infra STATIC $<TARGET_OBJECTS:infra_virtual>)
# target_include_directories(infra PUBLIC
#     stack/include/
# )