add_library(VCD_Out
	VCD_Out.cpp
)

add_executable( VCD_Main
    # Add source files here
    VCD_Main.cpp
)

target_link_libraries( VCD_Main
    # Add libraries here
    VCD_Out
    ${Boost_LIBRARIES}
    ${CGAL_LIBRARIES}
)
