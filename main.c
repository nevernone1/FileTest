#include <stdio.h>
#include "ConfigFile.h"

int main()
{
    char ** configStrs = NULL;
    struct ConfigInfo * configInfos = NULL;
    int line = 0;
    loadFile("/Users/jy/Desktop/t.txt",&configStrs,&line);
    printf("-------------\n");
   convertToStructArr(&configInfos,configStrs,line);
   for(int i = 0; i < line; i++){
   printf("key: %s, value: %s \n",configInfos[i].key,configInfos[i].value);
   }
   destroyMem(configInfos);

    return 0;
}
