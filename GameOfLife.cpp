#include <iostream>
#include <string> 
#include <fstream> //for files
#include <cstdlib> //rand(), srand()
#include <ctime>

using namespace std;

const unsigned short MAX_ROWS = 80;
const unsigned short MAX_COLS = 80;

const unsigned short STARTING_ROWS = 16;
const unsigned short STARTING_COLS = 8;

const unsigned short NEW_GAME = 1;
const unsigned short LOAD_GAME = 2;
const unsigned short EXIT = 3;

const unsigned short STEP_FORWARD = 1;
const unsigned short RESIZE = 2;
const unsigned short TOGGLE_CELL = 3;
const unsigned short CLEAR = 4;
const unsigned short RANDOMIZE = 5;
const unsigned short SAVE_TO_FILE = 6;
const unsigned short END = 7;

const unsigned short LOWEST_CHANCE = 1000;

void printStartingMenu()
{
	cout << endl;
	cout << "GAME OF LIFE" << endl;
	cout << "==============" << endl;
	cout << "1.New Game" << endl;
	cout << "2.Load Game" << endl;
	cout << "3.Exit" << endl;
	cout << "==============" << endl;
	return;
}

void printInGameMenu()
{
	cout << endl;
	cout << "SELECT OPTION:" << endl;
	cout << "==============" << endl;
	cout << "1.Step Forward" << endl;
	cout << "2.Resize" << endl;
	cout << "3.Toggle cell" << endl;
	cout << "4.Clear" << endl;
	cout << "5.Randomize" << endl;
	cout << "6.Save to file" << endl;
	cout << "7.End" << endl;
	cout << "==============" << endl;
	return;
}

unsigned short countDigits(int number)
{
	unsigned short count = 0;
	while (number)
	{
		number /= 10;
		count++;
	}
	return count;
}

bool isNumberBetween(const int number, const int start, const int last)
{
	return number >= start && number <= last;
}

void validate(int& number, const short start, const short last)
{
	while (!isNumberBetween(number, start, last))
	{
		cout << endl << "Input should be between " << start << " and " << last << ", try again: " << endl;
		cin.clear();//if user tries to type above MaxInt or below MinInt
		cin.ignore(100, '\n'); //for symbols
		cin >> number;
	}
	return;
}

void printField(const bool field[MAX_ROWS][MAX_COLS], const int currRows, const int currCols)
{
	cout << endl;
	for (int i = 0; i < countDigits(currRows); i++)
	{
		cout << ' ';
	}
	if (currCols > 1)
	{
		cout << '1';
	}
	for (int i = 0; i < currCols - 2; i++)
	{
		cout << ' ';
	}
	cout << currCols << endl;
	for (int i = 0; i < currRows; i++)
	{
		if (i == 0)
		{
			for (int i = 0; i < countDigits(currRows) - 1; i++)
			{
				cout << ' ';
			}
			cout << '1'; //first row
		}
		else if (i == (currRows - 1))
		{
			cout << currRows; //last row
		}
		else
		{
			for (int i = 0; i < countDigits(currRows); i++)
			{
				cout << ' ';
			}
		}

		for (int j = 0; j < currCols; j++)
		{
			if (field[i][j])
			{
				cout << '@';
			}
			else
			{
				cout << '-';
			}
		}
		cout << endl;
	}
	return;
}

unsigned short countOfNeighbors(const bool field[MAX_ROWS][MAX_COLS], const int currRows, const int currCols, const int x, const int y)
{
	unsigned short count = 0;

	if (x - 1 >= 0) //up
	{
		if (field[x - 1][y])
		{
			++count;
		}
		if (y - 1 >= 0 && field[x - 1][y - 1]) //up-left
		{
			++count;
		}
		if (y + 1 <= currCols && field[x - 1][y + 1]) //up-right
		{
			++count;
		}
	}

	if (x + 1 <= currRows) //down
	{
		if (field[x + 1][y])
		{
			++count;
		}
		if (y - 1 >= 0 && field[x + 1][y - 1]) //down-left
		{
			++count;
		}
		if (y + 1 <= currCols && field[x + 1][y + 1]) //down-right
		{
			++count;
		}
	}

	if (y - 1 >= 0 && field[x][y - 1]) //left
	{
		++count;
	}

	if (y + 1 <= currCols && field[x][y + 1]) //right
	{
		++count;
	}

	return count;
}

