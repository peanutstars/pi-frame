
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <pthread.h>

#include "vmshm-dev.h"
#include "vmshm.h"
#include "pfconfig.h"
#include "pfdebug.h"

/*****************************************************************************/

static int ConfigSemID;

static void semaInit(void)
{
	union semun {
		int val; 
		struct semid_ds *buf;
		unsigned short int *array;
	} arg; 

	ConfigSemID = semget((key_t)PFCONFIG_KEY, 1, IPC_CREAT|IPC_EXCL|0660);
	if(ConfigSemID < 0) { 
		if(errno != EEXIST) {
			ASSERT(! "semget must succeed, buf failed.");
		}    
		ConfigSemID = semget((key_t)PFCONFIG_KEY, 0, 0);
		ASSERT(ConfigSemID >= 0);
		/* 이미 존재 한다면 이전에 생성해 두었기 때문이다. 
		 * 초기화를 하지 않는다. */
		return;
	}    

	/* 세마포어 초기화 */
	arg.val = 1;//SEM_MAX_COUNT;
	if(semctl(ConfigSemID, 0, SETVAL, arg) < 0) { 
		ASSERT(! "semactl must succeed, buf failed.");
	}    
}


static void dump_vmconfig (int index)
{
	struct PFConfig *config;
	int i;

	config = (struct PFConfig *)PFConfigGet();

	printf ("%2d) ", index);
	for (i=0; i<9; i++)
		printf ("%9d ", config->dummy[i]);
		printf ("\n");

	PFConfigPut (config);
}

#define LOOP_COUNT		1000
void *thread_main (void *args)
{
	struct PFConfig *config;
	int index = *(int *)args;
	int i;

	config = (struct PFConfig *)PFConfigGet();
	PFConfigPut (config);
	/* 혼자 사용하는 영역 */
	for (i=0; i<LOOP_COUNT; i++)
	{
		config->dummy[index] ++;
	}
	return NULL;
}

int main (int argc, char *argv[])
{
	pthread_t thid;
	struct PFConfig *config;
	int i;
	int index = atoi (argv[1]);

	printf ("index = %d, sizeof(struct PFConfig) = %zd\n", index, sizeof(struct PFConfig));

	if (index == 1) {
		semaInit();
		config = (struct PFConfig *)PFConfigGet();
		memset ((void *)config, 0, sizeof(*config));
		PFConfigPut(config);
	}
	else {
		sleep(2);
	}

	config = (struct PFConfig *)PFConfigGet();
	PFConfigPut(config);

	printf ("config = %p\n", config);
	pthread_create (&thid, NULL, thread_main, (void *)(&index));
	pthread_detach(thid);

	/* 공통 사용하는 영역 */
	for (i=0; i<LOOP_COUNT; i++)
	{
		config = (struct PFConfig *)PFConfigGet();

		config->dummy[0] ++;

		PFConfigPut(config);
	}

	while (config->dummy[index] != LOOP_COUNT)
		usleep(1000);

	dump_vmconfig (index);

	return 0;
}
