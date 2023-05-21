#pragma once

namespace VisualInterpreter {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for JavaCode
	/// </summary>
	public ref class JavaCode : public System::Windows::Forms::Form
	{
		
	public:

		JavaCode(void)
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
		~JavaCode()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::RichTextBox^ javaCodeTextBox;

	protected:

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
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->javaCodeTextBox = (gcnew System::Windows::Forms::RichTextBox());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(13, 13);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(178, 37);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Java Code:";
			this->label1->Click += gcnew System::EventHandler(this, &JavaCode::label1_Click);
			// 
			// javaCodeTextBox
			// 
			this->javaCodeTextBox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->javaCodeTextBox->Font = (gcnew System::Drawing::Font(L"Consolas", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->javaCodeTextBox->Location = System::Drawing::Point(12, 54);
			this->javaCodeTextBox->Name = L"javaCodeTextBox";
			this->javaCodeTextBox->Size = System::Drawing::Size(917, 555);
			this->javaCodeTextBox->TabIndex = 1;
			this->javaCodeTextBox->Text = L"";
			// 
			// JavaCode
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(941, 621);
			this->Controls->Add(this->javaCodeTextBox);
			this->Controls->Add(this->label1);
			this->Name = L"JavaCode";
			this->Text = L"JavaCode";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	};
}
