include_directories(.)

set(LSRCS
    yours/trie_path.cpp yours/term.cpp
    yours/sqlite.cpp yours/prolog.cpp
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
    yours_path.cpp yours_list.cpp yours_compile.cpp yours_sqlite
    yours/options.cpp
)

add_executable(yours ${SRCS})

target_compile_options(yours PUBLIC -pie -fPIE)

target_link_libraries(yours
    yourslib
    stdc++fs
    sqlite3
)

install(TARGETS
    yours
    DESTINATION bin
)
