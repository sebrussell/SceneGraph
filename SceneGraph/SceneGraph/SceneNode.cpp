#include "SceneNode.h"


SceneNode::SceneNode(string name, ActorID id)
{
	Parent = nullptr;
	ModelScale = Fvector(1.0f, 1.0f, 1.0f);
	IsLeaf = false;
	this->name = name;
	radius = 0.0f;
	this->id = id;
}

SceneNode::~SceneNode()
{
}

// Add the child scene node to the list of children scene nodes 
// and set its parent as this scene node
void SceneNode::AddChild(shared_ptr<SceneNode> s)
{
	Children.push_back(s);
	s->Parent = this;
}

void SceneNode::RemoveChild(ActorID id)
{

	// Tutorial exercise:  Implement remove child ...
	cout<<"Child " <<id<<"been removed !"<<endl;
}

// Update the scene node's world transfermation matrix for this child scene node
// by matrix multiplications. Walk down the graph to update all children ...
// You can implement code to update other perporties of the scene nodes
bool SceneNode::Update(float dt)
{
   // If this node has a parent
   if(Parent)
   {
	   WorldTransformation = Parent->GetWorldTransformation()* LocalTransformation;
	   std::cout<<"Update " << name.data() <<std::endl;	
   }
   else
   {
	   WorldTransformation = LocalTransformation;
	   std::cout<<"Update " << name.data() <<std::endl;	
   }

   // Iterate thought the scene graph to update each child node
   for(auto child : Children)
   {
	   child->Update(dt);

	   if(child->IsLeaf)
	   {
	      child->Draw();
	   }
   }

   return true;
}

 void SceneNode::Draw()
 {
	 // Draw implementation in leaf node
 }

// MeshNode class implementation example
MeshNode::MeshNode(string name , ActorID id/*, shared_ptr<Mesh> mesh */): SceneNode(name, id)
{
	Parent = nullptr;
	ModelScale = Fvector(1.0f, 1.0f, 1.0f);
	IsLeaf = true;
	// this-> mesh =  mesh ;
}

MeshNode::~MeshNode()
{
}

void MeshNode::Draw()
{
	if(IsLeaf /*&& Mesh */)  // You need your own mesh class !
	{
	  /*this->Draw()*/;
	  std::cout<<"Draw "<<name.data()<<std::endl;
	}

}