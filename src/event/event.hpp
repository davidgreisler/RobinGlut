#ifndef EVENT_HPP
#define	EVENT_HPP

#include <list>
#include <algorithm>

#include "callback_base.hpp"
#include "callback_equals.hpp"
#include "callback1.hpp"
#include "callback2.hpp"

namespace event
{
	/**
	 * Event with 2 parameters.
	 */
	template<class A1, class A2 = void>
	class event : public event2_base<A1, A2> {};
	
	/**
	 * Event with a single parameter.
	 */
	template<class A1>
	class event<A1> : public event1_base<A1> {};
}

#endif	/* EVENT_HPP */

