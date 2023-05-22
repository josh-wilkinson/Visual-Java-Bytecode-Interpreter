#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <Windows.h>

#include <msclr\marshal_cppstd.h>

#include "vm.h"
#include "parser.h"

#include "JavaCode.h"


namespace VisualInterpreter {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	codeLine code[256]; // array of lines of code
	constantPoolLine cPool[256];
	int sizeOfCodeArray = 0; // number of elements in code array
	int sizeOfConstantPoolArray = 0;
	std::string fn;
	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
		
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			
			
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	protected:
	private: System::Windows::Forms::ToolStripMenuItem^ fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ openToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ exitToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ optionsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ helpToolStripMenuItem;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel1;
	private: System::Windows::Forms::Button^ runButton;
	private: System::Windows::Forms::Button^ stepForwardButton;
	private: System::Windows::Forms::Button^ resetButton;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel1;
	private: System::Windows::Forms::RichTextBox^ opcodeTextBox;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel2;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel3;
	private: System::Windows::Forms::Label^ registerLabel1;
	private: System::Windows::Forms::TextBox^ registerTextBox1;
	private: System::Windows::Forms::Label^ registerLabel2;
	private: System::Windows::Forms::TextBox^ registerTextBox2;
	private: System::Windows::Forms::Label^ registerLabel3;
	private: System::Windows::Forms::TextBox^ registerTextBox3;
	private: System::Windows::Forms::Label^ registerLabel4;
	private: System::Windows::Forms::TextBox^ registerTextBox4;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel4;
	private: System::Windows::Forms::Label^ stackTitleLabel;

	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel5;
	private: System::Windows::Forms::Label^ registersTitleLabel;

	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel6;
	private: System::Windows::Forms::Label^ stackLabel;
	private: System::Windows::Forms::RichTextBox^ stackTextBox;
	private: System::Windows::Forms::ToolStripMenuItem^ clearToolStripMenuItem;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel7;
	private: System::Windows::Forms::Label^ javaCodeLabel;



	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel8;
	private: System::Windows::Forms::RichTextBox^ javaCodeTextBox;




