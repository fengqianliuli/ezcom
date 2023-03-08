set_project("ezcom")
add_rules("mode.debug", "mode.release")
set_warnings("all", "error")
set_languages("c99", "c++14")
add_includedirs("$(projectdir)", "$(projectdir)/include", "$(projectdir)/src")
-- add_ldflags("-Wl,-Bstatic -lprotobuf -Wl,-Bdynamic -lzmq", {force = true})

target("ezcom")
    set_kind("shared")
    add_files("src/**.cpp")
    add_files("proto/gen/*.cc")
    add_links("zmq", "protobuf")
    add_syslinks("pthread")


target("simple")
    add_deps("ezcom")
    set_kind("binary")
    add_files("example/simple.cpp")
    add_links("protobuf", "zmq", "ezcom")
    add_syslinks("pthread")

