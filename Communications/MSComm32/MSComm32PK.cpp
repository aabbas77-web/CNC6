//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("MSComm32PK.res");
USEPACKAGE("vcl50.bpi");
USEUNIT("C:\Program Files\Borland\CBuilder5\Imports\MSCommLib_OCX.cpp");
USERES("c:\program files\borland\cbuilder5\Imports\MSCommLib_OCX.dcr");
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Package source.
//---------------------------------------------------------------------------

#pragma argsused
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void*)
{
	return 1;
}
//---------------------------------------------------------------------------
