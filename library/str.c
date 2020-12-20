
/* 字符串：字符串创建
 * （需提前创建好字符串空间）
 * 直接获取输入文字创建字符串
 * 只能输入单行文本，以回车键结束
 *
 * 使用方法：字符串名 = string_create(); // 不需要带*号
 */
char * string_create(){
    int len=0,i=0;
    char *input;
    input = (char*)malloc(sizeof(char)*(len+6));
    len += 6;
    scanf("%c",&input[i++]);
    len = strlen(input);
    while(input[i-1] != '\n'){
        if(i == len){
            input = (char *)realloc(input,sizeof(char)*(len+6));
            len += 6;
        }
        scanf("%c",&input[i++]);
    }
    if(i == len)
        input = (char *)realloc(input,sizeof(char)*(len+1));
    input[i-1] = '\0';
    return input;
}

/* 字符串：字符串转换
 * （需提前创建好字符串空间）
 * 将字符数组转换为字符串（跟放屁一样）
 *
 * 使用方法：字符串名 = string_trans("字符串，可换行"); // 不需要带*号
 */
char * string_trans(char * str){
    int len=strlen(str);
    char *output;
    output = (char*)malloc(sizeof(char)*len);
    strcpy(output,str);
    return output;
}

/* 字符串：读取真实长度
 * 做这个实属无奈之举
 *
 * 使用方法：整型变量名 = str_len(字符串名);
 */
int str_len(char str[]){
    int len=0,i=0;
    char *test = str;
    for(;(*test)!='\0';test++){
        if((*test)>=32&&(*test)<=126) len++;
        else i++;
        if((IsLinux&&i==3)||(!IsLinux&&i==2)){
            len += 2;
            i = 0;
        }
    }
    return len;
}

/* 字符串：动态连接
 * ！结尾以NULL结尾
 * ！别瞎拿空字符串试就好，别作死
 * 中间不能连着有两个空字符串
 *
 * 使用方法：字符串名 = str_cat(字符串1,字符串2...,NULL);
 */
char * str_cat(char *str,...){
    va_list strs;
    int size;
    char *tmp_name,*output;
    size = strlen(str);
    output = (char*)malloc(sizeof(char)*size);
    strcpy(output,str);
    va_start(strs,str);
    for(tmp_name = va_arg(strs,char*);tmp_name!=NULL;tmp_name = va_arg(strs,char*)){
        size += strlen(tmp_name);
        output = (char*)realloc(output,sizeof(char)*size);
        strcat(output,tmp_name);
    }
    va_end(strs);
    return output;
}

/* 字符串：数字转换字符串
 *
 * 使用方法：字符串名 = num_to_str(数字);
 */
long long mult10(long long times){
    long long i,sum=1;
    for(i=1;i<=times;i++)
        sum *= 10;
    return sum;
}
char * num_to_str(long long num){
    char cbit[1];
    char * output;
    long long bit=0,i=0;
    bit = num/mult10(0)%10;
    cbit[0] = (int)bit+'0';
    output = str_cat(cbit,NULL);
    for(i=1;true;i++){
        bit = num/mult10(i)%10;
        if(bit==0&&num/mult10(i)<=0)
            break;
        cbit[0] = (int)bit+'0';
        output = str_cat(cbit,output,NULL);
    }
    return output;
}

/* 字符串：字符串转换数字
 *
 * 使用方法：数字名 = str_to_num(数字字符串);
 */
long long str_to_num(char * num){
    long long sum=0,len=strlen(num),i;
    for(i=0;i<len;i++){
        if(num[i]>='0'&&num[i]<='9')
            sum = sum*10+(num[i]-'0');
        else
            return -1;
    }
    return sum;
}

/* 字符串：浮点数转换字符串
 * https://www.cnblogs.com/gleam/p/3607984.html
 *
 * 使用方法：字符串名 = float_to_str(浮点数);
 */
char * float_to_str(float val){
    char *cur, *end,*output;
    output = (char*)malloc(sizeof(char)*10);
    sprintf(output,"%.2f",val);
    cur = output+strlen(output)-1;
    end = cur-4;
    while(cur>end){
        if(*cur=='0')
            *cur = '\0';
        cur--;
    }
    return output;
}

/* 字符串：字符串转换浮点数
 *
 * 使用方法：数字名 = str_to_float(浮点数字符串);
 */
double str_to_float(char * num){
    return atof(num);
}
