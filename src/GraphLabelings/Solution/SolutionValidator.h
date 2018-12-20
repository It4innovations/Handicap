/**
 * @file    SolutionValidator.h
 * @author  Tomáš Michna
 * @date    May, 2018
 * @bug     No known bugs
 * @brief   Prototype of class SolutionValidator
 *
 * This file contains prototype of SolutionValidator class
 */

#pragma once

#include "../../Structures/Matrix.h"
#include "../../Graphs/ExtendedHandicapGraph.h"
#include "../../Structures/LabelingSolution.h"

class SolutionValidator {
	private:
		int verticesCount = { 0 };
	public:

		/**
 		 * Constructor which create new SolutionValidator
 		 *
 		 * @param ExtendedHandicapGraph is a smart pointer to ExtendedHandicapGraph
 		 */
		explicit SolutionValidator(std::shared_ptr<ExtendedHandicapGraph> & graph) {
			// +2 due too Extended Handicap labeling on regular graphs
			this->verticesCount = graph->getVerticesCount() + 2;
		}

		/**
 		 * The method validate solution and return result
 		 *
 		 * @param solution is a smart pointer to ExtendedHandicapGraph
 		 * @return bool parameter if solution is valid
 		 */
		bool validate(std::unique_ptr<LabelingSolution<int>> & solution) {
			bool isCorrectSolution = true;
			for (int i = 0; i < this->verticesCount && isCorrectSolution; ++i) {
				if (solution->getFreeCellsInColumn(i) == 0 && solution->getWeight(i) == 0) continue;
				isCorrectSolution = false;
			}

			return isCorrectSolution;
		}
};
