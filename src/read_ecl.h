#ifndef READ_ECL_H
#define READ_ECL_H

#include <map>
#include <string>
#include <vector>
#include <memory>
// More meaningful names for data type by aliasing existing data
// typedef was replaced with using to make the code more readable
// and consistent with the rest of the C++ language
// shorturl.at/qGT16
using BYTE = unsigned char;
using Int1D = std::vector<double>;
using Double1D = std::vector<double>;
using Double2D = std::vector<std::vector<double>>;
using String2D = std::vector<std::vector<std::string>>;

struct SLB_DATA{
    std::map<std::string, Double2D>     DATA;     // Double data
    std::map<std::string, String2D>     HEADER;   // String/Char data
};

/**
 * @class READ_ECL
 * @brief A class for reading ECL files and extracting data.
 *
 * The READ_ECL class provides methods to read ECL files and extract various types of data from them.
 * It supports reading values, names, and vectors from the ECL file.
 * The class also provides a C interface for creating an instance and accessing it.
 */
class READ_ECL {
public:
    READ_ECL(const std::string &filename);
    Double2D value(const std::string &key);
    std::vector<double> value(const std::string &key, int col);
    String2D name(const std::string &key);
    std::vector<std::string> name(const std::string &key, int col);
    void printVector(const std::string &key);
    SLB_DATA Data;

    // For c interface
    static void CreateInstance(const std::string &filename);
    static std::shared_ptr<READ_ECL> getInstance();

private:
    std::vector<BYTE> byteArray(const char* filename);

    std::string uChar2Str_b();

    // Big-endian ordering to integer
    int uChar2Int_b();

    // Big-endian ordering to double
    double uChar2Doub_b();

    // Big-endian ordering to integer
    float uChar2Real_b();

    // skip next word
    void skip();

    std::vector<BYTE> _byteVector;
    std::vector<BYTE> _temp4;
    std::vector<BYTE> _temp8;
    static std::shared_ptr<READ_ECL> _instance;
    int _i;
};

#endif // READ_ECL_H
