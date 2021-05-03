![](https://github.com/edisonslightbulbs/traceless/blob/main/doc/figures/concept.png)

## 3DINTACT: Toolkit for segmenting interaction regions on tabletop surfaces

### Overview:

|   Platform |   Hardware	|  Dependencies 	|
|---	|---	|---	|
|   :white_square_button: Linux	|   :white_square_button: Azure Kinect 	| :white_square_button: [ gflags](https://github.com/gflags/gflags)	|
|| |  :white_square_button: [ glog ](https://github.com/google/glog)  	|
|| |  :white_square_button: [ Eigen 3.3 ](https://gitlab.com/libeigen/eigen.git) |
||| :white_square_button:  [ Azure Kinect SDK ](https://github.com/microsoft/Azure-Kinect-Sensor-SDK) |
||| :white_square_button:  [ opencv ](https://github.com/opencv/opencv) |
||| :white_square_button:  [ Pangolin ](https://github.com/stevenlovegrove/Pangolin) |

### [1/3] Getting started

***

Clone this repository using `--recurse-submodules` flag.

If already cloned without the `--recurse-submodules` flag,  use `git submodule update --init --recursive` to initialize the submodules.

### [2/3] Installing the dependencies

***

Make sure to install all the dependencies listed in the table. As a caveat, Microsoft's Azure Kinect has a ceremonious list dependencies. Be sure to install them all. 3 steps to help get started are given below:

###### 1. The depth engine

A dated [Depth Engine](https://github.com/microsoft/Azure-Kinect-Sensor-SDK/blob/develop/docs/depthengine.md) binary is provided and can be installed by running this [`install_depthengine.sh`](./scripts/) helper script. Please follow [ this hyperlink ](https://github.com/microsoft/Azure-Kinect-Sensor-SDK/blob/develop/docs/depthengine.md) for the official step-by-step on how to get the most up-to-date depth engine.

###### 2. The USB rules

For convenience, the USB rules can be installed by running this [`install_usb_rules.sh`](./scripts/) helper script.

###### 3. Shared system libraries

For convenience, run this [`install_kinect_sdk_dependencies.sh`](./scripts/) helper script to install the Kinect dependencies.

### [3/3] Building the project

***

1) from the project directory

```bash
mkdir build && cd build || return
cmake ..
make
```

2) from the project directory

```bash
# change to project binary directory
cd build/bin

# run target
./3DINTACT

# to stdout logs [ optional ]
# ./3DINTACT --logtostderr=1
```
* * *

This project uses Microsoft's Azure Kinect to form a concrete example. The point cloud data source can, of course, be changed as [needed](/doc/README.md).
The project documentation is under development, as is the project itself. Should one opt to try to use or contribute to the toolkit's development, we kindly ask for your patience with the official documentation. It goes without say, any issues, recommendations, and feature requests are more than welcome.
