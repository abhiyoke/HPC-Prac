#include<bits/stdc++.h>
#include<omp.h>

using namespace std;
int maxi(int arr[],int n){
	int ma=INT_MIN;
	#pragma omp parellel for reduction(max:ma)
	for(int i=0;i<n;i++) ma = max(ma,arr[i]);
	return ma;
}

int mini(int arr[],int n){
	int mi=INT_MAX;
	#pragma omp parellel for reduction(min:mi)
	for(int i=0;i<n;i++) mi=min(mi,arr[i]);
	return mi;
}

int sum(int arr[],int n){
	int s=0;
	#pragma omp parellel for reduction(+:s)
	for(int i=0;i<n;i++) s+=arr[i];
	return s;
}

int main(){
int n;
cin>>n;
int arr[n];
for(int i=0;i<n;i++) cin>>arr[i];
double start_time=omp_get_wtime();
cout<<"max is: "<<maxi(arr,n)<<endl;
cout<<"min is: "<<mini(arr,n)<<endl;
cout<<"sum is: "<<sum(arr,n)<<endl;
cout<<"Average is: "<<double(sum(arr,n))/n;
double end_time=omp_get_wtime();
cout<<"Time taken: "<<end_time<<endl;

return 0;
}
