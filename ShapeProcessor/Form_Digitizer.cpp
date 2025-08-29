//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Form_Digitizer.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormDigitizer *FormDigitizer;
//---------------------------------------------------------------------------
__fastcall TFormDigitizer::TFormDigitizer(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormDigitizer::UpdateStatusBar()
{
    MouseColor = Image->Canvas->Pixels[MousePosX][MousePosY];
    MouseRed = GetRValue(MouseColor);
    MouseGreen = GetGValue(MouseColor);
    MouseBlue = GetBValue(MouseColor);

    StatusBar->Panels->Items[0]->Text=FormatFloat("0",MousePosX)+","+FormatFloat("0",MousePosY);
    StatusBar->Panels->Items[1]->Text=FormatFloat("0",MouseRed)+","+FormatFloat("0",MouseGreen)+","+FormatFloat("0",MouseBlue);
    StatusBar->Panels->Items[2]->Text=FormatFloat("0",pImage->Width)+"x"+FormatFloat("0",pImage->Height)+"x"+FormatFloat("0",pImage->Bits)+" > "+FormatFloat("0",ColorQuantizer.ColorsCount);
    if((pImage->ppLines)&&(pImage->Bits<=8)&&(MousePosX<pImage->Width)&&(MousePosY<pImage->Height))
    {
        StatusBar->Panels->Items[3]->Text=FormatFloat("0",pImage->ppLines[MousePosY][MousePosX]);
    }
    else
    {
        StatusBar->Panels->Items[3]->Text=FormatFloat("0",0);
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormDigitizer::FormCreate(TObject *Sender)
{
	pImage = new shp_Image();	

    MousePosX=0;
    MousePosY=0;
    UpdateStatusBar();
}
//---------------------------------------------------------------------------
void __fastcall TFormDigitizer::FormDestroy(TObject *Sender)
{
	if(pImage)
    {
     	delete pImage;
        pImage = NULL;
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormDigitizer::AFileExecute(TObject *Sender)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormDigitizer::AFileOpenExecute(TObject *Sender)
{
	if(!OpenPictureDialog->Execute())	return;
    pImage->LoadFromFile(OpenPictureDialog->FileName);

    ColorQuantizer.Assign(pImage);
    DrawGridColors->RowCount = ColorQuantizer.ColorsCount;
    Image->Picture->Assign(pImage->pBitmap);
}
//---------------------------------------------------------------------------
void __fastcall TFormDigitizer::AFileSaveAsExecute(TObject *Sender)
{
	if(!SavePictureDialog->Execute())	return;
    pImage->SaveToFile(SavePictureDialog->FileName);
}
//---------------------------------------------------------------------------
void __fastcall TFormDigitizer::AFileExitExecute(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TFormDigitizer::AProcessingExecute(TObject *Sender)
{
//	
}
//---------------------------------------------------------------------------

void __fastcall TFormDigitizer::AProcessingQuantizeExecute(TObject *Sender)
{
	AnsiString strText = "8";
    if(!InputQuery("Colors","Enter Colors Count:",strText))	return;
	UINT nColorsCount = StrToInt(strText);
    ColorQuantizer.Quantize(nColorsCount,true,false);
    DrawGridColors->RowCount = ColorQuantizer.ColorsCount;
    pImage->Assign(ColorQuantizer.m_pImage);
    Image->Picture->Assign(pImage->pBitmap);
}
//---------------------------------------------------------------------------

void __fastcall TFormDigitizer::ImageMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
//	
}
//---------------------------------------------------------------------------

void __fastcall TFormDigitizer::ImageMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
    MousePosX = X;
    MousePosY = Y;
    UpdateStatusBar();
}
//---------------------------------------------------------------------------

void __fastcall TFormDigitizer::ImageMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
//	
}
//---------------------------------------------------------------------------

void __fastcall TFormDigitizer::DrawGridColorsDrawCell(TObject *Sender,
      int ACol, int ARow, TRect &Rect, TGridDrawState State)
{
    DrawGridColors->Canvas->Brush->Style = bsSolid;
    DrawGridColors->Canvas->Brush->Color = ColorQuantizer.pColors[ARow];
	int d = 5;
	DrawGridColors->Canvas->FillRect(::Rect(Rect.left+d,Rect.top+d,Rect.right-d,Rect.bottom-d));
}
//---------------------------------------------------------------------------

