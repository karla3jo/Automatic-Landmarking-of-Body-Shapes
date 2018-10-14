// The contents of this file are in the public domain. See LICENSE_FOR_EXAMPLE_PROGRAMS.txt
/*

    This program shows how to find frontal human body shapes in an image and
    estimate their pose, based on the face_landmark_detection example from Dlib's library.  
    The pose takes the form of 180 landmarks. These are points on the whole body contour 
    starting from the center of the head, without taking the hair into account.  
    
    The human-shape detector presented here is made using the classic Histogram of 
    Oriented Gradients (HOG) feature combined with a linear classifier, an image pyramid,
    and sliding window detection scheme. The pose estimator was created by using Dlib's 
    implementation of the paper:
        One Millisecond Face Alignment with an Ensemble of Regression Trees by
        Vahid Kazemi and Josephine Sullivan, CVPR 2014
    and was trained on our own body landmark dataset created with only four
    handmarked images. 

    Also, note that you can train your own models using Dlib's machine learning
    tools. See train_shape_predictor_ex.cpp to see an example.

    Finally, note that the face detector is fastest when compiled with at least
    SSE2 instructions enabled.  So if you are using a PC with an Intel or AMD
    chip then you should enable at least SSE2 instructions.  If you are using
    cmake to compile this program you can enable them by using one of the
    following commands when you create the build project:
        cmake path_to_dlib_root/examples -DUSE_SSE2_INSTRUCTIONS=ON
        cmake path_to_dlib_root/examples -DUSE_SSE4_INSTRUCTIONS=ON
        cmake path_to_dlib_root/examples -DUSE_AVX_INSTRUCTIONS=ON
    This will set the appropriate compiler options for GCC, clang, Visual
    Studio, or the Intel compiler.  If you are using another compiler then you
    need to consult your compiler's manual to determine how to enable these
    instructions.  Note that AVX is the fastest but requires a CPU from at least
    2011.  SSE4 is the next fastest and is supported by most current machines.  
*/

#include <dlib/image_processing/render_body_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <iostream>

#include <dlib/svm_threaded.h>
#include <dlib/string.h>
#include <dlib/data_io.h>
#include <dlib/cmd_line_parser.h>

#include <fstream>

#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

using namespace dlib;
using namespace std;

// ----------------------------------------------------------------------------------------

