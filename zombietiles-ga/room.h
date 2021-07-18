#pragma once

class Room
{
public:
    enum PlacementType : int {
        T, //Top
        U, //Under
    };

    Room(int x, int y, int width, int height, PlacementType placement_type);

    int get_x() const;
    void set_x(int value);

    int get_y() const;
    void set_y(int value);

    int get_width() const;
    void set_width(int value);

    int get_height() const;
    void set_height(int value);

    PlacementType get_placement_type() const;
    void set_placement_type(const PlacementType &value);

private:
    int x;
    int y;
    int width;
    int height;
    PlacementType placement_type;
};
