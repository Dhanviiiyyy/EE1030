import ctypes
import matplotlib.pyplot as plt
func=ctypes.CDLL('./findK.so')

func.findK_a.argtypes = [ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int]
func.findK_a.restype = ctypes.c_float

func.findK_b.argtypes = [ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int]
func.findK_b.restype = ctypes.c_float

x1a, y1a = 7, -2
x2a, y2a = 5, 1
x3a = 3
ka = func.findK_a(x1a, y1a, x2a, y2a, x3a)

x1b, y1b = 8, 1
x3b, y3b = 2, -5
y2b = -4
kb = func.findK_b(x1b, y1b, y2b, x3b, y3b)

print(f"The value of k for case (a) is: {ka:.2f}")
print(f"The value of k for case (b) is: {kb:.2f}")

x_a = [x1a, x2a, x3a]
y_a = [y1a, y2a, ka]
x_b = [x1b, kb, x3b]
y_b = [y1b, y2b, y3b]
plt.figure(figsize=(10, 5))

plt.subplot(1, 2, 1)
plt.plot(x_a, y_a, 'bo-', label='Case (a)')
plt.scatter(x_a, y_a, color='red')
plt.title("Case (a): Collinear Points")
plt.xlabel('x')
plt.ylabel('y')

plt.text(x1a, y1a, f'A({x1a},{y1a})')
plt.text(x2a, y2a, f'B({x2a},{y2a})')
plt.text(x3a, ka, f'C({x3a},{ka:.2f})')

plt.subplot(1, 2, 2)
plt.plot(x_b, y_b, 'go-', label='Case (b)')
plt.scatter(x_b, y_b, color='red')
plt.title("Case (b): Collinear Points")
plt.xlabel('x')
plt.ylabel('y')

plt.text(x1b, y1b, f'A({x1b},{y1b})')
plt.text(kb, y2b, f'B({kb:.2f},{y2b})')
plt.text(x3b, y3b, f'C({x3b},{y3b})')

plt.tight_layout()
plt.show()

