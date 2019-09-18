#include<immintrin.h>
#include<iostream>
#include<omp.h>
#include<chrono>

using namespace std;

int main(int argc,char *argv[])
{
	//Initializations of variable datatypes
	long iops;
	int num_threads;
	uint64_t n;
 	chrono::time_point<std::chrono::system_clock> start, end;
	chrono::duration<double> elapsed;
	 
	//Number of loops
	n = 1000000000;
	//Using Chrono for measuring the running time of the code 
	start = chrono::system_clock::now();
	//Implementation of Parallelization of code to multiple threads 
#pragma omp parallel 
	{
		//Initialized the 8 variables with packed single precision vector
		//Here, _mm256_setr_epi32 sets packed 32-bit integers in dst with the supplied values in reverse order.
		//here, returns vector of type __m256i with all elements set to zero.
		__m256i b = _mm256_setr_epi32(1,2,1,2,1,2,1,2);
		__m256i a = _mm256_setzero_si256();
		__m256i d = _mm256_setr_epi32(2,1,2,1,2,1,2,1);
		__m256i c = _mm256_setzero_si256();
		__m256i e = _mm256_setr_epi32(1,2,1,2,1,2,1,2);
		__m256i f = _mm256_setzero_si256();
		__m256i g = _mm256_setr_epi32(2,1,2,1,2,1,2,1);
		__m256i h = _mm256_setzero_si256();
	
		__m256i v1,v2,v3,v4;
	

		num_threads = omp_get_num_threads();
		
		//Looping for maximum Iops 
		//Loop unrolling is used with factor of 10 to decrease the conditional checks by factor of 10.
		for(uint64_t i=0;i<n;i=i+10){
		
			a = _mm256_add_epi32(a,b);
		
			c = _mm256_add_epi32(c,d);

		
			e = _mm256_add_epi32(e,f);
		
			f = _mm256_add_epi32(g,h);

		
			a = _mm256_add_epi32(a,b);
		
			c = _mm256_add_epi32(c,d);
			

			e = _mm256_add_epi32(e,f);
		
			f = _mm256_add_epi32(g,h);;
			

			a = _mm256_add_epi32(a,b);
		
			c = _mm256_add_epi32(c,d);
			
		
			e = _mm256_add_epi32(e,f);
		
			f = _mm256_add_epi32(g,h);
			
			
			a = _mm256_add_epi32(a,b);
		
			c = _mm256_add_epi32(c,d);
			

			e = _mm256_add_epi32(e,f);
		
			f = _mm256_add_epi32(g,h);;
			

			a = _mm256_add_epi32(a,b);
		
			c = _mm256_add_epi32(c,d);
			
		
			e = _mm256_add_epi32(e,f);
		
			f = _mm256_add_epi32(g,h);

		}
		cout<<"\nvalues of v1:["<<a[1]<<"]";
	}
	end = chrono::system_clock::now();

	elapsed = end - start;
	//Iops = Number of threads * Number of Vector Integer instructions * Integer operations per instruction * Loop Count * Vector Capacity(Here 8 32-bit integer Numbers) 
	// Division of 1024 * 1024 is done to calculate the Integer operations in Mega Integer operations
	iops = num_threads * 1 * 2 * (n/10)*8 /(1024*1024);
	
	// Scalar integer operations for incrementing and the conditional Branching are also considered
	iops += num_threads * 2 * (n/10)/(1024*1024) ;
	
	//Division by time to calculate Integer operations per second
	iops = iops / (elapsed.count());
	
	cout<<"\nNumber of loops:"<<n/10;
	cout<<"\nNumber of Threads"<<num_threads;
	cout<<" \nExecution time for parallel Code:"<<elapsed.count();
	cout<<" \nNumber of Mega Iops "<<iops;
	cout<<" \nNumber of Giga Iops "<<iops/1024;
	return 0;
}
