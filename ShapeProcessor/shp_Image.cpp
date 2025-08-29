//---------------------------------------------------------------------------
#include <vcl.h>
#include <vector.h>
#include <set.h>
#include <Algorithms.h>
//---------------------------------------------------------------------------
#pragma hdrstop
//---------------------------------------------------------------------------
#include "shp_Image.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
shp_Image::shp_Image()
{
    pBitmap=new Graphics::TBitmap();
    Width=0;
    Height=0;
    Bits=1;
    LineSize=0;
    ImageSize=0;
    ppLines=NULL;
    Updated=false;
}
//---------------------------------------------------------------------------
shp_Image::~shp_Image()
{
    DeAllocate();
    if(pBitmap)     delete pBitmap;
}
//---------------------------------------------------------------------------
void shp_Image::Allocate()
{
    if(Height!=0)
    {
        ppLines=new Byte*[Height];
    }
}
//---------------------------------------------------------------------------
void shp_Image::DeAllocate()
{
    if(ppLines)
    {
        delete[] ppLines;
        ppLines=NULL;
    }
}
//---------------------------------------------------------------------------
void shp_Image::UpdateLines()
{
        Updated=false;
        if(Width!=(UINT)pBitmap->Width)
        {
            Width=pBitmap->Width;
            Updated=true;
        }
        if(Height!=(UINT)pBitmap->Height)
        {
            Height=pBitmap->Height;
            Updated=true;
        }
        switch(pBitmap->PixelFormat)
        {
            case pf1bit:
            {
                if(Bits!=1)
                {
                    Bits=1;
                    Updated=true;
                }
                break;
            }
            case pf8bit:
            {
                if(Bits!=8)
                {
                    Bits=8;
                    Updated=true;
                }
                break;
            }
            case pf16bit:
            {
                if(Bits!=16)
                {
                    Bits=16;
                    Updated=true;
                }
                break;
            }
            case pf24bit:
            {
                if(Bits!=24)
                {
                    Bits=24;
                    Updated=true;
                }
                break;
            }
            case pf32bit:
            {
                if(Bits!=32)
                {
                    Bits=32;
                    Updated=true;
                }
                break;
            }
            default:
            {
                if(Bits!=1)
                {
                    Bits=1;
                    Updated=true;
                }
                break;
            }
        }

        if(Updated)
        {
            if(Width*Bits % 8 ==0)
                LineSize=Width*Bits/8;
            else
                LineSize=Width*Bits/8+1;
            ImageSize=LineSize*Height;

            DeAllocate();
            Allocate();
        }

        for(UINT y=0;y<Height;y++)
        {
            ppLines[y]=(Byte *)pBitmap->ScanLine[y];
        }
}
//---------------------------------------------------------------------------
void shp_Image::LoadFromFile(AnsiString FileName)
{
    TPicture *pPicture=new TPicture();
    pPicture->LoadFromFile(FileName);
    pBitmap->Assign(pPicture->Graphic);
    UpdateLines();
    if(pPicture)    delete pPicture;pPicture=NULL;
}
//---------------------------------------------------------------------------
void shp_Image::LoadFromFile(AnsiString FileName,TPixelFormat pf)
{
    LoadFromFile(FileName);
    pBitmap->PixelFormat=pf;
    UpdateLines();
}
//---------------------------------------------------------------------------
void shp_Image::SaveToFile(AnsiString FileName)
{
	if(UpperCase(FileName).Pos(".JPG") > 0)
    {
		TJPEGImage *pJPEG = new TJPEGImage();
		pJPEG->Assign(pBitmap);
        pJPEG->SaveToFile(FileName);
        if(pJPEG)
        {
         	delete pJPEG;
            pJPEG = NULL;
        }
    }
    else// BMP
    {
    	pBitmap->SaveToFile(ChangeFileExt(FileName,".bmp"));
    }
}
//---------------------------------------------------------------------------
void shp_Image::Assign(shp_Image *pImage)
{
    pBitmap->Assign(pImage->pBitmap);
    UpdateLines();
}
//---------------------------------------------------------------------------
void shp_Image::Assign(shp_Image *pImage,UINT W,UINT H)
{
    pBitmap->Assign(pImage->pBitmap);
    pBitmap->Width=W;
    pBitmap->Height=H;
    UpdateLines();
}                      
//---------------------------------------------------------------------------
void shp_Image::Assign(shp_Image *pImage,TPixelFormat pf)
{
    pBitmap->Assign(pImage->pBitmap);
    pBitmap->PixelFormat=pf;
    UpdateLines();
}
//---------------------------------------------------------------------------
void shp_Image::Assign(shp_Image *pImage,UINT W,UINT H,TPixelFormat pf)
{
    pBitmap->Assign(pImage->pBitmap);
    pBitmap->Width=W;
    pBitmap->Height=H;
    pBitmap->PixelFormat=pf;
    UpdateLines();
}
//---------------------------------------------------------------------------
void shp_Image::Assign(TPersistent *pSource)
{
    pBitmap->Assign(pSource);
    UpdateLines();
}
//---------------------------------------------------------------------------
void shp_Image::SetWidth(UINT W)
{
    pBitmap->Width=W;
    UpdateLines();
}
//---------------------------------------------------------------------------
void shp_Image::SetHeight(UINT H)
{
    pBitmap->Height=H;
    UpdateLines();
}
//---------------------------------------------------------------------------
void shp_Image::SetSize(UINT W,UINT H)
{
    pBitmap->Width=W;
    pBitmap->Height=H;
    UpdateLines();
}
//---------------------------------------------------------------------------
void shp_Image::Clear()
{
    pBitmap->Width=0;
    pBitmap->Height=0;
    UpdateLines();
}
//---------------------------------------------------------------------------
void shp_Image::SetPixelFormat(TPixelFormat pf)
{
    pBitmap->PixelFormat=pf;
    UpdateLines();
}
//---------------------------------------------------------------------------
void shp_Image::SetAll(UINT W,UINT H,TPixelFormat pf)
{
    pBitmap->Width=W;
    pBitmap->Height=H;
    pBitmap->PixelFormat=pf;
    UpdateLines();
}
//---------------------------------------------------------------------------
void shp_Image::SetFrame(UINT W,UINT Color)
{
    pBitmap->Canvas->Pen->Color=TColor(Color);
    pBitmap->Canvas->Pen->Width=W;
    pBitmap->Canvas->Brush->Style=bsClear;

    UINT w2=W/2;
    UINT d=1-W % 2;
    pBitmap->Canvas->Rectangle(0+w2,0+w2,Width+d-w2,Height+d-w2);
}
//---------------------------------------------------------------------------
void shp_Image::AutoFrame(Byte Border,bool MaxMethode)
{
    this->Border=Border;
    if(Border==0)
        return;

    // Auto Frame
    vector<UINT> vColors;// Repeated Colors
    set<UINT> sColors;// Set Of Not Repeated Colors
    vector<UINT> oColors;// Not Repeated Colors
    for(UINT y=0;y<Height;y++)
    {
        vColors.push_back(pBitmap->Canvas->Pixels[0][y]);
        vColors.push_back(pBitmap->Canvas->Pixels[Width-1][y]);
    }
    for(UINT x=0;x<Width;x++)
    {
        vColors.push_back(pBitmap->Canvas->Pixels[x][0]);
        vColors.push_back(pBitmap->Canvas->Pixels[x][Height-1]);
    }
    for(UINT i=0;i<vColors.size();i++)
    {
        sColors.insert(vColors[i]);
    }
    copy(sColors.begin(),sColors.end(),back_inserter(oColors));

    UINT Count;
    if(MaxMethode)
    {
        UINT MaxCount=0,MaxIndex=0;
        for(UINT i=0;i<oColors.size();i++)
        {
            count(vColors.begin(),vColors.end(),oColors[i],Count);
            if(Count>MaxCount)
            {
                MaxCount=Count;
                MaxIndex=i;
            }
        }
        pBitmap->Canvas->Brush->Color=(TColor)oColors[MaxIndex];
    }
    else
    {
        UINT MinCount=MaxInt,MinIndex=MaxInt;
        for(UINT i=0;i<oColors.size();i++)
        {
            count(vColors.begin(),vColors.end(),oColors[i],Count);
            if(Count<MinCount)
            {
                MinCount=Count;
                MinIndex=i;
            }
        }
        pBitmap->Canvas->Brush->Color=(TColor)oColors[MinIndex];
    }

    Graphics::TBitmap *pTemp=new Graphics::TBitmap();
    pTemp->Assign(pBitmap);
    SetSize(Width+2*Border,Height+2*Border);
    pBitmap->Canvas->Brush->Style=bsSolid;
    pBitmap->Canvas->FillRect(Rect(0,0,pBitmap->Width,pBitmap->Height));
    pBitmap->Canvas->Draw(Border,Border,pTemp);
    if(pTemp)
        delete pTemp;
}
//---------------------------------------------------------------------------
void shp_Image::CreateMonochromePalette()
{
    // Create Palette
    LogPal SysPal;
    FillMemory(SysPal.lpal.palPalEntry,256,PC_RESERVED);
    SysPal.lpal.palVersion = 0x300;
    SysPal.lpal.palNumEntries = 2;

    SysPal.lpal.palPalEntry[0].peRed=0;
    SysPal.lpal.palPalEntry[0].peGreen=0;
    SysPal.lpal.palPalEntry[0].peBlue=0;
    SysPal.lpal.palPalEntry[0].peFlags=PC_RESERVED;

    SysPal.lpal.palPalEntry[1].peRed=255;
    SysPal.lpal.palPalEntry[1].peGreen=255;
    SysPal.lpal.palPalEntry[1].peBlue=255;
    SysPal.lpal.palPalEntry[1].peFlags=PC_RESERVED;

    SetPixelFormat(pf8bit);
    pBitmap->Palette=::CreatePalette(&SysPal.lpal);
    UpdateLines();
}
//---------------------------------------------------------------------------

