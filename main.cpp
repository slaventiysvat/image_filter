#include "includes.hpp"
#include <sqlite3.h>

std::string type2str(int type);
Matrix<uint8_t> copy_one_m_channel2vector(cv::Mat image, int num_of_channel);

cv::Mat split3channels2image(Matrix<uint8_t> image_ch1,
    Matrix<uint8_t> image_ch2,
    Matrix<uint8_t> image_ch3);

using namespace cv;

const char* window_name = "Pyramids Demo";

// main function!
int main(int argc, char** argv)
{
    std::string path1 = "../../../img/artifical_341_512.bmp";
    std::string path2 = "../../../img/DeltaE_8bit_gamma2.2.bmp";
    cv::Mat blue_channe_one, input_image_two;
    cv::Mat im_after_gauss_noise;
    cv::Mat im_after_gauss_filter;
    cv::Mat im_after_median_filter;
    cv::Mat im_after_nlm_filter;
    cv::Mat im_after_laplace_filter;

    blue_channe_one = cv::imread(path1);
    input_image_two = cv::imread(path2);
    int wight = blue_channe_one.size().width;
    int hight = blue_channe_one.size().height;

    //need optimize now this code can works only with small images
    cv::resize(blue_channe_one, blue_channe_one, cv::Size(wight, hight));
    cv::resize(input_image_two, input_image_two, cv::Size(wight, hight));

    //add gaussian noise to image
    image_noiser noiser_image;
    simple_image_filters image_filter;

    const float mean = 5.0;
    const float sigma = 8.0;

    noiser_image.AddGaussianNoise_Opencv(blue_channe_one, im_after_gauss_noise, mean, sigma);

    ////split image on 3 channels
    //Matrix<uint8_t> red_channel = copy_one_m_channel2vector(im_after_gauss_noise, 0);
    //Matrix<uint8_t> green_channel = copy_one_m_channel2vector(im_after_gauss_noise, 1);
    //Matrix<uint8_t> blue_channel = copy_one_m_channel2vector(im_after_gauss_noise, 2);

    cv::waitKey(0);
    //fmt::print("Hello, world!\n");
    //printf("%s\n", sqlite3_libversion());
    //std::cout << "Hello World" << std::endl;
    //std::cout << "\n Zoom In-Out demo \n "
    //    "------------------ \n"
    //    " * [i] -> Zoom in \n"
    //    " * [o] -> Zoom out \n"
    //    " * [ESC] -> Close program \n" << std::endl;

    ////const char* filename = argc >= 2 ? argv[1] : "../img/vscode_cmakepresets_selection.png";
    ////const char* filename[] = { "../img/vscode_cmakepresets_selection.png" };
    //std::string filename = { "../../../img/artifical_341_512.bmp" };
    //// Loads an image
    //Mat src = imread(samples::findFile(filename));

    //// Check if image is loaded fine
    //if (src.empty()) {
    //    printf(" Error opening image\n");
    //    printf(" Program Arguments: [image_name -- default ../../../img/artifical_341_512.bmp] \n");
    //    return EXIT_FAILURE;
    //}

    //for (int i = 0; i < 2; i++)
    //{
    //    imshow(window_name, src);
    //    char c = (char)waitKey(0);

    //    if (c == 27)
    //    {
    //        break;
    //    }
    //    else if (c == 'i')
    //    {
    //        pyrUp(src, src, Size(src.cols * 2, src.rows * 2));
    //        printf("** Zoom In: Image x 2 \n");
    //    }
    //    else if (c == 'o')
    //    {
    //        pyrDown(src, src, Size(src.cols / 2, src.rows / 2));
    //        printf("** Zoom Out: Image / 2 \n");
    //    }
    //}

    //return EXIT_SUCCESS;
}