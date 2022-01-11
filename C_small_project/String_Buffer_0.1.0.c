#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <lmsvc.h>

//结构体定义
int sz;
struct strbuf {
    int len;     //当前缓冲区（字符串）长度
    int alloc;   //当前缓冲区（字符串）容量
    char *buf;   //缓冲区（字符串）
};



static inline size_t strbuf_avail(const struct strbuf *sb){
    if(sb -> len < sb -> alloc){
        return (sb -> alloc) - (sb -> len);
    }
    else{
        return 0;
    }
}



void show_all_attr(struct strbuf *sb){
    printf("string is:");
    for(int i = 0 ; i < sb -> len ;i++){
        printf("%c",*(sb -> buf + i));
    }
    printf("\n");
    printf("len is: %d \ncapacity is:%d\nSpace reserve:%d\n",sb -> len,sb -> alloc,strbuf_avail(sb));
}


void strbuf_init(struct strbuf *sb, size_t alloc){
    sb -> buf = (char*)calloc(alloc,sizeof(char));
    sb -> len = 0;
    sb -> alloc = alloc;
}



void strbuf_attach(struct strbuf *sb, void *str, size_t len, size_t alloc){
    //不用考虑是否已经初始化，容量够不够，因为这里task要求属于第一部分的简单操作，不涉及扩容
    if(alloc < len) {
        printf("error");
        return;
    }
    sb -> buf = (char*)calloc(alloc,sizeof(char));
    sb -> len = len;
    sb -> alloc = alloc;
    for(int i = 0 ; i < len ; i++){
        *((sb -> buf)+i) = (char)(*(char*)(str+i));
    }
}



void strbuf_release(void *sb){
    free(sb+8);
    free(sb);
}



void strbuf_swap(struct strbuf *a, struct strbuf *b){
    struct strbuf temp;
    temp = *a;
    (*a).len = b -> len;
    (*a).alloc = b -> alloc;
    (*a).buf = b -> buf;

    (*b).len = temp.len;
    (*b).alloc = temp.alloc;
    (*b).buf = temp.buf;
    //strbuf_release(&temp);
}



char *strbuf_detach(struct strbuf *sb, size_t *sz){
    *sz = sb -> len;
    return sb -> buf;
}



int strbuf_cmp(const struct strbuf *first, const struct strbuf *second){
    if(first -> len != second -> len){
        return 0;
    }
    else{
        if(!strcmp(first->buf,second->buf)){
            return 1;
        }
        return 0;
    }
}



void strbuf_reset(struct strbuf *sb){
    for(int i = 0 ; i < sb -> len;i++){
        *((sb -> buf)+i) = '\0';
    }
    sb -> len = 0;
}



void strbuf_grow(struct strbuf *sb,size_t len){//利用了vector增长的思想
    //但是增长多少由len决定，调用的时候一般会传入sb->alloc达到双倍目的
    printf("oversize\n____auto-grow_____\nfrom %d to %d\n",sb -> alloc,sb -> alloc + len);
    char *a;
    a = calloc(sb->alloc + len,sizeof(char));
    for(int i = 0 ; i < sb->len;i++){
        *(a+i) = *((sb -> buf)+i);//赋值
    }
    free(sb -> buf);//free以前开辟的空间
    sb -> buf = a;//更新地址
    sb -> alloc += len;//更新容量
}



void strbuf_add(struct strbuf *sb,const void *data,size_t len){//后面很多函数都基于这个实现
    if(sb -> alloc <= sb -> len + len){//原有容量不足
        while(sb -> len + len >= sb -> alloc){//增长到能存下原有len以及新增len为止
            strbuf_grow(sb,sb -> alloc);
        }
        for(int i = sb -> len;i < sb -> len + len  ;i++){//拷贝
            *(sb -> buf + i) = *((char *)data + (i - sb -> len));
        }
        sb -> len += len;//更新len
    }
    else{//原有充足
        for(int i = sb -> len; i< sb->len + len;i++){
            *(sb -> buf + i) = *((char*)data + (i - sb -> len));
        }
        sb -> len += len;//更新len
    }
}



