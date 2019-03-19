# rtv_2.0

Same that [rtv1](https://github.com/kmieshko/rtv1#rtv1) but with next **update**:

1. New parser
2. New format of scene files
3. Added refraction, transparency and reflection of shapes
4. Project using SDL2 graphic library and it's needed to run this project

**Scene file example**:

```
Scene
{
	Rotation: 0, 30, 0
	Position: -10, 0, -10
	Recursion: 3
}
Light
{
	Type: ambient
	Intensity: 0.3
}
Light
{
	Type: point
	Intensity: 0.6
	Position: 0, 3, -1
}
Plane
{
	Position: 0, 0, 8
	Direction: 0, 0, 1
	Color: e9ed23
	Specular: 1
	Reflection: 0
}
Cone
{
	Angle: 15
	Position: 0, 0, 3
	Direction: 0, 1, 0
	Color: 6a6bca
	Specular: 100
	Reflection: 0
}
Sphere
{
	Position: -1, -1, 7
	radius: 3
	Color: 6ae9ca
	Specular: 300
	Reflection: 0
}
Cylinder
{
	Radius: 1
	Position: -2, 1, 5.5
	Direction: -1, 1, 0
	Color: ffc917
	Specular: 50
	Reflection: 0
}
```

# Some examples

<p align="center">
<img src="https://github.com/kmieshko/rtv1/blob/master/examples/reflect_coube.png" width=600>
<img src="https://github.com/kmieshko/rtv1/blob/master/examples/scene2.png" width=600>
<img src="https://github.com/kmieshko/rtv1/blob/master/examples/test2.png" width=600>
<img src="https://github.com/kmieshko/rtv1/blob/master/examples/transparency_coube.png" width=600>
</p>
