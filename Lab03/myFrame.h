///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/panel.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/scrolbar.h>
#include <wx/gauge.h>
#include <wx/textctrl.h>
#include <wx/choice.h>
#include <wx/stattext.h>
#include <wx/frame.h>
#include <wx/fontenum.h>

#include <wx/dcclient.h>
#include <wx/dcbuffer.h>
#include <wx/colour.h>
#include <wx/colourdata.h>
#include <wx/filedlg.h>
#include <wx/colordlg.h>
///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MyFrame2
///////////////////////////////////////////////////////////////////////////////
class MyFrame2 : public wxFrame
{
	private:

	protected:
		wxPanel* m_panel;
		wxButton* m_button_save;
		wxCheckBox* m_checkBox_banana;
		wxScrollBar* m_scrollBar;
		wxGauge* m_gauge;
		wxButton* m_button_starColor;
		wxTextCtrl* m_textCtrl;
		wxChoice* m_choice;
		wxStaticText* m_staticText_font;
		wxChoice* m_choice_font;
		wxStaticText* m_staticText_font2;
		wxChoice* m_choice_font2;

		wxImage  m_image;

		wxFileDialog* m_saveDialog;
		wxBitmap* m_saveBitmap;
		wxColourDialog* m_colorDialog;
		wxColourData m_starColor;

		bool banana_flag = false, sun_flag = false, moon_flag = false, star_flag = true;
		wxImage file;
		wxBitmap m_bitmap;


		void m_button_save_Click(wxCommandEvent &e);
		void m_checkBox_banana_Click(wxCommandEvent &e);
		void m_scrollBar_Click(wxScrollEvent &e);
		void m_button_starColor_Click(wxCommandEvent &e);
		void m_textCtrl_Click(wxCommandEvent &e);
		void m_choice_Click(wxCommandEvent &e);
	
		void myRefresh();
		
	public:

		MyFrame2(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = ("GFK LAB 3"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(760, 448), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);
	
		~MyFrame2();

};

