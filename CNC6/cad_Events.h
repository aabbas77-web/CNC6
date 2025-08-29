//---------------------------------------------------------------------------
#ifndef cad_EventsH
#define cad_EventsH
//---------------------------------------------------------------------------
#include "shp_Contour.h"
#include "cadapi.h"
//---------------------------------------------------------------------------
#define CALLBACK    __stdcall
//---------------------------------------------------------------------------
extern double g_dDividingStep;
//---------------------------------------------------------------------------
extern bool g_bGenerateNamesList;
//---------------------------------------------------------------------------
extern AnsiString g_strFMask;
//---------------------------------------------------------------------------
extern int g_nCurrToolIndex;
//---------------------------------------------------------------------------
extern double g_dCurrDepth;
//---------------------------------------------------------------------------
extern VHANDLE g_hMachineHeadIndex;
//---------------------------------------------------------------------------
extern double g_dZStep;
//---------------------------------------------------------------------------
extern double g_dSpeed;
//---------------------------------------------------------------------------
struct cnc_Tool
{
    double x0,y0;// Origin
	TColor nColor;
    AnsiString strName;
}; 
extern cnc_Tool g_pTools[10];
extern int g_pDefaultToolsColors[10];
//---------------------------------------------------------------------------
struct cad_Entity
{
	int nToolIndex;
    double dDepth;
};
//---------------------------------------------------------------------------
class cad_Contour
{
public:
	shp_Contour Points;
    cad_Contour(){};
    ~cad_Contour(){};
    cad_Contour(const cad_Contour &Contour)
    {
        Points.clear();
        copy(Contour.Points.begin(),Contour.Points.end(),back_inserter(Points));
    }
    cad_Contour &operator =(const cad_Contour &Contour)
    {
        Points.clear();
        copy(Contour.Points.begin(),Contour.Points.end(),back_inserter(Points));
        return *this;
    }
};
//---------------------------------------------------------------------------
class cad_Shape
{
public:
	vector<cad_Contour> Contours;
    cad_Entity cadEntity;
    cad_Shape(){};
    ~cad_Shape(){};
    cad_Shape(const cad_Shape &Shape)
    {
    	cadEntity = Shape.cadEntity;
        Contours.clear();
        copy(Shape.Contours.begin(),Shape.Contours.end(),back_inserter(Contours));
    }
    cad_Shape &operator =(const cad_Shape &Shape)
    {
    	cadEntity = Shape.cadEntity;
        Contours.clear();
        copy(Shape.Contours.begin(),Shape.Contours.end(),back_inserter(Contours));
        return *this;
    }
};
//---------------------------------------------------------------------------
class cad_Layer
{
public:
	vector<cad_Shape> Shapes;
    cad_Layer(){};
    ~cad_Layer(){};
    cad_Layer(const cad_Layer &Layer)
    {
        Shapes.clear();
        copy(Layer.Shapes.begin(),Layer.Shapes.end(),back_inserter(Shapes));
    }
    cad_Layer &operator =(const cad_Layer &Layer)
    {
        Shapes.clear();
        copy(Layer.Shapes.begin(),Layer.Shapes.end(),back_inserter(Shapes));
        return *this;
    }
};
//---------------------------------------------------------------------------
class cad_Drawing
{
public:
	vector<cad_Layer> Layers;
    cad_Drawing(){};
    ~cad_Drawing(){};
    cad_Drawing(const cad_Drawing &Drawing)
    {
        Layers.clear();
        copy(Drawing.Layers.begin(),Drawing.Layers.end(),back_inserter(Layers));
    }
    cad_Drawing &operator =(const cad_Drawing &Drawing)
    {
        Layers.clear();
        copy(Drawing.Layers.begin(),Drawing.Layers.end(),back_inserter(Layers));
        return *this;
    }
};
//---------------------------------------------------------------------------
void cad_ExtractSegments(int nEntity,int nPath,int &nVertex,cad_Contour &Contour);
void cad_ExtractSegments(int nEntity,cad_Shape &Shape);
void cad_ExtractSegments(int nLayer,cad_Layer &Layer);
void cad_ExtractSegments(VDWG hDwg,cad_Drawing &Drawing);

void cad_DrawSegments(VDWG hDwg,cad_Contour &Contour);
void cad_DrawSegments(VDWG hDwg,cad_Shape &Shape);

