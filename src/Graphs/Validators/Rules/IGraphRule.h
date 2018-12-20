/**
 * @file    IGraphRule.h
 * @author  Tomáš Michna
 * @date    May, 2018
 * @bug     No known bugs
 * @brief   Implementation of class IGraphRule
 *
 * This file contains implementation of IGraphRule class
 */

#pragma once

#include "../../MagicRegularGraph.h"

class IGraphRule {
	public:

		/**
  		 * This method is virtual. For implement some validation rule
  		 *
  		 * @param pointer to point MagicRegularGraph
  		 */
		virtual void validate(MagicRegularGraph * graph) = 0;
};
