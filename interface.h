#pragma once
#include "matrix.h"
#include <conio.h>

int get_key() {
	int key = _getch();
	if ((key == 0) || (key == 224)) key = _getch();
	return key;
}

int operations_menu() {
	while (true) {
		system("cls");
		std::cout << "1. Add up matrices\n2. Subtract matrices\n3. Matrix multiplication\n4. Multiply the matrix by a number.\n";
		std::cout << "5. Divide the current matrix by a number.\n6. Calculate the trace of the matrix.\n7. Compare matrices.\n\n";
		std::cout << "ENTER/ESC Exit to the previous menu.\n";
		int key = get_key();
		if (key == 27 || key >= 49 && key <= 55 || key == 13)
			return key;
	}
}
int type_menu() {
	while (true) {
		system("cls");
		std::cout << "Please select the type of data you want to work with. This selection can be changed.\n\n";
		std::cout << "1. INT\n2. FLOAT\n3. DOUBLE\n4. COMPLEX FLOAT\n";
		std::cout << "5. COMPLEX DOUBLE\n\nENTER/ESC Exiting the program.\n";
		int key = get_key();
		if (key == 27 || key >= 49 && key <= 53 || key == 13)
			return key;
	}
}
int type_comprare() {
	system("cls");
	while (true) {
		std::cout << "1. ==\n2. !=\n3. >=\n4. <=\n";
		std::cout << "5. >\n6. <\n\nENTER/ESC Exit to the previous menu.\n\n";
		int key = get_key();
		if (key == 27 || key >= 49 && key <= 54 || key == 13)
			return key;
	}
}

template <typename T>
void input_correctly_number(T& numb) //проверка на коректное число
{
	do {
		std::cout << "\nInput number: ";
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		std::cin >> numb;
	} while (std::cin.fail());
}

template <typename T>
void add_matrix(matrix<T, comparator_for_class_matrix>& a) //добавление матрицы
{
	unsigned int colums = 0, rows = 0;
	std::cout << "Enter the number of columns: ";
	input_correctly_number(colums);
	std::cout << "Enter the number of rows: ";
	input_correctly_number(rows);
	a.set_columns(colums);
	a.set_rows(rows);
	std::cout << "Enter data into this matrix!" << std::endl;
	std::cin >> a;
}

template <typename T>
void two_matrix_operations(matrix<T, comparator_for_class_matrix> first_matrix, matrix<T, comparator_for_class_matrix> second_matrix, int key)
{
	try {
		std::cout << "\nEnter the data of the first matrix.\n" << std::endl;
		add_matrix(first_matrix);
		std::cout << "Enter the data of the second matrix.\n" << std::endl;
		add_matrix(second_matrix);
		if (key == 49)
			std::cout << "\nCalculating the addition of two matrices\nRESULT IS:\n" << first_matrix + second_matrix;
		if (key == 50)
			std::cout << "\nCalculating the subtraction of two matrices\nRESULT IS:\n" << first_matrix - second_matrix;
		if (key == 51)
			std::cout << "\nCalculating the multiplication of two matrices\nRESULT IS:\n" << first_matrix * second_matrix;
	}
	catch (std::exception& e) {
		std::cerr << "\nCaught: " << e.what() << std::endl;
		std::cerr << "Type: " << typeid(e).name() << std::endl;
	}
	int click_to_continue = get_key();
}

template <typename T>
void single_matrix_operations(matrix<T, comparator_for_class_matrix> first_matrix, int key)
{
	try {
		std::cout << "\nEnter matrix data.\n" << std::endl;
		add_matrix(first_matrix);
		if (key == 54)
			std::cout << "\nCalculating the trace of a matrix\nRESULT IS: " << matrix_trace(first_matrix) << std::endl;
		else {
			double numb = 0;
			input_correctly_number(numb);
			if (key == 52)
				std::cout << "\nCalculating matrix multiplication\nRESULT IS:\n" << first_matrix * (T)numb;
			if (key == 53)
				std::cout << "\nCalculating division of a matrix\nRESULT IS:\n" << first_matrix / (T)numb;
		}
	}
	catch (std::exception& e) {
		std::cerr << "\nCaught: " << e.what() << std::endl;
		std::cerr << "Type: " << typeid(e).name() << std::endl;
	}
	int click_to_continue = get_key();
}

