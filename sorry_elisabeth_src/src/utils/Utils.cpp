#include "utils.h"
#include "../game/Room.h"

using namespace godot;

bool Utils::isInsideArea(const godot::Vector2 eltPosition, const godot::Vector2 objectPosition, const godot::Vector2 objectSize)
{
    return isInsideObjectX(eltPosition.x, objectPosition.x, objectSize.x) && isInsideObjectY(eltPosition.y, objectPosition.y, objectSize.y);
}

bool Utils::isInsideObjectX(const real_t eltPositionX, const real_t objectPositionX, const real_t objectSizeX)
{
    return eltPositionX >= objectPositionX && eltPositionX <= objectPositionX + objectSizeX;
}

bool Utils::isInsideObjectY(const real_t eltPositionY, const real_t objectPositionY, const real_t objectSizeY)
{
    return eltPositionY >= objectPositionY && eltPositionY <= objectPositionY + objectSizeY;
}

bool Utils::isInsideRoom(const godot::Vector2 eltPosition)
{
    return (isInsideRoomX(eltPosition.x) && isInsideRoomY(eltPosition.y));
}

bool Utils::isInsideRoomX(const real_t eltXPosition)
{
    return isInsideObjectX(eltXPosition, Room::ROOM_WIDTH_BEGINNING, (Room::ROOM_WIDTH_ENDING + (-Room::ROOM_WIDTH_BEGINNING)));
}

bool Utils::isInsideRoomY(const real_t eltYPosition)
{
    return isInsideObjectX(eltYPosition, Room::ROOM_HEIGHT_BEGINNING, (Room::ROOM_WIDTH_ENDING - Room::ROOM_HEIGHT_BEGINNING));
}

godot::Vector2 Utils::getCenteredPosition(const godot::Vector2 objectSize)
{
    return Vector2(real_t(int(SCREEN_WIDTH / 2 - objectSize.x / 2)), real_t(int(SCREEN_HEIGHT / 2 - objectSize.y / 2)));
}