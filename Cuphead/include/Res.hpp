#ifndef __RESOURCE_HPP
#define __RESOURCE_HPP

#include <string>

class Res {
public:
	Res( ) : resKey_{ }, relativePath_{ } {}
	virtual ~Res( ) = 0 {}

public:
	void setResKey( const std::wstring& resKey ) { resKey_ = resKey; }
	void setRelativePath( const std::wstring& relativePath ) { relativePath_ = relativePath; }

	const std::wstring& getResKey( ) const { return resKey_; }
	const std::wstring& getRelativePath( ) const { return relativePath_; }

private:
	std::wstring resKey_;			// 리소스 키
	std::wstring relativePath_;		// 리소스 상대 경로
};

#endif // __RESOURCE_HPP