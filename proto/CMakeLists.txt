include(FetchContent)
FetchContent_Declare(
  gRPC
  GIT_REPOSITORY https://github.com/grpc/grpc
  GIT_TAG        v1.49.1
)
set(FETCHCONTENT_QUIET OFF)
FetchContent_MakeAvailable(gRPC)
include(FindProtobuf)
find_package(Protobuf REQUIRED)
#
# Protobuf/Grpc source files
#
set(PROTO_FILES
    buildle.proto
)

#
# Add Library target with protobuf sources
#
add_library(buildleproto ${PROTO_FILES})
target_link_libraries(buildleproto
    PUBLIC
        protobuf::libprotobuf
        grpc
        grpc++
)
target_include_directories(buildleproto PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

#
# Compile protobuf and grpc files in myproto target to cpp
#
protobuf_generate(TARGET buildleproto LANGUAGE cpp)
protobuf_generate(TARGET buildleproto LANGUAGE grpc GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc PLUGIN "protoc-gen-grpc=$<TARGET_FILE:grpc_cpp_plugin>")