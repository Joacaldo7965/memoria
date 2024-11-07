import numpy as np

# Example 3D coordinates array
coordinates = np.random.rand(10, 3) * 10  # random points with shape (n, 3)
# List of indices to filter
indices = [0, 1, 2, 5, 7]  # Example list of indices

# Step 1: Filter points by indices
filtered_points = coordinates[indices]

# Step 2: Apply x-coordinate filter (x > 5.0)
x_greater_than_5 = filtered_points[:, 0] > 5.0
filtered_points = filtered_points[x_greater_than_5]

# Step 3: Get the indices in the original array
original_indices = np.array(indices)[x_greater_than_5]

# Output the result
print("Filtered Points:\n", filtered_points)
print("Original Indices of Points that meet the criteria:", original_indices)
