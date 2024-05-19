#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <string>
#include "image_estimator.h"
#include "image_noiser.h"
#include "stream_manager.h"
#include "simple_image_filters.h"
#include "stream_manager.h"
#include <opencv2/photo.hpp>
#include <cmath>

#include "convolution_tools.h"
#include "gauss_filter.h"
#include "median_filter.h"
#include "nlm_filter.h"
#include "simple_image_filters.h"
#include "filters.h"
#include "image_mat_tools.h"

std::string type2str(int type);
Matrix<uint8_t> copy_one_m_channel2vector(cv::Mat image, int num_of_channel);

cv::Mat split3channels2image(Matrix<uint8_t> image_ch1,
													   Matrix<uint8_t> image_ch2,
													   Matrix<uint8_t> image_ch3);

int main(int argc, char* argv[]) {

	//imread test image
	std::string path1 = "../Images/artifical_341_512.bmp";
	std::string path2 = "../Images/DeltaE_8bit_gamma2.2.bmp";
	cv::Mat blue_channe_one, input_image_two;
	cv::Mat im_after_gauss_noise;
	cv::Mat im_after_gauss_filter;
	cv::Mat im_after_median_filter;
	cv::Mat im_after_nlm_filter;
	cv::Mat im_after_laplace_filter;

	blue_channe_one = cv::imread(path1);
	input_image_two = cv::imread(path2);
	int wight = blue_channe_one.size().width;
	int hight =  blue_channe_one.size().height;

	//need optimize now this code can works only with small images
	cv::resize(blue_channe_one, blue_channe_one, cv::Size(wight, hight));
	cv::resize(input_image_two, input_image_two, cv::Size(wight, hight));

	//add gaussian noise to image
	image_noiser noiser_image;
	simple_image_filters image_filter;

	const float mean = 5.0;
	const float sigma = 8.0;

	noiser_image.AddGaussianNoise_Opencv(blue_channe_one, im_after_gauss_noise, mean, sigma);

	//split image on 3 channels
	Matrix<uint8_t> red_channel = copy_one_m_channel2vector(im_after_gauss_noise, 0);
	Matrix<uint8_t> green_channel = copy_one_m_channel2vector(im_after_gauss_noise, 1);
	Matrix<uint8_t> blue_channel = copy_one_m_channel2vector(im_after_gauss_noise, 2);

	//smooth image with gauss filter
	gauss_filter gauss_filt_tool;
	red_channel = gauss_filt_tool.gauss_filter_2_dims(red_channel, 0.8);
	green_channel = gauss_filt_tool.gauss_filter_2_dims(green_channel, 0.8);
	blue_channel = gauss_filt_tool.gauss_filter_2_dims(blue_channel, 0.8);

	im_after_gauss_filter = split3channels2image(red_channel, green_channel, blue_channel);

	//apply median filter to image
	median_filter median_filter_tool;
	red_channel = median_filter_tool.median_filter_2_dims(red_channel, 3);
	green_channel = median_filter_tool.median_filter_2_dims(green_channel, 3);
	blue_channel = median_filter_tool.median_filter_2_dims(blue_channel, 3);

	im_after_median_filter = split3channels2image(red_channel, green_channel, blue_channel);
	
	////apply NLM filter to image
	nlm_filter nlm_filter_tool;
	red_channel = nlm_filter_tool.nlm_filter_2_dims(red_channel, 5, 10, 0.04);
	green_channel = nlm_filter_tool.nlm_filter_2_dims(green_channel, 5, 10, 0.04);
	blue_channel = nlm_filter_tool.nlm_filter_2_dims(blue_channel, 5, 10, 0.04);

	im_after_nlm_filter = split3channels2image(red_channel, green_channel, blue_channel);
	
	//apply laplase filter to image

	Matrix<float> kernel = { {1.0f,1.0f,1.0f},{1.0f,-8.0,1.0f},{1.0f,1.0f,1.0f} };

	//Matrix<float> kernel = { {0.0f,0.0f,1.0f,0.0f,0.0f},{0.0f,1.0f,2.0f,1.0f,0.0f},{1.0f,2.0f,-16.0f,2.0f,1.0f},{0.0f,1.0f,2.0f,1.0f,0.0f},{0.0f,0.0f,1.0f,0.0f,0.0f}};

    //getting borders from original image
	//Matrix<uint8_t> red_channel_orig = copy_one_m_channel2vector(blue_channe_one, 0);
	//Matrix<uint8_t> green_channel_orig = copy_one_m_channel2vector(blue_channe_one, 1);
	//Matrix<uint8_t> blue_channel_orig = copy_one_m_channel2vector(blue_channe_one, 2);

	//Matrix<uint8_t> red_channel_filt = image_filter.simple_filter_2_dims(red_channel_orig, kernel);
	//Matrix<uint8_t> green_channel_filt = image_filter.simple_filter_2_dims(green_channel_orig, kernel);
	//Matrix<uint8_t> blue_channel_filt = image_filter.simple_filter_2_dims(blue_channel_orig, kernel);
	filters simple_filter;
	image_mat_tools mat_tool;
    Matrix<uint8_t> red_channel_filt = simple_filter.simple_filter_2_dims(red_channel, kernel);
	Matrix<uint8_t> green_channel_filt = simple_filter.simple_filter_2_dims(green_channel, kernel);
	Matrix<uint8_t> blue_channel_filt = simple_filter.simple_filter_2_dims(blue_channel, kernel);

	red_channel = mat_tool.image_substract(red_channel, red_channel_filt);
	green_channel = mat_tool.image_substract(green_channel, green_channel_filt);
	blue_channel = mat_tool.image_substract(blue_channel, blue_channel_filt);

	im_after_laplace_filter = split3channels2image(red_channel, green_channel, blue_channel);

	//show result image
    image_estimator get_ssim_psnr;
	std::cout << "===============PSNR Estimating================= " << std::endl;

    double psnr = get_ssim_psnr.getPSNR(blue_channe_one, input_image_two);
	std::cout << "PSNR Reference_Res and Task_Res Image = " << psnr << std::endl;
	psnr = get_ssim_psnr.getPSNR(blue_channe_one, im_after_gauss_noise);
	std::cout << "Resized Image and After Gaussian Noise = " << psnr << std::endl;
	psnr = get_ssim_psnr.getPSNR(blue_channe_one, im_after_gauss_filter);
	std::cout << "Resized Image and After Gauss Filter = " << psnr << std::endl;
	psnr = get_ssim_psnr.getPSNR(blue_channe_one, im_after_median_filter);
	std::cout << "Resized Image and After Median Filter = " << psnr << std::endl;
	psnr = get_ssim_psnr.getPSNR(blue_channe_one, im_after_nlm_filter);
	std::cout << "Resized Image and After NLM Filter = " << psnr << std::endl;
	psnr = get_ssim_psnr.getPSNR(blue_channe_one, im_after_laplace_filter);
	std::cout << "Resized Image and After NLM Filter = " << psnr << std::endl;

	std::cout << "===============SSIM Estimating================= " << std::endl;

	cv::Scalar ssim = get_ssim_psnr.getMSSIM(blue_channe_one, input_image_two);
	float ssim_aver = (ssim[0] + ssim[1] + ssim[2]) / 3;
	std::cout << "PSNR Reference_Res and Task_Res Image = " << ssim_aver << std::endl;
	ssim = get_ssim_psnr.getMSSIM(blue_channe_one, im_after_gauss_noise);
	ssim_aver = (ssim[0] + ssim[1] + ssim[2]) / 3;
	std::cout << "Resized Image and After Gaussian Noise = " << ssim_aver << std::endl;
	ssim = get_ssim_psnr.getMSSIM(blue_channe_one, im_after_gauss_filter);
	ssim_aver = (ssim[0] + ssim[1] + ssim[2]) / 3;
	std::cout << "Resized Image and After Gauss Filter = " << ssim_aver << std::endl;
	ssim = get_ssim_psnr.getMSSIM(blue_channe_one, im_after_median_filter);
	ssim_aver = (ssim[0] + ssim[1] + ssim[2]) / 3;
	std::cout << "Resized Image and After Median Filter = " << ssim_aver << std::endl;
	ssim = get_ssim_psnr.getMSSIM(blue_channe_one, im_after_nlm_filter);
	ssim_aver = (ssim[0] + ssim[1] + ssim[2]) / 3;
	std::cout << "Resized Image and After NLM Filter = " << ssim_aver << std::endl;
	ssim = get_ssim_psnr.getMSSIM(blue_channe_one, im_after_laplace_filter);
	ssim_aver = (ssim[0] + ssim[1] + ssim[2]) / 3;
	std::cout << "Resized Image and After NLM Filter = " << ssim_aver << std::endl;

	std::cout << "=== SSIM Estimating and PSNR for Task_Res and Filtred Images ===" << std::endl;
	psnr = get_ssim_psnr.getPSNR(blue_channe_one, im_after_laplace_filter);
	std::cout << "PSNR Task_Res and Filtred Image = " << psnr << std::endl;
	ssim = get_ssim_psnr.getMSSIM(blue_channe_one, im_after_laplace_filter);
	ssim_aver = (ssim[0] + ssim[1] + ssim[2]) / 3;
	std::cout << "SSIM Task_Res and Filtred Image = " << ssim_aver << std::endl;

	imshow("Image Task", blue_channe_one);
	imshow("Image Reference", input_image_two);
	imshow("Noised Image", im_after_gauss_noise);
	imshow("Image After Gauss Filter", im_after_gauss_filter);
	imshow("Image After Median Filter Filter", im_after_median_filter);
	imshow("Image After NLM Filter", im_after_nlm_filter);
	imshow("Image After Laplace Filter", im_after_laplace_filter);

	cv::waitKey(0);

	return 0;
}


