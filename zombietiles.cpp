#include "zombietiles.h"
#include "dungeonconfig.h"
#include "tilemap.h"
#include "utils/logger.h"
#include "utils/randomgenerator.h"
#include <QDebug>

std::list<TileTexture> ZombieTiles::generate_dungeon(const u_int width, const u_int height)
{
    DungeonConfig dungeon_config(width, height);
    Logger::doing("Testando");

    //    TileMap *tileMap = new TileMap(width, height);
    //    tileMap->init();
    //    tileMap-> get_tile({2, 5})->type();
    //    tileMap->print();

    qDebug() << RandomGenerator().random();
    qDebug() << RandomGenerator().random_between(5, 9);
    qDebug() << RandomGenerator().random_between(5, 9);
    qDebug() << RandomGenerator().random();
    qDebug() << RandomGenerator().random();
    Logger::done();
    return {};
}
