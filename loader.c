
// 错误捕捉函数
// 0  数据传入异常,或操作执行异常
// 1  程序正常
// -1 权限不足
// 2  数据不唯一
// 3  数据不存在
// 4  相同用户组下SID不唯一  （特殊情况：仅限修改用户时）
int err_catch(int code){
    if(code==1) return 1;
    if(code==-1) printf("\n权限不足！\n");
    if(code==0){
        printf("\n程序运行异常！\n");
        if(confirm("警告：是否继续运行？如果坚持继续，可能会有程序崩溃的风险！")) ;
        else exit(1);
    }
    if(code==2) printf("\n数据不唯一！\n");
    if(code==3) printf("\n数据不存在！\n");
    if(code==4) printf("\n相同用户组下SID不唯一！\n");
    return 0;
}

/* 控制器模块加载 */
#include "controller/usergroup_query.c"
#include "controller/user_query.c"
#include "controller/book_query.c"
#include "controller/introduction.c"
#include "controller/sys_cfg.c"
#include "controller/login.c"
#include "controller/main_menu.c"
