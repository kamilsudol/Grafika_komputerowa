#include <wx/dc.h>
#include <memory>

#include "ChartClass.h"
#include "vecmat.h"

ChartClass::ChartClass(std::shared_ptr<ConfigClass> c)
{
    cfg= std::move(c);
    x_step=200;
}

void ChartClass::Set_Range()
{
 double xmin=9999.9,xmax=-9999.9,ymin=9999.9,ymax=-9999.9;
 double x,y,step;
 int i;

 xmin=cfg->Get_x_start();
 xmax=cfg->Get_x_stop();

 step=(cfg->Get_x_stop()-cfg->Get_x_start())/(double)x_step;
 x=cfg->Get_x_start();

 for (i=0;i<=x_step;i++)
  {
   y=GetFunctionValue(x);
   if (y>ymax) ymax=y;
   if (y<ymin) ymin=y;
   x=x+step;
  }

 y_min=ymin;
 y_max=ymax;
 x_min=xmin;
 x_max=xmax;
}


double ChartClass::GetFunctionValue(double x)
{
 if (cfg->Get_F_type()==1) return x*x;
 if (cfg->Get_F_type()==2) return 0.5*exp(4*x-3*x*x);
 return x+sin(x*4.0);
}

void ChartClass::Draw(wxDC *dc, int w, int h)
{
 dc->SetBackground(wxBrush(RGB(255, 255, 255)));
 dc->Clear();
 dc->SetPen(wxPen(RGB(255, 0, 0)));
 dc->DrawRectangle(10, 10, w - 20, h - 20);
 dc->SetClippingRegion(10, 10, w - 20, h - 20);
 //dc->DrawText("Tu trzeba narysowac wykres", wxPoint(20, 20));

 Matrix transform;
 if (cfg->RotateScreenCenter()) {
	 transform = rotation(cfg->Get_Alpha(), w, h)* translation(cfg->Get_dX(), -cfg->Get_dY())* scale(w, h);
 }
 else {
	 transform = translation(cfg->Get_dX(), -cfg->Get_dY())* rotation(cfg->Get_Alpha(), w, h)* scale(w, h);
 }
	 
 DrawAxes(transform, dc);
 DrawFunction(transform, dc);

}

void ChartClass::line2d(Matrix t, double x1, double y1, double x2, double y2, wxDC *dc)
{
	Vector start, end;

	start.Set(x1, y1);
	start = t * start;

	end.Set(x2, y2);
	end = t * end;

	dc->DrawLine(start.GetX(), start.GetY(), end.GetX(), end.GetY());

}

void ChartClass::DrawAxes(Matrix &transform, wxDC *dc) {

	dc->SetPen(*wxBLUE_PEN);

	line2d(transform, cfg->Get_x_start(), 0.0 , cfg->Get_x_stop(), 0.0, dc);
	line2d(transform, 0.0, -Get_Y_min(), 0.0, -Get_Y_max(), dc);

	line2d(transform, cfg->Get_x_stop(), 0.0, cfg->Get_x_stop() - 0.08, 0.08, dc);
	line2d(transform, cfg->Get_x_stop(), 0.0, cfg->Get_x_stop() - 0.08, -0.08, dc);

	line2d(transform, 0.0, -Get_Y_max(), 0.05, -Get_Y_max() + 0.12, dc);
	line2d(transform, 0.0, -Get_Y_max(), -0.05, -Get_Y_max() + 0.12, dc);

	
	for (double i = cfg->Get_x_start(); i <= cfg->Get_x_stop(); i += 0.5) {
		if ( i > 0.1 ||  i < -0.1) {
			Vector txt_vec;
			line2d(transform, i, 0.02, i, -0.02, dc);
			txt_vec.Set(i + 0.01, -0.2);
			dc->DrawRotatedText(wxString::Format(wxT("%.2f"), i), (transform * txt_vec).GetX(), (transform * txt_vec).GetY(), cfg->Get_Alpha());
		}
	}
	
	for (double i = -Get_Y_min(); i >= -Get_Y_max(); i -= 0.5) {
		if ( i > 0.1 ||  i < -0.1) {
			Vector txt_vec;
			line2d(transform, 0.02, i, -0.02, i, dc);
			txt_vec.Set(0.05, i-0.05);
			dc->DrawRotatedText(wxString::Format(wxT("%.2f"), -i), (transform * txt_vec).GetX(), (transform * txt_vec).GetY(), cfg->Get_Alpha());
		}
	}
}

void ChartClass::DrawFunction(Matrix &transform, wxDC *dc) {

	dc->SetPen(*wxGREEN_PEN);

	double new_step = (x_max - x_min) / x_step;
	for (double i = x_min; i <= x_max; i += new_step) {
		line2d(transform, i, -GetFunctionValue(i), i + new_step, -GetFunctionValue(i + new_step), dc);
	}
}

Matrix ChartClass::rotation(double alfa, double w , double h) {
	
	Matrix rotated;
	double alf = - (3.14 * (alfa / 180));
	rotated.data[0][0] = cos(alf); rotated.data[0][1] = -sin(alf); rotated.data[0][2] = 0.0;
	rotated.data[1][0] = sin(alf); rotated.data[1][1] = cos(alf); rotated.data[1][2] = 0.0;
	rotated.data[2][0] = 0.0; rotated.data[2][1] = 0.0; rotated.data[2][2] = 1.0;

	Matrix scal = scale(w, h);
	Matrix new_pos , return_to_prev_pos;
	
	if (cfg->RotateScreenCenter()) {
		new_pos = translation(w / 2.0, h / 2.0);
		return_to_prev_pos = translation(-new_pos.data[0][2], -new_pos.data[1][2]);
	}else {
		new_pos = translation(scal.data[0][2], scal.data[1][2]);
		return_to_prev_pos = translation(-new_pos.data[0][2], -new_pos.data[1][2]);
	}
	
	return new_pos * rotated * return_to_prev_pos;

}

Matrix ChartClass::translation(double delta_x, double delta_y) {

	Matrix translated;
	translated.data[0][0] = 1.0; translated.data[0][1] = 0.0; translated.data[0][2] = delta_x;
	translated.data[1][0] = 0.0; translated.data[1][1] = 1.0; translated.data[1][2] = delta_y;
	translated.data[2][0] = 0.0; translated.data[2][1] = 0.0; translated.data[2][2] = 1.0;

	return translated;
}

Matrix ChartClass::scale(int w, int h) {

	Matrix scaled;
	double S1 = (w - x_min) / (cfg->Get_x1() - cfg->Get_x0()); 
	double S2 = (h - y_min) / (cfg->Get_y1() - cfg->Get_y0());
	scaled.data[0][0] = S1; scaled.data[0][1] = 0.0; scaled.data[0][2] = x_min - scaled.data[0][0] * cfg->Get_x0();
	scaled.data[1][0] = 0.0; scaled.data[1][1] = S2; scaled.data[1][2] = y_min - scaled.data[1][1] * cfg->Get_y0();
	scaled.data[2][0] = 0.0; scaled.data[2][1] = 0.0; scaled.data[2][2] = 1.0;

	return scaled;
}

double ChartClass::Get_Y_min()
{
    Set_Range();
    return y_min;
}

double ChartClass::Get_Y_max()
{
    Set_Range();
    return y_max;
}