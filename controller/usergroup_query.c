
void table_print_usergroup(UserGroup_result *result,th *header){
    tl * tl1;
    for(;result->n!=NULL;result=result->n){
        tl1 = tl_classify(3,num_to_str(result->u->gid),result->u->gname,num_to_str(write_mask(result->u->permission)));
        table_print_line(header,tl1);
        tl_free(tl1);
    }
}

/* 用户组条目操作 (修改、删除) */
void show_usergroup_edit(int _gid){
    interface_create("用户组信息编辑",true);
    UserGroup * actor;
    int action=1,__num,err=1;
    char *val;
    actor = usergroup_get(_gid,NULL);
    if(actor==NULL) err_catch(0);
    printf("\n========用户组信息=========\n");
    printf("      ID：%d\n用户组名：%s\n  权限码：%d",actor->gid,actor->gname,write_mask(actor->permission));
    hr(24,'=');
    printf("请选择你要进行的操作：\n[ 1 ] 编辑\n");
    printf("[ 2 ] 删除\n");
    action = num_check(0, 1, 2);
    switch(action){
        case 2:
            if(confirm("确认要删除吗？该操作不可逆！"))
                usergroup_sql_delete(_gid);
            break;
        case 1:
            printf("请选择你要编辑的字段：\n");
            action = menu_show_str(2,"用户组名","权限码");
            printf("请输入修改后的值：");
            switch(action){
                case 1:
                    val = string_create();
                    err = usergroup_sql_edit(actor->gid,val,0);
                    break;
                case 2:
                    __num = num_check(4,0,0);
                    err = usergroup_sql_edit(actor->gid,NULL,__num);
            }
            if(err_catch(err))
                alert("修改成功！");
            interface_delete(false);
    }
}

/* 用户组查询 */
void show_usergroup_query(){
    interface_create("用户组管理",true);
    UserGroup_result * _result;
    _result = result_usergroup_init();
    int _uid=0;
    usergroup_sql_query(_result);

// 用户组结果输出
    interface_create("用户组搜索结果",true);
    th *th1;
    int th_width[3]={3,12,9};
    th1 = th_classify(3,th_width,"Gid","UserGroup","Permission");
    table_print_header(th1);
    table_print_usergroup(_result,th1);
    th_free(th1);
    hr(20,'=');
    printf("请输入你想修改的用户组ID: ");
    _uid = num_check(0,0,0);
    show_usergroup_edit(_uid);

// 回退主菜单
    interface_delete(false);
    result_usergroup_delete(_result);
}

/* 用户组添加 */
void show_usergroup_add(){
    interface_create("用户组添加",true);
    char *gname_;
    UserGroup * new_one;
    int sid_,err=1;
    printf("请输入新用户信息：\n");
    printf("用户名: ");
    gname_ = string_create();
    printf("权限码: ");
    sid_ = num_check(4,0,0);
    new_one = usergroup_create(gname_,sid_);
    err = usergroup_sql_create(new_one);
    if(err_catch(err))
        alert("创建成功！");
    interface_delete(false);
}
