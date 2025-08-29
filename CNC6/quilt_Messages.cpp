//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#include <math.hpp>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "quilt_Messages.h"
#include "api_VecApi.h"
#include "quilt_Strings.h"
#include "Main.h"
#include "Export.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
double g_dSpeed = 1.0;
bool g_bGenerateNamesList = true;
bool g_bIsSimulator = false;
int g_nSimulatorDrawingIndex;
bool g_bControlPressed = false;
cnc_Tool g_pTools[10];
int g_pDefaultToolsColors[10] = {clBlack,clMaroon,clOlive,clNavy,clPurple,clTeal,clLime,clYellow,clFuchsia,clAqua};
//---------------------------------------------------------------------------
//spl_UInt Color;
//spl_GlobalStitchPath GlobalStitchPath;
//spl_GlobalStitch GlobalStitch;
//spl_StitchPath StitchPath;
//spl_Stitch Stitch;
//spl_EmbHeader EmbHeader;
bool bClicked;
bool OnlyOne = false;
bool g_bPolyArc = true;
//---------------------------------------------------------------------------
int g_nEdgeCounts = 3;
AnsiString g_strText = "WWPTC";
TCommandType CommandType = ctNone;
//---------------------------------------------------------------------------
VLPAINTSTRUCT *pPaintStruct;
//---------------------------------------------------------------------------
int spl_Cmd_PolyArc(int Msg,int Step,double x,double y);
//int spl_Cmd_Line(int Msg,int Step,double x,double y);
//int spl_Cmd_PolySatin(int Msg,int Step,double x,double y);
//int spl_Cmd_Text(int Msg,int Step,double x,double y);
//int spl_Cmd_PolyShape(int Msg,int Step,double x,double y);
//int spl_Cmd_ExtrudeShape(int Msg,int Step,double x,double y);
int spl_Cmd_Spiral(int Msg,int Step,double x,double y);
int spl_Cmd_Spiral_2(int Msg,int Step,double x,double y);
int spl_Cmd_Square(int Msg,int Step,double x,double y);
//---------------------------------------------------------------------------
//void DrawPolyline(spl_Contour &Contour,spl_UInt Color);
//void DrawSkeleton(spl_Contour &Contour,spl_Contour &Extrude,spl_UInt Color);
//void AddPolyline(spl_Contour &Contour,spl_UInt Color);
//void GetPolylineCenter(spl_Contour &Contour,spl_Point &Center);
void spl_DrawText(int x,int y);
//---------------------------------------------------------------------------
AnsiString GetEntityName(int nEntType,int nEntIndex)
{
    AnsiString strEntityName = FormatFloat("Unknown00000",nEntIndex);
    switch(nEntType)
    {
        case VL_ENT_POINT:
        {
            strEntityName = FormatFloat("Point00000",nEntIndex);
            break;
        }
        case VL_ENT_LINE:
        {
            strEntityName = FormatFloat("Line00000",nEntIndex);
            break;
        }
        case VL_ENT_POLY:
        {
            strEntityName = FormatFloat("Polyline00000",nEntIndex);
            break;
        }
        case VL_ENT_CIRCLE:
        {
            strEntityName = FormatFloat("Circle00000",nEntIndex);
            break;
        }
        case VL_ENT_ARC:
        {
            strEntityName = FormatFloat("Arc00000",nEntIndex);
            break;
        }
        case VL_ENT_ARC2:
        {
            strEntityName = FormatFloat("Arc200000",nEntIndex);
            break;
        }
        case VL_ENT_ELLIPSE:
        {
            strEntityName = FormatFloat("Ellipse00000",nEntIndex);
            break;
        }
        case VL_ENT_TEXT:
        {
            strEntityName = FormatFloat("Text00000",nEntIndex);
            break;
        }
        case VL_ENT_BITMAP:
        {
            strEntityName = FormatFloat("Bitmap00000",nEntIndex);
            break;
        }
        case VL_ENT_INSBLOCK:
        {
            strEntityName = FormatFloat("Block00000",nEntIndex);
            break;
        }
        case VL_ENT_HATCH:
        {
            strEntityName = FormatFloat("Hatch00000",nEntIndex);
            break;
        }
        case VL_ENT_FLOOD:
        {
            strEntityName = FormatFloat("Flood00000",nEntIndex);
            break;
        }
        case VL_ENT_RECT:
        {
            strEntityName = FormatFloat("Rect00000",nEntIndex);
            break;
        }
        case VL_ENT_DIMLIN:
        {
            strEntityName = FormatFloat("DimLin00000",nEntIndex);
            break;
        }
        case VL_ENT_DIMANG:
        {
            strEntityName = FormatFloat("DimAng00000",nEntIndex);
            break;
        }
        case VL_ENT_DIMRAD:
        {
            strEntityName = FormatFloat("DimRad00000",nEntIndex);
            break;
        }
        case VL_ENT_DIMDIAM:
        {
            strEntityName = FormatFloat("DimDiam00000",nEntIndex);
            break;
        }
        case VL_ENT_DIMORD:
        {
            strEntityName = FormatFloat("DimOrd00000",nEntIndex);
            break;
        }
        case VL_ENT_INSDWG:
        {
            strEntityName = FormatFloat("InsDwg00000",nEntIndex);
            break;
        }
        case VL_ENT_CUSTOM:
        {
            strEntityName = FormatFloat("Custom00000",nEntIndex);
            break;
        }
    }
	return strEntityName;
}
//---------------------------------------------------------------------------
bool ProcessExecutedCommands(int nCommand,bool bByExecute,bool bExecuted)
{
    switch(nCommand)
    {
/*    
        case VC_FILE_SAVE://	Save drawing to file
        case VC_FILE_SAVEAS://	Save drawing to file with another name
        case VC_FILE_CLOSE://	Close active drawing
        case VC_FILE_CLOSEALL://	Close all drawings
        case VC_IMPORT_DXF://	Import DXF file to current drawing
        case VC_EXPORT_DXF://	Export drawing to DXF format
        case VC_EXPORT_HPGL://	Export drawing to HPGL format
        case VC_EXPORT_BMP://	Export drawing to BMP format
        case VC_PRINT://	Print drawing

        case VC_ZOOM_ALL://	Zoom to drawing's extents
        case VC_ZOOM_WIN://	Zoom drawing by rectangle
        case VC_ZOOM_PAN://	Shift drawing's view by X and Y discriminate
        case VC_ZOOM_PAGE://	Show drawing in full page mode
        case VC_ZOOM_IN://	Enlarge drawing's view
        case VC_ZOOM_OUT://	Diminish drawing's view
        case VC_ZOOM_LEFT://	Shift drawing to right
        case VC_ZOOM_RIGHT://	Shift drawing to left
        case VC_ZOOM_UP://	Shift drawing downward
        case VC_ZOOM_DOWN://	Shift drawing upward
        case VC_ZOOM_PREV://	Show the previous view
        case VC_ZOOM_SEL://	Show all selected entities on active page

        case VC_PAGE_NEXT://	Show next page
        case VC_PAGE_PREV://	Show previous page
        case VC_PAGE_FIRST://	Show first page
        case VC_PAGE_LAST://	Show last page
        case VC_PAGE_DLG://	Select page from the list
        case VC_VIEW_SAVE://	Save current view
        case VC_VIEW_LIST://	Show window with picklist of saved views

        case VC_DRAW_POINT://	Draw point
        case VC_DRAW_LINE://	Draw line
        case VC_DRAW_POLYLINE://	Draw polyline
        case VC_DRAW_SPLINE://	Draw spline
        case VC_DRAW_CIRC_CR://	Draw circle by center, radius
        case VC_DRAW_CIRC_CD:// 	Draw circle by center, diameter
        case VC_DRAW_CIRC_2P://	Draw circle by 2 radial points
        case VC_DRAW_CIRC_3P://	Draw circle by 3 radial points
        case VC_DRAW_ARC_CSE://	Draw arc by center, start point, end point (CSE)
        case VC_DRAW_ARC_SEM://	Draw arc by start, end and middle points (SEM)
        case VC_DRAW_ARC_SME://	Draw arc by start, middle and end points (SME)
        case VC_DRAW_SECTOR://	Draw sector
        case VC_DRAW_ELLIPSE://	Draw ellipse
        case VC_DRAW_RECT://	Draw rectangle
        case VC_DRAW_DIM_HOR://	Draw horizontal dimension
        case VC_DRAW_DIM_VER://	Draw vertical dimension
        case VC_DRAW_DIM_PAR://	Draw parallel dimension
        case VC_DRAW_DIM_ANG://	Draw angular dimension
        case VC_DRAW_DIM_RAD://	Draw radial dimension
        case VC_DRAW_DIM_DIAM://	Draw diametric dimension
        case VC_DRAW_DIM_ORD://	Draw ordinate dimension
        case VC_DRAW_HATCH://	Draw hatch
        case VC_INS_TEXT://	Insert text
        case VC_INS_SYMBOL://	Insert TTF symbol
        case VC_INS_BLOCK://	Insert block
        case VC_INS_IMAGE://	Insert raster image
        case VC_INS_DRAWING://	Insert drawing

        case VC_EDIT_ENTPROP://	Edit entity's properties
        case VC_EDIT_COPY://	Copy entities
        case VC_EDIT_MOVE://	Move entities
        case VC_EDIT_ROTATE://	Rotate entities
        case VC_EDIT_SCALE://	Scale entities
        case VC_EDIT_MIRROR://	Mirror entities
        case VC_EDIT_ERASE://	Erase entities
        case VC_EDIT_EXPLODE://	Explode entities
        case VC_EDIT_CREBLOCK://	Create block definition
*/
        case VC_EDIT_UNDO://	Undo last change
        case VC_EDIT_REDO://	Redo undone changes
        {
			FormMain->BuildEntitiesList();
         	break;
        }
/*
        case VC_EDIT_CBCUT://	Cut entities to clipboard
        case VC_EDIT_CBCOPY://	Copy entities to clipboard
        case VC_EDIT_CBPASTE://	Paste entities from clipboard

        case VC_FMT_LAYOUT://	Show dialog "Drawing's layout"
        case VC_FMT_PAGE://	Show dialog "Pages"
        case VC_FMT_LAYER://	Show dialog "Layers"
        case VC_FMT_STLINE://	Show dialog "Line styles"
        case VC_FMT_STTEXT://	Show dialog "Text styles"
        case VC_FMT_STDIM://	Show dialog "Dimension styles"
        case VC_FMT_STPOINT://	Show dialog "Point styles"
        case VC_FMT_STHATCH://	Show dialog "Hatch styles"
        case VC_FMT_BLOCK://	Show dialog "Blocks definitions"
        case VC_FMT_GRID://	Show dialog "Grid"
        case VC_FMT_OSNAP://	Show dialog "Object snap"
        case VC_FMT_PSNAP://	Show dialog "Polar snap"
        case VC_FMT_UNITS://	Show dialog "Units"
        case VC_FMT_PRIVATE://	Show dialog "Private"
        case VC_FMT_PREFERS://	Show dialog "Preferences"

        case VC_SNAP_DLG://	Show dialog "Object snap"
        case VC_SNAP_CLEAR://	Disables all snap modes
        case VC_SNAP_GRID://	Toggles on/off snap to grid nodes
        case VC_SNAP_POLAR://	Toggles on/off polar snap
        case VC_SNAP_GRIPS://	Toggles on/off snap to entities grips
        case VC_SNAP_POINT://	Toggles on/off snap to point entities
        case VC_SNAP_NEAR://	Toggles on/off snap to nearest point on entity
        case VC_SNAP_END://	Toggles on/off snap to endpoint
        case VC_SNAP_MID://	Toggles on/off snap to middle point
        case VC_SNAP_CEN://	Toggles on/off snap to center point
        case VC_SNAP_PERP://	Toggles on/off snap to perpendicular point
        case VC_SNAP_TANG://	Toggles on/off snap to tangent point
        case VC_SNAP_REALTIME://	Toggles on/off realtime snap mode

        case VC_TOOL_DIST://	Runs "Measure distance / area" tool
        case VC_TOOL_PRNRECT://	Show dialog "Split drawing on print areas"
        case VC_TOOL_STAT://	Show drawing's statistics
        case VC_TOOL_NAVIGATOR://	Show Navigator tool
        case VC_TOOL_LAYERS://	Show Layers manager tool

        case VC_ENT_SWAP://	Swap draw order for 2 entities on one layer
        case VC_ENT_TOTOP://	Moves entity to top of layer
        case VC_ENT_TOBOTTOM://	Moves entity to bottom of layer

        case VC_SEL_BYPOINT://	Select entities by point
        case VC_SEL_BYRECT://	Select entities by rectangle
        case VC_SEL_BYPOLYGON://	Select entities by polygon
        case VC_SEL_BYPOLYLINE://	Select entities crossed by polyline
        case VC_SEL_BYDIST://	Select entities within distance from point
*/
        case VC_RESET://	Cancel currently active command, de-select all entities, redraw drawing
        {
        	if(bExecuted)
            {
				FormMain->ActivateEntity(-1);
            }
			break;
        }
/*
        case VC_REDRAW://	Redraw drawing
        case VC_SHOWLINEW://	Toggles mode of showing lines width (real width / hairlines)
        case VC_SHOWGRID://	Toggles visibility of coordinate grid
        case VC_SHOWFILL://	Toggles modes "Show fills" / "Show frames only"
*/
    }
    return false;
}
//---------------------------------------------------------------------------
static int s_nEntityIndex=-1;
static double s_dDepth=0;
static double s_dZStep=1.0;
static double s_dPrevDepth=0;
static int s_nZCount = 0;
static int s_nPenWidth;
static int s_nPenColor;
static int s_nLayerIndex;
static int s_nLinesCount;
static AnsiString s_strFileName;
static cnc_File s_cncContour;
static cnc_File s_cncFile;
static cnc_Stitch s_P;
static bool s_bClicked = false;
//---------------------------------------------------------------------------
int DwgExportProc(int iDwg,UINT Msg,int Prm1,int Prm2,double Prm3,double Prm4,void* Prm5)
{
    switch(Msg)
    {
        // Start Exporting
        case VM_EXP_BEGIN:
        {
        	if(FormExport->ShowModal() != mrOk)	return false;
    		g_dSpeed = StrToFloat(FormExport->EditSpeed->Text);
            if(g_dSpeed <= 0.0)	g_dSpeed = 1.0;
            s_dZStep = StrToFloat(FormExport->EditZStep->Text);
            if(s_dZStep <= 0.0)	s_dZStep = 1.0;
            s_strFileName = AnsiString((char *)Prm5);;
            s_cncFile.clear();
            s_cncContour.clear();

			s_P.cmd = stJump;
            s_P.x = 0.0;
            s_P.y = 0.0;
            s_P.z = 0.0;
            s_P.Vx = 0.0;
            s_P.Vy = 0.0;
            s_P.Vz = 0.0;
            s_P.Ax = 0.0;
            s_P.Ay = 0.0;
            s_P.Az = 0.0;
            s_cncFile.push_back(s_P);
            s_dPrevDepth = 0;
            return true;
        }
        // End Of Exporting
        case VM_EXP_END:
        {
        	if(s_cncContour.size() > 1)
            {
            	if(s_dDepth <= 0.0)	s_dDepth = s_dZStep;
            	s_nZCount = s_dDepth/s_dZStep;
            	for(int n=1;n<=s_nZCount;n++)
                {
                	if(n % 2 == 0)
                    {
                        for(UINT i=0;i<s_cncContour.size();i++)
                        {
                            s_P = s_cncContour[i];
                            // Remove Tools after first tour
                            if((n > 1) && (s_P.cmd <= stTool_9))	continue;
                            if(s_P.cmd <= stJump)
	                            s_P.z = 0.0;
                            else
	                            s_P.z = n*s_dZStep;
                            s_cncFile.push_back(s_P);
                        }
                    }
                    else
                    {
                        for(int i=s_cncContour.size()-1;i>=0;i--)
                        {
                            s_P = s_cncContour[i];
                            // Remove Tools after first tour
                            if((n > 1) && (s_P.cmd <= stTool_9))	continue;
                            if(s_P.cmd <= stJump)
	                            s_P.z = 0.0;
                            else
	                            s_P.z = n*s_dZStep;
                            s_cncFile.push_back(s_P);
                        }
                    }
                }
            }
            s_cncContour.clear();

			s_P.cmd = stJump;
            s_P.x = 0.0;
            s_P.y = 0.0;
            s_P.z = 0.0;
            s_P.Vx = 0.0;
            s_P.Vy = 0.0;
            s_P.Vz = 0.0;
            s_P.Ax = 0.0;
            s_P.Ay = 0.0;
            s_P.Az = 0.0;
            s_cncFile.push_back(s_P);

			cnc_SaveCMDFile(s_strFileName,s_cncFile);
            return true;
        }
        // Start Exporting Entities
        case VM_EXP_ENTITY:
        {
        	s_nEntityIndex = Prm1;
			if(s_nEntityIndex == FormMain->m_nWorkingAreaRectIndex)	return true;
            s_dPrevDepth = s_dDepth;
            s_dDepth = vlPropGetInt(VD_ENT_KEY,s_nEntityIndex);
            return false;
        }
        // Move To (Jump Stitch)
        case VM_EXP_MOVETO:
        {
        	if(s_cncContour.size() > 1)
            {
            	if(s_dDepth <= 0.0)	s_dDepth = s_dZStep;
            	s_nZCount = s_dDepth/s_dZStep;
            	for(int n=1;n<=s_nZCount;n++)
                {
                	if(n % 2 == 0)
                    {
                        for(UINT i=0;i<s_cncContour.size();i++)
                        {
                            s_P = s_cncContour[i];
                            // Remove Tools after first tour
                            if((n > 1) && (s_P.cmd <= stTool_9))	continue;
                            if(s_P.cmd <= stJump)
	                            s_P.z = 0.0;
                            else
	                            s_P.z = n*s_dZStep;
                            s_cncFile.push_back(s_P);
                        }
                    }
                    else
                    {
                        for(int i=s_cncContour.size()-1;i>=0;i--)
                        {
                            s_P = s_cncContour[i];
                            // Remove Tools after first tour
                            if((n > 1) && (s_P.cmd <= stTool_9))	continue;
                            if(s_P.cmd <= stJump)
	                            s_P.z = 0.0;
                            else
	                            s_P.z = n*s_dZStep;
                            s_cncFile.push_back(s_P);
                        }
                    }
                }
            }
            s_cncContour.clear();

			s_P.cmd = stJump;
            s_P.x = Prm3;
            s_P.y = Prm4;
            s_P.z = 0.0;
            s_P.Vx = 0.0;
            s_P.Vy = 0.0;
            s_P.Vz = 0.0;
            s_P.Ax = 0.0;
            s_P.Ay = 0.0;
            s_P.Az = 0.0;
            s_cncContour.push_back(s_P);
            break;
        }
        // Line To (Normal Stitch)
        case VM_EXP_LINETO:
        {
			s_P.cmd = stNormal;
            s_P.x = Prm3;
            s_P.y = Prm4;
            s_P.z = 0.0;
            s_P.Vx = 0.0;
            s_P.Vy = 0.0;
            s_P.Vz = 0.0;
            s_P.Ax = 0.0;
            s_P.Ay = 0.0;
            s_P.Az = 0.0;
            s_cncContour.push_back(s_P);
            break;
        }
        // Arc To
        case VM_EXP_ARCTO:
        {
            break;
        }
        // Color Changed
        case VM_EXP_COLOR:
        {
        	s_nPenColor = Prm1;
            if(s_nPenColor == clBlue)	return false;
            for(int i=0;i<10;i++)
            {
                if(g_pTools[i].nColor == s_nPenColor)
                {
                    s_P.cmd = i;// Tool_i
                    s_P.x = 0.0;
                    s_P.y = 0.0;
                    s_P.z = 0.0;
                    s_P.Vx = 0.0;
                    s_P.Vy = 0.0;
                    s_P.Vz = 0.0;
                    s_P.Ax = 0.0;
                    s_P.Ay = 0.0;
                    s_P.Az = 0.0;
                    s_cncContour.push_back(s_P);
                    break;
                }
            }
            break;
        }
        // Pen Width Changed
        case VM_EXP_WIDTH:
        {
            s_nPenWidth = Prm3;
            break;
        }
        // Layer Changed
        case VM_EXP_LAYER:
        {
            s_nLayerIndex = Prm1;
            break;
        }
        // Stop Pen Feed
        case VM_EXP_PUMPOFF:
        {
            break;
        }
        // Explode Into Small Lines
        case VM_EXP_EXPLODE:
        {
            s_nLinesCount = Prm1;
            break;
        }
    }
    return false;
}
//---------------------------------------------------------------------------
int CALLBACK DwgProc (int iDwg,UINT Msg,int Prm1,int Prm2,double Prm3,double Prm4,void* Prm5)
{
	g_bIsSimulator = (iDwg == g_nSimulatorDrawingIndex);
    switch(Msg)
    {
        case VM_GETSTRING:
        {
            return LoadString(Prm1);
        }
        case VM_MENUVER:// Vertex Popup Menu
        {
            return true;
        }
        case VM_MENUEDIT:// Edit Popup Menu
        {
            return true;
        }
        case VM_LBDBLCLK:
        {
         	return true;
        }
        case VM_ENTDELETE:
        {
        	if(g_bIsSimulator)	return false;
        	int nEntIndex = Prm2;
			int nPos = FormMain->ListBoxEntities->Items->IndexOfObject((TObject *)nEntIndex);
			if(nPos >= 0)
            {
            	FormMain->ListBoxEntities->Items->Delete(nPos);
    	        FormMain->CSpinEditDepth->Value = 0;
                FormMain->CSpinEditDepth->Enabled = false;
            	FormMain->ComboBoxTools->Enabled = false;
            }
         	break;
        }
        case VM_KEYDOWN:
        {
        	if(g_bIsSimulator)	return false;
			int nKey = Prm1;
            g_bControlPressed = false;
            switch(nKey)
            {
             	case VK_CONTROL:
                {
                    g_bControlPressed = true;
                 	break;
                }
            }
         	break;
        }
        case VM_ENTSELECT:
        {
        	if(g_bIsSimulator)	return true;
        	int nEntityIndex = Prm2;
            if(nEntityIndex == FormMain->m_nWorkingAreaRectIndex)	return true;
            int nIndex;
			nIndex = FormMain->ListBoxEntities->Items->IndexOfObject((TObject *)nEntityIndex);
            if(nIndex >= 0)
            {
            	FormMain->ListBoxEntities->ItemIndex = nIndex;
    			FormMain->ActivateEntity(nEntityIndex);
            }
            if(!g_bControlPressed)
            {
				vlSelect(false,-1);
            }
         	break;
        }
        case VM_ENTUNSELECT:
        {
         	break;
        }
        case VM_ENTADD:
        {
        	if(g_bIsSimulator)	return false;
			if(!g_bGenerateNamesList)	return false;
            int nEntType = Prm1;
        	int nEntityIndex = Prm2;
            if(nEntityIndex == FormMain->m_nWorkingAreaRectIndex)	return true;
            AnsiString strEntityName = GetEntityName(nEntType,nEntityIndex);
            FormMain->ListBoxEntities->Items->AddObject(strEntityName,(TObject *)nEntityIndex);
			vlPropPutInt(VD_ENT_KEY,nEntityIndex,0);
            break;
        }
        case VM_ENTMOVE:
        {
         	break;
        }
        case VM_ZOOM:
        {
            break;
        }
        case VM_BEGINPAINT:
        {
            pPaintStruct = (VLPAINTSTRUCT *)Prm5;
            FormMain->m_pCanvas->Handle = pPaintStruct->hdc;
         	return false;
        }
        case VM_ENDPAINT:
        {
            break;
        }
        case VM_OBJACTIVE:
        {
            break;
        }
        case VM_DWGSELECT:
        {
            break;
        }
        case VM_EXECUTE:
        {
        	int nCommand = Prm1;
            bool bByExecute = !Prm2;
            return ProcessExecutedCommands(nCommand,bByExecute,false);
        }
        case VM_EXECUTED:
        {
        	int nCommand = Prm1;
            bool bByExecute = !Prm2;
            return ProcessExecutedCommands(nCommand,bByExecute,true);
        }
        case VM_LBDOWN:// Left Button Down
        {
         	break;
        }
        case VM_MOUSEMOVE:// Mouse Move
        {
         	break;
        }
        case VM_RBDOWN:// Right Button Down
        {
            break;
        }
        case VM_CMD_CREATE:
        case VM_CMD_OPEN:
        case VM_CMD_CLICK:
        case VM_CMD_DRAG:
        case VM_CMD_REDRAW:
        case VM_CMD_CLOSE:
        {
            switch(Prm1)
            {
                case spl_CMD_POLYARC:
                {
                    return spl_Cmd_PolyArc(Msg,Prm2,Prm3,Prm4);
                }
                case spl_CMD_LINE:
                {
                	OnlyOne = true;
//                    return spl_Cmd_Line(Msg,Prm2,Prm3,Prm4);
                }
                case spl_CMD_POLYLINE:
                {
                	OnlyOne = false;
//                    return spl_Cmd_Line(Msg,Prm2,Prm3,Prm4);
                }
                case spl_CMD_POLYSATIN:
                {
//                    return spl_Cmd_PolySatin(Msg,Prm2,Prm3,Prm4);
                }
                case spl_CMD_POLYSHAPE:
                {
//                    return spl_Cmd_PolyShape(Msg,Prm2,Prm3,Prm4);
                }
                case spl_CMD_TEXT:
                {
//                    return spl_Cmd_Text(Msg,Prm2,Prm3,Prm4);
                }
                case spl_CMD_EXTRUDE_POLYSHAPE:
                {
//                    return spl_Cmd_ExtrudeShape(Msg,Prm2,Prm3,Prm4);
                }
                case spl_CMD_SPIRAL:
                {
                    return spl_Cmd_Spiral(Msg,Prm2,Prm3,Prm4);
                }
                case spl_CMD_SPIRAL_2:
                {
                    return spl_Cmd_Spiral_2(Msg,Prm2,Prm3,Prm4);
                }
                case spl_CMD_SQUARE:
                {
                    return spl_Cmd_Square(Msg,Prm2,Prm3,Prm4);
                }
                case spl_CMD_PLUG_IN:
                {
                	if(FormMain->nCurrPluginIndex < FormMain->pPlugins->Count)
                    {
					    TPlugin *pPlugin;
					    pPlugin = (TPlugin *)FormMain->pPlugins->Objects[FormMain->nCurrPluginIndex];
	                 	return pPlugin->Draw(Msg,Prm2,Prm3,Prm4);
                    }
                    else
                    	return 0;
                }
            }
            break;
        }
        case VM_CLOSEQUERY:
        {
        	if(g_bIsSimulator)	return true;
    		bool bChnaged = vlPropGetInt(VD_DWG_ISDIRTY,Prm1);
            if(!bChnaged)	return true;
            AnsiString FileName=AnsiString((char *)Prm5);
            int ID=MessageDlg("File ["+FileName+"] Changed! \nSave Changes?",mtInformation,TMsgDlgButtons()<<mbYes<<mbNo,0);
            switch(ID)
            {
                case IDYES:
                {
                    FormMain->AFileSaveExecute(NULL);
                    break;
                }
                case IDNO:
                {
                    break;
                }
            }
            return true;
        }
        ////////////////////////////////////////
        // Export Command File (*.CMD) Format //
        ////////////////////////////////////////
        case VM_EXP_BEGIN:
        case VM_EXP_END:
        case VM_EXP_ENTITY:
        case VM_EXP_MOVETO:
        case VM_EXP_LINETO:
        case VM_EXP_COLOR:
        case VM_EXP_WIDTH:
        case VM_EXP_LAYER:
        case VM_EXP_PUMPOFF:
        case VM_EXP_EXPLODE:
        case VM_EXP_ARCTO:
        {
			return DwgExportProc(iDwg,Msg,Prm1,Prm2,Prm3,Prm4,Prm5);
        }
    }
    return false;
}
//---------------------------------------------------------------------------
int spl_Cmd_PolyArc(int Msg,int Step,double x,double y)
{
    // Store Coordinates Of First Point
    static double x0;
    static double y0;
    static double x1;
    static double y1;
    switch(Msg)
    {
        case VM_CMD_CREATE:
        {
            // Don`t Need Selected Entity For The Command
            vlRedraw();
            return 0;
        }
        case VM_CMD_OPEN:
        {
            // Command Need 3 Steps
            return 3;
        }
        case VM_CMD_CLICK:
        {
            switch(Step)
            {
                case 3:// Entered First Point
                {
                    x0=x;
                    y0=y;
                    return 2;
                }
                case 2:// Entered Second Point
                {
                    x1=x;
                    y1=y;
                    return 1;
                }
                case 1:// Entered Third Point
                {
                    if(g_bPolyArc)
                    {
                    	vlAddArc3P(x0,y0,x1,y1,x,y);
                        x0=x;
                        y0=y;
                        return 2;// Don`t End The Command
                    }
                    else
                    {
                    	vlAddLine(x0,y0,x1,y1);
                    	vlAddLine(x1,y1,x,y);
                        x0=x;
                        y0=y;
                        return 2;// Don`t End The Command
                    }
                }
            }
            return 0;
        }
        case VM_CMD_DRAG:
        {
        	if(g_bPolyArc)
            {
                if(Step==2)
                {
                    // Drag Line By Mouse While Not Click The Second Point
                    vlDrawLine(x0,y0,x,y);
                }
                else
                if(Step==1)
                {
                    // Drag Line By Mouse While Not Click The Second Point
                    vlDrawLine(x1,y1,x,y);
                }
            }
            else
            {
                if(Step==2)
                {
                    // Drag Line By Mouse While Not Click The Second Point
                    vlDrawLine(x0,y0,x,y);
                }
                else
                if(Step==1)
                {
                    // Drag Line By Mouse While Not Click The Second Point
                    vlDrawLine(x1,y1,x,y);
                }
            }
            return 0;
        }
        case VM_CMD_CLOSE:
        {
            vlRedraw();
            return 0;
        }
        case VM_CMD_REDRAW:
        {
            return 0;
        }
    }
    return 0;
}
//---------------------------------------------------------------------------
/*
static double dx;
static double dy;
static spl_Contour Contour;
static spl_Contour Extrude;
static spl_Contour Result;
static double ExtrudeDistance;
static spl_Point Center;

static double Density=3.0;
static bool Default = false;
static bool bMin = true;
//---------------------------------------------------------------------------
void spl_Initialize_Commands()
{
    switch(CommandType)
    {
     	case ctNone:
        {
         	break;
        }
        case ctPolySatin:
        {
	        // Command Need PointsCount Steps
    	    Contour.Points.erase(Contour.Points.begin(),Contour.Points.end());
	        Extrude.Points.erase(Extrude.Points.begin(),Extrude.Points.end());
	        Extrude.Points.resize(g_nEdgeCounts);
         	break;
        }
    }
}
//---------------------------------------------------------------------------
int spl_Cmd_Line(int Msg,int Step,double x,double y)
{
    // Store Coordinates Of First Point
    static double x0;
    static double y0;
    switch(Msg)
    {
        case VM_CMD_CREATE:
        {
            // Don`t Need Selected Entity For The Command
            vlRedraw();
            return 0;
        }
        case VM_CMD_OPEN:
        {
            // Command Need 2 Steps
            return 2;
        }
        case VM_CMD_CLICK:
        {
            switch(Step)
            {
                case 2:// Entered First Point
                {
                    x0=x;
                    y0=y;
                    return 1;
                }
                case 1:// Entered Second Point
                {
                    vlAddLine(x0,y0,x,y);
                    if(OnlyOne)
                    {
                        return 0;// End The Command
                    }
                    else
                    {
                        x0=x;
                        y0=y;
                        return 1;// Don`t End The Command
                    }
                }
            }
            return 0;
        }
        case VM_CMD_DRAG:
        {
            if(Step==1)
            {
                // Drag Line By Mouse While Not Click The Second Point
                vlDrawLine(x0,y0,x,y);
            }
            return 0;
        }
        case VM_CMD_CLOSE:
        {
            vlRedraw();
            return 0;
        }
        case VM_CMD_REDRAW:
        {
            return 0;
        }
    }
    return 0;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void DrawPolyline(spl_Contour &Contour,spl_UInt Color)
{
    spl_UInt PointsCount=Contour.Points.size();
    for(spl_UInt i=0;i<PointsCount;i++)
    {
        vlDrawLine(Contour.Points[(i) % PointsCount].x,Contour.Points[(i) % PointsCount].y,Contour.Points[(i+1) % PointsCount].x,Contour.Points[(i+1) % PointsCount].y);
    }
}
//---------------------------------------------------------------------------
void DrawSkeleton(spl_Contour &Contour,spl_Contour &Extrude,spl_UInt Color)
{
    spl_UInt PointsCount=Contour.Points.size();
    for(spl_UInt i=0;i<PointsCount;i++)
    {
        vlDrawLine(Contour.Points[(i) % PointsCount].x,Contour.Points[(i) % PointsCount].y,Contour.Points[(i+1) % PointsCount].x,Contour.Points[(i+1) % PointsCount].y);
        vlDrawLine(Extrude.Points[(i) % PointsCount].x,Extrude.Points[(i) % PointsCount].y,Extrude.Points[(i+1) % PointsCount].x,Extrude.Points[(i+1) % PointsCount].y);
        vlDrawLine(Contour.Points[(i) % PointsCount].x,Contour.Points[(i) % PointsCount].y,Extrude.Points[(i) % PointsCount].x,Extrude.Points[(i) % PointsCount].y);
    }
}
//---------------------------------------------------------------------------
void AddPolyline(spl_Contour &Contour,spl_UInt Color)
{
    spl_UInt PointsCount=Contour.Points.size();
    vlPolylineBegin();
    for(spl_UInt i=0;i<=PointsCount;i++)
    {
        vlVertex(Contour.Points[i % PointsCount].x,Contour.Points[i % PointsCount].y);
    }
    vlAddPolyline(VL_POLY_LINE,true);
}
//---------------------------------------------------------------------------
int spl_Cmd_PolySatin(int Msg,int Step,double x,double y)
{
    // Store Coordinates Of First Point
    static double dx;
    static double dy;
    static spl_Contour Contour;
    static spl_Contour Extrude;
    static spl_Contour Result;
    static double ExtrudeDistance;
    static spl_UInt Color=clBlack;
    static spl_Point Center;
    static bool Created = false;

    static double Density=3.0;
    static bool Default = true;
    static bool bMin = true;

    switch(Msg)
    {
        case VM_CMD_CREATE:
        {
            // Don`t Need Selected Entity For The Command
            vlRedraw();
            return 0;
        }
        case VM_CMD_OPEN:
        {
            // Command Need PointsCount Steps
            Contour.Points.erase(Contour.Points.begin(),Contour.Points.end());
            Extrude.Points.erase(Extrude.Points.begin(),Extrude.Points.end());
//            Contour.Points.resize(g_nEdgeCounts);
            Extrude.Points.resize(g_nEdgeCounts);
            Created = true;
            return g_nEdgeCounts+1;
        }
        case VM_CMD_CLICK:
        {
        	if(Step == g_nEdgeCounts + 1)
            {
            	Contour.Points.resize(g_nEdgeCounts - Step + 2);
            	Contour.Points[g_nEdgeCounts - Step + 1].x=x;
                Contour.Points[g_nEdgeCounts - Step + 1].y=y;
                return Step - 1;
            }
            else
        	if(Step == g_nEdgeCounts)
            {
            	Contour.Points.resize(g_nEdgeCounts - Step + 2);
            	Contour.Points[g_nEdgeCounts - Step + 1].x=x;
                Contour.Points[g_nEdgeCounts - Step + 1].y=y;

                // Clear Line
                vlDrawLine(Contour.Points[g_nEdgeCounts - Step].x,Contour.Points[g_nEdgeCounts - Step].y,Contour.Points[g_nEdgeCounts - Step + 1].x,Contour.Points[g_nEdgeCounts - Step + 1].y);
                return Step - 1;
            }
            else
        	if(Step == 1)// Entered End Point
            {
            	dx=spl_ABS(x-Center.x);
                dy=spl_ABS(y-Center.y);
                ExtrudeDistance=sqrt(dx*dx+dy*dy);

                spl_ExtrudeBySkeleton(ExtrudeDistance,Contour,Extrude);
                spl_EmbroidContour(bMin,ExtrudeDistance,Density,Default,Contour,Result);
                AddPolyline(Result,Color);
                return Step - 1;// End The Command
            }
            else
            {
            	Contour.Points.resize(g_nEdgeCounts - Step + 2);
            	Contour.Points[g_nEdgeCounts - Step + 1].x=x;
                Contour.Points[g_nEdgeCounts - Step + 1].y=y;

                // Clear Polyline And Calculate Center
                DrawPolyline(Contour,Color);
//                GetPolylineCenter(Contour,Center);
                Center = spl_Center(Contour);
                return Step - 1;// End The Command
            }
        }
        case VM_CMD_DRAG:
        {
			if(!Created)	return 0;
            if(Step == g_nEdgeCounts)
            {
            	Contour.Points.resize(g_nEdgeCounts - Step + 2);
                Contour.Points[g_nEdgeCounts - Step + 1].x=x;
                Contour.Points[g_nEdgeCounts - Step + 1].y=y;
                vlDrawLine(Contour.Points[g_nEdgeCounts - Step].x,Contour.Points[g_nEdgeCounts - Step].y,Contour.Points[g_nEdgeCounts - Step + 1].x,Contour.Points[g_nEdgeCounts - Step + 1].y);
            }
            else
            if(Step == 1)
            {
                // Drag Line By Mouse While Not Click The Second Point
                vlDrawLine(Center.x,Center.y,x,y);

                dx=spl_ABS(x-Center.x);
                dy=spl_ABS(y-Center.y);
                ExtrudeDistance=sqrt(dx*dx+dy*dy);

                spl_ExtrudeBySkeleton(ExtrudeDistance,Contour,Extrude);
                DrawSkeleton(Contour,Extrude,Color);
            }
            else
            {
            	Contour.Points.resize(g_nEdgeCounts - Step + 2);
                Contour.Points[g_nEdgeCounts - Step + 1].x=x;
                Contour.Points[g_nEdgeCounts - Step + 1].y=y;
                DrawPolyline(Contour,Color);
            }
            return 0;
        }
        case VM_CMD_CLOSE:
        {
            vlRedraw();
            return 0;
        }
        case VM_CMD_REDRAW:
        {
            return 0;
        }
    }
    return 0;
}

//---------------------------------------------------------------------------
int spl_Cmd_ExtrudeShape(int Msg,int Step,double x,double y)
{
    // Store Coordinates Of First Point
    static double dx;
    static double dy;
    static spl_Contour Contour;
    static spl_Contour Extrude;
    static spl_Contour Result;
    static double ExtrudeDistance;
    static spl_UInt Color=clBlack;
    static spl_Point Center;
    static bool Created = false;

    static double Density=3.0;
    static bool Default = true;
    static bool bMin = true;

    switch(Msg)
    {
        case VM_CMD_CREATE:
        {
            // Don`t Need Selected Entity For The Command
            vlRedraw();
            return 0;
        }
        case VM_CMD_OPEN:
        {
            // Command Need PointsCount Steps
            Contour.Points.erase(Contour.Points.begin(),Contour.Points.end());
            Extrude.Points.erase(Extrude.Points.begin(),Extrude.Points.end());
            Created = true;
            return 2;
        }
        case VM_CMD_CLICK:
        {
        	if(Step == 2)
            {
				// Create new shape
                
	        	spl_Point P;
	            float fXRadius = 10.0;
	            float fYRadius = 10.0;

	        	for(float fAngle=0.0;fAngle<360.0;fAngle+=22.5)
	            {
					P.x = x + fXRadius * cos(DegToRad(fAngle));
					P.y = y + fYRadius * sin(DegToRad(fAngle));

	            	Contour.Points.push_back(P);
	            }

//	        	GetPolylineCenter(Contour,Center);
	        	Center = spl_Center(Contour);
    	        return 1;
            }
            else
        	if(Step == 1)
            {
	        	dx=spl_ABS(x-Center.x);
	            dy=spl_ABS(y-Center.y);
	            ExtrudeDistance=sqrt(dx*dx+dy*dy);

	            spl_ExtrudeBySkeleton(ExtrudeDistance,Contour,Extrude);
	            spl_EmbroidContour(bMin,ExtrudeDistance,Density,Default,Contour,Result);
	            AddPolyline(Result,Color);
    	        return 0;// End The Command
            }
        }
        case VM_CMD_DRAG:
        {
			if(!Created)	return 0;
			dx=spl_ABS(x-Center.x);
            dy=spl_ABS(y-Center.y);
            ExtrudeDistance=sqrt(dx*dx+dy*dy);

            spl_ExtrudeBySkeleton(ExtrudeDistance,Contour,Extrude);
            spl_EmbroidContour(bMin,ExtrudeDistance,Density,Default,Contour,Result);
            DrawPolyline(Result,Color);
            DrawPolyline(Contour,Color);
            DrawPolyline(Extrude,Color);
            return 0;
        }
        case VM_CMD_CLOSE:
        {
            vlRedraw();
            return 0;
        }
        case VM_CMD_REDRAW:
        {
            return 0;
        }
    }
    return 0;
}
//---------------------------------------------------------------------------
int spl_Cmd_PolyShape(int Msg,int Step,double x,double y)
{
    // Store Coordinates Of First Point
    static double dx;
    static double dy;
    static spl_Contour Contour;
    static spl_Contour Extrude;
    static spl_Contour Result;
    static double ExtrudeDistance;
    static spl_UInt Color=clBlack;
    static spl_Point Center;
    static bool Created = false;

    static double Density=1.0;
    static bool Default = false;
    static bool bMin = true;

    static spl_Rect Frame;

    switch(Msg)
    {
        case VM_CMD_CREATE:
        {
            // Don`t Need Selected Entity For The Command
            vlRedraw();
            Created = false;
            return 0;
        }
        case VM_CMD_OPEN:
        {
            // Command Need PointsCount Steps
            Contour.Points.clear();
            Extrude.Points.clear();
            Created = false;
            return 2;
        }
        case VM_CMD_CLICK:
        {
        	if(Step == 2)
            {
				// Create new shape
	        	spl_Point P;
	            float fXRadius = 3.0;
	            float fYRadius = 3.0;

                Contour.Points.clear();
	        	for(float fAngle=0.0;fAngle<360.0;fAngle+=22.5)
	            {
					P.x = x + fXRadius * cos(DegToRad(fAngle));
					P.y = y + fYRadius * sin(DegToRad(fAngle));

	            	Contour.Points.push_back(P);
	            }

                ExtrudeDistance = 10;
	            spl_ExtrudeBySkeleton(ExtrudeDistance,Contour,Extrude);
	            spl_EmbroidContour(bMin,ExtrudeDistance,Density,Default,Contour,Result);
//	        	GetPolylineCenter(Result,Center);
	        	Center = spl_Center(Result);
            	Created = true;
    	        return 1;
            }
            else
        	if(Step == 1)
            {
	            AddPolyline(Contour,Color);
    	        return 0;// End The Command
            }
        }
        case VM_CMD_DRAG:
        {
			if(!Created)	return 0;
			dx=spl_ABS(x-Center.x);
            dy=spl_ABS(y-Center.y);
            ExtrudeDistance=sqrt(dx*dx+dy*dy);

			Frame.left = Center.x - ExtrudeDistance;
			Frame.right = Center.x + ExtrudeDistance;
			Frame.top = Center.y - ExtrudeDistance;
			Frame.bottom = Center.y + ExtrudeDistance;

            spl_ScaleContour(Result,Frame,false,1.0,Contour);
            DrawPolyline(Contour,Color);
            return 0;
        }
        case VM_CMD_CLOSE:
        {
            vlRedraw();
            return 0;
        }
        case VM_CMD_REDRAW:
        {
            return 0;
        }
    }
    return 0;
}
//---------------------------------------------------------------------------
void spl_DrawText(int x,int y)
{
	AnsiString strText = FormInsertText->RichEdit->Text.Trim();
    UINT Count = strText.Length();
    wchar_t *pGlyphs = new wchar_t[Count];
    HDC hdc = FormInsertText->Label->Canvas->Handle;
    spl_TextToGlyphs(hdc,strText.c_str(),pGlyphs,Count);

    spl_Point Origin;
    Origin = splPoint(x,y);

    for(UINT i=0;i<Count;i++)
    {
		GetCharacterGlyphs(hdc,pGlyphs[i],false,Origin);
    }

    if(pGlyphs)
    {
     	delete[] pGlyphs;
        pGlyphs = NULL;
    }
}
//---------------------------------------------------------------------------
int spl_Cmd_Text(int Msg,int Step,double x,double y)
{
    switch(Msg)
    {
        case VM_CMD_CREATE:
        {
            // Don`t Need Selected Entity For The Command
            vlRedraw();
            return 0;
        }
        case VM_CMD_OPEN:
        {
			if(FormInsertText->ShowModal() != mrOk)	return 0;
            vlRedraw();
            return 1;
        }
        case VM_CMD_CLICK:
        {
        	if(Step == 1)// Entered End Point
            {
            	spl_DrawText(x,y);

                return Step - 1;// End The Command
            }
            return 0;
        }
        case VM_CMD_DRAG:
        {
            return 0;
        }
        case VM_CMD_CLOSE:
        {
            vlRedraw();
            return 0;
        }
        case VM_CMD_REDRAW:
        {
            return 0;
        }
    }
    return 0;
}
*/
//---------------------------------------------------------------------------
void cnc_DrawSpiral(double x0,double y0,double a,double v,double r0,double dTours,double dStep,bool bLines)
{
	if(dStep <= 0.0)	return;
    if(!bLines)	dStep = 10.0;
    // Draw
    double r;
    double x,y;
    double x1,y1;
    x1 = x0+r0;
    y1 = y0;
    for(double t=0.0;t<=dTours*360.0;t+=dStep)
    {
    	r = a*t*t+v*t+r0;
		x = x0+r*cos(DegToRad(t));
		y = y0+r*sin(DegToRad(t));
        vlDrawLine(x1,y1,x,y);
        x1 = x;
        y1 = y;
    }
}
//---------------------------------------------------------------------------
int cnc_AddSpiral(double x0,double y0,double a,double v,double r0,double dTours,double dStep,bool bLines)
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
//---------------------------------------------------------------------------
/*
int spl_Cmd_Spiral(int Msg,int Step,double x,double y)
{
    static bool Created = false;
    //static double x0,y0,a=0.0,v=0.5,r0=10.0,dTours=5.0,dStep=60.0;
    static double a=0.0,v=0.5,r0=10.0,dTours=0.0,dStep=60.0;
    static cnc_Point p0,p;
    static int nEntityIndex = -1;
    p.x = x;
    p.y = y;
    switch(Msg)
    {
        case VM_CMD_CREATE:
        {
            // Don`t Need Selected Entity For The Command
            vlRedraw();
            return 0;
        }
        case VM_CMD_OPEN:
        {
            // Command Need Steps Count
            Created = true;
            return 2;
        }
        case VM_CMD_CLICK:
        {
            switch(Step)
            {
                case 2:// Entered First Point
                {
                    p0.x = x;
                    p0.y = y;
                    return 1;
                }
                case 1:// Entered Next Point
                {
					dTours = cnc_Distance(p0,p)/100.0;
                    if(nEntityIndex >= 0)	vlErase(nEntityIndex);
                    g_bGenerateNamesList = true;
        			nEntityIndex = cnc_AddSpiral(p0.x,p0.y,a,v,r0,dTours,dStep);
                    nEntityIndex = -1;
                    vlRedraw();
                    return 0;
                }
            }
        	return 0;
        }
        case VM_CMD_DRAG:
        {
			if(!Created)	return 0;
            switch(Step)
            {
                case 1:// Entered Next Point
                {
					dTours = cnc_Distance(p0,p)/100.0;
                    if(nEntityIndex >= 0)	vlErase(nEntityIndex);
                    g_bGenerateNamesList = false;
        			nEntityIndex = cnc_AddSpiral(p0.x,p0.y,a,v,r0,dTours,dStep);
                    g_bGenerateNamesList = true;
                    vlRedraw();
        			vlDrawLine(p0.x,p0.y,p.x,p.y);
                    return 0;
                }
            }
            return 0;
        }
        case VM_CMD_CLOSE:
        {
            return 0;
        }
        case VM_CMD_REDRAW:
        {
            return 0;
        }
    }
    return 0;
}
*/
//---------------------------------------------------------------------------
int spl_Cmd_Spiral(int Msg,int Step,double x,double y)
{
    static bool Created = false;
    static double a=0.0,v=0.5,r0=10.0,dTours=0.0,dStep=60.0;
    static bool bLines = false;
    static cnc_Point p0,p;
    p.x = x;
    p.y = y;
    switch(Msg)
    {
        case VM_CMD_CREATE:
        {
            // Don`t Need Selected Entity For The Command
            vlRedraw();
            return 0;
        }
        case VM_CMD_OPEN:
        {
            // Command Need Steps Count
            Created = true;
            return 3;
        }
        case VM_CMD_CLICK:
        {
            switch(Step)
            {
                case 3:
                {
                    p0.x = x;
                    p0.y = y;
                    return 2;
                }
                case 2:
                {
                    dTours = abs(p.x-p0.x)/180;
                    r0 = abs(p.y-p0.y);
        			cnc_DrawSpiral(p0.x,p0.y,a,v,r0,dTours,dStep,bLines);
                    return 1;
                }
                case 1:
                {
                    v = abs(p.x-p0.x)/1000.0;
                    a = abs(p.y-p0.y)/1000000.0;
        			cnc_AddSpiral(p0.x,p0.y,a,v,r0,dTours,dStep,bLines);
                    return 0;
                }
            }
        	return 0;
        }
        case VM_CMD_DRAG:
        {
			if(!Created)	return 0;
            switch(Step)
            {
                case 2:
                {
                    dTours = abs(p.x-p0.x)/180;
                    r0 = abs(p.y-p0.y);
        			cnc_DrawSpiral(p0.x,p0.y,a,v,r0,dTours,dStep,bLines);
                    break;
                }
                case 1:
                {
                    v = abs(p.x-p0.x)/1000.0;
                    a = abs(p.y-p0.y)/1000000.0;
        			cnc_DrawSpiral(p0.x,p0.y,a,v,r0,dTours,dStep,bLines);
                    break;
                }
            }
            return 0;
        }
        case VM_CMD_CLOSE:
        {
        	vlRedraw();
            return 0;
        }
        case VM_CMD_REDRAW:
        {
            return 0;
        }
    }
    return 0;
}
//---------------------------------------------------------------------------
int spl_Cmd_Spiral_2(int Msg,int Step,double x,double y)
{
    static bool Created = false;
    static double a=0.0,v=0.5,r0=10.0,dTours=0.0,dStep=60.0;
    static bool bLines = true;
    static cnc_Point p0,p;
    p.x = x;
    p.y = y;
    switch(Msg)
    {
        case VM_CMD_CREATE:
        {
            // Don`t Need Selected Entity For The Command
            vlRedraw();
            return 0;
        }
        case VM_CMD_OPEN:
        {
            // Command Need Steps Count
            Created = true;
            return 4;
        }
        case VM_CMD_CLICK:
        {
            switch(Step)
            {
                case 4:
                {
                    p0.x = x;
                    p0.y = y;
                    return 3;
                }
                case 3:
                {
                    dTours = abs(p.x-p0.x)/180;
                    r0 = abs(p.y-p0.y);
        			cnc_DrawSpiral(p0.x,p0.y,a,v,r0,dTours,dStep,bLines);
                    return 2;
                }
                case 2:
                {
                    v = abs(p.x-p0.x)/1000.0;
                    a = abs(p.y-p0.y)/1000000.0;
        			cnc_DrawSpiral(p0.x,p0.y,a,v,r0,dTours,dStep,bLines);
                    return 1;
                }
                case 1:
                {
                	dStep = cnc_Distance(p0,p)/60.0;
        			cnc_AddSpiral(p0.x,p0.y,a,v,r0,dTours,dStep,bLines);
                    return 0;
                }
            }
        	return 0;
        }
        case VM_CMD_DRAG:
        {
			if(!Created)	return 0;
            switch(Step)
            {
                case 3:
                {
                    dTours = abs(p.x-p0.x)/180;
                    r0 = abs(p.y-p0.y);
        			cnc_DrawSpiral(p0.x,p0.y,a,v,r0,dTours,dStep,bLines);
                    break;
                }
                case 2:
                {
                    v = abs(p.x-p0.x)/1000.0;
                    a = abs(p.y-p0.y)/1000000.0;
        			cnc_DrawSpiral(p0.x,p0.y,a,v,r0,dTours,dStep,bLines);
                    break;
                }
                case 1:
                {
                	dStep = cnc_Distance(p0,p)/60.0;
        			cnc_DrawSpiral(p0.x,p0.y,a,v,r0,dTours,dStep,bLines);
                    break;
                }
            }
            return 0;
        }
        case VM_CMD_CLOSE:
        {
        	vlRedraw();
            return 0;
        }
        case VM_CMD_REDRAW:
        {
            return 0;
        }
    }
    return 0;
}
//---------------------------------------------------------------------------
int spl_Cmd_Square(int Msg,int Step,double x,double y)
{
    static bool Created = false;
    static double Width,Angle=0.0,Radius=0.0;
    static cnc_Point p0,p;
    p.x = x;
    p.y = y;
    switch(Msg)
    {
        case VM_CMD_CREATE:
        {
            // Don`t Need Selected Entity For The Command
            vlRedraw();
            return 0;
        }
        case VM_CMD_OPEN:
        {
            // Command Need Steps Count
            Created = true;
            return 2;
        }
        case VM_CMD_CLICK:
        {
            switch(Step)
            {
                case 2:
                {
                    p0.x = x;
                    p0.y = y;
                    return 1;
                }
                case 1:
                {
                	Width = 2*cnc_Distance(p0,p);
                	vlAddRect(p0.x,p0.y,Width,Width,Angle,Radius);
                    return 0;
                }
            }
        	return 0;
        }
        case VM_CMD_DRAG:
        {
			if(!Created)	return 0;
            switch(Step)
            {
                case 1:
                {
                	Width = 2*cnc_Distance(p0,p);
                	vlDrawLine(p0.x-Width/2,p0.y-Width/2,p0.x+Width/2,p0.y-Width/2);
                	vlDrawLine(p0.x+Width/2,p0.y-Width/2,p0.x+Width/2,p0.y+Width/2);
                	vlDrawLine(p0.x+Width/2,p0.y+Width/2,p0.x-Width/2,p0.y+Width/2);
                	vlDrawLine(p0.x-Width/2,p0.y+Width/2,p0.x-Width/2,p0.y-Width/2);
                    break;
                }
            }
            return 0;
        }
        case VM_CMD_CLOSE:
        {
        	vlRedraw();
            return 0;
        }
        case VM_CMD_REDRAW:
        {
            return 0;
        }
    }
    return 0;
}
//---------------------------------------------------------------------------

