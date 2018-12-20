/**
 * @file    PositiveRegularConstantRule.h
 * @author  Tomáš Michna
 * @date    May, 2018
 * @bug     No known bugs
 * @brief   Implementation of class PositiveRegularConstantRule
 *
 * This file contains implementation of PositiveRegularConstantRule class
 */


#pragma once

#include "IGraphRule.h"

class PositiveRegularConstantRule : public IGraphRule{
	public:

		/**
  		 * This method validate MagicRegularGraph if it has got positive number of regular
  		 *
  		 * @param pointer to point MagicRegularGraph
  		 */
		void validate(MagicRegularGraph * graph) override {
			if ((graph->getRegularConstant() < 0)) {
				throw "Regular number must be positive number\n";
			}
		}
};
