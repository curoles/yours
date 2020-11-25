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
)

add_executable(yours ${SRCS})

target_compile_options(yours PUBLIC -pie -fPIE)

install(TARGETS
    yours
    DESTINATION bin
)
