# Ray Tracer Project

## Project Overview

This project is a ray tracing engine developed from scratch, inspired by Peter Shirley's "Ray Tracing in One Weekend." Ray tracing is a rendering technique that generates images by simulating how light interacts with objects. 

## Features

- **Basic Ray Tracing**: Implements core algorithms to render spheres with simple lighting.
- **Materials**: Supports lambertian (diffuse), metal, and dielectric materials, allowing for varied textures and appearances.
- **Antialiasing**: Implements antialiasing to smooth out edges, improving visual quality.
- **Camera**: Includes a customizable camera model for flexibility in scene composition.
- **XML Scene Parsing**: Utilizes TinyXML for parsing XML files, enabling easy scene setup and configuration.
- **PNG Output**: Employs SBT (presumably a library for image output, ensure correct name if different) to write the rendered output to PNG files, offering a convenient way to view and share results.

# Examples 
The project can read input from 5 sample XML file and produce the scene settings based on elements and lights present in the scenes. Here are some example scenes: 

<p align="center">
  <img src="https://github.com/goge1221/Ray-Tracer/assets/75140192/b75db430-c327-4181-a1aa-9bca085bfcf6" alt="First Image" width="30%">
  <img src="https://github.com/goge1221/Ray-Tracer/assets/75140192/e5a34700-7b74-4226-9503-8020340451b8" alt="Second Image" width="30%">
  <img src="https://github.com/goge1221/Ray-Tracer/assets/75140192/85e8f230-83bc-481c-912d-f8f035540d27" alt="Third Image" width="30%">
</p>

## Technologies Used

- **Programming Language**: C++
- **XML Parsing**: TinyXML for parsing scene descriptions from XML files.
- **Image Output**: SBT for writing rendered scenes to PNG files.

## Compilation Instructions
1. Navigate to the cmake-build-debug folder and open it in the terminal.
2. Use the command `./Lab_3` to run the program.
3. You will be prompted to provide the file path of the XML file you want to use. The scenes you can run are located in the "scenes" folder and contains 5 examples. 
    - Example XML File path:
        - `/home/andreig/Desktop/raytracer/scenes/example5.xml`
    - **Important**: the program assumes that the .obj files are also located in the *scenes* folder
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


