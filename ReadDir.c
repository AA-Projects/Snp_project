#include<stdio.h>
#include<string.h>
#include<dirent.h>
int EndsWithFoo(char *str){
    if(strlen(str) >= strlen(".txt")){
        if(!strcmp(str + strlen(str) - strlen(".txt"), ".txt")){
            return 1;
        }
    }
    return 0;
}
int main(){
    DIR *dir;
    struct dirent *ent;
    if((dir=opendir("."))!=NULL){
        while((ent=readdir(dir))!=NULL){
            if(EndsWithFoo(ent->d_name)==1)
                printf ("%s\n", ent->d_name);
        }
        closedir (dir);
    }
    else{
        perror ("");
    }
    return 0;
}
