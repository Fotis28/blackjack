#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#define Size 13                  //The size of the arrays


#define spade 06                 //Used to print spade symbol
#define club 05                  //Used to print club symbol
#define diamond 04               //Used to print diamond symbol
#define heart 03                 //Used to print heart symbol
#define RESHUFFLE_AT 15   // cards left in the shoe before it is reshuffled

void showClub(int card);         // Print the card with Club symbol and take the variable "card" to show the card
void showHeart(int card);        // Print the card with Heart symbol and take the variable "card" to show the card
void showSpade(int card);        // Print the card with Spade symbol and take the variable "card" to show the card
void showDiamont( int card);     // Print the card with Diamont symbol and take the variable "card" to show the card
void showUpSideCard();           //Print the upsidedown card for the deler
int moirasmaP(int Diamont[Size],int Heart[Size],int Club[Size],int Spade[Size]); //with the help of the function "sum"and "ace" give  random card from 0 to 12 to the player and return the total of the cards
int moirasmaD(int Diamont[Size],int Heart[Size],int Club[Size],int Spade[Size]); //with the help of the function "sum"and "aceD" give  random card from 0 to 12 to the deler and retunr the total of the cards
int ace();                       // Give the choice to the player what he/she want to be the price of card 1 or 11 
int aceD();                      // Choice auto what the price of the card ace will be 1 or 11 for the deler 
int Ask_BetP(int AbetP);         // Ask the bet from the player 
void Test_betP(int AbetP,int AbetD,int *betD,int *betP);  // Test if the bet which was given have all the ineligible
int winner(int sumP,int sumD,int *ptr1,int *ptr2,int betP); // take the total of the player and the deler and find the winner.Return the 1 for the plaer  0 for the deler and -1 for Draw
int drawCard(int Diamond[Size], int Heart[Size], int Club[Size], int Spade[Size], int *suit);
int cardValue(int card, int isPlayer);


