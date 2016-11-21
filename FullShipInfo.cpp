#include "FullShipInfo.h"
#include "wx/wxprec.h"
#ifndef  WX_PRECOMP
#include "wx/wx.h"
#endif //precompiled headers
#include "../../../include/ocpn_plugin.h"

void FullShipInfo::setPixPoint(PlugIn_ViewPort *vp)
{
    wxPoint pix_point;
    GetCanvasPixLL(vp, &pix_point, lat, lon);
    pix_x = pix_point.x;
    pix_y = pix_point.y;
}

void FullShipInfo::setValue(std::string key, std::string value)
{
    if (key == "LAT")
    {
        lat = std::stod(value);
    }
    else if (key == "LON")
    {
        lon = std::stod(value);
    }
    else if (key == "SPEED")
    {
        speed = std::stoi(value);
    }
    else if (key == "COURSE")
    {
        course = std::stoi(value);
    }
    else if (key == "HEADING")
    {
        heading = std::stoi(value);
    }
    else if (key == "ELAPSED")
    {
        elapsed = std::stoi(value);
    }
    else if (key == "DESTINATION")
    {
        destination = value;
    }
    else if (key == "FLAG")
    {
        flag = value;
    }
    else if (key == "LENGTH")
    {
        length = std::stoi(value);
    }
    else if (key == "ROT")
    {
        rot = std::stoi(value);
    }
    else if (key == "SHIPNAME")
    {
        ship_name = value;
    }
    else if (key == "SHIPTYPE")
    {
        ship_type = std::stoi(value);
    }
    else if (key == "SHIP_ID")
    {
        ship_id = std::stol(value);
    }
    else if (key == "WIDTH")
    {
        width = std::stoi(value);
    }
    else if (key == "L_FORE")
    {
        l_fore = std::stoi(value);
    }
    else if (key == "W_LEFT")
    {
        w_left = std::stoi(value);
    }
    else if (key == "DWT")
    {
        dwt = std::stoi(value);
    }
    else if (key == "GT_SHIPTYPE")
    {
        gt_shiptype = std::stoi(value);
    }
    else
    {
#ifdef DEBUG
        __pragma(message("TODO: "_STR(x) " :: " __FILE__ "@"STR(__LINE__)))
#endif
    }
}
