#pragma once
#include "imge.h"
#include <Windows.h>
#include <atlstr.h>
#include<math.h>
#include<float.h>
#include<winnt.h>
namespace image {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;



	/// <summary>
	/// MyForm için özet
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Oluþturucu kodunu buraya ekle
			

			//
		}

	protected:
		/// <summary>
		///Kullanýlan tüm kaynaklarý temizleyin.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  openToolStripMenuItem;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	

	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart1;
	private: System::Windows::Forms::ToolStripMenuItem^  histogramToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  drawNormalToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  equalToolStripMenuItem;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart2;
	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::ToolStripMenuItem^  binaryToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  clearToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  rGBScaleToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  morpToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  dilationToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  erosionToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  mirrorImageToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  rGBSegmentToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  rGBSegmentToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  boundaryToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  cCLToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  cannyEdgeToolStripMenuItem;

	private: System::ComponentModel::IContainer^  components;


	protected:

	private:
		/// <summary>
		///Gerekli tasarýmcý deðiþkeni.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Tasarýmcý desteði için gerekli metot - bu metodun 
		///içeriðini kod düzenleyici ile deðiþtirmeyin.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea2 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->binaryToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->rGBScaleToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->mirrorImageToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->clearToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->histogramToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->drawNormalToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->equalToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->morpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->dilationToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->erosionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->rGBSegmentToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->rGBSegmentToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->boundaryToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->cCLToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->chart2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->cannyEdgeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->fileToolStripMenuItem,
					this->histogramToolStripMenuItem1, this->morpToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1395, 28);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->openToolStripMenuItem,
					this->binaryToolStripMenuItem, this->rGBScaleToolStripMenuItem, this->mirrorImageToolStripMenuItem, this->clearToolStripMenuItem
			});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(44, 24);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// openToolStripMenuItem
			// 
			this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
			this->openToolStripMenuItem->Size = System::Drawing::Size(167, 26);
			this->openToolStripMenuItem->Text = L"Open";
			this->openToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::openToolStripMenuItem_Click);
			// 
			// binaryToolStripMenuItem
			// 
			this->binaryToolStripMenuItem->Name = L"binaryToolStripMenuItem";
			this->binaryToolStripMenuItem->Size = System::Drawing::Size(167, 26);
			this->binaryToolStripMenuItem->Text = L"Binary";
			this->binaryToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::binaryToolStripMenuItem_Click);
			// 
			// rGBScaleToolStripMenuItem
			// 
			this->rGBScaleToolStripMenuItem->Name = L"rGBScaleToolStripMenuItem";
			this->rGBScaleToolStripMenuItem->Size = System::Drawing::Size(167, 26);
			this->rGBScaleToolStripMenuItem->Text = L"RGBScale";
			this->rGBScaleToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::rGBScaleToolStripMenuItem_Click);
			// 
			// mirrorImageToolStripMenuItem
			// 
			this->mirrorImageToolStripMenuItem->Name = L"mirrorImageToolStripMenuItem";
			this->mirrorImageToolStripMenuItem->Size = System::Drawing::Size(167, 26);
			this->mirrorImageToolStripMenuItem->Text = L"MirrorImage";
			this->mirrorImageToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::mirrorImageToolStripMenuItem_Click);
			// 
			// clearToolStripMenuItem
			// 
			this->clearToolStripMenuItem->Name = L"clearToolStripMenuItem";
			this->clearToolStripMenuItem->Size = System::Drawing::Size(167, 26);
			this->clearToolStripMenuItem->Text = L"Clear";
			this->clearToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::clearToolStripMenuItem_Click);
			// 
			// histogramToolStripMenuItem1
			// 
			this->histogramToolStripMenuItem1->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->drawNormalToolStripMenuItem,
					this->equalToolStripMenuItem, this->cannyEdgeToolStripMenuItem
			});
			this->histogramToolStripMenuItem1->Name = L"histogramToolStripMenuItem1";
			this->histogramToolStripMenuItem1->Size = System::Drawing::Size(91, 24);
			this->histogramToolStripMenuItem1->Text = L"Histogram";
			// 
			// drawNormalToolStripMenuItem
			// 
			this->drawNormalToolStripMenuItem->Name = L"drawNormalToolStripMenuItem";
			this->drawNormalToolStripMenuItem->Size = System::Drawing::Size(181, 26);
			this->drawNormalToolStripMenuItem->Text = L"Draw Normal";
			this->drawNormalToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::drawNormalToolStripMenuItem_Click);
			// 
			// equalToolStripMenuItem
			// 
			this->equalToolStripMenuItem->Name = L"equalToolStripMenuItem";
			this->equalToolStripMenuItem->Size = System::Drawing::Size(181, 26);
			this->equalToolStripMenuItem->Text = L"Equal";
			this->equalToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::equalToolStripMenuItem_Click);
			// 
			// morpToolStripMenuItem
			// 
			this->morpToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {
				this->dilationToolStripMenuItem,
					this->erosionToolStripMenuItem, this->rGBSegmentToolStripMenuItem, this->rGBSegmentToolStripMenuItem1, this->boundaryToolStripMenuItem,
					this->cCLToolStripMenuItem
			});
			this->morpToolStripMenuItem->Name = L"morpToolStripMenuItem";
			this->morpToolStripMenuItem->Size = System::Drawing::Size(57, 24);
			this->morpToolStripMenuItem->Text = L"Morp";
			// 
			// dilationToolStripMenuItem
			// 
			this->dilationToolStripMenuItem->Name = L"dilationToolStripMenuItem";
			this->dilationToolStripMenuItem->Size = System::Drawing::Size(198, 26);
			this->dilationToolStripMenuItem->Text = L"Dilation";
			this->dilationToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::dilationToolStripMenuItem_Click);
			// 
			// erosionToolStripMenuItem
			// 
			this->erosionToolStripMenuItem->Name = L"erosionToolStripMenuItem";
			this->erosionToolStripMenuItem->Size = System::Drawing::Size(198, 26);
			this->erosionToolStripMenuItem->Text = L"Erosion";
			this->erosionToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::erosionToolStripMenuItem_Click);
			// 
			// rGBSegmentToolStripMenuItem
			// 
			this->rGBSegmentToolStripMenuItem->Name = L"rGBSegmentToolStripMenuItem";
			this->rGBSegmentToolStripMenuItem->Size = System::Drawing::Size(198, 26);
			this->rGBSegmentToolStripMenuItem->Text = L"IntensýtySegment";
			this->rGBSegmentToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::rGBSegmentToolStripMenuItem_Click);
			// 
			// rGBSegmentToolStripMenuItem1
			// 
			this->rGBSegmentToolStripMenuItem1->Name = L"rGBSegmentToolStripMenuItem1";
			this->rGBSegmentToolStripMenuItem1->Size = System::Drawing::Size(198, 26);
			this->rGBSegmentToolStripMenuItem1->Text = L"RGBSegment";
			this->rGBSegmentToolStripMenuItem1->Click += gcnew System::EventHandler(this, &MyForm::rGBSegmentToolStripMenuItem1_Click);
			// 
			// boundaryToolStripMenuItem
			// 
			this->boundaryToolStripMenuItem->Name = L"boundaryToolStripMenuItem";
			this->boundaryToolStripMenuItem->Size = System::Drawing::Size(198, 26);
			this->boundaryToolStripMenuItem->Text = L"Boundary";
			this->boundaryToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::boundaryToolStripMenuItem_Click);
			// 
			// cCLToolStripMenuItem
			// 
			this->cCLToolStripMenuItem->Name = L"cCLToolStripMenuItem";
			this->cCLToolStripMenuItem->Size = System::Drawing::Size(198, 26);
			this->cCLToolStripMenuItem->Text = L"CCL";
			this->cCLToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::cCLToolStripMenuItem_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(22, 51);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(517, 369);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseDown);
			this->pictureBox1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseMove);
			this->pictureBox1->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseUp);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// chart1
			// 
			chartArea1->AxisX->Interval = 32;
			chartArea1->AxisY->Interval = 1000;
			chartArea1->Name = L"ChartArea1";
			this->chart1->ChartAreas->Add(chartArea1);
			legend1->Name = L"Legend1";
			this->chart1->Legends->Add(legend1);
			this->chart1->Location = System::Drawing::Point(286, 20);
			this->chart1->Name = L"chart1";
			series1->ChartArea = L"ChartArea1";
			series1->Legend = L"Legend1";
			series1->Name = L"NOP";
			this->chart1->Series->Add(series1);
			this->chart1->Size = System::Drawing::Size(702, 400);
			this->chart1->TabIndex = 4;
			this->chart1->Text = L"-+-";
			this->chart1->Visible = false;
			// 
			// chart2
			// 
			chartArea2->AxisX->Interval = 32;
			chartArea2->AxisY->Interval = 1000;
			chartArea2->Name = L"ChartArea1";
			this->chart2->ChartAreas->Add(chartArea2);
			legend2->Name = L"Legend1";
			this->chart2->Legends->Add(legend2);
			this->chart2->Location = System::Drawing::Point(286, 20);
			this->chart2->Name = L"chart2";
			this->chart2->Palette = System::Windows::Forms::DataVisualization::Charting::ChartColorPalette::Fire;
			series2->ChartArea = L"ChartArea1";
			series2->Legend = L"Legend1";
			series2->Name = L"NOPExtended";
			this->chart2->Series->Add(series2);
			this->chart2->Size = System::Drawing::Size(702, 402);
			this->chart2->TabIndex = 4;
			this->chart2->Text = L"chart2";
			this->chart2->Visible = false;
			// 
			// pictureBox2
			// 
			this->pictureBox2->Location = System::Drawing::Point(891, 31);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(492, 554);
			this->pictureBox2->TabIndex = 5;
			this->pictureBox2->TabStop = false;
			// 
			// cannyEdgeToolStripMenuItem
			// 
			this->cannyEdgeToolStripMenuItem->Name = L"cannyEdgeToolStripMenuItem";
			this->cannyEdgeToolStripMenuItem->Size = System::Drawing::Size(181, 26);
			this->cannyEdgeToolStripMenuItem->Text = L"Canny Edge";
			this->cannyEdgeToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::cannyEdgeToolStripMenuItem_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1395, 597);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->chart2);
			this->Controls->Add(this->chart1);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MyForm";
			this->Text = L"Goruntu";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
		
		LPCTSTR input;
		int Width, Height;
		long Size;
		int x_axis, y_axis, w_size, h_size;
		int x2_axis, y2_axis;
		int paramx_axis,param_yaxis;
		

