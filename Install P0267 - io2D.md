# Local setup for Udacity's CPPND Pathplanner project

## This is for Ubuntu 18.04 and its derivatives like Linux Mint.

## Update cmake
1. Make sure to get the newest `cmake` version. Minimum version is 3.11.3. And yes, this is required even if you change the CMakelists.txt to a lower version (the current cmake version from apt atm is 3.10)
    1. optional: uninstall cmake: `sudo apt remove cmake`
    2. download latest binary release (`.sh` file) from [here](https://cmake.org/download/)
    3. move file to `/opt`, e.g. `sudo mv ~/Downloads/cmake-3.16.0-Linux-x86_64.sh /opt`
    4. go to `/opt` and install cmake in this directory: `chmod u+x cmake-3.16.0-Linux-x86_64.sh` followed by `sudo ./cmake-3.16.0-Linux-x86_64.sh`
    5. link the installation to your `/usr/local/bin`: `sudo ln -s /opt/cmake-3.16.0-Linux-x86_64/bin/* /usr/local/bin`
    6. test that the correct version is installed with `cmake --version`
## Install dependencies
2. install dependencies:
    1. Refresh apt: `sudo apt update`
    2. Install GCC: `sudo apt install build-essential`
    3. Install Cairo: `sudo apt install libcairo2-dev`
    4. Install graphicsmagick: `sudo apt install libgraphicsmagick1-dev`
    5. Install libpng: `sudo apt install libpng-dev`
## Set up IO2D lib
3. build and install IO2D lib:
    1. clone repo `git clone --recurse-submodules https://github.com/cpp-io2d/P0267_RefImpl`
    2. enter dir and `mkdir build`
    3. comment out the last two build options for tests and samples in the `CMakeLists.txt`
    4. from the build directory run cmake: `cmake --config Release "-DCMAKE_BUILD_TYPE=Release" ..` (Release should be default, but just in case)
    5. compile with `make -j $number of your processor threads`
    6. install the library with `sudo make install`
## Project testbuild
4. clone and test the project repo
    1. clone repo with submodules `git clone --recurse-submodules https://github.com/udacity/CppND-Route-Planning-Project.git`
    2. enter local repo, `mkdir build`
    3. from build run cmake and make
    4. test build by running `./OSM_A_star_search`

![](https://i.redd.it/g68jjjamxwx31.jpg)
from [reddit](https://www.reddit.com/r/ProgrammerHumor/comments/duga41/how_it_really_looks/)