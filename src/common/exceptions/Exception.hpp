#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-noexcept"
/*
* export-giggle
* Exception.hpp
* Created by Nuno Levezinho on 09/08/2018.
* 
* Copyright (c) 2018 [Nuno Levezinho] All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*/

#ifndef EXPORT_GIGGLE_EXCEPTION_HPP
#define EXPORT_GIGGLE_EXCEPTION_HPP

#include <stdexcept>
#include <string>

namespace giggle::common::exception
{
	/**
	 * @brief This is the base class for all exceptions defined
	 * and used in the common library.
	 */
	class Exception : public std::exception
	{

	public:
		/**
		 * @brief Creates an exception.
		 * @param l_msg The exception message.
		 * @param l_code The exception code.
		 */
		explicit Exception(const std::string& l_msg, int l_code = 0);

		/**
		 * @brief Creates an exception.
		 * @param l_msg The exception message.
		 * @param l_arg The arguments of the message
		 * @param l_code The exception code.
		 */
		Exception(const std::string& l_msg, const std::string& l_arg, int l_code = 0);

		/**
		 * @brief Creates an exception and stores a clone
		 * of the nested exception.
		 * @param l_msg The exception message.
		 * @param l_arg The arguments of the message
		 * @param l_code The exception code.
		 */
		Exception(const std::string& l_msg, const Exception& l_nested, int l_code = 0);

		/**
		 * @brief Copy constructor.
		 * @param l_exc The other exception.
		 */
		Exception(const Exception& l_exc);

		/**
		 * @brief Destroys the exception and deletes the nested exception.
		 */
		~Exception() noexcept;

		/**
		 * @brief Assignment operator.
		 * @param l_exc The other exception.
		 * @return
		 */
		Exception& operator = (const Exception& l_exc);

		/**
		 * @brief Returns a static string describing the exception.
		 */
		virtual const char* Name() const noexcept;

		/**
		 * @brief Returns the name of the exception class.
		 */
		virtual const char* ClassName() const noexcept;

		/**
		 * @brief Returns a static string describing the exception.
		 * Same as name(), but for compatibility with std::exception.
		 */
		virtual const char* what() const noexcept;

		/**
		 * @brief Returns a pointer to the nested exception, or
		 * null if no nested exception exists.
		 */
		const Exception* Nested() const;

		/**
		 * @brief Returns the message text.
		 */
		const std::string& Message() const;

		/**
		 * @brief Returns the exception code if defined.
		 */
		int Code() const;

		/**
		 * @brief Returns a string consisting of the
		 * message name and the message text.
		 */
		std::string DisplayText() const;

		/**
		 * @brief Creates an exact copy of the exception.
		 *
		 * The copy can later be thrown again by
		 * invoking rethrow() on it.
		 * @return
		 */
		virtual Exception* Clone() const;

		/**
		 * @brief (Re)Throws the exception.
		 *
		 * This is useful for temporarily storing a
		 * copy of an exception (see clone()), then
		 * throwing it again.
		 */
		virtual void Rethrow() const;

	protected:
		/**
		 * @brief Standard constructor
		 * @param l_code The exception code
		 */
		explicit Exception(int l_code = 0);

		/**
		 * @brief Sets the message for the exception.
		 * @param l_msg The message
		 */
		void Message(const std::string& l_msg);

		/**
		 * @brief Sets the extended message for the exception.
		 * @param l_arg The arguments
		 */
		void ExtendedMessage(const std::string& l_arg);

		/**
		 * @brief Appends backtrace (if available) to the
		 * message.
		 */
		void AddBacktrace();

	private:
		std::string& msg() const
		{
			if (_msg.find(Name()) == std::string::npos)
			{
				std::string s(Name());
				s.append(": ");
				_msg.insert(0, s);
			}
			return _msg;
		}

		mutable std::string _msg;
		Exception*          _pNested;
		int					_code;

	};

	/**
	 * Macros for quickly declaring and implementing exception classes.
	 * Unfortunately, we cannot use a template here because character
	 * pointers (which we need for specifying the exception name)
	 * are not allowed as template arguments.
	 */

#define COMMON_DECLARE_EXCEPTION_CODE(CLS, BASE, CODE) 								\
	class CLS: public BASE 															\
	{																				\
	public:																			\
		CLS(int l_code = CODE);														\
		CLS(const std::string& l_msg, int l_code = CODE);							\
		CLS(const std::string& l_msg, const std::string& l_arg, int l_code = CODE);	\
		CLS(const std::string& l_msg, const Exception& l_exc, int l_code = CODE);	\
		CLS(const CLS& l_exc);														\
		~CLS() throw();																\
		CLS& operator = (const CLS& l_exc);											\
		const char* Name() const noexcept;											\
		const char* ClassName() const noexcept;										\
		Exception* Clone() const;													\
		void Rethrow() const;														\
	};

#define COMMON_DECLARE_EXCEPTION(CLS, BASE) \
	COMMON_DECLARE_EXCEPTION_CODE(CLS, BASE, 0)

	/**
	 * Standard exception classes
	 */
	COMMON_DECLARE_EXCEPTION(RuntimeException, Exception)
	COMMON_DECLARE_EXCEPTION(OutOfMemoryException, RuntimeException)

} // namespace exception

#endif //EXPORT_GIGGLE_EXCEPTION_HPP

#pragma clang diagnostic pop