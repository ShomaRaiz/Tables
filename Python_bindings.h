#ifndef PYTHON_BINDS_H
#define PYTHON_BINDS_H

#include <pybind11/embed.h> // everything needed for embedding
#include <pybind11/eval.h>

#include "Paths.h"

namespace py = pybind11;


class Python {
public:
	Python();
	~Python();

	void calcDistributions(Paths& path);
	void getDistributions(Paths& path);

};

#endif
