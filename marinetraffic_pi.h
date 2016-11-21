/*****************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  demo Plugin
 *
 ***************************************************************************
 *   Copyright (C) 2010 by David S. Register   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,  USA.         *
 ***************************************************************************
 */
/*
 * C++11,Python, Linux and BASH scripting, experience with low-latency computing and hardware-level design
 *
 * Strong background in C++ (11, 14)
 * Working knowledge of at least one scripting language (Perl, bash, python)
 * Proficiency in a Linux environment
 * Solid understanding of network programming
 * Thorough knowledge of common third-party libraries (STL, boost, etc.)
 * Experience developing multi-threaded applications
 * Comfortable working within an iterative development process
 * Commitment to following best documentation and testing practices
 * Knowledge of futures or options markets and how to trade them is a plus
 * Strong understanding of interaction between hardware and software
 * Excellent written and verbal communication skills
*/


#ifndef _MARINETRAFFICPI_H_
#define _MARINETRAFFICPI_H_

#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
#include "wx/wx.h"
#endif //precompiled headers

#define     PLUGIN_VERSION_MAJOR    0
#define     PLUGIN_VERSION_MINOR    1

#define     MY_API_VERSION_MAJOR    1
#define     MY_API_VERSION_MINOR    8

#include "../../../include/ocpn_plugin.h"

#include "nmea0183/nmea0183.h"
#include "DataReader.h"
#include "FullShipInfo.h"

class CDataReader;

class demoWindow;

//----------------------------------------------------------------------------------------------------------
//    The PlugIn Class Definition
//----------------------------------------------------------------------------------------------------------


class marinetraffic_pi : public opencpn_plugin_18
{
public:
    marinetraffic_pi(void *ppimgr):opencpn_plugin_18(ppimgr){}

    //    The required PlugIn Methods
    int Init(void);
    bool DeInit(void);

    int GetAPIVersionMajor();
    int GetAPIVersionMinor();
    int GetPlugInVersionMajor();
    int GetPlugInVersionMinor();

    wxString GetCommonName();
    wxString GetShortDescription();
    wxString GetLongDescription();

    //    The optional method overrides
    void SetNMEASentence(wxString &sentence);
    void OnContextMenuItemCallback(int id);
    void UpdateAuiStatus(void);

    //    The override PlugIn Methods
    bool RenderOverlay(wxDC &dc, PlugIn_ViewPort *vp);
    void SetCursorLatLon(double lat, double lon);
    bool RenderGLOverlay(wxGLContext *pcontext, PlugIn_ViewPort *vp);
    int GetToolbarToolCount(void);
    void ShowPreferencesDialog( wxWindow* parent );
    void OnToolbarToolCallback(int id);
    void SetPluginMessage(wxString &message_id, wxString &message_body);
    void SetPositionFixEx(PlugIn_Position_Fix_Ex &pfix);
    virtual void SetCurrentViewPort(PlugIn_ViewPort &vp);


private:
    wxWindow *m_parent_window;
    demoWindow *m_pdemo_window;
    wxAuiManager *m_AUImgr;
    int m_show_id;
    int m_hide_id;
    CDataReader m_dataReader;
};



class demoWindow : public wxWindow
{
protected:
    wxTextCtrl *m_latMinTCtrl;
    wxTextCtrl *m_latMaxTCtrl;
    wxTextCtrl *m_lonMinTCtrl;
    wxTextCtrl *m_lonMaxTCtrl;
    wxTextCtrl *m_latCentTCtrl;
    wxTextCtrl *m_lonCentTCtrl;
    wxTextCtrl *m_zoomTCtrl;
    virtual void updateDataReader(wxCommandEvent &event);
    PlugIn_ViewPort m_lastVp;
    CDataReader *m_pDataReader;

    wxTextCtrl *m_proxySiteTCtrl;
    wxTextCtrl *m_proxyPortTCtrl;
    wxCheckBox *m_enableProxyBox;
public:
    demoWindow(wxWindow *pparent, wxWindowID id);
    ~demoWindow();

    void SetCurrentViewPort(PlugIn_ViewPort &vp);

    void OnPaint(wxPaintEvent& event);
    void SetSentence(wxString &sentence);
    void OnSize(wxSizeEvent& event);
    void setDataReader(CDataReader *dataReader);

    wxString          m_NMEASentence;
    double            mLat, mLon, mSog, mCog, mVar;


    DECLARE_EVENT_TABLE()
};


#endif



