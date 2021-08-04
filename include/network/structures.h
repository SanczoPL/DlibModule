#ifndef STRUCTURES_PREPROCESSING_MODULES_H
#define STRUCTURES_PREPROCESSING_MODULES_H

#include <iostream>
#include <stdio.h>

#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QtCore>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/opencv.hpp>

#include <dlib/dnn.h>
#include <dlib/data_io.h>

#include "includespdlog.h"


struct geneticInfo
{
    QString name;
    qint32 min;
    qint32 max;
    bool onlyEven;
    bool onlyOdd;
    qint32 isDouble;
    QString isString;
    bool isBool;
};

struct geneticBit
{
    qint32 bytes;
};


// The object detection network.
// Adapted from dnn_mmod_train_find_cars_ex.cpp and friends.

template <long num_filters, typename SUBNET> using con5d = dlib::con<num_filters, 5, 5, 2, 2, SUBNET>;
template <long num_filters, typename SUBNET> using con5 = dlib::con<num_filters, 5, 5, 1, 1, SUBNET>;

template <typename SUBNET> using bdownsampler = dlib::relu<dlib::bn_con<con5d<128, dlib::relu<dlib::bn_con<con5d<128, dlib::relu<dlib::bn_con<con5d<32, SUBNET>>>>>>>>>;
template <typename SUBNET> using adownsampler = dlib::relu<dlib::affine<con5d<128, dlib::relu<dlib::affine<con5d<128, dlib::relu<dlib::affine<con5d<32, SUBNET>>>>>>>>>;

template <typename SUBNET> using brcon5 = dlib::relu<dlib::bn_con<con5<256, SUBNET>>>;
template <typename SUBNET> using arcon5 = dlib::relu<dlib::affine<con5<256, SUBNET>>>;

using det_bnet_type = dlib::loss_mmod<dlib::con<1, 9, 9, 1, 1, brcon5<brcon5<brcon5<bdownsampler<dlib::input_rgb_image_pyramid<dlib::pyramid_down<6>>>>>>>>;
using det_anet_type = dlib::loss_mmod<dlib::con<1, 9, 9, 1, 1, arcon5<arcon5<arcon5<adownsampler<dlib::input_rgb_image_pyramid<dlib::pyramid_down<6>>>>>>>>;



#endif // STRUCTURES_PREPROCESSING_MODULES_H
