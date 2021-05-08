CRyo
===

[![Build](https://github.com/awrznc/CRyo/actions/workflows/build.yml/badge.svg)](https://github.com/awrznc/CRyo/actions/workflows/build.yml)

Documentation testing tool for C programming language.

## Install

### Package manager

```bash
# Debian 10
apt-get install -y wget
wget https://github.com/awrznc/CRyo/releases/latest/download/CRyo.deb
apt-get install -y ./CRyo.deb

# CentOS 8
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

```cmake
cmake_minimum_required(VERSION 3.10)
project(sample C)

# cryo
include(${CMAKE_INSTALL_PREFIX}/share/cmake/cryo/CRyo.cmake)

cryo(
  IMPORT "${CMAKE_CURRENT_SOURCE_DIR}/src/"
  EXPORT "${CMAKE_BINARY_DIR}/test/"
)
```
