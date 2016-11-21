/******************************************************************************
 * updated: 4-5-2012
 * Project:  OpenCPN
 * Purpose:  demo Plugin
 * Author:   David Register
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


#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
#include "wx/wx.h"
#endif //precompiled headers

#include <wx/aui/aui.h>

#include "marinetraffic_pi.h"

// the class factories, used to create and destroy instances of the PlugIn

extern "C" DECL_EXP opencpn_plugin* create_pi(void *ppimgr)
{
    return new marinetraffic_pi(ppimgr);
}

extern "C" DECL_EXP void destroy_pi(opencpn_plugin* p)
{
    delete p;
}





//---------------------------------------------------------------------------------------------------------
//
//    demo PlugIn Implementation
//
//---------------------------------------------------------------------------------------------------------



//---------------------------------------------------------------------------------------------------------
//
//          PlugIn initialization and de-init
//
//---------------------------------------------------------------------------------------------------------


int marinetraffic_pi::Init(void)
{
    //      printf("marinetraffic_pi Init()\n");
    auto curr = 12;
    m_pdemo_window = NULL;

    // Get a pointer to the opencpn display canvas, to use as a parent for windows created
    m_parent_window = GetOCPNCanvasWindow();

    // Create the Context Menu Items

    //    In order to avoid an ASSERT on msw debug builds,
    //    we need to create a dummy menu to act as a surrogate parent of the created MenuItems
    //    The Items will be re-parented when added to the real context meenu
    wxMenu dummy_menu(_T("Plugin"));

    wxMenuItem *pmi = new wxMenuItem(&dummy_menu, -1, _("Show PlugIn DemoWindow"));
    m_show_id = AddCanvasContextMenuItem(pmi, this );
    SetCanvasContextMenuItemViz(m_show_id, true);

    wxMenuItem *pmih = new wxMenuItem(&dummy_menu, -1, _("Hide PlugIn DemoWindow"));
    m_hide_id = AddCanvasContextMenuItem(pmih, this );
    SetCanvasContextMenuItemViz(m_hide_id, false);

    m_pdemo_window = new demoWindow(m_parent_window, wxID_ANY);

    m_AUImgr = GetFrameAuiManager();
    m_AUImgr->AddPane(m_pdemo_window);
    m_AUImgr->GetPane(m_pdemo_window).Name(_T("MarineTraffic"));

    m_AUImgr->GetPane(m_pdemo_window).Float();
    m_AUImgr->GetPane(m_pdemo_window).FloatingPosition(300,30);

    m_AUImgr->GetPane(m_pdemo_window).Caption(_T("MarineTraffic"));
    m_AUImgr->GetPane(m_pdemo_window).CaptionVisible(true);
    m_AUImgr->GetPane(m_pdemo_window).GripperTop(true);
    m_AUImgr->GetPane(m_pdemo_window).CloseButton(true);
    m_AUImgr->GetPane(m_pdemo_window).Show(true);
    m_AUImgr->Update();
    m_pdemo_window->setDataReader(&m_dataReader);
    return (WANTS_OVERLAY_CALLBACK | WANTS_ONPAINT_VIEWPORT |
            INSTALLS_CONTEXTMENU_ITEMS     |
            WANTS_NMEA_SENTENCES           |
            USES_AUI_MANAGER
            );
}

bool marinetraffic_pi::DeInit(void)
{
    m_AUImgr->DetachPane(m_pdemo_window);
    if(m_pdemo_window)
    {
        m_pdemo_window->Close();
        m_pdemo_window->Destroy();
    }
    return true;
}

int marinetraffic_pi::GetAPIVersionMajor()
{
    return MY_API_VERSION_MAJOR;
}

int marinetraffic_pi::GetAPIVersionMinor()
{
    return MY_API_VERSION_MINOR;
}

int marinetraffic_pi::GetPlugInVersionMajor()
{
    return PLUGIN_VERSION_MAJOR;
}

int marinetraffic_pi::GetPlugInVersionMinor()
{
    return PLUGIN_VERSION_MINOR;
}

wxString marinetraffic_pi::GetCommonName()
{
    return _("MarineTraffic");
}

wxString marinetraffic_pi::GetShortDescription()
{
    return _("MarineTraffic PlugIn for OpenCPN");
}

wxString marinetraffic_pi::GetLongDescription()
{
    return _("MarineTraffic_pi PlugIn for OpenCPN\n\
             demonstrates PlugIn processing of NMEA messages.");

}

void marinetraffic_pi::SetNMEASentence(wxString &sentence)
{
    //      printf("marinetraffic_pi::SetNMEASentence\n");
    if(m_pdemo_window)
    {
        m_pdemo_window->SetSentence(sentence);
    }
}


void marinetraffic_pi::OnContextMenuItemCallback(int id)
{
    wxLogMessage(_T("marinetraffic_pi OnContextMenuCallBack()"));
    ::wxBell();

    //  Note carefully that this is a "reference to a wxAuiPaneInfo classs instance"
    //  Copy constructor (i.e. wxAuiPaneInfo pane = m_AUImgr->GetPane(m_pdemo_window);) will not work

    wxAuiPaneInfo &pane = m_AUImgr->GetPane(m_pdemo_window);
    if(!pane.IsOk())
        return;

    if(!pane.IsShown())
    {
        //            printf("show\n");
        SetCanvasContextMenuItemViz(m_hide_id, true);
        SetCanvasContextMenuItemViz(m_show_id, false);

        pane.Show(true);
        m_AUImgr->Update();

    }
    else
    {
        //            printf("hide\n");
        SetCanvasContextMenuItemViz(m_hide_id, false);
        SetCanvasContextMenuItemViz(m_show_id, true);

        pane.Show(false);
        m_AUImgr->Update();
    }

    /*
      if(NULL == m_pdemo_window)
      {
            m_pdemo_window = new demoWindow(m_parent_window, wxID_ANY);

            SetCanvasContextMenuItemViz(m_hide_id, true);
            SetCanvasContextMenuItemViz(m_show_id, false);
      }
      else
      {
            m_pdemo_window->Close();
            m_pdemo_window->Destroy();
            m_pdemo_window = NULL;

            SetCanvasContextMenuItemViz(m_hide_id, false);
            SetCanvasContextMenuItemViz(m_show_id, true);
      }
*/
}

