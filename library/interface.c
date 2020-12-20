
/* 数字输入检测
 * 输出为long long类型
 * ！当最小值大于等于最大值时，没有范围限制
 * ！当接受数字位数为0时，不限制数字位数
 *
 * 使用方法：整型变量名 = num_check(接受数字位数,最小值,最大值);
 */
long long num_check(int sbit,long long min,long long max){
    int times=1,i;
    char * test;
    long long sum=0;
    bool err;
    while(true){
        test = string_create();
        for(err=true,i=0;test[i]!='\0';i++){
            if(test[i]>='0'&&test[i]<='9')
                err = false;
            else {
                err = true;
                break;
            }
        }
        if(err==false&&(i<=sbit||sbit==0)){
            for(sum=0,i=0;test[i]!='\0';i++)
                sum = (long long)(sum*10)+(long long)(test[i]-'0');
            if((sum>=min&&sum<=max)||min>=max)
                return sum;
        }
        switch (times++) {
            case 1:
                printf("%s",input_errmsg[0]);
                break;
            case 2:
                printf("%s",input_errmsg[1]);
                break;
            case 50:
                printf("%s",input_errmsg[2]);
                exit(0);
            default:
                printf("%s重输: ",input_multi_errmsg[rand()%input_errmsg_num]);
        }
    }
}

/* 输出自定义分割线
 *
 * 使用方法：hr(长度,'分割线字符')
 */
void hr(int num,char sym){
    int count;
    putchar('\n');
    for(count=0;count<num;count++)
        putchar(sym);
    putchar('\n');
}

/* 对话框：警告对话框
 * (按任意键继续）
 * 可输出警示文字
 * 无返回值
 *
 * 使用方法：alert("字符串");
 */
void alert(char *notice){
    hr(30,'=');
    printf("%s (按任意键继续运行)\n",notice);
    if(IsLinux) system("read -s -n1 -p \"\" nullvalue");
    else system("pause>null");
}

/* 对话框：确认对话框
 * 可进行确认操作
 * 返回布尔值
 * 输入y，返回true；输入n，返回false；输入其他字符，反复输出确认信息直到输入合法字符为止
 *
 * 使用方法：confirm("字符串");
 */
bool confirm(char *notice){
    hr(30,'=');
    char con;
    while(true){
        printf("%s (y/n) ",notice);
        con = getchar();
        getchar();
        if(con=='y'){
            hr(30,'=');
            return true;
        }else if(con=='n'){
            hr(30,'=');
            return false;
        }
    }
}

/* 对话框：提示对话框
 * 可提供单行文本输入的对话框
 * 用于在其他显示组件后临时追加字符串的输入
 *
 * 使用方法：prompt("字符串，可多行");
 */
char * prompt(char *notice){
    hr(30,'=');
    printf("%s ",notice);
    return string_create();
}

/* 显示组件：面包屑导航 (BreadcrumbNavigation)
 * 用于显示窗体访问路径
 *
 * 使用方法：breadcrumb_show();
 */
void breadcrumb_show(){
    window *end,*init;
    init = window_group;
    printf("\n%s ",breadcrumb_notice);
    for(init=init->n;init->n!=NULL;init=init->n){
        printf("%s",init->name);
        end = init->n;
        if(end->n!=NULL) printf(" %c ",breadcrumb_separator);
        else break;
    }
    putchar('\n');
}

/* 窗体管理：初始化窗体组
 *
 * 使用方法：interface_init();
 */
void interface_init(){
    window *p1,*p2,*init;
    p1 = (window *)malloc(sizeof(window));
    p1->k = 0;
    p1->name = string_trans("init");
    p1->n = NULL;
    init = p1;
    p2 = p1;
    p1 = (window *)malloc(sizeof(window));
    p1->k = 1;
    p1->name = string_trans("null");
    p1->n = NULL;
    p2->n = p1;
    window_group = init;
}

/* 窗体管理：新建页
 *
 * 使用方法：interface_create("新窗体名",是否打印面包屑);
 */
void interface_create(char *new_window_name,bool ShowBreadcrumb){
    window *p1,*init;
    int key;
    init = window_group;
    for(;init->n!=NULL;init=init->n)
        key = init->k;
    p1 = (window *)malloc(sizeof(window));
    init->name = string_trans(new_window_name);
    init->k = key+1;
    p1->k = key+2;
    p1->name = string_trans("null");
    p1->n = NULL;
    init->n = p1;
    // 清空屏幕
    if(IsLinux) system("clear");
    else system("cls");
    if(ShowBreadcrumb) breadcrumb_show();
}

/* 窗体管理：销毁页
 * 销毁最近创建的窗体
 *
 * 使用方法：窗体组名 = interface_delete(是否打印面包屑);
 */
