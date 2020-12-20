
/* 0777
 * 1读 2写 4删除
 * 用户 LOG 书(架) x
 * x = {
 *     1 读写其他用户的信息
 *     2 管理用户组信息
 *     4 系统信息修改
 * }
 */

// 写入权限码
void permission_load_code(int code[]){
    if(code[3]&4==4) ua.Allow_Manage_Sys_Config = true;
    if(code[3]&2==2) ua.Allow_Manage_User_Group = true;
    if(code[3]&1==1) ua.Allow_Manage_Other_User_info = true;
    if(code[2]&4==4) ua.Allow_Lending_Log_Delete = true;
    if(code[2]&2==2) ua.Allow_Lending_Log_Write = true;
    if(code[2]&1==1) ua.Allow_Lending_Log_Read = true;
    if(code[1]&4==4) ua.Allow_User_info_Delete = true;
    if(code[1]&2==2) ua.Allow_User_info_Write = true;
    if(code[1]&1==1) ua.Allow_User_info_Read = true;
    if(code[0]&4==4) ua.Allow_Book_info_Delete = true;
    if(code[0]&2==2) ua.Allow_Book_info_Write = true;
    if(code[0]&1==1) ua.Allow_Book_info_Read = true;
}

// 写入掩码
void permission_load_mask(int mask[]){
    if(mask[3]&4==4) ua.Allow_Manage_Sys_Config = false;
    if(mask[3]&2==2) ua.Allow_Manage_User_Group = false;
    if(mask[3]&1==1) ua.Allow_Manage_Other_User_info = false;
    if(mask[2]&4==4) ua.Allow_Lending_Log_Delete = false;
    if(mask[2]&2==2) ua.Allow_Lending_Log_Write = false;
    if(mask[2]&1==1) ua.Allow_Lending_Log_Read = false;
    if(mask[1]&4==4) ua.Allow_User_info_Delete = false;
    if(mask[1]&2==2) ua.Allow_User_info_Write = false;
    if(mask[1]&1==1) ua.Allow_User_info_Read = false;
    if(mask[0]&4==4) ua.Allow_Book_info_Delete = false;
    if(mask[0]&2==2) ua.Allow_Book_info_Write = false;
    if(mask[0]&1==1) ua.Allow_Book_info_Read = false;
}

// 注销Agent
void ua_reset(){
    ua.Allow_Book_info_Read = false;
    ua.Allow_Book_info_Write = false;
    ua.Allow_Book_info_Delete = false;
    ua.Allow_User_info_Read = false;
    ua.Allow_User_info_Write = false;
    ua.Allow_User_info_Delete = false;
    ua.Allow_Lending_Log_Read = false;
    ua.Allow_Lending_Log_Write = false;
    ua.Allow_Lending_Log_Delete = false;
    ua.Allow_Manage_Other_User_info = false;
    ua.Allow_Manage_User_Group = false;
    ua.Allow_Manage_Sys_Config = false;
}

// 创建Agent
void ua_create(User *usr){
    ua_reset();
    permission_load_code(usr->permission);
    permission_load_mask(usr->mask);
}

void permission_check(int code){
    if(code==1) ;
    else if(code==0) printf("\n%s",ACCESS_DENIED);
}


/* 读取四位权限码（掩码）
 * ！如果特殊权限位为0，请不要传入，否则会被自动识别为八进制数字而造成错误
 * ！scanf输入的不会有这种问题
 * 如果权限码不规范，返回-1
 *
 * 使用方法：接受数字的整形变量名 = read_mask(掩码,位数);
 */
int read_mask(int mask,int bit){
    int output;
    switch(bit){
        case 0:
            output = mask/1000%10;
            break;
        case 1:
            output = mask/100%10;
            break;
        case 2:
            output = mask/10%10;
            break;
        case 3:
            output = mask/1%10;
            break;
        default:
            return -1;
    }
    if(output>=0&&output<=7) return output;
    else return -1;
}

/* 写入四位权限码（掩码）
 * 如果权限码不规范，返回-1
 *
 * 使用方法：接受数字的整形变量名 = write_mask(掩码数组);
 */
int write_mask(int mask[]){
    int code=0,i;
    for(i=0;i<4;i++){
        if(mask[i]>=0&&mask[i]<=7)
            code += mask[i]*mult10(3-i);
        else return -1;
    }
    return code;
}


void permission_echo(){
    if(ua.Allow_Manage_Sys_Config == false) printf("0 ");
    else printf("1 ");
    if(ua.Allow_Manage_User_Group == false) printf("0 ");
    else printf("1 ");
    if(ua.Allow_Manage_Other_User_info == false) printf("0 ");
    else printf("1 ");
    if(ua.Allow_Lending_Log_Delete == false) printf("0 "); else printf("1 ");
    if(ua.Allow_Lending_Log_Write == false) printf("0 "); else printf("1 ");
    if(ua.Allow_Lending_Log_Read == false) printf("0 "); else printf("1 ");
    if(ua.Allow_User_info_Delete == false) printf("0 "); else printf("1 ");
    if(ua.Allow_User_info_Write == false) printf("0 "); else printf("1 ");
    if(ua.Allow_User_info_Read == false) printf("0 "); else printf("1 ");
    if(ua.Allow_Book_info_Delete == false) printf("0 "); else printf("1 ");
    if(ua.Allow_Book_info_Write == false) printf("0 "); else printf("1 ");
    if(ua.Allow_Book_info_Read == false) printf("0 "); else printf("1 ");
    putchar('\n');
}