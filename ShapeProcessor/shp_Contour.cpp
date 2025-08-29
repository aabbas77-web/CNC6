//---------------------------------------------------------------------------
#include <vcl.h>
#include <math.h>
#include <math.hpp>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "shp_Contour.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
double g_dEpsilon = 0.01;
//---------------------------------------------------------------------------
shp_Point shpPoint(double x,double y)
{
	shp_Point p;
    p.x = x;
    p.y = y;
	return p;
}
//---------------------------------------------------------------------------
double shp_Distance(shp_Point &p1,shp_Point &p2)
{
 	return sqrt((p2.x-p1.x)*(p2.x-p1.x)+(p2.y-p1.y)*(p2.y-p1.y));
}
//---------------------------------------------------------------------------
// Clockwise: ÈÇÊÌÇå ÚÞÇÑÈ ÇáÓÇÚÉ
bool shp_IsClockwiseVertex(shp_Point &p1,shp_Point &p2,shp_Point &p3)
{
    return (((p2.x-p1.x)*(p3.y-p2.y)-(p2.y-p1.y)*(p3.x-p2.x)) >= 0);
}
//---------------------------------------------------------------------------
double shp_Angle_Rad(shp_Point &p0,shp_Point &p1,shp_Point &p2)
{
	shp_Point v1,v2;
    double Y,X,dAngle;
    v1.x = p1.x-p0.x;
    v1.y = p1.y-p0.y;
    v2.x = p2.x-p0.x;
    v2.y = p2.y-p0.y;
    Y = v1.x*v2.y-v1.y*v2.x;
    X = v1.x*v2.x+v1.y*v2.y;
    if(X == 0.0)
    {
		if(Y > 0.0)
			dAngle = shp_PI2;
        else
        if(Y < 0.0)
			dAngle = -shp_PI2;
        else
			dAngle = 0.0;
    }
    else
    {
		dAngle = ArcTan2(Y,X);
    }
 	return dAngle;
}
//---------------------------------------------------------------------------
bool shp_Intersect_Circle_Segment(shp_Point &p0,double r,shp_Point &p1,shp_Point &p2,bool &bOneIntersection,shp_Point &I1,shp_Point &I2)
{
	double x0,y0,dL;
    dL = shp_Distance(p1,p2);
    if(dL <= 0.0)	return false;
    shp_Point K;
    K.x = (p2.x-p1.x)/dL;
    K.y = (p2.y-p1.y)/dL;
    x0 = p1.x-p0.x;
    y0 = p1.y-p0.y;
	double a,b,c,delta;
    a = K.x*K.x+K.y*K.y;
    b = 2*K.x*x0+2*K.y*y0;
    c = x0*x0+y0*y0-r*r;
	delta = b*b-4*a*c;
    if(delta < 0.0)	return false;
    double t,t1,t2;
    if(delta == 0.0)
    {
		t = -b/(2*a);
        if((t < 0.0) || (t > dL))	return false;
        bOneIntersection = true;
        I1.x = p1.x+t*K.x;
        I1.y = p1.y+t*K.y;
 		return true;
    }
    double sqDelta = sqrt(delta);
	t1 = (-b-sqDelta)/(2*a);
	t2 = (-b+sqDelta)/(2*a);
    if((t1 >= 0.0) && (t1 <= dL) && (t2 >= 0.0) && (t2 <= dL))
    {
        bOneIntersection = false;
        if(t1 <= t2)
        {
            I1.x = p1.x+t1*K.x;
            I1.y = p1.y+t1*K.y;

            I2.x = p1.x+t2*K.x;
            I2.y = p1.y+t2*K.y;
        }
        else
        {
            I1.x = p1.x+t2*K.x;
            I1.y = p1.y+t2*K.y;

            I2.x = p1.x+t1*K.x;
            I2.y = p1.y+t1*K.y;
        }
 		return true;
    }
    else
    if((t1 >= 0.0) && (t1 <= dL))
    {
        bOneIntersection = true;
        I1.x = p1.x+t1*K.x;
        I1.y = p1.y+t1*K.y;
 		return true;
    }
    else
    if((t2 >= 0.0) && (t2 <= dL))
    {
        bOneIntersection = true;
        I1.x = p1.x+t2*K.x;
        I1.y = p1.y+t2*K.y;
 		return true;
    }
 	return false;
}
//---------------------------------------------------------------------------
bool shp_ExtrudeNode(double dStep,shp_Point &p0,shp_Point &p1,shp_Point &p2,shp_Point &p)
{
	p = p1;
	if(dStep == 0.0)	return false;
	shp_Point K,K1,K2,V1,V2;
    double dL,dL1,dL2,dNewStep,X,Y,dAngle;
    dL1 = shp_Distance(p1,p0);
    if(dL1 <= 0.0)	return false;
    dL2 = shp_Distance(p1,p2);
    if(dL2 <= 0.0)	return false;
    V1.x = (p0.x-p1.x);
    V1.y = (p0.y-p1.y);
    V2.x = (p2.x-p1.x);
    V2.y = (p2.y-p1.y);

	K1.x = V1.x/dL1;
	K1.y = V1.y/dL1;
	K2.x = V2.x/dL2;
	K2.y = V2.y/dL2;

	K.x = K1.x+K2.x;    
	K.y = K1.y+K2.y;    
    dL = sqrt(K.x*K.x+K.y*K.y);
    if(dL <= 0.0)	return false;
    K.x /= dL;
    K.y /= dL;

	X = V1.x*V2.x+V1.y*V2.y;
    Y = V1.x*V2.y-V1.y*V2.x;
    if(X == 0.0)
    {
        if(Y >= 0.0)
            dAngle = shp_PI2;
        else
            dAngle = -shp_PI2;
    }
    else
    {
        dAngle = ArcTan2(Y,X);
    }
	if(dAngle == 0.0)	return false;

    dNewStep = dStep/sin(dAngle/2.0);
    p.x = p1.x+K.x*dNewStep;
    p.y = p1.y+K.y*dNewStep;
    return true;
}
//---------------------------------------------------------------------------
bool shp_ExtrudeNode(double dStep,bool bStart,shp_Point &p0,shp_Point &p1,shp_Point &p)
{
    if(bStart)
		p = p0;
    else
		p = p1;
	if(dStep == 0.0)	return false;
	shp_Point K,K1,V1;
    double dL,dL1,dNewStep,X,Y,dAngle;
    dL1 = shp_Distance(p1,p0);
    if(dL1 <= 0.0)	return false;
    V1.x = (p0.x-p1.x);
    V1.y = (p0.y-p1.y);

	K1.x = V1.x/dL1;
	K1.y = V1.y/dL1;

	K.x = -K1.y;
	K.y = K1.x;    

    dNewStep = dStep/sin(shp_PI2);
    if(bStart)
    {
	    p.x = p0.x+K.x*dNewStep;
    	p.y = p0.y+K.y*dNewStep;
    }
    else
    {
	    p.x = p1.x+K.x*dNewStep;
    	p.y = p1.y+K.y*dNewStep;
    }
    return true;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void shp_CopyContour(shp_Contour &Dest,shp_Contour &Source)
{
	Dest.clear();
    for(UINT i=0;i<Source.size();i++)
    {
		Dest.push_back(Source[i]);
    }
}
//---------------------------------------------------------------------------
void shp_SaveContour(shp_Contour &Contour,AnsiString strFileName)
{
    TStringList *pList = new TStringList();
    shp_Point p;
    for(UINT i=0;i<Contour.size();i++)
    {
        p = Contour[i];
        pList->Add(FloatToStr(p.x)+" "+FloatToStr(p.y));  	
    }
    if(pList)
    {
        pList->SaveToFile(strFileName);
        delete pList;
        pList = NULL;
    }
}
//---------------------------------------------------------------------------
void shp_LoadContour(shp_Contour &Contour,AnsiString strFileName)
{
	Contour.clear();
    TStringList *pList = new TStringList();
    pList->LoadFromFile(strFileName);
    shp_Point p;
    AnsiString strText;
    int nPos;
    for(int i=0;i<pList->Count;i++)
    {
    	strText = pList->Strings[i].Trim();
        nPos = strText.Pos(" ");
        if(nPos <= 0)	continue;
		p.x = StrToFloat(strText.SubString(1,nPos-1));
        strText.Delete(1,nPos);
		p.y = StrToFloat(strText);
        Contour.push_back(p);
    }
    if(pList)
    {
        delete pList;
        pList = NULL;
    }
}
//---------------------------------------------------------------------------
/*
void shp_Adjust_Contour(shp_Contour &Contour,shp_Contour &ResContour)
{
	shp_Point p0,p,p1,p2,Pmin,Pmax;
    int nCount = Contour.size();
    double *pSeg = new double[nCount+1];
    double a,dS,dSmin,dSmax,dSeg,dSeg0;
    int Imin,Imax;

    for(int k=0;k<10;k++)
    {
        // Center
        p0.x = 0.0;
        p0.y = 0.0;
        for(int i=0;i<nCount;i++)
        {
            p = Contour[i];
            p0.x += p.x;
            p0.y += p.y;
        }
        p0.x /= nCount;
        p0.y /= nCount;

        // Convert Coordinates
        for(int i=0;i<nCount;i++)
        {
            p = Contour[i];
            p.x -= p0.x;
            p.y -= p0.y;
            Contour[i] = p;
        }

        pSeg[0] = 0.0;
        p1 = Contour[0];
        for(int i=1;i<nCount;i++)
        {
            p = Contour[i];
            pSeg[i] = pSeg[i-1]+shp_Distance(p1,p);
            p1 = p;
        }
        p = Contour[0];
        p1 = Contour[nCount-1];
        dSeg = pSeg[nCount-1]+shp_Distance(p1,p);
        pSeg[nCount] = dSeg;
        if(dSeg < 0.0)	return;
        for(int i=0;i<=nCount;i++)
        {
            pSeg[i] /= dSeg;
        }
        dSeg0 = 1.0/nCount;
		ResContour.clear();
        ResContour.push_back(Contour[0]);
        for(int i=1;i<nCount;i++)
        {
            dSeg = i*dSeg0;

            dSmin = +MaxInt;
            dSmax = -MaxInt;
            Imax = -1;
            Imin = -1;
            for(int j=0;j<=nCount;j++)
            {
                dS = pSeg[(j+nCount)%nCount];
                if((dS < dSeg) && (dS > dSmax))
                {
                    dSmax = dS;
                    Imax = j;
                }
                if((dS > dSeg) && (dS < dSmin))
                {
                    dSmin = dS;
                    Imin = j;
                }
            }
            if((Imax < 0) || (Imin < 0))
            {
            	dSmin = pSeg[nCount-1];
                dSmax = 1.0;
                Pmin = Contour[nCount-1];
                Pmax = Contour[0];
            }
            else
            {
                Pmin = Contour[(Imin+nCount)%nCount];
                Pmax = Contour[(Imax+nCount)%nCount];
            }
            a = (dSeg-dSmin)/(dSmax-dSmin);
            p.x = Pmin.x+a*(Pmax.x-Pmin.x);
            p.y = Pmin.y+a*(Pmax.y-Pmin.y);
            ResContour.push_back(p);
        }

        // for new iteration
        for(int i=0;i<nCount;i++)
        {
            Contour[i] = ResContour[i];
        }

        // Convert Coordinates
        for(int i=0;i<nCount;i++)
        {
            p = Contour[i];
            p.x += p0.x;
            p.y += p0.y;
            Contour[i] = p;
        }

        // Convert Coordinates
        for(int i=0;i<nCount;i++)
        {
            p = ResContour[i];
            p.x += p0.x;
            p.y += p0.y;
            ResContour[i] = p;
        }
    }

    if(pSeg)
    {
     	delete[] pSeg;
        pSeg = NULL;
    }
}
*/
//---------------------------------------------------------------------------
void shp_Adjust_Contour(shp_Contour &Contour,shp_Contour &ResContour)
{
	shp_Point p,p1,p2,Pmin,Pmax;
    int nCount = Contour.size();
    double *pSeg = new double[nCount+1];
    double a,dS,dSmin,dSmax,dSeg,dSeg0;
    int Imin,Imax;

    for(int k=0;k<1;k++)
    {
        pSeg[0] = 0.0;
        p1 = Contour[0];
        for(int i=1;i<nCount;i++)
        {
            p = Contour[i];
            pSeg[i] = pSeg[i-1]+shp_Distance(p1,p);
            p1 = p;
        }
        p = Contour[0];
        p1 = Contour[nCount-1];
        dSeg = pSeg[nCount-1]+shp_Distance(p1,p);
        pSeg[nCount] = dSeg;
        if(dSeg < 0.0)	return;
        for(int i=0;i<=nCount;i++)
        {
            pSeg[i] /= dSeg;
        }
        dSeg0 = 1.0/nCount;
		ResContour.clear();
        ResContour.push_back(Contour[0]);
        for(int i=1;i<nCount;i++)
        {
            dSeg = i*dSeg0;

            dSmin = +MaxInt;
            dSmax = -MaxInt;
            Imax = -1;
            Imin = -1;
            for(int j=0;j<=nCount;j++)
            {
                dS = pSeg[(j+nCount)%nCount];
                if((dS < dSeg) && (dS > dSmax))
                {
                    dSmax = dS;
                    Imax = j;
                }
                if((dS > dSeg) && (dS < dSmin))
                {
                    dSmin = dS;
                    Imin = j;
                }
            }
            if((Imax < 0) || (Imin < 0))
            {
            	dSmin = pSeg[nCount-1];
                dSmax = 1.0;
                Pmin = Contour[nCount-1];
                Pmax = Contour[0];
            }
            else
            {
                Pmin = Contour[(Imin+nCount)%nCount];
                Pmax = Contour[(Imax+nCount)%nCount];
            }
            a = (dSeg-dSmin)/(dSmax-dSmin);
            p.x = Pmin.x+a*(Pmax.x-Pmin.x);
            p.y = Pmin.y+a*(Pmax.y-Pmin.y);
            ResContour.push_back(p);
        }

        // for new iteration
        for(int i=0;i<nCount;i++)
        {
            Contour[i] = ResContour[i];
        }
    }

    if(pSeg)
    {
     	delete[] pSeg;
        pSeg = NULL;
    }
}
//---------------------------------------------------------------------------
void shp_Divide_Contour(double dStep,bool bLeaveLongSegments,shp_Contour &Contour,shp_Contour &ResContour)
{
	ResContour.clear();
	if(Contour.size() <= 0)	return;
    if(dStep <= 0.0)	return;
	shp_Point p0;
    shp_Point p1,p2;
    bool bOneIntersection;
    int nCount = Contour.size();
    shp_Point I1,I2;
    p0 = Contour[0];
    p1 = p0;
    ResContour.push_back(p0);
	for(int i=1;i<nCount;i++)
    {
     	p2 = Contour[i%nCount];

        if(bLeaveLongSegments)
        {
            if(shp_Distance(p1,p2) >= dStep)
            {
                p0 = p2;
                p1 = p0;
                ResContour.push_back(p0);
                continue;
            }
        }

        while(shp_Intersect_Circle_Segment(p0,dStep,p1,p2,bOneIntersection,I1,I2))
        {
            p0 = I1;
            p1 = p0;
            ResContour.push_back(p0);

            if(bLeaveLongSegments)
            {
                if(shp_Distance(p1,p2) >= dStep)
                {
                    p0 = p2;
                    p1 = p0;
                    ResContour.push_back(p0);
                    break;
                }
            }
        }
        p1 = p2;
    }
}
//---------------------------------------------------------------------------
static shp_Contour *_piPoly;
static shp_Contour *_poPoly;
static shp_Point _p;
static shp_Point _p1;
static shp_Point _p2;
static double _Epsilon2;
static double _J;
static double _d;
static double _MaxD;
static double _D;
static double _L;
//---------------------------------------------------------------------------
void Assemple(DWORD i1,DWORD i2)
{
    if(i2<=i1)	return;

    // Get _p1, _p2
    _p1=(*_piPoly)[i1];
    _p2=(*_piPoly)[i2];

    // Get _J, i3
    DWORD i3;
    _J=0.0f;
    _MaxD=-MaxInt;
    for(DWORD i=i1;i<=i2;i++)
    {
        _p=(*_piPoly)[i];

        if(_p2.x==_p1.x)// (Vertical Line)
            _d=(_p.x-_p1.x);
        else
        if(_p2.y==_p1.y)// (Horizontal Line)
            _d=(_p.y-_p1.y);
        else              // (Any Line)
        {
            _L=shp_Distance(_p1,_p2);
            if(_L>0.0f)
                _d=fabs(((_p.x-_p1.x)*(_p2.y-_p1.y)-(_p.y-_p1.y)*(_p2.x-_p1.x))/_L);
            else
                _d=shp_Distance(_p1,_p);
        } 
        _D=_d*_d;

        _J+=_D;
        if(_D>_MaxD)
        {
            _MaxD=_D;
            i3=i;
        }
    }

    // Assemble
    if(_J<=_Epsilon2)
    {
        (*_poPoly).push_back((*_piPoly)[i1]);
    }
    else
    {
        Assemple(i1,i3);
        Assemple(i3,i2);
    }
}
//---------------------------------------------------------------------------
void shp_FindBestContour(double dEpsilon,shp_Contour &iContour,shp_Contour &oContour)
{
	oContour.clear();
    if(iContour.empty())  	return;

    // Initialize Global
    _piPoly = &iContour;
    _poPoly = &oContour;
    _Epsilon2 = dEpsilon*dEpsilon;

    // Call Recursive Procedure
    Assemple(0,iContour.size()-1);

    // Add Last Point
    oContour.push_back(iContour[iContour.size()-1]);
}
//---------------------------------------------------------------------------
void shp_FindBestStartPoint(shp_Contour &Contour,int &nIndex)
{
	nIndex = 0;
    int nCount = Contour.size();
    if(nCount <= 0)	return;
	shp_Point p0,p1,p2;
    double dAngle;
    double dDiff,dMinDiff;
    dMinDiff = MaxInt;
    p1 = Contour[nCount-1];
    p0 = Contour[0];
	for(int i=1;i<=nCount;i++)
    {
     	p2 = Contour[i%nCount];
		dAngle = shp_Angle_Rad(p0,p1,p2);
        dDiff = abs(abs(dAngle)-shp_PI);
        if(!shp_IsClockwiseVertex(p1,p0,p2))
        {
            if(dDiff < dMinDiff)
            {
                dMinDiff = dDiff;
                nIndex = i;
            }
        }
        p1 = p0;
        p0 = p2;
    }
}
//---------------------------------------------------------------------------
void shp_SetContourStartPoint(shp_Contour &Contour,int nIndex)
{
	int nCount = Contour.size();
    if(nCount <= 0)	return;
    if((nIndex <= 0) || (nIndex >= nCount))	return;
    shp_Contour Temp;
	for(int i=0;i<nCount;i++)	Temp.push_back(Contour[(i+nIndex)%nCount]);
    Contour.clear();
	for(int i=0;i<nCount;i++)	Contour.push_back(Temp[i]);
}
//---------------------------------------------------------------------------
void shp_AutoSetContourStartPoint(shp_Contour &Contour)
{
	if(Contour.empty())	return;
    int nIndex;
    shp_FindBestStartPoint(Contour,nIndex);
	shp_SetContourStartPoint(Contour,nIndex);
}
//---------------------------------------------------------------------------
void shp_Contour_Center(shp_Contour &Contour,double &x0,double &y0)
{
	if(Contour.empty())	return;
	int nCount = Contour.size();
	shp_Point p;
    x0 = 0.0;
    y0 = 0.0;
	for(int i=0;i<nCount;i++)
    {
     	p = Contour[i];
        x0 += p.x;
        y0 += p.y;
    }
    x0 /= nCount;
    y0 /= nCount;
}
//---------------------------------------------------------------------------
void shp_Smooth_Contour(double dStep,AnsiString strFileName,AnsiString strNewFileName)
{
	shp_Contour Contour,ResContour;
    shp_LoadContour(Contour,strFileName);
	if(Contour.empty())	return;

	shp_AutoSetContourStartPoint(Contour);
	shp_Divide_Contour(dStep,false,Contour,ResContour);

    shp_SaveContour(ResContour,strNewFileName);
}
//---------------------------------------------------------------------------
void shp_Contour_Remove_Repeated_Points(double dEpsilon,shp_Contour &Contour)
{
	if(Contour.empty())	return;
	int nCount;
	shp_Point p,op;
    op = Contour[0];                
	for(UINT i=1;i<=Contour.size();)
    {
    	nCount = Contour.size();
     	p = Contour[i%nCount];
        if(shp_Distance(op,p) <= dEpsilon)
        {
			Contour.erase(&Contour[i%nCount]);
        }
        else
        {
        	op = p;
			i++;
        }
    }
}
//---------------------------------------------------------------------------
void shp_Extrude_Contour(double dStep,bool bClosed,shp_Contour &Contour,shp_Contour &Extrude)
{
    Extrude.clear();
    shp_Contour_Remove_Repeated_Points(g_dEpsilon,Contour);
    int nCount = Contour.size();
    if(nCount < 2) 	return;
    shp_Point p;
    if(bClosed)
    {
        for(int i=0;i<nCount;i++)
        {
            if(shp_ExtrudeNode(dStep,Contour[(i-1+nCount)%nCount],Contour[(i+0+nCount)%nCount],Contour[(i+1+nCount)%nCount],p))
            {
            	Extrude.push_back(p);
            }
        }
    }
    else
    {
        shp_ExtrudeNode(dStep,true,Contour[0],Contour[1],p);
        Extrude.push_back(p);
        for(int i=0+1;i<nCount-1;i++)
        {
            if(shp_ExtrudeNode(dStep,Contour[(i-1+nCount)%nCount],Contour[(i+0+nCount)%nCount],Contour[(i+1+nCount)%nCount],p))
            {
                Extrude.push_back(p);
            }
        }
        shp_ExtrudeNode(dStep,false,Contour[nCount-2],Contour[nCount-1],p);
        Extrude.push_back(p);
    }
}
//---------------------------------------------------------------------------

