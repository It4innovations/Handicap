/**
 * @file    Matrix.h
 * @author  Tomáš Michna
 * @date    May, 2018
 * @bug     No known bugs
 * @brief   Implementation of class Matrix
 *
 * This file contains implementation of Matrix class
 */

#pragma once

#include <memory>
#include <stdexcept>

template <typename T>
class Matrix {
	private:
		int rows;
		int columns;
		int filledCells = {0};
		T * data = nullptr;
		std::unique_ptr<T[]> freeCellInColumn = nullptr;
	public:

		/**
 		 * Constructor which create a new Matrix class
 		 *
 		 * @param rows rows are in numeric format
 		 * @param columns columns are in numeric format
 		 * @param missingLabel missingLabel is in numeric format
 		 */
		Matrix(const int rows, const int columns, const int missingLabel) : rows(rows), columns(columns) {
			if (rows < 1) {
				throw std::runtime_error("Number of rows at matrix are invalid.\n");
			}

			if (columns < 1) {
				throw std::runtime_error("Number of columns at matrix are invalid.\n");
			}

			this->data = new T[rows * columns]();
			this->freeCellInColumn = std::unique_ptr<T[]>(new T[columns]);
			for (int i = 0; i < columns; i++) {
				if (i == 0 || i == missingLabel) {
					this->freeCellInColumn[i] = 0;
					continue;
				}
				this->freeCellInColumn[i] = this->rows;
			}
		}

		/**
  		 * Destructor of matrix who will free memory
  		 */
		~Matrix() {
			delete[] this->data;
			this->data = nullptr;
		}

		/**
  		 * This method set value at last unfilled cells in column
  		 *
  		 * @param column column is in numeric format
  		 * @param value value is in numeric format
  		 */
		void set(const int & column, const T & value) {
			const int freeCellInColumn = this->freeCellInColumn[column] - 1;
			this->data[column * rows + freeCellInColumn] = value;
			--this->freeCellInColumn[column];
			++this->filledCells;
		}

		/**
		 * This method unset value at last filled cells in column
		 *
		 * @param column column is in numeric format
		 */
		void unsetLastInsertValue(const int & column) {
			this->data[rows * column + this->freeCellInColumn[column]] = 0;
			++this->freeCellInColumn[column];
			--this->filledCells;
		}

		/**
 		 * This method get value from correct cell which are determine by row and column
         *
         * @param column column is in numeric format
         * @param row row is in numeric format
         * @return value of cell is typically in numeric format
         */
		const T get(const int & row, const int & column) {
			return this->data[rows * column + row];
		}

		/**
  		 * This method get value about number of missing cells in column
		 *
		 * @param column column is in numeric format
 		 * @return number of missing cell is in numeric format
 		 */
		int getFreeCellsInColumn(const int & column) {
			return this->freeCellInColumn[column];
		}

		/**
  		 * This method return number of filled cells in matrix
		 *
 		 * @return number of filled cells in matrix in numeric format
 		 */
		int getFilledCells() const {
			return this->filledCells;
		}

		/**
  		 * This method return number of columns this matrix
		 *
 		 * @return number of column is in numeric format
 		 */
		int getColumnsSize() const {
			return columns;
		}
};
