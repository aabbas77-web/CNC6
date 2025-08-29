object FormExport: TFormExport
  Left = 190
  Top = 105
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'Export'
  ClientHeight = 107
  ClientWidth = 201
  Color = 14671839
  Ctl3D = False
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 72
    Width = 201
    Height = 35
    Align = alBottom
    Color = 14671839
    TabOrder = 0
    object BitBtn1: TBitBtn
      Left = 34
      Top = 5
      Width = 65
      Height = 25
      Caption = 'OK'
      Default = True
      TabOrder = 0
      OnClick = BitBtn1Click
      Glyph.Data = {
        DE010000424DDE01000000000000760000002800000024000000120000000100
        0400000000006801000000000000000000001000000000000000000000000000
        80000080000000808000800000008000800080800000C0C0C000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
        3333333333333333333333330000333333333333333333333333F33333333333
        00003333344333333333333333388F3333333333000033334224333333333333
        338338F3333333330000333422224333333333333833338F3333333300003342
        222224333333333383333338F3333333000034222A22224333333338F338F333
        8F33333300003222A3A2224333333338F3838F338F33333300003A2A333A2224
        33333338F83338F338F33333000033A33333A222433333338333338F338F3333
        0000333333333A222433333333333338F338F33300003333333333A222433333
        333333338F338F33000033333333333A222433333333333338F338F300003333
        33333333A222433333333333338F338F00003333333333333A22433333333333
        3338F38F000033333333333333A223333333333333338F830000333333333333
        333A333333333333333338330000333333333333333333333333333333333333
        0000}
      NumGlyphs = 2
    end
    object BitBtn2: TBitBtn
      Left = 103
      Top = 5
      Width = 65
      Height = 25
      TabOrder = 1
      Kind = bkCancel
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 0
    Width = 201
    Height = 72
    Align = alClient
    Color = 14671839
    TabOrder = 1
    object GroupBox1: TGroupBox
      Left = 8
      Top = 3
      Width = 185
      Height = 60
      TabOrder = 0
      object Label2: TLabel
        Left = 10
        Top = 17
        Width = 80
        Height = 13
        AutoSize = False
        Caption = 'Speed (cm/s)'
      end
      object Label1: TLabel
        Left = 98
        Top = 17
        Width = 80
        Height = 13
        AutoSize = False
        Caption = 'Z Step'
      end
      object EditSpeed: TEdit
        Left = 8
        Top = 32
        Width = 80
        Height = 19
        TabOrder = 0
        Text = '10.0'
      end
      object EditZStep: TEdit
        Left = 96
        Top = 32
        Width = 80
        Height = 19
        TabOrder = 1
        Text = '1.0'
      end
    end
  end
  object FormTranslation1: TFormTranslation
    Left = 156
    Top = 7
  end
end
