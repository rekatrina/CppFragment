#include<iostream>
#include <vector>
#include <list>
#include <string>

#include "routeTracker.h"



#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include<opencv2/stitching/detail/matchers.hpp>


using namespace std;

int main(int argc, char** argv)
{
	vector<string> imageList;
	
	int iStart = 591;
	int iEnd = 710;
	char *format = "D:\\data\\infr\\tif_35\\pic_%04d.png";

	char buff[100];
	for (int ind = iStart; ind <= iEnd; ind++){
		sprintf_s(buff, 100, format, ind);
		//cout << buff << endl;
		imageList.push_back(buff);
	}
	int nImg = imageList.size();
	cout << "#images: " << nImg << endl;

	cv::Ptr<cv::detail::FeaturesFinder> featFinder;
	featFinder = new cv::detail::SurfFeaturesFinder();
	vector<cv::detail::ImageFeatures> features(nImg);

	cout << "------ feature extraction ------" << endl;
	for (int i = 0; i < nImg; i++){
		cv::Mat img = cv::imread(imageList[i]);
		(*featFinder)(img, features[i]);
		features[i].img_idx = i;
		cout << "\timage" << i + 1 << ":  " << features[i].keypoints.size() << endl;
	}
	featFinder->collectGarbage();
	
	cout << "------ pairwise matching ------" << endl;
	cv::detail::BestOf2NearestMatcher matcher(false);
	vector<cv::Mat> homo(nImg - 1);

	for (int i = 0; i < nImg - 1; i++){
		cv::detail::MatchesInfo matchInfo;
		matchInfo.src_img_idx = i;
		matchInfo.dst_img_idx = i + 1;
		matcher(features[1], features[2], matchInfo);
		homo[i] = matchInfo.H;
		cout << matchInfo.src_img_idx << "->" << matchInfo.dst_img_idx << 
			"("<< matchInfo.confidence<<")"<<endl;
		cout << matchInfo.H << endl;
	}


	return 1;
}

