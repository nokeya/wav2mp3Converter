# CMakeList.txt : CMake project for wav2mp3Converter, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (wav2mp3Converter "main.cpp"  "fileUtils.cpp" "fileUtils.h" "platform.h" "platform.cpp" "posix_thread.cpp" "posix_thread.h")

if (MSVC)
	set(PTHREADS_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/pthreads_w32)
	
	target_include_directories(wav2mp3Converter PRIVATE ${PTHREADS_ROOT}/include)
	add_definitions(-DHAVE_STRUCT_TIMESPEC)

	get_filename_component(PTHREADS_LIB ${PTHREADS_ROOT}/lib REALPATH BASE_DIR "${PROJECT_SOURCE_DIR}")
	get_filename_component(PTHREADS_DLL ${PTHREADS_ROOT}/dll REALPATH BASE_DIR "${PROJECT_SOURCE_DIR}")
	if(CMAKE_SIZEOF_VOID_P EQUAL 8)
		#set_property(TARGET pthreads-win32 PROPERTY IMPORTED_IMPLIB "${PTHREADS_LIB}/x64/pthreadVC2.lib")
		#set_property(TARGET pthreads-win32 PROPERTY IMPORTED_LOCATION "${PTHREADS_LIB}/dll/x64/pthreadVC2.dll")
		#target_link_libraries(wav2mp3Converter ${PTHREADS_LIB}/x64/pthreadVC2.lib)
		#target_link_libraries(wav2mp3Converter ${PTHREADS_DLL}/x64/pthreadVC2.dll)
		#add_library(pthreads32 SHARED IMPORTED ${PTHREADS_DLL}/x64/pthreadVC2.dll)
		#target_link_libraries(wav2mp3Converter ${pthreads32})
	else()
		#target_link_libraries(wav2mp3Converter ${PTHREADS_LIB}/x86/pthreadVC2.lib)
	endif()
endif()

# TODO: Add tests and install targets if needed.
