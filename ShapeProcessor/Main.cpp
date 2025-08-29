//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Main.h"
#include "api_VecApi.h"
#include "api_Messages.h"
#include "Form_Digitizer.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMain *FormMain;
//---------------------------------------------------------------------------
const int ALISOFT_REG_CODE_5_2 = 330001309;
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ClearDoc()
{
	vlClear(true);
    vlRedraw();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::CreateVecWindow(HWND Handle)
{
    TheEnd=false;

    // Register your copy of Vecad.dll
    vlRegistration(ALISOFT_REG_CODE_5_2);

    // Set message handler function
    vlSetMsgHandler(DwgProc);

    // Create VeCAD StatusBar
    vlStatBarCreate( Handle, &SBarH );

    // Create VeCAD window, size will be set in OnSize()
    ghwVec = vlWndCreate( Handle, VL_WS_CHILD|VL_WS_SCROLL|VL_WS_BORDER, 0,0,400,300 );
    if(ghwVec)
    {
        ::PostMessage( Handle, WM_SIZE, 0, 0 );
        vlPropPut( VD_WND_EMPTYTEXT, (int)ghwVec,m_strAppCaption.c_str());
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::DrawContour(shp_Contour &Contour,bool bSmooth,TColor color)
{
    if(TheEnd) return;

    shp_Point p;
    int nEntityIndex;
    vlPolylineBegin();
    for(UINT i=0;i<Contour.size();i++)
    {
        p = Contour[i];
        vlVertex(p.x,p.y);
    }
    if(bSmooth)
	    nEntityIndex = vlAddPolyline(VL_POLY_FITBSPL3,false);
    else
	    nEntityIndex = vlAddPolyline(VL_POLY_LINE,false);
    vlPropPutInt(VD_ENT_COLOR,nEntityIndex,color);
    vlRedraw();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::SaveContourRep(AnsiString strFileName,shp_Contour Contour)
{
	int nCount = Contour.size();
	if(nCount < 2)	return;
    TStringList *pList = new TStringList();
    shp_Point p1,p;
    AnsiString strText;
    p1 = Contour[0];
    for(int i=1;i<nCount;i++)
    {
    	p = Contour[i%nCount];
        strText = FormatFloat("p[0000]",i)+"  ,  "+FormatFloat("Dist[0.000]",shp_Distance(p1,p));          
        pList->Add(strText);
        p1 = p;
    }
    pList->SaveToFile(strFileName);
    if(pList)
    {
     	delete pList;
        pList = NULL;
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormCreate(TObject *Sender)
{
	Left = 0;
    Top = 0;
    Width = Screen->Width;
    Height = Screen->Height - 30;

    m_strAppCaption = Caption;

    CreateVecWindow(PanelDisplay->Handle);
    m_nDocIndex = vlFileNew(ghwVec,"");
    ClearDoc();

//    shp_Smooth_Contour(10.0,"D:\\Abbas\\Contours\\0005.txt","D:\\Abbas\\Contours\\0005_div.txt");
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::PanelDisplayResize(TObject *Sender)
{
    if(TheEnd) return;

    int w, h;
    vlGetWinSize( PanelDisplay->Handle, &w, &h );
    if(w>0 && h>0)
    {
        // Resize drawing window
      	vlWndResize( ghwVec, 0, 0, w, h - SBarH );

        // Resize statusbar
        vlStatBarResize();

        // Update View
        vlZoom(VL_ZOOM_ALL);
        vlUpdate();
        vlExecute(VC_ZOOM_ALL);
        vlUpdate();
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormDestroy(TObject *Sender)
{
    vlExecute(VC_FILE_CLOSEALL);
    TheEnd=true;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AFileExecute(TObject *Sender)
{
//	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AFileOpenExecute(TObject *Sender)
{
	if(OpenDialog->Execute())
    {
    	shp_LoadContour(Contour,OpenDialog->FileName);

        Caption = FormatFloat("Tester [0 points]",Contour.size());
        ClearDoc();
        DrawContour(Contour,false,clBlack);
    	vlZoom(VL_ZOOM_ALL);
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AFileSaveAsExecute(TObject *Sender)
{
	if(SaveDialog->Execute())
    {
    	shp_SaveContour(Contour,SaveDialog->FileName);
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AFileReportExecute(TObject *Sender)
{
	if(SaveDialog->Execute())
    {
	    SaveContourRep(SaveDialog->FileName,Contour);
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AFileExitExecute(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AZoomExecute(TObject *Sender)
{
//	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AZoomAllExecute(TObject *Sender)
{
	vlExecute(VC_ZOOM_ALL);	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AZoomWinExecute(TObject *Sender)
{
	vlExecute(VC_ZOOM_WIN);	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AZoomInExecute(TObject *Sender)
{
	vlExecute(VC_ZOOM_IN);	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AZoomOutExecute(TObject *Sender)
{
	vlExecute(VC_ZOOM_OUT);	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ADrawPolylineExecute(TObject *Sender)
{
	ClearDoc();
	vlExecute(VC_DRAW_POLYLINE);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AProcessingExecute(TObject *Sender)
{
//	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AProcessingAdjustExecute(TObject *Sender)
{
	shp_AutoSetContourStartPoint(Contour);
	shp_Adjust_Contour(Contour,ResContour);
    DrawContour(ResContour,false,clBlue);
    shp_CopyContour(Contour,ResContour);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AProcessingDivideExecute(TObject *Sender)
{
	AnsiString strText = "10.0";
    if(!InputQuery("Step","Enter Step:",strText))	return;
	double dStep = StrToFloat(strText);
	shp_AutoSetContourStartPoint(Contour);
	shp_Divide_Contour(dStep,true,Contour,ResContour);
    DrawContour(ResContour,false,clBlue);
    shp_CopyContour(Contour,ResContour);
    Caption = FormatFloat("Tester [0 points]",Contour.size());
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AProcessingSameDivideExecute(TObject *Sender)
{
	AnsiString strText = "10.0";
    if(!InputQuery("Step","Enter Step:",strText))	return;
	double dStep = StrToFloat(strText);
	shp_AutoSetContourStartPoint(Contour);
	shp_Divide_Contour(dStep,false,Contour,ResContour);
    DrawContour(ResContour,false,clBlue);
    shp_CopyContour(Contour,ResContour);
    Caption = FormatFloat("Tester [0 points]",Contour.size());
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AProcessingReassempleExecute(TObject *Sender)
{
	AnsiString strText = "1.0";
    if(!InputQuery("Epsilon","Enter epsilon:",strText))	return;
	double dEpsilon = StrToFloat(strText);
	shp_AutoSetContourStartPoint(Contour);
	shp_FindBestContour(dEpsilon,Contour,ResContour);
    DrawContour(ResContour,false,clBlue);
    shp_CopyContour(Contour,ResContour);
    Caption = FormatFloat("Tester [0 points]",Contour.size());
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AProcessingExtrudeExecute(TObject *Sender)
{
	AnsiString strText = "3.0";
    if(!InputQuery("Extrusion","Enter Extrusion Step:",strText))	return;
	double dStep = StrToFloat(strText);
	shp_Extrude_Contour(dStep,true,Contour,ResContour);	
    DrawContour(ResContour,false,clBlue);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ADrawExecute(TObject *Sender)
{
//	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ADrawDrawExecute(TObject *Sender)
{
	DrawContour(Contour,false,clBlack);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ADrawDrawSmoothExecute(TObject *Sender)
{
	DrawContour(Contour,true,clBlack);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ADrawClearExecute(TObject *Sender)
{
	ClearDoc();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ADigitizerExecute(TObject *Sender)
{
//	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ADigitizerDigitizerExecute(TObject *Sender)
{
	FormDigitizer->ShowModal();
}
//---------------------------------------------------------------------------

