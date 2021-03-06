﻿// Nhận diện khuôn mặt trên ảnh


#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <iostream>

using namespace dlib;
using namespace std;

// ----------------------------------------------------------------------------------------

int main(int argc, char** argv)
{
	try
	{
		if (argc == 1)
		{
			cout << "Give some image files as arguments to this program." << endl;
			return 0;
		}

		frontal_face_detector detector = get_frontal_face_detector();
		image_window win;

		// Loop over all the images provided on the command line.
		for (int i = 1; i < argc; ++i)
		{
			cout << "processing image " << argv[i] << endl;
			array2d<unsigned char> img;
			load_image(img, argv[i]);
			
			
			// phóng to ảnh lên x2 bằng hàm PYRAMID_UP()
			// vì trình phát hiện khuôn mặt chỉ tìm kiếm các khuôn mặt  có kích thước >= 80*80px
			//nếu muốn nhận diện mặt nhỏ hơn tâm 40*40px thì chạy thêm hàm này 1 lần nữa
			pyramid_up(img);

			
			//hiển thị hộp vuông xung quanh các mặt phát hiện được
			std::vector<rectangle> dets = detector(img);

			cout << "So khuon mat phat hien duoc la: " << dets.size() << endl;
			
			//hiển thị kết quả với viền là màu xanh
			win.clear_overlay();
			win.set_image(img);
			win.add_overlay(dets, rgb_pixel(0, 255, 0));

			cout << "Hit enter to process the next image..." << endl;
			cin.get();
		}
	}
	catch (exception& e)
	{
		cout << "\nexception thrown!" << endl;
		cout << e.what() << endl;
	}
}

// ----------------------------------------------------------------------------------------