int main()
{  int AbetP,AbetD,betP,betD,plD,plP;
   AbetP=AbetD=100; //The start bujet of the two players
   int i,Diamont[Size],Heart[Size],Club[Size],Spade[Size],choice,p;
   plD=0; //show the wins of the deler
   plP=0; // show the wins of the player
   char choice_for_the_play[5];//Array for sring
   
   for (i = 0; i < Size; i++)//Fill the arrays 
   {
    Diamont[i]=1;
    Heart[i]=1;
    Club[i]=1;
    Spade[i]=1;
   }
   srand(time(NULL));
  do
   {
  
    
   int sumP=0;//the start total of the cards for the player 
   int sumD=0;// the start total of the cards for the deler 
    do
    {
      printf("Do you want to start the game(yes/no):");
       scanf("%4s",choice_for_the_play);
    } while ((strcmp(choice_for_the_play,"yes"))&&(strcmp(choice_for_the_play,"no")));
    if(strcmp(choice_for_the_play,"yes")==0 &&(AbetD!=0)&&(AbetP!=0))//&&sumpl>=13)
    {
      betP=Ask_BetP(AbetP);//The bet from the player 
     Test_betP(AbetP,AbetD,&betD,&betP);
     AbetD-=betP;
     AbetP-=betP;
     int sumB=betP;//variable for the total bet 
    do
    {
     do
     {
      printf("\nType 1 to hit card: ");
      printf("\nType 2 to stande: ");
      printf("\ntype 3 to raize your bet:");
      printf("\nGive your choice:");
      if (scanf("%d", &choice) != 1) { while (getchar() != '\n'); choice = 0; }
     } while ((choice!=1)&&(choice!=2)&&(choice!=3));
     if(choice==1&&sumP<=21)
     {
     sumP+=moirasmaP(Diamont,Heart,Club,Spade);
     printf("\nThe Playr  card is: %d",sumP);
     }
     if(choice==3)
     {
        betP=Ask_BetP(AbetP);
        Test_betP(AbetP,AbetD,&betD,&betP);
        AbetP-=betP;
        AbetD-=betP;
        sumB+=betP;
     }
   }while (choice!=2&& sumP<21);
   while(sumD<17)
   {
    sumD+=moirasmaD(Diamont,Heart,Club,Spade);
   }
   printf("\nThe total of your card is: %d",sumP);
   printf("\nThe total of the deler card is: %d",sumD);
   p=winner(sumP,sumD,&AbetP,&AbetD,sumB);
   if(p==0)
   {
    plP++;
    printf("\nThe winner is the Player!!!");
   }
   else if(p==1)
   {
    plD++;
    printf("\nThe winner is the Deler!!!");
   }
   else
   {
    printf("\nIt's a DRAW!!!");
   }
   

  system("pause");
  system("cls");
  printf("\nThe player wallet is: %d. His wins: %d and his loose: %d",AbetP,plP,plD);
  printf("\nThe Deler wallet is: %d. His wins: %d and his loose: %d\n",AbetD,plD,plP);

    }
    else if((AbetD==0)&&(AbetP!=0))
    { 
    
      printf("Sorry but the deler money is:%d and the player money is: %d .So you can't play another game",AbetD,AbetP);
      break;
    }
    else if((AbetD!=0)&&(AbetP==0))
    { 
    
      printf("Sorry but the deler money is:%d and the player money is: %d .So you can't play another game",AbetD,AbetP);
      break;
    }
    else
    {
    break;
    }
  //---------------------------------------------------------------------
   
  //printf("\nThe player wallet is: %d. His wins: %d and his loose: %d",AbetP,plP,plD);
   //printf("\nThe Deler wallet is: %d. His wins: %d and his loose: %d\n",AbetD,plD,plP);
    

  
    }while((strcmp(choice_for_the_play,"no")!=0));
    printf("\nThe player wallet is: %d. His wins: %d and his loose: %d",AbetP,plP,plD);
    printf("\nThe Deler wallet is: %d. His wins: %d and his loose: %d\n",AbetD,plD,plP);

}

// Draws a random card that is still in the shoe and removes it.
// When the shoe runs low it is reshuffled automatically, like in a real casino,
// so the game never stops for lack of cards. Returns the card index 0-12.
int drawCard(int Diamond[Size], int Heart[Size], int Club[Size], int Spade[Size], int *suit)
{
    int *decks[4];
    int remaining = 0;
    int s, c, card;

    decks[0] = Diamond;
    decks[1] = Heart;
    decks[2] = Club;
    decks[3] = Spade;

    for (s = 0; s < 4; s++)
        for (c = 0; c < Size; c++)
            remaining += decks[s][c];

    /* Reshuffle point: with fewer than RESHUFFLE_AT cards left the shoe is refilled */
    if (remaining < RESHUFFLE_AT) {
        for (s = 0; s < 4; s++)
            for (c = 0; c < Size; c++)
                decks[s][c] = 1;
        printf("\n--- The deck was reshuffled ---\n");
    }

    do {
        s = rand() % 4;
        card = rand() % Size;
    } while (decks[s][card] == 0);

    decks[s][card] = 0;
    *suit = s + 1;
    return card;
}

int moirasmaP(int Diamont[Size],int Heart[Size],int Club[Size],int Spade[Size])
{
  int suit;
  int card = drawCard(Diamont, Heart, Club, Spade, &suit);

  switch (suit) {
    case 1: showDiamont(card); break;
    case 2: showHeart(card);   break;
    case 3: showClub(card);    break;
    case 4: showSpade(card);   break;
  }

  return cardValue(card, 1);
}

int moirasmaD(int Diamont[Size],int Heart[Size],int Club[Size],int Spade[Size])
{
  int suit;
  int card = drawCard(Diamont, Heart, Club, Spade, &suit);

  showUpSideCard();
  (void)suit;   // the dealer's card is dealt face down, so the suit is not shown

  return cardValue(card, 0);
}



