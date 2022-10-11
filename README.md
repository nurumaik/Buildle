# Buildle
Guess the build system you will be using for your next C++ project. Like wordle, but with build systems

## Build and Execution

### Linux

You should have C++ compiler, gnu build tools, libproto and cmake installed. Probably something else

```bash
mkdir
cmake -G "Unix Makefiles" -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DgRPC_PROTOBUF_PACKAGE_TYPE=CONFIG ..
```

## References used
* https://grpc.io/docs/what-is-grpc/introduction/ -- grpc basics
* https://developers.google.com/protocol-buffers/docs/proto3 -- protobuf specification
* https://github.com/avinassh/grpc-errors -- error handling
* https://github.com/faaxm/exmpl-cmake-grpc -- for usage with cmake and structure example
* https://en.wikipedia.org/wiki/List_of_build_automation_software -- for word list