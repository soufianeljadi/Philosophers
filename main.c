#include <stdio.h>
#include <pthread.h>

//gcc -fsanitize=thread -g main.c && ./a.out
typedef	struct s_counter
{
	pthread_mutex_t	count_mutex;
	unsigned int	count;
} t_counter;

void	*thread_routine(void *data)
{
	pthread_t tid;
	// unsigned int	*count;
	unsigned int	i;
    t_counter	*counter; 

	tid = pthread_self();
	// count = (unsigned int *)data;
    counter = (t_counter *)data;

	pthread_mutex_lock(&counter->count_mutex);
	printf("Thread [%lu]: compte au depart = %u\n",  (unsigned long)tid, counter->count);
	pthread_mutex_unlock(&counter->count_mutex);

	i = 0;
	while (i < 100)
	{
		pthread_mutex_lock(&counter->count_mutex);
		counter->count++;
		pthread_mutex_unlock(&counter->count_mutex);
		i++;
	}
	pthread_mutex_lock(&counter->count_mutex);
	printf("\nThread [%ld]: Compte final = %u\n", (unsigned long)tid, counter->count);
	pthread_mutex_unlock(&counter->count_mutex);

	// printf("\nThread [%lu]: compte au depart = %u\n", (unsigned long)tid, *count);
	// printf("\nThread [%lu]: Compte final = %u\n" ,(unsigned long)tid, *count);
	return (NULL);
}

int main(void)
{
    pthread_t tid1; 
    pthread_t tid2;
	// unsigned int	count;
    t_counter	counter;


	pthread_mutex_init(&counter.count_mutex, NULL);
	counter.count = 0;
    pthread_create(&tid1, NULL, thread_routine, &counter);
    printf("\nCreation [%lu]\n", (unsigned long)tid1);
    pthread_create(&tid2, NULL, thread_routine, &counter);
    printf("\nCreation[%lu]\n\n", (unsigned long)tid2);

    pthread_join(tid1, NULL);
    // printf("\nMain: Union du premier thread [%lu]\n", (unsigned long)tid1);
    pthread_join(tid2, NULL);
    // printf("Main: Union du second thread [%lu]\n", (unsigned long)tid2);

    if (counter.count != (2 * 100))
		printf("\nMain: ERREUR ! Le compte est de %u\n", counter.count);
	else
		printf("\nMain: OK. Le compte est de %u\n", counter.count);

    pthread_mutex_destroy(&counter.count_mutex);
    return 0;
}