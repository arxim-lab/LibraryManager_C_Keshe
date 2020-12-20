
// Book status 状态列表
// 0  未就绪（新添加书籍，归还后尚未上架）
// 1  借出
// 2  在架
// -1 遗失（用户已挂失）

/* 获取特定书籍分类记录
 * SELECT * FROM bookshelf WHERE cid = ******;
 * 优先搜索ID，搜索分类名时请将ID赋0
 * 若没有搜索到对应的分类名，返回""或"\0"字符串
 *
 * 使用方法：书籍分类字符串 = bookshelf_get(书籍分类ID,书籍分类名);
 */
char * bookshelf_get(int cid){
    char *result,*sql_;
    result = string_trans("");
    int rc;
    if(cid!=0)
        sql_ = str_cat("SELECT * FROM bookshelf WHERE cid = ", num_to_str(cid), ";", NULL);\
    else
        return NULL;
    rc = db_exec(sql_,call_bookshelf,result);
    if(!rc) return NULL;
    return result;
}

/* 检查书籍分类是否存在
 * SELECT * FROM bookshelf WHERE cname = '******';
 *
 * 使用方法：bookshelf_check(书籍分类ID);
 */
int bookshelf_check(char *cname,int cid){
    char *sql_,*result;
    int rc;
    result = string_trans("");
    if(cname!=NULL){
        sql_ = str_cat("SELECT * FROM bookshelf WHERE cname = '",cname, "';", NULL);
        rc = db_exec(sql_,call_bookshelf,result);
    }else if(cid!=0)
        result = bookshelf_get(cid);
    else
        return false;
    if(strcmp(result,"\0")==0) return false;
    else return true;
}

/* 创建书籍分类记录
 * INSERT INTO bookshelf (cname) VALUES(******);
 *
 * 使用方法：bookshelf_sql_create(书籍分类名);
 */
int bookshelf_sql_create(char *cname){
    if(!ua.Allow_Book_info_Write) return -1;
    char *sql_;
    if(bookshelf_check(cname,0)) return 2;
    sql_ = str_cat("INSERT INTO bookshelf (cname) VALUES('",cname,"') ;",NULL);
    return db_exec(sql_,0,0);
}

/* 修改书籍分类记录
 * UPDATE bookshelf SET cname = '******' WHERE cid = ******;
 *
 * 使用方法：bookshelf_sql_edit（分类ID,分类名);
 */
int bookshelf_sql_edit(int cid,char *cname){
    if(!ua.Allow_Book_info_Write) return -1;
    char *sql_;
    if(!bookshelf_check(NULL,cid)) return 3;
    if(bookshelf_check(cname,0)) return 2;
    sql_ = str_cat("UPDATE bookshelf SET cname = '",cname,"' WHERE cid = ",num_to_str(cid)," ;",NULL);
    return db_exec(sql_,0,0);
}

/* 删除书籍分类记录
 * DELETE FROM bookshelf WHERE cid = ******;
 *
 * 使用方法：bookshelf_sql_delete(分类ID);
 */
int bookshelf_sql_delete(int cid){
    if(!ua.Allow_Book_info_Delete) return -1;
    char *sql_;
    if(!bookshelf_check(NULL,cid)) return 3;
    sql_ = str_cat("DELETE FROM bookshelf WHERE cid = ",num_to_str(cid),";",NULL);
    return db_exec(sql_,0,0);
}

/* 创建书籍结构体
 *
 * 使用方法：书籍名 = book_create(书名,分类ID,作者,出版社,ISBN码,价格,架号,位置号);
 */
Book * book_create(char *_bname,int _cid,char *_author,char *_press,char *_isbn,float _price,int _shelf,int _location){
    Book * output;
    output = (Book*)malloc(sizeof(Book));
    output->bname = string_trans(_bname);
    output->cid = _cid;
    output->author = string_trans(_author);
    output->press = string_trans(_press);
    output->isbn = string_trans(_isbn);
    output->shelf = _shelf;
    output->location = _location;
    output->price = _price;
    output->status = 0;
    output->add_time = tm_getnow();
    return output;
}

/* 书籍链表初始化
 *
 * 使用方法：书籍链表名 = result_book_init();
 */
