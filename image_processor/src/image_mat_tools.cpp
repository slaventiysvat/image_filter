#include "image_mat_tools.h"
#include <algorithm>
#include <cmath>
#include "standard_lib_includer.h"
Matrix<float> image_mat_tools::image_2_single(Matrix<uint8_t> input_image) {

	Matrix<float> image_out(input_image.size(), std::vector<float>(input_image[0].size(), 0));

	int m = input_image.size();
	int n = input_image[0].size();

	for (int i = 0; i < m; i++) {

		for (int j = 0; j < n; j++) {

			image_out[i][j] = (float)(input_image[i][j]);


		}

	}

	return image_out;

}



Matrix<uint8_t> image_mat_tools::image_substract(Matrix<uint8_t> input_image_1,
	Matrix<uint8_t> input_image_2) {


	int m = input_image_1.size();
	int n = input_image_1[0].size();
	image_mat_tools normalize_methods;
	Matrix<float> input_image_1_f = normalize_methods.image_2_float(input_image_1);
	Matrix<float> input_image_2_f = normalize_methods.image_2_float(input_image_2);
	Matrix<float> Image_tmp_f(m, std::vector<float>(n, 0));
	for (int i = 0; i < m; i++) {

		for (int j = 0; j < n; j++) {

			Image_tmp_f[i][j] = input_image_1_f[i][j] - input_image_2_f[i][j];

		}

	}

	Matrix<uint8_t>image_out = normalize_methods.im_float_cast_to_uint8(Image_tmp_f);
	return image_out;
}

Matrix<uint8_t> image_mat_tools::border_replication_circular(Matrix<uint8_t> input_array, int kernel_size) {
	//works only for matrix where array biger than kernel
	//kernel of median filter must be odd
	//kernel size must be bigger than 3
	//[m n] = size(input_array);
	int m = input_array.size();
	int n = input_array[0].size();
	int N = kernel_size - (int)ceil((float)(kernel_size) / 2.0f);
	Matrix<uint8_t> output_array((m + (2 * N)), std::vector<uint8_t>((n + (2 * N)), 0));
	int k = 0;
	int l = 0;
	for (int i = N; i < m + N; i++) {

		for (int j = N; j < m + N; j++) {

			output_array[i][j] = input_array[k][l];
			l = l + 1;
		}
		k = k + 1;
		l = 0;
	}
	m = output_array.size();
	n = output_array[0].size();
	k = 0;
	l = 0;
	// copy up border of image 'circular'
	k = k + N - 1;
	for (int i = N - 2; i < (2 * (N - 1)); i++) {

		for (int j = N; j < (n - N); j++) {

			output_array[i][j] = input_array[k][l];
			l = l + 1;
		}
		k = k - 1;
		l = 0;
	}

	//copy down border of image 'circular'
	int M = input_array.size();
	int L = input_array[0].size();
	k = M - (N - 2) - 1;
	l = 0;
	for (int i = m - N; i < m; i++) {

		for (int j = N; j < (n - N); j++) {

			output_array[i][j] = input_array[k][l];
			l = l + 1;
		}
		k = k - 1;
		l = 0;
	}
	k = N;
	int indx_i = m - N - 1;
	int indx_j = n - N;
	int indx_j_tale = n - N - 1;
	int d = N - 1;
	for (int i = 0; i < m; i++) {

		for (int j = 0; j < N; j++) {

			output_array[i][indx_j] = output_array[i][indx_j_tale - j];
			output_array[i][d] = output_array[i][k];
			indx_j = indx_j + 1;
			k = k + 1;
			d = d - 1;
		}
		d = N - 1;
		indx_j = n - N;
		k = N;
		l = 0;
	}
	return output_array;
}

