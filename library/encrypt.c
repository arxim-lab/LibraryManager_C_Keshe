
/* 异或加(解)密0
 *
 * 使用方法：接收字符串名 = xor_crypt(需要处理的字符串,数字KEY);
 */
char * xor_crypt(char *text,int sec){
    int len=strlen(text),i;
    char *output;
    output = (char*)malloc(sizeof(char)*len);
    free(output);
    output = (char*)malloc(sizeof(char)*len);
    for(i=0;i<len;i++)
        output[i] = text[i]^sec;
    return output;
}
