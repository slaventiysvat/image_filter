#include "convolution_tools.h"
#include "image_mat_tools.h"

Matrix<uint8_t> convolution_tools::convolution_2_dims(Matrix<uint8_t> input_image,
	Matrix<int8_t> kernel) {

	//A = border_replication_circular(input_array, kernel);
	int kernel_size = kernel.size();
	//A = border_replication_zerros(input_array, kernel_size);
	//kernel of median filter must be odd
	//kernel size must be bigger than 3
	//[m n] = size(input_image);
	int N = kernel_size - (int)ceil((float)(kernel_size) / 2.0f);
	int m = input_image.size();
	int n = input_image[0].size();
	Matrix<uint8_t> output_image(m, std::vector<uint8_t>(n, 0));
	Matrix<uint8_t> Rep((m + (2 * N)), std::vector<uint8_t>((n + (2 * N)), 0));
	m = input_image.size();
	n = input_image[0].size();
	int k = 0;
	int l = 0;
	//prepearing image before filtrations
	for (int i = N; i < m + N; i++) {

		for (int j = N; j < n + N; j++) {

			Rep[i][j] = input_image[k][l];
			l = l + 1;
		}

		k = k + 1;
		l = 0;
	}

	int r = input_image.size();
	int c = input_image[0].size();
	m = kernel.size();
	n = kernel.size();
	image_mat_tools rotator;
	//only for square matrix
	Matrix<int8_t> h = rotator.rotate_90(kernel);//creating square matrix

	int center1 = floor((m + 1) / 2);
	int center2 = floor((n + 1) / 2);
	int left = center2 - 1;
	int right = n - center2;
	int top = center1 - 1;
	int bottom = m - center1;

	Matrix<int> B(r, std::vector<int>(c, 0));	//B = zeros(r, c);
	//convolution loop
	for (int x = 0; x < r; x++) {
		for (int y = 0; y < c; y++) {
			for (int i = 0; i < m; i++) {
				for (int j = 0; j < n; j++) {
					/*  int q = x - 1;
					  int w = y - 1;*/
					int q = x;
					int w = y;
					B[x][y] = B[x][y] + (((int)Rep[i + q][j + w]) * (int)(h[i][j]));

				}
			}
		}
	}


	image_mat_tools converter;
	output_image = converter.im_int_cast_to_uint8(B);
	return output_image;
}


Matrix<float>  convolution_tools::convolution_2_dims_fin_fout_valid(Matrix<float> input_image,
	Matrix<float> kernel) {


	//A = border_replication_circular(input_array, kernel);
	int kernel_size = kernel.size();
	//A = border_replication_zerros(input_array, kernel_size);
	//kernel of median filter must be odd
	//kernel size must be bigger than 3
	//[m n] = size(input_image);
	int N = kernel_size - (int)ceil((float)(kernel_size) / 2.0f);
	int m = input_image.size();
	int n = input_image[0].size();
	Matrix<float> Rep((m + (2 * N)), std::vector<float>((n + (2 * N)), 0.0f));
	m = input_image.size();
	n = input_image[0].size();
	int k = 0;
	int l = 0;
	//prepearing image before filtrations
	for (int i = N; i < m + N; i++) {

		for (int j = N; j < n + N; j++) {

			Rep[i][j] = input_image[k][l];
			l = l + 1;
		}

		k = k + 1;
		l = 0;
	}

	int r = input_image.size();
	int c = input_image[0].size();
	m = kernel.size();
	n = kernel.size();
	//h = rot90(k, 2);
	image_mat_tools rotator;
	//only for square matrix
	Matrix<float> h = rotator.rotate_90_float(kernel);//creating square matrix
	int center1 = floor((m + 1) / 2);
	int center2 = floor((n + 1) / 2);
	int left = center2 - 1;
	int right = n - center2;
	int top = center1 - 1;
	int bottom = m - center1;

	Matrix<float> B(r, std::vector<float>(c, 0.0f));	//B = zeros(r, c);
	//convolution loop
	for (int x = 0; x < r; x++) {
		for (int y = 0; y < c; y++) {
			float B_tmp = 0;
			for (int i = 0; i < m; i++) {
				for (int j = 0; j < n; j++) {
					int q = x;
					int w = y;
					B_tmp = B_tmp + (Rep[i + q][j + w] * h[i][j]);

				}
			}
			B[x][y] = B_tmp;
		}
	}
	int k1 = r - (N + 1) - 1;
	int k2 = c - (N + 1) - 1;

	Matrix<float> output_image(k1, std::vector<float>(k2, 0));
	int i = 0;
	int j = 0;
	for (int x = N; x < (k1 + 2); x++) {
		for (int y = N; y < (k2 + 2); y++) {
			output_image[i][j] = B[x][y];
			j = j + 1;
		}
		i = i + 1;
		j = 0;
	}

	return output_image;

}


