/*
 * @Author: LQT
 * @Date: 2018-07-06 20:23:06
 * @LastEditors: LQT
 * @LastEditTime: 2018-07-06 20:37:59
 * @Description: 
 */
#include<stdio.h>
#include<uv.h>
int64_t count=0;
void waitForAWile(uv_idle_t *hadle){
    count++;
    if(count>=10e6){
        uv_idle_stop(hadle);
    }
}
int main(){
    uv_idle_t idle;
    uv_idle_init(uv_default_loop(),&idle);
    uv_idle_start(&idle,waitForAWile);
    printf("Idling...\n");
    uv_run(uv_default_loop(),UV_RUN_DEFAULT);
    uv_loop_close(uv_default_loop());
    return 0;
}