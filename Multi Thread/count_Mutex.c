#include<stdio.h>
#include<pthread.h>
pthread_mutex_t count_mutex;
long long count = 0;
void* count_thread(void * arg){
    long long n=*((long long*)arg);
    pthread_mutex_lock(&count_mutex);
    for (long long i = 0; i < n/2; i++) {
            count++;
    }
    pthread_mutex_unlock(&count_mutex);

    return NULL;
}
int main(){
    long long n=1000000;
    pthread_t thread1,thread2;
    pthread_mutex_init(&count_mutex,NULL);
    pthread_create(&thread1,NULL,count_thread,&n);
    pthread_create(&thread2,NULL,count_thread,&n);
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    printf("%lld",count);
    return 0;
}