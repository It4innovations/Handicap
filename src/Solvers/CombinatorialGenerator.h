/**
 * @file    CombinatorialGenerator.h
 * @author  Tomáš Michna
 * @date    May, 2018
 * @bug     No known bugs
 * @brief   Implementation of class CombinatorialGenerator
 *
 * This file contains implementation of CombinatorialGenerator class
 */

#pragma once

#include <memory>
#include <algorithm>
#include "kSumProblemSolver.h"
#include "../Graphs/ExtendedHandicapGraph.h"
#include "../Structures/LabelingSolution.h"


class CombinatorialGenerator {
	private:
		std::shared_ptr<ExtendedHandicapGraph> graph{};
		kSumProblemSolver<int> solver{};
		std::unique_ptr<int[]> allowedNumbersArray{};
		int currentLabel = {0};
		int sizeOfSet = {0};
		int missingWeight = {0};
	public:

		/**
 		 * Constructor which create new CombinatorialGenerator
 		 *
 		 * @param graph graph is smart pointer which point to Graph class
 		 */
		explicit CombinatorialGenerator(std::shared_ptr<ExtendedHandicapGraph> & graph) {
			this->graph = graph;
			this->solver = kSumProblemSolver<int>();
			this->allowedNumbersArray = std::unique_ptr<int[]>(new int[graph->getVerticesCount()]());
		}

		/**
	  	 * This method set parameter size of missing neighbours size
	  	 *
	  	 * @param size is in numeric format
	 	 */
		void setSizeOfSet(const int & size) {
			sizeOfSet = size;
		}

		/**
	   	 * This method set parameter weight of missing weigh for future comupute k-SUM problem
	     *
	     * @param weight is in numeric format
	     */
		void setMissingWeight(const int & weight) {
			missingWeight = weight;
		}

		/**
	   	 * This method set parameter label for determine which label is prohibited to use in compute k-SUM
	     *
	     * @param label is in numeric format
	     */
		void setCurrentLabel(const int & label) {
			currentLabel = label;
		}

		/**
	   	 * This method is manager which k-SUM problem will be compute
	   	 *
	     * @param kSumResults is stack of integer results
	     * @param matrix is a smart pointer to matrix which contains current labeling solution
	     */
		void computePossibleCombination(std::stack<int> & kSumResults,
		                                std::unique_ptr<LabelingSolution<int>> & matrix) {
			// solve 1-SUM problem
			if (sizeOfSet == 1) {
				bool checkIsWeightIsValid = missingWeight > 1
				                            && missingWeight <= graph->getVerticesCount() + 1
				                            && missingWeight != graph->getMissingLabel()
				                            && matrix->getFreeCellsInColumn(missingWeight) != 0
				                            && missingWeight != currentLabel;
				if (checkIsWeightIsValid) {
					kSumResults.emplace(missingWeight);
				}
				return;
			}

			// solve k-SUM, where k > 1
			if (sizeOfSet > 1 && sizeOfSet <= graph->getRegularConstant()) {
				int index = 0;
				for (int i = 1; i < graph->getVerticesCount() + 2; ++i) {
					if (matrix->getFreeCellsInColumn(i) && i != currentLabel) {
						allowedNumbersArray[index++] = i;
					}
				}

				solver.setK(sizeOfSet);
				solver.setSearchNumber(missingWeight);
				solver.solve(allowedNumbersArray, index, kSumResults);

				return;
			}

			throw "Invalid size of set";
		}
};