void sizePlus1onRight(bool field[MAX_ROWS][MAX_COLS], bool fieldAfterStepForward[MAX_ROWS][MAX_COLS],
	const int currRows, const int currCols, int& currColsAfter)
{
	if (currColsAfter >= MAX_COLS)
	{
		return;
	}
	bool gotWiderRight = false;
	for (int i = 1; i < currRows - 1; i++)
	{
		if (field[i - 1][currCols - 1] && field[i][currCols - 1] && field[i + 1][currCols - 1])
		{
			if (!gotWiderRight)
			{
				++currColsAfter;
			}
			fieldAfterStepForward[i][currColsAfter - 1] = true;
			gotWiderRight = true;
		}
	}
	return;
}

void sizePlus1onLeft(bool field[MAX_ROWS][MAX_COLS], bool fieldAfterStepForward[MAX_ROWS][MAX_COLS],
	const int currRows, const int currRowsAfter, int& currColsAfter)
{
	if (currColsAfter >= MAX_COLS)
	{
		return;
	}
	bool gotWiderLeft = false;
	for (int i = 1; i < currRows - 1; i++)
	{
		if (field[i - 1][0] && field[i][0] && field[i + 1][0])
		{
			if (!gotWiderLeft)
			{
				++currColsAfter;
				for (int i = 0; i < currRowsAfter; i++)
				{
					for (int j = currColsAfter - 1; j > 0; j--)
					{
						fieldAfterStepForward[i][j] = fieldAfterStepForward[i][j - 1];
					}
					fieldAfterStepForward[i][0] = false;
				}
			}
			fieldAfterStepForward[i][0] = true;
			gotWiderLeft = true;
		}
	}
	return;
}

void sizePlus1Down(bool field[MAX_ROWS][MAX_COLS], bool fieldAfterStepForward[MAX_ROWS][MAX_COLS],
	const int currRows, const int currCols, int& currRowsAfter)
{
	if (currRowsAfter >= MAX_ROWS)
	{
		return;
	}
	bool gotWiderDown = false;
	for (int i = 1; i < currCols - 1; i++)
	{
		if (field[currRows - 1][i - 1] && field[currRows - 1][i] && field[currRows - 1][i + 1])
		{
			if (!gotWiderDown)
			{
				++currRowsAfter;
			}
			fieldAfterStepForward[currRowsAfter - 1][i] = true;
			gotWiderDown = true;
		}
	}
	return;
}
void sizePlus1onUp(bool field[MAX_ROWS][MAX_COLS], bool fieldAfterStepForward[MAX_ROWS][MAX_COLS],
	const int currCols, int& currRowsAfter, const int currColsAfter)
{
	if (currRowsAfter >= MAX_ROWS)
	{
		return;
	}
	bool gotWiderUp = false;
	for (int i = 1; i < currCols - 1; i++)
	{
		if (field[0][i - 1] && field[0][i] && field[0][i + 1])
		{
			if (!gotWiderUp)
			{
				++currRowsAfter;
				for (int i = currRowsAfter - 1; i > 0; i--)
				{
					for (int j = 0; j < currColsAfter; j++)
					{
						fieldAfterStepForward[i][j] = fieldAfterStepForward[i - 1][j];
					}

				}
				for (int j = 0; j < currColsAfter; j++)
				{
					fieldAfterStepForward[0][j] = false;
				}
			}
			fieldAfterStepForward[0][i] = true;
			gotWiderUp = true;
		}
	}
	return;
}
void stepForward(bool field[MAX_ROWS][MAX_COLS], int& currRows, int& currCols)
{
	bool fieldAfterStepForward[MAX_ROWS][MAX_COLS] = { {false} };
	int currRowsAfterStepForward = currRows;
	int currColsAfterStepForward = currCols;

	for (int i = 0; i < currRows; i++)
	{
		for (int j = 0; j < currCols; j++)
		{
			int countNeighbors = countOfNeighbors(field, currRows, currCols, i, j);
			if ((field[i][j] && countNeighbors == 2) || countNeighbors == 3)
			{
				fieldAfterStepForward[i][j] = true;
			}

		}
	}
	sizePlus1onRight(field, fieldAfterStepForward, currRows, currCols, currColsAfterStepForward);
	sizePlus1Down(field, fieldAfterStepForward, currRows, currCols, currRowsAfterStepForward);
	sizePlus1onLeft(field, fieldAfterStepForward, currRows, currRowsAfterStepForward, currColsAfterStepForward);
	sizePlus1onUp(field, fieldAfterStepForward, currCols, currRowsAfterStepForward, currColsAfterStepForward);

	currRows = currRowsAfterStepForward;
	currCols = currColsAfterStepForward;
	for (int i = 0; i < currRows; i++)
	{
		for (int j = 0; j < currCols; j++)
		{
			field[i][j] = fieldAfterStepForward[i][j];
		}
	}
	return;
}

