#ifndef MY_EXCEPTION_HPP
#define MY_EXCEPTION_HPP

#include <string>
#include <exception>

class MyException : public std::exception {
public:
	MyException( int lineNum, const char* fileStr ) noexcept;
	const char* what( ) const noexcept override;
	virtual const char* type( ) const noexcept {
		return "MyException";
	}
	int lineNum( ) const noexcept {
		return lineNum_;
	}
	const std::string& fileStr( ) const noexcept {
		return fileStr_;
	}
	std::string metaStr( ) const noexcept;

private:
	int lineNum_;
	std::string fileStr_;

protected:
	mutable std::string whatBuffer_;
};

#endif // MY_EXCEPTION_HPP