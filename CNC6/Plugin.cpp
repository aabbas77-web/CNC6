//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Plugin.h"
#include <stdio.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
TPlugin::TPlugin()
{
	m_bLoaded = false;
    hLib = NULL;
}
//---------------------------------------------------------------------------
TPlugin::~TPlugin()
{
	Free();
}
//---------------------------------------------------------------------------
void TPlugin::LoadFromFile(AnsiString FileName)
{
 	try
  	{
		Free();
   		hLib=LoadLibrary(FileName.c_str());
   		if(hLib==NULL)
    	{
     		m_bLoaded=false;
     		return;
    	}
   		m_bLoaded=true;
		m_func_ShowModalInterface=(TFunc_ShowModalInterface)GetProcAddress(hLib,"_plug_ShowModalInterface");
        m_func_ShowInterface=(TFunc_ShowInterface)GetProcAddress(hLib,"_plug_ShowInterface");
        m_func_CloseInterface=(TFunc_CloseInterface)GetProcAddress(hLib,"_plug_CloseInterface");
        m_func_About=(TFunc_About)GetProcAddress(hLib,"_plug_About");
        m_func_GetIcon=(TFunc_GetIcon)GetProcAddress(hLib,"_plug_GetIcon");
        m_func_GetName=(TFunc_GetName)GetProcAddress(hLib,"_plug_GetName");
        m_func_GetHint=(TFunc_GetHint)GetProcAddress(hLib,"_plug_GetHint");
        m_func_GetVersion=(TFunc_GetVersion)GetProcAddress(hLib,"_plug_GetVersion");
        m_func_GetAuthorName=(TFunc_GetAuthorName)GetProcAddress(hLib,"_plug_GetAuthorName");
        m_func_GetDate=(TFunc_GetDate)GetProcAddress(hLib,"_plug_GetDate");
        m_func_GetGroup=(TFunc_GetGroup)GetProcAddress(hLib,"_plug_GetGroup");
        m_func_GetShortCut=(TFunc_GetShortCut)GetProcAddress(hLib,"_plug_GetShortCut");
        m_func_Initialize=(TFunc_Initialize)GetProcAddress(hLib,"_plug_Initialize");
        m_func_Draw=(TFunc_Draw)GetProcAddress(hLib,"_plug_Draw");
  	}
 	catch(...)
  	{
    	return;
  	}
}
//---------------------------------------------------------------------------
void TPlugin::Free()
{
 	try
  	{
	 	if(!m_bLoaded)	return;
        hLib = NULL;
        m_bLoaded=false;
  	}
 	catch(...)
  	{
    	return;
  	}
}
//---------------------------------------------------------------------------
int TPlugin::ShowModalInterface()
{
	try
    {
	 	if(!m_bLoaded) return mrCancel;
        if(m_func_ShowModalInterface == NULL)	return mrCancel;
        return (*m_func_ShowModalInterface)();
	}
    catch(...)
    {
    	return mrCancel;
    }
}
//---------------------------------------------------------------------------
void TPlugin::ShowInterface()
{
	try
    {
	 	if(!m_bLoaded) return;
    	if(m_func_ShowInterface == NULL)	return;
        (*m_func_ShowInterface)();
	}
    catch(...)
    {
    	return;
    }
}
//---------------------------------------------------------------------------
void TPlugin::CloseInterface()
{
	try
    {
	 	if(!m_bLoaded) return;
        if(m_func_CloseInterface == NULL)	return;
        (*m_func_CloseInterface)();
	}
    catch(...)
    {
    	return;
    }
}
//---------------------------------------------------------------------------
void TPlugin::About()
{
	try
    {
	 	if(!m_bLoaded) return;
        if(m_func_About == NULL)	return;
        (*m_func_About)();
	}
    catch(...)
    {
    	return;
    }
}
//---------------------------------------------------------------------------
void TPlugin::GetIcon(Graphics::TBitmap *pIcon)
{
	try
    {
	 	if(!m_bLoaded) return;
        if(m_func_GetIcon == NULL)	return;
        (*m_func_GetIcon)(pIcon);
	}
    catch(...)
    {
    	return;
    }
}
//---------------------------------------------------------------------------
char *TPlugin::GetName()
{
	try
    {
	 	if(!m_bLoaded) return "";
        if(m_func_GetName == NULL)	return "";
        return (*m_func_GetName)();
	}
    catch(...)
    {
    	return "";
    }
}
//---------------------------------------------------------------------------
char *TPlugin::GetHint()
{
	try
    {
	 	if(!m_bLoaded) return "";
        if(m_func_GetHint == NULL)	return "";
        return (*m_func_GetHint)();
	}
    catch(...)
    {
    	return "";
    }
}
//---------------------------------------------------------------------------
char *TPlugin::GetVersion()
{
	try
    {
	 	if(!m_bLoaded) return "";
        if(m_func_GetVersion == NULL)	return "";
        return (*m_func_GetVersion)();
	}
    catch(...)
    {
    	return "";
    }
}
//---------------------------------------------------------------------------
char *TPlugin::GetAuthorName()
{
	try
    {
	 	if(!m_bLoaded) return "";
        if(m_func_GetAuthorName == NULL)	return "";
        return (*m_func_GetAuthorName)();
	}
    catch(...)
    {
    	return "";
    }
}
//---------------------------------------------------------------------------
char *TPlugin::GetDate()
{
	try
    {
	 	if(!m_bLoaded) return "";
        if(m_func_GetDate == NULL)	return "";
        return (*m_func_GetDate)();
	}
    catch(...)
    {
    	return "";
    }
}
//---------------------------------------------------------------------------
char *TPlugin::GetGroup()
{
	try
    {
	 	if(!m_bLoaded) return "";
        if(m_func_GetGroup == NULL)	return "";
        return (*m_func_GetGroup)();
	}
    catch(...)
    {
    	return "";
    }
}
//---------------------------------------------------------------------------
TShortCut TPlugin::GetShortCut()
{
	try
    {
	 	if(!m_bLoaded) return ShortCut(Word(' '), TShiftState() << ssCtrl);
        if(m_func_GetShortCut == NULL)	return ShortCut(Word(' '), TShiftState() << ssCtrl);
        return (*m_func_GetShortCut)();
	}
    catch(...)
    {
    	return ShortCut(Word(' '), TShiftState() << ssCtrl);
    }
}
//---------------------------------------------------------------------------
void TPlugin::Initialize(TFunc_Redraw f_Redraw,TFunc_DrawLine func_DrawLine,
				TFunc_DrawPolyline func_DrawPolyline,TFunc_DrawPolygon func_DrawPolygon,
                TFunc_DrawCircle func_DrawCircle,TFunc_DrawArc func_DrawArc,
                TFunc_DrawEllipse func_DrawEllipse,TFunc_DrawText func_DrawText,
                TFunc_AddLine func_AddLine,TFunc_AddCircle func_AddCircle,
                TFunc_AddCircle3P func_AddCircle3P,TFunc_AddArc func_AddArc,
                TFunc_AddArc3P func_AddArc3P,TFunc_AddEllipse func_AddEllipse,
                TFunc_AddArcEx func_AddArcEx,TFunc_SetTextParam func_SetTextParam,
                TFunc_SetTextParams func_SetTextParams,TFunc_AddText func_AddText,
                TFunc_PolylineBegin func_PolylineBegin,TFunc_Vertex func_Vertex,
                TFunc_VertexR func_VertexR,TFunc_VertexF func_VertexF,
                TFunc_VertexB func_VertexB,TFunc_AddPolyline func_AddPolyline,
                TFunc_AddRect func_AddRect)
{
	try
    {
	 	if(!m_bLoaded) return;
        if(m_func_Initialize == NULL)	return;
        (*m_func_Initialize)(f_Redraw,func_DrawLine,
                func_DrawPolyline,func_DrawPolygon,
                func_DrawCircle,func_DrawArc,
                func_DrawEllipse,func_DrawText,
                func_AddLine,func_AddCircle,
                func_AddCircle3P,func_AddArc,
                func_AddArc3P,func_AddEllipse,
                func_AddArcEx,func_SetTextParam,
                func_SetTextParams,func_AddText,
                func_PolylineBegin,func_Vertex,
                func_VertexR,func_VertexF,
                func_VertexB,func_AddPolyline,
                func_AddRect);
	}
    catch(...)
    {
    	return;
    }
}
//---------------------------------------------------------------------------
int TPlugin::Draw(int Msg,int Step,double x,double y)
{
	try
    {
	 	if(!m_bLoaded) return false;
        if(m_func_Draw == NULL)	return false;
        return (*m_func_Draw)(Msg,Step,x,y);
	}
    catch(...)
    {
    	return false;
    }
}
//---------------------------------------------------------------------------