#pragma endregion
	private: System::Void openToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		CString str;
		
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			pictureBox1->ImageLocation = openFileDialog1->FileName;
			pictureBox1->AutoSize;
			pictureBox1->Visible = true;
			pictureBox2->Visible = true;
			
			str = openFileDialog1->FileName;
			input = (LPCTSTR)str;
			BYTE* buffer = LoadBMP(Width, Height, Size, input);
			BYTE* Raw_Intensity = ConvertBMPToIntensity(buffer, Width, Height);

			pictureBox1->Width = Width;
			pictureBox1->Height = Height;
			
			/*
			Bitmap^ surface = gcnew Bitmap(Width,Height);
			pictureBox2->Image = surface;
			Color c;
			int temp;
			for (unsigned int row = 0; row < Height; row++) {
				for (unsigned int column = 0; column < Width; column++)
				{
					temp = row * Width + column;
					c = Color::FromArgb(Raw_Intensity[temp], Raw_Intensity[temp], Raw_Intensity[temp]);
					surface->SetPixel(column, row, c);

				}
			}*/
		}
		
	};
	
private: System::Void drawNormalToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		
		int *Hist = new int[256];
		LPCTSTR input;
		CString str;
		int Width, Height;
		for (int i = 0; i < 256; i++)//salak visual studio direk ++ yapýnca bellekteki konumunu falan yazýyor böyle yapmadan çizmiyor gerizekalý bi dahakine aklýnda bulunsun dizilerde toplama yapacaksan ilk deger ata sabit bir ifade ver 
		{
			Hist[i] = 0;
		}

		str = pictureBox1->ImageLocation;
		input = (LPCTSTR)str;
		BYTE* buffer = LoadBMP(Width, Height, Size, input);
		BYTE* Raw_Intensity = ConvertBMPToIntensity(buffer, Width, Height);
		
		for (int i = 0; i < Width*Height; i++)
		{
			
			Hist[(int)Raw_Intensity[i]]++;
		}
		
		for (int j = 0; j < 256; j++)
		{
			chart1->Series["NOP"]->Points->AddXY(j,Hist[j]);

		}
		chart1->Visible = true;
		chart2->Visible = false;
	}

