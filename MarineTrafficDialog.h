#ifndef __MARINETRAFFICDIALOG_H__
#define __MARINETRAFFICDIALOG_H__

#include "InterfaceMTDialog.h"
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class MarineTrafficDialog
///////////////////////////////////////////////////////////////////////////////
class MarineTrafficDialog : public InterfaceMTDialog
{
public:
    MarineTrafficDialog(wxWindow* parent, wxWindowID id = wxID_ANY) : InterfaceMTDialog(parent, id) { }
protected:
    virtual void updateDataReader(wxCommandEvent &event);
    virtual void OnPaint(wxPaintEvent& event);

    PlugIn_ViewPort m_lastVp;
    CDataReader *m_pDataReader = nullptr;

    wxTextCtrl *m_proxySiteTCtrl = nullptr;
    wxTextCtrl *m_proxyPortTCtrl = nullptr;
    wxCheckBox *m_enableProxyBox = nullptr;
public:
    void SetCurrentViewPort(PlugIn_ViewPort &vp);
    void SetSentence(wxString &sentence);
    void OnSize(wxSizeEvent& event);
    void setDataReader(CDataReader *dataReader);

    wxString          m_NMEASentence;
    double            mLat, mLon, mSog, mCog, mVar;

    DECLARE_EVENT_TABLE()
};

#endif //__MARINETRAFFICDIALOG_H__
