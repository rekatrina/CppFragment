#include"frameExtractor.h"

int main(int argc, char **argv){
	frameExtractor extractor;
	
	extractor.loadVideo("D:\\data\\2015_0214_092046_002A.MOV");

	extractor.setSkipFrame(99);

	extractor.setOutputPath("D:\\");

	extractor.setROI(frameExtractor::Center, 0.5);

	extractor.extract();
	
	
}