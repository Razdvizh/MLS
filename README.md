# MLS
My Locomotion System is Unreal Engine 5.3 project created to explore various ways for animation optimization. It covers most of the methods that engine offers while trying to provide guidelines and explanation for each of them.

# Overview
Note that methods below were implemented in C++ when possible as nativization is universal for optimization of code in Unreal.

## Profiling tools
> [Unreal Documentation](https://docs.unrealengine.com/5.3/en-US/animation-insights-in-unreal-engine/)

Primary tool for animation profiling is **Animation Insights**, which allows to find expensive CPU time operations as well as thread hitches or stalls caused by animation updates.
[Rewind Debugger](https://docs.unrealengine.com/5.3/en-US/animation-rewind-debugger-in-unreal-engine/) is worth mentioning, although it is designed to debug visual animation artifacts and bugs rather than performance.

##  ACL
> [Unreal Documentation](https://docs.unrealengine.com/5.3/en-US/animation-compression-library-in-unreal-engine/)
>
> [Github repo](https://github.com/nfrechette/acl)

Animation Compression Library helps with optimization of bones and animation curves data, and it is utilized in many video game engines. Since Unreal Engine 5.3, ACL is fully integrated and can be enabled as plugin. In fact, after enabling the library its default compression settings will be applied to all animation assets automatically. 

Unfortunately, tests conducted in MLS haven't show much difference between compressed and non-compressed assets, likely due to small amount of bones and curves present. 
In conclusion, ACL can be enabled by default as it doesn't require any additional setup, and in case of artifacts or performance issues individual assets can be tweaked or opted-out of compression.

## Linked Anim Layers
> [Unreal Documentation](https://docs.unrealengine.com/5.3/en-US/using-animation-blueprint-linking-in-unreal-engine/)

In MLS, Linked Animation Layers are implemented to address two potential problems in large projects - how to change animation assets and potentially AnimGraph logic for different character states and how to prevent loading of unused animation assets in memory. 

First, main animation blueprint implements **Animation Layer Interface (ALI)** and calls its layers. Layers declared in ALI represent states that can change depending on character state, for example idle animation when on ground or when floating on water. Next step is to create *state animation blueprint* that would declare animation assets and define animation layers in AnimGraph for main anim blueprint. Multiple state anim blueprints and ALIs can be created depending on the complexity of the game. Finally, concrete animation blueprint for the state is derived from state anim blueprint to do nothing but fill empty animation assets declared in the base class. Check the UML diagram below and MLS project to see it in practice.

<img width="450" alt="LinkedAnimLayersUML" src="https://github.com/Razdvizh/MLS/assets/114196034/865eb1e0-ff90-42f1-a8e9-622c4051e59c">

[References](#AdditionalReferences)

<a id="AnimationBudgetAllocator"></a>
## Animation Budget Allocator
> [Unreal Documentation](https://docs.unrealengine.com/5.3/en-US/animation-budget-allocator-in-unreal-engine/)

Animation budget allocator replaces prior **Update Rate Optimizations (URO)** that were set to act similarly to LODs but for animations. Compared to URO, budget allocator works globally on all skeletal meshes that are **budgeted**, and quality reduction is applied based on the budget as well as distance. MLS demonstrates both advantages - first, budgeted skeletal mesh is only used for test characters since player character shouldn't be optimized. With that in place, change of settings in runtime is much easier because there is no need to apply new values to each instance individually. Now, the performance budget can be set that will determine the final quality of animation. If animation complexity of the scene doesn't exceed the budget, then there is no penalty. Otherwise animations of budgeted skeletal meshes will reduce the animation tick rate and possibly disable frame interpolation in an attempt to get closer to the set budget. Presence of the performance budget helps configure scalability from one global point in the project. Below is the comparison of different budgets in the same scene.
> Settings for animation budget allocator can be found in the ThirdPersonMap's level blueprint.

https://youtu.be/F-KTFv7hoB4

## Skeletal Mesh optimizations
> [Unreal Documentation](https://docs.unrealengine.com/5.3/en-US/animation-optimization-in-unreal-engine/)

Skeletal Mesh component has control over some options regarding udpate of Animation and Physics asset. The main one is **Update Rate Optimizations** which, following the same idea as LODs, reduces quality of animation for farther distances by throttling update rates and disabling frame interpolation. MLS character doesn't use this system because [Animation Budget Allocator](#AnimationBudgetAllocator) plugin is used instead. Also, MLS character has `Component Use Fixed Skel Bounds` enabled which allows to bypass Physics Asset calculations.
 
## Fast Path
> [Unreal Documentation](https://docs.unrealengine.com/5.3/en-US/animation-optimization-in-unreal-engine/)

Let's start with a quote from documentation: 
> Animation Fast Path provides a way to optimize variable access inside the AnimGraph update. This enables the engine to copy parameters internally rather than executing Blueprint code, which involves making calls into the Blueprint Virtual Machine.

So, accessing member variables directly without any additional blueprint logic (exception is `NOT` node) will enable compiler optimizations. If additional calculations are inevitable, they can be placed in node function to preserve Fast Path. Nodes that have Fast Path enabled are marked with ![AnimationNode_FastPath](https://github.com/Razdvizh/MLS/assets/114196034/07081192-1e63-49ad-8f9e-e1b9ae6bf917) icon. It is also possible to enable warnings for Fast Path in `Animation Blueprint->Optimization->Warn About Blueprint Usage`. 

<img width="450" alt="FastPathExample" src="https://github.com/Razdvizh/MLS/assets/114196034/bb30b776-12f3-47e4-a117-402b65b9f373">

## Multithreading
> [Unreal Documentation](https://docs.unrealengine.com/5.3/en-US/animation-optimization-in-unreal-engine/)

Animation blueprint can perform parallel update, reducing the work on the GameThread. Luckily, meta specifiers and appropriate virtual functions of `AnimInstance` class are sufficient to enable parallelism for animation update. Data needed to drive anim nodes can be set in `NativeThreadSafeUpdateAnimation(float DeltaSeconds)`. This data can be accessed from Property Access in blueprints or from function marked with `meta=(BlueprintThreadSafe)`. Check `MLSAnimInstanceBase.h` and `StateAnimLayersBase.h` for examples.

Note that root motion animations must be evaluated on the GameThread.

Here is the difference in performance observed in **Animation Insights** between `ABP_MLS` and `ABP_MLS_Slow`.

![image](https://github.com/Razdvizh/MLS/assets/114196034/9d462e51-8bb6-4372-a8eb-31420aca7ea5)

![image](https://github.com/Razdvizh/MLS/assets/114196034/2504cd19-8d61-4892-9eec-af0075101f62)

<a id="AdditionalReferences"></a>
### Additional references
> [Lyra](https://docs.unrealengine.com/5.3/en-US/animation-in-lyra-sample-game-in-unreal-engine/)
