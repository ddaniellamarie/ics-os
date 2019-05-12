/*
    Daniella Marie Costales
    Andrea Nicole Cuevas
    CMSC 125 T-1L
    2nd Sem AY 2018-2019
*/

#include "../../sdk/dexsdk.h"
#include "../../sdk/time.h"

#define up_key 'w'
#define down_key 's'
#define right_key 'd'
#define left_key 'a'
#define enter '\n'
#define quit 'q'
#define yes 'y'
#define no 'n'
#define main_menu 'm'

/*
    (colors are from the blacjack application in the ics-os)
*/
#define YELLOW 54
#define GRAY 56
#define WHITE 63
#define BROWN 20
#define VIOLET 40
#define RED 36
#define GREEN 18
#define BLUE 9
#define ORANGE 38
#define MAROON 4
#define FLESH 55
#define BLACK 70
#define DARK_GREEN 16
#define DARK_BROWN 32



char given[6][6] = {"001000","000600","100030","040002","002000","000200"}; //0 if empty circle
char guide[6][6] = {"00-000","000-00","-000-0","0-000-","00-000","000-00"};
char answ[6][6]={"261543","534621","126435","345162","412356","653214"}; //0 if position has given



/*  "Erases" the screen given the starting point and the width & height
    (from the blacjack application in the ics-os) */
void drawRectangle(int x, int y, int w, int h, int color){
   int i,j;
   for (i=y;i<=(y+h);i++)
      for (j=x;j<=(x+w);j++)
         write_pixel(j,i,color);
}

/*    this function will clear the screen and display the menu*/
void drawMenu(){
    drawRectangle(0,0,320,220, BLACK);
    write_text("SUDOKU",41,41,WHITE,1);

    write_text("[Enter] Start",40,120,WHITE,0);
	write_text("[q] Quit",40,140,WHITE,0);
	write_text("[i] Instructions", 40, 160, WHITE, 0);
}


void drawQuickInst(){
    char temp2[20];
    write_text("Instructions:",205,4,WHITE,1);

    write_text("[w] Up",205,29,WHITE,0);
    write_text("[a] Left",205,39,WHITE,0);
    write_text("[s] Down",205,49,WHITE,0);
    write_text("[d] Right",205,59,WHITE,0);

    write_text("[q] Quit",205,89,WHITE,0);
    
}

/* this function will draw the current state of the board */
void drawBoard(){
    int x,y,z;
    char temp[1];

    
    for(y=4; y<204; y+=34){
        for(x=4; x<204; x+=34){
            drawRectangle(x,y,30,30, BROWN);
            if(given[((y-4)/34)][((x-4)/34)]=='0'){
                sprintf(temp, "%c", '-');    
            }else{
                sprintf(temp, "%c", given[((y-4)/34)][((x-4)/34)]);
            }
            write_text(temp,x+1,y+2,WHITE,0);
            z++;
        }
    } 
    drawQuickInst();
}//DONE

/*to highlight the current cell where there will be an update*/
void highlight(int x, int y){
    char temp[1];
    drawRectangle(x,y,30,30, YELLOW);
    if(given[((y-4)/34)][((x-4)/34)]=='0'){
        sprintf(temp, "%c", '-');    
     }else{
         sprintf(temp, "%c", given[((y-4)/34)][((x-4)/34)]);
    }
    write_text(temp,x+1,y+2,WHITE,0);
} //DONE


/*will check if it can update or not edit function*/
void checkin(char a, int x, int y){
    if(a=='1'||a=='2'||a=='3'||a=='4'||a=='5'||a=='6'||a=='7'||a=='8'||a=='9'){
        if(guide[((y-4)/34)][((x-4)/34)]!='-'){
            given[((y-4)/34)][((x-4)/34)]=a;
        }
    }
} //DONE

/*this will check if the current game is finished*/
int checkIfFinish(){
    int x,y;
    for(x=0; x<6; x++){
        for(y=0; y<6; y++){
            if(given[x][y]=='0'){
                return 0;
            }
        }
    }
    return 1;
}//DONE

