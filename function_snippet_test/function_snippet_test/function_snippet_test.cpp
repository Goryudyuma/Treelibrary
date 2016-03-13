// function_snippet_test.cpp : メイン プロジェクト ファイルです。

#include "stdafx.h"


#ifndef _GLIBCXX_NO_ASSERT
#include <cassert>
#endif
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#if __cplusplus >= 201103L
#include <ccomplex>
#include <cfenv>
#include <cinttypes>
#include <cstdalign>
#include <cstdbool>
#include <cstdint>
#include <ctgmath>
#include <cwchar>
#include <cwctype>
#endif

// C++
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>

#if __cplusplus >= 201103L
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#endif

//#include <bits/stdc++.h>
using namespace std;

vector<long long int>RMQ;
long long int n;

void init( int n_ ) {
	n = 1LL;
	while( n < n_ ) {
		n <<= 1LL;
	}
	RMQ = vector<long long int>( 2LL * n - 1, powl( 2LL, 31LL ) - 1LL );
}

//k番目の値をaに変更
void update( long long int k, long long int a ) {
	k += n - 1;
	RMQ[k] = a;
	while( k > 0 ) {
		k = (k - 1) / 2;
		RMQ[k] = min( RMQ[k * 2 + 1], RMQ[k * 2 + 2] );
	}
}

//query(a,b,0,0,n)で呼び出すと、[a,b)の最小値が返る。
long long int query( long long int a, long long int b, long long int k, long long int l, long long int r ) {
	if( r <= a || b <= l ) {
		return powl( 2LL, 31LL ) - 1LL;
	}
	if( a <= l && r <= b ) {
		return RMQ[k];
	} else {
		long long int vl = query( a, b, k * 2 + 1, l, (l + r) / 2 );
		long long int vr = query( a, b, k * 2 + 2, (l + r) / 2, r );
		return min( vl, vr );
	}
}

int main() {
	long long int n_, q;
	cin >> n_ >> q;
	init( n_ );
	for( size_t i = 0; i < q; i++ ) {
		long long int c, x, y;
		cin >> c >> x >> y;
		if( c == 0 ) {
			update( x, y );
		} else {
			cout << query( x, y + 1, 0, 0, n ) << endl;
		}
	}
}