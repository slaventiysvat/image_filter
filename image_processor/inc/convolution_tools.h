#ifndef CONVOLUTION_TOOLS
#define CONVOLUTION_TOOLS
#include "standard_lib_includer.h"
class convolution_tools
{


public:

	convolution_tools() {}
	~convolution_tools() {}

	Matrix<uint8_t> convolution_2_dims(Matrix<uint8_t> input_imageput, Matrix<uint8_t> kernel_window);

	Matrix<uint8_t> convolution_2_dims(Matrix<uint8_t> input_image,
		Matrix<int8_t> window);

	Matrix<uint8_t> convolution_2_dims_float(Matrix<uint8_t> input_image,
		Matrix<float> window);

	Matrix<float> convolution_2_dims_fin_fout(Matrix<float> input_image,
		Matrix<float> window);

	Matrix<float> convolution_2_dims_fin_fout_valid(Matrix<float> input_image,
		Matrix<float> window);


};

#endif /*CONVOLUTION_TOOLS*/