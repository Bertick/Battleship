#include "Functions.h"
#include "Game.h"

Player::Player(bool ai)
{
    this->gAttack=new Grid(false);
    this->gDefense=new Grid(true);

    this->lost=false;    // Win\loose status
    this->name = "HAL9000";    //Lunatic AI
    this->AI=ai;

    xai=-1;
    yai=0;
}

Player::~Player() //lets deallocate some memory
{
    delete n1;
    delete n2;
    delete n3;
    delete n4;
    delete n5;

    delete gAttack;
    delete gDefense;
}

void Player::init()
{
	this->gAttack->print();
	this->gDefense->print();

    int x;
    int y;
    char direction[10];
    string dir1("");

    wmove(outwin,2,0);
    print(outwin,"Per specificare la posizione X si puo usare una lettera da A a J");
    print(outwin," (maiuscola o minuscola) oppure un numero da 0 a 9");
    cReturn(outwin);
    print(outwin,"Per secificare la posizione Y usare un numero da 1 a 10");
    cReturn(outwin);
    print(outwin,"E' inoltre necessario specificare una direzione down o right");
    cReturn(outwin);
    print(outwin,"Hai a disposizione 1 portaerei, 2 incrociatori, 2 fregate");
    cReturn(outwin);
    cReturn(outwin);
    print(outwin,"Esempio: A2 down");
    cReturn(outwin);

    //ship assembly

    //Carrier
    while(true)
    {
        print(outwin,"Posiziona la portaerei, 6 caselle: ");
        acquire(y,x,direction,dir1);
        cReturn(outwin);

        n1=new Ship(6,dir1); //allocate ship
        n1->p=gDefense->points; //lets assign ship pointer to Grid points
        n1->isWellPlaced(y,x); //check positioning

        if(n1->isAlive()){wclear(outwin);wrefresh(outwin);break;}
        else{delete n1;}

    }
    this->gAttack->print();
    this->gDefense->print();

    //Battlecruiser1
    while(true)
    {
    	print(outwin,"Posiziona il primo incrociatore, 5 caselle: ");
    	acquire(y,x,direction,dir1);
        cReturn(outwin);

    	n2=new Ship(5,dir1); //allocate ship
    	n2->p=gDefense->points; //lets assign ship pointer to Grid points
    	n2->isWellPlaced(y,x); //check positioning

    	if(n2->isAlive()){wclear(outwin);wrefresh(outwin);break;}
    	else{delete n2;}

    }
    this->gAttack->print();
    this->gDefense->print();


    //Battlecruiser2
    while(true)
    {
    	print(outwin,"Posiziona il secondo incrociatore, 5 caselle: ");
    	acquire(y,x,direction,dir1);
        cReturn(outwin);

    	n3=new Ship(5,dir1); //allocate ship
    	n3->p=gDefense->points; //lets assign ship pointer to Grid points
    	n3->isWellPlaced(y,x); //check positioning

    	if(n3->isAlive()){wclear(outwin);wrefresh(outwin);break;}
    	else{delete n3;}

    }
    this->gAttack->print();
    this->gDefense->print();

    //Frigate1
    while(true)
    {
    	print(outwin,"Posiziona la prima fregata, 4 caselle: ");
    	acquire(y,x,direction,dir1);
        cReturn(outwin);

    	n4=new Ship(4,dir1); //allocate ship
    	n4->p=gDefense->points; //lets assign ship pointer to Grid points
    	n4->isWellPlaced(y,x); //check positioning

    	if(n4->isAlive()){wclear(outwin);wrefresh(outwin);break;}
    	else{delete n4;}

    }
    this->gAttack->print();
    this->gDefense->print();

    //Battlecruiser2
    while(true)
    {
    	print(outwin,"Posiziona la seconda fregata, 4 caselle: ");
    	acquire(y,x,direction,dir1);
        cReturn(outwin);

    	n5=new Ship(4,dir1); //allocate ship
    	n5->p=gDefense->points; //lets assign ship pointer to Grid points
    	n5->isWellPlaced(y,x); //check positioning

    	if(n5->isAlive()){wclear(outwin);wrefresh(outwin);break;}
    	else{delete n5;}

    }
    this->gAttack->print();
    this->gDefense->print();

	cReturn(outwin);
	print(outwin,"Attendi");mySleep(0.5);

	for(int i=0; i<3; i++)
	{
		print(outwin,".");mySleep(0.5);
	}
}

