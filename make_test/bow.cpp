#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "opencv2/legacy/legacy.hpp"


#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;
using namespace cv;

#define PIC_NUM 10
std::vector<string> file_name;

char path[]="/home/xy/datasets_img/png-ZuBuD/";
char working_path[]="/home/xy/test_for_fun/make_test/";

int compare_string(char *string1,char* string2,int n){
    int i=0;
    for(i=0;i<n;i++){
        if((*string1=='\0')||(*string2=='\0')){
            cout<<"the input number is too big"<<endl;
            return 0;
        }
        if(*string1++!=*string2++){
            cout<<"the "<<i<<"th char is not equel"<<endl;
            return 0;
        }
    }
    return 1;
}


int  listdir(char* path){
    DIR *dir;
    struct dirent *ent;
    char buf[512];
    char compare_buf[]="object";
    int compare_result;
    if((dir=opendir(path))==NULL){
        cout<<"open dir error"<<endl;
        return 0;
    }
    chdir(path);
    while((ent=readdir(dir))!=NULL){
        if(ent->d_type==4){  /*如果是目录*/
            if(!strcmp(".",ent->d_name)||!strcmp("..",ent->d_name)){continue;}
            listdir(ent->d_name);
        }else{
         if(ent->d_type==8){ /*如果是文件*/
            compare_result=compare_string(compare_buf, ent->d_name, 6);
            if(compare_result==0){
                cout<<"the unequal string is "<<ent->d_name<<endl;
            }
            if(compare_result!=0){
              file_name.push_back(ent->d_name);  
            }
            
         }
        }
    }
    chdir("..");  /*重点是还要返回上一个目录，不然会出错*/
    closedir(dir);
    cout<<"vector file_name has a number of "<<file_name.size()<<endl;
    return 1;
}


int main(void){
 	Mat des[PIC_NUM];
 	int i=0,start,descount_total=0;
    cv::initModule_nonfree();

	Ptr<FeatureDetector> detector = FeatureDetector::create("SIFT");
    Ptr<DescriptorExtractor> extractor = DescriptorExtractor::create("SIFT");
    Ptr<DescriptorMatcher> match = DescriptorMatcher::create("BruteForce");

    listdir(path);

    /*计算所有图片的描述符，并将其存储于Mat des[i]中*/
    for(i=0;i<PIC_NUM;i++){
        chdir(path);
        Mat img = imread((file_name.at(i)).c_str(),CV_LOAD_IMAGE_GRAYSCALE);
        cout<<file_name.at(i).c_str()<<endl;
        if(img.empty()){
            cout<<"image read error"<<endl;
            return (-1);
        }
        chdir(working_path);
/*vector前必须加上std*/
        std::vector<KeyPoint> keypoints;
        detector->detect(img,keypoints);
        extractor->compute(img,keypoints,des[i]);
        descount_total+=des[i].rows; /*计算描述符的总数*/
        cout<<i<<"th img number of des is "<<des[i].rows<<endl;
    }


    /*合并所有图片的描述符至描述符MerDes中*/
    cout<<"des[0].cols is "<<des[0].cols<<endl;
    cout<<"des[0].type is "<<des[0].type()<<endl;
    cout<<"descount_total is "<<descount_total<<endl;
    
    Mat MergeDes(descount_total,des[0].cols,des[0].type());

    for(int i=0,start=0;i<PIC_NUM;i++){
        Mat sub=MergeDes.rowRange(start,start+des[i].rows);
        des[i].copyTo(sub);
        start+=des[i].rows;
    }
   

   /*将所有的描述符保存到文件fs1中*/
    FileStorage fs1("MerDes",CV_STORAGE_WRITE);
    if(!fs1.isOpened()){
        cout<<"fs1 open error"<<endl;
        return (-1);
    }

    write(fs1,MergeDes);
    fs1.release();
    return 1;

}
