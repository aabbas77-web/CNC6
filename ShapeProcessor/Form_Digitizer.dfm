object FormDigitizer: TFormDigitizer
  Left = 190
  Top = 105
  Width = 544
  Height = 375
  Caption = 'Digitizer'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object StatusBar: TStatusBar
    Left = 0
    Top = 310
    Width = 536
    Height = 19
    Panels = <
      item
        Alignment = taCenter
        Width = 100
      end
      item
        Alignment = taCenter
        Width = 100
      end
      item
        Alignment = taCenter
        Width = 100
      end
      item
        Alignment = taCenter
        Width = 100
      end>
    SimplePanel = False
  end
  object ScrollBox: TScrollBox
    Left = 0
    Top = 0
    Width = 485
    Height = 310
    HorzScrollBar.Tracking = True
    VertScrollBar.Tracking = True
    Align = alClient
    TabOrder = 1
    object Image: TImage
      Left = 0
      Top = 0
      Width = 105
      Height = 105
      AutoSize = True
      OnMouseDown = ImageMouseDown
      OnMouseMove = ImageMouseMove
      OnMouseUp = ImageMouseUp
    end
  end
  object DrawGridColors: TDrawGrid
    Left = 485
    Top = 0
    Width = 51
    Height = 310
    Cursor = crHandPoint
    Align = alRight
    ColCount = 1
    Ctl3D = False
    DefaultColWidth = 32
    DefaultRowHeight = 32
    FixedCols = 0
    RowCount = 1
    FixedRows = 0
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goTabs, goThumbTracking]
    ParentCtl3D = False
    ScrollBars = ssVertical
    TabOrder = 2
    OnDrawCell = DrawGridColorsDrawCell
  end
  object OpenPictureDialog: TOpenPictureDialog
    DefaultExt = 'jpg'
    Filter = 
      'All (*.jpg;*.jpeg;*.bmp;*.emf;*.wmf)|*.jpg;*.jpeg;*.bmp;*.emf;*.' +
      'wmf|JPEG Image File (*.jpg)|*.jpg|JPEG Image File (*.jpeg)|*.jpe' +
      'g|Bitmaps (*.bmp)|*.bmp|Enhanced Metafiles (*.emf)|*.emf|Metafil' +
      'es (*.wmf)|*.wmf'
    Left = 210
    Top = 122
  end
  object MainMenu1: TMainMenu
    Left = 210
    Top = 150
    object File1: TMenuItem
      Action = AFile
      object Open1: TMenuItem
        Action = AFileOpen
      end
      object N1: TMenuItem
        Action = ASeparator
      end
      object Saveas1: TMenuItem
        Action = AFileSaveAs
      end
      object N2: TMenuItem
        Action = ASeparator
      end
      object Exit1: TMenuItem
        Action = AFileExit
      end
    end
    object Processing1: TMenuItem
      Action = AProcessing
      object Quantize1: TMenuItem
        Action = AProcessingQuantize
      end
    end
  end
  object ActionList1: TActionList
    Left = 238
    Top = 150
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
      Caption = 'Save as...'
      OnExecute = AFileSaveAsExecute
    end
    object AFileExit: TAction
      Category = 'File'
      Caption = 'Exit'
      OnExecute = AFileExitExecute
    end
    object ASeparator: TAction
      Category = 'Other'
      Caption = '-'
    end
    object AProcessing: TAction
      Category = 'Processing'
      Caption = 'Processing'
      OnExecute = AProcessingExecute
    end
    object AProcessingQuantize: TAction
      Category = 'Processing'
      Caption = 'Quantize...'
      OnExecute = AProcessingQuantizeExecute
    end
  end
  object SavePictureDialog: TSavePictureDialog
    DefaultExt = 'jpg'
    Filter = 
      'All (*.jpg;*.bmp)|*.jpg;*.bmp|JPEG Image File (*.jpg)|*.jpg|Bitm' +
      'aps (*.bmp)|*.bmp'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofEnableSizing]
    Left = 238
    Top = 122
  end
end