Matrix<float> image_mat_tools::border_replication_symmetric_float(Matrix<float> input_array, int kernel_size) {
	//works only for matrix where array biger than kernel
	//kernel of median filter must be odd
	//kernel size must be bigger than 3
	//[m n] = size(input_array);
	int m = input_array.size();
	int n = input_array[0].size();
	int N = kernel_size - (int)ceil((float)(kernel_size) / 2.0f);
	Matrix<float> output_array((m + (2 * N)), std::vector<float>((n + (2 * N)), 0));
	int k = 0;
	int l = 0;
	for (int i = N; i < m + N; i++) {

		for (int j = N; j < n + N; j++) {

			output_array[i][j] = input_array[k][l];
			l = l + 1;
		}
		k = k + 1;
		l = 0;
	}

	m = output_array.size();
	n = output_array[0].size();
	k = 0;
	l = 0;
	// copy up border of image 'symmetric'
	for (int i = N - 1; i >= 0; i--) {

		for (int j = N; j < (n - N); j++) {

			output_array[i][j] = input_array[k][l];
			l = l + 1;
		}
		k = k + 1;
		l = 0;
	}

	//copy down border of image 'circular'
	int M = input_array.size();
	int L = input_array[0].size();
	//k = M - (N - 2) - 1;
	k = input_array.size() - 1;
	l = 0;
	for (int i = m - N; i < m; i++) {

		for (int j = N; j < (n - N); j++) {

			output_array[i][j] = input_array[k][l];
			l = l + 1;
		}
		k = k - 1;
		l = 0;
	}
	//computing left sideand right side  of image
	k = N;
	int indx_i = m - N - 1;
	int indx_j = n - N;
	int indx_j_tale = n - N - 1;
	int d = N - 1;
	for (int i = 0; i < m; i++) {

		for (int j = 0; j < N; j++) {

			output_array[i][indx_j] = output_array[i][indx_j_tale - j];
			output_array[i][d] = output_array[i][k];
			indx_j = indx_j + 1;
			k = k + 1;
			d = d - 1;
		}
		d = N - 1;
		indx_j = n - N;
		k = N;
		l = 0;
	}
	return output_array;

}

// Function to rotate the matrix 90 degree clockwise
Matrix<int8_t> image_mat_tools::rotate_90_clockwise(Matrix<int8_t> input)
{
	int m = input.size();
	int n = input.size();
	Matrix<int8_t> h(m, std::vector<int8_t>(n, 0));//cfreating square matrix
	// Traverse each cycle
	int N = m;
	for (int i = 0; i < N / 2; i++) {
		for (int j = i; j < N - i - 1; j++) {

			// Swap elements of each cycle
			// in clockwise direction
			int temp = input[i][j];
			input[i][j] = input[N - 1 - j][i];
			input[N - 1 - j][i] = input[N - 1 - i][N - 1 - j];
			input[N - 1 - i][N - 1 - j] = input[j][N - 1 - i];
			input[j][N - 1 - i] = temp;
		}
	}
	return h = input;
}

// Function to rotate the matrix 90 degree clockwise
Matrix<float> image_mat_tools::rotate_90_clockwise_float(Matrix<float> input)
{
	int m = input.size();
	int n = input.size();
	Matrix<float> h(m, std::vector<float>(n, 0));//cfreating square matrix
	// Traverse each cycle
	int N = m;
	for (int i = 0; i < N / 2; i++) {
		for (int j = i; j < N - i - 1; j++) {

			// Swap elements of each cycle
			// in clockwise direction
			float temp = input[i][j];
			input[i][j] = input[N - 1 - j][i];
			input[N - 1 - j][i] = input[N - 1 - i][N - 1 - j];
			input[N - 1 - i][N - 1 - j] = input[j][N - 1 - i];
			input[j][N - 1 - i] = temp;
		}
	}
	return h = input;
}

Matrix<int8_t> image_mat_tools::rotate_90(Matrix<int8_t> input) {

	int m = input.size();
	int n = input.size();
	image_mat_tools rotator;
	Matrix<int8_t> h(m, std::vector<int8_t>(n, 0));//cfreating square matrix

	h = rotator.rotate_90_clockwise(input);
	h = rotator.rotate_90_clockwise(h);
	h = rotator.rotate_90_clockwise(h);

	return h;
}

Matrix<float> image_mat_tools::rotate_90_float(Matrix<float> input) {

	int m = input.size();
	int n = input.size();
	image_mat_tools rotator;
	Matrix<float> h(m, std::vector<float>(n, 0));//cfreating square matrix

	h = rotator.rotate_90_clockwise_float(input);
	h = rotator.rotate_90_clockwise_float(h);
	h = rotator.rotate_90_clockwise_float(h);

	return h;
}

Matrix<float> image_mat_tools::img_power_2_float(Matrix<uint8_t> input) {

	int m = input.size();
	int n = input[0].size();

	Matrix<float> output_image(m, std::vector<float>(n, 0));

	for (int i = 0; i < m; i++) {

		for (int j = 0; j < n; j++) {

			output_image[i][j] = (float)(input[i][j]) * (float)(input[i][j]);

		}

	}
	return output_image;
}


Matrix<float> image_mat_tools::img_power_2_float_in(Matrix<float> input) {

	int m = input.size();
	int n = input[0].size();

	Matrix<float> output_image(m, std::vector<float>(n, 0));

	for (int i = 0; i < m; i++) {

		for (int j = 0; j < n; j++) {

			output_image[i][j] = input[i][j] * input[i][j];

		}

	}

	return output_image;
}


int image_mat_tools::im_max_value(Matrix<int> input) {
	//means that will returning absolute max value from matrix
	int result = 0;
	//taking module of matrix
	Matrix<int> tmp = input;
	for (int iX = 0; iX < input.size(); ++iX) {
		int val = *std::max_element(input[iX].begin(), input[iX].end());
		result = std::max(result, val);
	}
	return result;
}


