#ifndef FILTER_PROCESSOR
#define FILTERS_PROCESSOR
#include "standard_lib_includer.h"
class filtersmy
{
	protected:
		bool image_was_filtered = false;
	private:
	
	public:

	filtersmy() {}
	~filtersmy() {}

	Matrix<uint8_t> simple_filter_2_dims(Matrix<uint8_t> input_image,
		Matrix<float> window);

	Matrix<float> simple_filter_2_dims_float(Matrix<float> input_image,
		Matrix<float> window);
};

class image_improve_filtercv {

	protected:
		bool image_was_filtered = false;
	private:
	
	public:
		image_improve_filtercv() {}
		~image_improve_filtercv() {}

};



#endif /*FILTERS_PROCESSOR*/