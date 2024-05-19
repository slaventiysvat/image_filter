#include "image_noiser.h"
#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <random>
inline int Clamp(int n)
{
    n = n > 255 ? 255 : n;
    return n < 0 ? 0 : n;
}

void image_noiser::AddGaussianNoise_Opencv(cv::Mat mSrc, cv::Mat& mDst, const double Mean, const double StdDev)
{
    cv::Mat mSrc_16SC;
    cv::Mat mGaussian_noise = cv::Mat(mSrc.size(), CV_16SC3);
    randn(mGaussian_noise, cv::Scalar::all(Mean), cv::Scalar::all(StdDev));

    mSrc.convertTo(mSrc_16SC, CV_16SC3);
    addWeighted(mSrc_16SC, 1.0, mGaussian_noise, 1.0, 0.0, mSrc_16SC);
    mSrc_16SC.convertTo(mDst, mSrc.type());
}

image_noiser::image_noiser(double Mean, double StdDev) {

    image_noiser::Mean_val = Mean;
    image_noiser::StdDev_val = StdDev;
}

void image_noiser::gaussianNoise(cv::Mat& image, const unsigned char mean, const unsigned char sigma)
{
	std::default_random_engine generator;

	std::normal_distribution<float> distribution(mean, sigma);

	int imageChannels = image.channels();

	for (int row = 0; row < image.rows; row++)
	{
		for (int column = 0; column < image.cols; column++)
		{
			for (int channel = 0; channel < imageChannels; channel++)
			{
				unsigned char* pixelValuePtr = image.ptr(row) + (column * imageChannels) + channel;

				long test = distribution(generator);

				long newPixelValue = *pixelValuePtr + distribution(generator);

				*pixelValuePtr = newPixelValue > 255 ? 255 : newPixelValue < 0 ? 0 : newPixelValue;
			}
		}
	}
}