private: System::Void equalToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		
		int *Equal_Hist = new int[256];
		int *Hist = new int[256];
		int *Kumulative_Hist = new int[256];
		
		for (int i = 0; i < 256; i++)
		{
			Equal_Hist[i] = 0;
			Hist[i] = 0;
			Kumulative_Hist[i] = 0;
		}

		CString str;
		int Max_Brightness,temp;
		int index;

		str = pictureBox1->ImageLocation;
		input = (LPCTSTR)str;
		BYTE* buffer = LoadBMP(Width, Height, Size, input);
		BYTE* Raw_Intensity = ConvertBMPToIntensity(buffer, Width, Height);
		//BYTE* gray = ConvertIntensityToBMP(raw_intense, Width, Height, Size);
		for (int i = 0; i < Width*Height; i++)
		{
			Hist[(int)Raw_Intensity[i]]++;
		}

		for (int k = 256; k >= 0; k--)
		{
			if (Hist[k]>0)
			{
				Max_Brightness = k;
				break;
			}
		}
		
		Kumulative_Hist[0] = Hist[0];
		int one = round(Kumulative_Hist[0] * Max_Brightness / (Width*Height));
		Equal_Hist[one] = Kumulative_Hist[0];

		for (int i = 1; i <256; i++)
		{
			Kumulative_Hist[i] = Hist[i] + Kumulative_Hist[i - 1];
		}
		for (int j = 1; j <256; j++)
		{
			temp = round(Kumulative_Hist[j] * Max_Brightness / (Width*Height));
			Equal_Hist[temp] +=(Kumulative_Hist[j]-Kumulative_Hist[j-1]);
		}
		
		
		for (int j = 0; j < 256; j++)
		{
			chart2->Series["NOPExtended"]->Points->AddXY(j,Equal_Hist[j]);
		}
		chart2->Visible = true;
		chart1->Visible = false;

	}

