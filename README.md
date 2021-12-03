#  Gate Detector (CPP + OpenCV)

Real-time **yellow** and **red** u-shaped gate detector using `C++` and `OpenCV` libraries.

### Problem definition
There are some U-shaped gates on the ground. A drone robot is assigned to cross the yellow gates from the above and pass through the red gates without any collision to the gates in order to score the relevant point successfully. 

**Note that if there are several gates, the algorithm chooses the closest to pass by the robot.**

<br/>


### Step-by-Step solution

- Capturing real-time frame stream by opening the camera
- Applying preliminary filters to the stream (such as resizing to 320 x 240)
- Processing each frame to check if the gates exist in the frame
- Emitting direction signals when the gate found, based on the color of the detected gate.


### Requirements
- C++ Programming Language (version >=11)
- OpenCV (version 2.4.13 is preferred)
- `QT Creator IDE`

<br/>

### Run


1. Download the repository by clicking on[ this link](https://github.com/kimiaf1998/U-Shaped-Gate-Detection/archive/refs/heads/master.zip " this link") then extract it, or clone it using:
```bash
git clone  https://github.com/kimiaf1998/U-Shaped-Gate-Detection.git
```

2. Open the repository in QT Creator
2. Click the Run button from the IDE or press `CTRL+R` to start the application.

<br/>

### Screenshots

| ![screen 1](https://github.com/kimiaf1998/U-Shaped-Gate-Detection/blob/master/screenshots/Screenshot%20from%202021-12-03%2017-47-23.png "screen 1")  | ![screen 2](https://github.com/kimiaf1998/U-Shaped-Gate-Detection/blob/master/screenshots/Screenshot%20from%202021-12-03%2017-47-48.png "screen 2")   |  ![screen 3](https://github.com/kimiaf1998/U-Shaped-Gate-Detection/blob/master/screenshots/Screenshot%20from%202021-12-03%2017-49-26.png "screen 3")  |
| ------------ | ------------ | ------------ |
|  ![screen 4](https://github.com/kimiaf1998/U-Shaped-Gate-Detection/blob/master/screenshots/Screenshot%20from%202021-12-03%2017-49-39.png "screen 4")  |  ![screen 5](https://github.com/kimiaf1998/U-Shaped-Gate-Detection/blob/master/screenshots/Screenshot%20from%202021-12-03%2017-48-47.png "screen 5	")  | ![screen 6](https://github.com/kimiaf1998/U-Shaped-Gate-Detection/blob/master/samples/20190301_153334.jpg "screen 6")  |
