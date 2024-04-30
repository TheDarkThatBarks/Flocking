[Video](https://github.com/TheDarkThatBarks/Flocking/blob/9767e58e1de97f4a9aa515089a56d1fca39cfa24/Flocking%20Video.mkv)

A game that simulates the famous Boids algorithm

Uses the standard 3 rules:
1. Boids try to fly towards the centre of mass of neighbouring boids
2. Boids try to keep a small distance away from other objects (including other boids)
3. Boids try to match velocity with near boids

Also uses a new tweak, limiting the velocity (found in limitVelocity in FlockingManager.cpp)