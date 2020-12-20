
/* 用户组信息读取回调
 *
 * 么得使用方法
 */
int call_usergroup(void *data, int rows, char **values, char **keys){
    UserGroup_result *p1,*init;
    UserGroup * output;
    int i,tmp;
    init = (UserGroup_result *)data;
    for(;init->n!=NULL;init=init->n)
        continue;
    output = (UserGroup*)malloc(sizeof(UserGroup));
    for(i=0;i<rows;i++){
        if(!strcmp(keys[i],"gid")) output->gid = str_to_num(values[i]);
        if(!strcmp(keys[i],"gname")) output->gname = string_trans(values[i]);
        if(!strcmp(keys[i],"permission")){
            tmp = str_to_num(values[i]);
            output->permission[0] = read_mask(tmp,0);
            output->permission[1] = read_mask(tmp,1);
            output->permission[2] = read_mask(tmp,2);
            output->permission[3] = read_mask(tmp,3);
        }
    }
    init->u = output;
    p1 = (UserGroup_result*)malloc(sizeof(UserGroup_result));
    p1->n = NULL;
    init->n = p1;
    return 0;
}

/* 用户信息读取回调
 *
 * 么得使用方法
 */
int call_user(void *data, int rows, char **values, char **keys){
    User_result *p1,*init;
    User * output;
    int i,tmp;
    init = (User_result *)data;
    for(;init->n!=NULL;init=init->n)
        continue;
    output = (User*)malloc(sizeof(User));
    for(i=0;i<rows;i++){
        if(!strcmp(keys[i],"uid")) output->uid = str_to_num(values[i]);
        if(!strcmp(keys[i],"uname")) output->uname = string_trans(values[i]);
        if(!strcmp(keys[i],"IsMale")) output->IsMale = str_to_num(values[i]);
        if(!strcmp(keys[i],"reg_time")) output->reg_time = tm_get(str_to_num(values[i]));
        if(!strcmp(keys[i],"sid")) output->sid = str_to_num(values[i]);
        if(!strcmp(keys[i],"gid")) output->gid = str_to_num(values[i]);
        if(!strcmp(keys[i],"mask")){
            tmp = str_to_num(values[i]);
            output->mask[0] = read_mask(tmp,0);
            output->mask[1] = read_mask(tmp,1);
            output->mask[2] = read_mask(tmp,2);
            output->mask[3] = read_mask(tmp,3);
        }
    }
    init->u = output;
    p1 = (User_result*)malloc(sizeof(User_result));
    p1->n = NULL;
    init->n = p1;
    return 0;
}

/* 用户密码读取回调
 *
 * 么得使用方法
 */
int call_password(void *data, int rows, char **values, char **keys){
    int i;
    char * tmp;
    for(i=0;i<rows;i++){
        if(!strcmp(keys[i],"password")){
            tmp = string_trans(values[i]);
        }
    }
    data = (char*)realloc(data,sizeof(char)*strlen(tmp));
    strcpy(data,tmp);
    return 0;
}

// 书籍分类信息读取回调
int call_bookshelf(void *data, int rows, char **values, char **keys){
    int i;
    char * tmp;
    for(i=0;i<rows;i++){
        if(!strcmp(keys[i],"cname")){
            tmp = string_trans(values[i]);
        }
    }
    data = (char*)realloc(data,sizeof(char)*strlen(tmp));
    strcpy(data,tmp);
    return 0;
}

// 书籍信息读取回调
int call_book(void *data, int rows, char **values, char **keys){
    Book_result *p1,*init;
    Book * output;
    int i;
    init = (Book_result *)data;
    for(;init->n!=NULL;init=init->n)
        continue;
    output = (Book*)malloc(sizeof(Book));
    for(i=0;i<rows;i++){
        if(!strcmp(keys[i],"bid")) output->bid = str_to_num(values[i]);
        if(!strcmp(keys[i],"cid")) output->cid = str_to_num(values[i]);
        if(!strcmp(keys[i],"shelf")) output->shelf = str_to_num(values[i]);
        if(!strcmp(keys[i],"location")) output->location = str_to_num(values[i]);
        if(!strcmp(keys[i],"bname")) output->bname = string_trans(values[i]);
        if(!strcmp(keys[i],"isbn")) output->isbn = string_trans(values[i]);
        if(!strcmp(keys[i],"author")) output->author = string_trans(values[i]);
        if(!strcmp(keys[i],"press")) output->press = string_trans(values[i]);
        if(!strcmp(keys[i],"price")) output->price = str_to_float(values[i]);
        if(!strcmp(keys[i],"status")) output->status = str_to_num(values[i]);
        if(!strcmp(keys[i],"operator_id")) output->operator_id = str_to_num(values[i]);
        if(!strcmp(keys[i],"add_time")) output->add_time = tm_get(str_to_num(values[i]));
        if(!strcmp(keys[i],"operated_time")) output->operated_time = tm_get(str_to_num(values[i]));
    }
    init->u = output;
    p1 = (Book_result*)malloc(sizeof(Book_result));
    p1->n = NULL;
    init->n = p1;
    return 0;
}
