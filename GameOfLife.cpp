#include <iostream>
#include <stdlib.h>
#include <unistd.h>

#define no_of_rows 41
#define no_of_columns 85

using namespace std;

class Matrix
{
public:
	int mat[no_of_rows][no_of_columns];

	void initialize()
	{
		for (int i = 0; i < no_of_rows; ++i)
		{
			for (int j = 0; j < no_of_columns; ++j)
			{
				mat[i][j] = 0;
			}
		}
	}

	Matrix()
	{
		initialize();
	}

	void display()
	{
		cout<<"\n";
		for (int i = 0; i < no_of_rows; ++i)
		{
			for (int j = 0; j < no_of_columns; ++j)
			{
				if(mat[i][j] == 0)
					cout<<".";
				else
					cout<<"\u25A0";
			}
			cout<<"\n";
		}
	}
};

class Game 
{
public:
	Matrix *main_matrix,*temperory_matrix;
	int counter;
	Game()
	{
		counter = 0;
		main_matrix = new Matrix;
		temperory_matrix = new Matrix;
		main_matrix->initialize();
		temperory_matrix->initialize();
	}

	~Game()
	{
		delete main_matrix;
		delete temperory_matrix;
	}

	void display_main_matrix()
	{
		main_matrix->display();
	}

	void display_temp_matrix()
	{
		temperory_matrix->display();
	}

	int modulus(int n,int m)
	{
		return ((n%m) + m)%m;
	}
	
	void copy(Matrix *m1,Matrix *m2)
	{
		for (int i = 0; i < no_of_rows; ++i)
		{
			for (int j = 0; j < no_of_columns; ++j)
			{
				m2->mat[i][j] = m1->mat[i][j];
			}
		}
	}

	int calculate_no_of_live_cells(int i,int j)
	{
		int c = 0;
		int iadd1 = modulus(i+1,no_of_rows);
		int jadd1 = modulus(j+1,no_of_columns);
		int isub1 = modulus(i-1,no_of_rows);
		int jsub1 = modulus(j-1,no_of_columns);

		if(main_matrix->mat[i][jadd1]) {c++;}
		if(main_matrix->mat[i][jsub1]) {c++;}
		if(main_matrix->mat[iadd1][jadd1]) {c++;}
		if(main_matrix->mat[iadd1][jsub1]) {c++;}
		if(main_matrix->mat[iadd1][j]) {c++;}
		if(main_matrix->mat[isub1][jadd1]) {c++;}
		if(main_matrix->mat[isub1][jsub1]) {c++;}
		if(main_matrix->mat[isub1][j]) {c++;}
		
		return c;
	}
	
	int calculate_no_of_dead_cells(int i,int j)
	{
		int c = 0;
		int iadd1 = modulus(i+1,no_of_rows);
		int jadd1 = modulus(j+1,no_of_columns);
		int isub1 = modulus(i-1,no_of_rows);
		int jsub1 = modulus(j-1,no_of_columns);

		if(!main_matrix->mat[i][jadd1]) {c++;}
		if(!main_matrix->mat[i][jsub1]) {c++;}
		if(!main_matrix->mat[iadd1][jadd1]) {c++;}
		if(!main_matrix->mat[iadd1][jsub1]) {c++;}
		if(!main_matrix->mat[iadd1][j]) {c++;}
		if(!main_matrix->mat[isub1][jadd1]) {c++;}
		if(!main_matrix->mat[isub1][jsub1]) {c++;}
		if(!main_matrix->mat[isub1][j]) {c++;}
		
		return c;
	}

	
	void calculate_temperory_matrix()
	{
		copy(main_matrix,temperory_matrix);
		for (int i = 0; i < no_of_rows; ++i)
		{
			for (int j = 0; j < no_of_columns; ++j)
			{
				if(main_matrix->mat[i][j] == 0)
				{
					int neighbour_counter = calculate_no_of_live_cells(i,j);
					if(neighbour_counter == 3)
					{
						temperory_matrix->mat[i][j] = 1;
					}					
				}
				else if(main_matrix->mat[i][j] == 1)
				{
					int neighbour_counter = calculate_no_of_live_cells(i,j);
					if((neighbour_counter < 2)||(neighbour_counter > 3))
					{
						temperory_matrix->mat[i][j] = 0;
					}
					else
					{
						temperory_matrix->mat[i][j] = 1;
					}
				}
			}
		}
		copy(temperory_matrix,main_matrix);
	}

	

