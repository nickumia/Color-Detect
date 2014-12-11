Color-Detect
============

C++ code using OpenCV to detect colors using image processing methods

This project was developed with the idea of uploading it onto a quadcopter.  Although the implementation on a quadcopter has
not been completed, we are working our hardest to get it up and "flying".

1. We use the OpenCV Library available for windows, mac and android at:  http://opencv.org/
      1.1. A setup for OpenCV on windows is outlined at:  http://kevinhughes.ca/tutorials/opencv-install-on-windows-with-codeblocks-and-mingw/
      
2. Once that is working, download the code found in the "Red Detect" folder and run it in CodeBlocks.

Note: If we need help with anything, dont hestitate to contact me at: nickumia6@gmail.com


3. The main part of the code deals with:

     3.1. Obtaining a camera view from a specified camera.
     
     3.2. Converting the RGB scheme to HSV to be able to better separate colors.
     
     3.3. Thresholding a camera feed between two chosen colors.
    
     3.4. Removing noise from images.
     
     3.5. Determining the center of the chosen colored object.
     
     3.6. Tracking it in real-time to provide location for a quadcopter or any mobile robot to follow.

