#include "spine/spine.h"

using namespace spine;


class Animator
{
//String myExample = "./exampleAssets/stretchyman";

Atlas* atlas;
AnimationState* animationState;
Skeleton* skeleton;


 Animator(String atlasLocation, String skeletonLocation,Object sprite)//sprite is assumed to have world LocRotScale
{
//Load atlas
TextureLoader* textureLoad = new MyEngingeTextureLoader();
atlas = new Atlas(atlasLocation,textureLoad);

//Check for fault
if(atlas.getPages().size()==0)
	{
	printf("%s\n", "Atlas Err");
	exit(0);
	}

//Load skeleton from atlas
SkeletonJson json(skeletonLocation);
json.setScale(2);//default of 2, must be checked
SkeletonData* skeletonData = json.readSkeletonDataFile(skeletonLocation);


//Check for fault
if(!skeletonData)
	{
	printf("%s\n", "Initial Skeleton Err");
	exit(0);
	}

skeleton = new Skeleton(skeletonData);//json

skeleton->setX(sprite.getWorldX());
skeleton->setY(sprite.getWorldY());
skeleton->updateWorldTransform();

AnimationStateData* animationStateData = new AnimationStateData(skeletonData);
animationStateData -> setDefaultMix(0.1f);

}

//track = animation state seconds
void addAniation(String name, int track, bool loop, float delay)
{
    animationState->addAnimation(track,name,loop,delay);
}

void deleteAnimation(int track);
{
    animationState->clearTrack(track);
}

void setMix(int time, String first, String second)//Sets mix between two animations
{
    animationState(first,second,time);
}

void animated(String name, int track, bool loop)
{
    animationState->setAnimation(track,name,loop);
    animationState->update(track);
    animationState->apply(skeleton);
    //animationState->apply(*skeleton);
    skeleton->updateWorldTransform();
}

/*Loop:
	
    animationState->update(track);
    animationState->apply(skeleton);
    //animationState->apply(*skeleton);
    skeleton->updateWorldTransform();

*/
    ~Animator(){
        delete skeleton;
        delete animationSate;
        delete atlas;
        delete skeletonData;
        delete animationStateData;
    }
}