#ifndef FILTER_PROCESSOR
#define FILTERS_PROCESSOR
#include "standard_lib_includer.h"
class filters
{

public:
	Matrix<uint8_t> simple_filter_2_dims(Matrix<uint8_t> input_image,
		Matrix<float> window);

	Matrix<float> simple_filter_2_dims_float(Matrix<float> input_image,
		Matrix<float> window);

};

#endif /*FILTERS_PROCESSOR*/