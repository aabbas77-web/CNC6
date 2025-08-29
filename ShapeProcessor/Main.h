//---------------------------------------------------------------------------
#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
#include "shp_Contour.h"
#include <ExtCtrls.hpp>
#include <ActnList.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
	TMainMenu *MainMenu;
	TOpenDialog *OpenDialog;
	TSaveDialog *SaveDialog;
	TMenuItem *File1;
	TMenuItem *Open1;
	TMenuItem *Saveas1;
	TMenuItem *N1;
	TMenuItem *Exit1;
	TPanel *Panel1;
	TPanel *PanelDisplay;
	TActionList *ActionList;
	TAction *AFileOpen;
	TAction *AFileSaveAs;
	TAction *AFileExit;
	TToolBar *ToolBar1;
	TToolButton *ToolButton1;
	TToolButton *ToolButton2;
	TToolButton *ToolButton3;
	TMenuItem *Draw1;
	TAction *ADrawPolyline;
	TMenuItem *Polyline1;
	TToolButton *ToolButton4;
	TAction *AProcessingAdjust;
	TMenuItem *Processing1;
	TMenuItem *Adjust1;
	TMenuItem *Zoom1;
	TAction *AZoomAll;
	TMenuItem *ZoomAll1;
	TToolButton *ToolButton5;
	TToolButton *ToolButton6;
	TAction *AZoomWin;
	TAction *AZoomIn;
	TAction *AZoomOut;
	TMenuItem *ZoomWin1;
	TMenuItem *ZoomIn1;
	TMenuItem *ZoomOut1;
	TToolButton *ToolButton7;
	TToolButton *ToolButton8;
	TToolButton *ToolButton9;
	TAction *AFileReport;
	TMenuItem *Report1;
	TToolButton *ToolButton10;
	TAction *AProcessingDivide;
	TMenuItem *Divide1;
	TAction *AProcessingReassemple;
	TMenuItem *Reassemple1;
	TAction *ADrawClear;
	TMenuItem *Clear1;
	TMenuItem *N2;
	TToolButton *ToolButton11;
	TToolButton *ToolButton12;
	TAction *ADrawDraw;
	TMenuItem *Draw2;
	TToolButton *ToolButton13;
	TAction *ADrawDrawSmooth;
	TMenuItem *DrawS1;
	TToolButton *ToolButton14;
	TAction *ADigitizerDigitizer;
	TMenuItem *Digitizer1;
	TMenuItem *Digitizer2;
	TAction *AFile;
	TAction *ADigitizer;
	TAction *ADraw;
	TAction *AProcessing;
	TAction *AZoom;
	TAction *ASeparator;
	TAction *AProcessingSameDivide;
	TMenuItem *SameDivide1;
	TAction *AProcessingExtrude;
	TMenuItem *Extrude1;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall PanelDisplayResize(TObject *Sender);
	void __fastcall AFileOpenExecute(TObject *Sender);
	void __fastcall AFileSaveAsExecute(TObject *Sender);
	void __fastcall AFileExitExecute(TObject *Sender);
	void __fastcall ADrawPolylineExecute(TObject *Sender);
	void __fastcall AProcessingAdjustExecute(TObject *Sender);
	void __fastcall AZoomAllExecute(TObject *Sender);
	void __fastcall AZoomWinExecute(TObject *Sender);
	void __fastcall AZoomInExecute(TObject *Sender);
	void __fastcall AZoomOutExecute(TObject *Sender);
	void __fastcall AFileReportExecute(TObject *Sender);
	void __fastcall AProcessingDivideExecute(TObject *Sender);
	void __fastcall AProcessingReassempleExecute(TObject *Sender);
	void __fastcall ADrawClearExecute(TObject *Sender);
	void __fastcall ADrawDrawExecute(TObject *Sender);
	void __fastcall ADrawDrawSmoothExecute(TObject *Sender);
	void __fastcall ADigitizerDigitizerExecute(TObject *Sender);
	void __fastcall ADigitizerExecute(TObject *Sender);
	void __fastcall ADrawExecute(TObject *Sender);
	void __fastcall AFileExecute(TObject *Sender);
	void __fastcall AProcessingExecute(TObject *Sender);
	void __fastcall AZoomExecute(TObject *Sender);
	void __fastcall AProcessingSameDivideExecute(TObject *Sender);
	void __fastcall AProcessingExtrudeExecute(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFormMain(TComponent* Owner);
	void __fastcall CreateVecWindow(HWND Handle);
	void __fastcall ClearDoc();
	void __fastcall DrawContour(shp_Contour &Contour,bool bSmooth=false,TColor color=clBlack);
	void __fastcall SaveContourRep(AnsiString strFileName,shp_Contour Contour);
    HWND ghwVec;   // VeCAD window to display draw
    int  SBarH;    // height of status bar
    AnsiString m_strFileName;
    bool TheEnd;
    AnsiString m_strAppCaption;
    int m_nDocIndex;
    shp_Contour Contour,ResContour;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif
