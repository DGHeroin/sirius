function(decare_lua_module module_name)
    aux_source_directory(${SOURCE_DIR}/extends/${module_name} MODULE_SRC_LIST)

    add_library (${module_name} SHARED ${MODULE_SRC_LIST})
    target_link_libraries(${module_name} libsirius) # all ext module dep on libsirius
    set(DEP_LIBRARIES ${DEP_LIBRARIES} echo)
endfunction()

decare_lua_module(echo)
