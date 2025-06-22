
# Radar + Missile Targeting System — Prototype Overview

**Goal:**  
Build a small, self‑contained Unreal Engine prototype that demonstrates a defence‑style workflow:
1. **Radar** rotates and detects airborne targets.  
2. **Decision module** filters detections (ignores brief/noisy hits).  
3. **Launcher** fires a homing **missile** when a target is confidently locked.  
4. **Missile** guides toward and destroys the target.

---

## High‑Level Architecture

| Element | Responsibility |
|---------|----------------|
| **ARadarSystem** | • Continuous rotation (Yaw)  
• Checks angle + distance to each potential target  
• Emits “detection” events |
| **UDecisionModule** (Actor Component) | • Accumulates detection time per target  
• Confirms a **lock** after *X s* of continuous detection  
• Fires `OnValidTargetLocked` delegate |
| **AMissileLauncher** | • Listens to lock events  
• Spawns a missile and hands over the target |
| **AMissile** | • Propels forward at constant speed  
• Adjusts direction toward the target each tick  
• Self‑destructs on impact or if target is lost |
| **ATargetDrone** | • Moves along a simple path (linear, sinusoidal, random)  
• Serves as friendly or hostile aircraft |

---

## Key Features to Demonstrate

* 3‑D vector math (dot product, angles, normalization).  
* Clean **C++ Unreal** integration (`UCLASS`, `UPROPERTY`, `UFUNCTION`).  
* Modular design following **Single Responsibility Principle**.  
* Basic UI/log feedback (detection, lock, missile launch, impact).  
* Simple noise rejection logic (e.g. **ignore detections < 0.5 s**).  

---

## Quick Build Steps

1. **Clone** the repo.  
2. Open a developer prompt and run:  
   ```GenerateProjectFiles.bat```  
3. Open the solution in **Visual Studio 2022**, build **Development Editor**.  
4. Launch the `.uproject` in **Unreal Engine 5.4** (or 4.27+ if preferred).  
5. Press **Play** — radar scans, detects the drone, locks, and fires.

> **Estimated implementation time (baseline):** *≈ 3‑4 hours*  
> Add polish (UI, FX, component pooling) as time allows.

---

## Stretch Ideas (Optional)

* **Multiple drones** with friend/foe identification.  
* Adjustable radar parameters via in‑editor sliders.  
* Heat‑seeking vs. radar‑seeking missile modes.  
* Simple **Automation Tests** to verify lock timing logic.  

---

## Deliverables

* Compilable UE project (`.uproject`, `Source`, `Content`, `Config`).  
* This `README` (or similar) describing goals, architecture, and build steps.  
* Short screen capture or GIF (optional but recommended).  
