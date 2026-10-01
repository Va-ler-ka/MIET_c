if(NEWTON_USE_CATCH2)
    FetchContent_Declare(
        catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.16.0
    )
    FetchContent_MakeAvailable(catch2)

    add_executable(numerics_tests_catch2
        catch2/test_bisection_catch2.cpp
    )
    target_link_libraries(numerics_tests_catch2 PRIVATE
        numerics_core
        Catch2::Catch2WithMain
    )

    list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
    include(Catch)
    catch_discover_tests(numerics_tests_catch2)
endif()

if(NEWTON_USE_GTEST)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.17.0
    )
    FetchContent_MakeAvailable(googletest)

    add_executable(numerics_tests_gtest
        gtest/test_bisection_gtest.cpp
    )
    target_link_libraries(numerics_tests_gtest PRIVATE
        numerics_core
        GTest::gtest_main
    )

    include(GoogleTest)
    gtest_discover_tests(numerics_tests_gtest)
endif()
