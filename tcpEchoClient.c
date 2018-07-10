/*
 * @Author: LQT
 * @Date: 2018-07-10 14:43:09
 * @LastEditors: LQT
 * @LastEditTime: 2018-07-10 17:25:30
 * @Description: 
 */
#include<uv.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define DEFAULT_BACKLOG 128
#define DEFAULT_PORT 7000
uv_loop_t *loop;
typedef struct{
    uv_write_t req;
    uv_buf_t buf;
}write_req_t;


void free_write_req(uv_write_t *req){
    write_req_t *wr=(write_req_t*)req;
    free(wr->buf.base);
    free(wr);
    return;
}

void alloc_buffer(uv_handle_t *handle,size_t suggested_size,uv_buf_t *buf){
    buf->base=(char*)malloc(suggested_size);
    buf->len=suggested_size;
    return;
}

void echo_write(uv_write_t *req,int status){
    if(status){
        fprintf(stderr,"write error%s\n",uv_strerror(status));
    }
    free_write_req(req);
    return;
}

void echo_read(uv_stream_t *client,ssize_t nread,const uv_buf_t *buf){
    if(nread>0){
        printf("%s",buf->base);
    }
    return;
}


void on_connect(uv_connect_t *connect,int status){
    uv_tcp_t *client=(uv_tcp_t*)malloc(sizeof(uv_tcp_t));
    client=(uv_tcp_t*)connect->handle;
    uv_tcp_init(loop,client);
    
    char input;
    scanf("%s",&input);
    write_req_t *req=(write_req_t*)malloc(sizeof(write_req_t));
    req->buf=uv_buf_init(&input,sizeof(input));
    uv_write((uv_write_t*)req,client,&req->buf,1,echo_write);
    return;
}
int main(){
    loop=uv_default_loop();
    uv_tcp_t *socket=(uv_tcp_t*)malloc(sizeof(uv_tcp_t));
    uv_tcp_init(loop,socket);
    uv_connect_t* connect=(uv_connect_t*)malloc(sizeof(uv_connect_t));
    struct sockaddr_in dest;
    uv_ip4_addr("127.0.0.1",80,&dest);
    uv_tcp_connect(connect,socket,(const struct sockaddr*)&dest,on_connect);
    return uv_run(loop,UV_RUN_DEFAULT); 
    
}