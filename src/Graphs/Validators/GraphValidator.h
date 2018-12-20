/**
 * @file    GraphValidator.h
 * @author  Tomáš Michna
 * @date    May, 2018
 * @bug     No known bugs
 * @brief   Implementation of class GraphValidator
 *
 * This file contains implementation of GraphValidator class
 */

#pragma once

#include <vector>
#include <memory>
#include "../MagicRegularGraph.h"
#include "Rules/IGraphRule.h"
#include "Rules/EvenVerticesCountRule.h"
#include "Rules/PositiveEdgesCountRule.h"
#include "Rules/PositiveRegularConstantRule.h"
#include "Rules/PositiveVerticesCountRule.h"

class GraphValidator {
	private:
		std::vector<std::unique_ptr<IGraphRule>> rules;
	public:

		/**
		 * Constructor of new GraphValidator
		 */
		GraphValidator() {
			this->rules.emplace_back(std::unique_ptr<EvenVerticesCountRule> (new EvenVerticesCountRule()));
			this->rules.emplace_back(std::unique_ptr<PositiveEdgesCountRule> (new PositiveEdgesCountRule()));
			this->rules.emplace_back(std::unique_ptr<PositiveRegularConstantRule> (new PositiveRegularConstantRule()));
			this->rules.emplace_back(std::unique_ptr<PositiveVerticesCountRule> (new PositiveVerticesCountRule()));
		}

		/**
		 * Destructor of GraphValidator
		 */
		~GraphValidator() {
			this->rules.clear();
		}

		/**
 		 * This method validate graph according to validations rule
 		 *
 		 * @param graph is pointer for instance of MagicRegularGraph
 		 */
		void validate(MagicRegularGraph * graph) {
			for (auto & rule : this->rules) {
				rule->validate(graph);
			}
		}
};
