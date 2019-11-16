#ifndef MESH_H
#define MESH_H
#pragma once

#include "gvector.h"
#include <memory>

namespace gogolitor {

template<class T>
class Mesh { // 2D Mesh
	public:
		Mesh();
		
		struct Cell {
			Cell();

			T surface; // Surface of the cell. Would be a volume in 3D.
			Vector<T> position; // Position of the Cell
			std::vector<T> data; // TODO
		};
		
		// Links two cells
		struct Link {
			Link();

			T size; // Size of the shared segment of the two linked surfaces. Would be a surface in 3D.
			Vector<T> n; // Normal vector.
			Vector<T> t; // Tangent vector.
			
			Cell* pCell1; // Pointer to the first linked Cell.
			Cell* pCell2; // Pointer to the second linked Cell.
		};
	public:
		std::vector<Cell> cells;
		std::vector<Link> links;
};

template<class T>
class MeshStructured : public Mesh<T> { // 2D Mesh
	public:
		MeshStructured();

		virtual typename Mesh<T>::Cell getCell(const std::size_t& i, const std::size_t& j) = 0;
		virtual typename Mesh<T>::Cell getCell(const T& x, const T& y) = 0;
};

template<class T>
class MeshCartesian : public MeshStructured<T> { // 2D Mesh
	public:
		enum Indice {
			INDICE_X_MINUS_ONE,
			INDICE_X_PLUS_ONE,
			INDICE_Y_MINUS_ONE,
			INDICE_Y_PLUS_ONE
		};
	public:
		MeshCartesian(const T& lx, const T& ly, const std::size_t& nx, const std::size_t& ny);
		
		typename Mesh<T>::Cell getCell(const std::size_t& i, const std::size_t& j);
	public:
		const double m_lx;
		const double m_ly;
		const std::size_t m_nx;
		const std::size_t m_ny;
};

template<class T>
class MeshCartesianRegular : public MeshCartesian<T> { // 2D Mesh
	public:
		MeshCartesianRegular(const T& lx, const T& ly, const T& nx, const T& ny);

		typename Mesh<T>::Cell getCell(const T& x, const T& y);
	public:
		const double m_dx;
		const double m_dy;
};

}

#include "mesh.cpp" // VERY VERY VERY IMPORTANT : ALL THE CODE MUST BE IN THE .h because its templates !!!
#endif
