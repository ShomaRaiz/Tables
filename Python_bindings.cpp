#include "Python_bindings.h"
#include <string>
#include<QDebug>


namespace py = pybind11;
using namespace pybind11::literals;


Python::Python() {
    }

Python::~Python() {
}


void Python::calcDistributions(Paths& path) {
    py::scoped_interpreter guard{};
    
    py::module_ sys = py::module_::import("sys");
    
    std::string ad = path.home.toStdString();
    sys.attr("path").attr("append")(path.home.toStdString()); // append REPM//share//scripts//.


    py::module_ ex = py::module_::import("xtb_c_plus_plus_bindings");


    py::dict start_kwargs = py::dict(
        "mat"_a = path.mat.toStdString(),
        "par"_a = path.par.toStdString(),
        "home"_a = path.home.toStdString(),
        "proj"_a = path.proj.toStdString(),
        "rmp"_a = path.rmp.toStdString(),
        "tab"_a = path.tab.toStdString(),
        "lay"_a = path.lay.toStdString(),
        "photon"_a = path.photon,
        "electron"_a = path.electron);

    ex.attr("calc_distributions")(**start_kwargs);
}


void Python::getDistributions(Paths& path) {
    py::scoped_interpreter guard{};
    
    py::module_ sys = py::module_::import("sys");
    
    std::string ad = path.home.toStdString();
    sys.attr("path").attr("append")(path.home.toStdString()); // append REPM//share//scripts//.

    py::module_ ex = py::module_::import("xtb_c_plus_plus_bindings");

    py::dict start_kwargs = py::dict(
        "mat"_a = path.mat.toStdString(),
        "par"_a = path.par.toStdString(),
        "home"_a = path.home.toStdString(),
        "proj"_a = path.proj.toStdString(),
        "rmp"_a = path.rmp.toStdString(),
        "tab"_a = path.tab.toStdString(),
        "lay"_a = path.lay.toStdString(),
        "photon"_a = path.photon,
        "electron"_a = path.electron);

    ex.attr("get_distributions")(**start_kwargs);
}

