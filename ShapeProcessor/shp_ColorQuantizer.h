//---------------------------------------------------------------------------
#ifndef shp_ColorQuantizerH
#define shp_ColorQuantizerH
//---------------------------------------------------------------------------
#include "shp_Image.h"
//---------------------------------------------------------------------------
// SHP Scan Line
//---------------------------------------------------------------------------
// B G R    B G R   B G R   ..
// 0 1 2    3 4 5   6 7 8   ..
//---------------------------------------------------------------------------
class shp_ColorQuantizer
{
private:
	Byte m_nColorsCount;
public:
	shp_ColorQuantizer();
    ~shp_ColorQuantizer();

	TColor pColors[256];
	Byte pPalette[768];
    shp_Image *m_pImage;

	// 1<= ColorsCount <= 256
	// pIndices: (8 bits) Image That Contain Colors Indices
	// Where: [0 <=  Indices  < ColorsCount]
	void Assign(shp_Image *pImage);
	void Quantize(UINT nColorsCount,bool bCreatePalette,bool bFullPalette);
    __property Byte ColorsCount = {read = m_nColorsCount};
};
//---------------------------------------------------------------------------
#endif
