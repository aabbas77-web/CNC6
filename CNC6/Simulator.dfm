object FormSimulator: TFormSimulator
  Left = 190
  Top = 105
  Width = 610
  Height = 438
  BorderIcons = [biSystemMenu, biMaximize]
  Caption = 'CNC Simulator'
  Color = 14671839
  Ctl3D = False
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object StatusBar1: TStatusBar
    Left = 0
    Top = 373
    Width = 602
    Height = 19
    AutoHint = True
    Color = 14671839
    Panels = <>
    SimplePanel = False
  end
  object Panel1: TPanel
    Left = 0
    Top = 26
    Width = 100
    Height = 347
    Align = alLeft
    BevelOuter = bvNone
    Color = 14671839
    TabOrder = 1
    object Label1: TLabel
      Left = 4
      Top = 29
      Width = 90
      Height = 13
      AutoSize = False
      Caption = 'Delay'
    end
    object Label3: TLabel
      Left = 4
      Top = 72
      Width = 90
      Height = 13
      AutoSize = False
      Caption = 'Element Index'
    end
    object Label4: TLabel
      Left = 4
      Top = 108
      Width = 90
      Height = 13
      AutoSize = False
      Caption = 'Total Elements'
    end
    object Label5: TLabel
      Left = 4
      Top = 148
      Width = 90
      Height = 13
      AutoSize = False
      Caption = 'Current Position'
    end
    object Label6: TLabel
      Left = 4
      Top = 228
      Width = 90
      Height = 13
      AutoSize = False
      Caption = 'Speed X'
    end
    object Label2: TLabel
      Left = 4
      Top = 264
      Width = 90
      Height = 13
      AutoSize = False
      Caption = 'Speed Y'
    end
    object Label7: TLabel
      Left = 4
      Top = 308
      Width = 90
      Height = 13
      AutoSize = False
      Caption = 'Tool'
    end
    object CheckBoxKeepRatio: TCheckBox
      Left = 4
      Top = 8
      Width = 90
      Height = 17
      Caption = 'Keep Ratio'
      Checked = True
      Ctl3D = False
      ParentCtl3D = False
      State = cbChecked
      TabOrder = 0
    end
    object CSpinEditDelay: TCSpinEdit
      Left = 4
      Top = 44
      Width = 90
      Height = 22
      TabStop = True
      Ctl3D = True
      MaxValue = 1000000
      MinValue = 1
      ParentColor = False
      ParentCtl3D = False
      TabOrder = 1
      Value = 1
      OnChange = CSpinEditDelayChange
    end
    object EditElementIndex: TEdit
      Left = 4
      Top = 88
      Width = 90
      Height = 19
      Color = 14671839
      Ctl3D = False
      ParentCtl3D = False
      ReadOnly = True
      TabOrder = 2
      Text = '0'
    end
    object EditTotalElements: TEdit
      Left = 4
      Top = 124
      Width = 90
      Height = 19
      Color = 14671839
      Ctl3D = False
      ParentCtl3D = False
      ReadOnly = True
      TabOrder = 3
      Text = '0'
    end
    object EditCurrentPositionX: TEdit
      Left = 4
      Top = 164
      Width = 90
      Height = 19
      Color = 14671839
      Ctl3D = False
      ParentCtl3D = False
      ReadOnly = True
      TabOrder = 4
      Text = '0'
    end
    object EditSpeedX: TEdit
      Left = 4
      Top = 244
      Width = 90
      Height = 19
      Color = 14671839
      Ctl3D = False
      ParentCtl3D = False
      ReadOnly = True
      TabOrder = 5
      Text = '0'
    end
    object EditCurrentPositionY: TEdit
      Left = 4
      Top = 184
      Width = 90
      Height = 19
      Color = 14671839
      Ctl3D = False
      ParentCtl3D = False
      ReadOnly = True
      TabOrder = 6
      Text = '0'
    end
    object EditSpeedY: TEdit
      Left = 4
      Top = 280
      Width = 90
      Height = 19
      Color = 14671839
      Ctl3D = False
      ParentCtl3D = False
      ReadOnly = True
      TabOrder = 7
      Text = '0'
    end
    object EditCurrentPositionZ: TEdit
      Left = 4
      Top = 204
      Width = 90
      Height = 19
      Color = 14671839
      Ctl3D = False
      ParentCtl3D = False
      ReadOnly = True
      TabOrder = 8
      Text = '0'
    end
    object EditTool: TEdit
      Left = 4
      Top = 324
      Width = 90
      Height = 19
      Color = 14671839
      Ctl3D = False
      ParentCtl3D = False
      ReadOnly = True
      TabOrder = 9
      Text = '0'
    end
  end
  object ToolBar1: TToolBar
    Left = 0
    Top = 0
    Width = 602
    Height = 26
    AutoSize = True
    Caption = 'ToolBar1'
    EdgeBorders = [ebLeft, ebTop, ebRight, ebBottom]
    Flat = True
    Images = FormMain.ImageList
    TabOrder = 2
    Transparent = True
    object ToolButton5: TToolButton
      Left = 0
      Top = 0
      Action = AFileOpen
    end
    object ToolButton6: TToolButton
      Left = 23
      Top = 0
      Action = AFileSave
    end
    object ToolButton7: TToolButton
      Left = 46
      Top = 0
      Action = AFileSaveAs
    end
    object ToolButton8: TToolButton
      Left = 69
      Top = 0
      Width = 8
      Caption = 'ToolButton8'
      ImageIndex = 87
      Style = tbsSeparator
    end
    object ToolButton1: TToolButton
      Left = 77
      Top = 0
      Action = ASimulatorPlay
    end
    object ToolButton2: TToolButton
      Left = 100
      Top = 0
      Action = ASimulatorNext
    end
    object ToolButton3: TToolButton
      Left = 123
      Top = 0
      Action = ASimulatorPause
    end
    object ToolButton4: TToolButton
      Left = 146
      Top = 0
      Action = ASimulatorStop
    end
    object ToolButton9: TToolButton
      Left = 169
      Top = 0
      Width = 8
      Caption = 'ToolButton9'
      ImageIndex = 87
      Style = tbsSeparator
    end
    object EditCurrentIndex: TEdit
      Left = 177
      Top = 0
      Width = 60
      Height = 22
      TabOrder = 1
      Text = '-1'
    end
    object UpDown: TUpDown
      Left = 237
      Top = 0
      Width = 15
      Height = 22
      Associate = EditCurrentIndex
      Min = -1
      Position = -1
      TabOrder = 0
      Wrap = False
      OnChangingEx = UpDownChangingEx
    end
  end
  object PanelDisplay: TPanel
    Left = 100
    Top = 26
    Width = 502
    Height = 347
    Align = alClient
    BevelInner = bvLowered
    Color = 14671839
    TabOrder = 3
    OnResize = PanelDisplayResize
  end
  object OpenDialogPLT: TOpenDialog
    DefaultExt = 'plt'
    Filter = 'Plotter Files(*.plt)|*.plt'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofEnableSizing]
    Left = 420
    Top = 188
  end
  object SaveDialogPLT: TSaveDialog
    DefaultExt = 'plt'
    Filter = 'Plotter Files(*.plt)|*.plt'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofEnableSizing]
    Left = 448
    Top = 188
  end
  object ActionList1: TActionList
    Images = FormMain.ImageList
    Left = 420
    Top = 216
    object AFile: TAction
      Category = 'File'
      Caption = '&File'
      Hint = 'File Menu'
      OnExecute = AFileExecute
    end
    object AFileOpen: TAction
      Category = 'File'
      Caption = '&Open...'
      Hint = 'Open Quilting file'
      ImageIndex = 1
      OnExecute = AFileOpenExecute
    end
    object AFileSave: TAction
      Category = 'File'
      Caption = '&Save'
      Hint = 'Save Current changes'
      ImageIndex = 2
      OnExecute = AFileSaveExecute
    end
    object AFileSaveAs: TAction
      Category = 'File'
      Caption = 'Save &As...'
      Hint = 'Save changes as'
      ImageIndex = 73
      OnExecute = AFileSaveAsExecute
    end
    object AFileClose: TAction
      Category = 'File'
      Caption = '&Close'
      Hint = 'Close simluator window'
      ImageIndex = 77
      OnExecute = AFileCloseExecute
    end
    object ASimulator: TAction
      Category = 'Simulator'
      Caption = '&Simulator'
      Hint = 'Simulator Menu'
      OnExecute = ASimulatorExecute
    end
    object ASimulatorPlay: TAction
      Category = 'Simulator'
      Caption = '&Play'
      Enabled = False
      Hint = 'Play current file'
      ImageIndex = 83
      OnExecute = ASimulatorPlayExecute
    end
    object ASimulatorPause: TAction
      Category = 'Simulator'
      Caption = 'Pa&use'
      Enabled = False
      Hint = 'Pause playing current file'
      ImageIndex = 82
      OnExecute = ASimulatorPauseExecute
    end
    object ASimulatorStop: TAction
      Category = 'Simulator'
      Caption = '&Stop'
      Enabled = False
      Hint = 'Stop playing current file'
      ImageIndex = 86
      OnExecute = ASimulatorStopExecute
    end
    object ASimulatorNext: TAction
      Category = 'Simulator'
      Caption = '&Next'
      Enabled = False
      Hint = 'Show Next stitch'
      ImageIndex = 81
      ShortCut = 113
      OnExecute = ASimulatorNextExecute
    end
    object AMachine: TAction
      Category = 'Machine'
      Caption = '&Machine'
      Hint = 'Machine menu'
      OnExecute = AMachineExecute
    end
    object AMachineGenerate: TAction
      Category = 'Machine'
      Caption = 'Generate...'
      Hint = 'Generate machine file'
      OnExecute = AMachineGenerateExecute
    end
    object AMachineLoad: TAction
      Category = 'Machine'
      Caption = 'Load...'
      Hint = 'Load machine file'
      OnExecute = AMachineLoadExecute
    end
    object AMachineSend: TAction
      Category = 'Machine'
      Caption = 'Send'
      Hint = 'Send machine file'
      OnExecute = AMachineSendExecute
    end
  end
  object MainMenu1: TMainMenu
    Images = FormMain.ImageList
    Left = 448
    Top = 216
    object File1: TMenuItem
      Action = AFile
      object Open1: TMenuItem
        Action = AFileOpen
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object Save1: TMenuItem
        Action = AFileSave
      end
      object SaveAs1: TMenuItem
        Action = AFileSaveAs
      end
      object N2: TMenuItem
        Caption = '-'
      end
      object Close1: TMenuItem
        Action = AFileClose
      end
    end
    object Simulator1: TMenuItem
      Action = ASimulator
      object Play1: TMenuItem
        Action = ASimulatorPlay
      end
      object Next1: TMenuItem
        Action = ASimulatorNext
      end
      object Pause1: TMenuItem
        Action = ASimulatorPause
      end
      object Stop1: TMenuItem
        Action = ASimulatorStop
      end
    end
    object Machine1: TMenuItem
      Action = AMachine
      object Generate1: TMenuItem
        Action = AMachineGenerate
      end
      object Load1: TMenuItem
        Action = AMachineLoad
      end
      object Send1: TMenuItem
        Action = AMachineSend
      end
    end
  end
  object FormTranslation1: TFormTranslation
    Left = 448
    Top = 244
  end
  object ComPort: TComPort
    BaudRate = br9600
    Port = 'COM1'
    Parity.Bits = prNone
    StopBits = sbOneStopBit
    DataBits = dbEight
    Events = [evRxChar, evTxEmpty, evRxFlag, evRing, evBreak, evCTS, evDSR, evError, evRLSD, evRx80Full]
    FlowControl.OutCTSFlow = False
    FlowControl.OutDSRFlow = False
    FlowControl.ControlDTR = dtrDisable
    FlowControl.ControlRTS = rtsDisable
    FlowControl.XonXoffOut = False
    FlowControl.XonXoffIn = False
    Left = 392
    Top = 188
  end
  object SaveDialogCMD: TSaveDialog
    DefaultExt = 'cmd'
    Filter = 'Command Files (*.cmd)|*.cmd'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofEnableSizing]
    Left = 392
    Top = 244
  end
  object Timer: TTimer
    Enabled = False
    Interval = 1
    OnTimer = TimerTimer
    Left = 420
    Top = 244
  end
  object OpenDialogCMD: TOpenDialog
    DefaultExt = 'cmd'
    Filter = 'Command Files (*.cmd)|*.cmd'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofEnableSizing]
    Left = 392
    Top = 216
  end
  object ComDataPacket: TComDataPacket
    ComPort = ComPort
    OnPacket = ComDataPacketPacket
    Left = 364
    Top = 188
  end
end
