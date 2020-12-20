//
//void cfg_read(){
//    FILE *fp;
//    char tmp[30];
//    int i=0;
//    fp = fopen("sys.cfg","r");
//    if(NULL==fp) {
//        alert("系统文件不存在！");
//        fclose(fp);
//        exit(1);
//    }
//    fgetc(fp);
//
//}
void cfg_read()
{
    FILE *fp;
    char c,de,*cc,w[2]={0};
    cc = (char*)malloc(sizeof(char));
    if((fp=fopen("sys.cfg","r+"))==NULL) {
        printf("Wrong input!\n");
        exit(0);
    }
    de = fgetc(fp);
    Debug_mode = de-'0';
    fgetc(fp);
    while(!feof(fp)) {
        w[0] = fgetc(fp);
        if(w[0]=='\n')
            break;
        cc = str_cat(cc,w,NULL);
    }
    db_link = string_trans(cc);
    fclose(fp);
}
//
///* 配置文件：读取信息项
// *
// * 使用方法：cfg_read(数据组标识,项标识,文件路径,值存储位置);
// * 返回值：
// * true ———— 读取成功
// * false ——— 读取失败
// */
//bool cfg_read(char *title,char *key,char *filename,char *buf){
//    FILE *fp;
//    int flag=0;
//    char sTitle[64],*wTmp,sLine[1024];
//    sprintf(sTitle,"[%s]",title);
//    if(NULL==(fp=fopen(filename,"r"))){
//        perror("fopen");
//        return false;
//    }
//    while(NULL!=fgets(sLine,1024,fp)){
//        if (0==strncmp("//",sLine,2)) continue;
//        if ('#'==sLine[0]) continue;
//        wTmp = strchr(sLine, '=');
//        if((NULL!=wTmp)&&(1==flag)){
//            if(0==strncmp(key,sLine,strlen(key))){          // 长度依文件读取的为准
//                sLine[strlen(sLine)-1] = '\0';
//                fclose(fp);
//                while(*(wTmp+1)==' ')
//                    wTmp++;
//                strcpy(buf,wTmp + 1);
//                return true;
//            }
//        }else
//            if(0==strncmp(sTitle,sLine,strlen(sTitle)))     // 长度依文件读取的为准
//                flag = 1;                                   // 找到标题位置
//    }
//    fclose(fp);
//    return false;
//}
