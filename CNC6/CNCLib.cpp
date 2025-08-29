//---------------------------------------------------------------------------
#include <vcl.h>
#include <values.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "CNCLib.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
double cnc_Ax = 1;
double cnc_Bx = 0;
double cnc_Ay = 1;
double cnc_By = 0;
//---------------------------------------------------------------------------
double cnc_Distance(cnc_Stitch &p1,cnc_Stitch &p2)
{
	return sqrt((p2.x-p1.x)*(p2.x-p1.x)+(p2.y-p1.y)*(p2.y-p1.y));
}
//---------------------------------------------------------------------------
double cnc_Distance(cnc_Point &p1,cnc_Point &p2)
{
	return sqrt((p2.x-p1.x)*(p2.x-p1.x)+(p2.y-p1.y)*(p2.y-p1.y));
}
//---------------------------------------------------------------------------
bool cnc_LoadCNCFile(AnsiString strFileName,cnc_File &File)
{
	File.clear();
	TStringList *pList = new TStringList();
	pList->LoadFromFile(strFileName);
    AnsiString strLine;
    int nPos;
    cnc_Stitch s;
    for(int i=0;i<pList->Count;i++)
    {
		strLine = pList->Strings[i];
        if(UpperCase(strLine).Pos("PU") > 0)
        {
			s.cmd = stJump;
			strLine.Delete(1,2);
			nPos = strLine.Pos(",");
            if(nPos <= 0)// Corel PLT
            {
				nPos = strLine.Pos(" ");
            }
        }
        else
        if(UpperCase(strLine).Pos("PD") > 0)
        {
			s.cmd = stNormal;
			strLine.Delete(1,2);
			nPos = strLine.Pos(",");
            if(nPos <= 0)// Corel PLT
            {
				nPos = strLine.Pos(" ");
            }
        }
        else
        {
         	continue;
        }
        s.x = StrToInt(strLine.SubString(1,nPos-1).Trim());
        strLine.Delete(1,nPos);
        strLine.Trim();
        strLine.Delete(strLine.Length(),1);
        s.y = StrToInt(strLine);
        File.push_back(s);
    }
    if(pList)
    {
     	delete pList;
        pList = NULL;
    }
    return true;
}
//---------------------------------------------------------------------------
bool cnc_SaveCNCFile(AnsiString strFileName,cnc_File &File)
{
	TStringList *pList = new TStringList();
    AnsiString strLine;
    cnc_Stitch s;
    pList->Add("IN;");
    pList->Add("SP1;");
    pList->Add("PU 0,0;");
    for(UINT i=0;i<File.size();i++)
    {
    	s = File[i];
        if(s.cmd == stJump)
        {
	        strLine = "PU "+IntToStr((int)s.x)+","+IntToStr((int)s.y)+";";
    	    pList->Add(strLine);
        }
        else
        if(s.cmd == stNormal)
        {
            strLine = "PD "+IntToStr((int)s.x)+","+IntToStr((int)s.y)+";";
        	pList->Add(strLine);
        }
    }
    pList->Add("PU 0,0;");
    pList->Add("SP0;");
    if(pList)
    {
		pList->SaveToFile(strFileName);
     	delete pList;
        pList = NULL;
    }
    return true;
}
//---------------------------------------------------------------------------
bool cnc_LoadCMDFile(AnsiString strFileName,cnc_File &File)
{
	File.clear();
	TStringList *pList = new TStringList();
	pList->LoadFromFile(strFileName);
    AnsiString strLine;
    int nPos;
    cnc_Stitch s;
    for(int i=0;i<pList->Count;i++)
    {
		strLine = pList->Strings[i];
        if(UpperCase(strLine).Pos("U") > 0)
        {
			s.cmd = stJump;
			strLine.Delete(1,1);
			nPos = strLine.Pos(",");
			s.x = StrToInt(strLine.SubString(1,nPos-1).Trim());
			strLine.Delete(1,nPos);
			nPos = strLine.Pos(",");
			s.y = StrToInt(strLine.SubString(1,nPos-1).Trim());
			strLine.Delete(1,nPos);
			nPos = strLine.Pos(",");
			s.z = StrToInt(strLine.SubString(1,nPos-1).Trim());
			strLine.Delete(1,nPos);
			nPos = strLine.Pos(",");
			s.Vx = StrToInt(strLine.SubString(1,nPos-1).Trim());
			strLine.Delete(1,nPos);
			nPos = strLine.Pos(",");
			s.Vy = StrToInt(strLine.SubString(1,nPos-1).Trim());
			strLine.Delete(1,nPos);
			nPos = strLine.Pos(",");
			s.Vz = StrToInt(strLine.SubString(1,nPos-1).Trim());
			strLine.Delete(1,nPos);
			nPos = strLine.Pos(",");
			s.Ax = StrToInt(strLine.SubString(1,nPos-1).Trim());
			strLine.Delete(1,nPos);
			nPos = strLine.Pos(",");
			s.Ay = StrToInt(strLine.SubString(1,nPos-1).Trim());
			strLine.Delete(1,nPos);
			s.Az = StrToInt(strLine.Trim());
            File.push_back(s);
        }
        else
        if(UpperCase(strLine).Pos("D") > 0)
        {
			s.cmd = stNormal;
			strLine.Delete(1,1);
			nPos = strLine.Pos(",");
			s.x = StrToInt(strLine.SubString(1,nPos-1).Trim());
			strLine.Delete(1,nPos);
			nPos = strLine.Pos(",");
			s.y = StrToInt(strLine.SubString(1,nPos-1).Trim());
			strLine.Delete(1,nPos);
			nPos = strLine.Pos(",");
			s.z = StrToInt(strLine.SubString(1,nPos-1).Trim());
			strLine.Delete(1,nPos);
			nPos = strLine.Pos(",");
			s.Vx = StrToInt(strLine.SubString(1,nPos-1).Trim());
			strLine.Delete(1,nPos);
			nPos = strLine.Pos(",");
			s.Vy = StrToInt(strLine.SubString(1,nPos-1).Trim());
			strLine.Delete(1,nPos);
			nPos = strLine.Pos(",");
			s.Vz = StrToInt(strLine.SubString(1,nPos-1).Trim());
			strLine.Delete(1,nPos);
			nPos = strLine.Pos(",");
			s.Ax = StrToInt(strLine.SubString(1,nPos-1).Trim());
			strLine.Delete(1,nPos);
			nPos = strLine.Pos(",");
			s.Ay = StrToInt(strLine.SubString(1,nPos-1).Trim());
			strLine.Delete(1,nPos);
			s.Az = StrToInt(strLine.Trim());
            File.push_back(s);
        }
        else
        if(UpperCase(strLine).Pos("T") > 0)
        {
			strLine.Delete(1,1);
			s.cmd = StrToInt(strLine.Trim());
            File.push_back(s);
        }
    }
    if(pList)
    {
     	delete pList;
        pList = NULL;
    }
    return true;
}
//---------------------------------------------------------------------------
bool cnc_SaveCMDFile(AnsiString strFileName,cnc_File &File)
{
	TStringList *pList = new TStringList();
    AnsiString strLine;
    cnc_Stitch s;
    for(UINT i=0;i<File.size();i++)
    {
    	s = File[i];
        if(s.cmd == stJump)
        {
	        strLine = "U "+IntToStr((int)s.x)+","+IntToStr((int)s.y)+","+IntToStr((int)s.z)+","+IntToStr((int)s.Vx)+","+IntToStr((int)s.Vy)+","+IntToStr((int)s.Vz)+","+IntToStr((int)s.Ax)+","+IntToStr((int)s.Ay)+","+IntToStr((int)s.Az);
    	    pList->Add(strLine);
        }
        else
        if(s.cmd == stNormal)
        {
	        strLine = "D "+IntToStr((int)s.x)+","+IntToStr((int)s.y)+","+IntToStr((int)s.z)+","+IntToStr((int)s.Vx)+","+IntToStr((int)s.Vy)+","+IntToStr((int)s.Vz)+","+IntToStr((int)s.Ax)+","+IntToStr((int)s.Ay)+","+IntToStr((int)s.Az);
        	pList->Add(strLine);
        }
        else
        if(s.cmd <= stTool_9)
        {
	        strLine = "T "+IntToStr((int)s.cmd);
        	pList->Add(strLine);
        }
    }
    if(pList)
    {
		pList->SaveToFile(strFileName);
     	delete pList;
        pList = NULL;
    }
    return true;
}
//---------------------------------------------------------------------------
cnc_Rect cnc_CalculateFrame(cnc_File &CNCFile)
{
	cnc_Rect Frame;
	Frame.left = MAXDOUBLE;
	Frame.top = MAXDOUBLE;
	Frame.right = -MAXDOUBLE;
	Frame.bottom = -MAXDOUBLE;
    cnc_Stitch CNCStitch;
	for(UINT i=0;i<CNCFile.size();i++)
    {
		CNCStitch = CNCFile[i];

        if(Frame.left > CNCStitch.x)
        	Frame.left = CNCStitch.x;
        if(Frame.right < CNCStitch.x)
        	Frame.right = CNCStitch.x;
        if(Frame.top > CNCStitch.y)
        	Frame.top = CNCStitch.y;
        if(Frame.bottom < CNCStitch.y)
        	Frame.bottom = CNCStitch.y;
    }
	return Frame;
}
//---------------------------------------------------------------------------
void cnc_InitializeCNCFile(TRect &R,bool bKeepRatio,cnc_File &CNCFile)
{
	if(CNCFile.size() < 2)	return;
    cnc_Rect Frame = cnc_CalculateFrame(CNCFile);
	TRect Rec;
    Rec = R;
    if(bKeepRatio)
    {
        double dRatio = Frame.Width() / Frame.Height();
    	if(R.Width() >= R.Height())
        {
        	if(Frame.Width() >= Frame.Height())
            	Rec.right = R.left+dRatio*R.Height();
            else
            	Rec.bottom = R.top+R.Width()/dRatio;
        }
        else
        {
        	if(Frame.Width() >= Frame.Height())
	        	Rec.bottom = R.top+R.Width()/dRatio;
            else
	        	Rec.right = R.left+dRatio*R.Height();
        }
    }
    cnc_Ax = Rec.Width()/Frame.Width();
    cnc_Bx = Rec.left - cnc_Ax * Frame.left;
    cnc_Ay = - Rec.Height()/Frame.Height();
    cnc_By = Rec.top - cnc_Ay * Frame.bottom;
}
//---------------------------------------------------------------------------
void cnc_DrawCNCFile(TCanvas *pCanvas,TRect &R,bool bKeepRatio,cnc_File &CNCFile)
{
    if(pCanvas == NULL)	return;
	if(CNCFile.size() < 2)	return;
    cnc_Stitch CNCStitch;
    CNCStitch = CNCFile[0];
    pCanvas->MoveTo(cnc_Ax*CNCStitch.x+cnc_Bx,cnc_Ay*CNCStitch.y+cnc_By);
	for(UINT i=1;i<CNCFile.size();i++)
    {
		CNCStitch = CNCFile[i];
        switch(CNCStitch.cmd)
        {
         	case stNormal:// Continous Line
            {
            	pCanvas->Pen->Color = clBlack;
				pCanvas->Pen->Style = psSolid;
                pCanvas->LineTo(cnc_Ax*CNCStitch.x+cnc_Bx,cnc_Ay*CNCStitch.y+cnc_By);
             	break;
            }
         	case stJump:// Discrete Line
            {
            	pCanvas->Pen->Color = clBlue;
            	pCanvas->Pen->Style = psDot;
                pCanvas->LineTo(cnc_Ax*CNCStitch.x+cnc_Bx,cnc_Ay*CNCStitch.y+cnc_By);
             	break;
            }
        }
    }
}
//---------------------------------------------------------------------------
TPoint cnc_InitializeSimulator(TCanvas *pCanvas,TRect &R,bool bKeepRatio,cnc_File &CNCFile)
{
	if(CNCFile.size() < 2)	return Point(0,0);
    cnc_Stitch CNCStitch;
    CNCStitch = CNCFile[0];
    TPoint P = Point(cnc_Ax*CNCStitch.x+cnc_Bx,cnc_Ay*CNCStitch.y+cnc_By);
    pCanvas->MoveTo(P.x,P.y);
    return P;
}
//---------------------------------------------------------------------------
TPoint cnc_DrawStitch(TCanvas *pCanvas,cnc_Stitch &CNCStitch)
{
	TPoint P = Point(cnc_Ax*CNCStitch.x+cnc_Bx,cnc_Ay*CNCStitch.y+cnc_By); 
    switch(CNCStitch.cmd)
    {
        case stNormal:// Continous Line
        {
            pCanvas->Pen->Color = clBlack;
            pCanvas->Pen->Style = psSolid;
            pCanvas->LineTo(P.x,P.y);
            break;
        }
        case stJump:// Discrete Line
        {
            pCanvas->Pen->Color = clBlue;
            pCanvas->Pen->Style = psDot;
            pCanvas->LineTo(P.x,P.y);
            break;
        }
    }
    return P;
}
//---------------------------------------------------------------------------

