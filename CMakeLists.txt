cmake_minimum_required (VERSION 3.8)

project (wav2mp3Converter)

file(GLOB SRCS "${PROJECT_SOURCE_DIR}/*.h" "${PROJECT_SOURCE_DIR}/*.cpp")
add_executable (wav2mp3Converter ${SRCS})

#pthread
if (MSVC)
	add_definitions(-DHAVE_STRUCT_TIMESPEC)
	
	set(PTHREADS_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/pthreads_w32)
	target_include_directories(wav2mp3Converter PRIVATE ${PTHREADS_ROOT}/include)
	
	get_filename_component(PTHREADS_LIB ${PTHREADS_ROOT}/lib REALPATH BASE_DIR "${PROJECT_SOURCE_DIR}")
	get_filename_component(PTHREADS_DLL ${PTHREADS_ROOT}/dll REALPATH BASE_DIR "${PROJECT_SOURCE_DIR}")
	if(CMAKE_SIZEOF_VOID_P EQUAL 8)
		target_link_libraries(wav2mp3Converter ${PTHREADS_LIB}/x64/pthreadVC2.lib)
		add_custom_command(
			TARGET wav2mp3Converter POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_if_different
			${PTHREADS_DLL}/x64/pthreadVC2.dll
			$<TARGET_FILE_DIR:wav2mp3Converter>)
	else()
		target_link_libraries(wav2mp3Converter ${PTHREADS_LIB}/x86/pthreadVC2.lib)
		add_custom_command(
			TARGET wav2mp3Converter POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_if_different
			${PTHREADS_DLL}/x86/pthreadVC2.dll
			$<TARGET_FILE_DIR:wav2mp3Converter>)
    endif()
else()
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
    target_link_libraries(wav2mp3Converter Threads::Threads)
endif()


#lame
add_subdirectory(lame-3.100)
target_include_directories(wav2mp3Converter PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lame-3.100/include)
target_link_libraries(wav2mp3Converter libmp3lame-static)
