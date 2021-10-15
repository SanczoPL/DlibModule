#ifndef DNN_INSTANCE_H
#define DNN_INSTANCE_H

#include <dlib/dnn.h>
#include <dlib/data_io.h>
#include "dlib/cuda/gpu_data.h"
#include <iostream>

#include <iterator>
#include <thread>
#include "network/structures.h"

//#define DNN_1LAYERS_20CON
//#define DNN_1LAYERS_20CON
//#define DNN_1LAYERS_40CON
//#define DNN_1LAYERS_60CON

//21
//#define DNN_2LAYERS_20CON
//22
//#define DNN_2LAYERS_20CON_MULTIPLY05
//23
//#define DNN_2LAYERS_20CON_MULTIPLY09
//24
//#define DNN_2LAYERS_40CON
//25
//#define DNN_2LAYERS_40CON_MULTIPLY05
//26
//#define DNN_2LAYERS_40CON_MULTIPLY09


//27
//#define DNN_2LAYERS_60CON
#define DNN_2LAYERS_120CON
//28
//#define DNN_2LAYERS_60CON_MULTIPLY05
//29
//#define DNN_2LAYERS_60CON_MULTIPLY09
//30
//#define DNN_2LAYERS_60CON_DROPOUT05
//31
//#define DNN_2LAYERS_60CON_DROPOUT09






//#define DNN_3LAYERS_20CON
//#define DNN_3LAYERS_40CON
//#define DNN_3LAYERS_60CON

//#define DNN_1LAYERS_20CON_05DROPOUT


#ifdef DNN_1LAYERS_20CON
using net_type = dlib::loss_binary_log_per_pixel <          //1
	dlib::con<1, 1, 1, 1, 1,                              //1
	dlib::relu<dlib::con<20, 5, 5, 1, 1,                    //2
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

#ifdef DNN_1LAYERS_60CON
using net_type = dlib::loss_binary_log_per_pixel <          //1
	dlib::con<1, 1, 1, 1, 1,                              //1
	dlib::relu<dlib::con<60, 5, 5, 1, 1,                    //2
	dlib::input<dlib::matrix<unsigned char>>                //0
	>>>>;                                                 //4
#endif


//21
#ifdef DNN_2LAYERS_20CON
using net_type = dlib::loss_binary_log_per_pixel <          //1
	dlib::con<1, 1, 1, 1, 1,                              //1
	dlib::relu<dlib::con<20, 5, 5, 1, 1,                    //2
	dlib::relu<dlib::con<20, 5, 5, 1, 1,                    //2
	dlib::input<dlib::matrix<unsigned char>>                //0
	>>>>>>;                                                 //6
#endif
//22
#ifdef DNN_2LAYERS_20CON_MULTIPLY05
using net_type = dlib::loss_binary_log_per_pixel <          //1
	dlib::con<1, 1, 1, 1, 1,                              //1
	dlib::relu<dlib::con<20, 5, 5, 1, 1,dlib::multiply<     //3 
	dlib::relu<dlib::con<20, 5, 5, 1, 1,dlib::multiply<     //3 
	dlib::input<dlib::matrix<unsigned char>>                //0
	>>>>>>>>;                                                 //8
#endif
//23
#ifdef DNN_2LAYERS_20CON_MULTIPLY09
using net_type = dlib::loss_binary_log_per_pixel <          //1
	dlib::con<1, 1, 1, 1, 1,                              //1
	dlib::relu<dlib::con<20, 5, 5, 1, 1,dlib::multiply<     //3 
	dlib::relu<dlib::con<20, 5, 5, 1, 1,dlib::multiply<     //3 
	dlib::input<dlib::matrix<unsigned char>>                //0
	>>>>>>>>;                                                 //8
#endif

#ifdef DNN_2LAYERS_40CON
using net_type = dlib::loss_binary_log_per_pixel <          //1
	dlib::con<1, 1, 1, 1, 1,                              //1
	dlib::relu<dlib::con<40, 5, 5, 1, 1,                    //2
	dlib::relu<dlib::con<40, 5, 5, 1, 1,                    //2
	dlib::input<dlib::matrix<unsigned char>>                //0
	>>>>>>;                                                 //6
#endif

#ifdef DNN_2LAYERS_60CON
using net_type = dlib::loss_binary_log_per_pixel <          //1
	dlib::con<1, 1, 1, 1, 1,                              //1
	dlib::relu<dlib::con<60, 5, 5, 1, 1,                    //2
	dlib::relu<dlib::con<60, 5, 5, 1, 1,                    //2
	dlib::input<dlib::matrix<unsigned char>>                //0
	>>>>>>;                                                 //6
#endif

#ifdef DNN_2LAYERS_120CON
using net_type = dlib::loss_binary_log_per_pixel <          //1
	dlib::con<1, 1, 1, 1, 1,                              //1
	dlib::relu<dlib::con<120, 5, 5, 1, 1,                    //2
	dlib::relu<dlib::con<120, 5, 5, 1, 1,                    //2
	dlib::input<dlib::matrix<unsigned char>>                //0
	>>>>>>;                                                 //6