private: System::Void pictureBox1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
	{
		x_axis = e->X;
		y_axis = e->Y;
		x2_axis = 0;
	}	

private: System::Void pictureBox1_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
	{
		LPCTSTR output = L"C:\\Users\\asus\\Desktop\\image\\cropimage.bmp";
		long size;
		CString str;
		str = pictureBox1->ImageLocation;
		input = (LPCTSTR)str;
		x2_axis = e->X;
		y2_axis = e->Y;
		w_size = x2_axis - x_axis;
		h_size = y2_axis - y_axis;
		paramx_axis = x_axis;
		param_yaxis = y_axis;
		if (w_size < 0 && h_size < 0)
		{
			w_size = abs(w_size);
			h_size = abs(h_size);
			paramx_axis = x2_axis;
			param_yaxis = y2_axis;
		}
		if (h_size < 0)
		{
			h_size=abs(h_size);
			param_yaxis = abs(y_axis - h_size);
			paramx_axis = x_axis;
		}
		if (w_size < 0)
		{
			w_size=abs(w_size);
			paramx_axis = x2_axis;
			param_yaxis = abs(y2_axis - h_size);
			
		}
		
		BYTE* buffer = LoadBMP(Width, Height, Size, input);
		//BYTE* Raw_Intensity = ConvertBMPToIntensity(buffer, Width, Height);//gri resim kýrpýlmýþ
		BYTE* rgbscale = RGBScale(buffer, Width, Height, Size);//gri raw_intensity
		BYTE* crop = Crop(rgbscale, Width, w_size,h_size, paramx_axis, param_yaxis);
		BYTE* save = RGBScale(crop, w_size, h_size, size);
		SaveBMP(save, w_size,h_size, size, output);

		pictureBox2->Width = w_size;
		pictureBox2->Height = h_size;
		x_axis = 0;//basma tetikleme
		
		
		//bi toolun belli bir özelliði(methodu) grafik gibi bi sýnýfýn nesnesine atanabiliyorsa onu git en basýnda tanýmla
		Bitmap^ surface = gcnew Bitmap(w_size,h_size);
		pictureBox2->Image = surface;
		pictureBox2->AutoSize;
		Color c;
		int temp;
		for (unsigned int row = 0; row < h_size; row++) {
			for (unsigned int column = 0; column < w_size; column++)
			{
				temp = row * w_size + column;
				c = Color::FromArgb(crop[3*temp+2],crop[3*temp+1],crop[3*temp]);
				surface->SetPixel(column, row, c);

			}
		}
		
	}


	private: System::Void pictureBox1_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		Graphics^ g = pictureBox1->CreateGraphics();
		Pen^ pen = gcnew Pen(Color::GhostWhite, 5.0F);
		
		int downtemp = x_axis;
		int uptemp = x2_axis;

		if (downtemp != 0)
		{
			int current_x = e->X;
			int current_y = e->Y;
			int current_paramx = x_axis;
			int curren_paramy = y_axis;
			int current_width = current_x - x_axis;
			int current_height = current_y - y_axis;
			
			if (current_width < 0 && current_height < 0)
			{
				current_width = abs(current_width);
				current_height = abs(current_height);
				current_paramx = current_x;
				curren_paramy = current_y;
			}
			if (current_height < 0)
			{
				current_height = abs(current_height);
				curren_paramy = abs(y_axis - current_height);
				current_paramx = x_axis;
			}
			if (current_width < 0)
			{
				current_width = abs(current_width);
				current_paramx = current_x;
				curren_paramy = abs(current_y - current_height);

			}
			//pictureBox1->CreateGraphics()->DrawRectangle(pen, current_paramx, curren_paramy, current_width, current_height);
			g->DrawRectangle(pen, current_paramx, curren_paramy, current_width, current_height);//recursive oluyo elimi çektiðimde alt satýra geçiyor
		}
		if (uptemp != 0)
		{
			pictureBox1->Refresh();
			
		}
}
	private: System::Void binaryToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		LPCTSTR output = L"C:\\Users\\asus\\Desktop\\image\\binaryimage.bmp";
		int *Hist = new int[256];
		int Threshold, T;
		FLOAT Wb = 0.0F, WbMean = 0.0f, Wf = 0.0f, WfMean = 0.0f, MaxT = 0.0f;
		FLOAT Wbsum = 0.0f;
		FLOAT Meansum = 0.0f;
		FLOAT Wfsum = 0.0f;//float ta int de var toplam deðerlerinide float yaparsak iki sayýnýn float bölümü float cýkar diðer türlü sonuc int çýkabilir
		FLOAT Thresholdarray[256];

		LPCTSTR input;
		CString str;
		int Width, Height;
		for (int i = 0; i < 256; i++)//salak visual studio direk ++ yapýnca bellekteki konumunu falan yazýyor böyle yapmadan çizmiyor gerizekalý bi dahakine aklýnda bulunsun dizilerde toplama yapacaksan ilk deger ata sabit bir ifade ver 
		{
			Hist[i] = 0;
			Thresholdarray[i] = 0.0f;
		}

		str = pictureBox1->ImageLocation;
		input = (LPCTSTR)str;
		BYTE* buffer = LoadBMP(Width, Height, Size, input);
		BYTE* Raw_Intensity = ConvertBMPToIntensity(buffer, Width, Height);
		/*//1.çözüm
		for (int i = 0; i < Width*Height; i++)
		{

			Hist[(int)Raw_Intensity[i]]++;
		}
		//Otsu
		for (T = 0; T < 256; T++)
		{

			for (int j = 0; j < T; j++)
			{
				Wbsum += Hist[j];
				Meansum += (j*Hist[j]);
			}

			Wb = Wbsum/ (Width * Height);
			if (Wbsum == 0)
			{
				Wbsum += 1;
			}
			WbMean = Meansum / Wbsum;
			Meansum = 0.0f;
			
			for (int i = T; i < 256; i++)
			{
				Wfsum += Hist[i];
				Meansum += (i*Hist[i]);
			}
			Wf = Wfsum/ (Width * Height);
			if (Wfsum == 0)
			{
				Wfsum += 1;
			}
			WfMean = Meansum / Wfsum;
		
			Thresholdarray[T] = (Wb * Wf)*(WbMean-WfMean)*(WbMean-WfMean);//binary yaparken bunun max degeri alýnýyor
			//sýfýrlama her deger için ayrý ayrý
			Meansum = 0.0f;
			Wf = 0.0f;
			Wfsum = 0.0f;
			WfMean = 0.0f;
			Wbsum = 0.0f;
			Wb = 0.0f;
			WbMean = 0.0f;
		}
		MaxT = Thresholdarray[0];
		for (int i = 1; i < 256; i++)
		{

			if (Thresholdarray[i] > MaxT)
			{
				MaxT = Thresholdarray[i];
			}
		}

		for (int i = 0; i < 256; i++)
		{
			if (Thresholdarray[i] == MaxT)
			{
				Threshold = i;
			}
		}
		*/
		//end Otsu
		int thres=D2_K_Mean_Clustering(Raw_Intensity, Width, Height);//2.method
		BYTE* binary = BinaryImage(Raw_Intensity, Width, Height,thres);
		BYTE* New_Image = ConvertIntensityToBMP(binary, Width, Height, Size);
		SaveBMP(New_Image, Width, Height, Size, output);
		

		pictureBox2->Width = Width;
		pictureBox2->Height = Height;
		Bitmap^ surface = gcnew Bitmap(Width, Height);
		pictureBox2->Image = surface;
		pictureBox2->AutoSize;
		Color c;
		int temp;
		for (unsigned int row = 0; row < Height; row++) {
			for (unsigned int column = 0; column < Width; column++)
			{
				temp = row * Width + column;
				c = Color::FromArgb(binary[temp], binary[temp], binary[temp]);
				surface->SetPixel(column, row, c);

			}
		}

	}