Matrix<uint8_t> copy_one_m_channel2vector(cv::Mat blue_channe_one, int num_of_channel) {


	cv::Mat different_Channels[3];
    split(blue_channe_one, different_Channels);//splitting images into 3 different channels//  
    cv::Mat need_channel = different_Channels[num_of_channel];//loading blue channels//
    //cv::Mat g = different_Channels[1];//loading green channels//
    //cv::Mat r = different_Channels[2];//loading red channels//  
	int m = blue_channe_one.rows;
	int n = blue_channe_one.cols;
	Matrix<uint8_t> vec2(m, std::vector<uint8_t>(n, 0));
	for (int i = 0; i < m; i++) {
	
		uint8_t* ptr_val = need_channel.ptr<uint8_t>(i);
		for (int j = 0; j < n; j++) {

			vec2[i][j] = *ptr_val++;

		}
	
	}

	return vec2;
}
//image_ch1 = b
//image_ch2 = g
//image_ch3 = r
cv::Mat split3channels2image(Matrix<uint8_t> image_ch1,
	Matrix<uint8_t> image_ch2,
	Matrix<uint8_t> image_ch3) {

	
	//split(blue_channe_one, different_Channels);//splitting images into 3 different channels//  
	//cv::Mat need_channel = different_Channels[num_of_channel];//loading blue channels//
	//cv::Mat g = different_Channels[1];//loading green channels//
	//cv::Mat r = different_Channels[2];//loading red channels//  
	int m = image_ch1.size();
	int n = image_ch1[0].size();
	cv::Mat channel1(m,n, CV_8U);
	cv::Mat channel2(m,n, CV_8U);
	cv::Mat channel3(m,n, CV_8U);
	for (int i = 0; i < m; i++) {

		uint8_t* ptr_val = channel1.ptr<uint8_t>(i);
		for (int j = 0; j < n; j++) {

		  *ptr_val++ = image_ch1[i][j];

		}

	}

	for (int i = 0; i < m; i++) {

		uint8_t* ptr_val = channel2.ptr<uint8_t>(i);
		for (int j = 0; j < n; j++) {

			*ptr_val++ = image_ch2[i][j];

		}

	}

	for (int i = 0; i < m; i++) {

		uint8_t* ptr_val = channel3.ptr<uint8_t>(i);
		for (int j = 0; j < n; j++) {

			*ptr_val++ = image_ch3[i][j];

		}

	}
	cv::Mat rezult_image;
	cv::Mat chn[3];
	chn[0] = channel1;
	chn[1] = channel2;
	chn[2] = channel3;
	cv::merge(chn,3,rezult_image);

	return rezult_image;

  }

std::string type2str(int type) {
	std::string r;

	uchar depth = type & CV_MAT_DEPTH_MASK;
	uchar chans = 1 + (type >> CV_CN_SHIFT);

	switch (depth) {
	case CV_8U:  r = "8U"; break;
	case CV_8S:  r = "8S"; break;
	case CV_16U: r = "16U"; break;
	case CV_16S: r = "16S"; break;
	case CV_32S: r = "32S"; break;
	case CV_32F: r = "32F"; break;
	case CV_64F: r = "64F"; break;
	default:     r = "User"; break;
	}

	r += "C";
	r += (chans + '0');

	return r;
}