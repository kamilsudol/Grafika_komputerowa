#include "GUIMyFrame1.h"

GUIMyFrame1::GUIMyFrame1( wxWindow* parent )
:
MyFrame1( parent )
{
 m_staticText1->SetLabel(_(L"Jasno\u015B\u0107"));
 m_b_threshold->SetLabel(_(L"Pr\u00F3g 128"));
 this->SetBackgroundColour(wxColor(192, 192, 192));
 m_scrolledWindow->SetScrollbars(25, 25, 52, 40);
 m_scrolledWindow->SetBackgroundColour(wxColor(192, 192, 192));
}

void GUIMyFrame1::m_scrolledWindow_update( wxUpdateUIEvent& event )
{
 Repaint();
}

void GUIMyFrame1::m_b_grayscale_click( wxCommandEvent& event )
{
 // TO DO: Konwersja do skali szarosci    
	Img_Cpy = Img_Org.Copy();
	m_scrolledWindow->ClearBackground();
	Img_Cpy = Img_Cpy.ConvertToGreyscale();
}

void GUIMyFrame1::m_b_blur_click( wxCommandEvent& event )
{
 // TO DO: Rozmywanie obrazu (blur)
	Img_Cpy = Img_Org.Copy();
	m_scrolledWindow->ClearBackground();
	Img_Cpy = Img_Cpy.Blur(10);
}

void GUIMyFrame1::m_b_mirror_click( wxCommandEvent& event )
{
 // TO DO: Odbicie lustrzane
	Img_Cpy = Img_Org.Copy();
	m_scrolledWindow->ClearBackground();
	Img_Cpy = Img_Cpy.Mirror();
}

void GUIMyFrame1::m_b_replace_click( wxCommandEvent& event )
{
 // TO DO: Zamiana kolorow 
	Img_Cpy = Img_Org.Copy();
	m_scrolledWindow->ClearBackground();
	Img_Cpy.Replace(254, 0, 0, 0, 0, 255);
}

void GUIMyFrame1::m_b_rescale_click( wxCommandEvent& event )
{
 // TO DO: Zmiana rozmiarow do 320x240
	Img_Cpy = Img_Org.Copy();
	m_scrolledWindow->ClearBackground();
	Img_Cpy = Img_Cpy.Scale(320, 240);
}

void GUIMyFrame1::m_b_rotate_click( wxCommandEvent& event )
{
 // TO DO: Obrot o 30 stopni
	const double pi = 3.1415;
	Img_Cpy = Img_Org.Copy();
	m_scrolledWindow->ClearBackground();
	Img_Cpy = Img_Cpy.Rotate(30.0 * pi/180,wxPoint(Img_Org.GetWidth()/2,Img_Org.GetHeight()/2), true);
}

void GUIMyFrame1::m_b_rotate_hue_click( wxCommandEvent& event )
{
 // TO DO: Przesuniecie Hue o 180 stopni
	Img_Cpy = Img_Org.Copy();
	m_scrolledWindow->ClearBackground();
	Img_Cpy.RotateHue(0.5);
}

void GUIMyFrame1::m_b_mask_click( wxCommandEvent& event )
{
 // TO DO: Ustawienie maski obrazu
	Img_Cpy = Img_Org.Copy();
	m_scrolledWindow->ClearBackground();
	Img_Cpy.SetMaskFromImage(Img_Mask, 0, 0, 0);
}

void GUIMyFrame1::m_s_brightness_scroll( wxScrollEvent& event )
{
// Tutaj, w reakcji na zmiane polozenia suwaka, wywolywana jest funkcja
// Brightness(...), ktora zmienia jasnosc. W tym miejscu nic nie
// zmieniamy. Do uzupelnienia pozostaje funkcja Brightness(...)
Brightness(m_s_brightness->GetValue() - 100);
Repaint();
}

void GUIMyFrame1::m_s_contrast_scroll( wxScrollEvent& event )
{
// Tutaj, w reakcji na zmiane polozenia suwaka, wywolywana jest funkcja
// Contrast(...), ktora zmienia kontrast. W tym miejscu nic nie
// zmieniamy. Do uzupelnienia pozostaje funkcja Contrast(...)
Contrast(m_s_contrast->GetValue() - 100);
Repaint();
}

