#include "GUIMyFrame1.h"
#include <vector>
#include <fstream>
#include "vecmat.h"

struct Point {
 float x, y, z;
 Point(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
};

struct Color {
 int R, G, B;
 Color(int _R, int _G, int _B) : R(_R), G(_G), B(_B) {}
};

struct Segment {
 Point begin, end;
 Color color;
 Segment(Point _begin, Point _end, Color _color) : begin(_begin), end(_end), color(_color) {}
};

std::vector<Segment> data;

GUIMyFrame1::GUIMyFrame1( wxWindow* parent )
:
MyFrame1( parent )
{
 m_button_load_geometry->SetLabel(_("Wczytaj Geometri\u0119"));
 m_staticText25->SetLabel(_("Obr\u00F3t X:"));
 m_staticText27->SetLabel(_("Obr\u00F3t Y:"));
 m_staticText29->SetLabel(_("Obr\u00F3t Z:"));

 WxSB_TranslationX->SetRange(0, 200); WxSB_TranslationX->SetValue(100);
 WxSB_TranslationY->SetRange(0, 200); WxSB_TranslationY->SetValue(100);
 WxSB_TranslationZ->SetRange(0, 200); WxSB_TranslationZ->SetValue(100);

 WxSB_RotateX->SetRange(0, 360); WxSB_RotateX->SetValue(0);
 WxSB_RotateY->SetRange(0, 360); WxSB_RotateY->SetValue(0);
 WxSB_RotateZ->SetRange(0, 360); WxSB_RotateZ->SetValue(0);

 WxSB_ScaleX->SetRange(1, 200); WxSB_ScaleX->SetValue(100);
 WxSB_ScaleY->SetRange(1, 200); WxSB_ScaleY->SetValue(100);
 WxSB_ScaleZ->SetRange(1, 200); WxSB_ScaleZ->SetValue(100);
}

void GUIMyFrame1::WxPanel_Repaint( wxUpdateUIEvent& event )
{
 Repaint();
}

void GUIMyFrame1::m_button_load_geometry_click( wxCommandEvent& event )
{
 wxFileDialog WxOpenFileDialog(this, wxT("Choose a file"), wxT(""), wxT(""), wxT("Geometry file (*.geo)|*.geo"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);

 if (WxOpenFileDialog.ShowModal() == wxID_OK)
 {
  double x1, y1, z1, x2, y2, z2;
  int r, g, b;

  std::ifstream in(WxOpenFileDialog.GetPath().ToAscii());
  if (in.is_open())
  {
   data.clear();
   while (!in.eof())
   {
    in >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> r >> g >> b;
    data.push_back(Segment(Point(x1, y1, z1), Point(x2, y2, z2), Color(r, g, b)));
   }
   in.close();
  }
 }
}

void GUIMyFrame1::Scrolls_Updated( wxScrollEvent& event )
{
WxST_TranslationX->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationX->GetValue() - 100) / 50.0));
WxST_TranslationY->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationY->GetValue() - 100) / 50.0));
WxST_TranslationZ->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationZ->GetValue() - 100) / 50.0));

WxST_RotateX->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateX->GetValue()));
WxST_RotateY->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateY->GetValue()));
WxST_RotateZ->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateZ->GetValue()));

WxST_ScaleX->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleX->GetValue() / 100.0));
WxST_ScaleY->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleY->GetValue() / 100.0));
WxST_ScaleZ->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleZ->GetValue() / 100.0));


Repaint();
}

Matrix4 Translation(double delta_x, double delta_y, double delta_z)
{
	Matrix4 trans;
	trans.data[0][0] = 1.0; trans.data[0][1] = 0.0; trans.data[0][2] = 0.0; trans.data[0][3] = (delta_x - 100.0) / 50.0;
	trans.data[1][0] = 0.0; trans.data[1][1] = 1.0; trans.data[1][2] = 0.0; trans.data[1][3] = -(delta_y - 100.0) / 50.0;
	trans.data[2][0] = 0.0; trans.data[2][1] = 0.0; trans.data[2][2] = 1.0; trans.data[2][3] = (delta_z - 100.0) / 50.0 + 2;
	trans.data[3][0] = 0.0; trans.data[3][1] = 0.0; trans.data[3][2] = 0.0; trans.data[3][3] = 1.0;

	return trans;
}

Matrix4 Scale(int x, int y, int z) {

	double S1 = x / 100.0, S2 = y / 100.0, S3 = z / 100.0;

	Matrix4 scal;
	scal.data[0][0] = S1; scal.data[0][1] = 0.0; scal.data[0][2] = 0.0; scal.data[0][3] = 0.0;
	scal.data[1][0] = 0.0; scal.data[1][1] = S2; scal.data[1][2] = 0.0; scal.data[1][3] = 0.0;
	scal.data[2][0] = 0.0; scal.data[2][1] = 0.0; scal.data[2][2] = S3; scal.data[2][3] = 0.0;
	scal.data[3][0] = 0.0; scal.data[3][1] = 0.0; scal.data[3][2] = 0.0; scal.data[3][3] = 1.0;

	return scal;
}