//
//
//#include <iostream>
//#include <vector>
//#include <opencv2/core/core.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/features2d/features2d.hpp>
//#include <opencv2/calib3d/calib3d.hpp>
//#include <opencv2/nonfree/nonfree.hpp>
//#include <opencv2/nonfree/features2d.hpp>
//#include<opencv2\legacy\legacy.hpp> 
//#include <math.h>
//#include <opencv/cv.h>
//
//using namespace cv;
//using namespace std;
//#define PI 3.1415926535898
//
//
//
//
///************************************************************************
//If you have your Homography, you can calculate the camera pose with something like this:
//************************************************************************/
//
//void cameraPoseFromHomography(Mat&H, Mat&pose)
//{
//
//	Mat p1 = H.col(0);       // Pointer to first column of H
//	Mat p2;    // Pointer to first column of pose (empty)
//
//	cv::normalize(p1, p2); // Normalize the rotation, and copies the column to pose
//
//	//cout<<p2<<endl;
//	p2.copyTo(pose.col(0));
//	//cout<< pose.col(0)<<endl;
//	Mat   p3 = H.col(1);           // Pointer to second column of H
//	Mat  p4;        // Pointer to second column of pose (empty)
//
//	cv::normalize(p3, p4);   // Normalize the rotation and copies the column to pose
//	p4.copyTo(pose.col(1));
//
//	Mat    p5 = pose.col(0);
//	Mat   p6 = pose.col(1);
//	//cout<<p5<<endl;
//	//cout<<p6<<endl;
//	Mat p7 = p5.cross(p6); // Computes the cross-product of p1 and p2
//	// Third column is the crossproduct of columns one and two
//
//	Mat  p8;
//	cv::normalize(p7, p8);
//	p8.copyTo(pose.col(2));
//
//	// pose.col(3) = H.col(2) / tnorm;  //vector t [R|t] is the last column of pose
//
//
//}
//void PrintMat(CvMat *A)
//{
//	int i, j;
//	//printf("/nMatrix=:");
//	for (i = 0; i<A->rows; i++)
//	{
//		printf("\n");
//		switch (CV_MAT_DEPTH(A->type))
//		{
//		case CV_32F:
//		case CV_64F:
//			for (j = 0; j<A->cols; j++)
//				printf("%9.4f", (float)cvGetReal2D(A, i, j));
//			break;
//		case CV_8U:
//		case CV_16U:
//			for (j = 0; j<A->cols; j++)
//				printf("%6d", (int)cvGetReal2D(A, i, j));
//			break;
//		default:
//			break;
//		}
//	}
//	printf("\n");
//
//}
//
//
//
//int main()
//{
//
//	Mat img_1 = imread("E:\\75448161surf-and-Homography-decomposition (1)\\Image0001.bmp", CV_LOAD_IMAGE_GRAYSCALE);
//	Mat img_2 = imread("E:\\75448161surf-and-Homography-decomposition (1)\\Image001.bmp", CV_LOAD_IMAGE_GRAYSCALE);
//	/*cv::resize(img_1, img_1, cv::Size(), 0.5, 0.5);
//	cv::resize(img_2, img_2, cv::Size(), 0.5, 0.5);
//	*/
//	/* cv::Mat img1= cv::imread("Image000.bmp",CV_LOAD_IMAGE_GRAYSCALE);
//	cv::Mat img2= cv::imread("Image001.bmp",CV_LOAD_IMAGE_GRAYSCALE);
//
//	cv::Mat img_1, img_2;
//	cv::pyrDown(img1, img_1);
//	cv::pyrDown(img2, img_2);
//	*/
//	//-- Step 1: Detect the keypoints using SURF Detector
//
//	int minHessian = 400;
//	SurfFeatureDetector detector(minHessian);
//
//	//SiftFeatureDetector detector(0.06);
//	double t = (double)getTickCount();
//	std::vector<KeyPoint> keypoints_1, keypoints_2;
//
//	detector.detect(img_1, keypoints_1);
//	detector.detect(img_2, keypoints_2);
//
//	//-- Step 2: Calculate descriptors (feature vectors)
//	SurfDescriptorExtractor extractor;
//	// SiftDescriptorExtractor extractor;
//	Mat descriptors_1, descriptors_2;
//
//	extractor.compute(img_1, keypoints_1, descriptors_1);
//	extractor.compute(img_2, keypoints_2, descriptors_2);
//	t = ((double)getTickCount() - t) / getTickFrequency();
//	cout << " detection time [s]: " << t / 1.0 << endl;
//	//-- Step 3: Matching descriptor vectors using FLANN matcher
//	//第三步利用FlannBasedMatcher类进行特征匹配，并只保留好的特征匹配点，
//	FlannBasedMatcher matcher;
//	std::vector<vector<DMatch > > matches;
//	matcher.knnMatch(descriptors_1, descriptors_2, matches, 2);
//	std::vector< DMatch > good_matches;
//	for (int i = 0; i < min(descriptors_1.rows - 1, (int)matches.size()); i++) //THIS LOOP IS SENSITIVE TO SEGFAULTS
//	{
//		if ((matches[i][0].distance < 0.6*(matches[i][1].distance)) && ((int)matches[i].size() <= 2 && (int)matches[i].size()>0))
//		{
//			good_matches.push_back(matches[i][0]);
//		}
//	}
//	/************************************************************************
//	根据std::vector< DMatch > good_matches中distance的大小进行排序
//	***********************************************************************/
//	std::cout << "Number of matched points : " << good_matches.size() << std::endl;
//
//
//	int N = int(good_matches.size()*0.8);
//	//int N=10;
//	std::nth_element(good_matches.begin(),    // initial position
//		good_matches.begin() + (N - 1), // position of the sorted element
//		good_matches.end());     // end position
//	// remove all elements after the 25th
//	good_matches.erase(good_matches.begin() + N, good_matches.end());
//
//	std::cout << "Number of matched points (after erase): " << good_matches.size() << std::endl;
//
//	std::vector<Point2f> obj;
//	std::vector<Point2f> scene;
//
//	for (int i = 0; i < good_matches.size(); i++)
//	{
//		//-- Get the keypoints from the good matches
//		obj.push_back(keypoints_1[good_matches[i].queryIdx].pt);
//		scene.push_back(keypoints_2[good_matches[i].trainIdx].pt);
//	}
//
//	vector<uchar> flags(obj.size(), 0);
//	cv::Mat H = cv::findHomography(
//		cv::Mat(obj), cv::Mat(scene), // corresponding points
//		flags,	// outputed inliers matches 
//		CV_RANSAC// RANSAC method
//		, 1);	    // max distance to reprojection point
//	vector< DMatch > inliers;
//	for (int i = 0; i < good_matches.size(); i++)
//	{
//		if (flags[i])
//		{
//			inliers.push_back(good_matches[i]);
//		}
//	}
//	std::cout << "Number of matched points (inliers): " << inliers.size() << std::endl;
//	Mat img_matches;
//	drawMatches(img_1, keypoints_1, img_2, keypoints_2,
//		inliers, img_matches, Scalar::all(-1), Scalar::all(-1),
//		vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
//
//
//	CvMat K1, K2, H2, H1;
//
//
//	double a[] = { 1479.737, 0, 771.874,
//		0, 1474.563, 529.227,
//		0, 0, 1
//	};//good
//
//
//	/*double a[]={739.85,0,385.94,
//	0,737.28,264.6,
//	0,0,1
//	};//good
//	*/
//	double  b[9], c[9];
//	cvInitMatHeader(&K1, 3, 3, CV_64FC1, a, CV_AUTOSTEP);
//	cvInitMatHeader(&K2, 3, 3, CV_64FC1, b, CV_AUTOSTEP);
//	cvInitMatHeader(&H2, 3, 3, CV_64FC1, c, CV_AUTOSTEP);
//	cvInitMatHeader(&H1, 3, 3, CV_64FC1, c, CV_AUTOSTEP);
//	cvInvert(&K1, &K2, CV_SVD);
//	//cvInvert(&K1,&K2,CV_LU);
//	//cvInvert(&K1,&K2);
//
//	H1 = H;
//
//	cvMatMul(&K2, &H1, &H2);
//
//
//	Mat H3 = cvCreateMat(3, 3, CV_64FC1);
//
//	H3 = Mat::Mat(&H2, true);
//	Mat pose = cvCreateMat(3, 3, CV_64FC1);
//	cameraPoseFromHomography(H3, pose);
//
//	CvMat* dst;
//	CvMat* po;
//	po = cvCreateMat(3, 3, CV_64FC1);
//
//	CvMat tem = pose;
//	po = &tem;
//	dst = cvCreateMat(1, 3, CV_64FC1);
//	cvRodrigues2(po, dst, 0);
//	float rx1 = cvmGet(dst, 0, 0);
//	float ry1 = cvmGet(dst, 0, 1);
//	float rz1 = cvmGet(dst, 0, 2);
//	float Rx = rx1 * 180 / PI;
//	float Ry = ry1 * 180 / PI;
//	float Rz = rz1 * 180 / PI;
//	printf("俯仰角为：%f\n", Rx);
//	printf("旋转角为：%f\n", Ry);
//	printf("滚动角为：%f\n", Rz);
//
//
//
//
//
//	//-- Get the corners from the image_1 ( the object to be "detected" )
//	Point2f obj_corners[4] = { cvPoint(0, 0), cvPoint(img_1.cols, 0), cvPoint(img_1.cols, img_1.rows), cvPoint(0, img_1.rows) };
//	Point scene_corners[4];
//
//	//-- Map these corners in the scene ( image_2)
//	for (int i = 0; i < 4; i++)
//	{
//		double x = obj_corners[i].x;
//		double y = obj_corners[i].y;
//
//		double Z = 1. / (H.at<double>(2, 0)*x + H.at<double>(2, 1)*y + H.at<double>(2, 2));
//		double X = (H.at<double>(0, 0)*x + H.at<double>(0, 1)*y + H.at<double>(0, 2))*Z;
//		double Y = (H.at<double>(1, 0)*x + H.at<double>(1, 1)*y + H.at<double>(1, 2))*Z;
//		scene_corners[i] = cvPoint(cvRound(X) + img_1.cols, cvRound(Y));
//	}
//
//	//-- Draw lines between the corners (the mapped object in the scene - image_2 )
//	line(img_matches, scene_corners[0], scene_corners[1], Scalar(0, 255, 0), 2);
//	line(img_matches, scene_corners[1], scene_corners[2], Scalar(0, 255, 0), 2);
//	line(img_matches, scene_corners[2], scene_corners[3], Scalar(0, 255, 0), 2);
//	line(img_matches, scene_corners[3], scene_corners[0], Scalar(0, 255, 0), 2);
//
//	//-- Show detected matches
//	// namedWindow( "Good Matches & Object detection", WINDOW_AUTOSIZE);
//	namedWindow("Good Matches & Object detection", CV_WINDOW_NORMAL);
//	imshow("Good Matches & Object detection", img_matches);
//	//resizeWindow( "Good Matches & Object detection", 800, 800);
//
//	waitKey(0);
//	return 0;
//}
//
