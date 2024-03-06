#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class PGM
{
protected:
	int** board;
	int numrows;
	int numcols;
	int max;
	string magic;
	string comment;
	void readInput(ifstream& infile)
	{
		const int MAX = 80;
		char buffer[MAX];
		infile.getline(buffer, MAX);
		magic = buffer;
		infile.getline(buffer, MAX);
		comment = buffer;
		infile >> numrows >> numcols >> max;
		board = new int* [numrows];
		for (int i = 0; i < numrows; i++)
		{
			board[i] = new int[numcols];
			for (int j = 0; j < numcols; j++)
			{
				infile >> board[i][j];
			}
		}
	}
public:
	PGM() : numrows(1), numcols(1), max(1) {
		board = nullptr;
		string magic = {};
		string comment = {};
	}
	PGM(ifstream& infile)
	{
		cout << "> One-arg PGM constructor called..." << endl;
		readInput(infile);
	}
	virtual ~PGM()
	{
		cout << "> Destroying a PGM object..." << endl;
		if (board != nullptr)
		{
			for (unsigned int i = 0; i < numrows; i++)
			{
				delete[] board[i];
				board[i] = nullptr;
			}
			delete[] board;
			board = nullptr;
		}
	}
	virtual PGM& operator<<(int deg) = 0;
	class exceptionClass
	{
	private:
		const char* error;
	public:
		exceptionClass(const char* e) : error(e) {}
		const char* returnError()
		{
			return error;
		}
	};
	friend void saveToPGM(const PGM& f, const char* fn)
	{
		cout << "> Saving PGM object to ASCII file..." << endl;
		ofstream outfile(fn, ios::out);
		outfile << f.magic << endl << f.comment << endl << f.numrows << " " << f.numcols << endl << f.max << endl;
		for (unsigned int i = 0; i < f.numrows; i++)
		{
			for (unsigned int j = 0; j < f.numcols; j++)
			{
				outfile << f.board[i][j] << " ";
			}
			outfile << endl;
		}
	}
};
class DarkenPGM : public PGM
{
public:
	DarkenPGM() : PGM() {}
	DarkenPGM(ifstream& infile) : PGM(infile)
	{
		cout << "> One-arg DarkenPGM constructor called" << endl;
	}
	~DarkenPGM() {
		cout << "> DarkenPGM destructor called..." << endl;
	}
	DarkenPGM& operator<<(int deg)
	{
		for (unsigned int i = 0; i < numrows; i++)
		{
			for (unsigned int j = 0; j < numcols; j++)
			{
				board[i][j] = board[i][j] - deg;
				if (board[i][j] < 0)
					board[i][j] = 0;
			}
		}
		return (*this);
	}
};
class TshirtPGM : public PGM
{
public:
	TshirtPGM() : PGM() {}
	TshirtPGM(ifstream& infile) : PGM(infile)
	{
		cout << "> One-arg TshirtPGM constructor called" << endl;
	}
	~TshirtPGM() {
		cout << "> TshirtPGM destructor called..." << endl;
	}
	TshirtPGM& operator<<(int deg)
	{
		for (unsigned int i = 0; i < numrows; i++)
		{
			for (unsigned int j = 0; j < numcols; j++)
			{
				if (board[i][j] <= (max / deg))
				{
					board[i][j] = 0;
				}
				else
				{
					board[i][j] = max;
				}
			}
		}
		return (*this);
	}
};
int main()
{
	// Open the two input image files
	ifstream file1("image1.pgm", ios::in);
	ifstream file2("image2.pgm", ios::in);
	// Instantiate objects of the derived classes
	try
	{
		DarkenPGM image1(file1);
		TshirtPGM image2(file2);
		// Close the two input image files
		file1.close();
		file2.close();
		// Declare an integer array for the amount of change
		int degree[2] = { 10, 3 };
		// Declare an array of pointers to the objects
		PGM* ptrToPGM[2] = { &image1, &image2 };
		// Use overridden virtual function for each object
		for (int i = 0; i < 2; i++)
		{
			(*(ptrToPGM[i])) << degree[i];
		}
		// Save modified images to file.
		saveToPGM(image1, "image1_mod.pgm");
		saveToPGM(image2, "image2_mod.pgm");
	}
	catch (PGM::exceptionClass e)
	{
		cout << e.returnError() << endl;
		return 0;
	}

}
