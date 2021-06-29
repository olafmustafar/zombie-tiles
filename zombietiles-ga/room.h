#pragma once

class Room
{
public:
    enum PlacementType {
        T, //Top
        U, //Under
    };

    Room(int x, int y, int width, int height, PlacementType placement_type);

    int getX() const;
    void setX(int value);

    int getY() const;
    void setY(int value);

    int getWidth() const;
    void setWidth(int value);

    int getHeight() const;
    void setHeight(int value);

    PlacementType getPlacement_type() const;
    void setPlacement_type(const PlacementType &value);

private:
    int x;
    int y;
    int width;
    int height;
    PlacementType placement_type;
};
