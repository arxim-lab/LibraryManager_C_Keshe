
void table_print_user(User_result *result,th *header){
    tl * tl1;
    for(;result->n!=NULL;result=result->n){
        tl1 = tl_classify(5,num_to_str(result->u->uid),result->u->uname,usergroup_get(result->u->gid,NULL)->gname,num_to_str(result->u->sid),num_to_str(result->u->IsMale));
        table_print_line(header,tl1);
        tl_free(tl1);
    }
}

/* 用户条目操作 (修改、删除) */
void show_user_edit(int _uid){
    interface_create("用户信息编辑",true);
    User * actor;
    int action=1,__num,err=1;
    char *val;
    actor = user_get(_uid,NULL,0);
    if(actor==NULL) err_catch(0);
    printf("\n========用户信息=========\n");
    printf("用户名：%s\n  学号：%d\n用户组：%s\n  性别：%s",actor->uname,actor->sid,usergroup_get(actor->gid,NULL)->gname,actor->IsMale?"男":"女");
    hr(24,'=');
    if(ua.Allow_User_info_Delete){
        printf("请选择你要进行的操作：\n[ 1 ] 编辑\n");
        printf("[ 2 ] 删除\n");
        action = num_check(0, 1, 2);
    }
    switch(action){
        case 2:
            if(confirm("确认要删除吗？该操作不可逆！"))
                user_sql_delete(_uid);
            break;
        case 1:
            printf("请选择你要编辑的字段：\n");
            action = menu_show_str(4,"用户名","学号","用户组ID","性别 (1或0)");
            printf("请输入修改后的值：");
            switch(action){
                case 1:
                    val = string_create();
                    err = user_sql_edit(actor,"uname",val);
                    break;
                case 2:
                    __num = num_check(0,0,0);
                    err = user_sql_edit(actor,"sid",num_to_str(__num));
                    break;
                case 3:
                    __num = num_check(0,0,0);
                    err = user_sql_edit(actor,"gid",num_to_str(__num));
                    break;
                case 4:
                    __num = num_check(0,0,1);
                    err = user_sql_edit(actor,"IsMale",__num?"true":"false");
            }
            if(err_catch(err))
                alert("修改成功！");
            interface_delete(false);
    }
    if(_uid==Login_User->uid) {
        alert("信息修改成功，请重新登录！");
        exit(0);
    }
}

/* 用户查询 */
void show_user_query(){
    interface_create("用户管理",true);
    User_result * _result;
    _result = result_user_init();
    UserGroup_result *ugr,*init_ug;
    ugr = result_usergroup_init();
    int _sid=0,_gid=0,_IsMale=-1,get_ugr,_uid=0;
    char *_uname="\0";

// 用户查询界面输出
    printf("\n========请设置查找关键词========\n");
    if(confirm("是否将用户名设置为搜索属性？")){
        printf("用户名: ");
        _uname = string_create();
    }
    if(confirm("是否将学号设置为搜索属性？")){
        printf("  学号: ");
        _sid = num_check(0,0,0);
    }
    if(confirm("是否将用户组设置为搜索属性？")){
        usergroup_sql_query(ugr);
        int num=1,max=0;
        init_ug = ugr;
        for(;init_ug->n!=NULL;init_ug=init_ug->n){
            printf("[%-4d] GID=%d %s\n",num++,init_ug->u->gid,init_ug->u->gname);
            max++;
        }
        hr(30,'=');
        printf("请输入你想检索的用户组序号：");
        get_ugr = num_check(0,1,max);
        for(int i=1;i<get_ugr;i++)
            ugr = ugr->n;
        _gid = ugr->u->gid;
    }
    result_usergroup_delete(ugr);
    if(confirm("是否将性别设置为搜索属性？"))
        _IsMale = confirm("性别设为男？");
    if(!confirm("是否开始搜索？")){
        interface_delete(false);
        result_user_delete(_result);
        return;
    }
    user_sql_query(_result,_sid,_uname,_gid,_IsMale);

// 用户搜索结果输出
    interface_create("用户搜索结果",true);
    th *th1;
    int th_width[5]={3,12,12,8,6};
    th1 = th_classify(5,th_width,"Uid","Username","UserGroup","Sid","IsMale");
    table_print_header(th1);
    table_print_user(_result,th1);
    th_free(th1);
    hr(20,'=');
    printf("请输入你想修改的用户ID: ");
    _uid = num_check(0,0,0);
    show_user_edit(_uid);

// 回退主菜单
    interface_delete(false);
    result_user_delete(_result);
}

/* 用户添加 */
void show_user_add(){
    interface_create("用户添加",true);
    char *pwd_,*uname_;
    User * new_one;
    int gid_,sid_,reg_time,err=1,ismale;
    printf("请输入新用户信息：\n");
    printf("用户名: ");
    uname_ = string_create();
    printf("  密码: ");
    pwd_ = string_create();
    printf("用户组: ");
    gid_ = num_check(0,0,0);
    printf("  学号: ");
    sid_ = num_check(0,0,0);
    reg_time = 0;
    if(confirm("是否为男性？"))
        ismale = 1;
    else ismale = 0;
    new_one = user_create(uname_,gid_,sid_,ismale);
    err = user_sql_create(new_one,pwd_);
    if(err_catch(err))
        alert("创建成功！");
    interface_delete(false);
}
