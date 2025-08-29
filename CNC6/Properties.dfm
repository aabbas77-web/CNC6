object FormProperties: TFormProperties
  Left = 334
  Top = 353
  Width = 228
  Height = 216
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSizeToolWin
  Caption = 'Properties'
  Color = 14671839
  Ctl3D = False
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Grid: TStringGrid
    Left = 0
    Top = 0
    Width = 220
    Height = 189
    Align = alClient
    ColCount = 2
    Ctl3D = False
    DefaultColWidth = 100
    DefaultRowHeight = 20
    FixedColor = 14671839
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing, goEditing, goTabs, goThumbTracking]
    ParentCtl3D = False
    TabOrder = 0
    OnKeyDown = GridKeyDown
    OnMouseUp = GridMouseUp
    OnSelectCell = GridSelectCell
    OnSetEditText = GridSetEditText
    RowHeights = (
      20
      20
      20
      20
      20)
  end
end
