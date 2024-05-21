#include "filters.h"
#include "convolution_tools.h"
Matrix<uint8_t> filters::simple_filter_2_dims(Matrix<uint8_t> input_image,
	Matrix<float> window) {

	Matrix<uint8_t> image_out(input_image.size(), std::vector<uint8_t>(input_image[0].size(), 0));

	convolution_tools filter_my;

	image_out = filter_my.convolution_2_dims_float(input_image, window);

	return image_out;
}

Matrix<float> simple_filter_2_dims_float(Matrix<float> input_image,
	Matrix<float> window) {

	Matrix<float> output_array;

	return output_array;
}