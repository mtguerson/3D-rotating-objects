# **3D Object Creation with OpenGL**

## **Authors**
- Rafael Eitaró Oshiro
- Matheus Tavares Guerson

## **Institution**
FACOM - Federal University of Mato Grosso do Sul (UFMS)

## **Contact**
- Email: rafael.oshiro@ufms.br, mathes.guerson@ufms.br

---

## **Project Summary**
This part of the project extends our work on 3D solid objects by incorporating advanced lighting models in OpenGL to enhance realism. It's a hands-on exploration of essential 3D graphics programming concepts, such as object rendering, shader application, and dynamic lighting techniques.

### **Features**
- Utilization of OpenGL in C/C++ for rendering 3D graphics.
- Support for various lighting models: Phong, Ambient, Diffuse, Specular.
- Implementation of custom shaders for detailed lighting and shading effects.

---

## **Directory Structure**
- **`bin/`**: Contains the executable file.
- **`lib/`**: Custom libraries for OpenGL manipulation in C.
- **`res/`**: Shaders storage.
- **`src/`**: Source code, including subfolders for rendering (`solid`) and environment setup (`world`).
- **`Makefile`**: Facilitates compilation with necessary flags.

---

## **Key Components**
- **3D Solids Rendering**: Procedures for initializing and animating objects with lighting effects.
- **Shader Management**: Detailed explanation of vertex and fragment shaders for 3D visual effects.
- **Lighting Techniques**: Exploration of different lighting calculations within shaders for realism.

---

## **How to Compile & Run**
Requires a Linux environment. WSL is recommended for Windows users.
- **Compile**: `make`
- **Execute**: `bin/main <LightingType>` (Options: `phong`, `diffuse`, `ambient`, `specular`)

---

## **Resources**
- **Demonstration Videos**: [Google Drive Folder](https://drive.google.com/drive/folders/1WJoXxdiw4_7xKSqT9ckI_p2-QyePpaz-?usp=drive_link)

---

## **Conclusion**
This project underscores the importance of shader programming in OpenGL for achieving dynamic and realistic lighting on 3D models. It serves as a practical introduction to the fundamentals of graphical programming and computer graphics.

---

Feel free to reach out via email for any queries or further information. Enjoy exploring the world of 3D graphics with us!
