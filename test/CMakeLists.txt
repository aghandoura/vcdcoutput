message( STATUS ${CMAKE_SOURCE_DIR} )

include_directories( ${CMAKE_SOURCE_DIR}/src )

add_executable( AllTests
    AllTests.cpp
    VCD_OutTest.cpp
)

target_link_libraries( AllTests
    VCD_Out 
    gtest
    pthread
    ${Boost_LIBRARIES}
    ${CGAL_LIBRARIES}
)

add_custom_target(run_tests
    COMMAND ./AllTests
    DEPENDS AllTests
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

add_custom_target(run
    COMMAND gtkwave tst.vcd
    DEPENDS run_tests
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
