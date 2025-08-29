object FormMain: TFormMain
  Left = 190
  Top = 105
  Width = 610
  Height = 375
  Caption = 'Shape Processor'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 602
    Height = 25
    Align = alTop
    AutoSize = True
    BevelOuter = bvNone
    TabOrder = 0
    object ToolBar1: TToolBar
      Left = 0
      Top = 0
      Width = 602
      Height = 25
      AutoSize = True
      ButtonHeight = 21
      ButtonWidth = 48
      Caption = 'ToolBar1'
      EdgeBorders = [ebLeft, ebTop, ebRight, ebBottom]
      Flat = True
      ShowCaptions = True
      TabOrder = 0
      object ToolButton1: TToolButton
        Left = 0
        Top = 0
        Action = AFileOpen
      end
      object ToolButton2: TToolButton
        Left = 48
        Top = 0
        Action = AFileSaveAs
      end
      object ToolButton10: TToolButton
        Left = 96
        Top = 0
        Action = AFileReport
      end
      object ToolButton3: TToolButton
        Left = 144
        Top = 0
        Width = 8
        Caption = 'ToolButton3'
        ImageIndex = 0
        Style = tbsSeparator
      end
      object ToolButton5: TToolButton
        Left = 152
        Top = 0
        Action = AZoomAll
      end
      object ToolButton7: TToolButton
        Left = 200
        Top = 0
        Action = AZoomWin
      end
      object ToolButton9: TToolButton
        Left = 248
        Top = 0
        Action = AZoomOut
      end
      object ToolButton8: TToolButton
        Left = 296
        Top = 0
        Action = AZoomIn
      end
      object ToolButton6: TToolButton
        Left = 344
        Top = 0
        Width = 8
        Caption = 'ToolButton6'
        ImageIndex = 0
        Style = tbsSeparator
      end
      object ToolButton4: TToolButton
        Left = 352
        Top = 0
        Action = ADrawPolyline
      end
      object ToolButton13: TToolButton
        Left = 400
        Top = 0
        Action = ADrawDraw
      end
      object ToolButton14: TToolButton
        Left = 448
        Top = 0
        Action = ADrawDrawSmooth
      end
      object ToolButton11: TToolButton
        Left = 496
        Top = 0
        Action = ADrawClear
      end
      object ToolButton12: TToolButton
        Left = 544
        Top = 0
        Width = 8
        Caption = 'ToolButton12'
        ImageIndex = 0
        Style = tbsSeparator
      end
    end
  end
  object PanelDisplay: TPanel
    Left = 0
    Top = 25
    Width = 602
    Height = 304
    Align = alClient
    BevelOuter = bvLowered
    TabOrder = 1
    OnResize = PanelDisplayResize
  end
  object MainMenu: TMainMenu
    Left = 214
    Top = 84
    object File1: TMenuItem
      Action = AFile
      object Open1: TMenuItem
        Action = AFileOpen
      end
      object Saveas1: TMenuItem
        Action = AFileSaveAs
      end
      object Report1: TMenuItem
        Action = AFileReport
      end
      object N1: TMenuItem
        Action = ASeparator
      end
      object Exit1: TMenuItem
        Action = AFileExit
      end
    end
    object Zoom1: TMenuItem
      Action = AZoom
      object ZoomAll1: TMenuItem
        Action = AZoomAll
      end
      object ZoomWin1: TMenuItem
        Action = AZoomWin
      end
      object ZoomIn1: TMenuItem
        Action = AZoomIn
      end
      object ZoomOut1: TMenuItem
        Action = AZoomOut
      end
    end
    object Draw1: TMenuItem
      Action = ADraw
      object Polyline1: TMenuItem
        Action = ADrawPolyline
      end
      object N2: TMenuItem
        Action = ASeparator
      end
      object Draw2: TMenuItem
        Action = ADrawDraw
      end
      object DrawS1: TMenuItem
        Action = ADrawDrawSmooth
      end
      object Clear1: TMenuItem
        Action = ADrawClear
      end
    end
    object Processing1: TMenuItem
      Action = AProcessing
      object Adjust1: TMenuItem
        Action = AProcessingAdjust
      end
      object Divide1: TMenuItem
        Action = AProcessingDivide
      end
      object SameDivide1: TMenuItem
        Action = AProcessingSameDivide
      end
      object Reassemple1: TMenuItem
        Action = AProcessingReassemple
      end
      object Extrude1: TMenuItem
        Action = AProcessingExtrude
      end
    end
    object Digitizer1: TMenuItem
      Action = ADigitizer
      object Digitizer2: TMenuItem
        Action = ADigitizerDigitizer
      end
    end
  end
  object OpenDialog: TOpenDialog
    DefaultExt = 'txt'
    Filter = 'Text Files (*.txt)|*.txt|Dat Files (*.dat)|*.dat'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofEnableSizing]
    Left = 186
    Top = 112
  end
  object SaveDialog: TSaveDialog
    DefaultExt = 'txt'
    Filter = 'Text Files (*.txt)|*.txt|Dat Files (*.dat)|*.dat'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofEnableSizing]
    Left = 214
    Top = 112
  end
  object ActionList: TActionList
    Left = 186
    Top = 84
    object AZoom: TAction
      Category = 'Zoom'
      Caption = 'Zoom'
      OnExecute = AZoomExecute
    end
    object AProcessing: TAction
      Category = 'Processing'
      Caption = 'Processing'
      OnExecute = AProcessingExecute
    end
    object ADraw: TAction
      Category = 'Draw'
      Caption = 'Draw'
      OnExecute = ADrawExecute
    end
    object ADigitizer: TAction
      Category = 'Digitizer'
      Caption = 'Digitizer'
      OnExecute = ADigitizerExecute
    end
    object AFile: TAction
      Category = 'File'
      Caption = 'File'
      OnExecute = AFileExecute
    end
    object AFileOpen: TAction
      Category = 'File'
      Caption = 'Open...'
      OnExecute = AFileOpenExecute
    end
    object AFileSaveAs: TAction
      Category = 'File'
      Caption = 'Save...'
      OnExecute = AFileSaveAsExecute
    end
    object AFileExit: TAction
      Category = 'File'
      Caption = 'Exit'
      OnExecute = AFileExitExecute
    end
    object ADrawPolyline: TAction
      Category = 'Draw'
      Caption = 'Polyline'
      OnExecute = ADrawPolylineExecute
    end
    object ADrawDraw: TAction
      Category = 'Draw'
      Caption = 'Draw'
      OnExecute = ADrawDrawExecute
    end
    object AProcessingAdjust: TAction
      Category = 'Processing'
      Caption = 'Adjust'
      OnExecute = AProcessingAdjustExecute
    end
    object AZoomAll: TAction
      Category = 'Zoom'
      Caption = 'All'
      OnExecute = AZoomAllExecute
    end
    object AZoomWin: TAction
      Category = 'Zoom'
      Caption = 'Win'
      OnExecute = AZoomWinExecute
    end
    object AZoomIn: TAction
      Category = 'Zoom'
      Caption = '+'
      OnExecute = AZoomInExecute
    end
    object AZoomOut: TAction
      Category = 'Zoom'
      Caption = '--'
      OnExecute = AZoomOutExecute
    end
    object AFileReport: TAction
      Category = 'File'
      Caption = 'Report...'
      OnExecute = AFileReportExecute
    end
    object AProcessingDivide: TAction
      Category = 'Processing'
      Caption = 'Divide...'
      OnExecute = AProcessingDivideExecute
    end
    object AProcessingSameDivide: TAction
      Category = 'Processing'
      Caption = 'Same Divide...'
      OnExecute = AProcessingSameDivideExecute
    end
    object AProcessingReassemple: TAction
      Category = 'Processing'
      Caption = 'Reassemple...'
      OnExecute = AProcessingReassempleExecute
    end
    object ADrawDrawSmooth: TAction
      Category = 'Draw'
      Caption = 'DrawS'
      OnExecute = ADrawDrawSmoothExecute
    end
    object ADrawClear: TAction
      Category = 'Draw'
      Caption = 'Clear'
      OnExecute = ADrawClearExecute
    end
    object ADigitizerDigitizer: TAction
      Category = 'Digitizer'
      Caption = 'Digitizer...'
      OnExecute = ADigitizerDigitizerExecute
    end
    object ASeparator: TAction
      Category = 'Other'
      Caption = '-'
    end
    object AProcessingExtrude: TAction
      Category = 'Processing'
      Caption = 'Extrude...'
      OnExecute = AProcessingExtrudeExecute
    end
  end
end
