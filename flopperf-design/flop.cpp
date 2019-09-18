#include<immintrin.h>
#include<iostream>
#include<omp.h>
#include<chrono>

using namespace std;

int main(int argc,char *argv[])
{
	//Initializations of variable datatypes
	long flops;
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
		//Initialized the 4 variables with packed single precision vector
		//Here, _mm256_set_ps sets packed single-precision (32-bit) floating-point elements
		__m256 b = _mm256_set_ps(0.1,0.9,0.6,0.1,0.4,0.1,0.1,0.2);

		__m256 c = _mm256_set_ps(0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1);

		__m256 e = _mm256_set_ps(0.1,0.9,0.6,0.1,0.4,0.1,0.1,0.2);

		__m256 f = _mm256_set_ps(0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1);
	
		__m256 x,y,v1,v2,v3,v4,v5,v6,v7,v8;
	
		//Here,_mm256_setzero_ps returns vector of type __m256 with all elements set to zero.
		x = _mm256_setzero_ps();
		
		y = _mm256_setzero_ps();
		num_threads = omp_get_num_threads();
		
		//Looping for maximum flops 
		//Loop unrolling is used with factor of 10 to decrease the conditional checks by factor of 10.
		for(uint64_t i=0;i<n;i=i+10){
			x = _mm256_fmadd_ps(x,b,c);
			y = _mm256_fmadd_ps(y,e,f);
			
			v1 = _mm256_fmadd_ps(x,b,c);
			v2 = _mm256_fmadd_ps(y,e,f);
			
			v3 = _mm256_fmadd_ps(x,b,c);
			v4 = _mm256_fmadd_ps(y,e,f);
			
			v5 = _mm256_fmadd_ps(x,b,c);
			v6 = _mm256_fmadd_ps(y,e,f);
			
			v7 = _mm256_fmadd_ps(x,b,c);
			v8 = _mm256_fmadd_ps(y,e,f);
			
			x = _mm256_fmadd_ps(x,b,c);
			y = _mm256_fmadd_ps(y,e,f);
			
			v1 = _mm256_fmadd_ps(x,b,c);
			v2 = _mm256_fmadd_ps(y,e,f);
			
			v3 = _mm256_fmadd_ps(x,b,c);
			v4 = _mm256_fmadd_ps(y,e,f);
			
			v5 = _mm256_fmadd_ps(x,b,c);
			v6 = _mm256_fmadd_ps(y,e,f);
			
			v7 = _mm256_fmadd_ps(x,b,c);
			v8 = _mm256_fmadd_ps(y,e,f);
			

		}
		cout << "\n Values of x:" << x[1];
	}
	end = chrono::system_clock::now();

	elapsed = end - start;
	//Flops = Number of threads * Number of FMA's possible * Float operations per FMA * Loop Count * Vector Capacity(Here 8 32-bit Numbers) 
	// Division of 1024 * 1024 is done to calculate the Float operations in Mega Float operations
	flops = num_threads * 2 * 2 * (n/10) * 8 /(1024*1024);
	
	//Division by time to calculate Floating operations per second
	flops = flops / (elapsed.count());
	
	cout<<"\nNumber of loops:"<<n/10;
	cout<<"\nNumber of Threads"<<num_threads;
	cout<<" \nExecution time for parallel Code:"<<elapsed.count();
	cout<<" \nNumber of Mega Flops "<<flops;
	cout<<" \nNumber of Giga Flops "<<flops/1024;
	return 0;
}
