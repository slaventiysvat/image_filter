#include "gauss_filter.h"
#include "convolution_tools.h"
Matrix<uint8_t> gauss_filter::gauss_filter_2_dims(Matrix<uint8_t> input_image,
	float SIGMA) {

	Matrix<uint8_t> image_out(input_image.size(), std::vector<uint8_t>(input_image[0].size(), 0));
	gauss_filter gauss_filter_tools;

	Matrix<float> kernel = gauss_filter_tools.gauss_kernel_creator(SIGMA);
	convolution_tools conv_tools;

	image_out = conv_tools.convolution_2_dims_float(input_image, kernel);

	return image_out;
}


Matrix<float> gauss_filter::gauss_kernel_creator(float sigma) {

	//works only for square kernel
	int kernel_size = 2 * ceil(2 * sigma) + 1;
	int filter_radius_x = (kernel_size - 1) / 2;
	int filter_radius_y = filter_radius_x;
	Matrix<float> kernel(kernel_size, std::vector<float>(kernel_size, 0));

	int k_x = (float)(-filter_radius_x);
	int k_y = (float)(-filter_radius_y);
	float max = 0;
	float eps = 2.2204e-16;
	for (int i = 0; i < kernel_size; i++) {

		float val = 0;
		for (int j = 0; j < kernel_size; j++) {
			//emulating meshgrid
			//2 - D Gaussian kernel
			val = ((k_x * k_x) / (sigma * sigma)) + ((k_y * k_y) / (sigma * sigma));
			val = (-val) / 2.0f;
			kernel[i][j] = exp(val);
			if (kernel[i][j] > max) {
				max = kernel[i][j];
			}
			k_x = k_x + 1.0f;
		}
		k_y = k_y + 1.0f;
		k_x = -filter_radius_x;
	}


	//Suppress near - zero components
	for (int i = 0; i < kernel_size; i++) {

		for (int j = 0; j < kernel_size; j++) {

			if (kernel[i][j] < (max * eps)) { kernel[i][j] = 0; }

		}

	}
	//compute summ of all elements
	float summ = 0;
	for (int i = 0; i < kernel_size; i++) {

		for (int j = 0; j < kernel_size; j++) {

			summ = summ + kernel[i][j];

		}

	}
	//Normalize
	if (summ != 0) {

		for (int i = 0; i < kernel_size; i++) {

			for (int j = 0; j < kernel_size; j++) {

				kernel[i][j] = kernel[i][j] / summ;

			}

		}

	}
	return kernel;
}