/* archived */

// 早期使用链表实现可变长度字符串显示，功能较为完整，但并不符合实际生产环境,被废弃
// 留念 by Huntsman
// 2020.5.14

/* 动态字符串类型（字符串链表）
 * 不限长度
 *
 * 使用方法：string_old * 字符串名;
 */
typedef struct string_old{
    int k;    // Key
    char v; // Value
    struct string_old *n;   // Next
}string_old;

/* 字符串：字符串创建
 * （需提前创建好字符串空间）
 * 直接获取输入文字创建字符串
 * 只能输入单行文本，以回车键结束
 *
 * 使用方法：字符串名 = string_old_create(); // 不需要带*号
 */
string_old * string_old_create(){
    string_old *output,*p1,*p2;
    int i=0;
    p1 = (string_old*)malloc(sizeof(string_old));
    scanf("%c",&p1->v);
    p1->k = i++;
    p1->n = NULL;
    output = p1;
    while(p1->v!='\n'){
        p2 = p1;
        p1 = (string_old *)malloc(sizeof(string_old));
        scanf("%c",&p1->v);
        p1->k = i++;
        p1->n = NULL;
        p2->n = p1;
        // 最后一位是\n
    }
    return output;
}

/* 字符串：字符串转换
 * (需提前创建好字符串空间）
 * 将字符数组转换为字符串类型
 *
 * 使用方法：字符串名 = string_old_trans("字符串，可换行"); // 不需要带*号
 */
string_old * string_old_trans(char *str){
    int len=strlen(str),i=0;
    string_old *output,*p1,*p2;
    p1 = (string_old*)malloc(sizeof(string_old));
    p1->v = str[i];
    p1->k = i++;
    p1->n = NULL;
    output = p1;
    for(;i<=len;i++){
        p2 = p1;
        p1 = (string_old *)malloc(sizeof(string_old));
        p1->v = str[i];
        p1->k = i;
        p1->n = NULL;
        p2->n = p1;
        // 最后一位是\0
    }
    return output;
}

/* 字符串：字符串输出
 *
 * 使用方法：string_old_echo(字符串名);  // 不需要带*号
 */
void string_old_echo(string_old *str){
    for(;str->n!=NULL;str=str->n)
        putchar(str->v);
}

/* 字符串：字符串长度计算
 *
 * 使用方法：整型变量名 = string_old_len(字符串名);
 */
int string_old_len(string_old *str){
    while(str->n!=NULL)
        str = str->n;
    return str->k;
}

/* 字符串：字符串释放
 *
 * 使用方法：string_old_free(字符串名);  // 不需要带*号
 */
void string_old_free(string_old *str){
    string_old * p;
    while(str != NULL){
        p = str;
        str = str->n;
        free(p);
        p = NULL;
    }
}

/* 字符串：字符串转换定长字符数组
 * 最多可保留30个字符，长度设为0或30时为最大长度
 *
 * 使用方法：字符数组名 = string_old_cut(字符串名,保留字符长度);
 */
char * string_old_cut(string_old *str,int sbit){
    static char output[31];
    // 坑爹的地方，参考：https://blog.csdn.net/luna_zhan/article/details/80433196
    string_old *init;
    init = str;
    for(;((sbit==0||sbit==30)&&init->n!=NULL&&init->k<30)||((init->n!=NULL&&init->k<sbit&&sbit>0&&sbit<30));init=init->n){
        output[init->k] = init->v;
        if(init->n==NULL) break;
    }
    output[init->k] = '\0';
    if(init->k==30||init->k==sbit){
        output[init->k-1] = '.';
        output[init->k-2] = '.';
        output[init->k-3] = '.';
    }
    return output;
}

/* 读取字符数组真实长度
 * !仅适用于UTF-8编码
 * 做这个实属无奈之举
 *
 * 使用方法：整型变量名 = str_len(字符串名);
 */
int str_old_len(char str[]){
    int len=0,i=0;
    char *test=str;
    for(;(*test)!='\0';test++){
        if((*test)>=32&&(*test)<=126) len++;
        else i++;
        if(i==3){
            len += 2;
            i = 0;
        }
    }
    return len;
}
