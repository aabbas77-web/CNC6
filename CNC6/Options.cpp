//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Options.h"
//#include "quilt_Messages.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "FormTranslation"
#pragma resource "*.dfm"
TFormOptions *FormOptions;
//---------------------------------------------------------------------------
__fastcall TFormOptions::TFormOptions(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormOptions::BitBtn1Click(TObject *Sender)
{
	ModalResult = mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TFormOptions::ToolButton1Click(TObject *Sender)
{
    if(ComboBoxLanguage->Items->Count <= 0)	return;
	PanelLanguage->Tag = 1;// Arabic
    PanelLanguage->Caption = ComboBoxLanguage->Items->Strings[0];
}
//---------------------------------------------------------------------------

void __fastcall TFormOptions::ToolButton2Click(TObject *Sender)
{
    if(ComboBoxLanguage->Items->Count <= 0)	return;
	PanelLanguage->Tag = 0;// English
    PanelLanguage->Caption = ComboBoxLanguage->Items->Strings[1];
}
//---------------------------------------------------------------------------

void __fastcall TFormOptions::ToolButton3Click(TObject *Sender)
{
    if(ComboBoxLanguage->Items->Count <= 0)	return;
	PanelLanguage->Tag = 2;// Frensh
    PanelLanguage->Caption = ComboBoxLanguage->Items->Strings[2];
}
//---------------------------------------------------------------------------

void __fastcall TFormOptions::PanelGridSmallColorClick(TObject *Sender)
{
    ColorDialog->Color = PanelGridSmallColor->Color;
	if(!ColorDialog->Execute())	return;
    PanelGridSmallColor->Color = ColorDialog->Color;
}
//---------------------------------------------------------------------------

void __fastcall TFormOptions::PanelGridLargeColorClick(TObject *Sender)
{
    ColorDialog->Color = PanelGridLargeColor->Color;
	if(!ColorDialog->Execute())	return;
    PanelGridLargeColor->Color = ColorDialog->Color;	
}
//---------------------------------------------------------------------------

void __fastcall TFormOptions::ListBoxToolsClick(TObject *Sender)
{
/*
	if(ListBoxTools->ItemIndex < 0)	return;
    int i = ListBoxTools->ItemIndex;
    EditToolOX->Text = FormatFloat("0.00",g_pTools[i].x0);
    EditToolOY->Text = FormatFloat("0.00",g_pTools[i].y0);
	PanelToolColor->Color = g_pTools[i].nColor;
	EditToolName->Text = g_pTools[i].strName;
*/
}
//---------------------------------------------------------------------------

void __fastcall TFormOptions::EditToolOXChange(TObject *Sender)
{
/*
	try
    {
		StrToFloat(EditToolOX->Text);
    }
    catch(...)
    {
		return;
    }
	if(ListBoxTools->ItemIndex < 0)	return;
    int i = ListBoxTools->ItemIndex;
    g_pTools[i].x0 = StrToFloat(EditToolOX->Text);
*/
}
//---------------------------------------------------------------------------

void __fastcall TFormOptions::EditToolOYChange(TObject *Sender)
{
/*
	try
    {
		StrToFloat(EditToolOY->Text);
    }
    catch(...)
    {
		return;
    }
	if(ListBoxTools->ItemIndex < 0)	return;
    int i = ListBoxTools->ItemIndex;
    g_pTools[i].y0 = StrToFloat(EditToolOY->Text);
*/
}
//---------------------------------------------------------------------------

void __fastcall TFormOptions::EditToolNameChange(TObject *Sender)
{
/*
	if(ListBoxTools->ItemIndex < 0)	return;
    int i = ListBoxTools->ItemIndex;
    g_pTools[i].strName = EditToolName->Text;
*/
}
//---------------------------------------------------------------------------

void __fastcall TFormOptions::PanelToolColorClick(TObject *Sender)
{
/*
    ColorDialog->Color = PanelToolColor->Color;
	if(!ColorDialog->Execute())	return;
    PanelToolColor->Color = ColorDialog->Color;
	if(ListBoxTools->ItemIndex < 0)	return;
    int i = ListBoxTools->ItemIndex;
    g_pTools[i].nColor = PanelToolColor->Color;
*/
}
//---------------------------------------------------------------------------

void __fastcall TFormOptions::EditGridOXEnter(TObject *Sender)
{
	pEdit = (TEdit *)Sender;
    if(pEdit == NULL)	return;
	m_strText = pEdit->Text;
}
//---------------------------------------------------------------------------

void __fastcall TFormOptions::EditGridOXChange(TObject *Sender)
{
	pEdit = (TEdit *)Sender;
    if(pEdit == NULL)	return;
	try
    {
		StrToFloat(pEdit->Text);
    }
    catch(...)
    {
		pEdit->Text = m_strText;
        pEdit->SelStart = m_strText.Length();
        return;
    }	
	m_strText = pEdit->Text;
}
//---------------------------------------------------------------------------

void __fastcall TFormOptions::FormCreate(TObject *Sender)
{
	ListBoxTools->ItemIndex = 0;
    ListBoxToolsClick(NULL);	
}
//---------------------------------------------------------------------------

