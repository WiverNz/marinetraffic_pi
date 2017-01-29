#include "MarineTrafficDialog.h"

///////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------
//
//    MarineTraffic dialog Implementation
//
//----------------------------------------------------------------

//BEGIN_EVENT_TABLE(demoWindow, wxWindow)
//EVT_PAINT ( demoWindow::OnPaint )
//EVT_SIZE(demoWindow::OnSize)


//END_EVENT_TABLE()


//demoWindow::demoWindow(wxWindow *pparent, wxWindowID id)
//    :wxWindow(pparent, id, wxPoint(10,10), wxSize(200,470),
//              wxSIMPLE_BORDER, _T("MarineTraffic (Beta 0.1)"))
//{
//    mLat = 0.0;
//    mLon = 1.0;
//    mSog = 2.0;
//    mCog = 3.0;
//    mVar = 4.0;
//    SetSizeHints(wxSize(-1, -1), wxSize(-1, -1));

//    wxFlexGridSizer *fgSizer6;
//    fgSizer6 = new wxFlexGridSizer(2, 1, 0, 0);
//    fgSizer6->AddGrowableCol(0);
//    fgSizer6->AddGrowableRow(0);
//    fgSizer6->SetFlexibleDirection(wxBOTH);
//    fgSizer6->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);
//    wxBoxSizer *bSframe = new wxBoxSizer(wxVERTICAL);

//    bSframe->SetMinSize(wxSize(470, -1));
//    wxStaticBoxSizer *sbSCoords = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("Coords")), wxVERTICAL);

//    wxFlexGridSizer *gSCoords = new wxFlexGridSizer(7, 2, 0, 0);
//    gSCoords->AddGrowableCol(1);
//    gSCoords->SetFlexibleDirection(wxBOTH);
//    gSCoords->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

//    wxStaticText *m_latMinText = new wxStaticText(this, wxID_ANY, _("lat min "), wxDefaultPosition, wxDefaultSize, 0);
//    m_latMinTCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER);
//    m_latMinTCtrl->SetMaxLength(0);
//    gSCoords->Add(m_latMinText, 0, wxALL, 5);
//    gSCoords->Add(m_latMinTCtrl, 1, wxEXPAND, 5);

//    wxStaticText *m_latMaxText = new wxStaticText(this, wxID_ANY, _("lat max "), wxDefaultPosition, wxDefaultSize, 0);
//    m_latMaxTCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER);
//    m_latMaxTCtrl->SetMaxLength(0);
//    gSCoords->Add(m_latMaxText, 0, wxALL, 5);
//    gSCoords->Add(m_latMaxTCtrl, 1, wxEXPAND, 5);

//    wxStaticText *m_lonMinText = new wxStaticText(this, wxID_ANY, _("lon min "), wxDefaultPosition, wxDefaultSize, 0);
//    m_lonMinTCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER);
//    m_lonMinTCtrl->SetMaxLength(0);
//    gSCoords->Add(m_lonMinText, 0, wxALL, 5);
//    gSCoords->Add(m_lonMinTCtrl, 1, wxEXPAND, 5);

//    wxStaticText *m_lonMaxText = new wxStaticText(this, wxID_ANY, _("lon max "), wxDefaultPosition, wxDefaultSize, 0);
//    m_lonMaxTCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER);
//    m_lonMaxTCtrl->SetMaxLength(0);
//    gSCoords->Add(m_lonMaxText, 0, wxALL, 5);
//    gSCoords->Add(m_lonMaxTCtrl, 1, wxEXPAND, 5);

//    wxStaticText *m_latCentText = new wxStaticText(this, wxID_ANY, _("lat cent "), wxDefaultPosition, wxDefaultSize, 0);
//    m_latCentTCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER);
//    m_latCentTCtrl->SetMaxLength(0);
//    gSCoords->Add(m_latCentText, 0, wxALL, 5);
//    gSCoords->Add(m_latCentTCtrl, 1, wxEXPAND, 5);

