//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Export.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "FormTranslation"
#pragma resource "*.dfm"
TFormExport *FormExport;
//---------------------------------------------------------------------------
__fastcall TFormExport::TFormExport(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormExport::BitBtn1Click(TObject *Sender)
{
	ModalResult = mrOk;
}
//---------------------------------------------------------------------------

