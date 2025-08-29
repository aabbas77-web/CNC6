//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("CNC.res");
USEFORM("Main.cpp", FormMain);
USEFORM("About.cpp", FormAbout);
USEUNIT("CadApi.cpp");
USEUNIT("cad_Events.cpp");
USEUNIT("..\ShapeProcessor\shp_Contour.cpp");
USEFORM("Options.cpp", FormOptions);
USEFORM("Simulator.cpp", FormSimulator);
USEUNIT("CNCLib.cpp");
USEFORM("Export.cpp", FormExport);
//---------------------------------------------------------------------------
void ShowVendorMessage();
#pragma startup ShowVendorMessage 64
//---------------------------------------------------------------------------
void ShowVendorMessage()
{
//	MessageDlg(DecodeMessage(c_strForMoreInformation),mtInformation,TMsgDlgButtons()<<mbOK,0);
}
//---------------------------------------------------------------------------
#include "cadapi.h"
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{
    	if(CadLoadLibrary())
        {
	    	Application->Initialize();
    	    Application->CreateForm(__classid(TFormMain), &FormMain);
		Application->CreateForm(__classid(TFormAbout), &FormAbout);
		Application->CreateForm(__classid(TFormOptions), &FormOptions);
		Application->CreateForm(__classid(TFormSimulator), &FormSimulator);
		Application->CreateForm(__classid(TFormExport), &FormExport);
		Application->Run();
        }
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	return 0;
}
//---------------------------------------------------------------------------
