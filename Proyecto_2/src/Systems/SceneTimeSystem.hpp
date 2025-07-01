#ifndef SCENETIMESYSTEM_HPP
#define SCENETIMESYSTEM_HPP

#include <SDL2/SDL.h>
#include <iostream>


/**
 * @class SceneTimeSystem
 * @brief Manages scene timing including pause, resume, delta time, and total elapsed time.
 * 
 * Keeps track of elapsed time since scene start, accounting for paused durations.
 */
class SceneTimeSystem : public System {
private:
    int sceneStartTime;///< Time when the scene started (in milliseconds).
    int currentTime; ///< Current time (in milliseconds).
    int deltaTime;///< Time difference between last two updates (in milliseconds).
    bool paused;///< Flag indicating if the timer is paused.
    int pauseStartTime; ///< Time when the pause started. 
    int totalPausedTime;///< Total time spent paused. 
public:
    /**
     * @brief Constructs the SceneTimeSystem and initializes timing variables.
     */
    SceneTimeSystem() {
        sceneStartTime = SDL_GetTicks();
        currentTime = sceneStartTime;
        deltaTime = 0;
        paused = false;
        pauseStartTime = 0;
        totalPausedTime = 0;
    }
    /**
     * @brief Pauses the scene timer.
     * 
     * Records the time when pause starts.
     */
    void Pause() {
        if (!paused) {
            paused = true;
            pauseStartTime = SDL_GetTicks();
        }
    }
    /**
     * @brief Resumes the scene timer after being paused.
     * 
     * Updates total paused time and current time accordingly.
     */
    void Resume() {
        if (paused) {
            paused = false;
            int pauseDuration = SDL_GetTicks() - pauseStartTime;
            totalPausedTime += pauseDuration;
            currentTime = SDL_GetTicks();
        }
    }
    /**
     * @brief Updates the delta time and current time if not paused.
     * 
     * If paused, delta time is set to zero.
     */
    void Update() {
        if (paused) {
            deltaTime = 0;
            return;
        }

        int now = SDL_GetTicks();
        deltaTime = now - currentTime;
        currentTime = now;
    }
    /**
     * @brief Gets the total elapsed scene time, excluding paused durations.
     * @return The elapsed time since scene start in milliseconds.
     */
    int GetSceneTime() const {
        return (currentTime - sceneStartTime - totalPausedTime);
    }
    /**
     * @brief Gets the delta time between last two updates.
     * @return The delta time in milliseconds.
     */
    int GetDeltaTime() const {
        return deltaTime;
    }

    /**
     * @brief Resets the timer and all related variables.
     */
    void Reset() {
        sceneStartTime = SDL_GetTicks();
        currentTime = sceneStartTime;
        deltaTime = 0;
        paused = false;
        pauseStartTime = 0;
        totalPausedTime = 0;
    }
};

#endif
