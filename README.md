# U-Shaped Gate Detection



The task is real-time detection of yellow and red u-shaped gates using ``C++`` and ``OpenCV`` library. The robot’s mission is to cross the yellow gates from above and 
pass through the red gates without any collision to score the relevant point successfully. If there are several gates, the algotithm choose the closer one for the robot to pass.


# Description


* We open the video camera to capture real-time frames
* Resize the frames to (320,240)
* Process each frame for the probability of gates existance using color and u-shaped gate detection algorithms
* Emit signals when the gate found
* Set up and down sigal based on the color of detected gate


#Requirements


* C++ Programming Language (version 11 or higher is suggested)
* OpenCV