template <typename T>
void result_is_comprare(matrix<T, comparator_for_class_matrix> first_matrix, matrix<T, comparator_for_class_matrix> second_matrix, int key) //операции сравнения
{
	try {
		std::cout << "\nEnter the data of the first matrix.\n" << std::endl;
		add_matrix(first_matrix);
		std::cout << "Enter the data of the second matrix.\n" << std::endl;
		add_matrix(second_matrix);
		std::cout << "\n\nRESULT IS: ";
		if (key == 49) {
			std::cout << "First Matrix == Second Matrixd is: ";
			first_matrix == second_matrix ? std::cout << "TRUE." : std::cout << "FALSE. ";
		}
		if (key == 50) {
			std::cout << "First Matrix != Second Matrixd is: ";
			first_matrix != second_matrix ? std::cout << "TRUE." : std::cout << "FALSE. ";
		}
		if (key == 51) {
			std::cout << "First Matrix >= Second Matrixd is: ";
			first_matrix >= second_matrix ? std::cout << "TRUE." : std::cout << "FALSE. ";
		}
		if (key == 52) {
			std::cout << "First Matrix <= Second Matrixd is: ";
			first_matrix <= second_matrix ? std::cout << "TRUE." : std::cout << "FALSE. ";
		}
		if (key == 53) {
			std::cout << "First Matrix > Second Matrixd is: ";
			first_matrix > second_matrix ? std::cout << "TRUE." : std::cout << "FALSE. ";
		}
		if (key == 54) {
			std::cout << "First Matrix == Second Matrixd is: ";
			first_matrix < second_matrix ? std::cout << "TRUE." : std::cout << "FALSE. ";
		}
	}
	catch (std::exception& e) {
		std::cerr << "\nCaught: " << e.what() << std::endl;
		std::cerr << "Type: " << typeid(e).name() << std::endl;
	}
	int click_to_continue = get_key();
}

template <typename T>
void comprare_matrix(matrix<T, comparator_for_class_matrix> first_matrix, matrix<T, comparator_for_class_matrix> second_matrix) //вызов функции стравнения
{
	while (true) {
		int key = type_comprare();
		if (key == 13 || key == 27)
			break;
		if (key >= 49 && key <= 54) {
			result_is_comprare(first_matrix, second_matrix, key);
		}
	}
}

template <typename T>
void operation_selection(matrix<T, comparator_for_class_matrix> first_matrix, matrix<T, comparator_for_class_matrix> second_matrix)  //выбор операции
{
	while (true) {
		int key = operations_menu();
		if (key >= 49 && key <= 51)
			two_matrix_operations(first_matrix, second_matrix, key);
		if (key >= 52 && key <= 54)
			single_matrix_operations(first_matrix, key);
		if (key == 55)
			comprare_matrix(first_matrix, second_matrix);
		if (key == 13 || key == 27)
			break;
	}
}

void type_selection() 
{
	while (true) {
		int key = type_menu();
		if (key == 49) {
			matrix<int, comparator_for_class_matrix> first_int_matrix, second_int_matrix;
			operation_selection(first_int_matrix, second_int_matrix);
		}
		if (key == 50) {
			matrix<float, comparator_for_class_matrix> first_float_matrix, second_float_matrix;
			operation_selection(first_float_matrix, second_float_matrix);
		}
		if (key == 51) {
			matrix<double, comparator_for_class_matrix> first_double_matrix, second_double_matrix;
			operation_selection(first_double_matrix, second_double_matrix);
		}
		if (key == 52) {
			matrix<std::complex<float>, comparator_for_class_matrix> first_complex_float_matrix, second_complex_double_matrix;
			operation_selection(first_complex_float_matrix, second_complex_double_matrix);
		}
		if (key == 53) {
			matrix<std::complex<double>, comparator_for_class_matrix> first_complex_double_matrix, second_complex_double_matrix;
			operation_selection(first_complex_double_matrix, second_complex_double_matrix);
		}
		if (key == 13 || key == 27)
			break;
	}
}
