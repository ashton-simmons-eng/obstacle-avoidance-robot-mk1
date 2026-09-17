# Obstacle-Avoidance Robot – Mark 1

Arduino-based robot using ultrasonic distance sensing and differential (tank-style) steering to detect and avoid obstacles in real time.

## What it does

I wanted to build something that could react to its environment in real time, not just run a pre-programmed sequence. This robot drives forward continuously, using an ultrasonic sensor to measure the distance to whatever is ahead of it. When an obstacle comes within range, it slows one side's motors relative to the other, causing it to swerve away, then continues forward once clear.

**Demo video:** [Watch on Google Drive](https://drive.google.com/file/d/1OvaWbJaSq4alvr-HEgvK1Kx1PLRk49AQ/view?usp=sharing)

## Hardware

- Arduino Uno
- HC-SR04 ultrasonic distance sensor (fixed, forward-facing)
- 2x TT gear motors with wheels (differential/tank steering)
- 1x free-swivelling caster wheel (front)
- L298N motor driver module
- 4x AA battery pack (motor power), Arduino powered separately via portable charger
- Sticky pads, used to mount components to the chassis
- Cardboard-and-tape chassis (v1 — a 3D-printed rebuild is planned once I'm back at university with access to a printer)

## Build process

**1. Sensor test (`ultrasound_test.ino`)**
Isolated test of the HC-SR04, reading distance to the serial monitor, to confirm the sensor worked correctly before integrating it with anything else.

**2. Motor test — L293D driver (`motor_test.ino`)**
Isolated test of both TT motors (forward, stop, reverse) using the kit's L293D driver and a 9V battery. In testing, this setup couldn't sustain enough current to reliably drive two motors at once, the motors stalled or ran inconsistently.

**3. Switching to the L298N driver**
Diagnosed the problem as a current limitation in the L293D/9V battery combination, not a code issue. Switched to a separate L298N driver module (screw terminals, no soldering required) and a 4xAA battery pack for motor power instead. The battery pack I bought came fitted with a barrel jack connector rather than bare leads, so I had to cut it off and strip the wires to connect it directly to the L298N's screw terminals.

**4. Confirming the fix**
Re-ran the motor test on the new driver to confirm the hardware switch had fixed the current problem. It had, both motors now ran reliably, using the same core forward/stop/reverse logic as the original test.

**5. Combined sketch (`avoidance_sketch.ino`)**
Brought the sensor and motor control together into the final avoidance logic: continuously read distance, and if an obstacle is closer than the threshold, briefly reduce speed on one side to turn away, otherwise drive both sides forward evenly. Distance threshold, turn duration, and motor speeds were all tuned through iterative physical testing rather than calculated upfront.

## Known limitations (v1)

Documented here honestly rather than fully fixed, since they're the clearest targets for a Mark 2 rebuild:

- **Caster wheel drift:** the free-swivelling front caster wheel causes inconsistent left/right drift on long straight runs, and can randomise which way the robot initially turns on bootup.
- **Low-PWM stall:** below a certain PWM value, a motor stalls completely instead of just slowing down, since the value falls below the motor's start-up threshold. This limits how gentle a turn can be made without a motor cutting out entirely.

## What's next (Mark 2)

A 3D-printed chassis (replacing the cardboard-and-tape v1) to fix the caster wheel drift with a more controlled front wheel setup, and characterising each motor's minimum start-up PWM so turning speeds stay above the stall threshold.

## Files

| File | Description |
|---|---|
| `ultrasound_test.ino` | Isolated ultrasonic sensor test |
| `motor_test.ino` | Isolated motor test — run on the original L293D driver, then re-run unchanged after switching to the L298N driver |
| `avoidance_sketch.ino` | Final combined sensor + differential steering avoidance logic |
