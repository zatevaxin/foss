#pragma once

#include "ecs/EntityManager.hpp"

#include <glm/glm.hpp>


class CParticleUpdateSystem
{
public:
    CParticleUpdateSystem(ecs::EntityManager& entityManager);

    inline void setViewMatrix(const glm::mat4& view)
    {
        mView = view;
    }

    inline void setProjectionMatrix(const glm::mat4& projection)
    {
        mProjection = projection;
    }

    void update(double& delta);

private:
    glm::mat4 mProjection = glm::mat4(1);
    glm::mat4 mView = glm::mat4(1);

    ecs::EntityManager& mEntityManager;
};