int main(int argc, char** argv)
{  
    try
    {
        // This example takes in a shape model file and then a list of images to
        // process.  We will take these filenames in as command line arguments.
        // Dlib comes with example images in the examples/faces folder so give
        // those as arguments to this program.
        if (argc == 1)
        {
            cout << "Call this program like this:" << endl;
            cout << "./body_landmark_detection_ex shape_model.dat bodies/*.jpg" << endl;
            cout << "\nYou can get the shape_model.dat file from:\n";
            cout << "Automatic-Landmarking-of-Body-Shapes/shape_predictor_180_body_landmarks.dat.zip" << endl;            
            return 0;
        }

        // We need a people detector.  We will use this to get bounding boxes for
        // each body in an image.

        typedef scan_fhog_pyramid<pyramid_down<6> > image_scanner_type; 
        image_scanner_type scanner;
        ifstream fin("object_detector.svm", ios::binary);
        if (!fin)
        {
            cout << "Can't find a trained object detector file object_detector.svm. " << endl;
            cout << "You need to train one using the -t option." << endl;
            cout << "\nTry the -h option for more information." << endl;
            return EXIT_FAILURE;

        }
        object_detector<image_scanner_type> detector2;
        deserialize(detector2, fin);
        // And we also need a shape_predictor.  This is the tool that will predict body
        // landmark positions given an image and people bounding box.  Here we are just
        // loading the model from the .dat file you gave as a command line argument.
        shape_predictor shape_model;
        deserialize(argv[1]) >> shape_model;

        image_window win;
        // Loop over all the images provided on the command line.
        for (int i = 2; i < argc; ++i)
        {
            cout << "processing image " << argv[i] << endl;

//            cout << "Starting timer..." << endl;

            struct timeval start, end;
            long mtime, seconds, useconds;
            gettimeofday(&start, NULL);

            array2d<rgb_pixel> img;
            load_image(img, argv[i]);

            // Now tell the people detector to give us a list of bounding boxes
            // around all the bodies in the image.
            std::vector<rectangle> dets = detector2(img);
            cout << "Number of bodies detected: " << dets.size() << endl;

            // Now we will go ask the shape_predictor to tell us the pose of
            // each body we detected.
            std::vector<full_object_detection> shapes;
            for (unsigned long j = 0; j < dets.size(); ++j)
            {
                full_object_detection shape = shape_model(img, dets[j]);
                cout << "number of parts: "<< shape.num_parts() << endl;
                cout << "pixel position of 0 part:  " << shape.part(0) << endl;
                cout << "pixel position of 1 part:  " << shape.part(1) << endl;
                cout << "pixel position of 2 part:  " << shape.part(2) << endl;
//                cout << "pixel position of 3 part:  " << shape.part(3) << endl;
//                cout << "pixel position of 4 part:  " << shape.part(4) << endl;
//                cout << "pixel position of 5 part:  " << shape.part(5) << endl;
//                cout << "pixel position of 6 part:  " << shape.part(6) << endl;
//                cout << "pixel position of 7 part:  " << shape.part(7) << endl;
//                cout << "pixel position of 8 part:  " << shape.part(8) << endl;
//                cout << "pixel position of 9 part:  " << shape.part(9) << endl;
//                cout << "pixel position of 10 part: " << shape.part(10) << endl;
//                cout << "pixel position of 11 part: " << shape.part(11) << endl;
//                cout << "pixel position of 12 part: " << shape.part(12) << endl;
//                cout << "pixel position of 13 part: " << shape.part(13) << endl;
//                cout << "pixel position of 14 part: " << shape.part(14) << endl;
//                cout << "pixel position of 15 part: " << shape.part(15) << endl;
//                cout << "pixel position of 16 part: " << shape.part(16) << endl;
//                cout << "pixel position of 17 part: " << shape.part(17) << endl;
//                cout << "pixel position of 18 part: " << shape.part(18) << endl;
//                cout << "pixel position of 19 part: " << shape.part(19) << endl;
//                cout << "pixel position of 20 part: " << shape.part(20) << endl;
//                cout << "pixel position of 21 part: " << shape.part(21) << endl;
//                cout << "pixel position of 22 part: " << shape.part(22) << endl;
//                cout << "pixel position of 23 part: " << shape.part(23) << endl;
//                cout << "pixel position of 24 part: " << shape.part(24) << endl;
//                cout << "pixel position of 25 part: " << shape.part(25) << endl;
//                cout << "pixel position of 26 part: " << shape.part(26) << endl;
//                cout << "pixel position of 27 part: " << shape.part(27) << endl;
//                cout << "pixel position of 28 part: " << shape.part(28) << endl;
//                cout << "pixel position of 29 part: " << shape.part(29) << endl;
//                cout << "pixel position of 30 part: " << shape.part(30) << endl;
//                cout << "pixel position of 31 part: " << shape.part(31) << endl;
//                cout << "pixel position of 32 part: " << shape.part(32) << endl;
//                cout << "pixel position of 33 part: " << shape.part(33) << endl;
//                cout << "pixel position of 34 part: " << shape.part(34) << endl;
//                cout << "pixel position of 35 part: " << shape.part(35) << endl;
//                cout << "pixel position of 36 part: " << shape.part(36) << endl;
//                cout << "pixel position of 37 part: " << shape.part(37) << endl;
//                cout << "pixel position of 38 part: " << shape.part(38) << endl;
//                cout << "pixel position of 39 part: " << shape.part(39) << endl;
//                cout << "pixel position of 40 part: " << shape.part(40) << endl;
//                cout << "pixel position of 41 part: " << shape.part(41) << endl;
//                cout << "pixel position of 42 part: " << shape.part(42) << endl;
//                cout << "pixel position of 43 part: " << shape.part(43) << endl;
//                cout << "pixel position of 44 part: " << shape.part(44) << endl;
//                cout << "pixel position of 45 part: " << shape.part(45) << endl;
//                cout << "pixel position of 46 part: " << shape.part(46) << endl;
//                cout << "pixel position of 47 part: " << shape.part(47) << endl;
//                cout << "pixel position of 48 part: " << shape.part(48) << endl;
//                cout << "pixel position of 49 part: " << shape.part(49) << endl;
//                cout << "pixel position of 50 part: " << shape.part(50) << endl;
//                cout << "pixel position of 51 part: " << shape.part(51) << endl;
//                cout << "pixel position of 52 part: " << shape.part(52) << endl;
//                cout << "pixel position of 53 part: " << shape.part(53) << endl;
//                cout << "pixel position of 54 part: " << shape.part(54) << endl;
//                cout << "pixel position of 55 part: " << shape.part(55) << endl;
//                cout << "pixel position of 56 part: " << shape.part(56) << endl;
//                cout << "pixel position of 57 part: " << shape.part(57) << endl;
//                cout << "pixel position of 58 part: " << shape.part(58) << endl;
//                cout << "pixel position of 59 part: " << shape.part(59) << endl;
//                cout << "pixel position of 60 part: " << shape.part(60) << endl;
//                cout << "pixel position of 61 part: " << shape.part(61) << endl;
//                cout << "pixel position of 62 part: " << shape.part(62) << endl;
//                cout << "pixel position of 63 part: " << shape.part(63) << endl;
//                cout << "pixel position of 64 part: " << shape.part(64) << endl;
//                cout << "pixel position of 65 part: " << shape.part(65) << endl;
//                cout << "pixel position of 66 part: " << shape.part(66) << endl;
//                cout << "pixel position of 67 part: " << shape.part(67) << endl;
//                cout << "pixel position of 68 part: " << shape.part(68) << endl;
//                cout << "pixel position of 69 part: " << shape.part(69) << endl;
//                cout << "pixel position of 70 part: " << shape.part(70) << endl;
//                cout << "pixel position of 71 part: " << shape.part(71) << endl;
//                cout << "pixel position of 72 part: " << shape.part(72) << endl;
//                cout << "pixel position of 73 part: " << shape.part(73) << endl;
//                cout << "pixel position of 74 part: " << shape.part(74) << endl;
//                cout << "pixel position of 75 part: " << shape.part(75) << endl;
//                cout << "pixel position of 76 part: " << shape.part(76) << endl;
//                cout << "pixel position of 77 part: " << shape.part(77) << endl;
//                cout << "pixel position of 78 part: " << shape.part(78) << endl;
//                cout << "pixel position of 79 part: " << shape.part(79) << endl;
//                cout << "pixel position of 80 part: " << shape.part(80) << endl;
//                cout << "pixel position of 81 part: " << shape.part(81) << endl;
//                cout << "pixel position of 82 part: " << shape.part(82) << endl;
//                cout << "pixel position of 83 part: " << shape.part(83) << endl;
//                cout << "pixel position of 84 part: " << shape.part(84) << endl;
//                cout << "pixel position of 85 part: " << shape.part(85) << endl;
//                cout << "pixel position of 86 part: " << shape.part(86) << endl;
//                cout << "pixel position of 87 part: " << shape.part(87) << endl;
//                cout << "pixel position of 88 part: " << shape.part(88) << endl;
//                cout << "pixel position of 89 part: " << shape.part(89) << endl;
//                cout << "pixel position of 90 part: " << shape.part(90) << endl;
//                cout << "pixel position of 91 part: " << shape.part(91) << endl;
//                cout << "pixel position of 92 part: " << shape.part(92) << endl;
//                cout << "pixel position of 93 part: " << shape.part(93) << endl;
//                cout << "pixel position of 94 part: " << shape.part(94) << endl;
//                cout << "pixel position of 95 part: " << shape.part(95) << endl;
//                cout << "pixel position of 96 part: " << shape.part(96) << endl;
//                cout << "pixel position of 97 part: " << shape.part(97) << endl;
//                cout << "pixel position of 98 part: " << shape.part(98) << endl;
//                cout << "pixel position of 99 part: " << shape.part(99) << endl;
//                cout << "pixel position of 100 part: " << shape.part(100) << endl;
//                cout << "pixel position of 101 part: " << shape.part(101) << endl;
//                cout << "pixel position of 102 part: " << shape.part(102) << endl;
//                cout << "pixel position of 103 part: " << shape.part(103) << endl;
//                cout << "pixel position of 104 part: " << shape.part(104) << endl;
//                cout << "pixel position of 105 part: " << shape.part(105) << endl;
//                cout << "pixel position of 106 part: " << shape.part(106) << endl;
//                cout << "pixel position of 107 part: " << shape.part(107) << endl;
//                cout << "pixel position of 108 part: " << shape.part(108) << endl;
//                cout << "pixel position of 109 part: " << shape.part(109) << endl;
//                cout << "pixel position of 110 part: " << shape.part(110) << endl;
//                cout << "pixel position of 111 part: " << shape.part(111) << endl;
//                cout << "pixel position of 112 part: " << shape.part(112) << endl;
//                cout << "pixel position of 113 part: " << shape.part(113) << endl;
//                cout << "pixel position of 114 part: " << shape.part(114) << endl;
//                cout << "pixel position of 115 part: " << shape.part(115) << endl;
//                cout << "pixel position of 116 part: " << shape.part(116) << endl;
//                cout << "pixel position of 117 part: " << shape.part(117) << endl;
//                cout << "pixel position of 118 part: " << shape.part(118) << endl;
//                cout << "pixel position of 119 part: " << shape.part(119) << endl;
//                cout << "pixel position of 120 part: " << shape.part(120) << endl;
//                cout << "pixel position of 121 part: " << shape.part(121) << endl;
//                cout << "pixel position of 122 part: " << shape.part(122) << endl;
//                cout << "pixel position of 123 part: " << shape.part(123) << endl;
//                cout << "pixel position of 124 part: " << shape.part(124) << endl;
//                cout << "pixel position of 125 part: " << shape.part(125) << endl;
//                cout << "pixel position of 126 part: " << shape.part(126) << endl;
//                cout << "pixel position of 127 part: " << shape.part(127) << endl;
//                cout << "pixel position of 128 part: " << shape.part(128) << endl;
//                cout << "pixel position of 129 part: " << shape.part(129) << endl;
//                cout << "pixel position of 130 part: " << shape.part(130) << endl;
//                cout << "pixel position of 131 part: " << shape.part(131) << endl;
//                cout << "pixel position of 132 part: " << shape.part(132) << endl;
//                cout << "pixel position of 133 part: " << shape.part(133) << endl;
//                cout << "pixel position of 134 part: " << shape.part(134) << endl;
//                cout << "pixel position of 135 part: " << shape.part(135) << endl;
//                cout << "pixel position of 136 part: " << shape.part(136) << endl;
//                cout << "pixel position of 137 part: " << shape.part(137) << endl;
//                cout << "pixel position of 138 part: " << shape.part(138) << endl;
//                cout << "pixel position of 139 part: " << shape.part(139) << endl;
//                cout << "pixel position of 140 part: " << shape.part(140) << endl;
//                cout << "pixel position of 141 part: " << shape.part(141) << endl;
//                cout << "pixel position of 142 part: " << shape.part(142) << endl;
//                cout << "pixel position of 143 part: " << shape.part(143) << endl;
//                cout << "pixel position of 144 part: " << shape.part(144) << endl;
//                cout << "pixel position of 145 part: " << shape.part(145) << endl;
//                cout << "pixel position of 146 part: " << shape.part(146) << endl;
//                cout << "pixel position of 147 part: " << shape.part(147) << endl;
//                cout << "pixel position of 148 part: " << shape.part(148) << endl;
//                cout << "pixel position of 149 part: " << shape.part(149) << endl;
//                cout << "pixel position of 150 part: " << shape.part(150) << endl;
//                cout << "pixel position of 151 part: " << shape.part(151) << endl;
//                cout << "pixel position of 152 part: " << shape.part(152) << endl;
//                cout << "pixel position of 153 part: " << shape.part(153) << endl;
//                cout << "pixel position of 154 part: " << shape.part(154) << endl;
//                cout << "pixel position of 155 part: " << shape.part(155) << endl;
//                cout << "pixel position of 156 part: " << shape.part(156) << endl;
//                cout << "pixel position of 157 part: " << shape.part(157) << endl;
//                cout << "pixel position of 158 part: " << shape.part(158) << endl;
//                cout << "pixel position of 159 part: " << shape.part(159) << endl;
//                cout << "pixel position of 160 part: " << shape.part(160) << endl;
//                cout << "pixel position of 161 part: " << shape.part(161) << endl;
//                cout << "pixel position of 162 part: " << shape.part(162) << endl;
//                cout << "pixel position of 163 part: " << shape.part(163) << endl;
//                cout << "pixel position of 164 part: " << shape.part(164) << endl;
//                cout << "pixel position of 165 part: " << shape.part(165) << endl;
//                cout << "pixel position of 166 part: " << shape.part(166) << endl;
//                cout << "pixel position of 167 part: " << shape.part(167) << endl;
//                cout << "pixel position of 168 part: " << shape.part(168) << endl;
//                cout << "pixel position of 169 part: " << shape.part(169) << endl;
//                cout << "pixel position of 170 part: " << shape.part(170) << endl;
//                cout << "pixel position of 171 part: " << shape.part(171) << endl;
//                cout << "pixel position of 172 part: " << shape.part(172) << endl;
//                cout << "pixel position of 173 part: " << shape.part(173) << endl;
//                cout << "pixel position of 174 part: " << shape.part(174) << endl;
//                cout << "pixel position of 175 part: " << shape.part(175) << endl;
//                cout << "pixel position of 176 part: " << shape.part(176) << endl;
//                cout << "pixel position of 177 part: " << shape.part(177) << endl;
//                cout << "pixel position of 178 part: " << shape.part(178) << endl;
//                cout << "pixel position of 179 part: " << shape.part(179) << endl;

                // You get the idea, you can get all the body shape part locations if
                // you want them.  Here we just store them in shapes so we can
                // put them on the screen.
                shapes.push_back(shape);
            }

            // Now lets view our body shape poses on the screen.
            win.clear_overlay();
            win.set_image(img);
            win.add_overlay(render_body_detections(shapes));

            gettimeofday(&end, NULL);

            seconds  = end.tv_sec  - start.tv_sec;
            useconds = end.tv_usec - start.tv_usec;

            mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;
            cout << "Elapsed time (in milliseconds):" << mtime << endl;

//            return 0;

            cout << "Hit enter to process the next image..." << endl;
            cin.get();
        }
    }
    catch (exception& e)
    {
        cout << "\nexception thrown!" << endl;
        cout << e.what() << endl;
    }
}

// ----------------------------------------------------------------------------------------

