#ifndef CALLBACK2_HPP
#define	CALLBACK2_HPP

namespace event
{
	/**
	 * Base class for an event callback with two arguments.
         */
	template<class A1, class A2>
	class callback2_base : public callback_base
	{
	protected:
		virtual void execute(A1 arg1, A2 arg2) = 0;
		
	public:
		callback2_base(void* object, function_pointer_t pointer);
		callback2_base(const callback2_base& orig);
		virtual callback2_base* clone() const = 0;
		
		void operator()(A1 arg1, A2 arg2);
	};
	
	/**
	 * Method callback for an event with two arguments.
	 */
	template<class T, class A1, class A2>
	class callback2_method : public callback2_base<A1, A2>
	{
	public:
		typedef void (T::*method_pointer_t)(A1, A2);
	private:
		/**
		 * Pointer to the method to call.
                 */
		method_pointer_t method_pointer;
	public:
		callback2_method(void* object, method_pointer_t pointer);
		callback2_method(const callback2_method& orig);
		virtual callback2_method* clone() const;
		
	protected:
		virtual void execute(A1 arg1, A2 arg2);
	};
	
	template<class T, class A1, class A2>
	callback2_method<T, A1, A2> event_listener(T* object, void (T::*method_pointer)(A1, A2));
	
	/**
	 * Base class for an event with two parameters.
	 */
	template<class A1, class A2>
	class event2_base
	{
	private:
		typedef callback2_base<A1, A2> callback_t;
		typedef class std::list<callback_t*> callback_list_t;
		typedef class callback_list_t::iterator callback_list_it_t;
		
		std::list<callback_t*> callbacks;
	public:
		event2_base();
		~event2_base();
		
		void operator+=(callback_t& cb);
		void operator-=(callback_t& cb);
		void operator()(A1 arg1, A2 arg2);
	};
	
	/**
	 * Creates a new callback2_base object.
	 * 
         * @param object Pointer to object (used for method pointers).
         * @param pointer Function pointer.
         */
	template<class A1, class A2>
	callback2_base<A1, A2>::callback2_base(void* object, function_pointer_t pointer)
		: callback_base(object, pointer)
	{
		
	}
	
	/**
	 * Copy constructor.
	 * 
         * @param orig Object to copy.
         */
	template<class A1, class A2>
	callback2_base<A1, A2>::callback2_base(const callback2_base& orig)
		: callback_base(orig)
	{
		
	}
	
	/**
	 * Executes the callback.
	 * 
         * @param arg1 The first argument.
	 * @param arg2 The second argument.
         */
	template<class A1, class A2>
	void callback2_base<A1, A2>::operator()(A1 arg1, A2 arg2)
	{
		this->execute(arg1, arg2);
	}
	
	
	
	/**
	 * Creates a new callback2_method object.
	 * 
         * @param object Pointer to object (used for method pointers).
         * @param pointer Method pointer.
         */
	template<class T, class A1, class A2>
	callback2_method<T, A1, A2>::callback2_method(void* object, method_pointer_t pointer)
		: callback2_base<A1, A2>(object, 0), method_pointer(pointer)
	{
		
	}
	
	/**
	 * Copy constructor.
	 * 
         * @param orig Object to copy.
         */
	template<class T, class A1, class A2>
	callback2_method<T, A1, A2>::callback2_method(const callback2_method& orig)
		: callback2_base<A1, A2>(orig), method_pointer(orig.method_pointer)
	{
		
	}
	
	/**
	 * Creates a new instance of this class on the heap and then copies this
	 * object into it.
	 * 
         * @return Pointer to the clone.
         */
	template<class T, class A1, class A2>
	callback2_method<T, A1, A2>* callback2_method<T, A1, A2>::clone() const
	{
		return new callback2_method(*this);
	}
	
	/**
	 * Executes the callback.
	 * 
         * @param arg1 The first argument.
	 * @param arg2 The second argument.
         */
	template<class T, class A1, class A2>
	void callback2_method<T, A1, A2>::execute(A1 arg1, A2 arg2)
	{
		T* object = this->get_object();
		(object->*(this->method_pointer))(arg1, arg2);
	}
	
	
	
	/**
	 * Helper function that returns a callback to a method accepting 2 
	 * arguments.
	 * 
         * @param object The object.
         * @param method_pointer The method.
         * @return Callback to the method.
         */
	template<class T, class A1, class A2>
	callback2_method<T, A1, A2> event_listener(T* object, void (T::*method_pointer)(A1, A2))
	{
		return callback2_method<T, A1, A2>(object, method_pointer);
	}
	
	
	
	/**
	 * Creates a new event2_base object.
         */
	template<class A1, class A2>
	event2_base<A1, A2>::event2_base()
	{
		
	}
	
	/**
	 * Frees all used resources.
         */
	template<class A1, class A2>
	event2_base<A1, A2>::~event2_base()
	{
		typename event2_base::callback_list_it_t it;
		for (it = this->callbacks.begin(); 
		     it != this->callbacks.end(); it++)
		{
			delete *it;
		}
	}
	
	/**
	 * Adds the given callback as listener to this event if it isn't listed
	 * yet.
	 * 
         * @param cb Callback to add.
         */
	template<class A1, class A2>
	void event2_base<A1, A2>::operator+=(event2_base::callback_t& cb)
	{
		typename event2_base::callback_list_it_t result;
		callback_equals<event2_base::callback_t> predicate;
		result = std::find_if(this->callbacks.begin(),
		                      this->callbacks.end(), 
				      predicate);

		if (this->callbacks.end() == result)
		{
			this->callbacks.push_back(cb.clone());
		}
	}
	
	/**
	 * Removes the given callback from this event if it's listening to it.
	 * 
         * @param cb Callback to remove.
         */
	template<class A1, class A2>
	void event2_base<A1, A2>::operator-=(event2_base::callback_t& cb)
	{
		typename event2_base::callback_list_it_t result;
		callback_equals<event2_base::callback_t> predicate;
		result = std::find_if(this->callbacks.begin(),
		                      this->callbacks.end(), 
				      predicate);

		if (this->callbacks.end() != result)
		{
			delete *result;
			this->callbacks.erase(result);
		}
	}
	
	/**
	 * Calls all listeners.
	 * 
         * @param arg1 First argument.
	 * @param arg2 Second argument.
         */
	template<class A1, class A2>
	void event2_base<A1, A2>::operator()(A1 arg1, A2 arg2)
	{
		typename event2_base::callback_list_it_t it;
		for (it = this->callbacks.begin(); 
		     it != this->callbacks.end(); it++)
		{
			(*(*it))(arg1, arg2);
		}
	}
	
}

#endif	/* CALLBACK2_HPP */

