//---------------------------------------------------------------------------
#ifndef SimulatorH
#define SimulatorH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <ActnList.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <ToolWin.hpp>
#include "CSPIN.h"
#include <Buttons.hpp>
//---------------------------------------------------------------------------
#include "FormTranslation.h"
#include "CNCLib.h"
#include "CPort.hpp"
#include "cad_Events.h"
//---------------------------------------------------------------------------
class TFormSimulator : public TForm
{
__published:	// IDE-managed Components
	TOpenDialog *OpenDialogPLT;
	TSaveDialog *SaveDialogPLT;
	TActionList *ActionList1;
	TMainMenu *MainMenu1;
	TAction *AFile;
	TAction *AFileOpen;
	TAction *AFileSave;
	TAction *AFileSaveAs;
	TAction *AFileClose;
	TMenuItem *File1;
	TMenuItem *Open1;
	TMenuItem *N1;
	TMenuItem *Save1;
	TMenuItem *SaveAs1;
	TMenuItem *N2;
	TMenuItem *Close1;
	TStatusBar *StatusBar1;
	TPanel *Panel1;
	TToolBar *ToolBar1;
	TAction *ASimulator;
	TAction *ASimulatorPlay;
	TAction *ASimulatorPause;
	TAction *ASimulatorStop;
	TMenuItem *Simulator1;
	TMenuItem *Play1;
	TMenuItem *Pause1;
	TMenuItem *Stop1;
	TCheckBox *CheckBoxKeepRatio;
	TCSpinEdit *CSpinEditDelay;
	TLabel *Label1;
	TAction *ASimulatorNext;
	TMenuItem *Next1;
	TToolButton *ToolButton1;
	TToolButton *ToolButton2;
	TToolButton *ToolButton3;
	TToolButton *ToolButton4;
	TToolButton *ToolButton5;
	TToolButton *ToolButton6;
	TToolButton *ToolButton7;
	TToolButton *ToolButton8;
	TToolButton *ToolButton9;
	TLabel *Label3;
	TEdit *EditElementIndex;
	TFormTranslation *FormTranslation1;
	TLabel *Label4;
	TEdit *EditTotalElements;
	TEdit *EditCurrentPositionX;
	TLabel *Label5;
	TLabel *Label6;
	TEdit *EditSpeedX;
	TEdit *EditCurrentPositionY;
	TAction *AMachine;
	TAction *AMachineGenerate;
	TAction *AMachineLoad;
	TAction *AMachineSend;
	TComPort *ComPort;
	TMenuItem *Machine1;
	TMenuItem *Generate1;
	TMenuItem *Load1;
	TMenuItem *Send1;
	TSaveDialog *SaveDialogCMD;
	TTimer *Timer;
	TOpenDialog *OpenDialogCMD;
	TLabel *Label2;
	TEdit *EditSpeedY;
	TUpDown *UpDown;
	TEdit *EditCurrentIndex;
	TPanel *PanelDisplay;
	TEdit *EditCurrentPositionZ;
	TLabel *Label7;
	TEdit *EditTool;
	TComDataPacket *ComDataPacket;
	void __fastcall AFileExecute(TObject *Sender);
	void __fastcall AFileOpenExecute(TObject *Sender);
	void __fastcall AFileSaveExecute(TObject *Sender);
	void __fastcall AFileSaveAsExecute(TObject *Sender);
	void __fastcall AFileCloseExecute(TObject *Sender);
	void __fastcall ASimulatorExecute(TObject *Sender);
	void __fastcall ASimulatorPlayExecute(TObject *Sender);
	void __fastcall ASimulatorPauseExecute(TObject *Sender);
	void __fastcall ASimulatorStopExecute(TObject *Sender);
	void __fastcall TimerTimer(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall CSpinEditDelayChange(TObject *Sender);
	void __fastcall ASimulatorNextExecute(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall AMachineExecute(TObject *Sender);
	void __fastcall AMachineGenerateExecute(TObject *Sender);
	void __fastcall AMachineLoadExecute(TObject *Sender);
	void __fastcall AMachineSendExecute(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall UpDownChangingEx(TObject *Sender, bool &AllowChange,
          short NewValue, TUpDownDirection Direction);
	void __fastcall PanelDisplayResize(TObject *Sender);
	void __fastcall ComDataPacketPacket(TObject *Sender, AnsiString Str);
private:	// User declarations
public:		// User declarations
	__fastcall TFormSimulator(TComponent* Owner);
	void __fastcall DrawCNCStitch();
	void __fastcall DrawCNCFile();
	void __fastcall NewDocument(AnsiString strFileName);
	void __fastcall ClearDrawing();
	void __fastcall SendStitch(cnc_Stitch &Stitch);
	void __fastcall CalculateSpeeds();
    cnc_File CNCFile;
	int m_nCurrentIndex;
    int d;
    TRect WorkingAreaBox;
    cnc_Stitch CNCStitch;

    AnsiString m_strAppTitle;
    VDWG hDwg;     // handle to VeCAD object
  	HWND hVecWnd;     // handle to VeCAD window
  	int SBarH;       // height of status bar
    AnsiString m_strFileName;
    
    AnsiString strPacket;
    cnc_Packet Packet;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormSimulator *FormSimulator;
//---------------------------------------------------------------------------
#endif
