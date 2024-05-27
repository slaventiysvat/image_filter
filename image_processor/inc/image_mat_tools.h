#ifndef IMAGE_MATH_TOOLS
#define IMAGE_MATH_TOOLS
#include <vector>
#include "standard_lib_includer.h"
class image_mat_tools
{


  public:

	  image_mat_tools() {}
	  ~image_mat_tools() {}

	  Matrix<uint8_t> border_replication_circular(Matrix<uint8_t> input_array, int kernel_size);

	  Matrix<float> border_replication_symmetric_float(Matrix<float> input_array, int kernel_size);

	  Matrix<float> img_power_2_float(Matrix<uint8_t> input);

	  Matrix<float> img_power_2_float_in(Matrix<float> input);

	  Matrix<float> rotate_90_clockwise_float(Matrix<float> input);
	  Matrix<float> rotate_90_float(Matrix<float> input);

	  Matrix<int8_t> rotate_90_clockwise(Matrix<int8_t> input);
	  Matrix<int8_t> rotate_90(Matrix<int8_t> input);

	  int im_max_value(Matrix<int> input);
	  float im_max_value_float(Matrix<float> input);

	  Matrix<float> im_normalize(Matrix<int> input, int max);
	  Matrix<float> im_normalize_float(Matrix<float> input, float max);

	  Matrix<uint8_t> im_int_cast_to_uint8(Matrix<int> input);

	  Matrix<int> im_Abs(Matrix<int> input);

	  Matrix<float> im_Abs_float(Matrix<float> input);

	  Matrix<float> image_2_float(Matrix<uint8_t> input_image);

	  Matrix<float> image_2_single(Matrix<uint8_t> input_image);

	  Matrix<uint8_t> fimage_2_uint8(Matrix<float> input_image);

	  Matrix<uint8_t> im_float_cast_to_uint8(Matrix<float> input);

	  Matrix<uint8_t> image_substract(Matrix<uint8_t> input_image_1,
		  Matrix<uint8_t> input_image_2);


};
#endif /*IMAGE_MATH_TOOLS*/
