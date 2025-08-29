//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Comm32"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ComPortReceiveData(Pointer Buffer,
      WORD BufferLength)
{
	Packet = *((cnc_Packet *)Buffer);

    strPacket = "(";
	strPacket += IntToStr(Packet.cmd)+",";
	strPacket += IntToStr(Packet.x)+",";
	strPacket += IntToStr(Packet.y)+",";
	strPacket += IntToStr(Packet.z)+",";
	strPacket += IntToStr(Packet.Vx)+",";
	strPacket += IntToStr(Packet.Vy)+",";
	strPacket += IntToStr(Packet.Vz)+",";
	strPacket += IntToStr(Packet.Ax)+",";
	strPacket += IntToStr(Packet.Ay)+",";
	strPacket += IntToStr(Packet.Az)+")";
	Memo->Lines->Add(strPacket);

    c = 'A';
    ComPort->WriteCommData(&c,1);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
	ComPort->StartComm();	
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormDestroy(TObject *Sender)
{
	ComPort->StopComm();
}
//---------------------------------------------------------------------------