Book_result * result_book_init(){
    Book_result *p1;
    p1 = (Book_result*)malloc(sizeof(Book_result));
    p1->u = NULL;
    p1->n = NULL;
    return p1;
}

/* 书籍链表销毁
 *
 * 使用方法：result_book_delete(书籍链表名);
 */
void result_book_delete(Book_result * init){
    Book_result * p;
    while(init!=NULL){
        p = init;
        init=init->n;
        free(p);
        p = NULL;
    }
}

/* 书籍信息初选
 * SELECT * FROM book WHERE bname = '******';
 *
 * 使用方法：书籍链表名 = book_query(书名);
 */
Book_result * book_query(char *bname){
    int rc;
    char *sql_;
    Book_result * data;
    data = result_book_init();
    sql_ = str_cat("SELECT * FROM book WHERE bname = '",bname,"' ;",NULL);
    rc = db_exec(sql_,call_book,data);
    if(!rc) return NULL;
    if(data->u==NULL) return NULL;
    return data;
}

/* 书籍信息二选
 * 书籍使用不同的摆放位置作为区分方式
 *
 * 使用方法：书籍变量名 = user(书籍ID,书籍链表名,架号，位置号);
 */
Book * book_get(int bid,Book_result *query_,int shelf,int location){
    int rc;
    char *sql_;
    Book_result * data;
    if(bid!=0){
        data = result_book_init();
        sql_ = str_cat("SELECT * FROM book WHERE bid = ",num_to_str(bid)," ;",NULL);
        rc = db_exec(sql_,call_book,data);
        if(!rc) return NULL;
        if(data->u==NULL) return NULL;
        return data->u;
    }
    data = query_;
    for(;data->n!=NULL;data=data->n)
        if(data->u->location==location&&data->u->shelf==shelf)
            break;
    return data->u;
}

/* 检查书籍是否存在
 *
 * 使用方法：book_check(书籍ID);
 */
int book_check(int bid,int shelf,int location){
    Book * rc=NULL;
    char * sql_;
    Book_result * data;
    if(bid!=0)
        rc = book_get(bid,NULL,0,0);
    else{
        data = result_book_init();
        sql_ = str_cat("SELECT * FROM book WHERE shelf = ",num_to_str(shelf)," AND location = ",num_to_str(location)," ;",NULL);
        db_exec(sql_,call_book,data);
        rc = data->u;
    }
    if(!rc) return false;
    else return true;
}

/* 创建书籍记录
 * 以书籍位置作为区分书籍的唯一凭据
 *
 * 使用方法：book_sql_create(书籍结构体);
 */
int book_sql_create(Book *new_b){
    if(!ua.Allow_Book_info_Write)
        return -1;
    char *sql_,*cid_,*add_time_,*price_,*shelf_,*location_;
    if(book_check(0,new_b->shelf,new_b->location)) return 2;
    cid_ = num_to_str(new_b->cid);
    price_ = float_to_str(new_b->price);
    add_time_ = num_to_str(mktime(new_b->add_time));
    shelf_ = num_to_str(new_b->shelf);
    location_ = num_to_str(new_b->location);
    sql_ = str_cat("INSERT INTO book (bname,cid,shelf,location,isbn,author,price,press,add_time,status,operator_id) VALUES ('",new_b->bname,"',",cid_,",",shelf_,",",location_,",'",new_b->isbn,"','",new_b->author,"',",price_,",'",new_b->press,"',",add_time_,", 0 ,",num_to_str(Login_User->uid),") ;",NULL);
    return db_exec(sql_,0,0);
}

/* 修改书籍记录
 * ！不能用于修改位置，书的状态
 *
 * 使用方法：book_sql_edit(书籍ID,要改的字段名,字段值);
 */
