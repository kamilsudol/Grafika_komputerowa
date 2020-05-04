///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "myFrame.h"


///////////////////////////////////////////////////////////////////////////

MyFrame2::MyFrame2(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer(wxVERTICAL);

	m_panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	m_panel->SetBackgroundColour(wxColour(255, 255, 255));

	bSizer4->Add(m_panel, 1, wxEXPAND | wxALL, 5);


	bSizer2->Add(bSizer4, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer(wxVERTICAL);

	m_button_save = new wxButton(this, wxID_ANY, wxT("Zapisz do pliku"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer6->Add(m_button_save, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	m_checkBox_banana = new wxCheckBox(this, wxID_ANY, wxT("Banan"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer6->Add(m_checkBox_banana, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	m_scrollBar = new wxScrollBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSB_HORIZONTAL);
	bSizer6->Add(m_scrollBar, 0, wxALL | wxALIGN_CENTER_HORIZONTAL | wxEXPAND, 5);

	m_gauge = new wxGauge(this, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL);
	m_gauge->SetValue(0);
	bSizer6->Add(m_gauge, 0, wxALL | wxALIGN_CENTER_HORIZONTAL | wxEXPAND, 5);

	m_button_starColor = new wxButton(this, wxID_ANY, wxT("Kolor gwiazdki"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer6->Add(m_button_starColor, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	m_textCtrl = new wxTextCtrl(this, wxID_ANY, wxT("tekst"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer6->Add(m_textCtrl, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	wxString m_choiceChoices[] = { wxT("Slonko"), wxT("Ksiezyc"), wxT("Gwiazdka") };
	int m_choiceNChoices = sizeof(m_choiceChoices) / sizeof(wxString);
	m_choice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choiceNChoices, m_choiceChoices, 0);
	m_choice->SetSelection(2);
	bSizer6->Add(m_choice, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	m_staticText_font = new wxStaticText(this, wxID_ANY, wxT("Wybierz czcionke 1:"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText_font->Wrap(-1);
	bSizer6->Add(m_staticText_font, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	wxArrayString m_choice_fontChoices;
	m_choice_font = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice_fontChoices, 0);
	m_choice_font->SetSelection(0);
	bSizer6->Add(m_choice_font, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	m_staticText_font2 = new wxStaticText(this, wxID_ANY, wxT("Wybierz czcionke 2:"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText_font2->Wrap(-1);
	bSizer6->Add(m_staticText_font2, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	wxArrayString m_choice_font2Choices;
	m_choice_font2 = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice_font2Choices, 0);
	m_choice_font2->SetSelection(0);
	bSizer6->Add(m_choice_font2, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);


	bSizer2->Add(bSizer6, 0, wxEXPAND, 5);


	this->SetSizer(bSizer2);
	this->Layout();

	this->Centre(wxBOTH);

	m_colorDialog = new wxColourDialog(this);
	m_saveDialog = new wxFileDialog(this, _("Wybierz plik:"), _(""), _(""), _("*.*"), wxFD_SAVE);
	
	this->m_scrollBar->Disable();
	
	for (wxString x : wxFontEnumerator::GetFacenames()) { m_choice_font->Append(x); }
	for (wxString x : wxFontEnumerator::GetFacenames()) { m_choice_font2->Append(x); }

	m_button_save->Bind(wxEVT_BUTTON, &MyFrame2::m_button_save_Click, this);
	m_checkBox_banana->Bind(wxEVT_CHECKBOX, &MyFrame2::m_checkBox_banana_Click, this);
	m_scrollBar->Bind(wxEVT_SCROLL_THUMBTRACK, &MyFrame2::m_scrollBar_Click, this);
	m_button_starColor->Bind(wxEVT_BUTTON, &MyFrame2::m_button_starColor_Click, this);
	m_textCtrl->Bind(wxEVT_TEXT, &MyFrame2::m_textCtrl_Click, this);
	m_choice->Bind(wxEVT_CHOICE, &MyFrame2::m_choice_Click, this);
	m_choice_font->Bind(wxEVT_CHOICE, &MyFrame2::m_textCtrl_Click, this);
	m_choice_font2->Bind(wxEVT_CHOICE, &MyFrame2::m_textCtrl_Click, this);

	myRefresh();
}

MyFrame2::~MyFrame2()
{
}

void MyFrame2::m_button_save_Click(wxCommandEvent &e)
{
	wxClientDC dc_client(this->m_panel);
	wxBufferedDC dc_buffer(&dc_client);
	PrepareDC(dc_buffer);
	wxInitAllImageHandlers();

	if (m_saveDialog->ShowModal() == wxID_OK)
	{
		m_saveBitmap = new wxBitmap(m_panel->GetVirtualSize());

		wxMemoryDC memory;
		memory.SelectObject(*m_saveBitmap);
		memory.Blit(0, 0, m_panel->GetVirtualSize().GetX(), m_panel->GetVirtualSize().GetY(), &dc_buffer, 0, 0, wxCOPY, true);

		myRefresh();

		wxImage result = m_saveBitmap->ConvertToImage();
		result.SaveFile("result.png", wxBITMAP_TYPE_PNG);
	}
}

void MyFrame2::m_checkBox_banana_Click(wxCommandEvent &e)
{
	if (m_checkBox_banana->IsChecked())
	{
		banana_flag = true;
		m_scrollBar->Enable(true);
		myRefresh();
	}
	else
	{
		banana_flag = false;
		m_scrollBar->Enable(false);
		myRefresh();
	}
}

void MyFrame2::m_scrollBar_Click(wxScrollEvent &e)
{
	this->m_gauge->SetValue(m_scrollBar->GetThumbPosition());
	myRefresh();
}

void MyFrame2::m_button_starColor_Click(wxCommandEvent &e)
{
	m_colorDialog->ShowModal();
	m_starColor = m_colorDialog->GetColourData();
	myRefresh();
}

void MyFrame2::m_choice_Click(wxCommandEvent &e)
{
	if (m_choice->GetSelection() == 0)
	{
		star_flag = false;
		sun_flag = true;
		moon_flag = false;
		myRefresh();
	}
	else if (m_choice->GetSelection() == 1)
	{
		star_flag = false;
		sun_flag = false;
		moon_flag = true;
		myRefresh();
	}
	else if (m_choice->GetSelection() == 2)
	{
		star_flag = true;
		sun_flag = false;
		moon_flag = false;
		myRefresh();
	}
}

void MyFrame2::m_textCtrl_Click(wxCommandEvent &e)
{
	myRefresh();
}

void MyFrame2::myRefresh()
{
	wxClientDC clientDC(this->m_panel);
	wxBufferedDC DC_Buffer(&clientDC);

	PrepareDC(DC_Buffer);
	DC_Buffer.Clear();

	int x = m_panel->GetVirtualSize().GetX() / 2;
	int y = m_panel->GetVirtualSize().GetY() / 2;

	if (star_flag)
	{
		wxPoint star_points[] = {
			wxPoint(x - 150, y - 170),
			wxPoint(x - 130, y - 90),
			wxPoint(x - 210, y - 140),
			wxPoint(x - 105, y - 140),
			wxPoint(x - 200, y - 90) };

		DC_Buffer.SetPen(m_starColor.GetColour());
		DC_Buffer.SetBrush(wxBrush(m_starColor.GetColour()));
		DC_Buffer.DrawPolygon(WXSIZEOF(star_points), star_points, 0, 0);

	}
	else if (sun_flag)
	{
		wxPoint sun_points(x - 200, y - 135);

		DC_Buffer.SetPen(*wxYELLOW_PEN);
		DC_Buffer.SetBrush(*wxYELLOW_BRUSH);
		DC_Buffer.DrawCircle(sun_points, 40);
	
	}
	else if (moon_flag)
	{
		wxPoint smaller(x - 180, y - 120);
		wxPoint bigger(x - 200, y - 140);

		DC_Buffer.SetPen(*wxGREY_PEN);
		DC_Buffer.SetBrush(*wxGREY_BRUSH);
		DC_Buffer.DrawCircle(smaller, 40);

		DC_Buffer.SetPen(*wxWHITE);
		DC_Buffer.SetBrush(*wxWHITE);
		DC_Buffer.DrawCircle(bigger, 45);

	}

	DC_Buffer.SetPen(*wxBLACK_PEN);
	DC_Buffer.SetBrush(*wxTRANSPARENT_BRUSH);
	
	if (banana_flag)
	{
		wxInitAllImageHandlers();
		file.LoadFile("banan.png", wxBITMAP_TYPE_PNG);
		m_bitmap = wxBitmap(file);
		DC_Buffer.DrawBitmap(m_bitmap, x - 110, y + 20 - m_scrollBar->GetThumbPosition());

		this->m_scrollBar->SetRange(120);
		
		wxPoint smile_points[]{
			wxPoint(x - 38, y - 41),
			wxPoint(x - 24, y - 33),
			wxPoint(x - 10, y - 27),
			wxPoint(x + 4, y - 33),
			wxPoint(x + 18, y - 41) };
		
		DC_Buffer.DrawSpline(5, smile_points);

	}
	else
	{
		wxPoint smile_points[]{
			wxPoint(x - 38, y - 41),
			wxPoint(x - 24, y - 48),
			wxPoint(x - 10, y - 56),
			wxPoint(x + 4, y - 48),
			wxPoint(x + 18, y - 41) };
		
		DC_Buffer.DrawSpline(5, smile_points);

		DC_Buffer.SetPen(*wxCYAN);
		DC_Buffer.SetBrush(*wxCYAN);
		DC_Buffer.DrawCircle(x + 5, y - 53, 2);
		DC_Buffer.SetPen(*wxBLACK_PEN);
		DC_Buffer.SetBrush(*wxTRANSPARENT_BRUSH);

	}

	DC_Buffer.DrawCircle(x - 25, y - 65, 10);
	DC_Buffer.DrawCircle(x + 3, y - 65, 10);

	wxPoint malpiszon_points[] = {
		wxPoint(x-10, y-5),
		wxPoint(x-10, y - 20),
		wxPoint(x + 60, y + 30),
		wxPoint(x - 90, y + 40 - m_scrollBar->GetThumbPosition()),
		wxPoint(x-10, y - 55),
		wxPoint(x-10, y + 75),
		wxPoint(x - 55, y + 170),
		wxPoint(x + 35, y + 170),
		wxPoint(x + 40, y + 95),
		wxPoint(x + 50, y + 75) ,
		wxPoint(x + 35, y + 80) };

	DC_Buffer.DrawCircle(malpiszon_points[4], 35);
	DC_Buffer.DrawLine(malpiszon_points[1], malpiszon_points[5]);
	DC_Buffer.DrawLine(malpiszon_points[0], malpiszon_points[2]);
	DC_Buffer.DrawLine(malpiszon_points[0], malpiszon_points[3]);
	DC_Buffer.DrawLine(malpiszon_points[5], malpiszon_points[6]);
	DC_Buffer.DrawLine(malpiszon_points[5], malpiszon_points[7]);
	DC_Buffer.DrawLine(malpiszon_points[5], malpiszon_points[8]);
	DC_Buffer.DrawLine(malpiszon_points[8], malpiszon_points[9]);
	DC_Buffer.DrawLine(malpiszon_points[9], malpiszon_points[10]);

	DC_Buffer.SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_NORMAL, false, m_choice_font->GetString(m_choice_font2->GetSelection())));
	DC_Buffer.DrawRotatedText(m_textCtrl->GetValue(), x - 100, y + 150, 0);
	DC_Buffer.SetFont(wxFont(30, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_NORMAL, false, m_choice_font->GetString(m_choice_font->GetSelection())));
	DC_Buffer.DrawRotatedText(m_textCtrl->GetValue(), x + 100, y + 90, 90);
}

