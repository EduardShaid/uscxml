/**
 *  @file
 *  @author     2016 Stefan Radomski (stefan.radomski@cs.tu-darmstadt.de)
 *  @copyright  Simplified BSD
 *
 *  @cond
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the FreeBSD license as published by the FreeBSD
 *  project.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 *  You should have received a copy of the FreeBSD license along with this
 *  program. If not, see <http://www.opensource.org/licenses/bsd-license>.
 *  @endcond
 */

#ifndef BASICEVENTQUEUE_H_39DCC18B
#define BASICEVENTQUEUE_H_39DCC18B

#include "EventQueueImpl.h"
#include <string>
#include <map>
#include <list>
#include <thread>
#include <mutex>
#include <condition_variable>

#include <event2/event.h>


namespace uscxml {

/**
 * @ingroup eventqueue
 * @ingroup impl
 */
class USCXML_API BasicEventQueue : public EventQueueImpl {
public:
	BasicEventQueue();
	virtual ~BasicEventQueue();
	virtual Event dequeue(size_t blockMs);
	virtual void enqueue(const Event& event);
    virtual void reset();
    
protected:
	std::list<Event> _queue;
	std::recursive_mutex _mutex;
	std::condition_variable_any _cond;
};

/**
 * @ingroup eventqueue
 * @ingroup impl
 */
class USCXML_API BasicDelayedEventQueue : public BasicEventQueue, public DelayedEventQueueImpl {
public:
	BasicDelayedEventQueue(DelayedEventQueueCallbacks* callbacks);
	virtual ~BasicDelayedEventQueue();
	virtual void enqueueDelayed(const Event& event, size_t delayMs, const std::string& eventUUID);
	virtual void cancelDelayed(const std::string& eventId);
	virtual void cancelAllDelayed();
	virtual Event dequeue(size_t blockMs) {
		return BasicEventQueue::dequeue(blockMs);
	}
	virtual void enqueue(const Event& event) {
		return BasicEventQueue::enqueue(event);
	}
    virtual void reset();

protected:
	struct callbackData {
		Event userData;
		std::string eventUUID;
		bool persist;
		struct event *event;
		BasicDelayedEventQueue* eventQueue;
	};

	bool _isStarted;
	std::thread* _thread;

	std::map<std::string, callbackData> _callbackData;
	struct event_base* _eventLoop;
	struct event* _dummyEvent;

	static void run(void* instance);
	void start();
	void stop();

	static void timerCallback(evutil_socket_t fd, short what, void *arg);
	DelayedEventQueueCallbacks* _callbacks;
};

}

#endif /* end of include guard: BASICEVENTQUEUE_H_39DCC18B */
