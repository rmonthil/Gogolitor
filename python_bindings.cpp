#ifndef PYTHON_BINDINGS_CPP
#define PYTHON_BINDINGS_CPP

#include <pybind11/pybind11.h>
#include <pybind11/stl_bind.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

#include "modules/solver_goudunov.h"

namespace py = pybind11;

PYBIND11_MAKE_OPAQUE(std::vector<double>);

using namespace gogolitor;

// Trampoline class
template<class T>
class PySolver : public Solver<T> {
	public:
		using Solver<T>::Solver;
		
		void update() override { PYBIND11_OVERLOAD_PURE(void, Solver<T>, update, ); }
	private:
};
template<class T>
class PySolverEulerian : public SolverEulerian<T> {
	public:
		using SolverEulerian<T>::SolverEulerian;
		
		void update() override { PYBIND11_OVERLOAD_PURE(void, SolverEulerian<T>, update, ); }
	private:
};
template<class T>
class PySolverGoudunov : public SolverGoudunov<T> {
	public:
		using SolverGoudunov<T>::SolverGoudunov;
		
		void update() override { PYBIND11_OVERLOAD(void, SolverGoudunov<T>, update, ); }
	private:
};

PYBIND11_MODULE(gogolitor, m) {
	m.doc() = R"pbdoc(
	Module resulting of great Gogolitor project
	-----------------------

	.. currentmodule:: gogolitor

	.. autosummary::
		:toctree: _generate
	)pbdoc";

	py::bind_vector<std::vector<double>>(m, "StdVectorOfDouble");
	
	py::class_<Vector<double>, std::vector<double>>(m, "Vector")
		.def(py::init<const std::size_t&>())
		.def("dot", &Vector<double>::dot)
		.def("norm", &Vector<double>::norm)
		.def(py::self += py::self)
		.def(py::self -= py::self)
		.def(py::self *= double())
		.def(py::self /= double())
		.def(py::self + py::self)
		.def(py::self - py::self)
		.def(py::self * double())
		.def(double() * py::self)
		.def(-py::self);
	
	py::class_<Mesh<double>::Cell>(m, "Cell")
		.def(py::init<>())
		.def_readwrite("surface", &Mesh<double>::Cell::surface)
		.def_readwrite("position", &Mesh<double>::Cell::position)
		.def_readwrite("data", &Mesh<double>::Cell::data);
	
	py::class_<Mesh<double>::Link>(m, "Link")
		.def(py::init<>())
		.def_readwrite("size", &Mesh<double>::Link::size)
		.def_readwrite("n", &Mesh<double>::Link::n)
		.def_readwrite("t", &Mesh<double>::Link::t)
		.def_readwrite("cell1", &Mesh<double>::Link::pCell1)
		.def_readwrite("cell2", &Mesh<double>::Link::pCell2);

	py::bind_vector<std::vector<Mesh<double>::Cell>>(m, "StdVectorOfCells");
	py::bind_vector<std::vector<Mesh<double>::Link>>(m, "StdVectorOfLinks");
	
	py::class_<Mesh<double>>(m, "Mesh")
		.def(py::init<>())
		.def_readwrite("cells", &Mesh<double>::cells)
		.def_readwrite("links", &Mesh<double>::links);
	
	py::class_<MeshStructured<double>, Mesh<double>>(m, "MeshStrctured")
		.def(py::init<>());
	
	py::class_<MeshCartesian<double>, MeshStructured<double>>(m, "MeshCartesian")
		.def(py::init<const double&, const double&, const std::size_t&, const std::size_t&>())
		.def_readonly("lx", &MeshCartesian<double>::m_lx)
		.def_readonly("ly", &MeshCartesian<double>::m_ly)
		.def_readonly("nx", &MeshCartesian<double>::m_nx)
		.def_readonly("ny", &MeshCartesian<double>::m_ny);
	
	py::class_<MeshCartesianRegular<double>, MeshCartesian<double>>(m, "MeshCartesianRegular")
		.def(py::init<const double&, const double&, const std::size_t&, const std::size_t&>())
		.def_readonly("dx", &MeshCartesianRegular<double>::m_dx)
		.def_readonly("dy", &MeshCartesianRegular<double>::m_dy);
	
	py::class_<Solver<double>, PySolver<double>>(m, "Solver")
		.def(py::init<const double&>())
		.def("update", &Solver<double>::update)
		.def_readwrite("dt", &Solver<double>::m_dt);
	
	py::class_<SolverEulerian<double>, Solver<double>, PySolverEulerian<double>>(m, "SolverEulerian")
		.def(py::init<Mesh<double>*, const double&>())
		.def("update", &SolverEulerian<double>::update)
		.def_readwrite("dt", &Solver<double>::m_dt);
	
	py::class_<SolverGoudunov<double>, SolverEulerian<double>, PySolverGoudunov<double>>(m, "SolverGoudunov")
		.def(py::init<Mesh<double>*, const double&>())
		.def("update", &SolverGoudunov<double>::update)
		.def_readwrite("dt", &Solver<double>::m_dt);

#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}

#endif
