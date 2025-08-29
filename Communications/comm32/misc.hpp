// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Misc.pas' rev: 5.00

#ifndef MiscHPP
#define MiscHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <OLE2.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Misc
{
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
static const Word MAXOUTPUTSTRINGLENGTH = 0x1000;
extern PACKAGE AnsiString __fastcall FormatLastError(unsigned dwLastError);
extern PACKAGE char * __fastcall szFormatLastError(unsigned dwLastError, char * szOutputBuffer, unsigned 
	dwSizeofOutputBuffer);
extern PACKAGE bool __fastcall DelphiIsRunning(void);
extern PACKAGE void __fastcall mbstowcs(wchar_t * szw, char * m_pszPath, int len);
extern PACKAGE bool __fastcall iscntrl(char ch);
extern PACKAGE bool __fastcall isalpha(char ch);
extern PACKAGE bool __fastcall isdigit(char ch);
extern PACKAGE int __fastcall strtoul(char * pszBuffer, char * &ppszBuffer, int Base);

}	/* namespace Misc */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Misc;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Misc
