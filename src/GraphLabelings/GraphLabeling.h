/**
 * @file    GraphLabeling.h
 * @author  Tomáš Michna
 * @date    May, 2018
 * @bug     No known bugs
 * @brief   Implementation of class GraphLabeling
 *
 * This file contains implementation of GraphLabeling class
 */

#pragma once

#include "../Graphs/ExtendedHandicapGraph.h"
#include "../Outputs/TextPrinter.h"
#include "../Solvers/kSumProblemSolver.h"
#include "../Structures/LabelingSolution.h"
#include "../Solvers/CombinatorialGenerator.h"
#include "Solution/SolutionPrinter.h"
#include "Solution/SolutionValidator.h"
#include <memory>
#include <mutex>
#include <stack>

class GraphLabeling {
	private:
		std::shared_ptr<ExtendedHandicapGraph> graph{};
		std::unique_ptr<LabelingSolution<int>> solution;
		std::unique_ptr<SolutionValidator> solutionValidator;
		std::unique_ptr<SolutionPrinter> solutionPrinter;
		std::unique_ptr<CombinatorialGenerator> generator{};
		std::unique_ptr<std::stack<int>[]> intermediateNSumResults{};

		std::unique_ptr<int[]> disabledNumbersArray{};

		//GraphInfo graphInfo;
		int levelOfRecursion = {-1};

		/**
  		 * That method unmark neighbours labels from matrix
  		 *
  		 * @param label is in a numeric format
  		 * @param missingNeighbours is in numeric format
  		 */
		inline void unmarkLabelsFromSolution(const int label, const int missingNeigbours) {
			for (int slot = 0; slot < missingNeigbours; ++slot) {
				solution->prepareUnsetLabel(label);
				solution->prepareUnsetLabel(intermediateNSumResults[levelOfRecursion].top());
				intermediateNSumResults[levelOfRecursion].pop();
			}
			solution->unsetLabels();
		}

		/**
  		 * That method mark neighbours labels to matrix
  		 *
  		 * @param label is in a numeric format
  		 * @param missingNeighbours is in numeric format
  		 */
		inline void markLabelsToSolution(int label, int missingNeighbours) {
			for (int slot = 0; slot < missingNeighbours; ++slot) {
				this->disabledNumbersArray[slot] = this->intermediateNSumResults[this->levelOfRecursion].top();
				const int neighbourLabel = this->disabledNumbersArray[slot];
				solution->prepareSetLabel(label, neighbourLabel);
				solution->prepareSetLabel(neighbourLabel, label);
				this->intermediateNSumResults[this->levelOfRecursion].pop();
			}
			solution->setLabels();
		}

	public:
		static int numberOfSolution;

		/**
 		 * Constructor which create new GraphLabeling
 		 *
 		 * @param ExtendedHandicapGraph is a smart pointer to ExtendedHandicapGraph
 		 */
		explicit GraphLabeling(std::shared_ptr<ExtendedHandicapGraph> & graph) : graph{graph} {
			solutionValidator = std::unique_ptr<SolutionValidator>(new SolutionValidator(graph));
			solutionPrinter = std::unique_ptr<SolutionPrinter>(new SolutionPrinter(graph));
			generator = std::unique_ptr<CombinatorialGenerator>(new CombinatorialGenerator(graph));
			this->solution = std::unique_ptr<LabelingSolution<int>>(
					new LabelingSolution<int>(graph->getRegularConstant(), graph->getVerticesCount() + 2,
					                          graph->getMissingLabel()));

			this->intermediateNSumResults = std::unique_ptr<std::stack<int>[]>(
					new std::stack<int>[graph->getVerticesCount() + 1]);
			this->disabledNumbersArray = std::unique_ptr<int[]>(new int[graph->getRegularConstant()]());

			for (int i = 0; i < graph->getVerticesCount() + 2; i++) {
				this->solution->setMagicWeight(i, (i == 0 || i == graph->getMissingLabel()) ? 0 :
				                                  graph->getMagicConstant() + i);
			}
		}

		/**
  		 * This is recursive method, which solve and manage filling neighbours for one label in one call
  		 *
  		 * @param label is in a numeric format
  		 * @param mut is in a std::mutex
  		 */
		void solve(int label, std::mutex & mut) {
			++this->levelOfRecursion;
			const int freeSlots = solution->getFreeCellsInColumn(label);

			generator->setSizeOfSet(freeSlots);
			generator->setCurrentLabel(label);
			generator->setMissingWeight(this->solution->getWeight(label));
			generator->computePossibleCombination(intermediateNSumResults[levelOfRecursion], solution);

			const int resultsCount = (int) this->intermediateNSumResults[levelOfRecursion].size() / freeSlots;
			for (int position = 0; position < resultsCount; ++position) {
				// mark numbers to solution
				this->markLabelsToSolution(label, freeSlots);

				for (int slot = 0; slot < freeSlots; ++slot) {
					this->intermediateNSumResults[levelOfRecursion].emplace(this->disabledNumbersArray[slot]);
				}

				if (solution->getFilledCells() == graph->getEdgesCount() * 2) {
					if (this->solutionValidator->validate(solution)) {
						std::lock_guard<std::mutex> lock{mut};
						++GraphLabeling::numberOfSolution;
						solutionPrinter->print(solution, GraphLabeling::numberOfSolution);
					}

				} else {
					const int nextLabelIndex = solution->selectNextLabel();
					this->solve(nextLabelIndex, mut);
				}
				// unmark numbers from solution
				this->unmarkLabelsFromSolution(label, freeSlots);
			}
			--levelOfRecursion;
		}

		/**
  		 * This is starting method for filling first neighbours in parallel running
  		 *
  		 * @param label is in a numeric format
  		 * @param vec is in a std::vector contains numeric value
  		 * @param mut is in a std::mutex
  		 */
		void prepareSolve(int label, std::vector<int> vec, std::mutex & mut) {
			++this->levelOfRecursion;
			const int freeSlots = solution->getFreeCellsInColumn(label);
			for (int slot = 0; slot < (int) vec.size(); ++slot) {
				this->intermediateNSumResults[levelOfRecursion].emplace(vec[slot]);
			}
			this->markLabelsToSolution(label, freeSlots);

			for (int slot = 0; slot < freeSlots; ++slot) {
				this->intermediateNSumResults[levelOfRecursion].emplace(this->disabledNumbersArray[slot]);
			}

			const int nextLabelIndex = solution->selectNextLabel();
			this->solve(nextLabelIndex, mut);

			// unmark numbers from solution
			this->unmarkLabelsFromSolution(label, freeSlots);

			--levelOfRecursion;
		}
};
