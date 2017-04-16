// Graham scan algorithm for finding the convex hull points
// Assuming the input size is greater than 3
#include<bits/stdc++.h>
using namespace std;

struct Point{
	int x, y;
	double slope;
	int quad, dist;
};

void print_point(Point p){
	cout<<p.x<<" "<<p.y<<endl;
}

double get_slope(Point p1, Point p2){
	double num, den;
	num = p2.y - p1.y;
	den = p2.x - p1.x;
	if(den!=0) return num/den;
	else{
		if(num==0) return 0;
		if(num<0) return -DBL_MAX;
		return DBL_MAX;
	}
}

// actually this will calculate the square of the distance
int cal_dis(Point p, Point q){
	return pow(p.x-q.x, 2) + pow(p.y-q.y, 2);
}

void swap(Point& p, Point& q){
	Point temp;
	temp=p;
	p=q;
	q=temp;
}

bool cmp(Point p, Point q){
	if(p.quad != q.quad) return p.quad < q.quad;
	if(p.slope == q.slope){
		return p.dist < q.dist;
	}
	return p.slope < q.slope;
}

int orientation(Point p, Point q, Point r){
	int val = (q.x-p.x)*(r.y-q.y)-(r.x-q.x)*(q.y-p.y);
	if(val>0) return 1;
	if(val==0) return 0;
	return -1;
}

int main(){
	int n;
	cout<<"No. of points= ";
	cin>>n;
	Point *point = new Point[n];
	cout<<"Enter the description of "<<n<<" points:\n";

	Point *convex_hull_set = new Point[n];
	for(int i=0;i<n;i++){
		cin>>point[i].x>>point[i].y;
	}

	clock_t t;
	t=clock();
	int h=0;
	int *traversed;
	traversed = new int[n];
	for(int i=0;i<n;i++){
		traversed[i]=0;
		//cin>>point[i].x>>point[i].y;
		if(i!=0){
			if(point[i].y < point[0].y){
				swap(point[i], point[0]);
			}
			else if(point[i].y == point[0].y){
				if(point[i].x < point[0].x){
					swap(point[i], point[0]);

				}
			}
		}
	}
	point[0].slope = 0;
	point[0].quad = 1;
	point[0].dist = 0;

	//cout<<"slope wali for loop start\n";
	for(int i=1;i<n;i++){
		point[i].slope=get_slope(point[0], point[i]);
		//print_point(point[i]);
		//cout<<point[i].slope<<endl<<endl;
		if(point[i].slope < 0) point[i].quad = 2;
		else point[i].quad = 1;
		point[i].dist = cal_dis(point[i], point[0]);
	}
	//cout<<"loop end"<<endl;
	sort(point, point+n, cmp);
	
	/*cout<<"Sorted data set:\n";
	for(int i=0;i<n;i++) print_point(point[i]);
	cout<<endl;*/
	
	//remove the points with same slope except one.
	Point *modified_list = new Point[n];
	int m=1;
	modified_list[0] = point[0];
	for(int i=1;i<n-1;i++){
		if(point[i].slope != point[i+1].slope) modified_list[m++]=point[i];
	}
	modified_list[m++]=point[n-1];

	/*cout<<"Modified data set:\n";
	for(int i=0;i<m;i++) print_point(modified_list[i]);
	cout<<endl;*/

	convex_hull_set[0]=modified_list[0];
	convex_hull_set[1]=modified_list[1];
	h=2;

	for(int i=2;i<m;i++){
		int direction = orientation(convex_hull_set[h-2], convex_hull_set[h-1], modified_list[i]);
		if(direction == 1) convex_hull_set[h++]=modified_list[i];
		else{
			convex_hull_set[h-1]=modified_list[i];
			while(direction != 1){
				direction = orientation(convex_hull_set[h-3], convex_hull_set[h-2], convex_hull_set[h-1]);
				if(direction !=1 ){
					convex_hull_set[h-2] = convex_hull_set [h-1];
					h--;
				}
			}
		}
		/*cout<<"Convex hull set points:\n";
		cout<<"h="<<h<<endl;
		for(int i=0;i<h;i++){
			print_point(convex_hull_set[i]);
		}*/
	}
	t=clock()-t;
	cout<<"Convex hull set points:\n";
	cout<<"h="<<h<<endl;
	for(int i=0;i<h;i++){
		print_point(convex_hull_set[i]);
	}

	printf ("It took %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
	return 0;
}