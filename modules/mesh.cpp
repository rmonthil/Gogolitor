#ifndef MESH_CPP
#define MESH_CPP
#pragma once

#include "mesh.h"

template<class T>
gogolitor::Mesh<T>::Cell::Cell() : surface(0), position(2) {

}

template<class T>
gogolitor::Mesh<T>::Link::Link() : size(0), n(2), t(2), pCell1(nullptr), pCell2(nullptr) {
	
}

template<class T>
gogolitor::Mesh<T>::Mesh() {
}

template<class T>
gogolitor::MeshStructured<T>::MeshStructured() : Mesh<T>() {

}

// TODO : Maybe defining Mesh Blocks ?
template<class T>
gogolitor::MeshCartesian<T>::MeshCartesian(const T& lx, const T& ly, const std::size_t& nx, const std::size_t& ny) : MeshStructured<T>(), m_lx(lx), m_ly(ly), m_nx(nx), m_ny(ny) {
	// TODO find solution to remove double
	// Setting size of Vectors
	Mesh<T>::cells.resize(nx*ny);
	Mesh<T>::links.resize(2*nx*ny);
	// Defining Cell Neighbours
	for(std::size_t i = 0; i < nx; i++) {
		for(std::size_t j = 0; j < ny; j++) {
			const std::size_t k = i + j*nx;
			// Is by default periodic, TODO : Add new possibilities
			//const std::size_t k_im = (i-1) % nx + j*nx; // TODO : Replace this with a Macro
			const std::size_t k_ip = (i+1) % nx + j*nx; // TODO : Replace this with a Macro
			//const std::size_t k_jm = i + ((j-1) % ny)*nx; // TODO : Replace this with a Macro
			const std::size_t k_jp = i + ((j+1) % ny)*nx; // TODO : Replace this with a Macro
			// TODO TODO TODO : Manage Links
			Mesh<T>::links[2*k].pCell1 = &Mesh<T>::cells[k]; 
			Mesh<T>::links[2*k].pCell2 = &Mesh<T>::cells[k_ip]; 
			Mesh<T>::links[2*k + 1].pCell1 = &Mesh<T>::cells[k]; 
			Mesh<T>::links[2*k + 1].pCell2 = &Mesh<T>::cells[k_jp]; 
		}
	}
}

template<class T>
typename gogolitor::Mesh<T>::Cell gogolitor::MeshCartesian<T>::getCell(const std::size_t& i, const std::size_t& j) {
	return Mesh<T>::cells[i + j*m_nx];
}

template<class T>
gogolitor::MeshCartesianRegular<T>::MeshCartesianRegular(const T& lx, const T& ly, const T& nx, const T& ny) : MeshCartesian<T>(lx, ly, nx, ny), m_dx(lx/nx), m_dy(ly/ny) {
	Vector<T> ex(2); ex[0] = 1.0; ex[1] = 0.0;
	Vector<T> ey(2); ey[0] = 0.0; ey[1] = 1.0;
	for(std::size_t i = 0; i < nx; i++) {
		for(std::size_t j = 0; j < ny; j++) {
			const std::size_t k = i + j*nx;
			Mesh<T>::cells[k].surface = m_dx * m_dy;
			Mesh<T>::cells[k].position[0] = i * m_dx;
			Mesh<T>::cells[k].position[1] = j * m_dy;
			Mesh<T>::links[2*k].size = m_dy;
			Mesh<T>::links[2*k].n = ex;
			Mesh<T>::links[2*k].t = ey;
			Mesh<T>::links[2*k + 1].size = m_dx;
			Mesh<T>::links[2*k + 1].n = ey;
			Mesh<T>::links[2*k + 1].t = ex;
		}
	}
}

template<class T>
typename gogolitor::Mesh<T>::Cell gogolitor::MeshCartesianRegular<T>::getCell(const T& x, const T& y) {
	return getCell((std::size_t)(x/m_dx), (std::size_t)(y/m_dy));
}

#endif
