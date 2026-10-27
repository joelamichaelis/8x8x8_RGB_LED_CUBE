#8x8x8 RGB LED Cube Project
2026: cleaning up the repo a bit and making public primarily for archival purposes.
This repo contains detail on the 8x8x8 RGB LED cube project I worked on in 2 phases between 2018 & 2021 primarily.

#Phase 1:
A classmate and I built the cube back in 2018 for our senior design class.
This encompassed:
1. building the physical cube itself.
2. building prototype grade electronics wired to the cube and arduino.
3. Programming the arduino to do basic animations on the cube.
This is all we had time to do.

#Pase 2:
I kept the RGB cube and after graduating wanted to keep working on the project.
I designed, ordered, and built a motherboard pcb which eliminates the need for a messy jumble of wires under the led cube and instead plugs in directly.
It is powered by a 5V 5-10A power supply, drives the LED cube with a STM32F103 Blue Pill, has a display LCD, capacitive touch menu naviagation system, and more.

#Current State:
I took an indefinite hiatus just short of having something visually impressive I can easily power on and showcase different animations on.
Designing the motherboard specifically was a great learning experience. This is the first serious PCBA schematic + layout I designed myself.
Same goes for the STM32 firmware piece. Prior to this I was still using primarily arduino.
If I were to continue the project in the future, I would prioritize first cleaning up the firmware repo because it is a mess.

Also, check out companion repo: https://github.com/joelamichaelis/Eight-Cubed-RGB.
It appears that I later made that repo to try and migrate away from the messy firmware files here. Not sure how well that helped now having 2 repos.
