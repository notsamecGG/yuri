#pragma once

#include <cmath>
#include <list>
#include <vector>


struct Vector2D
{
    int x, y;

    Vector2D() : x(0), y(0) { }
    Vector2D(const int &a_x, const int &a_y) : x(a_x), y(a_y) { }

    Vector2D operator+(const Vector2D &other) const
    {
        int new_x = x + other.x; 
        int new_y = y + other.y;

        return Vector2D(new_x, new_y);
    }

    Vector2D operator-(const Vector2D &other) const
    {
        int new_x = x - other.x; 
        int new_y = y - other.y;

        return Vector2D(new_x, new_y);
    }

    Vector2D operator+=(const Vector2D &other)
    {
        x += other.x; y += other.y;

        return *this;
    }

    Vector2D operator-=(const Vector2D &other)
    {
        x -= other.x; y -= other.y;

        return *this;
    }

    int distance(const Vector2D& other) const
    {
        int new_x = std::abs(x - other.x);
        int new_y = std::abs(y - other.y);

        return std::sqrt(std::pow(new_x, 2) + std::pow(new_y, 2));
    }

    int value() const
    {
        return x * y;
    }
};

struct GameObject 
{
    Vector2D position;
    Vector2D size;
    Vector2D center;

    unsigned int radius;

    GameObject(const int &x, const int &y, const unsigned int &width, const unsigned int &height)
        : position(x, y), size(width, height) { radius = std::max(width, height); _updateCenter(); } 
    GameObject(const unsigned int &width, const unsigned int &height)
        : position(), size(width, height) { radius = std::max(width, height); _updateCenter(); }
    GameObject() 
        : position(), size(1, 1) { radius = 1; _updateCenter(); } 

    Vector2D getCenter()
    {
        _updateCenter();
        return center;
    }

    bool cheapCollision(const GameObject &other) const
    {
        int distance = center.distance(other.center);

        // if (distance < radius + other.radius)
        //     std::cout << "collision" << std::endl;

        return distance < radius /*+ other.radius*/;
    }

    /**
     * @brief Not completely done, so don't use it
     * 
     * @param other game object
     */
    bool collision(const GameObject& other, const Vector2D& speed) const
    {
        if (cheapCollision(other))
        {
            // check if the object are colliding vertically or horizontally
        }
        int x_check = position.x + !std::signbit(speed.x) * size.x;
        int y_check = position.y + !std::signbit(speed.y) * size.y;

        if (x_check >= other.position.x && x_check <= other.position.x + other.size.x)
            if (y_check >= other.position.y && y_check <= other.position.y + other.size.y)
                return true;

        return false;
    }

    void move(const int& x, const int& y)
    {
        position += Vector2D(x, y);

        _updateCenter();
    }

    void moveTo(const int& x, const int& y)
    {
        position.x = x; position.y = y;
        _updateCenter();
    }

    void toArray(std::vector<Vector2D> *out)
    {
        out->reserve(size.value());

        for (int y = 0; y < size.y; y++)
        {
            for (int x = 0; x < size.x; x++)
                out->push_back(Vector2D(position.x + x, position.y + y));
        }
    }

private:
    void _updateCenter()
    {
        center.x = position.x + std::floor(size.x/2);
        center.y = position.y + std::floor(size.y/2);
    }

    // TODO: move this function to more appropriate spot
    static void mulString(std::string* str, const int& count)
    {
        std::string orig = *str;

        if (count == 0)
        {
            *str = std::string("");
            return;
        }

        for (int i = 0; i < count - 1; i++)
            *str += orig;
    }
};