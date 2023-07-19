
target("connect_event_test_client")
    set_kind("binary")
    add_deps("ezcom")
    add_files("connect_event_test_client.cpp")
    add_includedirs("$(projectdir)/include")
    add_links("ezcom", "zmq", "protobuf", "pthread")

target("connect_event_test_server")
    set_kind("binary")
    add_deps("ezcom")
    add_files("connect_event_test_server.cpp")
    add_includedirs("$(projectdir)/include")
    add_links("ezcom", "zmq", "protobuf", "pthread")