//    wxStaticText *m_lonCentText = new wxStaticText(this, wxID_ANY, _("lon cent "), wxDefaultPosition, wxDefaultSize, 0);
//    m_lonCentTCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER);
//    m_lonCentTCtrl->SetMaxLength(0);
//    gSCoords->Add(m_lonCentText, 0, wxALL, 5);
//    gSCoords->Add(m_lonCentTCtrl, 1, wxEXPAND, 5);

//    wxStaticText *m_zoomText = new wxStaticText(this, wxID_ANY, _("zoom "), wxDefaultPosition, wxDefaultSize, 0);
//    m_zoomTCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER);
//    m_zoomTCtrl->SetMaxLength(0);
//    m_zoomTCtrl->SetValue(wxString("11"));
//    gSCoords->Add(m_zoomText, 0, wxALL, 5);
//    gSCoords->Add(m_zoomTCtrl, 1, wxEXPAND, 5);

//    sbSCoords->Add(gSCoords, 1, wxEXPAND, 0);
//    bSframe->Add(sbSCoords, 0, wxEXPAND|wxFIXED_MINSIZE, 0);

//    wxStdDialogButtonSizer *m_sdbUpdateBtns = new wxStdDialogButtonSizer();
//    wxButton *m_sdbSizerBtnsUpdate = new wxButton(this, wxID_ANY, _("Update"), wxDefaultPosition, wxDefaultSize, 0);
//    m_sdbUpdateBtns->Add(m_sdbSizerBtnsUpdate, 0, wxEXPAND|wxCenter, 0);
//    m_sdbUpdateBtns->Realize();

//    // Proxy{
//    wxStaticBoxSizer *sbSProxy = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("Proxy")), wxVERTICAL);

//    wxFlexGridSizer *gSProxy = new wxFlexGridSizer(3, 2, 0, 0);
//    gSProxy->AddGrowableCol(1);
//    gSProxy->SetFlexibleDirection(wxBOTH);
//    gSProxy->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

//    wxStaticText *m_proxyText = new wxStaticText(this, wxID_ANY, _("proxy "), wxDefaultPosition, wxDefaultSize, 0);
//    m_proxySiteTCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER);
//    m_proxySiteTCtrl->SetMaxLength(0);
//    m_proxySiteTCtrl->SetValue(wxString("127.0.0.1"));
//    gSProxy->Add(m_proxyText, 0, wxALL, 5);
//    gSProxy->Add(m_proxySiteTCtrl, 1, wxEXPAND, 5);

//    wxStaticText *m_proxyPortText = new wxStaticText(this, wxID_ANY, _("port "), wxDefaultPosition, wxDefaultSize, 0);
//    m_proxyPortTCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER);
//    m_proxyPortTCtrl->SetMaxLength(0);
//    m_proxyPortTCtrl->SetValue(wxString("8888"));
//    gSProxy->Add(m_proxyPortText, 0, wxALL, 5);
//    gSProxy->Add(m_proxyPortTCtrl, 1, wxEXPAND, 5);

//    wxStaticText *m_enableProxyText = new wxStaticText(this, wxID_ANY, _("enable "), wxDefaultPosition, wxDefaultSize, 0);
//    m_enableProxyBox = new wxCheckBox(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize);
//    gSProxy->Add(m_enableProxyText, 0, wxALL, 5);
//    gSProxy->Add(m_enableProxyBox, 1, wxEXPAND, 5);

//    sbSProxy->Add(gSProxy, 1, wxEXPAND, 0);
//    bSframe->Add(sbSProxy, 1, wxEXPAND|wxFIXED_MINSIZE, 0);
//    // }Proxy

//    // Settings{
//    wxStaticBoxSizer *sbSSettings = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("Settings")), wxVERTICAL);

//    wxFlexGridSizer *gSSettings = new wxFlexGridSizer(4, 2, 0, 0);
//    gSSettings->AddGrowableCol(1);
//    gSSettings->SetFlexibleDirection(wxBOTH);
//    gSSettings->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

