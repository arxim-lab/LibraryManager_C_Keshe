
/* 回调函数示例 */

//int call(void *data, int rows, char **values, char **keys){
//    printf("%s yes",(char*)data);
//    int i;
//    for(i=0;i<argc;i++)
//        printf("\n%s %s",keys[i],values[i]);
//    return 0;
//}

/* 官方手册：https://www.sqlite.org/capi3ref.html
 * 库使用：https://blog.csdn.net/QIJINGBO123/article/details/86663902
 * 错误代码：https://www.sqlite.org/rescode.html
 * 菜鸟教程：https://www.runoob.com/sqlite/sqlite-c-cpp.html
 */

/* 数据库：连接
 * https://www.sqlite.org/c3ref/open.htmlhttps://www.sqlite.org/capi3ref.html
 */
int db_connect(){
    int rc;
    rc = sqlite3_open(db_link,&mydb);
    if(Debug_mode&&rc)
        sqlite3_errmsg(mydb);
    return rc;
}

/* 数据库：断开连接
 * https://www.sqlite.org/c3ref/close.html
 */
int db_disconnect(){
    int rc;
    rc = sqlite3_close(mydb);
    if(Debug_mode&&rc)
        sqlite3_errmsg(mydb);
    return rc;
}

/* 数据库：执行操作
 * https://blog.csdn.net/u012351051/article/details/90382391
 * https://blog.myzony.com/sqlite3_exec-han-shu-yin-fa-de-xie-an/
 *
 * 使用方法：db_exec(SQL语句,回调函数名,传入指针名);
 */
bool db_exec(const char *sql,int (*callback)(void*,int,char**,char**),void* data){
    int rc=0;
    rc = sqlite3_exec(mydb,sql,callback,(void*)data,&sql_errmsg);
    if(rc&&Debug_mode)
        printf("\nSQLite3_DEBUG_ERROR %d: %s\n",rc,sql_errmsg);
    sqlite3_free(sql_errmsg);
    if(rc) return false;
    else return true;
}

/* 数据库：初始化
 *
 * 使用方法：db_init();
 */
bool db_init(){
    bool rc;
    rc = db_exec(sql_init,0,0);
    return rc;
}
