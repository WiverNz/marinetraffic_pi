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
    m_marineDialog = NULL;

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

    m_marineDialog = new demoWindow(m_parent_window, wxID_ANY);

    m_AUImgr = GetFrameAuiManager();
    m_AUImgr->AddPane(m_marineDialog);
    m_AUImgr->GetPane(m_marineDialog).Name(_T("MarineTraffic"));

    m_AUImgr->GetPane(m_marineDialog).Float();
    m_AUImgr->GetPane(m_marineDialog).FloatingPosition(300,30);

    m_AUImgr->GetPane(m_marineDialog).Caption(_T("MarineTraffic"));
    m_AUImgr->GetPane(m_marineDialog).CaptionVisible(true);
    m_AUImgr->GetPane(m_marineDialog).GripperTop(true);
    m_AUImgr->GetPane(m_marineDialog).CloseButton(true);
    m_AUImgr->GetPane(m_marineDialog).Show(true);
    m_AUImgr->Update();
    m_marineDialog->setDataReader(&m_dataReader);
    return (WANTS_OVERLAY_CALLBACK | WANTS_ONPAINT_VIEWPORT |
            INSTALLS_CONTEXTMENU_ITEMS     |
            WANTS_NMEA_SENTENCES           |
            USES_AUI_MANAGER
            );
}

bool marinetraffic_pi::DeInit(void)
{
    m_AUImgr->DetachPane(m_marineDialog);
    if(m_marineDialog)
    {
        m_marineDialog->Close();
        m_marineDialog->Destroy();
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
    if(m_marineDialog)
    {
        m_marineDialog->SetSentence(sentence);
    }
}


void marinetraffic_pi::OnContextMenuItemCallback(int id)
{
    wxLogMessage(_T("marinetraffic_pi OnContextMenuCallBack()"));
    ::wxBell();

    //  Note carefully that this is a "reference to a wxAuiPaneInfo classs instance"
    //  Copy constructor (i.e. wxAuiPaneInfo pane = m_AUImgr->GetPane(m_marineDialog);) will not work

    wxAuiPaneInfo &pane = m_AUImgr->GetPane(m_marineDialog);
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
      if(NULL == m_marineDialog)
      {
            m_marineDialog = new demoWindow(m_parent_window, wxID_ANY);

            SetCanvasContextMenuItemViz(m_hide_id, true);
            SetCanvasContextMenuItemViz(m_show_id, false);
      }
      else
      {
            m_marineDialog->Close();
            m_marineDialog->Destroy();
            m_marineDialog = NULL;

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


    wxAuiPaneInfo &pane = m_AUImgr->GetPane(m_marineDialog);
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
    m_marineDialog->SetCurrentViewPort(vp);
    m_dataReader.updatePixPositions(vp);
}
