project(ff_sim)

include_directories(/home/athrun/boost_1_53_0/)
include_directories(/home/athrun/projects/ff_sim)
link_directories(/home/athrun/boost_1_53_0/stage/lib)

add_executable(ff_sim main.cpp)

install(TARGETS ff_sim RUNTIME DESTINATION bin)
