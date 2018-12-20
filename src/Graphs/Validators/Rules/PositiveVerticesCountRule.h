/**
 * @file    PositiveVerticesCountRule.h
 * @author  Tomáš Michna
 * @date    May, 2018
 * @bug     No known bugs
 * @brief   Implementation of class PositiveVerticesCountRule
 *
 * This file contains implementation of PositiveVerticesCountRule class
 */

#pragma once

#include "IGraphRule.h"

class PositiveVerticesCountRule : public IGraphRule {
	public:

		/**
  		 * This method validate MagicRegularGraph if it has got positive number of vertices
  		 *
  		 * @param pointer to point MagicRegularGraph
  		 */
		void validate(MagicRegularGraph * graph) override {
			if ((graph->getVerticesCount() <= 0)) {
				throw "Vertices count isn`t positive number\n";
			}
		};
};
