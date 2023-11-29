#pragma once
#include <vector>
// singleton class that allows scene to be globally accessed since there will only be one current scene being displayed at a time
class Scene
{
private:
    inline static Scene* instance;
    class std::vector<class DisplayObject*> ObjectsInScene;
    class std::vector<class Light*> SceneLights;
    // Private constructor to prevent external instantiation
    Scene(){};
    // Private destructor to prevent accidental deletion
    ~Scene(){};
    // Prevent copying or assignment
    Scene(const Scene &) = delete;
    // Scene& operator=(const Scene&) = delete;
    class Camera* SceneCamera = nullptr;
public:
    static Scene *GetScene()
    {
        if (!instance)
        {
            instance = new Scene();
        }
        return instance;
    }

    void RenderScene();
    inline void AddSceneObject(DisplayObject* ObjectToAdd) { ObjectsInScene.push_back(ObjectToAdd); };
    inline void AddLight(Light* LightToAdd) { SceneLights.push_back(LightToAdd); };
    class Camera* GetCamera();
};