#include<bits/stdc++.h>
#include<omp.h>

using namespace std;

void parellel_bubble(int a[],int n){
	for(int i=0;i<n;i++){
		int first=i%2;
		#pragma omp parellel for num_threads(16)
		for(int j=first;j<n-1;j+=2){
			if(a[j]>a[j+1]) swap(a[j],a[j+1]);
		}
	}
}

void merge(int a[],int l,int mid,int h){
	int n1=mid-l+1;
	int n2=h-mid;
	int left[n1],right[n2];
	
	for(int i=0;i<n1;i++) left[i]=a[l+i];
	for(int j=0;j<n2;j++) right[j]=a[mid+1+j];
	
	int i=0,j=0,k=0;
	while(i<n1 && j<n2){
		if(left[i]<=right[j]){
			a[k]=left[i];
			k++;
			i++;
		}
		else {
		a[k]=right[j];
		k++;
		j++;
		}
	}
	while(i<n1) a[k++]=left[i++];
	while(j<n2) a[k++]=right[j++];
	
}

void parellel_merge(int a[],int l,int h){
	if(l<h){
	int mid=(l+h)/2;
	
	#pragma omp parallel sections
	{
		#pragma omp section
		parellel_merge(a,l,mid);
		
		#pragma omp section 
		parellel_merge(a,mid+1,h);
	}
	
	merge(a,l,mid,h);
	}
	
}


int main(){
int n;
cin>>n;
int a[n],b[n];
for(int i=0;i<n;i++) {
int x;
cin>>x;
a[i]=x;
b[i]=x;
}

double start_time=omp_get_wtime();
parellel_bubble(a,n);
double end_time=omp_get_wtime();
cout<<"time taken: "<<end_time-start_time<<endl;

double start_t=omp_get_wtime();
parellel_merge(b,0,n-1);
double end_t=omp_get_wtime();
cout<<"time taken: "<<end_time-start_time<<endl;

return 0;
}







