// Copyright (C) 2014  Davis E. King (davis@dlib.net)
// License: Boost Software License   See LICENSE.txt for the full license.
#ifndef DLIB_RENDER_FACE_DeTECTIONS_H_
#define DLIB_RENDER_FACE_DeTECTIONS_H_

#include "full_object_detection.h"
#include "../gui_widgets.h"
#include "render_body_detections_abstract.h"
#include <vector>

namespace dlib
{
    inline std::vector<image_window::overlay_line> render_body_detections (
        const std::vector<full_object_detection>& dets,
        const rgb_pixel color = rgb_pixel(0,255,0)
    )
    {
        std::vector<image_window::overlay_line> lines;
        for (unsigned long i = 0; i < dets.size(); ++i)
        {
            DLIB_CASSERT(dets[i].num_parts() == 180,//68,
                "\t std::vector<image_window::overlay_line> render_body_detections()"
                << "\n\t Invalid inputs were given to this function. "
                << "\n\t dets["<<i<<"].num_parts():  " << dets[i].num_parts() 
            );

            const full_object_detection& d = dets[i];
            for (unsigned long i = 1; i <= 10; ++i)
                lines.push_back(image_window::overlay_line(d.part(i), d.part(i-1), color));

            lines.push_back(image_window::overlay_line(d.part(10), d.part(21), color));

            for (unsigned long i = 12; i <= 20; ++i)
                lines.push_back(image_window::overlay_line(d.part(i), d.part(i-1), color));

            lines.push_back(image_window::overlay_line(d.part(20), d.part(22), color));

            for (unsigned long i = 23; i <= 31; ++i)
                lines.push_back(image_window::overlay_line(d.part(i), d.part(i-1), color));

            lines.push_back(image_window::overlay_line(d.part(21), d.part(32), color));
            lines.push_back(image_window::overlay_line(d.part(31), d.part(33), color));

            for (unsigned long i = 34; i <= 42; ++i)
                lines.push_back(image_window::overlay_line(d.part(i), d.part(i-1), color));

            lines.push_back(image_window::overlay_line(d.part(32), d.part(43), color));
            lines.push_back(image_window::overlay_line(d.part(42), d.part(44), color));

            for (unsigned long i = 45; i <= 53; ++i)
                lines.push_back(image_window::overlay_line(d.part(i), d.part(i-1), color));

            lines.push_back(image_window::overlay_line(d.part(43), d.part(54), color));
            lines.push_back(image_window::overlay_line(d.part(53), d.part(55), color));

            for (unsigned long i = 56; i <= 64; ++i)
                lines.push_back(image_window::overlay_line(d.part(i), d.part(i-1), color));

            lines.push_back(image_window::overlay_line(d.part(54), d.part(65), color));
            lines.push_back(image_window::overlay_line(d.part(64), d.part(66), color));

            for (unsigned long i = 67; i <= 75; ++i)
                lines.push_back(image_window::overlay_line(d.part(i), d.part(i-1), color));

            lines.push_back(image_window::overlay_line(d.part(65), d.part(76), color));
            lines.push_back(image_window::overlay_line(d.part(75), d.part(77), color));

            for (unsigned long i = 78; i <= 86; ++i)
                lines.push_back(image_window::overlay_line(d.part(i), d.part(i-1), color));

            lines.push_back(image_window::overlay_line(d.part(76), d.part(87), color));
            lines.push_back(image_window::overlay_line(d.part(86), d.part(88), color));

            for (unsigned long i = 89; i <= 97; ++i)
                lines.push_back(image_window::overlay_line(d.part(i), d.part(i-1), color));

            lines.push_back(image_window::overlay_line(d.part(87), d.part(98), color));
            lines.push_back(image_window::overlay_line(d.part(97), d.part(0), color));
            lines.push_back(image_window::overlay_line(d.part(179), d.part(11), color));

            for (unsigned long i = 99; i <= 179; ++i)
                lines.push_back(image_window::overlay_line(d.part(i), d.part(i-1), color));
        }
        return lines;
    }

}

#endif // DLIB_RENDER_FACE_DeTECTIONS_H_

