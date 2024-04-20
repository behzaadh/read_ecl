#include "READ_ECL.h"
#include <iterator>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

std::shared_ptr<READ_ECL> READ_ECL::_instance;

/**
 * @brief Constructs a new instance of the READ_ECL class.
 * 
 * @param filename The filename to read from.
 */
READ_ECL::READ_ECL(const std::string &filename) : _temp4(4), _temp8(8), _i(0)
{
    _byteVector = byteArray(filename.c_str());

    int     num   = 0;
    int     wsize = 0;
    std::string keyword;
    _i += sizeof(int32_t);
    while (_i < _byteVector.size()) {
        keyword = uChar2Str_b();
        // Function to remove all spaces from a given string
        keyword.erase(std::remove(keyword.begin(), keyword.end(), ' '), keyword.end());
        /*
        std::replace(keyword.begin(), keyword.end(), '+', '_');
        std::replace(keyword.begin(), keyword.end(), '-', '_');
        */

        num = uChar2Int_b();
        unsigned char type = _byteVector[_i];
        skip();
        // Skip next word
        skip();

        std::vector<double>      Vec_data;     // Double data
        std::vector<std::string> Vec_header;     // String/Char data

        int remnum = num;

        if (type == 'C') {
            remnum = num * 8;
        }

        int buflen = 0;
        int bufnum = 0;
        int maxNum = 0;
        while (remnum > 0) {
            buflen = uChar2Int_b();

            if (type == 'D') {
                bufnum = buflen / 8;
                maxNum = _i + buflen;
            } else if (type == 'C') {
                bufnum = buflen;
                maxNum = _i + buflen;
            } else {
                bufnum = buflen / 4;
                maxNum = _i + buflen;
            }

            switch (type) {
            case 'L':    // Logical or boolean is considered the same as Integer
            case 'I':{   // Integer

                while (_i < maxNum) {
                    Vec_data.push_back(uChar2Int_b());
                }

                break;
            }
            case 'R':{   // Real

                while (_i < maxNum) {
                    Vec_data.push_back(uChar2Real_b());
                }

                break;
            }
            case 'D':{   // Double

                while (_i < maxNum) {
                    Vec_data.push_back(uChar2Doub_b());
                }

                break;
            }
            case 'C':{ // Character

                while (_i < maxNum) {
                    Vec_header.push_back(uChar2Str_b());
                }
                break;
            }
            default:
                break;
            }

            remnum = remnum - bufnum;
            // Skip next word
            skip();
        }

        switch (type) {
        case 'L':    // Logical or boolean is considered the same as Integer
        case 'I':    // Integer
        case 'R':    // Real
        case 'D':{   // Double
            if (Data.DATA.find(keyword) == Data.DATA.end()) {
                Data.DATA[keyword] = Double2D{Vec_data};
            } else {
                Double2D vect = Data.DATA.at(keyword);
                if ((vect[0].size() != Vec_data.size()) && (vect.size() < 2)) {
                    Data.DATA[keyword][0].insert(Data.DATA[keyword][0].end(), Vec_data.begin(), Vec_data.end());
                } else {
                    Data.DATA[keyword].push_back(Vec_data);
                }
            }
            break;
        }
        case 'C':{   // Character
            if (Data.HEADER.find(keyword) == Data.HEADER.end()) {
                Data.HEADER[keyword] = String2D{Vec_header};
            } else {
                String2D vect = Data.HEADER.at(keyword);
                if ((vect[0].size() != Vec_header.size()) && (vect.size() < 2)) {
                    Data.HEADER[keyword][0].insert(Data.HEADER[keyword][0].end(), Vec_header.begin(), Vec_header.end());
                } else {
                    Data.HEADER[keyword].push_back(Vec_header);
                }
            }
            break;
        }
        default:
            break;
        }
        // Skip next word
        skip();
    }
}

/**
 * Retrieves the value associated with the given key.
 *
 * @param key The key to look up the value for.
 * @return The value associated with the given key.
 */
Double2D READ_ECL::value(const std::string &key)
{
    // Check if key exists
    if (Data.DATA.find(key) == Data.DATA.end()) {
        std::cout << "Could not find " << key << std::endl;
        return Double2D();
    }

    return Data.DATA.at(key);
}

/**
 * Retrieves the value from the specified column for the given key.
 *
 * @param key The key to search for.
 * @param col The column index to retrieve the value from.
 * @return A vector of double values from the specified column for the given key.
 */
std::vector<double> READ_ECL::value(const std::string &key, int col)
{
    // Check if key exists
    if (Data.DATA.find(key) == Data.DATA.end()) {
        std::cout << "Could not find " << key << std::endl;
        return std::vector<double>();
    }

    return Data.DATA.at(key)[col];
}

/**
 * Retrieves the name associated with the given key.
 *
 * @param key The key for which to retrieve the name.
 * @return The name associated with the key.
 */
