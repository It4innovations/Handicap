/**
 * @file    kSumProblemSolver.h
 * @author  Tomáš Michna
 * @date    May, 2018
 * @bug     No known bugs
 * @brief   Implementation of class kSumProblemSolver
 *
 * This file contains implementation of kSumProblemSolver class
 */
#pragma once

#include <stack>
#include <algorithm>
#include <iostream>
#include <memory>

template <typename T>
class kSumProblemSolver {
	private:
		T labelsCount = {0};
		T searchNumber = {0};
		T nSum = {0};

		/**
		 * This method solve 2-SUM problem, where in array are stored all possible labels to compute 2-SUM problem
		 *
		 * @param labels array is in numeric format
		 * @param solution store new solution onto stack
		 */
		void solve2SUM(const std::unique_ptr<T[]> & labels, std::stack<T> & solution) {
			int sum = 0, lhs = 0, rhs = this->labelsCount - 1;
			while (lhs < rhs) {
				sum = labels[lhs] + labels[rhs];
				if (sum < this->searchNumber) {
					lhs += 1;
				} else if (sum > this->searchNumber) {
					rhs -= 1;
				} else {
					solution.emplace(labels[lhs]);
					solution.emplace(labels[rhs]);
					rhs -= 1;
					lhs += 1;
				}
			}
		}

		/**
		 * This method solve 3-SUM problem, where in array are stored all possible labels to compute 3-SUM problem
		 *
		 * @param labels array is in numeric format
		 * @param solution store new solution onto stack
		 */
		void solve3SUM(const std::unique_ptr<T[]> & labels, std::stack<T> & solution) {
			int sum, lhs, rhs, searchWeight;
			for (int i = labelsCount - 1; i >= 2; --i) {
				lhs = 0;
				rhs = i - 1;
				searchWeight = searchNumber - labels[i];
				if (searchWeight <= 0) continue;
				while (lhs < rhs) {
					sum = labels[lhs] + labels[rhs];
					if (sum < searchWeight) {
						lhs += 1;
					} else if (sum > searchWeight) {
						rhs -= 1;
					} else {
						solution.emplace(labels[lhs]);
						solution.emplace(labels[rhs]);
						solution.emplace(labels[i]);
						rhs -= 1;
						lhs += 1;
					}
				}
			}
		}

		/**
		 * This method solve 4-SUM problem, where in array are stored all possible labels to compute 4-SUM problem
		 *
		 * @param labels array is in numeric format
		 * @param solution store new solution onto stack
		 */
		void solve4SUM(const std::unique_ptr<T[]> & labels, std::stack<T> & solution) {
			int sum, lhs, rhs, searchWeight;
			for (int i = labelsCount - 1; i >= 3; --i) {
				for (int j = i - 1; j >= 2; --j) {
					lhs = 0;
					rhs = j - 1;
					searchWeight = searchNumber - labels[i] - labels[j];
					if (searchWeight <= 0) continue;
					while (lhs < rhs) {
						sum = labels[lhs] + labels[rhs];
						if (sum < searchWeight) {
							lhs += 1;
						} else if (sum > searchWeight) {
							rhs -= 1;
						} else {
							solution.emplace(labels[lhs]);
							solution.emplace(labels[rhs]);
							solution.emplace(labels[j]);
							solution.emplace(labels[i]);
							rhs -= 1;
							lhs += 1;
						}
					}
				}
			}
		}
		/**
 		 * This method solve 5-SUM problem, where in array are stored all possible labels to compute 5-SUM problem
 		 *
 		 * @param labels array is in numeric format
 		 * @param solution store new solution onto stack
 		*/
		void solve5SUM(const std::unique_ptr<T[]> & labels, std::stack<T> & solution) {
			int sum, lhs, rhs, searchWeight;
			for (int k = labelsCount - 1; k >= 4; --k) {
				for (int i = k-1; i >= 3; --i) {
					for (int j = i - 1; j >= 2; --j) {
						lhs = 0;
						rhs = j - 1;
						searchWeight = searchNumber - labels[i] - labels[j] - labels[k];
						if (searchWeight <= 0) continue;
						while (lhs < rhs) {
							sum = labels[lhs] + labels[rhs];
							if (sum < searchWeight) {
								lhs += 1;
							} else if (sum > searchWeight) {
								rhs -= 1;
							} else {
								solution.emplace(labels[lhs]);
								solution.emplace(labels[rhs]);
								solution.emplace(labels[j]);
								solution.emplace(labels[i]);
								solution.emplace(labels[k]);
								rhs -= 1;
								lhs += 1;
							}
						}
					}
				}
			}
		}

	public:
		/**
		 * This method resolved which k-SUM problem will be solve
		 *
		 * @param labels array is in numeric format
		 * @param labelsCount number of labels in array labels
		 * @param solution store new solution onto stack
		 */
		void solve(const std::unique_ptr<T[]> & labels, const int & labelsCount, std::stack<T> & solution) {
			this->labelsCount = labelsCount;
			if (nSum < 1 || nSum > 5) {
				throw std::runtime_error("It does not implement " + std::to_string(nSum) + " nSum\n");
			}

			if (this->nSum == 2) {
				this->solve2SUM(labels, solution);
			} else if (this->nSum == 3) {
				this->solve3SUM(labels, solution);
			} else if (this->nSum == 4) {
				this->solve4SUM(labels, solution);
			} else if (this->nSum == 5) {
				this->solve5SUM(labels, solution);
			}
		}

		/**
	 	 * This method set parameter k in k-SUM problem
	 	 *
	 	 * @param k is typically in numeric format
		 */
		void setK(const T k) {
			this->nSum = k;
		}

		/**
	 	 * This method set looking search sum number
	 	 *
	 	 * @param searchNumber is typically in numeric format
		 */
		void setSearchNumber(const T searchNumber) {
			this->searchNumber = searchNumber;
		}
};

template class kSumProblemSolver<int>;
