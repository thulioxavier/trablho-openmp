
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <omp.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#define clipping 4

using namespace std;
using namespace cv;


int showImage(char arq[])
{

	Mat imagem;
	imagem = imread(arq);

	if (!imagem.data){
		cout << "Could not open or"
			 << "find the image\n";
		return 0;
	}


	Size sz = imagem.size();

	int cropped = trunc(imagem.rows / clipping);
	int rows_rest = 0;
	int rest = imagem.rows - (cropped * clipping);

	if (rest == 0){
		printf("clipping square\n");
	}else{
		rows_rest = cropped + rest;
	}

	cout << cropped << endl;
	cout << rest << endl;
	cout << rows_rest << endl;

	// printf("Elementos Estruturantes:\n");

	// cout << getStructuringElement(MORPH_CROSS, Size(7,7)) << endl;
	// cout << "\n" << endl;
	// cout << getStructuringElement(MORPH_ELLIPSE, Size(7,7)) << endl;
	// cout << "\n" << endl;
	// cout << getStructuringElement(MORPH_RECT, Size(7,7)) << endl;

	Mat cropped_image1, cropped_image2, cropped_image3, cropped_image4;
	Mat erode_output1, erode_output2, erode_output3, erode_output4;
	Mat dilate_output1, dilate_output2, dilate_output3, dilate_output4;

	Mat res; 
	Mat res2;
	Mat res3;
	
	Mat resD; 
	Mat resD2;
	Mat resD3;

	double start = omp_get_wtime();
	cropped_image1 = imagem(Range(0, cropped), Range(1, imagem.cols));
	erode(cropped_image1, erode_output1, getStructuringElement(MORPH_CROSS, Size(5,5)));
	dilate(erode_output1, dilate_output1, getStructuringElement(MORPH_CROSS, Size(5,5)));

	cropped_image2 = imagem(Range(cropped + 1, cropped * 2 + 1), Range(1, imagem.cols));
	erode(cropped_image2, erode_output2, getStructuringElement(MORPH_CROSS, Size(5,5)));
	dilate(erode_output2, dilate_output2, getStructuringElement(MORPH_CROSS, Size(5,5)));

	cropped_image3 = imagem(Range(cropped * 2 + 1, cropped * 3 + 1), Range(1, imagem.cols));
	erode(cropped_image3, erode_output3, getStructuringElement(MORPH_CROSS, Size(5,5)));
	dilate(erode_output3, dilate_output3, getStructuringElement(MORPH_CROSS, Size(5,5)));

	cropped_image4 = imagem(Range((cropped * 3) + rows_rest + 1, imagem.rows), Range(1, imagem.cols));
	erode(cropped_image4, erode_output4, getStructuringElement(MORPH_CROSS, Size(5,5)));
	dilate(erode_output4, dilate_output4, getStructuringElement(MORPH_CROSS, Size(5,5)));

	vconcat(dilate_output1, dilate_output2,  resD);
	vconcat(resD, dilate_output3, resD2);
	vconcat(resD2, dilate_output4, resD3);
	double end = omp_get_wtime();

	cout << "Time:\t";
	cout << end - start << endl;

	vconcat(erode_output1, erode_output2,  res);
	vconcat(res, erode_output3, res2);
	vconcat(res2, erode_output4, res3);

	namedWindow("Imagem", WINDOW_FREERATIO);
	resizeWindow("Imagem", 97, 600);
	imshow("Imagem", imagem);

	namedWindow("DIlate", WINDOW_FREERATIO);
	resizeWindow("DIlate", 97, 600);
	imshow("DIlate", resD3);

	namedWindow("Erode", WINDOW_FREERATIO);
	resizeWindow("Erode", 97, 600);
	imshow("Erode", res3);
	waitKey(0);


	return (0);
}

int main(int argc, char *argv[]){

	showImage(argv[1]);
	return (0);
}