void marinetraffic_pi::UpdateAuiStatus(void)
{
    //    This method is called after the PlugIn is initialized
    //    and the frame has done its initial layout, possibly from a saved wxAuiManager "Perspective"
    //    It is a chance for the PlugIn to syncronize itself internally with the state of any Panes that
    //    were added to the frame in the PlugIn ctor.

    //    We use this callback here to keep the context menu selection in sync with the window state


    wxAuiPaneInfo &pane = m_AUImgr->GetPane(m_pdemo_window);
    if(!pane.IsOk())
        return;

    printf("update %d\n",pane.IsShown());

    SetCanvasContextMenuItemViz(m_hide_id, pane.IsShown());
    SetCanvasContextMenuItemViz(m_show_id, !pane.IsShown());

}

bool marinetraffic_pi::RenderOverlay(wxDC &dc, PlugIn_ViewPort *vp)
{
    m_dataReader.draw(dc, vp);
    //    if(dc) {
    //        dc->SetPen(wxPen(color, 3));
    //        dc->SetTextForeground(color);
    //        dc->SetFont( font );
    //    } else {
    //        glLineWidth(3.0);
    //        glColor4ub(color.Red(), color.Green(), color.Blue(), color.Alpha());
    //        m_TexFont.Build( font );
    //    }
    //    if(m_pGribDialog && m_pGRIBOverlayFactory)
    //    {
    //        if(m_pGRIBOverlayFactory->IsReadyToRender())
    //        {
    //            m_pGRIBOverlayFactory->RenderGribOverlay ( dc, vp );
    //            return true;
    //        }
    //        else
    //            return false;
    //    }
    //    else
    return false;
}
void marinetraffic_pi::SetCursorLatLon(double lat, double lon)
{

}
bool marinetraffic_pi::RenderGLOverlay(wxGLContext *pcontext, PlugIn_ViewPort *vp)
{
    /*   if(m_pGribDialog && m_pGRIBOverlayFactory)
      {
            if(m_pGRIBOverlayFactory->IsReadyToRender())
            {
                  m_pGRIBOverlayFactory->RenderGLGribOverlay ( pcontext, vp );
                  return true;
            }
            else
                  return false;
      }
      else*/
    return false;

}
int marinetraffic_pi::GetToolbarToolCount(void)
{
    return 1;
}
void marinetraffic_pi::ShowPreferencesDialog( wxWindow* parent )
{

}
void marinetraffic_pi::OnToolbarToolCallback(int id)
{

}
void marinetraffic_pi::SetPluginMessage(wxString &message_id, wxString &message_body)
{

}
void marinetraffic_pi::SetPositionFixEx(PlugIn_Position_Fix_Ex &pfix)
{
    printf("SetPositionFixEx");
}

