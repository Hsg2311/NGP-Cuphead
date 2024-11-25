#ifndef __OBJECT_HPP
#define __OBJECT_HPP

#include "EventHandler.hpp"
#include "Collider.hpp"
#include "Animator.hpp"
#include "Camera.hpp"

#include <string>

struct texInfo {
	std::wstring resKey;
	std::wstring fileName;
	Vec2 sliceSize{ 0.f, 0.f };
	float duration = 0.f;
	UINT frameCount = 0;
	Vec2 offset{ 0.f, 0.f };
};

class Object {
public:
	Object( )
		: objName_{ }
		, objPos_ { }
		, objScale_{ }
		, collider_{ nullptr }
		, animator_{ nullptr }
		, alive_{ true } {}

	Object( const Object& other )
		: objName_{ other.objName_ }
		, objPos_{ other.objPos_ }
		, objScale_{ other.objScale_ }
		, collider_{ nullptr }
		, animator_{ nullptr }
		, alive_{ true } {
		createCollider( );
		getCollider( )->setOffset( other.getCollider( )->getOffset( ) );
		getCollider( )->setScale( other.getCollider( )->getScale( ) );

		createAnimator( );
	}

	Object( Object&& other ) noexcept
		: objName_{ std::move( other.objName_ ) }
		, objPos_{ std::move( other.objPos_ ) }
		, objScale_{ std::move( other.objScale_ ) }
		, collider_{ other.collider_ }
		, animator_{ other.animator_ }
		, alive_{ true } {
		other.collider_ = nullptr;
		other.animator_ = nullptr;
	}

	Object& operator=( const Object& ) = delete;
	Object& operator=( Object&& ) = delete;

	virtual ~Object( ) = 0 { 
		delete collider_;
		delete animator_;
	}

public:
	void setObjName( const std::wstring& objName ) { objName_ = objName; }
	void setObjPos( const Vec2& objPos ) { objPos_ = objPos; }
	void setObjScale( const Vec2& objScale ) { objScale_ = objScale; }

	const std::wstring& getObjName( ) const { return objName_; }
	Vec2 getObjPos( ) const { return objPos_; }
	Vec2 getObjScale( ) const { return objScale_; }

	Collider* getCollider( ) const { return collider_; }
	Animator* getAnimator( ) const { return animator_; }

	bool isAlive( ) const { return alive_; }

public:
	void createCollider( ) { collider_ = new Collider{ }; }
	void createAnimator( ) { animator_ = new Animator{ }; }

	virtual void onCollision( Object* other ) {}
	virtual void onCollisionEntry( Object* other ) {}
	virtual void onCollisionExit( Object* other ) {}

	void createObject( GROUP_TYPE groupType, Object* object ) {
		auto event = Event{
			.eventType = EVENT_TYPE::CREATE_OBJECT,
			.wParam = static_cast<DWORD_PTR>( groupType ),
			.lParam = reinterpret_cast<DWORD_PTR>( object )
		};

		EventHandler::getInst( ).addEvent( event );
	}

	void destroyObject( Object* object ) {
		auto event = Event{
			.eventType = EVENT_TYPE::DESTROY_OBJECT,
			.lParam = reinterpret_cast<DWORD_PTR>( object )
		};

		EventHandler::getInst( ).addEvent( event );
	}

public:
	virtual void update( ) = 0 {}

	virtual void componentUpdate( ) final {
		if ( collider_ ) {
			collider_->update( objPos_ );
		}
		if ( animator_ ) {
			animator_->update( );
		}
	}

	virtual void render( HDC hdc ) = 0 {
		auto renderPos = Camera::getInst( ).getRenderPos( objPos_ );

		Rectangle( hdc
			, static_cast<int>( renderPos.x - objScale_.x / 2.f )
			, static_cast<int>( renderPos.y - objScale_.y / 2.f )
			, static_cast<int>( renderPos.x + objScale_.x / 2.f )
			, static_cast<int>( renderPos.y + objScale_.y / 2.f ) );

		componentRender( hdc );
	}

	virtual void componentRender( HDC hdc ) final {
		if ( collider_ ) {
			collider_->render( hdc );
		}
		if ( animator_ ) {
			animator_->render( hdc, objPos_ );
		}
	}

public:
	virtual Object* clone( ) = 0;

private:
	std::wstring objName_;
	Vec2 objPos_;
	Vec2 objScale_;

	Collider* collider_;
	Animator* animator_;

	bool alive_;
	
	friend class EventHandler;
};

#endif // __OBJECT_HPP