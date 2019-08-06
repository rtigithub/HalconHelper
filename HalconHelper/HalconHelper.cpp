// HalconHelper.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "HalconCpp.h"
#include "HDevThread.h"
#include "bdaqctrl.h"
//#include "compatibility.h"

using namespace HalconCpp;
using namespace std;
using namespace Automation::BDaq;

Herror TryReadImage(HalconCpp::HImage& image, const char* filename);
void run(void);

// procedure which reads images with error handling
Herror TryReadImage(HalconCpp::HImage& image, const char* filename)
{
	Herror  error_num;

	try
	{
		cout << endl << "Trying to read '" << filename << "' ... ";
		image.ReadImage(filename);
	}
	catch (HException& except)
	{
		error_num = except.ErrorCode();
		cout << endl << except.ErrorMessage() << endl;
		return error_num;
	}
	// success
	cout << "succeeded!" << endl;
	return H_MSG_TRUE;
}

void run(void)
{
	HImage        image;
	Hlong         width, height;
	Herror        status;
	HWindow       window(0, 0, 100, 100);

	window.ClearWindow();
	status = TryReadImage(image, "mreut");
	if (status == H_MSG_TRUE)
	{
		width = image.Width()[0];
		height = image.Height()[0];
		window.SetWindowExtents(0, 0, width, height);
		window.SetPart(0, 0, height - 1, width - 1);
		image.DispImage(window);
		cout << "Halcon initialized and image loaded." << endl;

	}
	cout << "Hit <Enter> to quit" << endl;
	cin.get();
}

// main program
int main(int argc, char* argv[])
{
	SetSystem("use_window_thread", "true");

	static InstantDiCtrl* instantDiCtrl = InstantDiCtrl::Create();
	cout << "biodaq.dll successfully loaded" << endl;
	run();

	cout << "Goodbye" << endl;
}