void marinetraffic_pi::SetCurrentViewPort(PlugIn_ViewPort &vp)
{
    printf("update %d\n", static_cast<int>(vp.lat_max));
    m_pdemo_window->SetCurrentViewPort(vp);
    m_dataReader.updatePixPositions(vp);
}

//----------------------------------------------------------------
//
//    demo Window Implementation
//
//----------------------------------------------------------------

BEGIN_EVENT_TABLE(demoWindow, wxWindow)
EVT_PAINT ( demoWindow::OnPaint )
EVT_SIZE(demoWindow::OnSize)


END_EVENT_TABLE()

demoWindow::demoWindow(wxWindow *pparent, wxWindowID id)
    :wxWindow(pparent, id, wxPoint(10,10), wxSize(200,470),
              wxSIMPLE_BORDER, _T("MarineTraffic (Beta 0.1)"))
{
    mLat = 0.0;
    mLon = 1.0;
    mSog = 2.0;
    mCog = 3.0;
    mVar = 4.0;
    SetSizeHints(wxSize(-1, -1), wxSize(-1, -1));

    wxFlexGridSizer *fgSizer6;
    fgSizer6 = new wxFlexGridSizer(2, 1, 0, 0);
    fgSizer6->AddGrowableCol(0);
    fgSizer6->AddGrowableRow(0);
    fgSizer6->SetFlexibleDirection(wxBOTH);
    fgSizer6->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);
    wxBoxSizer *bSframe = new wxBoxSizer(wxVERTICAL);

    bSframe->SetMinSize(wxSize(470, -1));
    wxStaticBoxSizer *sbSCoords = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("Coords")), wxVERTICAL);

    wxFlexGridSizer *gSCoords = new wxFlexGridSizer(7, 2, 0, 0);
    gSCoords->AddGrowableCol(1);
    gSCoords->SetFlexibleDirection(wxBOTH);
    gSCoords->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

    wxStaticText *m_latMinText = new wxStaticText(this, wxID_ANY, _("lat min "), wxDefaultPosition, wxDefaultSize, 0);
    m_latMinTCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER);
    m_latMinTCtrl->SetMaxLength(0);
    gSCoords->Add(m_latMinText, 0, wxALL, 5);
    gSCoords->Add(m_latMinTCtrl, 1, wxEXPAND, 5);

    wxStaticText *m_latMaxText = new wxStaticText(this, wxID_ANY, _("lat max "), wxDefaultPosition, wxDefaultSize, 0);
    m_latMaxTCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER);
    m_latMaxTCtrl->SetMaxLength(0);
    gSCoords->Add(m_latMaxText, 0, wxALL, 5);
    gSCoords->Add(m_latMaxTCtrl, 1, wxEXPAND, 5);

    wxStaticText *m_lonMinText = new wxStaticText(this, wxID_ANY, _("lon min "), wxDefaultPosition, wxDefaultSize, 0);
    m_lonMinTCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER);
    m_lonMinTCtrl->SetMaxLength(0);
    gSCoords->Add(m_lonMinText, 0, wxALL, 5);
    gSCoords->Add(m_lonMinTCtrl, 1, wxEXPAND, 5);

    wxStaticText *m_lonMaxText = new wxStaticText(this, wxID_ANY, _("lon max "), wxDefaultPosition, wxDefaultSize, 0);
    m_lonMaxTCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER);
    m_lonMaxTCtrl->SetMaxLength(0);
    gSCoords->Add(m_lonMaxText, 0, wxALL, 5);
    gSCoords->Add(m_lonMaxTCtrl, 1, wxEXPAND, 5);

    wxStaticText *m_latCentText = new wxStaticText(this, wxID_ANY, _("lat cent "), wxDefaultPosition, wxDefaultSize, 0);
    m_latCentTCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER);
    m_latCentTCtrl->SetMaxLength(0);
    gSCoords->Add(m_latCentText, 0, wxALL, 5);
    gSCoords->Add(m_latCentTCtrl, 1, wxEXPAND, 5);

    wxStaticText *m_lonCentText = new wxStaticText(this, wxID_ANY, _("lon cent "), wxDefaultPosition, wxDefaultSize, 0);
    m_lonCentTCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER);
    m_lonCentTCtrl->SetMaxLength(0);
    gSCoords->Add(m_lonCentText, 0, wxALL, 5);
    gSCoords->Add(m_lonCentTCtrl, 1, wxEXPAND, 5);

    wxStaticText *m_zoomText = new wxStaticText(this, wxID_ANY, _("zoom "), wxDefaultPosition, wxDefaultSize, 0);
    m_zoomTCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER);
    m_zoomTCtrl->SetMaxLength(0);
    m_zoomTCtrl->SetValue(wxString("11"));
    gSCoords->Add(m_zoomText, 0, wxALL, 5);
    gSCoords->Add(m_zoomTCtrl, 1, wxEXPAND, 5);

    sbSCoords->Add(gSCoords, 1, wxEXPAND, 0);
    bSframe->Add(sbSCoords, 0, wxEXPAND|wxFIXED_MINSIZE, 0);

    wxStdDialogButtonSizer *m_sdbUpdateBtns = new wxStdDialogButtonSizer();
    wxButton *m_sdbSizerBtnsUpdate = new wxButton(this, wxID_ANY, _("Update"), wxDefaultPosition, wxDefaultSize, 0);
    m_sdbUpdateBtns->Add(m_sdbSizerBtnsUpdate, 0, wxEXPAND|wxCenter, 0);
    m_sdbUpdateBtns->Realize();

    // Proxy{
    wxStaticBoxSizer *sbSProxy = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("Proxy")), wxVERTICAL);

    wxFlexGridSizer *gSProxy = new wxFlexGridSizer(3, 2, 0, 0);
    gSProxy->AddGrowableCol(1);
    gSProxy->SetFlexibleDirection(wxBOTH);
    gSProxy->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

    wxStaticText *m_proxyText = new wxStaticText(this, wxID_ANY, _("proxy "), wxDefaultPosition, wxDefaultSize, 0);
    m_proxySiteTCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER);
    m_proxySiteTCtrl->SetMaxLength(0);
    m_proxySiteTCtrl->SetValue(wxString("127.0.0.1"));
    gSProxy->Add(m_proxyText, 0, wxALL, 5);
    gSProxy->Add(m_proxySiteTCtrl, 1, wxEXPAND, 5);

    wxStaticText *m_proxyPortText = new wxStaticText(this, wxID_ANY, _("port "), wxDefaultPosition, wxDefaultSize, 0);
    m_proxyPortTCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER);
    m_proxyPortTCtrl->SetMaxLength(0);
    m_proxyPortTCtrl->SetValue(wxString("8888"));
    gSProxy->Add(m_proxyPortText, 0, wxALL, 5);
    gSProxy->Add(m_proxyPortTCtrl, 1, wxEXPAND, 5);

    wxStaticText *m_enableProxyText = new wxStaticText(this, wxID_ANY, _("enable "), wxDefaultPosition, wxDefaultSize, 0);
    m_enableProxyBox = new wxCheckBox(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize);
    gSProxy->Add(m_enableProxyText, 0, wxALL, 5);
    gSProxy->Add(m_enableProxyBox, 1, wxEXPAND, 5);

    sbSProxy->Add(gSProxy, 1, wxEXPAND, 0);
    bSframe->Add(sbSProxy, 1, wxEXPAND|wxFIXED_MINSIZE, 0);
    // }Proxy

    // Settings{
    wxStaticBoxSizer *sbSSettings = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("Settings")), wxVERTICAL);

    wxFlexGridSizer *gSSettings = new wxFlexGridSizer(4, 2, 0, 0);
    gSSettings->AddGrowableCol(1);
    gSSettings->SetFlexibleDirection(wxBOTH);
    gSSettings->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

    wxStaticText *m_lastUpdText = new wxStaticText(this, wxID_ANY, _("last update "), wxDefaultPosition, wxDefaultSize, 0);
    wxTextCtrl *m_lastUpdTCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER);
    m_lastUpdTCtrl->SetMaxLength(0);
    gSSettings->Add(m_lastUpdText, 0, wxALL, 5);
    gSSettings->Add(m_lastUpdTCtrl, 1, wxEXPAND, 5);

    wxStaticText *m_errorMsgText = new wxStaticText(this, wxID_ANY, _("error msg "), wxDefaultPosition, wxDefaultSize, 0);
    wxTextCtrl *m_errorMsgTCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER);
    m_errorMsgTCtrl->SetMaxLength(0);
    gSSettings->Add(m_errorMsgText, 0, wxALL, 5);
    gSSettings->Add(m_errorMsgTCtrl, 1, wxEXPAND, 5);

    wxStaticText *m_updTimerText = new wxStaticText(this, wxID_ANY, _("upd timer "), wxDefaultPosition, wxDefaultSize, 0);
    wxTextCtrl *m_updTimerTCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER);
    m_updTimerTCtrl->SetMaxLength(0);
    gSSettings->Add(m_updTimerText, 0, wxALL, 5);
    gSSettings->Add(m_updTimerTCtrl, 1, wxEXPAND, 5);

    wxStaticText *m_enableUpdText = new wxStaticText(this, wxID_ANY, _("enable "), wxDefaultPosition, wxDefaultSize, 0);
    wxTextCtrl *m_enableUpdTCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER);
    m_enableUpdTCtrl->SetMaxLength(0);
    gSSettings->Add(m_enableUpdText, 0, wxALL, 5);
    gSSettings->Add(m_enableUpdTCtrl, 1, wxEXPAND, 5);

    sbSSettings->Add(gSSettings, 1, wxEXPAND, 0);
    bSframe->Add(sbSSettings, 2, wxEXPAND|wxFIXED_MINSIZE, 0);
    // }Settings

    fgSizer6->Add(bSframe, 0, wxEXPAND, 5);
    fgSizer6->Add(m_sdbUpdateBtns, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

    SetSizer(fgSizer6);
    Layout();

    Centre(wxBOTH);

    m_sdbSizerBtnsUpdate->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(demoWindow::updateDataReader), NULL, this);
    m_pDataReader = NULL;
}

