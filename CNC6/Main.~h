//---------------------------------------------------------------------------
#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include <ImgList.hpp>
#include <AppEvnts.hpp>
#include <ExtDlgs.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
#include "FormTranslation.h"
#include "CSPIN.h"
#include "cad_Events.h"
//#include "QuiltingLib.h"
//#include "Plugin.h"
//---------------------------------------------------------------------------
class cad_Document:public TObject
{
public:
	__fastcall cad_Document(){};
    __fastcall ~cad_Document(){};
    VDWG hDwg;     // handle to VeCAD object
  	HWND hVecWnd;     // handle to VeCAD window
};
//---------------------------------------------------------------------------
const AnsiString c_strUntitledFile = "Untitled.vec";
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
	TActionList *ActionList1;
	TMainMenu *MainMenu1;
	TAction *AFile;
	TAction *AFileOpen;
	TAction *AFileSave;
	TAction *AFileSaveAs;
	TAction *AFileExit;
	TMenuItem *File1;
	TMenuItem *Open1;
	TMenuItem *N1;
	TMenuItem *Save1;
	TMenuItem *SaveAs1;
	TMenuItem *Exit1;
	TOpenDialog *OpenDialogDXF;
	TSaveDialog *SaveDialogDXF;
	TControlBar *ControlBar1;
	TToolBar *ToolBar1;
	TToolButton *ToolButton1;
	TToolButton *ToolButton2;
	TToolButton *ToolButton3;
	TImageList *ImageList;
	TAction *AZoom;
	TAction *AZoomAll;
	TAction *AZoomWindow;
	TAction *AZoomIn;
	TAction *AZoomOut;
	TAction *AZoomPanWindow;
	TAction *ZoomToPrev;
	TToolButton *ToolButton4;
	TToolButton *ToolButton5;
	TToolButton *ToolButton6;
	TStatusBar *StatusBar;
	TToolBar *ToolBar2;
	TToolButton *ToolButton7;
	TToolButton *ToolButton8;
	TToolButton *ToolButton9;
	TAction *AFileNew;
	TToolButton *ToolButton10;
	TMenuItem *New1;
	TMenuItem *Zoom1;
	TMenuItem *ZoomAll1;
	TMenuItem *ZoomWindow1;
	TMenuItem *ZoomIn1;
	TMenuItem *ZoomOut1;
	TMenuItem *PanWindow1;
	TMenuItem *ZoomToPrev1;
	TAction *ASnap;
	TAction *ASnapDlg;
	TAction *ASnapGrid;
	TAction *ASnapPolar;
	TAction *ASnapGrips;
	TAction *ASnapPoint;
	TAction *ASnapNear;
	TAction *ASnapEnd;
	TAction *ASnapMid;
	TAction *ASnapCenter;
	TAction *ASnapPerpendicular;
	TAction *ASnapTangent;
	TToolBar *ToolBar3;
	TToolButton *ToolButton12;
	TToolButton *ToolButton17;
	TToolButton *ToolButton18;
	TToolButton *ToolButton19;
	TMenuItem *Snap1;
	TMenuItem *SnapGrid1;
	TMenuItem *SnapGrips1;
	TMenuItem *SnapPoint1;
	TMenuItem *SnapNear1;
	TMenuItem *SnapEnd1;
	TMenuItem *SnapMid1;
	TMenuItem *SnapCenter1;
	TMenuItem *SnapPerpendicular1;
	TMenuItem *SnapTangent1;
	TAction *AEdit;
	TAction *AEditEntProp;
	TAction *AEditCopy;
	TAction *AEditMove;
	TAction *AEditRotate;
	TAction *AEditScale;
	TAction *AEditMirror;
	TAction *AEditErase;
	TAction *AEditUndo;
	TAction *AEditRedo;
	TAction *AEditCutCB;
	TAction *AEditCopyCB;
	TAction *AEditPasteCB;
	TMenuItem *AEdit1;
	TMenuItem *Undo1;
	TMenuItem *Redo1;
	TMenuItem *N3;
	TMenuItem *CutToCB1;
	TMenuItem *CopyToCB1;
	TMenuItem *PasteFromCB1;
	TMenuItem *N4;
	TMenuItem *Properties1;
	TMenuItem *N5;
	TMenuItem *Copy1;
	TMenuItem *Move1;
	TMenuItem *Rotate1;
	TMenuItem *Scale1;
	TMenuItem *Mirror1;
	TMenuItem *N6;
	TMenuItem *Erase1;
	TToolBar *ToolBar4;
	TToolButton *ToolButton11;
	TToolButton *ToolButton22;
	TToolButton *ToolButton23;
	TToolButton *ToolButton24;
	TToolButton *ToolButton25;
	TToolButton *ToolButton26;
	TToolButton *ToolButton27;
	TToolButton *ToolButton30;
	TToolButton *ToolButton31;
	TToolButton *ToolButton32;
	TToolButton *ToolButton33;
	TToolButton *ToolButton34;
	TToolButton *ToolButton35;
	TToolButton *ToolButton36;
	TAction *AHelp;
	TAction *AHelpContents;
	TAction *AHelpAbout;
	TMenuItem *Help1;
	TMenuItem *Contents1;
	TMenuItem *N7;
	TMenuItem *About1;
	TAction *AFileExportDXF;
	TMenuItem *Export1;
	TMenuItem *N8;
	TAction *AFileImportDXF;
	TMenuItem *ExportQuilting1;
	TToolButton *ToolButton37;
	TToolButton *ToolButton38;
	TToolButton *ToolButton39;
	TAction *AFileClose;
	TMenuItem *Close1;
	TMenuItem *N2;
	TPopupMenu *PopupMenuFileList;
	TMenuItem *Close2;
	TToolBar *ToolBar5;
	TToolButton *ToolButton40;
	TAction *ADraw;
	TAction *ADrawPolyline;
	TMenuItem *Draw1;
	TMenuItem *ADrawPolyline1;
	TAction *ADrawArcCSE;
	TAction *ADrawArcSEM;
	TAction *ADrawArcSME;
	TAction *ADrawCircleCR;
	TAction *ADrawCircleCD;
	TAction *ADrawCircle2P;
	TAction *ADrawCircle3P;
	TAction *ADrawEllipse;
	TMenuItem *N9;
	TMenuItem *ArcCSE1;
	TMenuItem *ArcSEM1;
	TMenuItem *ArcSME1;
	TMenuItem *N10;
	TMenuItem *Circle2P1;
	TMenuItem *Circle3P1;
	TMenuItem *CircleCD1;
	TMenuItem *CircleCR1;
	TToolButton *ToolButton41;
	TToolButton *ToolButton42;
	TToolButton *ToolButton43;
	TToolButton *ToolButton44;
	TToolButton *ToolButton46;
	TToolButton *ToolButton47;
	TToolButton *ToolButton48;
	TToolButton *ToolButton49;
	TToolButton *ToolButton50;
	TAction *ADrawLine;
	TAction *ADrawRectangle;
	TAction *AEditSetJump;
	TMenuItem *SetJump1;
	TAction *AEditSetNormal;
	TMenuItem *SetNormal1;
	TSaveDialog *SaveDialogVEC;
	TOpenDialog *OpenDialogVEC;
	TAction *ATools;
	TAction *AToolsSimulator;
	TMenuItem *Tools1;
	TMenuItem *Simulator1;
	TAction *AToolsNavigator;
	TMenuItem *Navigator1;
	TFormTranslation *FormTranslation1;
	TTimer *Timer0;
	TTimer *Timer1;
	TTimer *Timer2;
	TTimer *Timer3;
	TApplicationEvents *ApplicationEvents;
	TOpenPictureDialog *OpenPictureDialog;
	TAction *ATrace;
	TAction *ATraceBackground;
	TMenuItem *Trace1;
	TMenuItem *Background1;
	TAction *ATraceTool;
	TAction *AFileCloseAll;
	TMenuItem *CloseAll1;
	TAction *AFileChangeDim;
	TMenuItem *ChangeDim1;
	TMenuItem *N11;
	TAction *AFileImportPLT;
	TAction *AFileExportPLT;
	TMenuItem *Import1;
	TMenuItem *Export2;
	TMenuItem *ImportPLT1;
	TMenuItem *ExportPLT1;
	TMenuItem *N12;
	TToolButton *ToolButton13;
	TToolButton *ToolButton45;
	TGroupBox *GroupBoxEntities;
	TSplitter *Splitter2;
	TListBox *ListBoxEntities;
	TAction *AToolsOptions;
	TMenuItem *Options1;
	TAction *AFileImport;
	TAction *AFileExport;
	TMenuItem *Line1;
	TAction *ADrawSpline;
	TMenuItem *Spline1;
	TToolButton *ToolButton51;
	TToolButton *ToolButton54;
	TAction *ADrawArc;
	TMenuItem *Arc1;
	TAction *ADrawCircle;
	TMenuItem *Circle1;
	TMenuItem *N13;
	TMenuItem *Ellipse1;
	TMenuItem *Rectangle1;
	TToolButton *ToolButton55;
	TToolButton *ToolButton56;
	TToolButton *ToolButton57;
	TToolBar *ToolBar6;
	TToolButton *ToolButton58;
	TToolButton *ToolButton59;
	TToolButton *ToolButton60;
	TAction *APlugin;
	TMenuItem *Plugin1;
	TSaveDialog *SaveDialogCMD;
	TPanel *Panel1;
	TLabel *Label1;
	TCSpinEdit *CSpinEditDepth;
	TPanel *Panel2;
	TToolBar *ToolBar7;
	TToolButton *ToolButton14;
	TToolButton *ToolButton28;
	TAction *AEntityUp;
	TAction *AEntityDown;
	TLabel *Label2;
	TComboBox *ComboBoxTools;
	TPanel *PanelTool;
	TToolButton *ToolButton29;
	TAction *ADrawSpiral;
	TMenuItem *Spiral1;
	TToolButton *ToolButton52;
	TAction *ADrawSpiral2;
	TMenuItem *Spiral21;
	TToolButton *ToolButton53;
	TAction *ADrawSquare;
	TMenuItem *Square1;
	TToolButton *ToolButton61;
	TColorDialog *ColorDialog;
	TPanel *PanelToolName;
	TPanel *PanelCommandLine;
	TMenuItem *N14;
	TSaveDialog *SaveDialogPLT;
	TOpenDialog *OpenDialogPLT;
	TPageControl *PageControl;
	TAction *ASnapAll;
	TAction *ASnapNone;
	TToolButton *ToolButton20;
	TToolButton *ToolButtonSnapNode;
	TAction *ASnapIntersection;
	TToolButton *ToolButton64;
	TToolButton *ToolButton15;
	TToolButton *ToolButton16;
	TAction *AEntityBuildList;
	TAction *ADrawMultiline;
	TMenuItem *Multiline1;
	TToolButton *ToolButton21;
	TAction *AFileExportCMD;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall AFileExecute(TObject *Sender);
	void __fastcall AFileOpenExecute(TObject *Sender);
	void __fastcall AFileSaveExecute(TObject *Sender);
	void __fastcall AFileSaveAsExecute(TObject *Sender);
	void __fastcall AFileExitExecute(TObject *Sender);
	void __fastcall AZoomExecute(TObject *Sender);
	void __fastcall AZoomAllExecute(TObject *Sender);
	void __fastcall AZoomWindowExecute(TObject *Sender);
	void __fastcall AZoomInExecute(TObject *Sender);
	void __fastcall AZoomOutExecute(TObject *Sender);
	void __fastcall AZoomPanWindowExecute(TObject *Sender);
	void __fastcall ZoomToPrevExecute(TObject *Sender);
	void __fastcall AFileNewExecute(TObject *Sender);
	void __fastcall ASnapExecute(TObject *Sender);
	void __fastcall ASnapDlgExecute(TObject *Sender);
	void __fastcall ASnapGridExecute(TObject *Sender);
	void __fastcall ASnapPolarExecute(TObject *Sender);
	void __fastcall ASnapGripsExecute(TObject *Sender);
	void __fastcall ASnapPointExecute(TObject *Sender);
	void __fastcall ASnapNearExecute(TObject *Sender);
	void __fastcall ASnapEndExecute(TObject *Sender);
	void __fastcall ASnapMidExecute(TObject *Sender);
	void __fastcall ASnapCenterExecute(TObject *Sender);
	void __fastcall ASnapPerpendicularExecute(TObject *Sender);
	void __fastcall ASnapTangentExecute(TObject *Sender);
	void __fastcall AEditExecute(TObject *Sender);
	void __fastcall AEditEntPropExecute(TObject *Sender);
	void __fastcall AEditCopyExecute(TObject *Sender);
	void __fastcall AEditMoveExecute(TObject *Sender);
	void __fastcall AEditRotateExecute(TObject *Sender);
	void __fastcall AEditScaleExecute(TObject *Sender);
	void __fastcall AEditMirrorExecute(TObject *Sender);
	void __fastcall AEditEraseExecute(TObject *Sender);
	void __fastcall AEditUndoExecute(TObject *Sender);
	void __fastcall AEditRedoExecute(TObject *Sender);
	void __fastcall AEditCutCBExecute(TObject *Sender);
	void __fastcall AEditCopyCBExecute(TObject *Sender);
	void __fastcall AEditPasteCBExecute(TObject *Sender);
	void __fastcall AHelpExecute(TObject *Sender);
	void __fastcall AHelpContentsExecute(TObject *Sender);
	void __fastcall AHelpAboutExecute(TObject *Sender);
	void __fastcall AFileExportDXFExecute(TObject *Sender);
	void __fastcall AFileImportDXFExecute(TObject *Sender);
	void __fastcall AFileCloseExecute(TObject *Sender);
	void __fastcall ADrawExecute(TObject *Sender);
	void __fastcall ADrawPolylineExecute(TObject *Sender);
	void __fastcall ADrawArcCSEExecute(TObject *Sender);
	void __fastcall ADrawArcSEMExecute(TObject *Sender);
	void __fastcall ADrawArcSMEExecute(TObject *Sender);
	void __fastcall ADrawCircleCRExecute(TObject *Sender);
	void __fastcall ADrawCircleCDExecute(TObject *Sender);
	void __fastcall ADrawCircle2PExecute(TObject *Sender);
	void __fastcall ADrawCircle3PExecute(TObject *Sender);
	void __fastcall ADrawEllipseExecute(TObject *Sender);
	void __fastcall ADrawLineExecute(TObject *Sender);
	void __fastcall ADrawRectangleExecute(TObject *Sender);
	void __fastcall AEditSetJumpExecute(TObject *Sender);
	void __fastcall AEditSetNormalExecute(TObject *Sender);
	void __fastcall AToolsExecute(TObject *Sender);
	void __fastcall AToolsSimulatorExecute(TObject *Sender);
	void __fastcall AToolsNavigatorExecute(TObject *Sender);
	void __fastcall ATraceExecute(TObject *Sender);
	void __fastcall ATraceToolExecute(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall AFileCloseAllExecute(TObject *Sender);
	void __fastcall AFileChangeDimExecute(TObject *Sender);
	void __fastcall AFileImportPLTExecute(TObject *Sender);
	void __fastcall AFileExportPLTExecute(TObject *Sender);
	void __fastcall ListBoxEntitiesClick(TObject *Sender);
	void __fastcall AToolsOptionsExecute(TObject *Sender);
	void __fastcall AFileImportExecute(TObject *Sender);
	void __fastcall AFileExportExecute(TObject *Sender);
	void __fastcall ADrawSplineExecute(TObject *Sender);
	void __fastcall ADrawArcExecute(TObject *Sender);
	void __fastcall ADrawCircleExecute(TObject *Sender);
	void __fastcall APluginExecute(TObject *Sender);
	void __fastcall CSpinEditDepthChange(TObject *Sender);
	void __fastcall AEntityUpExecute(TObject *Sender);
	void __fastcall AEntityDownExecute(TObject *Sender);
	void __fastcall ComboBoxToolsChange(TObject *Sender);
	void __fastcall ADrawSpiralExecute(TObject *Sender);
	void __fastcall ADrawSpiral2Execute(TObject *Sender);
	void __fastcall ADrawSquareExecute(TObject *Sender);
	void __fastcall ApplicationEventsHint(TObject *Sender);
	void __fastcall PageControlResize(TObject *Sender);
	void __fastcall PageControlChange(TObject *Sender);
	void __fastcall ASnapAllExecute(TObject *Sender);
	void __fastcall ASnapNoneExecute(TObject *Sender);
	void __fastcall ASnapIntersectionExecute(TObject *Sender);
	void __fastcall AEntityBuildListExecute(TObject *Sender);
	void __fastcall ADrawMultilineExecute(TObject *Sender);
	void __fastcall AFileExportCMDExecute(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFormMain(TComponent* Owner);
	void __fastcall LoadSettings();
	void __fastcall SaveSettings();
	void __fastcall AfterOpen(AnsiString strFileName);

	void __fastcall NewDocument(AnsiString strFileName);
	void __fastcall BuildEntitiesList();
	void __fastcall FindPlugins(TStringList *pFiles);
	void __fastcall UpdatePlugins();
	void __fastcall DoClickPlugin(TObject *Sender);
	void __fastcall ClearPlugins();
	void __fastcall ShowEntityProperty(int nEntityIndex);
	void __fastcall SetEntityProperty(int nRow);
	void __fastcall ActivateEntity(int nEntityIndex);
	void __fastcall ActivateDesigner();

    VDWG hDwg;     // handle to VeCAD object
  	HWND hVecWnd;     // handle to VeCAD window
  	int SBarH;       // height of status bar

    int m_nDotLineStyleIndex;
    int m_nSoildLineStyleIndex;

    AnsiString m_strAppTitle;
	int m_nIndex;

    TCanvas *m_pCanvas;

    int m_nWorkingAreaRectIndex;
    int m_nImageIndex;
    AnsiString strImageName;

    int m_nLanguageID;
    double m_dWorkingAreaWidthMM;// MM
    double m_dWorkingAreaHeightMM;
    double m_dMinStepMM;

    // Grid
    double m_dGridSmallStepX,m_dGridSmallStepY;
    int m_nGridLargeStepX,m_nGridLargeStepY;
    bool m_bGridSnap,m_bGridShow;
    int m_nGridSmallColor,m_nGridLargeColor;
    int nSnapData;

    TStringList *pPlugins;
    int nCurrPluginIndex;
    TMenuItem *pItem;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif
