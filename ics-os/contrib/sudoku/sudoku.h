/*
    Displays MECHANICS page given the page number
*/
char mechanics(char line[][35], int pageNo){
	int i,a;
	int linebreak = 20, skip;
	char pressed;

	drawRectangle(0,0,320,220, BLACK);
	if(pageNo==1){
		write_text(line[3], 31, 21, WHITE, 0);
		for(i=4; i<=7; i++){
			write_text(line[i], 30, 20+linebreak, WHITE, 0);
			linebreak+=20;
		}
	} else {
		write_text(line[8], 31, 21, WHITE, 0);
		for(a=1; a<=6; a++){
			skip=a*6;
			if(pageNo==a+1){
				for(i=3+skip; i<=8+skip; i++){
					write_text(line[i], 30, 20+linebreak, WHITE, 0);
					linebreak+=20;
				}
			}
		}
	}

	write_text(line[2], 30, 180, WHITE, 0); //main menu
	if(pageNo!=1) write_text(line[0], 155, 180, WHITE, 0); //back
	if(pageNo!=7) write_text(line[1], 230, 180, WHITE, 0); //next

	pressed = (char)getch();
	return pressed;
}



/*
    Houses an array of strings named line;
    allows navigation of user between pages using
    left_key and right_key or back to main menu
*/
void instruction(){
	char line[45][35];
	char pressed;
	int pageNo;

	strcpy(line[0], "[a]back");
	strcpy(line[1], "[d]next");
	strcpy(line[2], "[m]main menu");

	/*page 1*/
	strcpy(line[3], "NAVIGATION");
	strcpy(line[6], "Press [a] to go left");
	strcpy(line[7], "Press [d] to go right");

	/*page 2*/
	strcpy(line[8], "MECHANICS");
	strcpy(line[9], "Each player gets seven houses");
	strcpy(line[10], "and a head. The game moves in");
	strcpy(line[11], "a counter-clockwise direction.");
	strcpy(line[12], "Start with one of your houses.");
	strcpy(line[13], "Get the points. Log a point to");  //KAYA ATA PITONG LINES??????????
	strcpy(line[14], "each house you pass, until the");

	/*page 3*/
	strcpy(line[15], "last point. If it lands on:");
	strcpy(line[16],"(a) either player's unempty");
	strcpy(line[17], "house, get points of that");
	strcpy(line[18], "house, keep playing;");
	strcpy(line[19], "(b) your head, select again");
	strcpy(line[20], "from your houses, keep playing;");

	/*page 4*/
	strcpy(line[21], "(c) your empty house, get all");
	strcpy(line[22], "points from the adjacent house");
	strcpy(line[23], "[opponent's] add these points");
	strcpy(line[24], "to your head. Your turn ends;");
	strcpy(line[25], "(d) your opponent's empty");
	strcpy(line[26], "house, your turn ends. A game");

	/*page 5*/
	strcpy(line[27], "goes for several rounds. A round");
	strcpy(line[28], "ends if all points are in");
	strcpy(line[29], "respective heads. In succeeding");
	strcpy(line[30], "rounds, gained points are");
	strcpy(line[31], "redistributed to respective");
	strcpy(line[32], "houses. If remaining points do");

	/*page 6*/
	strcpy(line[33], "not suffice for a house, that");
	strcpy(line[34], "house becomes `burnt`. Burnt");
	strcpy(line[35], "houses are unusable, and cannot");
	strcpy(line[36], "be filled in later rounds. Game");
	strcpy(line[37], "ends when one player burns all");
	strcpy(line[38], "his houses.");

	/*page 7*/
	strcpy(line[39], "Goal: obtain all 98 points,");
	strcpy(line[40], "and burn all opponent's");
	strcpy(line[41], "houses!!!!!!!!!!!!");


	pageNo=1;
	pressed = mechanics(line, pageNo);
	if(pressed==right_key){ pageNo+=1; }

	do{
		switch(pressed){
			case right_key : 	pressed = mechanics(line, pageNo);
							if(pressed == right_key && pageNo<7){ pageNo+=1; }
							else if (pressed == left_key){ pageNo-=1; }
							break;

			case left_key : pressed = mechanics(line, pageNo);
                            if(pressed == right_key){ pageNo+=1; }
							else if (pressed == left_key && pageNo>1){ pageNo-=1;}
							break;
		}
	} while (pressed != main_menu);


}