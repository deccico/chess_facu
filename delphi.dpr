program delphi;

uses
  Forms,
  chess in 'chess.pas' {Form1},
  cPieza in 'cPieza.pas';

{$R *.RES}

begin
  Application.Initialize;
  Application.CreateForm(TForm1, Form1);
  Application.Run;
end.