int ace()
{ int choice;
    do
    {
        printf("What the Ace card want to be 1 or 11");
        if (scanf("%d", &choice) != 1) { while (getchar() != '\n'); choice = 0; }
    }while((choice!=1)&&(choice!=11));
    if(choice==1)
    {
        return 1;
    }
    else 
     {
        return 11;
     }

}

void showClub(int card)
{
if (card<=8 && card>0)
	{
	
 printf("-------\n");
    printf("|%c    |\n", club);
    printf("|  %d |\n", card+1);
    printf("|    %c|\n", club);
    printf("-------\n");
	
    }
	else if(card==10)
	{
 printf("-------\n");
    printf("|%c    |\n", club);
    printf("|  J  | \n");
    printf("|    %c|\n", club);
    printf("-------\n");
		
	}
	else if(card==11)
	{
	printf("-------\n");
    printf("|%c    |\n", club);
    printf("|  Q  |\n");
    printf("|    %c|\n", club);
    printf("-------\n");
	}
	
	else if(card==12)
	{
 printf("-------\n");
    printf("|%c    |\n", club);
    printf("|  K  |\n");
    printf("|    %c|\n", club);
    printf("-------\n");
	}
	else if (card==0)
	{
	 printf("-------\n");
    printf("|%c    |\n", club);
    printf("|  A  |\n");
    printf("|    %c|\n", club);
    printf("-------\n");
   }
   else if(card==9 )
	{
	
 printf("-------\n");
    printf("|%c    |\n", club);
    printf("|  %d |\n", card+1);
    printf("|    %c|\n", club);
    printf("-------\n");
    }  
	
	
}

void showHeart(int card)
{
		if (card<=8 && card>0)
	{
	
 printf("-------\n");
    printf("|%c    |\n", heart);
    printf("|  %d  |\n", card+1);
    printf("|    %c|\n", heart);
    printf("-------\n");
	
    }
	else if(card==10)
	{
 printf("-------\n");
    printf("|%c    |\n", heart);
    printf("|  J  | \n");
    printf("|    %c|\n", heart);
    printf("-------\n");
		
	}
	else if(card==11)
	{
	printf("-------\n");
    printf("|%c    |\n", heart);
    printf("|  Q  |\n");
    printf("|    %c|\n", heart);
    printf("-------\n");
	}
	
	else if(card==12)
	{
 printf("-------\n");
    printf("|%c    |\n", heart);
    printf("|  K  |\n");
    printf("|    %c|\n", heart);
    printf("-------\n");
	}
	else if (card==0)
	{
	 printf("-------\n");
    printf("|%c    |\n", heart);
    printf("|  A  |\n");
    printf("|    %c|\n", heart);
    printf("-------\n");
   }
   else if (card==9 )
	{
	
 printf("-------\n");
    printf("|%c    |\n", heart);
    printf("|  %d |\n", card+1);
    printf("|    %c|\n", heart);
    printf("-------\n");
    } 
	
}

void showSpade(int card)
{
	if (card<=8 && card>0)
	{
	
 printf("-------\n");
    printf("|%c    |\n", spade);
    printf("|  %d  |\n", card+1);
    printf("|    %c|\n", spade);
    printf("-------\n");
	
    }
	else if(card==10)
	{
 printf("-------\n");
    printf("|%c    |\n", spade);
    printf("|  J  | \n");
    printf("|    %c|\n", spade);
    printf("-------\n");
		
	}
	else if(card==11)
	{
	printf("-------\n");
    printf("|%c    |\n", spade);
    printf("|  Q  |\n");
    printf("|    %c|\n", spade);
    printf("-------\n");
	}
	
	else if(card==12)
	{
 printf("-------\n");
    printf("|%c    |\n", spade);
    printf("|  K  |\n");
    printf("|    %c|\n", spade);
    printf("-------\n");
	}
	else if (card==0)
	{
	 printf("-------\n");
    printf("|%c    |\n", spade);
    printf("|  A  |\n");
    printf("|    %c|\n", spade);
    printf("-------\n");
   }
   else if(card==9 )
	{
	
 printf("-------\n");
    printf("|%c    |\n", spade);
    printf("|  %d |\n", card+1);
    printf("|    %c|\n", spade);
    printf("-------\n");
   }
	
}

