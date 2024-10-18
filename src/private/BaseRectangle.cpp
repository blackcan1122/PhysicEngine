#include "BaseRectangle.h"
#include "iostream"
#include <math.h>
#include <cmath>
#include <algorithm>
#include "rlgl.h"

void BaseRectangle::Tick(float Deltatime)
{
	SetBBox();
	DrawSquare();
	if (IsControllable == true)
	{
		UseControllTransform(Deltatime);
	}
}



void BaseRectangle::SetIsControllable(bool Status)
{
	IsControllable = Status;
}

bool BaseRectangle::GetGravityAffected()
{
	return GravityAffects;
}

void BaseRectangle::SetPosition(Vector2 NewPos)
{
	Position = NewPos;
}

void BaseRectangle::SetUseGravity(bool Status)
{
	GravityAffects = Status;
}

void BaseRectangle::CalculateGravity(float Gravity, float Deltatime)
{
	Velocity.y += Gravity;

	if (this->GetPosition().y > GetScreenHeight() && IsBoundByScreen)
	{
		Vector2 Pos = this->GetPosition();
		Pos.y -= (Pos.y - GetScreenHeight());
		SetPosition(Pos);
		Vector2 Helper = { 0,-1 };
		Velocity = Vector2Reflect(Velocity, Helper);
	}
}

void BaseRectangle::SetIsBoundByScreen(bool Status)
{
	IsBoundByScreen = Status;
}


void BaseRectangle::UseControllTransform(float Deltatime)
{
	// Accelarting
	Accel = 30.f; // Magic Accel Number
	
	if (IsKeyDown(KEY_UP) && AxisRestriction != 'X')
	{
		Velocity.y -= Accel;
	}
	if (IsKeyDown(KEY_DOWN) && AxisRestriction != 'X')
	{
		Velocity.y += Accel;
	}
	if (IsKeyDown(KEY_RIGHT) && AxisRestriction != 'Y')
	{
		Velocity.x += Accel;
	}
	if (IsKeyDown(KEY_LEFT) && AxisRestriction != 'Y')
	{
		Velocity.x -= Accel;
	}

	// Apply Dampening
	Velocity.x *= Dampening;
	Velocity.y *= Dampening;

	// Update position with velocity

	Position.x += Velocity.x * Deltatime;
	Position.y += Velocity.y * Deltatime;

	//Check if velocity is close to zero and set it to zero if so
	if (std::abs(Velocity.x) < 0.02)
	{
		Velocity.x = 0;
	}
	if (std::abs(Velocity.y) < 0.02)
	{
		Velocity.y = 0;
	}

	if (IsBoundByScreen == true)
	{
		if (Position.x < 0 || Position.x > GetScreenWidth())
		{
			Velocity.x = 0;
		}
		else if (Position.y < 0 || Position.y > (GetScreenHeight()-Dimensions.y))
		{
			if (Position.y < 0)
			{
				Position.y = 0;
			}
			else
			{
				Position.y = (GetScreenHeight()-Dimensions.y);
			}
			Velocity.x = 0;
		}
	}
}

void BaseRectangle::DrawSquare()
{
	DrawRectangle(Position.x, Position.y, Dimensions.x, Dimensions.y, FColor);
}

void BaseRectangle::SetDimensions(Vector2 NewDimensions)
{
	Dimensions = NewDimensions;
}

void BaseRectangle::SetBBox()
{
	BBox = { Position.x, Position.y, Dimensions.x, Dimensions.y };
}

Vector2 BaseRectangle::GetDimensions()
{
	return Dimensions;
}

Rectangle BaseRectangle::GetBBox()
{
	return BBox;
}

void BaseRectangle::OnCollision(std::shared_ptr<CollisionEvent> event)
{
	if (event)
	{
		if (event->Rect1 == nullptr && event->Rect2 == nullptr)
		{
			std::cout << "Rects are nullptr" << std::endl;
			return;
		}

		std::shared_ptr<BaseRectangle> Rect1 = std::dynamic_pointer_cast<BaseRectangle>(event->Rect1);
		std::shared_ptr<BaseRectangle> Rect2 = std::dynamic_pointer_cast<BaseRectangle>(event->Rect2);

		// Find intersection rectangle
		Rectangle Intersection = GetCollisionRec(Rect1->GetBBox(), Rect2->GetBBox());
		DrawRectangleLinesEx(Intersection, 5, BLUE);
		// Calculate the collision normal
		Vector2 CollisionNormal;

		if (Intersection.width < Intersection.height) 
		{
			if (Rect1->GetPosition().x < Rect2->GetPosition().x) {
				CollisionNormal = { -1, 0 }; // Left side
			}
			else 
			{
				CollisionNormal = { 1, 0 }; // Right side
			}
		}
		else
		{
			if (Rect1->GetPosition().y < Rect2->GetPosition().y) 
			{
				CollisionNormal = { 0, -1 }; // Top side
			}
			else 
			{
				CollisionNormal = { 0, 1 }; // Bottom side
			}
		}


		Vector2 IntersectionDim;
		// Move the rectangle to the collision point
		IntersectionDim = 
		{ 
			(Intersection.width+2) * (std::abs(Vector2Length(this->Velocity)) / 100),
			(Intersection.height+2) * (std::abs(Vector2Length(this->Velocity)) / 100)
		};

		Vector2 OffsettedPos = (Vector2Add(this->GetPosition(), Vector2Multiply(CollisionNormal, IntersectionDim)));
		this->SetPosition(OffsettedPos);

		// Calculate the reflection vector
		Vector2 NormalizedVel = this->GetNormalizedVelocity();
		float MagnitudeVel = this->GetMagnitudeVelocity();
		Vector2 Reflection = Vector2Reflect(Velocity, CollisionNormal);

		// Update velocity
		this->Velocity = Reflection;
		


		std::cout << "Collision at: " << Intersection.x << ", " << Intersection.y << std::endl;
		std::cout << "New Position: " << Position.x << " , " << Position.y << std::endl;
	}
}

Vector2 BaseRectangle::GetNormalizedVelocity()
{
	Vector2 NormalizedVector = Vector2Normalize(Velocity);
	return NormalizedVector;
}

float BaseRectangle::GetMagnitudeVelocity()
{
	float Magnitude = std::sqrt((Velocity.x * Velocity.x) + (Velocity.y * Velocity.y));
	return Magnitude;
}

Vector2 BaseRectangle::CalculateForwardVector()
{
	Vector2 NormalizedVelocity = GetNormalizedVelocity();
	Vector2 ForwardVector = Vector2Scale(NormalizedVelocity, this->GetMagnitudeVelocity() * 0.25f);

	Vector2 Dim = this->GetDimensions();
	Vector2 OffsettedPos = { GetPosition().x + (Dim.x / 2),GetPosition().y + (Dim.y / 2) };

	ForwardVector = Vector2Add(ForwardVector, OffsettedPos);

	return ForwardVector;
}

void BaseRectangle::RestrictAxis(char Axis)
{
	if (Axis != 'X' && Axis != 'Y')
	{
		std::cerr << "No correct Axis were Defined\n";
		return;
	}
	AxisRestriction = Axis;
	return;
	
}

Vector2 BaseRectangle::GetCenter()
{
	Vector2 Dim = this->GetDimensions();
	Vector2 CenteredVector = { GetPosition().x + (Dim.x / 2),GetPosition().y + (Dim.y / 2) };
	return CenteredVector;
}

Vector2 BaseRectangle::GetVelocity()
{
	return Velocity;
}


