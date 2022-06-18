#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include "alg_info.h"
#include "ietf_constants.h"

struct ike_info;
key_t key;
int shmid, cntr;
struct ike_info *shmike_info;
int getIkeInfoId()
{
  /* Create unique key via call to ftok() */
  key = ftok(".", 1);

  /* Open the shared memory segment - create if necessary */
  if ((shmid = shmget(key, 32, IPC_CREAT | IPC_EXCL | 0666)) == -1)
  {
    printf("Shared memory segment exists - opening as client\n");

    /* Segment probably already exists - try as a client */
    if ((shmid = shmget(key, 32, 0)) == -1)
    {
      perror("shmget");
      exit(1);
    }
  }
  else
  {
    printf("Creating new shared memory segment\n");
  }
  return shmid;
}

int *getIkeInfoAddr(const void *shmaddr, int shmflg)
{
  shmid = getIkeInfoId();
  struct ike_info *shmike_info;
  /* Attach (map) the shared memory segment into the current process */
  if ((shmike_info = (struct ike_info *)shmat(shmid, 0, 0)) == (struct ike_info *)-1)
  {
    perror("shmat");
    exit(1);
  }
  return shmike_info;
}

void removeIkeInfo()
{
  shmid = getIkeInfoId();
  shmctl(shmid, IPC_RMID, 0);
  printf("Shared memory segment marked for deletion\n");
}

void delIkeInfo(struct ike_info *ike_info)
{
  if (shmdt(ike_info) == -1)
  {
    perror("shmdt");
    exit(1);
  }
}