int checkIfCorrect(){
    int x,y;
    for(x=0; x<6; x++){
        for(y=0; y<6; y++){
            if(given[x][y]!=answ[x][y]){
                return 0;
            }
        }
    }
    return 1;
}

int win_screen(){
    char p;
    drawRectangle(0,0,320,220, BLACK);
    write_text("You won! Good for you.",10,41,WHITE,1);
    write_text("[q] Quit",10,160,WHITE,0);

}

void displayStat(){
    write_text("Table",215,109,WHITE,0);
    write_text("Table",205,119,WHITE,0);

}

/*for moving*/
int move(char a, int x, int y){
    highlight(x,y);
    a = getchar();
    if(a == right_key && x<=170){
        x = x + 34;
        drawBoard();
        highlight(x,y);
        // move(a,x,y);
        return 0;        
    }else if(a == left_key && x!=4){
        x = x - 34;
        drawBoard();
        highlight(x,y);
        move(a,x,y);
        return 0;        
    }else if(a == up_key && y!=4){
        y = y - 34;
        drawBoard();
        highlight(x,y);
        move(a,x,y);
        return 0;        
    }else if(a == down_key && y<=170){
        y = y + 34;
        drawBoard();
        highlight(x,y);
        move(a,x,y);
        return 0;        
    }else if(a == quit){
        return 1;        
    }else{
        checkin(a,x,y);
    }
    if (checkIfFinish()!=0){
        if(checkIfCorrect()!=0){
            char p;
            win_screen();
        }else{
            displayStat();
            move(a,x,y);
        }
    }else{
        move(a,x,y);
    };
}//DONE




/*
    this will display the quit screen
*/

int quit_screen(){
    char p;
    drawRectangle(0,0,320,220, BLACK);
    write_text("Are you sure you want to quit?",10,41,WHITE,1);
    write_text("[y] Yes",10,160,WHITE,0);
    write_text("[n] No",150,160,WHITE,0);

    p = getchar();

    if(p==yes)
        return 1;
    else
        return 0;
}

/*
    this will simulate the alternating turn of each player
*/
int startGame(){
    //int currentx = 49;
    int i=0;
    int check=0;
    char pressed;
    //getNames();
    drawRectangle(0,0,320,220, BLACK);
    do{
        drawBoard();
        check=move(pressed,4,4);    
    } while(check!=1);   

    return 1;
}

/*
    Houses an array of strings named line;
*/
void instruction(){
	char line[45][35];
	char pressed;
    int linebreak = 20, i;

	strcpy(line[0], "MECHANICS");
	strcpy(line[1], "Move around the board with ");
	strcpy(line[2], "[a] left, [d] right, [w] up,");
	strcpy(line[3], "[s] down. Press the number to");
	strcpy(line[4], "put in. The goal is to arrange");
    strcpy(line[5], "the numbers with no duplicates");
	strcpy(line[6], "of the same number in a row,");  //KAYA ATA PITONG LINES??????????
	strcpy(line[7], "in a column, and in a block.");
    
    strcpy(line[8], "                [m]main menu");

    drawRectangle(0,0,320,220, BLACK);
    do{
        write_text(line[0], 20, linebreak-5, WHITE, 0);
        for(i=1; i<=8; i++){
                    write_text(line[i], 20, 20+linebreak, WHITE, 0);
                    linebreak+=20;
                }
        write_text(line[8], 60, linebreak+20, WHITE, 0);
        pressed = (char)getch();
    } while(pressed != main_menu);
}

main(){
    char pressed;
    set_graphics(VGA_320X200X256);

    do{
        drawMenu();
        pressed = (char)getch();
        if(pressed==enter){
            startGame();
        }
        else if(pressed=='i'){
            instruction();
        }
    }while(pressed!=quit);
    //Return ICS-OS graphics before exiting
	set_graphics(VGA_TEXT80X25X16);
	clrscr();
	exit(0);
return 0;
}
