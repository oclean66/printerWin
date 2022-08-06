// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include <string>
#include <System.JSON.hpp>
#include <System.DateUtils.hpp>
#include <System.SysUtils.hpp>
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
int width = 80;
int inter = 10;
int margin = 0;
int fontSize = 10;
String font = "Arial";

// ---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner) {
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender) {
	ComboBox1->Items->Clear();
	ComboBox1->Items = Printer()->Printers;
	ComboBox1->ItemIndex = Printer()->PrinterIndex;
	Memo2->Lines->Add(Printer()->Fonts->Text);

	for (int i = 1; i < ParamCount(); i++) {
		Memo1->Lines->Add(ParamStr(i));
		if (ParamStr(i) == "-width") {
			Memo1->Lines->Add("Ancho: " + ParamStr(i + 1));
			width = StrToInt(ParamStr(i + 1));
		}
		if (ParamStr(i) == "-fontSize") {
			Memo1->Lines->Add("TLetra: " + ParamStr(i + 1));
			fontSize = StrToInt(ParamStr(i + 1));
		}
		if (ParamStr(i) == "-inter") {
			Memo1->Lines->Add("Interlineado: " + ParamStr(i + 1));
			inter = StrToInt(ParamStr(i + 1));
		}
		if (ParamStr(i) == "-font") {
			Memo1->Lines->Add("Letra: " + ParamStr(i + 1));
			font = ParamStr(i + 1);
		}

	}
	Button1->Click();
	Application->Terminate();

}

