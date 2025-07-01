### Radar Simulator Project

🟢 Find the build here [Drive Link](https://drive.google.com/drive/folders/1HKk3oIGKdJkL-PVvqBYg7qxeGiaAkuS0?usp=sharing) 🟢

---

#### Overview

Prototype of a Radar Simulator. This project was made with the objective to simulate the behavior of a Radar with a Decision Component which filters out parasite noises and keep potential targets.

Once done the linked Missile Launcher if all conditions are right, fire a homing missile.


#### How to install ?

After cloning the project, right click on the uproject icon and :

 * If you want to see the source
  * Generate visual studio files

 * If you just want to look at the editor
  * Just double click the uproject

#### How was it made ?

After Setting Unreal environment I did the Class Diagram, then went into production for v1

After v1 was made I put the map together and other visual elements to improve UX

Then I checked what could be upgraded, and found that ticks were saturated and the spawn system missed a Pooling sytem

So I went back to work and here you have this final version

#### How Much Time ?

With everything, including testing and enhancement between 12-17h 


#### Potential Upgrades

* The current radar visualiser doesn't register enemy "bips", I rather focus on stable and structured code but definitly something on my mind.

* Add a more realistic missile Behavior 
  * Now using the predicted target location with predicted missile location 
  * Intent to use a radar attach to the missile  

* More FX and SFX
