#include "stream_manager.h"
#include <iostream>
#include <vector>
#include "standard_lib_includer.h"

void stream_manager::print_matrix(Matrix<uint8_t> arr, int m, int n)
{
	for (int i = 0; i < m; i++) {

		std::vector<uint8_t> arr_s = arr[i];
		print_vector(arr_s, n);
		std::cout << "\n" << std::endl;

	}
}

void  stream_manager::print_vector(std::vector<uint8_t> arr, int m) {

	for (int i = 0; i < m; i++) {

		std::cout << (int)(arr[i]) << " ";
	}

	std::cout << "\n" << std::endl;

}
//Need Use Templates in future
void stream_manager::print_matrix_csg(Matrix<int8_t>arr, int m, int n) {

	for (int i = 0; i < m; i++) {

		std::vector<int8_t> arr_s = arr[i];
		print_vector_csg(arr_s, n);
		std::cout << "\n" << std::endl;

	}

}

void stream_manager::print_vector_csg(std::vector<int8_t> arr, int m) {

	for (int i = 0; i < m; i++) {

		std::cout << (int)(arr[i]) << " ";
	}

	std::cout << "\n" << std::endl;
}

//Need Use Templates in future
void stream_manager::print_matrix_int(Matrix<int>arr, int m, int n) {

	for (int i = 0; i < m; i++) {

		std::vector<int> arr_s = arr[i];
		print_vector_int(arr_s, n);
		std::cout << "\n" << std::endl;

	}

}

void stream_manager::print_vector_int(std::vector<int> arr, int m) {

	for (int i = 0; i < m; i++) {

		std::cout << arr[i] << " ";
	}

	std::cout << "\n" << std::endl;
}


//Need Use Templates in future
void stream_manager::print_matrix_float(Matrix<float>arr, int m, int n) {

	for (int i = 0; i < m; i++) {
		std::vector<float> arr_s = arr[i];
		print_vector_float(arr_s, n);
		std::cout << "\n" << std::endl;

	}
	std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;

}

void stream_manager::print_vector_float(std::vector<float> arr, int m) {

	for (int i = 0; i < m; i++) {

		std::cout << arr[i] << " ";
	}

	std::cout << "\n" << std::endl;
}
