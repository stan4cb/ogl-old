#include "gameObject.h"

const static string DataDir = "Data/";
#include <iostream>
GameObject::GameObject(string pref )
{
    std::cout << "new game object : " << pref << std::endl;
    LoadPrefab(pref);
}
void GameObject::LoadPrefab(string fName)
{
    string fScr = DataDir + fName + ".pref";
    fstream file(fScr.c_str());
    if(file.is_open())
    {
        while(!file.eof())
        {
            string input,sVal;
            float fVal;
            file >> input;
            if(input == "model")
            {
                file >> sVal;
                if(!Load( DataDir + sVal))
                {
                    throw runtime_error(sVal);
                }
            }
            else if(input == "scale")
            {
                file >> fVal;
                uScale(fVal);
            }
            else if(input == "position")
            {
                vec3 tPos;
                file >> tPos.x >> tPos.y >> tPos.z;
                uPosition(tPos);
            }
        }
    }
    else
        throw runtime_error("Can't read prefab file");
}