/*
 <Mix-mesher: region type. This program generates a mixed-elements mesh>
 
 Copyright (C) <2013,2017>  <Claudio Lobos>
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/gpl.txt>
 */

#include "RemoveSubElementsVisitor.h"
#include "../Octant.h"

namespace Clobscode
{

    RemoveSubElementsVisitor::RemoveSubElementsVisitor():points(NULL)
    { }

    void RemoveSubElementsVisitor::setPoints(vector<MeshPoint> &points) {
        this->points = &points;
    }

    void RemoveSubElementsVisitor::setTriMesh(TriMesh &mesh) {
        this->mesh = &mesh;
    }

    bool RemoveSubElementsVisitor::visit(Octant *o) {
        // Mine
        vector<vector<unsigned int>> &sub_elements = o->sub_elements;
        list<unsigned int> intersected_faces = o->intersected_faces;

        list<vector<unsigned int> > still_in;
        list<vector<unsigned int> >::iterator iter;

        for (unsigned int i=0; i<sub_elements.size(); i++) {

            bool onein = false;
            vector<unsigned int> e_pts = sub_elements[i];

            Point3D centroid_pt;

            for (unsigned int j=0; j<e_pts.size(); j++) {
                centroid_pt += points->at(e_pts[j]).getPoint();

                if (points->at(e_pts[j]).isInside()) {
                    onein = true;
                    break;
                }
            }

            centroid_pt = centroid_pt / e_pts.size();

            if (onein) {
                //o->setSurface();
                still_in.push_back(sub_elements[i]);
            } else{
                // If centroid point is inside the mesh
                // this cover the case where all points are marked as outside but the centroid is inside
                if (mesh->pointIsInMesh(centroid_pt, intersected_faces) && true) { 
                    still_in.push_back(sub_elements[i]);
                } 
                // else{
                //     // Other points near centroid
                //     for (unsigned int j=0; j<e_pts.size(); j++) {
                //         cout << "Other point near centroid check" << endl;
                //         Point3D p = points->at(e_pts[j]).getPoint();

                //         Point3D midpoint = (p + centroid_pt) / 2.0;
                //         if (mesh->pointIsInMesh(midpoint, intersected_faces)) {
                //             still_in.push_back(sub_elements[i]);
                //             break;
                //         }
                //     }
                // }
            }
        }

        if (still_in.size()==sub_elements.size()) {
            return false;
        }
        if (still_in.empty()) {
            return true;
        }

        sub_elements.clear();
        sub_elements.reserve(still_in.size());
        for (iter=still_in.begin(); iter!=still_in.end(); iter++) {
            sub_elements.push_back(*iter);
        }
        return false;
    }
}