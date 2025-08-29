unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, Comm32;

type
  TForm1 = class(TForm)
    Memo1: TMemo;
    Edit1: TEdit;
    Comm321: TComm32;
    btnStart: TButton;
    btnStop: TButton;
    btnSend: TButton;
    btnSendCR: TButton;
    procedure Comm321ReceiveData(Buffer: Pointer; BufferLength: Word);
    procedure btnStartClick(Sender: TObject);
    procedure btnStopClick(Sender: TObject);
    procedure btnSendClick(Sender: TObject);
		procedure btnSendCRClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.DFM}

procedure TForm1.Comm321ReceiveData(Buffer: Pointer; BufferLength: Word);
var
	S:	string;
begin
	SetLength(S, BufferLength);
	Move(Buffer^, PChar(S)^, BufferLength);
	Memo1.Lines.Add(S);
	Memo1.Invalidate;
end;

procedure TForm1.btnStartClick(Sender: TObject);
begin
	Comm321.StartComm;
end;

procedure TForm1.btnStopClick(Sender: TObject);
begin
	Comm321.StopComm;
end;

procedure TForm1.btnSendClick(Sender: TObject);
begin       
	Comm321.WriteCommData( PChar(Edit1.Text), Length(Edit1.Text) );
end;

procedure TForm1.btnSendCRClick(Sender: TObject);
begin
	Comm321.WriteCommData( #13, 1 );
end;

end.
 