#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
	std::set<T> s3;
	for (typename std::set<T>::iterator it = s1.begin(); it != s1.end(); ++it) //does a O(logn) function n times so O(nlogn)
	{
		typename std::set<T>::iterator itr = s2.find(*it);
		if (itr != s2.end()) //if iterator to value is found in s1 and s2, insert it to s3
		{
			s3.insert(*it);
		}
	}
	return s3;

}
template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
	std::set<T> s3;

	for (typename std::set<T>::iterator i = s1.begin(); i != s1.end(); ++i)
	{
		s3.insert(*i);
	}

	for (typename std::set<T>::iterator i = s2.begin(); i != s2.end(); ++i)
	{
		if (s3.find(*i) == s3.end()) //if iterator to value is found in either s1 or s2, insert into s3
		{
			s3.insert(*i);
		}
	} 
	return s3;
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
