#ifndef STREAM_MANAGER
#define STREAM_MANAGER
#include <vector>
#include "standard_lib_includer.h"
class stream_manager
{

public:
	
	stream_manager() {}

	~stream_manager() {}
	
	void print_matrix(Matrix<uint8_t>arr, int m, int n);
	void print_vector(std::vector<uint8_t> arr, int m);

	void print_matrix_csg(Matrix<int8_t>arr, int m, int n);
	void print_vector_csg(std::vector<int8_t> arr, int m);

	void print_matrix_int(Matrix<int>arr, int m, int n);
	void print_vector_int(std::vector<int> arr, int m);

	void print_matrix_float(Matrix<float>arr, int m, int n);
	void print_vector_float(std::vector<float> arr, int m);

};

#endif /*STREAM_MANAGER*/