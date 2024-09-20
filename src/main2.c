#include <stdio.h>
#include <sys/time.h>

long	get_mic_sec_since(long start_time)
{
	struct timeval timeval;
	long	time_in_micro;

	if (gettimeofday(&timeval, NULL) == -1)
		return (-1);
	time_in_micro = timeval.tv_usec + 1000000 * timeval.tv_sec - start_time;
	return (time_in_micro);
}


int main(int argc, char *argv[]) {
	long start_time;

	start_time = get_mic_sec_since(0);
	for (int i=0; i<10; i++ )
	{
		printf("%li\n", get_mic_sec_since(start_time));
	}
	return (0);
}
