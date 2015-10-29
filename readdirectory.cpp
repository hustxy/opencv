#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <iostream>
#include <string>
using namespace std;

char path[]="/home/xy/datasets_img/png-ZuBuD/";

void listdir(char* path){
    DIR *dir;
    struct dirent *ent;
    char buf[512];
    if((dir=opendir(path))==NULL){
        cout<<"open dir error"<<endl;
        exit(0);
    }
    chdir(path);
    while((ent=readdir(dir))!=NULL){
        if(ent->d_type==4){  /*如果是目录*/
            if(!strcmp(".",ent->d_name)||!strcmp("..",ent->d_name)){continue;}
            listdir(ent->d_name);
        }else{
         if(ent->d_type==8){ /*如果是文件*/
            cout<<ent->d_name<<endl;
         }
        }
    }
    chdir("..");
    closedir(dir);
}

int main(){
 listdir(path);
 return 1;
}
