
void table_print_book(Book_result *result,th *header){
    tl * tl1;
    for(;result->n!=NULL;result=result->n){
        tl1 = tl_classify(6,num_to_str(result->u->bid),result->u->bname,bookshelf_get(result->u->cid),result->u->author,result->u->press,result->u->isbn,num_to_str(result->u->status));
        table_print_line(header,tl1);
        tl_free(tl1);
    }
}

/* 书籍条目管理操作 (修改、删除) */
void show_book_edit(int _uid){
    interface_create("书籍信息编辑",true);
    Book * actor;
    int action=1,__num,err=1;
    char *val;
    actor = book_get(_uid,NULL,0,0);
    if(actor==NULL) err_catch(0);
    printf("\n========书籍信息=========\n");
    printf("  书名：%s\n  分类：%s\n  作者：%s\n出版社：%s\n  ISBN：%s",actor->bname,bookshelf_get(actor->cid),actor->author,actor->press,actor->isbn);
    hr(24,'=');
    if(ua.Allow_Book_info_Delete){
        printf("请选择你要进行的操作：\n[ 1 ] 编辑\n");
        printf("[ 2 ] 删除\n");
        action = num_check(0, 1, 2);
    }
    switch(action){
        case 2:
            if(confirm("确认要删除吗？该操作不可逆！"))
                book_sql_delete(_uid);
            break;
        case 1:
            printf("请选择你要编辑的字段：\n");
            action = menu_show_str(4,"书名","分类ID","作者","出版社");
            printf("请输入修改后的值：");
            switch(action){
                case 1:
                    val = string_create();
                    err = book_sql_edit(actor->bid,"bname",val);
                    break;
                case 2:
                    __num = num_check(0,0,0);
                    err = book_sql_edit(actor->bid,"cid",num_to_str(__num));
                    break;
                case 3:
                    val = string_create();
                    err = book_sql_edit(actor->bid,"author",val);
                    break;
                case 4:
                    val = string_create();
                    err = book_sql_edit(actor->bid,"press",val);
            }
            if(err_catch(err))
                alert("修改成功！");
            interface_delete(false);
    }
}

/* 书籍查询 */
void show_book_query(){
    interface_create("书籍查询管理",true);
    Book_result * _result;
    _result = result_book_init();
    int _sid=0,_gid=0,_IsMale=-1,get_ugr,_uid=0,showdel=0;
    char *_bname="\0",*_aut="\0",*_pre="\0";

// 书籍查询界面输出
    printf("\n========请设置查找关键词========\n");
    if(confirm("是否将书名设置为搜索属性？")){
        printf("  书名: ");
        _bname = string_create();
    }
    if(confirm("是否将作者设置为搜索属性？")){
        printf("  作者: ");
        _aut = string_create();
    }
    if(confirm("是否将出版社设置为搜索属性？")){
        printf("出版社: ");
        _pre = string_create();
    }
    if(ua.Allow_Book_info_Delete) {
        if(confirm("是否显示被删除书籍？"))
            showdel = 1;
    }
    if(!confirm("是否开始搜索？")){
        interface_delete(false);
        result_book_delete(_result);
        return;
    }
    book_sql_query(_result,_bname,0,_aut,_pre,showdel);
    result_book_multi_sort(_result,true);

// 书籍搜索结果输出
    interface_create("书籍搜索结果",true);
    th *th1;
    int th_width[]={3,12,12,12,12,10,6};
    th1 = th_classify(7,th_width,"Bid","Bookname","BookClass","Author","Press","ISBN","Status");
    table_print_header(th1);
    table_print_book(_result,th1);
    th_free(th1);
    hr(20,'=');
    if(ua.Allow_Book_info_Write) {
        printf("请输入你想操作的书籍ID: ");
        _uid = num_check(0, 0, 0);
        show_book_edit(_uid);
    }else
        alert("搜索完毕，即将返回主菜单！");

// 回退主菜单
    interface_delete(false);
    result_book_delete(_result);
}

