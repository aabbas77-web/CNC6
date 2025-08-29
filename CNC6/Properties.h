//---------------------------------------------------------------------------

#ifndef PropertiesH
#define PropertiesH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TFormProperties : public TForm
{
__published:	// IDE-managed Components
	TStringGrid *Grid;
	void __fastcall GridSelectCell(TObject *Sender, int ACol, int ARow,
          bool &CanSelect);
	void __fastcall GridKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall GridMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
	void __fastcall GridSetEditText(TObject *Sender, int ACol, int ARow,
          const AnsiString Value);
private:	// User declarations
public:		// User declarations
	__fastcall TFormProperties(TComponent* Owner);
    AnsiString m_strText;
    int m_nCol,m_nRow;
    AnsiString m_strCaption;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormProperties *FormProperties;
//---------------------------------------------------------------------------
#endif