void Player::AIinit()
{
	int x;
	int y;
	int dir;

	//ship assembly

	//Carrier
	while(true)
	{
		x=rand()%10;
		y=rand()%10;
		dir=rand()%100;

		//x >= 4 lets forbid right ship direction
		if(x>=4 && y<4)
		{
	    	n1=new Ship(6,"down"); //allocate ship
	    	n1->p=gDefense->points; //lets assign ship pointer to Grid points
	    	n1->isWellPlaced(y,x,false); //check positioning
	    	if(n1->isAlive()){break;}
		}
		//y >= 4 lets forbid down ship direction
		else if(x<4 && y>=4)
		{
	    	n1=new Ship(6,"right"); //allocate ship
	    	n1->p=gDefense->points; //lets assign ship pointer to Grid points
	    	n1->isWellPlaced(y,x,false); //check positioning
	    	if(n1->isAlive()){break;}
		}
		//x<4 & Y<4 all direction are ok
		else if(x<4 && y<4)
		{
			if(dir<50)
			{
				n1=new Ship(6,"down"); //allocate ship
				n1->p=gDefense->points; //lets assign ship pointer to Grid points
				n1->isWellPlaced(y,x,false); //check positioning
				if(n1->isAlive()){break;}
			}
			else
			{
				n1=new Ship(6,"down"); //allocate ship
				n1->p=gDefense->points; //lets assign ship pointer to Grid points
				n1->isWellPlaced(y,x,false); //check positioning
				if(n1->isAlive()){break;}
			}
		}
		//if both x & y >= 4 lets re-roll the dice
		else{;}
	}

	//Cruiser 1
	while(true)
	{
		x=rand()%10;
		y=rand()%10;
		dir=rand()%100;

		//x >= 5 lets forbid right ship direction
		if(x>=5 && y<5)
		{
			n2=new Ship(5,"down"); //allocate ship
			n2->p=gDefense->points; //lets assign ship pointer to Grid points
			n2->isWellPlaced(y,x,false); //check positioning
			if(n2->isAlive()){break;}
		}
		//y >= 5 lets forbid down ship direction
		else if(x<5 && y>=5)
		{
			n2=new Ship(5,"right"); //allocate ship
			n2->p=gDefense->points; //lets assign ship pointer to Grid points
			n2->isWellPlaced(y,x,false); //check positioning
			if(n2->isAlive()){break;}
		}
		//if both x & y < 5 all direction are ok
		else if(x<5 && y<5)
		{
			if(dir<50)
			{
				n2=new Ship(5,"down"); //allocate ship
				n2->p=gDefense->points; //lets assign ship pointer to Grid points
				n2->isWellPlaced(y,x,false); //check positioning
				if(n2->isAlive()){break;}
			}
			else
			{
				n2=new Ship(5,"down"); //allocate ship
				n2->p=gDefense->points; //lets assign ship pointer to Grid points
				n2->isWellPlaced(y,x,false); //check positioning
				if(n2->isAlive()){break;}
			}
		}
		//if both x & y >= 5 lets re-roll the dice
		else{;}
	}

	//Cruiser 2
	while(true)
	{
		x=rand()%10;
		y=rand()%10;
		dir=rand()%100;

		//x >= 5 lets forbid right ship direction
		if(x>=5 && y<5)
		{
			n3=new Ship(5,"down"); //allocate ship
			n3->p=gDefense->points; //lets assign ship pointer to Grid points
			n3->isWellPlaced(y,x,false); //check positioning
			if(n3->isAlive()){break;}
		}
		//y >= 5 lets forbid down ship direction
		else if(x<5 && y>=5)
		{
			n3=new Ship(5,"right"); //allocate ship
			n3->p=gDefense->points; //lets assign ship pointer to Grid points
			n3->isWellPlaced(y,x,false); //check positioning
			if(n3->isAlive()){break;}
		}
		//if both x & y < 5 all direction are ok
		else if(x<5 && y<5)
		{
			if(dir<50)
			{
				n3=new Ship(5,"down"); //allocate ship
				n3->p=gDefense->points; //lets assign ship pointer to Grid points
				n3->isWellPlaced(y,x,false); //check positioning
				if(n3->isAlive()){break;}
			}
			else
			{
				n3=new Ship(5,"down"); //allocate ship
				n3->p=gDefense->points; //lets assign ship pointer to Grid points
				n3->isWellPlaced(y,x,false); //check positioning
				if(n3->isAlive()){break;}
			}
		}
		//if both x & y >= 5 lets re-roll the dice
		else{;}
	}

	//Frigate 1
	while(true)
	{
		x=rand()%10;
		y=rand()%10;
		dir=rand()%100;

		//x >= 6 lets forbid right ship direction
		if(x>=6 && y<6)
		{
			n4=new Ship(4,"down"); //allocate ship
			n4->p=gDefense->points; //lets assign ship pointer to Grid points
			n4->isWellPlaced(y,x,false); //check positioning
			if(n4->isAlive()){break;}
		}
		//y >= 6 lets forbid down ship direction
		else if(x<6 && y>=6)
		{
			n4=new Ship(4,"right"); //allocate ship
			n4->p=gDefense->points; //lets assign ship pointer to Grid points
			n4->isWellPlaced(y,x,false); //check positioning
			if(n4->isAlive()){break;}
		}
		//if both x & y < 6 all direction are OK
		else if(x<6 && y<6)
		{
			if(dir<50)
			{
				n4=new Ship(4,"down"); //allocate ship
				n4->p=gDefense->points; //lets assign ship pointer to Grid points
				n4->isWellPlaced(y,x,false); //check positioning
				if(n4->isAlive()){break;}
			}
			else
			{
				n4=new Ship(4,"down"); //allocate ship
				n4->p=gDefense->points; //lets assign ship pointer to Grid points
				n4->isWellPlaced(y,x,false); //check positioning
				if(n4->isAlive()){break;}
			}
		}
		//if both x & y >= 6 lets re-roll the dice
		else{;}
	}

	//Frigate 2
	while(true)
	{
		x=rand()%10;
		y=rand()%10;
		dir=rand()%100;

		//x >= 6 lets forbid right ship direction
		if(x>=6 && y<6)
		{
			n5=new Ship(4,"down"); //allocate ship
			n5->p=gDefense->points; //lets assign ship pointer to Grid points
			n5->isWellPlaced(y,x,false); //check positioning
			if(n5->isAlive()){break;}
		}
		//y >= 6 lets forbid down ship direction
		else if(x<6 && y>=6)
		{
			n5=new Ship(4,"right"); //allocate ship
			n5->p=gDefense->points; //lets assign ship pointer to Grid points
			n5->isWellPlaced(y,x,false); //check positioning
			if(n5->isAlive()){break;}
		}
		//if both x & y < 6 all direction are OK
		else if(x<6 && y<6)
		{
			if(dir<50)
			{
				n5=new Ship(4,"down"); //allocate ship
				n5->p=gDefense->points; //lets assign ship pointer to Grid points
				n5->isWellPlaced(y,x,false); //check positioning
				if(n5->isAlive()){break;}
			}
			else
			{
				n5=new Ship(4,"down"); //allocate ship
				n5->p=gDefense->points; //lets assign ship pointer to Grid points
				n5->isWellPlaced(y,x,false); //check positioning
				if(n5->isAlive()){break;}
			}
		}
		//if both x & y >= 6 lets re-roll the dice
		else{;}
	}
	cReturn(outwin);
	print(outwin,"Attendi");mySleep(0.5);

	for(int i=0; i<3; i++)
	{
		print(outwin,".");mySleep(0.5);
	}
}