demoWindow::~demoWindow()
{
}

void demoWindow::setDataReader(CDataReader *dataReader)
{
    m_pDataReader = dataReader;
}

void demoWindow::updateDataReader(wxCommandEvent &event)
{
    if (m_pDataReader)
    {
        double sw_y = wxAtof(m_latMinTCtrl->GetValue());
        double sw_x = wxAtof(m_lonMinTCtrl->GetValue());
        double ne_y = wxAtof(m_latMaxTCtrl->GetValue());
        double ne_x = wxAtof(m_lonMaxTCtrl->GetValue());
        int zoom = wxAtoi(m_zoomTCtrl->GetValue());
        int station = 0;
        double centery = wxAtof(m_latCentTCtrl->GetValue());
        double centerx = wxAtof(m_lonCentTCtrl->GetValue());
        if (m_enableProxyBox->IsChecked())
        {
            wxString proxySite = m_proxySiteTCtrl->GetValue();
            int proxyPort = wxAtoi(m_proxyPortTCtrl->GetValue());
            m_pDataReader->useProxy(true, proxySite.ToStdString(), proxyPort);

        }
        else
        {
            m_pDataReader->useProxy(false);
        }
        m_pDataReader->readData(sw_x, sw_y, ne_x, ne_y, zoom, station, centerx, centery);

        m_pDataReader->updatePixPositions(m_lastVp);
    }
}

