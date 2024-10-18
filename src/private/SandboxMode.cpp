#include "SandboxMode.h"
#include "EventDispatcher.hpp"
#include "Physic.hpp"
#include "TickAll.h"

SandboxMode::SandboxMode()
{
	SetName("Sandbox");
    MyRectangle = std::make_shared<BaseRectangle>();
    MyRectangle2 = std::make_shared<BaseRectangle>();


        //Dispatcher.AddListener("CollisionEvent", [MyRectangle](std::shared_ptr<Event> event)
        //{
        //    auto Test = std::dynamic_pointer_cast<CollisionEvent>(event);
        //    if (Test)
        //    {
        //        MyRectangle->OnCollision(Test);
        //    }
        //});

    // Initializing Start Position
    Vector2 Pos1 = { 0,0 };
    Vector2 Pos2 = { 200,200 };
    // Init Start Parameter of Objects
    MyRectangle->SetPosition(Pos1);
    MyRectangle->SetUseGravity(false);
    MyRectangle2->SetPosition(Pos2);
    MyRectangle2->SetUseGravity(false);
    MyRectangle->SetIsControllable(true);


    PhysicEngineObj.CollectAllObjectsForGravity();

    EventDispatcher GlobalDispatcher;

}

SandboxMode::~SandboxMode()
{
    RuntimeCircles.clear();
    RuntimeRectangles.clear();
    PhysicEngineObj.CleanUp();
}

void SandboxMode::Update()
{
    ClearBackground(LIGHTGRAY);

    // Start Parameter for the Frame:
    float DeltaTime = GetFrameTime();
    TickAll(DeltaTime);
    DrawText(TextFormat("%f", DeltaTime), 200, 200, 16, BLUE);
    if (IsKeyPressed(KEY_A))
    {
        for (auto& Objects : RuntimeCircles)
        {
            if (helper == false)
            {
                Objects->Debugmode = true;
                std::cout << "DebugMode On" << std::endl;
            }
            else
            {
                Objects->Debugmode = false;
                std::cout << "DebugMode Off" << std::endl;
            }

        }
        if (helper == false)
        {
            helper = true;
        }
        else
        {
            helper = false;
        }
    }

    AmountOfBalls += GetMouseWheelMove();
    DrawText(TextFormat("Amount of Spawned Balls Will be: %d", AmountOfBalls), 300, 200, 16, GREEN);

    // Collision Detection for All Circles
    for (auto& Object1 : RuntimeCircles)
    {
        for (auto& Object2 : RuntimeCircles)
        {
            if (Object1 == Object2) { break; }
            if (CheckCollisionCircles(Object1->GetCenter(), Object1->GetRadius(), Object2->GetCenter(), Object2->GetRadius()))
            {
                Object1->CalculateCollision(Object2);
            }
        }
    }

    // Collision Detection for Rectangle to Circle

    for (const auto& Circle : RuntimeCircles)
    {
        if (CheckCollisionCircleRec(Circle->GetCenter(), Circle->GetRadius(), MyRectangle->GetBBox()))
        {
            Circle->CalculateCollision(MyRectangle);
        }
    }
    if (IsKeyPressed(KEY_TAB))
    {
        for (int i = 0; i < AmountOfBalls; i++)
        {
            RuntimeCircles.push_back(std::make_shared<BaseCircle>());
            RuntimeCircles[RuntimeCircles.size() - 1]->SetIsControllable(false);
            RuntimeCircles[RuntimeCircles.size() - 1]->SetUseGravity(true);
            RuntimeCircles[RuntimeCircles.size() - 1]->SetIsBoundByScreen(true);
            RuntimeCircles[RuntimeCircles.size() - 1]->SetPosition(GetMousePosition());
            PhysicEngineObj.CollectAllObjectsForGravity();
        }
    }
    if (IsKeyPressed(KEY_D))
    {
        for (int i = 0; i < AmountOfBalls; i++)
        {
            if (RuntimeCircles.size() > 1)
            {
                RuntimeCircles.pop_back();
            }
            PhysicEngineObj.CollectAllObjectsForGravity();
        }
    }


    // Check for Collision for CollisionEvent Dispatch and filling in data
    if (CheckCollisionRecs(MyRectangle->GetBBox(), MyRectangle2->GetBBox()))
    {
        std::shared_ptr<CollisionEvent> eventCollision = std::make_shared<CollisionEvent>();
        eventCollision->m_HasCollisionHappend = true;
        eventCollision->CurrentDeltaTime = DeltaTime;
        eventCollision->Rect1 = std::dynamic_pointer_cast<Tickable>(MyRectangle);
        eventCollision->Rect2 = std::dynamic_pointer_cast<Tickable>(MyRectangle2);
        Dispatcher.Dispatch(eventCollision);
    }

    DrawText(TextFormat("There are Currently %d", TickableFactory::GetTickables().size()), 500, 500, 18, RED);

    // Debug Velocity Vector
    Vector2 DebugVelVector[2];
    DebugVelVector[0] = MyRectangle->GetCenter();
    DebugVelVector[1] = MyRectangle->CalculateForwardVector();
    DrawSplineLinear(DebugVelVector, 2, 2, RED);
}

void SandboxMode::SetName(std::string NewName)
{
	Name = NewName;
}

std::string SandboxMode::GetName()
{
	return Name;
}
