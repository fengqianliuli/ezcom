set_project("ezcom")
add_rules("mode.debug", "mode.release")
set_defaultmode("release")
set_warnings("all", "error")
set_languages("c99", "c++14")

target("ezcom")
    set_kind("shared")
    add_files("src/**.cpp|message.cpp")
    add_includedirs("$(projectdir)/include", "$(projectdir)/src")
    add_links("zmq", "pthread")

target("ezcom_test")
    set_kind("binary")
    add_deps("ezcom")
    add_files("example/test.cpp")
    add_includedirs("$(projectdir)/include")
    add_links("ezcom", "pthread")

