/**
 * @file    LabelingSolution.h
 * @author  Tomáš Michna
 * @date    May, 2018
 * @bug     No known bugs
 * @brief   Implementation of class LabelingSolution
 *
 * This file contains implementation of LabelingSolution class
 */

#pragma once

#include <memory>
#include <array>
#include <iostream>
#include "Matrix.h"

template <typename T>
class LabelingSolution : public Matrix<T> {
	private:
		std::unique_ptr<T[]> magicWeight = nullptr; // missing sum of missing number
		std::vector<std::pair<int, T> > setVector{};
		std::vector<T> unsetVector{};
		int currentSetVectorIndex = {0};
		int currentUnsetVectorIndex = {0};

	public:

		/**
 		 * Constructor which create a new LabelingSolution
 		 *
 		 * @param rows rows are in numeric format
 		 * @param columns columns are in numeric format
 		 * @param missingLabel missingLabel is in numeric format
 		 */
		LabelingSolution(const int rows, const int columns, const int missingLabel) : Matrix<T>(rows, columns,
		                                                                                        missingLabel) {
			this->magicWeight = std::unique_ptr<T[]>(new T[columns]);
			setVector.reserve((unsigned) columns * 2);
			unsetVector.reserve((unsigned) columns * 2);
		}

		/**
  		 * This method set magicWeight to column where column equal to label number
  		 *
  		 * @param column column is in numeric format
  		 * @param value value is in numeric format
  		 */
		void setMagicWeight(const int & column, const int & value) {
			this->magicWeight[column] = value;
		}

		/**
 		 * This method get current missing weight at column, column is equal to label number
         *
         * @param column column is in numeric format
         * @return missing current weight is typically in numeric format
         */
		T getWeight(const int & column) const {
			return this->magicWeight[column];
		}

		/**
 		 * This method save current pair like as temporary cache and execute this action at once
         *
         * @param column column is in numeric format
         * @param value value is typically in numeric format
         */
		void prepareSetLabel(const int & column, const T & value) {
			setVector[currentSetVectorIndex++] = std::make_pair(column, value);
		}

		/**
 		 * This method save column for unset like as temporary cache and execute this action at once
         *
         * @param column column is in numeric format
         */
		void prepareUnsetLabel(const int & column) {
			unsetVector[currentUnsetVectorIndex++] = column;
		}

		/**
  		 * This method set pairs of label int matrix
		 */
		void setLabels() {
			for (int i = 0; i < currentSetVectorIndex; ++i) {
				magicWeight[setVector[i].first] -= setVector[i].second;
				Matrix<T>::set(setVector[i].first, setVector[i].second);
			}
			currentSetVectorIndex = 0;
		}

		/**
  		 * This method usset pairs of label int matrix
		 */
		void unsetLabels() {
			for (int i = 0; i < currentUnsetVectorIndex; ++i) {
				const int latestFiledCellInColumn = this->getFreeCellsInColumn(unsetVector[i]);
				magicWeight[unsetVector[i]] += this->get(latestFiledCellInColumn, unsetVector[i]);
				Matrix<T>::unsetLastInsertValue(unsetVector[i]);
			}
			currentUnsetVectorIndex = 0;
		}

		/**
  		 * This method select next label which will be labeled in Labeling method
		 */
		int selectNextLabel() {
			int nextLabel = -1, missCount = 1000, l = 0, p = this->getColumnsSize() - 1;
			int countL, countP;
			while (l < p) {
				countL = this->getFreeCellsInColumn(l);
				countP = this->getFreeCellsInColumn(p);
				if (countL != 0 && countL < missCount) {
					missCount = countL;
					nextLabel = l;
					if (nextLabel == 1) break;
				} else if (countP != 0 && countP < missCount) {
					missCount = countP;
					nextLabel = p;
					if (nextLabel == 1) break;
				}
				l += 1;
				p -= 1;
			}

			return nextLabel;
		}
};