	private: System::Windows::Forms::ToolStripMenuItem^ viewToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ javaCodeToolStripMenuItem;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel9;
	private: System::Windows::Forms::RichTextBox^ outputTextBox;







	







	






	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->clearToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->optionsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->viewToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->javaCodeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->runButton = (gcnew System::Windows::Forms::Button());
			this->stepForwardButton = (gcnew System::Windows::Forms::Button());
			this->resetButton = (gcnew System::Windows::Forms::Button());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->opcodeTextBox = (gcnew System::Windows::Forms::RichTextBox());
			this->flowLayoutPanel2 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->flowLayoutPanel3 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->flowLayoutPanel5 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->registersTitleLabel = (gcnew System::Windows::Forms::Label());
			this->registerLabel1 = (gcnew System::Windows::Forms::Label());
			this->registerTextBox1 = (gcnew System::Windows::Forms::TextBox());
			this->registerLabel2 = (gcnew System::Windows::Forms::Label());
			this->registerTextBox2 = (gcnew System::Windows::Forms::TextBox());
			this->registerLabel3 = (gcnew System::Windows::Forms::Label());
			this->registerTextBox3 = (gcnew System::Windows::Forms::TextBox());
			this->registerLabel4 = (gcnew System::Windows::Forms::Label());
			this->registerTextBox4 = (gcnew System::Windows::Forms::TextBox());
			this->flowLayoutPanel4 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->stackTitleLabel = (gcnew System::Windows::Forms::Label());
			this->flowLayoutPanel6 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->stackLabel = (gcnew System::Windows::Forms::Label());
			this->stackTextBox = (gcnew System::Windows::Forms::RichTextBox());
			this->flowLayoutPanel7 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->javaCodeLabel = (gcnew System::Windows::Forms::Label());
			this->flowLayoutPanel8 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->javaCodeTextBox = (gcnew System::Windows::Forms::RichTextBox());
			this->flowLayoutPanel9 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->outputTextBox = (gcnew System::Windows::Forms::RichTextBox());
			this->menuStrip1->SuspendLayout();
			this->flowLayoutPanel1->SuspendLayout();
			this->tableLayoutPanel1->SuspendLayout();
			this->flowLayoutPanel2->SuspendLayout();
			this->flowLayoutPanel3->SuspendLayout();
			this->flowLayoutPanel5->SuspendLayout();
			this->flowLayoutPanel4->SuspendLayout();
			this->flowLayoutPanel6->SuspendLayout();
			this->flowLayoutPanel7->SuspendLayout();
			this->flowLayoutPanel8->SuspendLayout();
			this->flowLayoutPanel9->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->menuStrip1->GripMargin = System::Windows::Forms::Padding(2, 2, 0, 2);
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(24, 24);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->fileToolStripMenuItem,
					this->optionsToolStripMenuItem, this->helpToolStripMenuItem, this->viewToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1898, 33);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->openToolStripMenuItem,
					this->clearToolStripMenuItem, this->exitToolStripMenuItem
			});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(54, 29);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// openToolStripMenuItem
			// 
			this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
			this->openToolStripMenuItem->Size = System::Drawing::Size(158, 34);
			this->openToolStripMenuItem->Text = L"Open";
			this->openToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::openToolStripMenuItem_Click);
			// 
			// clearToolStripMenuItem
			// 
			this->clearToolStripMenuItem->Name = L"clearToolStripMenuItem";
			this->clearToolStripMenuItem->Size = System::Drawing::Size(158, 34);
			this->clearToolStripMenuItem->Text = L"Clear";
			this->clearToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::clearToolStripMenuItem_Click);
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(158, 34);
			this->exitToolStripMenuItem->Text = L"Exit";
			this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::exitToolStripMenuItem_Click);
			// 
			// optionsToolStripMenuItem
			// 
			this->optionsToolStripMenuItem->Name = L"optionsToolStripMenuItem";
			this->optionsToolStripMenuItem->Size = System::Drawing::Size(92, 29);
			this->optionsToolStripMenuItem->Text = L"Options";
			// 
			// helpToolStripMenuItem
			// 
			this->helpToolStripMenuItem->Name = L"helpToolStripMenuItem";
			this->helpToolStripMenuItem->Size = System::Drawing::Size(65, 29);
			this->helpToolStripMenuItem->Text = L"Help";
			this->helpToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::helpToolStripMenuItem_Click);
			// 
			// viewToolStripMenuItem
			// 
			this->viewToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->javaCodeToolStripMenuItem });
			this->viewToolStripMenuItem->Name = L"viewToolStripMenuItem";
			this->viewToolStripMenuItem->Size = System::Drawing::Size(65, 29);
			this->viewToolStripMenuItem->Text = L"View";
			// 
			// javaCodeToolStripMenuItem
			// 
			this->javaCodeToolStripMenuItem->Name = L"javaCodeToolStripMenuItem";
			this->javaCodeToolStripMenuItem->Size = System::Drawing::Size(194, 34);
			this->javaCodeToolStripMenuItem->Text = L"Java Code";
			this->javaCodeToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::javaCodeToolStripMenuItem_Click);
			// 
			// flowLayoutPanel1
			// 
			this->flowLayoutPanel1->Controls->Add(this->runButton);
			this->flowLayoutPanel1->Controls->Add(this->stepForwardButton);
			this->flowLayoutPanel1->Controls->Add(this->resetButton);
			this->flowLayoutPanel1->Location = System::Drawing::Point(12, 36);
			this->flowLayoutPanel1->Name = L"flowLayoutPanel1";
			this->flowLayoutPanel1->Size = System::Drawing::Size(1874, 50);
			this->flowLayoutPanel1->TabIndex = 1;
			// 
			// runButton
			// 
			this->runButton->Enabled = false;
			this->runButton->Location = System::Drawing::Point(3, 3);
			this->runButton->Name = L"runButton";
			this->runButton->Size = System::Drawing::Size(80, 40);
			this->runButton->TabIndex = 0;
			this->runButton->Text = L"Run";
			this->runButton->UseVisualStyleBackColor = true;
			this->runButton->Click += gcnew System::EventHandler(this, &MainForm::runButton_Click);
			// 
			// stepForwardButton
			// 
			this->stepForwardButton->Enabled = false;
			this->stepForwardButton->Location = System::Drawing::Point(89, 3);
			this->stepForwardButton->Name = L"stepForwardButton";
			this->stepForwardButton->Size = System::Drawing::Size(80, 40);
			this->stepForwardButton->TabIndex = 1;
			this->stepForwardButton->Text = L"Step";
			this->stepForwardButton->UseVisualStyleBackColor = true;
			this->stepForwardButton->Click += gcnew System::EventHandler(this, &MainForm::stepForwardButton_Click);
			// 
			// resetButton
			// 
			this->resetButton->Enabled = false;
			this->resetButton->Location = System::Drawing::Point(175, 3);
			this->resetButton->Name = L"resetButton";
			this->resetButton->Size = System::Drawing::Size(80, 40);
			this->resetButton->TabIndex = 2;
			this->resetButton->Text = L"Reset";
			this->resetButton->UseVisualStyleBackColor = true;
			this->resetButton->Click += gcnew System::EventHandler(this, &MainForm::resetButton_Click);
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->tableLayoutPanel1->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->tableLayoutPanel1->ColumnCount = 2;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				35.48904F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				64.51096F)));
			this->tableLayoutPanel1->Controls->Add(this->opcodeTextBox, 1, 0);
			this->tableLayoutPanel1->Controls->Add(this->flowLayoutPanel2, 0, 0);
			this->tableLayoutPanel1->Location = System::Drawing::Point(15, 93);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 1;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 721)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(1865, 721);
			this->tableLayoutPanel1->TabIndex = 2;
			this->tableLayoutPanel1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MainForm::tableLayoutPanel1_Paint);
			// 
			// opcodeTextBox
			// 
			this->opcodeTextBox->BackColor = System::Drawing::Color::MintCream;
			this->opcodeTextBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->opcodeTextBox->Font = (gcnew System::Drawing::Font(L"Consolas", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->opcodeTextBox->Location = System::Drawing::Point(664, 3);
			this->opcodeTextBox->MaximumSize = System::Drawing::Size(1500, 1500);
			this->opcodeTextBox->MinimumSize = System::Drawing::Size(1100, 600);
			this->opcodeTextBox->Name = L"opcodeTextBox";
			this->opcodeTextBox->ReadOnly = true;
			this->opcodeTextBox->Size = System::Drawing::Size(1198, 715);
			this->opcodeTextBox->TabIndex = 0;
			this->opcodeTextBox->Text = L"";
			this->opcodeTextBox->TextChanged += gcnew System::EventHandler(this, &MainForm::opcodeTextBox_TextChanged);
			// 
			// flowLayoutPanel2
			// 
			this->flowLayoutPanel2->Controls->Add(this->flowLayoutPanel3);
			this->flowLayoutPanel2->Controls->Add(this->flowLayoutPanel4);
			this->flowLayoutPanel2->Controls->Add(this->flowLayoutPanel6);
			this->flowLayoutPanel2->Controls->Add(this->flowLayoutPanel7);
			this->flowLayoutPanel2->Location = System::Drawing::Point(3, 3);
			this->flowLayoutPanel2->Name = L"flowLayoutPanel2";
			this->flowLayoutPanel2->Size = System::Drawing::Size(655, 715);
			this->flowLayoutPanel2->TabIndex = 1;
			// 
			// flowLayoutPanel3
			// 
			this->flowLayoutPanel3->Controls->Add(this->flowLayoutPanel5);
			this->flowLayoutPanel3->Controls->Add(this->registerLabel1);
			this->flowLayoutPanel3->Controls->Add(this->registerTextBox1);
			this->flowLayoutPanel3->Controls->Add(this->registerLabel2);
			this->flowLayoutPanel3->Controls->Add(this->registerTextBox2);
			this->flowLayoutPanel3->Controls->Add(this->registerLabel3);
			this->flowLayoutPanel3->Controls->Add(this->registerTextBox3);
			this->flowLayoutPanel3->Controls->Add(this->registerLabel4);
			this->flowLayoutPanel3->Controls->Add(this->registerTextBox4);
			this->flowLayoutPanel3->Location = System::Drawing::Point(3, 3);
			this->flowLayoutPanel3->Name = L"flowLayoutPanel3";
			this->flowLayoutPanel3->Size = System::Drawing::Size(654, 174);
			this->flowLayoutPanel3->TabIndex = 0;
			// 
			// flowLayoutPanel5
			// 
			this->flowLayoutPanel5->Controls->Add(this->registersTitleLabel);
			this->flowLayoutPanel5->Location = System::Drawing::Point(3, 3);
			this->flowLayoutPanel5->Name = L"flowLayoutPanel5";
			this->flowLayoutPanel5->Size = System::Drawing::Size(654, 80);
			this->flowLayoutPanel5->TabIndex = 2;
			// 
			// registersTitleLabel
			// 
			this->registersTitleLabel->AutoSize = true;
			this->registersTitleLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 26, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->registersTitleLabel->Location = System::Drawing::Point(3, 0);
			this->registersTitleLabel->Name = L"registersTitleLabel";
			this->registersTitleLabel->Size = System::Drawing::Size(244, 59);
			this->registersTitleLabel->TabIndex = 0;
			this->registersTitleLabel->Text = L"Registers";
			// 
			// registerLabel1
			// 
			this->registerLabel1->AutoSize = true;
			this->registerLabel1->Location = System::Drawing::Point(3, 86);
			this->registerLabel1->Name = L"registerLabel1";
			this->registerLabel1->Size = System::Drawing::Size(82, 20);
			this->registerLabel1->TabIndex = 8;
			this->registerLabel1->Text = L"Register 0";
			// 
			// registerTextBox1
			// 
			this->registerTextBox1->BackColor = System::Drawing::Color::LightGray;
			this->registerTextBox1->Location = System::Drawing::Point(91, 89);
			this->registerTextBox1->Name = L"registerTextBox1";
			this->registerTextBox1->ReadOnly = true;
			this->registerTextBox1->Size = System::Drawing::Size(100, 26);
			this->registerTextBox1->TabIndex = 9;
			// 
			// registerLabel2
			// 
			this->registerLabel2->AutoSize = true;
			this->registerLabel2->Location = System::Drawing::Point(197, 86);
			this->registerLabel2->Name = L"registerLabel2";
			this->registerLabel2->Size = System::Drawing::Size(82, 20);
			this->registerLabel2->TabIndex = 10;
			this->registerLabel2->Text = L"Register 1";
			// 
			// registerTextBox2
			// 
			this->registerTextBox2->BackColor = System::Drawing::Color::LightGray;
			this->registerTextBox2->Location = System::Drawing::Point(285, 89);
			this->registerTextBox2->Name = L"registerTextBox2";
			this->registerTextBox2->ReadOnly = true;
			this->registerTextBox2->Size = System::Drawing::Size(100, 26);
			this->registerTextBox2->TabIndex = 11;
			// 
			// registerLabel3
			// 
			this->registerLabel3->AutoSize = true;
			this->registerLabel3->Location = System::Drawing::Point(391, 86);
			this->registerLabel3->Name = L"registerLabel3";
			this->registerLabel3->Size = System::Drawing::Size(82, 20);
			this->registerLabel3->TabIndex = 12;
			this->registerLabel3->Text = L"Register 2";
			// 
			// registerTextBox3
			// 
			this->registerTextBox3->BackColor = System::Drawing::Color::LightGray;
			this->registerTextBox3->Location = System::Drawing::Point(479, 89);
			this->registerTextBox3->Name = L"registerTextBox3";
			this->registerTextBox3->ReadOnly = true;
			this->registerTextBox3->Size = System::Drawing::Size(100, 26);
			this->registerTextBox3->TabIndex = 13;
			// 
			// registerLabel4
			// 
			this->registerLabel4->AutoSize = true;
			this->registerLabel4->Location = System::Drawing::Point(3, 118);
			this->registerLabel4->Name = L"registerLabel4";
			this->registerLabel4->Size = System::Drawing::Size(82, 20);
			this->registerLabel4->TabIndex = 14;
			this->registerLabel4->Text = L"Register 3";
			// 
			// registerTextBox4
			// 
			this->registerTextBox4->BackColor = System::Drawing::Color::LightGray;
			this->registerTextBox4->Location = System::Drawing::Point(91, 121);
			this->registerTextBox4->Name = L"registerTextBox4";
			this->registerTextBox4->ReadOnly = true;
			this->registerTextBox4->Size = System::Drawing::Size(100, 26);
			this->registerTextBox4->TabIndex = 15;
			// 
			// flowLayoutPanel4
			// 
			this->flowLayoutPanel4->Controls->Add(this->stackTitleLabel);
			this->flowLayoutPanel4->Location = System::Drawing::Point(3, 183);
			this->flowLayoutPanel4->Name = L"flowLayoutPanel4";
			this->flowLayoutPanel4->Size = System::Drawing::Size(654, 64);
			this->flowLayoutPanel4->TabIndex = 1;
			// 
			// stackTitleLabel
			// 
			this->stackTitleLabel->AutoSize = true;
			this->stackTitleLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 26, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->stackTitleLabel->Location = System::Drawing::Point(3, 0);
			this->stackTitleLabel->Name = L"stackTitleLabel";
			this->stackTitleLabel->Size = System::Drawing::Size(155, 59);
			this->stackTitleLabel->TabIndex = 0;
			this->stackTitleLabel->Text = L"Stack";
			this->stackTitleLabel->Click += gcnew System::EventHandler(this, &MainForm::stackLabel_Click);
			// 
			// flowLayoutPanel6
			// 
			this->flowLayoutPanel6->Controls->Add(this->stackLabel);
			this->flowLayoutPanel6->Controls->Add(this->stackTextBox);
			this->flowLayoutPanel6->Location = System::Drawing::Point(3, 253);
			this->flowLayoutPanel6->Name = L"flowLayoutPanel6";
			this->flowLayoutPanel6->Size = System::Drawing::Size(654, 149);
			this->flowLayoutPanel6->TabIndex = 2;
			// 
			// stackLabel
			// 
			this->stackLabel->AutoSize = true;
			this->stackLabel->Location = System::Drawing::Point(3, 0);
			this->stackLabel->Name = L"stackLabel";
			this->stackLabel->Size = System::Drawing::Size(54, 20);
			this->stackLabel->TabIndex = 0;
			this->stackLabel->Text = L"Stack:";
			// 
			// stackTextBox
			// 
			this->stackTextBox->BackColor = System::Drawing::Color::Silver;
			this->stackTextBox->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->stackTextBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->stackTextBox->Location = System::Drawing::Point(63, 3);
			this->stackTextBox->Name = L"stackTextBox";
			this->stackTextBox->ReadOnly = true;
			this->stackTextBox->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->stackTextBox->Size = System::Drawing::Size(97, 146);
			this->stackTextBox->TabIndex = 1;
			this->stackTextBox->Text = L"";
			// 
			// flowLayoutPanel7
			// 
			this->flowLayoutPanel7->Controls->Add(this->javaCodeLabel);
			this->flowLayoutPanel7->Controls->Add(this->flowLayoutPanel8);
			this->flowLayoutPanel7->Location = System::Drawing::Point(3, 408);
			this->flowLayoutPanel7->Name = L"flowLayoutPanel7";
			this->flowLayoutPanel7->Size = System::Drawing::Size(613, 452);
			this->flowLayoutPanel7->TabIndex = 3;
			// 
			// javaCodeLabel
			// 
			this->javaCodeLabel->AutoSize = true;
			this->javaCodeLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 26, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->javaCodeLabel->Location = System::Drawing::Point(3, 0);
			this->javaCodeLabel->Name = L"javaCodeLabel";
			this->javaCodeLabel->Size = System::Drawing::Size(274, 59);
			this->javaCodeLabel->TabIndex = 1;
			this->javaCodeLabel->Text = L"Java Code";
			// 
			// flowLayoutPanel8
			// 
			this->flowLayoutPanel8->Controls->Add(this->javaCodeTextBox);
			this->flowLayoutPanel8->Location = System::Drawing::Point(3, 62);
			this->flowLayoutPanel8->Name = L"flowLayoutPanel8";
			this->flowLayoutPanel8->Size = System::Drawing::Size(610, 390);
			this->flowLayoutPanel8->TabIndex = 3;
			this->flowLayoutPanel8->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MainForm::flowLayoutPanel8_Paint);
			// 
			// javaCodeTextBox
			// 
			this->javaCodeTextBox->BackColor = System::Drawing::SystemColors::Control;
			this->javaCodeTextBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->javaCodeTextBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->javaCodeTextBox->ForeColor = System::Drawing::Color::Black;
			this->javaCodeTextBox->Location = System::Drawing::Point(3, 3);
			this->javaCodeTextBox->Name = L"javaCodeTextBox";
			this->javaCodeTextBox->ReadOnly = true;
			this->javaCodeTextBox->Size = System::Drawing::Size(607, 209);
			this->javaCodeTextBox->TabIndex = 0;
			this->javaCodeTextBox->Text = L"";
			// 
			// flowLayoutPanel9
			// 
			this->flowLayoutPanel9->Controls->Add(this->outputTextBox);
			this->flowLayoutPanel9->Location = System::Drawing::Point(18, 820);
			this->flowLayoutPanel9->Name = L"flowLayoutPanel9";
			this->flowLayoutPanel9->Size = System::Drawing::Size(1862, 192);
			this->flowLayoutPanel9->TabIndex = 3;
			// 
			// outputTextBox
			// 
			this->outputTextBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->outputTextBox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->outputTextBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->outputTextBox->ForeColor = System::Drawing::Color::Lime;
			this->outputTextBox->Location = System::Drawing::Point(3, 3);
			this->outputTextBox->Name = L"outputTextBox";
			this->outputTextBox->ReadOnly = true;
			this->outputTextBox->Size = System::Drawing::Size(1856, 189);
			this->outputTextBox->TabIndex = 1;
			this->outputTextBox->Text = L"OUTPUT\n--------\n";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->ClientSize = System::Drawing::Size(1898, 1024);
			this->Controls->Add(this->flowLayoutPanel9);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Controls->Add(this->flowLayoutPanel1);
			this->Controls->Add(this->menuStrip1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->menuStrip1;
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(3840, 2160);
			this->MinimumSize = System::Drawing::Size(1920, 1080);
			this->Name = L"MainForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Visual Java Bytecode Interpreter";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->flowLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel1->ResumeLayout(false);
			this->flowLayoutPanel2->ResumeLayout(false);
			this->flowLayoutPanel3->ResumeLayout(false);
			this->flowLayoutPanel3->PerformLayout();
			this->flowLayoutPanel5->ResumeLayout(false);
			this->flowLayoutPanel5->PerformLayout();
			this->flowLayoutPanel4->ResumeLayout(false);
			this->flowLayoutPanel4->PerformLayout();
			this->flowLayoutPanel6->ResumeLayout(false);
			this->flowLayoutPanel6->PerformLayout();
			this->flowLayoutPanel7->ResumeLayout(false);
			this->flowLayoutPanel7->PerformLayout();
			this->flowLayoutPanel8->ResumeLayout(false);
			this->flowLayoutPanel9->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void openToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		Stream^ myStream;
		OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;
		openFileDialog1->Filter = "java files (*.java)|*.java";
		openFileDialog1->FilterIndex = 2;
		openFileDialog1->RestoreDirectory = true;

		if (openFileDialog1->ShowDialog() == Windows::Forms::DialogResult::OK)
		{
			if ((myStream = openFileDialog1->OpenFile()) != nullptr)
			{
				

				String^ strfilename = openFileDialog1->InitialDirectory + openFileDialog1->FileName;								
				String^ JavaFile = File::ReadAllText(strfilename); // text for the java program text box
				String^ InitialDirectory = openFileDialog1->InitialDirectory;
				String^ JavaFileName = openFileDialog1->FileName;		
				std::string OpcodeDisplayFileName;

				//fn = msclr::interop::marshal_as<std::string>(strfilename); // converts System::String to std::string				
				std::string javaFileName = msclr::interop::marshal_as<std::string>(JavaFileName);
				std::string initialDirectory = "";
				std::string createClassFileCommand = "javac " + javaFileName;				
				WinExec(createClassFileCommand.c_str(), 0);

				eraseSubString(javaFileName, ".java"); //remove .java from string
				//javaFileName.erase(remove(javaFileName.begin(), javaFileName.end(), ".java"), javaFileName.end()); //remove .java from string
				OpcodeDisplayFileName = initialDirectory + javaFileName + ".txt";
				fn = initialDirectory + javaFileName + ".opcode";
				std::string baseFilename = fn.substr(fn.find_last_of("/\\") + 1);
				eraseSubString(baseFilename, ".opcode");
				// getting directory path to the file
				std::string directory;
				const size_t last_slash_idx = fn.rfind('\\');
				if (std::string::npos != last_slash_idx)
				{
					directory = fn.substr(0, last_slash_idx);
				}
				std::string temp1 = "cd/ & cd ";
				std::string javapFileCommand = temp1 + directory + " & javap -v " + baseFilename + " > " + baseFilename + ".opcode";
				system(javapFileCommand.c_str());

				javapFileCommand = temp1 + directory + " & javap -c " + baseFilename + " > " + baseFilename + ".txt";
				system(javapFileCommand.c_str());
				
				String^ OpcodeFilePath = gcnew String(OpcodeDisplayFileName.c_str());				
				// Trying to open file... fn
				String^ OpcodeFile = File::ReadAllText(OpcodeFilePath);
				this->javaCodeTextBox->Text = JavaFile; // add code to textbox

				this->opcodeTextBox->Text = OpcodeFile;
				MessageBox::Show("Created " + OpcodeFilePath);
				myStream->Close();
				reset();
				enableButtons();
			}
		}
	}

	private: System::Void exitToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		Application::Exit();
	}

	private: System::Void stackLabel_Click(System::Object^ sender, System::EventArgs^ e) {
	}

	private: System::Void opcodeTextBox_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		
	}

	private: System::Void runButton_Click(System::Object^ sender, System::EventArgs^ e) {
		reset();
		readInstructions(code, cPool, fn, sizeOfCodeArray, sizeOfConstantPoolArray);
		interpretResult result = vmInterpret(code, cPool, sizeOfCodeArray, sizeOfConstantPoolArray);
		update();
		vm.finishedExecution = true;
		stepForwardButton->Enabled = false;
	}	

	private: System::Void stepForwardButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (!vm.steppingThroughCode)
		{
			reset();
			readInstructions(code, cPool, fn, sizeOfCodeArray, sizeOfConstantPoolArray);
			vm.steppingThroughCode = true;
		}
		
		// we need to get the proper textboxIndex so that we actually highlight the proper opcode instead of the first one it comes across		
		int textboxIndex = 0; // char index, e.g. getting 't' from "data" would be number 2.
		int endIndex = 0;

		for (int i = 0; i < sizeOfCodeArray; i++)
		{
			if (code[i].methodName == code[vm.i].methodName)
			{
				textboxIndex = (i * 17) + 66;
				break;
			}
		}

		for (int i = textboxIndex; i < sizeOfCodeArray; i++)
		{
			if (code[i].methodName != code[vm.i].methodName)
			{
				//endIndex = (i * 17) + 66;
				break;
			}
		}

		//textboxIndex = opcodeTextBox->TextLength / textboxIndex;

		std::string textBoxText;
		String^ opcodeInstruction = gcnew String(opcodeToString(code[vm.i].instruction).c_str());
		String^ item = code[vm.i].opcodeNumber + ": " + opcodeInstruction;
		String^ temp = opcodeTextBox->Text;

			

		textBoxText = msclr::interop::marshal_as<std::string>(opcodeTextBox->Text);
		textBoxText.erase(remove(textBoxText.begin(), textBoxText.end(), ' '), textBoxText.end()); //remove blank spaces from string


		opcodeTextBox->Text = "";
		opcodeTextBox->Text = temp;

		// search for the text - this will need to be reworked when there are multiple methods
		opcodeTextBox->Find(item, textboxIndex, opcodeTextBox->TextLength, RichTextBoxFinds::None);
		
		
		
		// selection colour
		opcodeTextBox->SelectionBackColor = Color::Red;	

		if (!vm.finishedExecution)
		{			
			interpretResult result = vmInterpret(code, cPool, sizeOfCodeArray, sizeOfConstantPoolArray);
			update();
		}
		else
		{
			MessageBox::Show("Finished Execution");
			opcodeTextBox->SelectionBackColor = Color::Transparent;
		}

		opcodeTextBox->ScrollToCaret();
	}

	private: System::Void resetButton_Click(System::Object^ sender, System::EventArgs^ e) {
		reset();
	}

	private: System::Void helpToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

	}

	private: System::Void clearToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		reset();
		this->opcodeTextBox->Clear();
		this->outputTextBox->Clear();
		this->javaCodeTextBox->Clear();
		disableButtons();
	}
	
	void enableButtons()
	{
		this->runButton->Enabled = true;
		this->stepForwardButton->Enabled = true;
		this->resetButton->Enabled = true;
	}

	void disableButtons()
	{
		this->runButton->Enabled = false;
		this->stepForwardButton->Enabled = false;
		this->resetButton->Enabled = false;
	}

	void flipEnableButtons() // flips from enabled to disabled and vice versa for the buttons
	{
		this->runButton->Enabled = !this->runButton->Enabled;
		this->stepForwardButton->Enabled = !this->stepForwardButton->Enabled;
		this->resetButton->Enabled = !this->resetButton->Enabled;
	}

	void update()
	{
		String^ temp = gcnew String(vm.currentOutput.c_str());
		outputTextBox->Text = "OUTPUT\n--------\n" + temp;
		// interpreter / opcodeTextbox updates	
		if (vm.usingVar0)
		{
			this->registerTextBox1->Text = "" + vm.var0;
			this->registerTextBox1->BackColor = Color::Red;
		}	
		else
			this->registerTextBox1->BackColor = Color::LightGray;
		if (vm.usingVar1)
		{
			this->registerTextBox2->Text = "" + vm.var1;
			this->registerTextBox2->BackColor = Color::Red;
		}
		else
			this->registerTextBox2->BackColor = Color::LightGray;
		if (vm.usingVar2)
		{
			this->registerTextBox3->Text = "" + vm.var2;
			this->registerTextBox3->BackColor = Color::Red;
		}
		else
			this->registerTextBox3->BackColor = Color::LightGray;
		if (vm.usingVar3)
		{
			this->registerTextBox4->Text = "" + vm.var3;
			this->registerTextBox4->BackColor = Color::Red;
		}
		else
			this->registerTextBox4->BackColor = Color::LightGray;

		String^ itemsInStack = "";

		if (vm.elementsInStack > 0)
			this->stackTextBox->BackColor = Color::Red;
		else
			this->stackTextBox->BackColor = Color::LightGray;

		if (vm.elementsInStack <= 1)
			itemsInStack += "\n\n\n";
		else if (vm.elementsInStack == 2)
			itemsInStack += "\n\n";
		else if (vm.elementsInStack == 3)
			itemsInStack += "\n";
		else 
			itemsInStack += "";

		for (int i = vm.elementsInStack-1; i >= 0; i--)
		{
			itemsInStack += "   " + vm.stack[i];
			itemsInStack += "\n";
		}
		this->stackTextBox->Text = "" + itemsInStack; // stack
		
	}

	void reset()
	{
		// interpreter updates
		enableButtons();
		opcodeTextBox->SelectionBackColor = Color::Transparent;
		this->registerTextBox1->Text = "";
		this->registerTextBox2->Text = "";
		this->registerTextBox3->Text = "";
		this->registerTextBox4->Text = "";
		this->stackTextBox->Text = "";
		this->outputTextBox->Text = "OUTPUT\n--------\n";
		sizeOfCodeArray = 0;
		vmReset();
		update();
	}

	void eraseSubString(std::string& mainStr, const std::string& toErase)
	{
		// Search for the substring in string
		size_t pos = mainStr.find(toErase);
		if (pos != std::string::npos)
		{
			// If found then erase it from string
			mainStr.erase(pos, toErase.length());
		}
	}

	void consoleTextBoxOutput() // updates the console with new text from the interpreter
	{
		String^ temp = gcnew String(vm.currentOutput.c_str());
		outputTextBox->Text += temp;
	}
	
	private: System::Void javaCodeToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		
	}
	private: System::Void tableLayoutPanel1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void flowLayoutPanel8_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
};
}