void resizing(bool field[MAX_ROWS][MAX_COLS], int& currRows, int& currCols)
{
	cout << endl << "Enter field size (ROWS x COLUMNS): " << endl;
	cin >> currRows >> currCols;
	validate(currRows, 1, MAX_ROWS);
	validate(currCols, 1, MAX_COLS);
	if (!(currCols == MAX_COLS))
	{
		for (int i = 0; i < currRows; i++)
		{
			for (int j = currCols; j < MAX_COLS; j++)
			{
				field[i][j] = false;
			}
		}
	}
	if (!(currRows == MAX_ROWS))
	{
		for (int i = currRows; i < MAX_ROWS; i++)
		{
			for (int j = 0; j < currCols; j++)
			{
				field[i][j] = false;
			}
		}
	}
	if (!(currCols == MAX_COLS && currRows == MAX_ROWS))
	{
		for (int i = currRows; i < MAX_ROWS; i++)
		{
			for (int j = currCols; j < MAX_COLS; j++)
			{
				field[i][j] = false;
			}
		}
	}
	return;
}

void toggleCell(bool field[MAX_ROWS][MAX_COLS], const int currRows, const int currCols)
{
	cout << "Enter coordinates (x,y): ";
	int x, y;
	cin >> x >> y;
	validate(x, 1, currRows);
	validate(y, 1, currCols);
	field[x - 1][y - 1] = !field[x - 1][y - 1];
	return;
}

void clear(bool field[MAX_ROWS][MAX_COLS], const int currRows, const int currCols)
{
	for (int i = 0; i < currRows; i++)
	{
		for (int j = 0; j < currCols; j++)
		{
			field[i][j] = false;
		}
	}
	return;
}

void randomization(bool field[MAX_ROWS][MAX_COLS], const int currRows, const int currCols)
{
	cout << endl << "Enter 'X', where chance  of spawning living cell is 1/X " << endl;
	int chance;
	cin >> chance;
	validate(chance, 0, LOWEST_CHANCE); //when 0 all dead, when 1 all alive
	if (!chance)
	{
		clear(field, currRows, currCols);
		return;
	}
	srand(time(NULL));
	for (int i = 0; i < currRows; i++)
	{
		for (int j = 0; j < currCols; j++)
		{
			if ((1 + rand() % chance) == 1) //chance numbers between 1 and chance, chance to get 1 is 1/chance
			{
				field[i][j] = true;
			}
			else
			{
				field[i][j] = false;
			}
		}
	}
	return;
}

void saveToFileValid(const bool field[MAX_ROWS][MAX_COLS], const int currRows, const int currCols, const string fileName)
{
	ofstream saveFile(fileName);
	if (saveFile.is_open())
	{
		int mostLeftPosition, mostRightPosition, highestPosition, lowestPosition;
		mostRightPosition = 0; lowestPosition = 0;
		mostLeftPosition = MAX_COLS;
		highestPosition = MAX_ROWS;
		for (int i = 0; i < currRows; i++)
		{
			for (int j = 0; j < currCols; j++)
			{
				if (field[i][j])
				{
					if (i < highestPosition)
					{
						highestPosition = i;
					}
					if (i > lowestPosition)
					{
						lowestPosition = i;
					}
					if (j < mostLeftPosition)
					{
						mostLeftPosition = j;
					}
					if (j > mostRightPosition)
					{
						mostRightPosition = j;
					}
				}
			}
		}
		if (highestPosition > lowestPosition || mostLeftPosition > mostRightPosition)
		{
			saveFile.close();
			cout << endl << "File saved successfully!" << endl;
			return;
		}
		for (int i = highestPosition; i <= lowestPosition; i++)
		{
			for (int j = mostLeftPosition; j <= mostRightPosition; j++)
			{
				saveFile << (field[i][j] ? '@' : '-');
			}
			saveFile << endl;
		}
		saveFile.close();
		cout << endl << "File saved successfully!" << endl;
	}
	else
	{
		cout << endl << "Unable to save." << endl;
	}
	return;
}

