#define _USE_MATH_DEFINES
#include "CParticleEmitter.hpp"
#include "app/auxiliary/glm.hpp"

#include <glm/gtx/rotate_vector.hpp>

using glm::vec3;

CParticle::CParticle(const vec3& position, const vec3& velocity, float lifetime)
    : mPosition(position)
    , mVelocity(velocity)
    , mLifetime(lifetime)
    , mLifetimeInitial(lifetime)
    , mAlphaValue(0.f)
{
}

void CParticle::advance(float deltaSeconds, const glm::vec3& acceleration,
                        const glm::mat4& transform)
{
    float fp = (mLifetime / mLifetimeInitial);
    float fp10 = 0.1;
    float fp90 = 0.9;

    if (fp <= fp10)
    {
        mAlphaValue = glm::mix(0.f, 1.f, fp * 10);
    }
    else if (fp >= fp90)
    {
        mAlphaValue = glm::mix(1.f, 0.f, (fp - 0.9f) * 10);
    }
    else
    {
        mAlphaValue = 1.f;
    }


    mLifetime -= deltaSeconds;
    mVelocity += acceleration * deltaSeconds;
    mPosition += mVelocity * deltaSeconds;

    mDistanceFromCamera = glm::vec3(transform * glm::vec4(mPosition, 1.0)).z;
}

glm::vec3 CParticle::getPosition() const
{
    return mPosition;
}


float CParticle::getAlphaValue() const
{
    return mAlphaValue;
}


float CParticle::getDistanceFromCamera() const
{
    return mDistanceFromCamera;
}


bool CParticle::isAlive() const
{
    return (mLifetime > std::numeric_limits<float>::epsilon());
}

CParticleEmitter::CParticleEmitter()
{
    std::random_device rd;
    mRandom.seed(rd());
}

void CParticleEmitter::advance(float dt)
{
    mElapsedSeconds += dt;
}

bool CParticleEmitter::isEmitReady() const
{
    return mElapsedSeconds > mNextEmitTime;
}

CParticle CParticleEmitter::emit()
{
    mNextEmitTime += mEmitIntervalRange(mRandom);

    const vec3 direction = MakeRandomDirection();
    const vec3 position = mPosition + direction * mDistanceRange(mRandom);
    const vec3 velocity = direction * mSpeedRange(mRandom);
    const float lifetime = mLifetimeRange(mRandom);

    return CParticle(position, velocity, lifetime);
}

void CParticleEmitter::setPosition(const glm::vec3& value)
{
    mPosition = value;
}

glm::vec3 CParticleEmitter::getPosition() const
{
    return mPosition;
}

void CParticleEmitter::setDistanceRange(float minValue, float maxValue)
{
    mDistanceRange.param(linear_random_float::param_type(minValue, maxValue));
}

glm::vec2 CParticleEmitter::getDistanceRange() const
{
    return glm::vec2(mDistanceRange.min(), mDistanceRange.max());
}

void CParticleEmitter::setDirection(const glm::vec3& value)
{
    mDirection = glm::normalize(value);
}

glm::vec3 CParticleEmitter::getDirection() const
{
    return mDirection;
}

void CParticleEmitter::setMaxDeviationAngle(float value)
{
    mDeviationAngleRange.param(linear_random_float::param_type(0.f, value));
}

float CParticleEmitter::getMaxDeviationAngle() const
{
    return mDeviationAngleRange.max();
}

void CParticleEmitter::setLifetimeRange(float minValue, float maxValue)
{
    mLifetimeRange.param(linear_random_float::param_type(minValue, maxValue));
}

glm::vec2 CParticleEmitter::getLifetimeRange() const
{
    return glm::vec2(mLifetimeRange.min(), mLifetimeRange.max());
}

void CParticleEmitter::setEmitIntervalRange(float minValue, float maxValue)
{
    mEmitIntervalRange.param(linear_random_float::param_type(minValue, maxValue));
}

glm::vec2 CParticleEmitter::getEmitIntervalRange() const
{
    return glm::vec2(mEmitIntervalRange.min(), mEmitIntervalRange.max());
}

void CParticleEmitter::setSpeedRange(float minValue, float maxValue)
{
    mSpeedRange.param(linear_random_float::param_type(minValue, maxValue));
}

glm::vec2 CParticleEmitter::getSpeedRange() const
{
    return glm::vec2(mSpeedRange.min(), mSpeedRange.max());
}


glm::vec3 CParticleEmitter::MakeRandomDirection()
{
    vec3 dir = mDirection;

    // This vector will be orthogonal to the dir vector.
    vec3 normal = glm::normalize(vec3(dir.y + dir.z, -dir.x, -dir.x));

    // Rotate normal by an arbitrary angle (in the range -M_PI..M_PI)
    // around the dir vector to get a random axis of rotation.
    linear_random_float distribution(float(-M_PI), float(M_PI));
    normal = glm::rotate(normal, distribution(mRandom), dir);

    // Rotate dir around rotated normal (still orthogonal)
    // by a random angle limited by the maximum deflection angle.
    const float deviationAngle = mDeviationAngleRange(mRandom);
    dir = glm::rotate(dir, deviationAngle, normal);

    return dir;
}
