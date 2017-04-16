// Gift wrapping algorithm for finding the convex hull points
// Assuming n is greater than 3
#include<bits/stdc++.h>
using namespace std;

struct Point{
	int x, y;
};

void print_point(Point p){
	cout<<p.x<<" "<<p.y<<endl;
}

// clockwise: return -1
// anti-clockwise: return 1
// collinear: return 0
int orientation(Point a, Point b, Point c){
	int temp = a.x*(b.y-c.y) + b.x*(c.y-a.y) + c.x*(a.y-b.y);
	if(temp>0) return 1;
	if(temp<0) return -1;
	return 0;
}

int main(){
	int n;
	cout<<"No. of points= ";
	cin>>n;
	Point *point = new Point[n];
	cout<<"Enter the description of "<<n<<" points:\n";
	for(int i=0;i<n;i++){
		cin>>point[i].x>>point[i].y;
	}

	clock_t t;
	t=clock();
	Point *convex_hull_set = new Point[n];
	int h=0;
	
	// find the left-most point
	int l=0;
	for(int i=1;i<n;i++){
		if(point[i].x < point[l].x){
			l=i;
		}
	}
	//start from the leftmost point, keep moving clockwise
	//until we reach the start point again.
	int p=l, q;
	do{
		convex_hull_set[h++]=point[p];
		//find a point q which is most clockwise than all others
		//assume some point q and replace a more clockwise point found
		q=(p+1)%n;
		//cout<<"loop start\n";
		for(int i=0;i<n;i++){
			if(orientation(point[p], point[i], point[q]) == -1) q=i;
			//cout<<q<<" ";
		}
		//cout<<" loop end\n";
		//Now q is the most clockwise w.r.t. p
		// set p as q for next iteration
		p=q;
	}while(p!=l); 	//while we don't ome to the first point

	t=clock()-t;
	cout<<"Convex hull set points:\n";
	cout<<"h="<<h<<endl;
	for(int i=0;i<h;i++){
		print_point(convex_hull_set[i]);
	}

	printf ("It took %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
	return 0;
}