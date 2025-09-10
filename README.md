# Fooyin MSU-1 Plugin

**Fooyin MSU-1 Plugin** is a CMake project that automatically downloads and builds **Fooyin** and integrates the `msuinput` plugin into the Fooyin source tree.

## Requirements

- CMake ≥ 3.16  
- Git  
- A C++ compiler (tested with GCC 15.2.1)  

## Dependencies

Before building this project, make sure you have all dependencies required by Fooyin.  
See the [Fooyin build instructions](https://github.com/fooyin/fooyin/blob/master/BUILD.md) for detailed steps on installing libraries and setting up your build environment.

## Build Instructions

#### Clone this repository
```bash
git clone https://github.com/Vo1dTear/fooyin-msuinput.git
cd fooyin-msuinput
```

#### Create a build directory and navigate into it
```bash
mkdir build && cd build
```
#### Configure the project with CMake
```bash
cmake ..
```

#### Build Fooyin along with the msuinput plugin
```
cmake --build . -- -j$(nproc)
```

After building, the compiled plugin `fyplugin_msuinput.so` will be placed in the root of this repository
## Installing the Plugin

There are two ways to install the MSU-1 plugin:

1. **Manual installation:**  
Copy the plugin to your local Fooyin plugins directory:
```bash
   cp fyplugin_msuinput.so ~/.local/lib/fooyin/plugins/
```

2. **Install from Fooyin GUI:**  
Open Fooyin, then go to **Settings → Plugins → Install...**, and select `fyplugin_msuinput.so` from your project folder.
