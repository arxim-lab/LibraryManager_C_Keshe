
/* 系统设置界面函数 */
void show_syscfg(){
    interface_create("系统备份",true);
    if(!confirm("是否进行系统备份？")) {
        interface_delete(false);
        return;
    }
    char *cmd;
    db_disconnect();
    if(IsLinux)
        cmd = str_cat("cp '",db_link,"' 'backup.db'",NULL);
    else
        cmd = str_cat("copy '",db_link,"' 'backup.db'",NULL);
    system(cmd);
    alert("数据文件备份完成！文件被保存为 backup.db");
    interface_delete(false);
}
