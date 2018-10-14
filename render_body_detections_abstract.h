// Copyright (C) 2014  Davis E. King (davis@dlib.net)
// License: Boost Software License   See LICENSE.txt for the full license.
#undef DLIB_RENDER_FACE_DeTECTIONS_ABSTRACT_H_
#ifdef DLIB_RENDER_FACE_DeTECTIONS_ABSTRACT_H_

/* This library was modified from Dlib's render_face_detections_abstract.h.
Copy and paste this file in Dlib's image_processing folder. If you
encounter any error when running the main file of this repository, comment 
the original contents of render_face_detections_abstract.h and copy-paste 
the contents of this file, changing all the "body" words for "face".
*/

#include "full_object_detection_abstract.h"
#include "../gui_widgets.h"

namespace dlib
{

    inline std::vector<image_window::overlay_line> render_body_detections (
        const std::vector<full_object_detection>& dets,
        const rgb_pixel color = rgb_pixel(0,255,0)
    );
    /*!
        requires
            - for all valid i:
                - dets[i].num_parts() == 180
        ensures
            - Interprets the given objects as body contour detections with parts annotated using
              Karla Trejo's body landmark scheme.  We then return a set of overlay lines that
              will draw the objects onto the screen in a way that properly draws the
              outline of the human body shape defined by the part locations.
            - Returns a vector with dets.size() elements, each containing the lines
              necessary to render a people detection from dets.
    !*/

}

#endif // DLIB_RENDER_FACE_DeTECTIONS_ABSTRACT_H_


