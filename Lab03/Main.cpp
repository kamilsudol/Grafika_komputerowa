#include <wx/wxprec.h>
#include "myFrame.h"

class MyApp : public wxApp
{
public:
	virtual bool OnInit();
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
	MyFrame2 *frame = new MyFrame2(NULL);
	frame->Show(true);
	return true;
}