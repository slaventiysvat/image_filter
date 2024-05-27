#ifndef IMAGE_PLOTTER
#define IMAGE_PLOTTER
#include <opencv2/core.hpp> // Basic OpenCV structures (cv::Mat, Scalar)
class image_plotter
{

	public:

	image_plotter() {}
	~image_plotter() {}

	void print_both_images(cv::Mat input_image,
			cv::Mat image_out);


};

#endif /*IMAGE_PLOTTER*/