void GUIMyFrame1::m_b_prewitt_click( wxCommandEvent& event )
{
 // TO DO: Pionowa maska Prewitta
	Img_Cpy = Img_Org.Copy();
	m_scrolledWindow->ClearBackground();
	unsigned char *org_pix = Img_Cpy.GetData();

	int size = Img_Cpy.GetHeight() * Img_Cpy.GetWidth() * 3;
	unsigned char *cpy_pix = new unsigned char[size];
	
	for (int i = 0; i < size; i++) {
		cpy_pix[i] = org_pix[i];
	}

	int width = Img_Cpy.GetWidth() * 3;

	for (int i = 1; i < Img_Cpy.GetHeight() - 1; i++) {
		for (int j = 1; j < Img_Cpy.GetWidth() - 1; j++) {
			for (int k = 0; k < 3; k++) {
				int value = get_pix_val(i, j, k, width, cpy_pix);
				if (value > 0) {
					org_pix[i * width + j * 3 + k] = value/3;
				}
				else {
					org_pix[i * width + j * 3 + k] = -value/3;
				}
			}
		}
	}

	delete[] cpy_pix;
}

void GUIMyFrame1::m_b_threshold_click( wxCommandEvent& event )
{
 // TO DO: Prog o wartosci 128 dla kazdego kanalu niezaleznie
	Img_Cpy = Img_Org.Copy();
	m_scrolledWindow->ClearBackground();
	unsigned char *cpy_pix = Img_Cpy.GetData();
	for (int i = 0; i < Img_Cpy.GetHeight()*Img_Cpy.GetWidth() * 3; i++) {
		if (cpy_pix[i] < 128) {
			cpy_pix[i] = 0;
		}else {
			cpy_pix[i] = 255;
		}
	}
}

void GUIMyFrame1::Contrast(int value)
{
 // TO DO: Zmiana kontrastu obrazu. value moze przyjmowac wartosci od -100 do 100
	Img_Cpy = Img_Org.Copy();
	m_scrolledWindow->ClearBackground();
	unsigned char *cpy_pix = Img_Cpy.GetData();
	double contrast = (value + 100) / (100.1 - value);

	for (int i = 0; i < Img_Cpy.GetHeight()*Img_Cpy.GetWidth() * 3; i++) {
		if ((cpy_pix[i] - 255/2)* contrast + 255/2 > 255) {
			cpy_pix[i] = 255;
		}else if ((cpy_pix[i] - 255/2)* contrast + 255/2 < 0) {
			cpy_pix[i] = 0;
		}else {
			cpy_pix[i]=(cpy_pix[i] - 255/2)* contrast + 255/2;
		}
	}
}

void GUIMyFrame1::Repaint()
{
 wxBitmap bitmap(Img_Cpy);          // Tworzymy tymczasowa bitmape na podstawie Img_Cpy
 wxClientDC dc(m_scrolledWindow);   // Pobieramy kontekst okna
 m_scrolledWindow->DoPrepareDC(dc); // Musimy wywolac w przypadku wxScrolledWindow, zeby suwaki prawidlowo dzialaly
 dc.DrawBitmap(bitmap, 0, 0, true); // Rysujemy bitmape na kontekscie urzadzenia
}

void GUIMyFrame1::Brightness(int value)
{
 // TO DO: Zmiana jasnosci obrazu. value moze przyjmowac wartosci od -100 do 100
	Img_Cpy = Img_Org.Copy();
	unsigned char *cpy_pix = Img_Cpy.GetData();
	for (int i = 0; i < Img_Cpy.GetHeight()*Img_Cpy.GetWidth()*3; i++) {
		if (cpy_pix[i] + value > 255) {
			cpy_pix[i] = 255;
		}else if (cpy_pix[i] + value < 0) {
			cpy_pix[i] = 0;
		}else {
			cpy_pix[i] += value;
		}
	}
}

int GUIMyFrame1::get_pix_val(int i, int j, int k, int width, unsigned char *pix_tab) {
	int value = 0;

	value += pix_tab[i * width + (j + 1) * 3 + k];
	value += pix_tab[(i + 1) * width + (j + 1) * 3 + k];
	value += pix_tab[(i - 1) * width + (j + 1) * 3 + k];
	value -= pix_tab[i * width + (j - 1) * 3 + k];
	value -= pix_tab[(i + 1) * width + (j - 1) * 3 + k];
	value -= pix_tab[(i - 1) * width + (j - 1) * 3 + k];

	return value;
}