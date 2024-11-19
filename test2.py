import pyvista as pv
import numpy as np

points = []

with open("points.txt", "r") as f:
	for line in f:
		points.append([float(x) for x in line.split()])

points = np.array(points)

candidate_split_points = []

with open("candidate_split_points.txt", "r") as f:
	for line in f:
		candidate_split_points.append(int(line))

candidate_split_points = np.array(candidate_split_points)

# # Get points indices with x > 5.0
# X_LIMIT = 5.0
# indices = np.where(points[:, 0] > X_LIMIT)[0]

# Create a PyVista plotter for interactive visualization
plotter = pv.Plotter()

# Add points to the plotter
points_to_plot = points #[indices]
plotter.add_points(points_to_plot, color="green", point_size=7.0, render_points_as_spheres=True)

# other_points = points[np.where(points[:, 0] <= X_LIMIT)[0]]
# plotter.add_points(other_points, color="blue", point_size=5.0, render_points_as_spheres=True)

points_to_split = points[candidate_split_points]
plotter.add_points(points_to_split, color="yellow", point_size=9.0, render_points_as_spheres=True)

# points_to_split_c = points[candidate_split_points]
# x_greater_than_5 = points_to_split_c[:, 0] > 5.0
# points_to_split_c = points_to_split_c[x_greater_than_5]
# original_indices = np.array(candidate_split_points)[x_greater_than_5]
# plotter.add_points(points_to_split_c, color="yellow", point_size=5.0, render_points_as_spheres=True)

# print("Points to Split:\n", points_to_split_c)
# print("Original Indices of Points that meet the criteria:", original_indices)

# # Add labels for each point showing its index
# for i, point in enumerate(candidate_split_points):
# 	plotter.add_point_labels(points[point], [str(point)], font_size=10, text_color="yellow")

plotter.add_point_labels(points[5144], ["5144"], font_size=10, text_color="yellow")

# Set the initial camera orientation
plotter.view_vector([0, 0, 1])  # Set Z-axis to point out of the screen
plotter.camera.up = [0, 1, 0]   # Set Y-axis to point up

# Set plotter settings
plotter.show_axes()  # Show 3D axes
plotter.background_color = "white"

# Render the plot interactively
plotter.show()
