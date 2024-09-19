#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define SIZE_TABLE 8 
#define MINE_NUMBER 5

char tab[SIZE_TABLE+2][SIZE_TABLE+2];
int tabvalue[SIZE_TABLE+2][SIZE_TABLE+2];   
int row,column;
int win;

int control(); 
void create_mines();                    
void starting();
void after_starting();
void game_win();
void again_game();
void game_over();
void game_continue();

int main(){
    srand(time(0));
    printf("\nGame is on! Good luck! \n\n"); 
    starting();
    return 0;
}

void again_game(){
    int choice=0;
    printf("Would you like to play again? If so enter 1 or enter anything else: ");
    scanf("%d", &choice);
    if(choice==1){
        starting();
    }
    else{
        printf("Game ended!\n\n");
        exit (0);
    }
}

void game_win(){
        printf("You won! \n \n");
        int endline = 0;
        printf("1  2  3  4  5  6  7  8  \n------------------------\n");
        for(int i =1; i<SIZE_TABLE+1; i++){
            for(int j=1;j<SIZE_TABLE+1;j++){
                if(tabvalue[i][j]==-1){
                    printf("X  ");
                }
                else{
                    printf("%d  ",tabvalue[i][j]);
                }
            }
            endline+=1;
            printf("| %d",endline);
            printf("\n");
        }
}

void game_over(){
    printf("You lost!\n \n");
    int endline = 0;
    printf("1  2  3  4  5  6  7  8  \n------------------------\n");
    for(int i =1; i<SIZE_TABLE+1; i++){
        for(int j=1;j<SIZE_TABLE+1;j++){
            if(tabvalue[i][j]==-1){
                printf("X  ");
            }
            else{
                printf("%d  ",tabvalue[i][j]);
            }  
        }
        endline+=1;
        printf("| %d",endline);
        printf("\n");
    }
    again_game();
}

void game_continue(){
    for(int count=0;count<3;count++){
        int random_row = (rand() % (SIZE_TABLE)) + 1;
        int random_column = (rand() % (SIZE_TABLE)) + 1;
        if(tab[random_row][random_column]=='#'){
            if(tabvalue[random_row][random_column]!=-1){
                tab[random_row][random_column]=tabvalue[random_row][random_column];
                win--;
            }
        }
    }

}
    
int control(){
    if (win<6){
        game_win();
    }
    else{
        after_starting();
    }
}

void create_mines(){
    int loop=0;
    while(loop<5){
        int random_row = (rand() % (SIZE_TABLE)) + 1;
        int random_column = (rand() % (SIZE_TABLE)) + 1;
        if (tabvalue[random_row][random_column]!= -1){
            tabvalue[random_row][random_column]= -1;
            loop++;
        }
        
    }
    for(int i=1; i<SIZE_TABLE+1; i++){
        for(int j=1; j<SIZE_TABLE+1; j++){
            if(tabvalue[i][j]==-1){
                for(int k=-1; k<2;k++){
                    for(int m=-1; m<2; m++){
                        if(tabvalue[i+k][j+m]!=-1){
                            tabvalue[i+k][j+m]+=1;
                        }
                    }
                }
            }
        }
    }
}

void after_starting(){
    printf("Please enter the row and the column numbers(ex: 1 1):\n");
    printf("Row:");
    scanf("%d", &row);
    printf("Column:");
    scanf("%d", &column);
    getchar();
    if((row<=8 && row>=1)&&(column<=8 && column>=1)){
        if(tabvalue[row][column]==-1){
            game_over();
        }
        else if(tab[row][column]!='#'){
            printf("\n");
            printf("Enter different dimensions!\n");
            after_starting();
        }
        else{
            if(win>8){
                game_continue();
            }
            int endline = 0;
            printf("\n");
            printf("1  2  3  4  5  6  7  8  \n------------------------\n");
            for(int i =1; i<SIZE_TABLE+1; i++){
                for(int j=1;j<SIZE_TABLE+1;j++){
                    if(i==row && j==column){
                        tab[i][j]=tabvalue[i][j];
                        win--;
                    }

                    if(tab[i][j]=='#'){
                        printf("%c  ",tab[i][j]);
                    }
                    else{
                        printf("%d  ",tab[i][j]);
                    }   
                }
                endline+=1;
                printf("| %d",endline);
                printf("\n");
            }
            printf("\n");
            printf("Remaining cells: %d\n",win);
            control();
        }
    }
}




void starting(){
    int endline = 0;
    printf("\n");
    win = (SIZE_TABLE * SIZE_TABLE) ;
    printf("1  2  3  4  5  6  7  8  \n------------------------\n");
    for(int i =1; i<SIZE_TABLE+1; i++){
        for(int j=1;j<SIZE_TABLE+1;j++){
            tab[i][j]='#';
            printf("%c  ",tab[i][j]);
            tabvalue[i][j]=0;
        }
        endline+=1;
        printf("| %d",endline);
        printf("\n");
    }
    printf("\n");
    create_mines();
    after_starting();
}