PROJECT(detours)

#SET(CMAKE_VS_NUGET_PACKAGE_RESTORE TRUE)

SET(SOURCES creatwth.cpp
			detours.cpp
			detours.h
			detver.h
			disasm.cpp
			#disolarm.cpp
			#disolarm64.cpp
			#disolia64.cpp
			#disolx86.cpp
			disolx64.cpp
			image.cpp
			modules.cpp
	)

ADD_LIBRARY(detours ${SOURCES})

set_target_properties(detours PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
target_compile_definitions(detours PRIVATE "-D_AMD64_" "-D_UNICODE")
add_definitions(-D_UNICODE /EHsc)
