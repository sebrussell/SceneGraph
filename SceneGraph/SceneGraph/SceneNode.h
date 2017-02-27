//
// This is a teaching demonstration program to show how to build a
// very basic scene graph. There are many different approaches and
// some are more comprehensive offering a lot of functions for Scene Management. 
// Feel free to use my math library and this program for your project.
// You need your own mesh class to be integrated to your OpenGL render to draw objects.
// Wen Tang 
//

#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "../Math3D/math3d.h"

// In addition to common headers, you also need to include your own vector3D.h, Vector4D.h, Matrix4x4.h

using namespace std;
typedef unsigned int ActorID;

class SceneNode
{
public:
	SceneNode(string name, ActorID id);
	~SceneNode();

	void SetTransformation( FSmatrix4  &localMatrix) { LocalTransformation = localMatrix;}
    const FSmatrix4& GetTransform() const {return LocalTransformation;}
	FSmatrix4 GetWorldTransformation() const {return WorldTransformation;}
   
	void SetModelScale(Fvector s) { ModelScale = s;}
	void SetRadius(float r) {radius = r;}
	Fvector GetModelScale() const { return ModelScale;}
	string GetNodeName() const {return name;}
	unsigned int GetNodeID() const {return id;}
	float Radius() {return radius;}  // useful for the first pass test for collision detection etc.

	virtual void AddChild(shared_ptr<SceneNode> s);
	virtual void RemoveChild(ActorID id);
	virtual bool Update(float dt);
	virtual void Draw(); // implement your own draw function
	std::vector<shared_ptr<SceneNode>>::const_iterator GetChildInteratorStart() { return Children.begin();}
	std::vector<shared_ptr<SceneNode>>::const_iterator GetChildInteratorEnd() { return Children.end();}


protected:
	SceneNode* Parent;
	FSmatrix4  WorldTransformation;
	FSmatrix4  LocalTransformation;
	Fvector    ModelScale;
	std::vector<shared_ptr<SceneNode>> Children;
	bool IsLeaf;
	float radius;
	string name;  
	ActorID  id;

};


class MeshNode: public SceneNode
{
public:
	MeshNode(string name , ActorID id/*, shared_ptr<Mesh> mesh */); // You need your own mesh class
	~MeshNode();

	//shared_ptr<Mesh> GetMesh() { return Mesh;}    // You need your own mesh class
	//void SetMesh(shared_ptr<Mesh> m) {Mesh = m;}  // You need your own mesh class

	virtual void Draw();

protected:
	shared_ptr<SceneNode> Parent;
	// shared_ptr<Mesh> mesh;    // you need to have your own mesh class
};
