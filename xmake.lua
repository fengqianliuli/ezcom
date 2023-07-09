set_project("ezcom")
add_rules("mode.debug", "mode.release")
set_defaultmode("release")
set_warnings("all", "error")
set_languages("c99", "c++14")

add_includedirs("/usr/local/include")
add_linkdirs("/usr/local/lib")

target("ezcom")
    set_kind("shared")
    add_files("src/**.cpp", "proto/gen/**.cc")
    add_includedirs("$(projectdir)", "$(projectdir)/include", "$(projectdir)/src")
    add_links("zmq", "protobuf", "pthread")
    before_build(function (target)
        os.run("protoc -I=proto/raw --cpp_out=proto/gen ezcom.proto")
        os.exec("echo 'generate ezcom.proto file done'")
    end)

target("ezcom_test")
    set_kind("binary")
    add_deps("ezcom")
    add_files("test/test.cpp")
    add_includedirs("$(projectdir)/include")
    add_links("ezcom", "protobuf", "pthread")

