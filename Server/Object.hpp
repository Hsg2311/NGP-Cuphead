#ifndef __OBJECT_HPP
#define __OBJECT_HPP

#include "EventHandler.hpp"
#include "Collider.hpp"
#include "IDHandler.hpp"
#include "SendingStorage.hpp"

#include <string>
#include <optional>

class Object {
public:
	Object( )
		: objName_{ }
		, objPos_ { }
		, objScale_{ }
		, collider_{ nullptr }
		, alive_{ true }
		, networkId_( IDHandler::getInst( ).allocID( ) ) {}

	Object( const Object& other )
		: objName_{ other.objName_ }
		, objPos_{ other.objPos_ }
		, objScale_{ other.objScale_ }
		, collider_{ nullptr }
		, alive_{ true }
		, networkId_( IDHandler::getInst( ).allocID( ) ) {
		createCollider( );
		getCollider( )->setOffset( other.getCollider( )->getOffset( ) );
		getCollider( )->setScale( other.getCollider( )->getScale( ) );
	}

	Object( Object&& other ) noexcept
		: objName_{ std::move( other.objName_ ) }
		, objPos_{ std::move( other.objPos_ ) }
		, objScale_{ std::move( other.objScale_ ) }
		, collider_{ std::exchange( other.collider_, nullptr ) }
		, alive_{ std::exchange( other.alive_, false ) }
		, networkId_( std::exchange( other.networkId_, std::nullopt ) ) {
		other.collider_ = nullptr;
	}

	Object& operator=( const Object& ) = delete;
	Object& operator=( Object&& ) = delete;

	virtual ~Object( ) = 0 { 
		delete collider_;

		if ( networkId_ ) {
			SendingStorage::getInst( ).pushPacket( Packet{
				.type = PacketType::DESTROY,
				.ds = {
					.id = *networkId_
				}
			} );
			IDHandler::getInst( ).deallocID( *networkId_ );
		}
	}

public:
	void setObjName( const std::wstring& objName ) { objName_ = objName; }
	void setObjPos( const Vec2& objPos ) { objPos_ = objPos; }
	void setObjScale( const Vec2& objScale ) { objScale_ = objScale; }
	void setID( std::uint16_t id ) { networkId_ = id; }

	const std::wstring& getObjName( ) const { return objName_; }
	Vec2 getObjPos( ) const { return objPos_; }
	Vec2 getObjScale( ) const { return objScale_; }

	Collider* getCollider( ) const { return collider_; }

	void setAlive( bool alive ) { alive_ = alive; }
	bool isAlive( ) const { return alive_; }

	const std::optional<std::uint16_t>& getID( ) const { return networkId_; }

public:
	void createCollider( ) { collider_ = new Collider( ); }

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
	}

public:
	virtual Object* clone( ) = 0;

private:
	std::wstring objName_;
	Vec2 objPos_;
	Vec2 objScale_;

	Collider* collider_;

	bool alive_;

	std::optional<std::uint16_t> networkId_;
	
	friend class EventHandler;
};

#endif // __OBJECT_HPP