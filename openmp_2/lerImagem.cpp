
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

	Mat erode_output;
	Mat dilate_output;

	double start = omp_get_wtime();
	#pragma parallel num_threads(2) defult(none) shareads(imagem, erode_output, dilate_output)
	{
		#pragma omp single
		{
			erode(imagem, erode_output, getStructuringElement(MORPH_CROSS, Size(5,5)));
		}

		#pragma omp single
		{
			dilate(erode_output, dilate_output, getStructuringElement(MORPH_CROSS, Size(5,5)));	
		}
	}
	double end = omp_get_wtime();

	cout << "Time:\t";
	cout << end - start << endl;
	
	// namedWindow("Imagem", WINDOW_FREERATIO);
	// resizeWindow("Imagem", 97, 600);
	// imshow("Imagem", imagem);

	// namedWindow("Resultado", WINDOW_FREERATIO);
	// resizeWindow("Resultado", 97, 600);
	// imshow("Resultado", dilate_output);
	// waitKey(0);


	return (0);
}

int main(int argc, char *argv[]){

	showImage(argv[1]);
	return (0);
}