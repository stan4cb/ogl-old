#ifndef COLLIDER_H
#define COLLIDER_H

#include <glm/glm.hpp>
#include <vector>
#include "tools.h"
#include "component.h"

using namespace std;
using namespace glm;
using namespace Tools;

class GameObject;
class Collider : public Component
{
private:
    static vector<Collider*> colliders;

    float GetSize();
    static float GetSize(Collider*);
public:
    Rect box;
    float xMin,xMax,yMin,yMax;

    Collider(GameObject*);
    Collider(GameObject* , Rect);
    ~Collider();

    void Start() {}
    void Update() {}

    static GameObject* Get(vec3);
    static vector<GameObject*> GetAll(vec3);

    bool isGrounded();
    vector<Collider*> GetGrounded();

    vector<Collider*> Intersect();
    vector<Collider*> Intersect( vec3 );
    static vector<Collider*> Intersect( Collider* );
    static vector<Collider*> Intersect( Collider* , vec3);
};

#endif // COLLIDER_H