void showDiamont(int card)
{
	if (card<=8 && card>0)
	{
	
 printf("-------\n");
    printf("|%c    |\n", diamond);
    printf("|  %d  |\n", card+1);
    printf("|    %c|\n", diamond);
    printf("-------\n");
	
    }
	else if(card==10)
	{
 printf("-------\n");
    printf("|%c    |\n", diamond);
    printf("|  J  | \n");
    printf("|    %c|\n", diamond);
    printf("-------\n");
		
	}
	else if(card==11)
	{
	printf("-------\n");
    printf("|%c    |\n", diamond);
    printf("|  Q  |\n");
    printf("|    %c|\n", diamond);
    printf("-------\n");
	}
	
	else if(card==12)
	{
 printf("-------\n");
    printf("|%c    |\n", diamond);
    printf("|  K  |\n");
    printf("|    %c|\n", diamond);
    printf("-------\n");
	}
	else if (card==0)
	{
	 printf("-------\n");
    printf("|%c    |\n", diamond);
    printf("|  A  |\n");
    printf("|    %c|\n", diamond);
    printf("-------\n");
   }
   else if(card==9 )
	{
	
 printf("-------\n");
    printf("|%c    |\n", diamond);
    printf("|  %d |\n", card+1);
    printf("|    %c|\n", diamond);
    printf("-------\n");
    }  
	
	
}


// Returns the value of a card. isPlayer = 1 lets the player choose 1 or 11 for an ace.
int cardValue(int card, int isPlayer)
{
    if (card == 0) return isPlayer ? ace() : aceD();
    if (card >= 10) return 10;
    return card + 1;
}

int aceD()
{ 
  int choice=rand()%(2-1+1)+1;
    if(choice==1)
    {
        return 1;
    }
    else 
     {
        return 11;
     }

}

void showUpSideCard()
{

printf("--------\n");
    printf("|      |\n");
    printf("|      |\n");
    printf("|      |\n");
    printf("--------\n");
}

int Ask_BetP(int AbetP)
{
    int betP;
    do {
        printf("Give your bet (1 - %d): ", AbetP);
        if (scanf("%d", &betP) != 1) {
            while (getchar() != '\n');
            betP = 0;
        }
    } while (betP <= 0 || betP > AbetP);
    return betP;
}

void Test_betP(int AbetP,int AbetD,int *betD,int *betP)
{
  if(AbetP>AbetD)
   {
    do
    {
      if(*betP<=AbetD)
      { 
        *betD=*betP;
      }
      else
      {
        printf("The second player(deler) do not have so many money");
        *betP=Ask_BetP(AbetP);
      }
    } while (*betP>AbetD);
   }
   else if(AbetP<AbetD )
   {
    do
    {
      if(AbetP>=*betP)
      { 
        
        *betD=*betP;
      }
      else
      {
        printf("The first player do not have so many money");
        *betP=Ask_BetP(AbetP);
      }
    } while (AbetP<*betP);
   }
   else if(AbetP==AbetD)
   {
     
    *betD=*betP;
   }
}

// Returns 0 if the player wins, 1 if the dealer wins, -1 on a draw.
int winner(int sumP, int sumD, int *walletP, int *walletD, int bet)
{
    if (sumP > 21)    { *walletD += bet * 2; return 1; }
    if (sumD > 21)    { *walletP += bet * 2; return 0; }
    if (sumP == sumD) { *walletP += bet; *walletD += bet; return -1; }
    if (sumP > sumD)  { *walletP += bet * 2; return 0; }

    *walletD += bet * 2;
    return 1;
}
		

