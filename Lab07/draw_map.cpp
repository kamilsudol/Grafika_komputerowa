#include <wx/wx.h>
#include <cmath>
#include "GUIMyFrame1.h"
// UWAGA: TO JEST JEDYNY PLIK, KTORY NALEZY EDYTOWAC **************************

double shepard_method(float d[100][3], int N, int i, int j){
	double x, y;
	x = static_cast<double>(i / 100. - 2.5);
	y = static_cast<double>(-j / 100. + 2.5);
	float wk, sum1 = 0, sum2 = 0;
	for (int i = 0; i < N; i++) {
		wk = 1. / pow(sqrt(pow(x - d[i][0], 2) + pow(y - d[i][1], 2)), 2);
		sum1 += wk * d[i][2];
		sum2 += wk;
	}
	double result = sum1 / sum2;
	return result;
}

void GUIMyFrame1::DrawMap(int N, float d[100][3], bool Contour, int MappingType, int NoLevels, bool ShowPoints)
{
 wxMemoryDC memDC;
 memDC.SelectObject(MemoryBitmap);
 memDC.SetBackground(*wxWHITE_BRUSH);
 memDC.Clear();

 double min = d[0][2], max = d[0][2];

 for (int i = 0; i < N; i++) {
	 if (d[i][2] > max) {
		 max = d[i][2];
	 }
	 if (d[i][2] < min) {
		 min = d[i][2];
	 }
 }

 double **bitmap = new double*[500];
 for (int i = 0; i < 500; i++) {
	 bitmap[i] = new double[500]{0};
 }

 for (int i = 0; i < 500; i++) {
	 for (int j = 0; j < 500; j++) {
		 bitmap[j][i] = shepard_method(d, N, j, i);
	 }
 }

 unsigned char *pixels = new unsigned char[500 * 500 * 3]{" "};

 if (MappingType) {
	 if (MappingType == 1) {
		memDC.DrawText("Mapa niebiesko-czerwona...", wxPoint(10, 30));
		for (int i = 0; i < 500; i++) {
			for (int j = 0; j < 500; j++) {
				double color = 2 * (bitmap[i][j] - min) / (max - min) - 1;
				pixels[j * 500 * 3 + i * 3 + 0] = 255 / 2. - (255 / 2.)*color;
				pixels[j * 500 * 3 + i * 3 + 1] = 0;
				pixels[j * 500 * 3 + i * 3 + 2] = 255 / 2. + (255 / 2.)*color;
			}
		} 
	 }

	 if (MappingType == 2) {
		 memDC.DrawText("Mapa niebiesko-zielono-czerwona...", wxPoint(10, 30));
		 for (int i = 0; i < 500; i++) {
			 for (int j = 0; j < 500; j++) {
				 double color = 2 * (bitmap[i][j] - min) / (max - min) - 1.;
				 if (color < 0) {
					 pixels[j * 500 * 3 + i * 3 + 0] = 255 *(-color);
					 pixels[j * 500 * 3 + i * 3 + 1] = 255 - 255 * (-color);
					 pixels[j * 500 * 3 + i * 3 + 2] = 0;
				 }
				 else {
					 pixels[j * 500 * 3 + i * 3 + 0] = 0;
					 pixels[j * 500 * 3 + i * 3 + 1] = 255 - 255 * color;
					 pixels[j * 500 * 3 + i * 3 + 2] = 255 * color;
				 }
			 }
		 }
	 }

	 if (MappingType == 3) {
		 memDC.DrawText("Mapa szara...", wxPoint(10, 30));
		 for (int i = 0; i < 500; i++) {
			 for (int j = 0; j < 500; j++) {
				 double color = 2 * (bitmap[i][j] - min) / (max - min) - 1.;
				 pixels[j * 500 * 3 + i * 3 + 0] = 255 / 2. + (255 / 2.)*color;
				 pixels[j * 500 * 3 + i * 3 + 1] = 255 / 2. + (255 / 2.)*color;
				 pixels[j * 500 * 3 + i * 3 + 2] = 255 / 2. + (255 / 2.)*color;
			 }
		 }
	 }

	 memDC.DrawBitmap(wxBitmap(wxImage(500, 500, pixels)), 0, 0);
 }
  
 if (Contour) {
	 memDC.DrawText("Kontury...", wxPoint(10, 10));
	 memDC.SetPen(*wxBLACK_PEN);
	 memDC.SetBrush(*wxTRANSPARENT_BRUSH);
	 for (int k = 1; k < NoLevels + 1; k++) {
		 double color_value = min + k * (max - min) / (NoLevels + 1.);
		 for (int i = 0; i < 500; i++) {
			 for (int j = 0; j < 500; j++) {
				 if (bitmap[j][i] > color_value) {
					 if (i + 1 < 500 && j + 1 >= 0 && j + 1 < 500 && bitmap[j + 1][i + 1] < color_value) {
						 memDC.DrawPoint(j, i);
					 }
					 if (i - 1 < 500 && j + 1 >= 0 && j + 1 < 500 && j - 1 >= 0 && bitmap[j + 1][i - 1] < color_value) {
						 memDC.DrawPoint(j, i);
					 }
					 if (i + 1 < 500 && j - 1 >= 0 && j - 1 < 500 && j + 1 >= 0 && bitmap[j - 1][i + 1] < color_value) {
						 memDC.DrawPoint(j, i);
					 }
					 if (i - 1 < 500  && j - 1 >= 0 && j - 1 < 500 && bitmap[j - 1][i - 1] < color_value) {
						 memDC.DrawPoint(j, i);
					 }
				 }
			 }
		 }
	 }
 }

 if (ShowPoints) {
	 memDC.DrawText("Punkty...", wxPoint(10, 50));
	 memDC.SetPen(*wxBLACK);
	 memDC.SetBrush(*wxTRANSPARENT_BRUSH);
	 for (int i = 0; i < N; ++i) {
		 memDC.DrawLine(d[i][0] * 100 + 250, 250 - d[i][1] * 100 + 5, d[i][0] * 100 + 250, 250 - d[i][1] * 100 - 5);
		 memDC.DrawLine(d[i][0]*100 + 250 - 5, 250 - d[i][1] * 100, d[i][0] * 100 + 250 + 5, 250 - d[i][1] * 100);
	 }
 }

 for (int i = 0; i < 500; i++) {
	 delete[] bitmap[i];
 }
 delete[] bitmap;
}
