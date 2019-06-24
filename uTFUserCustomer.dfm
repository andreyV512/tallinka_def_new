object FUserCustomer: TFUserCustomer
  Left = 0
  Top = 0
  Caption = #1054#1087#1077#1088#1072#1090#1086#1088'/'#1047#1072#1082#1072#1079#1095#1080#1082
  ClientHeight = 276
  ClientWidth = 713
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = [fsBold]
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object LUsers: TLabel
    Left = 8
    Top = 5
    Width = 67
    Height = 13
    Caption = #1054#1087#1077#1088#1072#1090#1086#1088#1099
  end
  object LCustomers: TLabel
    Left = 264
    Top = 5
    Width = 60
    Height = 13
    Caption = #1047#1072#1082#1072#1079#1095#1080#1082#1080
  end
  object GUsers: TDBGrid
    Left = 8
    Top = 24
    Width = 240
    Height = 120
    DataSource = DSUsers
    Options = [dgEditing, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit, dgTitleClick, dgTitleHotTrack]
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = [fsBold]
  end
  object NUsers: TDBNavigator
    Left = 8
    Top = 150
    Width = 240
    Height = 25
    DataSource = DSUsers
    TabOrder = 1
  end
  object GCustomers: TDBGrid
    Left = 264
    Top = 24
    Width = 240
    Height = 120
    DataSource = DSCustomers
    Options = [dgEditing, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit, dgTitleClick, dgTitleHotTrack]
    TabOrder = 2
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = [fsBold]
  end
  object NCustomers: TDBNavigator
    Left = 264
    Top = 150
    Width = 240
    Height = 25
    DataSource = DSCustomers
    TabOrder = 3
  end
  object TUsers: TADOTable
    TableName = 'Users'
    Left = 64
    Top = 192
  end
  object DSUsers: TDataSource
    DataSet = TUsers
    Left = 16
    Top = 192
  end
  object DSCustomers: TDataSource
    DataSet = TCustomers
    Left = 264
    Top = 192
  end
  object TCustomers: TADOTable
    TableName = 'Customers'
    Left = 312
    Top = 192
  end
end
