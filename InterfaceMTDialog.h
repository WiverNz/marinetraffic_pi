///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan  9 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __INTERFACEMTDIALOG_H__
#define __INTERFACEMTDIALOG_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/scrolwin.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/checkbox.h>
#include <wx/notebook.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class InterfaceMTDialog
///////////////////////////////////////////////////////////////////////////////
class InterfaceMTDialog : public wxDialog 
{
	private:
	
	protected:
		wxNotebook* m_mainNotebook;
		wxScrolledWindow* m_coordsScrolledWindow;
		wxStaticText* m_latMinStaticText;
		wxTextCtrl* m_latMinTCtrl;
		wxStaticText* m_latMaxStaticText;
		wxTextCtrl* m_latMaxTCtrl;
		wxStaticText* m_lonMinStaticText;
		wxTextCtrl* m_lonMinTCtrl;
		wxStaticText* m_lonMaxStaticText;
		wxTextCtrl* m_lonMaxTCtrl;
		wxStaticText* m_latCentStaticText;
		wxTextCtrl* m_latCentTCtrl;
		wxStaticText* m_lonCentStaticText;
		wxTextCtrl* m_lonCentTCtrl;
		wxStaticText* m_zoomStaticText;
		wxTextCtrl* m_zoomTCtrl;
		wxScrolledWindow* m_proxyScrolledWindow;
		wxStaticText* m_proxyIPStaticText;
		wxTextCtrl* m_proxySiteTCtrl;
		wxStaticText* m_proxyPortStaticText;
		wxTextCtrl* m_proxyPortTCtrl;
		wxStaticText* m_proxyEnableStaticText;
		wxCheckBox* m_enableProxyBox;
		wxScrolledWindow* m_settingsSrolledWindow;
		wxStaticText* m_lastUpdateStaticText;
		wxTextCtrl* m_lastUpdTCtrl;
		wxStaticText* m_errorMsgStaticText;
		wxTextCtrl* m_errorMsgTCtrl;
		wxStaticText* m_updTimerStaticText;
		wxTextCtrl* m_updTimerTCtrl;
		wxStaticText* m_enableStaticText;
		wxTextCtrl* m_enableUpdTCtrl;
		wxButton* m_sdbSizerBtnsUpdate;
		
		// Virtual event handlers, overide them in your derived class
		virtual void onPaint( wxPaintEvent& event ) { event.Skip(); }
		virtual void updateDataReader( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		InterfaceMTDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 218,360 ), long style = wxDEFAULT_DIALOG_STYLE ); 
		~InterfaceMTDialog();
	
};

#endif //__INTERFACEMTDIALOG_H__
