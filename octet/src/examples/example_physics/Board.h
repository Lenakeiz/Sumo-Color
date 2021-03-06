#pragma once

namespace octet{
   class Board : public resource
   {

   private:
      int current_tilt;
      //btScalar radius;
      vec3 size;
      ref<material> mat;
      ref<scene_node> node;
      ref<mesh_instance> meshinstance;
      btRigidBody* rigidBody; //Try implementing an non invasive (smart) pointer -- effective c++ 

   public:

   
      Board(vec3_in size)
      {
         current_tilt = 0;
         this->size=size;
         //Assigning material
         mat = new material(new image("assets/ground3.gif"));

         //Creating default rigidbody
         mat4t modelToWorld;
         modelToWorld.loadIdentity();
         btCollisionShape *shape = new btCylinderShape(btVector3(size.x(),size.y(),size.z()));
         btMatrix3x3 matrix(get_btMatrix3x3(modelToWorld));
         btVector3 pos(get_btVector3(modelToWorld[3].xyz()));
         btTransform transform(matrix, pos);
         btDefaultMotionState *motion = new btDefaultMotionState(transform);

         //Calculate inertia for the body
         btVector3 inertia;
         shape->calculateLocalInertia(0.0f, inertia);
         //Saving rigid body 
         rigidBody = new btRigidBody(0.0f, motion, shape, inertia); //need to add this to the world (bullet physics) and also to the rigid bodies collection
         //rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() & btCollisionObject::CF_STATIC_OBJECT);
         int index = InnerObjectTag::BoardTag;
         rigidBody->setUserIndex(index);
         
         //Creating node to draw with mesh
         mat4t position;
         position.loadIdentity();
         position.scale(size.x(),size.y(),size.z());
         position.rotate(90, 1, 0, 0);
         mesh_cylinder* meshcylinder = new mesh_cylinder(zcylinder(), position, 50);
         node = new scene_node(modelToWorld, atom_);
         meshinstance = new mesh_instance(node, meshcylinder, mat);
         
      }

      ~Board()
      {
         //delete rigidBody;
      }

      void Draw(){
      
      }

      btScalar GetRadius(){
         return this->size.x();
      }

      btScalar GetHalfHeight(){
         return this->size.y();
      }

      mesh_instance* GetMesh(){
         return meshinstance;
      }

      btRigidBody* GetRigidBody(){
         return rigidBody;
      }

      scene_node* GetNode(){
         return node;
      }

   };
}

