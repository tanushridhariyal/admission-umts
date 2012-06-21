RE56 : Mobile networks
Admission control in UTMS Networks
By Masson Brice and Grosperrin Quentin

Spring 2012, UTBM

/* ------------------------------------------------- */
                 Source files architecture :
/* ------------------------------------------------- */

admission_umts.qrc 
=> Qt file 
admission_umts.ui
=> Qt file containing all the information to draw the GUI
BaseStation.h - BaseStation.cpp
=> Class used to simulate a base station. It contains all the base station parameters as attributes, 
and a list of users which are in the cell
User.h - User.cpp
=> Class used to simulate a user. A user is associated to a base station.
Launcher.h - Launcher.cpp
=> Class used to implement the application behavior and initialize the GUI and the simulation.
main.cpp
=> The main file used to launch an instance of Launcher to create the GUI.

/* ------------------------------------------------- */
                How to install/run the program :
/* ------------------------------------------------- */

No installation is needed, just execute the 'admission-umts.exe' on a Windows machine.
Once is done, all the parameters for the simulation are preset, just hit 'Launch simulation'.

/* ------------------------------------------------- */
                Where are the results :
/* ------------------------------------------------- */

All the results are directly displayed on-screen.