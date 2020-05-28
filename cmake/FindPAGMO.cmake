if (PAGMO_INCLUDE_DIR)
    # in cache already
    set(PAGMO_FOUND TRUE)
    set(PAGMO_INCLUDE_DIRS "${PAGMO_INCLUDE_DIR}" )
    set(PAGMO_LIBRARIES "${PAGMO_LIBRARY}" )
else (PAGMO_INCLUDE_DIR)

    find_path(PAGMO_INCLUDE_DIR
            NAMES
            algorithm.hpp
            archipelago.hpp
            bfe.hpp
            config.hpp
            exceptions.hpp
            io.hpp
            island.hpp
            pagmo.hpp
            population.hpp
            problem.hpp
            rng.hpp
            s11n.hpp
            r_policy.hpp
            s_policy.hpp
            threading.hpp
            topology.hpp
            types.hpp
            type_traits.hpp
            PATHS
            /usr/include/pagmo
            /usr/local/include/pagmo
            )

    find_library( PAGMO_LIBRARY
            NAMES pagmo
            /usr/local/lib
            /usr/lib
            )


    set(PAGMO_INCLUDE_DIRS "${PAGMO_INCLUDE_DIR}" )
    set(PAGMO_LIBRARIES "${PAGMO_LIBRARY};${PAGMO_CXX_LIBRARY}" )

    include(FindPackageHandleStandardArgs)
    # handle the QUIETLY and REQUIRED arguments and set LIBCPLEX_FOUND to TRUE
    # if all listed variables are TRUE
    find_package_handle_standard_args(PAGMO DEFAULT_MSG PAGMO_LIBRARY  PAGMO_INCLUDE_DIR)

    mark_as_advanced(PAGMO_INCLUDE_DIR PAGMO_LIBRARY)

endif(PAGMO_INCLUDE_DIR)