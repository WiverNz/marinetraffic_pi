///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan  9 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "InterfaceMTDialog.h"

///////////////////////////////////////////////////////////////////////////

InterfaceMTDialog::InterfaceMTDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 2, 1, 0, 0 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_mainNotebook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_coordsScrolledWindow = new wxScrolledWindow( m_mainNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL, wxT("Coords") );
	m_coordsScrolledWindow->SetScrollRate( 5, 5 );
	wxFlexGridSizer* fgCoordsSizer;
	fgCoordsSizer = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgCoordsSizer->SetFlexibleDirection( wxBOTH );
	fgCoordsSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_ALL );
	
	m_latMinStaticText = new wxStaticText( m_coordsScrolledWindow, wxID_ANY, wxT("lat min"), wxDefaultPosition, wxDefaultSize, 0 );
	m_latMinStaticText->Wrap( -1 );
	fgCoordsSizer->Add( m_latMinStaticText, 0, wxALL, 5 );
	
	m_latMinTCtrl = new wxTextCtrl( m_coordsScrolledWindow, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgCoordsSizer->Add( m_latMinTCtrl, 0, wxALL, 5 );
	
	m_latMaxStaticText = new wxStaticText( m_coordsScrolledWindow, wxID_ANY, wxT("lat max"), wxDefaultPosition, wxDefaultSize, 0 );
	m_latMaxStaticText->Wrap( -1 );
	fgCoordsSizer->Add( m_latMaxStaticText, 0, wxALL, 5 );
	
	m_latMaxTCtrl = new wxTextCtrl( m_coordsScrolledWindow, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgCoordsSizer->Add( m_latMaxTCtrl, 0, wxALL, 5 );
	
	m_lonMinStaticText = new wxStaticText( m_coordsScrolledWindow, wxID_ANY, wxT("lon min"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lonMinStaticText->Wrap( -1 );
	fgCoordsSizer->Add( m_lonMinStaticText, 0, wxALL, 5 );
	
	m_lonMinTCtrl = new wxTextCtrl( m_coordsScrolledWindow, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgCoordsSizer->Add( m_lonMinTCtrl, 0, wxALL, 5 );
	
	m_lonMaxStaticText = new wxStaticText( m_coordsScrolledWindow, wxID_ANY, wxT("lon max"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lonMaxStaticText->Wrap( -1 );
	fgCoordsSizer->Add( m_lonMaxStaticText, 0, wxALL, 5 );
	
	m_lonMaxTCtrl = new wxTextCtrl( m_coordsScrolledWindow, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgCoordsSizer->Add( m_lonMaxTCtrl, 0, wxALL, 5 );
	
	m_latCentStaticText = new wxStaticText( m_coordsScrolledWindow, wxID_ANY, wxT("lat cent"), wxDefaultPosition, wxDefaultSize, 0 );
	m_latCentStaticText->Wrap( -1 );
	fgCoordsSizer->Add( m_latCentStaticText, 0, wxALL, 5 );
	
	m_latCentTCtrl = new wxTextCtrl( m_coordsScrolledWindow, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgCoordsSizer->Add( m_latCentTCtrl, 0, wxALL, 5 );
	
	m_lonCentStaticText = new wxStaticText( m_coordsScrolledWindow, wxID_ANY, wxT("lon cent"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lonCentStaticText->Wrap( -1 );
	fgCoordsSizer->Add( m_lonCentStaticText, 0, wxALL, 5 );
	
	m_lonCentTCtrl = new wxTextCtrl( m_coordsScrolledWindow, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgCoordsSizer->Add( m_lonCentTCtrl, 0, wxALL, 5 );
	
	m_zoomStaticText = new wxStaticText( m_coordsScrolledWindow, wxID_ANY, wxT("zoom"), wxDefaultPosition, wxDefaultSize, 0 );
	m_zoomStaticText->Wrap( -1 );
	fgCoordsSizer->Add( m_zoomStaticText, 0, wxALL, 5 );
	
	m_zoomTCtrl = new wxTextCtrl( m_coordsScrolledWindow, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgCoordsSizer->Add( m_zoomTCtrl, 0, wxALL, 5 );
	
	
	m_coordsScrolledWindow->SetSizer( fgCoordsSizer );
	m_coordsScrolledWindow->Layout();
	fgCoordsSizer->Fit( m_coordsScrolledWindow );
	m_mainNotebook->AddPage( m_coordsScrolledWindow, wxT("Coords"), true );
	m_proxyScrolledWindow = new wxScrolledWindow( m_mainNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL, wxT("Proxy") );
	m_proxyScrolledWindow->SetScrollRate( 5, 5 );
	wxFlexGridSizer* fgProxySizer;
	fgProxySizer = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgProxySizer->SetFlexibleDirection( wxBOTH );
	fgProxySizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_proxyIPStaticText = new wxStaticText( m_proxyScrolledWindow, wxID_ANY, wxT("proxy"), wxDefaultPosition, wxDefaultSize, 0 );
	m_proxyIPStaticText->Wrap( -1 );
	fgProxySizer->Add( m_proxyIPStaticText, 0, wxALL, 5 );
	
	m_proxySiteTCtrl = new wxTextCtrl( m_proxyScrolledWindow, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgProxySizer->Add( m_proxySiteTCtrl, 0, wxALL, 5 );
	
	m_proxyPortStaticText = new wxStaticText( m_proxyScrolledWindow, wxID_ANY, wxT("port"), wxDefaultPosition, wxDefaultSize, 0 );
	m_proxyPortStaticText->Wrap( -1 );
	fgProxySizer->Add( m_proxyPortStaticText, 0, wxALL, 5 );
	
	m_proxyPortTCtrl = new wxTextCtrl( m_proxyScrolledWindow, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgProxySizer->Add( m_proxyPortTCtrl, 0, wxALL, 5 );
	
	m_proxyEnableStaticText = new wxStaticText( m_proxyScrolledWindow, wxID_ANY, wxT("enable"), wxDefaultPosition, wxDefaultSize, 0 );
	m_proxyEnableStaticText->Wrap( -1 );
	fgProxySizer->Add( m_proxyEnableStaticText, 0, wxALL, 5 );
	
	m_enableProxyBox = new wxCheckBox( m_proxyScrolledWindow, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgProxySizer->Add( m_enableProxyBox, 0, wxALL, 5 );
	
	
	m_proxyScrolledWindow->SetSizer( fgProxySizer );
	m_proxyScrolledWindow->Layout();
	fgProxySizer->Fit( m_proxyScrolledWindow );
	m_mainNotebook->AddPage( m_proxyScrolledWindow, wxT("Proxy"), false );
	m_settingsSrolledWindow = new wxScrolledWindow( m_mainNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_settingsSrolledWindow->SetScrollRate( 5, 5 );
	wxFlexGridSizer* fgSettingsSizer;
	fgSettingsSizer = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSettingsSizer->SetFlexibleDirection( wxBOTH );
	fgSettingsSizer->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_lastUpdateStaticText = new wxStaticText( m_settingsSrolledWindow, wxID_ANY, wxT("last update"), wxDefaultPosition, wxDefaultSize, 0 );
	m_lastUpdateStaticText->Wrap( -1 );
	fgSettingsSizer->Add( m_lastUpdateStaticText, 0, wxALL, 5 );
	
	m_lastUpdTCtrl = new wxTextCtrl( m_settingsSrolledWindow, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSettingsSizer->Add( m_lastUpdTCtrl, 0, wxALL, 5 );
	
	m_errorMsgStaticText = new wxStaticText( m_settingsSrolledWindow, wxID_ANY, wxT("error msg"), wxDefaultPosition, wxDefaultSize, 0 );
	m_errorMsgStaticText->Wrap( -1 );
	fgSettingsSizer->Add( m_errorMsgStaticText, 0, wxALL, 5 );
	
	m_errorMsgTCtrl = new wxTextCtrl( m_settingsSrolledWindow, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSettingsSizer->Add( m_errorMsgTCtrl, 0, wxALL, 5 );
	
	m_updTimerStaticText = new wxStaticText( m_settingsSrolledWindow, wxID_ANY, wxT("upd timer"), wxDefaultPosition, wxDefaultSize, 0 );
	m_updTimerStaticText->Wrap( -1 );
	fgSettingsSizer->Add( m_updTimerStaticText, 0, wxALL, 5 );
	
	m_updTimerTCtrl = new wxTextCtrl( m_settingsSrolledWindow, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSettingsSizer->Add( m_updTimerTCtrl, 0, wxALL, 5 );
	
	m_enableStaticText = new wxStaticText( m_settingsSrolledWindow, wxID_ANY, wxT("enable"), wxDefaultPosition, wxDefaultSize, 0 );
	m_enableStaticText->Wrap( -1 );
	fgSettingsSizer->Add( m_enableStaticText, 0, wxALL, 5 );
	
	m_enableUpdTCtrl = new wxTextCtrl( m_settingsSrolledWindow, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSettingsSizer->Add( m_enableUpdTCtrl, 0, wxALL, 5 );
	
	
	m_settingsSrolledWindow->SetSizer( fgSettingsSizer );
	m_settingsSrolledWindow->Layout();
	fgSettingsSizer->Fit( m_settingsSrolledWindow );
	m_mainNotebook->AddPage( m_settingsSrolledWindow, wxT("Settings"), false );
	
	fgSizer1->Add( m_mainNotebook, 1, wxEXPAND | wxALL, 5 );
	
	m_sdbSizerBtnsUpdate = new wxButton( this, wxID_ANY, wxT("Update"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer1->Add( m_sdbSizerBtnsUpdate, 0, wxALIGN_CENTER|wxALL|wxEXPAND, 5 );
	
	
	this->SetSizer( fgSizer1 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_PAINT, wxPaintEventHandler( InterfaceMTDialog::onPaint ) );
	m_sdbSizerBtnsUpdate->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( InterfaceMTDialog::updateDataReader ), NULL, this );
}

InterfaceMTDialog::~InterfaceMTDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_PAINT, wxPaintEventHandler( InterfaceMTDialog::onPaint ) );
	m_sdbSizerBtnsUpdate->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( InterfaceMTDialog::updateDataReader ), NULL, this );
	
}
