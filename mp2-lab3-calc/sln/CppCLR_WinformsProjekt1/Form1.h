#pragma once
#include <iostream>
#include <msclr\marshal_cppstd.h>
#include <string>
#include "../../include/stack.h"

namespace CppCLR_WinformsProjekt {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung fьr Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufьgen.
			//
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  textBox1;
	protected:
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Button^  button2;



	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode fьr die Designerunterstьtzung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geдndert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(129, 105);
			this->textBox1->Margin = System::Windows::Forms::Padding(10, 9, 10, 9);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(432, 45);
			this->textBox1->TabIndex = 0;
			// 
			// button1
			// 
			this->button1->AllowDrop = true;
			this->button1->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->button1->ForeColor = System::Drawing::SystemColors::WindowFrame;
			this->button1->Location = System::Drawing::Point(581, 101);
			this->button1->Margin = System::Windows::Forms::Padding(10, 9, 10, 9);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(40, 53);
			this->button1->TabIndex = 1;
			this->button1->Text = L"=";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(641, 108);
			this->label1->Margin = System::Windows::Forms::Padding(10, 0, 10, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(26, 39);
			this->label1->TabIndex = 2;
			this->label1->Text = L" ";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->ForeColor = System::Drawing::Color::Blue;
			this->label2->Location = System::Drawing::Point(122, 161);
			this->label2->Margin = System::Windows::Forms::Padding(10, 0, 10, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(349, 39);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Постфиксная форма";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->ForeColor = System::Drawing::Color::LightSlateGray;
			this->label3->Location = System::Drawing::Point(122, 58);
			this->label3->Margin = System::Windows::Forms::Padding(10, 0, 10, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(349, 39);
			this->label3->TabIndex = 4;
			this->label3->Text = L"Введите выражение:";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(77, 108);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(39, 42);
			this->button2->TabIndex = 5;
			this->button2->Text = L"×";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// Form1
			// 
			this->AcceptButton = this->button1;
			this->AllowDrop = true;
			this->AutoScaleDimensions = System::Drawing::SizeF(19, 38);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(988, 245);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button1);
			this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 25));
			this->Margin = System::Windows::Forms::Padding(10, 9, 10, 9);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		string form;
		form = msclr::interop::marshal_as<std::string>(textBox1->Text);
		Calculator postfix;
		postfix.SetExpr(form);
		try {
			if (postfix.CheckBrackets() == 0) throw 0;
			string t = postfix.ToPostfix();
			label1->Text = Convert::ToString(postfix.Calculate());
			label2->Text = gcnew System::String(t.c_str());
		}
		catch (int i) {
			if (i == 0)
				label1->Text = "Brackets' error";
			if (i == 1)
				label1->Text = "Stack is full";
			if (i == 2)
				label1->Text = "Stack is empty";
			if (i == 22)
				label1->Text = "Postfix's problem";
			if (i == 23)
				label1->Text = "Calculator's problem";
		}
	}
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		textBox1->Text = "";
	}
	};
}