private: System::Void clearToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
{
	chart1->Visible = false;
	chart2->Visible = false;
	pictureBox1->Visible=false;
	pictureBox2->Visible=false;
	pictureBox2->Image = nullptr;
	chart1->Series["NOP"]->Points->Clear();
	chart2->Series["NOPExtended"]->Points->Clear();
}

private: System::Void rGBScaleToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
	CString str;
	str = pictureBox1->ImageLocation;
	input = (LPCTSTR)str;
	BYTE* buffer = LoadBMP(Width, Height, Size, input);
	BYTE* ptr = RGBScale(buffer,Width,Height,Size);

	//picturebox2 ye yeni resmi koymak için
	pictureBox2->Width = Width;
	pictureBox2->Height = Height;
	Bitmap^ surface = gcnew Bitmap(Width, Height);
	pictureBox2->Image = surface;
	
	Color c;
	int temp;
	for (unsigned int row = 0; row < Height; row++) {
		for (unsigned int column = 0; column < Width; column++)
		{
			temp = row * Width + column;
			c = Color::FromArgb(ptr[(3*temp+2)],ptr[(3*temp)+1], ptr[(3*temp)]);
			surface->SetPixel(column, row, c);
			
		}
	}


}
private: System::Void dilationToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
{
	int Threshold;	
	LPCTSTR input;
	CString str;
	int Width, Height;
	
	str = pictureBox1->ImageLocation;
	input = (LPCTSTR)str;
	BYTE* buffer = LoadBMP(Width, Height, Size, input);
	BYTE* Raw_Intensity = ConvertBMPToIntensity(buffer, Width, Height);
	Threshold = D2_K_Mean_Clustering(Raw_Intensity, Width, Height);
	BYTE* binary = BinaryImage(Raw_Intensity, Width, Height, Threshold);
	BYTE Mask[9] = { 1,1,1,1,1,1,1,1,1 };
	/*BYTE* Mask = new BYTE[3 * 3];
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			int tp = i *3 + j;
			Mask[tp] = 1;
		}
	}*/
	LPCTSTR output = L"C:\\Users\\asus\\Desktop\\image\\dilation.bmp";
	BYTE *dila = Dilation(binary, Width, Height, Mask, 3, 3);
	BYTE* New_Image = ConvertIntensityToBMP(dila, Width, Height, Size);
	SaveBMP(New_Image, Width, Height, Size, output);

	pictureBox2->Width = Width;
	pictureBox2->Height = Height;
	Bitmap^ surface = gcnew Bitmap(Width, Height);
	pictureBox2->Image = surface;

	Color c;
	int temp;
	for (unsigned int row = 0; row < Height; row++) {
		for (unsigned int column = 0; column < Width; column++)
		{
			temp = row * Width + column;
			c = Color::FromArgb(dila[temp], dila[temp], dila[temp]);
			surface->SetPixel(column, row, c);
		}
	}
}
private: System::Void erosionToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
{
	int Threshold;
	LPCTSTR input;
	CString str;
	int Width, Height;
	
	str = pictureBox1->ImageLocation;
	input = (LPCTSTR)str;
	BYTE* buffer = LoadBMP(Width, Height, Size, input);
	BYTE* Raw_Intensity = ConvertBMPToIntensity(buffer, Width, Height);
	Threshold = D2_K_Mean_Clustering(Raw_Intensity, Width, Height);
	BYTE* binary = BinaryImage(Raw_Intensity, Width, Height, Threshold);
	BYTE Mask[9] = { 0,1,0,1,1,1,0,1,0};
	
	/*BYTE* Mask = new BYTE[3 * 3];
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			int tp = i * 3 + j;
			Mask[tp] = 0;
			
		}
	}*/
	LPCTSTR output = L"C:\\Users\\asus\\Desktop\\image\\erosion.bmp";
	BYTE *erosion = Erosion(binary, Width, Height, Mask, 3, 3);
	BYTE* New_Image = ConvertIntensityToBMP(erosion, Width, Height, Size);
	SaveBMP(New_Image, Width, Height, Size, output);

	pictureBox2->Width = Width;
	pictureBox2->Height = Height;
	Bitmap^ surface = gcnew Bitmap(Width, Height);
	pictureBox2->Image = surface;

	Color c;
	int temp;
	for (unsigned int row = 0; row < Height; row++) {
		for (unsigned int column = 0; column < Width; column++)
		{
			temp = row * Width + column;
			c = Color::FromArgb(erosion[temp], erosion[temp], erosion[temp]);
			surface->SetPixel(column, row, c);
		}
	}
}

