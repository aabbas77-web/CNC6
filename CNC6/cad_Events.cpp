//---------------------------------------------------------------------------
#include <vcl.h>
#include <Math.h>
#include <Math.hpp>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "cad_Events.h"
#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
double g_dDividingStep = 200.0;
//---------------------------------------------------------------------------
bool g_bGenerateNamesList = true;
//---------------------------------------------------------------------------
AnsiString g_strFMask = "0.0";// "mm.dm"
//---------------------------------------------------------------------------
int g_nCurrToolIndex = 0;
//---------------------------------------------------------------------------
double g_dCurrDepth = 0.0;
//---------------------------------------------------------------------------
VHANDLE g_hMachineHeadIndex = -1;
//---------------------------------------------------------------------------
double g_dZStep = 1.0;
//---------------------------------------------------------------------------
double g_dSpeed = 10.0;// cm/s
//---------------------------------------------------------------------------
cnc_Tool g_pTools[10];
int g_pDefaultToolsColors[10] = {clWhite,clMaroon,clOlive,clNavy,clPurple,clTeal,clLime,clYellow,clFuchsia,clAqua};
//---------------------------------------------------------------------------
//--------------------Extract Segments---------------------------------------
//---------------------------------------------------------------------------
void cad_ExtractSegments(int nEntity,int nPath,int &nVertex,cad_Contour &Contour)
{
	int nPathSize;
	double x,y;
    shp_Point P;

    Contour.Points.clear();
    nPathSize = CadEntityGetPathSize(nEntity,nPath);
    for(int j=0;j<nPathSize;j++)
    {
        CadEntityGetVer(nEntity,nVertex++,&x,&y);
        P.x = x;
        P.y = y;
        Contour.Points.push_back(P);
    }

    double dEpsilon = g_dDividingStep/100.0;
    cad_Contour ResContour;
	shp_FindBestContour(dEpsilon,Contour.Points,ResContour.Points);
    shp_Divide_Contour(g_dDividingStep,true,ResContour.Points,Contour.Points);
}
//---------------------------------------------------------------------------
void cad_ExtractSegments(int nEntity,cad_Shape &Shape)
{
	int nLayer,nPaths;
	int nVertex;
    cad_Contour Contour;
    cad_Entity CadEntity;

    CadEntityGetExData(nEntity,&CadEntity);
    Shape.cadEntity.nToolIndex = CadEntity.nToolIndex;
    Shape.cadEntity.dDepth = CadEntity.dDepth;

    Shape.Contours.clear();
    nVertex = 0;
    nPaths = CadEntityGetNumPaths(nEntity);
    for(int i=0;i<nPaths;i++)
    {
        cad_ExtractSegments(nEntity,i,nVertex,Contour);
        Shape.Contours.push_back(Contour);
    }
}
//---------------------------------------------------------------------------
void cad_ExtractSegments(int nLayer,cad_Layer &Layer)
{
	int nEntity;
    cad_Shape Shape;

    Layer.Shapes.clear();
    nEntity = CadLayerGetFirstEntity(nLayer);
    while(nEntity)
    {
    	cad_ExtractSegments(nEntity,Shape);
        Layer.Shapes.push_back(Shape);

        nEntity = CadLayerGetNextEntity(nLayer,nEntity);
    }
}
//---------------------------------------------------------------------------
void cad_ExtractSegments(VDWG hDwg,cad_Drawing &Drawing)
{
	int nLayer;
	cad_Layer Layer;

    Drawing.Layers.clear();
	nLayer = CadGetFirstLayer(hDwg);
	while(nLayer)
    {
    	cad_ExtractSegments(nLayer,Layer);
        Drawing.Layers.push_back(Layer);

  		nLayer = CadGetNextLayer(hDwg,nLayer);
	}
}
//---------------------------------------------------------------------------
//--------------------Draw Segments------------------------------------------
//---------------------------------------------------------------------------
void cad_DrawSegments(VDWG hDwg,cad_Contour &Contour)
{
	int nLayer,nEntity;
    shp_Point P,OP;
    bool bFirst;
	bFirst = true;
    for(UINT i=0;i<Contour.Points.size();i++)
	{
    	P = Contour.Points[i];
        if(bFirst)
        	bFirst = false;
        else
        {
        	nEntity = CadAddLine(hDwg,OP.x,OP.y,0,P.x,P.y,0);
            EntCreateProc(hDwg,nEntity);
        }
        OP = P;
    }
}
//---------------------------------------------------------------------------
void cad_DrawSegments(VDWG hDwg,cad_Shape &Shape)
{
	g_nCurrToolIndex = Shape.cadEntity.nToolIndex;
    g_dCurrDepth = Shape.cadEntity.dDepth;
    for(UINT i=0;i<Shape.Contours.size();i++)
	{
    	cad_DrawSegments(hDwg,Shape.Contours[i]);
    }
}
//---------------------------------------------------------------------------
void cad_DrawSegments(VDWG hDwg,cad_Layer &Layer)
{
    for(UINT i=0;i<Layer.Shapes.size();i++)
	{
    	cad_DrawSegments(hDwg,Layer.Shapes[i]);
    }
}
//---------------------------------------------------------------------------
void cad_DrawSegments(VDWG hDwg,cad_Drawing &Drawing)
{
    for(UINT i=0;i<Drawing.Layers.size();i++)
	{
    	cad_DrawSegments(hDwg,Drawing.Layers[i]);
    }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
bool cnc_Load_PLT(AnsiString strFileName,cad_Drawing &Drawing)
{
	Drawing.Layers.clear();
	TStringList *pList = new TStringList();
	pList->LoadFromFile(strFileName);
    AnsiString strLine;
    int nPos;
    shp_Point P;
    cad_Contour Contour;
    cad_Shape Shape;
    cad_Layer Layer;
    for(int i=0;i<pList->Count;i++)
    {
		strLine = pList->Strings[i];
        if(UpperCase(strLine).Pos("PU") > 0)
        {
    		if(!Contour.Points.empty())
            {
	        	Shape.Contours.push_back(Contour);
    	    	Contour.Points.clear();
            }

			strLine.Delete(1,2);
			nPos = strLine.Pos(",");
            if(nPos <= 0)// Corel PLT
            {
				nPos = strLine.Pos(" ");
            }

            P.x = StrToInt(strLine.SubString(1,nPos-1).Trim());
            strLine.Delete(1,nPos);
            strLine.Trim();
            strLine.Delete(strLine.Length(),1);
            P.y = StrToInt(strLine);
            Contour.Points.push_back(P);
        }
        else
        if(UpperCase(strLine).Pos("PD") > 0)
        {
			strLine.Delete(1,2);
			nPos = strLine.Pos(",");
            if(nPos <= 0)// Corel PLT
            {
				nPos = strLine.Pos(" ");
            }

            P.x = StrToInt(strLine.SubString(1,nPos-1).Trim());
            strLine.Delete(1,nPos);
            strLine.Trim();
            strLine.Delete(strLine.Length(),1);
            P.y = StrToInt(strLine);
            Contour.Points.push_back(P);
        }
        else
        if(UpperCase(strLine).Pos("SP") > 0)
        {
    		if(!Contour.Points.empty())
            {
	        	Shape.Contours.push_back(Contour);
    	    	Contour.Points.clear();
            }

        	if(!Shape.Contours.empty())
            {
    			Layer.Shapes.push_back(Shape);
                Shape.Contours.clear();
            }

			strLine.Delete(1,2);
			nPos = strLine.Pos(";");
            if(nPos >= 0)
            {
        		Shape.cadEntity.nToolIndex = StrToInt(strLine.SubString(1,nPos-1).Trim());
            }
        }
        else
        {
         	continue;
        }
    }

    if(!Contour.Points.empty())
    {
        Shape.Contours.push_back(Contour);
        Contour.Points.clear();
    }
    if(!Shape.Contours.empty())
    {
        Layer.Shapes.push_back(Shape);
        Shape.Contours.clear();
    }
    Drawing.Layers.push_back(Layer);
    if(pList)
    {
     	delete pList;
        pList = NULL;
    }
    return true;
}
//---------------------------------------------------------------------------
bool cnc_Save_PLT(AnsiString strFileName,cad_Drawing &Drawing)
{
	TStringList *pList = new TStringList();
    AnsiString strLine;
    shp_Point P;
    cad_Contour Contour;
    cad_Shape Shape;
    cad_Layer Layer;
    bool bFirst;

    pList->Add("IN;");
    pList->Add("PU 0,0;");
    
    for(UINT i=0;i<Drawing.Layers.size();i++)
    {
    	Layer = Drawing.Layers[i];
    	for(UINT j=0;j<Layer.Shapes.size();j++)
        {
        	Shape = Layer.Shapes[j];
    		pList->Add(FormatFloat("SP0",Shape.cadEntity.nToolIndex)+";");// Select pen

            // if(Shape.cadEntity.dDepth <= 0.0)	Shape.cadEntity.dDepth = g_dZStep;
            // int nZCount = Shape.cadEntity.dDepth / g_dZStep;

         	for(UINT k=0;k<Shape.Contours.size();k++)
            {
            	Contour = Shape.Contours[k];
                bFirst = true;
                for(UINT m=0;m<Contour.Points.size();m++)
                {
                 	P = Contour.Points[m];
			        if(bFirst)
                    {
        				bFirst = false;
				        strLine = "PU "+IntToStr((int)P.x)+","+IntToStr((int)P.y)+";";
    	    			pList->Add(strLine);
                    }
			        else
                    {
			            strLine = "PD "+IntToStr((int)P.x)+","+IntToStr((int)P.y)+";";
        				pList->Add(strLine);
                    }
                }
            }
            
        }
    }
    
    pList->Add("PU 0,0;");
    if(pList)
    {
		pList->SaveToFile(strFileName);
     	delete pList;
        pList = NULL;
    }
    return true;
}
//---------------------------------------------------------------------------

bool cad_Export_PLT(VDWG hDwg,AnsiString strFileName)
{
    cad_Drawing Drawing;
	cad_ExtractSegments(hDwg,Drawing);
    return cnc_Save_PLT(strFileName,Drawing);
}
//---------------------------------------------------------------------------

bool cad_Import_PLT(VDWG hDwg,AnsiString strFileName)
{
	cad_Drawing Drawing;
    if(!cnc_Load_PLT(strFileName,Drawing))	return false;
	cad_DrawSegments(hDwg,Drawing);
    CadUpdate(hDwg);
    return true;
}
//---------------------------------------------------------------------------
//-------------------Custom Commands-----------------------------------------
//---------------------------------------------------------------------------
void _stdcall Func_SQUARE(VDWG hDwg)
{
	char szText[256];
  	int status;
  	double x1,y1,z1;
  	double x2,y2,z2;

m1:
  	CadCmdPrompt(hDwg,"Input first corner:",""); 
  	status = CadCmdUserInput(hDwg);
  	switch(status)
    {
    	case CAD_CCS_LBUTTON:
        {
            // user have clicked left mouse button inside of VeCAD Window
            CadCmdGetInputPoint(hDwg,&x1,&y1,&z1);
            // save the entered point in a command buffer, in order to read it in the "Drag" function
            CadCmdAddPoint(hDwg,x1,y1,z1);
            // set this point as a base for relative coordinates, which can be
            // entered in a command line for the second point (for example: @10,20)
            CadCmdSetBasePoint(hDwg,x1,y1,z1);
            break;
        }
    	case CAD_CCS_STRING:
        {
            // user have input coordinates value in a command line
            CadCmdGetInputStr(hDwg,szText);
            // convert the string into point coordinates
            if(CadCmdStrToPoint(hDwg,szText,&x1,&y1,&z1))
            {
                // save the entered point in a command buffer, in order to read it in the "Drag" function
                CadCmdAddPoint(hDwg,x1,y1,z1);
                // set this point as a base for relative coordinates, which can be
                // entered in a command line for the second point (for example: @10,20)
                CadCmdSetBasePoint(hDwg,x1,y1,z1);
            }
            else
            {
                // invalid point
                CadCmdPrompt(hDwg,"Invalid point","");
                // repeat the input
                goto m1;
            }
            break;
        }
    	case CAD_CCS_RBUTTON:   // user have clicked right mouse button
    	case CAD_CCS_ESCAPE:    // user have pressed <Esc> kay
    	default:
        {
      		// finish the command
      		return;
        }
  	}

m2:
  	CadCmdPrompt(hDwg,"Input second corner:",""); 
  	status = CadCmdUserInput(hDwg);
  	switch(status)
    {
    	case CAD_CCS_LBUTTON:
        {
            // user have clicked left mouse button inside of VeCAD Window
            CadCmdGetInputPoint(hDwg,&x2,&y2,&z2);
            // save the entered point in a command buffer, in order to read it in the "Drag" function
            CadCmdAddPoint(hDwg,x2,y2,z2);
            // set this point as a base for relative coordinates, which can be
            // entered in a command line for the second point (for example: @10,20)
            CadCmdSetBasePoint(hDwg,x2,y2,z2);
      		break;
        }
    	case CAD_CCS_STRING:
        {
            // user have input coordinates value in a command line
            CadCmdGetInputStr(hDwg,szText);
            // convert the string into point coordinates
            if(CadCmdStrToPoint(hDwg,szText,&x2,&y2,&z2))
            {
                // save the entered point in a command buffer, in order to read it in the "Drag" function
                CadCmdAddPoint(hDwg,x2,y2,z2);
                // set this point as a base for relative coordinates, which can be
                // entered in a command line for the second point (for example: @10,20)
                CadCmdSetBasePoint(hDwg,x2,y2,z2);
            }
            else
            {
                // invalid point
                CadCmdPrompt(hDwg,"Invalid point","");
                // repeat the input
                goto m2;
            }
      		break;
        }
    	case CAD_CCS_RBUTTON:
    	case CAD_CCS_ESCAPE:
    	default:
        {
      		// finish the command
      		return;
        }
  	}

  	// create a polyline entity
	cad_Square data;
    double dW;
    dW = sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));

	data.x = x1;
	data.y = y1;
	data.z = z1;
	data.Size = 2*dW;
    data.RotAngle = vuGetAngle(x1,y1,z1,x2,y2,z2,CAD_PLANE_XY);
	cad_AddSquare(hDwg,data);

  	CadUpdate(hDwg);
  	CadWndRedraw(CadGetWindow(hDwg));
    cad_ShowText(1,"");
}
//---------------------------------------------------------------------------
void _stdcall Drag_SQUARE(VDWG hDwg,int nPoints,double x,double y,double z)
{
  	static double x1,y1,z1;
    double dW;
	cad_Square data;
    switch(nPoints)
    {
  		case 1:
        {
            // one point is already entered, get it from a command buffer
            CadCmdGetPoint(hDwg,0,&x1,&y1,&z1);

            // draw temporary rectangle
            dW = sqrt((x-x1)*(x-x1)+(y-y1)*(y-y1));

            data.x = x1;
            data.y = y1;
            data.z = z1;
            data.Size = 2*dW;
    		data.RotAngle = vuGetAngle(x1,y1,z1,x,y,z,CAD_PLANE_XY);
            cad_DrawSquare(data,false);

            CadDrawLine(x1,y1,z1,x,y,z);
            cad_ShowText(1,"Width: "+FormatFloat(g_strFMask,data.Size)+" , Rotation: "+FormatFloat(g_strFMask,RadToDeg(data.RotAngle)));
            break;
        }
    }
}
//---------------------------------------------------------------------------
//-------------------Utility-------------------------------------------------
//---------------------------------------------------------------------------
void cad_ShowText(int nIndex,AnsiString strText)
{
	if((nIndex < 0) || (nIndex >= FormMain->StatusBar->Panels->Count))	return;
	FormMain->StatusBar->Panels->Items[nIndex]->Text = strText;
}
//---------------------------------------------------------------------------
AnsiString GetEntityName(int nEntity)
{
	int nEntityType,nEntityID;
    AnsiString strEntityName;

    nEntityType = CadEntityGetType(nEntity);
    nEntityID = CadEntityGetID(nEntity);
    strEntityName = FormatFloat("Unknown0",nEntityID);
    switch(nEntityType)
    {
        case CAD_ENT_POINT:
        {
            strEntityName = FormatFloat("Point0",nEntityID);
            break;
        }
        case CAD_ENT_LINE:
        {
            strEntityName = FormatFloat("Line0",nEntityID);
            break;
        }
        case CAD_ENT_POLYLINE:
        {
            strEntityName = FormatFloat("Polyline0",nEntityID);
            int FitType = CadPlineGetFit(nEntity);
            switch(FitType)
            {
             	case CAD_PLINE_LINEAR:
                {
            		strEntityName = FormatFloat("Polyline0",nEntityID);
                 	break;
                }
             	case CAD_PLINE_QUAD:
                {
            		strEntityName = FormatFloat("QB-Spline0",nEntityID);
                 	break;
                }
             	case CAD_PLINE_CUBIC:
                {
            		strEntityName = FormatFloat("CB-Spline0",nEntityID);
                 	break;
                }
             	case CAD_PLINE_BEZIER:
                {
            		strEntityName = FormatFloat("Bezier0",nEntityID);
                 	break;
                }
             	case CAD_PLINE_SPLINE:
                {
            		strEntityName = FormatFloat("Spline0",nEntityID);
                 	break;
                }
             	case CAD_PLINE_ROUND:
                {
            		strEntityName = FormatFloat("R-Polyline0",nEntityID);
                 	break;
                }
             	case CAD_PLINE_LINQUAD:
                {
            		strEntityName = FormatFloat("Q-Polyline0",nEntityID);
                 	break;
                }
            }
            break;
        }
        case CAD_ENT_RECT:
        {
            strEntityName = FormatFloat("Rect0",nEntityID);
            break;
        }
        case CAD_ENT_MLINE:
        {
            strEntityName = FormatFloat("MLine0",nEntityID);
            break;
        }
        case CAD_ENT_ARC:
        {
            strEntityName = FormatFloat("Arc0",nEntityID);
            int et = CadArcGetType(nEntity);
            switch(et)
            {
                case CAD_ARC:
                {
            		strEntityName = FormatFloat("Arc0",nEntityID);
                    break;
                }
                case CAD_CIRCLE:
                {
            		strEntityName = FormatFloat("Circle0",nEntityID);
                    break;
                }
                case CAD_ELLIPSE:
                {
            		strEntityName = FormatFloat("Ellipse0",nEntityID);
                    break;
                }
            }
            break;
        }
        case CAD_ENT_TEXT:
        {
            strEntityName = FormatFloat("Text0",nEntityID);
            break;
        }
        case CAD_ENT_INSBLOCK:
        {
            strEntityName = FormatFloat("Block0",nEntityID);
            break;
        }
        case CAD_ENT_IMAGE:
        {
            strEntityName = FormatFloat("Bitmap0",nEntityID);
            break;
        }
        case CAD_ENT_HATCH:
        {
            strEntityName = FormatFloat("Hatch0",nEntityID);
            break;
        }
        case CAD_ENT_DIM:
        {
            strEntityName = FormatFloat("Dim0",nEntityID);
            break;
        }
        case CAD_ENT_LEADER:
        {
            strEntityName = FormatFloat("Leader0",nEntityID);
            break;
        }
        case CAD_ENT_ATTRIB:
        {
            strEntityName = FormatFloat("Attrib0",nEntityID);
            break;
        }
        case CAD_ENT_CUSTOM:
        {
            strEntityName = FormatFloat("Custom0",nEntityID);
            int et = CadCustomGetType(nEntity);
            switch(et)
            {
                case CAD_TYPE_SQUARE:
                {
            		strEntityName = FormatFloat("Square0",nEntityID);
                    break;
                }
            }
            break;
        }
    }
    return strEntityName;
}
//---------------------------------------------------------------------------
//--------------------Events-------------------------------------------------
//---------------------------------------------------------------------------
void CALLBACK EntCreateProc(VDWG hDwg,VHANDLE hEnt)
{
	if(g_bGenerateNamesList)
    {
	    AnsiString strEntityName;
		strEntityName = GetEntityName(hEnt);
	    FormMain->ListBoxEntities->Items->AddObject(strEntityName,(TObject *)hEnt);

        cad_Entity cadEntity;
        cadEntity.nToolIndex = g_nCurrToolIndex;
        cadEntity.dDepth = g_dCurrDepth;
        CadEntityPutExData(hEnt,&cadEntity,sizeof(cadEntity));

		CadEntityPutColor(hEnt,g_nCurrToolIndex);
    	CadUpdate(hDwg);
    }
}
//---------------------------------------------------------------------------
void CALLBACK EntSelectProc(VDWG hDwg,VHANDLE hEnt,BOOL bSelect,BOOL bFinal)
{
	if(hEnt == NULL)	return;
    if(bSelect)
    {
        int nIndex;
        nIndex = FormMain->ListBoxEntities->Items->IndexOfObject((TObject *)hEnt);
        if(nIndex >= 0)
        {
            FormMain->ListBoxEntities->ItemIndex = nIndex;
            FormMain->ActivateEntity(hEnt);
        }
    }
    else
    {
    	FormMain->ListBoxEntities->ItemIndex = -1;
        FormMain->ActivateEntity(-1);
    }
}
//---------------------------------------------------------------------------
void CALLBACK EntEraseProc(VDWG hDwg,VHANDLE hEnt)
{
	if(hEnt == g_hMachineHeadIndex)
    {
     	CadSetReturnInt(true);
        return;
    }

    int nIndex;
    nIndex = FormMain->ListBoxEntities->Items->IndexOfObject((TObject *)hEnt);
    if(nIndex >= 0)
    {
    	FormMain->ListBoxEntities->Items->Delete(nIndex);
    }
}
//---------------------------------------------------------------------------
void CALLBACK MouseMoveProc(VDWG hDwg,int Button,int Key,int Xwin,
							int Ywin,double Xdwg,double Ydwg,double Zdwg)
{
	cad_ShowText(0,FormatFloat(g_strFMask,Xdwg)+" , "+FormatFloat(g_strFMask,Ydwg));
}
//---------------------------------------------------------------------------
void CALLBACK MouseDownProc(VDWG hDwg,int Button,int Key,int Xwin,
							int Ywin,double Xdwg,double Ydwg,double Zdwg)
{
	if(Button == CAD_RBUTTON)
    {
	    // CadSetReturnInt(true);
    }
}
//---------------------------------------------------------------------------
void CALLBACK FontReplaceProc(VDWG hDwg,LPCTSTR szFont,int bBigFont)
{
	CadSetReturnStr(szFont);
}
//---------------------------------------------------------------------------
void CALLBACK SelCodepageProc(VDWG hDwg)
{
	CadSetReturnInt(CAD_CP_1256);// Arabic Code Page
}
//---------------------------------------------------------------------------
void CALLBACK ExecuteProc(VDWG hDwg,int Command)
{
	switch(Command)
    {
     	case CAD_CMD_UNDO:
     	case CAD_CMD_REDO:
        {
        	//FormMain->BuildEntitiesList();
         	break;
        }
    }
}
//---------------------------------------------------------------------------
void CALLBACK CmdStartProc(VDWG hDwg,int Command,int nSteps)
{

}
//---------------------------------------------------------------------------
void CALLBACK CmdLBDownProc(VDWG hDwg,int Command,int Step,double* pX,double* pY,double* pZ)
{

}
//---------------------------------------------------------------------------
void CALLBACK CmdFinishProc(VDWG hDwg,int Command)
{

}
//---------------------------------------------------------------------------
void CALLBACK RegenProc(VDWG hDwg,int Step,int Percent,int NumEnt)
{
	switch(Step)
    {
		case 0:// start of the regeneration
        {
         	break;
        }
		case 1:// regeneration is underway
        {
         	break;
        }
		case 2:// end of the regeneration
        {
         	break;
        }
    }
}
//---------------------------------------------------------------------------
//--------------------Custom Entities----------------------------------------
//---------------------------------------------------------------------------
void CALLBACK EventCEntGetName(VDWG hDwg,VHANDLE hEnt)
{
  	int et = CadCustomGetType(hEnt);
  	switch(et)
    {
    	case CAD_TYPE_SQUARE:
        {
         	CadSetReturnStr("Sqaure");
            break;
        }
  	}
}
//---------------------------------------------------------------------------
void CALLBACK EventCEntGetProps(VDWG hDwg,VHANDLE hEnt)
{
  	cad_Square data;
  	TCHAR szBuf[256];
  	int et = CadCustomGetType(hEnt);
  	switch(et)
    {
    	case CAD_TYPE_SQUARE:
        {
      		CadCustomGetData(hEnt,&data);
            CadAddCustProp(0,"Geometry","",CAD_PROP_SEPARATOR);
            vuNumToStr(data.x,szBuf,5,true,true);
            CadAddCustProp(1,"Center X",szBuf,CAD_PROP_VALUE);
            vuNumToStr(data.y,szBuf,5,true,true);
            CadAddCustProp(2,"Center Y",szBuf,CAD_PROP_VALUE);
            vuNumToStr(data.z,szBuf,5,true,true);
            CadAddCustProp(3,"Center Z",szBuf,CAD_PROP_VALUE);
            vuNumToStr(data.Size,szBuf,5,true,true);
            CadAddCustProp(4,"Size",szBuf,CAD_PROP_VALUE);
            vuNumToStr(data.RotAngle*57.295779513,szBuf,3,true,true);
            CadAddCustProp(5,"Rotation",szBuf,CAD_PROP_VALUE);
            if(CadEntityGetFilled(hEnt))
            {
              CadAddCustProp(6,"Filled","1",CAD_PROP_YESNO);
            }
            else
            {
              CadAddCustProp(6,"Filled","0",CAD_PROP_YESNO);
            }
            break;
  		}
    }
}
//---------------------------------------------------------------------------
void CALLBACK EventCEntPutProp(VDWG hDwg,VHANDLE hEnt,int PropId,LPCTSTR szValue)
{
  	cad_Square data;
  	TCHAR szBuf[256];
  	int et = CadCustomGetType(hEnt);
  	switch(et)
    {
    	case CAD_TYPE_SQUARE:
        {
      		CadCustomGetData(hEnt,&data);
      		switch(PropId)
            {
        		case 1:
                {
          			data.x = _tcstod(szValue,NULL);
          			vuNumToStr(data.x,szBuf,5,true,true);
          			CadSetCustProp(PropId,szBuf);
          			break;
                }
        		case 2:
                {
          			data.y = _tcstod(szValue,NULL);
          			vuNumToStr(data.y,szBuf,5,true,true);
          			CadSetCustProp(PropId,szBuf);
          			break;
                }
        		case 3:
                {
          			data.z = _tcstod(szValue,NULL);
          			vuNumToStr(data.z,szBuf,5,true,true);
          			CadSetCustProp(PropId,szBuf);
          			break;
                }
        		case 4:
                {
          			data.Size = _tcstod(szValue,NULL);
          			vuNumToStr(data.Size,szBuf,5,true,true);
          			CadSetCustProp(PropId,szBuf);
          			break;
                }
        		case 5:
                {
          			data.RotAngle = _tcstod(szValue,NULL)/57.295779513;
          			vuNumToStr(data.RotAngle*57.295779513,szBuf,3,true,true);
          			CadSetCustProp(PropId,szBuf);
          			break;
                }
        		case 6:
                {
          			if(strcmp(szValue,"0") == 0)
                    {
            			CadEntityPutFilled(hEnt,false);
          			}
                    else
                    {
            			CadEntityPutFilled(hEnt,true);
          			}
          			CadSetCustProp(PropId,szValue);
          			break;
                }
            }
      		CadCustomPutData(hEnt,&data,sizeof(cad_Square));
      		break;
        }
  	}
}
//---------------------------------------------------------------------------
void CALLBACK EventCEntGetExts(VDWG hDwg,VHANDLE hEnt,double* pXmin,double* pYmin,double* pZmin,double* pXmax,double* pYmax,double* pZmax)
{
  	cad_Square data;
  	int et = CadCustomGetType(hEnt);
  	switch(et)
    {
    	case CAD_TYPE_SQUARE:
        {
      		CadCustomGetData(hEnt,&data);
      		*pXmin = *pXmax = data.x;
      		*pYmin = *pYmax = data.y;
      		*pZmin = *pZmax = data.z;
      		break;
        }
  	}
}
//---------------------------------------------------------------------------
void CALLBACK EventCEntNumGrips(VDWG hDwg,VHANDLE hEnt,int* pN)
{
  	int et = CadCustomGetType(hEnt);
  	switch(et)
    {
    	case CAD_TYPE_SQUARE:
        {
         	*pN = 3;
            break;
        }
  	}
}
//---------------------------------------------------------------------------
void CALLBACK EventCEntGetGrip(VDWG hDwg,VHANDLE hEnt,UINT iGrip,double* pX,double* pY,double* pZ)
{
  	cad_Square data;
  	int Plane = CAD_PLANE_XY;  // Current projection planes
  	int et = CadCustomGetType(hEnt);
  	switch(et)
    {
    	case CAD_TYPE_SQUARE:
        {
      		CadCustomGetData(hEnt,&data);
      		*pX = data.x;
      		*pY = data.y;
            *pZ = data.z;
      		switch(iGrip)
            {
        		case 0:  // center grip
                {
          			break;
                }
        		case 1:  // rotation grip
                {
          			vuPolarPoint(pX,pY,pZ,data.RotAngle,data.Size/4.0,Plane);
          			break;
                }
        		case 2:  // Size grip
                {
          			vuPolarPoint(pX,pY,pZ,data.RotAngle,data.Size/2.0,Plane);
          			break;
                }
            }
      		break;
      	}
  	}
}
//---------------------------------------------------------------------------
void CALLBACK EventCEntMoveGrip(VDWG hDwg,VHANDLE hEnt,UINT iGrip,double dx,double dy,double dz)
{
  	cad_Square data;
  	int Plane = CAD_PLANE_XY;  // Current projection plane
  	int et = CadCustomGetType(hEnt);
  	double x,y,z,d0,d1,scale;
  	switch(et)
    {
    	case CAD_TYPE_SQUARE:
        {
      		CadCustomGetData(hEnt,&data);
      		switch(iGrip)
            {
        		case 0:  // move entity
                {
          			data.x += dx;
          			data.y += dy;
          			data.z += dz;
          			break;
                }
        		case 1:  // rotate
                {
          			EventCEntGetGrip(hDwg,hEnt,iGrip,&x,&y,&z);
          			x += dx;
          			y += dy;
          			z += dz;
          			data.RotAngle = vuGetAngle(data.x,data.y,data.z,x,y,z,Plane);
          			break;
                }
        		case 2:  //change Size
                {
          			EventCEntGetGrip(hDwg,hEnt,iGrip,&x,&y,&z);
          			x += dx;
          			y += dy;
          			z += dz;
          			data.Size = vuGetDist(data.x,data.y,data.z,x,y,z,Plane)*2.0;
          			break;
                }
            }
      		CadCustomPutData(hEnt,&data,sizeof(cad_Square));
	      	break;
      	}
  	}
}
//---------------------------------------------------------------------------
void CALLBACK EventCEntMove(VDWG hDwg,VHANDLE hEnt,double dx,double dy,double dz)
{
  	cad_Square data;
  	int et = CadCustomGetType(hEnt);
  	switch(et)
    {
    	case CAD_TYPE_SQUARE:
        {
      		CadCustomGetData(hEnt,&data);
      		data.x += dx;
      		data.y += dy;
      		data.z += dz;
      		CadCustomPutData(hEnt,&data,sizeof(cad_Square));
      		break;
        }
  	}
}
//---------------------------------------------------------------------------
void CALLBACK EventCEntRotate(VDWG hDwg,VHANDLE hEnt,double x0,double y0,double z0,double Angle,int Plane)
{
  	cad_Square data;
  	int et = CadCustomGetType(hEnt);
  	switch(et)
    {
    	case CAD_TYPE_SQUARE:
        { 
      		CadCustomGetData(hEnt,&data);
      		vuRotatePoint(&data.x,&data.y,&data.z,x0,y0,z0,Angle,Plane);
      		data.RotAngle += Angle;
      		CadCustomPutData(hEnt,&data,sizeof(cad_Square));
      		break;
        }
  	}
}
//---------------------------------------------------------------------------
void CALLBACK EventCEntScale(VDWG hDwg,VHANDLE hEnt,double x0,double y0,double z0,double ScaleX,double ScaleY,double ScaleZ)
{
  	cad_Square data;
  	int et = CadCustomGetType(hEnt);
  	switch(et)
    {
    	case CAD_TYPE_SQUARE:
        {
      		CadCustomGetData(hEnt,&data);
      		vuScalePoint(&data.x,&data.y,&data.z,x0,y0,z0,ScaleX,ScaleY,ScaleZ);
      		data.Size *= ScaleX;
      		CadCustomPutData(hEnt,&data,sizeof(cad_Square));
      		break;
        }
  	}
}
//---------------------------------------------------------------------------
void CALLBACK EventCEntMirror(VDWG hDwg,VHANDLE hEnt,double A1,double B1,int Plane)
{
  	cad_Square data;
  	double x,y,z;
  	int et = CadCustomGetType(hEnt);
  	switch(et)
    {
    	case CAD_TYPE_SQUARE:
        {
      		CadCustomGetData(hEnt,&data);
      		EventCEntGetGrip(hDwg,hEnt,1,&x,&y,&z);
      		vuMirrorPoint(&x,&y,&z,A1,B1,Plane);
      		vuMirrorPoint(&data.x,&data.y,&data.z,A1,B1,Plane);
      		data.RotAngle = vuGetAngle(data.x,data.y,data.z,x,y,z,Plane);
      		CadCustomPutData(hEnt,&data,sizeof(cad_Square));
      		break;
        }
  	}
}
//---------------------------------------------------------------------------
void cad_DrawSquare(const cad_Square& data,bool bFill)
{
  	double x[5],y[5],z=0.0;
  	int i;

  	x[0] = x[4] = x[3] = data.x - data.Size / 2.0;
  	y[0] = y[4] = y[1] = data.y - data.Size / 2.0;
  	x[1] = x[2] = x[0] + data.Size;
  	y[2] = y[3] = y[0] + data.Size;
  	for(i=0;i<5;i++)
    {
    	vuRotatePoint(x+i,y+i,&z,data.x,data.y,data.z,data.RotAngle,CAD_PLANE_XY);
    	CadDrawAddVertex(x[i],y[i],data.z);
  	}
  	if(bFill)
    {
    	CadDrawPolygon();
  	}
    else
    {
    	CadDrawPolyline();
  	}
}
//---------------------------------------------------------------------------
void cad_AddSquare(VDWG hDwg,cad_Square& data)
{
	int nEntity;
	nEntity = CadAddCustom(hDwg,CAD_TYPE_SQUARE,&data,sizeof(data));
    EntCreateProc(hDwg,nEntity);
    CadPutDirty(hDwg,true);
}
//---------------------------------------------------------------------------
void cad_AddSquare(VDWG hDwg,double x,double y,double z,double Size,double RotAngle)
{
    cad_Square data;
    data.x = x;
    data.y = y;
    data.z = z;
    data.Size = Size;
    data.RotAngle = RotAngle;
    cad_AddSquare(hDwg,data);
}
//---------------------------------------------------------------------------
int cad_AddSpiral(VDWG hDwg,cad_Spiral &data)
{
	if(data.dStep <= 0.0)	return -1;
    // Draw
    double r;
    double x,y;
    double t=0.0;
    int n = data.dTours*360.0/data.dStep;
    CadClearVertices();
    for(int i=0;i<=n+1;i++)
    {
    	r = data.a*t*t/1000000.0+data.v*t/1000.0+data.r0;
		x = data.x+r*cos(DegToRad(t));
		y = data.y+r*sin(DegToRad(t));
    	CadAddVertex(x,y,data.z);
        if(i < 1)
	        t += 0.1;
        else
        if(i < n)
	        t += data.dStep;
        else
	        t += 0.1;
    }
	int nEntity;
    if(data.bLines)
	    nEntity = CadAddPolyline(hDwg,CAD_PLINE_LINEAR,false);
    else
	    nEntity = CadAddPolyline(hDwg,CAD_PLINE_SPLINE,false);
    EntCreateProc(hDwg,nEntity);
    CadPutDirty(hDwg,true);
    return nEntity;
}
//---------------------------------------------------------------------------
/*
int cad_AddSpiral(VDWG hDwg,double x0,double y0,double a,double v,double r0,double dTours,double dStep,bool bLines)
{
	if(dStep <= 0.0)	return -1;
    // Draw
    double r;
    double x,y;
    double t=0.0;
    int n = dTours*360.0/dStep;
    vlPolylineBegin();
    for(int i=0;i<=n+1;i++)
    {
    	r = a*t*t+v*t+r0;
		x = x0+r*cos(DegToRad(t));
		y = y0+r*sin(DegToRad(t));
        vlVertex(x,y);
        if(i < 1)
	        t += 1.0;
        else
        if(i < n)
	        t += dStep;
        else
	        t += 1.0;
    }
    if(bLines)
	    return vlAddPolyline(VL_POLY_LINE,false);
    else
	    return vlAddPolyline(VL_POLY_FITBSPL3,false);
}
*/
//---------------------------------------------------------------------------
void CALLBACK EventCEntDisplay(VDWG hDwg,VHANDLE hEnt)
{
  	cad_Square data;
  	bool bFill;
  	int et = CadCustomGetType(hEnt);
  	if(et == CAD_TYPE_SQUARE)
    {
    	// rectangle
    	CadCustomGetData(hEnt,&data);
    	bFill = CadEntityGetFilled(hEnt);
    	cad_DrawSquare(data,bFill);
  	}
}
//---------------------------------------------------------------------------

