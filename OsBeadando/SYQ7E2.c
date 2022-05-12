#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{

	

    // Kulcs létrehozása
    key_t kulcs = ftok("shmf",65);

    // Az shmget egy azonosítót ad vissza az shmid-vel és az IPC_Creat létrehozza az osztott memóriát
    int shmid = shmget(kulcs, 1024, 0666|IPC_CREAT);

    // shmat-al csatlakozunk a memóriaszegmensre
    char* str = (char*) shmat(shmid,NULL,0);



    // beolvassuk a memóriába 
	char szoveg[1024] = "";
    if(strcmp(argv[1],"be")==0)
    {
     
		for(int i = 2; i < argc; i++)
		{
			strcat(szoveg,argv[i]);
			strcat(szoveg," ");
		}
		strcat(str,szoveg);
        // szöveg beolvasása majd kiírása a memóriaszegmensbe, pointer bezárása

        printf("written data: %s\n", str);
    }


	//kiírjuk mi van a memóriában
    else if(strcmp(argv[1],"ki")==0)
    {
        printf("A szegmensbol olvasott adat: %s\n",str);
    }

    else if(strcmp(argv[1],"torol")==0)
    {
        // Lecsatlakozás a memóriaszegmensrõl
        shmdt(str);

        // Memóriaszegmenst törlése
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