void Player::shipDeath()
{
	if(n1->isAlive()) //if ship is alive let's check its status then print a message
	{
		n1->checkPointStatus();
		if(!n1->isAlive())
		{
			print(outwin,this->getname());
			print(outwin," ha perso la portaerei");
			cReturn(outwin);
			mySleep(3);
		}
	}
	if(n2->isAlive())
	{
		n2->checkPointStatus();
		if(!n2->isAlive())
		{
			print(outwin,this->getname());
			print(outwin," ha perso l'incrociatore");
			cReturn(outwin);
			mySleep(3);
		}
	}
	if(n3->isAlive())
	{
		n3->checkPointStatus();
		if(!n3->isAlive())
		{
			print(outwin,this->getname());
			print(outwin," ha perso l'incrociatore");
			cReturn(outwin);
			mySleep(3);
		}
	}
	if(n4->isAlive())
	{
		n4->checkPointStatus();
		if(!n4->isAlive())
		{
			print(outwin,this->getname());
			print(outwin," ha perso la fregata");
			cReturn(outwin);
			mySleep(3);
		}
	}
	if(n5->isAlive())
	{
		n5->checkPointStatus();
		if(!n5->isAlive())
		{
			print(outwin,this->getname());
			print(outwin," ha perso la fregata");
			cReturn(outwin);
			mySleep(3);
		}
	}
}

bool Player::hasLost()
{
    return this->lost;
}

void Player::setLost()
{
    if(!n1->isAlive() && !n2->isAlive() && !n3->isAlive() && !n4->isAlive() && !n5->isAlive())
    {
    	this->lost=true; //checks if all ships are dead then sets lost variable
    }
    else{this->lost=false;}
}

void Player::setName(char* n)
{
    string n1(n);
    this->name=n1;
}

string Player::getname()
{
    return this->name;
}

bool Player::isAI()
{
	return this->AI;
}
