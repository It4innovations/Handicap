/**
 * @file    TextPrinter.h
 * @author  Tomáš Michna
 * @date    May, 2018
 * @bug     No known bugs
 * @brief   Implementation of class Matrix
 *
 * This file contains implementation of TextPrinter class
 */

#pragma once

#include "../Graphs/ExtendedHandicapGraph.h"
#include "../Structures/Matrix.h"
#include "../Structures/LabelingSolution.h"
#include <iostream>
#include <algorithm>

class TextPrinter {
	private:
		std::unique_ptr<int[]> neighbour;
		std::shared_ptr<ExtendedHandicapGraph> graph;
	public:

		/**
 		 * Constructor of new TextPrinter
 		 *
 		 * @param graph graph is smart pointer which point to Graph class
 		 */
		explicit TextPrinter(std::shared_ptr<ExtendedHandicapGraph> & graph) {
			this->graph = graph;
			this->neighbour = std::unique_ptr<int[]>(new int[graph->getRegularConstant()]);
		}

		/**
   		 * This method is used when we want to print final matrix solution
   		 *
   		 * @param matrix is a smart pointer which points to LabelingSolution class, it contains matrix
    	 * @param numberOfSolution is in numeric format
  		 */
		void print(std::unique_ptr<LabelingSolution<int> > & matrix, const int & numberOfSolution) {
			std::cout << '#' << numberOfSolution << '\n';
			for (int i = 1; i < this->graph->getVerticesCount()+2; ++i) {
				if (this->graph->getMissingLabel() == i) {
					continue;
				}
				std::cout << i << "\t|";

				for (int j = 0; j < graph->getRegularConstant(); j++) {
					this->neighbour[j] = matrix->get(j, i);
				}

				std::sort(this->neighbour.get(), this->neighbour.get() + this->graph->getRegularConstant());
				for (int j = 0; j < this->graph->getRegularConstant(); j++) {
					std::cout << '\t' << this->neighbour[j];
				}
				std::cout << '\n';
			}
			std::cout << "\n\n";
		}
};
