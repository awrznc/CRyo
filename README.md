CRyo
===

[![Build](https://github.com/awrznc/CRyo/actions/workflows/build.yml/badge.svg)](https://github.com/awrznc/CRyo/actions/workflows/build.yml)

Commentation testing tool for C programming language.

## Install

### Package manager

```bash
# Debian 10
apt-get install -y wget
wget https://github.com/awrznc/CRyo/releases/latest/download/CRyo.deb
apt-get install -y ./CRyo.deb

# AlmaLinux 8
dnf install -y https://github.com/awrznc/CRyo/releases/latest/download/CRyo.rpm
```


### Self-build

Build it using CMake and build tools.

```bash
# Clone project.
git clone https://github.com/awrznc/CRyo.git

# Make build directory.
mkdir -p ./CRyo/build && cd ./CRyo/build

# Build project.
cmake .. -DCMAKE_BUILD_TYPE=Release && cmake --build .

# Install CRyo.
make install
```


## Usage

### CLI

```bash
cryo --import ./src/ --export ./build/
```


### CMake

`/foo/src/bar.h` :

~~~c
/**
  * Return zero.
  *
  * ```c
  * #include "bar.h"
  *
  * int main() {
  *     return bar();
  * }
  * ```
  **/
int bar() {
     return 0;
}
~~~

`/foo/CMakeLists.txt` :

```cmake
cmake_minimum_required(VERSION 3.10)
project(sample C)
enable_testing()

# cryo
include(/usr/share/cmake/cryo/CRyo.cmake)

cryo(
  IMPORT "${CMAKE_CURRENT_SOURCE_DIR}/src/"
  EXPORT "${CMAKE_BINARY_DIR}/test/"
  INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/src/"
)
```

Run command :

```
$ mkdir -p /foo/build && cd /foo/build && cmake .. && cmake --build .
$ ctest

Test project /foo
      Start  1: /foo/build/test/bar.hh:4
 1/1  Test  #1: /foo/build/test/bar.hh:4 ......   Passed    0.01 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.01 sec
```
