//---------------------------------------------------------------------------
#ifndef QuiltingLibH
#define QuiltingLibH
//---------------------------------------------------------------------------
#include <vector.h>
//---------------------------------------------------------------------------
#define		Round(x)	(((x)-int(x)>=0.5)?int(x)+1:int(x))
//---------------------------------------------------------------------------
const int ALISOFT_REG_CODE_5_2 = 330001309;
//---------------------------------------------------------------------------
struct ql_Point
{
	double x,y;
};
//---------------------------------------------------------------------------
struct ql_Rect
{
	double left,top,right,bottom;
    double Width()
    {
     	return (right - left + 1.0);
    }
    double Height()
    {
     	return (bottom - top + 1.0);
    }
};
//---------------------------------------------------------------------------
typedef enum{stEof=-1,stContinousLine=0,stContinousArc=1,stDiscreteLine} ql_StitchType;
//---------------------------------------------------------------------------
const AnsiString c_strCompany =
	"AliSoft";
//---------------------------------------------------------------------------
const AnsiString c_strQuiltMaker =
	"QuiltMaker V1.0";
//---------------------------------------------------------------------------
const AnsiString c_strDemoVersionMessage =
	"This option exists only in full version...";
//---------------------------------------------------------------------------
const AnsiString c_strErrorInOpenQuiltingFile =
	"Couldn`t Open Quilting File...";
//---------------------------------------------------------------------------
const AnsiString c_strErrorInSaveQuiltingFile =
	"Couldn`t Save Quilting File...";
//---------------------------------------------------------------------------
const AnsiString c_strUntitledFile =
	"Untitled.vec";
//---------------------------------------------------------------------------
const AnsiString c_strYouMustRestartTheProgramToViewTheChanges =
	"You must restart the program to view new changes";
//---------------------------------------------------------------------------
const int MaxVertexCount=20000;
//---------------------------------------------------------------------------
//----------------------------Quilting---------------------------------------
//---------------------------------------------------------------------------
struct ql_Stitch
{
	int Type;
	ql_Point Start;
    ql_Point End;
    ql_Point Center;
    int Direction;
    int Speed;
};
//---------------------------------------------------------------------------
typedef vector<ql_Stitch> ql_File;
//---------------------------------------------------------------------------
typedef vector<int> ql_Entities;
//---------------------------------------------------------------------------
typedef vector<ql_Entities> ql_Layers;
//---------------------------------------------------------------------------
//------------------------Procedures-----------------------------------------
//---------------------------------------------------------------------------
ql_Point qlPoint(double x,double y);
ql_Rect ql_CalculateFrame(ql_File &QuiltingFile);
bool ql_LoadQuiltingFile(AnsiString strFileName,ql_File &QuiltingFile);
bool ql_SaveQuiltingFileAsDAT(AnsiString strFileName,ql_File &QuiltingFile);
void ql_DrawQuiltingFile(TCanvas *pCanvas,TRect &R,bool bKeepRatio,ql_File &QuiltingFile);
//---------------------------------------------------------------------------
void ql_InitializeSimulator(TRect &R,bool bKeepRatio,ql_File &QuiltingFile);
void ql_DrawStitch(TCanvas *pCanvas,ql_Stitch &QuiltingStitch);
//---------------------------------------------------------------------------
#endif
