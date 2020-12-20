
// 加载编译环境
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <stdarg.h>

// 加载系统环境
#include "init.c"                 // 初始化环境
#include "include.c"              // 加载系统模块
#include "loader.c"               //

int main(){
    cfg_read();
    db_connect();
    interface_init();
    show_login();
    show_main_menu();
}
