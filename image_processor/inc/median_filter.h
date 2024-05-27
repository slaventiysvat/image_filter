#ifndef MEDIAN_FILTER
#define MEDIAN_FILTER
#include <vector>
#include "standard_lib_includer.h"
class median_filter
{

   public:
	   median_filter() {}
	   ~median_filter() {}
	   Matrix<uint8_t> median_filter_2_dims(Matrix<uint8_t> input_image,
		   int kernel_size);

	   uint8_t get_median_1_dims(std::vector<uint8_t> kernel_mat);
	   uint8_t nlogn_median(std::vector<uint8_t> kernel_mat);

	   std::vector<uint8_t> fill_median_array(Matrix<uint8_t> kernel_mat, int i, int j, int kernel_size);
	   int border_size_estimate(int kernel_size);

};
#endif /*MEDIAN_FILTER*/
