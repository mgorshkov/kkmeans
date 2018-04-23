cmake_minimum_required(VERSION 3.5)
project(yamr VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

configure_file(version.h.in ${CMAKE_CURRENT_SOURCE_DIR}/version.h)

set(DEBUG_PRINT "0")

if (DEBUG_PRINT)
	message("DEBUG_PRINT is activated!")
	add_definitions(-DDEBUG_PRINT)
endif()

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
)

install(TARGETS kkmeans DESTINATION bin)
install(TARGETS sample.png DESTINATION bin)
install(TARGETS star.png DESTINATION bin)
install(TARGETS kkmeans_ex.txt DESTINATION bin)
install(TARGETS kkmeans_rnd.txt DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT mikhail.gorshkov@gmail.com)

include(CPack)
