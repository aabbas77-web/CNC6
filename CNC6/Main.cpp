//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.hpp>
#include <inifiles.hpp>
#include <fileCtrl.hpp>
#pragma hdrstop

#include "Main.h"
#include "About.h"
#include "cadapi.h"
#include "Options.h"
#include "Simulator.h"
#include "Export.h"
/*
#include "quilt_Messages.h"
#include "Properties.h"
*/
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "FormTranslation"
#pragma link "CSPIN"
#pragma resource "*.dfm"
TFormMain *FormMain;
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FindPlugins(TStringList *pFiles)
{
 	TSearchRec SR;
 	int iAttributes = 0;
    AnsiString strPath = IncludeTrailingBackslash(ExtractFilePath(Application->ExeName))+"Plugins\\";
	ForceDirectories(strPath);    
 	iAttributes |= faArchive | faAnyFile;
    pFiles->Clear();
 	if(FindFirst(strPath+"*.dll",iAttributes,SR)==0)
  	{
   		do
    	{
     		if((SR.Attr & iAttributes) == SR.Attr)
      			pFiles->AddObject(IncludeTrailingBackslash(strPath)+SR.Name,NULL);
    	}
        while(FindNext(SR) == 0);
   		FindClose(SR);
  	}
}    
//---------------------------------------------------------------------------
void __fastcall TFormMain::DoClickPlugin(TObject *Sender)
{
/*
	if(Sender == NULL)	return;
    nCurrPluginIndex = (dynamic_cast<TMenuItem *>(Sender))->Tag;
    TPlugin *pPlugin;
    pPlugin = (TPlugin *)pPlugins->Objects[nCurrPluginIndex];
    if(pPlugin == NULL)	return;
    if(pPlugin->ShowModalInterface() != mrOk)	return;
    vlExecute(spl_CMD_PLUG_IN);
*/
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ClearPlugins()
{
/*
    TPlugin *pPlugin;
    for(int i=0;i<pPlugins->Count;i++)
    {
     	pPlugin = (TPlugin *)pPlugins->Objects[i];
        if(pPlugin)
        {
         	delete pPlugin;
            pPlugin = NULL;
        }
    }
    pPlugins->Clear();
*/
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::UpdatePlugins()
{
/*
	ClearPlugins();
    FindPlugins(pPlugins);

    TPlugin *pPlugin;
    TMenuItem *pItem;
    TMenuItem *pGroupItem;
    AnsiString strGroupName;
    bool bGroupFound;
    Plugin1->Visible = (pPlugins->Count > 0);
    Plugin1->Clear();
    for(int i=0;i<pPlugins->Count;i++)
    {
    	pItem = new TMenuItem(this);

        pPlugin = new TPlugin();
		pPlugin->LoadFromFile(pPlugins->Strings[i]);
        pPlugin->GetIcon(pItem->Bitmap);
		pPlugin->Initialize(vlRedraw,vlDrawLine,vlDrawPolyline,vlDrawPolygon,
                vlDrawCircle,vlDrawArc,vlDrawEllipse,vlDrawText,
                vlAddLine,vlAddCircle,vlAddCircle3P,vlAddArc,
                vlAddArc3P,vlAddEllipse,vlAddArcEx,vlSetTextParam,
                vlSetTextParams,vlAddText,vlPolylineBegin,vlVertex,
                vlVertexR,vlVertexF,vlVertexB,vlAddPolyline,vlAddRect);

        pPlugins->Objects[i] = (TObject *)pPlugin;

        pItem->Caption = pPlugin->GetName()+AnsiString(" - V")+pPlugin->GetVersion();
        pItem->Hint = pPlugin->GetHint();
        pItem->ShortCut = pPlugin->GetShortCut();
//        pPlugin->GetAuthorName();
//        pPlugin->GetDate();
        pItem->OnClick = DoClickPlugin;
        pItem->Tag = i;

        strGroupName = pPlugin->GetGroup();
        bGroupFound = false;
        for(int j=0;j<Plugin1->Count;j++)
        {
			if(Plugin1->Items[j]->Caption == strGroupName)
            {
            	pGroupItem = Plugin1->Items[j];
            	bGroupFound = true;
             	break;
            }
        }
        if(bGroupFound)
        {
	    	pGroupItem->Add(pItem);
        }
        else
        {
	    	pGroupItem = new TMenuItem(this);
            pGroupItem->Caption = strGroupName;
	    	Plugin1->Add(pGroupItem);
	    	pGroupItem->Add(pItem);
        }
    }
*/
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::LoadSettings()
{
    TIniFile *pIniFile = new TIniFile(ChangeFileExt(Application->ExeName,".ini"));

    // Language
    m_nLanguageID = pIniFile->ReadInteger("Language","ID",0);
    m_dWorkingAreaWidthMM = pIniFile->ReadFloat("Settings","WorkingAreaWidthMM",100.0);
    m_dWorkingAreaHeightMM = pIniFile->ReadFloat("Settings","WorkingAreaHeightMM",100.0);
    m_dMinStepMM = pIniFile->ReadFloat("Settings","MinStepMM",0.1);

    // Grid
    m_dGridSmallStepX = pIniFile->ReadFloat("Grid","dGridSmallStepX",0.1);
    m_dGridSmallStepY = pIniFile->ReadFloat("Grid","dGridSmallStepY",0.1);
    m_nGridLargeStepX = pIniFile->ReadInteger("Grid","nGridLargeStepX",10);
    m_nGridLargeStepY = pIniFile->ReadInteger("Grid","nGridLargeStepY",10);
    m_bGridSnap = pIniFile->ReadBool("Grid","bGridSnap",true);
    m_bGridShow = pIniFile->ReadBool("Grid","bGridShow",true);
    m_nGridSmallColor = pIniFile->ReadInteger("Grid","nGridSmallColor",clBlue);
    m_nGridLargeColor = pIniFile->ReadInteger("Grid","nGridLargeColor",TColor(0x00FFC0C0));

    // Tools
    for(int i=0;i<10;i++)
    {
        g_pTools[i].x0 = pIniFile->ReadFloat("Tools",FormatFloat("dTool0_X",i),0.0);
        g_pTools[i].y0 = pIniFile->ReadFloat("Tools",FormatFloat("dTool0_Y",i),0.0);
        g_pTools[i].nColor = (TColor)pIniFile->ReadInteger("Tools",FormatFloat("nTool0_Color",i),g_pDefaultToolsColors[i]);
        g_pTools[i].strName = pIniFile->ReadString("Tools",FormatFloat("strTool0_Name",i),"");
    }

    if(pIniFile)	delete pIniFile;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::SaveSettings()
{
    TIniFile *pIniFile = new TIniFile(ChangeFileExt(Application->ExeName,".ini"));

    // Language
    pIniFile->WriteInteger("Language","ID",m_nLanguageID);

    pIniFile->WriteFloat("Settings","WorkingAreaWidthMM",m_dWorkingAreaWidthMM);
    pIniFile->WriteFloat("Settings","WorkingAreaHeightMM",m_dWorkingAreaHeightMM);
    pIniFile->WriteFloat("Settings","MinStepMM",m_dMinStepMM);

    // Grid
    if(PageControl->ActivePageIndex >= 0)
    {
        pIniFile->WriteFloat("Grid","dGridSmallStepX",m_dGridSmallStepX);
        pIniFile->WriteFloat("Grid","dGridSmallStepY",m_dGridSmallStepY);
        pIniFile->WriteInteger("Grid","nGridLargeStepX",m_nGridLargeStepX);
        pIniFile->WriteInteger("Grid","nGridLargeStepY",m_nGridLargeStepY);
        pIniFile->WriteBool("Grid","bGridSnap",m_bGridSnap);
        pIniFile->WriteBool("Grid","bGridShow",m_bGridShow);
        pIniFile->WriteInteger("Grid","nGridSmallColor",m_nGridSmallColor);
        pIniFile->WriteInteger("Grid","nGridLargeColor",m_nGridLargeColor);
    }

	// Tools
    for(int i=0;i<10;i++)
    {
        pIniFile->WriteFloat("Tools",FormatFloat("dTool0_X",i),g_pTools[i].x0);
        pIniFile->WriteFloat("Tools",FormatFloat("dTool0_Y",i),g_pTools[i].y0);
        pIniFile->WriteInteger("Tools",FormatFloat("nTool0_Color",i),g_pTools[i].nColor);
        pIniFile->WriteString("Tools",FormatFloat("strTool0_Name",i),g_pTools[i].strName);
    }

    if(pIniFile)	delete pIniFile;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::BuildEntitiesList()
{
	ListBoxEntities->Clear();
	if(!g_bGenerateNamesList)	return;

    int nLayer, nEntity;
    AnsiString strEntityName;
	nLayer = CadGetFirstLayer(hDwg);
	while(nLayer)
    {
  		nEntity = CadLayerGetFirstEntity(nLayer);
  		while(nEntity)
        {
        	strEntityName = GetEntityName(nEntity);
            ListBoxEntities->Items->AddObject(strEntityName,(TObject *)nEntity);
        
	    	nEntity = CadLayerGetNextEntity(nLayer,nEntity);
    	}
  		nLayer = CadGetNextLayer(hDwg,nLayer);
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::NewDocument(AnsiString strFileName)
{
	TTabSheet *pPage = new TTabSheet(PageControl);
    pPage->PageControl = PageControl;
    pPage->Caption = ExtractFileName(strFileName);
    PageControl->ActivePage = pPage;

    hDwg = CadCreate();
    hVecWnd = CadWndCreate(hDwg,pPage->Handle,CAD_WS_DEFAULT,0,0,100,100);

	PageControlResize(NULL);

    cad_Document *pDocument = new cad_Document();
    pDocument->hDwg = hDwg;
    pDocument->hVecWnd = hVecWnd;
	pPage->Tag = (int)pDocument;

    g_bGenerateNamesList = true;
    BuildEntitiesList();
    LoadSettings();

    // Grid
    CadGridPutSize(hDwg,m_dGridSmallStepX,m_dGridSmallStepY,m_dGridSmallStepX);
    CadGridPutBoldStep(hDwg,m_nGridLargeStepX,m_nGridLargeStepY,m_nGridLargeStepX);
    CadGridPutSnap(hDwg,m_bGridSnap);
    CadGridPutShow(hDwg,m_bGridShow);
    CadGridPutColor(hDwg,false,m_nGridSmallColor);
    CadGridPutColor(hDwg,true,m_nGridLargeColor);

 	// create "Square" command 
    CadAddCommand(hDwg,CAD_CMD_DRAW_SQUARE,"SQUARE","SQR",NULL,Func_SQUARE,Drag_SQUARE);

    VHANDLE hPage = CadAddPage(hDwg,"Drawing",CAD_PAPER_USER,
    							CAD_PAPER_ALBUM,m_dWorkingAreaWidthMM,
                                m_dWorkingAreaHeightMM);
	CadSetCurPage(hDwg,hPage);
  	VHANDLE hModelPage = CadGetPageByName(hDwg,"Model");
  	if(hModelPage)
    {
    	CadDeletePage(hDwg,hModelPage);
  	}
  	CadRegen(hDwg);
  	CadExecute(hDwg,hVecWnd,CAD_CMD_ZOOM_EXT);

    // Deactivate all snap type (not grid snap)
    ASnapNoneExecute(NULL);

/*
    g_bGenerateNamesList = true;

    int nDocIndex = vlFileNew(ghwVec,"");
    vlPropPut(VD_DWG_FILENAME,nDocIndex,strFileName.c_str());
    ListBoxOpenedFiles->Items->AddObject(ExtractFileName(strFileName),(TObject *)nDocIndex);

	// Clear and create default informational objects
    vlClear(true);

    // Units
    vlPropPutDbl(VD_UNITS_LIN,-1,VL_UNIT_CM);// -1 mean currenly active drawing.

    // Grid
    vlPropPutDbl(VD_GRID_X0,-1,m_dGridOX);
    vlPropPutDbl(VD_GRID_Y0,-1,m_dGridOY);
    vlPropPutDbl(VD_GRID_DX,-1,m_dGridSmallStepX);
    vlPropPutDbl(VD_GRID_DY,-1,m_dGridSmallStepY);
    vlPropPutInt(VD_GRID_BSTEPX,-1,m_nGridLargeStepX);
    vlPropPutInt(VD_GRID_BSTEPY,-1,m_nGridLargeStepY);
    nSnapData = vlPropGetInt(VD_DWG_SNAP,-1);
    if(m_bGridSnap && (!(nSnapData & VL_SNAP_GRID))) 	vlExecute(VC_SNAP_GRID);
    else
    if((!m_bGridSnap) && (nSnapData & VL_SNAP_GRID))	vlExecute(VC_SNAP_GRID);
    vlPropPutInt(VD_DWG_SHOWGRID,-1,m_bGridShow);
    vlPropPutInt(VD_GRID_COLOR,-1,m_nGridSmallColor);
    vlPropPutInt(VD_GRID_BCOLOR,-1,m_nGridLargeColor);

    vlPropPutDbl(VD_EXP_X0,nDocIndex,0);
    vlPropPutDbl(VD_EXP_Y0,nDocIndex,0);
    vlPropPutInt(VD_EXP_UNITX,nDocIndex,1);
    vlPropPutInt(VD_EXP_UNITY,nDocIndex,1);
    vlPropPutDbl(VD_EXP_MINSTEP,nDocIndex,m_dMinStepCM);// device

    // Working Area
    m_nWorkingAreaRectIndex = vlAddRect(m_dWorkingAreaWidthCM/2.0, m_dWorkingAreaHeightCM/2.0, m_dWorkingAreaWidthCM, m_dWorkingAreaHeightCM, 0, 0);
    vlPropPutInt(VD_ENT_COLOR,m_nWorkingAreaRectIndex,clGreen);
    vlPropPutInt(VD_ENT_KEY,m_nWorkingAreaRectIndex,-2);// Frame Key

	ActivateEntity(-1);
*/
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormCreate(TObject *Sender)
{
    LoadSettings();

	Left = 0;
    Top = 0;
    Width = Screen->Width;
    Height = Screen->Height - 30;

    m_pCanvas = new TCanvas();

    m_strAppTitle = Caption;

    m_nImageIndex = -1;

    // register you copy of VeCAD
  	CadRegistration( 1950125322 );

  	// define events procedures
    CadOnEventEntCreate(EntCreateProc);
    CadOnEventEntSelect(EntSelectProc);
    CadOnEventEntErase(EntEraseProc);
    CadOnEventMouseMove(MouseMoveProc);
    CadOnEventMouseDown(MouseDownProc);
    CadOnEventFontReplace(FontReplaceProc);
    CadOnEventSelCodepage(SelCodepageProc);
    CadOnEventExecute(ExecuteProc);
    CadOnEventCmdStart(CmdStartProc);
    CadOnEventCmdLBDown(CmdLBDownProc);
    CadOnEventCmdFinish(CmdFinishProc);
    CadOnEventRegen(RegenProc);

	// Custom entity events
  	CadOnEventCEntGetName(EventCEntGetName);
  	CadOnEventCEntGetProps(EventCEntGetProps);
  	CadOnEventCEntPutProp(EventCEntPutProp);
  	CadOnEventCEntGetExts(EventCEntGetExts);
  	CadOnEventCEntNumGrips(EventCEntNumGrips);
  	CadOnEventCEntGetGrip(EventCEntGetGrip);
  	CadOnEventCEntMoveGrip(EventCEntMoveGrip);
  	CadOnEventCEntMove(EventCEntMove);
  	CadOnEventCEntRotate(EventCEntRotate);
  	CadOnEventCEntScale(EventCEntScale);
  	CadOnEventCEntMirror(EventCEntMirror);
  	CadOnEventCEntDisplay(EventCEntDisplay);

    // set default assignment for accelerator keys
    CadAccelSetDefault();
    // load MRU list from a file
    CadRecentLoad("c:\recent.txt");
//    CadRecentLoad(ChangeFileExt(Application->ExeName,".txt").c_str());

    // set VeCAD properties
    CadSetShowCross(CAD_TRUE);

    // create window to enter VeCAD commands commands
    //	PanelCommandLine->Visible = true;
    //	CadCWCreate(PanelCommandLine->Handle,0,0,1,1);

    // create "Layers" combobox
//    CadCboxCreate(CAD_CBOX_LAYER,ToolBarLayers->Handle,0,0,ToolBarLayers->ClientWidth,ToolBarLayers->ClientHeight,200);

    // Curve Quality
    // CadSetCurveQuality(3);

/*
    m_strFileName="Untitled";
    Caption=m_strAppTitle;

    pPlugins = new TStringList();
	UpdatePlugins();
    nCurrPluginIndex = 0;
*/

	ActivateEntity(-1);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormDestroy(TObject *Sender)
{
	AFileCloseAllExecute(NULL);

    // save MRU list
    CadRecentSave();
    // delete command window
    CadCWDelete();

	SaveSettings();
    ClearPlugins();
    if(pPlugins)	delete pPlugins;pPlugins = NULL;
	if(m_pCanvas)
    {
     	delete m_pCanvas;
        m_pCanvas = NULL;
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::AFileExecute(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AFileNewExecute(TObject *Sender)
{
    NewDocument(c_strUntitledFile);
    AfterOpen(c_strUntitledFile);

    // Clear entity list
    FormMain->ListBoxEntities->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::AFileChangeDimExecute(TObject *Sender)
{
/*
	if(FormNew->ShowModal() != mrOk)	return;
    int nWidth,nHeight;
    nWidth = StrToInt(FormNew->EditWidth->Text)*100;
    nHeight = StrToInt(FormNew->EditHeight->Text)*100;

    // Show All
    vlZoom(VL_ZOOM_ALL);
    vlZoom(0.9);
*/    
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::AfterOpen(AnsiString strFileName)
{
    // add filename to MRU list
    CadRecentAdd(strFileName.c_str());
    // Show All
	CadExecute(hDwg,hVecWnd,CAD_CMD_ZOOM_EXT);
    // redraw VeCAD window content
    CadWndRedraw(hVecWnd);
    // set input focus to VeCAd window
    CadExecute(hDwg,hVecWnd,CAD_CMD_SETFOCUS);
    // set Form title
	PageControl->ActivePage->Caption = ExtractFileName(strFileName);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::AFileOpenExecute(TObject *Sender)
{
	if(!OpenDialogVEC->Execute())	return;
    if(UpperCase(OpenDialogVEC->FileName).Pos(".VEC") <= 0)	return;
    g_bGenerateNamesList = false;
    NewDocument(c_strUntitledFile);
    if(CadFileOpen(hDwg,hVecWnd,OpenDialogVEC->FileName.c_str()))
    {
        AfterOpen(OpenDialogVEC->FileName);
	    g_bGenerateNamesList = true;
    	BuildEntitiesList();
    }
    g_bGenerateNamesList = true;

/*
	if(OpenDialogVEC->Execute())
    {
	    g_bGenerateNamesList = false;
        vlFileOpen(ghwVec,OpenDialogVEC->FileName.c_str());
		ActivateEntity(-1);
        m_nWorkingAreaRectIndex = vlGetEntity(VL_EI_BYKEY,-2,VL_DRAWING);
	    int nDocIndex = vlDocGetActive();
    	ListBoxOpenedFiles->Items->AddObject(ExtractFileName(OpenDialogVEC->FileName),(TObject *)nDocIndex);
	    g_bGenerateNamesList = true;
	    BuildEntitiesList();

        vlPropPutDbl(VD_EXP_X0,nDocIndex,0);
        vlPropPutDbl(VD_EXP_Y0,nDocIndex,0);
        vlPropPutInt(VD_EXP_UNITX,nDocIndex,1);
        vlPropPutInt(VD_EXP_UNITY,nDocIndex,1);
        vlPropPutDbl(VD_EXP_MINSTEP,nDocIndex,m_dMinStepCM);// device
	}
*/
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::AFileImportDXFExecute(TObject *Sender)
{
	if(!OpenDialogDXF->Execute())	return;
    if(UpperCase(OpenDialogDXF->FileName).Pos(".DXF") <= 0)	return;
    g_bGenerateNamesList = false;
    NewDocument(c_strUntitledFile);
    if(CadFileOpen(hDwg,hVecWnd,OpenDialogDXF->FileName.c_str()))
    {
        AfterOpen(OpenDialogDXF->FileName);
	    g_bGenerateNamesList = true;
    	BuildEntitiesList();
    }
    g_bGenerateNamesList = true;
/*
	int nDocIndex = vlDocGetActive();
    if(nDocIndex < 0)
    {
		AFileNewExecute(NULL);
    }
    g_bGenerateNamesList = false;
    vlExecute(VC_IMPORT_DXF);
	ActivateEntity(-1);
    m_nWorkingAreaRectIndex = vlGetEntity(VL_EI_BYKEY,-2,VL_DRAWING);
    g_bGenerateNamesList = true;
    BuildEntitiesList();

    vlPropPutDbl(VD_EXP_X0,nDocIndex,0);
    vlPropPutDbl(VD_EXP_Y0,nDocIndex,0);
    vlPropPutInt(VD_EXP_UNITX,nDocIndex,1);
    vlPropPutInt(VD_EXP_UNITY,nDocIndex,1);
    vlPropPutDbl(VD_EXP_MINSTEP,nDocIndex,m_dMinStepCM);// device
*/
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::AFileSaveExecute(TObject *Sender)
{
	CadFileSave(hDwg,hVecWnd);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::AFileSaveAsExecute(TObject *Sender)
{
	if(!SaveDialogVEC->Execute())	return;
    if(UpperCase(SaveDialogVEC->FileName).Pos(".VEC") <= 0)	return;
    CadFileSaveAs(hDwg,hVecWnd,SaveDialogVEC->FileName.c_str());
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::AFileExportDXFExecute(TObject *Sender)
{
	if(!SaveDialogDXF->Execute())	return;
    if(UpperCase(SaveDialogDXF->FileName).Pos(".DXF") <= 0)	return;
    CadSetDxfVersion(CAD_ACAD2000);
    CadFileSaveAs(hDwg,hVecWnd,SaveDialogDXF->FileName.c_str());
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::AFileCloseExecute(TObject *Sender)
{
	if(PageControl->PageCount <= 0)	return;
    if(PageControl->ActivePageIndex < 0)	return;

	cad_Document *pDocument;
	pDocument = (cad_Document *)(PageControl->Pages[PageControl->ActivePageIndex]->Tag);
    hDwg = pDocument->hDwg;
    if(pDocument)
    {
     	delete pDocument;
        pDocument = NULL;
    }
    TTabSheet *pPage = PageControl->ActivePage;
    PageControl->ActivePage = NULL;
    if(CadGetDirty(hDwg))// Drawing Changed, Save it?
    {
		if(MessageDlg(FormOptions->LabelSaveChanges->Caption+"\n\r ["+pPage->Caption+" ]",mtConfirmation,TMsgDlgButtons()<<mbYes<<mbNo,0) == IDYES)
        {
			CadFileSave(hDwg,hVecWnd);
        }
    }

    if(pPage)
    {
     	delete pPage;
        pPage = NULL;
    }
	CadDelete(hDwg);
    PageControl->SelectNextPage(true);

    g_bGenerateNamesList = false;
    BuildEntitiesList();
    ActivateEntity(-1);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AFileCloseAllExecute(TObject *Sender)
{
	cad_Document *pDocument;
    TTabSheet *pPage;
    int nDrawing;
    while(PageControl->PageCount > 0)
    {
    	PageControl->SelectNextPage(false);
    	pPage = PageControl->ActivePage;
        PageControl->ActivePage = NULL;
        pDocument = (cad_Document *)(pPage->Tag);
        nDrawing = pDocument->hDwg;
        hVecWnd = pDocument->hVecWnd;
        if(pDocument)
        {
            delete pDocument;
            pDocument = NULL;
        }
        if(CadGetDirty(nDrawing))// Drawing Changed, Save it?
        {
            if(MessageDlg(FormOptions->LabelSaveChanges->Caption+"\n\r ["+pPage->Caption+" ]",mtConfirmation,TMsgDlgButtons()<<mbYes<<mbNo,0) == IDYES)
            {
                CadFileSave(nDrawing,hVecWnd);
            }
        }

        if(pPage)
        {
         	delete pPage;
        }
        CadDelete(nDrawing);
    }
    PageControl->ActivePage = NULL;
    g_bGenerateNamesList = false;
    BuildEntitiesList();
    ActivateEntity(-1);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::AFileExitExecute(TObject *Sender)
{
	Close();	
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::AZoomExecute(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AZoomAllExecute(TObject *Sender)
{
  	CadExecute(hDwg,hVecWnd,CAD_CMD_ZOOM_EXT);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AZoomWindowExecute(TObject *Sender)
{
  	CadExecute(hDwg,hVecWnd,CAD_CMD_ZOOM_WIN);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AZoomInExecute(TObject *Sender)
{
  	CadExecute(hDwg,hVecWnd,CAD_CMD_ZOOM_IN);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AZoomOutExecute(TObject *Sender)
{
	CadExecute(hDwg,hVecWnd,CAD_CMD_ZOOM_OUT);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AZoomPanWindowExecute(TObject *Sender)
{
  	CadExecute(hDwg,hVecWnd,CAD_CMD_PAN_RTIME);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ZoomToPrevExecute(TObject *Sender)
{
  	CadExecute(hDwg,hVecWnd,CAD_CMD_ZOOM_PREV);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ASnapExecute(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ASnapDlgExecute(TObject *Sender)
{
//	vlExecute(VC_SNAP_DLG);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ASnapGridExecute(TObject *Sender)
{
	ASnapGrid->Checked = !ASnapGrid->Checked;
	CadGridPutSnap(hDwg,ASnapGrid->Checked);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ASnapPolarExecute(TObject *Sender)
{
/*
	ASnapPolar->Checked = !ASnapPolar->Checked;
	vlExecute(VC_SNAP_POLAR);
*/
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ASnapGripsExecute(TObject *Sender)
{
    CadSnapPutMode(hDwg,CAD_SNAP_GRIP);
    CadSnapPutOn(hDwg,true);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ASnapPointExecute(TObject *Sender)
{
    CadSnapPutMode(hDwg,CAD_SNAP_NODE);
    CadSnapPutOn(hDwg,true);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ASnapNearExecute(TObject *Sender)
{
    CadSnapPutMode(hDwg,CAD_SNAP_NEAREST);
    CadSnapPutOn(hDwg,true);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ASnapEndExecute(TObject *Sender)
{
    CadSnapPutMode(hDwg,CAD_SNAP_ENDPOINT);
    CadSnapPutOn(hDwg,true);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ASnapMidExecute(TObject *Sender)
{
    CadSnapPutMode(hDwg,CAD_SNAP_MIDPOINT);
    CadSnapPutOn(hDwg,true);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ASnapCenterExecute(TObject *Sender)
{
    CadSnapPutMode(hDwg,CAD_SNAP_CENTER);
    CadSnapPutOn(hDwg,true);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ASnapPerpendicularExecute(TObject *Sender)
{
    CadSnapPutMode(hDwg,CAD_SNAP_PERPEND);
    CadSnapPutOn(hDwg,true);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ASnapTangentExecute(TObject *Sender)
{
    CadSnapPutMode(hDwg,CAD_SNAP_TANGENT);
    CadSnapPutOn(hDwg,true);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ASnapIntersectionExecute(TObject *Sender)
{
    CadSnapPutMode(hDwg,CAD_SNAP_INTER);
    CadSnapPutOn(hDwg,true);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ASnapAllExecute(TObject *Sender)
{
    CadSnapPutMode(hDwg,CAD_SNAP_ALL);
    CadSnapPutOn(hDwg,true);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ASnapNoneExecute(TObject *Sender)
{
    CadSnapPutMode(hDwg,0);
    CadSnapPutOn(hDwg,false);
    ToolButtonSnapNode->Down = true;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AEditExecute(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AEditEntPropExecute(TObject *Sender)
{
  	CadExecute(hDwg,hVecWnd,CAD_CMD_ENTPROP);
//	vlExecute(VC_EDIT_ENTPROP);
//	FormProperties->Show();	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AEditCopyExecute(TObject *Sender)
{
  	CadExecute(hDwg,hVecWnd,CAD_CMD_COPY);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AEditMoveExecute(TObject *Sender)
{
  	CadExecute(hDwg,hVecWnd,CAD_CMD_MOVE);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AEditRotateExecute(TObject *Sender)
{
  	CadExecute(hDwg,hVecWnd,CAD_CMD_ROTATE);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AEditScaleExecute(TObject *Sender)
{
  	CadExecute(hDwg,hVecWnd,CAD_CMD_SCALE);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AEditMirrorExecute(TObject *Sender)
{
  	CadExecute(hDwg,hVecWnd,CAD_CMD_MIRROR);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AEditEraseExecute(TObject *Sender)
{
  	CadExecute(hDwg,hVecWnd,CAD_CMD_ERASE);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AEditUndoExecute(TObject *Sender)
{
  	CadExecute(hDwg,hVecWnd,CAD_CMD_UNDO);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AEditRedoExecute(TObject *Sender)
{
  	CadExecute(hDwg,hVecWnd,CAD_CMD_REDO);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AEditCutCBExecute(TObject *Sender)
{
  	CadExecute(hDwg,hVecWnd,CAD_CMD_CBCUT);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AEditCopyCBExecute(TObject *Sender)
{
  	CadExecute(hDwg,hVecWnd,CAD_CMD_CBCOPY);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AEditPasteCBExecute(TObject *Sender)
{
  	CadExecute(hDwg,hVecWnd,CAD_CMD_CBPASTE);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::AEditSetJumpExecute(TObject *Sender)
{
/*
	bool First;
	int iEnt, iLayer;
    int EntityType;
	First = true;
	while(true)
    {
	  	if(First)
        {
		    iEnt = vlGetEntity( VL_EI_FIRST, VL_SELECTION, 0 );
		    First = false;
  		}
        else
        {
	    	iEnt = vlGetEntity(VL_EI_NEXT, 0, 0 );
  		}
  		if(iEnt >= 0)
  		{
            EntityType = vlPropGetInt(VD_ENT_TYPE,iEnt);
            switch(EntityType)
            {
                case VL_ENT_POLYLINE:// Polyline
                case VL_ENT_LINE:// Line
                {
        			vlPropPutInt(VD_ENT_COLOR,iEnt,0x00FF8000);
                    break;
                }
            }
  		}
        else
        {
    		break;
  		}
	}
*/
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AEditSetNormalExecute(TObject *Sender)
{
/*
	bool First;
	int iEnt, iLayer;
    int EntityType;
	First = true;
	while(true)
    {
	  	if(First)
        {
		    iEnt = vlGetEntity( VL_EI_FIRST, VL_SELECTION, 0 );
		    First = false;
  		}
        else
        {
	    	iEnt = vlGetEntity(VL_EI_NEXT, 0, 0 );
  		}
  		if(iEnt >= 0)
  		{
            EntityType = vlPropGetInt(VD_ENT_TYPE,iEnt);
            switch(EntityType)
            {
                case VL_ENT_POLYLINE:// Polyline
                case VL_ENT_LINE:// Line
                {
        			vlPropPutInt(VD_ENT_COLOR,iEnt,clBlack);
                    break;
                }
            }
  		}
        else
        {
    		break;
  		}
	}
*/
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AHelpExecute(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AHelpContentsExecute(TObject *Sender)
{
	AnsiString strFileName = ChangeFileExt(Application->ExeName,".htm");
	ShellExecute(0,"open",strFileName.c_str(),"","",SW_SHOW);	
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::AHelpAboutExecute(TObject *Sender)
{
	FormAbout->ShowModal();	
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ActivateDesigner()
{
	if(PageControl->PageCount <= 0)	return;
    if(PageControl->ActivePageIndex < 0)	return;
    if(PageControl->ActivePage == NULL)	return;

	cad_Document *pDocument;
	pDocument = (cad_Document *)(PageControl->Pages[PageControl->ActivePageIndex]->Tag);
    hDwg = pDocument->hDwg;
    hVecWnd = pDocument->hVecWnd;

    CadExecute(hDwg,hVecWnd,CAD_CMD_SETFOCUS);
    CadPutWindow(hDwg,hVecWnd);
  	CadWndRedraw(hVecWnd);

    g_bGenerateNamesList = true;
    BuildEntitiesList();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ADrawExecute(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ADrawLineExecute(TObject *Sender)
{
  	CadExecute(hDwg,hVecWnd,CAD_CMD_DRAW_LINE);
//	vlExecute(VC_DRAW_LINE);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ADrawRectangleExecute(TObject *Sender)
{
  	CadExecute(hDwg,hVecWnd,CAD_CMD_DRAW_RECT);
//	vlExecute(VC_DRAW_RECT);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ADrawPolylineExecute(TObject *Sender)
{
  	CadExecute(hDwg,hVecWnd,CAD_CMD_DRAW_POLYLINE);
//	vlExecute(VC_DRAW_POLYLINE);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ADrawMultilineExecute(TObject *Sender)
{
  	CadExecute(hDwg,hVecWnd,CAD_CMD_DRAW_MLINE);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ADrawArcCSEExecute(TObject *Sender)
{
  	CadExecute(hDwg,hVecWnd,CAD_CMD_DRAW_ARC_CSE);
//	vlExecute(VC_DRAW_ARC_CSE);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ADrawArcSEMExecute(TObject *Sender)
{
  	CadExecute(hDwg,hVecWnd,CAD_CMD_DRAW_ARC_SCA);
//	vlExecute(VC_DRAW_ARC_SEM);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ADrawArcSMEExecute(TObject *Sender)
{
  	CadExecute(hDwg,hVecWnd,CAD_CMD_DRAW_ARC_3P);
//	vlExecute(VC_DRAW_ARC_SME);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ADrawCircleCRExecute(TObject *Sender)
{
  	CadExecute(hDwg,hVecWnd,CAD_CMD_DRAW_CIRC_CR);
//	vlExecute(VC_DRAW_CIRC_CR);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ADrawCircleCDExecute(TObject *Sender)
{
  	CadExecute(hDwg,hVecWnd,CAD_CMD_DRAW_CIRC_CD);
//	vlExecute(VC_DRAW_CIRC_CD);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ADrawCircle2PExecute(TObject *Sender)
{
  	CadExecute(hDwg,hVecWnd,CAD_CMD_DRAW_CIRC_2P);
//	vlExecute(VC_DRAW_CIRC_2P);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ADrawCircle3PExecute(TObject *Sender)
{
  	CadExecute(hDwg,hVecWnd,CAD_CMD_DRAW_CIRC_3P);
//	vlExecute(VC_DRAW_CIRC_3P);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ADrawEllipseExecute(TObject *Sender)
{
  	CadExecute(hDwg,hVecWnd,CAD_CMD_DRAW_ELLIPSE);
//	vlExecute(VC_DRAW_ELLIPSE);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AToolsExecute(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AToolsSimulatorExecute(TObject *Sender)
{
	FormSimulator->ShowModal();
//	ActivateDesigner();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AToolsNavigatorExecute(TObject *Sender)
{
	if(PageControl->ActivePage == NULL)	return;
    int x,y;
    int w = 150;
    x = PageControl->ActivePage->ClientWidth - w;
    y = PageControl->ActivePage->ClientHeight - w;
	CadNavCreate(PageControl->ActivePage->Handle,x,y,w,w,CAD_NAV_SUNKEN);
	// CadNavCreate(PageControl->ActivePage->Handle,0,0,150,150,CAD_NAV_SUNKEN | CAD_NAV_CPANEL);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ATraceExecute(TObject *Sender)
{
//	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ATraceToolExecute(TObject *Sender)
{
//	vlExecute(spl_CMD_POLYARC);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FormClose(TObject *Sender, TCloseAction &Action)
{
    AFileCloseAllExecute(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::AFileImportPLTExecute(TObject *Sender)
{
	if(!OpenDialogPLT->Execute())	return;
    if(UpperCase(OpenDialogPLT->FileName).Pos(".PLT") <= 0)	return;
    g_bGenerateNamesList = true;
    NewDocument(c_strUntitledFile);
	if(cad_Import_PLT(hDwg,OpenDialogPLT->FileName))
    {
        AfterOpen(OpenDialogPLT->FileName);
    }
/*
	int nDocIndex = vlDocGetActive();
    if(nDocIndex < 0)
    {
		AFileNewExecute(NULL);
    }
    g_bGenerateNamesList = false;
	vlExecute(VC_IMPORT_HPGL);
	ActivateEntity(-1);
    m_nWorkingAreaRectIndex = vlGetEntity(VL_EI_BYKEY,-2,VL_DRAWING);
    g_bGenerateNamesList = true;
    BuildEntitiesList();

    vlPropPutDbl(VD_EXP_X0,nDocIndex,0);
    vlPropPutDbl(VD_EXP_Y0,nDocIndex,0);
    vlPropPutInt(VD_EXP_UNITX,nDocIndex,1);
    vlPropPutInt(VD_EXP_UNITY,nDocIndex,1);
    vlPropPutDbl(VD_EXP_MINSTEP,nDocIndex,m_dMinStepCM);// device
*/
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::AFileExportPLTExecute(TObject *Sender)
{
	if(!SaveDialogPLT->Execute())	return;
    if(UpperCase(SaveDialogPLT->FileName).Pos(".PLT") <= 0)	return;

    if(FormExport->ShowModal() != mrOk)	return;
    g_dSpeed = StrToFloat(FormExport->EditSpeed->Text);
    if(g_dSpeed <= 0.0)	g_dSpeed = 1.0;
    g_dZStep = StrToFloat(FormExport->EditZStep->Text);
    if(g_dZStep <= 0.0)	g_dZStep = 1.0;

    g_dDividingStep = m_dMinStepMM;
    cad_Export_PLT(hDwg,SaveDialogPLT->FileName);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AFileExportCMDExecute(TObject *Sender)
{
//	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ShowEntityProperty(int nEntityIndex)
{
/*
	if(FormProperties == NULL)	return;
    FormProperties->Caption = FormProperties->m_strCaption;
    FormProperties->Grid->RowCount = 2;
    FormProperties->Grid->Cells[0][0] = "Property";
    FormProperties->Grid->Cells[1][0] = "Value";
    FormProperties->Grid->Cells[0][1] = "";
    FormProperties->Grid->Cells[1][1] = "";
    if(nEntityIndex < 0)	return;
    int nEntityType;
    nEntityType = vlPropGetInt(VD_ENT_TYPE,nEntityIndex);
    switch(nEntityType)
    {
        case VL_ENT_POINT:// Point
        {
    		FormProperties->Caption = FormProperties->m_strCaption+" [Point] ";
            break;
        }
        case VL_ENT_LINE:// Line
        {
    		FormProperties->Caption = FormProperties->m_strCaption+" [Line] ";

            cnc_Point p1,p2;
            p1.x = vlPropGetDbl(VD_LINE_X1,nEntityIndex);
            p1.y = vlPropGetDbl(VD_LINE_Y1,nEntityIndex);
            p2.x = vlPropGetDbl(VD_LINE_X2,nEntityIndex);
            p2.y = vlPropGetDbl(VD_LINE_Y2,nEntityIndex);

    		FormProperties->Grid->RowCount = 1+4;
            FormProperties->Grid->Cells[0][1] = "X1";
            FormProperties->Grid->Cells[1][1] = FormatFloat(c_strFloatMask,p1.x);
            FormProperties->Grid->Cells[0][2] = "Y1";
            FormProperties->Grid->Cells[1][2] = FormatFloat(c_strFloatMask,p1.y);
            FormProperties->Grid->Cells[0][3] = "X2";
            FormProperties->Grid->Cells[1][3] = FormatFloat(c_strFloatMask,p2.x);
            FormProperties->Grid->Cells[0][4] = "Y2";
            FormProperties->Grid->Cells[1][4] = FormatFloat(c_strFloatMask,p2.y);
            break;
        }
        case VL_ENT_POLYLINE:// Polyline
        {
    		FormProperties->Caption = FormProperties->m_strCaption+" [Polyline] ";

		    int nCount;
		    double x,y;
    		double dParam;
            nCount = vlPropGetInt(VD_POLY_N_VER,nEntityIndex);
    		FormProperties->Grid->RowCount = 1+3*nCount;
            for(int i=0;i<nCount;i++)
            {
                vlPolyVerGet(nEntityIndex,i,&x,&y,&dParam);
	            FormProperties->Grid->Cells[0][3*i+1] = FormatFloat("X0",i+1);
    	        FormProperties->Grid->Cells[1][3*i+1] = FormatFloat(c_strFloatMask,x);
	            FormProperties->Grid->Cells[0][3*i+1+1] = FormatFloat("Y0",i+1);
    	        FormProperties->Grid->Cells[1][3*i+1+1] = FormatFloat(c_strFloatMask,y);
	            FormProperties->Grid->Cells[0][3*i+2+1] = FormatFloat("P0",i+1);
    	        FormProperties->Grid->Cells[1][3*i+2+1] = FormatFloat(c_strFloatMask,dParam);
            }
            break;
        }
        case VL_ENT_CIRCLE:// Circle
        {
    		FormProperties->Caption = FormProperties->m_strCaption+" [Circle] ";

        	double x,y,r;
            x = vlPropGetDbl(VD_CIRCLE_X,nEntityIndex);
            y = vlPropGetDbl(VD_CIRCLE_Y,nEntityIndex);
            r = vlPropGetDbl(VD_CIRCLE_R,nEntityIndex);

    		FormProperties->Grid->RowCount = 1+3;
            FormProperties->Grid->Cells[0][1] = "X";
            FormProperties->Grid->Cells[1][1] = FormatFloat(c_strFloatMask,x);
            FormProperties->Grid->Cells[0][2] = "Y";
            FormProperties->Grid->Cells[1][2] = FormatFloat(c_strFloatMask,y);
            FormProperties->Grid->Cells[0][3] = "R";
            FormProperties->Grid->Cells[1][3] = FormatFloat(c_strFloatMask,r);
            break;
        }
        case VL_ENT_ARC:// Arc
        case VL_ENT_ARC2:// Arc2
        {
    		FormProperties->Caption = FormProperties->m_strCaption+" [Arc] ";

        	double x,y,rh,rv,Ang0,AngArc,AngRot;
            x = vlPropGetDbl(VD_ARC_X,nEntityIndex);
            y = vlPropGetDbl(VD_ARC_Y,nEntityIndex);
            rh = vlPropGetDbl(VD_ARC_RH,nEntityIndex);
            rv = vlPropGetDbl(VD_ARC_RV,nEntityIndex);
            Ang0 = vlPropGetDbl(VD_ARC_ANG0,nEntityIndex);
            AngArc = vlPropGetDbl(VD_ARC_ANGARC,nEntityIndex);
            AngRot = vlPropGetDbl(VD_ARC_ANGROT,nEntityIndex);

    		FormProperties->Grid->RowCount = 1+7;
            FormProperties->Grid->Cells[0][1] = "X";
            FormProperties->Grid->Cells[1][1] = FormatFloat(c_strFloatMask,x);
            FormProperties->Grid->Cells[0][2] = "Y";
            FormProperties->Grid->Cells[1][2] = FormatFloat(c_strFloatMask,y);
            FormProperties->Grid->Cells[0][3] = "RH";
            FormProperties->Grid->Cells[1][3] = FormatFloat(c_strFloatMask,rh);
            FormProperties->Grid->Cells[0][4] = "RV";
            FormProperties->Grid->Cells[1][4] = FormatFloat(c_strFloatMask,rv);
            FormProperties->Grid->Cells[0][5] = "Ang0";
            FormProperties->Grid->Cells[1][5] = FormatFloat(c_strFloatMask,Ang0);
            FormProperties->Grid->Cells[0][6] = "Ang-Arc";
            FormProperties->Grid->Cells[1][6] = FormatFloat(c_strFloatMask,AngArc);
            FormProperties->Grid->Cells[0][7] = "Ang-Rot";
            FormProperties->Grid->Cells[1][7] = FormatFloat(c_strFloatMask,AngRot);
            break;
        }
        case VL_ENT_ELLIPSE:// Ellipse
        {
    		FormProperties->Caption = FormProperties->m_strCaption+" [Ellipse] ";

        	double x,y,rh,rv,AngRot;
            x = vlPropGetDbl(VD_ELLIPSE_X,nEntityIndex);
            y = vlPropGetDbl(VD_ELLIPSE_Y,nEntityIndex);
            rh = vlPropGetDbl(VD_ELLIPSE_RH,nEntityIndex);
            rv = vlPropGetDbl(VD_ELLIPSE_RV,nEntityIndex);
            AngRot = vlPropGetDbl(VD_ELLIPSE_ANGLE,nEntityIndex);

    		FormProperties->Grid->RowCount = 1+5;
            FormProperties->Grid->Cells[0][1] = "X";
            FormProperties->Grid->Cells[1][1] = FormatFloat(c_strFloatMask,x);
            FormProperties->Grid->Cells[0][2] = "Y";
            FormProperties->Grid->Cells[1][2] = FormatFloat(c_strFloatMask,y);
            FormProperties->Grid->Cells[0][3] = "RH";
            FormProperties->Grid->Cells[1][3] = FormatFloat(c_strFloatMask,rh);
            FormProperties->Grid->Cells[0][4] = "RV";
            FormProperties->Grid->Cells[1][4] = FormatFloat(c_strFloatMask,rv);
            FormProperties->Grid->Cells[0][5] = "Ang-Rot";
            FormProperties->Grid->Cells[1][5] = FormatFloat(c_strFloatMask,AngRot);
            break;
        }
        case VL_ENT_TEXT:// Text
        {
    		FormProperties->Caption = FormProperties->m_strCaption+" [Text] ";
            break;
        }
        case VL_ENT_BITMAP:// Bitmap
        {
    		FormProperties->Caption = FormProperties->m_strCaption+" [Bitmap] ";
            break;
        }
        case VL_ENT_INSBLOCK:// Block insertion
        {
    		FormProperties->Caption = FormProperties->m_strCaption+" [Ins-Block] ";
            break;
        }
        case VL_ENT_HATCH:// Hatch
        {
    		FormProperties->Caption = FormProperties->m_strCaption+" [Hatch] ";
            break;
        }
        case VL_ENT_FLOOD:// Flood
        {
    		FormProperties->Caption = FormProperties->m_strCaption+" [Flood] ";
            break;
        }
        case VL_ENT_RECT:// Rectangle
        {
    		FormProperties->Caption = FormProperties->m_strCaption+" [Rect] ";

        	double x,y,w,h,AngRot,r;
            x = vlPropGetDbl(VD_RECT_XCEN,nEntityIndex);
            y = vlPropGetDbl(VD_RECT_YCEN,nEntityIndex);
            w = vlPropGetDbl(VD_RECT_WIDTH,nEntityIndex);
            h = vlPropGetDbl(VD_RECT_HEIGHT,nEntityIndex);
            AngRot = vlPropGetDbl(VD_RECT_ANGLE,nEntityIndex);
            r = vlPropGetDbl(VD_RECT_RADIUS,nEntityIndex);

    		FormProperties->Grid->RowCount = 1+6;
            FormProperties->Grid->Cells[0][1] = "X";
            FormProperties->Grid->Cells[1][1] = FormatFloat(c_strFloatMask,x);
            FormProperties->Grid->Cells[0][2] = "Y";
            FormProperties->Grid->Cells[1][2] = FormatFloat(c_strFloatMask,y);
            FormProperties->Grid->Cells[0][3] = "Width";
            FormProperties->Grid->Cells[1][3] = FormatFloat(c_strFloatMask,w);
            FormProperties->Grid->Cells[0][4] = "Height";
            FormProperties->Grid->Cells[1][4] = FormatFloat(c_strFloatMask,h);
            FormProperties->Grid->Cells[0][5] = "Ang-Rot";
            FormProperties->Grid->Cells[1][5] = FormatFloat(c_strFloatMask,AngRot);
            FormProperties->Grid->Cells[0][6] = "Radius";
            FormProperties->Grid->Cells[1][6] = FormatFloat(c_strFloatMask,r);
            break;
        }
        case VL_ENT_DIMLIN:// DIMLIN
        {
    		FormProperties->Caption = FormProperties->m_strCaption+" [Dim-Line] ";
            break;
        }
        case VL_ENT_DIMANG:// DIMANG
        {
    		FormProperties->Caption = FormProperties->m_strCaption+" [Dim-Ang] ";
            break;
        }
        case VL_ENT_DIMRAD:// DIMRAD
        {
    		FormProperties->Caption = FormProperties->m_strCaption+" [Dim-Rad] ";
            break;
        }
        case VL_ENT_DIMDIAM:// DIMDIAM
        {
    		FormProperties->Caption = FormProperties->m_strCaption+" [Dim-Diam] ";
            break;
        }
        case VL_ENT_DIMORD:// DIMORD
        {
    		FormProperties->Caption = FormProperties->m_strCaption+" [Dim-Ord] ";
            break;
        }
        case VL_ENT_DWGINS:// DWGINS
        {
    		FormProperties->Caption = FormProperties->m_strCaption+" [Dwg-Ins] ";
            break;
        }
        case VL_ENT_CUSTOM:// CUSTOM
        {
    		FormProperties->Caption = FormProperties->m_strCaption+" [Custom] ";
            break;
        }
    }
*/
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::SetEntityProperty(int nRow)
{
/*
	if(ListBoxEntities->ItemIndex < 0)	return;
	int nEntityIndex;
    nEntityIndex = (int)ListBoxEntities->Items->Objects[ListBoxEntities->ItemIndex];
    int nEntityType;
    double d;
    nEntityType = vlPropGetInt(VD_ENT_TYPE,nEntityIndex);
    switch(nEntityType)
    {
        case VL_ENT_POINT:// Point
        {
            break;
        }
        case VL_ENT_LINE:// Line
        {
            switch(nRow)
            {
				case 1:
                {
				    d = StrToFloat(FormProperties->Grid->Cells[1][nRow]);
            		vlPropPutDbl(VD_LINE_X1,nEntityIndex,d);
                 	break;
                }
				case 2:
                {
				    d = StrToFloat(FormProperties->Grid->Cells[1][nRow]);
            		vlPropPutDbl(VD_LINE_Y1,nEntityIndex,d);
                 	break;
                }
				case 3:
                {
				    d = StrToFloat(FormProperties->Grid->Cells[1][nRow]);
		            vlPropPutDbl(VD_LINE_X2,nEntityIndex,d);
                 	break;
                }
				case 4:
                {
				    d = StrToFloat(FormProperties->Grid->Cells[1][nRow]);
		            vlPropPutDbl(VD_LINE_Y2,nEntityIndex,d);
                 	break;
                }
            }
            break;
        }
        case VL_ENT_POLYLINE:// Polyline
        {
		    int nCount;
		    double x,y;
    		double dParam;
            int nIndex;
            if((nRow-1) % 3 == 0)
				nIndex = (nRow-1)/3;
            else
            if((nRow-1) % 3 == 1)
				nIndex = (nRow-2)/3;
            else
            if((nRow-1) % 3 == 2)
				nIndex = (nRow-3)/3;
            vlPolyVerGet(nEntityIndex,nIndex,&x,&y,&dParam);
            if((nRow-1) % 3 == 0)
            {
            	x = StrToFloat(FormProperties->Grid->Cells[1][nRow]);
            }
            else
            if((nRow-1) % 3 == 1)
            {
            	y = StrToFloat(FormProperties->Grid->Cells[1][nRow]);
            }
            else
            if((nRow-1) % 3 == 2)
            {
            	dParam = StrToFloat(FormProperties->Grid->Cells[1][nRow]);
            }
            vlPolyVerSet(nEntityIndex,nIndex,x,y,dParam);
            break;
        }
        case VL_ENT_CIRCLE:// Circle
        {
            switch(nRow)
            {
				case 1:
                {
				    d = StrToFloat(FormProperties->Grid->Cells[1][nRow]);
            		vlPropPutDbl(VD_CIRCLE_X,nEntityIndex,d);
                 	break;
                }
				case 2:
                {
				    d = StrToFloat(FormProperties->Grid->Cells[1][nRow]);
            		vlPropPutDbl(VD_CIRCLE_Y,nEntityIndex,d);
                 	break;
                }
				case 3:
                {
				    d = StrToFloat(FormProperties->Grid->Cells[1][nRow]);
		            vlPropPutDbl(VD_CIRCLE_R,nEntityIndex,d);
                 	break;
                }
            }
            break;
        }
        case VL_ENT_ARC:// Arc
        case VL_ENT_ARC2:// Arc2
        {
            switch(nRow)
            {
				case 1:
                {
				    d = StrToFloat(FormProperties->Grid->Cells[1][nRow]);
            		vlPropPutDbl(VD_ARC_X,nEntityIndex,d);
                 	break;
                }
				case 2:
                {
				    d = StrToFloat(FormProperties->Grid->Cells[1][nRow]);
            		vlPropPutDbl(VD_ARC_Y,nEntityIndex,d);
                 	break;
                }
				case 3:
                {
				    d = StrToFloat(FormProperties->Grid->Cells[1][nRow]);
		            vlPropPutDbl(VD_ARC_RH,nEntityIndex,d);
                 	break;
                }
				case 4:
                {
				    d = StrToFloat(FormProperties->Grid->Cells[1][nRow]);
		            vlPropPutDbl(VD_ARC_RV,nEntityIndex,d);
                 	break;
                }
				case 5:
                {
				    d = StrToFloat(FormProperties->Grid->Cells[1][nRow]);
		            vlPropPutDbl(VD_ARC_ANG0,nEntityIndex,d);
                 	break;
                }
				case 6:
                {
				    d = StrToFloat(FormProperties->Grid->Cells[1][nRow]);
		            vlPropPutDbl(VD_ARC_ANGARC,nEntityIndex,d);
                 	break;
                }
				case 7:
                {
				    d = StrToFloat(FormProperties->Grid->Cells[1][nRow]);
		            vlPropPutDbl(VD_ARC_ANGROT,nEntityIndex,d);
                 	break;
                }
            }
            break;
        }
        case VL_ENT_ELLIPSE:// Ellipse
        {
            switch(nRow)
            {
				case 1:
                {
				    d = StrToFloat(FormProperties->Grid->Cells[1][nRow]);
            		vlPropPutDbl(VD_ELLIPSE_X,nEntityIndex,d);
                 	break;
                }
				case 2:
                {
				    d = StrToFloat(FormProperties->Grid->Cells[1][nRow]);
            		vlPropPutDbl(VD_ELLIPSE_Y,nEntityIndex,d);
                 	break;
                }
				case 3:
                {
				    d = StrToFloat(FormProperties->Grid->Cells[1][nRow]);
		            vlPropPutDbl(VD_ELLIPSE_RH,nEntityIndex,d);
                 	break;
                }
				case 4:
                {
				    d = StrToFloat(FormProperties->Grid->Cells[1][nRow]);
		            vlPropPutDbl(VD_ELLIPSE_RV,nEntityIndex,d);
                 	break;
                }
				case 5:
                {
				    d = StrToFloat(FormProperties->Grid->Cells[1][nRow]);
		            vlPropPutDbl(VD_ELLIPSE_ANGLE,nEntityIndex,d);
                 	break;
                }
            }
            break;
        }
        case VL_ENT_TEXT:// Text
        {
            break;
        }
        case VL_ENT_BITMAP:// Bitmap
        {
            break;
        }
        case VL_ENT_INSBLOCK:// Block insertion
        {
            break;
        }
        case VL_ENT_HATCH:// Hatch
        {
            break;
        }
        case VL_ENT_FLOOD:// Flood
        {
            break;
        }
        case VL_ENT_RECT:// Rectangle
        {
            switch(nRow)
            {
				case 1:
                {
				    d = StrToFloat(FormProperties->Grid->Cells[1][nRow]);
            		vlPropPutDbl(VD_RECT_XCEN,nEntityIndex,d);
                 	break;
                }
				case 2:
                {
				    d = StrToFloat(FormProperties->Grid->Cells[1][nRow]);
            		vlPropPutDbl(VD_RECT_YCEN,nEntityIndex,d);
                 	break;
                }
				case 3:
                {
				    d = StrToFloat(FormProperties->Grid->Cells[1][nRow]);
		            vlPropPutDbl(VD_RECT_WIDTH,nEntityIndex,d);
                 	break;
                }
				case 4:
                {
				    d = StrToFloat(FormProperties->Grid->Cells[1][nRow]);
		            vlPropPutDbl(VD_RECT_HEIGHT,nEntityIndex,d);
                 	break;
                }
				case 5:
                {
				    d = StrToFloat(FormProperties->Grid->Cells[1][nRow]);
		            vlPropPutDbl(VD_RECT_ANGLE,nEntityIndex,d);
                 	break;
                }
				case 6:
                {
				    d = StrToFloat(FormProperties->Grid->Cells[1][nRow]);
		            vlPropPutDbl(VD_RECT_RADIUS,nEntityIndex,d);
                 	break;
                }
            }
            break;
        }
        case VL_ENT_DIMLIN:// DIMLIN
        {
            break;
        }
        case VL_ENT_DIMANG:// DIMANG
        {
            break;
        }
        case VL_ENT_DIMRAD:// DIMRAD
        {
            break;
        }
        case VL_ENT_DIMDIAM:// DIMDIAM
        {
            break;
        }
        case VL_ENT_DIMORD:// DIMORD
        {
            break;
        }
        case VL_ENT_DWGINS:// DWGINS
        {
            break;
        }
        case VL_ENT_CUSTOM:// CUSTOM
        {
            break;
        }
    }
    vlRedraw();
*/
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ActivateEntity(int nEntityIndex)
{
	if(nEntityIndex >= 0)
    {
	    cad_Entity CadEntity;
    	CadEntityGetExData(nEntityIndex,&CadEntity);

        CSpinEditDepth->Value = CadEntity.dDepth;

        ComboBoxTools->ItemIndex = CadEntity.nToolIndex;
        ComboBoxToolsChange(NULL);
    }
    else
    {
          ListBoxEntities->ItemIndex = -1;
    }
//    ShowEntityProperty(nEntityIndex);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ListBoxEntitiesClick(TObject *Sender)
{
	if(ListBoxEntities->ItemIndex < 0)	return;
	int nEntity;
    nEntity = (int)ListBoxEntities->Items->Objects[ListBoxEntities->ItemIndex];
    ActivateEntity(nEntity);
    CadSelClear(hDwg);
	CadSelectEntity(hDwg,nEntity,true);
    CadSelMakeGrips(hDwg);
    CadUpdate(hDwg);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AToolsOptionsExecute(TObject *Sender)
{
	// Language
    switch(m_nLanguageID)
    {
        case 0:
        {
			FormOptions->ToolButton2->Click();
            FormOptions->ToolButton1->Down = false;
            FormOptions->ToolButton2->Down = true;
            FormOptions->ToolButton3->Down = false;
            break;
        }
        case 1:
        {
			FormOptions->ToolButton1->Click();
            FormOptions->ToolButton1->Down = true;
            FormOptions->ToolButton2->Down = false;
            FormOptions->ToolButton3->Down = false;
            break;
        }
        case 2:
        {
			FormOptions->ToolButton3->Click();
            FormOptions->ToolButton1->Down = false;
            FormOptions->ToolButton2->Down = false;
            FormOptions->ToolButton3->Down = true;
            break;
        }
    }


    if(PageControl->ActivePageIndex >= 0)
    {
        // Grid
        double x,y,z;
        int X,Y,Z;
        CadGridGetSize(hDwg,&x,&y,&z);
        CadGridGetBoldStep(hDwg,&X,&Y,&Z);
        FormOptions->EditGridSmallStepX->Text = FormatFloat("0.00",x);
        FormOptions->EditGridSmallStepY->Text = FormatFloat("0.00",y);
        FormOptions->EditGridLargeStepX->Text = IntToStr(X);
        FormOptions->EditGridLargeStepY->Text = IntToStr(Y);
        FormOptions->CheckBoxGridSnap->Checked = CadGridGetSnap(hDwg);
        FormOptions->CheckBoxGridShow->Checked = CadGridGetShow(hDwg);
        FormOptions->PanelGridSmallColor->Color = (TColor)CadGridGetColor(hDwg,false);
        FormOptions->PanelGridLargeColor->Color = (TColor)CadGridGetColor(hDwg,true);
    }
	if(FormOptions->ShowModal() != mrOk)	return;

    // Grid
    m_dGridSmallStepX = StrToFloat(FormOptions->EditGridSmallStepX->Text);
    m_dGridSmallStepY = StrToFloat(FormOptions->EditGridSmallStepY->Text);
	m_nGridLargeStepX = StrToInt(FormOptions->EditGridLargeStepX->Text);
	m_nGridLargeStepY = StrToInt(FormOptions->EditGridLargeStepY->Text);
	m_bGridSnap = FormOptions->CheckBoxGridSnap->Checked;
    m_bGridShow = FormOptions->CheckBoxGridShow->Checked;
    m_nGridSmallColor = FormOptions->PanelGridSmallColor->Color;
	m_nGridLargeColor = FormOptions->PanelGridLargeColor->Color;

    if(PageControl->ActivePageIndex >= 0)
    {
        CadGridPutSize(hDwg,m_dGridSmallStepX,m_dGridSmallStepY,m_dGridSmallStepX);
        CadGridPutBoldStep(hDwg,m_nGridLargeStepX,m_nGridLargeStepY,m_nGridLargeStepX);
        CadGridPutSnap(hDwg,m_bGridSnap);
        CadGridPutShow(hDwg,m_bGridShow);
        CadGridPutColor(hDwg,false,m_nGridSmallColor);
        CadGridPutColor(hDwg,true,m_nGridLargeColor);
	}
    if(m_nLanguageID != FormOptions->PanelLanguage->Tag)
    {
	    m_nLanguageID = FormOptions->PanelLanguage->Tag;
	    MessageDlg(FormOptions->LabelRestartProg->Caption,mtInformation,TMsgDlgButtons()<<mbOK,0);
    }
    SaveSettings();
    if(PageControl->ActivePageIndex >= 0)
    {
	    CadUpdate(hDwg);
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AFileImportExecute(TObject *Sender)
{
//	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AFileExportExecute(TObject *Sender)
{
//	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ADrawSplineExecute(TObject *Sender)
{
  	CadExecute(hDwg,hVecWnd,CAD_CMD_DRAW_SPLINE);
//	vlExecute(VC_DRAW_SPLINE);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ADrawArcExecute(TObject *Sender)
{
//	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ADrawCircleExecute(TObject *Sender)
{
//	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::APluginExecute(TObject *Sender)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::CSpinEditDepthChange(TObject *Sender)
{
	g_dCurrDepth = CSpinEditDepth->Value;
	if(ListBoxEntities->ItemIndex < 0)	return;
	int nEntityIndex;
    nEntityIndex = (int)ListBoxEntities->Items->Objects[ListBoxEntities->ItemIndex];

    cad_Entity CadEntity;
    CadEntityGetExData(nEntityIndex,&CadEntity);
    CadEntity.dDepth = g_dCurrDepth;
	CadEntityPutExData(nEntityIndex,&CadEntity,sizeof(CadEntity));
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AEntityUpExecute(TObject *Sender)
{
/*
	if(ListBoxEntities->ItemIndex < 0)	return;
    if(ListBoxEntities->ItemIndex < 1)	return;
	int nIndex,nUpIndex;
	int nEntityIndex,nUpEntityIndex;
    nIndex = ListBoxEntities->ItemIndex;
    nUpIndex = ListBoxEntities->ItemIndex-1;
    nEntityIndex = (int)ListBoxEntities->Items->Objects[nIndex];
    nUpEntityIndex = (int)ListBoxEntities->Items->Objects[nUpIndex];
	vlEntSwap(nEntityIndex,nUpEntityIndex);
    vlRedraw();
    ListBoxEntities->Items->Exchange(nIndex,nUpIndex);
    ListBoxEntities->Items->Objects[nIndex] = (TObject *)nEntityIndex;
    ListBoxEntities->Items->Objects[nUpIndex] = (TObject *)nUpEntityIndex;
*/
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::AEntityDownExecute(TObject *Sender)
{
/*
	if(ListBoxEntities->ItemIndex < 0)	return;
    if(ListBoxEntities->ItemIndex >= ListBoxEntities->Items->Count-1)	return;
	int nIndex,nDownIndex;
	int nEntityIndex,nDownEntityIndex;
    nIndex = ListBoxEntities->ItemIndex;
    nDownIndex = ListBoxEntities->ItemIndex+1;
    nEntityIndex = (int)ListBoxEntities->Items->Objects[nIndex];
    nDownEntityIndex = (int)ListBoxEntities->Items->Objects[nDownIndex];
	vlEntSwap(nEntityIndex,nDownEntityIndex);
    vlRedraw();
    ListBoxEntities->Items->Exchange(nIndex,nDownIndex);
    ListBoxEntities->Items->Objects[nIndex] = (TObject *)nEntityIndex;
    ListBoxEntities->Items->Objects[nDownIndex] = (TObject *)nDownEntityIndex;
*/
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::AEntityBuildListExecute(TObject *Sender)
{
	BuildEntitiesList();	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ComboBoxToolsChange(TObject *Sender)
{
	if(ComboBoxTools->ItemIndex < 0)	return;
	g_nCurrToolIndex = ComboBoxTools->ItemIndex;
	PanelTool->Color = (TColor)g_pTools[ComboBoxTools->ItemIndex].nColor;
    PanelToolName->Caption = g_pTools[ComboBoxTools->ItemIndex].strName;
	if(ListBoxEntities->ItemIndex < 0)	return;
	int nEntityIndex;
    nEntityIndex = (int)ListBoxEntities->Items->Objects[ListBoxEntities->ItemIndex];

    cad_Entity CadEntity;
    CadEntityGetExData(nEntityIndex,&CadEntity);
    CadEntity.nToolIndex = g_nCurrToolIndex;
	CadEntityPutExData(nEntityIndex,&CadEntity,sizeof(CadEntity));

	CadEntityPutColor(nEntityIndex,ComboBoxTools->ItemIndex);
    CadUpdate(hDwg);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ADrawSpiralExecute(TObject *Sender)
{
	cad_Spiral data;
    data.x = 500.0;
    data.y = 500.0;
    data.z = 0.0;
    data.a = 10.0;
    data.v = 50.0;
    data.r0 = 100.0;
    data.dTours = 10.0;
    data.dStep = 60.0;
    data.bLines = false;
	cad_AddSpiral(hDwg,data);
//	vlExecute(spl_CMD_SPIRAL);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ADrawSpiral2Execute(TObject *Sender)
{
//	vlExecute(spl_CMD_SPIRAL_2);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ADrawSquareExecute(TObject *Sender)
{
  	CadExecute(hDwg,hVecWnd,CAD_CMD_DRAW_SQUARE);
//	vlExecute(spl_CMD_SQUARE);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ApplicationEventsHint(TObject *Sender)
{
	StatusBar->SimpleText = Application->Hint;	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::PageControlResize(TObject *Sender)
{
	if(PageControl->ActivePage == NULL)	return;
    if(hVecWnd <= 0)	return;
    if(hDwg <= 0)	return;
	int W,H;
    // get size of the form window
    vuGetWindowSize(PageControl->ActivePage->Handle,&W,&H);
    if((W > 0) && (H > 0))
    {
        CadWndResize(hVecWnd,0,0,W,H);

        // create window to enter VeCAD commands commands
        CadCWResize(0,0,PanelCommandLine->ClientWidth,PanelCommandLine->ClientHeight);
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::PageControlChange(TObject *Sender)
{
	ActivateDesigner();
}
//---------------------------------------------------------------------------

