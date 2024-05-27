#ifndef N_L_MEANS_FILTER
#define N_L_MEANS_FILTER
#include "standard_lib_includer.h"
class nlm_filter
{

  public:

	  nlm_filter() {}
	  ~nlm_filter() {}

	  Matrix<uint8_t> nlm_filter_2_dims(Matrix<uint8_t> input_image,
		  int radius,
		  int srhc_range,
		  float sigma);

};

#endif /*N_L_MEANS_FILTER*/