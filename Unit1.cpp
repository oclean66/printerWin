//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include <System.JSON.hpp>
#include <System.DateUtils.hpp>
#include <System.SysUtils.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
	ComboBox1->Items->Clear();
	ComboBox1->Items = Printer()->Printers;
	ComboBox1->ItemIndex = Printer()->PrinterIndex;
	Memo2->Lines->Add(Printer()->Fonts->Text);
	if(ParamCount() > 0){
//		Memo1->Lines->Add(ParamStr(0));
		Memo1->Lines->Add(ParamStr(1));
	}
   else{
		Memo1->Lines->Clear();
		Memo1->Lines->LoadFromFile("cache.bin");
		Button1->Click();
		Application->Terminate();
	}


}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{

	Memo1->Lines->Clear();
	Memo1->Lines->LoadFromFile("cache.bin");
	TFileName fileName = "cache.bin";

	TJSONObject * objeto = (TJSONObject*) TJSONObject::ParseJSONValue(TEncoding::ASCII->GetBytes(Memo1->Lines->Text),0);
	Memo1->Lines->Clear();


	int pageline = 0;
	Printer()->BeginDoc();
	Printer()->Canvas->Font->Name = "consolas";

	Printer()->Canvas->Font->Size = 7;
	//    HEADER
//	Printer()->Canvas->TextOut(10,(10 + Printer()->Canvas->TextHeight("H")) * pageline, Printer()->PageWidth);
//	pageline += 1;

	TJSONObject * header = (TJSONObject*) objeto->GetValue("header");
	for (int i = 0; i < header->Count; i++) {
		Printer()->Canvas->TextOut(10,(10 + Printer()->Canvas->TextHeight("H")) * pageline, StringReplace(header->Pairs[i]->JsonValue->ToString(), _D("\""), _D(""), TReplaceFlags() << rfReplaceAll));
		pageline += 1;
	}
	Printer()->Canvas->Font->Size = 7;
	Printer()->Canvas->Font->Name = "consolas";

	Printer()->Canvas->TextOut(10,(10 + Printer()->Canvas->TextHeight("H")) * pageline, "--------------------------------");
	pageline += 1;

    //    BODY
	TJSONObject * body = (TJSONObject*) objeto->GetValue("body");
	for (int i = 0; i < body->Count; i++) {

		TJSONObject * itemValue = (TJSONObject*)body->Pairs[i]->JsonValue;

		for (int j = 0; j < itemValue->Count; j++) {
			Printer()->Canvas->TextOut(10,(10 + Printer()->Canvas->TextHeight("H")) * pageline,StringReplace(itemValue->Pairs[j]->JsonValue->ToString(), _D("\""), _D(""), TReplaceFlags() << rfReplaceAll));
			pageline += 1;
		}
	}


	Printer()->Canvas->TextOut(10,(10 + Printer()->Canvas->TextHeight("H")) * pageline, "--------------------------------");
	pageline += 1;


//    FOOTER
	TJSONObject * footer = (TJSONObject*) objeto->GetValue("footer");
	for (int i = 0; i < footer->Count; i++) {
		Printer()->Canvas->TextOut(10,(10 + Printer()->Canvas->TextHeight("H")) * pageline, StringReplace(footer->Pairs[i]->JsonValue->ToString(), _D("\""), _D(""), TReplaceFlags() << rfReplaceAll));
		pageline += 1;
	}


	Printer()->EndDoc();
	Application->Terminate();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ComboBox1Change(TObject *Sender)
{
	Printer()->PrinterIndex = ComboBox1->ItemIndex;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	Memo1->Lines->Clear();
	Memo1->Lines->LoadFromFile("cache.bin");
	TFileName fileName = "cache.bin";

	TJSONObject * objeto = (TJSONObject*) TJSONObject::ParseJSONValue(TEncoding::ASCII->GetBytes(Memo1->Lines->Text),0);
	Memo1->Lines->Clear();

//    HEADER
	TJSONObject * header = (TJSONObject*) objeto->GetValue("header");
	for (int i = 0; i < header->Count; i++) {
		Memo1->Lines->Add(StringReplace(header->Pairs[i]->JsonValue->ToString(), _D("\""), _D(""), TReplaceFlags() << rfReplaceAll));
	}

	Memo1->Lines->Add("-------------------------------");

//    BODY
	TJSONObject * body = (TJSONObject*) objeto->GetValue("body");
	for (int i = 0; i < body->Count; i++) {

		TJSONObject * itemValue = (TJSONObject*)body->Pairs[i]->JsonValue;

		for (int j = 0; j < itemValue->Count; j++) {
			Memo1->Lines->Add(StringReplace(itemValue->Pairs[j]->JsonValue->ToString(), _D("\""), _D(""), TReplaceFlags() << rfReplaceAll));
		}

	}

	Memo1->Lines->Add("-------------------------------");

//    FOOTER
	TJSONObject * footer = (TJSONObject*) objeto->GetValue("footer");
	for (int i = 0; i < footer->Count; i++) {
		Memo1->Lines->Add(StringReplace(footer->Pairs[i]->JsonValue->ToString(), _D("\""), _D(""), TReplaceFlags() << rfReplaceAll));
	}


}
//---------------------------------------------------------------------------




void __fastcall TForm1::Button3Click(TObject *Sender)
{

	Printer()->BeginDoc();
	Printer()->Canvas->StretchDraw(
					Rect(100, 50, Printer()->PageWidth - 100,Printer()->PageWidth - 100),
					Image1->Picture->Graphic);
	Printer()->EndDoc();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{

	Memo1->Lines->Clear();
	Memo1->Lines->LoadFromFile("short.bin");
	TFileName fileName = "short.bin";

	TJSONObject * objeto = (TJSONObject*) TJSONObject::ParseJSONValue(TEncoding::ASCII->GetBytes(Memo1->Lines->Text),0);
	Memo1->Lines->Clear();


	int pageline = 0;
	Printer()->BeginDoc();
	Printer()->Canvas->Font->Name = "consolas";

	Printer()->Canvas->Font->Size = 7;
	Printer()->Canvas->Font->Style = TFontStyles() << fsBold;
	//    HEADER
//	Printer()->Canvas->TextOut(10,(10 + Printer()->Canvas->TextHeight("H")) * pageline, Printer()->PageWidth);
//	pageline += 1;
//	Printer()->Canvas->TextOut(10,(10 + Printer()->Canvas->TextHeight("H")) * pageline, "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ?!#$%&/()=");
//	pageline += 1;

	TJSONObject * header = (TJSONObject*) objeto->GetValue("header");
	for (int i = 0; i < header->Count; i++) {
		Printer()->Canvas->TextOut(10,(10 + Printer()->Canvas->TextHeight("H")) * pageline, StringReplace(header->Pairs[i]->JsonValue->ToString(), _D("\""), _D(""), TReplaceFlags() << rfReplaceAll));
		pageline += 1;
	}
	Printer()->Canvas->Font->Size = 7;
	Printer()->Canvas->Font->Name = "consolas";

   	Printer()->Canvas->TextOut(10,(10 + Printer()->Canvas->TextHeight("H")) * pageline, "--------------------------------");
	pageline += 1;

    //    BODY
	TJSONObject * body = (TJSONObject*) objeto->GetValue("body");
	for (int i = 0; i < body->Count; i++) {

		TJSONObject * itemValue = (TJSONObject*)body->Pairs[i]->JsonValue;

		for (int j = 0; j < itemValue->Count; j++) {
			Printer()->Canvas->TextOut(10,(10 + Printer()->Canvas->TextHeight("H")) * pageline,StringReplace(itemValue->Pairs[j]->JsonValue->ToString(), _D("\""), _D(""), TReplaceFlags() << rfReplaceAll));
			pageline += 1;
		}
	}


	Printer()->Canvas->TextOut(10,(10 + Printer()->Canvas->TextHeight("H")) * pageline, "--------------------------------");
	pageline += 1;


//    FOOTER
	TJSONObject * footer = (TJSONObject*) objeto->GetValue("footer");
	for (int i = 0; i < footer->Count; i++) {
		Printer()->Canvas->TextOut(10,(10 + Printer()->Canvas->TextHeight("H")) * pageline, StringReplace(footer->Pairs[i]->JsonValue->ToString(), _D("\""), _D(""), TReplaceFlags() << rfReplaceAll));
		pageline += 1;
	}


	Printer()->EndDoc();
	Application->Terminate();
}
//---------------------------------------------------------------------------

