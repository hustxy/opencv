#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgpro/imgpro.hpp"
#include "opencv2/features2d/features2d.hpp"

#include <vector>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int main(void){
 
 char path1[]="test1";
 char path2[]="test2";

 int i=0;
 vector<string> S;
 S.push_back(path1);
 S.push_back(path2);
 
 cout<<"the element number in vector S is "<<S.size()<<endl;
 for(i=0;i<S.size();i++){
 
 	cout<<S.at(i)<<endl;

 }
return 1;
}