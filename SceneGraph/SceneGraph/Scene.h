#pragma once
#include<memory>
#include <map>
#include "SceneNode.h"

// map actor id with its node
typedef std::map<ActorID, shared_ptr<SceneNode> > SceneActorMap;
// Only implemented the MeshNode class for demonstration 
class MeshNode;

// You can implement more node classes, such as list here
//class CameraNode;
//class LightNode;
// ...

class Scene
{
public:
	Scene();
	virtual ~Scene(void);
	void OnRender();
	void OnUpdate(const float dt);
	

	shared_ptr<SceneNode> FindActor(ActorID id);
	void AddChild(ActorID id, shared_ptr<SceneNode> child);
	void RemoveChild(ActorID id);

protected:
	shared_ptr<SceneNode> Root;
	// Implement more scene nodes
	//shared_ptr<CameraNode> camera_node;
	//shared_ptr<LightNode> light_node;
	//...
	
	SceneActorMap ActorMap;

};

