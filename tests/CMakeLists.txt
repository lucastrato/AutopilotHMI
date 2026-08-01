find_package(GTest REQUIRED)

add_executable(UnitTests
    HeadingControllerTest.cpp
    AutopilotControllerTest.cpp
    MockDriver.h
    MockObserver.h
)

target_link_libraries(UnitTests PRIVATE
    AutopilotCore
    GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(UnitTests)