String2D READ_ECL::name(const std::string &key)
{
    // Check if key exists
    if (Data.HEADER.find(key) == Data.HEADER.end()) {
        std::cout << "Could not find " << key << std::endl;
        return String2D();
    }

    return Data.HEADER.at(key);
}

/**
 * Retrieves the names from the specified key and column in the ECL file.
 *
 * @param key The key to search for.
 * @param col The column index to retrieve the names from.
 * @return A vector of strings containing the names.
 */
std::vector<std::string> READ_ECL::name(const std::string &key, int col)
{
    // Check if key exists
    if (Data.HEADER.find(key) == Data.HEADER.end()) {
        std::cout << "Could not find " << key << std::endl;
        return std::vector<std::string>();
    }

    return Data.HEADER.at(key)[col];
}

/**
 * Prints the elements of a vector associated with the given key.
 *
 * @param key The key associated with the vector.
 */
void READ_ECL::printVector(const std::string &key)
{
    // Check if key exists
    if (Data.DATA.find(key) == Data.DATA.end()) {
        std::cout << "Could not find " << key << std::endl;
        return;
    }
    Double2D vect = Data.DATA.at(key);

    for (int i = 0; i < vect.size(); i++) {
        for (int j = 0; j < vect[i].size(); j++) {
            std::cout << vect[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

/**
 * @brief Creates an instance of the READ_ECL class.
 * 
 * This function creates an instance of the READ_ECL class and initializes it with the specified filename.
 * 
 * @param filename The name of the file to be read.
 */
void READ_ECL::CreateInstance(const std::string &filename)
{
    if (!READ_ECL::_instance) {
        READ_ECL::_instance = std::make_shared<READ_ECL>(filename);
    }
}

/**
 * @brief Returns a shared pointer to the singleton instance of the READ_ECL class.
 *
 * This function is used to obtain a shared pointer to the singleton instance of the READ_ECL class.
 * The singleton pattern ensures that only one instance of the class is created throughout the program's lifetime.
 *
 * @return A shared pointer to the singleton instance of the READ_ECL class.
 */
std::shared_ptr<READ_ECL> READ_ECL::getInstance()
{
    return READ_ECL::_instance;
}


/**
 * @brief Reads the contents of a file and returns them as a vector of bytes. 
 * adopted from https://stackoverflow.com/a/21802936/4027652
 * 
 * @param filename The name of the file to read.
 * @return std::vector<BYTE> The contents of the file as a vector of bytes.
 */
std::vector<BYTE> READ_ECL::byteArray(const char *filename)
{
    std::vector<BYTE> vec;
    // open the file:
    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        std::cout << "failed to open " << filename << '\n';
    } else {

        // Stop eating new lines in binary mode!!!
        file.unsetf(std::ios::skipws);

        // get its size:
        std::streampos fileSize;

        file.seekg(0, std::ios::end);
        fileSize = file.tellg();
        file.seekg(0, std::ios::beg);

        // reserve capacity
        vec.reserve(fileSize);

        // read the data:
        vec.insert(vec.begin(),
                   std::istream_iterator<BYTE>(file),
                   std::istream_iterator<BYTE>());
    }
    return vec;
}

/**
 * Converts an unsigned char to a string representation.
 *
 * @return The string representation of the unsigned char.
 */
std::string READ_ECL::uChar2Str_b()
{
    _i += 8;
    return std::string(reinterpret_cast<const char *>(&_byteVector.data()[_i-8]), 8);
}


// TODO: find a way to not construct a new vector
/**
 * Converts an unsigned char to an integer.
 *
 * @return The converted integer value.
 */
int READ_ECL::uChar2Int_b()
{
    _temp4[3] = _byteVector[_i];
    _temp4[2] = _byteVector[_i+1];
    _temp4[1] = _byteVector[_i+2];
    _temp4[0] = _byteVector[_i+3];
    _i += 4;

    return *reinterpret_cast<const int32_t*>(&_temp4[0]);
}

/**
 * Converts an unsigned char value to a double value.
 *
 * @return The converted double value.
 */
double READ_ECL::uChar2Doub_b()
{
    _temp8[7] = _byteVector[_i];
    _temp8[6] = _byteVector[_i+1];
    _temp8[5] = _byteVector[_i+2];
    _temp8[4] = _byteVector[_i+3];
    _temp8[3] = _byteVector[_i+4];
    _temp8[2] = _byteVector[_i+5];
    _temp8[1] = _byteVector[_i+6];
    _temp8[0] = _byteVector[_i+7];
    _i += 8;

    return *reinterpret_cast<const double*>(&_temp8[0]);
}

/**
 * Converts an unsigned char value to a float value.
 *
 * @return The converted float value.
 */
float READ_ECL::uChar2Real_b()
{
    _temp4[3] = _byteVector[_i];
    _temp4[2] = _byteVector[_i+1];
    _temp4[1] = _byteVector[_i+2];
    _temp4[0] = _byteVector[_i+3];
    _i += 4;

    return *reinterpret_cast<const float*>(&_temp4[0]);
}

void READ_ECL::skip()
{
    _i += 4;
}
