#ifndef _FULLSHIPINFO_H_
#define _FULLSHIPINFO_H_
#include <iostream>
class PlugIn_ViewPort;

struct FullShipInfo
{
    double lat = 0;
    double lon = 0;
    int speed = 0;
    int course = 0;
    int heading = 0;
    int elapsed = 0;
    std::string destination;
    std::string flag;
    int length = 0;
    int rot = 0;
    std::string ship_name;
    int ship_type = 0;
    long ship_id = 0;
    int width = 0;
    int l_fore = 0;
    int w_left = 0;
    int dwt = 0;
    int gt_shiptype = 0;
    int pix_x;
    int pix_y;
    void setPixPoint(PlugIn_ViewPort *vp);
    void setValue(std::string key, std::string value);
};

#endif // _FULLSHIPINFO_H_
