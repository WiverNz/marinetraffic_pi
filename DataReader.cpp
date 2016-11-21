#include "DataReader.h"
#ifdef _MSC_VER
#include <boost/config/compiler/visualc.hpp>
#endif
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <cassert>
#include <exception>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include "CURLMarineExtractor.h"

#include "wx/wxprec.h"
#ifndef  WX_PRECOMP
#include "wx/wx.h"
#endif //precompiled headers
#include "../../../include/ocpn_plugin.h"
#include <wx/mstream.h>
#include <wx/filename.h>
#include "FullShipInfo.h"

CDataReader::CDataReader()
{
    //    try
    //    {
    //        std::stringstream ss;
    //        // send your JSON above to the parser below, but populate ss first


    //        boost::property_tree::ptree pt;
    //        boost::property_tree::read_json(ss, pt);

    //        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, pt.get_child("particles.electron"))
    //        {
    //            assert(v.first.empty()); // array elements have no names
    //            std::cout << v.second.data() << std::endl;
    //            // etc
    //        }
    //        return;
    //    }
    //    catch (std::exception const& e)
    //    {
    //        std::cerr << e.what() << std::endl;
    //    }
}

CDataReader::~CDataReader()
{
    clearData();
}

void CDataReader::clearData()
{
    for (auto *shipInfo : m_ships)
    {
        delete shipInfo;
        shipInfo = nullptr;
    }
    m_ships.clear();
}

void CDataReader::useProxy(const bool &useProxy, const std::__cxx11::string &site, const int &port)
{
    m_useProxy = useProxy;
    m_proxySite = site;
    m_proxyPort = port;
}