float image_mat_tools::im_max_value_float(Matrix<float> input) {

	//means that will returning absolute max value from matrix
	float result = 0;
	//taking module of matrix
	Matrix<float> tmp = input;
	int m = input.size();
	for (int iX = 0; iX < m; ++iX) {
		float val = *std::max_element(input[iX].begin(), input[iX].end());
		result = std::fmax(result, val);
	}
	return result;

}


Matrix<int> image_mat_tools::im_Abs(Matrix<int> input) {

	//means that will returning absolute max value from matrix
	int result = 0;
	//taking module of matrix
	Matrix<int> tmp = input;
	for (int i = 0; i < input.size(); ++i) {

		for (int j = 0; j < input.size(); ++j) {

			tmp[i][j] = (input[i][j] > 0) ? input[i][j] : abs(input[i][j]);

		}

	}
	return tmp;
}


Matrix<float> image_mat_tools::im_Abs_float(Matrix<float> input) {

	//means that will returning absolute max value from matrix
	int result = 0;
	//taking module of matrix
	Matrix<float> tmp = input;
	int m = input.size();
	int n = input[0].size();

	for (int i = 0; i < m; ++i) {

		for (int j = 0; j < n; ++j) {

			tmp[i][j] = (input[i][j] > 0) ? input[i][j] : fabs(input[i][j]);

		}

	}

	return tmp;

}


Matrix<float> image_mat_tools::im_normalize(Matrix<int> input, int max) {

	Matrix<float> norm_arr(input.size(), std::vector<float>(input[0].size(), 0));

	for (int i = 0; i < input.size(); i++) {

		for (int j = 0; j < input[0].size(); j++) {
			//copy pixel after filtrations to rezult array
			norm_arr[i][j] = (float)input[i][j] / (float)max;

		}
	}

	return norm_arr;
}


Matrix<float> image_mat_tools::im_normalize_float(Matrix<float> input, float max) {

	Matrix<float> norm_arr(input.size(), std::vector<float>(input[0].size(), 0));

	for (int i = 0; i < input.size(); i++) {

		for (int j = 0; j < input[0].size(); j++) {
			//copy pixel after filtrations to rezult array
			norm_arr[i][j] = (float)input[i][j] / (float)max;

		}
	}

	return norm_arr;
}

Matrix<uint8_t> image_mat_tools::im_int_cast_to_uint8(Matrix<int> input) {

	Matrix<uint8_t> casted_arr(input.size(), std::vector<uint8_t>(input[0].size(), 0));

	image_mat_tools mat_handler;

	Matrix<int> abs_mat = mat_handler.im_Abs(input);

	int max_val = mat_handler.im_max_value(abs_mat);

	Matrix<float> norm_arr = mat_handler.im_normalize(abs_mat, max_val);

	for (int i = 0; i < input.size(); i++) {

		for (int j = 0; j < input[0].size(); j++) {
			//copy pixel after filtrations to rezult array
			casted_arr[i][j] = (uint8_t)(round(norm_arr[i][j] * 255.0f));

		}
	}

	return casted_arr;
}


Matrix<uint8_t> image_mat_tools::im_float_cast_to_uint8(Matrix<float> input) {


	Matrix<uint8_t> casted_arr(input.size(), std::vector<uint8_t>(input[0].size(), 0));

	image_mat_tools mat_handler;

	Matrix<float> abs_mat = mat_handler.im_Abs_float(input);

	float max_val = mat_handler.im_max_value_float(abs_mat);

	Matrix<float> norm_arr = mat_handler.im_normalize_float(abs_mat, max_val);

	for (int i = 0; i < input.size(); i++) {

		for (int j = 0; j < input[0].size(); j++) {
			//copy pixel after filtrations to rezult array
			casted_arr[i][j] = (uint8_t)(round(norm_arr[i][j] * 255.0f));

		}
	}

	return casted_arr;

}

Matrix<float> image_mat_tools::image_2_float(Matrix<uint8_t> input_image) {


	Matrix<float> image_out(input_image.size(), std::vector<float>(input_image[0].size(), 0));

	int m = input_image.size();
	int n = input_image[0].size();

	for (int i = 0; i < m; i++) {

		for (int j = 0; j < n; j++) {

			image_out[i][j] = (float)(input_image[i][j]) / 255.0f;

		}

	}
	return image_out;
}

Matrix<uint8_t> image_mat_tools::fimage_2_uint8(Matrix<float> input_image) {


	Matrix<uint8_t> image_out(input_image.size(), std::vector<uint8_t>(input_image[0].size(), 0));


	return image_out;

}