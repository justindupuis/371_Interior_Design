 COMP 371 AA (Summer 2016)
 Assignment 1
 Justin Dupuis - 29690352
 

 Requirements Implemented:
 > GRAPHICS
 	- Create meshes for Spinner (Cube composed of 12 triangles)		- COMPLETE
 	- Create meshes for Revolver (Cube composed of 12 triangles)	- COMPLETE
 	- Make Spinner larger than Revolver								- COMPLETE
 	- Make the two cubes different colors							- COMPLETE
 	- Rotate Spinner on it's central axis							- COMPLETE
 	- Revolve Revolver around the same axis							- COMPLETE
 	- Do NOT make Revolver rotate on it's own axis					- COMPLETE
 	- Match Spinner's rotation to Revolver's revolutions			- COMPLETE
 	- Use an 800x800 GLFW window with double buffering				- COMPLETE
 	- Use a perspective view to display								- COMPLETE
 	- Use the depth buffer for hidden surface removal				- COMPLETE
 
 > CONTROLS
 	- Increase size of Spinner with S								- COMPLETE
 	- Decrease size of Spinner with s								- COMPLETE
 	- Increase size of Revolver with R								- NOT COMPLETED: Spinners controls impact revolver as well
 	- Decrease size of Revolver with r								- NOT COMPLETED: Spinners controls impact revolver as well
 	- Rotate mesh with L/R/U/D arrows								- 50% COMPLETED: L/R work, but U/D not implemented.
 	- Change Rendering mode with P,W,T								- COMPLETE
 	- Zoom camera forward/back with mouse when left-clicking		- COMPLETE

 Base code modified from Lab 2 source (original source = learnopengl.com).
 NOTE: Shaders found in: C:\Users\Justin\Dropbox\Concordia\COMP371\030 Assignments\Assignment1\comp371lab2