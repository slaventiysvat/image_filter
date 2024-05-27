#include "includes.hpp"
#include <sqlite3.h>

std::string type2str(int type);
Matrix<uint8_t> copy_one_m_channel2vector(cv::Mat image, int num_of_channel);

cv::Mat split3channels2image(Matrix<uint8_t> image_ch1,
    Matrix<uint8_t> image_ch2,
    Matrix<uint8_t> image_ch3);

using namespace cv;

//inline uchar Clamp(int n)
//{
//	n = n > 255 ? 255 : n;
//	return n < 0 ? 0 : n;
//}
//
//bool AddGaussianNoise(const Mat mSrc, Mat& mDst, double Mean = 0.0, double StdDev = 10.0)
//{
//	if (mSrc.empty())
//	{
//		std::cout << "[Error]! Input Image Empty!";
//		return 0;
//	}
//
//	Mat mGaussian_noise = Mat(mSrc.size(), CV_16SC3);
//	randn(mGaussian_noise, Scalar::all(Mean), Scalar::all(StdDev));
//
//	for (int Rows = 0; Rows < mSrc.rows; Rows++)
//	{
//		for (int Cols = 0; Cols < mSrc.cols; Cols++)
//		{
//			Vec3b Source_Pixel = mSrc.at<Vec3b>(Rows, Cols);
//			Vec3b& Des_Pixel = mDst.at<Vec3b>(Rows, Cols);
//			Vec3s Noise_Pixel = mGaussian_noise.at<Vec3s>(Rows, Cols);
//
//			for (int i = 0; i < 3; i++)
//			{
//				int Dest_Pixel = Source_Pixel.val[i] + Noise_Pixel.val[i];
//				Des_Pixel.val[i] = Clamp(Dest_Pixel);
//			}
//		}
//	}
//
//	return true;
//}

bool AddGaussianNoise_Opencv(const Mat mSrc, Mat& mDst, double Mean = 0.0, double StdDev = 10.0)
{
	if (mSrc.empty())
	{
		std::cout << "[Error]! Input Image Empty!";
		return 0;
	}
	Mat mSrc_16SC;
	Mat mGaussian_noise = Mat(mSrc.size(), CV_16SC3);
	randn(mGaussian_noise, Scalar::all(Mean), Scalar::all(StdDev));

	mSrc.convertTo(mSrc_16SC, CV_16SC3);
	addWeighted(mSrc_16SC, 1.0, mGaussian_noise, 1.0, 0.0, mSrc_16SC);
	mSrc_16SC.convertTo(mDst, mSrc.type());

	return true;
}

int main(int argc, char** argv)
{

    std::string path1 = "../../../img/artifical_341_512.bmp";
    std::string path2 = "../../../img/DeltaE_8bit_gamma2.2.bmp";
	cv::Mat image_to_be_filtered, input_image_two;
	cv::Mat im_after_gauss_noise;
	cv::Mat im_after_gauss_filter;
	cv::Mat im_after_median_filter;
	cv::Mat im_after_nlm_filter;
	cv::Mat im_after_laplace_filter;

	image_to_be_filtered = cv::imread(path1);

	cv::Mat image_artifacted = image_to_be_filtered;
	 
	input_image_two = cv::imread(path2);

	//add gaussian noise to image
	image_noiser noiser_image;
	simple_image_filters image_filter;

	const float mean = 5.0;
	const float sigma = 8.0;

	//noiser_image.AddGaussianNoise_Opencv(image_to_be_filtered, im_after_gauss_noise, mean, sigma);
    AddGaussianNoise_Opencv(image_to_be_filtered, im_after_gauss_noise, mean, sigma);
	//split image on 3 channels

	//smooth image with gauss filter
    GaussianBlur(im_after_gauss_noise, im_after_gauss_noise, Size(3, 3), 0);
	//im_after_gauss_filter = split3channels2image(red_channel, green_channel, blue_channel);

	//apply median filter to image
	//median_filter median_filter_tool;
    medianBlur(im_after_gauss_noise, im_after_median_filter,5);

	////apply NLM filter to image
	//nlm_filter nlm_filter_tool;
    bilateralFilter(im_after_median_filter, im_after_nlm_filter, 1, 2, 0.5);
	//im_after_nlm_filter = split3channels2image(red_channel, green_channel, blue_channel);

	//apply laplase filter to image

	/*Matrix<float> kernel = { {1.0f,1.0f,1.0f},{1.0f,-8.0,1.0f},{1.0f,1.0f,1.0f} };*/

	//Matrix<float> kernel = { {0.0f,0.0f,1.0f,0.0f,0.0f},{0.0f,1.0f,2.0f,1.0f,0.0f},{1.0f,2.0f,-16.0f,2.0f,1.0f},{0.0f,1.0f,2.0f,1.0f,0.0f},{0.0f,0.0f,1.0f,0.0f,0.0f}};

	//getting borders from original image

	/*im_after_laplace_filter = split3channels2image(red_channel, green_channel, blue_channel);*/

	imshow("Image Task", image_to_be_filtered);
	imshow("Image Filtered", im_after_nlm_filter);

	cv::waitKey(0);

	return 0;
}


Matrix<uint8_t> copy_one_m_channel2vector(cv::Mat image_to_be_filtered, int num_of_channel) {


	cv::Mat different_Channels[3];
	split(image_to_be_filtered, different_Channels);//splitting images into 3 different channels//  
	cv::Mat need_channel = different_Channels[num_of_channel];//loading blue channels//
	//cv::Mat g = different_Channels[1];//loading green channels//
	//cv::Mat r = different_Channels[2];//loading red channels//  
	int m = image_to_be_filtered.rows;
	int n = image_to_be_filtered.cols;
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


	//split(image_to_be_filtered, different_Channels);//splitting images into 3 different channels//  
	//cv::Mat need_channel = different_Channels[num_of_channel];//loading blue channels//
	//cv::Mat g = different_Channels[1];//loading green channels//
	//cv::Mat r = different_Channels[2];//loading red channels//  
	int m = image_ch1.size();
	int n = image_ch1[0].size();
	cv::Mat channel1(m, n, CV_8U);
	cv::Mat channel2(m, n, CV_8U);
	cv::Mat channel3(m, n, CV_8U);
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
	cv::merge(chn, 3, rezult_image);

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