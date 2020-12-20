
/* 书籍单属性信息排序
 * 我觉得只做这个就够了
 *
 * 使用方法：result_book_single_sort(需要排序的书籍链表,是否按降序排列);
 */
void result_book_single_sort(Book_result *data,bool IsReverse){
    Book * tmp;
    Book_result *p1,*p2,*min;
    p1 = p2 = data;
    for(;p1->n!=NULL;p1=p1->n){
        min = p1;
        for(p2=p1->n;p2->n!=NULL;p2=p2->n){
            if(!IsReverse){
                if(strcmp(p2->u->bname,min->u->bname)<0){
                    min = p2;
                }
            }else{
                if(strcmp(p2->u->bname,min->u->bname)>0){
                    min = p2;
                }
            }
        }
        tmp = min->u;
        min->u = p1->u;
        p1->u = tmp;
    }
}

/* 书籍多属性信息排序
 * 我觉得只做这个就够了
 *
 * 使用方法：result_book_multi_sort(需要排序的书籍链表,是否按降序排列);
 */
void result_book_multi_sort(Book_result *data,bool IsReverse){
    Book * tmp;
    Book_result *p1,*p2,*min;
    for(p1=data;p1->n!=NULL;p1=p1->n){
        min = p1;
        for(p2=p1->n;p2->n!=NULL;p2=p2->n)
            if(!IsReverse){
                if(p2->u->cid<min->u->cid)
                    min = p2;
            }else{
                if(p2->u->cid>min->u->cid)
                    min = p2;
            }
        tmp = min->u;
        min->u = p1->u;
        p1->u = tmp;
    }
    for(p1=data;p1->n!=NULL;p1=p1->n){
        min = p1;
        for(p2=p1->n;p2->u->cid==p1->u->cid;p2=p2->n)
            if(!IsReverse){
                if(strcmp(p2->u->bname,min->u->bname)<0)
                    min = p2;
            }else{
                if(strcmp(p2->u->bname,min->u->bname)>0)
                    min = p2;
            }
        tmp = min->u;
        min->u = p1->u;
        p1->u = tmp;
    }
}
