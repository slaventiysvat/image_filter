#ifndef IMAGE_NOISER
#define IMAGE_NOISER
#include <opencv2/core.hpp> 
class image_noiser
{

public:

	//image_noiser() = default;
	~image_noiser() {}

	image_noiser(double Mean = 0.0, double StdDev = 0.01);

	void AddGaussianNoise_Opencv(cv::Mat mSrc,
							     cv::Mat& mDst, 
								 const double Mean,
								 const double StdDev);

	void gaussianNoise(cv::Mat& image, const unsigned char mean, const unsigned char sigma);

private:
	 double Mean_val;
	 double StdDev_val;


};
#endif /*IMAGE_NOISER*/
