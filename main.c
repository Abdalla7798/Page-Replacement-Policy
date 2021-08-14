#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int pages_count = 0 , frames_count , i=0;
    char * type ;
    int *frames;
    int *pages;

    pages = (int*)malloc(300*sizeof(int));

    printf("Enter the frames number: ");
    scanf("%d",&frames_count);
    frames = (int*)malloc(frames_count*sizeof(int));

    printf("Enter the name of replacement policy: ");
    scanf("%s",type);

    printf("Enter the sequence of pages:\n");
    scanf("%d",&pages[i]);

    while (pages[i] != -1){
       pages_count++;
       i++;
       scanf("%d",&pages[i]);
    }
    printf("\n");
    system("clear");

   if (strcasecmp (type, "fifo") == 0) {

     FIFO (type, pages ,pages_count,frames ,frames_count);

   }

   else if (strcasecmp (type, "lru") == 0) {

     LRU (type, pages ,pages_count , frames ,frames_count);

   }

   else if (strcasecmp (type, "optimal") == 0) {

     Optimal (type, pages , pages_count ,frames , frames_count);

    }
   else if (strcasecmp (type, "clock") == 0) {

     Clock (type, pages , pages_count , frames , frames_count);

    }

    return 0;
}

void FIFO (char * type, int *pages , int pages_count , int *frames , int frames_count){

       int faults = 0;
       int i;
       int j = 0;
       int flag; // indicate the page does not found in the frame only;
       int flag2; // indicate the frames contain at least on location free
       int k;

       printf("Replacement Policy = %s\n",type);
       printf("-------------------------------------\n");
       printf("Page   Content of Frames\n");
       printf("----   -----------------\n");

       for(i = 0 ; i < frames_count ; i++)
          frames[i]= -1;

       for(i = 0;i < pages_count ; i++){
            flag = 0;
            flag2 = 0;

            for(k = 0;k < frames_count ; k++){
               if(frames[k]==pages[i])
                  flag = 1;
               if (frames[k] == -1)
                  flag2 = 1;
            }
            if (flag == 0){
               frames[j]=pages[i];
               j = (j+1) % frames_count;
               if (flag2 == 0){
                  faults = faults + 1;
               }
            }

            printf("%02d ",pages[i]);

            if (flag == 0 && flag2 == 0){
               printf("F   ");
            }
            else {
               for(k = 0 ; k < 4 ; k ++){
                  printf(" ");
               }
            }

            for (k = 0 ; k < frames_count ; k++){
               if (frames[k] !=-1){
                   printf("%02d ",frames[k]);
               }
            }
         printf("\n");
       }
       printf("-------------------------------------\n");
       printf("Number of page faults = %d\n",faults);
}

void LRU (char * type, int *pages , int pages_count , int *frames , int frames_count){

     int i ;
     int faults = 0;
     int counter = 0;
     int flag1 = 0;
     int flag2 = 0;
     int j;

     int *frame_time = (int*)malloc(frames_count*sizeof(int)); // LRU

     printf("Replacement Policy = %s\n",type);
     printf("-------------------------------------\n");
     printf("Page   Content of Frames\n");
     printf("----   -----------------\n");

     for(i=0;i<frames_count;i++)
          frames[i]= -1;

     for(i = 0; i < pages_count; i++){
        flag1 = 0;
        flag2 = 0;

        for(j = 0; j < frames_count; j++){
    		if(frames[j] == pages[i]){
	    		counter++;
	    		frame_time[j] = counter;
	   			flag1 = 1;
	   			flag2 = 1;
	   			break;
   			}
    	}

    	if (flag1 == 0){ // if there is at least on frame is free

    	     for(j = 0; j < frames_count; j++){
	    		if(frames[j] == -1){
	    			counter++;
	    			frames[j] = pages[i];
	    			frame_time[j] = counter;
	    			flag2 = 1;
	    			break;
	    		}
    		}
    	}

    	if (flag2 == 0){ // get the LRU page
    	 int min = frame_time[0];
    	 int loc = 0;

    	 for(j = 1; j < frames_count; j++){
		      if(frame_time[j] < min){
			      min= frame_time[j];
			      loc = j;
		      }
	      }

	      counter++;
          faults++;
          frames[loc] = pages[i];
          frame_time[loc] = counter;
    	}


            printf("%02d ",pages[i]);

            if (flag2 == 0){
               printf("F   ");
            }
            else {
               for(j = 0 ; j < 4 ; j ++){
                  printf(" ");
               }
            }

            for (j = 0 ; j < frames_count ; j++){
               if (frames[j] !=-1){
                   printf("%02d ",frames[j]);
               }
            }
         printf("\n");
     }
     printf("-------------------------------------\n");
     printf("Number of page faults = %d\n",faults);
}

