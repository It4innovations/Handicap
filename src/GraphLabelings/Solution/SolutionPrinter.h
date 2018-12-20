/**
 * @file    SolutionPrinter.h
 * @author  Tomáš Michna
 * @date    May, 2018
 * @bug     No known bugs
 * @brief   Prototype of class SolutionPrinter
 *
 * This file contains prototype of SolutionPrinter class
 */

#pragma once

#include <memory>
#include "../../Outputs/TextPrinter.h"
#include "../../Structures/LabelingSolution.h"

class SolutionPrinter {
	private:
		std::unique_ptr<TextPrinter> printer = nullptr;
	public:

		/**
 		 * Constructor which create a new SolutionPrinter
 		 *
 		 * @param graph is a smart pointer to ExtendedHandicapGraph
 		 */
		explicit SolutionPrinter(std::shared_ptr<ExtendedHandicapGraph> & graph) {
			this->printer = std::unique_ptr<TextPrinter>(new TextPrinter(graph));
		}

		/**
         * That method print matrix solution
         *
         * @param solution is a smart pointer to LabelingSolution
         * @param numberofSolution is in a numeric format
         */
		void print(std::unique_ptr<LabelingSolution<int>> & solution, int numberofSolution) {
			this->printer->print(solution, numberofSolution);
		}
};
