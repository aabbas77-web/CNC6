//---------------------------------------------------------------------------
#ifndef shp_ContourH
#define shp_ContourH
//---------------------------------------------------------------------------
#include <vector.h>
//---------------------------------------------------------------------------
#define shp_PI	(3.1415926535897932384626433832795)	// PI
#define shp_2PI	(6.283185307179586476925286766559)	// 2*PI
#define shp_PI2	(1.5707963267948966192313216916398) // PI/2
//---------------------------------------------------------------------------
struct shp_Point
{
	double x,y;
};
//---------------------------------------------------------------------------
typedef vector<shp_Point> shp_Contour;
//---------------------------------------------------------------------------
shp_Point shpPoint(double x,double y);
double shp_Distance(shp_Point &p1,shp_Point &p2);
// Clockwise: ÈÇÊÌÇå ÚÞÇÑÈ ÇáÓÇÚÉ
bool shp_IsClockwiseVertex(shp_Point &p1,shp_Point &p2,shp_Point &p3);
double shp_Angle_Rad(shp_Point &p0,shp_Point &p1,shp_Point &p2);
bool shp_Intersect_Circle_Segment(shp_Point &p0,double r,shp_Point &p1,shp_Point &p2,bool &bOneIntersection,shp_Point &I1,shp_Point &I2);
bool shp_ExtrudeNode(double dStep,shp_Point &p0,shp_Point &p1,shp_Point &p2,shp_Point &p);
bool shp_ExtrudeNode(double dStep,bool bStart,shp_Point &p0,shp_Point &p1,shp_Point &p);
//---------------------------------------------------------------------------
void shp_CopyContour(shp_Contour &Dest,shp_Contour &Source);
void shp_SaveContour(shp_Contour &Contour,AnsiString strFileName);
void shp_LoadContour(shp_Contour &Contour,AnsiString strFileName);
//---------------------------------------------------------------------------
void shp_Adjust_Contour(shp_Contour &Contour,shp_Contour &ResContour);
void shp_Divide_Contour(double dStep,bool bLeaveLongSegments,shp_Contour &Contour,shp_Contour &ResContour);
void shp_FindBestContour(double dEpsilon,shp_Contour &iContour,shp_Contour &oContour);
void shp_Smooth_Contour(double dStep,AnsiString strFileName,AnsiString strNewFileName);
void shp_Extrude_Contour(double dStep,bool bClosed,shp_Contour &Contour,shp_Contour &Extrude);
void shp_Contour_Remove_Repeated_Points(double dEpsilon,shp_Contour &Contour);
//---------------------------------------------------------------------------
void shp_FindBestStartPoint(shp_Contour &Contour,int &nIndex);
void shp_SetContourStartPoint(shp_Contour &Contour,int nIndex);
void shp_AutoSetContourStartPoint(shp_Contour &Contour);
void shp_Contour_Center(shp_Contour &Contour,double &x0,double &y0);
//---------------------------------------------------------------------------
extern double g_dEpsilon;
//---------------------------------------------------------------------------
#endif
