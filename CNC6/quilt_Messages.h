//---------------------------------------------------------------------------
#ifndef cad_MessagesH
#define cad_MessagesH
//---------------------------------------------------------------------------
#include "CNCLib.h"
//---------------------------------------------------------------------------
#define spl_CMD_LINE            	VC_CUSTOM+1
#define spl_CMD_POLYLINE        	VC_CUSTOM+2
#define spl_CMD_POLYSATIN       	VC_CUSTOM+3
#define spl_CMD_POLYSHAPE			VC_CUSTOM+4
#define spl_CMD_TEXT       			VC_CUSTOM+5
#define spl_CMD_EXTRUDE_POLYSHAPE  	VC_CUSTOM+6
#define spl_CMD_PLUG_IN			 	VC_CUSTOM+7
#define spl_CMD_POLYARC			 	VC_CUSTOM+8
#define spl_CMD_SPIRAL			 	VC_CUSTOM+9
#define spl_CMD_SPIRAL_2		  	VC_CUSTOM+10
#define spl_CMD_SQUARE		  		VC_CUSTOM+11
//---------------------------------------------------------------------------
typedef enum{ctNone,ctPolySatin} TCommandType;
//---------------------------------------------------------------------------
int CALLBACK DwgProc (int iDwg,UINT Msg,int Prm1,int Prm2,double Prm3,double Prm4,void* Prm5);
//---------------------------------------------------------------------------
void spl_Initialize_Commands();
AnsiString GetEntityName(int nEntType,int nEntIndex);
bool ProcessExecutedCommands(int nCommand,bool bByExecute,bool bExecuted);
//---------------------------------------------------------------------------
extern int g_nEdgeCounts;
extern AnsiString g_strText;
extern TCommandType CommandType;
extern bool g_bGenerateNamesList;
extern bool g_bIsSimulator;
extern int g_nSimulatorDrawingIndex;
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
extern double g_dSpeed;
//---------------------------------------------------------------------------
#endif
