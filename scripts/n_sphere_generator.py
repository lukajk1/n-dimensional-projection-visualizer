import numpy as np
import math

def generate_hypersphere_vertices(count, dimension):
    """
    Generates 'count' vertices evenly distributed on a 'dimension'-dimensional sphere.
    
    - 2D: Uses Golden Angle (Fibonacci) on a circle.
    - 3D: Uses Standard Fibonacci Sphere algorithm.
    - nD: Uses Gaussian Normalization (standard uniform distribution for hyperspheres).
    """
    vertices = []
    
    # Constants
    phi = (1 + math.sqrt(5)) / 2  # Golden Ratio
    
    if dimension == 2:
        # 2D Case: Points on a Circle (1-Sphere) using Golden Angle
        golden_angle = 2 * math.pi * (1 - 1/phi)
        for i in range(count):
            theta = i * golden_angle
            x = math.cos(theta)
            y = math.sin(theta)
            vertices.append([x, y])
            
    elif dimension == 3:
        # 3D Case: Standard Fibonacci Sphere Algorithm
        golden_angle = 2 * math.pi * (1 - 1/phi)
        for i in range(count):
            # y goes from 1 to -1
            y = 1 - (i / float(count - 1)) * 2
            
            # Radius at y
            radius = math.sqrt(1 - y * y)
            
            theta = golden_angle * i
            
            x = math.cos(theta) * radius
            z = math.sin(theta) * radius
            
            vertices.append([x, y, z])
            
    else:
        # nD Case: Gaussian Normalization (Muller's Method)
        # This is the standard method for uniform points on an N-sphere
        # as the Fibonacci lattice does not generalize simply to N > 3.
        
        # Generate random points from a normal distribution
        # Note: We use a fixed seed for deterministic output (optional)
        np.random.seed(42) 
        random_points = np.random.normal(0, 1, (count, dimension))
        
        # Normalize each vector to lie on the unit hypersphere
        norms = np.linalg.norm(random_points, axis=1)
        vertices = random_points / norms[:, np.newaxis]
        
        return vertices.tolist()

    return vertices

# --- Usage Example ---
if __name__ == "__main__":
    # Example: 100 points in 4 Dimensions
    points_4d = generate_hypersphere_vertices(100, 4)
    
    # Example: 10 points in 3 Dimensions (Fibonacci)
    points_3d = generate_hypersphere_vertices(10, 3)

    print(f"Generated {len(points_4d)} points in 4D.")
    print(f"First 3D point: {points_3d[0]}")
