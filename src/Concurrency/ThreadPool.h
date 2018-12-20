/**
 * @file    ThreadPool.h
 * @author  Tomáš Michna
 * @date    May, 2018
 * @bug     No known bugs
 * @brief   Implementation of class ThreadPool
 *
 * This file contains implementation of ThreadPool class
 */

#pragma once

#include <functional>
#include <thread>
#include "ThreadSafeQueue.h"

class ThreadPool {
	private:
		int numberOfThread;
		ThreadSafeQueue<std::function<void()>> queue;
	public:


		/**
 		 * Constructor which create a new ThreadPool
 		 *
 		 * @param n is number of threads
 		 */
		explicit ThreadPool(int n) {
			this->numberOfThread = n;
		}

		/**
 		 * This method adding function with parameters to the thread safe queue
 		 *
 		 * @param f is type of std::function<void()>
 		 */
		void addJob(std::function<void()> f) {
			queue.push(f);
		}

		/**
 		 * This method start parallel processing tasks from queue
 		 */
		void execute() {
			std::vector<std::thread> threads;
			for (int i = 0; i < this->numberOfThread; i++) {
				threads.emplace_back(std::thread([this]() {
					while (true) {
						std::function<void()> task;
						bool result = this->queue.tryPop(task);
						if (!result) break;
						task();
					}
				}));
			}
			for (auto & thread : threads) {
				if (thread.joinable()) {
					thread.join();
				}
			}
		}
};