void Optimal (char * type, int *pages , int pages_count , int *frames , int frames_count){

     int i;
     int faults = 0;
     int flag1 = 0;
     int flag2 = 0;
     int flag3 = 0;
     int j,k,loc;

     int *frame_temp = (int*)malloc(frames_count*sizeof(int)); // optimal

     printf("Replacement Policy = %s\n",type);
     printf("-------------------------------------\n");
     printf("Page   Content of Frames\n");
     printf("----   -----------------\n");


     for(i=0;i<frames_count;i++)
          frames[i]= -1;

     for(i = 0; i < pages_count; i++){
        flag1 = 0;
        flag2 = 0;

        for(j = 0; j < frames_count; j++){
    		if(frames[j] == pages[i]){
	   			flag1 = 1;
	   			flag2 = 1;
	   			break;
   			}
    	}

    	if (flag1 == 0){

    	     for(j = 0; j < frames_count; j++){
	    		if(frames[j] == -1){
	    			frames[j] = pages[i];
	    			flag2 = 1;
	    			break;
	    		}
    		}
    	}

        if(flag2 == 0){
             flag3 = 0;
             for(j = 0; j <frames_count; j++)
            	frame_temp[j] = -1;

             for(j = 0; j < frames_count; j++){

            	for(k = i + 1; k < pages_count; k++){
            		if(frames[j] == pages[k]){
            			frame_temp[j] = k;
            			break;
            		}
            	}
             }

             for(j = 0; j < frames_count; j++){
            	if(frame_temp[j] == -1){
            		loc = j;
            		flag3 = 1;
            		break;
            	}
             }

             if(flag3 ==0){
            	int max = frame_temp[0];
            	loc = 0;

            	for(j = 1; j < frames_count; j++){
            		if(frame_temp[j] > max){
            			max = frame_temp[j];
            			loc = j;
            		}
            	}
            }

			frames[loc] = pages[i];
			faults++;
        }

        printf("%02d ",pages[i]);

            if (flag2 == 0){
               printf("F   ");
            }
            else {
               for(j = 0 ; j < 4 ; j ++){
                  printf(" ");
               }
            }

            for (j = 0 ; j < frames_count ; j++){
               if (frames[j] !=-1){
                   printf("%02d ",frames[j]);
               }
            }
         printf("\n");
      }
      printf("-------------------------------------\n");
      printf("Number of page faults = %d\n",faults);
}

void Clock (char * type, int *pages , int pages_count , int *frames , int frames_count){

        int i;
        int faults = 0;
        int pointer = 0;
        int flag = 0;
        int flag2 = 0;
        int flag3 = 1;
        int j;


        int *use = (int*)malloc(frames_count*sizeof(int)); // clock

        printf("Replacement Policy = %s\n",type);
        printf("-------------------------------------\n");
        printf("Page   Content of Frames\n");
        printf("----   -----------------\n");

        for(i=0; i<frames_count; i++) {
		    frames[i] = -1;
		    use[i] = 0;
	    }

	    for(i = 0; i < pages_count; i++) {

		     flag = 0;
		     flag2 = 0;
		     flag3 = 1;

		     for(j = 0; j < frames_count; j++) {
                if(pages[i] == frames[j]) {
                    flag = 1;
                    use[j]=1;
                }
                if (frames[j] == -1)
                    flag2 = 1;
             }
		     if(flag == 0) {
		        flag3 = 0;
			     do {
				    if(use[pointer]==0) {
					    frames[pointer]=pages[i];
					    use[pointer]=1;
					    flag = 1;
					    if (flag2 == 0){
					       faults = faults + 1;
					    }
				    }
				    else {
					    use[pointer] = 0;
				    }
				    pointer = (pointer +1)%frames_count;
				    //pointer++;

				    /*if(pointer == frames_count){
                        pointer = 0;
			        }*/
                 } while (flag != 1);
		     }

		     printf("%02d ",pages[i]);

            if (flag3 == 0 && flag2 == 0){
               printf("F   ");
            }
            else {
               for(j = 0 ; j < 4 ; j++){
                  printf(" ");
               }
            }

            for (j = 0 ; j < frames_count ; j++){
               if (frames[j] !=-1){
                   printf("%02d ",frames[j]);
               }
            }
         printf("\n");
        }
        printf("-------------------------------------\n");
        printf("Number of page faults = %d\n",faults);
}
