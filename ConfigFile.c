#include "ConfigFile.h"
#include <stdlib.h>
#include <string.h>

#define CHARSIZE 1024

//获取有效行数
int getLines(FILE * fp){
    int line = 0;
    char *buf = (char *)malloc(sizeof (char)*CHARSIZE);
    memset(buf,0,CHARSIZE);
    while (fgets(buf,CHARSIZE,fp) != NULL) {
        if(isValidContent(buf) == 0){
            continue;
        }
        line ++;
        memset(buf,0,CHARSIZE);
    }
    fseek(fp,0,SEEK_SET);
    free(buf);
    return  line;
}

//加载文件
void loadFile(const char * filePath, char ***configStrs, int * lines){

    if(strlen(filePath) == 0){
        printf("输入文件路径有误");
        return;
    }
    FILE * fp = fopen(filePath,"r");
    if(fp == NULL){
         printf("打开失败");
        return;
    }
    int i = 0;
    int lineNum = getLines(fp);

    char ** strArr = (char **)malloc(sizeof (char*) * (unsigned int)lineNum);
    char * buf = (char *)malloc(sizeof (char) * CHARSIZE);
    memset(buf,0,CHARSIZE);
    while(fgets(buf,CHARSIZE,fp) != NULL){
        if(isValidContent(buf) == 0){
            memset(buf,0,CHARSIZE);
            continue;
        }
        strArr[i] = (char *)malloc(sizeof (char) * 1024);
        memset(strArr[i],0,1024);
        strcpy(strArr[i],buf);
        unsigned long int lenth = strlen(strArr[i]);
        if(strArr[i][lenth - 1] == '\n'){
            strArr[i][lenth - 1] = '\0';
        }
        memset(buf,0,CHARSIZE);
        i++;
    }
    *configStrs = strArr;
    *lines = lineNum;

    free(buf);
    fclose(fp);
}

//转换为结构体数组
void convertToStructArr(struct  ConfigInfo ** configInfos,char ** configStrs, int line){
   struct ConfigInfo * configIns = malloc(sizeof (struct ConfigInfo) *(unsigned long) line);
   for(int i = 0; i< line; i++){
       strncpy(configIns[i].key, configStrs[i],strchr(configStrs[i],':') - configStrs[i]);
       strncpy(configIns[i].value, strchr(configStrs[i],':') + 1,strlen(strchr(configStrs[i],':') + 1));
   }
   *configInfos = configIns;
   for(int i = 0; i < line; i ++){
       free(configStrs[i]);
       configStrs[i] = NULL;
   }
   free(configStrs);
   configStrs = NULL;
}

//判断行内容是否有效
int isValidContent(const char * content){
    if(strcmp(content,"") == 0 || strchr(content,':') == NULL ||strncmp(content,"#",1) == 0){
        return 0;
    }
    return 1;
}

//释放空间
void destroyMem(struct  ConfigInfo * configInfos){
    free(configInfos);
    configInfos = NULL;
}
