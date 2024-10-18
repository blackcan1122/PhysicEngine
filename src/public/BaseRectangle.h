#pragma once
#include "Core.h"
#include "CollisionEvent.hpp"
#include "GravityEvent.hpp"
#include "TickableFactory.h"

class BaseRectangle : public Tickable
{
public:
	BaseRectangle()
	{
		TickableFactory::Register(this);	
    }
	~BaseRectangle() override
	{
		TickableFactory::Unregister(this);
		std::cout << "BaseRectangle Was Deleted" << std::endl;
	}

public:
	/*
	* *****************************************
	* Parent Methods and Variables:
	* 
	* METHODS:
	* 
	* virtual void SetPosition(Vector2 NewPos);
	* virtual void SetColor(Color NewColor);
	* virtual void SetIsControllable(bool Status) = 0;
	* virtual void SetUseGravity(bool Status);
	* virtual void SetIsBoundByScreen(bool Status);
	* 
	* virtual Vector2 GetPosition();
	* virtual Color GetColor();
	* 
	* MEMBERS:
	* 
	*     
	* bool IsBoundByScreen;
    * bool GravityAffects;
    * Vector2 Position;
    * Color FColor;
    * bool IsControllable;
	* *****************************************
	*/

	/*
	* ****************************
	* Overriding Virtual Functions
	* ****************************
	*/

	// Tick Function From Tickable Class
	void Tick(float Deltatime) override;

	void SetIsControllable(bool Status) override;
	bool GetGravityAffected() override;
	void SetPosition(Vector2 NewPos) override;
	void SetUseGravity(bool Status) override;
	void CalculateGravity(float Gravity, float Deltatime) override;
	void SetIsBoundByScreen(bool Status) override;

	/*
	* *******************************
	* BaseRectangle Classes Specifics
	* *******************************
	*/
	
	void UseControllTransform(float Deltatime);
	void DrawSquare();
	Vector2 CalculateForwardVector();
	void RestrictAxis(char Axis);

	// Setter Functions specific for Rectangles
	void SetDimensions(Vector2 NewDimensions);
	void SetBBox();

	// Getter Functions Specific for Rectangles
	Vector2 GetDimensions();
	Vector2 GetNormalizedVelocity();
	Vector2 GetCenter();
	Vector2 GetVelocity();
	Rectangle GetBBox();
	float GetMagnitudeVelocity();
	bool IsBoundByScreen;

	// Collision Function Event
	void OnCollision(std::shared_ptr<CollisionEvent> event);
	





private:

	bool GravityAffects;
	Vector2 Dimensions = { 100,100 };
	Vector2 Velocity = { 0,0 };
	float Accel = 0;
	float Dampening = 0.97;
	Rectangle BBox;
	char AxisRestriction;

};

