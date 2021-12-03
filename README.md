#  Gate Detection

Real-time **yellow** and **red** u-shaped gate detector using `C++` and `OpenCV` libraries.

### Problem definition
There are some U-shaped gates on the ground. A drone robot is assigned to cross the yellow gates from above and pass through the red gates without any collision to the gates in order to score the relevant point successfully. 

**Note that if there are several gates, the algorithm chooses the closest to pass by the robot.**



### Step-by-Step solution

- Capturing real-time frame stream by opening the camera
- Applying preliminary filters to the stream (such as resizing to 320 x 240)
- Processing each frame to check if the gates exist in the frame
- Emitting direction signals when the gate found, based on the color of the detected gate.



### Requirements
- C++ Programming Language (version >=11)
- OpenCV (version 2.4.13 is preferred)
- `QT Creator IDE`



### Run


1. Download the repository by clicking on[ this link](https://github.com/kimiaf1998/U-Shaped-Gate-Detection/archive/refs/heads/master.zip " this link") then extract it, or clone it using:
```bash
git clone  https://github.com/kimiaf1998/U-Shaped-Gate-Detection.git
```

2. Open the repository in QT Creator
3. Click the Run button from the IDE or press `CTRL+R` to start the application
4. Change yellow and red HSV threshold by relevant sliders




### Screenshots

| <img src="https://github.com/kimiaf1998/U-Shaped-Gate-Detection/blob/master/screenshots/Screenshot%20from%202021-12-03%2017-47-23.png" width="240">  | <img src="https://github.com/kimiaf1998/U-Shaped-Gate-Detection/blob/master/screenshots/Screenshot%20from%202021-12-03%2017-47-48.png" width="240">  |  <img src="https://github.com/kimiaf1998/U-Shaped-Gate-Detection/blob/master/screenshots/Screenshot%20from%202021-12-03%2017-49-26.png" width="240"> |
| ------------ | ------------ | ------------ |
| <img src="https://github.com/kimiaf1998/U-Shaped-Gate-Detection/blob/master/screenshots/Screenshot%20from%202021-12-03%2017-49-39.png" width="240"> | <img src="https://github.com/kimiaf1998/U-Shaped-Gate-Detection/blob/master/screenshots/Screenshot%20from%202021-12-03%2017-48-47.png" width="240"> | <img src="https://github.com/kimiaf1998/U-Shaped-Gate-Detection/blob/master/samples/20190301_153334.jpg" width="240"> |
