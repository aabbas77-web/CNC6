//---------------------------------------------------------------------------
#ifndef shp_TypesH
#define shp_TypesH
//---------------------------------------------------------------------------
#include <vector.h>
//---------------------------------------------------------------------------
// Usefull Defines
//---------------------------------------------------------------------------
#define     shp_MaxInt          (2147483647.0) // 2^31 - 1
#define     shp_MaxWord         (65535.0) // 2^16 - 1
#define     shp_MaxImageWidth   (10000.0) 
#define     shp_DisiemPerInch   (254.00050800101600203200406400813)
#define     shp_sqrt2           (1.4142135623730950488016887242097)
#define     shp_sqrt1_2         (0.70710678118654752440084436210485)
#define     shp_PI              (3.1415926535897932384626433832795)
#define     shp_Sign(x)         (((x)>0.0)?1.0:(((x)<0.0)?-1.0:0.0))
#define     shp_Round(x)        ((((x)-int(x))>=0.5)?(int(x)+1):(int(x)))
#define     shp_ABS(x)		    (((x)<0)?-(x):(x))
#define     shp_MIN(a,b)	    (((a)<(b))?(a):(b))
#define     shp_MAX(a,b)	    (((a)>(b))?(a):(b))	
//---------------------------------------------------------------------------
#define     shp_ByteToComp(b)       ((b)<=127)?(b):(b)-256)
#define     shp_CompToByte(b)       ((b)>=0)?(b):(b)+256)
//---------------------------------------------------------------------------
const int   shp_Power2[8]={1,2,4,8,16,32,64,128};
//---------------------------------------------------------------------------
#define     shp_GetBit(b,i)     ((b) &    shp_Power2[(i)])
#define     shp_SetBit(b,i)     ((b) |=   shp_Power2[(i)])
#define     shp_ClrBit(b,i)     ((b) &= (~shp_Power2[(i)]))
//---------------------------------------------------------------------------
struct shp_RGB
{
    Byte r;
    Byte g;
    Byte b;
    bool operator == (const shp_RGB &Color)
    {
        return ((r == Color.r) && (g == Color.g) && (b == Color.b));
    }
    bool operator != (const shp_RGB &Color)
    {
        return ((r != Color.r) || (g != Color.g) || (b != Color.b));
    }
};
//---------------------------------------------------------------------------
typedef vector<Byte> shp_ByteArray;
typedef vector<int> shp_IntArray;
typedef vector<double> shp_DoubleArray;
//---------------------------------------------------------------------------
#endif
