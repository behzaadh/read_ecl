#include "read_ecl.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <chrono>

#define AreSame(X, Y) ((abs((X)-(Y))) < 1.0e-16)

int main(void)
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    READ_ECL INIT("../Examples/2D.INIT");
    READ_ECL INSPEC("../Examples/2D.INSPEC");
    READ_ECL RSSPEC("../Examples/2D.RSSPEC");
    READ_ECL S0001("../Examples/2D.S0001");
    READ_ECL SMSPEC("../Examples/2D.SMSPEC");
    READ_ECL X0000("../Examples/2D.X0000");
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time elapsed = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;


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
        std::cout << "Successfully read PARAMS matrix!" << std::endl;
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
        std::cout << "Successfully read SWAT matrix!" << std::endl;
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
        std::cout << "Successfully read IWEL matrix!" << std::endl;
    } else {
        std::cerr << __LINE__ << ": unable to open IWEL matrix"  << std::endl;
        exit(0);
    }
    fid_IWEL.close();

    READ_ECL slb_init("../Examples/2D.INIT");
    std::ifstream fid_DX("../Examples/DX.mtx", std::ifstream::in);

    if (fid_DX.is_open()) {
        for (int i = 0; i < slb_init.Data.DATA["DX"][0].size(); ++i) {
            for (int j = 0; j < slb_init.Data.DATA["DX"].size(); ++j) {
                int b;
                fid_DX >> b;
                if (!AreSame(b, slb_init.Data.DATA["DX"][j][i])) {
                    std::cerr << __LINE__ << ":Failed to read DX matrix"  << std::endl;
                    exit(0);
                }
            }
        }
        std::cout << "Successfully read DX matrix!" << std::endl;
    } else {
        std::cerr << __LINE__ << ": unable to open DX matrix"  << std::endl;
        exit(0);
    }
    fid_DX.close();

    std::ifstream fid_LOGIHEAD("../Examples/LOGIHEAD.mtx", std::ifstream::in);

    if (fid_LOGIHEAD.is_open()) {
        for (int i = 0; i < slb_init.Data.DATA["LOGIHEAD"][0].size(); ++i) {
            for (int j = 0; j < slb_init.Data.DATA["LOGIHEAD"].size(); ++j) {
                bool b;
                fid_LOGIHEAD >> b;
                bool c = slb_init.Data.DATA["LOGIHEAD"][j][i];
                if (b != c) {
                    std::cerr << __LINE__ << ":Failed to read LOGIHEAD matrix"  << std::endl;
                    exit(0);
                }
            }
        }
        std::cout << "Successfully read LOGIHEAD matrix!" << std::endl;
    } else {
        std::cerr << __LINE__ << ": unable to open LOGIHEAD matrix"  << std::endl;
        exit(0);
    }
    fid_LOGIHEAD.close();

    READ_ECL slb_INSPEC("../Examples/2D.INSPEC");
    std::ifstream fid_NAMES("../Examples/NAMES.mtx", std::ifstream::in);

    if (fid_NAMES.is_open()) {
        for (int i = 0; i < slb_INSPEC.Data.HEADER["NAME"][0].size(); ++i) {
            for (int j = 0; j < slb_INSPEC.Data.HEADER["NAME"].size(); ++j) {
                std::string b;
                fid_NAMES >> b;
                std::string c = slb_INSPEC.Data.HEADER["NAME"][j][i];
                c.erase(std::remove(c.begin(), c.end(), ' '), c.end());
                if (b != c) {
                    std::cerr << __LINE__ << ":Failed to read LOGIHEAD matrix"  << std::endl;
                    exit(0);
                }
            }
        }
        std::cout << "Successfully read NAMES matrix!" << std::endl;
    } else {
        std::cerr << __LINE__ << ": unable to open LOGIHEAD matrix"  << std::endl;
        exit(0);
    }
    fid_NAMES.close();

    READ_ECL slb_RSSPEC("../Examples/2D.RSSPEC");
    std::ifstream fid_TYPE("../Examples/TYPE.mtx", std::ifstream::in);

    if (fid_TYPE.is_open()) {
        for (int i = 0; i < slb_RSSPEC.Data.HEADER["TYPE"][0].size(); ++i) {
            for (int j = 0; j < slb_RSSPEC.Data.HEADER["TYPE"].size(); ++j) {
                std::string b;
                fid_TYPE >> b;
                std::string c = slb_RSSPEC.Data.HEADER["TYPE"][j][i];
                c.erase(std::remove(c.begin(), c.end(), ' '), c.end());
                if (b != c) {
                    std::cerr << __LINE__ << ":Failed to read TYPE matrix"  << std::endl;
                    exit(0);
                }
            }
        }
        std::cout << "Successfully read TYPE matrix!" << std::endl;
    } else {
        std::cerr << __LINE__ << ": unable to open TYPE matrix"  << std::endl;
        exit(0);
    }
    fid_TYPE.close();


    READ_ECL slb_SMSPEC("../Examples/2D.SMSPEC");
    std::ifstream fid_DIMS("../Examples/DIMENS.mtx", std::ifstream::in);

    if (fid_DIMS.is_open()) {
        for (int i = 0; i < slb_SMSPEC.Data.DATA["DIMENS"][0].size(); ++i) {
            for (int j = 0; j < slb_SMSPEC.Data.DATA["DIMENS"].size(); ++j) {
                double b;
                fid_DIMS >> b;
                double c = slb_SMSPEC.Data.DATA["DIMENS"][j][i];
                if (!AreSame(b,c)) {
                    std::cerr << __LINE__ << ":Failed to read DIMENS matrix"  << std::endl;
                    exit(0);
                }
            }
        }
        std::cout << "Successfully read DIMENS matrix!" << std::endl;
    } else {
        std::cerr << __LINE__ << ": unable to open DIMENS matrix"  << std::endl;
        exit(0);
    }
    fid_DIMS.close();


    return 0;
}
