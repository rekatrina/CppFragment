#include "frameExtractor.h"
#include <opencv2/opencv.hpp>
#include <iostream>

frameExtractor::frameExtractor() :frameExtractor("")
{
}

frameExtractor::frameExtractor(std::string path_) : frameExtractor(path_, "result")
{

}

frameExtractor::frameExtractor(std::string path_, std::string perfix)
{

	videoPath_ = path_;
	outputPrefix_ = perfix;
	outputPath_ = ".";
	num_skip_ = 0;
	roi = frameExtractor::All;
	ROIPercent_ = 1;

}

frameExtractor::~frameExtractor()
{

}

void frameExtractor::loadVideo(std::string path_ = "")
{
	if (path_ != "")
		videoPath_ = path_;
}

void frameExtractor::extract()
{
	if (videoPath_ == "")
		cout << "no video file has been set"<<endl;

	capture_.open(videoPath_);
	if (!capture_.isOpened())
	{
		cout << "can not open video file: " << videoPath_ << endl;
		return;
	}
	
	
	cv::Mat frame;
	int iFrame = 0;
	char name[100];
	while (capture_.read(frame))
	{
		
		//cv::imshow("video", frame);
		//cv::waitKey(30);

		if (iFrame % (num_skip_+1) == 0)
		{
			sprintf_s(name, 100, "%s\\%s_%04d.png", outputPath_, outputPrefix_, iFrame);
			cout << name << endl;
			//cout << frame.cols << endl;
			//cout << frame.rows << endl;

			try{
				cv::imwrite(name, getROI(frame));
			}
			catch (runtime_error e){
				cerr << "Exception when writing " << name << " : "
					<< e.what() << endl;
			}
		}

		iFrame++;

	}

	capture_.release();
	return;
}

void frameExtractor::setSkipFrame(int num)
{
	num_skip_ = num;
}

void frameExtractor::setPrefix(std::string prefix_)
{
	outputPrefix_ = prefix_;
}

void frameExtractor::setOutputPath(std::string outPath_)
{
	outputPath_ = outPath_;
}

void frameExtractor::setROI(ROI roi_, float percent_)
{
	roi = roi_;
	ROIPercent_ = percent_;
}

cv::Mat frameExtractor::getROI(cv::Mat &before)
{
	int w = before.cols;
	int h = before.rows;

	cv::Mat after;

	switch (roi)
	{
	case frameExtractor::All:
		after = before;
		break;

	case frameExtractor::Center:{
		cv::Rect rect(w * (1 - ROIPercent_) / 2 - 1, h * (1 - ROIPercent_) / 2 - 1, w * ROIPercent_, h * ROIPercent_);
		cout << "("	<< w * (1 - ROIPercent_) / 2 - 1 << "," 
			<< h * (1 - ROIPercent_) / 2 - 1 << ")" << endl;
		cout << w*ROIPercent_ << "x" << h*ROIPercent_ << endl;
		after = before(rect).clone();
		break;
	}
	case frameExtractor::Left:{
		cv::Rect rect(0, 0, w * ROIPercent_, h);
		after = before(rect).clone();
		break;
	}
	case frameExtractor::Right:{
		cv::Rect rect(w * (1 - ROIPercent_) - 1, 0, w, h * ROIPercent_);
		after = before(rect);
		break;
	}
	case frameExtractor::Top:{
		cv::Rect rect(0, 0, w, h * ROIPercent_);
		after = before(rect);
		break;
	}


	case frameExtractor::Bottom:{
		cv::Rect rect(0, h * (1 - ROIPercent_) - 1, w, h * ROIPercent_);
		after = before(rect);
		break;
	}

	case frameExtractor::BottomLeft:
		break;

	case frameExtractor::BottomRight:
		break;

	case frameExtractor::TopLeft:
		break;

	case frameExtractor::TopRight:
		break;

	}

	return after;
}

