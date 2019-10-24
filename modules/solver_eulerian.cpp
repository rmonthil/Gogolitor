#ifndef SOLVER_EULERIAN_CPP
#define SOLVER_EULERIAN_CPP
#pragma once

#include "solver_eulerian.h"

// Solver Class

template<class T>
SolverEulerian<T>::SolverEulerian(Mesh<T>* pMesh, const double& dt) : Solver<T>(dt), m_pMesh(pMesh) {
	
}

#endif
