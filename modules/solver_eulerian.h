#ifndef SOLVER_EULERIAN_H
#define SOLVER_EULERIAN_H
#pragma once

#include "solver.h"
#include "mesh.h"

template<class T>
class SolverEulerian : public Solver<T> {
	public:
		SolverEulerian(Mesh<T>* pMesh, const double& dt);
		
		virtual void update() = 0;
	public:
		Mesh<T>* m_pMesh;
};

#include "solver_eulerian.cpp"
#endif
