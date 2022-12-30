#include "READ_ECL.h"
#include <iterator>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

READ_ECL::READ_ECL(const std::string &filename) : _i(0)
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
        int buflen = 0;
        int bufnum = 0;
        int maxNum = 0;
        while (remnum > 0) {
            buflen = uChar2Int_b();

            if (type == 'D') {
                bufnum = buflen / 8;
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
                wsize = 1;
                num *= 8;
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
            if (data.DATA.find(keyword) == data.DATA.end()) {
                data.DATA[keyword] = std::vector<std::vector<double>>{Vec_data};
            } else {
                std::vector<std::vector<double>> vect = data.DATA.at(keyword);
                if ((vect[0].size() != Vec_data.size()) && (vect.size() < 2)) {
                    data.DATA[keyword][0].insert(data.DATA[keyword][0].end(), Vec_data.begin(), Vec_data.end());
                } else {
                    data.DATA[keyword].push_back(Vec_data);
                }

              // found
            }
            //data.DATA
            break;
        }
        case 'C':{   // Character
            break;
        }
        default:
            break;
        }
        // Skip next word
        skip();
    }
}

void READ_ECL::printVector(const std::string &key)
{
    std::vector<std::vector<double>> vect = data.DATA.at(key);

    for (int i = 0; i < vect.size(); i++) {
        for (int j = 0; j < vect[i].size(); j++) {
            std::cout << vect[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

/*!
 * \brief convert binary ECLIPSE files to bytearray to read it easily
 * \param filename: file location
 * \return
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

std::string READ_ECL::uChar2Str_b()
{
    _i += 8;
    return std::string(reinterpret_cast<const char *>(&_byteVector.data()[_i-8]), 8);
}


/*!
 * \brief uChar2Int_b
 * \param byteVector
 * \param i
 * \return
 */
// TODO: find a way to not construct a new vector
int READ_ECL::uChar2Int_b()
{
    std::vector<BYTE> temp(4);
    temp[3] = _byteVector[_i];
    temp[2] = _byteVector[_i+1];
    temp[1] = _byteVector[_i+2];
    temp[0] = _byteVector[_i+3];
    _i += 4;

    return *reinterpret_cast<const int32_t*>(&temp[0]);
}

double READ_ECL::uChar2Doub_b()
{
    std::vector<BYTE> temp(8);
    temp[7] = _byteVector[_i];
    temp[6] = _byteVector[_i+1];
    temp[5] = _byteVector[_i+2];
    temp[4] = _byteVector[_i+3];
    temp[3] = _byteVector[_i+4];
    temp[2] = _byteVector[_i+5];
    temp[1] = _byteVector[_i+6];
    temp[0] = _byteVector[_i+7];
    _i += 8;

    return *reinterpret_cast<const double*>(&temp[0]);
}

float READ_ECL::uChar2Real_b()
{
    std::vector<BYTE> temp(4);
    temp[3] = _byteVector[_i];
    temp[2] = _byteVector[_i+1];
    temp[1] = _byteVector[_i+2];
    temp[0] = _byteVector[_i+3];
    _i += 4;

    return *reinterpret_cast<const float*>(&temp[0]);
}

void READ_ECL::skip()
{
    _i += 4;
}
