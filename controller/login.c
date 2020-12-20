
/* 登录界面调用函数 */
void show_login(){

// 登录界面输出
    int input_sid=0,gid_num;
    User_result *login_check;
    char *input_pwd,*encrypt_pwd,*get_pwd;
    interface_create("登录界面",false);
    hr(30,'=');
    printf("\n%s\n",LOGIN_WELCOME);
    hr(30,'=');
    encrypt_pwd = (char*)malloc(sizeof(char));
    while(1) {
        free(encrypt_pwd);
        printf("\nStudent_ID: ");
        input_sid = num_check(0, 0, 0);
        printf("  Password: ");
        input_pwd = string_create();

// 输入结果处理
        encrypt_pwd = xor_crypt(input_pwd, KEY);
        login_check = user_query(input_sid);
        if(login_check==NULL){                                      // 检测用户是否存在
            printf("\n用户不存在！");
            continue;
        }
        get_pwd = string_trans(user_get_password(input_sid));
        if (strcmp(encrypt_pwd,get_pwd)==0)   // 检查密码是否正确
            break;
        printf("\n密码错误！");
    }

// 多身份用户检查
    if(login_check->n->n!=NULL){
        printf("\n此用户拥有多个身份账户，请选择你想登录的账户：\n");
        int num=1,max=0;
        User_result *init;
        init = login_check;
        for(;init->n!=NULL;init=init->n){
            printf("[%-4d] UID=%d %s\n",num++,init->u->uid,usergroup_get(init->u->gid,NULL)->gname);
            max++;
        }
        hr(30,'=');
        printf("请输入你想登录的账户序号：");
        gid_num = num_check(0,1,max);
        for(int i=1;i<gid_num;i++)
            login_check = login_check->n;
        Login_User = user_get(login_check->u->uid,NULL,0);
    }
    Login_UserGroup = usergroup_get(Login_User->gid,NULL);
//    printf("%d%d%d%d\n",Login_User->mask[0],Login_User->mask[1],Login_User->mask[2],Login_User->mask[3]);
    Login_User->permission[0] = Login_UserGroup->permission[0];
    Login_User->permission[1] = Login_UserGroup->permission[1];
    Login_User->permission[2] = Login_UserGroup->permission[2];
    Login_User->permission[3] = Login_UserGroup->permission[3];
    Login_User->gname = string_trans(usergroup_get(Login_User->gid,NULL)->gname);
    ua_create(Login_User);
    result_user_delete(login_check);
    interface_delete(false);
}

/* 注销界面调用函数 */
void show_logout(){

// 注销界面输出
    interface_create("注销界面",false);
    printf("  尊敬的%s ，你已成功注销登录。",Login_User->uname);
    free(Login_User);
    ua_reset();
    alert("请重新登录!");
    interface_delete(false);
    exit(0);
}
