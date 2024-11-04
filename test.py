import numpy as np
import plotly.graph_objects as go

# Function to plot 3D points with Plotly, including index labels
def plot_3d_points_with_labels(points):
    # Calculate the centroid of the points
    centroid = np.mean(points, axis=0)

    # Center points around the centroid
    points_centered = points - centroid

    # Create text labels with point indices
    labels = [f"Point {i}" for i in range(len(points))]

    # Create a 3D scatter plot with labels
    fig = go.Figure(data=[go.Scatter3d(
        x=points_centered[:, 0],
        y=points_centered[:, 1],
        z=points_centered[:, 2],
        mode='markers+text',
        marker=dict(size=5, color='blue'),
        text=labels,               # Add labels for each point
        textposition="top center"  # Position labels above points
    )])

    # Set the layout for better visualization
    fig.update_layout(
        scene=dict(
            xaxis_title='X',
            yaxis_title='Y',
            zaxis_title='Z'
        ),
        title="3D Points Centered on Centroid with Labels",
    )

    # Show the plot
    fig.show()

# Sample input of 3D points
# points = np.array([
#     [1, 2, 3],
#     [4, 5, 6],
#     [7, 8, 9],
#     [2, 3, 5],
#     [6, 7, 8]
# ])

import numpy as np

points = []

with open("points.txt", "r") as f:
	for line in f:
		points.append([float(x) for x in line.split()])

points = np.array(points)
# print(points)
# print(points.shape)

plot_3d_points_with_labels(points)