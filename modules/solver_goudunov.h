#ifndef SOLVER_GOUDUNOV_H
#define SOLVER_GOUDUNOV_H
#pragma once

#include "solver_eulerian.h"

// TODO : Add Slope and Bathimetry effect

namespace gogolitor {

template<class T>
class SolverGoudunov : public SolverEulerian<T> {
	public:
		enum MeshData {
			MESH_DATA_H,
			MESH_DATA_UX,
			MESH_DATA_UY,
			MESH_DATA_H_COPY,
			MESH_DATA_SOURCE,
			MESH_DATA_SIZE
		};
	public:
		SolverGoudunov(Mesh<T>* pMesh, const double& dt);
		
		void update();
	private:
		Vector<T> f(const T& h, const T& un, const T& ut);
		void computeFlux();
	private:
		const T g = 9.81; // TODO Externalize Physics Parameters
		// Fluxs
		std::vector<Vector<T>> m_f; // F =(Fh, Funh, Futh)
};

}

#include "solver_goudunov.cpp"
#endif
