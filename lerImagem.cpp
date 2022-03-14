#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

#include <omp.h>

#include <iostream>
#include <stdio.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int showImage(char arq[])
{

	Mat imagem;
	imagem = imread(arq);
	Size sz = imagem.size();

	cout << sz << endl;
	cout << imagem.cols << endl;
	cout << imagem.rows << endl;
	cout << imagem.u << endl;
	cout << imagem.allocator << endl;
	cout << imagem.step << endl;
	cout << imagem.size << endl;
	// cout << imagem.data << endl;
	cout << imagem.dataend << endl;
	cout << imagem.datalimit << endl;
	// cout << imagem.datastart << endl;
	cout << imagem.dims << endl;
	cout << imagem.flags << endl;

	if (!imagem.data)
	{
		cout << "Could not open or"
			 << " find the image\n";
		return 0;
	}

	// int ci = 0, cj = 0;
	// for (int i = 0; i < imagem.cols; i++){
	// 	for (int j = 0; j < imagem.rows; j++){
	// 		// Vec3b pixel = imagem.at<Vec3b>(i,j);
	// 		// cout << pixel;
	// 		// cout << "\t";
	// 	}
	// }

	int altW = 97;
	int cropped = 97;
	int aux_cropped = 0;

	Mat cropped_image1 = imagem(Range(0, cropped), Range(1, 599));

	Mat cropped_image2 = imagem(Range(cropped + 1, cropped * 2 + 1), Range(1, 599));

	Mat cropped_image3 = imagem(Range(cropped * 2 + 1, cropped * 3 + 1), Range(1, 599));

	Mat cropped_image4 = imagem(Range(cropped * 3 + 1, imagem.rows), Range(1, 599));

	// namedWindow("Imagem 2", WINDOW_FREERATIO);
	// resizeWindow("Imagem 2", 97, 600);
	// imshow("Imagem 2", cropped_image2);

	// namedWindow("Imagem 1", WINDOW_FREERATIO);
	// resizeWindow("Imagem 1", 97, 600);
	// imshow("Imagem 1", cropped_image1);

	// namedWindow("Imagem 3", WINDOW_FREERATIO);
	// resizeWindow("Imagem 3", 97, 600);
	// imshow("Imagem 3", cropped_image3);

	// namedWindow("Imagem 4", WINDOW_FREERATIO);
	// resizeWindow("Imagem 4", 97, 600);
	// imshow("Imagem 4", cropped_image4);


	// Mat3b res(400, Vec3b(0,0,0));
	// cropped_image1.copyTo(res(Rect(0,0, cropped_image1.cols, cropped_image1.rows)));
	// cropped_image2.copyTo(res(Rect(cropped_image1.cols, 0, cropped_image2.cols, cropped_image2.rows)));

	Mat res; 
	Mat res2;
	Mat res3;
	
	vconcat(cropped_image1, cropped_image2,  res);
	vconcat(res, cropped_image3, res2);
	vconcat(res2, cropped_image4, res3);

	namedWindow("Imagem", WINDOW_FREERATIO);
	resizeWindow("Imagem", 97, 600);
	imshow("Imagem", imagem);

	namedWindow("Imagem 5", WINDOW_FREERATIO);
	resizeWindow("Imagem 5", 97, 600);
	imshow("Imagem 5", res3);
	waitKey(0);



	
	// Mat erode_output;
	// erode(imagem, erode_output, getStructuringElement(MORPH_RECT, Size(7, 7)));
	// namedWindow("Erode", WINDOW_FREERATIO);
	// resizeWindow("Erode", 800, 800);
	// imshow("Erode", erode_output);

	// Mat dilate_output;
	// dilate(imagem, dilate_output, getStructuringElement(MORPH_RECT, Size(10, 10)));
	// namedWindow("Dilate", WINDOW_FREERATIO);
	// resizeWindow("Dilate", 800, 800);
	// imshow("Dilate", dilate_output);

	// int morph_size = 3;

	// Mat element = getStructuringElement(
	// 	MORPH_RECT,
	// 	Size(2 * morph_size + 1, 2 * morph_size + 1),
	// 	Point(morph_size, morph_size));

	// Mat output;

	// morphologyEx(imagem, output, MORPH_OPEN, element, Point(-1, -1), 2);

	// namedWindow("Imagem 1", WINDOW_FREERATIO);
	// namedWindow("Imagem 2", WINDOW_FREERATIO);
	// resizeWindow("Imagem 1", 800, 800);
	// resizeWindow("Imagem 2", 800, 800);
	// imshow("Imagem 1", imagem);
	// imshow("Imagem 2", output);

	return (0);
}

int main(int argc, char *argv[])
{

	showImage(argv[1]);
	return (0);
}