set(PATTERN_FILES    # (found in the "patterns" folder) 
  data.raw 
  data2.raw 
  data_folder/data3.raw
) 

foreach( pattern_file ${PATTERN_FILES} ) 
  add_custom_command( 
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${pattern_file}" 
    COMMAND cmake -E copy 
"${CMAKE_CURRENT_SOURCE_DIR}/${pattern_file}" 
"${CMAKE_CURRENT_BINARY_DIR}/${pattern_file}" 
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${pattern_file}" 
  ) 
  list( APPEND pattern_files_dest 
"${CMAKE_CURRENT_BINARY_DIR}/${pattern_file}" ) 
endforeach( pattern_file ) 
add_custom_target( CopyPatterns ALL DEPENDS ${pattern_files_dest} ) 

foreach( pattern_file ${PATTERN_FILES} ) 
  get_filename_component( path_name "patterns/${pattern_file}" PATH ) 
  install( FILES "patterns/${pattern_file}" DESTINATION ${path_name} ) 
endforeach() 

