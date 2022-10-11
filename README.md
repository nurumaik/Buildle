# Buildle
Guess the build system you will be using for your next C++ project. Like wordle, but with build systems

## Build and Execution

### Linux (mac should probably work as well)

#### Dependencies:
You should have C++ compiler, gnu build tools, libproto and cmake installed. Probably something else. Grpc is downloaded and installed by cmake itself so it isn't required

Example for ubuntu: `sudo apt install build-essential cmake libprotoc-dev`

#### Build (your favorite IDE with cmake support may work as well)
```bash
mkdir build && cd build
cmake -G "Unix Makefiles" -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DgRPC_PROTOBUF_PACKAGE_TYPE=CONFIG ..
cmake --build -j 9 .
```

#### Launch
Launch server first, then client(s) on the same PC

Server listens on localhost so you can't run this over network yet

(from `build` directory)
```sh
server/server # To start server
client/client # To start client
```

## References used to make this
* https://grpc.io/docs/what-is-grpc/introduction/ -- grpc basics
* https://developers.google.com/protocol-buffers/docs/proto3 -- protobuf specification
* https://github.com/avinassh/grpc-errors -- error handling
* https://github.com/faaxm/exmpl-cmake-grpc -- for usage with cmake and structure example
* https://github.com/faaxm/exmpl-cmake-grpc/issues/1#issuecomment-873905356 -- some guy here told to add `-DgRPC_PROTOBUF_PACKAGE_TYPE=CONFIG` and I'm still not sure whether it's necessary
* Lots of trial and error to find out why cmake won't build my proto files
* https://en.wikipedia.org/wiki/List_of_build_automation_software -- for word list