// ---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender) {

	Memo1->Lines->Clear();
	Memo1->Lines->LoadFromFile("cache.bin");
	TFileName fileName = "cache.bin";

	TJSONObject * objeto = (TJSONObject*) TJSONObject::ParseJSONValue
		(TEncoding::ASCII->GetBytes(Memo1->Lines->Text), 0);
	Memo1->Lines->Clear();

	int pageline = 0;
	int lineas = 0;
	Printer()->BeginDoc();

	Printer()->Canvas->Font->Name = font;
	Printer()->Canvas->Font->Size = fontSize;
	Printer()->Canvas->Font->Style = TFontStyles() << fsBold;

	// HEADER
	TJSONObject * header = (TJSONObject*) objeto->GetValue("header");
	for (int i = 0; i < header->Count; i++) {
		lineas = lineas + ((inter + Printer()->Canvas->TextHeight("H")));
		Printer()->Canvas->TextOut(margin, lineas,
			StringReplace(header->Pairs[i]->JsonValue->ToString(), _D("\""),
			_D(""), TReplaceFlags() << rfReplaceAll));
		pageline += 1;
		if (i > 0) {
			Printer()->Canvas->Font->Style = TFontStyles();
		}
	}
	// pageline += 2;
	lineas = lineas + ((inter + Printer()->Canvas->TextHeight("H")));
	Printer()->Canvas->TextOut(margin, lineas,
		"--------------------------------");
	pageline += 1;
	// Printer()->Canvas->Font->Size = 65;
	// BODY
	TJSONObject * body = (TJSONObject*) objeto->GetValue("body");
	for (int i = 0; i < body->Count; i++) {

		TJSONObject * itemValue = (TJSONObject*)body->Pairs[i]->JsonValue;

		for (int j = 0; j < itemValue->Count; j++) {
			lineas = lineas + ((inter + Printer()->Canvas->TextHeight("H")));
			if (j >= 2) {
				Printer()->Canvas->Font->Style = TFontStyles() << fsBold;
			}
			else {
				Printer()->Canvas->Font->Style = TFontStyles();
			}
			Printer()->Canvas->TextOut(margin, lineas,
				StringReplace(itemValue->Pairs[j]->JsonValue->ToString(),
				_D("\""), _D(""), TReplaceFlags() << rfReplaceAll));
			pageline += 1;
		}
	}

	lineas = lineas + ((inter + Printer()->Canvas->TextHeight("H")));
	Printer()->Canvas->TextOut(margin, lineas,
		"--------------------------------");
	pageline += 1;

	// FOOTER
	TJSONObject * footer = (TJSONObject*) objeto->GetValue("footer");
	for (int i = 0; i < footer->Count; i++) {
		if (i > 2) {
			Printer()->Canvas->Font->Size = fontSize - 2;
			Printer()->Canvas->Font->Style = TFontStyles() << fsBold;
		}
		lineas = lineas + ((inter + Printer()->Canvas->TextHeight("H")));

		Printer()->Canvas->TextOut(margin, lineas,
			StringReplace(footer->Pairs[i]->JsonValue->ToString(), _D("\""),
			_D(""), TReplaceFlags() << rfReplaceAll));
		pageline += 1;
	}

	Printer()->EndDoc();
	Application->Terminate();
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::ComboBox1Change(TObject *Sender) {
	Printer()->PrinterIndex = ComboBox1->ItemIndex;
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender) {
	Memo1->Lines->Clear();
	Memo1->Lines->LoadFromFile("cache.bin");
	TFileName fileName = "cache.bin";

	TJSONObject * objeto = (TJSONObject*) TJSONObject::ParseJSONValue
		(TEncoding::ASCII->GetBytes(Memo1->Lines->Text), 0);
	Memo1->Lines->Clear();

	// HEADER
	TJSONObject * header = (TJSONObject*) objeto->GetValue("header");
	for (int i = 0; i < header->Count; i++) {
		Memo1->Lines->Add(StringReplace(header->Pairs[i]->JsonValue->ToString(),
			_D("\""), _D(""), TReplaceFlags() << rfReplaceAll));
	}

	Memo1->Lines->Add("-------------------------------");

	// BODY
	TJSONObject * body = (TJSONObject*) objeto->GetValue("body");
	for (int i = 0; i < body->Count; i++) {

		TJSONObject * itemValue = (TJSONObject*)body->Pairs[i]->JsonValue;

		for (int j = 0; j < itemValue->Count; j++) {
			Memo1->Lines->Add
				(StringReplace(itemValue->Pairs[j]->JsonValue->ToString(),
				_D("\""), _D(""), TReplaceFlags() << rfReplaceAll));
		}

	}

	Memo1->Lines->Add("-------------------------------");

	// FOOTER
	TJSONObject * footer = (TJSONObject*) objeto->GetValue("footer");
	for (int i = 0; i < footer->Count; i++) {
		Memo1->Lines->Add(StringReplace(footer->Pairs[i]->JsonValue->ToString(),
			_D("\""), _D(""), TReplaceFlags() << rfReplaceAll));
	}

}
// ---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender) {

	Printer()->BeginDoc();
	int fontSize = 7;
	int pageline = 0;
	int max = 151 * 5;
	int margin = 30;
	int height = 43 * 5;
	int pr = Printer()->PageWidth;
	if (pr >= 300) {
		max = 225 * 4;
		margin = 35;
		height = 65 * 5;
	}

	Printer()->Canvas->Font->Name = "consolas";
	Printer()->Canvas->Font->Size = fontSize;
	Printer()->Canvas->Font->Style = TFontStyles() << fsBold;
	pageline = 5;

	Printer()->Canvas->TextOut(fontSize,
		(Printer()->Canvas->TextHeight("H")) * pageline,
		"--------------------------------");
	pageline += 1;

	Printer()->Canvas->TextOut(fontSize,
		(fontSize + Printer()->Canvas->TextHeight("H")) * pageline, pr);
	pageline += 1;

	Printer()->Canvas->TextOut(fontSize,
		(fontSize + Printer()->Canvas->TextHeight("H")) * pageline, max);
	pageline += 1;
	Printer()->Canvas->TextOut(fontSize,
		(fontSize + Printer()->Canvas->TextHeight("H")) * pageline, margin);
	pageline += 1;

	Printer()->EndDoc();
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender) {
	int fontSize = 7;
	int pageWidth = Printer()->PageWidth;
	Memo1->Lines->Clear();
	Memo1->Lines->LoadFromFile("short.bin");

	TJSONObject * objeto = (TJSONObject*) TJSONObject::ParseJSONValue
		(TEncoding::ASCII->GetBytes(Memo1->Lines->Text), 0);
	Memo1->Lines->Clear();

	int pageline = 0;

	Printer()->BeginDoc();
	Printer()->Canvas->Font->Name = "consolas";

	Printer()->Canvas->Font->Size = fontSize;
	Printer()->Canvas->Font->Style = TFontStyles() << fsBold;

	Printer()->Canvas->TextOut(fontSize,
		(fontSize + Printer()->Canvas->TextHeight("H")) * pageline, fontSize);
	pageline += 1;
	Printer()->Canvas->TextOut(fontSize,
		(fontSize + Printer()->Canvas->TextHeight("H")) * pageline, pageWidth);
	pageline += 1;

	// HEADER

	TJSONObject * header = (TJSONObject*) objeto->GetValue("header");
	for (int i = 0; i < header->Count; i++) {
		Printer()->Canvas->TextOut(fontSize,
			(fontSize + Printer()->Canvas->TextHeight("H")) * pageline,
			StringReplace(header->Pairs[i]->JsonValue->ToString(), _D("\""),
			_D(""), TReplaceFlags() << rfReplaceAll));
		pageline += 1;
	}

	Printer()->Canvas->TextOut(fontSize,
		(fontSize + Printer()->Canvas->TextHeight("H")) * pageline,
		"--------------------------------");
	pageline += 1;

	// BODY
	TJSONObject * body = (TJSONObject*) objeto->GetValue("body");
	for (int i = 0; i < body->Count; i++) {

		TJSONObject * itemValue = (TJSONObject*)body->Pairs[i]->JsonValue;

		for (int j = 0; j < itemValue->Count; j++) {
			Printer()->Canvas->TextOut(fontSize,
				(fontSize + Printer()->Canvas->TextHeight("H")) * pageline,
				StringReplace(itemValue->Pairs[j]->JsonValue->ToString(),
				_D("\""), _D(""), TReplaceFlags() << rfReplaceAll));
			pageline += 1;
		}
	}

	Printer()->Canvas->TextOut(fontSize,
		(fontSize + Printer()->Canvas->TextHeight("H")) * pageline,
		"--------------------------------");
	pageline += 1;

	// FOOTER
	TJSONObject * footer = (TJSONObject*) objeto->GetValue("footer");
	for (int i = 0; i < footer->Count; i++) {
		Printer()->Canvas->TextOut(fontSize,
			(fontSize + Printer()->Canvas->TextHeight("H")) * pageline,
			StringReplace(footer->Pairs[i]->JsonValue->ToString(), _D("\""),
			_D(""), TReplaceFlags() << rfReplaceAll));
		pageline += 1;
	}

	Printer()->EndDoc();
	Application->Terminate();
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::Button6Click(TObject *Sender) {
	Memo2->Lines->Add(Printer()->Fonts->Text);
}
// ---------------------------------------------------------------------------
