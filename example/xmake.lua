
target("pub_sub_example")
    set_kind("binary")
    add_deps("ezcom")
    add_files("pub_sub/pub_sub.cpp")
    add_includedirs("$(projectdir)/include")
    add_links("ezcom", "zmq", "protobuf", "pthread")

target("req_req_example")
    set_kind("binary")
    add_deps("ezcom")
    add_files("req_rep/req_rep.cpp")
    add_includedirs("$(projectdir)/include")
    add_links("ezcom", "zmq", "protobuf", "pthread")