private: System::Void mirrorImageToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
{
	CString str;
	str = pictureBox1->ImageLocation;
	input = (LPCTSTR)str;
	BYTE* buffer = LoadBMP(Width, Height, Size, input);
	BYTE* ptr = MirrorImage(buffer,Size);

	//picturebox2 ye yeni resmi koymak için
	pictureBox2->Width = Width;
	pictureBox2->Height = Height;
	Bitmap^ surface = gcnew Bitmap(Width, Height);
	pictureBox2->Image = surface;

	Color c;
	int temp;
	for (unsigned int row = 0; row < Height; row++) {
		for (unsigned int column = 0; column < Width; column++)
		{
			temp = row * Width + column;
			c = Color::FromArgb(ptr[(3 * temp)], ptr[(3 * temp) + 1], ptr[(3 * temp)+2]);
			surface->SetPixel(column, row, c);

		}
	}
}

private: System::Void rGBSegmentToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
{
	CString str;
	str = pictureBox1->ImageLocation;
	input = (LPCTSTR)str;
	BYTE* buffer = LoadBMP(Width, Height, Size, input);
	BYTE* Raw_Intensity = ConvertBMPToIntensity(buffer, Width, Height);
	BYTE* intensegment = MULTID_K_Means_Clustering(Raw_Intensity, Width, Height,5);
	//picturebox2 ye yeni resmi koymak için
	pictureBox2->Width = Width;
	pictureBox2->Height = Height;
	Bitmap^ surface = gcnew Bitmap(Width, Height);
	pictureBox2->Image = surface;

	Color c;
	int temp;
	for (unsigned int row = 0; row < Height; row++) {
		for (unsigned int column = 0; column < Width; column++)
		{
			temp = row * Width + column;
			c = Color::FromArgb(intensegment[temp], intensegment[temp], intensegment[temp]);
			surface->SetPixel(column, row, c);

		}
	}

}
private: System::Void rGBSegmentToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e) 
{
	LPCTSTR output = L"C:\\Users\\asus\\Desktop\\image\\rgbsegment.bmp";
	CString str;
	str = pictureBox1->ImageLocation;
	input = (LPCTSTR)str;
	BYTE* buffer = LoadBMP(Width, Height, Size, input);
	//BYTE* Raw_Intensity = ConvertBMPToIntensity(buffer, Width, Height);
	BYTE* rgb = RGBScale(buffer, Width, Height, Size);
	BYTE* rgbsegment = MultD_K_Means_Clustering(rgb,Width, Height,3);
	SaveBMP(rgbsegment, Width, Height, Size, output);
	//picturebox2 ye yeni resmi koymak için
	pictureBox2->Width = Width;
	pictureBox2->Height = Height;
	Bitmap^ surface = gcnew Bitmap(Width, Height);
	pictureBox2->Image = surface;

	Color c;
	int temp;
	for (unsigned int row = 0; row < Height; row++) {
		for (unsigned int column = 0; column < Width; column++)
		{
			temp = row * Width + column;
			c = Color::FromArgb(rgbsegment[3*temp+2], rgbsegment[3*temp+1], rgbsegment[3*temp]);
			surface->SetPixel(column, row, c);

		}
	}
}


