#ifndef IMAGE_ESTIMATOR
#define IMAGE_ESTIMATOR
#include <opencv2/core.hpp>     // Basic OpenCV structures (cv::Mat, Scalar)
class image_estimator
{

public:

	image_estimator() {}
	~image_estimator() {}
	// ![get-psnr]
	double getPSNR(const cv::Mat& I1, const cv::Mat& I2);
	cv::Scalar getMSSIM(const cv::Mat& i1, const cv::Mat& i2);

};

#endif/*IMAGE_ESTIMATOR*/