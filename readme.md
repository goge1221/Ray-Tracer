# Raytracer by Andrei Goje 12032793

#### 1. Claims: T1 - T5 fully implemented
#### 2. Tested in CLion and in the Mac terminal also on almighty. 


**How to compile?**

The project is located under: /home/andreig01/Desktop/GFX

If you cd inside the build folder you can use the command **_./Lab_3_** to run the program.

After this you will be asked to give the file path of the xml file you want to use. 
My files are located in the scenes folder so you can copy and paste the location from here and paste it into the terminal: 

/home/andreig01/Desktop/GFX/scenes/personal_example.xml
/home/andreig01/Desktop/GFX/scenes/example1.xml
/home/andreig01/Desktop/GFX/scenes/example2.xml
/home/andreig01/Desktop/GFX/scenes/example3.xml

All of the files will be saved in the form of a PPM file in the build directory. 

If something is now working you can try and delete the build folder then execute following commands: 

1. mkdir build
2. cd build
3. cmake ..
4. make

After this try to run the program normally. 
