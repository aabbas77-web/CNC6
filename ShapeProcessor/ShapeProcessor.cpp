//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("ShapeProcessor.res");
USEFORM("Main.cpp", FormMain);
USEUNIT("api_VecApi.cpp");
USEUNIT("api_Messages.cpp");
USEUNIT("api_Strings.cpp");
USEUNIT("shp_Contour.cpp");
USEUNIT("shp_Types.cpp");
USEUNIT("shp_Image.cpp");
USEFORM("Form_Digitizer.cpp", FormDigitizer);
USEUNIT("shp_ColorQuantizer.cpp");
//---------------------------------------------------------------------------
#include "api_VecApi.h"
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{
        // load vecad.dll
        if(vlStartup()==FALSE)
        {
            MessageDlg("VECAD52.DLL is not found",mtError,TMsgDlgButtons()<<mbOK,0);
            exit(0);
        }
        else
        {
			Application->Initialize();
			Application->CreateForm(__classid(TFormMain), &FormMain);
		Application->CreateForm(__classid(TFormDigitizer), &FormDigitizer);
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
