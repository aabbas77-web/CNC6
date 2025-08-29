//---------------------------------------------------------------------------

#ifndef OptionsH
#define OptionsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include "FormTranslation.h"
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include <ImgList.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TFormOptions : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TBitBtn *BitBtn1;
	TBitBtn *BitBtn2;
	TFormTranslation *FormTranslation1;
	TImageList *ImageList1;
	TPageControl *PageControl1;
	TTabSheet *TabSheetLanguage;
	TLabel *Label1;
	TToolBar *ToolBar1;
	TToolButton *ToolButton1;
	TToolButton *ToolButton2;
	TToolButton *ToolButton3;
	TComboBox *ComboBoxLanguage;
	TPanel *PanelLanguage;
	TTabSheet *TabSheetGrid;
	TGroupBox *GroupBox2;
	TCheckBox *CheckBoxGridSnap;
	TCheckBox *CheckBoxGridShow;
	TTabSheet *TabSheetTools;
	TGroupBox *GroupBox3;
	TLabel *Label4;
	TLabel *Label5;
	TEdit *EditGridSmallStepX;
	TEdit *EditGridSmallStepY;
	TGroupBox *GroupBox4;
	TLabel *Label6;
	TLabel *Label7;
	TEdit *EditGridLargeStepX;
	TEdit *EditGridLargeStepY;
	TPanel *PanelGridSmallColor;
	TPanel *PanelGridLargeColor;
	TColorDialog *ColorDialog;
	TListBox *ListBoxTools;
	TGroupBox *GroupBox5;
	TLabel *Label8;
	TLabel *Label9;
	TEdit *EditToolOX;
	TEdit *EditToolOY;
	TGroupBox *GroupBox6;
	TLabel *Label10;
	TEdit *EditToolName;
	TPanel *PanelToolColor;
	TLabel *Label11;
	TLabel *LabelRestartProg;
	TLabel *LabelSaveChanges;
	void __fastcall BitBtn1Click(TObject *Sender);
	void __fastcall ToolButton1Click(TObject *Sender);
	void __fastcall ToolButton2Click(TObject *Sender);
	void __fastcall ToolButton3Click(TObject *Sender);
	void __fastcall PanelGridSmallColorClick(TObject *Sender);
	void __fastcall PanelGridLargeColorClick(TObject *Sender);
	void __fastcall ListBoxToolsClick(TObject *Sender);
	void __fastcall EditToolOXChange(TObject *Sender);
	void __fastcall EditToolOYChange(TObject *Sender);
	void __fastcall EditToolNameChange(TObject *Sender);
	void __fastcall PanelToolColorClick(TObject *Sender);
	void __fastcall EditGridOXEnter(TObject *Sender);
	void __fastcall EditGridOXChange(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFormOptions(TComponent* Owner);
    AnsiString m_strText;
    TEdit *pEdit;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormOptions *FormOptions;
//---------------------------------------------------------------------------
#endif
