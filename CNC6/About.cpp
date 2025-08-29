//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "About.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormAbout *FormAbout;
//---------------------------------------------------------------------------
__fastcall TFormAbout::TFormAbout(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormAbout::Button1Click(TObject *Sender)
{
 	ModalResult = mrOk;    
}
//---------------------------------------------------------------------------
void __fastcall TFormAbout::LabelURLClick(TObject *Sender)
{
	ShellExecute(0,"open",LabelURL->Hint.c_str(),"","",SW_SHOW);
}
//---------------------------------------------------------------------------

void __fastcall TFormAbout::LabelEMailClick(TObject *Sender)
{
	ShellExecute(0,"open",LabelEMail->Hint.c_str(),"","",SW_SHOW);
}
//---------------------------------------------------------------------------

