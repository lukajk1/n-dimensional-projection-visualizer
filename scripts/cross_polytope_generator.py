import numpy as np
import itertools

def generate_cross_polytope(dimensions):
    """
    Generate vertex data for an N-dimensional cross-polytope.

    A cross-polytope in N dimensions has 2N vertices positioned at
    ±1 on each coordinate axis. It has N(2N-2) edges.
    """

    # Generate vertices: 2N vertices, one positive and one negative on each axis
    vertices = []
    for axis in range(dimensions):
        # Positive vertex on this axis
        pos_vertex = [0.0] * dimensions
        pos_vertex[axis] = 1.0
        vertices.append(pos_vertex)

        # Negative vertex on this axis
        neg_vertex = [0.0] * dimensions
        neg_vertex[axis] = -1.0
        vertices.append(neg_vertex)

    # Generate edges: connect each vertex to all others except its opposite
    edges = []
    num_vertices = len(vertices)

    for i in range(num_vertices):
        for j in range(i + 1, num_vertices):
            # Check if vertices i and j are opposites
            # Opposites have all coordinates negated (i and i^1 when indexed as 0,1,2,3,...)
            # Even indices are positive, odd are negative on same axis
            # So i and j are opposite if they differ by 1 and i is even
            if not (j == i + 1 and i % 2 == 0):
                edges.append((i, j))

    # Convert to wireframe format (GL_LINES pairs)
    wireframe_vertices = []
    for edge in edges:
        v1_idx, v2_idx = edge
        wireframe_vertices.append(vertices[v1_idx])
        wireframe_vertices.append(vertices[v2_idx])

    return wireframe_vertices, len(wireframe_vertices), len(vertices), len(edges)

def format_vertex_array(vertices, dimensions, dimension_name):
    """Format vertices as C++ array initializer."""
    output = []
    output.append(f"// Regular {dimension_name}-Cross-Polytope (Wireframe Pairs)")
    output.append(f"// Dimension: {dimensions}")
    output.append(f"// Total Vertices: {len(vertices) // 2}")  # Divide by 2 since wireframe duplicates
    output.append(f"// Total Edges: {len(vertices) // 2}")     # Each edge = 2 vertices in wireframe
    output.append(f"float crossPolytopeVerts_{dimensions}D[] = {{")

    for i, vertex in enumerate(vertices):
        # Format vertex coordinates
        coords = ", ".join([f"{coord:.4f}f" for coord in vertex])

        # Add comma except for last vertex
        if i < len(vertices) - 1:
            output.append(f"    {coords},")
        else:
            output.append(f"    {coords}")

    output.append("};")
    return "\n".join(output)

# Generate cross-polytopes for dimensions 2-8
if __name__ == "__main__":
    print("// Cross-Polytope Vertex Data")
    print("// Generated using cross_polytope_generator.py\n")

    for dim in range(2, 9):
        wireframe_verts, total_verts, num_base_verts, num_edges = generate_cross_polytope(dim)

        # Dimension names
        dim_names = {2: "2", 3: "3", 4: "4", 5: "5", 6: "6", 7: "7", 8: "8"}

        print(format_vertex_array(wireframe_verts, dim, dim_names[dim]))
        print()

        # Print statistics
        print(f"// Stats: {num_base_verts} vertices, {num_edges} edges, {total_verts} wireframe vertices")
        print()
