/**
 * @file    ThreadSafeQueue.h
 * @author  Tomáš Michna
 * @date    May, 2018
 * @bug     No known bugs
 * @brief   Implementation of class ThreadSafeQueue
 *
 * This file contains implementation of ThreadSafeQueue class
 */


#pragma once

#include <atomic>
#include <mutex>
#include <queue>
#include <condition_variable>

template <typename T>
class ThreadSafeQueue {
	private:
        std::atomic_bool valid = {true};
		mutable std::mutex mut;
		std::queue<T> queue;
		std::condition_variable conditionVariable;

	public:

		/**
 	   	 * That method push new valu into queue
 		 *
 		 * @param value is T parameter typicaly is in numeric format
 		 */
		void push(T value) {
			std::lock_guard<std::mutex> lock{this->mut};
			this->queue.push(std::move(value));
			this->conditionVariable.notify_one();
		}

		/**
 		 * That method pop element from queue and return if pop was successful
 		 *
 		 * @param out is typically in numeric format which pop element
 		 * @return bool if pop was successfull
 		 */
		bool tryPop(T & out) {
			std::lock_guard<std::mutex> lock{this->mut};
			if (this->queue.empty() || !this->valid) {
				return false;
			}
			out = std::move(this->queue.front());
			this->queue.pop();
			return true;
		}

		/**
 		 * That method destruct queue
 		 */
		~ThreadSafeQueue() {
			std::lock_guard<std::mutex> lock{this->mut};
			this->valid = false;
			this->conditionVariable.notify_all();
		}

};
