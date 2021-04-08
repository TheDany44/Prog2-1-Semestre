#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void node_found(int width,int height,int grid[height][width]){
    int h,w,x,y,xcontrol=1,ycontrol=1;

    for(h=0;h<height;h++){
        for(w=0;w<width;w++){
            if(grid[h][w]==0){
                printf("%d %d ",w,h);
                
                if(w+1!=width){
                    xcontrol=1;
                    for(x=w+1;x<width;x++){
                        if(grid[h][x]==0){
                            printf("%d %d ",x,h);
                            xcontrol=0;
                            break;
                        }
                    }
                    if(xcontrol){printf("-1 -1 ");}
                    
                }
                else{printf("-1 -1 ");}

                if(h+1!=height){
                    ycontrol=1;
                    for(y=h+1;y<height;y++){
                        if(grid[y][w]==0){
                            printf("%d %d ",w,y);
                            ycontrol=0;
                            break;
                        }
                    }
                    if(ycontrol){printf("-1 -1 ");}
                }
                else{printf("-1 -1 ");}
                printf("\n");
            }
        }
    }


    return;
}




int main(){
    int width,height,i,k;
    char caracter;


    scanf(" %d",&width);
    if(width<0||width>=30){exit(1);}
    scanf(" %d",&height);
    if(height<0||height>=30){exit(1);}
    int grid[height][width];

    for(i=0;i<height;i++){
        for(k=0;k<width;k++){
            scanf(" %c",&caracter);
            if(caracter=='0'){
                grid[i][k]=0;
            }
            else if(caracter=='.'){
                grid[i][k]=-1;
            }
        }
    }

    node_found(width,height,grid);


    return 0;
}