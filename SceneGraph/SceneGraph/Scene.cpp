#include "Scene.h"


Scene::Scene()
{
	Root = make_shared<SceneNode>("Root", 1);

	// ...
}


Scene::~Scene(void)
{
}

void Scene::OnRender()
{
  // Do somthing here
  // ...
}

void Scene::OnUpdate(const float dt)
{
	if(!Root)  
	{
		cout<<" Nothing to update !"<<endl;
	}

	Root->Update(dt);
}

void Scene::AddChild(ActorID id, shared_ptr<SceneNode> child)
{
	if(id)
	{
		ActorMap[id] = child;
	}

	// add light to this node ...
	
	// add child scene node
	Root->AddChild(child);

}

void Scene::RemoveChild(ActorID id)
{

	shared_ptr<SceneNode> child = FindActor(id);
	// remove light... remove other associated node
	//...
	// remove the child node
	ActorMap.erase(id);
	Root->RemoveChild(id);

}
shared_ptr<SceneNode> Scene::FindActor(ActorID id)
{
	SceneActorMap::iterator it = ActorMap.find(id);
	if(it == ActorMap.end())
	{
		return shared_ptr<SceneNode>();

	}

	return (*it).second;
}

