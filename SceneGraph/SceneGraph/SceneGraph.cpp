// This a Tutorial to demonstrate how to build Scene Graph
// for game engine or graphics engine
// wtang@bournemouth.ac.uk

#include "SceneNode.h"
#include "Scene.h"

int main()
{

	// Build a robot
	shared_ptr<SceneNode> root (new SceneNode("root", 1));

    shared_ptr<SceneNode> body (new SceneNode ("body", 2));
	body->SetModelScale(Fvector(1.0f, 1.0f, 1.0f));

	float data[16] = {1, 0, 0, 0,
	                  0, 1, 0, 0,
	                  0, 0, 1, 0,
	                  0, 0, 0, 1};

	FSmatrix4 bodyTransform (data);
    body->SetTransformation(bodyTransform);
	shared_ptr<MeshNode> bodyMesh(new MeshNode("body mesh",3/*,shared_ptr<Mesh> mesh */));
	body->AddChild(bodyMesh); // add body mesh to body operational node
	root->AddChild(body); // add body node to root node 

	shared_ptr<SceneNode> head (new SceneNode("head",4));
	shared_ptr<MeshNode> headMesh(new MeshNode("head mesh",5/*,shared_ptr<Mesh> mesh */));
	head->SetModelScale(Fvector(1.0f, 1.0f, 1.0f));

	float data2[16] = {1, 0, 0, 0,
				       0, 1, 0, 0,
				       0, 0, 1, 0,
				       0, 0, 5.0, 1};
	FSmatrix4 headTransform (data2);
	head->SetTransformation(headTransform);
	head->AddChild(headMesh);
	body->AddChild(head);

	 //... to build left arm, right arm, left leg, right leg 

	bool success = root->Update(1.0);
	if(!success)
	{
		cout<<"Failed to update Scene nodes"<<endl;
	}


	//--------------- Test Scene class------------
	//Scene* testScene;
	//testScene = new Scene;

	//shared_ptr<SceneNode> body (new SceneNode ("body", 2));
	//body->SetModelScale(Fvector(1.0f, 1.0f, 1.0f));

	//float data[16] = {1, 0, 0, 0,
	//                  0, 1, 0, 0,
	//                  0, 0, 1, 0,
	//                  0, 0, 0, 1};

	//FSmatrix4 bodyTransform (data);
	//   body->SetTransformation(bodyTransform);
	//shared_ptr<MeshNode> bodyMesh(new MeshNode("body mesh",3/*,shared_ptr<Mesh> mesh */));
	//body->AddChild(bodyMesh); // add body mesh to body operational node
	//testScene->AddChild(2, body); // add body node to root node 

	//shared_ptr<SceneNode> head (new SceneNode("head",4));
	//shared_ptr<MeshNode> headMesh(new MeshNode("head mesh",5/*,shared_ptr<Mesh> mesh */));
	//head->SetModelScale(Fvector(1.0f, 1.0f, 1.0f));

	//float data2[16] = {1, 0, 0, 0,
	//			       0, 1, 0, 0,
	//			       0, 0, 1, 0,
	//			       0, 0, 5.0, 1};
	//FSmatrix4 headTransform (data2);
	//head->SetTransformation(headTransform);
	//head->AddChild(headMesh);
	//body->AddChild(head);

	//// ... to build left arm, right arm, left leg, right leg 

 //   testScene->OnUpdate(1.0);
	//-----------end of test scene class ----------

	system("pause");
	return 0;
}
