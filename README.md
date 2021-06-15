# vvchess

## Build

The code is built and tested at Ubuntu 21.04 with `gcc-11 (Ubuntu 11.1.0-1ubuntu1~21.04) 11.1.0` and [`cmake`](https://cmake.org/). The following shell commands do the job:

```sh
export CC=/usr/bin/gcc-11
export CXX=/usr/bin/g++-11
mkdir build; cd build
cmake ..
cmake --build .
ctest -V
```

The last command runs unit tests.
