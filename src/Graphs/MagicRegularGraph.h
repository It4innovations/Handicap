/**
 * @file    MagicRegularGraph.h
 * @author  Tomáš Michna
 * @date    May, 2018
 * @bug     No known bugs
 * @brief   Implementation of class MagicRegularGraph
 *
 * This file contains implementation of MagicRegularGraph class
 */

#pragma once

class MagicRegularGraph {
	private:
		int edgesCount;
		int verticesCount;
		int regularConstant;
		int magicConstant;

		/**
  		 * This method compute and return magic constant of MagicRegularGraph
  		 *
  		 * @return magic constant in numeric format
  		 */
		int computeMagicConstant() const {
			return (this->getRegularConstant() - 1) * ((this->getVerticesCount() / 2) + 1);
		}

	public:

		/**
 		 * Constructor of new MagicRegularGraph
 		 *
 		 * @param verticesCount is in numeric format
 		 * @param regularConstant is in numeric format
 		 */
		MagicRegularGraph(int verticesCount, int regularConstant) : verticesCount(verticesCount),
		                                                            regularConstant(regularConstant) {
			this->edgesCount = (verticesCount * regularConstant) / 2;
			this->magicConstant = this->computeMagicConstant();
		}

		/**
 		 * This method returns number of MagicRegularGraph vertices
 		 *
 		 * @return number of MagicRegularGraph vertices in numeric format
 		 */
		int getVerticesCount() const {
			return this->verticesCount;
		}

		/**
  		 * This method returns number of MagicRegularGraph edges
  		 *
  		 * @return number of MagicRegularGraph edges in numeric format
  		 */
		int getEdgesCount() const {
			return this->edgesCount;
		}

		/**
   		 * This method returns magic constant of MagicRegularGraph
   		 *
   		 * @return magic constant is in numeric format
   		 */
		int getMagicConstant() const {
			return this->magicConstant;
		}

		/**
  		 * This method returns regular constant of MagicRegularGraph
  		 *
  		 * @return regular constant of MagicRegularGraph is in numeric format
  		 */
		int getRegularConstant() const {
			return this->regularConstant;
		}
};
