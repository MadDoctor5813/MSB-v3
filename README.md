# MSB-v3
This is the ROBOTC control code for VEX team 296B, 2015-2016 season, This is being uploaded for posterity, (and maybe so I can use part of it next year)

The design works on the concept of systems, located in the include files. Each system has a poll input function, and an apply input function.
These are called every loop by the main file, much like a game loop. Each system reads input from the joystick system, saves any needed state to a local struct, then applies the input to the robot mainly through motors. 

This is MSB version 3. MSB stands for Masterful Struct Blob, the name a team mate gave it when I first proposed the concept. Version 1 tried to use ROBOTC tasks have each system run at the same time. This only led to pain and suffering, so the current game loop design was adopted for version 2. After our first competition, the robot was redesigned, and so was the code, leading to the current version 3.
