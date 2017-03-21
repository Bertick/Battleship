#include "Game.h"

#include "Functions.h"

Game::Game()
{
	if(Game::AIactive)
	{
		player1=new Player(false);
		player2=new Player(true);

		srand(time(0));
	}
	else
	{
		player1=new Player(false);
		player2=new Player(false);
	}
}

Game::~Game() //destructor
{
	delete player1;
	delete player2;
}

void Game::initNames()
{
	wmove(welcome,4,0); //lets place the lines in the middle

	char name1[20]={};

	if(Game::AIactive)
    {
		print(welcome,"Player 1 Inserisci il tuo nome [max 20 caratteri]: ");
		wgetstr(welcome,name1);
		player1->setName(name1);
	    wmove(welcome,6,0);

	    print(welcome,"Benvenuto ");
	    print(welcome,player1->getname());
	    print(welcome,", HAL9000 sara' il tuo rivale per questo incontro");
		mySleep(2);
    }
	else
	{
		//Initializing players' names
		print(welcome,"Player 1 Inserisci il tuo nome [max 20 caratteri]: ");
		wgetstr(welcome,name1);
		player1->setName(name1);
		cReturn(welcome);

		print(welcome,"Player 2 Inserisci il tuo nome [max 20 caratteri]: ");
		wgetstr(welcome,name1);
		player2->setName(name1);
		mySleep(1);
	}
}

void Game::initGame()
{
	if(Game::AIactive)
	{
		wmove(outwin,0,0);
		print(outwin,player1->getname());
		cReturn(outwin);
		print(outwin,"Posiziona le tue navi");

		cReturn(outwin);

		player1->init(); //ask player for ship placement
		mySleep(1);

		print(outwin,"HAL9000 posizionera' le sue navi");
		cReturn(outwin);
		mySleep(2.5);

		player2->AIinit();
	}
	else
	{
		wmove(outwin,0,0);

		print(outwin,player1->getname());
		cReturn(outwin);
		print(outwin,"Posiziona le tue navi");

		cReturn(outwin);

		player1->init(); //ask player for ship placement
		mySleep(1);

		wclear(outwin);wclear(attackg);wclear(defenseg);
		wmove(outwin,0,0);
		//same as above but for player2

		print(outwin,player2->getname());
		cReturn(outwin);
		print(outwin,"Posiziona le tue navi");
		cReturn(outwin);

		player2->init();
		wclear(outwin);wclear(attackg);wclear(defenseg);
	}

    //Both attack grid need to know enemy ship location
    //they are not shown but needed for user feedback:
    //when he hits a ship a different symbol should be shown

    for(int i=0; i<10; i++)
    {
    	for(int j=0; j<10; j++)
    	{
    		player1->gAttack->points[i][j]=player2->gDefense->points[i][j];
    		player2->gAttack->points[i][j]=player1->gDefense->points[i][j];
    	}
    }
}

void Game::playGame()
{
    do{
        attack(player1, player2); //player attack
        if (player2->hasLost()) //check if someone wins
        {
        	wclear(attackg);
        	wclear(defenseg);
        	wclear(outwin);
        	wrefresh(attackg);wrefresh(defenseg);wrefresh(outwin);
        	delwin(attackg);
        	delwin(defenseg);
        	delwin(outwin);

            closing=newwin(15,50,4,4);

            wmove(closing,0,10);
        	string outs="";
            outs+=player1->getname();
            outs+=" WINS!";
            print(closing,outs);
            if(player2->isAI()){wmove(closing,2,0);print(closing,"HAL9000 says:This conversation can serve no purpose anymore, goodbye");}
            wmove(closing,4,0);
            break;
        }

        attack(player2,player1);
        if (player1->hasLost())
        {
        	wclear(attackg);
        	wclear(defenseg);
        	wclear(outwin);
        	wrefresh(attackg);wrefresh(defenseg);wrefresh(outwin);
        	delwin(attackg);
        	delwin(defenseg);
        	delwin(outwin);

        	closing=newwin(15,50,4,4);

        	wmove(outwin,0,10);
            string outs="";
            outs+=player2->getname();
            outs+=" WINS!";
            print(closing,outs);
            if(player2->isAI()){wmove(closing,2,0);print(closing,"HAL9000 says: Thank you for a very enjoyable game");}
            wmove(closing,10,16);
            mySleep(3);
            break;
        }

    }while( !player1->hasLost() && !player2->hasLost() ); //do...while loop until one of the players looses

    print(closing,"Vuoi fare un altra partita ? [y/n]");
    int ans=wgetch(closing);

    if(ans=='y' || ans=='Y')
    {
    	Game::newgame=true;
        clear();
        refresh();
        delwin(closing);
    }
    else if(ans=='n'||ans=='N')
    {
    	Game::newgame=false;
    }
    mySleep(2);

}