void strbuf_addch(struct strbuf *sb,int c){
    char* a =&c;
    strbuf_add(sb,a,1);
}



void strbuf_addstr(struct strbuf *sb,const char *s){
    strbuf_add(sb,s,strlen(s));
}



void strbuf_addbuf(struct strbuf *sb,const struct strbuf *sb2 ){
    strbuf_addstr(sb,sb2->buf);
}



static inline void strbuf_setlen(struct strbuf *sb, size_t len){
    if(sb -> len + len < sb -> alloc){
        for(int i = sb -> len; i < sb -> len + len;i++){
            *((sb -> buf)+i) = ' ';
        }
        sb -> len += len;
    }
    else{
        while(sb -> len + len >= sb -> alloc){//增长到能存下原有len以及新增len为止
            strbuf_grow(sb,sb -> alloc);
        }
        for(int i = sb -> len; i < sb -> len + len;i++){
            *((sb -> buf)+i) = ' ';
        }
        sb -> len += len;
    }
}



void strbuf_insert(struct strbuf *sb, size_t pos, const void *data, size_t len){
    if(pos > sb -> len){//分两种情况，1.pos越过len
        sb -> len = pos + len;
    }
    else{//分两种情况，2.位置没越过len
        sb -> len += len;
    }


    char *temp = (char*)calloc(len,sizeof(char));
    if(pos < sb -> len -len){//分两种情况，1.越过len，原有内容不移动则if不生效    2.pos没越过len，需要拷贝，if生效
        for(int i = 0 ; i < sb -> len ; i++){
            *(temp + i) = *((sb -> buf) + pos +i);//拷贝被迫后移的元素
        }
    }


    if(sb -> len <= sb -> alloc){
        if(pos < sb -> len -len){//分两种情况，1.越过len，原有内容不移动则if不生效    2.pos没越过len，需要拷贝，if生效
            for(int j = pos; j < sb -> len; j++){
                *((sb -> buf) + j + len) = *(temp + j - pos);//粘贴被后移元素
            }
        }
        for(int k = 0; k < len ; k++){
            *((sb -> buf)+pos+k) = *((char*)data + k);//指定位置插入数据
        }
    }
    else{
        while(sb -> len  >= sb -> alloc){//增长到能存下原有len以及新增len为止
            strbuf_grow(sb,sb -> alloc);
        }
        for(int j = pos; j < sb -> len; j++){
            *((sb -> buf) + j + len) = *(temp + j - pos);//粘贴被后移元素
        }
        for(int k = 0; k < len ; k++){
            *((sb -> buf)+pos+k) = *((char*)data + k);//指定位置插入数据
        }
    }


    free(temp);
}



void strbuf_rtrim(struct strbuf *sb){
    int flag = 0 ;
    char *temp  = (char*)calloc(sb -> alloc,sizeof(char));
    for(int i = 0;i < sb -> len; i++){
        if(*(sb -> buf + i ) != ' '&&*(sb -> buf + i ) != '\t'&&*(sb -> buf + i ) != ' '){
            *(temp + flag) = *(sb -> buf + i);
            flag++;
        }
    }
    free(sb -> buf);
    sb -> buf = temp;
    sb -> len = flag;
}



void strbuf_ltrim(struct strbuf *sb){
    for(int i = sb -> len;i < sb -> alloc; i++){
        if(*(sb -> buf + i ) != ' '||*(sb -> buf + i ) || '\t'&&*(sb -> buf + i ) != ' '||*(sb -> buf + i ) != '\0'){
            *(sb -> buf + i) ='\0';
        }
    }
}



void strbuf_remove(struct strbuf *sb, size_t pos, size_t len){
    if(pos+1+len>sb -> len){
        printf("Error");
        return;
    }
    int flag = 0;
    char *temp  = (char*)calloc(sb -> alloc,sizeof(char));
    for(int i = pos;i<pos + len;i++){
        *(sb -> buf + i) = '\0';
    }
    for(int i = 0 ; i < sb -> len;i++){
        if(*(sb -> buf + i)!='\0'){
            *(temp+flag) = *(sb -> buf + i);
            flag++;
        }
    }
    free(sb -> buf);
    sb -> buf = temp;
    sb -> len = flag;

}



