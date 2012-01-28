#ifndef CALLBACK_BASE_HPP
#define	CALLBACK_BASE_HPP

namespace event
{

	/**
	 * Base class for event callbacks.
	 */
	class callback_base
	{
	public:
		typedef void (*function_pointer_t)();
	private:
		/**
		 * Pointer to the object.
		 */
		void* object;

		/**
		 * The function pointer.
		 */
		function_pointer_t function_pointer;

	protected:

		/**
		 * Returns the object.
		 * 
		 * @return The object.
		 */
		void* get_object()
		{
			return this->object;
		}

		/**
		 * Returns the function pointer.
		 * 
		 * @return The function pointer.
		 */
		function_pointer_t get_function_pointer()
		{
			return this->function_pointer;
		}

	public:

		/**
		 * Creates a new callback_base object.
		 * 
		 * @param object Pointer to object (used for method pointers).
		 * @param pointer Function pointer.
		 */
		callback_base(void* object, function_pointer_t pointer)
			: object(object), function_pointer(pointer)
		{

		}

		/**
		 * Copy constructor.
		 * 
		 * @param orig Object to copy.
		 */
		callback_base(const callback_base& orig)
			: object(orig.object), function_pointer(orig.function_pointer)
		{

		}

		/**
		 * Compares the callback with the given callback.
		 * 
		 * @param rhs Right hand side.
		 * @return When they are equal true, otherwise false.
		 */
		bool operator==(const callback_base& rhs) const
		{
			return (this->object == rhs.object &&
			        this->function_pointer == rhs.function_pointer);
		}
	};

}

#endif	/* CALLBACK_BASE_HPP */

