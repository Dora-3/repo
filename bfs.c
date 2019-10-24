#include<stdio.h>
#include<math.h>
#include<mpi.h>

int bfs(int* tree,int ele_to_search,int start,int end,int n)
{
   int* queue;
   queue=(int*)malloc(sizeof(int)*n);
   for(int i=0;i<n;i++)
   {
      queue[i]=-1;
   }
   int que_ptr=0;
   queue[0]=tree[start];
   int que_put_ptr=1;

   while(queue[que_ptr]!=-1 && que_ptr<n)
   {
      if(queue[que_ptr]==ele_to_search)
          return que_ptr;

      int left=2*que_ptr+1;
      int right=2*que_ptr+2;

      if(left<=end)
      {
         queue[que_put_ptr++]=tree[left];
      }
      if(right<=end)
      {
         queue[que_put_ptr++]=tree[right];
      }
      que_ptr++;
   }
 return -1;
}

int main(int argc,char const *argv[])
{
   int* tree;
   int n=100;
   int ele=91;

   tree=(int*)malloc(n*sizeof(int));
   for(int i=0;i<n;i++)
   {
      tree[i]=i;
   }

   MPI_Init(NULL,NULL);
   MPI_Status status;

   int proc_id,num_procs;

   MPI_Comm_rank(MPI_COMM_WORLD,&proc_id);
   MPI_Comm_size(MPI_COMM_WORLD,&num_procs);

   if(proc_id==0)
   {
     printf("\nOriginal=%d\n",proc_id);
     int avg=n/num_procs;
     int k=bfs(tree,ele,0,avg-1,n);

      if(k>0)
      {
        printf("Process #0, found %d at index %d\n", ele, k) ;
         MPI_Finalize();
         return 0;
      }
      else
      {
         printf("Process #0 failed to find %d\n", ele);
         for(int i=1;i<num_procs;i++)
         {
            int start=i*avg;
            int end=start+avg-1;

            if(end>(n-1))
                end=n-1;

            MPI_Send(&start,1,MPI_INT,i,1,MPI_COMM_WORLD);
            MPI_Send(&end,1,MPI_INT,i,2,MPI_COMM_WORLD);
         }

         for(int i=1;i<num_procs;i++)
         {
            int found;

            MPI_Recv(&found,1,MPI_INT,i,10,MPI_COMM_WORLD,&status);

            int sender=status.MPI_SOURCE;
            if(found>0)
            {
               printf("%d found at index %d by Process #%d\n", ele, found, sender);

               break;
            }
            else
            {
                printf("Process #%d failed to find %d\n", sender, ele);
            }
         }
      }
   }
   else
   {
      int start,end;

     MPI_Recv(&start,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
     MPI_Recv(&end,1,MPI_INT,0,2,MPI_COMM_WORLD,&status);

     int found=bfs(tree,ele,start,end,n);

     MPI_Send(&found,1,MPI_INT,0,10,MPI_COMM_WORLD);
         
   }
   MPI_Finalize();
   return 0;
}
