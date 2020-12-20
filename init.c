
/* 布尔类型
 * true & false
 *
 * 使用方法：bool 变量名;
 */
typedef enum bool{
    false=0,true
}bool;

// Debug MODE
int Debug_mode;
char *db_link;
//bool Debug_mode = true;
//char *db_link = "test.db";
char *ACCESS_DENIED = "权限不足！";
int KEY = 123;
int GID_READERS = 6;
//bool Allow_Self_Change_Info = true;

// 系统环境判定
#ifdef linux
bool IsLinux = true;
#include <unistd.h>
#else
bool IsLinux = false;
#include <windows.h>
#endif



// 窗体准备
char *menu_notice = "请选择您的操作: ";                // 菜单选择提示文字
char breadcrumb_separator = '>';                    // 面包屑分隔符
char *breadcrumb_notice = "您现在的位置: ";           // 面包屑提示文字

// 准备数据库环境
char *sql_errmsg = 0;
// 初始化SQL语句
char *sql_init = "create table book("
                 "    bid integer primary key autoincrement,"
                 "    bname text not null,"
                 "    cid integer default 0,"
                 "    shelf integer default 0,"
                 "    location integer default 0,"
                 "    isbn text,"
                 "    author text,"
                 "    price float,"
                 "    press text,"
                 "    add_time bigint not null,"
                 "    status integer default 0,"
                 "    operator_id integer not null,"
                 "    operated_time bigint"
                 ");"
                 "create table bookshelf("
                 "    cid integer primary key autoincrement,"
                 "    cname text not null"
                 ");"
                 "create table syscfg("
                 "    cid integer primary key autoincrement,"
                 "    auth text not null,"
                 "    key text not null"
                 ");"
                 "create table user("
                 "    uid integer primary key autoincrement,"
                 "    uname text not null,"
                 "    gid integer not null,"
                 "    password text not null,"
                 "    sid integer not null,"
                 "    IsMale boolean default false,"
                 "    reg_time bigint not null,"
                 "    mask integer default 0"
                 ");"
                 "create table usergroup("
                 "    gid integer primary key autoincrement,"
                 "    gname text not null,"
                 "    permission integer not null"
                 ");";

// 异常输入提示
int input_errmsg_num = 6;
char *input_errmsg[] = {
        "输入错误，请重新输入: ",                      // 第一次输入错误
        "又输错了，请重新输入: ",                      // 第二次输入错误
        "你认真的吗？\n系统强制关闭！"                  // 输入错误过多
};
char *input_multi_errmsg[] = {
        "走点心吧老铁！",
        "球球你做个人吧！",
        "系统表示不想和你说话。",
        "要被玩坏惹！",
        "系统已经懒得理你了……",
        "人言否？"
};

// 时间模块准备
char *time_format = "%X";                       // 短时间输出格式
char *date_format = "%Y.%m.%d";                 // 短日期输出格式
char *longtime_format = "%Y.%m.%d %X";          // 长时间输出格式

// ==================================================
//                    结构体定义
// ==================================================

sqlite3 *mydb;

typedef struct tm* tm;

/* 动态字符串类型（动态分配内存空间）
 * 不限长度
 *
 * 使用方法：string 字符串名;
 */
typedef char* string;

/* 窗体类型
 * 用于记录当前窗口的信息
 * 与面包屑组件和窗体管理配合使用
 */
typedef struct window{
    int k;                                       // Key
    char * name;                                 // Window Name
    struct window * n;                           // Next
}window;
window * window_group;

// 用户类型
typedef struct User{
    int uid,sid,gid,mask[4],permission[4];       // permission同时储存权限码
    char *uname,*gname;                          // gname同时储存用户组名
    bool IsMale;
    tm reg_time;
}User;
User * Login_User;

// 用户组类型
typedef struct Usergroup{
    int gid,permission[4];
    char * gname;
}UserGroup;
UserGroup * Login_UserGroup;

// 书籍类型（自动识别书架）
typedef struct Book{
    int bid,cid,shelf,location,status,operator_id;
    tm add_time,operated_time;
    float price;
    char *bname,*isbn,*author,*press,*cname;    // cname同时储存书籍分类名
}Book;

// UserAgent类型
typedef struct UserAgent{
    bool Allow_Book_info_Read;                  // 0100 开关：书籍信息->读
    bool Allow_Book_info_Write;                 // 0200 开关：书籍信息->写
    bool Allow_Book_info_Delete;                // 0400 开关：书籍信息->删除
    bool Allow_User_info_Read;                  // 0010 开关：用户信息->读
    bool Allow_User_info_Write;                 // 0020 开关：用户信息->写
    bool Allow_User_info_Delete;                // 0040 开关：用户信息->删除
    bool Allow_Lending_Log_Read;                // 0001 开关：借阅日志->读
    bool Allow_Lending_Log_Write;               // 0002 开关：借阅日志->写
    bool Allow_Lending_Log_Delete;              // 0004 开关：借阅日志->删除
    bool Allow_Manage_Other_User_info;          // 1000 开关：特殊权限->其他用户管理
    bool Allow_Manage_User_Group;               // 2000 开关：特殊权限->用户组管理
    bool Allow_Manage_Sys_Config;               // 4000 开关：特殊权限->系统信息管理
}UserAgent;
UserAgent ua;

// 用户组搜索结果链表
typedef struct usergroup_result{
    UserGroup * u;                              // 储存用户组信息
    struct usergroup_result * n;                // 指向下一个用户组
}UserGroup_result;

// 用户搜索结果链表
typedef struct user_result{
    User * u;                                   // 储存用户信息
    struct user_result * n;                     // 指向下一个用户
}User_result;

// 书籍搜索结果链表
typedef struct book_result{
    Book * u;                                   // 储存书信息
    struct book_result * n;                     // 指向下一本书
}Book_result;

// 显示语句
char *LOGIN_WELCOME = "Welcome!";
