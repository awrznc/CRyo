CRyo
===

Documentation testing tool for C programming language.

## Install

### Package manager

```bash
# Debian 10
apt-get install -y https://github.com/awrznc/CRyo/releases/latest/download/CRyo-0.0.1-Linux.deb

# CentOS 8
dnf install -y https://github.com/awrznc/CRyo/releases/latest/download/CRyo-0.0.1-Linux.rpm
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