#endif

#ifdef DNN_2LAYERS_60CON_MULTIPLY05
using net_type = dlib::loss_binary_log_per_pixel <          //1
	dlib::con<1, 1, 1, 1, 1,                              //1
	dlib::relu<dlib::con<60, 5, 5, 1, 1,dlib::multiply<     //3 
	dlib::relu<dlib::con<60, 5, 5, 1, 1,dlib::multiply<     //3 
	dlib::input<dlib::matrix<unsigned char>>                //0
	>>>>>>>>;                                                 //8
#endif

#ifdef DNN_2LAYERS_60CON_MULTIPLY09
using net_type = dlib::loss_binary_log_per_pixel <          //1
	dlib::con<1, 1, 1, 1, 1,                              //1
	dlib::relu<dlib::con<60, 5, 5, 1, 1,dlib::multiply<     //3 
	dlib::relu<dlib::con<60, 5, 5, 1, 1,dlib::multiply<     //3 
	dlib::input<dlib::matrix<unsigned char>>                //0
	>>>>>>>>;                                                 //6
#endif

#ifdef DNN_2LAYERS_60CON_DROPOUT05
using net_type = dlib::loss_binary_log_per_pixel <          //1
	dlib::con<1, 1, 1, 1, 1,                              //1
	dlib::relu<dlib::con<60, 5, 5, 1, 1,dlib::dropout<     //3 
	dlib::relu<dlib::con<60, 5, 5, 1, 1,dlib::dropout<     //3 
	dlib::input<dlib::matrix<unsigned char>>                //0
	>>>>>>>>;                                                 //8
#endif

#ifdef DNN_2LAYERS_60CON_DROPOUT09
using net_type = dlib::loss_binary_log_per_pixel <          //1
	dlib::con<1, 1, 1, 1, 1,                              //1
	dlib::relu<dlib::con<60, 5, 5, 1, 1,dlib::dropout<     //3 
	dlib::relu<dlib::con<60, 5, 5, 1, 1,dlib::dropout<     //3 
	dlib::input<dlib::matrix<unsigned char>>                //0
	>>>>>>>>;                                                 //6
#endif



#ifdef DNN_3LAYERS_20CON
using net_type = dlib::loss_binary_log_per_pixel <          //1
	dlib::con<1, 1, 1, 1, 1,                              //1
	dlib::relu<dlib::con<20, 5, 5, 1, 1,                    //2
	dlib::relu<dlib::con<20, 5, 5, 1, 1,                    //2
	dlib::relu<dlib::con<20, 5, 5, 1, 1,                    //2
	dlib::input<dlib::matrix<unsigned char>>                //0
	>>>>>>>>;                                                 //8
#endif

#ifdef DNN_3LAYERS_40CON
using net_type = dlib::loss_binary_log_per_pixel <          //1
	dlib::con<1, 1, 1, 1, 1,                              //1
	dlib::relu<dlib::con<40, 5, 5, 1, 1,                    //2
	dlib::relu<dlib::con<40, 5, 5, 1, 1,                    //2
	dlib::relu<dlib::con<40, 5, 5, 1, 1,                    //2
	dlib::input<dlib::matrix<unsigned char>>                //0
	>>>>>>;                                                 //8
#endif

#ifdef DNN_3LAYERS_60CON
using net_type = dlib::loss_binary_log_per_pixel <          //1
	dlib::con<1, 1, 1, 1, 1,                              //1
	dlib::relu<dlib::con<60, 5, 5, 1, 1,                    //2
	dlib::relu<dlib::con<60, 5, 5, 1, 1,                    //2
	dlib::relu<dlib::con<60, 5, 5, 1, 1,                    //2
	dlib::input<dlib::matrix<unsigned char>>                //0
	>>>>>>;                                                 //8
#endif

#ifdef DNN_1LAYERS_20CON_05DROPOUT
using net_type = dlib::loss_binary_log_per_pixel <          //1
	dlib::con<1, 1, 1, 1, 1,                              //1
	dlib::relu<dlib::con<20, 5, 5, 1, 1, dlib::multiply<     //3
	dlib::input<dlib::matrix<unsigned char>>                //0
	>>>>>;                                               //5

using net_type2 = dlib::loss_binary_log_per_pixel <          //1
	dlib::con<1, 1, 1, 1, 1,                              //1
	dlib::relu<dlib::con<20, 5, 5, 1, 1, dlib::multiply<     //3
	dlib::input<dlib::matrix<unsigned char>>                //0
	>>>>>;                                               //5
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



// A single training sample for segmentation. A mini-batch comprises many of these.
struct seg_training_sample
{
	dlib::matrix<unsigned char> input_image;
	dlib::matrix<float> label_image; // The ground-truth label of each pixel. (+1 or -1)
};
// ----------------------------------------------------------------------------------------

#endif // DNN_INSTANCE_H
