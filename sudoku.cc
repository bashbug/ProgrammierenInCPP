#include <iostream>
using namespace std;

int main(void) {

	int zeile, spalte, wunschzahl;
	int count = 0;
	
	int sudoku[9][9] = { {8, 6, 7, 3, 5, 4, 0, 2, 9}, 
	{1, 2, 9, 8, 6, 7, 5, 0, 3}, 
	{5, 0, 4, 0, 0, 9, 8, 7, 6}, 
	{4, 8, 6, 1, 9, 5, 7, 3, 2}, 
	{0, 0, 3, 7, 4, 0, 0, 1, 0}, 
	{7, 1, 2, 6, 3, 8, 0, 9, 5}, 
	{3, 4, 1, 5, 2, 6, 9, 8, 0}, 
	{6, 9, 8, 4, 0, 0, 2, 5, 1}, 
	{0, 7, 0, 9, 8, 1, 3, 6, 4} } ;

	cout << "Viel Spaß beim Lösen des folgenden Sudokus! \n \n";

	for(int i=0; i<9; i++) {
		cout << "[ ";
		for(int j=0; j<9; j++) {
			cout << sudoku[i][j] << " ";
			if(j == 2 || j == 5) {
				cout << "| ";
			} 
			if(j == 8) {
				cout << "] \n";
			}
			if((i == 2 && j == 8) || (i == 5 && j == 8)) {
				cout << "  - - - - - - - - - - -\n";
			}
		}
	}


	for (int g=0; g<9; g++) {
		for (int h=0; h<9; h++) {	
			if (sudoku[g][h] == 0) {
				if(count == 0) {
					cout << "\nIhr Wunschfeld können Sie wählen, indem Sie zuerst die Zeile (0-8) und die entsprechende Spalte (0-8) angeben \n";
					cout << "Bitte geben Sie die Zeile an: ";
					cin >> zeile;
					cout << "Bitte geben Sie die Spalte an: ";
					cin >> spalte;
					cout << "Nun geben Sie bitte an, welche Zahl Sie einfügen wollen: ";
					cin >> wunschzahl;
					cout << '\n';
					count++;
				} else {
					cout << "\nBitte geben Sie die Zeile an: ";
					cin >> zeile;
					cout << "Bitte geben Sie die Spalte an: ";
					cin >> spalte;
					cout << "Bitte geben Sie die Zahl an, die Sie einfügen wollen: ";
					cin >> wunschzahl;
					cout << '\n';
				}

				if (sudoku[zeile][spalte] == 0) {
					sudoku[zeile][spalte] = wunschzahl;
				} else {
					cout << "\nACHTUNG: In dieses Feld können Sie keine Zahl eingeben! \n \n";
				}

				for(int i=0; i<9; i++) {
					cout << "[ ";
					for(int j=0; j<9; j++) {
						cout << sudoku[i][j] << " ";
						if(j == 2 || j == 5) {
							cout << "| ";
						} 
						if(j == 8) {
							cout << "] \n";
						}
						if((i == 2 && j == 8) || (i == 5 && j == 8)) {
							cout << "  - - - - - - - - - - -\n";
						}
					}
				}
			}
		}
	}
	return 0;
}
