include_directories(.)

set(LSRCS
    yours/trie_path.cpp
)

add_library(yourslib STATIC ${LSRCS})

add_library(yoursdlib SHARED ${LSRCS})

target_compile_options(yoursdlib PUBLIC -fPIC)

install(TARGETS
    yourslib yoursdlib
    DESTINATION lib
)

set(SRCS
    yours.cpp
    yours_path.cpp yours_list.cpp
    yours/options.cpp
)

add_executable(yours ${SRCS})

target_compile_options(yours PUBLIC -pie -fPIE)

target_link_libraries(yours yourslib -lstdc++fs)

install(TARGETS
    yours
    DESTINATION bin
)
