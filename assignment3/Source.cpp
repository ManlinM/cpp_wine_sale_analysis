#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
using namespace std;
//Name:Manlin Mao
//Purpose:a program that produces analysis of 
//sales of wine data for a local wine store

const int SIZE = 25;
const int QUATER_SALES = 4;


void loadArrays(ifstream&, string[], double[][QUATER_SALES], int&);
void printReport(ofstream&, const string[], const double[][QUATER_SALES],
	const double[], int, int);
void computeSum(const double[][QUATER_SALES], double[], int);
void mostWineSold(const double[], int&, int);
void findWine(const double[][QUATER_SALES], int&, int&, int);

int main()
{
	double salesAmt[SIZE][4];  //no need to change your variable names to match mine!
	string wine[SIZE];
	double yearlySales[SIZE] = { 0.00 };
	int noWines;
	int highestRow, highestCol, mostSold;
	cout << fixed << setprecision(2);
	ifstream fin("wines.dat");
	if (!fin.is_open())
	{
		cout << "error opening wines.dat file - contact systems";
		system("pause");
		exit(-1);
	}
	ofstream fout("winesales.rpt");
	if (!fout.is_open())
	{
		cout << "error opening winesales.rpt file - contact systems";
		system("pause");
		exit(-2);
	}
	fout << fixed << setprecision(2);

	cout << "\n\nLoad arrays\n\n";
	loadArrays(fin, wine, salesAmt, noWines);
	cout << "\n\n=======================================================\n\n";

	cout << "\n\nCompute yearly Sale\n\n";
	computeSum(salesAmt, yearlySales, noWines);
	cout << "\n\n=======================================================\n\n";

	cout << "\n\nFind best selling wine and highest sales amount:\n\n";
	findWine(salesAmt, highestRow, highestCol, noWines);
	cout << "\n\n" << wine[highestRow] << " had the highest sales amount = $"
		<< salesAmt[highestRow][highestCol] << endl;
	cout << "\n\n=======================================================\n\n";

	cout << "\n\nFind the most sold wine:\n\n";
	mostWineSold(yearlySales, mostSold, noWines);
	cout << "\n\n Most sold wine is " << wine[mostSold] << endl;

	cout << "\n\n=======================================================\n\n";
	printReport(fout, wine, salesAmt, yearlySales, mostSold, noWines);
	cout << "\n\n=======================================================\n\n";

	cout << "program ended successfully" << endl;
	cout << "\n\n Printing wines.dat file\n\n";
	system("type wines.dat");
	cout << "\n\n Printing winesales.rpt file\n\n";
	system("type winesales.rpt");
	system("pause");
}//end of main

//function that compute sum of each wine's quarterly sales

void computeSum(const double quarterlyWineSales[][QUATER_SALES],
	double yearlySales[], int noWines)
{
	for (int row = 0; row < noWines; row++)
	{
		for (int col = 0; col < QUATER_SALES; col++)
		{
			yearlySales[row] += quarterlyWineSales[row][col];
		}
	}
}

//function that find the type of wine with the most sales
void mostWineSold(const double yearlySales[], int& mostSold, int noWines)
{
	mostSold = 0;
	for (int index = 1; index < noWines; index++)
	{
		if (yearlySales[index] > yearlySales[mostSold])
		{
			mostSold = index;
		}
	}
}

//loadArrays
void loadArrays(ifstream& fin, string wineName[],
	double quarterlyWineSales[][QUATER_SALES], int& noWines)
{

	for (noWines = 0; noWines < SIZE; noWines++)
	{
		getline(fin, wineName[noWines]);
		if (fin.eof())
			break;

		for (int col = 0; col < QUATER_SALES; col++)
		{
			fin >> quarterlyWineSales[noWines][col];
		}

		fin.ignore(80, '\n');
	}

}

//function that will find the highest quarterly sales amount
void findWine(const double price[][QUATER_SALES], int& highestRow,
	int& highestCol, int noWines)
{
	highestRow = 0; highestCol = 0;
	for (int row = 0; row < noWines; row++)
	{
		for (int col = 0; col < QUATER_SALES; col++)
		{
			if (price[row][col] > price[highestRow][highestCol])
			{
				highestRow = row;
				highestCol = col;
			}
		}
	}
}

//print a report function
void printReport(ofstream& fout, const string wineName[],
	const  double price[][QUATER_SALES],
	const double yearlySale[], int mostSold, int length)
{
	double total = 0.0;

	fout << "Wine" << setw(60) << "Quarterly Sales" << endl;
	fout << right << setw(20) << "1st"
		<< right << setw(15) << "2nd"
		<< right << setw(15)
		<< "3rd" << right << setw(15) << "4th"
		<< right << setw(20) << "Yearly" << endl;
	fout << endl;
	for (int row = 0; row < length; row++)
	{

		fout << left << setw(5) << wineName[row];

		for (int col = 0; col < QUATER_SALES; col++)
		{
			fout << setw(15) << right << price[row][col];

		}
		fout << right << setw(20) << yearlySale[row];
		if (row == mostSold)
		{

			fout << "*** most sold ***";
		}
		fout << endl;
		total += yearlySale[row];

	}
	fout << endl;
	fout << "Total Sales Amount $" << total << endl;

	system("type winesales.rpt");
}
/*


Load arrays



=======================================================



Compute yearly Sale



=======================================================



Find best selling wine and highest sales amount:



White had the highest sales amount = $300000.00


=======================================================



Find the most sold wine:



 Most sold wine is White


=======================================================

Wine                                             Quarterly Sales
				 1st            2nd            3rd            4th              Yearly

Red        200000.00       50000.00       57000.00       16800.00           323800.00
Rose        25000.00           0.00        4500.00        7800.00            37300.00
White      300000.00        4400.00       23000.00        5300.00           332700.00*** most sold ***

Total Sales Amount $693800.00


=======================================================

program ended successfully


 Printing wines.dat file

Red
200000.00       50000.00        57000.00        16800.00
Rose
25000.00                0.00      4500.00         7800.00
White
300000.00            4400.00            23000.00              5300.00

 Printing winesales.rpt file

Wine                                             Quarterly Sales
				 1st            2nd            3rd            4th              Yearly

Red        200000.00       50000.00       57000.00       16800.00           323800.00
Rose        25000.00           0.00        4500.00        7800.00            37300.00
White      300000.00        4400.00       23000.00        5300.00           332700.00*** most sold ***

Total Sales Amount $693800.00
Press any key to continue . . .
*/