# Automatic-Landmarking-of-Body-Shapes

Released code for the paper "Single-camera automatic landmarking of body shapes with an ensemble of regression trees". 
http://www.cys.cic.ipn.mx/ojs/index.php/CyS/article/view/2365/2109

This code is open-source and free for anyone to experiment further with it :)
If you publish any work that uses this software or refers to it in any way, please just cite us:

Trejo, K., Angulo, C. Single-camera automatic landmarking for people recognition with an ensemble of regression trees. "Computación y Sistemas", 2016, vol. 20, núm. 1, p. 19-28.

## Requisites:

-Dlib 18.10
-Shape model pre-trained (shape_predictor_180_body_landmarks.dat)
-Images containing people in front poses (640x480 size)

## How to use:

1) Download and compile Dlib C++ Library (http://dlib.net/compile.html).
2) Copy render_body_detections_abstract.h and render_body detections.h files in dlib-18.10/dlib/image_processing folder.
3) Copy body_landmark_detection_ex_timer.cpp file in dlib-18.10/dlib/examples folder and generate the executable file in the dlib-18.10/dlib/build folder.
4) In the build folder, unzip shape_predictor_180_body_landmarks.dat.zip and test_images.zip to obtain the pre-trained body shape model as described and tuned in our paper, and a folder with the test images used in the same paper.
5) Run the software on this location with ./body_landmark_detection_ex_timer shape_model.dat karla_test/*.jpg

You can visualize some aspects from the training process described in the paper here:
https://www.youtube.com/watch?v=zrJ43trD1rI

And the final results in:
https://www.youtube.com/watch?v=txJw4CeSCIw

## Contact:

Please leave a comment in my YouTube channel if you have any questions, require assistance or any extra files. 
I'll be glad to help!
