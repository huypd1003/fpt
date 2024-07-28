#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
sem_t count_sem;
long long count = 0;
void* count_thread(void * arg) {
    long long n = *((long long*)arg);
    for (long long i = 0; i < n / 2; i++) {
        sem_wait(&count_sem);
        count++;
        sem_post(&count_sem);
    }
    return NULL;
}
int main() {
    long long n = 1000000000;
    pthread_t thread1, thread2;
    sem_init(&count_sem, 0, 1);
    pthread_create(&thread1, NULL, count_thread, &n);
    pthread_create(&thread2, NULL, count_thread, &n);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    sem_destroy(&count_sem);
    printf("%lld\n", count);

    return 0;
}
