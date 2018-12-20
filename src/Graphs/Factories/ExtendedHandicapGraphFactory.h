/**
 * @file    ExtendedHandicapGraphFactory.h
 * @author  Tomáš Michna
 * @date    May, 2018
 * @bug     No known bugs
 * @brief   Implementation of class ExtendedHandicapGraphFactory
 *
 * This file contains implementation of ExtendedHandicapGraphFactory class
 */

#pragma once

#include "../ExtendedHandicapGraph.h"

class ExtendedHandicapGraphFactory {
	public:

		/**
  		 * This method create new smart pointer of ExtendedHandicapGraph
  		 *
  		 * @param regularConstant is in numeric format
  		 * @param verticesCount is in numeric format
  		 * @return smart shared pointer to ExtendedHandicapGraph
  		 */
		std::shared_ptr<ExtendedHandicapGraph> create(int verticesCount, int regularConstant) {
			std::unique_ptr<GraphValidator> validator(new GraphValidator());
			return std::make_shared<ExtendedHandicapGraph>(verticesCount, regularConstant, validator);
		}
};