private: System::Void boundaryToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
{
	int Threshold;
	LPCTSTR input;
	CString str;
	int Width, Height;
	LPCTSTR output= L"C:\\Users\\asus\\Desktop\\image\\boundary.bmp";

	str = pictureBox1->ImageLocation;
	input = (LPCTSTR)str;
	BYTE* buffer = LoadBMP(Width, Height, Size, input);
	BYTE* Raw_Intensity = ConvertBMPToIntensity(buffer, Width, Height);
	Threshold = D2_K_Mean_Clustering(Raw_Intensity, Width, Height);
	BYTE* binary = BinaryImage(Raw_Intensity, Width, Height, Threshold);
	BYTE Mask[9] = { 0,1,0,1,1,1,0,1,0 };
	/*BYTE* Mask = new BYTE[3 * 3];
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			int tp = i * 3 + j;
			Mask[tp] = 0;
		}
	}*/
	BYTE *erosion = Erosion(binary, Width, Height, Mask, 3, 3);
	BYTE *bound = Boundary(erosion, binary, Width, Height);
	BYTE* New_Image = ConvertIntensityToBMP(bound, Width, Height, Size);
	SaveBMP(New_Image, Width, Height, Size, output);


	pictureBox2->Width = Width;
	pictureBox2->Height = Height;
	Bitmap^ surface = gcnew Bitmap(Width, Height);
	pictureBox2->Image = surface;

	Color c;
	int temp;
	for (unsigned int row = 0; row < Height; row++) {
		for (unsigned int column = 0; column < Width; column++)
		{
			temp = row * Width + column;
			c = Color::FromArgb(bound[temp], bound[temp], bound[temp]);
			surface->SetPixel(column, row, c);
		}
	}

}


