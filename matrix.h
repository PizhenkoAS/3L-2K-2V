#pragma once
#include <utility>
#include <iostream>
#include <complex>
#include <vector>

struct comparator_for_class_matrix {    //описание структуры 
	bool operator()(std::complex<double> lhs, std::complex<double> rhs) const {
		return lhs.real() == rhs.real() ? lhs.imag() < rhs.imag() : lhs.real() < rhs.real();
	}
	bool operator()(std::complex<int> lhs, std::complex<int> rhs) const {
		return lhs.real() == rhs.real() ? lhs.imag() < rhs.imag() : lhs.real() < rhs.real();
	}
	bool operator()(std::complex<float> lhs, std::complex<float> rhs) const {
		return lhs.real() == rhs.real() ? lhs.imag() < rhs.imag() : lhs.real() < rhs.real();
	}
	bool operator()(float lhs, float rhs) const {
		return lhs < rhs;
	}
	bool operator()(int lhs, int rhs) const {
		return lhs < rhs;
	}
	bool operator()(double lhs, double rhs) const {
		return lhs < rhs;
	}
};

template <typename T, typename TComparator = std::less < T>>  //класс принимает любой тип данных и любой метод 
class matrix 
{
private:
	std::vector<std::vector<T>> _matr; //создается матрица
	int _columns, _rows;

public:
	matrix()
	{
		_columns = 0;
		_rows = 0;
	}
	matrix(const int columns, const int rows) 
	{
		_columns = columns;
		_rows = rows;
		_matr.resize(_columns); //задаем кол-во солбцов
		for (int i = 0; i < _columns; i++)
		{
			_matr[i].resize(_rows); //задаем кол-во строк 
		}
	}

	int get_columns() const
	{
		return _columns;
	}
	int get_rows() const
	{
		return _rows;
	}
	void set_columns(const int columns) 
	{
		_columns = columns;
		_matr.resize(_columns);
	}
	void set_rows(const int rows) 
	{
		_rows = rows;
		for (int i = 0; i < _columns; i++) 
		{
			_matr[i].resize(_rows);
		}
	}

	void swap(const matrix& rhs) 
	{
		matrix<T, comparator_for_class_matrix> tmp = rhs; //создаем доп. матрицу
		std::swap(_columns, tmp._columns);
		std::swap(_rows, tmp._rows);
		std::swap(_matr, tmp._matr);
	}

	T& operator()(const int columns, const int rows) //получение значения по индексу
	{
		if (_columns <= columns || _rows <= rows)
			throw::std::out_of_range("error index");
		if (_matr.empty())
			throw::std::logic_error("vector emptry");
		return _matr[columns][rows];
	}
	T operator()(const int columns, const int rows) const
	{
		if (_columns <= columns || _rows <= rows)
			throw::std::out_of_range("error index");
		if (_matr.empty())
			throw::std::logic_error("vector emptry");
		return _matr[columns][rows];
	}

	matrix<T, comparator_for_class_matrix> operator+(const matrix& rhs) //сложение
	{
		if (_rows != rhs._rows || _columns != rhs._columns)
			throw std::logic_error("Matrices with different sizes cannot be added!");
		matrix<T, comparator_for_class_matrix> c(_columns, _rows);
		for (int i = 0; i < c._columns; i++) {
			for (int j = 0; j < c._rows; j++) {
				c._matr[i][j] = _matr[i][j] + rhs._matr[i][j];
			}
		}
		return c;
	}
	matrix<T, comparator_for_class_matrix> operator-(const matrix& rhs) //вычитание
	{
		if (_rows != rhs._rows || _columns != rhs._columns)
			throw std::logic_error("Matrices with different sizes cannot be added!");

		matrix<T, comparator_for_class_matrix> c(_columns, _rows);

		for (int i = 0; i < c._columns; i++) {
			for (int j = 0; j < c._rows; j++) {
				c._matr[i][j] = _matr[i][j] - rhs._matr[i][j];
			}
		}
		return c;
	}
	matrix<T, comparator_for_class_matrix> operator*(const matrix& rhs)//умножение
	{
		if (_rows != rhs._columns)
			throw std::logic_error("Matrices of different sizes!");
		matrix<T, comparator_for_class_matrix> c(_columns, rhs._rows);

		for (int i = 0; i < _columns; i++) {
			for (int j = 0; j < rhs._rows; j++) {
				c._matr[i][j] = 0;
				for (int k = 0; k < _rows; k++) {
					c._matr[i][j] += _matr[i][k] * rhs._matr[k][j];
				}
			}
		}
		return c;
	}
	matrix<T, comparator_for_class_matrix> operator*(const T rhs)//умножение на число
	{
		matrix<T, comparator_for_class_matrix> c(_columns, _rows);
		for (int i = 0; i < _columns; i++) {
			for (int j = 0; j < _rows; j++) {
				c._matr[i][j] = _matr[i][j] * rhs;
			}
		}
		return c;
	}
	matrix<T, comparator_for_class_matrix> operator/(const T rhs) //деление
	{
		matrix<T, comparator_for_class_matrix> c(_columns, _rows);
		for (int i = 0; i < _columns; i++) {
			for (int j = 0; j < _rows; j++) {
				c._matr[i][j] = _matr[i][j] / rhs;
			}
		}
		return c;
	}

