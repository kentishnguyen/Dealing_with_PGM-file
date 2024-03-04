#include <iostream>
#include <fstream>
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
        
    }
public:
    PGM() : numrows(1), numcols(1), max(255) {
        board = nullptr;
        string magic = {};
        string comment = {};
    }
    PGM(ifstream& infile)
    {
        cout << "> One-arg PGM constructor called..." << endl;

    }
    ~PGM();
    virtual PGM& operator<<(int deg) = 0;
    class exceptionClass;
    friend void saveToPGM(const PGM& f, const char* fn);
};
 
class DarkenPGM : public PGM
{
private:

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
    catch(PGM::exceptionClass e)
    {
        cout << e.returnError() << endl;
        return 0;
    }
    
}