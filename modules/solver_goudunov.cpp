#ifndef SOLVER_GOUDUNOV_CPP
#define SOLVER_GOUDUNOV_CPP
#pragma once

#include "solver_goudunov.h"

template<class T>
gogolitor::SolverGoudunov<T>::SolverGoudunov(Mesh<T>* pMesh, const double& dt) : SolverEulerian<T>(pMesh, dt), m_f(pMesh->links.size(), Vector<T>(3)) {
	Mesh<T>& mesh = *SolverEulerian<T>::m_pMesh;
	for(std::size_t k = 0; k < mesh.cells.size(); k++){
		mesh.cells[k].data.resize(MESH_DATA_SIZE, 0.0);
	}
}

template<class T>
void gogolitor::SolverGoudunov<T>::update() {
	Mesh<T>& mesh = *SolverEulerian<T>::m_pMesh;
	// Just save h
	for(std::size_t k = 0; k < mesh.cells.size(); k++){
		mesh.cells[k].data[MESH_DATA_H_COPY] = mesh.cells[k].data[MESH_DATA_H];
	}
	// Compute the fluxs
	computeFlux();
	// Update based on the computed flux
	// TODO : Could be a bit optimized
	for(std::size_t k = 0; k < mesh.links.size(); k++){
		const T h1 = mesh.links[k].pCell1->data[MESH_DATA_H_COPY];
		const T dh1 = -Solver<T>::m_dt*mesh.links[k].size/mesh.links[k].pCell1->surface * m_f[k][0];
		const Vector<T> du1 = -Solver<T>::m_dt*mesh.links[k].size/mesh.links[k].pCell1->surface * (m_f[k][1] * mesh.links[k].n + m_f[k][2] * mesh.links[k].t) / h1;
		mesh.links[k].pCell1->data[MESH_DATA_H] += dh1;
		mesh.links[k].pCell1->data[MESH_DATA_UX] += du1[0];
		mesh.links[k].pCell1->data[MESH_DATA_UY] += du1[1];
		const T h2 = mesh.links[k].pCell2->data[MESH_DATA_H_COPY];
		const T dh2 = Solver<T>::m_dt*mesh.links[k].size/mesh.links[k].pCell2->surface * m_f[k][0];
		const Vector<T> du2 = Solver<T>::m_dt*mesh.links[k].size/mesh.links[k].pCell2->surface * (m_f[k][1] * mesh.links[k].n + m_f[k][2] * mesh.links[k].t) / h2;
		mesh.links[k].pCell2->data[MESH_DATA_H] += dh2;
		mesh.links[k].pCell2->data[MESH_DATA_UX] += du2[0];
		mesh.links[k].pCell2->data[MESH_DATA_UY] += du2[1];
	}
}

template<class T>
gogolitor::Vector<T> gogolitor::SolverGoudunov<T>::f(const T& h, const T& un, const T& ut) {
	Vector<T> flux(3); flux[0] = h*un; flux[1] = g*h*h + un*un*h; flux[2] = un*ut*h;
	return flux;
}

template<class T>
void gogolitor::SolverGoudunov<T>::computeFlux() {
	const Mesh<T>& mesh = *SolverEulerian<T>::m_pMesh;
	for(std::size_t k = 0; k < mesh.links.size(); k++){
		// Getting ui
		Vector<T> u1(2); u1[0] = mesh.links[k].pCell1->data[MESH_DATA_UX]; u1[1] = mesh.links[k].pCell1->data[MESH_DATA_UY];
		const T un1 = u1.dot(mesh.links[k].n);
		const T ut1 = u1.dot(mesh.links[k].t);
		Vector<T> u2(2); u2[0] = mesh.links[k].pCell2->data[MESH_DATA_UX]; u2[1] = mesh.links[k].pCell2->data[MESH_DATA_UY];
		const T un2 = u2.dot(mesh.links[k].n);
		const T ut2 = u2.dot(mesh.links[k].t);
		// Getting hi
		const T h1 = mesh.links[k].pCell1->data[MESH_DATA_H];
		const T h2 = mesh.links[k].pCell2->data[MESH_DATA_H];
		// Computing Ui
		Vector<T> U1(3); U1[0] = h1; U1[1] = h1*un1; U1[2] = h1*ut1;
		Vector<T> U2(3); U2[0] = h2; U2[1] = h2*un2; U2[2] = h2*ut2;
		// Computing u and c
		const T u = 0.5*(un1 + un2);
		const T c = sqrt(g*0.5*(h1 + h2));
		// Computing eigen values
		const T lambda_1 = u - c;
		const T lambda_2 = u + c;
		if (lambda_1 >= 0.0) {
			m_f[k] = f(h1, un1, ut1);
		}
		else if (lambda_2 < 0.0) {
			m_f[k] = f(h2, un2, ut2);
		}
		else {
			m_f[k] = (lambda_2 * f(h1, un1, ut1) - lambda_1 * f(h2, un2, ut2) + lambda_1 * lambda_2 * (U2 - U1))/(lambda_2 - lambda_1);
		}
		m_f[k][0] += -mesh.links[k].pCell1->data[MESH_DATA_SOURCE] + mesh.links[k].pCell2->data[MESH_DATA_SOURCE]; // TODO Should be F/(rho l_tot)
	}
}

#endif
