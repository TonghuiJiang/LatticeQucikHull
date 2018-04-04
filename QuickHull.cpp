#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <assert.h>
#include <sstream>
#include <limits>
#include <fstream>
#include <string>
#include "Point2D.h"
          
using namespace std;

/*
 * Taken from https://en.wikipedia.org/wiki/Quickhull
 */ 


#define debug true

void PrintArray(vector<Point2D> &A)
{
  std::vector<Point2D>::iterator it;
  for (it=A.begin(); it != A.end(); ++it ) {
    cout << *it << " ";
  }
  cout << endl;
}

bool isLeft(Point2D a, Point2D b, Point2D c){
     return ((b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x)) > 0;
}
// formula for line ax+by+c = 0
void getLine(Point2D p1, Point2D p2, float &a, float &b, float &c)
{
    // (x- p1X) / (p2X - p1X) = (y - p1Y) / (p2Y - p1Y) 
    a = p1.y - p2.y;
    b = p2.x - p1.x;
    c = p1.x * p2.y - p2.x * p1.y;
}
/*
float distLinePoint(Point2D &p0, Point2D &p1, Point2D &p2)
{
    float a, b, c;
    getLine(p1, p2, a, b, c);
    float A
    return abs(a * p0.x + b * p0.y + c) / sqrt(a * a + b * b);
}
*/
/*
Note that each 3 points [a,b,p] for each p in the array form a trianle, 
whose area is denoted by: (ab) * h /2 [where h is the distance from p to ab].
Largest Triangle == greatest distance.
*/
float AreaOfTriangle(Point2D &p0, Point2D &p1, Point2D &p2)
{
  float area;
  //area=(1.0/2)* fabs((p1.x-p0.x)*(p2.y-p1.y) - (p1.x-p2.x)*(p0.y-p1.y));
  area = abs((p0.x*(p1.y-p2.y)+p1.x*(p2.y-p0.y)+p2.x*(p0.y-p1.y))/2.0);
  return area;
}

Point2D FurthestPoint(vector<Point2D> &S, Point2D &p1, Point2D &p2)
{
  Point2D ret = S[0];
  int remove = 0;
  //  float curdist = distLinePoint(ret, p1, p2);
  float curdist = AreaOfTriangle(ret, p1, p2);
  for (int i = 1; i < S.size(); i ++) 
 	{
    //    float tmp = distLinePoint(S[i], p1, p2);
    float tmp = AreaOfTriangle(S[i], p1, p2);
    if (tmp > curdist) 
   {
      ret = S[i];
      curdist = tmp;
      remove = i;
   }
    else if (tmp == curdist) 
   { 
     //In this case, 3 or more points can be parallel with line p1p2.
     int upFlag=0;
     int downFlag=0;
     for (int j=0; j < S.size(); j++)
     {
        if (S[j].x > ret.x) upFlag++;
        if (S[j].x < ret.x) downFlag++;
     }
     // ret is in the middle
     if (upFlag*downFlag != 0)
     {
        ret = S[i];
        curdist = tmp;
        remove = i;
     }
      
      /*when the xmin and xmax is downward diagonal,get rid of (3,2), (1,2) 
      if (p1.x==0&&p2.x==4&&S[i].y==2)
       {
	ret = S[i];
        curdist = tmp;
        remove = i;
       }
      //when the xmin and xmax is upward disgonal, get rid of (2,1), (2,3)
      if (p1.x==4&&p2.x==0&&S[i].x==2)
       {
        ret = S[i];
        curdist = tmp;
        remove = i;
       }
       */
   }
 }
  S.erase(S.begin()+ remove);

  return ret;
}  

Point2D GetMinX(vector<Point2D> &A)
{
  Point2D ret = A[0];
  int remove = 0;
  for (int i = 1; i < A.size(); i ++) {
    if (ret.x > A[i].x) {
      ret = A[i];
      remove = i;
    }
  }
  A.erase(A.begin()+ remove);
  return ret;
}

Point2D GetMaxX(vector<Point2D> &A)
{
  Point2D ret = Point2D(A[0]);
  int remove = 0;
  for (int i = 1; i < A.size(); i ++) {
    if (ret.x < A[i].x) {
      ret = A[i];
      remove = i;
    }
  }
  A.erase(A.begin()+remove);

  return ret;
}

void FindHull (vector<Point2D> Sk, vector<Point2D> &H, Point2D &P, Point2D &Q);