int book_sql_edit(int bid,char *key,char *value){
    if(!ua.Allow_Book_info_Write)
        return -1;
    char *sql_;
    int rc;
    if(!book_check(bid,0,0)) return 3;
    if(strcmp(key,"bname")==0)
        sql_ = str_cat("UPDATE book SET bname = '",value,"' WHERE bid = ",num_to_str(bid)," ;",NULL);
    else if(strcmp(key,"cid")==0)
        sql_ = str_cat("UPDATE book SET cid = ",value," WHERE bid = ",num_to_str(bid)," ;",NULL);
    else if(strcmp(key,"isbn")==0)
        sql_ = str_cat("UPDATE book SET isbn = '",value,"' WHERE bid = ",num_to_str(bid)," ;",NULL);
    else if(strcmp(key,"author")==0)
        sql_ = str_cat("UPDATE book SET author = '",value,"' WHERE bid = ",num_to_str(bid)," ;",NULL);
    else if(strcmp(key,"press")==0)
        sql_ = str_cat("UPDATE book SET press = '",value,"' WHERE bid = ",num_to_str(bid)," ;",NULL);
    else if(strcmp(key,"price")==0)
        sql_ = str_cat("UPDATE book SET price = ",value," WHERE bid = ",num_to_str(bid)," ;",NULL);
    else if(strcmp(key,"status")==0)
        sql_ = str_cat("UPDATE book SET status = ", value, " , operator_id = ",num_to_str(Login_User->uid),",operated_time = ",num_to_str(time_t_getnow())," WHERE bid = ", num_to_str(bid), " ;", NULL);
    else if(strcmp(key,"operator_id")==0)
        sql_ = str_cat("UPDATE book SET operator_id = ",value," WHERE bid = ",num_to_str(bid)," ;",NULL);
    else
        return 0;
    rc = db_exec(sql_,0,0);
    if(!rc) return 0;
    return 1;
}

// 书籍状态修改
// UPDATE book SET status = ****** ,operator_id = ******,operated_time = ****** WHERE bid = ******;
int book_status_edit(int bid,int sid,int status){
    if(!ua.Allow_Book_info_Write)
        return -1;
    char *sql_;
    int rc;
    long long op_time;
    op_time = time_t_getnow();
    sql_ = str_cat("UPDATE book SET status = ",num_to_str(status),",operator_id = ",num_to_str(sid),",operated_time = ",num_to_str(op_time),"WHERE bid = ",num_to_str(bid),";",NULL);
    rc = db_exec(sql_,0,0);
    return rc;
}

/* 修改书籍位置
 *
 * 使用方法：book_locale_edit(书籍ID,新架号,新位置号);
 */
int book_locale_edit(int bid,int shelf,int location){
    if(!ua.Allow_Book_info_Write)
        return -1;
    char *sql_,*shelf_,*location_,*bid_;
    int rc;
    if(!book_check(bid,0,0)) return 3;
    if(book_check(0,shelf,location)) return 2;
    shelf_ = num_to_str(shelf);
    location_ = num_to_str(location);
    bid_ = num_to_str(bid);
    sql_ = str_cat("UPDATE book SET shelf = ",shelf_,", location = ",location_," WHERE bid = ",bid_," ;",NULL);
    rc = db_exec(sql_,0,0);
    if(!rc) return 0;
    return 1;
}

/* 删除用户记录
 *
 * 使用方法：book_sql_delete(书籍ID);
 */
int book_sql_delete(int bid){
    if(!ua.Allow_Book_info_Delete)
        return -1;
    char *sql_;
    if(!book_check(bid,0,0)) return 3;
    sql_ = str_cat("UPDATE book SET status = -2 WHERE bid = ",num_to_str(bid),";",NULL);
    return db_exec(sql_,0,0);
}

/* 查询书籍记录
 *
 * 使用方法：book_sql_query(书籍链表名,书名,分类ID,作者,出版社);
 */
int book_sql_query(Book_result *result,char *bname,int cid,char *author,char *press,int showdel){
    if(!ua.Allow_Book_info_Read)
        return -1;
    int rc;
    char *sql_,*where;
    where = str_cat("WHERE bname LIKE '%",bname,"%' ",NULL);
    if(cid!=0)
        where = str_cat(where,"AND cid = ",num_to_str(cid)," ",NULL);
    if(author!="\0"&&author!=NULL)
        where = str_cat(where,"AND author LIKE '%",author,"%' ",NULL);
    if(press!=NULL&&press!="\0")
        where = str_cat(where,"AND press LIKE '%",press,"%' ",NULL);
    if(showdel==0)
        where = str_cat(where,"AND status != -2 ",NULL);
    sql_ = str_cat("SELECT * FROM book ",where,";",NULL);
    rc = db_exec(sql_,call_book,result);
    return rc;
}
