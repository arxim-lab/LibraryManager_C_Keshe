
// 主菜单调用函数
void show_main_menu(){
    int choice,i,j=0,menu[9]={0};
    char *notic_;
    
// 主界面头输出      // 0100 开关：书籍信息->读
    bool Allow_Book_info_Write;                 // 0200 开关：书籍信息->写
    bool Allow_Book_info_Delete;                // 0400 开关：书籍信息->删除
    bool Allow_User_info_Read;
    interface_create("主菜单",true);
    printf("\n========用户信息=========\n");
    printf("用户名：%s\n  学号：%d\n用户组：%s",Login_User->uname,Login_User->sid,Login_User->gname);
    hr(24,'=');
    printf("欢迎你，%s！\n\n",Login_User->uname);
//    permission_echo();
    if(!ua.Allow_Book_info_Read){
        alert("你的账户已被封禁，请至前天管理员处办理解封手续！");
        interface_delete(false);
        show_logout();
    }

//o1 书籍信息查询
//o2 书籍信息管理
//o3 用户记录管理
//o4 用户组信息管理
//o5 书籍分类管理
//o6 用户信息修改
//o7 系统设置
//o8 关于制作团队
//o9 注销登录

// 菜单项选择
    if(ua.Allow_Book_info_Read)
        menu[j++] = 1;
    if(ua.Allow_Book_info_Write)
        menu[j++] = 2;
    if(ua.Allow_User_info_Write&&ua.Allow_Manage_Other_User_info)
        menu[j++] = 3;
    if(ua.Allow_Manage_User_Group)
        menu[j++] = 4;
    if(ua.Allow_Book_info_Write)
        menu[j++] = 5;
    if(ua.Allow_User_info_Write)
        menu[j++] = 6;
    if(ua.Allow_Manage_Sys_Config)
        menu[j++] = 7;
    menu[j++] = 8;
    menu[j] = 9;
    
// 菜单项输出
    for(i=0;menu[i]!=0&&i<9;i++){
        switch(menu[i]){
            case 1:
                notic_ = string_trans("书籍信息查询");
                break;
            case 2:
                notic_ = string_trans("书籍信息管理");
                break;
            case 3:
                notic_ = string_trans("用户记录管理");
                break;
            case 4:
                notic_ = string_trans("用户组信息管理");
                break;
            case 5:
                notic_ = string_trans("书籍分类管理");
                break;
            case 6:
                notic_ = string_trans("用户信息修改");
                break;
            case 7:
                notic_ = string_trans("系统备份");
                break;
            case 8:
                notic_ = string_trans("关于制作团队");
                break;
            case 9:
                notic_ = string_trans("注销登录");
        }
        printf("[ %d ] %s\n",i+1, notic_);
    }
    hr(20,'=');
    printf("请选择你要进行的操作: ");
    choice = num_check(0,1,j+1);

// 菜单项跳转
    switch(menu[choice-1]) {
        case 1:
            show_book_query();
            break;
        case 2:
            show_book_query();
            break;
        case 3:
            if(confirm("选择是进入用户信息管理界面，否进入用户添加界面: "))
                show_user_query();
            else
                show_user_add();
            break;
        case 4:
            if(confirm("选择是进入用户组信息管理界面，否进入用户组添加界面: "))
                show_usergroup_query();
            else
                show_usergroup_add();
            break;
        case 5:
            show_bookshelf_add();
            break;
        case 6:
            show_user_edit(Login_User->uid);
            break;
        case 7:
            show_syscfg();
            break;
        case 8:
            show_about();
            break;
        case 9:
            show_logout();
    }

// 递归调用显示主菜单
    interface_delete(false);
    show_main_menu();
}
