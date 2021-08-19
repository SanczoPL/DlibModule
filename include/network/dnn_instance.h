#ifndef DNN_INSTANCE_H
#define DNN_INSTANCE_H

#include <dlib/dnn.h>
#include <dlib/data_io.h>
#include "dlib/cuda/gpu_data.h"
#include <iostream>

#include <iterator>
#include <thread>
#include "network/structures.h"

//#define STANDARD_NET
#define STANDARD_NET_DROPOUT_05
//#define STANDARD_NET_DROPOUT_09

using net_type_not_used = dlib::loss_binary_log_per_pixel <          //1
	dlib::cont < 1, 1, 1, 1, 1,                             //1
	dlib::relu<dlib::con<50, 5, 5, 1, 1,dlib::dropout<      //3
	dlib::relu<dlib::con<100, 5, 5, 1, 1,dlib::dropout<      //3
	dlib::relu<dlib::con<150, 5, 5, 1, 1,dlib::dropout<      //3
	dlib::relu<dlib::con<100, 5, 5, 1, 1,dlib::dropout<      //2
	dlib::relu<dlib::con<50, 5, 5, 1, 1,dlib::dropout<      //3
	dlib::input<dlib::matrix<unsigned char>>                //0
	>>>>>>>>>>>>>>>>>;                                      //11

#ifdef STANDARD_NET
using net_type = dlib::loss_binary_log_per_pixel <          //1
	dlib::con < 1, 1, 1, 1, 1,                              //1
	dlib::relu<dlib::con<20, 5, 5, 1, 1,                    //2
	dlib::input<dlib::matrix<unsigned char>>                //0
	>>>>;                                                 //4
#endif

#ifdef STANDARD_NET_DROPOUT_05
using net_type = dlib::loss_binary_log_per_pixel <          //1
	dlib::con < 1, 1, 1, 1, 1,                              //1
	dlib::relu<dlib::con<20, 5, 5, 1, 1, dlib::dropout<     //3
	dlib::input<dlib::matrix<unsigned char>>                //0
	>>>>>;                                               //5
#endif

#ifdef STANDARD_NET_DROPOUT_09
using net_type = dlib::loss_binary_log_per_pixel <          //1
	dlib::con < 1, 1, 1, 1, 1,                              //1
	dlib::relu<dlib::con<20, 5, 5, 1, 1, dlib::dropout<     //3
	dlib::input<dlib::matrix<unsigned char>>                //0
	>>>>>;                                               //5
#endif

// A single training sample for segmentation. A mini-batch comprises many of these.
struct seg_training_sample
{
	dlib::matrix<unsigned char> input_image;
	dlib::matrix<float> label_image; // The ground-truth label of each pixel. (+1 or -1)
};
// ----------------------------------------------------------------------------------------

#endif // DNN_INSTANCE_H