private: System::Void cCLToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
{
	CString str;
	str = pictureBox1->ImageLocation;
	input = (LPCTSTR)str;
	BYTE* buffer = LoadBMP(Width, Height, Size, input);
	BYTE* Raw_Intensity = ConvertBMPToIntensity(buffer, Width, Height);
	int Threshold = D2_K_Mean_Clustering(Raw_Intensity, Width, Height);
	BYTE* binary = BinaryImage(Raw_Intensity, Width, Height, Threshold);
	BYTE* rgb = RGBScale(buffer, Width, Height, Size);

	BYTE* label = CCL(binary, Width, Height);
	int sayi = CounterObject(label, Width, Height);
	BYTE* coloring = CCLColoring(label,rgb,Width, Height,Size);
	MessageBox::Show(sayi.ToString());
	
	pictureBox2->Width = Width;
	pictureBox2->Height = Height;
	Bitmap^ surface = gcnew Bitmap(Width, Height);
	pictureBox2->Image = surface;

	Color c;
	int temp;
	for (unsigned int row = 0; row < Height; row++) {
		for (unsigned int column = 0; column < Width; column++)
		{
			temp = row * Width + column;
			c = Color::FromArgb(coloring[3*temp+2], coloring[3*temp+1], coloring[3*temp]);
			surface->SetPixel(column, row, c);
		}
	}


}


private: System::Void cannyEdgeToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
{
	CString str;
	str = pictureBox1->ImageLocation;
	input = (LPCTSTR)str;
	int Width, Height,tp;
	int m_w = 3;
	int m_h = 3;
	BYTE* buffer = LoadBMP(Width, Height, Size, input);
	BYTE* Raw_Intensity = ConvertBMPToIntensity(buffer, Width, Height);
	int w_new = Width - (m_w - 1);
	int h_new = Height - (m_h - 1);
	BYTE* display = new BYTE[w_new*h_new];
	int dikeytürev[9] = { 1,2,1,0,0,0,-1,-2,-1 };//mask
	int yataytürev[9] = { 1,0,-1,2,0,-2,1,0,-1 };
	int* deriveV = Convolution(Raw_Intensity, Width, Height, dikeytürev, m_w, m_h);
	int* deriveH = Convolution(Raw_Intensity, Width, Height, yataytürev, m_w, m_h);
	double* edgeimge = edgeimage(deriveH, deriveV, 1020, w_new, h_new);
	//double* angle = gradient(deriveH, deriveV, w_new, h_new);
	//double* nonmax = nms(edgeimge, angle, w_new, h_new);
	//double* histt = histerize_threshold(nonmax, w_new, h_new);
	//double* bedge = binaryedge(histt, angle, w_new, h_new);
	for (int row = 0; row < h_new; row++)
	{
		for (int col = 0; col < w_new; col++)
		{
			tp = row * w_new + col;
			display[tp] =edgeimge[tp];//edgeimge ve bedge alýr edgeimge türevlerden sonra direk cýkar diðeri nms den sonra
		}
	}
	//int Threshold = D2_K_Mean_Clustering(display, Width, Height);
	//BYTE* binary = BinaryImage(display, Width, Height, Threshold);//bu kýsým edge den nms siz kenarlarý bulma
	/*for (int row = 0; row < h_new; row++)
	{
		for (int col = 0; col < w_new; col++)
		{
			tp = row * w_new + col;
			if (display[tp] == 1)
			{
				display[tp] = 255;
			}
		}
	}*/
	
	pictureBox2->Width = w_new;
	pictureBox2->Height = h_new;
	Bitmap^ surface = gcnew Bitmap(w_new, h_new);
	pictureBox2->Image = surface;

	Color c;
	int temp;
	for (unsigned int row = 0; row < h_new; row++) {
		for (unsigned int column = 0; column < w_new; column++)
		{	
			temp = row * w_new + column;
			c = Color::FromArgb(display[temp], display[temp], display[temp]);
			surface->SetPixel(column, row, c);
		}
	}
}
		  



};
}
//end point