void saveToFile(const bool field[MAX_ROWS][MAX_COLS], const int currRows, const int currCols)
{
	cout << endl << "Enter the name of the file (format must be <name>.txt):" << endl;
	string fileName;
	cin >> fileName;
	ifstream existingFile(fileName);
	if (existingFile.is_open())
	{
		existingFile.close();
		cout << endl << "Didn't save, because file with this name has already been created." << endl;
		return;
	}
	saveToFileValid(field, currRows, currCols, fileName);
	return;
}

unsigned int myStrLength(const string text)
{
	unsigned int count = 0;
	for (int i = 0; text[i] != '\0'; i++)
	{
		++count;
	}
	return count;
}

void loadStartingField(bool field[MAX_ROWS][MAX_COLS], int& currRows, int& currCols, const string fileName)
{
	ifstream file(fileName);
	string lineRow;
	unsigned int row = 0;
	bool colsTaken = false;
	while (getline(file, lineRow) && row < MAX_ROWS)
	{
		if (!colsTaken)
		{
			(myStrLength(lineRow) < MAX_COLS) ? (currCols = myStrLength(lineRow)) : (currCols = MAX_COLS);
			colsTaken = true;
		}
		for (int i = 0; i < myStrLength(lineRow); i++)
		{
			if (lineRow[i] == '@')
			{
				field[row][i] = true;
			}
			else //if the file has other symbols except '@', '-' , it turns them into '-'.
			{
				field[row][i] = false;
			}
		}
		++row;
	}
	currRows = row;
	file.close();
	return;
}

bool loadValidFieldFile(bool field[MAX_ROWS][MAX_COLS], int& currRows, int& currCols)
{
	cout << endl << "Loading existing file with name (format must be <name>.txt):" << endl;

	string fileName;
	cin >> fileName;
	ifstream file(fileName);
	if (file.is_open()) //valid
	{
		file.close();
		loadStartingField(field, currRows, currCols, fileName);
		return true;
	}
	//not valid:
	cout << endl << "There isn't a file with this name" << endl;
	return false;

}

void selectInGameOption(bool maxField[MAX_ROWS][MAX_COLS], int& currRows, int& currCols)
{
	while (true)
	{
		printField(maxField, currRows, currCols);
		printInGameMenu();
		cout << endl << "Choose option: " << endl;
		int choice_number;
		cin >> choice_number;
		validate(choice_number, STEP_FORWARD, END);

		switch (choice_number)
		{
		case STEP_FORWARD:
			stepForward(maxField, currRows, currCols);
			break;
		case RESIZE:
			resizing(maxField, currRows, currCols);
			break;
		case TOGGLE_CELL:
			toggleCell(maxField, currRows, currCols);
			break;
		case CLEAR:
			clear(maxField, currRows, currCols);
			break;
		case RANDOMIZE:
			randomization(maxField, currRows, currCols);
			break;
		case SAVE_TO_FILE:
			saveToFile(maxField, currRows, currCols);
			break;
		case END:
			return;
		}
	}
}

void selectMenuOption()
{
	while (true)
	{
		printStartingMenu();
		cout << endl << "Choose option: " << endl;
		int choice_number;
		cin >> choice_number;
		validate(choice_number, NEW_GAME, EXIT);

		if (choice_number == NEW_GAME)
		{
			bool field[MAX_ROWS][MAX_COLS] = {};
			int currentRows, currentCols = 0;
			currentRows = STARTING_ROWS;
			currentCols = STARTING_COLS;
			selectInGameOption(field, currentRows, currentCols);
		}
		else if(choice_number == LOAD_GAME)
		{
			bool field[MAX_ROWS][MAX_COLS] = {};
			int currentRows, currentCols = 0;
			if (!loadValidFieldFile(field, currentRows, currentCols))
			{
				continue;
			}
			selectInGameOption(field, currentRows, currentCols);
		}
		else if (choice_number == EXIT)
		{
			return;
		}
		else
		{
			continue;
		}
	}
}

int main()
{
	selectMenuOption();
	return 0;
}