#include <stdio.h>
#include <time.h>
#include<pthread.h>
long long no_thread(long long n) {
    long long count = 0;
    for (long long i = 0; i < n; i++) {
        if (i % 2 != 0) {
            count++;
        }
    }
    return count;
}
void* count_thread(void * argvs){
    long long count = 0;
    long long n=*((long long*)argvs);
    for (long long i = 0; i < n; i++) {
            count++;
    }
}
int main() {
    long long n = 1000000000;
    clock_t start = clock();
    long long count = no_thread(n);
    clock_t end = clock();
    double time = ((double) (end - start)) / CLOCKS_PER_SEC;


    long long count1 = 0;
    clock_t start1 = clock();
    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;
    pthread_t thread4;
    long long n1=250000000;
    pthread_create(&thread1,NULL,count_thread,&n1);   
    pthread_create(&thread2,NULL,count_thread,&n1);
    pthread_create(&thread3,NULL,count_thread,&n1);   
    pthread_create(&thread4,NULL,count_thread,&n1);
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    pthread_join(thread3,NULL);
    pthread_join(thread4,NULL);
    clock_t end1 = clock();
    double time1 = ((double) (end1 - start1)) / CLOCKS_PER_SEC;
    printf("Number : %lld\n", count);
    printf(" Time with no threading: %f seconds\n", time);   
    printf(" Time with threading: %f seconds\n", time1);  
    return 0;
}


