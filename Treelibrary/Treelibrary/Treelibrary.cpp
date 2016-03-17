// Treelibrary.cpp : メイン プロジェクト ファイルです。

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

template <typename D, typename T = D>
class Tree
{
public:
	Tree( long long int size = 0, D InitialValueArg = D() ) {
		long long int n = 1LL;
		CalcTree.emplace_back( vector<T>( n ) );
		while( n <= size ) {
			n <<= 1LL;
			addOneLine( n );
		}
		InitialValue = InitialValueArg;
		Data.resize( n, InitialValue );
		for( size_t i = 0; i < Data.size(); i++ ) {
			update( i, Data[i] );
		}
		MaxSize = n;
		NowIndex = 0LL;
	}

	virtual T preprocessing( D a ) {
		return T( a );
	}

	virtual T treeupdate( T a, T b ) {
		return a;
	}

	void update( long long int idx, D data ) {
		Data[idx] = data;
		(*(CalcTree.rbegin()))[idx] = preprocessing( data );
		for( auto ite = CalcTree.rbegin(); ite + 1 < CalcTree.rend(); ) {
			idx >>= 1LL;
			T updatedata = treeupdate( (*ite)[idx * 2], (*ite)[idx * 2 + 1] );
			ite++;
			if( (*ite)[idx] != updatedata ) {
				(*ite)[idx] = updatedata;
			} else {
				break;
			}
		}
	}

	void show() {
		for( auto x : CalcTree ) {
			for( auto y : x ) {
				cout << y << " ";
			}
			cout << endl;
		}
	}

	void push( D data ) {
		if( NowIndex == MaxSize ) {
			MaxSize <<= 1LL;
			addOneLine( MaxSize );
			vector<D>Datamemo( MaxSize, InitialValue );
			copy( Data.begin(), Data.end(), Datamemo.begin() );
			for( long long int i = 0; i < Datamemo.size(); i++ ) {
				update( i, Datamemo[i] );
			}
		}
		Data[NowIndex] = data;
		update( NowIndex, data );
		NowIndex++;
	}

	T range( long long int l, long long int r ) {
		return rangeProcessing( 0, l, r, 0, 0, MaxSize );
	}

	long long int t() {
		return 10;
	}

private:
	vector<vector<T>> CalcTree;
	vector<D> Data;
	long long int MaxSize;
	long long int NowIndex;
	D InitialValue;

	void addOneLine( long long int n ) {
		CalcTree.emplace_back( vector<T>( n ) );
	}

	T rangeProcessing( long long int d, long long int a, long long int b, long long int k, long long int l, long long int r ) {
		if( !(r <= a || b <= l) && d < CalcTree.size() ) {
			if( a <= l&&r <= b ) {
				return CalcTree[d][k];
			} else {
				return treeupdate( rangeProcessing( d + 1, a, b, k * 2, l, (l + r) / 2 ), rangeProcessing( d + 1, a, b, k * 2 + 1, (l + r) / 2, r ) );
			}
		}
		return InitialValue;
	}
};

class Takoyaki : public Tree<pair<long double, long double>>
{
public:
	Takoyaki( long long int a, pair<long double, long double> b ) :Tree( a, b ) {

	}
	pair<long double, long double> treeupdate( pair<long double, long double> a, pair<long double, long double> b ) {
		return make_pair( b.first*a.first, b.first*a.second + b.second );
	}
};

int main() {
	long long int N, M;
	cin >> N >> M;
	pair<long double, long double> ans = make_pair( 1, 1 );
	vector<pair<long long int, pair<long double, long double>>>data( M );
	set<long long int>Pset;
	for( size_t i = 0; i < M; i++ ) {
		cin >> data[i].first >> data[i].second.first >> data[i].second.second;
		Pset.insert( data[i].first );
	}
	map<long long int, long long int>Pmap;
	long long int x = 0;
	for( auto s : Pset ) {
		Pmap[s] = x++;
	}
	Takoyaki T( Pset.size(), make_pair( 1, 0 ) );
	for( size_t i = 0; i < M; i++ ) {
		T.update( Pmap[data[i].first], data[i].second );
		auto nowF = T.range( 0, N + 1 );
		auto nowO = nowF.first + nowF.second;
		ans.first = max( ans.first, nowO );
		ans.second = min( ans.second, nowO );
	}
	cout << fixed << setprecision( 20 ) << ans.second << endl;
	cout << fixed << setprecision( 20 ) << ans.first << endl;

	return 0;
}