#pragma once
#include <GameObject.h>
#include <primitive_builder.h>
enum class TreeType
{
	birch,
	birch_orange,
	pine
};

class PropMaker
{
public:
	static std::unique_ptr<GameObject> addCrate(float x, float y, ModelLoader& ml, b2World& world);
	static std::unique_ptr<GameObject> addTree(float x, float y, ModelLoader& ml, b2World& world, TreeType type);
	static std::unique_ptr<GameObject> addDirtTile(float x, float y, ModelLoader& ml, b2World& world);
	static std::unique_ptr<GameObject> addDirtBlock(float x, float y, ModelLoader& ml, b2World& world);
	static std::unique_ptr<GameObject> addWater(float x, float y, ModelLoader & ml, b2World& world);
	static std::unique_ptr<GameObject> addPassableWater(float x, float y, ModelLoader& ml, b2World& world);

	static std::unique_ptr<GameObject> addConcreteTile(float x, float y, ModelLoader& ml, b2World& world);
	static std::unique_ptr<GameObject> addTile(float grid_x, float grid_y, ModelLoader& ml, b2World& world, char type);
	static std::unique_ptr<GameObject> addGrass(float x, float y, ModelLoader& ml, b2World& world);
	static std::unique_ptr<GameObject> addBridge(float x, float y, float rotation, ModelLoader& ml, b2World& world);
	static std::unique_ptr<GameObject> addFence(float x, float y, float rotation, ModelLoader& ml, b2World& world);
	static std::unique_ptr<GameObject> addFenceCorner(float x, float y, float rotation, ModelLoader& ml, b2World& world);
	static std::unique_ptr<GameObject> addTent(float x, float y, float rotation, ModelLoader& ml, b2World& world);
	static std::unique_ptr<GameObject> addHanger(float x, float y, float rotation, ModelLoader& ml, b2World& world);

};

