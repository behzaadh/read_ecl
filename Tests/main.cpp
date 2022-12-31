#include "read_ecl.h"
#include <fstream>
#include <iostream>
#include <cmath>

#define AreSame(X, Y) ((abs((X)-(Y))) < 1.0e-16)

int main(void)
{
    READ_ECL slb_sFile("../Examples/2D.S0001");

    std::ifstream fid_s("../Examples/PARAMS.mtx", std::ifstream::in);

    if (fid_s.is_open()) {
        for (int i = 0; i < slb_sFile.Data.DATA["PARAMS"][0].size(); ++i) {
            for (int j = 0; j < slb_sFile.Data.DATA["PARAMS"].size(); ++j) {
                double b;
                fid_s >> b;
                if (!AreSame(b, slb_sFile.Data.DATA["PARAMS"][j][i])) {
                    std::cerr << __LINE__ << ":Failed to read PARAMS matrix"  << std::endl;
                    exit(0);
                }
            }
        }
    } else {
        std::cerr << __LINE__ << ": unable to open PARAMS matrix"  << std::endl;
        exit(0);
    }
    fid_s.close();

    READ_ECL slb_xFile("../Examples/2D.X0000");

    std::ifstream fid_SWAT("../Examples/SWAT.mtx", std::ifstream::in);

    if (fid_SWAT.is_open()) {
        for (int i = 0; i < slb_xFile.Data.DATA["SWAT"][0].size(); ++i) {
            for (int j = 0; j < slb_xFile.Data.DATA["SWAT"].size(); ++j) {
                double b;
                fid_s >> b;
                if (!AreSame(b, slb_xFile.Data.DATA["SWAT"][j][i])) {
                    std::cerr << __LINE__ << ":Failed to read SWAT matrix"  << std::endl;
                    exit(0);
                }
            }
        }
    } else {
        std::cerr << __LINE__ << ": unable to open SWAT matrix"  << std::endl;
        exit(0);
    }
    fid_SWAT.close();

    std::ifstream fid_IWEL("../Examples/IWEL.mtx", std::ifstream::in);

    if (fid_IWEL.is_open()) {
        for (int i = 0; i < slb_xFile.Data.DATA["IWEL"][0].size(); ++i) {
            for (int j = 0; j < slb_xFile.Data.DATA["IWEL"].size(); ++j) {
                double b;
                fid_IWEL >> b;
                if (!AreSame(b, slb_xFile.Data.DATA["IWEL"][j][i])) {
                    std::cerr << __LINE__ << ":Failed to read IWEL matrix"  << std::endl;
                    exit(0);
                }
            }
        }
    } else {
        std::cerr << __LINE__ << ": unable to open IWEL matrix"  << std::endl;
        exit(0);
    }
    fid_IWEL.close();

    return 0;
}
