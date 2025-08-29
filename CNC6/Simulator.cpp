//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Simulator.h"
#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma link "FormTranslation"
#pragma link "CPort"
#pragma resource "*.dfm"
TFormSimulator *FormSimulator;
//---------------------------------------------------------------------------
__fastcall TFormSimulator::TFormSimulator(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
bool IsPointInRect(int x,int y,TRect &R)
{
	return ((x >= R.left) && (x <= R.right) && (y >= R.top) && (y <= R.bottom));
}
//---------------------------------------------------------------------------
void __fastcall TFormSimulator::DrawCNCStitch()
{
	if(CNCFile.size() < 2)	return;
    if(m_nCurrentIndex < 1)	return;
    if(m_nCurrentIndex >= (int)CNCFile.size())	return;
	cnc_Stitch os,s;
    os = CNCFile[m_nCurrentIndex-1];
    s = CNCFile[m_nCurrentIndex];
    int nObjIndex;
    static int nColor = clBlack;
	nObjIndex = CadAddLine(hDwg,os.x,os.y,0,s.x,s.y,0);
    switch(s.cmd)
    {
        case stNormal:// Continous Line
        {
            CadEntityPutColor(nObjIndex,nColor);
            break;
        }
        case stJump:// Discrete Line
        {
            CadEntityPutColor(nObjIndex,190);
            break;
        }
        default:
        {
        	if(s.cmd <= stTool_9)	nColor = s.cmd;
         	break;
        }
    }
    // Draw Machine Head
    CadRectPutCenter(g_hMachineHeadIndex,s.x,s.y,0);

	CadUpdate(hDwg);
}
//---------------------------------------------------------------------------
void __fastcall TFormSimulator::DrawCNCFile()
{
	if(CNCFile.size() < 2)	return;
	cnc_Stitch os,s;
    int nObjIndex;
    static int nColor = clBlack;
    os = CNCFile[0];
	for(UINT i=1;i<CNCFile.size();i++)
    {
		s = CNCFile[i];
		nObjIndex = CadAddLine(hDwg,os.x,os.y,0,s.x,s.y,0);
        switch(s.cmd)
        {
            case stNormal:// Continous Line
            {
            	CadEntityPutColor(nObjIndex,nColor);
                break;
            }
            case stJump:// Discrete Line
            {
            	CadEntityPutColor(nObjIndex,190);
                break;
            }
            default:
            {
                if(s.cmd <= stTool_9)	nColor = s.cmd;
                break;
            }
        }
        os = s;
    }

    // Show All
	CadUpdate(hDwg);
	CadExecute(hDwg,hVecWnd,CAD_CMD_ZOOM_EXT);
}
//---------------------------------------------------------------------------
void __fastcall TFormSimulator::NewDocument(AnsiString strFileName)
{
    hDwg = CadCreate();
    hVecWnd = CadWndCreate(hDwg,PanelDisplay->Handle,CAD_WS_DEFAULT,0,0,100,100);
    
	PanelDisplayResize(NULL);

    VHANDLE hPage = CadAddPage(hDwg,"Drawing",CAD_PAPER_USER,
    							CAD_PAPER_ALBUM,FormMain->m_dWorkingAreaWidthMM,
                                FormMain->m_dWorkingAreaHeightMM);
	CadSetCurPage(hDwg,hPage);
  	VHANDLE hModelPage = CadGetPageByName(hDwg,"Model");
  	if(hModelPage)
    {
    	CadDeletePage(hDwg,hModelPage);
  	}
  	CadRegen(hDwg);
  	CadExecute(hDwg,hVecWnd,CAD_CMD_ZOOM_EXT);

    // Machine Head
    g_hMachineHeadIndex = CadAddRect(hDwg,0,0,0,FormMain->m_dWorkingAreaWidthMM/20.0, FormMain->m_dWorkingAreaHeightMM/20.0,0);
	CadEntityPutColor(g_hMachineHeadIndex,1);
}
//---------------------------------------------------------------------------
void __fastcall TFormSimulator::ClearDrawing()
{
	CadSelectEntity(hDwg,NULL,true);
	CadSelErase(hDwg);
    CadUpdate(hDwg);
}
//---------------------------------------------------------------------------
void __fastcall TFormSimulator::SendStitch(cnc_Stitch &Stitch)
{
    if(!ComPort->Connected)
    {
        ComPort->ShowSetupDialog();
        ComPort->Connected = true;
    }
    if(!ComPort->Connected)	return;

    Packet.cmd = Stitch.cmd;
	Packet.x = Stitch.x;
    Packet.y = Stitch.y;
    Packet.z = Stitch.z;
    Packet.Vx = Stitch.Vx;
    Packet.Vy = Stitch.Vy;
    Packet.Vz = Stitch.Vz;
    Packet.Ax = Stitch.Ax;
    Packet.Ay = Stitch.Ay;
    Packet.Az = Stitch.Az;
    ComPort->Write(&Packet,40);
}
//---------------------------------------------------------------------------
void __fastcall TFormSimulator::AFileExecute(TObject *Sender)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormSimulator::AFileOpenExecute(TObject *Sender)
{
	if(OpenDialogPLT->Execute())
    {
    	if(!cnc_LoadCNCFile(OpenDialogPLT->FileName,CNCFile))	return;
        ClearDrawing();
		DrawCNCFile();

        Timer->Enabled = false;
		m_nCurrentIndex = -1;
        UpDown->Max = CNCFile.size();
        EditCurrentIndex->Text = "-1";
    	EditElementIndex->Text = FormatFloat("0",m_nCurrentIndex);
        EditTotalElements->Text = FormatFloat("0",CNCFile.size());

		ASimulatorPlay->Enabled = true;
		ASimulatorPause->Enabled = !ASimulatorPlay->Enabled;
		ASimulatorStop->Enabled = !ASimulatorPlay->Enabled;
		ASimulatorNext->Enabled = ASimulatorPlay->Enabled;
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormSimulator::AFileSaveExecute(TObject *Sender)
{
    if(SaveDialogPLT->FileName == "")
    	AFileSaveAsExecute(NULL);
    else
	    cnc_SaveCNCFile(SaveDialogPLT->FileName,CNCFile);
}
//---------------------------------------------------------------------------
void __fastcall TFormSimulator::AFileSaveAsExecute(TObject *Sender)
{
	if(SaveDialogPLT->Execute())
    {
		cnc_SaveCNCFile(SaveDialogPLT->FileName,CNCFile);
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormSimulator::AFileCloseExecute(TObject *Sender)
{
	Close();	
}
//---------------------------------------------------------------------------
void __fastcall TFormSimulator::ASimulatorExecute(TObject *Sender)
{
//	
}
//---------------------------------------------------------------------------

void __fastcall TFormSimulator::ASimulatorPlayExecute(TObject *Sender)
{
	if(m_nCurrentIndex == -1)
    {
        ClearDrawing();
    }

    ASimulatorPlay->Enabled = false;
    ASimulatorPause->Enabled = !ASimulatorPlay->Enabled;
    ASimulatorStop->Enabled = !ASimulatorPlay->Enabled;
    ASimulatorNext->Enabled = ASimulatorPlay->Enabled;

	Timer->Interval = CSpinEditDelay->Value;
    Timer->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TFormSimulator::ASimulatorPauseExecute(TObject *Sender)
{
    ASimulatorPlay->Enabled = true;
    ASimulatorPause->Enabled = !ASimulatorPlay->Enabled;
    ASimulatorStop->Enabled = !ASimulatorPlay->Enabled;
    ASimulatorNext->Enabled = ASimulatorPlay->Enabled;

    Timer->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TFormSimulator::ASimulatorStopExecute(TObject *Sender)
{
    ASimulatorPlay->Enabled = true;
    ASimulatorPause->Enabled = !ASimulatorPlay->Enabled;
    ASimulatorStop->Enabled = !ASimulatorPlay->Enabled;
    ASimulatorNext->Enabled = ASimulatorPlay->Enabled;

    Timer->Enabled = false;
	m_nCurrentIndex = -1;
    EditCurrentIndex->Text = "-1";
    EditElementIndex->Text = FormatFloat("0",m_nCurrentIndex);
    ClearDrawing();
}
//---------------------------------------------------------------------------

void __fastcall TFormSimulator::ASimulatorNextExecute(TObject *Sender)
{
	if(m_nCurrentIndex == -1)
    {
        ClearDrawing();
    }

    ASimulatorPlay->Enabled = true;
    ASimulatorPause->Enabled = !ASimulatorPlay->Enabled;
    ASimulatorStop->Enabled = !ASimulatorPlay->Enabled;
    ASimulatorNext->Enabled = ASimulatorPlay->Enabled;

	TimerTimer(NULL);
}
//---------------------------------------------------------------------------

void __fastcall TFormSimulator::TimerTimer(TObject *Sender)
{
	m_nCurrentIndex++;
	if(m_nCurrentIndex < (int)CNCFile.size())
    {
        DrawCNCStitch();

    	CNCStitch = CNCFile[m_nCurrentIndex];
        EditCurrentIndex->Text = IntToStr(m_nCurrentIndex);
        EditCurrentPositionX->Text = IntToStr((int)(CNCStitch.x));
        EditCurrentPositionY->Text = IntToStr((int)(CNCStitch.y));
        EditCurrentPositionZ->Text = IntToStr((int)(CNCStitch.z));
        EditSpeedX->Text = FormatFloat("0",CNCStitch.Vx);
        EditSpeedY->Text = FormatFloat("0",CNCStitch.Vy);
        if(CNCStitch.cmd <= stTool_9)	EditTool->Text = FormatFloat("0",CNCStitch.cmd);

        Label5->Font->Color = (IsPointInRect(CNCStitch.x,CNCStitch.y,WorkingAreaBox)?clBlack:clRed);
    }
    else
    {
        ASimulatorPlay->Enabled = true;
        ASimulatorPause->Enabled = !ASimulatorPlay->Enabled;
        ASimulatorStop->Enabled = !ASimulatorPlay->Enabled;
        ASimulatorNext->Enabled = ASimulatorPlay->Enabled;

        Timer->Enabled = false;
        m_nCurrentIndex = -1;
        EditCurrentIndex->Text = "-1";
    }
    EditElementIndex->Text = FormatFloat("0",m_nCurrentIndex);
}
//---------------------------------------------------------------------------

void __fastcall TFormSimulator::FormCreate(TObject *Sender)
{
	m_nCurrentIndex = -1;
    EditCurrentIndex->Text = "-1";
    EditElementIndex->Text = FormatFloat("0",m_nCurrentIndex);
    d = 40;

    Timer->Enabled = false;
	Timer->Interval = CSpinEditDelay->Value;

    m_strAppTitle = Caption;

    NewDocument("Simulator");
}
//---------------------------------------------------------------------------

void __fastcall TFormSimulator::FormDestroy(TObject *Sender)
{
	CadDelete(hDwg);
	ComPort->Connected = false;
}
//---------------------------------------------------------------------------

void __fastcall TFormSimulator::CSpinEditDelayChange(TObject *Sender)
{
	Timer->Interval = CSpinEditDelay->Value;
}
//---------------------------------------------------------------------------

void __fastcall TFormSimulator::FormClose(TObject *Sender,
      TCloseAction &Action)
{
	ASimulatorStopExecute(NULL);	
}
//---------------------------------------------------------------------------


void __fastcall TFormSimulator::AMachineExecute(TObject *Sender)
{
//	
}
//---------------------------------------------------------------------------
void __fastcall TFormSimulator::CalculateSpeeds()
{
	if(CNCFile.size() < 2)	return;
	cnc_Stitch os,s;
    double dLength;
    double dSpeed;
    AnsiString strText = 100.0;
    if(!InputQuery("Speed","Enter Speed (m/s):",strText))	return;
    dSpeed = StrToFloat(strText);
    os = CNCFile[0];
	for(UINT i=1;i<CNCFile.size();i++)
    {
		s = CNCFile[i];

        dLength = cnc_Distance(s,os);
        if(dLength <= 0.0)	continue;
        s.Vx = dSpeed*abs(s.x-os.x)/dLength;
        s.Vy = dSpeed*abs(s.y-os.y)/dLength;

        CNCFile[i] = s;
        os = s;
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormSimulator::AMachineGenerateExecute(TObject *Sender)
{
	if(CNCFile.size() < 2)	return;
    if(!SaveDialogCMD->Execute())	return;
    CalculateSpeeds();
    cnc_SaveCMDFile(SaveDialogCMD->FileName,CNCFile);
}
//---------------------------------------------------------------------------
void __fastcall TFormSimulator::AMachineLoadExecute(TObject *Sender)
{
	if(OpenDialogCMD->Execute())
    {
    	if(!cnc_LoadCMDFile(OpenDialogCMD->FileName,CNCFile))	return;
        ClearDrawing();
		DrawCNCFile();

        Timer->Enabled = false;
		m_nCurrentIndex = -1;
        UpDown->Max = CNCFile.size();
        EditCurrentIndex->Text = "-1";
    	EditElementIndex->Text = FormatFloat("0",m_nCurrentIndex);
        EditTotalElements->Text = FormatFloat("0",CNCFile.size());

		ASimulatorPlay->Enabled = true;
		ASimulatorPause->Enabled = !ASimulatorPlay->Enabled;
		ASimulatorStop->Enabled = !ASimulatorPlay->Enabled;
		ASimulatorNext->Enabled = ASimulatorPlay->Enabled;
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormSimulator::AMachineSendExecute(TObject *Sender)
{
    AMachineSend->Checked = !AMachineSend->Checked;
    if(!AMachineSend->Checked)	return;
	if(!ComPort->Connected)
    {
    	ComPort->ShowSetupDialog();
	    ComPort->Connected = true;
    }

    if(m_nCurrentIndex == -1)
    {
        ClearDrawing();
    }
    CalculateSpeeds();
    ComDataPacketPacket(NULL,"A");
}
//---------------------------------------------------------------------------

void __fastcall TFormSimulator::UpDownChangingEx(TObject *Sender,
      bool &AllowChange, short NewValue, TUpDownDirection Direction)
{
	if(Direction != updUp)
    {
    	AllowChange = false;
    	return;
    }
	ASimulatorNextExecute(NULL);
}
//---------------------------------------------------------------------------

void __fastcall TFormSimulator::PanelDisplayResize(TObject *Sender)
{
    if(hVecWnd <= 0)	return;
    if(hDwg <= 0)	return;
	int W,H;
    // get size of the form window
    vuGetWindowSize(PanelDisplay->Handle,&W,&H);
    if((W > 0) && (H > 0))
    {
        CadWndResize(hVecWnd,0,0,W,H);

  		CadExecute(hDwg,hVecWnd,CAD_CMD_ZOOM_EXT);
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormSimulator::ComDataPacketPacket(TObject *Sender,
      AnsiString Str)
{
    if(AMachineSend->Checked)
    {
        m_nCurrentIndex++;
        EditElementIndex->Text = FormatFloat("0",m_nCurrentIndex);
        if(m_nCurrentIndex < (int)CNCFile.size())
        {
        	DrawCNCStitch();

            CNCStitch = CNCFile[m_nCurrentIndex];
        	EditCurrentIndex->Text = IntToStr(m_nCurrentIndex);
            EditCurrentPositionX->Text = IntToStr((int)(CNCStitch.x));
            EditCurrentPositionY->Text = IntToStr((int)(CNCStitch.y));
        	EditCurrentPositionZ->Text = IntToStr((int)(CNCStitch.z));
	        EditSpeedX->Text = FormatFloat("0",CNCStitch.Vx);
    	    EditSpeedY->Text = FormatFloat("0",CNCStitch.Vy);
        	if(CNCStitch.cmd <= stTool_9)	EditTool->Text = FormatFloat("0",CNCStitch.cmd);

            Label5->Font->Color = (IsPointInRect(CNCStitch.x,CNCStitch.y,WorkingAreaBox)?clBlack:clRed);

            if(!ComPort->Connected)
            {
                ComPort->ShowSetupDialog();
                ComPort->Connected = true;
            }
            if(!ComPort->Connected)	return;
            SendStitch(CNCStitch);
        }
        else
        {
            AMachineSend->Checked = false;
            m_nCurrentIndex = -1;
    		EditCurrentIndex->Text = "-1";
        }
    }
}
//---------------------------------------------------------------------------

