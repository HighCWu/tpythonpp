def test():
	print('hello world')
	v = vec2(1.1, 2.2)
	print(v)
	print(v.x)
	print(v.y)
	v.x = 99
	print(v.x)
	v.y += 400
	print(v.y)
	ratio = v.aspect()
	print(ratio)
	print(v.length())
	v2 = v.normalized()
	print(v2)
	print(v2.angle())
	v3 = v + v2
	print(v3)

test()