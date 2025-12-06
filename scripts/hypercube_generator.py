def generate_hypercube_cpp_array(n):
    """
    Generates a C++ float array for the edges (GL_LINES) of an n-hypercube.
    Vertices range from -1.0 to 1.0 in each dimension.
    """
    num_vertices = 1 << n # 2^n
    
    # Helper function to convert vertex index integer to N-dimensional coordinates
    def get_coords_from_index(idx, dim):
        coords = []
        for i in range(dim):
            # Check if the i-th bit is set. 
            # If yes -> 1.0, If no -> -1.0
            if (idx >> i) & 1:
                coords.append(1.0)
            else:
                coords.append(-1.0)
        return coords

    edges = []
    # Iterate through all possible vertices
    for i in range(num_vertices):
        # Find neighbors by flipping bits one by one
        for bit_pos in range(n):
            # Create neighbor index by flipping the bit at bit_pos
            neighbor_idx = i ^ (1 << bit_pos)
            
            # Crucial step: Only add the edge if the current index 'i' is 
            # less than the neighbor index. This prevents adding the same 
            # edge twice (e.g., adding 0->1 and then later 1->0).
            if i < neighbor_idx:
                edges.append((i, neighbor_idx))

    num_edges = len(edges)

    # --- Format Output ---
    print(f"// {n}-Cube (Hypercube) Wireframe Pairs")
    print(f"// Dimension: {n}")
    print(f"// Total Vertices: {num_vertices}")
    print(f"// Total Edges: {num_edges}")
    # Calculate size: number of edges * 2 vertices per edge * N floats per vertex
    print(f"// Total Floats: {num_edges * 2 * n}") 
    print(f"float hypercubeVerts_{n}D[] = {{")

    for edge_idx, (v1_idx, v2_idx) in enumerate(edges):
        coords1 = get_coords_from_index(v1_idx, n)
        coords2 = get_coords_from_index(v2_idx, n)

        # Format as C++ float strings with 'f' suffix
        c1_str = ", ".join([f"{x: .4f}f" for x in coords1])
        c2_str = ", ".join([f"{x: .4f}f" for x in coords2])

        print(f"    // Edge {edge_idx + 1} (connects vertex {v1_idx} and {v2_idx})")
        print(f"    {c1_str},")
        print(f"    {c2_str},")
        print("") # Spacing

    print("};")

# ========= USAGE =========
# Change N here to generate for different dimensions.
# N=3 is a standard cube. N=4 is a Tesseract.
N = 3
generate_hypercube_cpp_array(N)
