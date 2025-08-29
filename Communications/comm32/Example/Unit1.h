//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Comm32.hpp"
//---------------------------------------------------------------------------
struct cnc_Packet// Size = 40 bytes
{
	DWORD cmd;// Command
	DWORD x,y,z;// Position
    DWORD Vx,Vy,Vz;//Speed
    DWORD Ax,Ay,Az;// Acceleration
};
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TComm32 *ComPort;
	TMemo *Memo;
	void __fastcall ComPortReceiveData(Pointer Buffer, WORD BufferLength);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
    cnc_Packet Packet;
    AnsiString strPacket;
    Byte c;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
