#include<bits/stdc++.h>
using namespace std;
#define vi vector<int>
class SegmentTree{
	vi st, A;
	int n;
	int left (int p) { return p << 1; }
	int right(int p) { return (p << 1) + 1; }
	
	void build(int p, int L, int R)
	 { 
		if (L == R)
		st[p] = L;
		else
		{ 
			build(left(p) , L , (L + R) / 2);
			build(right(p), (L + R) / 2 + 1, R );
	
			int p1 = st[left(p)], p2 = st[right(p)];
			st[p] = (A[p1] <= A[p2]) ? p1 : p2;
		}
	}
	int rmq(int p, int L, int R, int i, int j)
	{
		if (i > R || j < L) return -1;
		if (L >= i && R <= j) return st[p];
	int p1 = rmq(left(p) , L , (L+R) / 2, i, j);
	int p2 = rmq(right(p), (L+R) / 2 + 1, R , i, j);
		if (p1 == -1) return p2;
		if (p2 == -1) return p1;
	return (A[p1] <= A[p2]) ? p1 : p2;
	}
	
        void update(int node, int start, int end, int idx, int val)// this function not tested
        {
           if(start == end)
           {
              A[idx] = val;
              st[node] = start;
           }
           else
    	   {
               if(start <= idx && idx <= mid)
                {
                  update(left(node), start, (start + end) / 2, idx, val);
                }
               else
                {
                  update(right(node), (start + end) / 2+1, end, idx, val);
                }
            int p1 = st[left(node)], p2 = st[right(node)];
            st[node] = (A[p1] <= A[p2]) ? p1 : p2;
         }
       }

	public:
	SegmentTree(const vi &_A) {
		A = _A; n = (int)A.size(); 
		st.assign(4 * n, 0); 
		build(1, 0, n - 1); 
	}
	int rmq(int i, int j) { return rmq(1, 0, n - 1, i, j); }
        void update(int idx,int val) { update(1,0,n-1,idx,val);}
	
};

int main(){
  int arr[] = { 18, 17, 13, 19, 15, 11, 20 };
  vi A(arr, arr + 7);

  SegmentTree st(A);
  printf("RMQ(1, 3) = %d\n", st.rmq(1, 3)); // answer = index 2
  printf("RMQ(4, 6) = %d\n", st.rmq(4, 6)); // answer = index 5
}
