#include "FullShipInfo.h"
#include "wx/wxprec.h"
#ifndef  WX_PRECOMP
#include "wx/wx.h"
#endif //precompiled headers
#include "../../../include/ocpn_plugin.h"
#include "boost/assign.hpp"
#include "boost/format.hpp"

using std::make_pair;

class specific_visitor : public boost::static_visitor<>
{
public:
    explicit specific_visitor(int i) : i_num(i) { }
    explicit specific_visitor(double d) : d_num(d) { }
    explicit specific_visitor(long l) : l_num(l) { }
    explicit specific_visitor(std::string s) : str(s) { }

    void operator()(int *i) const
    {
        *i = i_num;
    }

    void operator()(double *d) const
    {
        *d = d_num;
    }

    void operator()(long *l) const
    {
        *l = l_num;
    }

    void operator()(std::string *s) const
    {
        *s = str;
    }
private:
    int i_num;
    double d_num;
    long l_num;
    std::string str;
};

FullShipInfo::FullShipInfo()
{
    //boost::assign::map_list_of<std::string, PairVariant>
    boost::assign::insert(m_valueMap)
            ("LAT", make_pair(DOUBLE_TYPE, &lat))
            ("LON", make_pair(DOUBLE_TYPE, &lon))
            ("SPEED", make_pair(INT_TYPE, &speed))
            ("COURSE", make_pair(INT_TYPE, &course))
            ("HEADING", make_pair(INT_TYPE, &heading))
            ("ELAPSED", make_pair(INT_TYPE, &elapsed))
            ("DESTINATION", make_pair(STRING_TYPE, &destination))
            ("FLAG", make_pair(STRING_TYPE, &flag))
            ("LENGTH", make_pair(INT_TYPE, &length))
            ("ROT", make_pair(INT_TYPE, &rot))
            ("SHIPNAME", make_pair(STRING_TYPE, &ship_name))
            ("SHIPTYPE", make_pair(INT_TYPE, &ship_type))
            ("SHIP_ID", make_pair(LONG_TYPE, &ship_id))
            ("WIDTH", make_pair(INT_TYPE, &width))
            ("L_FORE", make_pair(INT_TYPE, &l_fore))
            ("W_LEFT", make_pair(INT_TYPE, &w_left))
            ("DWT", make_pair(INT_TYPE, &dwt))
            ("GT_SHIPTYPE", make_pair(INT_TYPE, &gt_shiptype))
            ("LEGEND", make_pair(STRING_TYPE, &legend))
            ;
}

void FullShipInfo::setPixPoint(PlugIn_ViewPort *vp)
{
    wxPoint pix_point;
    GetCanvasPixLL(vp, &pix_point, lat, lon);
    pix_x = pix_point.x;
    pix_y = pix_point.y;
}

void FullShipInfo::setValue(std::string key, std::string value)
{
    auto it = m_valueMap.find(key);
    if(it != m_valueMap.end())
    {
        PairVariant currPair = it->second;
        switch (currPair.first)
        {
        case INT_TYPE:
            boost::apply_visitor(specific_visitor(std::stoi(value)), currPair.second);
            break;
        case STRING_TYPE:
            boost::apply_visitor(specific_visitor(value), currPair.second);
            break;
        case DOUBLE_TYPE:
            boost::apply_visitor(specific_visitor(std::stod(value)), currPair.second);
            break;
        case LONG_TYPE:
            boost::apply_visitor(specific_visitor(std::stol(value)), currPair.second);
            break;
        default:
            std::string logText = "%1%[%2%]: Unexpected type of variant %3%";
            wxLogMessage(wxString((boost::format(logText) % __FILE__ % __LINE__ % currPair.first).str()));
            return;
        }
    }
    else
    {
#ifdef _DEBUG
        std::string logText = "%1%[%2%]: Can't set a value for key %3%";
        wxLogMessage(wxString((boost::format(logText) % __FILE__ % __LINE__ % key).str()));
#endif
    }
}
