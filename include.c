
/* 基础模块加载 */
#include "library/encrypt.c"              // 加载数据加解密模块
#include "library/str.c"                  // 加载字符串模块
#include "library/datetime.c"             // 加载时间处理模块
#include "library/interface.c"            // 加载显示模块
#include "library/sqlite.c"               // 加载SQLite数据库操作模块
#include "library/config_read.c"          // 加载配置文件读取模块
#include "library/sort.c"                 // 加载数据排序模块

/* 数据处理模块加载 */
#include "module/permission.c"            // 加载权限控制器
#include "module/callback.c"              // 加载回调函数
#include "module/mgr_user.c"              // 加载用户管理器
#include "module/mgr_bookshelf.c"         // 加载书架管理器