bool cnc_Load_PLT(AnsiString strFileName,cad_Drawing &Drawing);
bool cnc_Save_PLT(AnsiString strFileName,cad_Drawing &Drawing);
bool cad_Export_PLT(VDWG hDwg,AnsiString strFileName);
bool cad_Import_PLT(VDWG hDwg,AnsiString strFileName);
//---------------------------------------------------------------------------
// Utilities
void cad_ShowText(int nIndex,AnsiString strText);
AnsiString GetEntityName(int nEntity);
//---------------------------------------------------------------------------
// Events
void CALLBACK EntCreateProc(VDWG hDwg,VHANDLE hEnt);
void CALLBACK EntSelectProc(VDWG hDwg,VHANDLE hEnt,BOOL bSelect,BOOL bFinal);
void CALLBACK EntEraseProc(VDWG hDwg,VHANDLE hEnt);
void CALLBACK MouseMoveProc(VDWG hDwg,int Button,int Key,int Xwin,int Ywin,
   					double Xdwg,double Ydwg,double Zdwg);
void CALLBACK MouseDownProc(VDWG hDwg,int Button,int Key,int Xwin,
							int Ywin,double Xdwg,double Ydwg,double Zdwg);
void CALLBACK FontReplaceProc(VDWG hDwg,LPCTSTR szFont,int bBigFont);
void CALLBACK SelCodepageProc(VDWG hDwg);
void CALLBACK ExecuteProc(VDWG hDwg,int Command);
void CALLBACK CmdStartProc(VDWG hDwg,int Command,int nSteps);
void CALLBACK CmdLBDownProc(VDWG hDwg,int Command,int Step,double* pX,double* pY,double* pZ);
void CALLBACK CmdFinishProc(VDWG hDwg,int Command);
void CALLBACK RegenProc(VDWG hDwg,int Step,int Percent,int NumEnt);
//---------------------------------------------------------------------------
// Custom commands
#define		CAD_CMD_DRAW_SQUARE		(CAD_CMD_CUSTOM + 1)
//---------------------------------------------------------------------------
// define callback functions for the command
void _stdcall Func_SQUARE(VDWG hDwg);
void _stdcall Drag_SQUARE(VDWG hDwg,int nPoints,double x,double y,double z);
//---------------------------------------------------------------------------
// Custom Entities
//---------------------------------------------------------------------------
// Sqaure - custom entity data
struct cad_Square
{
  	double x,y,z;
  	double Size;
  	double RotAngle;
};
void cad_DrawSquare(const cad_Square& data,bool bFill);
void cad_AddSquare(VDWG hDwg,cad_Square& data);
void cad_AddSquare(VDWG hDwg,double x,double y,double z,double Size,double RotAngle);
//---------------------------------------------------------------------------
// Spiral - custom entity data
struct cad_Spiral
{
	double x,y,z;
    double a,v,r0,dTours,dStep;
    bool bLines;
};
int cad_AddSpiral(VDWG hDwg,cad_Spiral &data);
/*
void cad_DrawSquare(const cad_Square& data,bool bFill);
void cad_AddSquare(VDWG hDwg,double x,double y,double z,double Size,double RotAngle);
*/
//---------------------------------------------------------------------------
// types of custom entities
#define 	CAD_TYPE_SQUARE 	1  	// Square
//---------------------------------------------------------------------------
void CALLBACK EventCEntGetName(VDWG hDwg,VHANDLE hEnt);
void CALLBACK EventCEntGetProps(VDWG hDwg,VHANDLE hEnt);
void CALLBACK EventCEntPutProp(VDWG hDwg,VHANDLE hEnt,int PropId,LPCTSTR szValue);
void CALLBACK EventCEntGetExts(VDWG hDwg,VHANDLE hEnt,double* pXmin,double* pYmin,double* pZmin,double* pXmax,double* pYmax,double* pZmax);
void CALLBACK EventCEntNumGrips(VDWG hDwg,VHANDLE hEnt,int* pN);
void CALLBACK EventCEntGetGrip(VDWG hDwg,VHANDLE hEnt,UINT iGrip,double* pX,double* pY,double* pZ);
void CALLBACK EventCEntMoveGrip(VDWG hDwg,VHANDLE hEnt,UINT iGrip,double dx,double dy,double dz);
void CALLBACK EventCEntMove(VDWG hDwg,VHANDLE hEnt,double dx,double dy,double dz);
void CALLBACK EventCEntRotate(VDWG hDwg,VHANDLE hEnt,double x0,double y0,double z0,double Angle,int Plane);
void CALLBACK EventCEntScale(VDWG hDwg,VHANDLE hEnt,double x0,double y0,double z0,double ScaleX,double ScaleY,double ScaleZ);
void CALLBACK EventCEntMirror(VDWG hDwg,VHANDLE hEnt,double A1,double B1,int Plane);
void CALLBACK EventCEntDisplay(VDWG hDwg,VHANDLE hEnt);
//---------------------------------------------------------------------------
#endif
