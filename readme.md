# Raytracer by Andrei Goje 12032793

## Features Implemented
- Claims: T1 and T2 fully implemented.

## Compilation Instructions
1. Navigate to the cmake-build-debug folder and open it in the terminal.
2. Use the command `./Lab_3` to run the program.
3. You will be prompted to provide the file path of the XML file you want to use.
    - Example XML File path:
        - `/home/andreig01/Desktop/GFX/scenes/example5.xml`
    - **Important**: the program assumes that the .obj file is also located in the *scenes* folder
4. The rendered images will be saved as PPM files in the build directory.

## Troubleshooting
If you encounter any issues, you can try the following steps:

1. Delete the existing build folder.
2. Execute the following commands in order:
    - `mkdir build`
    - `cd build`
    - `cmake ..`
    - `make`
3. Once the build process completes, run the program normally as stated above.

## Remarks
- XML Parsing: The TinyXML library (cpp and h) were used for parsing XML files. You can find it at: [https://github.com/leethomason/tinyxml2](https://github.com/leethomason/tinyxml2).
- Structure and Geometry: The structure of the code and the geometry calculations, including camera ray calculation and collision checking formulas, were inspired and adapted from the book "Ray Tracing in One Weekend," by Peter Shirley available at: [https://raytracing.github.io/books/RayTracingInOneWeekend.html](https://raytracing.github.io/books/RayTracingInOneWeekend.html).
- Displaying the "walls":  The collision checking formulas for the wall and the structure of the code, were inspired and adapted from the book "Ray Tracing The Next Week," by Peter Shirley available at: [https://raytracing.github.io/books/RayTracingTheNextWeek.html#rectanglesandlights](https://raytracing.github.io/books/RayTracingTheNextWeek.html#rectanglesandlights).
