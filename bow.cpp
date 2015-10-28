#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/legacy/legacy.hpp"

#include <iostream>
#include <vector>

#define CENTER_NUM 10

#define PIC_NUM 10

using namespace cv;
using namespace std;

int main(){
    int i=0;
    Mat img[PIC_NUM],img2;
    Mat des2;
    int descount[PIC_NUM];
    int descount_total=0;
    cv::initModule_nonfree();
    Ptr<FeatureDetector> detector = FeatureDetector::create("SIFT");
    Ptr<DescriptorExtractor> extractor = DescriptorExtractor::create("SIFT");
    Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce");
    std::vector<KeyPoint> keypoints1,keypoints2;

/*
    BOWKMeansTrainer bowTraining(CENTER_NUM,cvTermCriteria(CV_TERMCRIT_EPS+CV_TERMCRIT_ITER,10,0.1),3,2);
    if(detector.data||extractor.data||matcher.empty()){
        cout<<"cant create detector or extractor or matcher"<<endl;
        return -1;
    }
    for(i=0;i<PIC_NUM;i++){
       img[i] = imread("/home/xy/datasets_img/png-ZuBuD/*.jpg",CV_LOAD_IMAGE_GRAYSCALE);
       if(img[i].empty()){
            cout<<"img read error"<<endl;
            return -1;
       }

    }
*/
	img2 = imread("/home/xy/datasets_img/png-ZuBuD/object0001.view01.png",CV_LOAD_IMAGE_GRAYSCALE);
	if(img2.empty()){
        cout<<"read img error"<<endl;
        return -1;
	}


	detector->detect(img2,keypoints2);
	extractor->compute(img2,keypoints2,des2);

    cout<<"the number of des is "<<des2.size()<<endl;
    FileStorage fs1("descriptor",CV_STORAGE_WRITE);
    if(!fs1.isOpened()){
        cout<<"fs1 open error"<<endl;
        return -1;
    }
    write(fs1,des2);
    fs1.release();




}