	void play_game()
	{	
		//system("clear");	
		usleep(100000);
		cout<<"\n\nIttereation :- "<<++counter<<"\n\n";
		display_main_matrix();
		calculate_temperory_matrix();
	}
};

int main(int argc, char const *argv[])
{
	Game *g;
	g = new Game;
	cout<<"\n\nWelcome to Conor's Game of life simulated on C++\n\n"
		<<"\nThe Matrix is as follows :- \n";
	g->display_main_matrix();
		
	int x,y,choice = 1;
	while(choice != 3)
	{
		cout<<"\nEnter a choice :- \n"
			<<"1 ==> Generate a cell at a point.\n"
			<<"2 ==> Kill a cell at a point.\n"
			<<"4 ==> Gilder.\n"
			<<"5 ==> LWSS.\n"
			<<"3 ==> Start The game!\n"
			<<"choice ? (1/2/3) ";
		cin>>choice;
		switch(choice)
		{
			case 1:
				cout<<"\nEnter the row position :- ";
				cin>>x;
				cout<<"Enter column position :- ";
				cin>>y;
				g->main_matrix->mat[x][y] = 1;
				cout<<"\nCell Generated!\n";
				g->display_main_matrix();
				break;

			case 2:
				cout<<"\nEnter the row position :- ";
				cin>>x;
				cout<<"Enter column position :- ";
				cin>>y;
				g->main_matrix->mat[x][y] = 0;
				cout<<"\nCell Killed!\n";	
				g->display_main_matrix();
				break;

			case 3:
				cout<<"\nLet the game begin!\n";
				break;
			case 4:
				cout<<"\nEnter the row position :- ";
				cin>>x;
				cout<<"Enter column position :- ";
				cin>>y;
				g->main_matrix->mat[x + 1][y] = !g->main_matrix->mat[x + 1][y];
				g->main_matrix->mat[x + 2][y + 1] = !g->main_matrix->mat[x + 2][y + 1];
				g->main_matrix->mat[x][y + 2] = !g->main_matrix->mat[x][y + 2];
				g->main_matrix->mat[x + 1][y + 2] = !g->main_matrix->mat[x + 1][y + 2];
				g->main_matrix->mat[x + 2][y + 2] = !g->main_matrix->mat[x + 2][y + 2];
				g->display_main_matrix();
				break;
			case 5:
				cout<<"\nEnter the row position :- ";
				cin>>x;
				cout<<"Enter column position :- ";
				cin>>y;

				g->main_matrix->mat[x][y] = !g->main_matrix->mat[x][y];
				g->main_matrix->mat[x + 2][y] = !g->main_matrix->mat[x + 2][y];
				g->main_matrix->mat[x][y + 3] = !g->main_matrix->mat[x][y + 3];
				g->main_matrix->mat[x + 3][y + 1] = !g->main_matrix->mat[x + 3][y + 1];
				g->main_matrix->mat[x + 3][y + 2] = !g->main_matrix->mat[x + 3][y + 2];
				g->main_matrix->mat[x + 3][y + 3] = !g->main_matrix->mat[x + 3][y + 3];
				g->main_matrix->mat[x + 3][y + 4] = !g->main_matrix->mat[x + 3][y + 4];
				g->main_matrix->mat[x + 2][y + 4] = !g->main_matrix->mat[x + 2][y + 4];
				g->main_matrix->mat[x + 1][y + 4] = !g->main_matrix->mat[x + 1][y + 4];

				g->display_main_matrix();
			default:
				cout<<"\nWrong Input";
				break;
		}
	}	
	
	while(1)
		g->play_game();
	return 0;
	

	//cout<<g->modulus(-1,5);
	return 0;
}
