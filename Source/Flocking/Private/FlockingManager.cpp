#include "FlockingManager.h"
#include "Agent.h"

#define AGENT_COUNT 10    

void UFlockingManager::Init(UWorld* world, UStaticMeshComponent* mesh) {
    UE_LOG(LogTemp, Warning, TEXT("MANAGER INIT"));

    World = world;

    float incr = (PI * 2.f) / AGENT_COUNT;
    for (int i = 0; i < AGENT_COUNT; i++) {
        if (World != nullptr) {
            FRotator rotation = FRotator();

            FVector location = FVector();
            location.X = FMath::Sin(incr * i) * 150.f;
            location.Z = FMath::Cos(incr * i) * 150.f + 250.f;

            AAgent* agent = World->SpawnActor<AAgent>(location, rotation);
            agent->Init(mesh, i);
            Agents.Add(agent);
        }
    }

    initialized = true;
}

void UFlockingManager::Flock() {
    FVector v1, v2, v3;
    for (AAgent* agent : Agents) {
        v1 = rule1(agent);
        v2 = rule2(agent);
        v3 = rule3(agent);
        agent->Velocity += v1 + v2 + v3;
        limitVelocity(agent);
    }
}

FVector UFlockingManager::rule1(AAgent* agent) {
    FVector pc;
    for (AAgent* a : Agents) {
        if (a != agent)
            pc += a->GetActorLocation();
    }
    return (pc / (AGENT_COUNT - 1) - agent->GetActorLocation()) / 100;
}

FVector UFlockingManager::rule2(AAgent* agent) {
    FVector c = FVector(0.f);
    for (AAgent* a : Agents) {
        if (a != agent && abs(FVector::Dist(a->GetActorLocation(), agent->GetActorLocation())) < 100)
            c -= a->GetActorLocation() - agent->GetActorLocation();
    }
    return c;
}

FVector UFlockingManager::rule3(AAgent* agent) {
    FVector pv;
    for (AAgent* a : Agents) {
        if (a != agent)
            pv += a->Velocity;
    }
    return ((pv / (AGENT_COUNT - 1)) - agent->Velocity) / 8;
}

void UFlockingManager::limitVelocity(AAgent* agent) {
    float limit = 500.f;
    if (abs((int32)agent->Velocity.Size()) > limit)
        agent->Velocity = (agent->Velocity / abs((int32)agent->Velocity.Size())) * limit;
}