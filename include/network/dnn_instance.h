#ifndef DNN_INSTANCE_H
#define DNN_INSTANCE_H

#include <dlib/dnn.h>
#include <dlib/data_io.h>
#include "dlib/cuda/gpu_data.h"
#include <iostream>

#include <iterator>
#include <thread>
#include "network/structures.h"

#define DNN_1LAYERS_30CON
//#define DNN_1LAYERS_40CON

//#define DNN_2LAYERS_30CON
//#define DNN_2LAYERS_30CON_05DROPOUT
//#define DNN_2LAYERS_30CON_09DROPOUT
//#define DNN_2LAYERS_30CONT
//#define DNN_2LAYERS_30CONT_05DROPOUT
//#define DNN_2LAYERS_30CONT_09DROPOUT
//#define DNN_2LAYERS_40CON


#ifdef DNN_1LAYERS_30CON
using net_type = dlib::loss_binary_log_per_pixel <          //1
	dlib::con<1, 1, 1, 1, 1,                              //1
	dlib::relu<dlib::con<30, 5, 5, 1, 1,                    //2
	dlib::input<dlib::matrix<unsigned char>>                //0
	>>>>;                                                 //4
#endif

#ifdef DNN_1LAYERS_40CON
using net_type = dlib::loss_binary_log_per_pixel <          //1
	dlib::con<1, 1, 1, 1, 1,                              //1
	dlib::relu<dlib::con<40, 5, 5, 1, 1,                    //2
	dlib::input<dlib::matrix<unsigned char>>                //0
	>>>>;                                                 //4
#endif


#ifdef DNN_2LAYERS_30CON
using net_type = dlib::loss_binary_log_per_pixel <          //1
	dlib::con<1, 1, 1, 1, 1,                              //1
	dlib::relu<dlib::con<30, 5, 5, 1, 1,                    //2
	dlib::relu<dlib::con<30, 5, 5, 1, 1,                    //2
	dlib::input<dlib::matrix<unsigned char>>                //0
	>>>>>>;                                                 //6
#endif

#ifdef DNN_2LAYERS_40CON
using net_type = dlib::loss_binary_log_per_pixel <          //1
	dlib::con<1, 1, 1, 1, 1,                              //1
	dlib::relu<dlib::con<40, 5, 5, 1, 1,                    //2
	dlib::relu<dlib::con<40, 5, 5, 1, 1,                    //2
	dlib::input<dlib::matrix<unsigned char>>                //0
	>>>>>>;                                                 //6
#endif



#ifdef DNN_2LAYERS_30CON_05DROPOUT
using net_type = dlib::loss_binary_log_per_pixel <          //1
	dlib::con<1, 1, 1, 1, 1,                              //1
	dlib::relu<dlib::con<30, 5, 5, 1, 1, dlib::dropout<     //3
	dlib::relu<dlib::con<30, 5, 5, 1, 1, dlib::dropout<     //3
	dlib::input<dlib::matrix<unsigned char>>                //0
	>>>>>>>>;                                               //8
#endif

#ifdef DNN_2LAYERS_30CON_09DROPOUT
using net_type = dlib::loss_binary_log_per_pixel <          //1
	dlib::con<1, 1, 1, 1, 1,                              //1
	dlib::relu<dlib::con<30, 5, 5, 1, 1, dlib::dropout<     //3
	dlib::relu<dlib::con<30, 5, 5, 1, 1, dlib::dropout<     //3
	dlib::input<dlib::matrix<unsigned char>>                //0
	>>>>>>>>;                                               //8
#endif

#ifdef DNN_2LAYERS_30CONT
using net_type = dlib::loss_binary_log_per_pixel <          //1
	dlib::cont<1, 1, 1, 1, 1,                              //1
	dlib::relu<dlib::cont<30, 5, 5, 1, 1, dlib::dropout<     //3
	dlib::relu<dlib::cont<30, 5, 5, 1, 1, dlib::dropout<     //3
	dlib::input<dlib::matrix<unsigned char>>                //0
	>>>>>>>>;                                               //8
#endif

#ifdef DNN_2LAYERS_30CONT_05DROPOUT
using net_type = dlib::loss_binary_log_per_pixel <          //1
	dlib::cont<1, 1, 1, 1, 1,                              //1
	dlib::relu<dlib::cont<30, 5, 5, 1, 1, dlib::dropout<     //3
	dlib::relu<dlib::cont<30, 5, 5, 1, 1, dlib::dropout<     //3
	dlib::input<dlib::matrix<unsigned char>>                //0
	>>>>>>>>;                                               //8
#endif

#ifdef DNN_2LAYERS_30CONT_09DROPOUT
using net_type = dlib::loss_binary_log_per_pixel <          //1
	dlib::cont<1, 1, 1, 1, 1,                              //1
	dlib::relu<dlib::cont<30, 5, 5, 1, 1, dlib::dropout<     //3
	dlib::relu<dlib::cont<30, 5, 5, 1, 1, dlib::dropout<     //3
	dlib::input<dlib::matrix<unsigned char>>                //0
	>>>>>>>>;                                               //8
#endif


// A single training sample for segmentation. A mini-batch comprises many of these.
struct seg_training_sample
{
	dlib::matrix<unsigned char> input_image;
	dlib::matrix<float> label_image; // The ground-truth label of each pixel. (+1 or -1)
};
// ----------------------------------------------------------------------------------------

#endif // DNN_INSTANCE_H
