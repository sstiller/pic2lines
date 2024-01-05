# pic2lines

This is a program to generate line art from images.

Currently there is only a commandline tool with compile-time configuration.
A GUI is planned.

Target platform is GNU/Linux, I don't have MS Windows to test. However, I try to keep the software portable, so you could try to compile it for different platforms.


## Purpose
For me, this project is one of my playgrounds to test some C++ concepts and libraries, I never tried.  
For this reason, the code may
* not be well planned, internal and external interfaces may change any time
* be ugly (readability, maintainability, different half-implemented concepts))
* contain some bugs (as currently I am not in the mood of testing)
* 
   

Also, I want to play with my cheap chinese laser plotter a bit

Things I experiment with
* cmake
* gtest
* spdlog
* libjpeg
* boost.json
* g-code
* svg


Things I may want to test later
* boost.gil
* fltk


## Dependencies
* boost >= 1.75 (needed for boost.json)
   * in Ubuntu currently not available, you can add it with `sudo add-apt-repository ppa:mhier/libboost-latest`
* spdlog (logging)
* libjpeg (to load jpeg images, maybe replaced by boost.GIL in the future)


