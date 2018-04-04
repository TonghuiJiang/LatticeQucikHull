#Latttice  Polygon Quickhull
A lattice (d,k)-polytope is the convex hull of a set of points in dimension d whosecoordinates are integers between 0 and k. In R^2, d is equal to 2 and the lattice polytopes are polygons. Let D(2,k) be the largest diameter of all lattice polygons and D(2,k)=k when k=4, 5 and 6. Let F(2, k) denote polygons having the largest diameter of different k. This project provides a computational framework based on the quickhull algorithm to verify F(2, k) for small instances. We verify that the number of elements in set F(2, 4)=335, F(2, 5)=92 and F(2, 6)=4 respectively by our algorithm within minutes; that is, our algorithm has the capacity to finnd out F(2, k) for a given k.

This is a demo of my project, computation algorithm of F(2, 4) with 8 vertices. In the 4\*4 grid, D(2, 4)=4. 

Hulls have 8 vertices, located at 5 horizontal lines: there are three horizontal lines having two vertices and two horizontal lines holding one vertex. Thus, there are Combination(5, 2) selections. In this example, line 1 and 3 only have one vertex, these 8 vertices should be (\*, 0), (\*, 0), (\*, 1), (\*, 2), (\*, 2), (\*, 3), (\*, 4), (\*, 4).

There are 36 hulls satisfying the rule in the output.