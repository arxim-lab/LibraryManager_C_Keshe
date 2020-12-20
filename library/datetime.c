
// https://blog.csdn.net/gaoshangdemao/article/details/80910062
// https://www.runoob.com/cprogramming/c-standard-library-time-h.html

/* 时间：获取当前时间(time_t格式）
 *
 * 使用方法：time_t变量名 = time_t_getnow();
 */
time_t time_t_getnow(){
    time_t now;
    time(&now);
    return now;
}

/* 时间：获取当前时间（tm格式）
 *
 * 使用方法：tm变量名 = tm_getnow();
 */
tm tm_getnow(){
    time_t now;
    time(&now);
    return localtime(&now);
}

/* 时间：提取存储日期时间
 *
 * 使用方法：tm变量名 = tm_get(时间数字);
 */
tm tm_get(long time){
    time_t ti;
    ti = (time_t)time;
    return localtime(&ti);
}

/* 时间：输出时间
 *
 * 使用方法：tm_print(tm变量名,格式字符串名);
 */
void tm_print(tm time,char *format){
    char echo[80];
    strftime(echo,80,format,time);
    printf("%s",echo);
}
