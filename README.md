# rtv1

RTv1 is a simple ray tracing program. The project was developed as a part of 42 school program. It parses a 3D scene from a file and applies ray tracing algorithm to render the given scene.
This project is written for macOS (OS X High Sierra) using MinilibX graphic library (https://github.com/abouvier/minilibx) and it is needed to run this project

# Usage

```
git clone https://github.com/kmieshko/rtv1.git
cd rtv1
make
./RTv1 [scene file]
```

**Scene file example**:

```
Rotation
	Angle: 0, 0, 0
Camera
	Center: 0, 1, -10
Light
	Type: ambient
	Intensity: 0.1
	Center: 0, 0, 0
Light
	Type: point
	Intensity: 0.1
	Center: 0, 5, 0
Plane
	Center: 0, 0, 7
	Vector: 0, 0, -1
	Color: ffffff
	Specular: 10
Cylinder
	Radius: 1
	Center: 0, 0, 4
	Vector: 0, -1, 0
	Color: 00ffff
	Specular: 500
Sphere
	Radius: 1
	Center: 0, -1, 2
	Color: ff0000
	Specular: 100
Cone
	Tangle: 20
	Center: 0, 2, 3
	Vector: 1, 1, 0
	Color: ff00ff
	Specular: 300
```

# Bonuses

1. Multi-spots
2. Shine effect

# Some examples

# Disclaimer

This project is written according to 42's "The Norm" which specifies special rules for code like less then 25 lines in each function, 85 symbols in line, forbidden most of libraries and functions that wasn't written by you, also "for", "switch case" and others are forbidden (you can read more at https://ncoden.fr/datas/42/norm.pdf)
