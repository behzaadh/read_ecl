#include "pybind11/pybind11.h"
#include <pybind11/stl_bind.h>
#include "read_ecl.h"

// https://github.com/tiger-punch-sports-club/pybind11-tutorial

PYBIND11_MAKE_OPAQUE(std::vector<double>);
PYBIND11_MAKE_OPAQUE(std::vector<std::string>);
PYBIND11_MAKE_OPAQUE(std::vector<std::vector<double>>);
PYBIND11_MAKE_OPAQUE(std::vector<std::vector<std::string>>);
PYBIND11_MAKE_OPAQUE(std::map<std::string, Double2D>);
PYBIND11_MAKE_OPAQUE(std::map<std::string, String2D>);

PYBIND11_MODULE(read_ecl4py, m)
{
    m.doc() = "Read Eclipse data file";

    pybind11::bind_vector<std::vector<double>>(m, "VectorDouble");
    pybind11::bind_vector<std::vector<std::string>>(m, "VectorString");
    pybind11::bind_vector<std::vector<std::vector<double>>>(m, "2DVectorDouble");
    pybind11::bind_vector<std::vector<std::vector<std::string>>>(m, "2DVectorString");
    pybind11::bind_map<std::map<std::string, Double2D>>(m, "2DMapDouble");
    pybind11::bind_map<std::map<std::string, String2D>>(m, "2DMapString");

    pybind11::class_<SLB_DATA>(m, "SLB_DATA")
        .def(pybind11::init<>())
        .def_readonly("DATA", &SLB_DATA::DATA)
        .def_readonly("HEADER", &SLB_DATA::HEADER);

    pybind11::class_<READ_ECL>(m, "READ_ECL")
        .def(pybind11::init<const std::string &>())
        .def("printVector", &READ_ECL::printVector)
        .def_readonly("Data", &READ_ECL::Data);

}
