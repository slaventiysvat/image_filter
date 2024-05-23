#ifndef GAUSS_FILTER
#define GAUSS_FILTER
#include "standard_lib_includer.h"
class gauss_filter
{
public:

	Matrix<uint8_t> gauss_filter_2_dims(Matrix<uint8_t> input_image,
		float SIGMA);
	Matrix<float> gauss_kernel_creator(float sigma);

};
#endif /*GAUSS_FILTER*/
