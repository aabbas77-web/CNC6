//---------------------------------------------------------------------------
#ifndef shp_ImageH
#define shp_ImageH
//---------------------------------------------------------------------------
#include <Graphics.hpp>
#include <JPEG.hpp>
#include "shp_Types.h"
//---------------------------------------------------------------------------
// Support: 1,8,16,24,32 Bits Images
// Data Stored As:
// 0 1 2 3 4 5 6 7 8 9 ...

// In R Mode (1 And 8 bits):
// R R R R R R R R R R ...

// In RGB Mode (16 bits):(C= Contour Index)
// C C C C C C C C C C ...

// In RGB Mode (24 bits):
// B G R B G R B G R ...

// In RGBI Mode (32 bits):(I: Color Index)
// I B G R I B G R I B G R ...
//---------------------------------------------------------------------------
#define shp_GetPixel_1bit(x,y,pImage) ((((pImage)->ppLines[(y)][(x)>>3])&(0x80>>((x)&0x7)))!=0)
#define shp_SetPixel_1bit(x,y,Color,pImage) (Color ? ((pImage)->ppLines[(y)][(x)>>3] |= (0x80>>((x) & 0x7))) : ((pImage)->ppLines[(y)][(x)>>3] &= (0xff7f>>((x) & 0x7))))
//---------------------------------------------------------------------------
#define shp_GetIValue32(rgbi) ( (Byte)((UINT)(rgbi) >> 24) )
#define shp_GetBValue32(rgbi) ( (Byte)((UINT)(rgbi) >> 16) )
#define shp_GetGValue32(rgbi) ( (Byte)((UINT)(rgbi) >> 8 ) )
#define shp_GetRValue32(rgbi) ( (Byte)((UINT)(rgbi)      ) )
//---------------------------------------------------------------------------
#define shp_RGBI32(r,g,b,i) ( ((UINT)((Byte)(r))) | ((UINT)((Byte)(g)) << 8) | ((UINT)((Byte)(b)) << 16) | ((UINT)((Byte)(i)) << 24) )
//---------------------------------------------------------------------------
#define shp_GetLoWord(dw) ( (Word)((UINT)(dw)      ) )
#define shp_GetHiWord(dw) ( (Word)((UINT)(dw) >> 16) )
//---------------------------------------------------------------------------
#define DWORD(lw,hw)  ( ((UINT)((Word)(lw))) | ((UINT)((Word)(hw)) << 16) )
//---------------------------------------------------------------------------
#define shp_GetLoByte(w) ( (Byte)((Word)(w)     ) )
#define shp_GetHiByte(w) ( (Byte)((Word)(w) >> 8) )
//---------------------------------------------------------------------------
#define Word(lb,hb)  ( ((Word)((Byte)(lb))) | ((Word)((Byte)(hb)) << 8) )
//---------------------------------------------------------------------------
typedef struct
{
    TLogPalette lpal;
    TPaletteEntry dummy[260];
} LogPal;
//---------------------------------------------------------------------------
class shp_Image
{
    private:
        void Allocate();
        void DeAllocate();
//        void UpdateLines();
    public:
        shp_Image();
        ~shp_Image();

        // Read Only Properties
        Graphics::TBitmap *pBitmap;
        Byte **ppLines;
        UINT Width;// In Pixel
        UINT Height;// In Pixel
        Byte Border;
        UINT LineSize;// In Byte
        UINT ImageSize;// In Byte (Including Zero Padding)
        Byte Bits;// (1,8,16,24,32) <Default = 1>
        bool Updated;// (Read Only)

        // Call <UpdateLines> After Any Change in Data Size
        // Then (ppLines) Became Available
        // After:
        // 1- Changing Image (Width,Height,PixelFormat)
        // 2- Loading Image
        // 3- Assign Image
        // 3- Changing Image Palette
        void UpdateLines();

        void LoadFromFile(AnsiString FileName);
        void LoadFromFile(AnsiString FileName,TPixelFormat pf);
        void SaveToFile(AnsiString FileName);
        void Assign(shp_Image *pImage);
        void Assign(shp_Image *pImage,UINT W,UINT H);
        void Assign(shp_Image *pImage,TPixelFormat pf);
        void Assign(shp_Image *pImage,UINT W,UINT H,TPixelFormat pf);
        void Assign(TPersistent *pSource);
        void SetWidth(UINT W);
        void SetHeight(UINT H);
        void SetSize(UINT W,UINT H);
        void SetPixelFormat(TPixelFormat pf);
        void SetAll(UINT W,UINT H,TPixelFormat pf);
        void SetFrame(UINT W,UINT Color);
        void Clear();
        void AutoFrame(Byte Border,bool MaxMethode);
		void CreateMonochromePalette();
};
//---------------------------------------------------------------------------
#endif
