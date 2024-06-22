# pic2lines

![Build Status](https://github.com/sstiller/pic2lines/actions/workflows/ci.yml/badge.svg)

This is a program to generate line art from images.

Target platform is GNU/Linux. I don't have MS Windows to test. However, I try to keep the software portable, so you could try to compile it for different platforms.


## Purpose
For me, this project is one of my playgrounds to test some C++ concepts and libraries, I never tried.  
For this reason, the code may
* not be well planned, internal and external interfaces may change any time
* be ugly (readability, maintainability, different half-implemented concepts))
* contain some bugs (as currently I am not in the mood of testing)   

Also, I want to play with my cheap chinese laser plotter a bit

### Libraries I experiment with
* [ ] boost.gil
* [x] boost.json
* [x] fltk
* [x] gtest
* [x] libjpeg
* [x] spdlog

### Other things I experiment with
* gitlab CI
* [x] g-code
* [x] svg
* [x] cmake
* [x] Replaceable GUI framework (abstract GUI interface)
* [ ] design for testability
* [ ] new C++ features
* Different IDEs
   * [x] Qt creator
   * [ ] Clion
   * [ ] Eclipse cdt

## Dependencies
* boost >= 1.77 (needed for boost.json)
   * in Ubuntu currently not available, you can add it with `sudo add-apt-repository ppa:mhier/libboost-latest`
* spdlog (logging)
* libjpeg (to load jpeg images, maybe replaced by boost.GIL in the future)
* fltk
* for tests: libgtest

## Build
1. Go to the main project dir
2. `mkdir build`
3. `cd build`
4. `cmake ..`
   * if you want to build tests, call `cmake -DBUILD_TESTS=ON ..` instead
5. `make -j8`
   * instead of 8, you can use the number of processors on you build system
6. `./pic2lines`

