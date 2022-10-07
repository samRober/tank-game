#include "PropMaker.h"


 std::unique_ptr<GameObject> PropMaker::addCrate(float x, float y, ModelLoader& ml, b2World& world)
{
	auto crate = std::make_unique<GameObject>(x, y, world, ObjectType::prop);
	crate->set_mesh(ml.loadMeshFromFile("crate.scn"));
	//set up body
	auto crate_body = crate->get_body();

	crate_body->SetAngularDamping(2);
	crate_body->SetLinearDamping(2);

	b2PolygonShape crate_shape;
	crate_shape.SetAsBox(1.0f, 1.0f);


	b2FixtureDef crate_fixture_def;
	crate_fixture_def.shape = &crate_shape;
	crate_fixture_def.density = 1.0f;
	crate_fixture_def.friction = 1.0f;
	crate_fixture_def.restitution = 0.5f;
	crate_fixture_def.filter.categoryBits = static_cast<int>(CollisionLayers::ground) | static_cast<int>(CollisionLayers::air);
	crate_fixture_def.filter.maskBits = static_cast<int>(CollisionLayers::ground) | static_cast<int>(CollisionLayers::air);
	crate_body->CreateFixture(&crate_fixture_def);

	return crate;
}

 std::unique_ptr<GameObject> PropMaker::addTree(float x, float y, ModelLoader& ml, b2World& world, TreeType type)
{
	auto tree = std::make_unique<GameObject>(x, y, world, ObjectType::scenery);

	switch (type)//different models based on type provided
	{
	case TreeType::birch:
		tree->set_mesh(ml.loadMeshFromFile("tree.scn"));
		break;
	case TreeType::birch_orange:
		tree->set_mesh(ml.loadMeshFromFile("birch_tree_orange.scn"));
		break;
	case TreeType::pine:
		tree->set_mesh(ml.loadMeshFromFile("pine_tree.scn"));
		break;
	default:
		tree->set_mesh(ml.loadMeshFromFile("tree.scn"));
		break;
	}
	//set up body
	auto tree_body = tree->get_body();

	tree_body->SetType(b2BodyType::b2_staticBody);

	b2CircleShape tree_shape;
	tree_shape.m_radius = 0.75f;


	b2FixtureDef tree_fixture_def;
	tree_fixture_def.shape = &tree_shape;
	tree_fixture_def.density = 1.0f;
	tree_fixture_def.friction = 1.0f;
	tree_fixture_def.restitution = 0.5f;
	tree_fixture_def.filter.categoryBits = static_cast<int>(CollisionLayers::ground) | static_cast<int>(CollisionLayers::air);
	tree_fixture_def.filter.maskBits = static_cast<int>(CollisionLayers::ground) | static_cast<int>(CollisionLayers::air);
	tree_body->CreateFixture(&tree_fixture_def);

	return tree;
}

 std::unique_ptr<GameObject> PropMaker::addDirtTile(float x, float y, ModelLoader& ml, b2World& world)
 {
	 //a brown square
	 auto tile = std::make_unique<GameObject>(x, y, world, ObjectType::scenery);
	 tile->set_mesh(ml.loadMeshFromFile("dirt_floor.scn"));
	 tile->modelOffset_.set_y(-0.05);
	 auto tile_body = tile->get_body();

	 tile_body->SetType(b2BodyType::b2_staticBody);

	 return tile;
 }

 std::unique_ptr<GameObject> PropMaker::addDirtBlock(float x, float y, ModelLoader& ml, b2World& world)
 {
	 //a 1x1 cube withe grass on top
	 auto block = std::make_unique<GameObject>(x, y, world, ObjectType::scenery);
	 
	 block->set_mesh(ml.loadMeshFromFile("dirt_block.scn"));
	 auto block_body = block->get_body();
	 //set up body
	 block_body->SetType(b2BodyType::b2_staticBody);


	 b2PolygonShape block_shape;
	 block_shape.SetAsBox(2.1f, 2.1f);


	 b2FixtureDef block_fixture_def;
	 block_fixture_def.shape = &block_shape;
	 block_fixture_def.density = 1.0f;
	 block_fixture_def.friction = 1.0f;
	 block_fixture_def.restitution = 0.5f;
	 block_fixture_def.filter.categoryBits = static_cast<int>(CollisionLayers::ground) | static_cast<int>(CollisionLayers::air);
	 block_fixture_def.filter.maskBits = static_cast<int>(CollisionLayers::ground) | static_cast<int>(CollisionLayers::air);
	 block_body->CreateFixture(&block_fixture_def);
	 return block;
 }

 std::unique_ptr<GameObject> PropMaker::addWater(float x, float y, ModelLoader & ml, b2World& world)
 {
	 auto water = std::make_unique<GameObject>(x, y, world, ObjectType::scenery);
	 water->set_mesh(ml.loadMeshFromFile("water.scn"));

	 auto water_body = water->get_body();
	 water->modelOffset_ = gef::Vector4(0, -0.2f, 0);
	 water_body->SetType(b2BodyType::b2_staticBody);


	 b2PolygonShape water_shape;
	 water_shape.SetAsBox(2.1f, 2.1f);


	 b2FixtureDef water_fixture_def;
	 water_fixture_def.shape = &water_shape;
	 water_fixture_def.density = 1.0f;
	 water_fixture_def.friction = 1.0f;
	 water_fixture_def.restitution = 0.5f;
	 water_fixture_def.filter.categoryBits = static_cast<int>(CollisionLayers::ground);
	 water_fixture_def.filter.maskBits = static_cast<int>(CollisionLayers::ground);
	 water_body->CreateFixture(&water_fixture_def);
	 return water;
 }

 std::unique_ptr<GameObject> PropMaker::addPassableWater(float x, float y, ModelLoader& ml, b2World& world)
 {
	 //water without a body for putting under bridges
	 auto water = std::make_unique<GameObject>(x, y, world, ObjectType::scenery);
	 water->set_mesh(ml.loadMeshFromFile("water.scn"));

	 auto water_body = water->get_body();
	 water->modelOffset_ = gef::Vector4(0, -0.2f, 0);
	 water_body->SetType(b2BodyType::b2_staticBody);
	 return water;

 }

 std::unique_ptr<GameObject> PropMaker::addConcreteTile(float x, float y, ModelLoader& ml, b2World& world)
 {
	 //for military bases
	 auto tile = std::make_unique<GameObject>(x, y, world, ObjectType::scenery);
	 tile->set_mesh(ml.loadMeshFromFile("concrete_tile.scn"));
	 tile->modelOffset_.set_y(-0.05);
	 auto tile_body = tile->get_body();

	 tile_body->SetType(b2BodyType::b2_staticBody);

	 return tile;
 }

 std::unique_ptr<GameObject> PropMaker::addTile(float x, float y, ModelLoader& ml, b2World& world, char type)
 {
	 std::unique_ptr<GameObject> out;
	 //for reading from a file
	 // maybe an enum would be better and reading the char should be done in the section that is reading the file

	 switch (type)
	 {
	 case 'g':
		 out = addDirtBlock(x, y, ml, world);
		 break;
	 case 'c':
		 out = addConcreteTile(x, y, ml, world);
		 break;
	 case 'w':
		 out = addWater(x, y, ml, world);
		 break;
	 case 'd':
		 out = addDirtTile(x, y, ml, world);
		 break;
	 case 'b':
		 out = addPassableWater(x, y, ml, world);
		 break;
	 default:
		 break;
	 }
	 return out;
 }

 std::unique_ptr<GameObject> PropMaker::addGrass(float x, float y, ModelLoader& ml, b2World& world)
 {
	 auto grass = std::make_unique<GameObject>(x, y, world, ObjectType::scenery);
	 grass->set_mesh(ml.loadMeshFromFile("grass.scn"));
	 grass->modelOffset_.set_y(-0.05);
	 auto grass_body = grass->get_body();

	 grass_body->SetType(b2BodyType::b2_staticBody);

	 return grass;
 }

 std::unique_ptr<GameObject> PropMaker::addBridge(float x, float y, float rotation, ModelLoader& ml, b2World& world)
 {
	 auto bridge = std::make_unique<GameObject>(x, y, world, ObjectType::prop);
	 bridge->set_mesh(ml.loadMeshFromFile("bridge.scn"));
	 auto bridge_body = bridge->get_body();
	 bridge_body->SetTransform(b2Vec2(x, y), rotation);
	 bridge_body->SetType(b2BodyType::b2_staticBody);
	 bridge->modelOffset_ = gef::Vector4(0, -0.1f, 0);
	 return bridge;
 }

 std::unique_ptr<GameObject> PropMaker::addFence(float x, float y, float rotation, ModelLoader& ml, b2World& world)
 {
	 auto fence = std::make_unique<GameObject>(x, y, world, ObjectType::scenery);
	 fence->set_mesh(ml.loadMeshFromFile("fence.scn"));
	 auto fence_body = fence->get_body();
	 //set up body
	 fence_body->SetTransform(b2Vec2(x, y), rotation);
	 
	 b2PolygonShape shape;
	 shape.SetAsBox(1.35f, 0.15f);

	 b2FixtureDef fixtureDef;
	 fixtureDef.shape = &shape;
	 fixtureDef.density = 1.0f;
	 fixtureDef.friction = 1.0f;
	 fixtureDef.restitution = 0.5f;
	 fixtureDef.filter.categoryBits = static_cast<int>(CollisionLayers::ground) | static_cast<int>(CollisionLayers::air);
	 fixtureDef.filter.maskBits = static_cast<int>(CollisionLayers::ground) | static_cast<int>(CollisionLayers::air);
	 fence_body->CreateFixture(&fixtureDef);
	 fence_body->SetType(b2BodyType::b2_staticBody);


	 return fence;
 }

 std::unique_ptr<GameObject> PropMaker::addFenceCorner(float x, float y, float rotation, ModelLoader& ml, b2World& world)
 {
	 auto fence = std::make_unique<GameObject>(x, y, world, ObjectType::scenery);
	 fence->set_mesh(ml.loadMeshFromFile("fence_corner.scn"));
	 auto fence_body = fence->get_body();
	 fence_body->SetTransform(b2Vec2(x, y), rotation);
	 //set up body
	 b2PolygonShape shape;
	 shape.SetAsBox(0.75f, 0.75f);

	 b2FixtureDef fixtureDef;
	 fixtureDef.shape = &shape;
	 fixtureDef.density = 1.0f;
	 fixtureDef.friction = 1.0f;
	 fixtureDef.restitution = 0.5f;
	 fixtureDef.filter.categoryBits = static_cast<int>(CollisionLayers::ground) | static_cast<int>(CollisionLayers::air);
	 fixtureDef.filter.maskBits = static_cast<int>(CollisionLayers::ground) | static_cast<int>(CollisionLayers::air);
	 fence_body->CreateFixture(&fixtureDef);
	 fence_body->SetType(b2BodyType::b2_staticBody);


	 return fence;
 }

 std::unique_ptr<GameObject> PropMaker::addTent(float x, float y, float rotation, ModelLoader& ml, b2World& world)
 {
	 auto tent = std::make_unique<GameObject>(x, y, world, ObjectType::scenery);
	 tent->set_mesh(ml.loadMeshFromFile("tent.scn"));
	 auto tent_body = tent->get_body();
	 tent_body->SetTransform(b2Vec2(x, y), rotation);

	 b2PolygonShape shape;
	 shape.SetAsBox(1.95f, 2.1f);

	 b2FixtureDef fixtureDef;
	 fixtureDef.shape = &shape;
	 fixtureDef.density = 1.0f;
	 fixtureDef.friction = 1.0f;
	 fixtureDef.restitution = 0.5f;
	 fixtureDef.filter.categoryBits = static_cast<int>(CollisionLayers::ground) | static_cast<int>(CollisionLayers::air);
	 fixtureDef.filter.maskBits = static_cast<int>(CollisionLayers::ground) | static_cast<int>(CollisionLayers::air);
	 tent_body->CreateFixture(&fixtureDef);
	 tent_body->SetType(b2BodyType::b2_staticBody);


	 return tent;
 }

 std::unique_ptr<GameObject> PropMaker::addHanger(float x, float y, float rotation, ModelLoader& ml, b2World& world)
 {
	 auto hanger = std::make_unique<GameObject>(x, y, world, ObjectType::scenery);
	 hanger->set_mesh(ml.loadMeshFromFile("hanger.scn"));
	 auto hanger_body = hanger->get_body();
	 hanger_body->SetTransform(b2Vec2(x, y), rotation);

	 b2PolygonShape shape;
	 shape.SetAsBox(8.f, 8.2f);

	 b2FixtureDef fixtureDef;
	 fixtureDef.shape = &shape;
	 fixtureDef.density = 1.0f;
	 fixtureDef.friction = 1.0f;
	 fixtureDef.restitution = 0.5f;
	 fixtureDef.filter.categoryBits = static_cast<int>(CollisionLayers::ground) | static_cast<int>(CollisionLayers::air);
	 fixtureDef.filter.maskBits = static_cast<int>(CollisionLayers::ground) | static_cast<int>(CollisionLayers::air);
	 hanger_body->CreateFixture(&fixtureDef);
	 hanger_body->SetType(b2BodyType::b2_staticBody);


	 return hanger;
 }
