#include "median_filter.h"
#include <algorithm>

Matrix<uint8_t> median_filter::median_filter_2_dims(Matrix<uint8_t> input_image,
	int kernel_size)
{

	median_filter median_filter_tools;
	//kernel of median filter must be odd
	//kernel size must be bigger than 3
	//[m n] = size(input_image);
	int N = kernel_size - (int)ceil((float)(kernel_size) / 2.0f);
	int m = input_image.size();
	int n = input_image[0].size();
	Matrix<uint8_t> output_image(m, std::vector<uint8_t>(n, 0));
	Matrix<uint8_t> output_array((m + (2 * N)), std::vector<uint8_t>((n + (2 * N)), 0));
	m = input_image.size();
	n = input_image[0].size();
	int k = 0;
	int l = 0;
	//prepearing image before filtrations
	for (int i = N; i < m + N; i++) {

		for (int j = N; j < n + N; j++) {

			output_array[i][j] = input_image[k][l];
			l = l + 1;
		}

		k = k + 1;
		l = 0;
	}

	//median filter process
	k = 0;
	l = 0;

	for (int i = N; i < (m + N); i++) {

		for (int j = N; j < (n + N); j++) {
			//copy pixel after filtrations to rezult array
			std::vector<uint8_t> array_med = median_filter_tools.fill_median_array(output_array, i, j, kernel_size);
			output_image[k][l] = median_filter_tools.get_median_1_dims(array_med);
			l = l + 1;
		}
		k = k + 1;
		l = 0;
	}

	return output_image;
}

int median_filter::border_size_estimate(int kernel_size) {

	int val = 0;
	return val = kernel_size - (int)ceil(float(kernel_size) / 2.0f);

}

uint8_t median_filter::nlogn_median(std::vector<uint8_t> kernel_mat) {

	std::sort(kernel_mat.begin(), kernel_mat.end());
	int N = kernel_mat.size();
	int med_val = 0;
	int indx1 = 0;
	int indx2 = 0;
	if ((N % 2) == 1) {
		indx1 = (int)ceil((float)N / 2.0f) - 1;
		med_val = kernel_mat[indx1];
	}
	else {
		indx2 = (int)(ceil((float)N / 2.0f) - 1.0f) - 1;//!!!!! 
		med_val = (kernel_mat[indx2] + kernel_mat[indx1]) >> 1; // med_val = 0.5 * (l(ceil(N/2) - 1) + l(ceil(N / 2)));
	}

	med_val = (med_val > 255) ? 255 : med_val;
	return (uint8_t)med_val;
}

uint8_t median_filter::get_median_1_dims(std::vector<uint8_t> kernel_mat) {
	// need to optimize using pivot median
	return median_filter::nlogn_median(kernel_mat);

}

std::vector<uint8_t> median_filter::fill_median_array(Matrix<uint8_t> input_mat, int i, int j, int kernel_size) {

	// i, j - current indexes of array_in
	// kernel_size - size of median filter kernel
	int m = kernel_size;
	int n = kernel_size;
	std::vector<uint8_t> output_array(m * n, 0);
	int k = 0;
	int start_step_y = (i - (kernel_size / 2));
	int start_step_x = (j - (kernel_size / 2));
	int end_row = start_step_y + kernel_size - 1;
	int end_col = start_step_x + kernel_size - 1;
	for (int i_ind = start_step_y; i_ind <= end_row; ++i_ind) {

		for (int j_ind = start_step_x; j_ind <= end_col; ++j_ind) {

			output_array[k] = input_mat[i_ind][j_ind];
			k = k + 1;
		}

	}
	return output_array;
}