void interface_delete(bool ShowBreadcrumb){
    window *init,*end;
    init = window_group;
    for (;init->n!=NULL;init=init->n)
        end = init;
    free(init); // 释放内存空间
    end->name = string_trans("null");
    end->n = NULL;
    // 清空屏幕
    if(IsLinux) system("clear");
    else system("cls");
    if(ShowBreadcrumb) breadcrumb_show();
}

/* 显示组件：菜单
 * 返回所选项数（从1开始）
 *
 * 使用方法：menu_show_str(菜单项数,"菜单项文字（char类型）"...);
 */
int menu_show_str(int num,char *li,...){
    va_list menu;
    int i=1;
    char *li_str;
    va_start(menu,li);
    hr(30,'=');
    printf("[ %d ] %s\n",i++,li);
    for(;i<=num;i++){
        li_str = va_arg(menu,char*);
        printf("[ %d ] %s\n",i,li_str);
    }
    hr(30,'=');
    printf("%s: ",menu_notice);
    va_end(menu);
    return num_check(0,1,num);
}

/* 表格头类型
 *
 * 使用方法：th * 表格头名;
 */
typedef struct tableheader{
    struct tableheader *n;
    int len;
    char *name;
}th;

/* 表格信息列
 *
 * 使用方法：tl * 表格头名;
 */
typedef struct tableline{
    char * value;
    struct tableline *n;
}tl;

/* 表格行：定义
 *
 * 使用方法：表格行名 = th_classify(列数,各列内容...);
 */
tl * tl_classify(int tr,char *name,...){
    va_list names;
    int i=0;
    char *tmp_name;
    tl *output,*p1,*p2;
    p1 = (tl*)malloc(sizeof(tl));
    p1->value = name;
    p1->n = NULL;
    output = p1;
    va_start(names,name);
    for(;i<tr;i++){
        p2 = p1;
        p1 = (tl*)malloc(sizeof(tl));
        tmp_name = va_arg(names,char*);
        p1->value = tmp_name;
        p1->n = NULL;
        p2->n = p1;
    }
    p2 = p1;
    p1 = (tl*)malloc(sizeof(tl));
    p1->n = NULL;
    p2->n = p1;
    return output;
}

/* 表格头：定义
 *
 * 使用方法：表格头名 = th_classify(列数,由各列宽度组成的数组,各列标题...);
 */
th * th_classify(int tr,int len[],char *name,...){
    va_list names;
    int i=0;
    char *tmp_name;
    th *output,*p1,*p2;
    p1 = (th*)malloc(sizeof(th));
    p1->len = len[i++];
    p1->name = name;
    p1->n = NULL;
    output = p1;
    va_start(names,name);
    for(;i<tr;i++){
        p2 = p1;
        p1 = (th*)malloc(sizeof(th));
        p1->len = len[i];
        tmp_name = va_arg(names,char*);
        p1->name = tmp_name;
        p1->n = NULL;
        p2->n = p1;
    }
    p2 = p1;
    p1 = (th*)malloc(sizeof(th));
    p1->n = NULL;
    p2->n = p1;
    return output;
}

/* 表格头：释放
 *
 * 使用方法：th_free(表格头名);
 */
void th_free(th *str){
    th * p;
    while(str != NULL){
        p = str;
        str = str->n;
        free(p);
        p = NULL;
    }
}

/* 表格行：释放
 *
 * 使用方法：tl_free(表格行名);
 */
void tl_free(tl *str){
    tl * p;
    while(str != NULL){
        p = str;
        str = str->n;
        free(p);
        p = NULL;
    }
}

/* 指定输出域长度输出字符串（兼容UTF-8中文）
 * ！仅在等宽字体环境中有效
 * 我他妈还能有什么办法
 *
 * 使用方法：printf_l(字符数组名,指定长度);
 */
void printf_l(char str[],int len){
    int str__len=str_len(str),i;
    printf("%s",str);
    for(i=0;i<(len-str__len);i++)
        putchar(' ');
}

/* 显示组件：表格：打印表头
 *
 * 使用方法：table_show_header(表格头名);
 */
void table_print_header(th *header){
    th * init=header;
    for(;init->n!=NULL;init=init->n){
        printf("|");
        printf_l(init->name,init->len);
    }
    printf("|\n");
}

/* 显示组件：表格：逐行打印信息
 *
 * 使用方法：table_show_header(表格头名，表格行名);
 */
void table_print_line(th *header,tl *line){
    th *h=header;
    tl *l=line;
    for(;h->n!=NULL;h=h->n,l=l->n){
        printf("|");
        printf_l(l->value,h->len);
    }
    printf("|\n");
}

