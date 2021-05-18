#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

//The global variables are to keep the check of the home cells

int heart_p = 0; 
int diamond_p = 0;
int spade_p = 0;
int club_p = 0;

//Structure of a card

struct card
{
	char rank;
	char suit;
	int ID;
	int color;

	//0 Black
	//1 Red
	card()
	{
		rank = ' ';
		suit = ' ';
		ID = 0;
		color = 2;
	}

	void card_display()
	{
		cout << rank << suit;
	}
};

//The home cell of heart

struct heartpile
{
	card list[13]; //Total cards of hearts = 13
	int ascend_check; //To keep check that the cards are placed in ascending order
	bool done; //If the home cell is filled with ascending order hearts.

	heartpile()
	{
		ascend_check = 1;
		done = false;
	}
};

//The home cell of diamonds

struct diamondpile
{
	card list[13];
	int ascend_check;
	bool done;

	diamondpile()
	{
		ascend_check = 1;
		done = false;
	}
};

//Home cell of clubs

struct clubpile
{
	card list[13];
	int ascend_check;
	bool done;

	clubpile()
	{
		ascend_check = 1;
		done = false;
	}
};

//Home cell of spades

struct spadepile
{
	card list[13];
	int ascend_check;
	bool done;

	spadepile()
	{
		ascend_check = 1;
		done = false;
	}
};

//Shuffling the cards

void shuffle(char *cards, int n)
{
	srand(time(0));
	for (int i = 0; i < n; i++)
	{

		int r = i + (rand() % (52 - i));
		swap(cards[i], cards[r]);
	}
}

void card_initializer(card** deck, int* hidden_c, int *c, int n)
{
	char rr[] = { 'A', '2', '3', '4', '5', '6', '7', '8',
			   '9', 'T', 'J', 'Q', 'K', 'A', '2', '3', '4', '5', '6', '7', '8',
			   '9', 'T', 'J', 'Q', 'K', 'A', '2', '3', '4', '5', '6', '7', '8',
			   '9', 'T', 'J', 'Q', 'K', 'A', '2', '3', '4', '5', '6', '7', '8',
			   '9', 'T', 'J', 'Q', 'K' };
	char ss[] = { 'h', 's','d', 'c','h', 's','d', 'c','h', 's','d', 'c',
			  'h', 's','d', 'c','h', 's','d', 'c','h', 's','d', 'c','h', 's','d', 'c',
			  'h', 's','d', 'c','h', 's','d', 'c','h', 's','d', 'c','h', 's','d', 'c',
			  'h', 's','d', 'c','h', 's','d', 'c' };

	shuffle(rr, 52);
	shuffle(ss, 52);

	int k = 0;

	//Giving a rank and suit to the cards
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < c[i]; j++)
		{
			if (j < 7)
			{
				deck[i][j].rank = rr[k];
				deck[i][j].suit = ss[k];
			}
			else
			{
				deck[i][j].rank = ' ';
				deck[i][j].suit = ' ';
			}
			k++;
		}
	}

	//Assigning colors and IDs to cards according to suits and ranks respectively
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < c[i]; j++)
		{
			if (deck[i][j].suit == 'h' || deck[i][j].suit == 'd')
			{
				deck[i][j].color = 1;
			}
			else if (deck[i][j].suit == 's' || deck[i][j].suit == 'c')
			{
				deck[i][j].color = 0;
			}
			else if (deck[i][j].suit == ' ')
			{
				deck[i][j].color = 2;
			}

			if (deck[i][j].rank == 'A')
			{
				deck[i][j].ID = 1;
			}
			else if (deck[i][j].rank == '2')
			{
				deck[i][j].ID = 2;
			}
			else if (deck[i][j].rank == '3')
			{
				deck[i][j].ID = 3;
			}
			else if (deck[i][j].rank == '4')
			{
				deck[i][j].ID = 4;
			}
			else if (deck[i][j].rank == '5')
			{
				deck[i][j].ID = 5;
			}
			else if (deck[i][j].rank == '6')
			{
				deck[i][j].ID = 6;
			}
			else if (deck[i][j].rank == '7')
			{
				deck[i][j].ID = 7;
			}
			else if (deck[i][j].rank == '8')
			{
				deck[i][j].ID = 8;
			}
			else if (deck[i][j].rank == '9')
			{
				deck[i][j].ID = 9;
			}
			else if (deck[i][j].rank == 'T')
			{
				deck[i][j].ID = 10;
			}
			else if (deck[i][j].rank == 'J')
			{
				deck[i][j].ID = 11;
			}
			else if (deck[i][j].rank == 'Q')
			{
				deck[i][j].ID = 12;
			}
			else if (deck[i][j].rank == 'K')
			{
				deck[i][j].ID = 13;
			}
			else if (deck[i][j].rank == ' ')
			{
				deck[i][j].ID = 0;
			}
		}
	}
}

