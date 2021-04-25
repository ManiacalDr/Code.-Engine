//#include "spine/spine.h"
//
//using namespace spine;
//
////Load atlas, which is an example asset for now
//TextureLoader* textureLoad = new MyEngineTextureLoader();
//String myExample = "./exampleAssets/stretchyman";
//Atlas* atlas = new Atlas(myAtlas + "/stretchyman.atlas", textureLoad);
//
////Check for fault
//if (atlas.getPages().size() == 0)
//{
//    printf("%s\n", "Atlas Err");
//    exit(0);
//}
//
//
////Load skeleton from atlas
//SkeletonJson json(atlas);
//int x = 2;//set as a default, must be checked
//json.setScale(x);
//SkeletonData* skeletonData = json.readSkeletonDataFile(myExample + "/stretchyman-pro.json");
//
////Skeletons can also be edited manually. We could use this to our advantage
//Skeleton* skeleton = new Skeleton(skeletonData);
////Bone* armBone = skeleton->findBone("armBone");
////printf(skeleton->updateWorldTransform()); //enocded array and worldX and Y
////bone->getWorldRotationY(); ScaleX();
////bone->worldToLocal(worldX,worldY(to),localX,localY)
////localToWorld(); bone-> worldToLocalRotation(bone)
//
////Check for fault
//if (!skeletonData)
//{
//    printf("%s\n", "Initial Skeleton Err");
//    exit(0);
//}
//
////Load AnimationStateData from Skeleton
//AnimatonStateData* animationStateData = new ANimationStateData(skeletonData);
//
////smooth animation transition var in "mix time" form
//animationStateData->setDefaultMix(0.1f);
//
////to set certain mixes
////animationState->setMix("jump","walk",0.2f);
//
////position skeleton
//skeleton->setX(myObj->worldX);
//skeleton->setX(myObj->worldY);
////setFlipX(true);
//
////(optional) skeleton->setSkin("skinName");
////(optional) skeleton->setAttachment("hand","sword"); clear = setAttachment(skeleton,"hand","");
//
//
//
////Animating
////Only 1 animation for example
////tracks go by seconds
//int track = 0;
//bool loop = true;
//float delay = 0;
//AnimationState* animationState = new AnimationState(animationStateData);
//animationState->addAnimation(track, "walk", loop, delay);
//
////->clearTrack(0) clearall clearTracks(animationState);
////Set						track, animation, loop
////animationState->setAnimation(0, "walk", true);
////->setMix("walk","shot",0.1f);
//
////Animation Events
///*void callback(AnimationState* state, EventType type, TrackEntry* entry, Event* event){
//   const String& animationName = (entry && entry->getAnimation()) ? entry->getAnimation()->getName() : String("");
//   switch (type) {
//   case EventType_Start:
//      printf("%d start: %s\n", entry->getTrackIndex(), animationName.buffer());
//      break;
//   case EventType_Interrupt:
//      printf("%d interrupt: %s\n", entry->getTrackIndex(), animationName.buffer());
//      break;
//   case EventType_End:
//      printf("%d end: %s\n", entry->getTrackIndex(), animationName.buffer());
//      break;
//   case EventType_Complete:
//      printf("%d complete: %s\n", entry->getTrackIndex(), animationName.buffer());
//      break;
//   case EventType_Dispose:
//      printf("%d dispose: %s\n", entry->getTrackIndex(), animationName.buffer());
//      break;
//   case EventType_Event:
//      printf("%d event: %s, %s: %d, %f, %s\n", entry->getTrackIndex(), animationName.buffer(), event->getData().getName().buffer(), event->getIntValue(), event->getFloatValue(),
//            event->getStringValue().buffer());
//      break;
//
//
//    state->update(0)
//    state->apply(skeleton);//on every update
//    state->apply(*skeleton);//I think they do different things
//    skeleton->updateWorldTransform();
//   }
//   fflush(stdout);*/
//
//
//   //main loop
//   //Skeleton* skeleton = skeletons[i]; for i max
//AnimationState* animationState = new AnimationState(animationStateData);
//animationState->apply(skeleton);
//skeleton->updateWorldTransform();
////engine_drawSkeleton(skeleton);
//
////When done
//delete skeleton;
//delete animationSate;
//delete atlas;
//delete skeletonData;
//delete animationStateData;
//

