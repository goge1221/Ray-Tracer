# Raytracer by Andrei Goje 12032793

## Features Implemented
- Claims: T1 - T5 fully implemented.

## Compilation Instructions
1. The project is located at: `/home/andreig01/Desktop/GFX`.
2. Navigate to the build folder.
3. Use the command `./Lab_3_` to run the program.
4. You will be prompted to provide the file path of the XML file you want to use.
    - Example XML file paths:
        - `/home/andreig01/Desktop/GFX/scenes/personal_example.xml`
        - `/home/andreig01/Desktop/GFX/scenes/example1.xml`
        - `/home/andreig01/Desktop/GFX/scenes/example2.xml`
        - `/home/andreig01/Desktop/GFX/scenes/example3.xml`
5. The rendered images will be saved as PPM files in the build directory.

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
- Structure and Geometry: The structure of the code and the geometry calculations, including camera ray calculation and collision checking formulas, were inspired and adapted from the book "Ray Tracing in One Weekend," available at: [https://raytracing.github.io/books/RayTracingInOneWeekend.html](https://raytracing.github.io/books/RayTracingInOneWeekend.html).