//Structure of a FreeCell
struct FreeCell
{
	card freecell;
	bool filled; //If the free-cell is already filled or not

	FreeCell()
	{
		filled = false;
	}

	void fill_check()
	{
		if (freecell.ID != ' ')
		{
			filled = true;
		}
		else
		{
			filled = false;
		}
	}
};

//Displaying the game
void display_game(card** deck, FreeCell* cells, int* c, int n, heartpile hp, diamondpile dp, spadepile sp, clubpile cp)
{
	for (int i = 0; i < n; i++)
	{
		cout << "Tableau " << i + 1 << ": ";
		for (int j = 0; j < c[i]; j++)
		{
			cout << "|";
			deck[i][j].card_display();
			cout << "|";
			cout << "    ";
		}
		if (i == 3)
		{
			cout << endl;
		}
		cout << endl;
	}

	cout << endl << endl;

	cout << "				  FREE CELLS" << endl << endl << "			";
	for (int i = 0; i < 4; i++)
	{
		cout << "|*";
		cells[i].freecell.card_display();
		cout << "*|" << "	";
	}

	cout << endl << endl;

	cout << "\tHeart     " << "Diamond     " << "Spade     " << " Club     " << endl << endl;

	for (int i = 0; i < 13; i++)
	{
		cout << "\t|*"; 
		hp.list[i].card_display();
		cout << "*|     |*";
		dp.list[i].card_display();
		cout << "*|     |*";
		sp.list[i].card_display();
		cout << "*|     |*";
		cp.list[i].card_display();
		cout << "*|" << endl;
	}
	
	cout << endl << endl;
}

//Will help in copying cards
void card_copier(card& a, card b)
{
	a.rank = b.rank;
	a.suit = b.suit;
	a.ID = b.ID;
	a.color = b.color;
}

//When we have to empty the free-cell
void FreeCell_emptier(FreeCell cell)
{
	cell.freecell.rank = ' ';
	cell.freecell.suit = ' ';
	cell.freecell.ID = 0;
	cell.freecell.color = 2;
	cell.filled = false;
}

//To check if the transfer from free-cell to tableau or tableau to tableau is applicable or not

bool replace_check(card a, card b)
{
	bool check = a.color ^ b.color; //If the colors are opposite,
	bool check2 = (a.ID == b.ID + 1) ? true : false; //and the ID of 1st card is 1 bigger than the next one

	bool f_check = check & check2; //Applying & on above 2 operations
	return f_check;
}

//Function to move cards from tableau to tableau
void tablutotablu(card** deck, int* c, int v, int u)
{
	u--;
	v--;
	
	int r = v;

	int l;
	cout << "How many cards do you want to transfer? ";
	cin >> l;

	int j = v - l;
	bool ch = replace_check(deck[u][c[u]-1], deck[r][c[v]-l]);


	if (!ch)
	{
		cout << "Invalid move." << endl;
	}
	else
	{
		card* cpycard = new card[l];
		int g = l;
		for (int i = 0; i < l; i++)
		{
			card_copier(cpycard[i], deck[r][c[v] - g]);
			g--;;
		}
		for (int i = 0; i < l; i++)
		{
			c[v]--;
			card_copier(deck[u][c[u]], cpycard[i]);
			c[u]++;
		}
	}
	

}

//Function to move card from tableau to free-cell

void tablutofreecell(card** deck, int* c, FreeCell cells[], int v, int u)
{
	
	u--;

	if (cells[u].filled) //If the free-cell is already filled, we cannot move the card there.
	{
		cout << "Invalid Move" << endl;
	}

	else
	{
		v--;
		c[v]--;

		card_copier(cells[u].freecell, deck[v][c[v]]);

		cells[u].filled = true;
	}

}

//Function to move card from from free-cell to tableau
void freecelltotablu(card** deck, int* c, FreeCell cells[], int v, int u)
{
	v--;
	u--;
	bool ch = replace_check(deck[u][c[u]-1], cells[v].freecell);
	
	if (!cells[v].filled || !ch) //Checking both the conditions (transfer applicability and if the free-cell is empty)
	{
		cout << "Invalid Move. " << endl;
	}
	else
	{
		cout << endl;
		card_copier(deck[u][c[u]], cells[v].freecell);

		FreeCell_emptier(cells[v]);

		c[u]++;
	}
}