void CDataReader::readData(double sw_x, double sw_y, double ne_x, double ne_y, int zoom, int station,
                           double centerx, double centery)
{
    clearData();
    CURLMarineExtractor client;
    if (!m_useProxy)
    {
        client.init();
    }
    else
    {
        client.init(m_proxySite, m_proxyPort);
    }
    std::string str = client.getByArea(sw_x, sw_y, ne_x, ne_y, zoom, station, centerx, centery);
    try
    {
        std::stringstream ss;
        ss.str(str);
        boost::property_tree::ptree pt;
        boost::property_tree::read_json(ss, pt);
        for (auto row : pt.get_child("data.rows"))
        {
            FullShipInfo *shipInfo = new FullShipInfo();
            m_ships.push_back(shipInfo);
            for (boost::property_tree::ptree::value_type &cell : row.second)
            {
                if (cell.first.empty())
                {
                    continue;
                }
                shipInfo->setValue(cell.first, cell.second.data());
            }
        }
    }
    catch (std::exception const& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void CDataReader::updatePixPositions(PlugIn_ViewPort &vp)
{
    std::for_each (m_ships.begin(), m_ships.end(), [&vp] (auto shipInfo)
    {
        shipInfo->setPixPoint(&vp);
    });
}

void CDataReader::draw(wxDC &dc, PlugIn_ViewPort *vp)
{
    if(dc.IsOk())
    {
        std::for_each(m_ships.begin(), m_ships.end(), [&dc, &vp, this] (auto shipInfo)
        {
            this->drawShip(shipInfo, dc);
        });
    }
}


void CDataReader::drawShip(FullShipInfo *shipInfo, wxDC &dcIn)
{
    wxString NewVal = wxString::Format(_T("%.1f"), 1.2);
    double scale = GetOCPNGUIToolScaleFactor_PlugIn();
    scale = wxRound(scale * 4.0) / 4.0;
    scale = wxMax(1.0, scale);          // Let the upstream processing handle minification.
    wxMemoryInputStream sm("\211PNG\r\n\032\n\000\000\000\rIHDR\000\000\000 \000\000\000 \b\002\000\000\000\374\030\355\243\000\000\000\001sRGB\000\256\316\034\351\000\000\000\004gAMA\000\000\261\217\013\374a\005\000\000\000\011pHYs\000\000\r\326\000\000\r\326\001\220oy\234\000\000\000\032tEXtSoftware\000Paint.NET v3.5.100\364r\241\000\000\aXIDATHK\245\226\375S\032I\032\307\347?\246\246\306\233`\271\271\335K\335\236\265[w1\306\2151!\204Y\224\260Z\254,\213!z\036\221\245\230\340\340\3108\016\216C8\002\"\210(\276\307\274\335\017\271O;\226gm\274\237\266\253\241\272{\236\376~\237\347\351\347y\272\245\317\237?\177\370\360\3010\214\271\271\271\331\331\331\237\377p\003\004(\000?}\372\004\270\364\361\343\307\347\317\2373?::b\374\237\233\032\032\274\177\377\376\335\273w\3743~\373\366\355\371\3719\343\033\205\0019<<\\^^\006\026a\351U\361U\261Xd\365\313\206\n\240\234\236\236\302\315\236~\277\277w\2551e\0212Pn\334\016,4R\"\221888\000\350zCYv\002\r\004\230\335n\267\323\351\264\276h\355v\233u\004\216\217\217}\373\256\267\375\375}\334%\305\236\305\316\336\236\235\277;\277\352@\037\237\034\037\036\035\366\366z>n\275Q\367<\317\2518\366\372\372ze\235\201\353\271\325Z\265^\2577\232\rz\273\323\356\365z\247g\247\327q\200\005\\\232\234\232<9;a\342w\204\230^A\203R\331\330X2\234\207\311\362\327\321\362\367\331\376w\331\303o\246\254\247skzyscs\323g\252\325j\220uw\273''\377\203\002\ap\351\307\350\217\350{rzBg@\367\265F/\307qf\263VP+\a\2436\375\366\264\367C\361,T:\373:Q\023+\232\375\225\266\266XXwi\236\350X\331\351v0\375\n\rp)\242E\016\216\016\216\216\371\035p\230\255\266pH\255^+[\353\337\306VT\315R\243\266\032s\324x\205~;\325\274\235j\005\247\031;,\006\243\026\002w\247\315\215\r\030\\\333\261\371G?\320|@\300\245\360\323p\377\240\177px@T\300\357{vum\375\351\213\315\241)\037\332Q\247]u\306U\023\336`\262:\224\2542`z'f\014\305L\025\031\315\322\346]\334\205\305\246ib\aA!\000\017\372\200K\241'\241\336~\217\023g\3167\b\234\r\347o\223+\003\232\025\315\325o'\334\201\031w \341\r$\253\003\311\332P\246Ng\240&\275p|\216O\301\270\203\230\252\225G\246W\275\252gYV\251Tz\323|Ch\001\013\270\364\350\361\243\335\336\356~\177\277\331l\242\002B\317^\224\224\260\251D-6+3\256\222\360\224dMI\323\353C\213M:\203H\"3\034/\212OX\206X\324b\313?u\273\342V\364\242\216\257\210+`\001\227\036N<\3043X@\360\321M\313\032\b\225\024\255\254L\331\n;\023\256\222\254\202\250d\032\312|s(\327\242\1773_I\307\242\202\222O\b \206p\244|+dlnzE\203\014+b\004\260\200K\017\306\037\300\306\311\224\2552\374\277\276\\\221C%Y\263\344\230-\317T\344YON\327ng\233\301lKYl\r\026:\364\371\2246\026\317\263(\247jB\0001\204\2652\033\363\313k\340\344\3629\202\252\265\335\002\\\032{0FBr\260\370\016\013\276\213\351r\270$G-9\356\3103\256\234\254\312\351\272@\317\265\203z7X\354\206s\371%m\\L!H\327\345$\004\356\025\301\304\317E\264\\\312-q\030\030\001\2704:6\212\005\020b\032g\240\206KJ\324\016D\255@\334\011$\334@\252\032\310\324\345\205fP\357\004\213\275!\275e\246G\302\261\005\246,\006\346\352\201\244\027\230q\0031;\200W5\353VH'R!@\335\332\277k\200K#\243#\255N\213c\201`mm\355\357\213]\315\350\2533\234\2363\220t\325LM]l\006\363-U\357\312zo,\032.\30445\337V\341\313\265\202\213\215`\246\026L\022i\2162\355\335]\332Sg[\004!\004\034\003\001\011\270t\367\336\335\355\316\266OP\026\004\235\361B\237\300\277N\240\346Z\212\336Q\363--\221\3128\rE\357*\205k\004)\262D\020\214\344\366\324d\253R\251\344r9\237\000pA\320l5\361\276\256\353\266m\253\241\342\000\376\321\312\302\352\231\212\360\000~\300E\205\316H\246\030\317\233\240c\rS\341\242t\355\302E\225\013\027\231\270\350O\217u\240 \300E\325\327\027\004X\261\325\332\"\305\374\370\035\236,\004B\006\322b\317\264\023\230\365\002\251\232\272\320T\262\315\360\\\366\216\336Dw5\337\221\227Z\352b\203O\342\234\020\233\262\002\0213\360\310\030\237\3219H\242\310,\233T@\341\242{\243\367\3364\336\220e\030\205\005\277\376\313\bL\030\201\260yy\316\034 \345a\261\361}\2724\221\265\203\2716\356Bw(\207\026\032\227'L8`4[&\014\302\224jQ(\024pT\375M\035pi\364\376hs\253I\365\340\203e[\346\252%O\024\003\341\322\245\227\320.\341\312)o<]\2203\304+\011q\021<\276s|\365/B(\020*\rL\02476D4\322_\277~\r,\340\322\375\037\356omo\355\354\354\020\251p\020\305\3172\313\"\327\"&\371y\221\r\225;\211\322\235\264CZ\005\347\353t9U\025\341\0171)&\322\330BX~T\312\374\266\202\212F\311\340\237j\017,\340\"\321\266\332[\333;\333\030A\022rD\253\226\365\027MW\302%-[\035 Ec\366p\242$\262)\341\006S\036\375\002\332\225\247\035\221_Qk|\336C\241\341I\341}T\244\341\375\355\3666\260\"\321.K\305Ngww\227k\000r\016\334(\231\2419G\016\233\024\200Ajr\374\302\024\352v\202\242\355\372c\037]T\210p)\374\334)\3336\372\221\300\370\200\260\354\354P\177\332\242T\370\305\216\333\216\342G\215\005\035\011\262\021\216\341\251eQV/\342\217\364\306c\203\211\332\320l]\211\331\242|\262\030)+!\363\037\317\226\255\26554\363/\034\234\003\024\200\227\305\316/\327\\\302\242\367z\330\001\a6\362\277\272\272:\363\302\270\025^\0214\221r0\346\014/\035\215\026\216\206HC\240\303\346`\330H\277\\!\377\011?\241\226\347r\260 \370h\227\345\372I\370\011\227\001\267\215\337\367\366\305\323\247\321hP\376\240\021n]\265\026~3\037$\214\2574\343\257\363{\337.\366\377\034-=N\032Y}\265\214_l[\334\"\236\207\374\326\326\026\240WP\300\002.E\"\021\336E\334\306W\215)\327\003%\226\344\240\261S\334\267\270\270\\\346\000\371\247\371\270\254W\253\342\212E\214\202\317#\352w8\200K?M\377$\2364_4\377)\3076\230xd\000\341\233u\325Xa\235\2574\020x\260\374\016\203\320\217\307\343R6\233%\361xk~\331x\201\241\021\326\210\013\266\327#\216\375\006\353\325\030%\300\275q{>\237\a\\\002\"\225JQ'\372\207\375S^\2137u\377\031\202\216\376\200\207\"\273x\225\374?y\216A\177\245\377\222\372\005n\211\0276{\226\226\226\240\341\351\316S\365\0176@\200z\231{\011:\340\377\005\302vQQqo\232\271\000\000\000\000IEND\256B`\202", 2025);
    wxBitmap *_img_wmm_live = new wxBitmap(wxImage(sm));
    int w = _img_wmm_live->GetWidth() * scale;
    int h = _img_wmm_live->GetHeight() * scale;
    wxMemoryDC dc;
    wxBitmap icon;
    wxString m_shareLocn =*GetpSharedDataLocation() +
            _T("plugins") + wxFileName::GetPathSeparator() +
            _T("marinetraffic_pi") + wxFileName::GetPathSeparator() +
            _T("data") + wxFileName::GetPathSeparator();
    //  Is SVG available?
    wxBitmap live = GetBitmapFromSVGFile(m_shareLocn + _T("wmm_live.svg"), w, h);
    if(!live.IsOk())
    {
        icon = wxBitmap(_img_wmm_live->GetWidth(), _img_wmm_live->GetHeight());
        dc.SelectObject(icon);
        dc.DrawBitmap(*_img_wmm_live, 0, 0, true);
    }
    else
    {
        icon = wxBitmap(w, h);
        dc.SelectObject(icon);
        wxColour col;
        dc.SetBackground( *wxTRANSPARENT_BRUSH );
        dc.Clear();

        dc.DrawBitmap(live, 0, 0, true);
    }

    wxColour cf;
    GetGlobalColor(_T("CHBLK"), &cf);
    dc.SetTextForeground(cf);
    wxSize s = dc.GetTextExtent(NewVal);
    dc.DrawText(NewVal, (icon.GetWidth() - s.GetWidth()) / 2, (icon.GetHeight() - s.GetHeight()) / 2);
    dc.SelectObject(wxNullBitmap);

    if(live.IsOk())
    {
        //  By using a DC to modify the bitmap, we have lost the original bitmap's alpha channel
        //  Recover it by copying from the original to the target, bit by bit
        wxImage imo = live.ConvertToImage();
        wxImage im = icon.ConvertToImage();

        if(!imo.HasAlpha())
        {
            imo.InitAlpha();
        }
        if(!im.HasAlpha())
        {
            im.InitAlpha();
        }

        unsigned char *alive = imo.GetAlpha();
        unsigned char *target = im.GetAlpha();

        for(int i = 0; i < h; i++)
        {
            for(int j = 0; j < w; j++)
            {
                int index = (i * w) + j;
                target[index] = alive[index];
            }
        }
        icon = wxBitmap(im);
    }

    //SetToolbarToolBitmaps(m_leftclick_tool_id, &icon, &icon);
    dcIn.DrawBitmap(icon, shipInfo->pix_x, shipInfo->pix_y);
    delete _img_wmm_live;
}