void demoWindow::SetCurrentViewPort(PlugIn_ViewPort &vp)
{
    m_latMinTCtrl->SetValue(wxString::FromDouble(vp.lat_min));
    m_latMaxTCtrl->SetValue(wxString::FromDouble(vp.lat_max));
    m_latCentTCtrl->SetValue(wxString::FromDouble(vp.lat_min + (vp.lat_max - vp.lat_min) / 2));
    m_lonMinTCtrl->SetValue(wxString::FromDouble(vp.lon_min));
    m_lonMaxTCtrl->SetValue(wxString::FromDouble(vp.lon_max));
    m_lonCentTCtrl->SetValue(wxString::FromDouble(vp.lon_min + (vp.lon_max - vp.lon_min) / 2));
    m_lastVp = vp;
}

void demoWindow::OnSize(wxSizeEvent& event)
{
    printf("demoWindow OnSize()\n");
}


void demoWindow::SetSentence(wxString &sentence)
{

}

void demoWindow::OnPaint(wxPaintEvent& event)
{
    wxLogMessage(_T("demo_pi onpaint"));

    wxPaintDC dc ( this );

    //      printf("onpaint\n");

    {
        dc.Clear();

        wxString data;
        data.Printf(_T("Lat: %g "), mLat);
        dc.DrawText(data, 10, 10);

        data.Printf(_T("Lon: %g"), mLon);
        dc.DrawText(data, 10, 40);

        data.Printf(_T("Sog: %g"), mSog);
        dc.DrawText(data, 10, 70);

        data.Printf(_T("Cog: %g"), mCog);
        dc.DrawText(data, 10, 100);
    }
}