	matrix<T, comparator_for_class_matrix>& operator+=(const matrix& rhs) 
	{
		if (_rows != rhs._rows || _columns != rhs._columns)
			throw std::logic_error("Matrices with different sizes cannot be added!");
		for (int i = 0; i < _columns; i++) {
			for (int j = 0; j < _rows; j++) {
				_matr[i][j] = _matr[i][j] + rhs._matr[i][j];
			}
		}
		return *this;
	}
	matrix<T, comparator_for_class_matrix>& operator-=(const matrix& rhs) 
	{
		if (_rows != rhs._rows || _columns != rhs._columns)
			throw std::logic_error("Matrices with different sizes cannot be added!");
		for (int i = 0; i < _columns; i++) {
			for (int j = 0; j < _rows; j++) {
				_matr[i][j] -= rhs._matr[i][j];
			}
		}
		return *this;
	}
	matrix<T, comparator_for_class_matrix>& operator*=(const T rhs) 
	{
		for (int i = 0; i < _columns; i++) {
			for (int j = 0; j < _rows; j++) {
				_matr[i][j] *= rhs;
			}
		}
		return *this;
	}
	matrix<T, comparator_for_class_matrix>& operator/=(const T rhs)
	{
		for (int i = 0; i < _columns; i++) {
			for (int j = 0; j < _rows; j++) {
				_matr[i][j] *= rhs;
			}
		}
		return *this;
	}

	bool operator==(const matrix& rhs) 
	{
		if (_columns != rhs._columns || _rows != rhs._rows)
			return false;
		for (int i = 0; i < _columns; i++) {
			for (int j = 0; j < _rows; j++) {
				if (_matr[i][j] != rhs._matr[i][j])
					return false;
			}
		}
		return true;
	}
	bool operator!=(const matrix& rhs)
	{
		return !this->operator==(rhs);
	}
	bool operator<(const matrix& rhs) {
		if (_rows != rhs._rows || _columns != rhs._columns)
			return false;
		for (int i = 0; i < _columns; i++) {
			for (int j = 0; j < _rows; j++) {
				if (TComparator()(_matr[i][j], rhs._matr[i][j]))
					return false;
			}
		}
		return true;
	}
	bool operator>(const matrix& rhs) {
		return !this->operator<(rhs);
	}
	bool operator<=(const matrix& rhs) {
		if (_rows != rhs._rows || _columns != rhs._columns)
			return false;
		for (int i = 0; i < _columns; i++) {
			for (int j = 0; j < _rows; j++) {
				if (TComparator()(_matr[i][j], rhs._matr[i][j]) && _matr[i][j] != rhs._matr[i][j])
					return false;
			}
		}
		return true;
	}
	bool operator>=(const matrix& rhs) {
		return !this->operator<=(rhs);
	}

	auto begin() 
	{
		return _matr.begin();
	}
	auto end()
	{
		return _matr.end();
	}
	auto cbegin()
	{
		return _matr.cbegin();
	}
	auto cend()
	{
		return _matr.cend();
	}
};

template<typename T>
double matrix_trace(const matrix<std::complex<T>, comparator_for_class_matrix>& lhs) //след
{
	if (lhs.get_columns() != lhs.get_rows())
		throw std::logic_error("The matrix is not square!");
	double res = 0;
	for (int i = 0; i < lhs.get_columns(); i++) {
		res += lhs(i, i).real();
	}
	return res;
}
template<typename T>
double matrix_trace(const matrix<T, comparator_for_class_matrix>& lhs)
{
	if (lhs.get_columns() != lhs.get_rows())
		throw std::logic_error("The matrix is not square!");
	double res = 0;
	for (int i = 0; i < lhs.get_columns(); i++) {
		res += lhs(i, i);
	}
	return res;
}
template<typename T> //вывод
std::ostream& operator<< (std::ostream& out, const matrix<T, comparator_for_class_matrix>& lhs) {
	for (int i = 0; i < lhs.get_columns(); i++) {
		for (int j = 0; j < lhs.get_rows(); j++) {
			out << lhs(i, j) << '\t';
		}
		out << '\n';
	}
	return out;
}

template<typename T>
std::istream& operator>> (std::istream& in, matrix<T, comparator_for_class_matrix>& lhs)
{

	for (int i = 0; i < lhs.get_columns(); i++) {
		for (int j = 0; j < lhs.get_rows(); j++) {
			std::cout << "Input data [" << i << "][" << j << "] - ";
			in >> lhs(i, j);
		}
	}
	return in;
}
template<typename T>
std::istream& operator>>(std::istream& in, matrix<std::complex <T>, comparator_for_class_matrix>& lhs) {
	for (int i = 0; i < lhs.get_columns(); i++) {
		for (int j = 0; j < lhs.get_rows(); j++) {
			T real = 0, imagine = 0;
			std::cout << "\nData [" << i << ", " << j << "]\nInput real part: ";
			std::cin >> real;
			std::cout << "Input imagine part: ";
			std::cin >> imagine;
			lhs(i, j) = { real, imagine };
		}
	}
	return in;
}
