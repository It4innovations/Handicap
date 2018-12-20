/**
 * @file    EvenVerticesCountRule.h
 * @author  Tomáš Michna
 * @date    May, 2018
 * @bug     No known bugs
 * @brief   Implementation of class EvenVerticesCountRule
 *
 * This file contains implementation of EvenVerticesCountRule class
 */

#pragma once

#include "IGraphRule.h"

class EvenVerticesCountRule : public IGraphRule {
	public:

		/**
  		 * This method validate MagicRegularGraph if it has got even number of vertices
  		 *
  		 * @param pointer to point MagicRegularGraph
  		 */
		void validate(MagicRegularGraph * graph) override {
			if (graph->getVerticesCount() % 2 == 1) {
				throw "Vertices must be even at Magic regular graph\n";
			}
		}
};
