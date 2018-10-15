# Automatic Landmarking of Body Shapes

Released code for the paper "Single-camera automatic landmarking of body shapes with an ensemble of regression trees". 
http://www.cys.cic.ipn.mx/ojs/index.php/CyS/article/view/2365/2109

This code is open-source and free for anyone to experiment further with it :)
If you publish any work that uses this software or refers to it in any way, please just cite us:

Trejo, K., Angulo, C. Single-camera automatic landmarking for people recognition with an ensemble of regression trees. "Computación y Sistemas", 2016, vol. 20, núm. 1, p. 19-28.

## Requisites

- Dlib 18.10
- Pre-trained people detector (object_detector.svm)
- Pre-trained body shape model (shape_predictor_180_body_landmarks.dat)
- Images containing people in front poses (640x480 size)

## How to use

1) Download and compile Dlib C++ Library (http://dlib.net/compile.html).
2) Copy *render_body_detections_abstract.h* and *render_body detections.h* files in dlib-18.10/dlib/image_processing folder.
3) Copy *body_landmark_detection_ex_timer.cpp* file in dlib-18.10/dlib/examples folder and generate the executable file in the dlib-18.10/dlib/build folder.
4) Once in the build folder, unzip *shape_predictor_180_body_landmarks.dat.zip* and *test_images.zip* to obtain the pre-trained body shape model as described and tuned in our paper, and a folder with the test images used in the same paper.
5) Copy *object_detector.svm* file to the build directory as well.
6) Run the software on this location with **./body_landmark_detection_ex_timer shape_model.dat karla_test/*.jpg**

You can visualize some aspects from the training process described in the paper here:
https://www.youtube.com/watch?v=zrJ43trD1rI

And the final results in:
https://www.youtube.com/watch?v=txJw4CeSCIw

## Re-training

Remember that if you intend to train a new shape model with Dlib's library, whatever the target might be, you must follow the guidelines under http://dlib.net/train_shape_predictor_ex.cpp.html and adjust the parameters according to your own problem. Same case for the object detector, one must refer to http://dlib.net/train_object_detector.cpp.html to retrain the detector for a different target with the help of Dlib's imglab tool.

## Contact

Please leave a comment in my YouTube channel or ResearchGate page* if you have any questions or require assistance of any kind. I'll be glad to help!

*https://www.researchgate.net/publication/301544464_Single-Camera_Automatic_Landmarking_for_People_Recognition_with_an_Ensemble_of_Regression_Trees/comments