Matrix<uint8_t>  convolution_tools::convolution_2_dims_float(Matrix<uint8_t> input_image,
	Matrix<float> kernel) {

	//A = border_replication_circular(input_array, kernel);
	int kernel_size = kernel.size();
	//A = border_replication_zerros(input_array, kernel_size);
	//kernel of median filter must be odd
	//kernel size must be bigger than 3
	//[m n] = size(input_image);
	int N = kernel_size - (int)ceil((float)(kernel_size) / 2.0f);
	int m = input_image.size();
	int n = input_image[0].size();
	Matrix<uint8_t> output_image(m, std::vector<uint8_t>(n, 0));
	Matrix<float> Rep((m + (2 * N)), std::vector<float>((n + (2 * N)), 0.0f));
	m = input_image.size();
	n = input_image[0].size();
	int k = 0;
	int l = 0;
	image_mat_tools mat_tols;
	Matrix<float> input_imagef = mat_tols.image_2_float(input_image);
	//prepearing image before filtrations
	for (int i = N; i < m + N; i++) {

		for (int j = N; j < n + N; j++) {

			Rep[i][j] = input_imagef[k][l];
			l = l + 1;
		}

		k = k + 1;
		l = 0;
	}

	int r = input_image.size();
	int c = input_image[0].size();
	m = kernel.size();
	n = kernel.size();
	//h = rot90(k, 2);
	//only for square matrix
	Matrix<float> h = mat_tols.rotate_90_float(kernel);//creating square matrix

	int center1 = floor((m + 1) / 2);
	int center2 = floor((n + 1) / 2);
	int left = center2 - 1;
	int right = n - center2;
	int top = center1 - 1;
	int bottom = m - center1;

	Matrix<float> B(r, std::vector<float>(c, 0.0f));	//B = zeros(r, c);
	//convolution loop
	for (int x = 0; x < r; x++) {
		for (int y = 0; y < c; y++) {
			for (int i = 0; i < m; i++) {
				for (int j = 0; j < n; j++) {
					/*  int q = x - 1;
					  int w = y - 1;*/
					int q = x;
					int w = y;
					float test = B[x][y] + (((float)Rep[i + q][j + w]) * (float)(h[i][j]));
					B[x][y] = B[x][y] + (((float)Rep[i + q][j + w]) * (float)(h[i][j]));

				}
			}
		}
	}

	output_image = mat_tols.im_float_cast_to_uint8(B);
	return output_image;
}


Matrix<float>  convolution_tools::convolution_2_dims_fin_fout(Matrix<float> input_image,
	Matrix<float> kernel) {

	//A = border_replication_circular(input_array, kernel);
	int kernel_size = kernel.size();
	//A = border_replication_zerros(input_array, kernel_size);
	//kernel of median filter must be odd
	//kernel size must be bigger than 3
	//[m n] = size(input_image);
	int N = kernel_size - (int)ceil((float)(kernel_size) / 2.0f);
	int m = input_image.size();
	int n = input_image[0].size();
	Matrix<float> output_image(m, std::vector<float>(n, 0));
	Matrix<float> Rep((m + (2 * N)), std::vector<float>((n + (2 * N)), 0.0f));
	m = input_image.size();
	n = input_image[0].size();
	int k = 0;
	int l = 0;
	//prepearing image before filtrations
	for (int i = N; i < m + N; i++) {

		for (int j = N; j < n + N; j++) {

			Rep[i][j] = input_image[k][l];
			l = l + 1;
		}

		k = k + 1;
		l = 0;
	}

	int r = input_image.size();
	int c = input_image[0].size();
	m = kernel.size();
	n = kernel.size();
	//h = rot90(k, 2);
	image_mat_tools rotator;
	//only for square matrix
	Matrix<float> h = rotator.rotate_90_float(kernel);//creating square matrix

	int center1 = floor((m + 1) / 2);
	int center2 = floor((n + 1) / 2);
	int left = center2 - 1;
	int right = n - center2;
	int top = center1 - 1;
	int bottom = m - center1;

	Matrix<float> B(r, std::vector<float>(c, 0.0f));	//B = zeros(r, c);
	//convolution loop
	for (int x = 0; x < r; x++) {
		for (int y = 0; y < c; y++) {
			for (int i = 0; i < m; i++) {
				for (int j = 0; j < n; j++) {
					/*  int q = x - 1;
					  int w = y - 1;*/
					int q = x;
					int w = y;
					B[x][y] = B[x][y] + (Rep[i + q][j + w] * h[i][j]);

				}
			}
		}
	}
	output_image = B;
	return output_image;

}
