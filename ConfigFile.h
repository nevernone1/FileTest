
#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#include <stdio.h>

struct ConfigInfo{
    char key[64];
    char value[128];
};

#ifdef __cplusplus
extern "C"{
#endif

//获取有效行数
int getLines(FILE * fp);

//加载文件
void loadFile(const char * filePath, char ***configStrs, int * lines);

//转换为结构体数组
void convertToStructArr(struct  ConfigInfo ** configInfos,char ** configStrs, int line);

//判断行内容是否有效
int isValidContent(const char * content);

//释放空间
void destroyMem(struct  ConfigInfo * configInfos);

#ifdef __cplusplus
}
#endif

#endif
