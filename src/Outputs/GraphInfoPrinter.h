/**
 * @file    GraphInfoPrinter.h
 * @author  Tomáš Michna
 * @date    May, 2018
 * @bug     No known bugs
 * @brief   Implementation of class GraphInfoPrinter
 *
 * This file contains implementation of GraphInfoPrinter class
 */

#pragma once

#include <iostream>
#include <array>
#include "../Graphs/ExtendedHandicapGraph.h"

class GraphInfoPrinter {
	public:

		/**
		 * This method print statistics about Extended graph
		 *
		 * @param graph is a smart pointer which points to ExtendedHandicapGraph class
		 */
		static void print(std::shared_ptr<ExtendedHandicapGraph> & graph) {
			std::cout << "extended handicap regular graphs\n"
			          << "Vertices count: " << graph->getVerticesCount()
			          << "\nRegular number: " << graph->getRegularConstant()
			          << "\nMagic constant l: " << graph->getMagicConstant()
			          << "\nMissing label: " << graph->getMissingLabel()
			          << '\n';
		}

		/**
		 * This method print statistics about MagicRegularGraph graph
		 *
		 * @param graph is a smart pointer which points to MagicRegularGraph class
		 */
		static void print(std::shared_ptr<MagicRegularGraph> & graph) {
			std::cout << "Vertices count: " << graph->getVerticesCount()
			          << "\nRegular number: " << graph->getRegularConstant()
			          << "\nMagic constant:    " << graph->getMagicConstant()
			          << '\n';
		}
};
