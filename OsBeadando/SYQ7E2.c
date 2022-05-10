#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{

    printf("Milyen muveletet szeretne vegre hajtani?");
    printf("Beolvasas/Kiiras/torles (o/i/t)");
    char m = getchar();

    // Kulcs létrehozása
    key_t kulcs = ftok("shmf",65);

    // Az shmget egy azonosítót ad vissza az shmid-vel és az IPC_Creat létrehozza az osztott memóriát
    int shmid = shmget(kulcs, 1024, 0666|IPC_CREAT);

    // shmat-al csatlakozunk a memóriaszegmensre
    char* str = (char*) shmat(shmid,NULL,0);



    // beolvassuk a memóriába 
    if(m == 'o')
    {
        FILE* fl;

		// ellenõrzés hogy a file olvasható e 
        if ((fl=fopen("test.txt", "r")) == NULL)
        {
            printf("Openning file failed. error:\n");
            perror(0);
            exit(1);
        }

        // Fájl tartalmának beolvasása majd kiírása a memóriaszegmensbe, pointer bezárása
        fgets(str, 256, fl);
        fclose(fl);

        printf("written data: %s\n", str);
    }


	//kiírjuk mi van a memóriában
    else if(m == 'i')
    {
        printf("A szegmensbol olvasott adat: %s\n",str);
    }

    else if(m == 't')
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
