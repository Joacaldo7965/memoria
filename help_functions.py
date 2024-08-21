import numpy as np

def get_tri(a, b, c, d):
    return (a, b, c), (c, d, a)

def read_off(filename):
    # Read vertex list from and .off file

    vertices = []
    vertices_count = 0

    faces_info = []

    with open(filename, 'r') as f:
        #return f.readlines()
        for i, line in enumerate(f.readlines()):
            line = line.strip()
            if i == 0:
                if line != 'OFF':
                    raise ValueError('Not an OFF file')
                continue
            elif i == 1:
                n_vertex, n_face, _ = map(int, line.split())
                continue

            if line == '':
                continue
            if line.startswith('#'):
                continue

            if vertices_count < n_vertex:
                vertices.append(list(map(float, line.split())))
                vertices_count += 1
            # TODO: Read faces
            else:
                faces_info.append(list(map(int, line.split())))
        return np.array(vertices), faces_info

def rotate_vertex(vertices, angle):
    # Rotate vertices around the z-axis
    # Angle in degrees

    angle = np.radians(angle)
    rotation_matrix = np.array([
        [np.cos(angle), -np.sin(angle), 0],
        [np.sin(angle), np.cos(angle), 0],
        [0, 0, 1]
    ])

    return np.dot(vertices, rotation_matrix)

def write_vertex(vertices, faces_info, filename):
    with open(filename, 'w') as f:
        f.write('OFF\n')
        f.write(f'{len(vertices)} {len(faces_info)} 0\n')
        for vertex in vertices:
            f.write(' '.join(map(str, vertex)) + '\n')
        for face in faces_info:
            f.write(' '.join(map(str, face)) + '\n')