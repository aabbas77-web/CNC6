// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Comm32.pas' rev: 5.00

#ifndef Comm32HPP
#define Comm32HPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Misc.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Comm32
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS ECommsError;
class PASCALIMPLEMENTATION ECommsError : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall ECommsError(const AnsiString Msg) : Sysutils::Exception(Msg
		) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ECommsError(const AnsiString Msg, const System::TVarRec 
		* Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ECommsError(int Ident)/* overload */ : Sysutils::Exception(
		Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ECommsError(int Ident, const System::TVarRec * Args, 
		const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ECommsError(const AnsiString Msg, int AHelpContext) : 
		Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ECommsError(const AnsiString Msg, const System::TVarRec 
		* Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext
		) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ECommsError(int Ident, int AHelpContext)/* overload */
		 : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ECommsError(System::PResStringRec ResStringRec, 
		const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(
		ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ECommsError(void) { }
	#pragma option pop
	
};


#pragma option push -b-
enum TParity { pNone, pOdd, pEven, pMark, pSpace };
#pragma option pop

#pragma option push -b-
enum TStopBits { sb1_0, sb1_5, sb2_0 };
#pragma option pop

class DELPHICLASS TReadThread;
class PASCALIMPLEMENTATION TReadThread : public Classes::TThread 
{
	typedef Classes::TThread inherited;
	
protected:
	virtual void __fastcall Execute(void);
	
public:
	unsigned hCommFile;
	unsigned hCloseEvent;
	unsigned hComm32Window;
	bool __fastcall SetupCommEvent(Windows::POverlapped lpOverlappedCommEvent, unsigned &dwEventMask);
	bool __fastcall SetupReadEvent(Windows::POverlapped lpOverlappedRead, char * szInputBuffer, unsigned 
		dwSizeofBuffer, unsigned &NumberOfBytesRead);
	bool __fastcall HandleCommEvent(Windows::POverlapped lpOverlappedCommEvent, unsigned &dwEventMask, 
		bool fRetrieveEvent);
	bool __fastcall HandleReadEvent(Windows::POverlapped lpOverlappedRead, char * szInputBuffer, unsigned 
		dwSizeofBuffer, unsigned &NumberOfBytesRead);
	bool __fastcall HandleReadData(char * szInputBuffer, unsigned dwSizeofBuffer);
	BOOL __fastcall ReceiveData(char * lpNewString, unsigned dwSizeofNewString);
	void __fastcall PostHangupCall(void);
public:
	#pragma option push -w-inl
	/* TThread.Create */ inline __fastcall TReadThread(bool CreateSuspended) : Classes::TThread(CreateSuspended
		) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TThread.Destroy */ inline __fastcall virtual ~TReadThread(void) { }
	#pragma option pop
	
};


class DELPHICLASS TWriteThread;
class PASCALIMPLEMENTATION TWriteThread : public Classes::TThread 
{
	typedef Classes::TThread inherited;
	
protected:
	virtual void __fastcall Execute(void);
	bool __fastcall HandleWriteData(Windows::POverlapped lpOverlappedWrite, char * pDataToWrite, unsigned 
		dwNumberOfBytesToWrite);
	
public:
	unsigned hCommFile;
	unsigned hCloseEvent;
	unsigned hComm32Window;
	bool __fastcall WriteComm(char * pDataToWrite, unsigned dwSizeofDataToWrite);
	void __fastcall PostHangupCall(void);
public:
	#pragma option push -w-inl
	/* TThread.Create */ inline __fastcall TWriteThread(bool CreateSuspended) : Classes::TThread(CreateSuspended
		) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TThread.Destroy */ inline __fastcall virtual ~TWriteThread(void) { }
	#pragma option pop
	
};


typedef void __fastcall (__closure *TReceiveDataEvent)(void * Buffer, Word BufferLength);

class DELPHICLASS TComm32;
class PASCALIMPLEMENTATION TComm32 : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	TReadThread* ReadThread;
	TWriteThread* WriteThread;
	bool ThreadError;
	bool WriteCreated;
	bool ReadCreated;
	AnsiString FCommsLogFileName;
	AnsiString FCommPort;
	unsigned hCommFile;
	unsigned hCloseEvent;
	TReceiveDataEvent FOnReceiveData;
	Classes::TNotifyEvent FOnRequestHangup;
	unsigned FHWnd;
	unsigned FBaudRate;
	TParity FParity;
	TStopBits FStopBits;
	Byte FByteSize;
	void __fastcall SetCommsLogFileName(AnsiString LogFileName);
	TReceiveDataEvent __fastcall GetReceiveDataEvent();
	void __fastcall SetReceiveDataEvent(TReceiveDataEvent AReceiveDataEvent);
	Classes::TNotifyEvent __fastcall GetRequestHangupEvent();
	void __fastcall SetRequestHangupEvent(Classes::TNotifyEvent ARequestHangupEvent);
	void __fastcall CommWndProc(Messages::TMessage &msg);
	
protected:
	void __fastcall CloseReadThread(void);
	void __fastcall CloseWriteThread(void);
	void __fastcall ReceiveData(char * Buffer, Word BufferLength);
	void __fastcall RequestHangup(void);
	
public:
	__fastcall virtual TComm32(Classes::TComponent* AOwner);
	__fastcall virtual ~TComm32(void);
	bool __fastcall StartComm(void);
	void __fastcall StopComm(void);
	bool __fastcall WriteCommData(char * pDataToWrite, Word dwSizeofDataToWrite);
	
__published:
	__property unsigned BaudRate = {read=FBaudRate, write=FBaudRate, default=9600};
	__property Byte ByteSize = {read=FByteSize, write=FByteSize, default=8};
	__property TParity Parity = {read=FParity, write=FParity, default=0};
	__property TStopBits StopBits = {read=FStopBits, write=FStopBits, default=0};
	__property AnsiString CommPort = {read=FCommPort, write=FCommPort};
	__property AnsiString CommsLogFileName = {read=FCommsLogFileName, write=SetCommsLogFileName};
	__property TReceiveDataEvent OnReceiveData = {read=GetReceiveDataEvent, write=SetReceiveDataEvent};
		
	__property Classes::TNotifyEvent OnRequestHangup = {read=GetRequestHangupEvent, write=SetRequestHangupEvent
		};
};


//-- var, const, procedure ---------------------------------------------------
static const Word PWM_GOTCOMMDATA = 0x401;
static const Word PWM_REQUESTHANGUP = 0x402;
static const Word PWM_THREADREADY = 0x403;
static const Word PWM_COMMWRITE = 0x401;
static const Word INPUTBUFFERSIZE = 0x800;
extern PACKAGE TextFile CommsLogFile;
extern PACKAGE void __fastcall LogDebugLastError(unsigned dwLastError, char * szPrefix);
extern PACKAGE void __fastcall LogDebugInfo(char * outstr);
extern PACKAGE void __fastcall Register(void);

}	/* namespace Comm32 */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Comm32;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Comm32
