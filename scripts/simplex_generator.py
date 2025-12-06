import numpy as np
import itertools

def generate_simplex_cpp_array(n):
    """
    Generates a C++ float array for the edges (GL_LINES) of a regular n-simplex.
    """
    # 1. Generate Regular Simplex Vertices in R^n
    # Start with standard basis in R^(n+1)
    base_verts = np.eye(n + 1)
    
    # Center the vertices at the origin
    mean = np.mean(base_verts, axis=0)
    centered_verts = base_verts - mean
    
    # Use SVD/Orthonormalization to rotate the simplex into the first n dimensions
    # and discard the (n+1)th dimension (which will be effectively 0)
    u, s, vh = np.linalg.svd(centered_verts.T)
    # The first n rows of u give us the coordinates in R^n
    final_verts = u[:, :n]

    # Scale edges to be roughly length 2.0 (like -1 to 1) for better visibility
    # The default edge length here is sqrt(2), so we scale by sqrt(2)
    final_verts = final_verts * np.sqrt(2)

    # 2. Generate Edges (Combinations of 2 vertices)
    # A simplex is a complete graph; every vertex connects to every other.
    indices = range(n + 1)
    edge_pairs = list(itertools.combinations(indices, 2))

    # 3. Print the C++ Array
    print(f"// Regular {n}-Simplex (Wireframe Pairs)")
    print(f"// Dimension: {n}")
    print(f"// Total Vertices: {len(final_verts)}")
    print(f"// Total Edges: {len(edge_pairs)}")
    print(f"float simplexVerts_{n}D[] = {{")

    for i, (idx1, idx2) in enumerate(edge_pairs):
        v1 = final_verts[idx1]
        v2 = final_verts[idx2]

        # Format Vertex 1
        v1_str = ", ".join([f"{x: .4f}f" for x in v1])
        # Format Vertex 2
        v2_str = ", ".join([f"{x: .4f}f" for x in v2])

        print(f"    // Edge {i+1}")
        print(f"    {v1_str},")
        print(f"    {v2_str},")
        print("") # Empty line for readability between pairs

    print("};")

# --- USAGE ---
# Change this number to generate for different dimensions
# 3 = Tetrahedron, 4 = Pentachoron, etc.
generate_simplex_cpp_array(3)
