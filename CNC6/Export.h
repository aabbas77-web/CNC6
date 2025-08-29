//---------------------------------------------------------------------------

#ifndef ExportH
#define ExportH
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
//---------------------------------------------------------------------------
class TFormExport : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TPanel *Panel2;
	TBitBtn *BitBtn1;
	TBitBtn *BitBtn2;
	TFormTranslation *FormTranslation1;
	TGroupBox *GroupBox1;
	TEdit *EditSpeed;
	TLabel *Label2;
	TLabel *Label1;
	TEdit *EditZStep;
	void __fastcall BitBtn1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFormExport(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormExport *FormExport;
//---------------------------------------------------------------------------
#endif
