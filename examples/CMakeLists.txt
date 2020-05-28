#Sourced from pagmp
function(ADD_SYSID_PAGMO_TUTORIAL arg1)
    add_executable(${arg1} ${arg1}.cpp)
    target_link_libraries(${arg1} sysid_pagmo)
    target_compile_options(${arg1} PRIVATE
        "$<$<CONFIG:Debug>:${SYSID_PAGMO_CXX_FLAGS_DEBUG}>"
        "$<$<CONFIG:Release>:${SYSID_PAGMO_CXX_FLAGS_RELEASE}>"
        "$<$<CONFIG:RelWithDebInfo>:${SYSID_PAGMO_CXX_FLAGS_RELEASE}>"
        "$<$<CONFIG:MinSizeRel>:${SYSID_PAGMO_CXX_FLAGS_RELEASE}>"
    )
    # Let's setup the target C++ standard, but only if the user did not provide it manually.
    if(NOT CMAKE_CXX_STANDARD)
        set_property(TARGET ${arg1} PROPERTY CXX_STANDARD 14)
    endif()
    set_property(TARGET ${arg1} PROPERTY CXX_STANDARD_REQUIRED YES)
    set_property(TARGET ${arg1} PROPERTY CXX_EXTENSIONS NO)
    add_test(${arg1} ${arg1})
endfunction()

ADD_SYSID_PAGMO_TUTORIAL(test)