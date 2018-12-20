/**
 * @file    PositiveEdgesCountRule.h
 * @author  Tomáš Michna
 * @date    May, 2018
 * @bug     No known bugs
 * @brief   Implementation of class PositiveEdgesCountRule
 *
 * This file contains implementation of PositiveEdgesCountRule class
 */

#pragma once

#include "IGraphRule.h"

class PositiveEdgesCountRule : public IGraphRule {
	public:

		/**
  		 * This method validate MagicRegularGraph if it has got positive number of edges
  		 *
  		 * @param pointer to point MagicRegularGraph
  		 */
		void validate(MagicRegularGraph * graph) override {
			if ((graph->getEdgesCount() < 0)) {
				throw "Edges count isn`t positive number\n";
			}
		}
};