//    wxStaticText *m_lastUpdText = new wxStaticText(this, wxID_ANY, _("last update "), wxDefaultPosition, wxDefaultSize, 0);
//    wxTextCtrl *m_lastUpdTCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER);
//    m_lastUpdTCtrl->SetMaxLength(0);
//    gSSettings->Add(m_lastUpdText, 0, wxALL, 5);
//    gSSettings->Add(m_lastUpdTCtrl, 1, wxEXPAND, 5);

//    wxStaticText *m_errorMsgText = new wxStaticText(this, wxID_ANY, _("error msg "), wxDefaultPosition, wxDefaultSize, 0);
//    wxTextCtrl *m_errorMsgTCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER);
//    m_errorMsgTCtrl->SetMaxLength(0);
//    gSSettings->Add(m_errorMsgText, 0, wxALL, 5);
//    gSSettings->Add(m_errorMsgTCtrl, 1, wxEXPAND, 5);

//    wxStaticText *m_updTimerText = new wxStaticText(this, wxID_ANY, _("upd timer "), wxDefaultPosition, wxDefaultSize, 0);
//    wxTextCtrl *m_updTimerTCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER);
//    m_updTimerTCtrl->SetMaxLength(0);
//    gSSettings->Add(m_updTimerText, 0, wxALL, 5);
//    gSSettings->Add(m_updTimerTCtrl, 1, wxEXPAND, 5);

//    wxStaticText *m_enableUpdText = new wxStaticText(this, wxID_ANY, _("enable "), wxDefaultPosition, wxDefaultSize, 0);
//    wxTextCtrl *m_enableUpdTCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER);
//    m_enableUpdTCtrl->SetMaxLength(0);
//    gSSettings->Add(m_enableUpdText, 0, wxALL, 5);
//    gSSettings->Add(m_enableUpdTCtrl, 1, wxEXPAND, 5);

//    sbSSettings->Add(gSSettings, 1, wxEXPAND, 0);
//    bSframe->Add(sbSSettings, 2, wxEXPAND|wxFIXED_MINSIZE, 0);
//    // }Settings

//    fgSizer6->Add(bSframe, 0, wxEXPAND, 5);
//    fgSizer6->Add(m_sdbUpdateBtns, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

//    SetSizer(fgSizer6);
//    Layout();

//    Centre(wxBOTH);

//    m_sdbSizerBtnsUpdate->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(demoWindow::updateDataReader), NULL, this);
//    m_pDataReader = NULL;
//}

void MarineTrafficDialog::setDataReader(CDataReader *dataReader)
{
    m_pDataReader = dataReader;
}

void MarineTrafficDialog::updateDataReader(wxCommandEvent &event)
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

void MarineTrafficDialog::SetCurrentViewPort(PlugIn_ViewPort &vp)
{
    auto setCtrlText = [] (wxTextCtrl *textCtrl, wxString &&string) -> void
    {
        if (textCtrl != nullptr)
        {
            textCtrl->SetValue(string);
        }
    };
    setCtrlText(m_latMinTCtrl, wxString::FromDouble(vp.lat_min));
    setCtrlText(m_latMaxTCtrl, wxString::FromDouble(vp.lat_max));
    setCtrlText(m_latCentTCtrl, wxString::FromDouble(vp.lat_min + (vp.lat_max - vp.lat_min) / 2));
    setCtrlText(m_lonMinTCtrl, wxString::FromDouble(vp.lon_min));
    setCtrlText(m_lonMaxTCtrl, wxString::FromDouble(vp.lon_max));
    setCtrlText(m_lonCentTCtrl, wxString::FromDouble(vp.lon_min + (vp.lon_max - vp.lon_min) / 2));
    m_lastVp = vp;
}

void MarineTrafficDialog::OnSize(wxSizeEvent& event)
{
    printf("demoWindow OnSize()\n");
}


void MarineTrafficDialog::SetSentence(wxString &sentence)
{

}

void MarineTrafficDialog::OnPaint(wxPaintEvent& event)
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
