//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Properties.h"
#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormProperties *FormProperties;
//---------------------------------------------------------------------------
__fastcall TFormProperties::TFormProperties(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormProperties::GridSelectCell(TObject *Sender, int ACol,
      int ARow, bool &CanSelect)
{
	CanSelect = ((ACol == 1) && (ARow >= 1));
    if(!CanSelect)	return;
    m_nCol = ACol;
    m_nRow = ARow;
	m_strText = Grid->Cells[m_nCol][m_nRow];
}
//---------------------------------------------------------------------------
void __fastcall TFormProperties::GridKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
	switch(Key)
    {
     	case VK_ESCAPE:
        {
			if((m_nCol == 1) && (m_nRow >= 1))
				Grid->Cells[m_nCol][m_nRow] = m_strText;
         	break;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormProperties::FormCreate(TObject *Sender)
{
    m_nCol = 0;
    m_nRow = 0;
	m_strText = "";
	m_strCaption = Caption;
}
//---------------------------------------------------------------------------
void __fastcall TFormProperties::GridMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
	int ACol,ARow;
	Grid->MouseToCell(X,Y,ACol,ARow);
	if((ACol == 1) && (ARow >= 1))
    {
	    m_nCol = ACol;
    	m_nRow = ARow;
		m_strText = Grid->Cells[m_nCol][m_nRow];
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormProperties::GridSetEditText(TObject *Sender, int ACol,
      int ARow, const AnsiString Value)
{
	if((ACol == 1) && (ARow >= 1))
    {
        if(Grid->Objects[ACol][ARow] == NULL)// Number
        {
            try
            {
                StrToFloat(Value);
            }
            catch(...)
            {
            	Grid->Cells[ACol][ARow] = m_strText;
                return;
            }
        }
    }
	FormMain->SetEntityProperty(ARow);
}
//---------------------------------------------------------------------------
