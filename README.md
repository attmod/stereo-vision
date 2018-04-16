Stereo Vision
============

A C++ [YARP](https://github.com/robotology/yarp) library that provides the **iCub** robot with stereo vision capabilities.

<a href="https://zenhub.com"><img src="https://raw.githubusercontent.com/ZenHubIO/support/master/zenhub-badge.png"></a>

## Installation

##### Dependencies
- [YARP](https://github.com/robotology/yarp)
- [iCub](https://github.com/robotology/icub-main)
- [icub-contrib-common](https://github.com/robotology/icub-contrib-common)
- [OpenCV](http://opencv.org/downloads.html) (**>=2.4** and with **SIFT** features available)
- [SiftGPU](http://cs.unc.edu/~ccwu/siftgpu) (optional but suggested for better performance)

We also make use of [libelas](http://www.cvlibs.net/software/libelas/) for computing
disparity maps, but there is no need to download it, since it is embedded inside the code.

## Documentation

Online documentation is available here: [http://robotology.github.com/stereo-vision](http://robotology.github.com/stereo-vision).

## License

Material included here is Copyright of _iCub Facility - Istituto Italiano di Tecnologia_ and is released under the terms of the GPL v2.0 or later. See the file LICENSE for details.