Matrix4 Rotation_x(double teta) {
	double tet = teta * 3.14 / 180;
	Matrix4 rot_x;
	rot_x.data[0][0] = 1.0; rot_x.data[0][1] = 0.0; rot_x.data[0][2] = 0.0; rot_x.data[0][3] = 0.0;
	rot_x.data[1][0] = 0.0; rot_x.data[1][1] = cos(tet); rot_x.data[1][2] = -sin(tet); rot_x.data[1][3] = 0.0;
	rot_x.data[2][0] = 0.0; rot_x.data[2][1] = sin(tet); rot_x.data[2][2] = cos(tet); rot_x.data[2][3] = 0.0;
	rot_x.data[3][0] = 0.0; rot_x.data[3][1] = 0.0; rot_x.data[3][2] = 0.0; rot_x.data[3][3] = 1.0;

	return rot_x;
}

Matrix4 Rotation_y(double teta) {
	double tet = teta * 3.14 / 180;
	Matrix4 rot_y;
	rot_y.data[0][0] = cos(tet); rot_y.data[0][1] = 0.0; rot_y.data[0][2] = sin(tet); rot_y.data[0][3] = 0.0;
	rot_y.data[1][0] = 0.0; rot_y.data[1][1] = 1.0; rot_y.data[1][2] = 0.0; rot_y.data[1][3] = 0.0;
	rot_y.data[2][0] = -sin(tet); rot_y.data[2][1] = 0.0; rot_y.data[2][2] = cos(tet); rot_y.data[2][3] = 0.0;
	rot_y.data[3][0] = 0.0; rot_y.data[3][1] = 0.0; rot_y.data[3][2] = 0.0; rot_y.data[3][3] = 1.0;

	return rot_y;
}

Matrix4 Rotation_z(double teta) {
	double tet = teta * 3.14 / 180;
	Matrix4 rot_z;
	rot_z.data[0][0] = cos(tet); rot_z.data[0][1] = -sin(tet); rot_z.data[0][2] = 0.0; rot_z.data[0][3] = 0.0;
	rot_z.data[1][0] = sin(tet); rot_z.data[1][1] = cos(tet); rot_z.data[1][2] = 0.0; rot_z.data[1][3] = 0.0;
	rot_z.data[2][0] = 0.0; rot_z.data[2][1] = 0.0; rot_z.data[2][2] = 1.0; rot_z.data[2][3] = 0.0;
	rot_z.data[3][0] = 0.0; rot_z.data[3][1] = 0.0; rot_z.data[3][2] = 0.0; rot_z.data[3][3] = 1.0;

	return rot_z;
}

void GUIMyFrame1::Repaint()
{
	wxClientDC dc1(WxPanel);
	wxBufferedDC dc(&dc1);

	int w, h;

	WxPanel->GetSize(&w, &h);
	dc.SetBackground(wxBrush(RGB(255, 255, 255)));
	dc.Clear();
	dc.SetClippingRegion(0, 0, w, h);

	Matrix4 scaled = Scale(WxSB_ScaleX->GetValue(), WxSB_ScaleY->GetValue(), WxSB_ScaleZ->GetValue());
	Matrix4 translated = Translation(WxSB_TranslationX->GetValue(), WxSB_TranslationY->GetValue(), WxSB_TranslationZ->GetValue());
	Matrix4 rotated_x = Rotation_x(WxSB_RotateX->GetValue()); 
	Matrix4 rotated_y = Rotation_y(-WxSB_RotateY->GetValue()); 
	Matrix4 rotated_z = Rotation_z(WxSB_RotateZ->GetValue());

	Matrix4 transformed = translated * rotated_z * rotated_y * rotated_x * scaled;

	for (auto i : data) {

		dc.SetPen(wxPen(RGB(i.color.R, i.color.G, i.color.B)));

		Vector4 start;
		start.Set(i.begin.x, i.begin.y, i.begin.z);
		start = transformed * start;

		Vector4 end;
		end.Set(i.end.x, i.end.y, i.end.z);
		end = transformed * end;

		dc.DrawLine(w * (0.5 + start.GetX() /  std::abs(start.GetZ())), h * (0.5 + start.GetY() / std::abs(start.GetZ())), w * (0.5 + end.GetX() / std::abs(end.GetZ())), h * (0.5 + end.GetY() / std::abs(end.GetZ())));

	}
}