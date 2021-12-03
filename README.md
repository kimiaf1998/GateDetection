# U-Shaped Gate Detection



The task is real-time detecting of yellow and red u-shaped gates using ``C++`` and ``OpenCV`` library. The robot has a mission to cross the yellow gates from above and 
pass through the red gates without any collision to score the relevant point successfully. If there are several gates, the algorithm chooses the closest one for the robot to pass.



### Requirements


* C++ Programming Language (version 11 or higher is suggested)
* OpenCV




### Algorithm Steps


* Opening the video camera to capture real-time frames
* Resizing the frames to (320,240)
* Processing each frame for the probability of gates existence using color and u-shaped gate detection algorithms
* Emitting signals when the gate found
* Setting up-and-down signal based on the color of detected gate



### Run


1. Download the repository by clicking on[ this link](https://github.com/kimiaf1998/U-Shaped-Gate-Detection/archive/refs/heads/master.zip " this link") then extract it, or clone it using:
```bash
git clone  https://github.com/kimiaf1998/U-Shaped-Gate-Detection.git
```

2. Run the ``main.cpp`` file in your IDE



### Screenshots


