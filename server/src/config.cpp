#include "config.h"

namespace BuildleGame {

const std::vector<std::string> Builds = {
    "cmake"s,
    "bazel"s,
    "conan"s,
    "ninja"s,
    "meson"s,
    "qmake"s,
    "scons"s,
    "maven"s,
    "nmake"s,
    "shake"s,
    // Ok not sure following ones can build C++
    "cabal"s,
    "stack"s,
    "crate"s,
    "boost"s,  // Boost.Build
    "grunt"s,  // We frontend now 
    "imake"s,  // Tf is this
};

}