cmake_minimum_required( VERSION 3.12 )
project( infectious
	DESCRIPTION "Infectious Disease Executables"
  VERSION 1.0 )


set( SIMULATION_SOURCES 
    source/person.cpp 
    source/disease.cpp 
    source/population.cpp
    source/person.hpp 
    source/disease.hpp 
    source/population.hpp 
)

# first executable

add_executable( test )
target_sources( test PRIVATE tests/tests.cpp ${SIMULATION_SOURCES} )
target_compile_features( test PRIVATE cxx_std_23 )

target_include_directories( test PRIVATE source )

find_package( PkgConfig REQUIRED )
pkg_check_modules( CATCH2 REQUIRED catch2-with-main )
target_include_directories(
	test PUBLIC
	${CATCH2_INCLUDE_DIRS}
	)
target_link_directories(
	test PUBLIC
	${CATCH2_LIBRARY_DIRS}
	)
target_link_libraries(
	test PUBLIC
	${CATCH2_LIBRARIES}
	)


# second executable

add_executable( exp1 )
target_sources( exp1 PRIVATE experiments/experiment1.cpp ${SIMULATION_SOURCES} )
target_compile_features( exp1 PRIVATE cxx_std_23 )

target_include_directories( exp1 PRIVATE source )

# third executable

add_executable( exp2 )
target_sources( exp2 PRIVATE experiments/experiment2.cpp ${SIMULATION_SOURCES} )
target_compile_features( exp2 PRIVATE cxx_std_23 )
target_include_directories( exp2 PRIVATE source )

# fourth executable

add_executable( exp3 )
target_sources( exp3 PRIVATE experiments/experiment3.cpp ${SIMULATION_SOURCES} )
target_compile_features( exp3 PRIVATE cxx_std_23 )
target_include_directories( exp3 PRIVATE source )




install( TARGETS test exp1 exp2 exp3 DESTINATION . )
