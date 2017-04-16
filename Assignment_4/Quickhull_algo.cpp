// Quickhull algo for finding the convex hull points
#include<bits/stdc++.h>
using namespace std;

struct Point{
	double x, y;
};

void print_point(Point p){
	cout<<p.x<<" "<<p.y<<endl;
}

// returns 2*area enclosed between three points: p, q and r
// or basically the absolute value of cross product of vectors p-q and q-r
int area(Point p, Point q, Point r){
	return abs( p.x*(q.y-r.y) + q.x*(r.y-p.y) + r.x*(p.y-q.y) );
}

// actually this will calculate the square of the distance
// of a point r from the line formed by joining points p and q
double cal_dis(Point p, Point q, Point r){
	double num,den;
	num = area(p, q, r);
	//den = pow(pow(p.x-q.x, 2) + pow(p.y-q.y, 2), 0.5);
	// no need to calculate the denominator part
	return num;
}

Point *convex_hull_set;
int h=0;

int get_sign(Point A, Point B, Point X){
	int sign = (A.y-B.y)*X.x + (B.x-A.x)*X.y + (B.y*A.x-A.y*B.x);
	if(sign>0) return 1;
	if(sign<0) return -1;
	return 0;
}

void FindHull(Point *point, int n, Point A, Point B){
	//print the set of points received
	/*cout<<"Set of points:\n";
	for(int i=0;i<n;i++) print_point(point[i]);
	cout<<endl;*/
	// find a point which is at maximum distance from the line
	if(n<=0) return;
	int index=0, max_dis, temp_dis;
	//cout<<"dist loop start\n";
	for(int i=0;i<n;i++){
		temp_dis = cal_dis(A, B, point[i]);
		//cout<<temp_dis<<endl;
		if(i==0) max_dis=temp_dis;
		else if(temp_dis > max_dis){
			max_dis = temp_dis;
			index = i;
		}
	}
	//cout<<"dist loop end\n";
	convex_hull_set[h++]=point[index];
	/*cout<<"New convex hull point: ";
	print_point(point[index]);*/
	// name it as Point C for simplicity in further use
	Point C = point[index];
	// Now points: A, B and C formed a triangle
	// eliminate points which are inside the triangle
	// and then solve recursively for two set of points
	// centroid will be a point that will always be inside a triangle
	// use this as refernce point
	Point G;
	G.x = (A.x + B.x + C.x)/3;
	G.y = (A.y + B.y + C.y)/3;
	int sign = get_sign(A, C, G);
	// this is for comparison
	// our point will be on the opposite side relative to this point
	Point *point_pos = new Point[n];
	Point *point_neg = new Point[n];
	int p=0, q=0;
	for(int i=0;i<n;i++){
		if(sign*get_sign(A,C,point[i]) < 0) point_pos[p++]=point[i];
	}
	sign = get_sign(B, C, G);
	for(int i=0;i<n;i++){
		if(sign*get_sign(B,C,point[i]) < 0) point_neg[q++]=point[i];
	}
	FindHull(point_pos, p, A, C);
	FindHull(point_neg, q, C, B);	
}

int main(){
	int n;
	cout<<"No. of points= ";
	cin>>n;
	Point *point = new Point[n];
	convex_hull_set = new Point[n];
	cout<<"Enter the description of "<<n<<" points:\n";
	int leftmost=0, rightmost=0;
	for(int i=0;i<n;i++){
		cin>>point[i].x>>point[i].y;
		if(point[i].x < point[leftmost].x) leftmost=i;
		if(point[i].x > point[rightmost].x) rightmost=i;
	}

	clock_t t;
	t=clock();
	// divide points in 2 sets
	Point *point_pos = new Point[n];
	Point *point_neg = new Point[n];
	// defining equation of line formed by joining leftmost and rightmost points
	// as Ay+Bx+C=0
	int A,B,C;
	A = point[leftmost].y - point[rightmost].y;
	B = -point[leftmost].x + point[rightmost].x;
	C = point[rightmost].y*point[leftmost].x - point[leftmost].y*point[rightmost].x;
	/*cout<<"The equation if the first line:\n";
	cout<<A<<"x+"<<B<<"y+"<<C<<"=0"<<endl;*/
	int p=0, q=0, val;
	for(int i=0;i<n;i++){
		if(i!=leftmost && i!=rightmost){
			val = A*point[i].x + B*point[i].y + C;
			if(val>0){
				point_pos[p++]=point[i];
			}
			if(val<0){
				point_neg[q++]=point[i];
			}
		}
	}
	
	convex_hull_set[h++] = point[leftmost];
	convex_hull_set[h++] = point[rightmost];

	/*cout<<"Convex hull set points:\n";
	for(int i=0;i<h;i++){
		print_point(convex_hull_set[i]);
	}*/
	FindHull(point_pos, p, point[leftmost], point[rightmost]);
	FindHull(point_neg, q, point[leftmost], point[rightmost]);
	t=clock()-t;

	cout<<"Convex hull set points:\n";
	cout<<"h="<<h<<endl;
	for(int i=0;i<h;i++){
		print_point(convex_hull_set[i]);
	}

	printf ("It took %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
	return 0;
}