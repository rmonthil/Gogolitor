#ifndef SOLVER_H
#define SOLVER_H
#pragma once

#include "gvector.h"

namespace gogolitor {

template<class T>
class Solver {
	public:
		Solver(const double& dt);
		
		virtual void update() = 0;
	public:
		T m_dt;
};

}

#include "solver.cpp"
#endif