/* 书籍添加 */
void show_book_add(){
    interface_create("书籍添加",true);
    char *bname_=NULL,*_aut,*_pre,*_isbn;
    float pric_;
    Book * new_one;
    int cid_,add_time,err=1,loca_,shel_;
    printf("请输入新书信息：\n");
    printf("  书名: ");
    bname_ = string_create();
    printf("  分类: ");
    cid_ = num_check(0,0,0);
    printf("  作者: ");
    _aut = string_create();
    printf("出版社: ");
    _pre = string_create();
    printf("  ISBN: ");
    _isbn = string_create();
    printf("  售价: ");
    pric_ = str_to_float(string_create());
    add_time = 0;
    printf("  架号: ");
    shel_ = num_check(0,0,0);
    printf("位置号: ");
    loca_ = num_check(0,0,0);
    new_one = book_create(bname_,cid_,_aut,_pre,_isbn,pric_,shel_,loca_);
    err = book_sql_create(new_one);
    if(err_catch(err))
        alert("创建成功！");
    interface_delete(false);
}

// 书籍的借、还、挂失
// Book status 状态列表
// 0  未就绪（新添加书籍，归还后尚未上架）
// 1  借出
// 2  在架
// -1 遗失（用户已挂失）
// -2 被删除
void show_book_borrow(){
    interface_create("书籍借还",true);
    int err=1,bid_,_status,status,op_sid;
    long long tt;
    Book * sel;
    User * opr;
    User_result *rec;
    printf("请输入需要操作的书籍ID:");
    bid_ = num_check(0,0,0);
    if(!book_check(bid_,0,0)) {
        alert("所选书不存在！");
        interface_delete(false);
        return;
    }
    sel = book_get(bid_,NULL,0,0);
    _status = sel->status;
    switch(_status) {
        case 0:
            if(confirm("这本书尚未上架，是否上架？"))
                status = 1;
            break;
        case 1:
            if(confirm("这本书已经被借走，是否遗失？"))
                status = -1;
            else if(confirm("这本书已经被借走，是否归还这本书？"))
                status = 0;
            break;
        case 2:
            if(confirm("这本书目前在架，是否出借？"))
                status = 2;
            break;
        case -2:
            if(confirm("这本书已被删除，是否撤销删除？"))
                status = 1;
        case -1:
            if(confirm("这本书已经被挂失了，是否归还？"))
                status = 0;
    }
    switch(status){
        case 0:
            opr = user_get(sel->operator_id,NULL,0);
            tt = time_t_getnow();
            book_sql_edit(bid_,"status","0");
            if(difftime((time_t)tt,timelocal(sel->operated_time))>5184000.0) {    // 归还超时
                user_sql_edit(opr, "mask", "0700");
                alert("该用户归还超时，账户已被停用，请至前台管理员处办理解封手续！");
            }else{
                alert("归还成功！");
            }
            break;
        case 1:
            book_sql_edit(bid_,"status","1");
            alert("上架成功！");
            break;
        case 2:
            printf("请输入借阅读者SID:");
            op_sid = num_check(0,0,0);
            while(true){
                rec = user_query(op_sid);
                if(rec==NULL)
                    printf("该用户不存在，请输入正确的SID: ");
                else if(write_mask(user_get(0,rec,GID_READERS)->mask)==700)
                    printf("该用户已被封禁，请输入正确的SID: ");
                else
                    break;
                result_user_delete(rec);
                op_sid = num_check(0,0,0);
            }
            book_sql_edit(bid_,"status","1");
            book_sql_edit(bid_,"operator_id",num_to_str(op_sid));
            alert("借阅成功！");
            break;
        case -1:
            book_sql_edit(bid_,"status","-1");
            alert("挂失成功！");
    }
    interface_delete(false);
}

/* 书籍分类添加 */
void show_bookshelf_add(){
    interface_create("书籍分类添加",true);
    char *gname_;
    int err=1;
    printf("请输入新分类信息：\n");
    printf("分类名: ");
    gname_ = string_create();
    err = bookshelf_sql_create(gname_);
    if(err_catch(err))
        alert("创建成功！");
    interface_delete(false);
}
