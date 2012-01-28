#ifndef CALLBACK1_HPP
#define	CALLBACK1_HPP

namespace event
{
	
	/**
	 * Base class for an event callback with one argument.
         */
	template<class A1>
	class callback1_base : public callback_base
	{
	protected:
		virtual void execute(A1 arg1) = 0;
		
	public:
		callback1_base(void* object, function_pointer_t pointer);
		callback1_base(const callback1_base& orig);
		virtual callback1_base* clone() const = 0;
		
		void operator()(A1 arg1);
	};
	
	/**
	 * Method callback for an event with one argument.
	 */
	template<class T, class A1>
	class callback1_method : public callback1_base<A1>
	{
	public:
		typedef void (T::*method_pointer_t)(A1);
	private:
		/**
		 * Pointer to the method to call.
                 */
		method_pointer_t method_pointer;
	public:
		callback1_method(void* object, method_pointer_t pointer);
		callback1_method(const callback1_method& orig);
		virtual callback1_method* clone() const;
		
	protected:
		virtual void execute(A1 arg1);
	};
	
	template<class T, class A1>
	callback1_method<T, A1> event_listener(T* object, void (T::*method_pointer)(A1));
	
	/**
	 * Base class for an event with one parameter.
	 */
	template<class A1>
	class event1_base
	{
	private:
		typedef callback1_base<A1> callback_t;
		typedef class std::list<callback_t*> callback_list_t;
		typedef class callback_list_t::iterator callback_list_it_t;
		
		std::list<callback_t*> callbacks;
	public:
		event1_base();
		~event1_base();
		
		void operator+=(const callback_t& cb);
		void operator-=(callback_t& cb);
		void operator()(A1 arg1);
	};
	
	/**
	 * Creates a new callback1_base object.
	 * 
         * @param object Pointer to object (used for method pointers).
         * @param pointer Function pointer.
         */
	template<class A1>
	callback1_base<A1>::callback1_base(void* object, callback1_base::function_pointer_t pointer)
		: callback_base(object, pointer)
	{
		
	}
	
	/**
	 * Copy constructor.
	 * 
         * @param orig Object to copy.
         */
	template<class A1>
	callback1_base<A1>::callback1_base(const callback1_base& orig)
		: callback_base(orig)
	{
		
	}
	
	/**
	 * Executes the callback.
	 * 
         * @param arg1 The first argument.
         */
	template<class A1>
	void callback1_base<A1>::operator()(A1 arg1)
	{
		this->execute(arg1);
	}
	
	/**
	 * Creates a new callback1_method object.
	 * 
         * @param object Pointer to object (used for method pointers).
         * @param pointer Method pointer.
         */
	template<class T, class A1>
	callback1_method<T, A1>::callback1_method(void* object, method_pointer_t pointer)
		: callback1_base<A1>(object, 0), method_pointer(pointer)
	{
		
	}
	
	/**
	 * Copy constructor.
	 * 
         * @param orig Object to copy.
         */
	template<class T, class A1>
	callback1_method<T, A1>::callback1_method(const callback1_method& orig)
		: callback1_base<A1>(orig), method_pointer(orig.method_pointer)
	{
		
	}
	
	/**
	 * Creates a new instance of this class on the heap and then copies this
	 * object into it.
	 * 
         * @return Pointer to the clone.
         */
	template<class T, class A1>
	callback1_method<T, A1>* callback1_method<T, A1>::clone() const
	{
		return new callback1_method(*this);
	}
	
	/**
	 * Executes the callback.
	 * 
         * @param arg1 The first argument.
         */
	template<class T, class A1>
	void callback1_method<T, A1>::execute(A1 arg1)
	{
		T* object = (T*)this->get_object();
		(object->*(this->method_pointer))(arg1);
	}
	
	/**
	 * Helper function that returns a callback to a method accepting 1 
	 * argument.
	 * 
         * @param object The object.
         * @param method_pointer The method.
         * @return Callback to the method.
         */
	template<class T, class A1>
	callback1_method<T, A1> event_listener(T* object, void (T::*method_pointer)(A1))
	{
		return callback1_method<T, A1>(object, method_pointer);
	}
	
	/**
	 * Creates a new event1_base object.
         */
	template<class A1>
	event1_base<A1>::event1_base()
	{
		
	}
	
	/**
	 * Frees all used resources.
         */
	template<class A1>
	event1_base<A1>::~event1_base()
	{
		typename event1_base::callback_list_it_t it;
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
	template<class A1>
	void event1_base<A1>::operator+=(const event1_base::callback_t& cb)
	{
		typename event1_base::callback_list_it_t result;
		//event1_base::callback_t* pcb = cb.clone();
		callback_equals<typename event1_base::callback_t> predicate(&cb);
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
	template<class A1>
	void event1_base<A1>::operator-=(event1_base::callback_t& cb)
	{
		typename event1_base::callback_list_it_t result;
		callback_equals<typename event1_base::callback_t> predicate(&cb);
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
         */
	template<class A1>
	void event1_base<A1>::operator()(A1 arg1)
	{
		typename event1_base::callback_list_it_t it;
		for (it = this->callbacks.begin(); 
		     it != this->callbacks.end(); it++)
		{
			(*(*it))(arg1);
		}
	}
}

#endif	/* CALLBACK1_HPP */

