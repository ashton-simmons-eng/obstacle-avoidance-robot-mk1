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
Brought the sensor and motor control together into the final avoidance logic: continuously read distance, and if an obstacle is closer than the threshold, briefly reduce speed on one side to turn away, otherwise drive both sides forward evenly. Distance threshold, turn duration, and motor speeds were all tuned through iterative physical testing rather than calculated upfront. The motors were originally run at full speed, but this made the robot too fast to react cleanly to obstacles, so I reduced the base speed via `analogWrite` until it had enough reaction time.

**6. Attempting to fix drift**
To address the left/right drift on straight runs, I tried trimming the two motors' PWM values slightly unevenly in code, giving the drifting side a bit more power to compensate. This helped a little, but didn't fully solve the problem, since the caster wheel's free-swivelling behaviour meant the drift wasn't fully consistent between runs, so a fixed code-level trim couldn't fully correct for it.


## Known limitations (v1)

Documented here honestly rather than fully fixed, since they're the clearest targets for a Mark 2 rebuild:

- **Caster wheel drift:** the free-swivelling front caster wheel causes inconsistent left/right drift on long straight runs, and can randomise which way the robot initially turns on bootup. A code-level fix (trimming one motor's PWM slightly higher to compensate) helped somewhat but couldn't fully correct it, since the drift itself wasn't consistent enough between runs for a fixed trim value to reliably cancel out.
- **Low-PWM stall:** below a certain PWM value, a motor stalls completely instead of just slowing down, since the value falls below the motor's start-up threshold. This limits how gentle a turn can be made without a motor cutting out entirely.
- **Fixed turn direction:** the current avoidance logic always turns the same way when it detects an obstacle, regardless of which side has more space. It doesn't yet make any judgement about which direction is actually clearer.
## What's next (Mark 2)

The main planned change is moving to full four-wheel drive, replacing the free-swivelling caster wheel entirely so there's no unpowered wheel left to cause drift, addressing the root cause rather than compensating for it in code. A 3D-printed chassis is also planned to replace the cardboard-and-tape v1.

Beyond that, I'm considering (not yet decided): mounting the ultrasonic sensor on a servo so it can scan side to side rather than only sensing straight ahead, which would also let the robot compare distances on each side and choose which way to turn instead of always turning the same direction, and exploring some form of MATLAB integration, though I haven't worked out what that would look like in practice yet.

## Files

| File | Description |
|---|---|
| `ultrasound_test.ino` | Isolated ultrasonic sensor test |
| `motor_test.ino` | Isolated motor test — run on the original L293D driver, then re-run unchanged after switching to the L298N driver |
| `avoidance_sketch.ino` | Final combined sensor + differential steering avoidance logic |

## Glossary

- **PWM (Pulse Width Modulation):** the method used to control motor speed by rapidly switching power on and off; a higher PWM value means more time on, so a faster motor speed.
- **HC-SR04:** the specific model of ultrasonic distance sensor used, measures distance by timing how long a sound pulse takes to bounce back.
- **TT motor:** a common, low-cost gear motor used in small robotics projects, named after its gearbox type.
- **Differential/tank steering:** a steering method where the two sides of the robot are driven independently, turning by running one side faster than the other, rather than using a separate steering mechanism.
- **Caster wheel:** a free-swivelling, unpowered wheel used for support rather than drive or steering.
- **L293D / L298N:** motor driver ICs/modules, used to control motor direction and speed from the low-power signals an Arduino can output, since the Arduino itself can't supply enough current to drive motors directly.
