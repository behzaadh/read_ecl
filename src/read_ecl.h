#ifndef READ_ECL_H
#define READ_ECL_H

#include <map>
#include <string>
#include <vector>
#include <variant>
#include <stdint.h>
typedef unsigned char BYTE;

struct SLB_DATA{
    std::map<std::string, std::vector<std::vector<double>>>      DATA;     // Double data
    std::map<std::string, std::vector<std::vector<std::string>>> HEADER;     // String/Char data
};

class READ_ECL {
public:
    READ_ECL(const std::string &filename);
    void printVector(const std::string &key);
    SLB_DATA Data;

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
int _i;
};

#endif // READ_ECL_H