ssize_t strbuf_read(struct strbuf *sb, int fd, size_t hint){
    int c;
    strbuf_grow(sb,(hint ? hint : 8192));
    while ((c = getc(fd)) != EOF){
        strbuf_addch(sb,c);
    }
}



ssize_t strbuf_read_file(struct strbuf *sb, const char *path, size_t 提示){
    int fp,c;
    fp = fopen(path,'r');
    while ((c = getc(fp)) != EOF){
        strbuf_addch(sb,c);
    }
}



int strbuf_getline(struct strbuf *sb, FILE *fp){
    int c;
    while ((c = getc(fp)) != EOF){
        strbuf_addch(sb,c);
    }
}



void test_strbuf_cmp(){
    struct strbuf a;
    struct strbuf b;
    strbuf_attach(&a,"xiyou", 5, 8);
    strbuf_attach(&b,"xiyou", 5, 8);
    int flag = strbuf_cmp(&a,&b);
    printf("%d",flag);
}
void test_strbuf_reset(){
    struct strbuf a;
    strbuf_attach(&a,"xiyou", 5, 8);
    strbuf_reset(&a);
    show_all_attr(&a);
}
void test_strbuf_grow(){
    struct strbuf a;
    strbuf_attach(&a,"xiyou", 5, 8);
    strbuf_grow(&a,20);
    show_all_attr(&a);
}
void test_strbuf_add(){
    struct strbuf a;
    strbuf_attach(&a,"xiyou", 5, 8);
    strbuf_add(&a,"sa",2);
    show_all_attr(&a);
}
void test_strbuf_addch(){
    struct strbuf a;
    strbuf_attach(&a,"xiyou", 5, 8);
    strbuf_addch(&a,'b');
    show_all_attr(&a);
}
void test_strbuf_addstr(){
        struct strbuf a;
        strbuf_attach(&a,"xiyou", 5, 8);
        strbuf_addstr(&a,"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
        show_all_attr(&a);
};
void test_over_size(){
    printf("strbuf_addch and strbuf_add oversize test\n");
    struct strbuf a;
    strbuf_attach(&a,"xiyou", 5, 5);
    strbuf_addch(&a,'b');
    show_all_attr(&a);
}
void test_strbuf_addbuf(){
    struct strbuf a;
    struct strbuf b;
    strbuf_attach(&a,"xiyou", 5, 7);
    strbuf_attach(&b,"1234567890", 10, 10);
    strbuf_addbuf(&a,&b);
    show_all_attr(&a);
}
void test_strbuf_setlen(){
    struct strbuf a;
    strbuf_attach(&a,"xiyou", 5, 10);
    strbuf_setlen(&a,10);
    show_all_attr(&a);
}
void test_strbuf_avail(){
    struct strbuf a;
    strbuf_attach(&a,"xiyou", 5, 5);
    printf("%d",strbuf_avail(&a));
    show_all_attr(&a);
}
void test_strbuf_insert(){
    struct strbuf a;
    strbuf_attach(&a,"xiyou", 5, 6);
    strbuf_insert(&a,3,"123",3);
    show_all_attr(&a);
//    struct strbuf a;          bug?????????????
//    strbuf_attach(&a,"xiyou", 5, 8);
//    strbuf_insert(&a,2,"1234567",7);
//    show_all_attr(&a);
}
void test_strbuf_ltrim(){//稍微利用一下那个bug
    struct strbuf a;
    strbuf_attach(&a,"xiyou", 5, 6);
    strbuf_insert(&a,3,"123",3);
    strbuf_ltrim(&a);
    show_all_attr(&a);
}
void test_strbuf_rtrim(){
    struct strbuf a;
    strbuf_attach(&a,"x i y o u", 9, 10);
    strbuf_rtrim(&a);
    show_all_attr(&a);
}
void test_strbuf_remove(){
    struct strbuf a;
    strbuf_attach(&a,"x i y o u", 9, 10);
    strbuf_rtrim(&a);
    strbuf_remove(&a,1,2);
    show_all_attr(&a);
}
int main(){

}
