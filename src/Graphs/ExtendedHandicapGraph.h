/**
 * @file    ExtendedHandicapGraph.h
 * @author  Tomáš Michna
 * @date    May, 2018
 * @bug     No known bugs
 * @brief   Implementation of class ExtendedHandicapGraph
 *
 * This file contains implementation of ExtendedHandicapGraph class
 */

#pragma once

#include "MagicRegularGraph.h"
#include "Validators/GraphValidator.h"

class ExtendedHandicapGraph : public MagicRegularGraph {
	private:
		int missingLabel;

		/**
  		 * This method compute and return missing label in extended handicap labeling
  		 *
  		 * @return missing label is in numeric format
  		 */
		int computeMissingLabel() const {
			return this->getVerticesCount() / 2 + 1;
		}

	public:
		/**
 		 * Constructor of new ExtendedHandicapGraph
 		 *
 		 * @param verticesCount is in numeric format
 		 * @param regularConstant is in numeric format
 		 * @param validator is smart pointer, which point to GraphValidator class
 		 */
		ExtendedHandicapGraph(int verticesCount, int regularCount, std::unique_ptr<GraphValidator> & validator)
				: MagicRegularGraph(verticesCount, regularCount) {
			validator->validate(this);
			this->missingLabel = this->computeMissingLabel();
		}

		/**
	     * This method return missing label in extended handicap labeling
	     *
	     * @return missing label is in numeric format
	     */
		int getMissingLabel() const {
			return this->missingLabel;
		}
};
