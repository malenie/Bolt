############################################################################                                                                                     
#   � 2012,2014 Advanced Micro Devices, Inc. All rights reserved.                                     
#                                                                                    
#   Licensed under the Apache License, Version 2.0 (the "License");   
#   you may not use this file except in compliance with the License.                 
#   You may obtain a copy of the License at                                          
#                                                                                    
#       http://www.apache.org/licenses/LICENSE-2.0                      
#                                                                                    
#   Unless required by applicable law or agreed to in writing, software              
#   distributed under the License is distributed on an "AS IS" BASIS,              
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.         
#   See the License for the specific language governing permissions and              
#   limitations under the License.                                                   

############################################################################                                                                                     

# List the names of common files to compile across all platforms
set( clBolt.Test.Iterator.Transform.Source ${BOLT_CL_TEST_DIR}/common/stdafx.cpp 
                             TransformIteratorTest.cpp )
set( clBolt.Test.Iterator.Transform.Headers   ${BOLT_CL_TEST_DIR}/common/stdafx.h 
                                ${BOLT_CL_TEST_DIR}/common/targetver.h 
                                ${BOLT_INCLUDE_DIR}/bolt/cl/iterator/transform_iterator.h )

set( clBolt.Test.Iterator.Transform.Files ${clBolt.Test.Iterator.Transform.Source} ${clBolt.Test.Iterator.Transform.Headers} )

# Set project specific compile and link options
if( MSVC )
set( CMAKE_CXX_FLAGS "-bigobj ${CMAKE_CXX_FLAGS}" )
                set( CMAKE_C_FLAGS "-bigobj ${CMAKE_C_FLAGS}" )
endif()

add_executable( clBolt.Test.Iterator.Transform ${clBolt.Test.Iterator.Transform.Files} )

if(BUILD_TBB)
    target_link_libraries( clBolt.Test.Iterator.Transform clBolt.Runtime ${OPENCL_LIBRARIES} ${GTEST_LIBRARIES} ${Boost_LIBRARIES}  ${TBB_LIBRARIES} )
else (BUILD_TBB)
    target_link_libraries( clBolt.Test.Iterator.Transform clBolt.Runtime ${OPENCL_LIBRARIES} ${GTEST_LIBRARIES} ${Boost_LIBRARIES}  )
endif()

set_target_properties( clBolt.Test.Iterator.Transform PROPERTIES VERSION ${Bolt_VERSION} )
set_target_properties( clBolt.Test.Iterator.Transform PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/staging" )

set_property( TARGET clBolt.Test.Iterator.Transform PROPERTY FOLDER "Test/OpenCL")

# CPack configuration; include the executable into the package
install( TARGETS clBolt.Test.Iterator.Transform
    RUNTIME DESTINATION ${BIN_DIR}
    LIBRARY DESTINATION ${LIB_DIR}
    ARCHIVE DESTINATION ${LIB_DIR}/import
    )
