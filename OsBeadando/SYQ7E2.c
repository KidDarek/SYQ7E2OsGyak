#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{

	

    // Kulcs l�trehoz�sa
    key_t kulcs = ftok("shmf",65);

    // Az shmget egy azonos�t�t ad vissza az shmid-vel �s az IPC_Creat l�trehozza az osztott mem�ri�t
    int shmid = shmget(kulcs, 1024, 0666|IPC_CREAT);

    // shmat-al csatlakozunk a mem�riaszegmensre
    char* str = (char*) shmat(shmid,NULL,0);



    // beolvassuk a mem�ri�ba 
	char szoveg[1024] = "";
    if(strcmp(argv[1],"be")==0)
    {
     
		for(int i = 2; i < argc; i++)
		{
			strcat(szoveg,argv[i]);
			strcat(szoveg," ");
		}
		strcat(str,szoveg);
        // sz�veg beolvas�sa majd ki�r�sa a mem�riaszegmensbe, pointer bez�r�sa

        printf("written data: %s\n", str);
    }


	//ki�rjuk mi van a mem�ri�ban
    else if(strcmp(argv[1],"ki")==0)
    {
        printf("A szegmensbol olvasott adat: %s\n",str);
    }

    else if(strcmp(argv[1],"torol")==0)
    {
        // Lecsatlakoz�s a mem�riaszegmensr�l
        shmdt(str);

        // Mem�riaszegmenst t�rl�se
        shmctl(shmid, IPC_RMID, NULL);
    }

    else
    {
        shmdt(str);
        shmctl(shmid, IPC_RMID, NULL);
        printf("Wrong input");
        exit(1);

    }


    return 0;
}
