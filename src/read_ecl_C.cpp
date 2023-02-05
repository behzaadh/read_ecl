#include "read_ecl.h"

void Create_Instance_C(const char *filename)
{
    READ_ECL::CreateInstance(filename);
}

void value2D(const char *key, double **data)
{
    Double2D vect = READ_ECL::getInstance()->value(key);
    // Get the number of rows and columns
    int rows = vect.size();
    int cols = vect[0].size();
    // Allocate memory for the 2D array
    for (int i = 0; i < rows; i++)
    {
       for (int j = 0; j < cols; j++)
       {
          data[i][j] = vect[i][j];
       }
    }
}

void value1D(const char *key, int col, double *data)
{
    std::vector<double> vect = READ_ECL::getInstance()->value(key, col);
    data = vect.data();
}

void name2D(const char *key, char ***data)
{
    String2D vect = READ_ECL::getInstance()->name(key);
    for (int i = 0; i < vect.size(); i++) {
        for (int j = 0; j < vect[0].size(); j++) {
            strcpy(data[i][j], vect[i][j].c_str());
        }
    }
}

void name1D(const char *key, int col, char **data)
{
    std::vector<std::string> vect = READ_ECL::getInstance()->name(key, col);
    for (int i = 0; i < vect.size(); ++i) {
        strcpy(data[i], vect[i].c_str());
    }
}