//2,2, 4,6, 6,2, 4,0 
/*
 *    Input = a set S of n points 
 * Assume that there are at least 2 points in the input set S of points
*/
void QuickHull(vector<Point2D> &S,vector<Point2D> &H)
{

  //Find left and right most points, say A & B, and add A & B to convex hull 

  Point2D A = GetMinX(S);
  Point2D B = GetMaxX(S);

  H.push_back(A);
  H.push_back(B);

  /*
   *  Segment AB divides the remaining (n-2) points into 2 groups S1 and S2 
   *  where S1 are points in S that are on the right side of the oriented line from A to B, 
   *  and S2 are points in S that are on the right side of the oriented line from B to A 
  */
  vector<Point2D> S1;
  vector<Point2D> S2;

  for (int i =0; i < S.size(); i++) {
      if (isLeft(A, B, S[i])) 
      {
				S2.push_back(S[i]);
      } 
      else 
      {
				S1.push_back(S[i]);
      }
  }
  FindHull (S1, H, A, B);
  FindHull (S2, H, B, A);
}

/* 
 * Find points on convex hull from the set Sk of points 
 * that are on the right side of the oriented line from P to Q
 */
void FindHull (vector<Point2D> Sk, vector<Point2D> &H, Point2D &P, Point2D &Q)
{
  /*
  cout << "Starting FindHull\n";
  cout << "H:  ";
  PrintArray(H);
  cout << "Sk: ";
  PrintArray(Sk);
  cout << P << Q << endl;
  */
  std::vector<Point2D>::iterator it;
  if (Sk.size() == 0) {
    return;
  }
  // From the given set of points in Sk, find farthest point, say C, from segment PQ 
  Point2D C = FurthestPoint(Sk, P, Q);
  //  Add point C to convex hull at the location between P and Q
  for (it = H.begin(); it != H.end(); ++it) {
    if (*it == Q&&AreaOfTriangle(P,C,Q)>0.01) {
      H.insert(it, C);
	/*if(AreaOfTriangle(P,C,Q)!=0)
		cout << AreaOfTriangle(P,C,Q) <<endl;
         	cout << "new point: ("<<C.x <<", "<<C.y<<")"<<endl;
*/
      break;
    }
  }
  /*
   * Three points P, Q, and C partition the remaining points of Sk into 3 subsets: S0, S1, and S2 
   * where S0 are points inside triangle PCQ, S1 are points on the right side of the oriented 
   * line from  P to C, and S2 are points on the right side of the oriented line from C to Q. 
  */

  //std::vector<Point2D> S0; //inside
  std::vector<Point2D> S1; //right
  std::vector<Point2D> S2; //left

  for (int i =0; i < Sk.size(); i++) 
  {
      if (isLeft(C, P, Sk[i])) 
      {
				S1.push_back(Sk[i]);
      } 
      else if (isLeft(Q, C, Sk[i])) 
      {
				S2.push_back(Sk[i]);
      } 
   } 
  FindHull(S1, H, P, C);
  FindHull(S2, H, C, Q);
}

//general
int test1()
{
  vector<Point2D> H;
  vector<Point2D> A
  {{3, 2}, {6, 3}, {2, 5}, {5, 2}, {1, 1}, {4, 4}}; 
  cout << "A: ";  PrintArray(A);
  QuickHull(A, H);
  cout << "H: ";  PrintArray(H);
}
void ReadData()
{
	ifstream fin("usefuldata.txt");
	const int LINE_LENGTH = 10;
	char str[LINE_LENGTH];
	float X[LINE_LENGTH];
  int numberofHulls=0;
	while (fin.getline(str, LINE_LENGTH))
	{
		for(int i=0;i<8;i++)
    {
	    X[i]=str[i]-48;
 	    //cout << X[i];
    }
		vector<Point2D> A	{{X[0], 1}, {X[1], 3}, {X[2], 0}, {X[3], 0}, {X[4], 2}, {X[5], 2}, {X[6], 4},{X[7], 4}}; 
		vector<Point2D> H;
    QuickHull(A, H);
                
                          
		if(H.size()==8) 
    {
			int index[5]={0};
			for(int i=0; i<8; i++)
			{
				index[(int)X[i]]++;
			}
			if(index[0]==3||index[1]==3||index[2]==3||index[3]==3||index[4]==3)
			{/*cout << "H: "; PrintArray(H);
         cout <<"size of H is : "<< H.size() <<endl;
         cout<<"xmin and xmax points are not in the hull." <<endl;*/
      }
			else 
			{
				numberofHulls = numberofHulls + 1;
				cout << "\n\n\n";
			  cout << "A without 1st 2 points:\n "; PrintArray(A);
       	cout << "H: "; PrintArray(H);
        cout <<"size of H is : "<< H.size() <<"\n\n\n";
			}
		}
  }
	cout << "The number of hulls: "<<numberofHulls <<endl;

	
}
	

int main(int argc, char * argv[])
{
  ReadData();

  
  return 0;
}
