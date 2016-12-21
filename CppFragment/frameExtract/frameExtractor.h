#pragma once
#include<string>
#include<iostream>
#include <opencv2/opencv.hpp>

using namespace std;

class frameExtractor
{

public:
	enum ROI{
		All = 0,

		Center = -1,

		Left = 1,
		Right = 2,
		Top = 3,
		Bottom = 4,

		TopLeft = 5,
		BottomLeft = 6,
		TopRight = 7,
		BottomRight = 8
	};

private:
	//input
	std::string videoPath_;

	//output
	std::string outputPrefix_;
	std::string outputPath_;

	cv::VideoCapture capture_;
	
	int num_skip_;
	
	// ROI of frame
	frameExtractor::ROI roi;
	float ROIPercent_;

public:
	frameExtractor();

	frameExtractor(std::string path_, std::string prefix_);

	frameExtractor(std::string path_);
	
	~frameExtractor();

	void setPrefix(std::string prefix_);

	void setOutputPath(std::string outPath_);

	void setSkipFrame(int num);
	
	void setROI(frameExtractor::ROI roi_, float percent_);

	cv::Mat getROI(cv::Mat& before);

	void loadVideo(std::string path_);

	void extract();
};