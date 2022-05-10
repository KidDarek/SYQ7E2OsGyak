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

    // Kulcs l�trehoz�sa
    key_t kulcs = ftok("shmf",65);

    // Az shmget egy azonos�t�t ad vissza az shmid-vel �s az IPC_Creat l�trehozza az osztott mem�ri�t
    int shmid = shmget(kulcs, 1024, 0666|IPC_CREAT);

    // shmat-al csatlakozunk a mem�riaszegmensre
    char* str = (char*) shmat(shmid,NULL,0);



    // beolvassuk a mem�ri�ba 
    if(m == 'o')
    {
        FILE* fl;

		// ellen�rz�s hogy a file olvashat� e 
        if ((fl=fopen("test.txt", "r")) == NULL)
        {
            printf("Openning file failed. error:\n");
            perror(0);
            exit(1);
        }

        // F�jl tartalm�nak beolvas�sa majd ki�r�sa a mem�riaszegmensbe, pointer bez�r�sa
        fgets(str, 256, fl);
        fclose(fl);

        printf("written data: %s\n", str);
    }


	//ki�rjuk mi van a mem�ri�ban
    else if(m == 'i')
    {
        printf("A szegmensbol olvasott adat: %s\n",str);
    }

    else if(m == 't')
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
