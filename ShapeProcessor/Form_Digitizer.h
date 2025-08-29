//---------------------------------------------------------------------------
#ifndef Form_DigitizerH
#define Form_DigitizerH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
#include "shp_Image.h"
#include "shp_ColorQuantizer.h"
//---------------------------------------------------------------------------
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
#include <ActnList.hpp>
#include <Menus.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TFormDigitizer : public TForm
{
__published:	// IDE-managed Components
	TStatusBar *StatusBar;
	TScrollBox *ScrollBox;
	TImage *Image;
	TOpenPictureDialog *OpenPictureDialog;
	TMainMenu *MainMenu1;
	TActionList *ActionList1;
	TAction *AFile;
	TAction *AFileOpen;
	TAction *AFileExit;
	TMenuItem *File1;
	TMenuItem *Open1;
	TAction *ASeparator;
	TMenuItem *N1;
	TMenuItem *Exit1;
	TAction *AFileSaveAs;
	TSavePictureDialog *SavePictureDialog;
	TMenuItem *Saveas1;
	TMenuItem *N2;
	TAction *AProcessing;
	TAction *AProcessingQuantize;
	TMenuItem *Processing1;
	TMenuItem *Quantize1;
	TDrawGrid *DrawGridColors;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall AFileExecute(TObject *Sender);
	void __fastcall AFileOpenExecute(TObject *Sender);
	void __fastcall AFileExitExecute(TObject *Sender);
	void __fastcall AFileSaveAsExecute(TObject *Sender);
	void __fastcall AProcessingExecute(TObject *Sender);
	void __fastcall AProcessingQuantizeExecute(TObject *Sender);
	void __fastcall ImageMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
	void __fastcall ImageMouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y);
	void __fastcall ImageMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
	void __fastcall DrawGridColorsDrawCell(TObject *Sender, int ACol,
          int ARow, TRect &Rect, TGridDrawState State);
private:	// User declarations
public:		// User declarations
	__fastcall TFormDigitizer(TComponent* Owner);
	void __fastcall UpdateStatusBar();
    shp_Image *pImage;
    shp_ColorQuantizer ColorQuantizer;
    UINT MousePosX,MousePosY;
    TColor MouseColor;
    Byte MouseRed,MouseGreen,MouseBlue;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormDigitizer *FormDigitizer;
//---------------------------------------------------------------------------
#endif
