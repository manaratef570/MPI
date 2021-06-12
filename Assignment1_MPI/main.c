#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc , char * argv[])
{
   int my_rank;		/* rank of process	*/
	int p;			/* number of process	*/

	MPI_Status status;	/* return status for 	*/
				/* recieve		*/

	/* Start up MPI */
	MPI_Init( &argc , &argv );

	/* Find out process rank */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	/* Find out number of process */
	MPI_Comm_size(MPI_COMM_WORLD, &p);

  int Lowerbound = 10;
  int Upperbound = 30;
  int size = (Upperbound-Lowerbound)/(p-1);

	if( my_rank == 0)
	{

        int globalCount = 0,i=0;

        for (i = 1 ; i < p ; i++){

          MPI_Send (&size , 1 ,MPI_INT, i , 0 , MPI_COMM_WORLD );

          MPI_Send (&Lowerbound, 1 ,MPI_INT, i , 0 , MPI_COMM_WORLD );

        }
        for (i = 1 ; i < p ; i++){

          int subCount;

          MPI_Recv(&subCount , 1 ,MPI_INT,i,0,MPI_COMM_WORLD, &status);

          globalCount += subCount;

        }
        printf("Total number of prime numbers is: %d\n",globalCount );

	}else
	{

    MPI_Recv(&size , 1 , MPI_INT , 0 , 0 , MPI_COMM_WORLD, &status);

    MPI_Recv( &Lowerbound, 1 , MPI_INT , 0 , 0 , MPI_COMM_WORLD , &status);

    int n=0;
    n=Lowerbound+((my_rank-1)*size);


    int localCount = 0,i=0;
    int  z, m=0, flag=0;


    for(;i<size;i++){


     if(n>Upperbound){
        break;
     }

     m=n/2;
    for(z = 2; z <= m; z++)
     {
    if(n % z == 0)
    {

    flag=1;
    break;
     }
      }

     if (flag==0&&n!=1)
    {
        localCount++;
    }


    n++;

    flag=0;


    }


    printf("Total number of prime numbers in P %d ",my_rank );
    printf("is: %d\n",localCount );

    MPI_Send (&localCount , 1 , MPI_INT , 0 , 0 , MPI_COMM_WORLD);

	}


	MPI_Finalize();
    return 0;
}


