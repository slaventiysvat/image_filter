#include "nlm_filter.h"
#include "convolution_tools.h"
#include "image_mat_tools.h"

Matrix<uint8_t> nlm_filter::nlm_filter_2_dims(Matrix<uint8_t> input_image,
	int radius,
	int srhc_range,
	float sigma) {

	Matrix<uint8_t> image_out(input_image.size(), std::vector<uint8_t>(input_image[0].size(), 0));
	Matrix<float> image_out_tmp(input_image.size(), std::vector<float>(input_image[0].size(), 0));

	//make kernel for NLM filter
	//kernel = make_kernel(f);
	const float const_r = (float)(radius);
	float numin = 1.0f;
	Matrix<float> kernel((2 * radius) + 1, std::vector<float>((2 * radius) + 1, 0));

	for (int d = 1; d <= radius; d++) {
		int denum = ((2 * d) + 1) * ((2 * d) + 1);
		float val = numin / (float)(denum);

		for (int i = -d; i <= d; i++) {

			for (int j = -d; j <= d; j++) {

				kernel[radius - i][radius - j] = kernel[radius - i][radius - j] + val;

			}

		}

	}

	// maybe i can merge this two loops
	int size = (2 * radius) + 1;
	for (int i = 0; i < size; i++) {

		for (int j = 0; j < size; j++) {

			kernel[i][j] = kernel[i][j] / const_r;

		}

	}

	
	convolution_tools conv_tool;
	image_mat_tools mat_tool;
	Matrix<float> x1 = mat_tool.image_2_float(input_image);

	Matrix<float> x2 = mat_tool.border_replication_symmetric_float(x1, (radius + srhc_range) * 2);

	Matrix<float> squ_sum = mat_tool.img_power_2_float_in(x2);

	Matrix<float> gsqu_sum = conv_tool.convolution_2_dims_fin_fout(squ_sum, kernel);

	int wd = size;           //width of widow;
	float h = sigma * sigma; //
	int r_srcw2p1 = (radius + srhc_range) * 2 + (int)floor(kernel.size() / 2) - 1;
	int m = input_image.size();
	int n = input_image[0].size();

	const int radis_range = radius + srhc_range;
	Matrix<float> rw(kernel.size(), std::vector<float>(kernel[0].size(), 0));
	Matrix<float> bw(r_srcw2p1, std::vector<float>(r_srcw2p1, 0));
	int N = floor(kernel.size() / 2) + 1;
	int k1 = bw.size() - (N + 1);
	int k2 = bw[0].size() - (N + 1);
	Matrix<float> cv_bw(k1, std::vector<float>(k2, 0));
	Matrix<float> gsqu_sum_w(k1, std::vector<float>(k2, 0));
	Matrix<float> gsq_dis(k1, std::vector<float>(k2, 0));
	Matrix<float> weight(k1, std::vector<float>(k2, 0));
	for (int i = 0; i < m; i++) {


		for (int j = 0; j < n; j++) {

			int i1 = i + radis_range;
			int j1 = j + radis_range;
			int v = 0;
			int p = 0;
			//reference window
			for (int g = (i1 + radius); g >= (i1 - radius); g--) {

				for (int h = (j1 + radius); h >= (j1 - radius); h--) {

					rw[v][p] = x2[g][h] * kernel[v][p];
					p = p + 1;
				}
				v = v + 1;
				p = 0;
			}
			v = 0;
			p = 0;

			for (int c = (i1 - (srhc_range + radius)); c <= (i1 + (radius + srhc_range)); c++) {

				for (int s = (j1 - (srhc_range + radius)); s <= (j1 + (radius + srhc_range)); s++) {
					//big window for similarity searching
					bw[v][p] = x2[c][s];
					p = p + 1;
				}
				v = v + 1;
				p = 0;
			}

			cv_bw = conv_tool.convolution_2_dims_fin_fout_valid(bw, rw);

			v = 0;
			p = 0;
			for (int c = (i1 - srhc_range); c <= (i1 + srhc_range); c++) {

				for (int s = (j1 - srhc_range); s <= (j1 + srhc_range); s++) {

					gsq_dis[v][p] = (gsqu_sum[i1][j1] + gsqu_sum[c][s]) - (2.0f * cv_bw[v][p]);
					p = p + 1;
				}
				v = v + 1;
				p = 0;
			}

			for (int c = 0; c < weight.size(); c++) {

				for (int s = 0; s < weight[0].size(); s++) {

					weight[c][s] = exp((-gsq_dis[c][s]) / h);

				}
			}

			weight[srhc_range][srhc_range] = 0;
			float max_val_w = mat_tool.im_max_value_float(weight);
			weight[srhc_range][srhc_range] = max_val_w;

			float summ_weight = 0;
			float summ_est = 0;

			v = 0;
			p = 0;
			for (int c = (i1 - srhc_range); c <= (i1 + srhc_range); c++) {

				for (int s = (j1 - srhc_range); s <= (j1 + srhc_range); s++) {

					summ_est = summ_est + x2[c][s] * weight[v][p];
					summ_weight = summ_weight + weight[v][p];
					p = p + 1;
				}
				v = v + 1;
				p = 0;
			}

			image_out_tmp[i][j] = summ_est / summ_weight;
		}


	}

	image_out = mat_tool.im_float_cast_to_uint8(image_out_tmp);

	return image_out;

}