//The next four functions are used to move card to home cell of hearts, diamonds, spades and clubs respectively

void tablutoheartpile(card** deck, int* c, int k, heartpile &hp)
{
	k--;
	
	if (deck[k][c[k]-1].ID == hp.ascend_check && deck[k][c[k]-1].suit == 'h') //Checking the ascending order and the suit of card
	{
		c[k]--;
		card_copier(hp.list[heart_p], deck[k][c[k]]);
		heart_p++;
		hp.ascend_check++;

	}
	else
	{
		cout << "Invalid move." << endl << endl;
	}

	if (hp.ascend_check == 13)
	{
		hp.done = true;
	}
}

void tablutodiamondpile(card** deck, int* c, int k, diamondpile& dp)
{
	k--;

	if (deck[k][c[k] - 1].ID == dp.ascend_check && deck[k][c[k] - 1].suit == 'd')
	{
		c[k]--;
		card_copier(dp.list[diamond_p], deck[k][c[k]]);
		diamond_p++;
		dp.ascend_check++;

	}
	else
	{
		cout << "Invalid move." << endl << endl;
	}

	if (dp.ascend_check == 13)
	{
		dp.done = true;
	}
}

void tablutospadepile(card** deck, int* c, int k, spadepile& sp)
{
	k--;

	if (deck[k][c[k] - 1].ID == sp.ascend_check && deck[k][c[k] - 1].suit == 's')
	{
		c[k]--;
		card_copier(sp.list[spade_p], deck[k][c[k]]);
		spade_p++;
		sp.ascend_check++;

	}
	else
	{
		cout << "Invalid move." << endl << endl;
	}

	if (sp.ascend_check == 13)
	{
		sp.done = true;
	}
}

void tablutoclubpile(card** deck, int* c, int k, clubpile& cp)
{
	k--;

	if (deck[k][c[k] - 1].ID == cp.ascend_check && deck[k][c[k] - 1].suit == 'c')
	{
		c[k]--;
		card_copier(cp.list[club_p], deck[k][c[k]]);
		club_p++;
		cp.ascend_check++;

	}
	else
	{
		cout << "Invalid move." << endl << endl;
	}

	if (cp.ascend_check == 13)
	{
		cp.done = true;
	}
}

//The next four functions are to move card from free-cell to home cell

void free_to_heart(FreeCell cells[], heartpile& hp, int v)
{
	if (cells[v].freecell.suit == 'h' && cells[v].freecell.ID == hp.ascend_check)
	{
		card_copier(hp.list[heart_p], cells[v].freecell);
		heart_p++;
		hp.ascend_check++;

		FreeCell_emptier(cells[v]);
	}
	else
	{
		cout << "Invalid move. " << endl;
	}

	if (hp.ascend_check == 13)
	{
		hp.done = true;
	}
}

void free_to_diamond(FreeCell cells[], diamondpile& dp, int v)
{
	if (cells[v].freecell.suit == 'd' && cells[v].freecell.ID == dp.ascend_check)
	{
		card_copier(dp.list[diamond_p], cells[v].freecell);
		diamond_p++;
		dp.ascend_check++;

		FreeCell_emptier(cells[v]);
	}
	else
	{
		cout << "Invalid move. " << endl;
	}

	if (dp.ascend_check == 13)
	{
		dp.done = true;
	}
}

void free_to_spade(FreeCell cells[], spadepile& sp, int v)
{
	if (cells[v].freecell.suit == 's' && cells[v].freecell.ID == sp.ascend_check)
	{
		card_copier(sp.list[spade_p], cells[v].freecell);
		sp.ascend_check++;
		spade_p++;

		FreeCell_emptier(cells[v]);
	}
	else
	{
		cout << "Invalid move. " << endl;
	}

	if (sp.ascend_check == 13)
	{
		sp.done = true;
	}
}

void free_to_club(FreeCell cells[], clubpile& cp, int v)
{
	if (cells[v].freecell.suit == 'c' && cells[v].freecell.ID == cp.ascend_check)
	{
		card_copier(cp.list[club_p], cells[v].freecell);
		club_p++;
		cp.ascend_check++;

		FreeCell_emptier(cells[v]);
	}
	else
	{
		cout << "Invalid move. " << endl;
	}

	if (cp.ascend_check == 13)
	{
		cp.done = true;
	}
}