void Game::attack(Player* attacker, Player* defender)
{
	int x;
	int y;
	char data[5];

	wclear(turn);
	wmove(turn,0,0);
	print(turn,"Turno di: ");
	print(turn, attacker->getname());

	if(attacker->isAI())
	{
		wclear(outwin);wrefresh(outwin);
		// map exploration not ended yet; There is not possibility to attack twice (no loop needed)
		if (attacker->yai<10)
		{
			if( (attacker->xai + 4)>10 && attacker->yai<9)
			{
				attacker->yai++;
				attacker->xai = (attacker->xai +4)%10 -1;//-1 to correct an issue on the line change
			}
			else if((attacker->xai+4)==10)//last column correction
			{
				attacker->yai++;
				attacker->xai=3%10;
			}
			else if(attacker->yai==9 && (attacker->xai+4)>=10)//last line & column correction
			{
				attacker->xai=0;
				attacker->yai=10;
			}
			else{attacker->xai=(attacker->xai +4)%10;}

			if(attacker->yai==10 && attacker->xai==0)//last line & column correction
			{
				x=0;
				y=0;
				attacker->xai=10;
				attacker->yai=10;
			}
			else
			{
				x= attacker->xai;
				y= attacker->yai;
			}

			attacker->gAttack->points[y][x].setHit();//sets attacker point as hit
			defender->gDefense->points[y][x].setHit();//sets defender point as hit
		}
		else
		{
			y=0;x=0;
			bool breaking=false;
			//if yai is 10, the map has been explored completely, let's start attacking ships
			for(int i=0;i<10;i++)
			{
				for (int j=0;j<10;j++)
				{
					if( attacker->gAttack->points[i][j].isHit() && attacker->gAttack->points[i][j].hasShip() )
					{
						if (i-1>=0)
						{
							if(!attacker->gAttack->points[i-1][j].isHit())
							{
								attacker->gAttack->points[i-1][j].setHit();
								defender->gDefense->points[i-1][j].setHit();
								y=i-1;
								x=j;
								//print(outwin,"b1f");
								breaking=true;
								break;
							}
						}
						if (i+1<10)
						{
							if(!attacker->gAttack->points[i+1][j].isHit())
							{
								attacker->gAttack->points[i+1][j].setHit();
								defender->gDefense->points[i+1][j].setHit();
								y=i+1;
								x=j;
								//print(outwin,"b1f");
								breaking=true;
								break;
							}
						}
						if (j-1 >=0)
						{
							if(!attacker->gAttack->points[i][j-1].isHit())
							{
								attacker->gAttack->points[i][j-1].setHit();
								defender->gDefense->points[i][j-1].setHit();
								y=i;
								x=j-1;
								//print(outwin,"b1f");
								breaking=true;
								break;
							}
						}
						if (j+1<10)
						{
							if(!attacker->gAttack->points[i][j+1].isHit())
							{
								attacker->gAttack->points[i][j+1].setHit();
								defender->gDefense->points[i][j+1].setHit();
								y=i;
								x=j+1;
								//print(outwin,"b1f");
								breaking=true;
								break;
							}
						}
					}
					else{;}
				}
				if(breaking){break;}//breaks 2nd cycle if an attack has been done
			}
		}
		defender->gAttack->print(); //instead of attacker we print defender grids
		defender->gDefense->print();//because attacker is an IA ...

		wmove(outwin,1,0);
		if ( attacker->gAttack->points[y][x].hasShip()){ print(outwin,"Colpito!"); cReturn(outwin);}
		else{ print(outwin,"Mancato..."); cReturn(outwin);}

		defender->shipDeath();
		cReturn(outwin);
		print(outwin,"Attendi");mySleep(0.35);

		for(int i=0;i<3;i++)
		{
			print(outwin,".");mySleep(0.35);
		}
	}
	else
	{
		if(!Game::AIactive){wclear(attackg);wclear(defenseg);wclear(outwin);} //clear window if it's a two player game
		else{wclear(outwin);wrefresh(outwin);} //clear only output window if it's a one player game
		attacker->gAttack->print(); //re-prints grids
		attacker->gDefense->print();

		while(true)
		{
			string outs("");
			outs+=attacker->getname();
			outs+=": Scrivi dove vuoi attaccare [es: A3]: ";
			print(outwin,outs);

			acquire(y,x,data);
			cRetafterInput(outwin);

			if (x<0 || x>=10 || y<0 || y>=10)
			{
				print(outwin,"Posizione non riconosciuta");cReturn(outwin);

				mySleep(1);

			}
			else if (attacker->gAttack->points[y][x].isHit())
			{
				print(outwin,"Posizione gia' colpita");cReturn(outwin);

				mySleep(1);
			}

			else
			{
				attacker->gAttack->points[y][x].setHit();//sets attacker point as hit
				defender->gDefense->points[y][x].setHit();//sets defender point as hit

				//saves current cursor location
				int i, j;
				getyx(outwin,j,i);

				attacker->gAttack->print(); //re-prints grids
				attacker->gDefense->print();

				move(j,i);//restores previous cursor location

				if (attacker->gAttack->points[y][x].hasShip()){print(outwin,"Colpito!"); cReturn(outwin);}
				else{print(outwin,"Mancato..."); cReturn(outwin);}

				defender->shipDeath();

				cReturn(outwin);
				print(outwin,"Attendi");mySleep(0.35);

				for(int i=0;i<3;i++)
				{
					print(outwin,".");mySleep(0.35);
				}
				break;
			}
		}
	}
	defender->setLost();
}

void Game::ActivateAI()
{
	Game::AIactive=true;
}
