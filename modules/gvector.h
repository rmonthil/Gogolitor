#ifndef GVECTOR_H
#define GVECTOR_H
#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <numeric>
// TODO : Be sure of this includes :
#include <functional>
#include <algorithm>

namespace gogolitor {

template<class T>
struct Vector : public std::vector<T> {
	Vector(const std::size_t& dim) : std::vector<T>(dim) {
		
	}
	
	T dot(const Vector& b) const {
		return std::inner_product(std::vector<T>::begin(), std::vector<T>::end(), b.begin(), 0.0);
	}
	T norm() const {
		return std::sqrt(dot(*this));
	}
	Vector& normalize() {
		*this /= norm();
		return *this;
	}
	
	// Operators definition
	Vector& operator+=(const Vector& b) {
		std::transform(std::vector<T>::begin(), std::vector<T>::end(), b.begin(), std::vector<T>::begin(), std::plus<T>());
		return *this;
	}
	Vector& operator-=(const Vector& b) {
		std::transform(std::vector<T>::begin(), std::vector<T>::end(), b.begin(), std::vector<T>::begin(), std::minus<T>());
		return *this;
	}
	Vector& operator*=(const T& b) {
		std::transform(std::vector<T>::begin(), std::vector<T>::end(), std::vector<T>::begin(), [b](T a) { return a*b; });
		return *this;
	}
	Vector& operator/=(const T& b) {
		*this *= 1.0/b;
		return *this;
	}
	Vector operator+(const Vector& b) const {
		Vector vec(*this);
		vec += b;
		return vec;
	}
	Vector operator-(const Vector& b) const {
		Vector vec(*this);
		vec -= b;
		return vec;
	}
	Vector operator*(const T& b) const {
		Vector vec(*this);
		vec *= b;
		return vec;
	}
	Vector operator/(const T& b) const {
		Vector vec(*this);
		vec /= b;
		return vec;
	}
	Vector operator-() const {
		Vector vec(*this);
		vec *= -1.0;
		return vec;
	}
};

// Global Operators definition
template<class T>
inline Vector<T> operator*(const T& b, const Vector<T>& a) {
	return a * b;
}

}

#endif