//Function to put all the above four functions into one.
void freecelltopile(FreeCell cells[], heartpile &hp, diamondpile &dp, spadepile &sp, clubpile &cp)
{
	int v;
	int u;
	cout << "Enter the free cell number: ";
	cin >> v;
	
	v--;
	if (!cells[v].filled)
	{
		cout << "Invalid move. ";
	}
	else
	{
		cout << "Enter home cell number: ";
		cin >> u;
		if (u == 1)
		{
			free_to_heart(cells, hp, v);
		}
		else if (u == 2)
		{
			free_to_diamond(cells, dp, v);
		}
		else if (u == 3)
		{
			free_to_spade(cells, sp, v);
		}
		else if (u == 4)
		{
			free_to_club(cells, cp, v);
		}
		else
		{
			cout << "Invalid move. " << endl;
		}
	}
}
//Win condition
bool win_condition(heartpile hp, diamondpile dp, spadepile sp, clubpile cp)
{
	bool win = false;
	if (hp.done && dp.done && sp.done && cp.done) //If all the home cells are done or not
	{
		win = true;
	}

	return win;
}

//Putting everything into main.
int main()
{
	int n = 8;
	card** deck = new card*[n];
	FreeCell cells[4];
	heartpile hp;
	diamondpile dp;
	spadepile sp;
	clubpile cp;

	int m = n;
	int* c = new int[m];
	int* hidden_c = new int[m];

	for (int i = 0; i < m; i++)
	{
		hidden_c[i] = 52;
	}

	int k = 0;
	for (int i = 0; i < 4; i++)
	{
		c[k] = 7;
		k++;
	}
	for (int i = 0; i < 4; i++)
	{
		c[k] = 6;
		k++;
	}

	for (int i = 0; i < m; i++)
	{
		deck[i] = new card[hidden_c[i]];
	}

	card_initializer(deck, hidden_c, c, n);

again:
	system("cls");
	display_game(deck, cells, c, n, hp, dp, sp, cp);

	char option, home, a;
	cout << "Press 1 to move card from tableau to tableau. " << endl;
	cout << "Press 2 to move card from tableau to free-cell." << endl;
	cout << "Press 3 to move card from free cell to tableau. " << endl;
	cout << "Press 4 to move card from tableau to home cell. " << endl;
	cout << "Press 5 to move card from free-cell to homecell. " << endl;

	cin >> option;

	int x = 0, y = 0;
	if (option == '1')
	{
		cout << "Enter tableau number from which card will be transferred: ";
		cin >> x;
		cout << "Enter tableau number to which card will be transferred: ";
		cin >> y;
		tablutotablu(deck, c, x, y);
	}
	
	else if (option == '2')
	{
		cout << "Enter tableau number from which card will be transferred: ";
		cin >> x;
		cout << "Enter free-cell number to which card will be transferred: ";
		cin >> y;
		tablutofreecell(deck, c, cells, x, y);
	}

	else if (option == '3')
	{
		cout << "Enter free-cell number from which card will be transferred: ";
		cin >> x;
		cout << "Enter tableau number to which card will be transferred: ";
		cin >> y;
		freecelltotablu(deck, c, cells, x, y);
	}

	else if (option == '4')
	{
		cout << "Enter the tableau number from which card will be transferred: ";
		cin >> x;
		cout << "Enter the home cell to which card will be transferred (h: heart, d: diamond, s: spades, c: club): ";
		cin >> home;

		if (home == 'h')
		{
			tablutoheartpile(deck, c, x, hp);
		}
		else if (home == 'd')
		{
			tablutodiamondpile(deck, c, x, dp);
		}
		else if (home == 's')
		{
			tablutospadepile(deck, c, x, sp);
		}
		else if (home == 'c')
		{
			tablutoclubpile(deck, c, x, cp);
		}
		else
		{
			cout << "Invalid move " << endl;
		}

	}

	else if (option == '5')
	{
		freecelltopile(cells, hp, dp, sp, cp);
	}

	else
	{
		cout << "Invalid move." << endl;
	}

	bool ch = win_condition(hp, dp, sp, cp);
	if (!ch)
	{
		cout << "Press anything (except 0) to proceed. ";
		cin >> a;

		if (a != '0')
		{
			goto again;
		}
	}
	else
	{
		cout << "You have completed the game!. " << endl;
	}
	return 0;
}