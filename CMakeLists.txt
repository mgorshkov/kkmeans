cmake_minimum_required(VERSION 3.5)
project(kkmeans VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

configure_file(version.h.in ${CMAKE_CURRENT_SOURCE_DIR}/version.h)

set(DEBUG_PRINT "0")

if (DEBUG_PRINT)
	message("DEBUG_PRINT is activated!")
	add_definitions(-DDEBUG_PRINT)
endif()

include_directories(dlib)
link_directories(dlib/dlib)

add_executable(kkmeans
	kkmeans.h
	kkmeans.cpp
	main.cpp)

set_target_properties(kkmeans PROPERTIES
	COMPILE_OPTIONS -Wpedantic -Wall -Wextra
	CMAKE_CXX_STANDARD 14
	CMAKE_CXX_STANDARD_REQUIRED ON
)

target_link_libraries(kkmeans
	${CMAKE_THREAD_LIBS_INIT}
	dlib
	png
)

install(TARGETS kkmeans DESTINATION bin)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/kkmeans_ex.txt DESTINATION /usr/local/share/)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/kkmeans_rnd.txt DESTINATION /usr/local/share/)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/sample.png DESTINATION /usr/local/share/)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/star.png DESTINATION /usr/local/share/)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT mikhail.gorshkov@gmail.com)

include(CPack)
